package com.haypi.app;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.WeakHashMap;

import android.app.Activity;
import android.content.Context;
import android.content.ContextWrapper;

import com.haypi.util.WeakHashSet;

public class DialogManager {

	private static WeakHashMap<Object, WeakHashSet<Dialog>> dialogs = new WeakHashMap<Object, WeakHashSet<Dialog>>();

	public static Activity getActivity(Dialog dialog) {
		if (dialog == null)
			throw new NullPointerException();
		Context ctx = dialog.getContext();
		do {
			if (ctx instanceof Activity) {
				return (Activity) ctx;
			}
			if (ctx instanceof ContextWrapper) {
				ctx = ((ContextWrapper) ctx).getBaseContext();
				continue;
			} else {
				return null;
			}
		} while (true);
	}

	static void add(Dialog dialog) {
		final Object key = getActivity(dialog);
		if (key == null)
			return;
		synchronized (dialogs) {
			WeakHashSet<Dialog> dialogSet = dialogs.get(key);
			if (dialogSet == null) {
				dialogs.put(key, dialogSet = new WeakHashSet<Dialog>());
			}
			dialogSet.add(dialog);
		}
	}

	static void remove(Dialog dialog) {
		final Object key = getActivity(dialog);
		if (key == null)
			return;
		synchronized (dialogs) {
			WeakHashSet<Dialog> dialogSet = dialogs.get(key);
			if (dialogSet != null) {
				dialogSet.remove(dialog);
			}
		}
	}

	public static void dismiss(Dialog dialog) {
		if (dialog == null)
			return;
		if (dialog.isShowing()) {
			try {
				dialog.dismiss();
			} catch (Exception e) {
			}
		}
	}

	public static void dismissAll(Iterable<Dialog> iterable) {
		if (iterable == null)
			return;
		Iterator<Dialog> it = iterable.iterator();
		for (; it.hasNext();) {
			dismiss(it.next());
			it.remove();
		}
	}

	public static void dismissAll(Activity activity) {
		if (activity == null)
			throw new NullPointerException();
		final Object key = activity;
		WeakHashSet<Dialog> set;
		synchronized (dialogs) {
			set = dialogs.remove(key);
		}
		dismissAll(set);
	}

	public static void dismissAll() {
		ArrayList<WeakHashSet<Dialog>> list;
		synchronized (dialogs) {
			list = new ArrayList<WeakHashSet<Dialog>>(dialogs.values());
			dialogs.clear();
		}
		for (WeakHashSet<Dialog> set : list) {
			dismissAll(set);
		}
		list.clear();
	}

	public static void dismissAll(Class<? extends Dialog> clazz) {
		ArrayList<Dialog> list = new ArrayList<Dialog>();
		synchronized (dialogs) {
			for (WeakHashSet<Dialog> set : dialogs.values()) {
				Iterator<Dialog> it = set.iterator();
				for (; it.hasNext();) {
					Dialog dialog = it.next();
					if (clazz.isInstance(dialog)) {
						list.add(dialog);
						it.remove();
					}
				}
			}
		}
		dismissAll(list);
	}
}