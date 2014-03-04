/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#include "HpInterpHolder.h"
#include "ccColorExtension.h"
#include "HpKeyframe.h"


namespace haypi_animation{

HpInterpHolder::HpInterpHolder(){
    m_pCenterInterp = NULL;
    m_pTransInterp = NULL;
    m_pSkewInterp = NULL;
    m_pScaleInterp = NULL;
    m_pRotInterp = NULL;
    m_pColorInterp = NULL;
    m_pTarget = NULL;
}

HpInterpHolder::~HpInterpHolder(){
    CC_SAFE_RELEASE(m_pCenterInterp);
    CC_SAFE_RELEASE(m_pTransInterp);
    CC_SAFE_RELEASE(m_pSkewInterp);
    CC_SAFE_RELEASE(m_pScaleInterp);
    CC_SAFE_RELEASE(m_pRotInterp);
    CC_SAFE_RELEASE(m_pColorInterp);
}


CCPoint HpInterpHolder::getCenterAt(float time, HpKeyframe* p_self){
    float f = m_pCenterInterp->getFactorWithStart(p_self->getTime(), m_pTarget->getTime(), time);
    return ccpLerp(p_self->getCenter(), m_pTarget->getCenter(), f);
}

CCPoint HpInterpHolder::getTransAt(float time, HpKeyframe* p_self){
    float f = m_pTransInterp->getFactorWithStart(p_self->getTime(), m_pTarget->getTime(), time);
    return ccpLerp(p_self->getTrans(), m_pTarget->getTrans(), f);
}

CCPoint HpInterpHolder::getSkewAt(float time, HpKeyframe* p_self){
    float f = m_pSkewInterp->getFactorWithStart(p_self->getTime(), m_pTarget->getTime(), time);
    return ccpLerp(p_self->getSkew(), m_pTarget->getSkew(), f);
}

CCPoint HpInterpHolder::getScaleAt(float time, HpKeyframe* p_self){
    float f = m_pScaleInterp->getFactorWithStart(p_self->getTime(), m_pTarget->getTime(), time);
    return ccpLerp(p_self->getScale(), m_pTarget->getScale(), f);
}

float HpInterpHolder::getRotAt(float time, HpKeyframe* p_self){
    float f = m_pRotInterp->getFactorWithStart(p_self->getTime(), m_pTarget->getTime(), time);
    return p_self->getRot() * (1.f - f) + m_pTarget->getRot() * f;
}

ccColor4F HpInterpHolder::getColorAt(float time, HpKeyframe* p_self){
    float f = m_pColorInterp->getFactorWithStart(p_self->getTime(), m_pTarget->getTime(), time);
    return cccLerp(p_self->getColor(), m_pTarget->getColor(), f);
}
    
ccColor4F HpInterpHolder::getColorExAt(float time, HpKeyframe* p_self){
    float f = m_pColorInterp->getFactorWithStart(p_self->getTime(), m_pTarget->getTime(), time);
    return cccLerp(p_self->getColorEx(), m_pTarget->getColorEx(), f);
}

void HpInterpHolder::setTarget(HpKeyframe* p_fm){
    m_pTarget = p_fm;
}

}

