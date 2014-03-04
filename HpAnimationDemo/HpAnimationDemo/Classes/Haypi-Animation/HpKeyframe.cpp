/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#include "HpKeyframe.h"
#include "HpInterpHolder.h"
#include "Hpheaders.h"
#include "ccColorExtension.h"


NS_HPAM_BEGIN



/**
 * class HpKeyframe
 *
 */

HpKeyframe::HpKeyframe(){
    this->m_pContent = NULL;
    this->m_pInterps = NULL;
    this->m_pEvent = NULL;
    setColorEx(ccClear4F);
}

HpKeyframe::~HpKeyframe(){
    setContent(NULL);
    setInterps(NULL);
    setEvent(NULL);
}

CCPoint HpKeyframe::getCenterAt(float p_t){
    if(this->m_pInterps){
        return m_pInterps->getCenterAt(p_t, this);
    }
    return this->m_cCenter;
}


CCPoint HpKeyframe::getTransAt(float p_t){
    if(this->m_pInterps){
        return this->m_pInterps->getTransAt(p_t, this);
    }
    return this->m_cTrans;
}


float HpKeyframe::getRotAt(float p_t){
    if(this->m_pInterps){
        return this->m_pInterps->getRotAt(p_t, this);
    }
    return this->m_fRot;
}


CCPoint HpKeyframe::getSkewAt(float p_t){
    if(this->m_pInterps){
        return this->m_pInterps->getSkewAt(p_t, this);
    }
    return this->m_cSkew;
}


CCPoint HpKeyframe::getScaleAt(float p_t){
    if(this->m_pInterps){
        return this->m_pInterps->getScaleAt(p_t, this);
    }
    return this->m_cScale;
}



ccColor4F HpKeyframe::getColorAt(float p_t){
    if(this->m_pInterps){
        return this->m_pInterps->getColorAt(p_t, this);
    }
    return this->m_cColor;
}

ccColor4F HpKeyframe::getColorExAt(float p_t){
    if(this->m_pInterps){
        return this->m_pInterps->getColorExAt(p_t, this);
    }
    return this->m_cColorEx;
}

HpInterpHolder* HpKeyframe::getInterps(){
    return m_pInterps;
}

void HpKeyframe::setInterps(HpInterpHolder *var){
    if (m_pInterps != var) {
        CC_SAFE_RETAIN(var);
        CC_SAFE_RELEASE(m_pInterps);
        m_pInterps = var;
    }
}

/**
 * HpContentKeyframe
 */

HpContentKeyframe::HpContentKeyframe(){
    this->m_pContentName = NULL;
}

HpContentKeyframe::~HpContentKeyframe(){
    setContentName(NULL);
}

NS_HPAM_END



