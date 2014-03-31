package com.haypi.xapk.google;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Messenger;

import com.android.vending.expansion.downloader.R;
import com.google.android.vending.expansion.downloader.DownloadProgressInfo;
import com.google.android.vending.expansion.downloader.DownloaderClientMarshaller;
import com.google.android.vending.expansion.downloader.DownloaderServiceMarshaller;
import com.google.android.vending.expansion.downloader.Helpers;
import com.google.android.vending.expansion.downloader.IDownloaderClient;
import com.google.android.vending.expansion.downloader.IDownloaderService;
import com.google.android.vending.expansion.downloader.IStub;
import com.google.android.vending.expansion.downloader.impl.DownloaderService;
import com.google.android.vending.expansion.downloader.impl.DownloadsDB;
import com.haypi.framework.util.HaypiLog;

public class XAPK implements IDownloaderClient {
	public static final String tag = "XAPK";

	private static Context ctx;

	private static int mainVersion, patchVersion;
	private static long mainSize, patchSize;

	private static XAPK instance;

	private int state = -1;
	private DownLoaderListener listener;
	private IDownloaderService mRemoteService;
	private IStub mDownloaderClientStub;
	private PendingIntent pendingIntent;

	private XAPK(DownLoaderListener listener) {
		this.listener = listener;
	}

	@Override
	public void onServiceConnected(Messenger m) {
		HaypiLog.d(tag, "onServiceConnected");
		mRemoteService = DownloaderServiceMarshaller.CreateProxy(m);
		mRemoteService.onClientUpdated(mDownloaderClientStub.getMessenger());
	}

	@Override
	public void onDownloadStateChanged(int newState) {
		if (this.state == newState)
			return;
		this.state = newState;
		HaypiLog.d(tag, "onDownloadStateChanged: %d", newState);
		listener.onDownloadStateChanged(newState);
	}

	@Override
	public void onDownloadProgress(DownloadProgressInfo progress) {
		HaypiLog.d(tag, "download: " + progress.mOverallProgress + " bytes");
		if (XAPK.ctx != null) {
			listener.onDownloadProgress(progress);
		}
	}

	private void resume(boolean download_over_cellular) {
		if (download_over_cellular) {
			mRemoteService.setDownloadFlags(DownloaderService.FLAGS_DOWNLOAD_OVER_CELLULAR);
		}
		mRemoteService.requestContinueDownload();
	}

	public static void init(int mainVersion, long mainSize, int patchVersion, long patchSize) {
		HaypiLog.d(tag, "init(%1$d,%2$d,%3$d,%4$d)", mainVersion, mainSize, patchVersion, patchSize);
		XAPK.mainVersion = mainVersion;
		XAPK.mainSize = mainSize;
		XAPK.patchVersion = patchVersion;
		XAPK.patchSize = patchSize;
	}

	public static void init(int mainVersion, long mainSize) {
		init(mainVersion, mainSize, 0, 0);
	}

	public static boolean needDownload(Context ctx, boolean deleteFileOnMismatch) {
		boolean needDownload = false;
		if (mainVersion > 0 && mainSize > 0) {
			needDownload |= !Helpers.doesFileExist(ctx, Helpers.getExpansionAPKFileName(ctx, true, mainVersion), mainSize, deleteFileOnMismatch);
		}
		if (patchVersion > 0 && patchSize > 0) {
			needDownload |= !Helpers.doesFileExist(ctx, Helpers.getExpansionAPKFileName(ctx, true, patchVersion), patchSize, deleteFileOnMismatch);
		}
		HaypiLog.d(tag, "needDownload ? " + needDownload);
		return needDownload;
	}

	public static void startDownload(Activity activity, DownLoaderListener listener, Class<? extends DownloaderService> service) {
		if (instance != null)
			return;
		HaypiLog.d(tag, "startDownload");
		if (needDownload(activity, false) == false) {
			listener.onDownloadStateChanged(STATE_COMPLETED);
			return;
		}
		instance = new XAPK(listener);
		try {
			Intent launchIntent = activity.getIntent();
			Intent intentToLaunchThisActivityFromNotification = new Intent(activity, activity.getClass());
			intentToLaunchThisActivityFromNotification.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TOP);
			intentToLaunchThisActivityFromNotification.setAction(launchIntent.getAction());

			if (launchIntent.getCategories() != null) {
				for (String category : launchIntent.getCategories()) {
					intentToLaunchThisActivityFromNotification.addCategory(category);
				}
			}

			// Build PendingIntent used to open this activity from
			// Notification
			instance.pendingIntent = PendingIntent.getActivity(activity, 0, intentToLaunchThisActivityFromNotification, PendingIntent.FLAG_UPDATE_CURRENT);
			listener.onDownloadStateChanged(0);
			// Request to start the download
			int startResult = DownloaderClientMarshaller.startDownloadServiceIfRequired(activity, instance.pendingIntent, service);
			if (startResult == DownloaderClientMarshaller.NO_DOWNLOAD_REQUIRED) {
				DownloadsDB.getDB(activity).updateMetadata(0, 0);
				startResult = DownloaderClientMarshaller.startDownloadServiceIfRequired(activity, instance.pendingIntent, service);
			}
			instance.mDownloaderClientStub = DownloaderClientMarshaller.CreateStub(instance, service);
			instance.mDownloaderClientStub.connect(activity);
		} catch (NameNotFoundException e) {
			HaypiLog.e(tag, "Cannot find own package!", e);
		}
	}

	public static void continueDownloadOverCellular() {
		if (instance != null) {
			HaypiLog.d(tag, "continue download over cellular");
			instance.resume(true);
		}
	}

	public static void stopDownload(Activity ctx) {
		if (instance != null) {
			HaypiLog.d(tag, "stopDownload");
			instance.mDownloaderClientStub.disconnect(ctx);
			instance.pendingIntent.cancel();
			instance = null;
		}
	}

	public static void connect(Activity ctx) {
		XAPK.ctx = ctx;
		if (instance != null) {
			HaypiLog.d(tag, "connect");
		}
	}

	public static void disconnect(Activity ctx) {
		XAPK.ctx = null;
		if (instance != null) {
			HaypiLog.d(tag, "disconnect");
			instance.state = -1;
		}
	}

	public static String getStatusText(Context ctx, int state) {
		return ctx.getString(Helpers.getDownloaderStringResourceIDFromState(state));
	}

	public static String getStatusText(Context ctx, DownloadProgressInfo progress) {
		return Helpers.getDownloadProgressString(progress.mOverallProgress, progress.mOverallTotal);
	}

	public static String getTimeRemaining(Context ctx, DownloadProgressInfo progress) {
		return ctx.getString(R.string.time_remaining_notification, Helpers.getTimeRemaining(progress.mTimeRemaining));
	}
}