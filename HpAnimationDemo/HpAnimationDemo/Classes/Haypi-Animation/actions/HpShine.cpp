//
//  HpShineTo.cpp
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-8.
//
//

#include "HpShine.h"
#include "HpLightProtocol.h"

NS_HPAM_BEGIN

HpShineTo* HpShineTo::create(float duration, GLubyte red, GLubyte green, GLubyte blue)
{
    HpShineTo *pShineTo = new HpShineTo();
    pShineTo->initWithDuration(duration, red, green, blue);
    pShineTo->autorelease();
    
    return pShineTo;
}

bool HpShineTo::initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_to = ccc3(red, green, blue);
        return true;
    }
    
    return false;
}

CCObject* HpShineTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    HpShineTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (HpShineTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new HpShineTo();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration(m_fDuration, m_to.r, m_to.g, m_to.b);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void HpShineTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    HpLightProtocol *lightProtocol = dynamic_cast<HpLightProtocol*>(m_pTarget);
    if (lightProtocol)
    {
        m_from = lightProtocol->getLight();
    }
}

void HpShineTo::update(float time)
{
    HpLightProtocol *lightProtocol = dynamic_cast<HpLightProtocol*>(m_pTarget);
    if (lightProtocol)
    {
        lightProtocol->setLight(ccc3(GLubyte(m_from.r + (m_to.r - m_from.r) * time),
                                     (GLbyte)(m_from.g + (m_to.g - m_from.g) * time),
                                     (GLbyte)(m_from.b + (m_to.b - m_from.b) * time)));
    }
}

//
// ShineBy
//

HpShineBy* HpShineBy::create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue)
{
    HpShineBy *pTintBy = new HpShineBy();
    pTintBy->initWithDuration(duration, deltaRed, deltaGreen, deltaBlue);
    pTintBy->autorelease();
    
    return pTintBy;
}

bool HpShineBy::initWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_deltaR = deltaRed;
        m_deltaG = deltaGreen;
        m_deltaB = deltaBlue;
        
        return true;
    }
    
    return false;
}

CCObject* HpShineBy::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    HpShineBy* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (HpShineBy*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new HpShineBy();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration(m_fDuration, (GLubyte)m_deltaR, (GLubyte)m_deltaG, (GLubyte)m_deltaB);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void HpShineBy::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    
    HpLightProtocol *lightProtocol = dynamic_cast<HpLightProtocol*>(pTarget);
    if (lightProtocol)
    {
        ccColor3B color = lightProtocol->getLight();
        m_fromR = color.r;
        m_fromG = color.g;
        m_fromB = color.b;
    }
}

void HpShineBy::update(float time)
{
    HpLightProtocol *lightProtocol = dynamic_cast<HpLightProtocol*>(m_pTarget);
    if (lightProtocol)
    {
        lightProtocol->setLight(ccc3((GLubyte)(m_fromR + m_deltaR * time),
                                     (GLubyte)(m_fromG + m_deltaG * time),
                                     (GLubyte)(m_fromB + m_deltaB * time)));
    }    
}

CCActionInterval* HpShineBy::reverse(void)
{
    return HpShineBy::create(m_fDuration, -m_deltaR, -m_deltaG, -m_deltaB);
}


NS_HPAM_END