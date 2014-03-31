package com.haypi.share.twitter;

public class TwitterError extends Throwable {

	private static final long serialVersionUID = 1L;

	private int mErrorCode = 0;
	private String mErrorType;

	public TwitterError(String message) {
		super(message);
	}

	public TwitterError(String message, String type, int code) {
		super(message);
		mErrorType = type;
		mErrorCode = code;
	}

	public int getErrorCode() {
		return mErrorCode;
	}

	public String getErrorType() {
		return mErrorType;
	}
}
