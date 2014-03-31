package com.haypi.share.twitter;

import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;
import twitter4j.auth.AccessToken;
import twitter4j.auth.RequestToken;
import twitter4j.conf.Configuration;
import twitter4j.conf.ConfigurationBuilder;
import android.net.Uri;

import com.haypi.share.ShareListener;
import com.haypi.share.ShareSystem;

public class TwitterSharer {
	public static final String kConsumerKey = "twitter.appkey";
	public static final String kConsumerSecret = "twitter.appsecret";

	static final String CALLBACK_URL = "haypi://twitteroauth";
	static final String OAUTH_VERIFIER = "oauth_verifier";

	private static ShareListener listener;

	private static Twitter twitter;
	private static RequestToken requestToken;

	private static Twitter createTwitter() {
		ConfigurationBuilder builder = new ConfigurationBuilder();
		builder.setOAuthConsumerKey(ShareSystem.getParam(kConsumerKey)); // consumer_key
		builder.setOAuthConsumerSecret(ShareSystem.getParam(kConsumerSecret)); // consumer_secret
		Configuration conf = builder.build();
		Twitter twitter = new TwitterFactory(conf).getInstance();
		twitter.setOAuthAccessToken(null);
		return twitter;
	}

	public static void share(final ShareListener listener) {
		TwitterSharer.listener = listener;
		if (twitter == null) {
			twitter = createTwitter();
		}
		if (!SessionStore.restore(twitter, ShareSystem.activity)) {
			twitter = createTwitter();
			auth();
		} else {
			doShare();
		}
	}

	private static void postResult(int code) {
		ShareListener listener = TwitterSharer.listener;
		TwitterSharer.listener = null;
		ShareSystem.postResult(listener, code);
	}

	private static void auth() {
		ShareSystem.d("start authorize");
		askOAuth();
	}

	private static void doShare() {
		ShareSystem.d("post content");
		new Thread() {
			public void run() {
				try {
					twitter.updateStatus(ShareSystem.getContent());
					postResult(ShareListener.SUCCESS);
				} catch (TwitterException e) {
					e.printStackTrace();
					ShareSystem.d("onFail:%s", e.getMessage());
					if (e.getErrorCode() == 187) {
						postResult(ShareListener.FAIL_REPEAT_CONTENT);
					} else {
						postResult(ShareListener.FAIL);
					}

				}
			}
		}.start();
	}

	private static void askOAuth() {
		new Thread() {
			public void run() {
				try {
					final RequestToken requestToken = twitter.getOAuthRequestToken(CALLBACK_URL);
					final String authUrl = requestToken.getAuthenticationURL();
					ShareSystem.d("authUrl=" + authUrl);
					ShareSystem.runOnUiThread(new Runnable() {
						@Override
						public void run() {
							TwitterSharer.requestToken = requestToken;
							popAuthDialog(authUrl);
						}
					});
				} catch (Exception e) {
					e.printStackTrace();
					ShareSystem.d("onFail:%s", e.getMessage());
					postResult(ShareListener.FAIL_LOGIN);
				}
			}
		}.start();
	}

	private static void popAuthDialog(String authUrl) {
		new TwDialog(ShareSystem.activity, authUrl, new DialogListener() {
			@Override
			public void onComplete(String url) {
				if (url != null && url.startsWith(CALLBACK_URL)) {
					String verifier = Uri.parse(url).getQueryParameter(OAUTH_VERIFIER);
					ShareSystem.d("verifier=" + verifier);
					if (verifier == null) {
						postResult(ShareListener.FAIL_LOGIN);
						return;
					}
					AccessToken at;
					try {
						at = twitter.getOAuthAccessToken(requestToken, verifier);
						twitter.setOAuthAccessToken(at);
						SessionStore.save(twitter, ShareSystem.activity);
					} catch (TwitterException e) {
						e.printStackTrace();
						postResult(ShareListener.FAIL_LOGIN);
						return;
					}
					doShare();
				}
			}

			@Override
			public void onTwitterError(TwitterError error) {
				ShareSystem.d("onTwitterError %1$d %2$s %3$s", error.getErrorCode(), error.getErrorType(), error.getMessage());
				ShareSystem.postResult(listener, ShareListener.FAIL_LOGIN);
			}

			@Override
			public void onError(DialogError error) {
				ShareSystem.d("onError %s", error.getMessage());
				ShareSystem.postResult(listener, ShareListener.FAIL_LOGIN);
			}

			@Override
			public void onCancel() {
				ShareSystem.d("onCancel");
				ShareSystem.postResult(listener, ShareListener.FAIL_LOGIN);
			}

		}).show();
	}
}