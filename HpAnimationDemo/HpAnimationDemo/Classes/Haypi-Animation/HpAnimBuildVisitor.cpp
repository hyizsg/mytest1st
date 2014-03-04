
#include "HpAnimBuildVisitor.h"

#include "HpCharactor.h"
#include "Hpheaders.h"

NS_HPAM_BEGIN


HpAnimBuildVisitor::HpAnimBuildVisitor(){
    this->m_hdmode = false;
    this->m_hdpostfix = NULL;
}

HpAnimBuildVisitor::~HpAnimBuildVisitor(){
    CC_SAFE_RELEASE(m_hdpostfix);
    CC_SAFE_RELEASE(m_anima_map);
}

void HpAnimBuildVisitor::begin(CCObject* p_map){
    CCAssert(dynamic_cast<CCDictionary*>(p_map) != NULL, "Invalid target-HpAnimBuildVisitor");
    m_anima_map = static_cast<CCDictionary*>(p_map);
}

void HpAnimBuildVisitor::end(){
}

void HpAnimBuildVisitor::visitAnima(HpAnimation *p_ani, bool p_first, float p_frm){
    CCObject* p_item = NULL;
    CCARRAY_FOREACH(p_ani->getLayers(), p_item){
        HpLayer* obj = static_cast<HpLayer*>(p_item);
        this->visitLayer(obj, p_first, p_frm);
    }
}

void HpAnimBuildVisitor::visitLayer(HpLayer *p_layer, bool p_first, float p_frm){
    p_layer->build();

    for(int i = 0; i < p_layer->getKeys()->count(); ++ i){
        HpKeyframe* frm = static_cast<HpKeyframe*>(p_layer->getKeys()->objectAtIndex(i));

        if(frm->getInterps()){
            HpKeyframe* next_frm = static_cast<HpKeyframe*>(p_layer->getKeys()->objectAtIndex(i + 1));
            if (frm->getContent()->isEqual(next_frm->getContent())) {
                frm->getInterps()->setTarget(next_frm);
            }else{
                frm->setInterps(NULL);
            }
        }
    }

    HPLOG("apple...HpContentKeyframe %d", p_layer->getContentKeys()->count());

    CCObject* item = NULL;
    CCARRAY_FOREACH(p_layer->getContentKeys(), item){
        HpContentKeyframe* k = dynamic_cast<HpContentKeyframe*>(item);
        k->visitBy(this, NULL, 0);
    }

}

void HpAnimBuildVisitor::visitImageKey(HpImageKeyframe *p_ikf, HpKeyframe *p_frm, float time){
    if(p_ikf->getSpriteFrame()) return;

    if(getHDMode()){

    } else {

    }
    const char* pszName = p_ikf->getContentName()->getCString();
    CCSpriteFrame* pframe = HpCharactorManager::sharedManager()->getSpriteFrameCache()->spriteFrameByName(pszName);
    CCAssert(pframe, "HpAnimBuildVisitor visiImagekey the pframe is NULL");
    p_ikf->setSpriteFrame(pframe);

}

/**
 * @brief HpAnimBuildVisitor::visitAnimaKey  这里的p_akf不能获取一个Animation会出现空值
 * @param p_akf
 * @param p_frm
 * @param time
 *
 */

void HpAnimBuildVisitor::visitAnimaKey(HpAnimaKeyframe *p_akf, HpKeyframe *p_frm, float time){
    CCObject* _ani = this->m_anima_map->objectForKey(p_akf->getContentName()->getCString());
    HpAnimation* ani = dynamic_cast<HpAnimation*>(_ani);
    if(_ani == NULL){
        HPLOG("visitAnimaKey   the Animation is NULL and content name is %s", p_akf->getContentName()->getCString());
        return;
    }
    p_akf->setAnima(ani);
}

NS_HPAM_END
