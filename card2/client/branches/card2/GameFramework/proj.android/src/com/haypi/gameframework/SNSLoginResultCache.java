package com.haypi.gameframework;

import android.content.Context;
import android.content.SharedPreferences;

import com.haypi.framework.net.HaypiNetManager;
import com.haypi.gameframework.SNSLogin.LoginResult;

class SNSLoginResultCache {
	private static final String name = "sns.login.state";
	static final int NOT_EXISTS = -1;

	private static SharedPreferences getData(Context ctx) {
		return ctx.getSharedPreferences(name, Context.MODE_PRIVATE);
	}

	private static String getKey() {
		return HaypiNetManager.getGCType() + "@" + HaypiNetManager.getGCName();
	}

	static boolean isRegistered(Context ctx) {
		return getData(ctx).getInt(getKey(), NOT_EXISTS) == LoginResult.Registered.code;
	}

	static void setRegistered(Context ctx) {
		getData(ctx).edit().putInt(getKey(), LoginResult.Registered.code).commit();
	}
}
