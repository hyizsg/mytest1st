package com.haypi.widget;

import java.lang.reflect.Constructor;
import java.util.ArrayList;
import java.util.HashMap;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;

import com.haypi.framework.util.HaypiLog;

public class ListViewAdapter<T> extends BaseAdapter {
	private Context ctx;
	private Constructor<? extends ListViewItemView<T>> constructor;
	private ArrayList<T> items = new ArrayList<T>();
	private HashMap<Class<T>, Constructor<? extends ListViewItemView<T>>> constructorMap;
	private boolean supportMultiType;

	public ListViewAdapter(Context ctx, Class<? extends ListViewItemView<T>> clazz) {
		this.ctx = ctx;
		try {
			constructor = clazz.getConstructor(Context.class);
		} catch (NoSuchMethodException e) {
			throw new RuntimeException("cant find <init>(Context) for class " + clazz.getName(), e);
		}
	}

	public final void addSupportItemView(Class<T> item, Class<? extends ListViewItemView<T>> view) {
		if (!supportMultiType) {
			supportMultiType = true;
			constructorMap = new HashMap<Class<T>, Constructor<? extends ListViewItemView<T>>>();
		}
		try {
			constructorMap.put(item, view.getConstructor(Context.class));
		} catch (NoSuchMethodException e) {
			throw new RuntimeException("cant find <init>(Context) for class " + view.getName(), e);
		}
	}

	private Constructor<? extends ListViewItemView<T>> getConstructor(T t) {
		if (!supportMultiType)
			return constructor;
		Class clazz = t.getClass();
		Constructor<? extends ListViewItemView<T>> c = null;
		while (true) {
			c = constructorMap.get(clazz);
			clazz = clazz.getSuperclass();
			if (c != null || clazz == null)
				break;
		}
		return c;
	}

	@Override
	public final int getCount() {
		return items.size();
	}

	@Override
	public final T getItem(int position) {
		return items.get(position);
	}

	@Override
	public final long getItemId(int position) {
		return position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		T t = getItem(position);
		if (convertView == null) {
			try {
				convertView = getConstructor(t).newInstance(ctx);
			} catch (Exception e) {
				HaypiLog.e(e);
			}
		}
		ListViewItemView<T> itemView = (ListViewItemView<T>) convertView;
		itemView.updateView(t);
		return itemView;
	}

	public final void setData(Iterable<T> iterable) {
		this.items.clear();
		for (T t : iterable)
			this.items.add(t);
		super.notifyDataSetChanged();
	}

	public final void setData(T... data) {
		this.items.clear();
		for (T t : data)
			this.items.add(t);
		super.notifyDataSetChanged();
	}
}