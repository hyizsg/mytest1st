package com.haypi.util;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.util.HashMap;

import android.content.Context;
import android.graphics.Typeface;
import android.util.Log;

public class HaypiFont {
	private static HashMap<String, Typeface> cache = new HashMap<String, Typeface>();
	private static final String SystemFont = "SystemFont";
	private static final String SystemBoldFont = "SystemBoldFont";

	public static Typeface get(Context ctx, String fontName) {
		Typeface typeFace = cache.get(fontName);
		if (typeFace != null)
			return typeFace;
		if (fontName.toLowerCase().endsWith(".ttf")) {
			try {
				typeFace = Typeface.createFromAsset(ctx.getAssets(), fontName);
				cache.put(fontName, typeFace);
				return typeFace;
			} catch (Exception e) {
				e("loadFromAsset:%s", fontName);
				e.printStackTrace();
			}
		} else if (fontName.equalsIgnoreCase(SystemFont)) {
			return Typeface.DEFAULT;
		} else if (fontName.equalsIgnoreCase(SystemBoldFont)) {
			return Typeface.DEFAULT_BOLD;
		}
		return Typeface.create(fontName, Typeface.NORMAL);
	}

	private static void set(Typeface typeFace, String... fontNames) {
		for (String fontName : fontNames) {
			cache.put(fontName, typeFace);
		}
	}

	public static void load(Context ctx, byte[] data, String... fontNames) {
		File temp = new File(ctx.getCacheDir(), "temp.ttf");
		temp.getParentFile().mkdirs();
		OutputStream os = null;
		try {
			os = new FileOutputStream(temp);
			os.write(data);
			os.flush();
			os.close();
		} catch (Exception e) {
			return;
		}
		Typeface typeFace = Typeface.createFromFile(temp);
		temp.delete();
		set(typeFace, fontNames);
	}

	public static void loadFromFile(File file, String... fontNames) {
		try {
			Typeface typeFace = Typeface.createFromFile(file);
			set(typeFace, fontNames);
		} catch (Exception e) {
			e("loadFromFile:%s", file.getPath());
			e.printStackTrace();
		}
	}

	public static void loadFromAsset(Context ctx, String path, String... fontNames) {
		try {
			Typeface typeFace = Typeface.createFromAsset(ctx.getAssets(), path);
			set(typeFace, fontNames);
		} catch (Exception e) {
			e("loadFromAsset:%s", path);
			e.printStackTrace();
		}
	}

	private static void e(String format, Object... args) {
		Log.e("HaypiFont", String.format(format, args));
	}

	public static void replaceWithSystemFont(boolean bold, String... fontNames) {
		set(bold ? Typeface.DEFAULT_BOLD : Typeface.DEFAULT, fontNames);
	}
}