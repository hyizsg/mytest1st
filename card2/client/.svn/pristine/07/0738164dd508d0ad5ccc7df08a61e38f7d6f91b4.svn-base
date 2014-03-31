#ifndef HPCHARACTORMANAGER_H
#define HPCHARACTORMANAGER_H

#include "cocos2d.h"


#include "HpCharactor.h"
#include "HpAnimation.h"
#include "HpLayer.h"
#include "HpCharaInstObserver.h"
#include "HpAnimaStatus.h"
#include "HpAttachPoint.h"
#include "HpCharactorXmlParser.h"
#include "HpCharactorBinParser.h"
#include "HpAnimBuildVisitor.h"
#include "HpAnimRenderVisitor.h"


USING_NS_CC;

namespace haypi_animation{

class HpCharactorXmlParser;
class HpAnimBuildVisitor;
class HpAnimRenderVisitor;
class HpCharactorBinParser;


class HpCharactorManager : public CCObject {
private:
    CCDictionary* m_charactors;
    HpCharactorXmlParser* m_xml_parser;
    HpCharactorBinParser* m_chr_parser;

    HpStack* m_atlas_pool;
    HpStack* m_layer_status_pool;
    HpStack* m_anima_status_pool;

    cocos2d::CCSet* m_plist_cache;
    CCArray* m_instance_todestory;

protected:
    CC_SYNTHESIZE_READONLY(HpAnimBuildVisitor*, m_builder, Builder)
    CC_SYNTHESIZE_READONLY(HpAnimRenderVisitor*, m_render, Render)
    
    CC_SYNTHESIZE_RETAIN(CCSpriteFrameCache*, m_spriteFrameCache, SpriteFrameCache);
    
    CC_SYNTHESIZE_RETAIN(CCString*, m_aniFilePath, AniFilePath);
    CC_SYNTHESIZE(bool, m_hd, HD);

    HpCharactorManager();
    virtual ~HpCharactorManager();

public:
    void destroyInstance(HpCharaInst* p_inst);
    void destroyCharactorForId(CCString* p_id);
public:

    static HpCharactorManager* SharedCharactorManager();

    static void purgeCharactorManager();
    void loadPlist(CCString* p_plist_file);
    void removePlist(CCString* p_plist_file);
    void loadCharactorForId(CCString* p_id, CCString* p_file);
    void removeCharactorForId(CCString* p_id);
    HpCharaInst* createInstanceOfId(CCString* p_id, CCNode* p_node);

    void destroyLater(CCObject* p_instance);
    CCObject* getCharactorById(CCString* p_id);

    CCObject* allocAtlas();
    void freeAtlas(CCObject* p_atlas);

    CCObject* requestLS();
    void recycleLS(CCObject* p_ls);

    CCObject* requestAS();
    void recycleAS(CCObject* p_as);

    void removeAllCharactor();

};

}

#endif // HPCHARACTORMANAGER_H
