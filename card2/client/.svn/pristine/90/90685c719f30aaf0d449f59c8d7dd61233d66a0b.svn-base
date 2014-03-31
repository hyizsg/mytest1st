package com.haypi.gameframework;

import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;

import com.haypi.framework.util.HaypiLog;

public class SimpleNotification {
	public static final String ACTION = "com.haypi.gameframework.SimpleNotification-";
	private int id;
	private int icon;
	private String title;
	private String message;
	private long when = System.currentTimeMillis();
	private long delay;
	private Intent intent;
	private int alarmId;

	public void setId(int id) {
		this.id = id;
	}

	public void setIcon(int icon) {
		this.icon = icon;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public void setMessage(String message) {
		this.message = message;
	}

	public void setWhen(long when) {
		this.when = when;
		this.delay = when - System.currentTimeMillis();
	}

	public void setDelay(long delay) {
		this.when = delay + System.currentTimeMillis();
		this.delay = delay;
	}

	public void setIntent(Intent intent) {
		this.intent = intent;
	}

	public void setAlarmId(int alarmId) {
		this.alarmId = alarmId;
	}

	@SuppressWarnings("deprecation")
	public void Notify(Context ctx) {
		if (delay <= 0) {
			NotificationManager notificationManager = (NotificationManager) ctx.getSystemService(Context.NOTIFICATION_SERVICE);
			Notification notification = new Notification(icon, message, when);

			PendingIntent pendingIntent = PendingIntent.getActivity(ctx, 0, intent, 0);
			notification.setLatestEventInfo(ctx, title, message, pendingIntent);
			notification.flags |= Notification.FLAG_AUTO_CANCEL;

			notificationManager.notify(id, notification);
			HaypiLog.d("notify", "%1$d:%2$s", id, message);
		} else {
			Intent i = new Intent(ctx.getApplicationContext(), NotificationReceiver.class);
			i.setAction(ACTION);
			i.setData(Uri.parse("AlarmId=" + alarmId));
			i.putExtra("Id", id);
			i.putExtra("Icon", icon);
			i.putExtra("Title", title);
			i.putExtra("Message", message);
			i.putExtra("Intent", intent);
			PendingIntent pendingIntent = PendingIntent.getBroadcast(ctx, 0, i, PendingIntent.FLAG_UPDATE_CURRENT);
			AlarmManager alarmManager = (AlarmManager) ctx.getSystemService(Context.ALARM_SERVICE);
			alarmManager.set(AlarmManager.RTC, when, pendingIntent);
		}
	}

	public static void cancelAll(Context ctx) {
		NotificationManager notificationManager = (NotificationManager) ctx.getSystemService(Context.NOTIFICATION_SERVICE);
		notificationManager.cancelAll();
	}

	public static void cancel(Context ctx, int id) {
		NotificationManager notificationManager = (NotificationManager) ctx.getSystemService(Context.NOTIFICATION_SERVICE);
		notificationManager.cancel(id);
	}

	public static void cancel(Context ctx, String tag, int id) {
		NotificationManager notificationManager = (NotificationManager) ctx.getSystemService(Context.NOTIFICATION_SERVICE);
		notificationManager.cancel(tag, id);
	}
}