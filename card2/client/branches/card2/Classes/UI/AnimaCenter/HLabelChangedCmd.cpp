//
//  HLabelChangedCmd.cpp
//  card
//
//  Created by zhou gang on 13-3-26.
//
//

#include "../../headers.h"


HLabelChangedCmd::HLabelChangedCmd(CCNode* pTarget, int orgin_num, int target_num, const char* format, HAnimaDelegate* delegate)
: HAnimaCommand(pTarget, delegate)
{
    m_orgin_num = orgin_num;
    m_target_num = target_num;
    m_format = new CCString(format);
    m_flag = m_target_num > m_orgin_num ? 1 : -1;
}

HLabelChangedCmd::~HLabelChangedCmd()
{
    CC_SAFE_RELEASE(m_format);
}

HLabelChangedCmd* HLabelChangedCmd::create(cocos2d::CCNode *pTarget, int orgin_num, int target_num, const char *format, HAnimaDelegate* delegate, AnimaFlag flag)
{
    HLabelChangedCmd* cmd = new HLabelChangedCmd(pTarget, orgin_num, target_num, format, delegate);
    if (cmd) {
        cmd->setFlag(flag);
//        cmd->autorelease();
        CC_AUTO_RELEASE(cmd);
        return cmd;
    }
    return NULL;
}

void HLabelChangedCmd::begin()
{
    HAnimaCommand::begin();
    
    m_text_num = m_orgin_num;
}

void HLabelChangedCmd::update(float delta)
{
    HAnimaCommand::update(delta);
    
    CCLabelTTF* label = (CCLabelTTF*)getTarget();
    
    m_text_num = lerp(m_orgin_num, m_target_num);
    
    label->setString(_T(m_format->getCString(), (int)m_text_num));
}


// **********

HLabelChangel::HLabelChangel()
{
    m_format = NULL;
}

HLabelChangel::~HLabelChangel()
{
    CC_SAFE_RELEASE_NULL(m_format);
}

HLabelChangel* HLabelChangel::create(float dur, int org_num, int tar_num, const char *format)
{
    HLabelChangel* ac = new HLabelChangel;
    if (ac && ac->init(dur, org_num, tar_num, format)) {
        ac->autorelease();
        return ac;
    }
    return ac;
}

bool HLabelChangel::init(float dur, int org_num, int tar_num, const char *format)
{
    CCActionInterval::initWithDuration(dur);
    
    m_orgin_num = org_num;
    m_target_num = tar_num;
    m_format = new CCString(format);
    m_flag = m_target_num > m_orgin_num ? 1 : -1;
    
    return true;
}

void HLabelChangel::startWithTarget(cocos2d::CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_text_num = m_orgin_num;
}

void HLabelChangel::update(float dt)
{
    CCLabelTTF* label = (CCLabelTTF*)getTarget();
    m_text_num = lerp(m_orgin_num, m_target_num, dt);
//    CCLOG("%f",m_text_num);
    label->setString(_T(m_format->getCString(), (int)m_text_num));
}





