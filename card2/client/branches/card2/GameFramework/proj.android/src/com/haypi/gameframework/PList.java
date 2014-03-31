package com.haypi.gameframework;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Stack;

import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import android.content.Context;

import com.haypi.util.HaypiUtil;

public class PList {
	final static int BINARY_TAG = 0x01020304;

	public enum SourceType {
		STREAM, NATIVE, ASSETS, FILE;
	}

	@SuppressWarnings("unused")
	private static final String tag = "PList";
	final ArrayList<HashMap<String, Object>> root = new ArrayList<HashMap<String, Object>>();
	boolean isArray = false;
	private SourceType sourceType = null;
	private String source;

	public void loadFromNative(String path) {
		this.sourceType = SourceType.NATIVE;
		this.source = path;
		reset();
		try {
			byte[] data = GameFramework.loadResource(path + "b");
			if (data != null) {
				__loadBinary(data);
			} else {
				data = GameFramework.loadResource(path);
				__loadXML(data);
			}
		} catch (Exception e) {
			throw new RuntimeException("loadFromNative failed " + path, e);
		}
	}

	public void loadFromAssets(Context ctx, String path) {
		sourceType = SourceType.ASSETS;
		source = path;
		reset();
		try {
			try {
				__loadBinary(ctx.getAssets().open(path + "b"));
			} catch (FileNotFoundException e) {
				__loadXML(ctx.getAssets().open(path));
			}
		} catch (Exception e) {
			throw new RuntimeException("loadFromAssets failed " + path, e);
		}
	}

	public void load(File file) {
		sourceType = SourceType.FILE;
		source = file.getAbsolutePath();
		reset();
		try {
			File bin = new File(file.getAbsolutePath() + "b");
			if (bin.exists()) {
				__loadBinary(new FileInputStream(bin));
			} else {
				__loadXML(new FileInputStream(file));
			}
		} catch (Exception e) {
			throw new RuntimeException("load file failed " + file.getAbsolutePath(), e);
		}
	}

	public void load(InputStream is) {
		sourceType = SourceType.STREAM;
		source = null;
		DataInputStream dis = HaypiUtil.getMarkDataInputStream(is);
		dis.mark(4);
		try {
			boolean isBinary = Integer.reverseBytes(dis.readInt()) == BINARY_TAG;
			dis.reset();
			if (isBinary) {
				__loadBinary(dis);
			} else {
				__loadXML(dis);
			}
		} catch (Exception e) {
			throw new RuntimeException(e);
		} finally {
			HaypiUtil.close(is);
		}
	}

	private void __loadXML(byte[] data) {
		__loadXML(new ByteArrayInputStream(data));
	}

	private void __loadXML(InputStream is) {
		SAXParserFactory factory = SAXParserFactory.newInstance();
		try {
			factory.newSAXParser().parse(is, new PListHandler());
		} catch (Exception e) {
			throw new RuntimeException(e);
		} finally {
			HaypiUtil.close(is);
		}
	}

	private void __loadBinary(byte[] data) throws Exception {
		loadBinaryImpl(data);
	}

	private void __loadBinary(InputStream is) throws Exception {
		__loadBinary(HaypiUtil.readFully(is));
	}

	void loadBinaryImpl(byte[] data) throws Exception {
		throw new UnsupportedOperationException();
	}

	void reset() {
		root.clear();
		isArray = false;
	}

	public boolean isArray() {
		return isArray;
	}

	public HashMap<String, Object> getDict(int index) {
		return root.get(index);
	}

	public HashMap<String, Object> getDict() {
		return getDict(0);
	}

	public SourceType getSourceType() {
		return sourceType;
	}

	public String getSource() {
		return source;
	}

	public String getSourceDir() {
		int index = source.lastIndexOf(File.separatorChar);
		if (index < 0)
			return "";
		return source.substring(0, index);
	}

	enum STATE {
		NONE, KEY, STRING, INTEGER;
	}

	private class PListHandler extends DefaultHandler {
		private STATE state = STATE.NONE;
		private String key;
		private HashMap<String, Object> dict;
		private Stack<HashMap<String, Object>> dictStack = new Stack<HashMap<String, Object>>();

		@Override
		public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
			if ("array".equals(qName)) {
				isArray = true;
			}
			if ("dict".equals(qName)) {
				if (key == null) {
					root.add(dict = new HashMap<String, Object>());
					dictStack.clear();
				} else {
					dictStack.push(dict);
					HashMap<String, Object> subDict = new HashMap<String, Object>();
					dict.put(key, subDict);
					dict = subDict;
				}
			} else if ("key".equals(qName)) {
				state = STATE.KEY;
			} else if ("string".equals(qName)) {
				state = STATE.STRING;
			} else if ("false".equals(qName)) {
				dict.put(key, false);
				key = null;
			} else if ("true".equals(qName)) {
				dict.put(key, true);
				key = null;
			} else if ("integer".equals(qName)) {
				state = STATE.INTEGER;
			}
		}

		@Override
		public void characters(char[] ch, int start, int length) throws SAXException {
			if (length <= 0)
				return;
			String value = new String(ch, start, length);
			switch (state) {
			case KEY:
				key = value;
				state = STATE.NONE;
				break;
			case STRING:
				dict.put(key, value);
				key = null;
				state = STATE.NONE;
				break;
			case INTEGER:
				dict.put(key, Integer.valueOf(value));
				key = null;
				state = STATE.NONE;
				break;
			default:
				break;
			}
		}

		@Override
		public void endElement(String uri, String localName, String qName) throws SAXException {
			if ("dict".equals(qName)) {
				dict = dictStack.isEmpty() ? null : dictStack.pop();
			}
		}
	};
}