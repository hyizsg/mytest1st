//
//  HThreadSprite.h
//  card
//
//  Created by zhou gang on 13-5-16.
//
//

#ifndef __card__HThreadSprite__
#define __card__HThreadSprite__

struct HSettingFun : public CCObject {
    virtual void operator() (CCObject* target, CCObject* tex) {};
    HCREATE_FUNC(HSettingFun);
};

struct HThreadData : public CCObject {
    CC_SYNTHESIZE_RETAIN(CCObject*, target, Target);
    CC_SYNTHESIZE_RETAIN(CCTexture2D*, texture, Texture);
    CC_SYNTHESIZE_RETAIN(CCString*, filename, FileName);
    CC_SYNTHESIZE_RETAIN(HSettingFun*, setting, SettingFun);
    
    HThreadData();
    virtual ~HThreadData();
};

struct HTextureData : public CCObject {
    CC_SYNTHESIZE(void *, buff, Buff);
    CC_SYNTHESIZE(unsigned long, size, Size);
    CC_SYNTHESIZE(CCImage::EImageFormat, format, Format);
    CC_SYNTHESIZE(HThreadData*, tdata, ThreadData);
};

struct HCachePair : public CCObject {
    
    CCObject* first() { return m_first; };
    CCObject* second() { return m_second; };
    
    HCachePair();
    virtual ~HCachePair();
    static HCachePair* create(CCObject* first, CCObject* second);
    
    __retain CCObject* m_first;
    __retain CCObject* m_second;
};

struct HClockData {
    double begin;
    double load_file_data;
    double create_tmp_image;
    double wait_main_thread;
    double create_texture;
    double setting_texture;
    double end;
};

class HThreadTextureCache : public CCObject {    
    HSINGLETON_OBJECT(HThreadTextureCache);
    
public:

    void start();
    
    void removeTexture(CCTexture2D* pTex);
    void removeUnusedTexture();
    
    CCDictionary* shareTextureChace() { return loaded; }
    
    CC_SYNTHESIZE_BOOL(bool, m_isAutoRelease, AutoRelease);
    
    // 同步加载部分
public:
    CCTexture2D* textureWithName(const char* name);
    CCTexture2D* addImage(const char * path);
    
    // 异步加载部分
public:
    void loadTexture(CCSprite*, const char* fileName);
    void loadTexture(CCObject* target, const char* fileName, HSettingFun* setting);
    void loadTexture(HThreadData* data);
    
    CCTexture2D* addImage(const char* path, CCImage::EImageFormat fmt, HThreadData* tData);
    CCTexture2D* addPVRImage(const char* path, HThreadData* tData);
    
    void lockTexture();
    void unlockTexture();
    
protected:
    // 线程循环
    void onThreadLoadTexture(HThread *);
    
    // Main Thread Call
    CCObject* onMainThreadCreateTexture(int command, CCObject* data);
    CCObject* onMainThreadPVRCreateGLTexture(int command, CCObject* data);
    CCObject* onMainThreadSetting(int command, CCObject* data);
        
    
protected:
    
    // help function
    static CCImage::EImageFormat computeImageFormatType(string& filename);
    static void dumpCachedTextureInfo(const char* key, CCTexture2D* tex);
    static double getCurrentTime();
    
    // @autoreleasepool
    static string fullPathFromRelativePath(const char *pszRelativePath);
    
protected:
    CCArray* cache;
    
    CCDictionary* loaded;
    CCDictionary* loadedName; // for auto release cache
    
//    map<string, string> nameMap;
    HClockData clock;
    
};

class HTexture2D : public CCTexture2D {
    
    
public:
    bool initWithPVR(CCTexturePVR* pvr);
    
};


#endif /* defined(__card__HThreadSprite__) */
