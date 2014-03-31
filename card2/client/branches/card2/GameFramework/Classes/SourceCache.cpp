
#include "cocos2dxframework.h"
#include "Base.h"

HNAMESPACE_BEGIN

#define HPLISTNAMELENGTH  48
#define HPLISTBINTAG    0x01020304
typedef struct tagPlistHead {
    int tag;
    int count;
    int format;
    float w;
    float h;
    char textureFilename[HPLISTNAMELENGTH];
    tagPlistHead() { memset(this, 0, sizeof(*this)); tag = HPLISTBINTAG; }
} HPLISTHEAD;
typedef struct tagPlistContent {
    float x; //frame
    float y; //frame
    float w; //frame
    float h; //frame
    float ox; //offset x
    float oy; //offset y
    union {
        struct {
            int ow; //original w
            int oh; //original h
        } format0;
        struct {
            float sw; //source size
            float sh; //source size
            bool r; //rotate
        } format1or2;
        struct {
            float sw; //sprite size
            float sh; //sprite size
            float ssw; //sprite source size
            float ssh; //sprite source size
        } format3;
    };
    char name[HPLISTNAMELENGTH];
}HPLISTCONTENT;
typedef struct tagPlistData {
    HPLISTCONTENT content;
    tagPlistData *pNext;
    tagPlistData() { memset(this, 0, sizeof(*this)); }
} HPLISTDATA;
class HPlistParser {
public:
    HPlistParser(const char *filename) {
        m_strFilename = filename;
        m_strFilename += "b";
        
        string pszPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(m_strFilename.c_str());
        
        if (!haypi::pathExists(pszPath.c_str())) {
            m_strFilename = filename;
            pszPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(m_strFilename.c_str()).c_str();
        }
        m_nSize = 0;
        m_pData = CCFileUtils::sharedFileUtils()->getFileData(pszPath.c_str(), "rb", &m_nSize);
    }
    ~HPlistParser() {
        if (m_pData) delete [] m_pData;
    }
    bool isValid() { return (m_pData && m_nSize > 0); }
    bool isBinary() { return isValid() && (*(int *)m_pData == HPLISTBINTAG); }
    bool isXML() { return !isBinary(); }
    int count() {
        if (!isValid()) return 0;
        if (isBinary()) {
            return ((HPLISTHEAD *)m_pData)->count;
        } else {
            CCDictionary *dict = dictionaryFromPlist((char *)m_pData, m_nSize);
            if (!dict) return 0;
            CCDictionary *framesDict = (CCDictionary *)dict->objectForKey("frames");
            if (!framesDict) return 0;
            return framesDict->count();
        }
    }
    void saveToBinary() {
        HASSERT(isXML(), "data already is binary");
        m_strFilename += "b";
        CCDictionary *dict = toDictionary();
        if (!dict) return;
        HPLISTHEAD head;
        CCDictionary* metadataDict = (CCDictionary*)dict->objectForKey("metadata");
        strcpy(head.textureFilename, metadataDict->valueForKey("textureFileName")->getCString());
        int format = metadataDict->valueForKey("format")->intValue();
        head.format = format;
        HASSERT((head.format >= 0) && (head.format < 3), "(saveToBinary)plist format is not supported.");
        CCDictionary *framesDict = (CCDictionary *)dict->objectForKey("frames");
        HPLISTDATA *pFirst = NULL;
        HPLISTDATA *pCurrent = NULL;
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(framesDict, pElement) {
            HPLISTDATA *pData = new HPLISTDATA;
            head.count++;
            CCDictionary* frameDict = (CCDictionary*)pElement->getObject();
            std::string spriteFrameName = pElement->getStrKey();
            strcpy(pData->content.name, spriteFrameName.c_str());
            if (format == 0) {
                float x = frameDict->valueForKey("x")->floatValue();
                float y = frameDict->valueForKey("y")->floatValue();
                float w = frameDict->valueForKey("width")->floatValue();
                float h = frameDict->valueForKey("height")->floatValue();
                float ox = frameDict->valueForKey("offsetX")->floatValue();
                float oy = frameDict->valueForKey("offsetY")->floatValue();
                int ow = frameDict->valueForKey("originalWidth")->intValue();
                int oh = frameDict->valueForKey("originalHeight")->intValue();
                // check ow/oh
                if(!ow || !oh) {
                    HLOGW("cocos2d: WARNING: originalWidth/Height not found on the CCSpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
                }
                // abs ow/oh
                ow = abs(ow);
                oh = abs(oh);
                // create frame
                pData->content.x = x;
                pData->content.y = y;
                pData->content.w = w;
                pData->content.h = h;
                pData->content.ox = ox;
                pData->content.oy = oy;
                pData->content.format0.ow = ow;
                pData->content.format0.oh = oh;
//                spriteFrame->initWithTexture(pTexture,
//                                             CCRectMake(x, y, w, h),
//                                             false,
//                                             CCPointMake(ox, oy),
//                                             CCSizeMake((float)ow, (float)oh)
//                                             );
            } else if(format == 1 || format == 2) {
                CCRect frame = CCRectFromString(frameDict->valueForKey("frame")->getCString());
                bool rotated = false;
                // rotation
                if (format == 2) rotated = frameDict->valueForKey("rotated")->boolValue();
                
                CCPoint offset = CCPointFromString(frameDict->valueForKey("offset")->getCString());
                CCSize sourceSize = CCSizeFromString(frameDict->valueForKey("sourceSize")->getCString());
                
                // create frame
                pData->content.x = frame.origin.x;
                pData->content.y = frame.origin.y;
                pData->content.w = frame.size.width;
                pData->content.h = frame.size.height;
                pData->content.ox = offset.x;
                pData->content.oy = offset.y;
                pData->content.format1or2.sw = sourceSize.width;
                pData->content.format1or2.sh = sourceSize.height;
//                spriteFrame->initWithTexture(pTexture,
//                                             frame,
//                                             rotated,
//                                             offset,
//                                             sourceSize
//                                             );
            }
            if (!pFirst) {
                pFirst = pData;
                pCurrent = pData;
            } else {
                pCurrent->pNext = pData;
                pCurrent = pData;
            }
        }
        FILE *f = fopen(m_strFilename.c_str(), "wb");
        if (f) {
            fwrite(&head, sizeof(HPLISTHEAD), 1, f);
            HPLISTDATA *pData = pFirst;
            while (pData) {
                fwrite(&pData->content, sizeof(HPLISTCONTENT), 1, f);
                pCurrent = pData->pNext;
                delete pData;
                pData = pCurrent;
            }
            fclose(f);
        }
    }
    CCDictionary *toDictionary() {
        if (isXML()) return dictionaryFromPlist((char *)m_pData, m_nSize);
        if (isBinary()) {
            HPLISTHEAD *pHead = (HPLISTHEAD *)m_pData;
            CCDictionary *dict = CCDictionary::create();
            
            CCDictionary *metadataDict = CCDictionary::create();
            dict->setObject(metadataDict, "metadata");
            metadataDict->setObject(HString::create(pHead->textureFilename), "textureFileName");
            metadataDict->setObject(HString::createWithInteger(pHead->format), "format");
            
            CCDictionary *framesDict = CCDictionary::create();
            dict->setObject(framesDict, "frames");            
            HPLISTCONTENT *pContent = (HPLISTCONTENT *)(m_pData + sizeof(HPLISTHEAD));
            for (int i = 0; i < pHead->count; ++i) {
                CCDictionary *frame = CCDictionary::create();
                framesDict->setObject(frame, pContent->name);
                frame->setObject(HString::createWithInteger(0), "0");
                ++pContent;
            }
            return dict;
        }
        return NULL;
    }
    void addSpriteFrames(HPListInfo *info, bool bNoTexture, bool bIgnoreTexture, FuncOnPercent onPercent) {
        if (isBinary()) {
            parseBinary(info, bNoTexture, bIgnoreTexture, onPercent);
        } else {
            parseDictionary(info, bNoTexture, bIgnoreTexture, onPercent);
        }
    }
    void removeSpriteFrames(CCDictionary *pSpriteFrames) {
        
    }
    void loadTexture() {
        if (isBinary()) {
            loadTextureForBinary();
        } else {
            loadTextureForDictionary();
        }
    }
    void releaseTexture() {
        if (isBinary()) {
            releaseTextureForBinary();
        } else {
            releaseTextureForDictionary();
        }
    }
private:
    std::string m_strFilename;
    unsigned long m_nSize;
    unsigned char *m_pData;
    CCDictionary *m_pDict;
    void parseBinary(HPListInfo *info, bool bNoTexture, bool bIgnoreTexture, FuncOnPercent onPercent) {
        HASSERT(isBinary(), "data is  not binary");
        HPLISTHEAD *pHead = (HPLISTHEAD *)m_pData;
        
        std::string texturePath(pHead->textureFilename);
        if ( texturePath.empty()) {
            texturePath = m_strFilename;
            size_t startPos = texturePath.find_last_of(".");
            texturePath = texturePath.erase(startPos);
            texturePath = texturePath.append(".png");
        } else {
            // delete by zg
//            if (texturePath.find("/") == std::string::npos) {
//                const char *path = CCFileUtils::sharedFileUtils()->fullPathForFilename(m_strFilename.c_str()).c_str();
//                std::string str = path;
//                str += texturePath;
//                texturePath = str;
//            }
            
            texturePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(texturePath.c_str(), m_strFilename.c_str());
        }
        
        info->setTextureFile(CCString::create(texturePath));
        
        CCTexture2D *pTexture = NULL;
//        if (!bNoTexture && !bIgnoreTexture) pTexture = (CCTexture2D *)HTimerManager::getInstance()->processOnMainThread(HInvocation::create(HSourceCache::getInstance(), hinvocation_selector(HSourceCache::createTexture), 0, info->getTextureFile()), true);
        
        if (!bNoTexture && !bIgnoreTexture) {
            pTexture = (CCTexture2D*)HSourceCache::getInstance()->createTexture(0, info->getTextureFile());
        }
        
        CCArray *pSpriteFrames = CCArray::createWithCapacity(pHead->count+1);
        info->setSpriteFrames(pSpriteFrames);
        
        float totalCount = pHead->count;
        int step = pHead->count / 20;
        int stepAdder = 0;
        if (onPercent) onPercent(0);
        HPLISTCONTENT *pContent = (HPLISTCONTENT *)(m_pData + sizeof(HPLISTHEAD));
        for (int i = 0; i < pHead->count; ++i) {
            HSpriteFrame* spriteFrame = NULL;
            if (pTexture) {
                spriteFrame = HSpriteFrame::create(/*autoReleaseTexture*/);
            } else {
                spriteFrame = HSpriteFrame::create(pContent->name/*, autoReleaseTexture*/);
            }
            if (pHead->format == 0) {
                spriteFrame->initWithTexture(pTexture,
                                             CCRectMake(pContent->x, pContent->y, pContent->w, pContent->h),
                                             false,
                                             CCPointMake(pContent->ox, pContent->oy),
                                             CCSizeMake((float)pContent->format0.ow, (float)pContent->format0.oh)
                                             );
            } else if(pHead->format == 1 || pHead->format == 2) {
                spriteFrame->initWithTexture(pTexture,
                                             CCRectMake(pContent->x, pContent->y, pContent->w, pContent->h),
                                             pContent->format1or2.r,
                                             CCPointMake(pContent->ox, pContent->oy),
                                             CCSizeMake(pContent->format1or2.sw, pContent->format1or2.sh)
                                             );
            } else {
                HASSERT(0, "(parseBinary)plist format is not supported.");
            }
            // add sprite frame
            spriteFrame->setClickRect(CCRectMake(0, 0, spriteFrame->getRect().size.width, spriteFrame->getRect().size.height));
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spriteFrame, pContent->name);
            pSpriteFrames->addObject(spriteFrame);
            if (!pTexture && !bIgnoreTexture) {
                CCRect rect = spriteFrame->getRect();
                rect.origin = CCPointZero;
                spriteFrame->setRect(rect);
            }
            
            ++pContent;
            if (onPercent) {
                ++stepAdder;
                if (stepAdder >= step) {
                    onPercent(i / totalCount);
                    stepAdder = 0;
                    HThread::sleepWithMilliSeconds(1);
                }
            }
        }
        if (onPercent) {
            onPercent(1.0f);
            HThread::sleepWithMilliSeconds(1);
        }
    }
    void parseDictionary(HPListInfo *info, bool bNoTexture, bool bIgnoreTexture, FuncOnPercent onPercent) {
        HASSERT(isXML(), "data is  not binary");
        CCDictionary *dict = dictionaryFromPlist((char *)m_pData, m_nSize);
        if (!dict) return;
        
        std::string texturePath("");
        CCDictionary* metadataDict = (CCDictionary*)dict->objectForKey("metadata");
        if (metadataDict) {
            texturePath = metadataDict->valueForKey("textureFileName")->getCString();
        }
        if ( texturePath.empty()) {
            texturePath = m_strFilename;
            size_t startPos = texturePath.find_last_of(".");
            texturePath = texturePath.erase(startPos);
            texturePath = texturePath.append(".png");
        } else {
            //modify by zg
//            if (texturePath.find("/") == std::string::npos) {
//                const char *path = HFileUtils::getFilepath(m_strFilename.c_str());
//                std::string str = path;
//                str += texturePath;
//                texturePath = str;
//            }
            
            texturePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(texturePath.c_str(), m_strFilename.c_str());
        }
        
        info->setTextureFile(CCString::create(texturePath));
        
        CCTexture2D *pTexture = NULL;
        if (!bNoTexture && !bIgnoreTexture) pTexture = (CCTexture2D *)HTimerManager::getInstance()->processOnMainThread(HInvocation::create(HSourceCache::getInstance(), hinvocation_selector(HSourceCache::createTexture), 0, info->getTextureFile()), true);
        
        CCDictionary *framesDict = (CCDictionary *)dict->objectForKey("frames");
        int format = 0;
        
        // get the format
        if(metadataDict) format = metadataDict->valueForKey("format")->intValue();
        
        // check the format
        CCAssert(format >=0 && format <= 2, "format is not supported for CCSpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");
        
        CCArray *pSpriteFrames = CCArray::createWithCapacity(framesDict->count()+1);
        info->setSpriteFrames(pSpriteFrames);
        
        float totalCount = framesDict->count();
        int step = framesDict->count() / 20;
        int stepAdder = 0;
        if (onPercent) onPercent(0);
        int index = 0;
        
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(framesDict, pElement) {
            CCDictionary* frameDict = (CCDictionary*)pElement->getObject();
            std::string spriteFrameName = pElement->getStrKey();
            HSpriteFrame* spriteFrame = dynamic_cast<HSpriteFrame *>(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName.c_str()));
            if (spriteFrame) continue;
            
            if (pTexture) {
                spriteFrame = HSpriteFrame::create(/*autoReleaseTexture*/);
            } else {
                spriteFrame = HSpriteFrame::create(spriteFrameName.c_str()/*, autoReleaseTexture*/);
            }
            if(format == 0) {
                float x = frameDict->valueForKey("x")->floatValue();
                float y = frameDict->valueForKey("y")->floatValue();
                float w = frameDict->valueForKey("width")->floatValue();
                float h = frameDict->valueForKey("height")->floatValue();
                float ox = frameDict->valueForKey("offsetX")->floatValue();
                float oy = frameDict->valueForKey("offsetY")->floatValue();
                int ow = frameDict->valueForKey("originalWidth")->intValue();
                int oh = frameDict->valueForKey("originalHeight")->intValue();
                // check ow/oh
                if(!ow || !oh) {
                    HLOGW("cocos2d: WARNING: originalWidth/Height not found on the CCSpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
                }
                // abs ow/oh
                ow = abs(ow);
                oh = abs(oh);
                // create frame
                spriteFrame->initWithTexture(pTexture,
                                             CCRectMake(x, y, w, h),
                                             false,
                                             CCPointMake(ox, oy),
                                             CCSizeMake((float)ow, (float)oh)
                                             );
            } else if(format == 1 || format == 2) {
                CCRect frame = CCRectFromString(frameDict->valueForKey("frame")->getCString());
                bool rotated = false;
                
                // rotation
                if (format == 2) rotated = frameDict->valueForKey("rotated")->boolValue();
                
                CCPoint offset = CCPointFromString(frameDict->valueForKey("offset")->getCString());
                CCSize sourceSize = CCSizeFromString(frameDict->valueForKey("sourceSize")->getCString());
                
                // create frame
                spriteFrame->initWithTexture(pTexture,
                                             frame,
                                             rotated,
                                             offset,
                                             sourceSize
                                             );
            } else if (format == 3) {
                // get values
                CCSize spriteSize = CCSizeFromString(frameDict->valueForKey("spriteSize")->getCString());
                CCPoint spriteOffset = CCPointFromString(frameDict->valueForKey("spriteOffset")->getCString());
                CCSize spriteSourceSize = CCSizeFromString(frameDict->valueForKey("spriteSourceSize")->getCString());
                CCRect textureRect = CCRectFromString(frameDict->valueForKey("textureRect")->getCString());
                bool textureRotated = frameDict->valueForKey("textureRotated")->boolValue();
                
                // get aliases
                //         CCArray* aliases = (CCArray*) (frameDict->objectForKey("aliases"));
                //         CCString * frameKey = new CCString(spriteFrameName);
                
                //         CCObject* pObj = NULL;
                //         CCARRAY_FOREACH(aliases, pObj)
                //          {
                //             std::string oneAlias = ((CCString*)pObj)->getCString();
                //             if (m_pSpriteFramesAliases->objectForKey(oneAlias.c_str())) {
                //                 HLOGW("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
                //              }
                //             m_pSpriteFramesAliases->setObject(frameKey, oneAlias.c_str());
                //         }
                //         frameKey->release();
                // create frame
                spriteFrame->initWithTexture(pTexture,
                                             CCRectMake(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
                                             textureRotated,
                                             spriteOffset,
                                             spriteSourceSize);
            }
            
            // add sprite frame
            spriteFrame->setClickRect(CCRectMake(0, 0, spriteFrame->getRect().size.width, spriteFrame->getRect().size.height));
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spriteFrame, spriteFrameName.c_str());
            pSpriteFrames->addObject(spriteFrame);
            if (!pTexture && !bIgnoreTexture) {
                CCRect rect = spriteFrame->getRect();
                rect.origin = CCPointZero;
                spriteFrame->setRect(rect);
            }
            
            ++index;
            
            if (onPercent) {
                ++stepAdder;
                if (stepAdder >= step) {
                    onPercent(index / totalCount);
                    stepAdder = 0;
                    HThread::sleepWithMilliSeconds(1);
                }
            }
        }
        if (onPercent) {
            onPercent(1.0f);
            HThread::sleepWithMilliSeconds(1);
        }
    }
    void loadTextureForBinary() {
        HASSERT(isBinary(), "data is not binary");
        HPLISTHEAD *pHead = (HPLISTHEAD *)m_pData;
        
        std::string texturePath(pHead->textureFilename);
        if ( texturePath.empty()) {
            texturePath = m_strFilename;
            size_t startPos = texturePath.find_last_of(".");
            texturePath = texturePath.erase(startPos);
            texturePath = texturePath.append(".png");
        } else {
            
            //delete by zg
//            if (texturePath.find("/") == std::string::npos) {
//                const char *path = HFileUtils::getFilepath(m_strFilename.c_str());
//                std::string str = path;
//                str += texturePath;
//                texturePath = str;
//            }
            
            texturePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(texturePath.c_str(), m_strFilename.c_str());
            
        }
        CCTexture2D *pTexture = (CCTexture2D *)HTimerManager::getInstance()->processOnMainThread(HInvocation::create(HSourceCache::getInstance(), hinvocation_selector(HSourceCache::createTexture), 0, CCString::create(texturePath)), true);
        
        HPLISTCONTENT *pContent = (HPLISTCONTENT *)(m_pData + sizeof(HPLISTHEAD));
        for (int i = 0; i < pHead->count; ++i) {
            HSpriteFrame* spriteFrame = dynamic_cast<HSpriteFrame *>(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pContent->name));
            if (spriteFrame) spriteFrame->setTexture(pTexture);            
            ++pContent;
        }
    }
    
    void releaseTextureForBinary() {
        HASSERT(isBinary(), "data is not binary");
        HPLISTHEAD *pHead = (HPLISTHEAD *)m_pData;
        
        std::string texturePath(pHead->textureFilename);
        if ( texturePath.empty()) {
            texturePath = m_strFilename;
            size_t startPos = texturePath.find_last_of(".");
            texturePath = texturePath.erase(startPos);
            texturePath = texturePath.append(".png");
        } else {
            
            //delete by zg
//            if (texturePath.find("/") == std::string::npos) {
//                const char *path = HFileUtils::getFilepath(m_strFilename.c_str());
//                std::string str = path;
//                str += texturePath;
//                texturePath = str;
//            }
            
            
            texturePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(texturePath.c_str(), m_strFilename.c_str());
        }
//        CCTexture2D *pTexture = (CCTexture2D *)HTimerManager::getInstance()->processOnMainThread(HInvocation::create(HSourceCache::getInstance(), hinvocation_selector(HSourceCache::createTexture), 0, CCString::create(texturePath)), true);
//        CCTextureCache::sharedTextureCache()->removeTexture(pTexture);
        CCTextureCache::sharedTextureCache()->removeTextureForKey(texturePath.c_str());
        
        HPLISTCONTENT *pContent = (HPLISTCONTENT *)(m_pData + sizeof(HPLISTHEAD));
        for (int i = 0; i < pHead->count; ++i) {
            HSpriteFrame* spriteFrame = dynamic_cast<HSpriteFrame *>(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pContent->name));
            if (spriteFrame) spriteFrame->setTexture(NULL);
            ++pContent;
        }
    }
    void loadTextureForDictionary() {
        HASSERT(isXML(), "data is  not binary");
        CCDictionary *dict = dictionaryFromPlist((char *)m_pData, m_nSize);
        if (!dict) return;
        
        std::string texturePath("");
        CCDictionary* metadataDict = (CCDictionary*)dict->objectForKey("metadata");
        if (metadataDict) {
            texturePath = metadataDict->valueForKey("textureFileName")->getCString();
        }
        if ( texturePath.empty()) {
            texturePath = m_strFilename;
            size_t startPos = texturePath.find_last_of(".");
            texturePath = texturePath.erase(startPos);
            texturePath = texturePath.append(".png");
        } else {
            //delete by zg
//            if (texturePath.find("/") == std::string::npos) {
//                const char *path = HFileUtils::getFilepath(m_strFilename.c_str());
//                std::string str = path;
//                str += texturePath;
//                texturePath = str;
//            }
//            
            
            texturePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(texturePath.c_str(), m_strFilename.c_str());
        }
        CCTexture2D *pTexture = (CCTexture2D *)HTimerManager::getInstance()->processOnMainThread(HInvocation::create(HSourceCache::getInstance(), hinvocation_selector(HSourceCache::createTexture), 0, CCString::create(texturePath)), true);
        
        CCDictionary *framesDict = (CCDictionary *)dict->objectForKey("frames");        
        
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(framesDict, pElement) {
            std::string spriteFrameName = pElement->getStrKey();
            HSpriteFrame* spriteFrame = dynamic_cast<HSpriteFrame *>(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName.c_str()));
            if (spriteFrame) spriteFrame->setTexture(pTexture); 
        }
    }
    
    void releaseTextureForDictionary() {
        HASSERT(isXML(), "data is  not binary");
        CCDictionary *dict = dictionaryFromPlist((char *)m_pData, m_nSize);
        if (!dict) return;
        
        std::string texturePath("");
        CCDictionary* metadataDict = (CCDictionary*)dict->objectForKey("metadata");
        if (metadataDict) {
            texturePath = metadataDict->valueForKey("textureFileName")->getCString();
        }
        if ( texturePath.empty()) {
            texturePath = m_strFilename;
            size_t startPos = texturePath.find_last_of(".");
            texturePath = texturePath.erase(startPos);
            texturePath = texturePath.append(".png");
        } else {
            
            //delete by zg
//            if (texturePath.find("/") == std::string::npos) {
//                const char *path = HFileUtils::getFilepath(m_strFilename.c_str());
//                std::string str = path;
//                str += texturePath;
//                texturePath = str;
//            }
            
            
            texturePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(texturePath.c_str(), m_strFilename.c_str());
        }
//        CCTexture2D *pTexture = (CCTexture2D *)HTimerManager::getInstance()->processOnMainThread(HInvocation::create(HSourceCache::getInstance(), hinvocation_selector(HSourceCache::createTexture), 0, CCString::create(texturePath)), true);
//        CCTextureCache::sharedTextureCache()->removeTexture(pTexture);
        CCTextureCache::sharedTextureCache()->removeTextureForKey(texturePath.c_str());
        
        CCDictionary *framesDict = (CCDictionary *)dict->objectForKey("frames");
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(framesDict, pElement) {
            std::string spriteFrameName = pElement->getStrKey();
            HSpriteFrame* spriteFrame = dynamic_cast<HSpriteFrame *>(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName.c_str()));
            if (spriteFrame) spriteFrame->setTexture(NULL);
        }
    }
};

HSINGLETON_OBJECT_IMP(HSourceCache);

HSourceCache::HSourceCache(): m_pTimer(NULL), m_bAntiAliasTexture(true), m_bUsePVR(false) {
    m_pAutoManagedSpriteFrames = new CCArray();
    m_pPlists = new CCDictionary();
}

HSourceCache::~HSourceCache() {
    disableAutoreleaseTextures();
    delete m_pPlists;
    delete m_pAutoManagedSpriteFrames;
}

void HSourceCache::convertScaleToNode(float &scaleX, float &scaleY, CCNode *node, CCNode *toNode) {
    scaleX = 1.0f;
    scaleY = 1.0f;
    do {
        scaleX *= node->getScaleX();
        scaleY *= node->getScaleY();
        node = node->getParent();
    } while (node && (node != toNode));
}

const char *HSourceCache::image2pvr(const char *filename) {
    if (m_bUsePVR) {
        // delete by zg
//        if (HFileUtils::fileIsPng(filename) || HFileUtils::fileIsJpeg(filename)) {
//            char path[256];
//            strcpy(path, filename);
//            char *pos = strrchr(path, '.');
//            if (pos) {
//                strcpy(pos, ".pvr.ccz");
//                return CCString::create(path)->getCString();
//            }
//        }
    }
    return filename;
}

CCObject *HSourceCache::createTexture(int command, CCObject *param) {
    CCString *pFilename = dynamic_cast<CCString *>(param);
    if (pFilename) {
        CCTexture2D *pTexture = textureWithFile(pFilename->getCString());
        return pTexture;
    }
    return NULL;
}

CCTexture2D *HSourceCache::textureWithFile(const char *fileName) {
    CCTexture2D *pRet = CCTextureCache::sharedTextureCache()->addImage(image2pvr(fileName));
    if (!pRet && m_bUsePVR) pRet = CCTextureCache::sharedTextureCache()->addImage(fileName);
    if (pRet) {
        if (m_bAntiAliasTexture) {
            pRet->setAntiAliasTexParameters();
        } else {
            pRet->setAliasTexParameters();
        }
    }
    return pRet;
}

void HSourceCache::removeTexture(const char *filename) {
    CCTextureCache::sharedTextureCache()->removeTextureForKey(image2pvr(filename));
}

CCSprite *HSourceCache::spriteWithFile(const char *fileName) {
    CCTexture2D *texture = textureWithFile(fileName);
    if (!texture) return NULL;
    return CCSprite::createWithTexture(texture);
}

CCTexture2D *HSourceCache::textureForKey(const char *key) {
    return CCTextureCache::sharedTextureCache()->textureForKey(image2pvr(key));
}

HSpriteFrame *HSourceCache::spriteFrameWithFilename(const char *filename) {
    HSpriteFrame *pRet = dynamic_cast<HSpriteFrame *>(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename));
    if (!pRet) {
        CCTexture2D *pTexture = textureWithFile(filename);
        if (pTexture) {
            pRet = HSpriteFrame::create();
            pRet->initWithTexture(pTexture,
                                  CCRectMake(0, 0, pTexture->getContentSizeInPixels().width, pTexture->getContentSizeInPixels().height),
                                  false,
                                  CCPointZero,
                                  pTexture->getContentSizeInPixels()
                                  );
//            m_pSpriteFrames->setObject(pRet, filename);
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(pRet, filename);
        }
    }
    return pRet;
}

HSpriteFrame *HSourceCache::spriteFrameWithName(const char *name) {
    return dynamic_cast<HSpriteFrame *>(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
}

CCSprite *HSourceCache::spriteWithFrameName(const char *frameName) {
    HSpriteFrame *spriteFrame = spriteFrameWithName(frameName);
    if (spriteFrame) return CCSprite::createWithSpriteFrame(spriteFrame);
    return NULL;
}

CCRect HSourceCache::clickRectForSpriteFrame(HSpriteFrame *spriteFrame, bool flipX, bool flipY) {
    CCPoint relativeOffsetInPixels = spriteFrame->getOffsetInPixels();
	
    if (flipX)
        relativeOffsetInPixels.x = -relativeOffsetInPixels.x;
    if (flipY)
        relativeOffsetInPixels.y = -relativeOffsetInPixels.y;
    
    CCSize contentSize = spriteFrame->getOriginalSizeInPixels();
    CCSize sourceSize = spriteFrame->getRectInPixels().size;
	
	float x = relativeOffsetInPixels.x + (contentSize.width - sourceSize.width) / 2;
	float y = relativeOffsetInPixels.y + (contentSize.height - sourceSize.height) / 2;
    
    return CCRectMake(x, y, sourceSize.width, sourceSize.height);
}

CCRect HSourceCache::clickRectWithName(const char *frameName, bool flipX, bool flipY) {
    HSpriteFrame *frame = spriteFrameWithName(frameName);
    if (frame) {
        return clickRectForSpriteFrame(frame,  flipX, flipY);
    }
    return CCRectZero;
}

CCSpriteFrame *HSourceCache::spriteFrameAndClickRectWithSpriteFrameName(const char *frameName, CCRect &clickRect,  bool flipX, bool flipY) {
    HSpriteFrame *spriteFrame = spriteFrameWithName(frameName);
    if (!spriteFrame) return NULL;
    clickRect = clickRectForSpriteFrame(spriteFrame, flipX, flipY);
    return spriteFrame;
}

CCSprite *HSourceCache::spriteAndClickRectWithSpriteFrameName(const char *frameName, CCRect &clickRect,  bool flipX, bool flipY) {
    HSpriteFrame *spriteFrame = spriteFrameWithName(frameName);
    if (!spriteFrame) return NULL;
    clickRect = clickRectForSpriteFrame(spriteFrame, flipX, flipY);
    return CCSprite::createWithSpriteFrame(spriteFrame);
}

void HSourceCache::clear() {
    disableAutoreleaseTextures();
//    m_pSpriteFrames->removeAllObjects();
    m_pPlists->removeAllObjects();
    m_pAutoManagedSpriteFrames->removeAllObjects();
}

void HSourceCache::addSpriteFramesWithPList(const char *plist, FuncOnPercent onPercent, bool bNoTexture, bool bIgnoreTexture)
{
    if (m_pPlists->objectForKey(plist)) return;
    
    if (!bNoTexture) bIgnoreTexture = false;
    
 
    
    HPListInfo *info = HPListInfo::create();
    m_pPlists->setObject(info, plist);
    
    HPlistParser parser(plist);
    parser.addSpriteFrames(info, bNoTexture, bIgnoreTexture, onPercent);
    
//    if (!parser.isBinary()) parser.saveToBinary();
    

    
}

void HSourceCache::removeSpriteFramesWithPList(const char *plist) {
    HPListInfo *info = (HPListInfo *)m_pPlists->objectForKey(plist);
    if (info) {
        CCTexture2D *pTexture = info->getTexture();
        if (pTexture) {
            CCTextureCache::sharedTextureCache()->removeTextureForKey(info->getTextureFile()->getCString());
            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromTexture(pTexture);
        }
        m_pPlists->removeObjectForKey(plist);
    }
}

void HSourceCache::loadTextureWithPList(const char *plist) {
    HPListInfo *info = (HPListInfo *)m_pPlists->objectForKey(plist);
    if (info) {
        CCTexture2D *pTexture = info->getTexture();
        if (!pTexture) {
            pTexture = (CCTexture2D *)HTimerManager::getInstance()->processOnMainThread(HInvocation::create(HSourceCache::getInstance(), hinvocation_selector(HSourceCache::createTexture), 0, info->getTextureFile()), true);
            HASSERT(pTexture != NULL, "loadTextureWithPList, texture does not exist.");
            CCArray *array = info->getSpriteFrames();
            for (int i = array->count() - 1; i >= 0; --i) {
                HSpriteFrame *spriteFrame = (HSpriteFrame *)array->objectAtIndex(i);
                spriteFrame->setTexture(pTexture);
            }
        }
    }
}

void HSourceCache::releaseTextureWithPList(const char *plist) {
    HPListInfo *info = (HPListInfo *)m_pPlists->objectForKey(plist);
    if (info) {
        CCTexture2D *pTexture = info->getTexture();
        if (pTexture) {
            CCTextureCache::sharedTextureCache()->removeTextureForKey(info->getTextureFile()->getCString());
            CCArray *array = info->getSpriteFrames();
            for (int i = array->count() - 1; i >= 0; --i) {
                HSpriteFrame *spriteFrame = (HSpriteFrame *)array->objectAtIndex(i);
                spriteFrame->setTexture(NULL);
            }
        }
    }
}

void HSourceCache::addToAutoManager(HSpriteFrame *spriteFrame) {
    if (!m_pAutoManagedSpriteFrames->containsObject(spriteFrame)) {
        m_pAutoManagedSpriteFrames->addObject(spriteFrame);
    }
}

void HSourceCache::forceReleaseTextures() {
    for (int i = m_pAutoManagedSpriteFrames->count() - 1; i >= 0; --i) {
        HSpriteFrame *spriteFrame = (HSpriteFrame *)m_pAutoManagedSpriteFrames->objectAtIndex(i);
        CCTexture2D *texture = spriteFrame->getTexture();
        if (texture && (texture->retainCount() == 2) && (spriteFrame->retainCount() == 3)) {
            spriteFrame->setTextureAutoRelease(false);
            CCTextureCache::sharedTextureCache()->removeTexture(texture);
            spriteFrame->setTexture(NULL);
            m_pAutoManagedSpriteFrames->removeObjectAtIndex(i);
        }
    }
}

void HSourceCache::enableAutoreleaseTextures(float interval) {
    if (!m_pTimer) {
        m_pTimer = new HTimer();
        m_pTimer->setAlwaysCount(true);
        m_pTimer->registerTimer(this, 0, interval, 0);
        HTimerManager::getInstance()->registerTimer(m_pTimer);
    }
}

void HSourceCache::disableAutoreleaseTextures() {
    if (m_pTimer) {
        HTimerManager::getInstance()->unregisterTimer(m_pTimer);
        m_pTimer->release();
        m_pTimer = NULL;
    }
}

void HSourceCache::onTimeOut(int gid, int count) {
    for (int i = m_pAutoManagedSpriteFrames->count() - 1; i >= 0; --i) {
        HSpriteFrame *spriteFrame = (HSpriteFrame *)m_pAutoManagedSpriteFrames->objectAtIndex(i);
        CCTexture2D *texture = spriteFrame->getTexture();
        if (texture && (texture->retainCount() == 2) && (spriteFrame->retainCount() == 3)) {
            if (spriteFrame->getTextureAutoRelease()) {
                spriteFrame->setTextureAutoRelease(false);
            } else {
                CCTextureCache::sharedTextureCache()->removeTexture(texture);
                spriteFrame->setTexture(NULL);
                m_pAutoManagedSpriteFrames->removeObjectAtIndex(i);
            }
        }
    }
//    CCDictElement* pElement = NULL;
//    CCDICT_FOREACH(m_pSpriteFrames, pElement) {
//        HSpriteFrame *spriteFrame = (HSpriteFrame *)pElement->getObject();
//        CCTexture2D *texture = spriteFrame->getTexture();
//        if (texture && (texture->retainCount() == 2) && (spriteFrame->retainCount() == 2)) {
//            CCTextureCache::sharedTextureCache()->removeTexture(texture);
//            spriteFrame->setTexture(NULL);
//        }
//    }
}


//HShaderCache
HSINGLETON_OBJECT_IMP(HShaderCache);

HShaderCache::HShaderCache(){
    m_pPrograms = new CCDictionary();
}

HShaderCache::~HShaderCache() {
    delete m_pPrograms;
}

CCGLProgram *HShaderCache::getProgram(const char *key) {
    HProgramData *data = (HProgramData *)m_pPrograms->objectForKey(key);
    if (data) return data->getProgram();
    return NULL;
}

void HShaderCache::addProgram(const char *key, const char *vert, const char *frag, int shaderType) {
    HProgramData *data = (HProgramData *)m_pPrograms->objectForKey(key);
    if (!data) {
        data = HProgramData::create(vert, frag, shaderType);
        m_pPrograms->setObject(data, key);
    }
}

void HShaderCache::removeProgram(const char *key) {
    m_pPrograms->removeObjectForKey(key);
}

void HShaderCache::removeAllPRograms() {
    m_pPrograms->removeAllObjects();
}

void HShaderCache::reloadAllPrograms(CCObject *) {
    asyncReloadAllPrograms(0, NULL);
//    HTimerManager::getInstance()->asyncProcess(HInvocation::create(this, hinvocation_selector(HShaderCache::asyncReloadAllPrograms), 0, NULL, 0.5f));
}

CCObject *HShaderCache::asyncReloadAllPrograms(int, CCObject *) {
    CCLOG("HShaderCache::asyncReloadAllPrograms");
    CCArray *array = m_pPrograms->allKeys();
    for (int i = m_pPrograms->count() - 1; i >= 0; --i) {
        HProgramData *data = (HProgramData *)m_pPrograms->objectForKey(((CCString *)array->objectAtIndex(i))->getCString());
        data->reloadProgram();
    }
    HLOGI("HProgramCache::reloadAllPrograms");
    return NULL;
}

void HShaderCache::HProgramData::reloadProgram() {
    CCGLProgram *pProgram = getProgram();
    if (pProgram) {
        pProgram->reset();
    } else {
        pProgram = new CCGLProgram();
    }
    pProgram->initWithVertexShaderByteArray(getVertex()->getCString(), getFragment()->getCString());
    
    if (getShaderType() | HSHADERTYPE_POSITION) {
        pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    }
    if (getShaderType() | HSHADERTYPE_TEXTURE) {
        pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    }
    if (getShaderType() | HSHADERTYPE_COLOR) {
        pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    }
    
    pProgram->link();    
    pProgram->updateUniforms();
    
    if (!getProgram()) {
        setProgram(pProgram);
        pProgram->release();
    }
}

HNAMESPACE_END
