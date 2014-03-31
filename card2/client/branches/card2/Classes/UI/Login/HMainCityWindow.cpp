//
//  HMainCityWindow.cpp
//  card2
//
//  Created by zhou gang on 14-2-13.
//
//

#include "headers.h"
#include "HMainCityWindow.h"

HMainCityWindow::HMainCityWindow()
{
    
}

HMainCityWindow::~HMainCityWindow()
{
    
}

BEGIN_PLIST(HMainCityWindow)

END_PLIST()

BEGIN_MEMBER_MAP(HMainCityWindow)
    MEMBER(m_pBg)
END_MEMBER_MAP()

BEGIN_CLICK_MAP(HMainCityWindow)

END_CLICK_MAP()


bool HMainCityWindow::init()
{
    super::init();
    
    m_pBg->setTextureBgThread("game/img/zjm_bg.jpg");
    
    return true;
}

void HMainCityWindow::onPresented()
{
    
}

void HMainCityWindow::resetUI()
{
    
}

void HMainCityWindow::notifyActionMsg(CCObject* obj)
{
    
}

