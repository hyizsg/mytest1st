package com.haypi.widget;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.RelativeLayout;

abstract public class ListViewItemView<T> extends RelativeLayout {
	protected T item;

	public ListViewItemView(Context context, T t) {
		this(context);
		updateView(t);
	}

	public ListViewItemView(Context context) {
		super(context);
		init();
	}

	public ListViewItemView(Context context, AttributeSet attrs) {
		super(context, attrs);
		init();
	}

	public ListViewItemView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		init();
	}

	protected final void setContentView(int layout) {
		LayoutInflater.from(getContext()).inflate(layout, this);
	}

	abstract protected void init();

	public void updateView(T item) {
		this.item = item;
	}

	public final T getItem() {
		return item;
	}
}