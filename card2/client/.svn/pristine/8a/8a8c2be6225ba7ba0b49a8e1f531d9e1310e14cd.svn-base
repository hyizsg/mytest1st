/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.haypi.gameframework;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.util.Locale;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import proguard.annotation.Keep;
import android.annotation.TargetApi;
import android.app.Activity;
import android.app.Application;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.text.Editable;
import android.text.InputFilter;
import android.text.InputType;
import android.text.TextPaint;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.text.method.PasswordTransformationMethod;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.TextView;

import com.haypi.framework.net.HaypiNetManager;
import com.haypi.framework.net.IHaypiLoginDelegate;
import com.haypi.framework.net.IHaypiNetDelegate;
import com.haypi.framework.net.IHaypiNotificationDelegate;
import com.haypi.framework.util.HaypiLog;
import com.haypi.util.HaypiFont;
import com.haypi.util.HaypiUtil;

public class GameFramework implements IHaypiLoginDelegate, IHaypiNotificationDelegate, IHaypiNetDelegate {
	public static int HCOMMAND_VIEW_MIN = -999;
	public static int HCOMMAND_VIEW_MAX = -100;
	public static int HCOMMAND_SETLOCALE = -1000;
	public static int HCOMMAND_MEMORY = -1001;
	public static int HCOMMAND_RENDER_CONTROL = -1002;
	
	public static final int HORIENTATION_LANDSCAPE = 1;
	public static final int HORIENTATION_PORTRAIT = 2;
	public static final int HORIENTATION_ALL = 3;
	
	//self defined view, such as editbox
	private static final int HVIEWTYPE_EDITBOX = 1;
	private static final int HVIEWTYPE_LABEL = 2;
	private static final int HVIEWTYPE_BUTTON = 3;
	private static final int HVIEWTYPE_IMAGE = 4;
	
	public static final int HCMD_DONE   = -100;
	public static final int HCMD_CREATE	= -101;
	public static final int HCMD_REMOVE	= -102;
	public static final int HCMD_SHOW	= -103;
	public static final int HCMD_HIDE	= -104;
	public static final int HCMD_UPDATE	= -105;
	public static final int HCMD_CHECK	= -106;
	public static final int HVIEWCMD_GETTEXT	= -107;
	public static final int HVIEWCMD_SETTEXT	= -108;

	private static final int HVIEWFEATURE_SINGLINE = (1<<1);
	private static final int HVIEWFEATURE_PASSWORD = (1<<2);
	private static final int HVIEWFEATURE_NUMERIC = (1<<3);
	private static final int HVIEWFEATURE_EMAIL = (1<<4);
	private static final int HVIEWFEATURE_STYPE_BOLD = (1<<5);
	private static final int HVIEWFEATURE_STYPE_ITALIC = (1<<6);
	private static final int HVIEWFEATURE_STYPE_BOLDITALIC = (HVIEWFEATURE_STYPE_BOLD | HVIEWFEATURE_STYPE_ITALIC);
	private static final int HVIEWFEATURE_TYPEFACE_MONO = (1<<7);
	private static final int HVIEWFEATURE_TYPEFACE_SANS = (1<<8);
	private static final int HVIEWFEATURE_TYPEFACE_SERIF = (1<<9);
	private static final int HVIEWFEATURE_TYPEFACE_SANSSERIF = (HVIEWFEATURE_TYPEFACE_SANS | HVIEWFEATURE_TYPEFACE_SERIF);
	private static final int HVIEWFEATURE_NORMAL = (HVIEWFEATURE_SINGLINE | HVIEWFEATURE_TYPEFACE_SERIF);
	
	private static final String HVIEWKEY_ALL = "all";
	private static final String HVIEWKEY_ID = "id";
	private static final String HVIEWKEY_TYPE = "type";
	private static final String HVIEWKEY_VISIBLE = "visible";
	private static final String HVIEWKEY_X = "x";
	private static final String HVIEWKEY_Y = "y";
	private static final String HVIEWKEY_W = "w";
	private static final String HVIEWKEY_H = "h";
	private static final String HVIEWKEY_FEATURE = "feature";
	private static final String HVIEWKEY_TEXT = "text";
	private static final String HVIEWKEY_HINT = "hint";
	private static final String HVIEWKEY_FONTNAME = "fn";
	private static final String HVIEWKEY_FONTSIZE = "fs";
	private static final String HVIEWKEY_FONTCOLOR = "fc";
	private static final String HVIEWKEY_HINTCOLOR = "hc";
	private static final String HVIEWKEY_MAXLEN = "len";
	
	private static int HREFRESH_INTERVAL = 200; //defalut 200 milli seconds
	private boolean mNeedRefesh = false;

	private Activity mMainActivity = null;
	private FrameLayout mMainLayout = null;

	Handler mHandler = new Handler();
	
	Runnable mRunable = new Runnable() {
		@Override
		public void run() {
			// TODO Auto-generated method stub
			mMainLayout.requestLayout();
			if (mNeedRefesh) mHandler.postDelayed(mRunable, HREFRESH_INTERVAL);
		}
	};
	
	public void setMainActivityAndLayout(Activity activity, FrameLayout layout) {
		mMainActivity = activity;
		mMainLayout = layout;
	}
	//self defined view end---
	
	
	private static Application mApp = null;
    private static GameFramework mGameFramework = null;
    private static String packageName;
    private static Resources res;
    private static HaypiNetManager mManager = HaypiNetManager.GetInstance();
    private static Handler handler;
    private NativeCommandListener mNativeCommandListener;
    private static Runnable initializeListener;
	private static Boolean hasSignature;
	
    public static boolean isFakeLogin() {
		return mManager.mIsFake;
	}

    public GameFramework() {
		mGameFramework = this;

        Locale locale = Locale.getDefault();
        String localeCode = (locale.getLanguage() + "_" + locale.getCountry()).toLowerCase(Locale.ENGLISH);
        commandToNative(HCOMMAND_SETLOCALE, localeCode);
    }

	public static void setApplication(Application app) {
		if (mApp == null) {
			handler = new Handler();
			packageName = app.getPackageName();
			res = app.getResources();
			mApp = app;
		}
	}

	public void setNativeCommandListener(NativeCommandListener nativeCommandListener) {
		this.mNativeCommandListener = nativeCommandListener;
	}

	public static void setInitializeListener(Runnable initializeListener) {
		GameFramework.initializeListener = initializeListener;
	}

    static {
         System.loadLibrary("game");
    }
    
    @Keep
    public static void initialize(String gameID, String registerURL, String fakeRegisterURL, String keySocketIP, String keySocketPort, String version, boolean useSocket) {
		HaypiLog.i("java: initialize: " + gameID + ", " + registerURL + ", " + fakeRegisterURL + ", " + keySocketIP + ", " + keySocketPort + ", " + version + ", " + useSocket);
    	mManager.Initialize(GameFramework.mApp, gameID, registerURL, fakeRegisterURL, keySocketIP, keySocketPort, version, mGameFramework, mGameFramework);
    	if (useSocket) {
    		mManager.UseSocketFeature(HaypiNetManager.SOCKET_CRYPT_METHOD_PLAIN, HaypiNetManager.SOCKET_SERVER_TYPE_HAYPISERVER, HaypiNetManager.SOCKET_PROPOCOL_TYPE_TCP);
    	} else {
    		mManager.UseHttpFeature();
    	}
    	mManager.RegisterCommonNotification(mGameFramework);
		
		Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView.queueEvent(new Runnable() {
			@Override
			public void run() {
				registerToNative(mGameFramework, (mManager.mLastUsername != null) && (mManager.mLastUsername.length() > 0), (mManager.mFakeLastUsername != null)  && (mManager.mFakeLastUsername.length() > 0));
			}
		});
		if (initializeListener != null) {
			handler.post(initializeListener);
			initializeListener = null;
		}
    }
    
    @Keep
    public static String CreateJsonWithAction(int action) {
    	JSONObject json =  mManager.CreateJsonWithAction(action);
    	if (json != null) return json.toString();
    	else return null;
    }
    
    @Keep
    public static void closeSocket() {
    	mManager.closeSocket();
    }
    
    @Keep
    public static boolean connectWithSocket() {
    	return mManager.connectWithSocket();
    }
    
    private static long getTotalMemory() {
		long memorySize = 0;
		try {
			FileReader localFileReader = new FileReader("/proc/meminfo");
			BufferedReader loaclBufferedReader = new BufferedReader(localFileReader, 8192);
			String line = loaclBufferedReader.readLine();
			String[] array = line.split("\\s+");
			memorySize = Integer.valueOf(array[1]).intValue() * 1024;
		} catch (IOException e) {
			e.printStackTrace();
		}
		return memorySize;
	}
    
    @Keep
    public static String getSystemInfo() {
    	JSONObject json = new JSONObject();
		try {
			long memory = getTotalMemory() / 1000 / 1000;
			json.put("totalMemory", memory);
			return json.toString();
		} catch (JSONException e) {
			HaypiLog.e(e);
		}
    	return null;
    }
    
    @Keep
    public static String getUserInfo() {
    	JSONObject json = new JSONObject();
		try {
			json.put("username", mManager.GetUsername());
			json.put("deviceid", mManager.GetDeviceID());
			json.put("authkey", mManager.GetAuthKey());
			return json.toString();
		} catch (JSONException e) {
			HaypiLog.e(e);
		}
    	return null;
    }
    
    @Keep
    public static void changeUserInfo(String username, String authkey) {
    	mManager.SetUsername(username);
    	mManager.SetAuthKey(authkey);
    }
    
    @Keep
    public static String getServerList(boolean fake) {
    	return mManager.getServerList(fake);
    }

	@Keep
	public static void register(String inviteCode) {
		register(mManager.mIsFake, -1, inviteCode, -1);
	}

	@Keep
	public static void register(int serverID) {
		register(mManager.mIsFake, serverID, null, -1);
	}

	@Keep
	public static void register(int serverID, String inviteCode) {
		register(mManager.mIsFake, serverID, inviteCode, -1);
	}

	@Keep
	public static void register(int serverID, String inviteCode, int platform) {
		register(mManager.mIsFake, serverID, inviteCode, platform);
	}

	@Keep
	public static void register(boolean isFake, int serverID, String inviteCode, int platform) {
		HaypiLog.d("register(sid=%d,code=%s,platform=%d)", serverID, inviteCode, platform);
		HaypiNetManager.clearRegisterParam();
		HaypiNetManager.mRegisterServerID = serverID;
		HaypiNetManager.mRegisterInviteCode = inviteCode;
		if (platform != -1)
			HaypiNetManager.mPlatformCode = platform;
		if (isFake) {
			mManager.FakeLogin();
		} else {
			mManager.Login();
		}
	}

	@Deprecated
    @Keep
    public static void registerWithInviteCode(String inviteCode) {
    	HaypiLog.d("registerWithInviteCode(%s)", inviteCode);
    	HaypiNetManager.clearRegisterParam();
    	HaypiNetManager.mRegisterInviteCode = inviteCode;
    	if (mManager.mIsFake) {
    		mManager.FakeLogin();
    	} else {
    		mManager.Login();
    	}
    }
    
	@Deprecated
    @Keep
    public static void registerWithServerID(int serverID, int platform) {
    	HaypiLog.d("registerWithServerID(%1$d,%2$d)",serverID,platform);
    	HaypiNetManager.clearRegisterParam();
    	HaypiNetManager.mRegisterServerID = serverID;
    	if (platform != -1) HaypiNetManager.mPlatformCode = platform;
    	if (mManager.mIsFake) {
    		mManager.FakeLogin();
    	} else {
    		mManager.Login();
    	}
    }

	public static int getColor(int id) {
		return res.getColor(id);
	}

	public static int getColorID(String name) {
		return res.getIdentifier(name, "color", packageName);
	}

	public static int getColor(String name) {
		return res.getColor(getColorID(name));
	}

	public static Drawable getDrawable(int id) {
		return res.getDrawable(id);
	}

	public static Drawable getDrawableForDensity(int id, int density) {
		return res.getDrawableForDensity(id, density);
	}

	public static int getDrawableID(String name) {
		return res.getIdentifier(name, "drawable", packageName);
	}

	public static Drawable getDrawable(String name) {
		return res.getDrawable(getDrawableID(name));
	}

	public static Drawable getDrawableForDensity(String name, int density) {
		return res.getDrawableForDensity(getDrawableID(name), density);
	}

	public static String getString(int id) {
		return res.getString(id);
	}

	public static String getString(int id, Object... formatArgs) {
		return res.getString(id, formatArgs);
	}

	public static int getStrID(String name) {
		return res.getIdentifier(name, "string", packageName);
	}

	public static String getString(String name) {
		int id = getStrID(name);
		if (id == 0)
			return "";
		return getString(id);
	}

	public static String getString(String name, Object... formatArgs) {
		int id = getStrID(name);
		if (id == 0)
			return "";
		return getString(id, formatArgs);
	}

	public static int getId(String name) {
		return res.getIdentifier(name, "id", packageName);
	}

	public static int getStyle(String name) {
		return res.getIdentifier(name, "style", packageName);
	}

	public static int getLayout(String name) {
		return res.getIdentifier(name, "layout", packageName);
	}

	public static byte[] loadRes(int id) {
		TypedValue value = new TypedValue();
		res.getValue(id, value, true);
		String path = value.string.toString();
		try {
			return HaypiUtil.readFully(res.getAssets().openNonAssetFd(value.assetCookie, path).createInputStream());
		} catch (Throwable th) {
			return null;
		}
	}

	@TargetApi(Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1)
	public static byte[] loadResForDensity(int id, int density) {
		TypedValue value = new TypedValue();
		res.getValueForDensity(id, density, value, true);
		String path = value.string.toString();
		try {
			return HaypiUtil.readFully(res.getAssets().openNonAssetFd(value.assetCookie, path).createInputStream());
		} catch (Throwable th) {
			return null;
		}
	}

	public static byte[] loadImageData(int id) {
		return loadRes(id);
	}

	public static byte[] loadImageData(String name) {
		return loadRes(getDrawableID(name));
	}

	public static byte[] loadImageDataForDensity(int id, int density) {
		return loadResForDensity(id, density);
	}

	public static byte[] loadImageDataForDensity(String name, int density) {
		return loadResForDensity(getDrawableID(name), density);
	}

	@Keep
    public static void ResetAccount() {
    	mManager.ResetAccount();
    }
    
	@Keep
    public static void Login() {
    	mManager.Login();
	}
	
	@Keep
	public static void FakeLogin() {
		mManager.FakeLogin();
	}
	
	@Keep
	public static void LoginWithAccount(String username, String password) {
		mManager.LoginWithAccount(username, password);
	}
	
	@Keep
	public static void FakeLoginWithAccount(String username, String password) {
		mManager.FakeLoginWithAccount(username, password);
	}
	
	private static SNSLogin snsLogin;

	public static void setSNSLogin(SNSLogin snsLogin) {
		GameFramework.snsLogin = snsLogin;
	}

	@Keep
	public static boolean isSNSLogin() {
		return HaypiNetManager.getGCType() != HaypiNetManager.GC_TYPE_NULL;
	}

	@Keep
	public static void SNSInit() {
		handler.post(new Runnable() {
			@Override
			public void run() {
				if (snsLogin != null) {
					snsLogin.init();
				}
			}
		});
	}

	@Keep
	public static void SNSLogin(final boolean isFake) {
		mManager.mIsFake = isFake;
		handler.post(new Runnable() {
			@Override
			public void run() {
				if (snsLogin != null) {
					snsLogin.invokeLogin(isFake);
				} else {
					String lastUsername = isFake ? mManager.mFakeLastUsername : mManager.mLastUsername;
					boolean registered = !TextUtils.isEmpty(lastUsername);
					SNSLogin.LoginResult result = registered ? SNSLogin.LoginResult.Registered : SNSLogin.LoginResult.Unregistered;
					onSNSLogin(result, "GC_TYPE_NULL");
				}
			}
		});
	}

	@Keep
	public static void SNSLogout() {
		handler.post(new Runnable() {
			@Override
			public void run() {
				if (snsLogin != null) {
					snsLogin.logout();
				}
			}
		});
	}

	@Keep
	public static boolean SNSShowLogin(final boolean isFake) {
		HaypiNetManager.GetInstance().mIsFake = isFake;
		if (snsLogin != null) {
			handler.post(new Runnable() {
				@Override
				public void run() {
					snsLogin.showLogin(isFake);
				}
			});
			return true;
		}
		return false;
	}

	@Keep
	public static void SNSShowMain() {
		handler.post(new Runnable() {
			@Override
			public void run() {
				if (snsLogin != null) {
					snsLogin.showMain();
				}
			}
		});
	}

	@Keep
	public static void SNSShowToolBar(final boolean show) {
		handler.post(new Runnable() {
			@Override
			public void run() {
				if (snsLogin != null) {
					snsLogin.showToolBar(show);
				}
			}
		});
	}

	public static void SNSOnActivityCreate() {
		if (snsLogin != null) {
			snsLogin.onActivityCreate();
		}
	}

	public static void SNSOnActivityStart() {
		if (snsLogin != null) {
			snsLogin.onActivityStart();
		}
	}
	
	public static void SNSOnActivityResume() {
		if (snsLogin != null) {
			snsLogin.invokeOnActivityResume();
		}
	}

	public static void SNSOnActivityPause() {
		if (snsLogin != null) {
			snsLogin.onActivityPause();
		}
	}
	
	public static void SNSOnActivityStop() {
		if (snsLogin != null) {
			snsLogin.invokeOnActivityStop();
		}
	}
	
	public static void SNSOnActivityDestroy() {
		if (snsLogin != null) {
			snsLogin.onActivityDestroy();
		}
	}

	@Keep
	public static void SNSOnExit() {
		handler.post(new Runnable() {
			@Override
			public void run() {
				if (snsLogin != null) {
					snsLogin.onExit();
				}
			}
		});
	}

	public static void SNSSetInGame(final boolean inGame) {
		handler.post(new Runnable() {
			@Override
			public void run() {
				if (snsLogin != null) {
					snsLogin.setInGame(inGame);
				}
			}
		});
	}

	static void onSNSLogin(SNSLogin.LoginResult result, String message) {
		JSONObject json = new JSONObject();
		try {
			json.put("STATE", result.code);
			json.put("MESSAGE", message);
		} catch (JSONException e) {
		}
		mGameFramework.OnNotifyForLogin(HaypiNetManager.SNS_LOGIN_RESULT, json.toString());
	}

	static void onSNSLogout() {
		mGameFramework.OnNotifyForLogin(HaypiNetManager.NEED_RELOGIN, null);
	}

	private void SNSOnLoginToPassport() {
		handler.post(new Runnable() {
			@Override
			public void run() {
				if (snsLogin != null) {
					snsLogin.invokeLoginToPassport();
				}
			}
		});
	}

	@Keep
	public static void VisitWeb(String webSite) {
		Intent intent = new Intent();
		intent.setAction("android.intent.action.VIEW");
		Uri content_url = Uri.parse(webSite);
		intent.setData(content_url);
		intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		try {
			GameFramework.mApp.startActivity(intent);
		} catch (ActivityNotFoundException e) {
			HaypiLog.e(e);
		}
	}
	
	@Keep
	public static void ReceiveMessage(final int cmd, final String param) {
		handler.post(new Runnable() {
			@Override
			public void run() {
				try {
					if ((cmd >= HCOMMAND_VIEW_MIN) && (cmd <= HCOMMAND_VIEW_MAX)) {
						mGameFramework.onGameView(cmd, param);
					} else {
						if (mGameFramework.mNativeCommandListener == null) {
							throw new RuntimeException("mNativeCommandListener == null");
						}
						mGameFramework.mNativeCommandListener.onNativeCommandReceived(cmd, param);
					}
				} catch (Exception e) {
					HaypiLog.e(e);
				}
			}
		});
	}
    
	@Keep
    public static int NewActionKey() {
    	return HaypiNetManager.NewActionKey();
    }
    
    @Keep
	public static int PostRequest(int command, String param, long delegate, boolean ignoreDuplication, int commandLevel, int netMode, int validActionKey) {
    	if(HaypiNetManager.mLogEnable) HaypiLog.i("postRequest:cmd("+command+"), param("+param+"), delegate("+delegate+"), level("+commandLevel+"), net mode("+netMode+"), actionKey("+validActionKey+")...");
		try {
			JSONObject dict = ((param != null) && (param.length() > 0)) ? new JSONObject(param) : new JSONObject();
//	    	++mTimestamp;
//	    	dict.put("TIMESTAMP", mTimestamp);
    		dict.put("delegate", delegate);
			mManager.PostRequest(command, dict, mGameFramework, ignoreDuplication, commandLevel, true, netMode, validActionKey);
		} catch (JSONException e) {
			HaypiLog.e(e);
		}
		return 0;
	}
	
	@Keep
	public static void ClearAll() {
		mManager.ClearAll();
	}
	
    public void OnNotifyForLogin(final int msg, final Object param) {
		if (msg == HaypiNetManager.LOGIN_TO_PASSPORT_SUCCESS) {
			SNSOnLoginToPassport();
		}
    	Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView.queueEvent(new Runnable() {
			@Override
			public void run() {
		    	switch (msg) {
		    	case HaypiNetManager.LOGIN_WITH_NEW_ACCOUNT:
		    		HaypiLog.i("login with new account");
		    		notifyForLoginToNative(msg, (String)param);
		    		break;
		    	case HaypiNetManager.LOGIN_NEED_ACCOUNT:
		    		HaypiLog.i("need account");
		    		notifyForLoginToNative(msg, (String)param);
		    		break;
		    	case HaypiNetManager.LOGIN_SHOW_PROGRESS:
		    		HaypiLog.i("show progress");
		    		notifyForLoginToNative(msg, (String)param);
		    		break;
		    	case HaypiNetManager.LOGIN_FAILED:
		    		HaypiLog.i("login failed");
		    		notifyForLoginToNative(msg, (String)param);
		    		break;
		    	case HaypiNetManager.LOGIN_TO_SOCKET: {
		    		HaypiLog.i("login to socket");
		    		notifyForLoginToNative(msg, (String)param);
		    	}
		    		break;
		    	case HaypiNetManager.LOGIN_TO_SOCKET_FAILED: {
		    		HaypiLog.i("login to socket failed");
		    		notifyForLoginToNative(msg, (String)param);
		    	}
		    		break;
		    	case HaypiNetManager.LOGIN_TO_GAMECENTER_FAILED: {
		    		HaypiLog.i("login to gamecenter failed");
		    		notifyForLoginToNative(msg, (String)param);
		    	}
		    		break;
		    	case HaypiNetManager.LOGIN_TO_SOCKET_NEED_RELOGIN: {
		    		HaypiLog.i("login to socket: need relogin.");
		    		notifyForLoginToNative(msg, (String)param);
		    	}
		    		break;
		    	case HaypiNetManager.LOGIN_TO_GAMECENTER_NEED_RELOGIN: {
		    		HaypiLog.i("login to gamecenter: need relogin.");
		    		notifyForLoginToNative(msg, (String)param);
		    	}
		    		break;
		    	case HaypiNetManager.LOGIN_SUCCESS:
		    		HaypiLog.i("login success");
		    		notifyForLoginToNative(msg, (String)param);
		    		break;    	
		    	case HaypiNetManager.SNS_LOGIN_RESULT:
		    		HaypiLog.i("sns login complete: " + param.toString());
		    		notifyForLoginToNative(msg, (String)param);
		    		break;    
		    	case HaypiNetManager.NEED_RELOGIN:
		    		HaypiLog.i("need relogin");
		    		notifyForLoginToNative(msg, null);
		    		break;
		    	}
			}
		});
    	
//    	notifyForLoginToNative(msg, (String)param);
    }
    
    public void StartGame() {
		HaypiLog.i("-------------- Start Game --------------");

    	Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView.queueEvent(new Runnable() {
			@Override
			public void run() {
		    	startGameToNative();
			}
		});

//		Toast.makeText(this, "login success", Toast.LENGTH_SHORT).show();
		
		//store test
//		sendDataWithHttp(6505, null);
//		sendDataWithHttp(4005, null);
//		
//		mTimer.Run();
		
		//monst test

	}
    
    public void OnCommonNotification(final int id, final JSONObject result) {
    	Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView.queueEvent(new Runnable() {
			@Override
			public void run() {
		    	notificationToNative(id, (result != null) ? result.toString() : null);
			}
		});
	}
	
	public void OnDataReceived(final int command, final JSONObject result, final JSONObject param) {
//		HaypiLog.i("OnDataReceived:("+((result == null) ? "" : result.toString())+"), param(" +((param == null) ? "" : param.toString())+ ")");
		Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView.queueEvent(new Runnable() {
			@Override
			public void run() {
				dataReceivedToNative(command, (result == null) ? null : result.toString(), (param == null) ? 0 : param.optLong("delegate"));
			}
		});
	}

	public int onCommand(int command) {
		return onCommand(command, "");
	}

	public int onCommand(int command, JSONObject json) {
		return onCommand(command, json == null ? "" : json.toString());
	}

	public int onCommand(final int command, final String data) {
		Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView.queueEvent(new Runnable() {
			@Override
			public void run() {
				commandToNative(command, data == null ? "" : data);
			}
		});
		return 0;
	}

	public static byte[] loadResource(String path) {
		if (TextUtils.isEmpty(path))
			return null;
		return GetFileData(path);
	}

	public static native int requestScreenOrientation();
	
    private static native void registerToNative(Object netManager, boolean isRegistered, boolean isFakeRegistered);
    private static native void commandToNative(int command, String data);
    private static native void notifyForLoginToNative(int notify, String data);
    private static native void startGameToNative();
    private static native void notificationToNative(int identifier, String result);
    private static native void dataReceivedToNative(int command, String result, long delegate);
    private static native byte[] GetFileData(String filename); 
    
    //self defined view
    private void onGameView(int command, String param) {
    	try {
    		HaypiLog.i("game view: "+command + ", "+param);
    		JSONObject dict = new JSONObject(param);
			JSONArray array = dict.getJSONArray(HVIEWKEY_ALL);
			int count = array.length();
			
    		switch (command) {
    		case HCMD_CREATE: {
    			mNeedRefesh = true;
    			GameFramework.HREFRESH_INTERVAL = dict.optInt("fresh", 100);//default 200 milli seconds
//    			EditText lastEdit = null;
    			for (int i = 0; i < count; ++i) {
    				JSONObject item = array.getJSONObject(i);
    				String tag = item.getString(HVIEWKEY_ID);
    				int type = item.getInt(HVIEWKEY_TYPE);
//    				boolean visible = item.getBoolean(HVIEWKEY_VISIBLE);
    				int x = item.getInt(HVIEWKEY_X);
    				int y = item.getInt(HVIEWKEY_Y);
    				int w = item.getInt(HVIEWKEY_W);
    				int h = item.getInt(HVIEWKEY_H);
    				HaypiLog.i("create, type:"+type+",x:"+x+",y:"+y+",w:"+w+",h:"+h);
    				switch (type) {
    				case HVIEWTYPE_EDITBOX: //edit box
    					HaypiLog.i("edit box");
    					final EditText edit = new EditText(mMainActivity);
//    					lastEdit = edit;
    					edit.setTag(tag);
    					
    					int feature = item.optInt(HVIEWKEY_FEATURE, 0);
    					if (0 != (feature & HVIEWFEATURE_SINGLINE)) {
    						HaypiLog.i("single line");
    						edit.setSingleLine();
    						float fontSize = h * 3 / 4;
        					edit.setTextSize(TypedValue.COMPLEX_UNIT_PX, fontSize);
        					
        					int inputType = InputType.TYPE_CLASS_TEXT;
        					if (0 != (feature & HVIEWFEATURE_EMAIL)) {
        						inputType |= InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS;
        					}
        					if (0 != (feature & HVIEWFEATURE_NUMERIC)) {
        						inputType = InputType.TYPE_CLASS_NUMBER;
        					}
        					if (0 != (feature & HVIEWFEATURE_PASSWORD)) {
        						edit.setTransformationMethod(PasswordTransformationMethod.getInstance());
        					}
    						edit.setInputType(inputType);
    					} else {
    						HaypiLog.i("multi line");
    						edit.setGravity(Gravity.TOP);
    						float fontSize = (float)item.optDouble(HVIEWKEY_FONTSIZE, 20);
    						if ((fontSize < 5) || (fontSize > 60)) fontSize = 20;
    						edit.setTextSize(TypedValue.COMPLEX_UNIT_PX, fontSize);
    					}
						
						edit.setText(item.optString(HVIEWKEY_TEXT, ""));
						edit.setSelection(edit.length());
						edit.setHint(item.optString(HVIEWKEY_HINT, ""));
    					
//    					edit.setTypeface(Typeface.SANS_SERIF);
    					
    					edit.setTextColor(item.optInt(HVIEWKEY_FONTCOLOR, 0xFFFFFFFF));
    					edit.setHintTextColor(item.optInt(HVIEWKEY_HINTCOLOR, 0xFF7F7F7F));
    					int maxLength = item.optInt(HVIEWKEY_MAXLEN, 0);
    					if (maxLength > 0) {
    						edit.setFilters(new InputFilter[]{new InputFilter.LengthFilter(maxLength)});
    					}
    					if (HaypiLog.mLevel > HaypiLog.LOG_LEVEL.NONE) edit.setBackgroundColor(0x7F000000);
    					else edit.setBackgroundColor(0x00000000);

    					FrameLayout.LayoutParams lp = new FrameLayout.LayoutParams(w, h);
						lp.gravity = Gravity.TOP | Gravity.LEFT;
    					lp.leftMargin = x;
    					lp.topMargin = y;
    					edit.setLayoutParams(lp);
    					
    					edit.setPadding(0, 0, 0, 0);
    					
    					mMainLayout.addView(edit);
    					edit.setVisibility(View.INVISIBLE);
    					
//    					edit.setOnFocusChangeListener(new View.OnFocusChangeListener() {
//							@Override
//							public void onFocusChange(View v, boolean hasFocus) {
//								// TODO Auto-generated method stub
//								if (!hasFocus) {
//									Log.i(LOGTAG, "lost focus");
//									try {
//										JSONObject ret = new JSONObject();
//										JSONArray content = new JSONArray();
//										ret.put(HVIEWKEY_ALL, content);
//										JSONObject value = new JSONObject();
//										content.put(value);
//										value.put(HVIEWKEY_ID, ((EditText)v).getTag());
//										value.put(HVIEWKEY_TYPE, HVIEWTYPE_EDITBOX);
//										value.put(HVIEWKEY_TEXT, ((EditText)v).getText().toString());
//						    			mGameFramework.onCommand(HCMD_CHECK, ret);
//									} catch (JSONException e) {
//										e.printStackTrace();
//									}
//								} else {
//									mFocusEditText = (EditText)v;
////									InputMethodManager m = (InputMethodManager)v.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
////		    						m.hideSoftInputFromWindow(v.getWindowToken(), 0);
//								}
//							}
//						});
//    					lastEdit.setImeActionLabel("login", 0);
    					edit.setOnEditorActionListener(new EditText.OnEditorActionListener() {
							@Override
							public boolean onEditorAction(TextView v,
									int actionId, KeyEvent event) {
								// TODO Auto-generated method stub
								HaypiLog.i("edit text:"+v.getTag().toString()+", actionId:"+actionId);
								try {
									JSONObject ret = new JSONObject();
									JSONArray content = new JSONArray();
									ret.put(HVIEWKEY_ALL, content);
									JSONObject value = new JSONObject();
									content.put(value);
									value.put(HVIEWKEY_ID, ((EditText)v).getTag());
									value.put(HVIEWKEY_TYPE, HVIEWTYPE_EDITBOX);
									value.put(HVIEWKEY_TEXT, ((EditText)v).getText().toString());
					    			mGameFramework.onCommand(HCMD_CHECK, ret);
								} catch (JSONException e) {
									e.printStackTrace();
								}
								return false;
							}
    						
    					});
    					edit.addTextChangedListener(new TextWatcher() {
							@Override
							public void afterTextChanged(Editable s) {
								// TODO Auto-generated method stub
								HaypiLog.i("edit text:"+s.toString());
								try {
									JSONObject ret = new JSONObject();
									JSONArray content = new JSONArray();
									ret.put(HVIEWKEY_ALL, content);
									JSONObject value = new JSONObject();
									content.put(value);
									value.put(HVIEWKEY_ID, ((EditText)edit).getTag());
									value.put(HVIEWKEY_TYPE, HVIEWTYPE_EDITBOX);
									value.put(HVIEWKEY_TEXT, s.toString());
					    			mGameFramework.onCommand(HVIEWCMD_SETTEXT, ret);
								} catch (JSONException e) {
									e.printStackTrace();
								}
							}

							@Override
							public void beforeTextChanged(CharSequence s,
									int start, int count, int after) {
								// TODO Auto-generated method stub
							}

							@Override
							public void onTextChanged(CharSequence s,
									int start, int before, int count) {
								// TODO Auto-generated method stub
							}
    						
    					});
    					edit.setOnKeyListener(new View.OnKeyListener() {
							@Override
							public boolean onKey(View v, int keyCode, KeyEvent event) {
								// TODO Auto-generated method stub
								switch (keyCode) {
								case KeyEvent.KEYCODE_BACK:
								case KeyEvent.KEYCODE_MENU: 
									switch (event.getAction()) {
									case KeyEvent.ACTION_UP:
										Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView.onKeyUp(keyCode, event);
										break;
									case KeyEvent.ACTION_DOWN:
										Cocos2dxGLSurfaceView.mCocos2dxGLSurfaceView.onKeyDown(keyCode, event);
										break;
									} 
									return true;
								}
								return false;
							}
						});
    					break;
    				}
    			}
    		}
    	    	break;
    		case HCMD_REMOVE: {
    			for (int i = 0; i < count; ++i) {
    				JSONObject item = array.getJSONObject(i);
    				String tag = item.getString(HVIEWKEY_ID);
//    				int type = item.getInt(HVIEWKEY_TYPE);
    				View view = mMainLayout.findViewWithTag(tag);
    				if (view != null) mMainLayout.removeView(view);
    			}

    			mNeedRefesh = false;
    			hideSoftInput();
    		}
    	    	break;
    	    case HCMD_SHOW: {
    			mNeedRefesh = true;
    			for (int i = 0; i < count; ++i) {
    				JSONObject item = array.getJSONObject(i);
    				String tag = item.getString(HVIEWKEY_ID);
    				boolean visible = item.getBoolean(HVIEWKEY_VISIBLE);
    				View view = mMainLayout.findViewWithTag(tag);
    				if (view != null) {
    					view.setVisibility(visible ? View.VISIBLE : View.INVISIBLE);
    				}
    			}
    		}
    	    	break;
    	    case HCMD_HIDE: {
    			for (int i = 0; i < count; ++i) {
    				JSONObject item = array.getJSONObject(i);
    				String tag = item.getString(HVIEWKEY_ID);
    				boolean visible = item.getBoolean(HVIEWKEY_VISIBLE);
    				View view = mMainLayout.findViewWithTag(tag);
    				if (view != null) {
    					view.setVisibility(visible ? View.VISIBLE : View.INVISIBLE);
    				}
    			}
    			mNeedRefesh = false;
    			hideSoftInput();
    		}
    	    	break;
    	    case HCMD_UPDATE: {
    			for (int i = 0; i < count; ++i) {
    				JSONObject item = array.getJSONObject(i);
    				String tag = item.getString(HVIEWKEY_ID);
    				int type = item.getInt(HVIEWKEY_TYPE);
    				boolean visible = item.getBoolean(HVIEWKEY_VISIBLE);
    				int x = item.getInt(HVIEWKEY_X);
    				int y = item.getInt(HVIEWKEY_Y);
    				int w = item.getInt(HVIEWKEY_W);
    				int h = item.getInt(HVIEWKEY_H);
    				HaypiLog.i("update, type:"+type+",x:"+x+",y:"+y+",w:"+w+",h:"+h);
    				switch (type) {
    				case HVIEWTYPE_EDITBOX: //edit box
    					HaypiLog.i("edit box");
    					final EditText edit = (EditText)mMainLayout.findViewWithTag(tag);
    					if (edit == null) break;
    					
    					int feature = item.optInt(HVIEWKEY_FEATURE, 0);
    					if (0 != (feature & HVIEWFEATURE_SINGLINE)) {
    						HaypiLog.i("single line");
    						edit.setSingleLine();
    						float fontSize = h * 3 / 4;
        					edit.setTextSize(TypedValue.COMPLEX_UNIT_PX, fontSize);
        					
        					int inputType = InputType.TYPE_CLASS_TEXT;
        					if (0 != (feature & HVIEWFEATURE_EMAIL)) {
        						inputType |= InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS;
        					}
        					if (0 != (feature & HVIEWFEATURE_NUMERIC)) {
        						inputType = InputType.TYPE_CLASS_NUMBER;
        					}
        					if (0 != (feature & HVIEWFEATURE_PASSWORD)) {
        						edit.setTransformationMethod(PasswordTransformationMethod.getInstance());
        					}
    						edit.setInputType(inputType);
    					} else {
    						HaypiLog.i("multi line");
    						edit.setGravity(Gravity.TOP);
    						float fontSize = (float)item.optDouble(HVIEWKEY_FONTSIZE, 20);
    						if ((fontSize < 5) || (fontSize > 60)) fontSize = 20;
    						edit.setTextSize(TypedValue.COMPLEX_UNIT_PX, fontSize);
    					}
						
						edit.setText(item.optString(HVIEWKEY_TEXT, ""));
						edit.setSelection(edit.length());
						edit.setHint(item.optString(HVIEWKEY_HINT, ""));
    					
    					edit.setTextColor(item.optInt(HVIEWKEY_FONTCOLOR, 0xFFFFFFFF));
    					edit.setHintTextColor(item.optInt(HVIEWKEY_HINTCOLOR, 0xFF7F7F7F));
    					int maxLength = item.optInt(HVIEWKEY_MAXLEN, 0);
    					if (maxLength > 0) {
    						edit.setFilters(new InputFilter[]{new InputFilter.LengthFilter(maxLength)});
    					}
    					if (HaypiLog.mLevel > HaypiLog.LOG_LEVEL.NONE) edit.setBackgroundColor(0x7F000000);
    					else edit.setBackgroundColor(0x00000000);

    					FrameLayout.LayoutParams lp = new FrameLayout.LayoutParams(w, h);
    					lp.gravity = Gravity.TOP | Gravity.LEFT;
    					lp.leftMargin = x;
    					lp.topMargin = y;
    					edit.setLayoutParams(lp);
    					
    					edit.setPadding(0, 0, 0, 0);

    					edit.setVisibility(visible ? View.VISIBLE : View.INVISIBLE);
    				}
    			}
    	    }
    	    	break;
    	    case HCMD_CHECK:
    	    	break;
    	    case HVIEWCMD_GETTEXT: {
    			for (int i = 0; i < count; ++i) {
    				JSONObject item = array.getJSONObject(i);
    				int type = item.getInt(HVIEWKEY_TYPE);
    				String tag = item.getString(HVIEWKEY_ID);
    				View view = mMainLayout.findViewWithTag(tag);
    				if (view != null) {
    					if (type == HVIEWTYPE_EDITBOX) {
    						String text = ((EditText)view).getText().toString();
    						item.put(HVIEWKEY_TEXT, text);
    					}
    				}
    			}
    			mGameFramework.onCommand(HVIEWCMD_SETTEXT, dict);
    	    }
    	    	break;
    	    case HVIEWCMD_SETTEXT: {
    			for (int i = 0; i < count; ++i) {
    				JSONObject item = array.getJSONObject(i);
    				int type = item.getInt(HVIEWKEY_TYPE);
    				String tag = item.getString(HVIEWKEY_ID);
    				View view = mMainLayout.findViewWithTag(tag);
    				if (view != null) {
    					if (type == HVIEWTYPE_EDITBOX) {
    						((EditText)view).setText(item.optString(HVIEWKEY_TEXT, ""));
    					}
    				}
    			}
    		}
    	    	break;
    		}

    		HaypiLog.i("view count: " + mMainLayout.getChildCount());
    		
//    		mNeedRefesh = dict.optBoolean("refresh", true);
    		if (mNeedRefesh) mHandler.postDelayed(mRunable, HREFRESH_INTERVAL);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}

	public static boolean hasSignature(Context ctx) {
		if (hasSignature == null) {
			PackageManager pm = ctx.getPackageManager();
			try {
				PackageInfo pi = pm.getPackageInfo(ctx.getPackageName(), 0);
				hasSignature = (pi.applicationInfo.flags & ApplicationInfo.FLAG_DEBUGGABLE) == 0;
			} catch (NameNotFoundException nnfe) {
				nnfe.printStackTrace();
				hasSignature = false;
			}
		}
		return hasSignature;
	}

	@Keep
	public static String formatDate(int format, int secondsFrom1970) {
		long date = secondsFrom1970 * 1000L;
		String pattern = null;
		switch (format) {
		default:
			pattern = "yyyy-MM-dd hh:mm:ss";
			break;
		}
		return new SimpleDateFormat(pattern, Locale.getDefault()).format(date);
	}

	@Keep
	public static String adjustText(String content, String font, int fontSize, int width, int minTextLength) {
		content = getFirstLine(content);
		if (TextUtils.isEmpty(content))
			return content;
		int len = content.length();
		if (minTextLength < 1)
			minTextLength = 1;
		if (len <= minTextLength)
			return content;
		TextPaint paint = new TextPaint();
		paint.setTextSize(fontSize);
		if (!TextUtils.isEmpty(font)) {
			paint.setTypeface(HaypiFont.get(GameFramework.mApp, font));
		}
		float fWidth = paint.measureText(content);
		if (fWidth <= width) {
			return content;
		}
		final String tail = "...";
		int start = minTextLength;
		int end = len;
		int index;
		for (;;) {
			index = (start + end) / 2;
			if (index == start) {
				break;
			}
			fWidth = paint.measureText(content.subSequence(0, index) + tail);
			if (fWidth <= width) {
				start = index;
			} else {
				end = index;
			}
		}
		return content.substring(0, start) + tail;
	}

	private static String getFirstLine(String content) {
		if (TextUtils.isEmpty(content))
			return content;
		int len = content.length();
		int index1 = content.indexOf("\r\n");
		int index2 = content.indexOf('\n');
		if (index1 < 0)
			index1 = len;
		if (index2 < 0)
			index2 = len;
		return content.substring(0, Math.min(index1, index2));
	}

	@Keep
	public static byte[] loadFileFromAssets(String path) {
		AssetManager assets = GameFramework.mApp.getAssets();
		byte[] data = null;
		InputStream is = null;
		try {
			is = assets.open(path);
			data = HaypiUtil.readFully(is);
		} catch (Exception e) {
			HaypiUtil.close(is);
		}
		return data;
	}

	public static String[] getStringArray(int id) {
		return res.getStringArray(id);
	}

	public static String[] getStringArray(String name) {
		return getStringArray(getArray(name));
	}

	public static int getArray(String name) {
		return res.getIdentifier(name, "array", packageName);
	}

	public static boolean checkBadWords(String nickName) {
		if (TextUtils.isEmpty(nickName))
			return true;
		for (String s : getStringArray("bad_words_array")) {
			if (nickName.contains(s))
				return false;
		}
		return true;
	}

	//@formatter:off
	private static String[] bad_words_replacement = {
		"*",
		"**",
		"***",
		"****",
		"*****",
		"******",
		"*******",
		"********",
		"*********",
		"**********",
	};
	//@formatter:on

	public static String replaceBadWords(String message) {
		if (TextUtils.isEmpty(message))
			return message;
		for (String s : getStringArray("bad_words_array")) {
			message = message.replace(s, bad_words_replacement[Math.min(s.length() - 1, 9)]);
		}
		return message;
	}

	@Keep
	public static void hideSoftInput() {
		HaypiUtil.hideSoftInput((Activity) Cocos2dxActivity.getContext());
	}

	public static void pauseGLRender() {
		mGameFramework.onCommand(HCOMMAND_RENDER_CONTROL, "0");
	}

	public static void resumeGLRender() {
		mGameFramework.onCommand(HCOMMAND_RENDER_CONTROL, "1");
	}
}
