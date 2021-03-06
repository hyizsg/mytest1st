﻿//
//  HWindow.cpp
//  card
//
//  Created by zhou gang on 13-7-11.
//
//

#include "../../headers.h"
#include "HWindow.h"
#include "HRootScene.h"
#include "HDialog.h"


HWindow::HWindow()
{
    
}

HWindow::~HWindow()
{

}

HRootScene* HWindow::scene()
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

bool HWindow::init()
{
    super::init();
    m_bTouchEnabled = true;
    
//    CCLOG("HWindow create:0x%0x class: %s: uid: %d ", (unsigned int)this, getClass().c_str(), m_uID);
    
    return true;
}

bool HWindow::loadPlistCCBI(const char* ccbi)
{
    INIT_PLISTS_CCBI(ccbi);
    
    return true;
}

void HWindow::HWindow::loadPlist()
{
    
}

void HWindow::disposPlist()
{
    
}

void HWindow::release(void)
{
    if (retainCount() == 1) {
        this->disposPlist();
    }
    
    HRootLayer::release();
}

bool HWindow::isDialog(CCObject* obj)
{
    return dynamic_cast<HDialog*>(obj) != NULL;
}

bool HWindow::isDialog()
{
    return dynamic_cast<HDialog*>(this) != NULL;
}


void HWindow::presentRootLayer(bool bAnima)
{
    HRootScene::current()->presentWindow(this, bAnima);
}

void HWindow::dismissRootLayer(bool bAnima)
{
      HRootScene::current()->dissmisWindow(this, bAnima);
}

void HWindow::dismissAllLayers(bool bAnima)
{
    HRootScene::current()->dissmisAllWinodw(bAnima);
}

void HWindow::replaceRootLayer(bool bAnima)
{
    HRootScene::current()->replaceWindow(this, bAnima);
}

void HWindow::dismissLater(bool banima, float delay)
{
    CCDelayTime *action1 = CCDelayTime::create(delay);
    HCallFuncI *action2 = HCallFuncI::create(this, callfuncI_selector(HWindow::dismissRootLayer), banima);
    HRootScene::current()->getTopShowLayer()->runAction(CCSequence::createWithTwoActions(action1, action2));
}


CCNode* HWindow::readNodeGraphFromFile(const char *pCCBFileName, bool originalSize)
{
    return super::readNodeGraphFromFile(pCCBFileName, originalSize);
}

void HWindow::onBackClick(CCObject*, CCControlEvent)
{
    HGameManager::getInstance()->playSoundEffect(HMUSIC_BUTTON);
    dismissRootLayer();
}

void HWindow::onCloseClick(CCObject*, CCControlEvent)
{
    HGameManager::getInstance()->playSoundEffect(HMUSIC_BUTTON);
    dismissAllLayers();
}

void HWindow::onEnter()
{
    CCLOG("%30s: %s", "onEnter", getClass().c_str());
    
    super::onEnter();
    
    onEnterForeground();
    willMoveToWindow(getParent());
}

void HWindow::onExit()
{
    CCLOG("%30s: %s", "onExit", getClass().c_str());
    
    super::onExit();
    
    onEnterBackground();
    didMoveToWindow(NULL);
}

void HWindow::onEnterTransitionDidFinish()
{
//    CCLOG("%30s: %s", "onEnterTransitionDidFinish", getClass().c_str());
    
    super::onEnterTransitionDidFinish();
    
    didMoveToWindow(getParent());
}

void HWindow::onExitTransitionDidStart()
{
//    CCLOG("%30s: %s", "onExitTransitionDidStart", getClass().c_str());
    
    super::onExitTransitionDidStart();
    
    willMoveToWindow(NULL);
}

void HWindow::onEnterForeground()
{
//    CCLOG("%30s: %s", "onEnterForeground", getClass().c_str());
}

void HWindow::onEnterBackground()
{
//    CCLOG("%30s: %s", "onEnterBackground", getClass().c_str());
}

void HWindow::onPresented()
{
    
}

void HWindow::onDismissed()
{
    
}

HWindow* HWindow::current()
{
    return HRootScene::current()->getRunningLayer();
}
