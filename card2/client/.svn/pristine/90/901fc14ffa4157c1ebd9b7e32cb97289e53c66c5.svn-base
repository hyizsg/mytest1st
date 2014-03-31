package com.haypi.util;

import android.text.TextUtils;

public class HaypiResourceHelper {
	private static String zipFilePath;

	public static void setZipFilePath(String zipFilePath) {
		HaypiResourceHelper.zipFilePath = zipFilePath;
	}

	public static String getZipFilePath(String apk) {
		return TextUtils.isEmpty(zipFilePath) ? apk : zipFilePath;
	}
}