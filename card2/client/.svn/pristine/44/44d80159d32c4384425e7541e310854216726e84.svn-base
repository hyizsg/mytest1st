package com.haypi.gameframework;

import java.io.UnsupportedEncodingException;
import java.lang.ref.WeakReference;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.HashMap;
import java.util.Locale;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.ColorFilter;
import android.graphics.Paint;
import android.graphics.PointF;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.drawable.AnimationDrawable;
import android.graphics.drawable.Drawable;

import com.haypi.framework.util.HaypiLog;

public class TexturePackerPList extends PList {
	private static final int MODE_UNKNOW = 0;
	private static final int MODE_WHOLE_BITMAP = 1;
	private static final int MODE_ORIGINAL_BITMAP = 2;
	private static final int MODE_OPTIMIZE_BITMAP = 3;

	private static final int CPP_STRING_LENGTH = 48;
	private static int cpp_string_length = CPP_STRING_LENGTH;

	private static final String tag = "TexturePackerPList";
	private WeakReference<Bitmap> bitmap;
	private HashMap<String, WeakReference<Bitmap>> splitBitmaps;

	public static void setCppStringLength(int len) {
		cpp_string_length = len;
	}

	@Override
	void loadBinaryImpl(byte[] data) throws Exception {
		root.add(new HashMap<String, Object>());
		ByteBuffer bb = ByteBuffer.wrap(data).order(ByteOrder.LITTLE_ENDIAN);
		if (bb.getInt() != BINARY_TAG) {
			throw new UnsupportedEncodingException();
		}
		int count = bb.getInt();
		int format = bb.getInt();
		if (format != 1 && format != 2) {
			HaypiLog.w(TexturePackerPList.tag, "format=" + format);
		}
		bb.position(bb.position() + 8);// w,h
		HashMap<String, Object> metadata = new HashMap<String, Object>();
		getDict().put("metadata", metadata);
		String filename = readString(bb, cpp_string_length);
		metadata.put("realTextureFileName", filename);
		metadata.put("textureFileName", filename);
		metadata.put("format", format);
		HashMap<String, Object> frames = new HashMap<String, Object>();
		getDict().put("frames", frames);
		for (int i = 0; i < count; i++) {
			HashMap<String, Object> dict = new HashMap<String, Object>();
			int x = (int) bb.getFloat(); // frame
			int y = (int) bb.getFloat(); // frame
			int w = (int) bb.getFloat(); // frame
			int h = (int) bb.getFloat(); // frame
			dict.put("frame", format("{{%1$d,%2$d},{%3$d,%4$d}}", x, y, w, h));
			int ox = (int) bb.getFloat(); // offset x
			int oy = (int) bb.getFloat(); // offset y
			dict.put("offset", format("{%1$d,%2$d}", ox, oy));
			bb.mark();
			switch (format) {
			case 1:
			case 2:
				int sw = (int) bb.getFloat();// source size
				int sh = (int) bb.getFloat();// source size
				boolean rotated = bb.get() != 0;// rotate
				dict.put("sourceSize", format("{%1$d,%2$d}", sw, sh));
				dict.put("rotated", rotated);
				break;
			}
			bb.reset();
			bb.position(bb.position() + 16);
			frames.put(readString(bb, cpp_string_length), dict);
		}
	}

	private String readString(ByteBuffer bb, int len) {
		byte[] bytes = new byte[len];
		bb.get(bytes);
		for (int i = 0; i < len; i++) {
			if (bytes[i] == 0) {
				len = i;
				break;
			}
		}
		return new String(bytes, 0, len);
	}

	private String format(String format, Object... args) {
		return String.format(Locale.ENGLISH, format, args);
	}

	@Override
	void reset() {
		super.reset();
		bitmap = null;
		if (splitBitmaps != null) {
			splitBitmaps.clear();
		}
		splitBitmaps = null;
	}

	private Bitmap getBitmap(String frame) {
		WeakReference<Bitmap> ref = bitmap;
		if (ref == null && splitBitmaps != null) {
			ref = splitBitmaps.get(frame);
		}
		if (ref != null) {
			Bitmap _bitmap = ref.get();
			if (_bitmap != null) {
				return _bitmap;
			}
		}
		return loadBitmap(frame);
	}

	private Bitmap loadBitmap(String frame) {
		switch (getSourceType()) {
		default:
			throw new IllegalArgumentException("unsupport yet~");
		case NATIVE:
			if (splitBitmaps == null) {
				@SuppressWarnings("unchecked")
				HashMap<String, Object> metadata = (HashMap<String, Object>) getDict().get("metadata");
				String realTextureFileName = (String) metadata.get("realTextureFileName");
				Bitmap _bitmap = loadBitmapFromNative(realTextureFileName);
				if (_bitmap != null) {
					this.bitmap = new WeakReference<Bitmap>(_bitmap);
					return _bitmap;
				}
			}
			Bitmap _bitmap = loadBitmapFromNative(frame);
			if (_bitmap == null) {
				throw new RuntimeException("load failed: " + frame);
			}
			if (splitBitmaps == null) {
				splitBitmaps = new HashMap<String, WeakReference<Bitmap>>();
			}
			splitBitmaps.put(frame, new WeakReference<Bitmap>(_bitmap));
			return _bitmap;
		}
	}

	private Bitmap loadBitmapFromNative(String name) {
		byte[] data = GameFramework.loadResource(getSourceDir() + "/" + name);
		if (data == null) {
			return null;
		}
		return BitmapFactory.decodeByteArray(data, 0, data.length);
	}

	@SuppressWarnings("unchecked")
	public Drawable createFrame(final String frame) {
		HashMap<String, Object> metadata = (HashMap<String, Object>) getDict().get("metadata");
		int format = (Integer) metadata.get("format");
		if (format != 1 && format != 2) {
			HaypiLog.w(tag, "format=" + format);
		}
		HashMap<String, Object> frames = (HashMap<String, Object>) getDict().get("frames");
		final HashMap<String, Object> frameData = (HashMap<String, Object>) frames.get(frame);
		boolean rotated = (Boolean) frameData.get("rotated");
		if (rotated) {
			throw new RuntimeException("not implements rotate");
		}
		return new Drawable() {
			private final Bitmap bitmap = getBitmap(frame);
			private int mode = TexturePackerPList.this.bitmap != null ? MODE_WHOLE_BITMAP : MODE_UNKNOW;
			private Paint paint = new Paint();
			private Rect src = new Rect();
			private PointF dstOffset = new PointF();
			private int imgWidth, imgHeight;
			{
				int[] frame = Parser.rect((String) frameData.get("frame"), new int[4]);// {{146,2},{68,97}}
				src.set(frame[Parser.X], frame[Parser.Y], +frame[Parser.X] + frame[Parser.W], frame[Parser.Y] + frame[Parser.H]);
				int[] sourceSize = Parser.size((String) frameData.get("sourceSize"), new int[2]);// {102,119}
				this.imgWidth = sourceSize[Parser.X];
				this.imgHeight = sourceSize[Parser.Y];
				if (frameData.containsKey("sourceColorRect")) {
					int[] sourceColorRect = Parser.rect((String) frameData.get("sourceColorRect"), new int[4]);// {{26,19},{68,97}}
					dstOffset.set(sourceColorRect[Parser.X], sourceColorRect[Parser.Y]);
				} else if (frameData.containsKey("offset")) {
					int[] offset = Parser.size((String) frameData.get("offset"), new int[2]);// {9,-8}
					dstOffset.set((imgWidth - frame[Parser.W]) / 2.0f + offset[Parser.X], (imgHeight - frame[Parser.H]) / 2.0f - offset[Parser.Y]);
				} else {
					throw new RuntimeException("error");
				}
				if (mode == MODE_UNKNOW) {
					int width = bitmap.getWidth();
					int height = bitmap.getHeight();
					if (this.imgWidth == width && this.imgHeight == height) {
						mode = MODE_ORIGINAL_BITMAP;
					} else {
						mode = MODE_OPTIMIZE_BITMAP;
					}
					src.set(0, 0, width, height);
				}
			}

			@Override
			public void setColorFilter(ColorFilter cf) {
			}

			@Override
			public void setAlpha(int alpha) {
			}

			@Override
			public int getOpacity() {
				return 0;
			}

			@Override
			public void draw(Canvas canvas) {
				RectF dst = new RectF(getBounds());
				switch (mode) {
				case MODE_WHOLE_BITMAP:
				case MODE_OPTIMIZE_BITMAP:
					// x
					double xScale = dst.width() / imgWidth;
					dst.left += dstOffset.x * xScale;
					dst.right = (float) (dst.left + src.width() * xScale);
					// y
					double yScale = dst.height() / imgHeight;
					dst.top += dstOffset.y * yScale;
					dst.bottom = (float) (dst.top + src.height() * yScale);
					break;
				}
				canvas.drawBitmap(bitmap, src, dst, paint);
			}
		};
	}

	public AnimationDrawable createFrameAnimation(int duration, Iterable<String> names) {
		AnimationDrawable animation = new AnimationDrawable();
		for (String name : names) {
			animation.addFrame(createFrame(name), duration);
		}
		return animation;
	}

	public AnimationDrawable createFrameAnimation(int duration, String... names) {
		AnimationDrawable animation = new AnimationDrawable();
		for (String name : names) {
			animation.addFrame(createFrame(name), duration);
		}
		return animation;
	}

	public AnimationDrawable createFrameAnimation(int duration, String format, int start, int end) {
		AnimationDrawable animation = new AnimationDrawable();
		for (int index = start; index <= end; index++) {
			animation.addFrame(createFrame(String.format(Locale.ENGLISH, format, index)), duration);
		}
		return animation;
	}

	private static class Parser {
		static final int X = 0;
		static final int Y = 1;
		static final int W = 2;
		static final int H = 3;

		private static final String d = "(-?\\d+)";
		static final Pattern sizePattern = Pattern.compile("\\{" + d + "," + d + "\\}");// {9,-8}
		static final Pattern rectPattern = Pattern.compile("\\{" + sizePattern + "," + sizePattern + "\\}");// {{146,2},{68,97}}

		static int[] size(String str, int[] size) {
			Matcher m = sizePattern.matcher(str);
			m.find();
			size[X] = Integer.parseInt(m.group(1));
			size[Y] = Integer.parseInt(m.group(2));
			return size;
		}

		static int[] rect(String str, int[] rect) {
			Matcher m = rectPattern.matcher(str);
			m.find();
			rect[X] = Integer.parseInt(m.group(1));
			rect[Y] = Integer.parseInt(m.group(2));
			rect[W] = Integer.parseInt(m.group(3));
			rect[H] = Integer.parseInt(m.group(4));
			return rect;
		}
	}
}