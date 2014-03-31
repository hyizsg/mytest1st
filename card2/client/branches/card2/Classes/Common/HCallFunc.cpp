//
//  HCallFunc.cpp
//  card2
//
//  Created by zhou gang on 14-2-11.
//
//

#include "headers.h"
#include "HCallFunc.h"



// ---------------

HCallFuncI* HCallFuncI::create(cocos2d::CCObject *pSelectorTarget, SEL_CallFuncI selector, int value)
{
    HCallFuncI *pRet = new HCallFuncI();
    
    if (pRet && pRet->initWithTarget(pSelectorTarget)) {
        pRet->m_pCallFunc = (SEL_CallFunc)selector;
        pRet->m_nValue = value;
        //        pRet->autorelease();
        CC_AUTO_RELEASE(pRet);
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void HCallFuncI::execute()
{
    if (m_pCallFunc) {
        (m_pSelectorTarget->*((SEL_CallFuncI)m_pCallFunc))(m_nValue);
    }
}
