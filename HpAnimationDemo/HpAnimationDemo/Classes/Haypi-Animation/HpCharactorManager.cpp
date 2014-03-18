//
//  HpCharactorManager.cpp
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-4.
//
//

#include "HpCharactorManager.h"
#include "cocos-ext.h"
#include "HpCharaInstLoader.h"
#include "HpShaderCache.h"

USING_NS_CC_EXT;

NS_HPAM_BEGIN

static HpCharactorManager* s_charator_manager = NULL;

class HpSpriteFrameCache : public CCSpriteFrameCache{};

HpCharactorManager::HpCharactorManager()
{
    m_charactors = new CCDictionary;
    m_xml_parser = new HpCharactorXmlParser;
    m_chr_parser = new HpCharactorBinParser;
    m_builder = new HpAnimBuildVisitor;
    m_render = new HpAnimRenderVisitor;
    m_atlas_pool = new HpStack;
    m_layer_status_pool = new HpStack;
    m_anima_status_pool = new HpStack;
    m_instance_todestory = new CCArray;
    
    m_spriteFrameCache = new HpSpriteFrameCache;;
    m_spriteFrameCache->init();
    
    m_aniFilePath = NULL;
    m_hd = false;
}

HpCharactorManager::~HpCharactorManager()
{
    m_instance_todestory->release();
    m_anima_status_pool->release();
    m_layer_status_pool->release();
    m_atlas_pool->release();
    m_render->release();
    m_builder->release();
    m_xml_parser->release();
    m_chr_parser->release();
    m_charactors->release();
    m_spriteFrameCache->release();
    
    CC_SAFE_RELEASE_NULL(m_aniFilePath);
}

HpCharactorManager* HpCharactorManager::sharedManager()
{
    if(s_charator_manager == NULL){
        s_charator_manager = new HpCharactorManager;
    }
    
    return s_charator_manager;
}

void HpCharactorManager::purgeManager()
{
    CC_SAFE_RELEASE(s_charator_manager);
}

void HpCharactorManager::addCharactorsWithFile(const char *pszFile)
{
    if(m_charactors->objectForKey(pszFile)){
        HPLOG("Charactor of file %s already exists", pszFile);
        return;
    }
    
    const char* suffix = strrchr(pszFile, '.');
    HpCharactorParser* parser = strcasecmp(suffix, ".xml") == 0 ? (HpCharactorParser*)m_xml_parser : m_chr_parser;
    
    if (parser != NULL) {
        HpCharactor* chr = static_cast<HpCharactor*>(parser->parse(pszFile));
        
        if(chr == NULL){
            HPLOG("Fail to load charactor file %s", p_file);
            return;
        }
        HPLOG("build Charactor %s", p_id->getCString());
        m_charactors->setObject(chr, pszFile);
        chr->build();
    }
}

void HpCharactorManager::removeCharactorsFromFile(const char* file)
{
    HpCharactor* chara = (HpCharactor*)m_charactors->objectForKey(file);
    if (chara) {
        CCObject* plist = NULL;
        CCARRAY_FOREACH(chara->getPLists(), plist){
            removePlist(((CCString*)plist)->getCString());
        }
    }
    
    m_charactors->removeObjectForKey(file);
}

void HpCharactorManager::removeAllCharactor()
{
    CCDictElement* ele = NULL;
    CCDICT_FOREACH(m_charactors, ele) {
        HpCharactor* chara = (HpCharactor*)ele->getObject();
        CCObject* plist = NULL;
        CCARRAY_FOREACH(chara->getPLists(), plist){
            removePlist(((CCString*)plist)->getCString());
        }
    }
    
    m_charactors->removeAllObjects();
}

HpCharactor* HpCharactorManager::getCharactorById(const char* key)
{
    return (HpCharactor*)m_charactors->objectForKey(key);
}

HpAnimation* HpCharactorManager::charaAnimaByName(const char *pszName, HpCharactor** p_chara_out)
{
    CCDictElement* chara = NULL;
    CCDICT_FOREACH(m_charactors, chara) {
        HpCharactor* p = (HpCharactor*)chara->getObject();
        HpAnimation* anima = (HpAnimation*)p->getAnimas()->objectForKey(pszName);
        if (anima) {
            if (p_chara_out) {
                *p_chara_out = p;
            }
            return anima;
        }
    }
    
    return NULL;
}

HpTextureAtlas* HpCharactorManager::allocAtlas()
{
    if(m_atlas_pool->getCount() > 0){
        HPLOG("allocAtlas from matlas_pool");
        return (HpTextureAtlas*)m_atlas_pool->pop();
    }
    
    HpTextureAtlas* ret = new HpTextureAtlas();
    ret->initWithTexture(NULL, 100);
    
    return ret;
}

void HpCharactorManager::freeAtlas(CCObject* p_atlas)
{
    if(dynamic_cast<HpTextureAtlas*>(p_atlas) != NULL)
        m_atlas_pool->push(p_atlas);
}

HpLayerStatus* HpCharactorManager::requestLS()
{
    if(m_layer_status_pool->getCount() > 0){
        return (HpLayerStatus*)m_layer_status_pool->pop();
    }
    HpLayerStatus* ret = new HpLayerStatus;
    return ret;
}

void HpCharactorManager::recycleLS(CCObject* p_ls)
{
    if(dynamic_cast<HpLayerStatus*>(p_ls) != NULL){
        HpLayerStatus* ls = static_cast<HpLayerStatus*> (p_ls);
        ls->recycle();
        m_layer_status_pool->push(p_ls);
    }
    
}

HpAnimaStatus* HpCharactorManager::requestAS()
{
    HpAnimaStatus* ret = NULL;
    if(m_anima_status_pool->getCount() > 0){
        ret = (HpAnimaStatus*)m_anima_status_pool->pop();
        if(ret == NULL){
            HPLOG("");
        }
        HPLOG("requestAS0");
    } else{
        HPLOG("requestAS1");
        ret = new HpAnimaStatus;
    }
    if(ret == NULL){
        HPLOG("");
    }
    return ret;
}

void HpCharactorManager::recycleAS(CCObject* p_as)
{
    if(dynamic_cast<HpAnimaStatus*>(p_as) != NULL){
        HpAnimaStatus* as = static_cast<HpAnimaStatus*> (p_as);
        as->recycle();
        if(p_as == NULL){
            HPLOG("");
        }
        m_anima_status_pool->push(p_as);
    }
}

void HpCharactorManager::loadPlist(const char* p_plist_file)
{
    if (m_plist_cache.find(p_plist_file) != m_plist_cache.end()) {
        return;
    }
    
    m_plist_cache.insert(p_plist_file);
    
    string real_plist = p_plist_file;
//    real_plist = real_plist.substr(real_plist.rfind('\\')+1, real_plist.size());
//    
//    if (m_aniFilePath != NULL && m_aniFilePath->compare("") != 0) {
//        
//        string suffix = "/";
//        string path = m_aniFilePath->getCString();
//        
//        int pos = path.rfind('/');
//        if (pos == path.size() - 1) {
//            if (m_hd) {
//                path.insert(pos, "@2x");
//            }
//        } else {
//            if (m_hd) {
//                path = path + "@2x/";
//            } else {
//                path = path + "/";
//            }
//        }
//        
//        
//        real_plist = path + real_plist;
//    }else{
//        
//    }
    
    
    HPLOG("loadPlist %s", real_plist.c_str());
    m_spriteFrameCache->addSpriteFramesWithFile(real_plist.c_str());
}

void HpCharactorManager::removePlist(const char* p_plist_file)
{
    m_plist_cache.erase(p_plist_file);
    m_spriteFrameCache->removeSpriteFramesFromFile(p_plist_file);
}

bool HpCharactorManager::loadDefaultConfig()
{
    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader("HpCharaInst", HpCharaInstLoader::loader());
    HpShaderCache::loadDefaultShaders();
    return true;
}

bool HpCharactorManager::reloadDefaultConfig()
{
    HpShaderCache::reloadDefaultShaders();
    return true;
}

NS_HPAM_END











