package com.haypi.billing;

import org.json.JSONException;
import org.json.JSONObject;

import com.haypi.framework.net.HaypiNetManager;

public final class BillingPayload {
	public final String id;
	public final String name;
	public final int paymentId;

	private BillingPayload(String id, String name, int paymentId) {
		this.id = id;
		this.name = name;
		this.paymentId = paymentId;
	}

	BillingPayload() {
		id = HaypiNetManager.GetInstance().GetUIDForSocket();
		name = HaypiNetManager.GetInstance().GetUsername();
		paymentId = BillingPayment.get();
	}

	public final JSONObject toJson() {
		JSONObject json = new JSONObject();
		try {
			json.put("ID", id);
			json.put("NAME", name);
			json.put("PAYMENTID", paymentId);
		} catch (JSONException e) {
		}
		return json;
	}

	public static BillingPayload fromJson(String json) throws JSONException {
		return fromJson(new JSONObject(json));
	}

	public static BillingPayload fromJson(JSONObject json) {
		return new BillingPayload(json.optString("ID"), json.optString("NAME"), json.optInt("PAYMENTID"));
	}
}