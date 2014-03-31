package com.haypi.widget;

import android.annotation.TargetApi;
import android.content.Context;
import android.os.Build;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.view.MotionEvent;

public class ScrollView extends android.widget.ScrollView {
	private static final int CHECK_SCROLL_END = 1234;
	private Handler handler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			if (msg.what == CHECK_SCROLL_END) {
				checkScrollEnd();
			}
		}
	};
	private OnScrollListener onScrollListener;
	private boolean isScrolling;
	private boolean isTouching;

	private float maxOverScroll = 0.5f;

	public ScrollView(Context context) {
		super(context);
		init(context);
	}

	public ScrollView(Context context, AttributeSet attrs) {
		super(context, attrs);
		init(context);
	}

	public ScrollView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		init(context);
	}

	private void init(Context context) {
	}

	@TargetApi(Build.VERSION_CODES.GINGERBREAD)
	@Override
	protected boolean overScrollBy(int deltaX, int deltaY, int scrollX, int scrollY, int scrollRangeX, int scrollRangeY, int maxOverScrollX, int maxOverScrollY, boolean isTouchEvent) {
		if (isTouchEvent) {
			maxOverScrollY = getMaxOverScrollY();
		}
		return super.overScrollBy(deltaX, deltaY, scrollX, scrollY, scrollRangeX, scrollRangeY, maxOverScrollX, maxOverScrollY, isTouchEvent);
	}

	private int getMaxOverScrollY() {
		int overScroll = (int) (this.maxOverScroll * getHeight());
		return Math.max(0, overScroll);
	}

	public void setMaxOverScroll(float maxOverScroll) {
		this.maxOverScroll = maxOverScroll;
	}

	@Override
	protected void onScrollChanged(int scrollX, int scrollY, int oldScrollX, int oldScrollY) {
		super.onScrollChanged(scrollX, scrollY, oldScrollX, oldScrollY);
		checkScroll(scrollX, scrollY, oldScrollX, oldScrollY);
	}

	private void checkScroll(int scrollX, int scrollY, int oldScrollX, int oldScrollY) {
		if (onScrollListener == null) {
			isScrolling = false;
			return;
		}
		if (scrollX != oldScrollX || scrollY != oldScrollY) {
			if (!isScrolling) {
				isScrolling = true;
				onScrollListener.onScrollStart(this, oldScrollX, oldScrollY);
			} else {
				onScrollListener.onScroll(this);
			}
		}
		if (isScrolling) {
			checkScrollEndLater();
		}
	}

	private void checkScrollEndLater() {
		handler.removeMessages(CHECK_SCROLL_END);
		handler.sendEmptyMessageDelayed(CHECK_SCROLL_END, 100);
	}

	private void checkScrollEnd() {
		if (onScrollListener == null) {
			isScrolling = false;
			return;
		}
		if (!isScrolling)
			return;
		if (isTouching) {
			checkScrollEndLater();
			return;
		}
		isScrolling = false;
		onScrollListener.onScrollEnd(this);
	}

	@Override
	public boolean onTouchEvent(MotionEvent ev) {
		switch (ev.getAction() & MotionEvent.ACTION_MASK) {
		case MotionEvent.ACTION_DOWN:
			isTouching = true;
			break;
		case MotionEvent.ACTION_UP:
			isTouching = false;
			checkScrollEndLater();
			break;
		}
		return super.onTouchEvent(ev);
	}

	public boolean isScrolling() {
		return isScrolling;
	}

	public void setOnScrollListener(OnScrollListener onScrollListener) {
		this.onScrollListener = onScrollListener;
	}
}