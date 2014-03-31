package com.haypi.share.facebook;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.MalformedURLException;

import android.content.Intent;
import android.os.Bundle;

import com.facebook.android.AsyncFacebookRunner;
import com.facebook.android.DialogError;
import com.facebook.android.Facebook;
import com.facebook.android.Facebook.DialogListener;
import com.facebook.android.FacebookError;
import com.haypi.share.ShareListener;
import com.haypi.share.ShareSystem;
import com.haypi.share.ShareType;

public class FacebookSharer {
	private static final String[] PERMISSIONS = new String[] { "publish_stream", "read_stream" };
	public static final String kAppID = "facebook.appid";
	public static final String kAppSecretKey = "facebook.appsecretkey";

	private static Facebook facebook;
	private static AsyncFacebookRunner asyn;

	public static void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (facebook != null) {
			facebook.authorizeCallback(requestCode, resultCode, data);
		}
	}

	public static void share(final ShareListener listener) {
		if (facebook == null) {
			facebook = new Facebook(ShareSystem.getParam(kAppID));
			SessionStore.restore(facebook, ShareSystem.activity);
			asyn = new AsyncFacebookRunner(facebook);
		}
		ShareSystem.d("check session");
		if (!facebook.isSessionValid()) {
			ShareSystem.d("session is invalid");
			auth(listener);
		} else {
			ShareSystem.d("session is valid");
			doShare(asyn, listener);
		}
	}

	private static void auth(final ShareListener listener) {
		ShareSystem.d("start authorize");
		facebook.authorize(ShareSystem.activity, PERMISSIONS, ShareType.Facebook.getRequestCode(), new DialogListener() {
			public void onComplete(Bundle values) {
				ShareSystem.d("onAuthSucceed");
				doShare(asyn, listener);
			}

			public void onFacebookError(FacebookError error) {
				ShareSystem.d("onFacebookError %1$d %2$s %3$s", error.getErrorCode(), error.getErrorType(), error.getMessage());
				ShareSystem.postResult(listener, ShareListener.FAIL_LOGIN);
			}

			public void onError(DialogError error) {
				ShareSystem.d("onError %s", error.getMessage());
				ShareSystem.postResult(listener, ShareListener.FAIL_LOGIN);
			}

			public void onCancel() {
				ShareSystem.d("onCancel");
				ShareSystem.postResult(listener, ShareListener.CACEL);
			}
		});
	}

	private static void doShare(AsyncFacebookRunner asyn, final ShareListener listener) {
		ShareSystem.d("post content");
		Bundle parameters = new Bundle();
		parameters.putString("method", "stream.publish");
		parameters.putString("message", ShareSystem.getContent());
		asyn.request(parameters, new AsyncFacebookRunner.RequestListener() {
			public void onComplete(String response, Object state) {
				ShareSystem.d("onComplete %s", response);
				ShareSystem.postResult(listener, ShareListener.SUCCESS);
			}

			public void onIOException(IOException e, Object state) {
				e.printStackTrace();
				ShareSystem.d("onIOException %s", e.getMessage());
				ShareSystem.postResult(listener, ShareListener.FAIL);
			}

			public void onFileNotFoundException(FileNotFoundException e, Object state) {
				e.printStackTrace();
				ShareSystem.d("onFileNotFoundException %s", e.getMessage());
				ShareSystem.postResult(listener, ShareListener.FAIL);
			}

			public void onMalformedURLException(MalformedURLException e, Object state) {
				e.printStackTrace();
				ShareSystem.d("onMalformedURLException %s", e.getMessage());
				ShareSystem.postResult(listener, ShareListener.FAIL);
			}

			public void onFacebookError(FacebookError e, Object state) {
				e.printStackTrace();
				ShareSystem.d("onFacebookError %s", e.getMessage());
				ShareSystem.postResult(listener, ShareListener.FAIL);
			}
		});
	}
}