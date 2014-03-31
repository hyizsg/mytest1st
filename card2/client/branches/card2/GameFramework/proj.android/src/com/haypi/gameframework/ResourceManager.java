package com.haypi.gameframework;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Locale;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Environment;
import android.os.Handler;

import com.haypi.framework.util.HaypiLog;
import com.haypi.util.HaypiUtil;

public class ResourceManager {
	public static interface ResourceListener {
		void onResourceStateUpdate(STATE state, String info);
	}

	private static ArrayList<ResourceListener> resourceListeners = new ArrayList<ResourceListener>();

	public static void addResourceListener(ResourceListener listener) {
		resourceListeners.add(listener);
	}

	public static void removeResourceListener(ResourceListener listener) {
		resourceListeners.remove(listener);
	}

	private static void fireResourceListeners(final STATE state, final String info) {
		handler.post(new Runnable() {
			@Override
			public void run() {
				ResourceListener[] listeners = resourceListeners.toArray(new ResourceListener[resourceListeners.size()]);
				for (ResourceListener listener : listeners) {
					listener.onResourceStateUpdate(state, info);
				}
			}
		});
	}

	private static final String tag = "ResourceManager";
	private static boolean unzipInJava = false;
	private static Handler handler;

	//@formatter:off
	public enum MODE {
		ASSETS,
		XAPK;
	}

	public enum STATE {
		SDCARD_CHECK,
		SDCARD_UNMOUNTED,
		VERSION_CHECK,
		UNZIPING,
		UNZIP_ERROR,
		READY,
		DOWNLOAD_FAILED,
		REQUEST_DOWNLOAD;
	}
	//@formatter:on

	private static final String DIR_UNZIP = "resource";
	private static final String DIR_XAPK = "Android/obb";

	private static Context ctx;
	private static String packageName;
	private static int version;
	private static int size;
	private static File dir_unzip;
	private static MODE mode;
	private static volatile STATE state = null;

	public static void init(Context ctx, MODE mode, int version, int size) {
		if (ResourceManager.ctx != null) {
			setState(state);
			return;
		}
		handler = new Handler();
		HaypiLog.d(tag, "sdcard " + Environment.getExternalStorageDirectory().getPath());
		ResourceManager.ctx = ctx.getApplicationContext();
		packageName = ctx.getPackageName();
		ResourceManager.version = version;
		ResourceManager.size = size;
		dir_unzip = new File(ctx.getFilesDir(), DIR_UNZIP);
		ResourceManager.mode = mode;
		checkState();
	}

	public static void reCheck() {
		if (mode != MODE.XAPK)
			return;
		if (state != STATE.REQUEST_DOWNLOAD)
			return;
		boolean ignoreObbFileSize = isIgnoreObbFileSize(ctx);
		File obbFile = getObbFile(version);
		if (!obbFile.exists() || obbFile.length() != size && !ignoreObbFileSize) {
			return;
		}
		if (!unzipInJava) {
			setState(STATE.READY);
			return;
		}
		unzip();
	}

	private static void checkState() {
		if (mode == MODE.XAPK) {
			setState(STATE.SDCARD_CHECK);
			if (HaypiUtil.isSDCardMounted() == false) {
				setState(STATE.SDCARD_UNMOUNTED);
				return;
			}
			setState(STATE.VERSION_CHECK);
			int lastVersion = getVersion();
			int lastSize = getSize();
			boolean ignoreObbFileSize = isIgnoreObbFileSize(ctx);
			if (version != lastVersion || size != lastSize && !ignoreObbFileSize) {
				getObbFile(lastVersion).delete();
				cleanUnzipDir();
			}
			setVersion(version);
			setSize(size);
			File obbFile = getObbFile(version);
			HaypiLog.d(tag, "file  " + obbFile.getPath());
			HaypiLog.d(tag, "exists: " + obbFile.exists());
			if (obbFile.exists()) {
				HaypiLog.d(tag, "size: " + obbFile.length());
			}
			if (!obbFile.exists() || obbFile.length() != size && !ignoreObbFileSize) {
				setState(STATE.REQUEST_DOWNLOAD);
				return;
			}
		}
		if (!unzipInJava) {
			setState(STATE.READY);
			return;
		}
		unzip();
	}

	private static void checkInited() {
		if (ctx == null)
			throw new IllegalStateException("call check(Context,mode,version,size) first");
	}

	public static File getFile(String path) {
		checkInited();
		return new File(dir_unzip, path);
	}

	public static InputStream openFileInput(String path) throws FileNotFoundException {
		return new BufferedInputStream(new FileInputStream(getFile(path)));
	}

	private static OutputStream openFileOutput(String path) throws FileNotFoundException {
		File file = getFile(path);
		file.getParentFile().mkdirs();
		return new BufferedOutputStream(new FileOutputStream(file));
	}

	public static File getObbFile() {
		return getObbFile(getVersion());
	}

	private static File getObbFile(final int version) {
		if (HaypiUtil.isSDCardMounted() == false)
			return null;
		File SDCard = Environment.getExternalStorageDirectory();
		String filename = String.format(Locale.ENGLISH, "main.%1$d.%2$s.obb", version, packageName);
		File obbFile = new File(SDCard, DIR_XAPK + "/" + packageName + "/" + filename);
		if (!obbFile.exists()) {
			// just for test
			obbFile = new File(SDCard, filename);
		}
		return obbFile;
	}

	private static void unzip() {
		new Thread() {
			public void run() {
				try {
					switch (mode) {
					case ASSETS:
						unzip(new File(ctx.getPackageCodePath()));
						break;
					case XAPK:
						unzip(getObbFile(getVersion()));
						break;
					}
					setState(STATE.READY);
				} catch (Exception e) {
					HaypiLog.e(e);
					setState(STATE.UNZIP_ERROR);
				}
			}
		}.start();
	}

	private static void unzip(File file) throws Exception {
		HaypiLog.d(tag, "unzip from " + file.getAbsolutePath());
		ZipFile zip = new ZipFile(file);
		int ver = readVersionFromUnzip();
		boolean isAPK = file.getName().toLowerCase().endsWith(".apk") || zip.getEntry("assets") != null;
		int VER = readVersionFromZip(zip, isAPK);
		HaypiLog.d(tag, "check version %1$d -> %2$d", ver, VER);
		if (VER > 0 && VER == ver) {
			zip.close();
			HaypiLog.d(tag, "skip unzip");
			return;
		}
		cleanUnzipDir();
		long start = getTime();
		final long period = 50L;
		long nextUpdateTime = 0;
		int total = getUnzipCount(zip, isAPK) + 1;
		float unzipped = 0;
		Enumeration<? extends ZipEntry> entries = zip.entries();
		ZipEntry ze;
		InputStream is;
		OutputStream os;
		byte[] buf = new byte[50 * 1024];
		int count;
		String name;
		while (entries.hasMoreElements()) {
			ze = entries.nextElement();
			if (ze.isDirectory())
				continue;
			name = ze.getName();
			if (isAPK) {
				if (!name.startsWith("assets/")) {
					continue;
				}
				name = name.substring(7);
			}
			os = openFileOutput(name);
			HaypiLog.d(tag, "unzip %s", name);
			is = new BufferedInputStream(zip.getInputStream(ze));
			while ((count = is.read(buf)) > -1) {
				os.write(buf, 0, count);
			}
			is.close();
			os.flush();
			os.close();
			unzipped++;
			long now = getTime();
			if (now > nextUpdateTime) {
				setState(STATE.UNZIPING, String.valueOf(unzipped / total));
				nextUpdateTime = now + period;
			}
		}
		os = openFileOutput("config/ver");
		os.write((VER + "\n" + VER + "\n").getBytes());
		os.flush();
		os.close();
		zip.close();
		HaypiLog.d(tag, "total %d ms", getTime() - start);
	}

	private static int getUnzipCount(ZipFile zip, boolean isAPK) {
		int total = 0;
		Enumeration<? extends ZipEntry> entries = zip.entries();
		ZipEntry ze;
		while (entries.hasMoreElements()) {
			ze = entries.nextElement();
			if (ze.isDirectory())
				continue;
			if (isAPK && !ze.getName().startsWith("assets/"))
				continue;
			total++;
		}
		return total;
	}

	private static void clean(File file) {
		if (file.isDirectory()) {
			File[] subFiles = file.listFiles();
			if (subFiles != null) {
				for (File subFile : subFiles) {
					clean(subFile);
				}
			}
		}
		file.delete();
	}

	private static void cleanUnzipDir() {
		clean(dir_unzip);
	}

	private static int readVersionFromZip(ZipFile zip, boolean isAPK) throws IOException {
		int VER = 0;
		ZipEntry ze;
		if (isAPK) {
			ze = zip.getEntry("assets/config/ver");
		} else {
			ze = zip.getEntry("config/ver");
		}
		if (ze != null) {
			InputStream is = zip.getInputStream(ze);
			VER = Integer.parseInt(new BufferedReader(new InputStreamReader(is)).readLine());
			is.close();
		}
		return VER;
	}

	private static int readVersionFromUnzip() throws IOException {
		int ver = 0;
		File f = getFile("config/ver");
		if (f.exists()) {
			BufferedReader br = new BufferedReader(new FileReader(f));
			String line1 = br.readLine();
			String line2 = br.readLine();
			br.close();
			if (line1 != null && line1.equals(line2)) {
				ver = Integer.parseInt(line1);
			}
		}
		return ver;
	}

	private static void setVersion(int version) {
		Editor e = getSharedPreferences().edit();
		e.putInt("version", version);
		e.commit();
	}

	private static int getVersion() {
		return getSharedPreferences().getInt("version", -1);
	}

	private static void setSize(int size) {
		Editor e = getSharedPreferences().edit();
		e.putInt("size", size);
		e.commit();
	}

	private static int getSize() {
		return getSharedPreferences().getInt("size", -1);
	}

	private static void setState(STATE state) {
		setState(state, null);
	}

	private static void setState(STATE state, String info) {
		ResourceManager.state = state;
		fireResourceListeners(state, info);
	}

	private static SharedPreferences getSharedPreferences() {
		return ctx.getSharedPreferences("ResourceManager", Context.MODE_PRIVATE);
	}

	private static boolean isIgnoreObbFileSize(Context ctx) {
		return !GameFramework.hasSignature(ctx);
	}

	public static void setUnzipInJava() {
		ResourceManager.unzipInJava = true;
	}

	private static long getTime() {
		return System.currentTimeMillis();
	}
}
