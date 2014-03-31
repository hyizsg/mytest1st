//
//  HLayerWithConfigButton.cpp
//  card
//
//  Created by zhou gang on 13-7-19.
//
//


#include "../../headers.h"
#include "HGameConfig.h"

HLayerWithConfigButton::HLayerWithConfigButton()
: m_pBtnCardGroup(NULL)
{
    NOTIFY_ADD_USERINFO();
}

HLayerWithConfigButton::~HLayerWithConfigButton()
{
    NOTIFY_REMOVE_USERINFO();
}

BEGIN_MEMBER_MAP(HLayerWithConfigButton)
    MEMBER(m_pBtnCardGroup)
END_MEMBER_MAP()


BEGIN_CLICK_MAP(HLayerWithConfigButton)
    CLICK(onCardGroupClick)
    CLICK(onAddActiveClick)
    CLICK(onShopClick)
END_CLICK_MAP()

void HLayerWithConfigButton::setTouchPriorityEx(CCNode* node)
{
    CCArray* child = node->getChildren();
    FOREACH(CCNode*, ch, child){
        CCControlButton* btn = dynamic_cast<CCControlButton*>(ch);
        if (btn) {
            btn->setTouchPriority(-100);
        }else if(ch->getChildrenCount() > 0) {
            setTouchPriorityEx(ch);
        }
    }
}

bool HLayerWithConfigButton::init()
{
    super::init();
    
    
    return true;
}

void HLayerWithConfigButton::onEnter()
{
//    HUIHelper::setCardConfigButton(m_pBtnCardGroup);
    super::onEnter();
    
//    if (HGameConfig::getInstance()->getIntValue(EB_CardGroup+kShiningKey)) {
//        play_shine2(m_pBtnCardGroup, 1);
//    }else{
//        m_pBtnCardGroup->removeChildByTag(kShiningTag);
//    }
}

void HLayerWithConfigButton::notifyUserInfo(cocos2d::CCObject *obj)
{
//    HUIHelper::setCardConfigButton(m_pBtnCardGroup);
//    if (HGameConfig::getInstance()->getIntValue(EB_CardGroup+kShiningKey)) {
//        play_shine2(m_pBtnCardGroup, 1);
//    }else{
//        m_pBtnCardGroup->removeChildByTag(kShiningTag);
//    }
}

void HLayerWithConfigButton::onCardGroupClick(cocos2d::CCObject *sender, CCControlEvent event)
{
//    HGameConfig::getInstance()->setConfig(EB_CardGroup+kShiningKey, 0);
//    
//    HGameManager::getInstance()->playSoundEffect(HMUSIC_BUTTON);
//    HConfigMainWindow* config = HConfigMainWindow::create();
//    config->presentRootLayer();
}

void HLayerWithConfigButton::onShopClick(cocos2d::CCObject *sender, CCControlEvent event)
{
//    HGameManager::getInstance()->playSoundEffect(HMUSIC_BUTTON);
//    HShopMain* shop = HShopMain::create();
//    shop->presentRootLayer();
}

void HLayerWithConfigButton::onAddActiveClick(cocos2d::CCObject *sender, CCControlEvent event)
{
//    HGameManager::getInstance()->playSoundEffect(HMUSIC_BUTTON);
//    HCommonErrorProcess::getInstance()->AddEnergy();
}


// ***************

HLayerWithTabButton::HLayerWithTabButton()
: m_pGroupNode(NULL)
, m_nSelectTabIndex(0)
{
    
}

HLayerWithTabButton::~HLayerWithTabButton()
{
    
}

bool HLayerWithTabButton::init()
{
    super::init();
    
    setCurrentTabIndex(0);
    
    return true;
}


BEGIN_MEMBER_MAP(HLayerWithTabButton)
    MEMBER(m_pGroupNode)
END_MEMBER_MAP()


BEGIN_CLICK_MAP(HLayerWithTabButton)
    CLICK(onBtnTabClick)
END_CLICK_MAP()

void HLayerWithTabButton::resetUI()
{
    
}

CCControlButton* HLayerWithTabButton::getCurrentTab()
{
    return getTabByIndex(m_nSelectTabIndex);
}

CCControlButton* HLayerWithTabButton::getTabByIndex(int idx)
{
    return (CCControlButton*)m_pGroupNode->getChildren()->objectAtIndex(idx);;
}

void HLayerWithTabButton::setCurrentTabIndex(int idx)
{
    int oldIdx = m_nSelectTabIndex;
    m_nSelectTabIndex = idx;
    
    CCControlButton* sender = (CCControlButton*)m_pGroupNode->getChildren()->objectAtIndex(idx);
    if (!onTabButtonChanged(sender, idx)) {
        m_nSelectTabIndex = oldIdx;
        return;
    }
    
    if (m_pGroupNode) {
        for (int i=0; i<m_pGroupNode->getChildrenCount(); i++) {
            CCControlButton* btn = (CCControlButton*)m_pGroupNode->getChildren()->objectAtIndex(i);
            btn->setEnabled(m_nSelectTabIndex != i);
        }
    }
}

void HLayerWithTabButton::onBtnTabClick(cocos2d::CCObject *sender, CCControlEvent event)
{
    playButtonSound();
    
    int tag = ((CCNode*)sender)->getTag();
    setCurrentTabIndex(tag);
    
}

