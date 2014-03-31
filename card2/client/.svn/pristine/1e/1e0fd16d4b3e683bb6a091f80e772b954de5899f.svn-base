//
//  HMaskLayer.cpp
//  card
//
//  Created by 周 刚 on 13-7-13.
//
//

#include "../../headers.h"
#include "HMaskLayer.h"
#include "HWindow.h"
#include "HRootScene.h"

#define kMaskActionTag  16700

HMaskWindow::HMaskWindow()
{
    m_pInWindow = new CCArray;
    m_pOutWindow = new CCArray;
    
    m_pNullObject = new HWindow;
}

HMaskWindow::~HMaskWindow()
{
    CC_SAFE_RELEASE_NULL(m_pInWindow);
    CC_SAFE_RELEASE_NULL(m_pOutWindow);
    CC_SAFE_RELEASE_NULL(m_pNullObject);
}


HMaskWindow* HMaskWindow::create()
{
    HMaskWindow* mask = new HMaskWindow;
    mask->initWithColor(ccc4(0, 0, 0, 0));
//    mask->autorelease();
    CC_AUTO_RELEASE(mask);
    mask->onEnter();
    return mask;
}

void HMaskWindow::maskWithInOut(HWindow* pIn, HWindow* pOut, float fDuration, bool bCleanup)
{
    m_pInWindow->addObject(pIn ? pIn : m_pNullObject);
    m_pOutWindow->addObject(pOut ? pOut : m_pNullObject);
    
    m_fDuration.push_back(fDuration);
    m_bSendCleanup.push_back(bCleanup);
    
//    if (m_pInWindow->count() == 1)
    {
        beginMask();
    }
    
}

HRootScene* HMaskWindow::scene()
{
    CCNode* parent = getParent();
    while (parent) {
        HRootScene* scene = dynamic_cast<HRootScene*>(parent);
        if (scene) {
            return scene;
        }else{
            parent = parent->getParent();
        }
    }
    
    return NULL;
}

HWindow* HMaskWindow::inWindow()
{
    return dynamic_cast<HWindow*>(m_pInWindow->objectAtIndex(0));
}

HWindow* HMaskWindow::outWindow()
{
    return dynamic_cast<HWindow*>(m_pOutWindow->objectAtIndex(0));
}

void HMaskWindow::beginMask()
{
//    CCLog("HMaskWindow::beginMask");
    
    if (m_pInWindow->count() > 0) {
        
        CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(false);
        setVisible(true);
        setOpacity(0);
        
        if (m_pInWindow->count() > 1 || !inWindow()->isEnableAnimaInOut()
            || inWindow()->isDialog() || outWindow()->isDialog()
            || !scene()->isRunning() || HRootScene::isEnterBackgroud())
        {
            if (getActionByTag(kMaskActionTag)) {
//                stopMaskAction();
//                stopAllActions();
//                begin();
//                hideOutShowIn();
//                finish();
            }else{
                begin();
                hideOutShowIn();
                finish();
            }
        }else{
            
            CCActionInterval* a = (CCActionInterval *)CCSequence::create
            (
             CCCallFunc::create(this, callfunc_selector(HMaskWindow::begin)),
             CCFadeIn::create(m_fDuration[0]/2),
             CCCallFunc::create(this, callfunc_selector(HMaskWindow::hideOutShowIn)),
             CCFadeOut::create(m_fDuration[0]/2),
             CCCallFunc::create(this, callfunc_selector(HMaskWindow::finish)),
             NULL
             );
            this->runAction(a)->setTag(kMaskActionTag);
            
        }
    }
}

void HMaskWindow::begin()
{
    CCLog("HMaskWindow::begin");
    
    if (this->scene()->isRunning()) {
        outWindow()->onExitTransitionDidStart();
        inWindow()->onEnter();
    }
}

bool HMaskWindow::isWindowWillBeClear(HWindow* wnd)
{
    bool bClear = false;
    for (int i=0; i<m_pOutWindow->count(); i++) {
        HWindow* out = (HWindow*)m_pOutWindow->objectAtIndex(i);
        if (out == wnd) {
            bClear = m_bSendCleanup[i];
            break;
        }
    }
    
    return bClear;
}

void HMaskWindow::hideOutShowIn()
{
    CCLog("HMaskWindow::hideOutShowIn");
    
    inWindow()->setVisible(true);
    if (!inWindow()->isDialog()) {
        outWindow()->setVisible(false);
    }else{
        HWindow* inwnd = inWindow();
        CCNode* node = inwnd->getParent();
        int idx = -1;
        for (int i=node->getChildrenCount()-1; i>=0; i--) {
            if (node->getChildren()->objectAtIndex(i) == inwnd) {
                idx =i; break;
            }
        }
        for (int i=idx-1; i>=0; i--) {
            HWindow* wnd = (HWindow*)node->getChildren()->objectAtIndex(i);
            if (!wnd->isDialog() && !isWindowWillBeClear(wnd)) {
                wnd->setVisible(true);
                break;
            }
        }
    }
}

void HMaskWindow::finish()
{
    CCLog("HMaskWindow::finish");
    
    CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
    setVisible(false);
    
    HWindow* inwnd = inWindow();
    HWindow* outwnd = outWindow();
    bool bclean = m_bSendCleanup[0];
    
    m_fDuration.erase(m_fDuration.begin());
    m_bSendCleanup.erase(m_bSendCleanup.begin());
    
    inwnd->retain();
    inwnd->autorelease();
    
    outwnd->retain();
    outwnd->autorelease();
    
    m_pInWindow->removeObjectAtIndex(0);
    m_pOutWindow->removeObjectAtIndex(0);
    
    
    if (this->scene()->isRunning()) {
        outwnd->onExit();
        inwnd->onEnterTransitionDidFinish();
    }
    
    if (bclean) {
        outwnd->removeFromParent();
    }
    
    if (m_pOutWindow->count() > 0) {
//        beginMask();
        runAction(CCCallFunc::create(this, callfunc_selector(HMaskWindow::beginMask)));
    }
}

void HMaskWindow::stopMaskAction()
{
    CCSequence* action = dynamic_cast<CCSequence*>(getActionByTag(kMaskActionTag));
    if (action) {
        while (!action->isDone()) {
            action->step(HRootScene::gfDurationFadeInOut);
        }
    }
    
    stopActionByTag(kMaskActionTag);
//    CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
}

