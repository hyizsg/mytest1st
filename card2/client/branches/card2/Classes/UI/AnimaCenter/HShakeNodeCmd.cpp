//
//  HShakeNodeCmd.cpp
//  card
//
//  Created by zhou gang on 13-5-9.
//
//

#include "../../headers.h"

HShakeNodeCmd::HShakeNodeCmd(CCNode* target, CMD_ARGS)
: HAnimaCommand(target, delegate, flag, duration)
{
    
}

HShakeNodeCmd::~HShakeNodeCmd()
{
    
}

HShakeNodeCmd* HShakeNodeCmd::create(CCNode* target, int times, float offx, float offy, CMD_ARGS)
{
    HShakeNodeCmd* cmd = new HShakeNodeCmd(target, delegate, flag, duration);
    cmd->m_offx = offx; cmd->m_offy = offy;
    cmd->m_times = times*2+1;
    cmd->autorelease();
    return cmd;
}

#define PI_2    (M_PI*0.5)

void HShakeNodeCmd::begin()
{
    HAnimaCommand::begin();
    
    m_rootChild = (CCNode*)getTarget()->getChildren()->objectAtIndex(0);
    
    m_beginx = m_rootChild->getPositionX();
    m_beginy = m_rootChild->getPositionY();
    
    
    float a = cosf((m_times % 4) * PI_2);
    
    m_endx = m_rootChild->getPositionX() + a * m_offx;
    m_endy = m_rootChild->getPositionY() + a * m_offy;
    
//    CCLog("(%f, %f)", m_endx, m_endy);
}

void HShakeNodeCmd::update(float delta)
{
    HAnimaCommand::update(delta);

    float x = lerp(m_beginx, m_endx);
    float y = lerp(m_beginy, m_endy);
    
    m_rootChild->setPosition(x, y);
    
    if (x == m_endx && y == m_endy) {
        m_times--;
        
        float a = cosf((m_times % 4) * PI_2);
        
        m_endx = m_beginx + a * m_offx;
        m_endy = m_beginy + a * m_offy;
        
//        CCLog("(%f, %f)", m_endx, m_endy);
        
    }
}

void HShakeNodeCmd::end()
{

    HAnimaCommand::end();
    
}

bool HShakeNodeCmd::isOver()
{
    return m_times <= 0;
}

