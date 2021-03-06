﻿//
//  HNewbieGuide.cpp
//  card
//
//  Created by zhou gang on 13-7-3.
//
//


#include "headers.h"
#include "HNewbieGuide.h"
#include "HPlayerGuide.h"
#include "HMaskedSprite.h"
#include "HNewbieAction.h"
#include "HGameConfig.h"

HNewbieGuide::HNewbieLog HNewbieGuide::s_newbieLog;
HNewbieGuide* HNewbieGuide::s_newbieSingle = NULL;

HNewbieGuide::HNewbieGuide()
: m_pMask(NULL)
, m_pTarget(NULL)
, m_pArrow(NULL)
, m_pBackgrd(NULL)
, m_pActions(new CCArray)
{
    
    
}

HNewbieGuide::~HNewbieGuide()
{
    
    CC_SAFE_RELEASE_NULL(m_pActions);
    CC_SAFE_RELEASE_NULL(m_pBackgrd);
    CC_SAFE_RELEASE_NULL(m_pTarget);
    CC_SAFE_RELEASE_NULL(m_pArrow);
}

BEGIN_PLIST(HNewbieGuide)

END_PLIST()

BEGIN_MEMBER_MAP(HNewbieGuide)
    MEMBER(m_pBackgrd)
    MEMBER(m_pChatDlg)
    MEMBER(m_pBtnSkip)
    MEMBER(m_pMask)
    MEMBER(m_pArrow)
    MEMBER(m_pTipBox)
    MEMBER(m_pTipMask)
    MEMBER(m_pChatDlg->iconLeft)
    MEMBER(m_pChatDlg->iconRight)
    MEMBER(m_pChatDlg->msg)
END_MEMBER_MAP()

BEGIN_CLICK_MAP(HNewbieGuide)
    CLICK(onSkipClick)
END_CLICK_MAP()

string chat[] = {
    "你说什么呀？",
    "今天天气不错呦～～",
    "要下雨了，回家收衣服吧！",
    "。。。"
};

HNewbieGuide* HNewbieGuide::create(int tag, int step, HNewbieGuideDelegate* delegate)
{

//    return NULL;
    
    if (isPass(tag, step)) {
        return NULL;
    }
    
    if (s_newbieSingle == NULL) {
        s_newbieSingle = create();
        s_newbieSingle->retain();
    }
    
    if (s_newbieSingle->getParent() != NULL) {
        return NULL;
    }
    
    HNewbieGuide* guide = s_newbieSingle; //create();
    guide->setTag(tag);
    guide->m_delegate = delegate;
    guide->m_pActions->removeAllObjects();
    guide->stopAllActions();
    
    log(tag);
    
    
    return guide;
}

bool HNewbieGuide::loadLog()
{
    
    return true;
}

void HNewbieGuide::updateLog(CCArray* array)
{
    
    vector<int> logs;
    ccarray2vector(logs, array);
    
    map<int, vector<const HNewbie* > >::iterator it = HNewbie::newbies.begin();
    for (; it!=HNewbie::newbies.end(); it++) {
        bool inlocal = isPass(it->first);
        bool inserver = exist(logs, it->first);
        if (inserver && !inlocal) {
            log(it->first);
        }else if(inlocal && !inserver){
            logToSvr(it->first, 1);
        }
    }
    
    reset();
    
}

void HNewbieGuide::reset()
{
    s_newbieLog.id = 0;
    s_newbieLog.step.clear();
}

void HNewbieGuide::log(int tag)
{
    log(tag, 0);
    HGameConfig::getInstance()->setConfig(tag, "1");
}

void HNewbieGuide::log(int tag, int step)
{    
    if (s_newbieLog.id != tag) {
        s_newbieLog.id = tag;
        s_newbieLog.step.clear();
    }
    if (step != 0) {
        s_newbieLog.step.push_back(step);
    }
    
    CCLOG("HNewbieGuide::log: %d\tcount: %lu", s_newbieLog.id, s_newbieLog.step.size());
    for (int i=0; i<s_newbieLog.step.size(); i++) {
        CCLOG("\t\tstep: %d", s_newbieLog.step[i]);
    }
    
    if (step == 1) {
        logToSvr(tag, step);
    }
}

void HNewbieGuide::logToSvr(int tag, int step)
{
    CCDictionary* param = CCDictionary::create();
    param->setObject(HString::createWithInteger(tag), "StepID");
    param->setObject(HString::createWithInteger(step), "ItemID");
    HDataCenter::post(HDataRequest::create(ACTION_NEWBIE_LOG, param));
    HGameManager::getInstance()->getUILayer()->stopAIV();
    
}

bool HNewbieGuide::isPass(int tag)
{
    return tag == 0 || HGameConfig::getInstance()->getIntValue(tag);
}

bool HNewbieGuide::isPass(int tag, int step)
{
    if (s_newbieLog.id == tag) {
        return exist(s_newbieLog.step, step);
    }else{
        return isPass(tag);
    }
}


bool HNewbieGuide::isRuning()
{
    return s_newbieSingle && s_newbieSingle->getParent();
}

bool HNewbieGuide::init()
{
    super::init();
    
    m_pBackgrd->retain();
    m_pArrow->retain();
    m_pArrow->removeFromParent();
    
    
      
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pTarget = CCRenderTexture::create(s.width, s.height);
    m_pTarget->retain();
    ccBlendFunc ccb1 = {GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};
    m_pTarget->getSprite()->setBlendFunc(ccb1);
    
     
    
    m_pTarget->setPosition(ccp(s.width/2,s.height/2));
    
    // 加快第一次渲染的速度
    m_pTarget->visit();
    
    setTouchPriority(-500);
    m_bTouchEnabled = true;
    m_pBtnSkip->setTouchPriority(-501);
    
    m_pChatDlg->msg->setString("");
    
    clear();
    m_pBtnSkip->setVisible(false);
    
    return true;
}

void HNewbieGuide::showIn(HRootLayer* parent)
{
    if (parent) {
        parent->addChild(this);
    }else{
        this->presentRootLayer(false);
    }
    
    setOpacity(0);
    
    m_pChatDlg->setPositionY(-100);
    m_pChatDlg->msg->setString("");
    pauseSchedulerAndActions();
    
    HAnimaCenter::play(HTransformCmd::create(this, 1, 1, HTransformCmd::Alpha, this));
}

void HNewbieGuide::hidden()
{
    if (!isAnimaing()) {
        stopAllActions();
        m_pActions->removeAllObjects();
        HAnimaCenter::play(HTransformCmd::create(this, 0, 0, HTransformCmd::Alpha, this));
    }
}

void HNewbieGuide::onExit()
{
    super::onExit();
}

void HNewbieGuide::hiddenAfterActionWithoutAnima()
{
    runAction(CCCallFunc::create(this, callfunc_selector(HNewbieGuide::removeFromParent)));
}

void HNewbieGuide::hiddenInActionWithoutAnima()
{
    runAction(HCallFuncI::create(this, callfuncI_selector(HNewbieGuide::removeFromParentAndCleanup), false));
}

CCAction* HNewbieGuide::runAction(CCAction* action)
{
    action->setTag(kNewbieActionTag);
    
    if (getActionByTag(kNewbieActionTag)) {
        m_pActions->addObject(action);
    }else{
        super::runAction(action);
        if (dynamic_cast<HNewbieAction*>(action) == NULL) {
            CCCallFuncO* call = CCCallFuncO::create(this, callfuncO_selector(HNewbieGuide::onNewbieActionEnd), action);
            super::runAction(call);
        }
    }
    
    return action;
}

void HNewbieGuide::onNewbieActionEnd(CCAction* action)
{
    if(dynamic_cast<HNewbieAction*>(action)){
        log(getTag(), dynamic_cast<HNewbieAction*>(action)->getNewbieStep());
    }
    
    if (m_pActions->count() > 0) {
        action = super::runAction((CCAction*)m_pActions->objectAtIndex(0));
        m_pActions->removeObjectAtIndex(0);
        
        if (dynamic_cast<HNewbieAction*>(action) == NULL) {
            CCCallFuncO* call = CCCallFuncO::create(this, callfuncO_selector(HNewbieGuide::onNewbieActionEnd), action);
            super::runAction(call);
        }
        
    }else{
        if(getParent()) {hidden();};
        if (m_delegate) {
            m_delegate->onNewbieGuideEnd(getTag(), this);
        }
    }
}

bool HNewbieGuide::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCTouchDelegate* action = dynamic_cast<CCTouchDelegate*>(getActionByTag(kNewbieActionTag));
   
    if (action) {
        return  action->ccTouchBegan(pTouch, pEvent);
    }
    
    return super::ccTouchBegan(pTouch, pEvent);
}

void HNewbieGuide::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    HNewbieAction* action = dynamic_cast<HNewbieAction*>(getActionByTag(kNewbieActionTag));
    
    if (action) {
        action->ccTouchEnded(pTouch, pEvent);
    }
}

void HNewbieGuide::showChatDlg(bool bShow)
{
    CCMoveTo* move = CCMoveTo::create(0.3, ccp(0, bShow ? 0 : -100));
    m_pChatDlg->stopAllActions();
    m_pChatDlg->runAction(move);
}

void HNewbieGuide::onAnimaEnd(HAnimaCommand* cmd)
{
    HTransformCmd* tCmd = (HTransformCmd*)cmd;
    if (tCmd->m_target.x < 0.2) {
        removeFromParent();
    }else{
        resumeSchedulerAndActions();
        if(m_pArrow) m_pArrow->resumeSchedulerAndActions();
    }
}

void HNewbieGuide::onSkipClick(cocos2d::CCObject *sender, CCControlEvent event)
{
    HGameManager::getInstance()->playSoundEffect(HMUSIC_BUTTON);
    reset();
    hidden();
}

void HNewbieGuide::begin()
{
    if (m_pTarget->getParent() == NULL) {        
        this->addChild(m_pTarget, -1);
        m_pTarget->getSprite()->setOpacity(255);
    }
    
    m_pTarget->clear(0.0f, 0.0f, 0.0f, 0.4f);
    m_pTarget->begin();

}

void HNewbieGuide::end()
{
    m_pTarget->end();
    m_pBackgrd->removeFromParent();
}

void HNewbieGuide::clear()
{
    m_pArrow->removeFromParent();
    
    begin();
    end();
}

void HNewbieGuide::visit(HGuideFlag flag, CCNode* node, const CCSize& exSize)
{
    visit(flag, exSize.width + node->getContentSize().width,
          exSize.height + node->getContentSize().height,
          node->convertToWorldSpace(CENTER(node)));
}

void HNewbieGuide::visit(HGuideFlag flag, float width,float height,CCPoint point)
{
    if (flag == GF_Arrow) {
        m_pMask->setPosition(point);
        m_pMask->setScaleX(width / 68.f);
        m_pMask->setScaleY(height / 68.f);
        m_pMask->setOpacity(255);
        m_pMask->visit();
        
        
        if (m_pArrow->getParent() == NULL) {
            CCMoveBy* move1 = CCMoveBy::create(0.3, ccp(0, 10));
            CCMoveBy* move2 = CCMoveBy::create(0.3, ccp(0, -10));
            CCRepeatForever* repeate = CCRepeatForever::create((CCSequence*)CCSequence::create(move1, move2, NULL));
            this->addChild(m_pArrow);
            m_pArrow->runAction(repeate);
        }
        
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        bool down = point.y < size.height/2 ? true : false;
        
        m_pArrow->setScaleX(0.6);
        m_pArrow->setScaleY((down ? 0.7 : -0.7));
        m_pArrow->setPosition(ccpAdd(point, ccp(0, down ? 15 : -15)));
        m_pArrow->setOpacity(255);
        
    }else if(flag == GF_TipBox){
        m_pTipBox->setOpacity(255);
        m_pTipBox->setPosition(point);
        m_pTipBox->setContentSize(CCSizeMake(width+2, height+2));
        m_pTipBox->visit();
        
        m_pTipMask->setOpacity(255);
        m_pTipMask->setPosition(point);
        m_pTipMask->setContentSize(CCSizeMake(width, height));
        m_pTipMask->visit();
    }
}
