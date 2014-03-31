package com.haypi.util;

import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;

abstract public class Timer {
	private static final long INFINITE = Long.MIN_VALUE;
	private final long mDelayTime;
	private final long mCountdownInterval;
	private final long mMillisInFuture;
	private long mStopTimeInFuture;

	private final boolean mRepeat;
	private final boolean mInfinite;
	private boolean firstRun = true;

	public Timer(long delayTime) {
		this(delayTime, 0);
	}

	public Timer(long delayTime, long countDownInterval) {
		this(delayTime, countDownInterval, INFINITE);
	}

	public Timer(long delayTime, long countDownInterval, long millisInFuture) {
		this.mDelayTime = delayTime;
		this.mCountdownInterval = countDownInterval;
		this.mMillisInFuture = millisInFuture;
		this.mRepeat = countDownInterval > 0;
		this.mInfinite = mRepeat && millisInFuture == INFINITE;
	}

	public final void cancel() {
		mHandler.removeMessages(MSG);
	}

	public synchronized final Timer start() {
		mHandler.sendMessageDelayed(mHandler.obtainMessage(MSG), mDelayTime);
		return this;
	}

	protected void onTick() {
	}

	protected void onFinish() {
	}

	private static final int MSG = 1;
	private Handler mHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			synchronized (Timer.this) {
				if (mInfinite) {
					invokeOnTick();
				} else if (!mRepeat || mMillisInFuture <= 0) {
					onFinish();
					return;
				} else {
					if (firstRun) {
						firstRun = false;
						mStopTimeInFuture = getTime() + mMillisInFuture;
					}
					final long millisLeft = mStopTimeInFuture - getTime();
					if (millisLeft <= 0) {
						onFinish();
					} else {
						invokeOnTick();
					}
				}
			}
		}

		private void invokeOnTick() {
			long lastTickStart = getTime();
			Timer.this.onTick();
			long delay = lastTickStart + mCountdownInterval - getTime();
			while (delay < 0)
				delay += mCountdownInterval;
			sendMessageDelayed(obtainMessage(MSG), delay);
		}
	};

	private static long getTime() {
		return SystemClock.elapsedRealtime();
	}
}
