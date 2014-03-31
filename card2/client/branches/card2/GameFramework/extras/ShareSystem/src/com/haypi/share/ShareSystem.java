package com.haypi.share;

import java.util.HashMap;

import android.app.Activity;
import android.content.Intent;

import com.haypi.framework.util.HaypiLog;
import com.haypi.share.facebook.FacebookSharer;
import com.haypi.share.sina.SinaWeiboSharer;
import com.haypi.share.twitter.TwitterSharer;

public class ShareSystem {
	private static final String tag = "share";
	public static final String kShareContent = "content";
	public static final String kMailSubject = "mail.subject";
	public static final String kMailChooserTitle = "mail.chooser.title";
	public static final String kWeiboAppID = SinaWeiboSharer.kAppID;
	public static final String kWeiboAppRedirectURI = SinaWeiboSharer.kAppRedirectURI;
	public static final String kFacebookAppID = FacebookSharer.kAppID;
	public static final String kTwitterConsumerKey = TwitterSharer.kConsumerKey;
	public static final String kTwitterConsumerSecret = TwitterSharer.kConsumerSecret;

	private static HashMap<String, String> params = new HashMap<String, String>();

	public static void setParam(String key, String value) {
		params.put(key, value);
	}

	public static String getParam(String key) {
		return params.get(key);
	}

	public static int REQUEST_CODE = 4567;
	public static Activity activity;
	private static ShareListener shareListener;

	public static void onCreate(Activity act) {
		ShareSystem.activity = act;
	}

	public static void onDestroy(Activity act) {
		ShareSystem.activity = null;
		shareListener = null;
	}

	public static void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode == REQUEST_CODE) {
			ShareListener listener = shareListener;
			shareListener = null;
			if (listener == null)
				return;
			int code;
			switch (resultCode) {
			case Activity.RESULT_OK:
				code = ShareListener.SUCCESS;
				break;
			default:
				code = ShareListener.FAIL;
				break;
			}
			listener.onShareFinish(code, null);
		} else if (requestCode == ShareType.Facebook.getRequestCode()) {
			FacebookSharer.onActivityResult(requestCode, resultCode, data);
		}
	}

	public static void share(ShareType type, ShareListener listener) {
		d("share with: %s", type.toString());
		switch (type) {
		case SinaWeibo:
			SinaWeiboSharer.share(listener);
			break;
		case Facebook:
			FacebookSharer.share(listener);
			break;
		case Twitter:
			TwitterSharer.share(listener);
			break;
		case SMS:
			shareViaSMS(listener);
			break;
		case Mail:
			shareViaMail(listener);
			break;
		}
	}

	private static void shareViaSMS(ShareListener listener) {
		shareListener = listener;
		Intent sendIntent = new Intent(Intent.ACTION_VIEW);
		sendIntent.putExtra("sms_body", getContent());
		sendIntent.setType("vnd.android-dir/mms-sms");
		activity.startActivityForResult(sendIntent, REQUEST_CODE);
	}

	private static void shareViaMail(ShareListener listener) {
		shareListener = listener;
		Intent sendIntent = new Intent(Intent.ACTION_SEND);
		sendIntent.setType("message/rfc822");
		sendIntent.putExtra(Intent.EXTRA_SUBJECT, params.get(kMailSubject));
		sendIntent.putExtra(Intent.EXTRA_TEXT, getContent());
		activity.startActivityForResult(Intent.createChooser(sendIntent, params.get(kMailChooserTitle)), REQUEST_CODE);
	}

	public static String getContent() {
		return params.get(kShareContent);
	}

	public static void postResult(final ShareListener listener, final int code) {
		postResult(listener, code, null);
	}

	public static void postResult(final ShareListener listener, final int code, final String result) {
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				listener.onShareFinish(code, result);
			}
		});
	}

	public static void d(String format, Object... args) {
		HaypiLog.d(tag, format, args);
	}

	public static void runOnUiThread(Runnable action) {
		activity.runOnUiThread(action);
	}
}