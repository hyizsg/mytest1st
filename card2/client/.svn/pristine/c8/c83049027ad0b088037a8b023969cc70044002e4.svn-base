//
//  HPlistMgr.cpp
//  card
//
//  Created by zhou gang on 13-4-2.
//
//

#include "headers.h"

HSINGLETON_OBJECT_IMP(HPlistManager);

HPlistManager::HPlistManager()
{
    m_plist_cache = new CCDictionary();
}

HPlistManager::~HPlistManager()
{
    m_plist_cache->release();
}

void HPlistManager::addPlist(const char *plist)
{
    CCObject* obj = m_plist_cache->objectForKey(plist);
    if (obj != NULL) {
        obj->retain();
    }else{
        CC_PROFILER_START("HPlistManager::addPlist");
        obj = new CCObject;
        m_plist_cache->setObject(obj, plist);
        g_SourceCache->addSpriteFramesWithPList(plist);
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist);
        obj->release();
        CC_PROFILER_STOP("HPlistManager::addPlist");
//        CC_PROFILER_DISPLAY("HPlistManager::addPlist");
        CCLOG("HPlistManager: add plist ----- [%s]\ttotal: %d", plist, m_plist_cache->count());
        
        CCDictElement* ele = NULL;
        CCDICT_FOREACH(m_plist_cache, ele) {
            CCLOG("\t\tPlist: %s", ele->getStrKey());
        }
    }
}

void HPlistManager::removePlist(const char *plist)
{
    CCObject* obj = m_plist_cache->objectForKey(plist);
    if (obj != NULL) {
        if (obj->retainCount() > 1) {
            obj->release();
        }else{
            m_plist_cache->removeObjectForKey(plist);
            g_SourceCache->removeSpriteFramesWithPList(plist);
//            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plist);
            CCLOG("HPlistManager: remove plist ----- [%s]\tstay: %d", plist, m_plist_cache->count());
            CCDictElement* ele = NULL;
            CCDICT_FOREACH(m_plist_cache, ele) {
                CCLOG("\t\tPlist: %s", ele->getStrKey());
            }
        }
    }
}

CCSpriteFrame* HPlistManager::spriteFrameWithName(const char *fileName)
{
    return g_SourceCache->spriteFrameWithName(fileName);
//    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName);
}

HSINGLETON_OBJECT_IMP(HFontManager);

HFontManager::HFontManager()
{
    m_fontMap["BRITANIC.TTF"] = "Britannic Bold";
//    m_fontMap["simhei.ttf"] = "SimHei";
    m_fontMap["simhei.ttf"] = "Arial-BoldMT";
//    m_fontMap["STLITI.TTF"] = "Stliti";
    m_fontMap["STLITI.TTF"] = kIsTaiWanChinese ? "LiSu" : "Stliti";
    m_fontMap["FONTH___.TTF"] = "Fontdinerdotcom Huggable";
}

HFontManager::~HFontManager()
{
    m_fontMap.clear();
}

const char* HFontManager::getFontName(const char *ttfFile)
{
    string ttf = ttfFile;
    if (m_fontMap.find(ttf) != m_fontMap.end()) {
        return m_fontMap[ttf];
    }
    return ttfFile;
}

void HFontManager::replaceFont(cocos2d::CCNode *node)
{
    CCLabelTTF* label = dynamic_cast<CCLabelTTF*>(node);
    if (label != NULL) {
        label->setFontName(getFontName(label->getFontName()));
    }else{
        CCArray* children = node->getChildren();
        FOREACH(CCNode*, child, children) {
            replaceFont(child);
        }
    }
}
