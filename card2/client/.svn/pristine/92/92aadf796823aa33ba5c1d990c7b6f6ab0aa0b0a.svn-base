package com.haypi.app;

import android.content.Context;

public class Dialog extends android.app.Dialog {
	public Dialog(Context context, boolean cancelable, OnCancelListener cancelListener) {
		super(context, cancelable, cancelListener);
	}

	public Dialog(Context context, int theme) {
		super(context, theme);
	}

	public Dialog(Context context) {
		super(context);
	}

	@Override
	protected void onStart() {
		super.onStart();
		DialogManager.add(this);
	}

	@Override
	protected void onStop() {
		super.onStop();
		DialogManager.remove(this);
	}
}