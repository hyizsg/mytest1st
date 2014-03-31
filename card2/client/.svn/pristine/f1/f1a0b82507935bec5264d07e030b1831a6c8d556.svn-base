package com.haypi.billing.google.v3;

import java.util.ArrayList;

import org.json.JSONException;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.RemoteException;
import android.text.TextUtils;

import com.haypi.billing.BillingItem;
import com.haypi.billing.BillingListener;
import com.haypi.billing.google.v3.impl.IabHelper;
import com.haypi.billing.google.v3.impl.IabResult;
import com.haypi.billing.google.v3.impl.Inventory;
import com.haypi.billing.google.v3.impl.Purchase;
import com.haypi.billing.google.v3.impl.SkuDetails;
import com.haypi.framework.util.HaypiLog;
import com.haypi.gameframework.GameFramework;

public abstract class BillingService extends com.haypi.billing.BillingService {
	protected String base64PublicKey;
	private final ArrayList<String> SKUs = new ArrayList<String>();
	protected IabHelper mHelper;
	protected int purchase_request_code = 1001;

	@Override
	public final boolean isSuccess(int code) {
		return code == IabHelper.BILLING_RESPONSE_RESULT_OK;
	}

	@Override
	public final String getMessage(int code) {
		String strID = ("GOOGLE_BILLING_MESSAGE_" + code).replace('-', '_');
		String message = GameFramework.getString(strID);
		if (TextUtils.isEmpty(message)) {
			return GameFramework.getString("GOOGLE_BILLING_MESSAGE_UNKNOW", code);
		}
		return message;
	}

	protected abstract void verify(Purchase purchase);

	protected abstract String getPayload();

	@Override
	protected final void doInit(final Context ctx) {
		mHelper = new IabHelper(ctx.getApplicationContext(), base64PublicKey);
		mHelper.enableDebugLogging(enableDebug, tag);
		mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {
			public void onIabSetupFinished(IabResult result) {
				HaypiLog.d(tag, "Setup finished.");
				if (result.isFailure()) {
					HaypiLog.d(tag, "Setup fail: %s", result.toString());
					postInitResult(false);
				} else {
					querySkuDetailsAsync();
				}
			}
		});
	}

	private void querySkuDetailsAsync() {
		mHelper.flagStartAsync("querySkuDetails");
		final ArrayList<String> skuList = BillingItem.getSKUs();
		(new Thread(new Runnable() {
			public void run() {
				IabResult result = new IabResult(IabHelper.BILLING_RESPONSE_RESULT_OK, "querySkuDetails successful.");
				final ArrayList<SkuDetails> skuDetailList = new ArrayList<SkuDetails>();
				try {
					querySkuDetails(skuList, skuDetailList);
				} catch (RemoteException e) {
					result = new IabResult(IabHelper.IABHELPER_REMOTE_EXCEPTION, "Remote exception while querySkuDetails.");
				} catch (JSONException e) {
					result = new IabResult(IabHelper.IABHELPER_BAD_RESPONSE, "Error parsing JSON response while querySkuDetails.");
				}
				mHelper.flagEndAsync();
				final IabResult _result = result;
				runOnUIThread(new Runnable() {
					@Override
					public void run() {
						if (_result.isFailure()) {
							HaypiLog.d(tag, "Setup fail: %s", _result.toString());
							postInitResult(false);
						} else {
							updateBillingItems(skuDetailList);
							postInitResult(true);
						}
					}
				});
			}
		})).start();
	}

	private void updateBillingItems(ArrayList<SkuDetails> skuDetailList) {
		SKUs.clear();
		for (SkuDetails skuDetails : skuDetailList) {
			HaypiLog.d(tag, skuDetails.toString());
			BillingItem item = BillingItem.getBySKU(skuDetails.getSku());
			String title = skuDetails.getTitle();
			int index = title.lastIndexOf('(');
			if (index > -1) {
				title = title.substring(0, index);
			}
			String description = skuDetails.getDescription();
			String price = skuDetails.getPrice();

			item.setTitle_CN(null);
			item.setTitle(title);
			item.setDescription_CN(null);
			item.setDescription(description);
			item.setPrice(price);

			SKUs.add(skuDetails.getSku());
		}
		// notify items updated
		BillingItem.setItems(BillingItem.getItems());
	}

	private int querySkuDetails(ArrayList<String> skuList, ArrayList<SkuDetails> skuDetailList) throws RemoteException, JSONException {
		String itemType = IabHelper.ITEM_TYPE_INAPP;
		mHelper.logDebug("Querying SKU details.");
		if (skuList.size() == 0) {
			mHelper.logDebug("queryPrices: nothing to do because there are no SKUs.");
			return IabHelper.BILLING_RESPONSE_RESULT_OK;
		}

		Bundle querySkus = new Bundle();
		querySkus.putStringArrayList(IabHelper.GET_SKU_DETAILS_ITEM_LIST, skuList);
		Bundle skuDetails = mHelper.mService.getSkuDetails(3, mHelper.mContext.getPackageName(), itemType, querySkus);

		if (!skuDetails.containsKey(IabHelper.RESPONSE_GET_SKU_DETAILS_LIST)) {
			int response = mHelper.getResponseCodeFromBundle(skuDetails);
			if (response != IabHelper.BILLING_RESPONSE_RESULT_OK) {
				mHelper.logDebug("getSkuDetails() failed: " + IabHelper.getResponseDesc(response));
				return response;
			} else {
				mHelper.logError("getSkuDetails() returned a bundle with neither an error nor a detail list.");
				return IabHelper.IABHELPER_BAD_RESPONSE;
			}
		}

		ArrayList<String> responseList = skuDetails.getStringArrayList(IabHelper.RESPONSE_GET_SKU_DETAILS_LIST);

		for (String thisResponse : responseList) {
			SkuDetails d = new SkuDetails(itemType, thisResponse);
			mHelper.logDebug("Got sku details: " + d);
			skuDetailList.add(d);
		}
		return IabHelper.BILLING_RESPONSE_RESULT_OK;
	}

	@Override
	protected final void doLoadData(Context ctx) {
		mHelper.queryInventoryAsync(false, mGotInventoryListener);
	}

	@Override
	protected final void doOrder(final Activity activity, final BillingItem item, final BillingListener listener) {
		if (!isAvailable()) {
			postBillingResult(item, listener, IabHelper.BILLING_RESPONSE_RESULT_BILLING_UNAVAILABLE);
			return;
		}
		String payload = getPayload();
		HaypiLog.d(tag, "payload: " + payload);
		mHelper.launchPurchaseFlow(activity, item.getSku(), purchase_request_code, new IabHelper.OnIabPurchaseFinishedListener() {
			public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
				HaypiLog.d(tag, "Purchase finished: " + result + ", purchase: " + purchase);
				if (result.isFailure()) {
					HaypiLog.d("Error purchasing: " + result);
					postBillingResult(item, listener, result.getResponse());
					return;
				}
				HaypiLog.d(tag, "Purchase successful.");
				HaypiLog.d(tag, "Consuming %s", purchase.getSku());
				verify(purchase);
				postBillingResult(item, listener, result.getResponse());
			}
		}, payload);
	}

	@Override
	public final String showPurchaseList(Activity act) {
		return super.showPurchaseList(act);
	}

	@Override
	public final boolean handleActivityResult(int requestCode, int resultCode, Intent data) {
		return isAvailable() && mHelper.handleActivityResult(requestCode, resultCode, data);
	}

	public final void consumeAsync(final Purchase purchase) {
		addTask(new Runnable() {
			@Override
			public void run() {
				mHelper.consumeAsync(purchase, mConsumeFinishedListener);
			}
		});
	}

	private IabHelper.QueryInventoryFinishedListener mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
		public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
			HaypiLog.d(tag, "Query inventory finished.");
			if (result.isFailure()) {
				HaypiLog.d(tag, "Failed to query inventory: " + result);
			} else {
				HaypiLog.d(tag, "Query inventory was successful.");
				for (String SKU : SKUs) {
					Purchase purchase = inventory.getPurchase(SKU);
					if (purchase != null) {
						verify(purchase);
					}
				}
			}
			doNext();
		}
	};

	private IabHelper.OnConsumeFinishedListener mConsumeFinishedListener = new IabHelper.OnConsumeFinishedListener() {
		public void onConsumeFinished(Purchase purchase, IabResult result) {
			HaypiLog.d(tag, "Consumption finished. Purchase: " + purchase + ", result: " + result);
			if (result.isSuccess()) {
				HaypiLog.d(tag, "Consumption successful. Provisioning.");
			} else {
				HaypiLog.d(tag, "Error while consuming: " + result);
			}
			HaypiLog.d(tag, "End consumption flow.");
			doNext();
		}
	};
}