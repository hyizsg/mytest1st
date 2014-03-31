//
//  HMoveNodeCmd.cpp
//  card
//
//  Created by zhou gang on 13-3-26.
//
//


#include "../../headers.h"

HMoveNodeCmd::HMoveNodeCmd(CCNode* target, CCNode* middle, CCNode* to, CMD_ARGS)
: HAnimaCommand(target, delegate, flag)
{
    m_middle = middle;
    m_to = to;
}

HMoveNodeCmd::~HMoveNodeCmd()
{
    
}

HMoveNodeCmd* HMoveNodeCmd::create(cocos2d::CCNode *target, cocos2d::CCNode *middle, cocos2d::CCNode *to, CMD_ARGS)
{
    HMoveNodeCmd* cmd = new HMoveNodeCmd(target, middle, to, delegate, flag, duration);
    if (cmd) {
        cmd->setDuration(duration);
        cmd->m_position = CCPointZero;
//        cmd->autorelease();
        CC_AUTO_RELEASE(cmd);
        return cmd;
    }
    return NULL;
}

HMoveNodeCmd* HMoveNodeCmd::create(CCNode* target, CCNode* middle, CCNode* to, const CCPoint& postion, CMD_ARGS)
{
    HMoveNodeCmd* cmd = create(target, middle, to, delegate, flag, duration);
    cmd->m_position = postion;
    return cmd;
}

void HMoveNodeCmd::begin()
{
    HAnimaCommand::begin();
    
//    m_duration = 12;
    
    if (dynamic_cast<HRootLayer*>(m_middle)) {
        m_middle = dynamic_cast<HRootLayer*>(m_middle)->getCCBNode();
    }
    
    if (m_to != NULL) {
        m_from_point = getTarget()->convertToWorldSpaceAR(CCPointZero);
        m_to_point = m_to->convertToWorldSpaceAR(m_position);
        
        m_rootChild = getTarget()->getChildrenCount() > 0 ? (CCNode*)getTarget()->getChildren()->objectAtIndex(0) : getTarget();
        m_rootChild->retain();
        m_rootChild->removeFromParentAndCleanup(false);
        m_middle->addChild(m_rootChild);
        
        m_from_point = m_middle->convertToNodeSpace(m_from_point);
        m_to_point = m_middle->convertToNodeSpace(m_to_point);
        
        m_rootChild->setPosition(m_from_point);
        
        if (getTarget() != m_rootChild) {
            getTarget()->removeFromParent();
            m_to->addChild(getTarget());
            
            getTarget()->setPosition(m_position);
        }
    }
}

void HMoveNodeCmd::update(float delta)
{
    HAnimaCommand::update(delta);
    
    CCPoint p = m_rootChild->getPosition();
    
    p.x = lerp(m_from_point.x, m_to_point.x);
    p.y = lerp(m_from_point.y, m_to_point.y);
    
    m_rootChild->setPosition(p);
    
}

void HMoveNodeCmd::end()
{
    if (m_middle != NULL) {
        m_rootChild->removeFromParent();
        getTarget()->addChild(m_rootChild);
        m_rootChild->setPosition(CCPointZero);
        m_rootChild->release();
    }
    
    HAnimaCommand::end();

}
