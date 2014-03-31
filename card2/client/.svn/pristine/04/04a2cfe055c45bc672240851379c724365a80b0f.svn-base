
#include "cocos2dxframework.h"
#include "Base.h"
#include "support/zip_support/unzip.h"
#include "UpdateManager.h"


HNAMESPACE_BEGIN

HSINGLETON_OBJECT_IMP(HFileUtils);

std::string HFileUtils::m_strLocalPath = "";

HFileUtils::HFileUtils(): m_bInUI(false), m_pResourceExtendPath(NULL), m_pResourceZipFilePath(NULL) {
    m_gHFileUtils = this;
//    resetFileUtil(this);
    
#ifdef HOS_APPLE
    const char *zipFilePath = GetFullPathFromRelativePath("resource.dat");
    if (zipFilePath && strcmp(zipFilePath, "resource.dat")) {
        int zipFilePathLen = strlen(zipFilePath);
        if (zipFilePathLen > 0) {
            m_pResourceZipFilePath = (char *)malloc(sizeof(char) * (zipFilePathLen + 1));
            strcpy(m_pResourceZipFilePath, zipFilePath);
        }
    }
#endif
#ifdef HOS_LINUX
#endif
#ifdef HOS_WIN32
#endif
}

HFileUtils::~HFileUtils() {
    if (m_pResourceExtendPath) free(m_pResourceExtendPath);
    if (m_pResourceZipFilePath) free(m_pResourceZipFilePath);
}

bool HFileUtils::fileInApp(const char *filename) {
    return NULL != strstr(filename, ".app/");
}

bool HFileUtils::fileIsPVR(const char *filename) {
    return stringEndsWith(filename, ".pvr") || stringEndsWith(filename, ".pvr.ccz");
}

bool HFileUtils::fileIsJS(const char *filename) {
    return stringEndsWith(filename, ".js");
}

bool HFileUtils::fileIsPng(const char *filename) {
    int len = strlen(filename);
    if (len < 4) return false;
    char tmp[8];
    strcpy(tmp, filename + len - 4);
    HLOWERCASE(tmp);
    return 0 == strcmp(tmp, ".png");
//    return stringEndsWith(filename, ".png");
}

bool HFileUtils::fileIsImg(const char *filename)
{    
    return stringEndsWith(filename, ".png") ||
           stringEndsWith(filename, ".jpg") ||
           stringEndsWith(filename, ".jpeg") ||
               stringEndsWith(filename, ".pvr") ||
               stringEndsWith(filename, ".pvr.ccz") ||
               stringEndsWith(filename, ".plist") ||
    stringEndsWith(filename, ".plistb");
}

bool HFileUtils::fileIsJpeg(const char *filename) {
    int len = strlen(filename);
    if (len < 5) return false;
    char tmp[8];
    strcpy(tmp, filename + len - 5);
    HLOWERCASE(tmp);
    return (0 == strcmp(tmp + 1, ".jpg")) || (0 == strcmp(tmp, ".jpeg"));
//    return stringEndsWith(filename, ".jpg") || stringEndsWith(filename, ".jpeg");
}

bool HFileUtils::fileIsPlist(const char *filename) {
    return stringEndsWith(filename, ".plist");
}

bool HFileUtils::fileIsPlistb(const char *filename) {
    return stringEndsWith(filename, ".plistb");
}

bool HFileUtils::fileIsCCBI(const char *filename) {
    return stringEndsWith(filename, ".ccbi");
}

bool HFileUtils::fileIsStrings(const char *filename) {
    return stringEndsWith(filename, ".strings");
}

void HFileUtils::deleteFile(const char *filename) {
    remove(filename);
}

const char *HFileUtils::validPath(const char *filename) {
    char *pos = strstr(filename, "../");
    if (!pos) return filename;
    char fileBuffer[256];
    strcpy(fileBuffer, filename);
    int len = pos - filename;
    pos = fileBuffer + len;
    while (1) {
        HASSERT(pos != fileBuffer, "connot process dir ../ as root dir in zip file");
        char *start = pos - 2;
        while (start >= fileBuffer) {
            if (*start == '/') break;
            --start;
        }
        if (start >= fileBuffer) {
            strcpy(start, pos + 2);
        } else {
            strcpy(fileBuffer, pos + 3);
            break;
        }
        
        pos = strstr(fileBuffer, "../");
        if (!pos) break;
    }
    return CCString::create(fileBuffer)->getCString();
}

const char *HFileUtils::getFilename(const char *file) {
    int len = strlen(file);
    int pos = len - 1;
    while (pos >= 0) {
        if (file[pos] == '/') break;
        --pos;
    }
    if (pos >= 0) {
        return CCString::create(file + pos + 1)->getCString();
    } else {
        return file;
    }
}

const char *HFileUtils::getFilepath(const char *file) {
    int len = strlen(file);
    int pos = len - 1;
    while (pos >= 0) {
        if (file[pos] == '/') break;
        --pos;
    }
    if (pos >= 0) {
        char buf[256];
        memcpy(buf, file, pos + 1);
        buf[pos + 1] = '\0';
        return CCString::create(buf)->getCString();
    } else {
        return "";
    }
}

bool HFileUtils::pathExists(const char * path) {
    if (path[0] == '/') {
        return haypi::pathExists(path);
    }
//    if (m_pResourceExtendPath) {
//        std::string filename = m_pResourceExtendPath;
//        filename += path;
//        return haypi::pathExists(filename.c_str());
//    }
    std::string filename = path;
    const char *zipFile = m_pResourceZipFilePath;
    if (!zipFile) {
        zipFile = getResourceZipFilePathEx();
        filename.insert(0, "assets/"); //for android
    }
    if (zipFile) {
        return fileExistInZip(zipFile, filename.c_str());
    }
    return false;
}

int HFileUtils::createDir(const char * path) {
    return haypi::createDir(path);
}

void HFileUtils::setResourceExtendPath(const char *path) {
    CC_SAFE_FREE(m_pResourceExtendPath);
    if (path) {
        int len = strlen(path);
        if (len > 0) {
            m_pResourceExtendPath =  (char *)malloc(sizeof(char) * (len + 1));
            strcpy(m_pResourceExtendPath, path);
        }
    }
}


bool HFileUtils::currentInUI() {
    return m_gHFileUtils->getInUI();
}

void HFileUtils::resetInUI(bool inUI) {
    m_gHFileUtils->setInUI(inUI);
}
const char* HFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{    
    UpdateManager* mgr = UpdateManager::sharedInstance();
    if ( mgr->pathForName((char*)pszRelativePath) == "" )
        pszRelativePath = getResourceName(pszRelativePath);
    else
        pszRelativePath = getResourceName(mgr->pathForName((char*)pszRelativePath).c_str());
    
    if (!fileExist(pszRelativePath)) return CCFileUtils::fullPathFromRelativePath(pszRelativePath);
    return pszRelativePath;
}

unsigned char *HFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize) {
    return getFileData(pszFileName, pSize);
//    return CCFileUtils::getFileData(pszFileName, pszMode, pSize);
}

unsigned char* HFileUtils::getFileDataEx(const char* pszFileName, const char* pszMode, unsigned long * pSize) {
    return CCFileUtils::getFileData(pszFileName, pszMode, pSize);
}

const char *HFileUtils::getResourceName(const char *filename) {
    filename = validPath(filename);
    std::string strPath;
#if 1
    if (filename[0] == '/') {
        if (m_bIsRetina && (fileIsPng(filename) || fileIsPVR(filename) || fileIsJpeg(filename) || fileIsPlist(filename) || fileIsPlistb(filename))) {
            strPath = filename;
            int pos = strPath.rfind(".");
            if (0 != memcmp(strPath.c_str() + pos - 3, "_hd", 3)) {
                strPath.insert(pos, "_hd");
            }
            if (pathExists(strPath.c_str())) {
                return CCString::create(strPath)->getCString();
            }
        }
        return CCString::create(filename)->getCString();
    }
    
    if(m_oAttachedPaths.count() > 0) {
        std::vector<std::string> suffixs;
        strPath = "";
        bool isimage = false;
        bool imagehasPath = false;
        
        if (fileIsJS(filename)) {            
            if (!strstr(filename, "js/")) {
                strPath += "js/";
            }
            strPath += filename;            
        } else if (fileIsCCBI(filename)) {
            PHSCREENDATA pData = currentScreenData();
            
            if (!strstr(filename, "layout/")) {
                strPath += "layout/";
                strPath += pData->suffix;
                strPath += "/";
            }
            strPath += filename;
            
            int pos = strPath.rfind(".ccbi");
            int suffixLen = (int)strlen(pData->suffix);
            if (0 != memcmp(strPath.c_str() + pos - suffixLen, pData->suffix, suffixLen)) {
                std::string suffix = "_";
                suffix += pData->suffix;
                suffixs.push_back(suffix);
            }            
        } else if (fileIsImg(filename)) {
            if (!m_bIsRetina)
            {
                suffixs.push_back("_ld");
            }
            strPath += filename;
            isimage = true;
            if (strstr(filename, "/")) {
                imagehasPath = true;
            } 
        } else {            
            strPath += filename;
        }
        suffixs.push_back("");
        std::string str;
        for(int j=0;j<suffixs.size();j++)
            for (int i =0; i< m_oAttachedPaths.count();i++) {
                if (!isimage || imagehasPath) {
                    str = ((CCString *)m_oAttachedPaths.objectAtIndex(i))->getCString();
                    str =  str +  strPath;
                    std::string &suffix = suffixs[j];
                    if (suffix != "") {
                        int pos = str.rfind("/");
                        pos = (pos > 0) ? pos: 0;
                        pos = str.find('.', pos);
                        str.insert(pos, suffix.c_str());
                    }
                
                    if ((str.length() > 0) && (str.c_str()[0] == '/') && (haypi::pathExists(str.c_str())))
                    {
                        return CCString::create(str)->getCString();
                    }                
                } else {
                    const char *imagepath[2] = {"ui/", "game/"};
                    for(int k=0;k<2;k++)
                    {
                        str = ((CCString *)m_oAttachedPaths.objectAtIndex(i))->getCString();
                        str =  str + imagepath[k] + strPath;
                        std::string &suffix = suffixs[j];
                        if (suffix != "") {
                            int pos = str.rfind("/");
                            pos = (pos > 0) ? pos: 0;
                            pos = str.find('.', pos);
                            str.insert(pos, suffix.c_str());
                        }
                        
                        if ((str.length() > 0) && (str.c_str()[0] == '/') && (haypi::pathExists(str.c_str())))
                        {
                            return CCString::create(str)->getCString();
                        }
                    }
                }
            }
    }
    
    
    if (fileIsJS(filename)) {
        if (m_pResourceExtendPath) strPath = m_pResourceExtendPath;
        else strPath = "";
        if (!strstr(filename, "js/")) {
            strPath += "js/";
        }
        strPath += filename;
        if (pathExists(strPath.c_str())) {
            return CCString::create(strPath)->getCString();
        }
    } else if (fileIsCCBI(filename)) {
        PHSCREENDATA pData = currentScreenData();
        if (m_pResourceExtendPath) strPath = m_pResourceExtendPath;
        else strPath = "";
        if (!strstr(filename, "layout/")) {
            strPath += "layout/";
            strPath += pData->suffix;
            strPath += "/";
        }
        strPath += filename;
        if (pathExists(strPath.c_str())) {
            return CCString::create(strPath)->getCString();
        }
        int pos = strPath.rfind(".ccbi");
        int suffixLen = (int)strlen(pData->suffix);
        if (0 != memcmp(strPath.c_str() + pos - suffixLen, pData->suffix, suffixLen)) {
            strPath.insert(pos, "_");
            strPath.insert(pos + 1, pData->suffix);
        }
        if (pathExists(strPath.c_str())) {
            return CCString::create(strPath)->getCString();
        }
    } else if (fileIsPng(filename) || fileIsPVR(filename) || fileIsJpeg(filename) || fileIsPlist(filename) || fileIsPlistb(filename)) {
        if (m_pResourceExtendPath) strPath = m_pResourceExtendPath;
        else strPath = "";
        if (strstr(filename, "/")) {
            strPath += filename;
            if (m_bIsRetina) {
                int pos = fileIsPVR(filename) ? strPath.find(".pvr") : strPath.rfind(".");
                if (0 != memcmp(strPath.c_str() + pos - 3, "_hd", 3)) {
                    strPath.insert(pos, "_hd");
                }
                if (!pathExists(strPath.c_str())) {
                    if (m_pResourceExtendPath) strPath = m_pResourceExtendPath;
                    else strPath = "";
                    strPath += filename;
                }
            }
        } else {
            do {
                strPath += "game/";
                strPath += filename;
                if (m_bIsRetina) {
                    int pos = fileIsPVR(filename) ? strPath.find(".pvr") : strPath.rfind(".");
                    if (0 != memcmp(strPath.c_str() + pos - 3, "_hd", 3)) {
                        strPath.insert(pos, "_hd");
                    }
                    if (pathExists(strPath.c_str())) break;
                    strPath.replace(pos, 3, "");
                }
                if (pathExists(strPath.c_str())) break;
                if (m_pResourceExtendPath) strPath = m_pResourceExtendPath;
                else strPath = "";
                strPath += "ui/";
                strPath += filename;
                if (m_bIsRetina) {
                    int pos = fileIsPVR(filename) ? strPath.find(".pvr") : strPath.rfind(".");
                    if (0 != memcmp(strPath.c_str() + pos - 3, "_hd", 3)) {
                        strPath.insert(pos, "_hd");
                    }
                    if (!pathExists(strPath.c_str())) {
                        strPath.replace(pos, 3, "");
                    }
                }
            } while (0);
        }
    } else {
        if (m_pResourceExtendPath) strPath = m_pResourceExtendPath;
        else strPath = "";
        strPath += filename;
    }
    if (pathExists(strPath.c_str())) {
        return CCString::create(strPath)->getCString();
    }
    return HFileUtils::getInstance()->fullPathFromRelativePathEx(filename);
#else
    if (m_pResourceExtendPath) {
        strPath = m_pResourceExtendPath;
        strPath += filename;
        if (haypi::pathExists(strPath.c_str())) {
            strcpy(gpPath, strPath.c_str());
            return gpPath;
        }
    }
    
    if (fileIsCCBI(filename)) {
        if (strstr(filename, "/")) return filename;
        strPath = getUILayout(filename, NULL);
        strcpy(gpPath, strPath.c_str());
        return gpPath;
//        return CCString::create(strPath)->getCString();
    }
    
    if (strstr(filename, "/")) {
        strPath = filename;
        if (m_bIsRetina) {
            std::string filePath = strPath;
            int pos = filePath.rfind(".");
            if (pos > 0) {
                filePath.insert(pos, "_hd");
                if (pathExists(filePath.c_str())) {
                    strPath = filePath;
                }
            }
        }
    } else {
        do {
            strPath = "game/";
            strPath += filename;
            if (m_bIsRetina) {
                std::string filePath = strPath;
                int pos = filePath.rfind(".");
                if (pos > 0) {
                    filePath.insert(pos, "_hd");
                    if (pathExists(filePath.c_str())) {
                        strPath = filePath;
                        break;
                    }
                }
            }
            if (pathExists(strPath.c_str())){
                break;
            }
            
            strPath = "ui/";
            strPath += filename;
            if (m_bIsRetina) {
                std::string filePath = strPath;
                int pos = filePath.rfind(".");
                if (pos > 0) {
                    filePath.insert(pos, "_hd");
                    if (pathExists(filePath.c_str())) {
                        strPath = filePath;
                        break;
                    }
                }
            }
            if (pathExists(strPath.c_str())){
                break;
            }
            
            strPath = filename;
        } while (0);
    }
    
    strcpy(gpPath, strPath.c_str());
    return gpPath;
//    return CCString::create(strPath)->getCString();
#endif
}

unsigned char* HFileUtils::getFileDataFromFile(const char* pszFileName, unsigned long * pSize) {
    unsigned char * pBuffer = NULL;
    *pSize = 0;
    do {
        FILE *fp = fopen(pszFileName, "rb");
        CC_BREAK_IF(!fp);
        
        fseek(fp,0,SEEK_END);
        *pSize = ftell(fp);
        fseek(fp,0,SEEK_SET);
        pBuffer = new unsigned char[*pSize];
        *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
        fclose(fp);
    } while (0);
    
    return pBuffer;
}

unsigned char *HFileUtils::getFileData(const char* pszFileName, unsigned long * pSize) {

    const char *pFilename = getResourceName(pszFileName);

    unsigned long size = 0;
    unsigned char *data = NULL;
    if (!pathExists(pFilename) || fileInApp(pFilename)) {
        data = CCFileUtils::getFileData(pFilename, "rb", &size);
    } else {
        if (pFilename[0] == '/') {
            data = getFileDataEx(pFilename, "rb", &size);
        } else {
            if (m_pResourceExtendPath) {
                std::string filename = m_pResourceExtendPath;
                filename += pFilename;
                data = getFileDataFromFile(filename.c_str(), &size);
            } else {
                if (m_pResourceZipFilePath) {
                    data = getFileDataFromZip(m_pResourceZipFilePath, pFilename, &size);
                } else {
                    data = getFileDataEx(pFilename, "rb", &size);
                }
            }
        }
    }
    if (!data) return data;
    
    restoreData(data, size, pszFileName);
    
    if (pSize) *pSize = size;
    return data;
}

//unsigned char *HFileUtils::getFileDataEx(const char* pszFileName, unsigned long * pSize) {
//    const char *pFilename = pszFileName;
//    unsigned long size = 0;
//    unsigned char *data = NULL;
//    if (m_pResourceExtendPath) {
//        std::string filename = m_pResourceExtendPath;
//        filename += pFilename;
//        data = getFileDataFromFile(filename.c_str(), &size);
//    } else {
//        if (m_pResourceZipFilePath) {
//            data = getFileDataFromZip(m_pResourceZipFilePath, pFilename, &size);
//        } else {
//            data = getFileDataEx(pFilename, "rb", &size);
//        }
//    }
//    if (!data) return data;
//    
//    restoreData(data, size, pszFileName);
//    
//    if (pSize) *pSize = size;
//    return data;
//}

void HFileUtils::restoreBinaryData(unsigned char *data, unsigned long size, const char *ids, int idLen, int offset) {
    if (0 == memcmp(data, ids, idLen)) {
        return;
    }
    unsigned char *start = data + 4;
    unsigned char *end = data + size - 1;
    for (int i = offset; i < 16 + offset; ++i) {
        if (start >= end) break;
        *start = (*start) ^ data[i % 4];
        *end = (*end) ^ data[i % 4];
        ++start;
        --end;
    }
    memcpy(data, ids, idLen);
}

void HFileUtils::restoreTextData(unsigned char *data, unsigned long size, const char *ids, int idLen, int offset) {
    if (0 == memcmp(data, ids, idLen)) {
        return;
    }
    unsigned char *start = data + 4;
    unsigned char *end = data + size - 1;
    int i = offset;
    while (start < end) {
        *start = (*start) ^ data[i % 4];
        *end = (*end) ^ data[i % 4];
        ++start;
        --end;
        ++i;
    }
    memcpy(data, ids, idLen);
}

void HFileUtils::restoreDataContent(unsigned char *data, unsigned long size, const char *ids, int offset, const char *cmpID) {
    int len = (int)strlen(cmpID);
    if (0 == memcmp(data, cmpID, len)) {
        return;
    }
    unsigned char *start = data;
    unsigned char *end = data + size - 1;
    int i = offset;
    while (start < end) {
        *start = (*start) ^ ids[i % 4];
        *end = (*end) ^ ids[i % 4];
        ++start;
        --end;
        ++i;
    }
}

void HFileUtils::encodeDataContent(unsigned char *data, unsigned long size, const char *ids, int offset, const char *cmpID) {
    int len = (int)strlen(cmpID);
    if (0 != memcmp(data, cmpID, len)) {
        return;
    }
    unsigned char *start = data;
    unsigned char *end = data + size - 1;
    int i = offset;
    while (start < end) {
        *start = (*start) ^ ids[i % 4];
        *end = (*end) ^ ids[i % 4];
        ++start;
        --end;
        ++i;
    }
}

void HFileUtils::restoreData(unsigned char *data, unsigned long size, const char* pszFileName) {
    if (stringEndsWith(pszFileName, ".png")) {
        char ids[4] = {static_cast<char>(0x89), 0x50, 0x4e, 0x47};
        restoreBinaryData(data, size, ids, 4, 2);
    } else if (stringEndsWith(pszFileName, ".pvr") || stringEndsWith(pszFileName, "pvr.ccz")) {
        char ids[4] = {0x43, 0x43, 0x5A, 0x21};
        restoreBinaryData(data, size, ids, 4, 3);
    } else if (stringEndsWith(pszFileName, ".jpg") || stringEndsWith(pszFileName, ".jpeg")) {
        char ids[4] = {static_cast<char>(0xFF), static_cast<char>(0xD8), static_cast<char>(0xFF), static_cast<char>(0xE0)};
        restoreBinaryData(data, size, ids, 3, 1);
    } else if (stringEndsWith(pszFileName, ".plist")) {
        restoreTextData(data, size, "<?xm", 4, 1);
    } else if (stringEndsWith(pszFileName, ".strings")) {
        restoreTextData(data, size, "////", 4, 3);
    } else if (stringEndsWith(pszFileName, ".data")) {
        restoreDataContent(data, size, "c xj", 2, "{");
    } else if (stringEndsWith(pszFileName, ".mdat")) {
        restoreTextData(data, size, "mdat", 4, 2);
    }
}

void HFileUtils::encodeMapData(unsigned char *data, unsigned long size) {
    const char ids[4] = {'m', 'd', 'a', 't'};
    if (0 != memcmp(data, ids, 4)) {
        return;
    }
    srandom((unsigned int)time(NULL));
    while (1) {
        for (int j = 0; j < 4; ++j) {
            data[j] = (unsigned int)random() % 192 + 32;
        }
        if (0 != memcmp(data, ids, 4)) {
            break;
        }
    }
    unsigned char *start = data + 4;
    unsigned char *end = data + size - 1;
    int i = 2;
    while (start < end) {
        *start = (*start) ^ data[i % 4];
        *end = (*end) ^ data[i % 4];
        ++start;
        --end;
        ++i;
    }
}

const char *HFileUtils::fullPathFromRelativePathEx(const char *pszRelativePath) {
    return CCFileUtils::fullPathFromRelativePath(pszRelativePath);
}

const char *HFileUtils::GetFullPathFromRelativePath(const char *pszRelativePath) {
    return m_gHFileUtils->fullPathFromRelativePathEx(pszRelativePath);
}

CCDictionary *HFileUtils::dictionaryWithContentsOfFileThreadSafe(const char *pFileName) {
    return dictionaryFromPlist(pFileName);
}

CCArray *HFileUtils::arrayWithContentsOfFileThreadSafe(const char *pFileName) {
    return NULL; //implement later
}

std::string HFileUtils::getWriteablePath() {
    return m_strLocalPath;
}

std::string HFileUtils::getWriteablePathEx() {
    return CCFileUtils::getWriteablePath();
}

bool HFileUtils::fileExistInZip(const char* pszZipFilePath, const char* pszFileName) {
    bool bRet = false;
    unzFile pFile = NULL;
    do {
        CC_BREAK_IF(!pszZipFilePath || !pszFileName);
        CC_BREAK_IF(strlen(pszZipFilePath) == 0);
        
        pFile = unzOpen(pszZipFilePath);
        CC_BREAK_IF(!pFile);
        
        int nRet = unzLocateFile(pFile, pszFileName, 1);
        CC_BREAK_IF(UNZ_OK != nRet);
        
        char szFilePathA[260];
        unz_file_info FileInfo;
        nRet = unzGetCurrentFileInfo(pFile, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
        CC_BREAK_IF(UNZ_OK != nRet);
        bRet = true;
    } while (0);
    
    if (pFile) {
        unzClose(pFile);
    }
    
    return bRet;
}

bool HFileUtils::fileExist(const char* pszFileName) {
    const char *pFilename = getResourceName(pszFileName);
    return pathExists(pFilename);
    
//    FILE *f = NULL;
//    if ((f  = fopen(pszFileName, "rb"))){
//        fclose(f);
//        return true;
//    }
//    return false;
}

void HFileUtils::setLocalPath(const char *path) {
    if (path) {

            m_strLocalPath = path;

    } else {
        m_strLocalPath = HFileUtils::getInstance()->getWriteablePathEx();
    }

}

const char *HFileUtils::getLocalPath() {
    return m_strLocalPath.c_str();
}

void HFileUtils::saveFileToLocal(const char *data, int size, const char *filename) {
    std::string filepath = (strstr(filename, m_strLocalPath.c_str())) ? filename : (m_strLocalPath + filename);
    FILE *f = fopen(filepath.c_str(), "wb");
    if (f) {
        fwrite(data, 1, size, f);
        fclose(f);
    }
}

char *HFileUtils::loadFileFromLocal(int *size, const char *filename) {
    char *pRet = NULL;
    *size = 0;
    std::string filepath = (strstr(filename, m_strLocalPath.c_str())) ? filename : (m_strLocalPath + filename);
    FILE *f = fopen(filepath.c_str(), "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        *size = ftell(f);
        fseek(f, 0, SEEK_SET);
        if (*size > 0) {
            pRet = new char [*size + 1];
            *size = fread(pRet, 1, *size, f);
            pRet[*size] = '\0';
        }
        fclose(f);
    }
    return pRet;
}

void HFileUtils::saveToLocal(CCDictionary *pDict, const char *filename) {
    std::string content = dictionaryToJSON(pDict);
    if (content.length() > 0) {
        int len = content.length();
        char *data = new char[len + 1];
        memcpy(data, content.c_str(), len);
        data[len] = '\0';
        encodeDataContent((unsigned char *)data, len, "c xj", 2, "{");
        saveFileToLocal(data, len, filename);
//        HLOGI("save dictionary to file: %s", filename);
        delete [] data;
    }
}

CCDictionary *HFileUtils::loadFromLocal(const char *filename) {
    CCDictionary *pRet = NULL;
    std::string filepath = m_strLocalPath + "/" + filename;
//    HLOGI("load dictionary from file: %s", filepath.c_str());
    FILE *f = fopen(filepath.c_str(), "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long len = ftell(f);
        fseek(f, 0, SEEK_SET);
        if (len > 0) {
            char *data = new char [len + 1];
            len = fread(data, 1, len, f);
            data[len] = '\0';
            restoreDataContent((unsigned char *)data, len, "c xj", 2, "{");
            pRet = dictionaryFromJSON(data, len);
            delete [] data;
        }
        fclose(f);
    }
    return pRet;
}

CCDictionary *HFileUtils::loadFromResource(const char *filename) {
    CCDictionary *pRet = NULL;
    long len = 0;
    char *data = (char *)m_gHFileUtils->getFileData(filename, (unsigned long *)&len);
    if (data && (len > 0)) {
        pRet = dictionaryFromJSON(data, len);
        delete [] (unsigned char *)data;
    }
    return pRet;
}

//CCDictionary *HFileUtils::loadFromResourceEx(const char *filename) {
//    CCDictionary *pRet = NULL;
//    long len = 0;
//    char *data = (char *)m_gHFileUtils->getFileDataEx(filename, (unsigned long *)&len);
//    if (data && (len > 0)) {
//        pRet = dictionaryFromJSON(data, len);
//        delete [] (unsigned char *)data;
//    }
//    return pRet;
//}

HNAMESPACE_END
