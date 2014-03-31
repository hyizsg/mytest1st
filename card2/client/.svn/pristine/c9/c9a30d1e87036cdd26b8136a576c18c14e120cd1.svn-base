/*
 * Copyright 2010 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.haypi.share.twitter;

import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.auth.AccessToken;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.text.TextUtils;

import com.haypi.share.ShareSystem;

public class SessionStore {

	private static final String TOKEN = "access_token";
	private static final String SECRET = "access_token_secret";
	private static final String KEY = "twitter-session";

	public static boolean save(Twitter twitter, Context context) {
		AccessToken token = null;
		try {
			token = twitter.getOAuthAccessToken();
		} catch (TwitterException e) {
			e.printStackTrace();
			ShareSystem.d("exception while getOAuthAccessToken");
		}
		if (token != null) {
			Editor editor = context.getSharedPreferences(KEY, Context.MODE_PRIVATE).edit();
			editor.putString(TOKEN, token.getToken());
			editor.putString(SECRET, token.getTokenSecret());
			return editor.commit();
		}
		return false;
	}

	public static boolean restore(Twitter twitter, Context context) {
		SharedPreferences savedSession = context.getSharedPreferences(KEY, Context.MODE_PRIVATE);
		String token = savedSession.getString(TOKEN, null);
		String secret = savedSession.getString(SECRET, null);
		if (TextUtils.isEmpty(token) || TextUtils.isEmpty(secret)) {
			return false;
		}
		twitter.setOAuthAccessToken(new AccessToken(token, secret));
		return true;
	}

	public static void clear(Context context) {
		Editor editor = context.getSharedPreferences(KEY, Context.MODE_PRIVATE).edit();
		editor.clear();
		editor.commit();
	}

}
