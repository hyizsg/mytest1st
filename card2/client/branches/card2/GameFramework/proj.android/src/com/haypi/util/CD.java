package com.haypi.util;

import java.util.Locale;

import android.os.SystemClock;

public class CD {
	public static final long SECOND = 1000;
	public static final long MINUTE = SECOND * 60;
	public static final long HOUR = MINUTE * 60;
	public static final long DAY = HOUR * 24;

	private static long now() {
		return SystemClock.elapsedRealtime();
	}

	public static String toHHMMSS(long leftTime) {
		if (leftTime < SECOND) {
			return "00:00:00";
		}
		long hour = leftTime / HOUR;
		long minute = leftTime / MINUTE % 60;
		long second = leftTime / SECOND % 60;
		return String.format(Locale.ENGLISH, "%1$02d:%2$02d:%3$02d", hour, minute, second);
	}

	public static String toMMSS(long leftTime) {
		if (leftTime < SECOND) {
			return "00:00";
		}
		leftTime += 999;
		long minute = leftTime / MINUTE;
		long second = leftTime / SECOND % 60;
		return String.format(Locale.ENGLISH, "%1$02d:%2$02d", minute, second);
	}

	private long endTime;
	private long leftTime;
	private boolean pause;

	public CD() {

	}

	public CD(long leftTime) {
		setLeftTime(leftTime);
	}

	public synchronized long getLeftTime() {
		return pause ? leftTime : endTime - now();
	}

	public synchronized void setLeftTime(long leftTime) {
		if (pause) {
			this.leftTime = leftTime;
		} else {
			this.endTime = leftTime + now();
		}
	}

	public boolean isEnd() {
		return getLeftTime() <= 0;
	}

	public synchronized void pause() {
		if (!pause) {
			pause = true;
			leftTime = endTime - now();
		}
	}

	public synchronized void resume() {
		if (pause) {
			pause = false;
			endTime = leftTime + now();
		}
	}

	public String toHHMMSS() {
		return toHHMMSS(getLeftTime());
	}

	public String toMMSS() {
		return toMMSS(getLeftTime());
	}
}