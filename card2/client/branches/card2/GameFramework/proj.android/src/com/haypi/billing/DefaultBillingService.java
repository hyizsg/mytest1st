package com.haypi.billing;

import android.app.Activity;
import android.content.Context;

class DefaultBillingService extends BillingService {
	@Override
	public boolean isSuccess(int code) {
		return false;
	}

	@Override
	protected void doInit(Context ctx) {
		postInitResult(false);
	}

	@Override
	public String getMessage(int code) {
		return "BillingService have NOT implement~";
	}

	@Override
	protected void doOrder(Activity activity, BillingItem item, BillingListener listener) {
		postBillingResult(item, listener, 3);
	}
}