package com.haypi.share;

public enum ShareType {
	SinaWeibo, Facebook, Twitter, SMS, Mail;

	public int getRequestCode() {
		return ShareSystem.REQUEST_CODE + ordinal();
	}
}