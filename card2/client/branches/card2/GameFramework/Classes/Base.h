#ifndef _BASE_H_
#define _BASE_H_

HNAMESPACE_BEGIN

//common
CC_DLL void setRandomSeed(long seed);
CC_DLL long getRandom();

CC_DLL bool stringEndsWith(const char *filename, const char *ends);

//base64
CC_DLL int encodeBase64(void *result, const void *data, int len);
CC_DLL int decodeBase64(void *result, const void *data, int len);

//md5
CC_DLL void MD5Init (MD5_CTX *context);
CC_DLL void MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen);
CC_DLL void MD5Final (unsigned char digest[16], MD5_CTX *context);
CC_DLL void MD5Data(const void *data, int len, unsigned char digest[16]);

CC_DLL void convertPVR2PNG(const char *pvr, const char *png);
//zip
CC_DLL int zip(unsigned char *data, int len, unsigned char *result, int size);
CC_DLL int unzip(unsigned char *data, int len, unsigned char *result, int size);
CC_DLL void unzipFile(const char *zipFile, const char *dir, const char *resultPath, CCArray *excludeList = NULL, CCArray *includeList = NULL, FuncOnPercent onPercent = NULL, bool pvr2Png = false);
CC_DLL bool pathExists(const char *path);
CC_DLL int createDir(const char *path);

//dictionary
CC_DLL CCDictionary *dictionaryFromPlist(const char *data, unsigned int size);
CC_DLL CCDictionary *dictionaryFromPlist(const char *filename);
CC_DLL CCDictionary *dictionaryFromJSON(const char *data, unsigned int size);
CC_DLL CCDictionary *dictionaryFromJSON(const char *filename);
CC_DLL std::string dictionaryToJSON(CCDictionary *dict);
CC_DLL CCArray *arrayFromJSON(const char *data, unsigned int size);

HNAMESPACE_END

#endif //_BASE_H_