package com.haypi.share.sina;

import java.io.IOException;

import org.json.JSONObject;

import android.os.Bundle;

import com.haypi.share.ShareListener;
import com.haypi.share.ShareSystem;
import com.weibo.sdk.android.Oauth2AccessToken;
import com.weibo.sdk.android.Weibo;
import com.weibo.sdk.android.WeiboAuthListener;
import com.weibo.sdk.android.WeiboDialogError;
import com.weibo.sdk.android.WeiboException;
import com.weibo.sdk.android.api.StatusesAPI;
import com.weibo.sdk.android.net.RequestListener;

public class SinaWeiboSharer {
	public static final String kAppID = "weibo.appid";
	public static final String kAppRedirectURI = "weibo.appredirecturi";

	public static void share(final ShareListener listener) {
		ShareSystem.d("check session");
		Oauth2AccessToken accessToken = AccessTokenKeeper.readAccessToken(ShareSystem.activity);
		if (!accessToken.isSessionValid()) {
			ShareSystem.d("session is invalid");
			auth(listener);
		} else {
			ShareSystem.d("session is valid");
			doShare(accessToken, listener);
		}
	}
	
	private static void auth(final ShareListener listener){
		ShareSystem.d("start authorize");
		Weibo weibo = Weibo.getInstance(ShareSystem.getParam(kAppID), ShareSystem.getParam(kAppRedirectURI));
		weibo.authorize(ShareSystem.activity, new WeiboAuthListener() {
			@Override
			public void onWeiboException(WeiboException e) {
				e.printStackTrace();
				ShareSystem.d("onWeiboException %s", e.getMessage());
				ShareSystem.postResult(listener, ShareListener.FAIL_LOGIN);
			}

			@Override
			public void onError(WeiboDialogError e) {
				e.printStackTrace();
				ShareSystem.d("WeiboDialogError %s", e.getMessage());
				ShareSystem.postResult(listener, ShareListener.FAIL_LOGIN);
			}

			@Override
			public void onComplete(Bundle values) {
				ShareSystem.d("onComplete %s", values.toString());
				String token = values.getString("access_token");
				String expires_in = values.getString("expires_in");
				Oauth2AccessToken accessToken = new Oauth2AccessToken(token, expires_in);
				AccessTokenKeeper.keepAccessToken(ShareSystem.activity, accessToken);
				doShare(accessToken, listener);
			}

			@Override
			public void onCancel() {
				ShareSystem.postResult(listener, ShareListener.FAIL_LOGIN);
			}
		});
	}

	private static void doShare(Oauth2AccessToken accessToken, final ShareListener listener) {
		ShareSystem.d("post content");
		StatusesAPI statusesAPI = new StatusesAPI(accessToken);
		statusesAPI.update(ShareSystem.getContent(), null, null, new RequestListener() {
			@Override
			public void onIOException(IOException e) {
				e.printStackTrace();
				ShareSystem.d("onIOException %s", e.getMessage());
				ShareSystem.postResult(listener, ShareListener.FAIL);
			}

			@Override
			public void onError(WeiboException e) {
				e.printStackTrace();
				ShareSystem.d("onError %s", e.getMessage());
				int error_code = 0;
				try {
					error_code = new JSONObject(e.getMessage()).getInt("error_code");
				} catch (Exception e2) {
				}
				if (error_code == 20019) {
					ShareSystem.postResult(listener, ShareListener.FAIL_REPEAT_CONTENT);
				} else {
					ShareSystem.postResult(listener, ShareListener.FAIL);
				}
			}

			@Override
			public void onComplete(String response) {
				ShareSystem.d("onComplete %s", response);
				ShareSystem.postResult(listener, ShareListener.SUCCESS);
			}
		});
	}
}