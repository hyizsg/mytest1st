//
//  HFileUtils.cpp
//  GameFramework
//
//  Created by zhou gang on 13-9-25.
//  Copyright (c) 2013年 cxj. All rights reserved.
//

#include "cocos2dxframework.h"
#include "HFileUtils.h"
#include "UpdateManager.h"
#include "GameScene.h"
#include "AppDelegate.h"

void HFileUtils::initUserFileUtils()
{
    if (s_sharedFileUtils) {
        purgeFileUtils();
    }
    
    HFileUtils* temp = new HFileUtils;
    temp->init();
    
    s_sharedFileUtils = temp;
    
}

std::string HFileUtils::fullPathForFilename(const char* pszFileName)
{
    CCAssert(pszFileName != NULL, "HFileUtils: Invalid path");
    
    // add by zg,
    if (strcmp("cc_2x2_white_image", pszFileName) == 0) {
        return pszFileName;
    }
    
    std::string strFileName = pszFileName;
    if (isAbsolutePath(pszFileName))
    {
        //CCLOG("Return absolute path( %s ) directly.", pszFileName);
        return pszFileName;
    }
    
    // Already Cached ?
    std::map<std::string, std::string>::iterator cacheIter = m_fullPathCache.find(pszFileName);
    if (cacheIter != m_fullPathCache.end())
    {
        //CCLOG("Return full path from cache: %s", cacheIter->second.c_str());
        return cacheIter->second;
    }
    
    haypi::UpdateManager* mgr = haypi::UpdateManager::sharedInstance();
    const char* newFileName = mgr->pathForName((char*)pszFileName).c_str();
    std::string fullPath = "";
    
    if (strlen(newFileName) == 0) {
        fullPath = getResourceNameInApp(pszFileName);
    }else{
        fullPath = getResourceNameInDoc(newFileName);
    }

    if (isAbsolutePath(fullPath.c_str())) {
        m_fullPathCache[pszFileName] = fullPath;
    }
    
    return fullPath;
}

std::string HFileUtils::getResourceNameInApp(const char *pszFileName)
{
    std::string newFileName = pszFileName;
    std::string fullPath = pszFileName;
    std::string fileExt = getExtension(pszFileName);
    std::string fileName = getFileNameWithoutExtension(pszFileName);
    
    bool bSeached = false;
    bool bRetina = AppDelegate::getInstance()->getRetinaScreen();
    
    static string imageSeachPath[] = {"", "game/", "ui/", "ui2/"};
    static const int imageSeachPathCount = sizeof(imageSeachPath)/sizeof(string);
    
    /*static*/ string imageSeachSuffix[] = {""}; //{ bRetina ? "" : "_ld", ""};
    /*static*/ const int imageSeachSuffixCount = sizeof(imageSeachSuffix)/sizeof(string) - bRetina;
    
    static string imageSeachExt[] = {"", ".pvr.ccz"};
    static const int imageSeachExtCount = sizeof(imageSeachExt)/sizeof(string);
    
    
    /*if (fileExt == ".plist") {
        newFileName = string(pszFileName) + "b";
    }else */
        
    if (fileExt == ".ccbi") {
        if (strstr(pszFileName, "_iphone")) {
            newFileName = std::string("layout/iphone/") + pszFileName;
        }else{
            newFileName = std::string("layout/iphone/") + fileName + "_iphone" + fileExt;
        }
    }else if(fileExtIsPlist(fileExt.c_str())){
        
        string newExt = fileExt;
        
        if (newExt == ".plist") {
            newExt = ".plistb";
        }
        
        bool bFileWithPath = strchr(pszFileName, '/') != NULL;
        int nSeachPathIdx = 0;
        
        do {
            for (int i=0; i<imageSeachSuffixCount; i++) {
                // 组合新字串
                if (fileEndWith(fileName.c_str(), imageSeachSuffix[i].c_str())) {
                    newFileName = imageSeachPath[nSeachPathIdx] + fileName + newExt;
                }else{
                    newFileName = imageSeachPath[nSeachPathIdx] + fileName + imageSeachSuffix[i] + newExt;
                }
                
                fullPath = super::fullPathForFilename(newFileName.c_str());
                if (isAbsolutePath(fullPath)) {
                    bSeached = true;
                    break;
                }
            }
            
        } while (!bSeached && !bFileWithPath && ++nSeachPathIdx < imageSeachPathCount);
        
        if (!bSeached) {
            newFileName = pszFileName;
        }
        
    }else if(fileExtIsImage(fileExt.c_str())){
        
        bool bFileWithPath = strchr(pszFileName, '/') != NULL;
        int nSeachPathIdx = 0;
        
        do {
            for (int i=0; i<imageSeachSuffixCount; i++) {
                for (int j=0; j<imageSeachExtCount; j++) {
                    // 转换后缀名
                    string newExt = imageSeachExt[j] == "" ? fileExt : imageSeachExt[j];
                    
                    // 组合新字串
                    if (fileEndWith(fileName.c_str(), imageSeachSuffix[i].c_str())) {
                        newFileName = imageSeachPath[nSeachPathIdx] + fileName + newExt;
                    }else{
                        newFileName = imageSeachPath[nSeachPathIdx] + fileName + imageSeachSuffix[i] + newExt;
                    }
                    
                    fullPath = super::fullPathForFilename(newFileName.c_str());
                    if (isAbsolutePath(fullPath)) {
                        bSeached = true;
                        break;
                    }
                    
                    if (j<imageSeachExtCount-1 && imageSeachExt[j+1]==newExt) {
                        j++;
                    }
                }
                
                if (bSeached) {
                    break;
                }
            }
            
        } while (!bSeached && !bFileWithPath && ++nSeachPathIdx < imageSeachPathCount);
        
        if (!bSeached) {
            newFileName = pszFileName;
        }
        
    }
    
    if (!bSeached) {
        fullPath = super::fullPathForFilename(newFileName.c_str());
    }
    
    CCLOG("HFileUtils::getResourceNameInApp: %s ---> %s", pszFileName, fullPath.c_str());
    
    return fullPath;
}


std::string HFileUtils::getResourceNameInDoc(const char* pszFileName)
{
    return super::fullPathForFilename(pszFileName);
}


std::string HFileUtils::getExtension(const char* path)
{
    const char* pos = strrchr(path, '/');
    const char* pExt = strchr(pos ? pos : path, '.');
    return pExt ? pExt : "";
}

std::string HFileUtils::getFileName(const char* path)
{
    const char* pos = strrchr(path, '/');
    return pos ? pos + 1 : path;
}

std::string HFileUtils::getFileNameWithoutExtension(const char *path)
{
    const char* pos = strrchr(path, '/');
    const char* pExt = strchr(pos ? pos : path, '.');
    if (pExt)
    {
        std::string fileName = path;
        return fileName.substr(0, pExt - path);
    }
    
    return path;
}

bool HFileUtils::fileExtIsImage(const char* pExt)
{
    std::string lowExt = pExt;
    
    return (lowExt == ".pvr.ccz") ||
    (lowExt == ".pkm") ||
    (lowExt == ".mask") ||
    (lowExt == ".jpg") ||
    (lowExt == ".png") ||
    (lowExt == ".jpeg") ||
    (lowExt == ".pvr")
    ;
}

bool HFileUtils::fileExtIsPlist(const char* pExt)
{
    std::string lowExt = pExt;
    return (lowExt == ".plist") ||  (lowExt == ".plistb");
}

bool HFileUtils::fileEndWith(const char* path, const char* ends)
{
    bool bRet = true;
    for (int i=strlen(path)-1, j=strlen(ends)-1; i>=0 && j>=0; i--, j--) {
        if (path[i] != ends[j]) {
            bRet = false;
            break;
        }
    }
    
    return bRet;
}

