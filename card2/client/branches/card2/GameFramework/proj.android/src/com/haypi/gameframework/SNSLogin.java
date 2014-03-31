package com.haypi.gameframework;

import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.LinkedHashMap;
import java.util.Map;

import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Process;

import com.haypi.framework.net.HaypiNetManager;
import com.haypi.framework.net.IHaypiNetDelegate;
import com.haypi.framework.util.HaypiLog;
import com.haypi.util.HaypiUtil;

/**
 * 第三方登录接口
 * @author Mao Yudong
 */
public abstract class SNSLogin {
	private static final String tag = "SNSLogin";
	/**
	 * 第三方登录结果枚举
	 */
	public static enum LoginResult {
		//@formatter:off
		Error(0),
		Unregistered(1),
		Registered(2),
		Banned(3),
		Canceled(100);
		//@formatter:on

		public final int code;

		private LoginResult(int code) {
			this.code = code;
		}

		static LoginResult valueOf(int code) {
			for (LoginResult v : values()) {
				if (v.code == code)
					return v;
			}
			return Error;
		}
	}

	/*
	 * 创建此SNSLogin实例的Activity
	 */
	protected final Activity activity;
	private boolean isBusy4Login;
	private boolean resumeFromBackground;
	private boolean inGame = true;

	/**
	 * 构造方法，指定当前的GCType,会设置到HaypiNetManager里去
	 * @param gcType
	 * @param activity 创建此SNSLogin实例的Activity
	 */
	protected SNSLogin(int gcType, Activity activity) {
		HaypiNetManager.setGCType(gcType);
		this.activity = activity;
	}

	/**
	 * 第三方登录结束时应当调用的方法
	 * @param result 登录结果,登录成功时为null.此时会去判定是否注册过
	 * @param message
	 */
	protected final void onLogin(LoginResult result, String message) {
		if (result != null) {
			isBusy4Login = false;
			HaypiLog.i(tag, "onLogin:%s", result.toString());
			GameFramework.onSNSLogin(result, message);
		} else {
			checkRegistered();
		}
	}

	/**
	 * 检查此第三方账号是否有注册过游戏
	 */
	private void checkRegistered() {
		HaypiLog.i(tag, "checkRegistered");
		if (SNSLoginResultCache.isRegistered(activity)) {
			HaypiLog.i(tag, "check registered from cache");
			onLogin(LoginResult.Registered, "");
			return;
		}
		HaypiLog.i(tag, "check from server");
		HaypiNetManager.GetInstance().checkRegisterState(new IHaypiNetDelegate() {
			@Override
			public void OnDataReceived(int command, JSONObject result, JSONObject param) {
				LoginResult loginResult = LoginResult.Error;
				if (result != null) {
					loginResult = LoginResult.valueOf(result.optInt("State"));
					if (loginResult == LoginResult.Registered) {
						SNSLoginResultCache.setRegistered(activity);
					}
				}
				onLogin(loginResult, "");
			}
		});
	}

	/**
	 * 初始化接口，有些第三方登录需要进行初始化
	 */
	protected void init() {
	}

	/**
	 * 调用第三方登录窗口
	 * @param isFake 是否为内网登录
	 */
	protected abstract void showLogin(boolean isFake);

	final void invokeLogin(boolean isFake) {
		if (isBusy4Login)
			return;
		isBusy4Login = true;
		login(isFake);
	}

	/**
	 * 调用第三饭登录
	 * @param isFake 是否为内网登录
	 */
	protected abstract void login(boolean isFake);

	/**
	 * 调用第三方注销
	 */
	protected abstract void logout();

	/**
	 * 调用显示第三方主界面
	 */
	protected void showMain() {
	}

	/**
	 * 调用显示/隐藏第三方工具条/悬浮框
	 * @param show 是否显示
	 */
	protected void showToolBar(boolean show) {
	}

	/**
	 * 第三方需要在Activity.onCreate时执行的代码放这里
	 */
	protected void onActivityCreate() {
	}

	/**
	 * 第三方需要在Activity.onStart时执行的代码放这里
	 */
	protected void onActivityStart() {
	}

	void invokeOnActivityResume() {
		onActivityResume();
		resumeFromBackground = false;
	}

	/**
	 * 第三方需要在Activity.onResume时执行的代码放这里
	 */
	protected void onActivityResume() {
	}

	/**
	 * 第三方需要在Activity.onPause时执行的代码放这里
	 */
	protected void onActivityPause() {
	}

	void invokeOnActivityStop() {
		resumeFromBackground = !HaypiUtil.isAppOnForeground(activity);
		onActivityStop();
	}

	/**
	 * 第三方需要在Activity.onStop时执行的代码放这里
	 */
	protected void onActivityStop() {
	}

	/**
	 * 第三方需要在Activity.onDestroy时执行的代码放这里
	 */
	protected void onActivityDestroy() {
	}

	/**
	 * 第三方需要在按返回键退出app时执行的代码放这里 比如：有的第三方需要显示退出确认，显示其它游戏的入口或广告等
	 * 默认是调用 exitGame 方法退出游戏
	 */
	protected void onExit() {
		exitGame();
	}

	/**
	 * 退出游戏,在onExit方法中根据需要调用
	 */
	protected final void exitGame(){
		activity.finish();
		Process.killProcess(Process.myPid());
	}

	void invokeLoginToPassport() {
		SNSLoginResultCache.setRegistered(activity);
		onLoginToPassport();
	}

	/**
	 * 第三方需要在登录到passport后需要执行的代码放这里 比如：昆仑需要在进入游戏时调用他们的选服函数
	 */
	protected void onLoginToPassport() {
	}

	/**
	 * 第三方在监听到用户注销或切换时，调用此方法，以通知我们的游戏切回到登录页面
	 */
	protected void onLogout() {
		GameFramework.onSNSLogout();
	}

	protected final boolean isInGame() {
		return inGame;
	}

	void setInGame(boolean inGame) {
		this.inGame = inGame;
	}

	protected final boolean isResumeFromBackground() {
		return resumeFromBackground;
	}

	abstract class GCTask extends AsyncTask<Void, Void, JSONObject> {
		private static final String tag = "GCTask";
		private final String url;
		private final int action;
		private boolean debug;
		private Map<String, Object> params = new LinkedHashMap<String, Object>();

		GCTask(int action, String url) {
			this.action = action;
			this.url = url;
		}

		protected final void setDebug(boolean debug) {
			this.debug = debug;
		}

		protected final void d(String message) {
			HaypiLog.d(tag, message);
		}

		protected final void d(String message, Object... args) {
			HaypiLog.d(tag, message, args);
		}

		/**
		 * 添加参数
		 * @param key 参数名
		 * @param value 参数值
		 */
		protected final void setParam(String key, Object value) {
			params.put(key, value);
		}

		@Override
		protected final JSONObject doInBackground(Void... params) {
			int retryTime = 3;
			JSONObject json = new JSONObject();
			try {
				json.put("ACTION", action);
				json.put("GCType", HaypiNetManager.getGCType());
				json.put("Debug", debug ? 1 : 0);
				for (Map.Entry<String, Object> e : this.params.entrySet()) {
					json.put(e.getKey(), e.getValue());
				}
			} catch (JSONException e) {
			}
			d("url: %s",url);
			d("param: %s", json.toString());
			HttpURLConnection con = null;
			for (; retryTime > 0; retryTime--) {
				try {
					con = (HttpURLConnection) new URL(url).openConnection();
					con.setUseCaches(false);
					con.setConnectTimeout(300000);
					con.setRequestMethod("POST");
					OutputStream out = con.getOutputStream();
					out.write(json.toString().getBytes("UTF-8"));
					out.close();
					int respCode = con.getResponseCode();
					d("respCode : %d", respCode);
					if (respCode == HttpURLConnection.HTTP_OK) {
						String response = new String(HaypiUtil.readFully(con.getInputStream()));
						d("response : %s", response);
						JSONObject result = new JSONObject(response);
						return result;
					}
				} catch (Exception e) {
					HaypiLog.e(e);
				}
			}
			return null;
		}

		@Override
		protected final void onPostExecute(JSONObject result) {
			super.onPostExecute(result);
			d("finish, result=%s", String.valueOf(result));
			boolean success = result != null && result.optInt("ACTION_COM", -1) == 0;
			if (success) {
				onSuccess(result);
			} else {
				onFailed(result);
			}
		}

		/**
		 * 获取第三方用户成功
		 * @param result
		 */
		protected abstract void onSuccess(JSONObject result);

		/**
		 * 获取第三方用户信息失败
		 * @param result
		 */
		abstract protected void onFailed(JSONObject result);
	}

	/**
	 * 有些第三方登录后不直接诶返回GCName时，执行此Task与我们的服务器通讯以获取GCName等用户信息,比如360，UC等
	 * @author Mao Yudong
	 */
	abstract protected class GetGCInfoTask extends GCTask {
		public GetGCInfoTask(String url, String authCode) {
			super(151, url);
			setParam("AuthCode", authCode);
		}

		/**
		 * 获取第三方用户成功
		 */
		@Override
		protected void onSuccess(JSONObject result) {
			HaypiNetManager.setGCName(result.optString("GCName"));
		}
	}

	/**
	 * 有些第三方登录后需要定时刷新Token,执行此Task与我们的服务器通许以获取刷新后的内容
	 * @author Mao Yudong
	 */
	abstract protected class RefreshTokenTask extends GCTask {
		protected RefreshTokenTask(String url) {
			super(152, url);
			setParam("GCName", HaypiNetManager.getGCName());
		}
	}
}