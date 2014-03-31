package com.haypi.billing;

public interface BillingListener {
	void onBillingFinish(int code, BillingItem item);
}