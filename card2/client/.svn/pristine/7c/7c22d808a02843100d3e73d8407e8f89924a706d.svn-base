package com.haypi.billing;

import java.util.ArrayList;

import org.json.JSONObject;

import android.text.TextUtils;

import com.haypi.util.HaypiUtil;

public final class BillingItem {
	private static ArrayList<BillingItemListener> listeners = new ArrayList<BillingItemListener>();

	public static void addBillingItemListener(BillingItemListener listener) {
		if (listener == null)
			throw new NullPointerException();
		if (!listeners.contains(listener)) {
			listeners.add(listener);
		}
	}

	public static void removeListener(BillingItemListener listener) {
		listeners.remove(listener);
	}

	private static void onItemsUpdate() {
		int n = listeners.size();
		if (n == 0)
			return;
		BillingItemListener[] __listeners = listeners.toArray(new BillingItemListener[n]);
		for (BillingItemListener listener : __listeners) {
			listener.onBillingItemsUpdate();
		}
	}

	private static ArrayList<BillingItem> items = new ArrayList<BillingItem>();

	public static void setItems(ArrayList<BillingItem> items) {
		BillingItem.items = items;
		onItemsUpdate();
	}

	public static ArrayList<BillingItem> getItems() {
		return items;
	}

	public static BillingItem getBySKU(String sku) {
		for (BillingItem item : items)
			if (sku.equals(item.sku))
				return item;
		return null;
	}

	public static ArrayList<String> getSKUs() {
		ArrayList<String> SKUs = new ArrayList<String>();
		for (BillingItem item : items)
			SKUs.add(item.sku);
		return SKUs;
	}

	private String sku;
	private String priceAndSymbol;
	private double price;
	private String priceSymbol;
	private String title;
	private String title_CN;
	private String description;
	private String description_CN;
	private int icon;
	private int coin;
	private int bonus;
	private String tip;
	private int id;
	private JSONObject info;

	public JSONObject getInfo() {
		return info;
	}

	public void setInfo(JSONObject info) {
		this.info = info;
	}

	public String getSku() {
		return sku;
	}

	public void setSku(String sku) {
		this.sku = sku;
	}

	public String getTitle() {
		if (HaypiUtil.isCN() && !TextUtils.isEmpty(title_CN))
			return title_CN;
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public void setTitle_CN(String title_CN) {
		this.title_CN = title_CN;
	}

	public String getDescription() {
		if (HaypiUtil.isCN() && !TextUtils.isEmpty(description_CN))
			return description_CN;
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public void setDescription_CN(String description_CN) {
		this.description_CN = description_CN;
	}

	public int getIcon() {
		return icon;
	}

	public void setIcon(int icon) {
		this.icon = icon;
	}

	public int getCoin() {
		return coin;
	}

	public void setCoin(int coin) {
		this.coin = coin;
	}

	public int getBonus() {
		return bonus;
	}

	public void setBonus(int bonus) {
		this.bonus = bonus;
	}

	public String getTip() {
		return tip;
	}

	public void setTip(String tip) {
		this.tip = tip;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public double getPrice() {
		return price;
	}

	public String getPriceSymbol() {
		return priceSymbol;
	}

	public String getPriceAndSymbol() {
		return priceAndSymbol;
	}

	public void setPrice(double price, String priceSymbol) {
		this.price = price;
		this.priceSymbol = priceSymbol;
		this.priceAndSymbol = String.format("%1$.2f %2$s", price, priceSymbol);
	}

	public void setPriceAndSymbol(String priceAndSymbol) {
		this.priceAndSymbol = priceAndSymbol;
	}

	public void setPrice(String priceAndSymbol) {
		this.priceAndSymbol = priceAndSymbol = priceAndSymbol.trim();
		int len = priceAndSymbol.length();
		if (Character.isDigit(priceAndSymbol.charAt(0))) {
			for (int i = len - 1; i > 0; i--) {
				try {
					priceSymbol = priceAndSymbol.substring(i).trim();
					price = Double.parseDouble(priceAndSymbol.substring(0, i).trim());
					break;
				} catch (NumberFormatException e) {
				}
			}
		} else {
			for (int i = 1; i < len; i++) {
				try {
					priceSymbol = priceAndSymbol.substring(0, i).trim();
					price = Double.parseDouble(priceAndSymbol.substring(i).trim());
					break;
				} catch (NumberFormatException e) {
				}
			}
		}
	}

}