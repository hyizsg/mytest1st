package com.haypi.share.twitter;


interface DialogListener {
	public void onTwitterError(TwitterError e);
	public void onError(DialogError e);
	public void onCancel();
	public void onComplete(String url);
}