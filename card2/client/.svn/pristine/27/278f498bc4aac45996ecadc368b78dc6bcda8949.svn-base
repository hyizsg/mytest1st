#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include "platform/ios/CCFileUtilsIOS.h"

HNAMESPACE_BEGIN

class CC_DLL HFileUtils: public CCFileUtilsIOS {
    HSINGLETON_OBJECT(HFileUtils);
    CC_SYNTHESIZE(bool, m_bIsRetina, IsRetina);
    CC_SYNTHESIZE(bool, m_bInUI, InUI);
    CC_SYNTHESIZE_READONLY(char *, m_pResourceExtendPath, ResourceExtendPath);
    CC_SYNTHESIZE_READONLY(char *, m_pResourceZipFilePath, ResourceZipFilePath);
public:
    static bool fileInApp(const char *filename); //if file is in ios app
    
    static bool fileIsPVR(const char *filename);
    static bool fileIsJS(const char *filename);
    static bool fileIsPng(const char *filename);
    static bool fileIsJpeg(const char *filename);
    static bool fileIsImg(const char *filename);
    static bool fileIsPlist(const char *filename);
    static bool fileIsPlistb(const char *filename);
    static bool fileIsCCBI(const char *filename);
    static bool fileIsStrings(const char *filename);
    static void deleteFile(const char *filename);
    static const char *validPath(const char *filename);
    static const char *getFilename(const char *file);
    static const char *getFilepath(const char *file);
    bool pathExists(const char * path);
    int createDir(const char * path);
    void setResourceExtendPath(const char *path);
    
    static bool currentInUI();
    static void resetInUI(bool inUI);
    virtual unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
    unsigned char* getFileDataEx(const char* pszFileName, const char* pszMode, unsigned long * pSize);
    
    const char *getResourceName(const char *filename);
    unsigned char* getFileDataFromFile(const char* pszFileName, unsigned long * pSize);
    unsigned char* getFileData(const char* pszFileName, unsigned long * pSize);
//    unsigned char* getFileDataEx(const char* pszFileName, unsigned long * pSize);
    
    static void restoreBinaryData(unsigned char *data, unsigned long size, const char *ids, int idLen, int offset);
    static void restoreTextData(unsigned char *data, unsigned long size, const char *ids, int idLen, int offset);
    static void restoreDataContent(unsigned char *data, unsigned long size, const char *ids, int offset, const char *cmpID);
    static void restoreData(unsigned char *data, unsigned long size, const char* pszFileName);
    static void encodeDataContent(unsigned char *data, unsigned long size, const char *ids, int offset, const char *cmpID);
    static void encodeMapData(unsigned char *data, unsigned long size);
    
    virtual const char* fullPathFromRelativePath(const char *pszRelativePath);
    const char *fullPathFromRelativePathEx(const char *pszRelativePath);
    static const char *GetFullPathFromRelativePath(const char *pszRelativePath);
    
    virtual CCDictionary *dictionaryWithContentsOfFileThreadSafe(const char *pFileName);
    virtual CCArray *arrayWithContentsOfFileThreadSafe(const char *pFileName);
    virtual std::string getWriteablePath();
    std::string getWriteablePathEx();
    
    bool fileExistInZip(const char* pszZipFilePath, const char* pszFileName);
    bool fileExist(const char* pszFileName);
    static void setLocalPath(const char *path);
    static const char *getLocalPath();
    static void saveFileToLocal(const char *data, int size, const char *filename);
    static char *loadFileFromLocal(int *size, const char *filename);
    static void saveToLocal(CCDictionary *pDict, const char *filename);
    static CCDictionary *loadFromLocal(const char *filename);
    static CCDictionary *loadFromResource(const char *filename);
//    static CCDictionary *loadFromResourceEx(const char *filename);
    
    void attachPath(const char *path) { if (path) m_oAttachedPaths.addObject(CCString::create(path)); }
private:
    static std::string m_strLocalPath;
    CCArray m_oAttachedPaths;
};

HNAMESPACE_END

#endif // _FILE_UTILS_H_
