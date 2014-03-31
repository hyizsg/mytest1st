/**
 * @author mingjiang.bai@gmail.com
 * @date 20121214
 *
 */
#include "HpImageKeyframe.h"
#include "HpLog.h"

using namespace haypi_animation;


HpImageKeyframe::HpImageKeyframe(){
    m_pSpriteFrame = NULL;
}

HpImageKeyframe::HpImageKeyframe(HpImageKeyframe* p_image){
    this->setTime(p_image->getTime());
    this->setContentName(p_image->getContentName());
    this->setSpriteFrame(p_image->getSpriteFrame());
}

HpImageKeyframe::~HpImageKeyframe(){
    CC_SAFE_RELEASE_NULL(m_pSpriteFrame);
}


CCSpriteFrame* HpImageKeyframe::getSpriteFrame(){
    return m_pSpriteFrame;
}

void HpImageKeyframe::setSpriteFrame(CCSpriteFrame *var){
    if (m_pSpriteFrame != var) {
        CC_SAFE_RETAIN(var);
        CC_SAFE_RELEASE(m_pSpriteFrame);
        m_pSpriteFrame = var;
    }
}


void HpImageKeyframe::visitBy(HpAnimVisitor *p_visitor, HpKeyframe *p_fm, float time){
    HPLOG("HpImageKeyframe visitBy...%x    %x", p_visitor, p_fm);
    p_visitor->visitImageKey(this, p_fm, time);
}


HpContentKeyframe* HpImageKeyframe::clone(){
    HpImageKeyframe* ret = new HpImageKeyframe();
    ret->setTime(this->getTime());
    ret->setContentName(this->getContentName());
    ret->setSpriteFrame(this->getSpriteFrame());
    
//    ret->autorelease();
    CC_AUTO_RELEASE(ret);
    return ret;
}
