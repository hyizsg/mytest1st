//
//  HNewbieAction.cpp
//  card
//
//  Created by zhou gang on 13-7-4.
//
//

#include "../../headers.h"
#include "HNewbieGuide.h"
#include "HNewbieAction.h"
#include "HGameConfig.h"

HGuideTipBox* HGuideTipBox::create(cocos2d::CCNode *node, const cocos2d::CCSize &exSize)
{
    HGuideTipBox* tip = new HGuideTipBox;
    CC_AUTO_RELEASE(tip);
    
    tip->flag = HNewbieGuide::GF_TipBox;
    tip->point = node->convertToWorldSpace(CENTER(node));
    tip->size = CCSizeMake(node->getContentSize().width * node->getScaleX() + exSize.width,
                           node->getContentSize().height * node->getScaleY() + exSize.height);
    
    return tip;
}

HGuideTipBox* HGuideTipBox::create(const cocos2d::CCSize &size, const cocos2d::CCPoint &point)
{
    HGuideTipBox* tip = new HGuideTipBox;
    CC_AUTO_RELEASE(tip);
    
    tip->size = size;
//    tip->point = HGameManager::scalePoint(point);
    tip->flag = HNewbieGuide::GF_TipBox;
    
    return tip;
}

HGuideArrow* HGuideArrow::create(cocos2d::CCNode *node, const cocos2d::CCSize &exSize)
{
    return create(CCSizeMake(node->getContentSize().width * node->getScaleX() + exSize.width,
                             node->getContentSize().height * node->getScaleY() + exSize.height) ,
                  node->convertToWorldSpace(CENTER(node)));
}

HGuideArrow* HGuideArrow::create(const cocos2d::CCSize &size, const cocos2d::CCPoint &point)
{
    HGuideArrow* tip = new HGuideArrow;
//    tip->autorelease();
    CC_AUTO_RELEASE(tip);
    
    tip->size = size;
    tip->point = point;
    tip->flag = HNewbieGuide::GF_Arrow;
    
    return tip;
}


void HGuideTipBoxDelegate::addTipBox(int chatIndex, HGuideTipBox *tip)
{
    if (m_tips == NULL) {
        m_tips = new CCDictionary;
    }
    
    if (m_tips->objectForKey(chatIndex) == NULL ) {
        m_tips->setObject(CCArray::create(), chatIndex);
    }
    
    CCArray* tipArr = PARSE_ARR(m_tips, chatIndex);
    tipArr->addObject(tip);
}

void HGuideTipBoxDelegate::addTipBox(int chatIndex, CCNode* node, const CCSize& exSize)
{
    addTipBox(chatIndex, HGuideTipBox::create(node, exSize));
}

void HGuideTipBoxDelegate::addTipArrow(int chatIndex, CCNode* node, const CCSize& exSize)
{
    addTipBox(chatIndex, HGuideArrow::create(node, exSize));
}

// -----------------------------------------

HGuideChat* HGuideChat::create(int beginStep, int endStep)
{
    HGuideChat* chat = new HGuideChat;
//    chat->autorelease();
    CC_AUTO_RELEASE(chat);
    chat->initWithNewbieStep(beginStep);
    chat->m_begin = beginStep;
    chat->m_end = endStep;
    chat->m_bAutoDone = false;
    return chat;
}

HGuideChat* HGuideChat::create(int beginStep, int endStep, HGuideTipBox* tip)
{
    HGuideChat* chat = create(beginStep, endStep);
    chat->addTipBox(beginStep, tip);
    return chat;
}

bool HGuideChat::init()
{
    m_content.id = 0;
    m_content.icon = 5010;
    m_content.msg = "这是一个测试，这是一个测试，这是一个测试，测试完毕。";
    
    m_isDone = false;
    m_tips = NULL;
    
    return true;
}

bool HGuideChat::initWithNewbieStep(int step)
{
    m_curStep = 0;
    m_pos = 0;
    m_isDone = false;
    m_tips = NULL;
    setNewbieStep(step);
    
    return true;
}

void HGuideChat::startWithTarget(CCNode *pTarget)
{
    CCAction::startWithTarget(pTarget);
    
    HNewbieGuide* guide = dynamic_cast<HNewbieGuide*>(pTarget);
    CCAssert(guide, "not a guide");
    
    if (guide) {
        m_chatDlg = guide->m_pChatDlg;
//        guide->showChatDlg(true);
        guide->clear();
        showChatByStep(m_begin);
    }
}

void HGuideChat::showChatByStep(int step)
{
    HNewbieGuide* guide = dynamic_cast<HNewbieGuide*>(getTarget());
    const vector<const HNewbie*> newbies = getNewbieById(guide->getTag());
    
    if (step <= m_end && step <= newbies.size()) {
        
        m_curStep = step;
        
        setNewbieStep(step);
        if (step > m_begin && step <= m_end) {
            guide->log(guide->getTag(), step-1);
        }
        
        const HNewbie* newbie = getNewbieById(guide->getTag())[step-1];
        
        m_pos = 0;
        m_delta = 0;
        m_content.msg = newbie->msg;
        
        if (newbie->icon >= 0) {
            m_chatDlg->icon[newbie->person]->setTextureBgThread(HPlayer::getIcon(newbie->icon));
            m_chatDlg->icon[newbie->person]->getParent()->setVisible(true);
            m_chatDlg->icon[1-newbie->person]->getParent()->setVisible(false);
        }
        
        if (m_content.msg == "0") {
            guide->showChatDlg(false);
        }else{
            guide->showChatDlg(true);
        }
        
        CCArray* tipArr = m_tips ? PARSE_ARR(m_tips, step) : NULL;
        if (tipArr) {
            HNewbieGuide* guide = dynamic_cast<HNewbieGuide*>(getTarget());
            guide->begin();
            {
                FOREACH(HGuideTipBox*, tip, tipArr){
                    guide->visit(tip->flag, tip->size.width, tip->size.height, tip->point);
                }
            }
            guide->end();
        }
        
    }else{
        m_isDone = true;
    }
}

bool HGuideChat::isDone()
{
    return m_isDone;
}

void HGuideChat::stop(void)
{
    HNewbieGuide* guide = dynamic_cast<HNewbieGuide*>(getTarget());
    
    CC_UNUSED_PARAM(guide);
    
    HNewbieAction::stop();
}

void HGuideChat::step(float dt)
{
    m_delta += dt;
    if (m_delta > 0.1) {
        m_delta = 0;
        
        string& str = m_content.msg;
        if (m_pos <= str.length()) {
            m_chatDlg->msg->setString(str.substr(0, m_pos).c_str());
            int len = 0;
            if ((str[m_pos] & 0x80) == 0) {
                len = 1;
            }
            else if((str[m_pos] & 0x20) == 0){
                len = 2;
            }
            else if((str[m_pos] & 0x10) == 0){
                len = 3;
            }
            else if((str[m_pos] & 0x08) == 0){
                len = 4;
            }
            
            CCLOG("[pos: %d, %d]: %s", m_pos, len, m_chatDlg->msg->getString());
            m_pos += len;
            
        }else if(m_bAutoDone){
            showChatByStep(m_curStep+1);
        }
    }
}

void HGuideChat::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_pos < m_content.msg.length()) {
        m_pos = m_content.msg.length();
    }else{
        showChatByStep(m_curStep+1);
    }
}


//*---------------------------

HGuideClick* HGuideClick::create(int step, cocos2d::CCNode *pClickTarget, const CCSize& exSize)
{
    HGuideClick* action = new HGuideClick;
//    action->autorelease();
    CC_AUTO_RELEASE(action);
    action->m_pClickTarget = pClickTarget;
    action->m_isDone = false;
    action->m_exSize = exSize;
    action->setNewbieStep(step);
    return action;
}

void HGuideClick::stop()
{
    HNewbieGuide* guide = dynamic_cast<HNewbieGuide*>(getTarget());
    guide->clear();
    m_pClickTarget = NULL;
    
    HNewbieAction::stop();
    
}

void HGuideClick::startWithTarget(cocos2d::CCNode *pTarget)
{
    CCAction::startWithTarget(pTarget);
    
    HNewbieGuide* guide = dynamic_cast<HNewbieGuide*>(pTarget);
    CCAssert(guide, "not a guide");
    
    if (guide) {
        guide->begin();
        {
            // 手
            guide->visit(HNewbieGuide::GF_Arrow, m_pClickTarget, m_exSize);
            
            // tip
            CCArray* tipArr = m_tips ? PARSE_ARR(m_tips, 0) : NULL;
            FOREACH(HGuideTipBox*, tip, tipArr){
                guide->visit(tip->flag, tip->size.width, tip->size.height, tip->point);
            }
        }
        guide->end();
        guide->showChatDlg(false);
    }
}


bool HGuideClick::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (isTouchInside(pTouch, m_pClickTarget)) {
        m_isDone = true;
        return false;
    }
    
    return true;
}

HGuideReward::HGuideReward()
{
    NOTIFY_ADD_OBSERVER(HGuideReward::notifyGuideReward, itoa(ACTION_NEWBIE_LOG));
}

HGuideReward::~HGuideReward()
{
    NOTIFY_REMOVE_OBSERVER(itoa(ACTION_NEWBIE_LOG));
}

HGuideReward* HGuideReward::create(int step)
{
    HGuideReward* reward = new HGuideReward;
//    reward->autorelease();
    CC_AUTO_RELEASE(reward);
    reward->m_isDone = false;
    reward->setNewbieStep(step);
    
    
    return reward;
}

void HGuideReward::startWithTarget(cocos2d::CCNode *pTarget)
{
    CCAction::startWithTarget(pTarget);
    
    HNewbieGuide* guide = dynamic_cast<HNewbieGuide*>(pTarget);
    CCAssert(guide, "not a guide");
    
    const HNewbie* newbie = getNewbieById(guide->getTag())[m_newbieStep-1];
    if (strcmp(newbie->reward, "0") != 0) {
        guide->clear();
        guide->showChatDlg(false);
        
        if (m_newbieStep != 1) {
            HNewbieGuide::logToSvr(guide->getTag(), m_newbieStep);
        }
        
        g_Game->getUILayer()->startAIV();
        
    }else{
        setNewbieStep(0);
        m_isDone = true;
    }
    
}

void HGuideReward::notifyGuideReward(CCObject* obj)
{
    HDataRequest* request = dynamic_cast<HDataRequest*>(obj);
    if (request && !request->isNotifyError()) {
        int tag = PARSE_INT(request->getResult(), "StepID");
        int step = PARSE_INT(request->getResult(), "ItemID");
        HNewbieGuide* guide = dynamic_cast<HNewbieGuide*>(getTarget());
        
        if (!guide) {
            return;
        }
        
        if (tag == guide->getTag() && step == m_newbieStep && step > 0 && tag > 0) {
            const HNewbie* newbie = getNewbieById(guide->getTag())[m_newbieStep-1];
            
            char tmp[64] = {0};
            strcpy(tmp, newbie->reward);
            
            vector<char*> sp = split(tmp, ",");
            vector<int> ids;
            vector<int> num;
            
            for (int i=0; i<sp.size(); i++) {
                vector<char*> p = split(sp[i], ";");
                ids.push_back(atoi(p[0]));
                num.push_back(atoi(p[1]));
            }
            
            for (int i=0; i<ids.size(); i++) {
                
                CCLabelTTF* label = CCLabelTTF::create("", "Arial-BoldMT", 15);
                label->setString(_T(ccLocalizedString("HNEWB_GOT"), HGameConfig::getInstance()->getItemName(ids[i]), num[i]));
                showReward(label, i);
                
            }
            
            NOTIFY_REMOVE_OBSERVER(itoa(ACTION_NEWBIE_LOG));
            setNewbieStep(0);
            m_isDone = true;
        }
    }
    
}

void HGuideReward::showReward(CCLabelTTF* label, int i)
{
//    HUIHelper::addToTopMost(label);
    label->setVisible(false);
    label->setPosition(CENTER(getTarget()));
    
    CCDelayTime* delay = CCDelayTime::create(i*0.4);
    CCShow* show = CCShow::create();
    CCMoveBy* move = CCMoveBy::create(0.5-i*0.1, ccp(0, 30-16*i));
    CCDelayTime* delay2 = CCDelayTime::create(1);
    CCFadeOut* fade = CCFadeOut::create(0.2);
    CCCallFunc* call = CCCallFunc::create(label, callfunc_selector(CCNode::removeFromParent));
    
    label->runAction(CCSequence::create(delay, show, move, delay2, fade, call, NULL));
}



