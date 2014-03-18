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


//
// GrayIn
//

HpGrayIn* HpGrayIn::create(float d)
{
    HpGrayIn* pAction = new HpGrayIn();
    
    pAction->initWithDuration(d);
    pAction->autorelease();
    
    return pAction;
}

CCObject* HpGrayIn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    HpGrayIn* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (HpGrayIn*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new HpGrayIn();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    CC_SAFE_DELETE(pNewZone);
    
    return pCopy;
}

void HpGrayIn::update(float time)
{
    HpLightProtocol *pLightProtocol = dynamic_cast<HpLightProtocol*>(m_pTarget);
    if (pLightProtocol)
    {
        pLightProtocol->setGray((GLubyte)(255 * time));
    }
}

CCActionInterval* HpGrayIn::reverse(void)
{
    return HpGrayOut::create(m_fDuration);
}

//
// GrayOut
//

HpGrayOut* HpGrayOut::create(float d)
{
    HpGrayOut* pAction = new HpGrayOut();
    
    pAction->initWithDuration(d);
    pAction->autorelease();
    
    return pAction;
}

CCObject* HpGrayOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    HpGrayOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (HpGrayOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new HpGrayOut();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    CC_SAFE_DELETE(pNewZone);
    
    return pCopy;
}

void HpGrayOut::update(float time)
{
    HpLightProtocol *pLightProtocol = dynamic_cast<HpLightProtocol*>(m_pTarget);
    if (pLightProtocol)
    {
        pLightProtocol->setGray(GLubyte(255 * (1 - time)));
    }
}

CCActionInterval* HpGrayOut::reverse(void)
{
    return HpGrayIn::create(m_fDuration);
}

//
// GrayTo
//

HpGrayTo* HpGrayTo::create(float duration, GLubyte gray)
{
    HpGrayTo *pGrayTo = new HpGrayTo();
    pGrayTo->initWithDuration(duration, gray);
    pGrayTo->autorelease();
    
    return pGrayTo;
}

bool HpGrayTo::initWithDuration(float duration, GLubyte gray)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_toGray = gray;
        return true;
    }
    
    return false;
}

CCObject* HpGrayTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    HpGrayTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (HpGrayTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new HpGrayTo();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration(m_fDuration, m_toGray);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void HpGrayTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    
    HpLightProtocol *pLightProtocol = dynamic_cast<HpLightProtocol*>(pTarget);
    if (pLightProtocol)
    {
        m_fromGray = pLightProtocol->getGray();
    }
}

void HpGrayTo::update(float time)
{
    HpLightProtocol *pLightProtocol = dynamic_cast<HpLightProtocol*>(m_pTarget);
    if (pLightProtocol)
    {
        pLightProtocol->setGray((GLubyte)(m_fromGray + (m_toGray - m_fromGray) * time));
    }
}


NS_HPAM_END