//
//  HRootScence.cpp
//  card
//
//  Created by zhou gang on 13-7-12.
//
//

#include "../../headers.h"
#include "HRootScene.h"
#include "HWindow.h"
#include "HMaskLayer.h"
#include "HDialog.h"
#include "HLoadingLayer.h"
#include "HMaskLayer2.h"

const float HRootScene::gfDurationFadeInOut = 0.3f;
bool HRootScene::s_bEnterBackgroud = false;

class HGameWindow : public HWindow { public: CREATE_FUNC(HGameWindow); HCLASSTYPE(HGameWindow, HWindow);};
class HUIWindow : public HWindow { public: CREATE_FUNC(HUIWindow); HCLASSTYPE(HUIWindow, HWindow);};
class HScaleWindow : public HWindow { public: CREATE_FUNC(HScaleWindow); HCLASSTYPE(HScaleWindow, HWindow);};
class HTopWindow : public HWindow { public: CREATE_FUNC(HTopWindow); HCLASSTYPE(HTopWindow, HWindow);};

HRootScene* HRootScene::s_pCurrentScene =  NULL;

HRootScene::HRootScene()
: m_pNextWindw(NULL)
, m_pRunningWindow(NULL)
, m_pUINode(NULL)
, m_pGameNode(NULL)
{
    
    
}

HRootScene::~HRootScene()
{
    if (s_pCurrentScene == this) {
        s_pCurrentScene = NULL;
    }
}


HRootScene* HRootScene::create()
{
    HRootScene* scene = new HRootScene;
    scene->init();
//    scene->autorelease();
    CC_AUTO_RELEASE(scene);
    
    return scene;
}

HRootScene* HRootScene::current()
{
    if (s_pCurrentScene == NULL) {
        s_pCurrentScene = HRootScene::create();
        CCDirector::sharedDirector()->pushScene(s_pCurrentScene);
    }
    
    return s_pCurrentScene;
}

void HRootScene::setEnterBackgroud(bool backgroud)
{
    s_bEnterBackgroud = backgroud;
    
    HRootScene* root = current();
    if (root) {
//        ((CCNode*)root->m_pMaskNode)->stopMaskAction();
    }
}

bool HRootScene::isAddSlib = false;

bool HRootScene::init()
{
    CCScene::init();
    
    m_pScaleNode = HScaleWindow::create();
    addChild(m_pScaleNode);
    
    //if (CrossDelegate::isIphone5()) {
    if (isAddSlib) {
        CCSprite* left = HRichSprite::createWithSpriteFrame(_M("base_frame.jpg"));
        CCSize size = left->getContentSize();
        CCSize wholesize = this->getContentSize();
        float x = size.width - (wholesize.width-480.0)/2;
        left->setAnchorPoint(ccp(0, 0));
        left->setPosition(CCPointMake(x, 0));
        addChild(left, -1000);
        
        CCSprite* right = HRichSprite::createWithSpriteFrame(_M("base_frame.jpg"));
        right->setAnchorPoint(ccp(0, 0));
        right->setScaleX(-1);
        right->setPositionX(wholesize.width-x);
        addChild(right, -1000);
    }
    
    m_pGameNode = HGameWindow::create();
    m_pScaleNode->addChild(m_pGameNode, -2);
    
    m_pUINode = HUIWindow::create();
    m_pScaleNode->addChild(m_pUINode, 0);
    
    m_pTopNode = HTopWindow::create();
    m_pScaleNode->addChild(m_pTopNode, 998);
    m_pTopNode->onEnter();
    
    m_pLoading = HLoadingLayer2::create();
    m_pScaleNode->addChild(m_pLoading, 999);
    m_pLoading->setVisible(false);
    m_pLoading->onEnter();
    
    m_pMaskNode = HMaskWindow2::create();
//    m_pMaskNode = HMaskWindow::create();
    m_pScaleNode->addChild(m_pMaskNode, 1000);
    m_pMaskNode->setVisible(false);
    m_pMaskNode->onEnter();
    
    m_pRunningWindow = m_pGameNode;
    
    return true;
}

void HRootScene::visit()
{
    m_pMaskNode->beginMask();
    CCScene::visit();
}

void HRootScene::pressentGame(CCNode* game)
{
    m_pGameNode->addChild(game);
}

int getLastZOrder(CCNode* node)
{
    if (node->getChildrenCount() == 0) {
        return 0;
    }else{
        return ((CCNode*)node->getChildren()->lastObject())->getZOrder()+1;
    }
}

void HRootScene::dissmisAllWinodw(bool bAnima)
{
    stopAIV();
    
    if (m_pUINode->getChildrenCount() > 0) {
        for (int i=0; i<m_pUINode->getChildrenCount(); i++) {
            HWindow* node = (HWindow*)m_pUINode->getChildren()->objectAtIndex(i);
            if (m_bRunning && node->isRunning()) {
                node->onExitTransitionDidStart();
                node->onExit();
            }
        }
        
        m_pUINode->removeAllChildren();
        m_pRunningWindow = NULL;
        if (m_pGameNode->getChildrenCount() > 0) {
            m_pNextWindw = m_pGameNode;
            m_pNextWindw->setEnableAnimaInOut(bAnima);
        }
        
        
        setNextWindow();
    }
    
}

void HRootScene::presentWindow(HWindow* window, bool bAnima)
{
    CCLOG("HRootScene::presentWindow\t %s ==> %s", m_pRunningWindow ? m_pRunningWindow->getClass().c_str() : "...", window->getClass().c_str());
    
    m_pNextWindw = window;
    m_pNextWindw->setEnableAnimaInOut(bAnima);
    
    m_pUINode->addChild(m_pNextWindw, getLastZOrder(m_pUINode));
    m_pNextWindw->setVisible(false);
    m_bSendCleanupToWindow = false;
    
    FOREACH(HWindow*, wnd, m_pUINode->getChildren()){
        CCLOG("\t%s\t%d", wnd->getClass().c_str(), wnd->getZOrder());
    }
    
    setNextWindow();
    
    window->onPresented();
}

void HRootScene::replaceWindow(HWindow* window, bool bAnima)
{
    CCLOG("HRootScene::replaceWindow\t %s ==> %s", m_pRunningWindow->getClass().c_str(), window->getClass().c_str());
    
    m_pNextWindw = window;
    m_pNextWindw->setEnableAnimaInOut(bAnima);
    
    m_pUINode->addChild(m_pNextWindw, getLastZOrder(m_pUINode));
    m_pNextWindw->setVisible(false);
    m_bSendCleanupToWindow = true;
    
    FOREACH(HWindow*, wnd, m_pUINode->getChildren()){
        CCLOG("\t%s\t%d", wnd->getClass().c_str(), wnd->getZOrder());
    }
    
    setNextWindow();
    
    window->onPresented();
}

void HRootScene::dissmisWindow(HWindow* window, bool bAnima)
{
    CCLOG("HRootScene::dissmisWindow\t %s ==> %s", m_pRunningWindow->getClass().c_str(), window->getClass().c_str());
    stopAIV();
    
    if (window == m_pRunningWindow) {
        for (int i=m_pUINode->getChildrenCount()-1; i>0; i--) {
            if (m_pUINode->getChildren()->objectAtIndex(i) == m_pRunningWindow) {
                m_pNextWindw = (HWindow*)m_pUINode->getChildren()->objectAtIndex(i-1);
                break;
            }
        }
        
        if (m_pNextWindw == NULL && m_pGameNode->getChildrenCount() > 0) {
            m_pNextWindw = m_pGameNode;
        }
        
        if (m_pNextWindw == NULL) {
            CCDirector::sharedDirector()->replaceScene(PopLayer::scene(gfDurationFadeInOut));
        }else{
            m_pNextWindw->setEnableAnimaInOut(bAnima);
            m_bSendCleanupToWindow = true;
        }
    }else{
        if (m_bRunning && window->isRunning()) {
            window->onExitTransitionDidStart();
            window->onExit();
        }
        
        window->removeFromParent();
        this->updateAllWindows();
    }
    
    FOREACH(HWindow*, wnd, m_pUINode->getChildren()){
        CCLOG("\t%s\t%d", wnd->getClass().c_str(), wnd->getZOrder());
    }

    setNextWindow();
    
}

void HRootScene::setNextWindow()
{
    if (m_pNextWindw) {
        
        HWindow* runwnd = m_pRunningWindow;
        HWindow* nextwnd = m_pNextWindw;
        bool bclean = m_bSendCleanupToWindow;
        
        m_pRunningWindow = m_pNextWindw;
        m_pNextWindw = NULL;
        
        m_pMaskNode->maskWithInOut(nextwnd, runwnd, gfDurationFadeInOut, bclean);
    }
}

void HRootScene::presentDialog(HDialog* dlg, bool bAnima)
{
    presentDialog(m_pRunningWindow, dlg, bAnima);
}

void HRootScene::presentDialog(HWindow* parent, HDialog* dlg, bool bAnima)
{
    presentWindow(dlg, false);
}

void HRootScene::dissmisDialog(HDialog* dlg, bool bAnima)
{
    dissmisWindow(dlg, false);
}

void HRootScene::finish()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
}

void HRootScene::updateAllWindows(HWindow* outWnd)
{
    if (m_pRunningWindow->isDialog()) {
        int idx = 0;
        for (int i=m_pUINode->getChildrenCount()-1; i>=0; i--) {
            HWindow* wnd = (HWindow*)m_pUINode->getChildren()->objectAtIndex(i);
            if (wnd == m_pRunningWindow) {
                idx = i;
                break;
            }
        }
        
        for (int i=idx-1; i>=0; i--) {
            HWindow* wnd = (HWindow*)m_pUINode->getChildren()->objectAtIndex(i);
            if (!wnd->isDialog()) {
                wnd->setVisible(true);
                break;
            }
        }
        
        m_pGameNode->setVisible(idx == 0);
    }else{
        m_pGameNode->setVisible(false);
    }
}

void HRootScene::onEnter()
{
    s_pCurrentScene = this;
    
    this->resumeSchedulerAndActions();
    
    m_bRunning = true;
    
    if (m_pRunningWindow) {
        m_pRunningWindow->onEnter();
    }
}

void HRootScene::onEnterTransitionDidFinish()
{
    if (m_pRunningWindow) {
        m_pRunningWindow->onEnterTransitionDidFinish();
    }
}

void HRootScene::onExit()
{
    this->pauseSchedulerAndActions();
    
    m_bRunning = false;
    
    if (m_pRunningWindow) {
        m_pRunningWindow->onExit();
    }
}

void HRootScene::onExitTransitionDidStart()
{
    if (m_pRunningWindow) {
        m_pRunningWindow->onExitTransitionDidStart();
    }
}

void HRootScene::startAIV()
{
    m_pLoading->setVisible(true);
}

void HRootScene::stopAIV()
{
    m_pLoading->setVisible(false);
}


HWindow* HRootScene::currentWindowByType(const char* className)
{
    CCNode* uinode = HRootScene::current()->getUIShowLayer();
    for (int i=uinode->getChildrenCount()-1; i>=0; i--) {
        HWindow* wnd = (HWindow*)uinode->getChildren()->objectAtIndex(i);
        if (wnd->getClass() == className) {
            return wnd;
        }
    }
    
    CCNode* gamenode = HRootScene::current()->getGameShowLayer();
    for (int i=gamenode->getChildrenCount()-1; i>=0; i--) {
        HWindow* wnd = (HWindow*)gamenode->getChildren()->objectAtIndex(i);
        if (wnd->getClass() == className) {
            return wnd;
        }
    }
    
    return NULL;
}
