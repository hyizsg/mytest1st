//
//  HTransformCmd.cpp
//  card
//
//  Created by zhou gang on 13-4-2.
//
//



#include "../../headers.h"


HTransformCmd::HTransformCmd(CCNode* target, HAnimaDelegate* delegate, AnimaFlag flag, double duration)
: HAnimaCommand(target, delegate, flag, duration)
{
    
}

HTransformCmd* HTransformCmd::create(CCNode* target, float tx, float ty, int type, HAnimaDelegate* delegate, AnimaFlag flag, double duration)
{
    HTransformCmd* cmd = new HTransformCmd(target, delegate, flag, duration);
    cmd->m_type = type;
    cmd->m_target.x = tx;
    cmd->m_target.y = ty;
//    cmd->autorelease();
    CC_AUTO_RELEASE(cmd);
    return cmd;
}

#define IS(t) ((m_type & t) > 0)


void HTransformCmd::begin()
{
    HAnimaCommand::begin();
    
    if (IS(Translate)) {
        m_origin = getTarget()->getPosition();
        m_target.x += m_origin.x;
        m_target.y += m_origin.y;
    }else if (IS(Position)) {
        m_origin = getTarget()->getPosition();
    }else if (IS(Scale)){
        m_origin.x = getTarget()->getScaleX();
        m_origin.y = getTarget()->getScaleY();
    }else if (IS(Rotation)) {
        m_origin.x = getTarget()->getRotationX();
        m_origin.y = getTarget()->getRotationY();
    }else if (IS(Alpha)){
        CCRGBAProtocol* node = dynamic_cast<CCRGBAProtocol*>(getTarget());
        if (node) {
            m_origin.x = m_origin.y = node->getOpacity() / 255.0;
        }else{
            m_origin.x = m_origin.y = 1;
        }
    }
}

void HTransformCmd::update(float delta)
{
    HAnimaCommand::update(delta);
    
    float x = lerp(m_origin.x, m_target.x);
    float y = lerp(m_origin.y, m_target.y);
    
    if (IS(Translate)) {
        getTarget()->setPosition(x, y);
    }else if (IS(Scale)){
        getTarget()->setScaleX(x);
        getTarget()->setScaleY(y);
    }else if (IS(Rotation)) {
        getTarget()->setRotationX(x);
        getTarget()->setRotationY(y);
    }else if (IS(Alpha)){
        CCRGBAProtocol* node = dynamic_cast<CCRGBAProtocol*>(getTarget());
        if (node) {
            node->setOpacity(x * 255);
        }
    }
}




