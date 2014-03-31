package com.haypi.util;

import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.Closeable;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Set;

import org.json.JSONArray;
import org.json.JSONObject;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.Dialog;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ColorMatrixColorFilter;
import android.os.Environment;
import android.os.Looper;
import android.text.TextUtils;
import android.util.SparseArray;
import android.view.View;
import android.view.ViewTreeObserver;
import android.view.Window;
import android.view.inputmethod.InputMethodManager;

import com.haypi.framework.util.HaypiLog;

public class HaypiUtil {
	private static int screenWidth, screenHeight;

	public static void setScreenSize(Activity activity) {
		if (screenWidth > 0 && screenHeight > 0) {
			return;
		}
		View v = activity.getWindow().getDecorView();
		screenWidth = v.getWidth();
		screenHeight = v.getHeight();
	}

	public static int getScreenWidth() {
		return screenWidth;
	}

	public static int getScreenHeight() {
		return screenHeight;
	}

	public static String[] split(String str, String sep) {
		int sepLen = sep.length();
		ArrayList<String> list = new ArrayList<String>();
		while (str.length() > 0) {
			int index = str.indexOf(sep);
			if (index < 0)
				break;
			list.add(str.substring(0, index));
			str = str.substring(index + sepLen);
		}
		list.add(str);
		return list.toArray(new String[list.size()]);
	}

	public static void close(Closeable closeable) {
		try {
			closeable.close();
		} catch (Exception e) {
		}
	}

	public static void checkUIThread() {
		if (Looper.myLooper() != Looper.getMainLooper()) {
			throw new IllegalThreadStateException();
		}
	}

	public static boolean isInUIThread() {
		return Looper.myLooper() == Looper.getMainLooper();
	}

	public static String formatTime2HHMMSS(long second) {
		if (second < 0)
			second = 0;
		long time = second;
		StringBuilder sb = new StringBuilder(10);
		sb.append(time % 10);
		time /= 10;
		sb.append(time % 6);
		time /= 6;
		sb.append(':');
		sb.append(time % 10);
		time /= 10;
		sb.append(time % 6);
		time /= 6;
		sb.append(':');
		sb.append(time % 10);
		time /= 10;
		sb.append(time % 10);
		time /= 10;
		while (time > 0) {
			sb.append(time % 10);
			time /= 10;
		}
		return sb.reverse().toString();
	}

	public static void asynConnect(final String url) {
		new Thread() {
			public void run() {
				try {
					new URL(url).openStream().close();
				} catch (Exception e) {
				}
			}
		}.start();
	}

	public static int mid(int v, int min, int max) {
		if (min > max) {
			int temp = min;
			min = max;
			max = temp;
		}
		return Math.max(min, Math.min(v, max));
	}

	public static boolean isSDCardMounted() {
		return Environment.MEDIA_MOUNTED.equals(Environment.getExternalStorageState());
	}

	public static boolean isCN() {
		return Locale.CHINA.equals(Locale.getDefault());
	}

	public static void addOneFrameOnPreDrawListener(final View v, final ViewTreeObserver.OnPreDrawListener listener) {
		v.getViewTreeObserver().addOnPreDrawListener(new ViewTreeObserver.OnPreDrawListener() {
			@Override
			public boolean onPreDraw() {
				v.getViewTreeObserver().removeOnPreDrawListener(this);
				return listener.onPreDraw();
			}
		});
	}

	//@formatter:off
	public static final ColorMatrixColorFilter greyColorFilter = new ColorMatrixColorFilter(new float[]{
		0.299f,0.587f,0.114f,0,0,
		0.299f,0.587f,0.114f,0,0,
		0.299f,0.587f,0.114f,0,0,
		0,0,0,1,0
	});
	public static final ColorMatrixColorFilter blackColorFilter = new ColorMatrixColorFilter(new float[]{
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,1,0
	});
	//@formatter:on

	public static Bitmap decodeScaleBitmap(final int w, final int h, final byte[] data) {
		int len = data.length;
		BitmapFactory.Options opts = new BitmapFactory.Options();

		opts.inJustDecodeBounds = true;
		BitmapFactory.decodeByteArray(data, 0, len, opts);

		opts.inJustDecodeBounds = false;
		opts.inSampleSize = Math.min(opts.outWidth / w, opts.outHeight / h);
		return BitmapFactory.decodeByteArray(data, 0, len, opts);
	}

	public static Map<String, Object> toMap(JSONObject json) {
		Map<String, Object> map = new HashMap<String, Object>();
		@SuppressWarnings("unchecked")
		Iterator<String> it = (Iterator<String>) json.keys();
		String key;
		Object value;
		while (it.hasNext()) {
			key = it.next();
			value = json.opt(key);
			map.put(key, value);
		}
		return map;
	}

	public static Map<Integer, Object> toMap(JSONArray jsonArray) {
		Map<Integer, Object> map = new LinkedHashMap<Integer, Object>();
		int size = jsonArray.length();
		for (int i = 0; i < size; i++) {
			map.put(i, jsonArray.opt(i));
		}
		return map;
	}

	public static <T> Map<Integer, T> toMap(SparseArray<T> sparseArray) {
		Map<Integer, T> map = new LinkedHashMap<Integer, T>();
		int size = sparseArray.size();
		for (int i = 0; i < size; i++)
			map.put(sparseArray.keyAt(i), sparseArray.valueAt(i));
		return map;
	}

	public static Set<Map.Entry<String, Object>> entrySet(JSONObject json) {
		return toMap(json).entrySet();
	}

	public static Set<Map.Entry<Integer, Object>> entrySet(JSONArray jsonArray) {
		return toMap(jsonArray).entrySet();
	}

	public static <T> Set<Map.Entry<Integer, T>> entrySet(SparseArray<T> sparseArray) {
		return toMap(sparseArray).entrySet();
	}

	public static Collection<Object> values(JSONObject json) {
		return toMap(json).values();
	}

	public static Collection<Object> values(JSONArray jsonArray) {
		return toMap(jsonArray).values();
	}

	public static <T> Collection<T> values(SparseArray<T> sparseArray) {
		return toMap(sparseArray).values();
	}

	public static boolean equals(Object o1, Object o2) {
		return o1 == o2 || o1 != null && o1.equals(o2);
	}

	public static int indexOf(Object obj, Object[] array) {
		int len = array.length;
		for (int i = 0; i < len; i++)
			if (equals(obj, array[i]))
				return i;
		return -1;
	}

	public static DataInputStream getMarkDataInputStream(InputStream is) {
		if (is == null)
			return null;
		if (is.markSupported()) {
			if (is instanceof DataInputStream) {
				return (DataInputStream) is;
			}
		} else {
			is = new BufferedInputStream(is);
		}
		return new DataInputStream(is);
	}

	public static byte[] readFully(InputStream is) throws IOException {
		ByteArrayOutputStream baos = new ByteArrayOutputStream(4096);
		byte[] buf = new byte[4096];
		int len;
		while ((len = is.read(buf)) > -1) {
			baos.write(buf, 0, len);
		}
		is.close();
		return baos.toByteArray();
	}

	public static void setLocale(Context ctx, String single_locale) {
		if (TextUtils.isEmpty(single_locale))
			return;
		Locale locale = null;
		String[] ss = single_locale.split("-r");
		if (ss.length == 2) {
			locale = new Locale(ss[0], ss[1]);
		} else {
			locale = new Locale(ss[0]);
		}
		Locale.setDefault(locale);

		Resources res = ctx.getResources();
		Configuration config = res.getConfiguration();
		config.locale = locale;
		res.updateConfiguration(config, null);
	}

	public static void hideSoftInput(View view) {
		if (view != null) {
			InputMethodManager im = (InputMethodManager) view.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
			im.hideSoftInputFromWindow(view.getWindowToken(), 0);
		}
	}

	public static void hideSoftInput(Window window) {
		if (window != null) {
			hideSoftInput(window.getDecorView());
		}
	}

	public static void hideSoftInput(Activity activity) {
		hideSoftInput(activity.getWindow());
	}

	public static void hideSoftInput(Dialog dialog) {
		hideSoftInput(dialog.getWindow());
	}

	private static final char[] lowerChars = "0123456789abcdef".toCharArray();

	public static String toHex(byte[] b) {
		int len = b.length;
		StringBuilder sb = new StringBuilder(len * 2);
		for (int ch : b) {
			ch &= 0xFF;
			sb.append(lowerChars[ch >> 4]);
			sb.append(lowerChars[ch & 0xF]);
		}
		return sb.toString();
	}

	public static byte[] getApkSignature(Context ctx) {
		try {
			return ctx.getPackageManager().getPackageInfo(ctx.getPackageName(), PackageManager.GET_SIGNATURES).signatures[0].toByteArray();
		} catch (NameNotFoundException e) {
			HaypiLog.e(e);
			return null;
		}
	}

	public static String getApkSignatureWithMD5(Context ctx) {
		byte[] signature = getApkSignature(ctx);
		if (signature == null) {
			return null;
		}
		try {
			return toHex(MessageDigest.getInstance("MD5").digest(signature));
		} catch (NoSuchAlgorithmException e) {
			HaypiLog.e(e);
			return null;
		}
	}

	public static boolean isAppOnForeground(Context ctx) {
		ActivityManager activityManager = (ActivityManager) ctx.getSystemService(Context.ACTIVITY_SERVICE);
		String packageName = ctx.getPackageName();
		List<RunningAppProcessInfo> appProcesses = activityManager.getRunningAppProcesses();
		if (appProcesses == null)
			return false;
		for (RunningAppProcessInfo appProcess : appProcesses) {
			if (appProcess.processName.equals(packageName) && appProcess.importance == RunningAppProcessInfo.IMPORTANCE_FOREGROUND) {
				return true;
			}
		}
		return false;
	}
}
