package com.haypi.billing;

public class BillingPayment {
	private static int id;

	public static void create() {
		id = (int) (System.currentTimeMillis() / 1000);
	}

	public static int get() {
		return id;
	}
}
