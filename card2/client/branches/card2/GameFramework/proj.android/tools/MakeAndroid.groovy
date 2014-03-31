import java.io.*;
import java.util.*;
import java.util.regex.*;

public class MakeAndroid {
	static ArrayList<String> ignores = new ArrayList<String>();
	static{
		ignores.add("gameframework/HaypiJSBFunc.cpp");
		ignores.add("FileUtils.cpp");
		ignores.add("Haypi-JSB/.*");
		ignores.add("json/.*");
	}
	static boolean ignore(String path){
		for(String s : ignores) {
			if(path.matches(s))
				return true;
		}
		return false;
	}
	static String SRC_PATH = "../../Classes";
	static String makefile = "../jni/Android.mk";
	static String makefile_debug = "../jni/Android.mk.debug";
	static String makefile_release = "../jni/Android.mk.release";

	static ArrayList<String> contents = new ArrayList<String>();
	static Comparator<String> comparator = new Comparator<String>() {
		@Override
		public int compare(String s1, String s2) {
			return s1.compareTo(s2);
		}
	};

	public static void main(String[] args) throws Exception {
		SRC_PATH = newFile(SRC_PATH).getCanonicalPath();
		makefile = newFile(makefile).getCanonicalPath();
		loadMakeFile();
		saveMakeFile();
		contents.clear();
		makefile = newFile(makefile_debug).getCanonicalPath();
		loadMakeFile();
		saveMakeFile();
		contents.clear();
		makefile = newFile(makefile_release).getCanonicalPath();
		loadMakeFile();
		saveMakeFile();
	}

	static void loadMakeFile() throws Exception {
		BufferedReader br = new BufferedReader(new FileReader(makefile));
		String line;
		while ((line = br.readLine()) != null) {
			//LOCAL_SRC_FILES
			if (line.trim().startsWith("LOCAL_SRC_FILES :=")) {
				while(true){
					line = br.readLine();
					if(line.trim().isEmpty()){
						list_LOCAL_SRC_FILES();
						break;
					}
				}
			}
			contents.add(line);
		}
		br.close();
	}

	static void list_LOCAL_SRC_FILES() throws Exception {
		ArrayList<String> cppFiles = listFiles(new File(makefile).getParentFile(), ".cpp", ".c");
		for(int i=0;i<cppFiles.size();i++){
			if(ignore(cppFiles.get(i))){
				cppFiles.remove(i);
				i--;
			}
		}
		for(String s : listFiles(new File(SRC_PATH), ".cpp", ".c"))
			if(ignore(s) == false)
				cppFiles.add("\$(SRC_PATH)/"+s);
		contents.add("LOCAL_SRC_FILES := " + cppFiles.get(0) + " \\");
		for (int i = 1; i < cppFiles.size()-1; i++)
			contents.add("                   " + cppFiles.get(i) + " \\");
		contents.add("                   " + cppFiles.get(cppFiles.size() - 1));
	}

	static void saveMakeFile() throws Exception {
		PrintStream out = new PrintStream(makefile);
		for (String s : contents)
			out.println(s);
		out.flush();
		out.close();
	}

	static ArrayList<String> listFiles(File dir, String... suffix) {
		ArrayList<String> list = new ArrayList<String>();
		listFiles(dir.getPath().length() + 1, list, dir, suffix);
		Collections.sort(list, comparator);
		return list;
	}

	static ArrayList<String> listFiles(int baseDirLength, ArrayList<String> list, File dir, String... suffix) {
		File[] files = dir.listFiles();
		if (files != null) {
			for (File f : files) {
				if (f.isDirectory()) {
					listFiles(baseDirLength, list, f, suffix);
				}
				if (f.isFile()) {
					String filename = f.getPath().substring(baseDirLength).replace('\\', '/');
					for (String s : suffix)
						if (filename.endsWith(s)) {
							list.add(filename);
							break;
						}
				}
			}
		}
		return list;
	}

	static ArrayList<String> listDirs(File dir, String... suffix) {
		ArrayList<String> list = new ArrayList<String>();
		int beginIndex = dir.getPath().length() + 1;
		for (String f : listFiles(dir, suffix)) {
			String dirname = new File(dir, f).getParentFile().getAbsolutePath();
			dirname = dirname.substring(Math.min(dirname.length(), beginIndex)).replace('\\', '/');
			if (!list.contains(dirname)) {
				list.add(dirname);
			}
		}
		Collections.sort(list, comparator);
		return list;
	}

	private static String CLASS_DIR;
	static {
		try {
			CLASS_DIR = new File(java.net.URLDecoder.decode(MakeAndroid.class.getProtectionDomain().getCodeSource().getLocation().getFile(), "UTF-8")).getParent();
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
	}

	static File newFile(String path) {
		return new File(CLASS_DIR, path);
	}
}
