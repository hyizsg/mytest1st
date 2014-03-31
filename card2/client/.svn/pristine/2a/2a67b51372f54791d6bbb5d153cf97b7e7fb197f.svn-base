package com.haypi.share.twitter;

import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.view.Display;
import android.view.Window;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.LinearLayout;

public class TwDialog extends Dialog {
	static final float[] DIMENSIONS_DIFF_LANDSCAPE = { 20, 60 };
	static final float[] DIMENSIONS_DIFF_PORTRAIT = { 40, 60 };

	private String mUrl;
	private DialogListener mListener;
	private ProgressDialog mSpinner;
	private WebView mWebView;
	private LinearLayout mContent;

	public TwDialog(Context context, String url, DialogListener listener) {
		super(context);
		this.mUrl = url;
		this.mListener = listener;
	}

	@SuppressWarnings("deprecation")
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		mSpinner = new ProgressDialog(getContext());
		mSpinner.requestWindowFeature(Window.FEATURE_NO_TITLE);
		mSpinner.setMessage("Loading...");
		mContent = new LinearLayout(getContext());
		mContent.setOrientation(LinearLayout.VERTICAL);
		setUpWebView();

		Display display = getWindow().getWindowManager().getDefaultDisplay();
		final float scale = getContext().getResources().getDisplayMetrics().density;
		int orientation = getContext().getResources().getConfiguration().orientation;
		float[] dimensions = (orientation == Configuration.ORIENTATION_LANDSCAPE) ? DIMENSIONS_DIFF_LANDSCAPE : DIMENSIONS_DIFF_PORTRAIT;
		addContentView(mContent, new LinearLayout.LayoutParams(display.getWidth() - ((int) (dimensions[0] * scale + 0.5f)), display.getHeight() - ((int) (dimensions[1] * scale + 0.5f))));

		setCancelable(false);
	}

	private void setUpWebView() {
		mWebView = new WebView(getContext());
		mWebView.setVerticalScrollBarEnabled(false);
		mWebView.setHorizontalScrollBarEnabled(false);
		mWebView.setWebViewClient(new TwWebViewClient());
		mWebView.getSettings().setJavaScriptEnabled(true);
		mWebView.loadUrl(mUrl);
		mWebView.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
		mContent.addView(mWebView);
	}

	private class TwWebViewClient extends WebViewClient {
		@Override
		public boolean shouldOverrideUrlLoading(WebView view, String url) {
			if (url.startsWith(TwitterSharer.CALLBACK_URL)) {
				dismiss();
				mListener.onComplete(url);
				return true;
			}
			view.loadUrl(url);
			return true;
		}

		@Override
		public void onReceivedError(WebView view, int errorCode, String description, String failingUrl) {
			super.onReceivedError(view, errorCode, description, failingUrl);
			mListener.onError(new DialogError(description, errorCode, failingUrl));
			TwDialog.this.dismiss();
		}

		@Override
		public void onPageStarted(WebView view, String url, Bitmap favicon) {
			super.onPageStarted(view, url, favicon);
			mSpinner.show();
		}

		@Override
		public void onPageFinished(WebView view, String url) {
			super.onPageFinished(view, url);
			mSpinner.dismiss();
		}
	}
}