package com.haypi.gameframework;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class NotificationReceiver extends BroadcastReceiver {
	@Override
	public void onReceive(Context ctx, Intent intent) {
		if (intent.getAction().equals(SimpleNotification.ACTION)) {
			int id = intent.getIntExtra("Id", 0);
			int icon = intent.getIntExtra("Icon", 0);
			String title = intent.getStringExtra("Title");
			String message = intent.getStringExtra("Message");
			SimpleNotification notify = new SimpleNotification();
			notify.setId(id);
			notify.setIcon(icon);
			notify.setTitle(title);
			notify.setMessage(message);
			notify.setIntent((Intent) intent.getParcelableExtra("Intent"));
			notify.Notify(ctx);
		}
	}
}
