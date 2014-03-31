//
//  HFileUtils.h
//  GameFramework
//
//  Created by zhou gang on 13-9-25.
//  Copyright (c) 2013年 cxj. All rights reserved.
//

#ifndef __GameFramework__HFileUtils__
#define __GameFramework__HFileUtils__

// iphone
#if defined(CC_TARGET_OS_IPHONE)
#undef HCLS
#define HCLS(class)  class##IOS
#endif

// android
#if defined(ANDROID)
#undef HCLS
#define HCLS(class)  class##Android
#endif



#if defined(CC_TARGET_OS_IPHONE)
#include "CCFileUtilsIOS.h"
#elif defined(ANDROID)
#include "CCFileUtilsAndroid.h"
#endif

USING_NS_CC;


class HFileUtils : public HCLS(CCFileUtils) {
    typedef HCLS(CCFileUtils) super;
    
    
protected:
    HFileUtils(): super() {};
    
public:
    virtual ~HFileUtils(){};
    static void initUserFileUtils();
    
    virtual std::string fullPathForFilename(const char* pszFileName);
    std::string getResourceNameInApp(const char* filename);
    std::string getResourceNameInDoc(const char* filename);
    
    std::string getExtension(const char* path);
    std::string getFileName(const char* path);
    std::string getFileNameWithoutExtension(const char* path);
    
    bool fileEndWith(const char* path, const char* ends);
    bool fileExtIsImage(const char* pExt);
    bool fileExtIsPlist(const char* pExt);
};


#endif /* defined(__GameFramework__HFileUtils__) */
