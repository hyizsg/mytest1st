package com.haypi.widget;

import android.annotation.TargetApi;
import android.content.Context;
import android.os.Build;
import android.util.AttributeSet;

public class ListView extends android.widget.ListView {

	public ListView(Context context) {
		super(context);
	}

	public ListView(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	public ListView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
	}

	@TargetApi(Build.VERSION_CODES.GINGERBREAD)
	@Override
	protected boolean overScrollBy(int deltaX, int deltaY, int scrollX, int scrollY, int scrollRangeX, int scrollRangeY, int maxOverScrollX, int maxOverScrollY, boolean isTouchEvent) {
		if (isTouchEvent) {
			maxOverScrollY = getHeight() / 2;
		}
		return super.overScrollBy(deltaX, deltaY, scrollX, scrollY, scrollRangeX, scrollRangeY, maxOverScrollX, maxOverScrollY, isTouchEvent);
	}
}