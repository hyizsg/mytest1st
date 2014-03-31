//
//  HThreadSprite.cpp
//  card
//
//  Created by zhou gang on 13-5-16.
//
//


#include "../../headers.h"
#include "support/zip_support/ZipUtils.h"

#define toKey(id) ((int)id)
#define DEFAULT_CARD    "1007"

#if 0
#undef CCLOG
#define CCLOG(format, ... ) do{}while(0)
#endif


HLock lock_cache;

#define smart_lock(lock) for (HSmartLock smlock_##lock(&lock), *pSmLock_##lock = &smlock_##lock; pSmLock_##lock; pSmLock_##lock = NULL)
#define smart_lock2(lock1, lock2) for (HSmartLock smlock_##lock1(&lock1), smlock_##lock2(&lock2), *pSmLock_##lock1 = &smlock_##lock1; pSmLock_##lock1; pSmLock_##lock1 = NULL)


HSINGLETON_OBJECT_IMP(HThreadTextureCache);

HThreadData::HThreadData()
: target(NULL)
, texture(NULL)
, filename(NULL)
, setting(NULL)
{
    
}

HThreadData::~HThreadData()
{
    CC_SAFE_RELEASE_NULL(target);
    CC_SAFE_RELEASE_NULL(texture);
    CC_SAFE_RELEASE_NULL(filename);
    CC_SAFE_RELEASE_NULL(setting);
}

HCachePair::HCachePair()
: m_first(NULL)
, m_second(NULL)
{
    
}

HCachePair::~HCachePair()
{
    CC_SAFE_RELEASE_NULL(m_first);
    CC_SAFE_RELEASE_NULL(m_second);
}

HCachePair* HCachePair::create(cocos2d::CCObject *first, cocos2d::CCObject *second)
{
    HCachePair* pair = new HCachePair;
    CC_AUTO_RELEASE(pair);
    
    HC_SET(pair->m_first, first);
    HC_SET(pair->m_second, second);
    
    return pair;
}

HThreadTextureCache::HThreadTextureCache()
{
    cache = new CCArray;
    loaded  = new CCDictionary;
    loadedName = new CCDictionary;
    m_isAutoRelease = true;
}

HThreadTextureCache::~HThreadTextureCache()
{
    CC_SAFE_RELEASE_NULL(cache);
    CC_SAFE_RELEASE_NULL(loaded);
    CC_SAFE_RELEASE_NULL(loadedName);
}

void HThreadTextureCache::start()
{
    HThread::createThreadAutoRelease(this, hthread_selector(HThreadTextureCache::onThreadLoadTexture), -1);
}

CCTexture2D* HThreadTextureCache::textureWithName(const char* fileName)
{
    std::string fileKey = path2key(fileName);
    smart_lock(lock_cache){
         return (CCTexture2D*)loaded->objectForKey(fileKey);
    }
    
    return NULL;
}

void HThreadTextureCache::loadTexture(CCSprite* sprite, const char* fileName)
{
    HSettingFun* func = new HRichSprite::settingtexture();
    loadTexture(sprite, fileName, func);
}

void HThreadTextureCache::loadTexture(CCObject* target, const char* fileName, HSettingFun* setting)
{
    std::string fileKey = path2key(fileName);
    
    smart_lock(lock_cache)
    {
//        if (nameMap.find(fileKey) != nameMap.end()) {
//            fileKey = nameMap[fileKey];
//        }
        if (loaded->objectForKey(fileKey) != NULL) {
            (*setting)(target, loaded->objectForKey(fileKey));
            setting->release();
            return;
        }
        
        (*setting)(target, NULL);
    }
    
    HThreadData* data = new HThreadData;
    data->setTarget(target);
    CCString *str = new CCString(fileName);
    data->setFileName(str);
    str->release();
    data->setSettingFun(setting);
    setting->release();
    
    smart_lock(lock_cache)
    {
        cache->addObject(data);
        data->release();
    }
}

//void HThreadTextureCache::loadTexture(HThreadData* data)
//{
//    std::string fileKey = path2key(data->getFileName()->getCString());
//    
//    if (nameMap.find(fileKey) != nameMap.end()) {
//        fileKey = nameMap[fileKey];
//    }
//    
//    smart_lock(lock_cache)
//    {
//        if (loaded->objectForKey(fileKey) != NULL) {
//            data->setTexture((CCTexture2D*)loaded->objectForKey(fileKey));
//            HTimerManager::getInstance()->processOnMainThread(HInvocation::create(this, hinvocation_selector(HThreadTextureCache::onMainThreadSetting), 0, data), true);
//        }else{
//            (*data->getSettingFun())(data->getTarget(), NULL);
//            cache->setObject(data, toKey(data->getTarget()));
//        }
//    }
//}

void HThreadTextureCache::removeTexture(CCTexture2D* object)
{
    if (object == NULL)
        return;
    
    if (m_isAutoRelease) {
        CCString* name = (CCString*)loadedName->objectForKey(toKey(object));
        if ((name != NULL) && (object->retainCount() == 2)) {
//            CCLOG("ThreadCache: removeTexture\t%s. \tstay: %d", name->getCString(), loaded->count()-1);
            loaded->removeObjectForKey(name->getCString());
            loadedName->removeObjectForKey(toKey(object));
        }
    }
}

void HThreadTextureCache::lockTexture()
{
    lock_cache.lock();
}

void HThreadTextureCache::unlockTexture()
{
    lock_cache.unlock();
}

double HThreadTextureCache::getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000.0;
}

void HThreadTextureCache::onThreadLoadTexture(HThread *)
{
    try {
        
        HThreadData* data = NULL;
        
        smart_lock(lock_cache){
            if (cache->count() > 0) {
                data = (HThreadData*)cache->objectAtIndex(0);;
                data->retain();
                cache->removeObjectAtIndex(0);
            }
        }
        
        do {
            if (data == NULL) {
                HThread::sleepWithMilliSeconds(100);
                break;
            }
            
            double t = getCurrentTime();
            for (int i=0; i<sizeof(clock); i+=sizeof(double)) {
                ((double*)(&clock))[i/sizeof(double)] = t;
            }
            
            std::string keyfile = path2key(data->getFileName()->getCString());
            CCTexture2D* texture = NULL;
            
            smart_lock(lock_cache)
            {
                texture = (CCTexture2D*)loaded->objectForKey(keyfile);
                data->setTexture(texture);                
            }            
            
            if (texture) {               
                // 进入主线程，设置图片
                HTimerManager::getInstance()->processOnMainThread(HInvocation::create(this, hinvocation_selector(HThreadTextureCache::onMainThreadSetting), 0, data), true);
                break;
            }
            
            // 从文件加载图片
            const char* path = data->getFileName()->getCString();
            std::string fullpath = fullPathFromRelativePath(path);
            
            CCImage::EImageFormat fmt = computeImageFormatType(fullpath);
            if (fmt == CCImage::kFmtRawData) {
                texture = this->addPVRImage(fullpath.c_str(), data);
            }else{
                texture = this->addImage(fullpath.c_str(), fmt, data);
            }
            
            if (texture == NULL) {
//                CCString* defaultIcon = new CCString(getDefaultIcon(data->getFileName()->getCString()));
//                CCLOG("Faid: #777 - to Load Thread Texture: [%s]->[%s]", data->getFileName()->getCString(), defaultIcon->getCString());
//                
//                if (!data->getFileName()->isEqual(defaultIcon)) {
//                    data->setFileName(defaultIcon);
//                    smart_lock(lock_task) {
//                        keyfile = nameMap[keyfile] = path2key(data->getFileName()->getCString());
//                        loadTexture(data);
//                    }
//                }
//                
//                defaultIcon->release();
                break;
            }
            
            
            
            smart_lock(lock_cache)
            {
                CCString* strKey = new CCString(keyfile);
                loaded->setObject(texture, keyfile);
                loadedName->setObject(strKey, toKey(texture));
                strKey->release();
                
                clock.end = getCurrentTime();
#if 0
                CCLOG("ThreadCache: loadTexture\t%s.\ttotal: %d", keyfile.c_str(), loaded->count());
                CCLOG("%20s:\t%8.3fms", "load_file_data", clock.load_file_data-clock.begin);
                CCLOG("%20s:\t%8.3fms", "create_tmp_image", clock.create_tmp_image-clock.load_file_data);
                CCLOG("%20s:\t%8.3fms", "wait_main_thread", clock.wait_main_thread-clock.create_tmp_image);
                CCLOG("%20s:\t%8.3fms", "create_texture", clock.create_texture-clock.wait_main_thread);
                CCLOG("%20s:\t%8.3fms", "setting_texture", clock.setting_texture-clock.create_texture);
                CCLOG("%20s:\t%8.3fms", "end", clock.end-clock.begin);
                
                dumpCachedTextureInfo(keyfile.c_str(), texture);
#endif
            }
            
        } while (0);
        smart_lock(lock_cache)
        {
            CC_SAFE_RELEASE(data);
        }
        
    } catch (...) {
        CCLOG("HThreadTextureCache onThreadLoadTexture 2: ");
    }
}


CCObject* HThreadTextureCache::onMainThreadSetting(int command, cocos2d::CCObject *obj)
{
    
    HThreadData* data = (HThreadData*)obj;
    
    smart_lock(lock_cache)
    {
        // imageView又换新图了，跳出
        bool rechange = false;
        if (data->getTarget() != NULL) {
            FOREACH(HThreadData*, tmp, cache){
                if (tmp->getTarget() == data->getTarget()) {
                    rechange = true;
                    break;
                }
            }
        }
        
        if (!rechange) {
             (*data->getSettingFun())(data->getTarget(), data->getTexture());
        }
    }

    clock.setting_texture = getCurrentTime();
    
    return NULL;
}

CCTexture2D * HThreadTextureCache::addPVRImage(const char* path, HThreadData* tData)
{
    CCTexturePVR* pvr = new CCTexturePVR;
    
    unsigned char* pvrdata = NULL;
    int pvrlen = 0;
    
    std::string lowerCase(path);
    for (unsigned int i = 0; i < lowerCase.length(); ++i)
    {
        lowerCase[i] = tolower(lowerCase[i]);
    }
    
    if (lowerCase.find(".ccz") != std::string::npos)
    {
        pvrlen = ZipUtils::ccInflateCCZFile(path, &pvrdata);
    }
    else if (lowerCase.find(".gz") != std::string::npos)
    {
        pvrlen = ZipUtils::ccInflateGZipFile(path, &pvrdata);
    }
    else
    {
        pvrdata = CCFileUtils::sharedFileUtils()->getFileData(path, "rb", (unsigned long *)(&pvrlen));
    }
    
    if (pvrlen <= 0)
    {
        pvr->release();
        return NULL;
    }
    
    clock.load_file_data = getCurrentTime();
    
    CCTexture2D* texture = NULL;
    
    if (! (pvr->unpackPVRv2Data(pvrdata, pvrlen)  || pvr->unpackPVRv3Data(pvrdata, pvrlen)) )
    {
        CC_SAFE_DELETE_ARRAY(pvrdata);
        pvr->release();
        return NULL;
    }else{
        
        clock.create_tmp_image = getCurrentTime();
        
        CCArray* array = new CCArray(2);
        array->addObject(pvr);
        array->addObject(tData);
        
        HTimerManager::getInstance()->processOnMainThread(HInvocation::create(this, hinvocation_selector(HThreadTextureCache::onMainThreadPVRCreateGLTexture), 0, array), true);
        
        texture = tData->getTexture();
        
        array->release();
    }
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // cache the texture file name
    VolatileTexture::addImageTexture(texture, path, CCImage::kFmtRawData);
#endif
    
    CC_SAFE_DELETE_ARRAY(pvrdata);
    pvr->release();
    
    return texture;
    
}

CCObject* HThreadTextureCache::onMainThreadPVRCreateGLTexture(int command, CCObject* data)
{
    clock.wait_main_thread = getCurrentTime();
    
    CCArray* array = (CCArray*)data;
    CCTexturePVR* pvr = dynamic_cast<CCTexturePVR*>(array->objectAtIndex(0));
    HThreadData* tData = dynamic_cast<HThreadData*>(array->objectAtIndex(1));
    
    pvr->createGLTexture();
    
    HTexture2D* tex = new HTexture2D;
    tex->initWithPVR(pvr);
    
    clock.create_texture = getCurrentTime();

    tData->setTexture(tex);
    onMainThreadSetting(0, tData);
    
    tex->release();
    
    return NULL;
}

void HThreadTextureCache::dumpCachedTextureInfo(const char* key, CCTexture2D* tex)
{
    unsigned int bpp = tex->bitsPerPixelForFormat();
    // Each texture takes up width * height * bytesPerPixel bytes.
    unsigned int bytes = tex->getPixelsWide() * tex->getPixelsHigh() * bpp / 8;
    CCLOG("TextureCache: \"%s\" rc=%lu id=%lu %lu x %lu @ %ld bpp => %lu KB",
          key,
          (long)tex->retainCount(),
          (long)tex->getName(),
          (long)tex->getPixelsWide(),
          (long)tex->getPixelsHigh(),
          (long)bpp,
          (long)bytes / 1024);
}

CCImage::EImageFormat HThreadTextureCache::computeImageFormatType(string& filename)
{
    CCImage::EImageFormat ret = CCImage::kFmtUnKnown;
    
    if ((std::string::npos != filename.find(".jpg")) || (std::string::npos != filename.find(".jpeg")) ||
        (std::string::npos != filename.find(".JPG")) || (std::string::npos != filename.find(".JPEG")))
    {
        ret = CCImage::kFmtJpg;
    }
    else if ((std::string::npos != filename.find(".png")) || (std::string::npos != filename.find(".PNG")))
    {
        ret = CCImage::kFmtPng;
    }
    else if ((std::string::npos != filename.find(".tiff")) || (std::string::npos != filename.find(".TIFF")))
    {
        ret = CCImage::kFmtTiff;
    }else if((std::string::npos != filename.find(".pvr")) || (std::string::npos != filename.find(".PVR")))
    {
        ret = CCImage::kFmtRawData;
    }
    
    return ret;
}

void HThreadTextureCache::removeUnusedTexture()
{
    smart_lock(lock_cache)
    {
        CCArray* keys = loaded->allKeys();
        if (keys == NULL || keys->count() == 0) {
            CCLOG("UserBag: removeUnusedTexture \t\tno cache");
            return;
        }
        
        CCLOG("UserBag: removeUnusedTexture \t\tcout:%d", loaded->count());
        for (int i=0; i<keys->count(); i++) {
            std::string strkey = ((CCString*)keys->objectAtIndex(i))->getCString();
            CCTexture2D* text = (CCTexture2D*)loaded->objectForKey(strkey);
            if (text->retainCount() == 1) {
//                CCLOG("\trelease image %s", strkey.c_str());
                loaded->removeObjectForKey(strkey);
            }else{
//                CCLOG("\tkeep image %s,\t%d", strkey.c_str(), text->retainCount());
            }
        }
        
        CCLOG("UserBag: remove %d success. still keep %d", keys->count() - loaded->count(), loaded->count());
    }
}


CCTexture2D * HThreadTextureCache::addImage(const char * path)
{
    CCAssert(path != NULL, "TextureCache: fileimage MUST not be NULL");
    
    CCTexture2D * texture = NULL;

    std::string pathKey = path2key(path);
    
    smart_lock(lock_cache){
        texture = (CCTexture2D*)loaded->objectForKey(pathKey.c_str());
    }
    
    if( ! texture )
    {
        texture = CCTextureCache::sharedTextureCache()->addImage(path);
        if (texture) {
            smart_lock(lock_cache){
                loaded->setObject(texture, pathKey);
            }
        }
        
        CCLOG("TextureCache::addImage: %s", path);
        CCTextureCache::sharedTextureCache()->removeTextureForKey(path);
    }
    
    return texture;
    
}

bool HTexture2D::initWithPVR(cocos2d::CCTexturePVR *pvr)
{
    pvr->setRetainName(true); // don't dealloc texture on release
    
    m_uName = pvr->getName();
    m_fMaxS = 1.0f;
    m_fMaxT = 1.0f;
    m_uPixelsWide = pvr->getWidth();
    m_uPixelsHigh = pvr->getHeight();
    m_tContentSize = CCSizeMake((float)m_uPixelsWide, (float)m_uPixelsHigh);
    m_bHasPremultipliedAlpha =  false; // PVRHaveAlphaPremultiplied_;
    m_ePixelFormat = pvr->getFormat();
    m_bHasMipmaps = pvr->getNumberOfMipmaps() > 1;
    
    return true;
}
