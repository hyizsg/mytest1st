#include "HpAnimaKeyframe.h"
#include "HpAnimBuildVisitor.h"
#include "HpAnimRenderVisitor.h"

#include "HpLog.h"


using namespace haypi_animation;


HpAnimaKeyframe::HpAnimaKeyframe(){
    m_isTimeInherited = true;
    m_anima = NULL;
}

HpAnimaKeyframe::~HpAnimaKeyframe(){
    CC_SAFE_RELEASE(m_anima);
}

HpAnimaKeyframe::HpAnimaKeyframe(HpAnimaKeyframe *p_akf){
    setTime(p_akf->getTime());
    setContentName(p_akf->getContentName());
    setAnima(p_akf->getAnima());
    setIsTimeInherited(p_akf->getIsTimeInherited());
}

void HpAnimaKeyframe::visitBy(HpAnimVisitor *p_visitor, HpKeyframe *p_frm, float time){
    HPLOG("AnimaKeyframe visitBy...%x    %x", p_visitor, p_frm);
    p_visitor->visitAnimaKey(this, p_frm, time);
}

HpContentKeyframe* HpAnimaKeyframe::clone(){
    HpAnimaKeyframe* ret = new HpAnimaKeyframe(this);
//    ret->autorelease();
    HP_AUTO_RELEASE(ret);
    return ret;
}
