package com.haypi.billing;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Locale;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;

import com.haypi.framework.net.HaypiNetManager;
import com.haypi.framework.util.HaypiLog;
import com.haypi.util.HaypiUtil;

public abstract class BillingService {
	protected static final String tag = "IAP";

	private static BillingService instance;

	public static void create(Class<? extends BillingService> clazz) {
		HaypiUtil.checkUIThread();
		if (instance != null)
			return;
		if (clazz == null || clazz == BillingService.class) {
			clazz = DefaultBillingService.class;
		}
		try {
			instance = clazz.newInstance();
		} catch (Exception e) {
			e("Failed to create BillingService: %s", clazz.getName());
		}
	}

	public static BillingService getInstance() {
		HaypiUtil.checkUIThread();
		if (instance == null) {
			create(null);
		}
		return instance;
	}

	private static final int STATE_NONE = 0;
	private static final int STATE_CHECKING = 1;
	private static final int STATE_AVAILABLE = 2;
	private static final int STATE_UNAVAILABLE = 3;

	private int state = STATE_NONE;

	protected final Handler handler = new Handler();
	private final LinkedList<Runnable> tasks = new LinkedList<Runnable>();
	private Runnable currentTask;
	protected boolean enableDebug = true;
	private final List<Runnable> resumeTasks = Collections.synchronizedList(new LinkedList<Runnable>());

	public BillingService() {
		HaypiUtil.checkUIThread();
	}

	protected final BillingPayload getPayload() {
		return new BillingPayload();
	}

	protected String getCallback(BillingItem item) {
		String sku = "xxxxxx";
		if (item != null) {
			sku = item.getSku();
		}
		return String.format(Locale.ENGLISH, "%1$s-%2$s", sku, HaypiNetManager.GetInstance().GetUIDForSocket());
	}

	public abstract String getMessage(int code);

	public abstract boolean isSuccess(int code);

	public final boolean isFailure(int code) {
		return !isSuccess(code);
	}

	protected final boolean isAvailable() {
		return state == STATE_AVAILABLE;
	}

	protected void doInit(Context ctx) {
		postInitResult(true);
	}

	protected void doLoadData(Context ctx) {
		doNext();
	}

	public final void onActivityPause() {
		d("onActivityPause");
	}

	public final void onActivityResume() {
		d("onActivityResume");
		Runnable[] tasks;
		synchronized (resumeTasks) {
			tasks = resumeTasks.toArray(new Runnable[resumeTasks.size()]);
			resumeTasks.clear();
		}
		for (Runnable task : tasks) {
			task.run();
		}
	}

	protected abstract void doOrder(Activity activity, BillingItem item, BillingListener listener);

	protected final void addTask(final Runnable task) {
		tasks.offer(task);
		if (currentTask == null && (state == STATE_AVAILABLE || state == STATE_UNAVAILABLE)) {
			doNext();
		}
	}

	protected final void doNext() {
		runOnUIThread(new Runnable() {
			@Override
			public void run() {
				if ((currentTask = tasks.poll()) != null) {
					currentTask.run();
				}
			}
		});

	}

	private final void checkInit(Context ctx) {
		if (state != STATE_CHECKING && state != STATE_AVAILABLE) {
			state = STATE_CHECKING;
			enableDebug = HaypiLog.mLevel == HaypiLog.LOG_LEVEL.VERBOSE;
			d("doInit");
			doInit(ctx);
		}
	}

	public final void init(final Context ctx) {
		HaypiUtil.checkUIThread();
		checkInit(ctx);
		addTask(new Runnable() {
			@Override
			public void run() {
				if (isAvailable()) {
					d("doLoadData");
					doLoadData(ctx);
				} else {
					doNext();
				}
			}
		});
	}

	public String showPurchaseList(Activity act) {
		d("showPurchaseList");
		HaypiUtil.checkUIThread();
		return "0";
	}

	public final void order(final Activity activity, final BillingItem item, final BillingListener listener) {
		HaypiUtil.checkUIThread();
		init(activity);
		addTask(new Runnable() {
			@Override
			public void run() {
				d("doOrder,item=%s", item.getSku());
				doOrder(activity, item, listener);
			}
		});
	}

	public boolean handleActivityResult(int requestCode, int resultCode, Intent data) {
		return false;
	}

	protected final void postInitResult(final boolean support) {
		runOnUIThread(new Runnable() {
			@Override
			public void run() {
				state = support ? STATE_AVAILABLE : STATE_UNAVAILABLE;
				doNext();
			}
		});
	}

	protected final void postBillingResult(final BillingItem item, final BillingListener listener, final int code) {
		runOnUIThread(new Runnable() {
			@Override
			public void run() {
				d("onBillingFinish,item=%1$s,result=%2$d,message=%3$s", item.getSku(), code, getMessage(code));
				listener.onBillingFinish(code, item);
				doNext();
			}
		});
	};

	protected final void postBillingResultOnResume(final BillingItem item, final BillingListener listener, final int code) {
		resumeTasks.add(new Runnable() {
			@Override
			public void run() {
				postBillingResult(item, listener, code);
			}
		});
	}

	protected final void runOnUIThread(Runnable action) {
		if (HaypiUtil.isInUIThread()) {
			action.run();
		} else {
			handler.post(action);
		}
	}

	public static void d(String message) {
		HaypiLog.d(tag, message);
	}

	public static void d(String message, Object... args) {
		HaypiLog.d(tag, String.format(message, args));
	}

	public static void e(Throwable th, String message) {
		if ((HaypiLog.mLevel & 1) != 0) {
			android.util.Log.e(tag, message, th);
		}
	}

	public static void e(Throwable th, String message, Object... args) {
		if ((HaypiLog.mLevel & 1) != 0) {
			android.util.Log.e(tag, String.format(message, args), th);
		}
	}

	public static void e(String message) {
		if ((HaypiLog.mLevel & 1) != 0) {
			android.util.Log.e(tag, message);
		}
	}

	public static void e(String message, Object... args) {
		if ((HaypiLog.mLevel & 1) != 0) {
			android.util.Log.e(tag, String.format(message, args));
		}
	}
}