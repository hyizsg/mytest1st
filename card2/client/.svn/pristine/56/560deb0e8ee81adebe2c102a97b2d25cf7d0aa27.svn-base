//
//  HAnimaCenter.cpp
//  card
//
//  Created by zhou gang on 13-3-26.
//
//

#include "../../headers.h"

HSINGLETON_OBJECT_IMP(HAnimaCenter);


HAnimaCenter::HAnimaCenter()
: m_cmd_cache(NULL)
, m_timer(NULL)
{
    m_cmd_cache = new CCArray();
    this->schedule(schedule_selector(HAnimaCenter::update));
}

HAnimaCenter::~HAnimaCenter()
{
    this->unschedule(schedule_selector(HAnimaCenter::update));
    
    CC_SAFE_RELEASE(m_cmd_cache);
    CC_SAFE_RELEASE(m_timer);
    
}

void HAnimaCenter::update(float fDelta)
{
//    CCLOG("%f", 1.f / fDelta);
    for (int i=0; i<m_cmd_cache->count(); i++) {
        HAnimaCommand* pCmd = (HAnimaCommand*)m_cmd_cache->objectAtIndex(i);
        if (pCmd->isOver()) {
            pCmd->end();
            m_cmd_cache->removeObject(pCmd);
            i--;
        }
    }
    
    FOREACH(HAnimaCommand*, pCmd, m_cmd_cache){
        pCmd->update(fDelta);
    }
}

HAnimaCommand::HAnimaCommand(CCNode* target, CMD_ARGS)
: m_pTarget(NULL)
{
    HC_SET(m_pTarget, target);
    m_pDelegate = delegate;
    m_total_time = 0;
    m_flag = flag;
    m_duration = duration;
}

HAnimaCommand::~HAnimaCommand()
{
    CC_SAFE_RELEASE(m_pTarget);
    m_pDelegate = NULL;
}

void HAnimaCommand::begin()
{
    m_total_time = 0;
    HAnimaProtocol* tar = dynamic_cast<HAnimaProtocol*>(m_pTarget);
    if (tar != NULL) {
        tar->setAnimaing(true);
    }
}

void HAnimaCommand::update(float delta)
{
     m_total_time += delta;
}

void HAnimaCommand::end()
{
    HAnimaProtocol* tar = dynamic_cast<HAnimaProtocol*>(m_pTarget);
    if (tar != NULL) {
        tar->setAnimaing(false);
    }
    
    if (m_pDelegate != NULL) {
        m_pDelegate->onAnimaEnd(this);
    }
}

bool HAnimaCommand::isOver()
{
    return m_total_time >= m_duration;
}

