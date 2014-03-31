#include "HpCharactorManager.h"

#include "HpLog.h"
#include "HpTextureAtlas.h"

using namespace haypi_animation;


static HpCharactorManager* s_charator_manager = NULL;

class HpSpriteFrameCache : public CCSpriteFrameCache {
    
    
public:
    
};

HpCharactorManager::HpCharactorManager(){
    m_charactors = new CCDictionary;
    m_xml_parser = new HpCharactorXmlParser;
    m_chr_parser = new HpCharactorBinParser;
    m_builder = new HpAnimBuildVisitor;
    m_render = new HpAnimRenderVisitor;
    m_atlas_pool = new HpStack;
    m_layer_status_pool = new HpStack;
    m_anima_status_pool = new HpStack;
    m_plist_cache = new CCSet;
    m_hd = false;
    m_instance_todestory = new CCArray;
    
    m_spriteFrameCache = new HpSpriteFrameCache;;
    m_spriteFrameCache->init();
    
    m_aniFilePath = NULL;
    m_hd = false;
}

HpCharactorManager::~HpCharactorManager(){
    m_instance_todestory->release();
    m_plist_cache->release();
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

// private method
void HpCharactorManager::destroyInstance(HpCharaInst* p_inst){
    p_inst->removeFromParentAndCleanup(true);
    // HpCharaInst is autorelease now.
    //CC_SAFE_RELEASE(p_inst);
}

HpCharactorManager* HpCharactorManager::SharedCharactorManager(){
    if(s_charator_manager == NULL){
        s_charator_manager = new HpCharactorManager;
    }

    return s_charator_manager;
}

void HpCharactorManager::purgeCharactorManager(){
    CC_SAFE_RELEASE(s_charator_manager);
}



void HpCharactorManager::loadCharactorForId(CCString* p_id, CCString* p_file){    
    if(m_charactors->objectForKey(p_id->getCString())){
        HPLOG("Charactor of id %s already exists", p_id->getCString());
        return;
    }
    
    char* suffix = strrchr(p_file->getCString(), '.');
    HpCharactorParser* parser = strcasecmp(suffix, ".xml") == 0 ? (HpCharactorParser*)m_xml_parser : m_chr_parser;
    
    if (parser != NULL) {
        HpCharactor* chr = static_cast<HpCharactor*>(parser->parse(p_file));
        
        if(chr == NULL){
            HPLOG("Fail to load charactor file %s", p_file);
            return;
        }
        HPLOG("build Charactor %s", p_id->getCString());
        m_charactors->setObject(chr, p_id->getCString());
        chr->build();
    }
}

void HpCharactorManager::removeCharactorForId(CCString* p_id){
    m_charactors->removeObjectForKey(p_id->getCString());
}

void HpCharactorManager::destroyCharactorForId(CCString* p_id)
{
    HpCharactor *charactor = (HpCharactor*)m_charactors->objectForKey(p_id->m_sString);
    if (charactor == NULL)
        return;
    CCArray* list = charactor->getPLists();
    for (int i=0; i<list->count(); i++) {
        removePlist((CCString*)list->objectAtIndex(i));
    }
    
    removeCharactorForId(p_id);
}

HpCharaInst* HpCharactorManager::createInstanceOfId(CCString* p_id, CCNode* p_node){
    HpCharactor* chr = dynamic_cast<HpCharactor*>(m_charactors->objectForKey(p_id->getCString()));
    if(chr == NULL){
        HPLOG("Charactor of id %s doesn't exist!", p_id->getCString());
        return NULL;
    }
    HpCharaInst* inst = HpCharaInst::create(chr);
#ifdef ANDROID
    inst->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorMask));
#endif
    if(p_node){
        inst->addToWorld(p_node);
    }
    return inst;
}

void HpCharactorManager::destroyLater(CCObject* p_instance){

}

CCObject* HpCharactorManager::getCharactorById(CCString* p_id){
    return m_charactors->objectForKey(p_id->getCString());
}

CCObject* HpCharactorManager::allocAtlas(){
    if(m_atlas_pool->getCount() > 0){
        HPLOG("allocAtlas from matlas_pool");
        return m_atlas_pool->pop();
    }
    
    CCTextureAtlas* ret = new HpTextureAtlas();
    ret->initWithTexture(NULL, 100);
    
    return ret;
}

void HpCharactorManager::freeAtlas(CCObject* p_atlas){
    if(dynamic_cast<CCTextureAtlas*>(p_atlas) != NULL)
        m_atlas_pool->push(p_atlas);
}

CCObject* HpCharactorManager::requestLS(){
    if(m_layer_status_pool->getCount() > 0){
        return m_layer_status_pool->pop();
    }
    HpLayerStatus* ret = new HpLayerStatus;
    return ret;
}

void HpCharactorManager::recycleLS(CCObject* p_ls){
    if(dynamic_cast<HpLayerStatus*>(p_ls) != NULL){
        HpLayerStatus* ls = static_cast<HpLayerStatus*> (p_ls);
        ls->recycle();
        m_layer_status_pool->push(p_ls);
    }

}

CCObject* HpCharactorManager::requestAS(){
    CCObject* ret = NULL;
    if(m_anima_status_pool->getCount() > 0){
        ret = m_anima_status_pool->pop();
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

void HpCharactorManager::recycleAS(CCObject* p_as){
    if(dynamic_cast<HpAnimaStatus*>(p_as) != NULL){
        HpAnimaStatus* as = static_cast<HpAnimaStatus*> (p_as);
        as->recycle();
        if(p_as == NULL){
            HPLOG("");
        }
        m_anima_status_pool->push(p_as);
    }
}

void HpCharactorManager::removeAllCharactor(){
    m_charactors->removeAllObjects();
}



void HpCharactorManager::loadPlist(CCString* p_plist_file){
    if(m_plist_cache->containsObject(p_plist_file))
        return;

    m_plist_cache->addObject(p_plist_file);

    string real_plist = p_plist_file->m_sString;
    real_plist = real_plist.substr(real_plist.rfind('\\')+1, real_plist.size());
    
    if (m_aniFilePath != NULL && m_aniFilePath->compare("") != 0) {
        
        string suffix = "/";
        string path = m_aniFilePath->getCString();
        
        int pos = path.rfind('/');
        if (pos == path.size() - 1) {
            if (m_hd) {
                path.insert(pos, "@2x");
            }
        } else {
            if (m_hd) {
                path = path + "@2x/";
            } else {
                path = path + "/";
            }
        }
        
        
        real_plist = path + real_plist;
    }else{
//        real_plist = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(p_plist_file->m_sString, pszPlist);
    }

    
    HPLOG("loadPlist %s", real_plist.c_str());
    m_spriteFrameCache->addSpriteFramesWithFile(real_plist.c_str());
}

void HpCharactorManager::removePlist(CCString* p_plist_file)
{
    m_plist_cache->removeObject(p_plist_file);
    m_spriteFrameCache->removeSpriteFramesFromFile(p_plist_file->getCString());
}
