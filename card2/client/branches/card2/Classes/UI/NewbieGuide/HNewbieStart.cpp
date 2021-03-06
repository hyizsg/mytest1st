﻿//
//  HNewbieStart.cpp
//  card
//
//  Created by zhou gang on 13-7-25.
//
//

#include "../../headers.h"
#include "HNewbieStart.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

HNewbieStart::HNewbieStart()
: HNewbieGuide()
, m_selectIndex(0)
{
//    INIT_PLISTS_CCBI(ccbi);
}

HNewbieStart::~HNewbieStart()
{
//    DISPOSE_PLISTS();
}

BEGIN_PLIST(HNewbieStart)
    PLIST(ingame960)
    PLIST(cardstrong960)
END_PLIST()

BEGIN_MEMBER_MAP(HNewbieStart)
    MEMBER(m_pMaskLayer)
    MEMBER(m_pIcon)
    MEMBER(m_pLightBg)
    MEMBER(m_pSelectIconNode)
    MEMBER(m_pGuideNode)
    MEMBER(m_pGuideBg)
    MEMBER(m_pLastTipInfo)
    MEMBER(m_pSelectBtn)
END_MEMBER_MAP()

BEGIN_CLICK_MAP(HNewbieStart)
    CLICK(onOKClick)
    CLICK(onSelectIconClick)
END_CLICK_MAP()

bool HNewbieStart::init()
{
    super::super::init();
    m_bTouchEnabled = true;
    
    m_pGuideNode->setVisible(false);
    m_pMaskLayer->setVisible(false);
    m_pSelectIconNode->setVisible(true);
    m_pLastTipInfo->setVisible(false);
    
    m_pIcon[0]->setTexture(_U(HPlayer::getIcon(6006)));
    m_pIcon[1]->setTexture(_U(HPlayer::getIcon(6007)));
    
//    HUIHelper::adjustScale(m_pIcon[0]);
//    HUIHelper::adjustScale(m_pIcon[1]);
//    HUIHelper::adjustScale(m_pGuideBg);
    
    addObserver(callfuncO_selector(HNewbieStart::notifySaveIcon), ACTION_SETTING_ORIGINICON);
    addObserver(callfuncO_selector(HNewbieStart::notifyReplaylRequest), ACTION_REPLAY_LEVEL+1);
    
    
    log(401);
    
    setTag(401);
    
    
    setTouchPriority(-500);
    
    for (int i=0; i<3; i++) {
        m_pSelectBtn[i]->setTouchPriority(-501);
    }
    
    return true;
}

void HNewbieStart::onOKClick(cocos2d::CCObject *sender, CCControlEvent event)
{
    // save icon
    CCDictionary* param = CCDictionary::create();
    param->setObject(HString::createWithInteger(6006+m_selectIndex), "Guide");
    
    HDataCenter::post(HDataRequest::create(ACTION_SETTING_ORIGINICON, param));
    
}

void HNewbieStart::onSelectIconClick(cocos2d::CCObject *sender, CCControlEvent event)
{
    m_selectIndex = ((CCControlButton*)(sender))->getTag();
    m_pLightBg->setPositionX(152 + 90 * m_selectIndex);
    
}

void HNewbieStart::notifySaveIcon(CCObject * obj)
{
    HDataRequest* requset = dynamic_cast<HDataRequest*>(obj);
    if (requset && !requset->isNotifyError())
    {
        setTag(402);
        log(402);
//        beginMaskToGuide(0);
        beginMaskToStory();
        setTouchPriority(-500);
        
        for (int i=0; i<3; i++) {
            m_pSelectBtn[i]->setTouchPriority(0);
        }
    }
}

void HNewbieStart::notifyReplaylRequest(CCObject* obj)
{
    HDataRequest* request = dynamic_cast<HDataRequest*>(obj);
    if (request && !request->isNotifyError()) {
        
        HBattleController::getInstance()->startBattle(request->getResult(), true);
        
        CCDelayTime* delay = CCDelayTime::create(20);
        CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HNewbieStart::onBattleDelay));
        m_pGuideBg->runAction(CCSequence::create(delay, call, NULL));
        
    }else{
        HLoadingWindow::getInstance()->end();
        hidden();
    }
}

void HNewbieStart::showChatDlg(bool bShow)
{
    m_pChatDlg->setVisible(bShow);
}

void HNewbieStart::beginMaskToStory()
{
    m_pMaskLayer->setOpacity(0);
    m_pMaskLayer->setVisible(true);
    
    CCFadeIn* fadeIn = CCFadeIn::create(0.3);
    CCCallFunc* call1 = CCCallFunc::create(this, callfunc_selector(HNewbieStart::onMaskFadeInStroy));
    CCFadeOut* fadeOut = CCFadeOut::create(0.2);
    CCCallFunc* call2= CCCallFunc::create(this, callfunc_selector(HNewbieStart::onMaskFadeOutStroy));
    
    m_pMaskLayer->runAction(CCSequence::create(fadeIn, call1, fadeOut, call2, NULL));
}

void HNewbieStart::onMaskFadeInStroy()
{
    if (m_pSelectIconNode) {
        m_pSelectIconNode->removeFromParent();
        m_pSelectIconNode = NULL;
    }
    
    m_pGuideNode->setVisible(true);
    m_pChatDlg->msg->setString("");
    m_pGuideBg->setVisible(false);
    
    HEffectHelper* effect = HEffectHelper::create("game/story.chr");
    HpCharaInst* story = effect->playEffect("story", m_pGuideNode, CENTER(getCCBNode()));
    story->setDelegate(this);
    story->setZOrder(-1);
}

void HNewbieStart::onMaskFadeOutStroy()
{

}

void HNewbieStart::beginMaskToReplay()
{
    m_pMaskLayer->setOpacity(0);
    m_pMaskLayer->setVisible(true);
    
    
    m_pChatDlg->msg->setString("");
    
    CCFadeIn* fadeIn = CCFadeIn::create(0.0);
    CCCallFunc* call1 = CCCallFunc::create(this, callfunc_selector(HNewbieStart::onMaskFadeInReplay));
    CCFadeOut* fadeOut = CCFadeOut::create(0.0);
    CCCallFunc* call2= CCCallFunc::create(this, callfunc_selector(HNewbieStart::onMaskFadeOutReplay));
    
    m_pMaskLayer->runAction(CCSequence::create(fadeIn, call1, fadeOut, call2, NULL));
}

void HNewbieStart::onMaskFadeInReplay()
{
    HEffectHelper* effect = HEffectHelper::create("game/effects_luxiang4.chr");
    effect->playEffect("zzz_luxiang", m_pGuideNode, CENTER(getCCBNode()))->setDelegate(this);
    
    g_Game->playMusic(HMUSIC_BATTLE_BOSS);
}

void HNewbieStart::onMaskFadeOutReplay()
{
    
}

void HNewbieStart::actionOnAnimationEnd(HpAnimation* p_ani, HpCharaInst* p_sender)
{
    if (p_sender->getCurrentAnimationName()->m_sString == "story"){
        
        beginMaskToReplay();
        
    }else if(p_sender->getCurrentAnimationName()->m_sString == "zzz_luxiang"){
        
        m_pMaskLayer->setOpacity(0);
        m_pMaskLayer->setVisible(true);
        
        CCFadeIn* fadeIn = CCFadeIn::create(0.2);
        CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HNewbieStart::onBattleFadeEnd));
        
        m_pMaskLayer->runAction(CCSequence::create(fadeIn, call, NULL));
    }
}

void HNewbieStart::actionOnCustomEvent(CCString* p_event, HpCharaInst* p_sender)
{
    m_pChatDlg->setVisible(true);
    m_pChatDlg->setPosition(ccp(0, 0));
    
    m_pChatDlg->msg->setOpacity(0);
    m_pChatDlg->msg->runAction(CCFadeIn::create(0.2));
    
    if (p_event->m_sString == "story_word1") {
        const HNewbie* newbie = getNewbieById(getTag())[0];
        m_pChatDlg->msg->setString(newbie->msg);
    }else if(p_event->m_sString == "story_word2"){
        const HNewbie* newbie = getNewbieById(getTag())[1];
        m_pChatDlg->msg->setString(newbie->msg);
    }else if(p_event->m_sString == "story_word3"){
        const HNewbie* newbie = getNewbieById(getTag())[2];
        m_pChatDlg->msg->setString(newbie->msg);
    }else if(p_event->m_sString == "story_word4"){
        const HNewbie* newbie = getNewbieById(getTag())[3];
        m_pChatDlg->msg->setString(newbie->msg);
    }else if(p_event->m_sString == "105"){
        g_Game->playMusic(HMUSIC_REPLAY);
    }else{
//        HUIHelper::getInstance()->actionOnCustomEvent(p_event, p_sender);
    }
}

void HNewbieStart::beginMaskToGuide(int idx)
{
    m_selectIndex = idx;
    
    m_pMaskLayer->setOpacity(0);
    m_pMaskLayer->setVisible(true);
    
    CCFadeIn* fadeIn = CCFadeIn::create(0.3);
    CCCallFunc* call1 = CCCallFunc::create(this, callfunc_selector(HNewbieStart::onMaskFadeInEnd));
    CCFadeOut* fadeOut = CCFadeOut::create(0.3);
    CCCallFunc* call2= CCCallFunc::create(this, callfunc_selector(HNewbieStart::onMaskFadeOutEnd));
    
    m_pMaskLayer->runAction(CCSequence::create(fadeIn, call1, fadeOut, call2, NULL));
}

void HNewbieStart::onMaskFadeInEnd()
{
    if (m_pSelectIconNode) {
        m_pSelectIconNode->removeFromParent();
        m_pSelectIconNode = NULL;
    }   
    
    m_pGuideNode->setVisible(true);
    m_pChatDlg->msg->setString("");
    
    m_pGuideBg->setTextureBgThread(_T("game/img/sg_00%d.jpg", m_selectIndex+1));

}

void HNewbieStart::onMaskFadeOutEnd()
{
    m_pMaskLayer->setVisible(false);
    
    if (m_selectIndex < 4) {
        runAction(HGuideChat::create(m_selectIndex+1, m_selectIndex+1));
        m_pChatDlg->setPositionY(0);
    }else{
        
        onBattleFadeEnd();
        return;
        
        HLoadingWindow::getInstance()->start();

        CCDictionary* param = CCDictionary::create();
        param->setObject(HString::createWithInteger(0), "PID");
        param->setObject(HString::createWithInteger(99999), "MapID");
        HDataCenter::post(HDataRequest::create(ACTION_REPLAY_LEVEL+1, param));
    }
    
}

void HNewbieStart::onNewbieActionEnd(CCAction* action)
{
    CCDelayTime* delay = CCDelayTime::create(0.5);
    HCallFuncI* call = HCallFuncI::create(this, callfuncI_selector(HNewbieStart::beginMaskToGuide), m_selectIndex+1);
    
    m_pGuideBg->runAction(CCSequence::create(delay, call, NULL));
}

void HNewbieStart::onBattleDelay()
{
    log(getTag(), 5);
    
    HBattleController::getInstance()->getBattleWnd()->onExit();
    
    HRootLayer* layer = new HRootLayer;
//    HUIHelper::addChild(layer, m_pMaskLayer);
    layer->setDisableAnimInOut(true);
    layer->setIsFullScreen(false);
    layer->presentRootLayer();
    
    m_pMaskLayer->setOpacity(0);
    m_pMaskLayer->setVisible(true);
    
    CCFadeIn* fadeIn = CCFadeIn::create(2);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HNewbieStart::onBattleFadeEnd));
    
    m_pMaskLayer->runAction(CCSequence::create(fadeIn, call, NULL));
}

void HNewbieStart::onBattleFadeEnd()
{
    HWindow* bat = HBattleController::getInstance()->getBattleWnd();
    if(bat){
        bat->dismissRootLayer(false);
    }
    
    m_pMaskLayer->setVisible(false);
    
    m_pLastTipInfo->onEnter();
    m_pLastTipInfo->setString(getNewbieById(getTag())[5]->msg);
    m_pLastTipInfo->setVisible(true);
    m_pLastTipInfo->setOpacity(50);
    m_pLastTipInfo->setScale(0.2);
    
    CCScaleTo* scale = CCScaleTo::create(0.3, 1);
    CCFadeTo* fade = CCFadeTo::create(0.3, 255);
    CCDelayTime* delay = CCDelayTime::create(2);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HNewbieStart::onLastInfoShowEnd));
    
    m_pLastTipInfo->runAction(CCSequence::create(
                                                 CCEaseOut::create((CCSpawn*)CCSpawn::create(scale, fade, NULL), 0.3),
                                                 delay, call, NULL));
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
}

void HNewbieStart::onLastInfoShowEnd()
{
    if (!isAnimaing()) {
        
        log(getTag(), 6);
        
        stopAllActions();
        m_pActions->removeAllObjects();
        HAnimaCenter::play(HTransformCmd::create(this, 0, 0, HTransformCmd::Alpha, this, AF_None, 0.5));
    }
}

void HNewbieStart::onAnimaEnd(HAnimaCommand* cmd)
{
    HTransformCmd* tCmd = (HTransformCmd*)cmd;
    
    if (tCmd->m_target.x < 0.2) {
//        HRootLayer* layer = dynamic_cast<HRootLayer*>(m_pMaskLayer->getParent()); ;
//        if(layer) {
//            layer->dismissRootLayer();
//            this->removeFromParent();
//        }else {
//            this->dismissRootLayer();
//        }
        this->dismissRootLayer();
//        g_Game->playMusic(g_Game->getBackGroundMusicID());
    }else{
        
        super::onAnimaEnd(cmd);
    }
}

