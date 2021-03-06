//
//  HLoginMainWindow.cpp
//  card2
//
//  Created by zhou gang on 14-2-13.
//
//

#include "headers.h"
#include "HLoginMainWindow.h"

HLoginMainWindow::HLoginMainWindow()
{
    
}

HLoginMainWindow::~HLoginMainWindow()
{
    
}

BEGIN_PLIST(HLoginMainWindow)

END_PLIST()

BEGIN_MEMBER_MAP(HLoginMainWindow)

END_MEMBER_MAP()

BEGIN_CLICK_MAP(HLoginMainWindow)
    CLICK(onAccountClick)
    CLICK(onWebClick)
    CLICK(onFakeAccountClick)
    CLICK(onFakeStartClick)
    CLICK(onFakeResetClick)
END_CLICK_MAP()


bool HLoginMainWindow::init()
{
    super::init();
    
    return true;
}

void HLoginMainWindow::onPresented()
{
    
}

void HLoginMainWindow::resetUI()
{
    
}

void HLoginMainWindow::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    HGameManager::getInstance()->login();
}

void HLoginMainWindow::onAccountClick(cocos2d::CCObject *sender, CCControlEvent event)
{
    
}

void HLoginMainWindow::onWebClick(cocos2d::CCObject *sender, CCControlEvent event)
{
    
}

void HLoginMainWindow::onFakeAccountClick(cocos2d::CCObject *sender, CCControlEvent event)
{
    
}

void HLoginMainWindow::onFakeStartClick(cocos2d::CCObject *sender, CCControlEvent event)
{
    HGameManager::getInstance()->fakeLogin();
}

void HLoginMainWindow::onFakeResetClick(cocos2d::CCObject *sender, CCControlEvent event)
{
    HGameManager::getInstance()->resetAccount();
}

void HLoginMainWindow::notifyActionMsg(cocos2d::CCObject *obj)
{
    
}
