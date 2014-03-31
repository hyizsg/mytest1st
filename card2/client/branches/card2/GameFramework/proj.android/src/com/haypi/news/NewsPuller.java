package com.haypi.news;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;

import com.haypi.framework.net.HaypiNetManager;
import com.haypi.framework.util.HaypiLog;
import com.haypi.util.HaypiUtil;

class NewsPuller implements Runnable {
	static final String TAG = News.TAG;
	private static Thread thread = null;
	private static final long MINUTE = 60 * 1000L;

	static void start() {
		if (thread != null)
			return;
		HaypiLog.d(TAG, "start");
		String url = buildURL();
		HaypiLog.d(TAG, "url=%s", url);
		thread = new Thread(new NewsPuller(url));
		thread.start();
	}

	static void stop() {
		if (thread == null)
			return;
		HaypiLog.d(TAG, "stop");
		thread.interrupt();
		thread = null;
	}

	private final String url;

	private NewsPuller(String url) {
		this.url = url;
	}

	@Override
	public void run() {
		while (true) {
			try {
				// refresh per 30 minutes or retry after 10 minutes
				Thread.sleep(pull(url) ? 30 * MINUTE : 10 * MINUTE);
			} catch (Exception e) {
			}
			if (Thread.interrupted()) {
				break;
			}
		}
	}

	/*
	 * pull News from Server
	 */
	private boolean pull(String url) {
		try {
			HttpURLConnection con = (HttpURLConnection) new URL(url).openConnection();
			int respCode = con.getResponseCode();
			if (respCode != HttpURLConnection.HTTP_OK) {
				HaypiLog.d(TAG, respCode + " " + con.getResponseMessage());
				return false;
			}
			InputStream in = con.getInputStream();
			ByteArrayOutputStream out = new ByteArrayOutputStream(4096);
			byte[] buf = new byte[2048];
			int n;
			while ((n = in.read(buf)) > -1) {
				out.write(buf, 0, n);
			}
			String encoding = con.getContentEncoding();
			if (encoding == null) {
				encoding = "UTF-8";
			}
			String resp = out.toString(encoding);
			String[] ss = HaypiUtil.split(resp, "\r\n");

			if (ss.length >= 3 && ss[0].equals("0") && ss[1].equals("0")) {
				int index = 2;
				int count = Integer.parseInt(ss[index++]);
				if (count > 0) {
					ArrayList<News> list = new ArrayList<News>();
					for (; count > 0; count--) {
						int version = Integer.parseInt(ss[index++]);
						if (version <= News.lastNewsVersion)
							continue;
						News.lastNewsVersion = version;
						News entity = new News();
						entity.setNew(true);
						entity.setVersion(version);
						entity.setStartTime(Integer.parseInt(ss[index++]));
						entity.setEndTime(Integer.parseInt(ss[index++]));
						entity.setSubject(ss[index++]);
						entity.setDescription(ss[index++]);
						entity.setContent(ss[index++]);
						entity.setToken(ss[index++]);
						entity.setButtonText(ss[index++]);
						entity.setNewsType(News.TYPE.values()[Integer.parseInt(ss[index++])]);
						entity.setTopNews("1".equals(ss[index++]));
						entity.setParams1(ss[index++]);
						entity.setParams2(ss[index++]);
						entity.setParams3(ss[index++]);
						list.add(entity);
					}
					if (list.size() > 0) {
						News.add(list);
					}
				}
			}
			con.disconnect();
			return true;
		} catch (Exception e) {
			HaypiLog.e(TAG, "poll", e);
			return false;
		}
	}

	private static String buildURL() {
		StringBuilder sb = new StringBuilder(256);
		sb.append(News.url);
		sb.append("?gid=" + News.gid);
		sb.append("&lan=" + HaypiNetManager.GetInstance().getCurrentRegionID());
		sb.append("&ver=" + News.lastNewsVersion);
		sb.append("&deviceid=" + HaypiNetManager.GetInstance().GetDeviceID());
		sb.append("&host_appid=" + News.host_appid);
		sb.append("&df=" + News.df);
		sb.append("&server=" + HaypiNetManager.GetInstance().GetServerID());
		return sb.toString();
	}
}