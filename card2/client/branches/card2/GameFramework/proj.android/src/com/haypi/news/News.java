package com.haypi.news;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import android.app.Application;
import android.content.Context;
import android.os.Handler;
import android.util.DisplayMetrics;

import com.haypi.util.HaypiUtil;

public class News {
	// config
	static String url;
	static String gid;
	static String host_appid;

	public static void init(Application app, String gid, String host_appid, String url) {
		HaypiUtil.checkUIThread();
		News.gid = gid;
		News.host_appid = host_appid;
		News.url = url;
		ctx = app;
		handler = new Handler();
		DisplayMetrics dm = app.getResources().getDisplayMetrics();
		int size = Math.max(dm.widthPixels, dm.heightPixels);
		if (size >= 720) {
			df = PAD;
		}
	}

	static final String TAG = "News";

	private static final int PHONE = 3;
	private static final int PAD = 4;

	private static final String filename = "news.db";
	private static final int HEADER = 0xFEDCBA98;
	private static boolean loaded = false;

	private static Context ctx;
	private static Handler handler;
	static int df = PHONE;
	private static List<News> newsList = new ArrayList<News>();
	private static List<News> topNewsList = new ArrayList<News>();
	private static volatile boolean newsArrive;
	static int lastNewsVersion = 0;

	public static boolean hasNewsArrive() {
		return newsArrive;
	}

	public static void setNewsArrive(boolean b) {
		newsArrive = b;
	}

	public static List<News> getNewsList() {
		HaypiUtil.checkUIThread();
		return newsList;
	}

	public static List<News> getTopNewsList() {
		HaypiUtil.checkUIThread();
		return topNewsList;
	}

	public static int getUnread() {
		int unread = 0;
		for (News news : newsList)
			if (news.isNew) {
				unread++;
			}
		return unread;
	}

	public static void start() {
		HaypiUtil.checkUIThread();
		load();
		NewsPuller.start();
	}

	public static void stop() {
		HaypiUtil.checkUIThread();
		NewsPuller.stop();
	}

	private static void load() {
		if (loaded)
			return;
		loaded = true;
		newsList = new ArrayList<News>();
		InputStream in = null;
		int now = (int) (System.currentTimeMillis() / 1000);
		try {
			in = ctx.openFileInput(filename);
			DataInputStream dis = new DataInputStream(in);
			while (true) {
				if (dis.read() < 0)
					break;
				if (dis.readInt() != HEADER)
					throw new IOException();
				News entity = new News();
				entity.isNew = dis.readBoolean();
				entity.version = dis.readInt();
				entity.startTime = dis.readInt();
				entity.endTime = dis.readInt();
				entity.subject = dis.readUTF();
				entity.description = dis.readUTF();
				entity.content = dis.readUTF();
				entity.token = dis.readUTF();
				entity.buttonText = dis.readUTF();
				entity.newsType = TYPE.values()[dis.readByte()];
				entity.topNews = dis.readBoolean();
				entity.params1 = dis.readUTF();
				entity.params2 = dis.readUTF();
				entity.params3 = dis.readUTF();
				if (entity.version <= lastNewsVersion)
					continue;
				lastNewsVersion = entity.version;
				newsList.add(entity);
			}
			in.close();
		} catch (Exception e) {
			newsList.clear();
			HaypiUtil.close(in);
			clear();
			lastNewsVersion = 0;
		}
		boolean removed = false;
		// keep the last News to keep the lastNewsVersion
		for (int i = newsList.size() - 2; i >= 0; i--) {
			News entity = newsList.get(i);
			if (entity.endTime <= now) {
				newsList.remove(i);
				removed = true;
			}
		}
		if (removed) {
			save();
		}
	}

	private static void clear() {
		ctx.deleteFile(filename);
	}

	public static void save() {
		try {
			DataOutputStream out = new DataOutputStream(ctx.openFileOutput(filename, Context.MODE_PRIVATE));
			for (News entity : newsList) {
				out.write(0);
				out.writeInt(HEADER);
				out.writeBoolean(entity.isNew);
				out.writeInt(entity.version);
				out.writeInt(entity.startTime);
				out.writeInt(entity.endTime);
				out.writeUTF(entity.subject);
				out.writeUTF(entity.description);
				out.writeUTF(entity.content);
				out.writeUTF(entity.token);
				out.writeUTF(entity.buttonText);
				out.writeByte(entity.newsType.ordinal());
				out.writeBoolean(entity.topNews);
				out.writeUTF(entity.params1);
				out.writeUTF(entity.params2);
				out.writeUTF(entity.params3);
			}
			out.flush();
			out.close();
		} catch (Exception e) {
		}
	}

	static void add(final ArrayList<News> added) {
		handler.post(new Runnable() {
			@Override
			public void run() {
				newsList.addAll(added);
				save();
				for (News entity : added) {
					if (entity.topNews)
						topNewsList.add(entity);
				}
				newsArrive = true;
			}
		});
	}

	public enum TYPE {
		ADV, NEWS
	}

	private boolean isNew;
	private int version;
	private int startTime;
	private int endTime;
	private String subject;
	private String description;
	private String content;
	private String token;
	private String buttonText;
	private TYPE newsType;
	private boolean topNews;
	private String params1;
	private String params2;
	private String params3;

	public boolean isNew() {
		return isNew;
	}

	public void setNew(boolean isNew) {
		this.isNew = isNew;
	}

	public int getVersion() {
		return version;
	}

	public void setVersion(int version) {
		this.version = version;
	}

	public int getStartTime() {
		return startTime;
	}

	public void setStartTime(int startTime) {
		this.startTime = startTime;
	}

	public int getEndTime() {
		return endTime;
	}

	public void setEndTime(int endTime) {
		this.endTime = endTime;
	}

	public String getSubject() {
		return subject;
	}

	public void setSubject(String subject) {
		this.subject = subject;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

	public String getToken() {
		return token;
	}

	public void setToken(String token) {
		this.token = token;
	}

	public String getButtonText() {
		return buttonText;
	}

	public void setButtonText(String buttonText) {
		this.buttonText = buttonText;
	}

	public TYPE getNewsType() {
		return newsType;
	}

	public void setNewsType(TYPE newsType) {
		this.newsType = newsType;
	}

	public boolean isTopNews() {
		return topNews;
	}

	public void setTopNews(boolean topNews) {
		this.topNews = topNews;
	}

	public String getParams1() {
		return params1;
	}

	public void setParams1(String params1) {
		this.params1 = params1;
	}

	public String getParams2() {
		return params2;
	}

	public void setParams2(String params2) {
		this.params2 = params2;
	}

	public String getParams3() {
		return params3;
	}

	public void setParams3(String params3) {
		this.params3 = params3;
	}
}