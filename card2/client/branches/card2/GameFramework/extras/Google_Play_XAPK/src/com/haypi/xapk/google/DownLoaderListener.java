package com.haypi.xapk.google;

import com.google.android.vending.expansion.downloader.DownloadProgressInfo;

public interface DownLoaderListener {
	void onDownloadStateChanged(int state);
	void onDownloadProgress(DownloadProgressInfo progress);
}