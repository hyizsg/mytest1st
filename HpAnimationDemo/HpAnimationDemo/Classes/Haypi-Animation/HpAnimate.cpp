#include "HpAnimate.h"
#include "HpCharaInst.h"
#include "HpTextureAtlas.h"

#include "Hpheaders.h"


NS_HPAM_BEGIN

HpAnimate::HpAnimate(HpAnimation *p_anima, float p_offset, int p_fps)
{
    CCActionInterval::initWithDuration((float)(p_anima->getLength()) / p_fps);
    m_fps = p_fps;
    m_start = p_offset;
    m_anima = p_anima;
    m_anima->retain();
    m_repeat_count = 0;
    m_repeat_number = 0;
    m_auto_destroy = false;
}

HpAnimate::~HpAnimate(){
    //CC_SAFE_RELEASE(m_anima);
}

void HpAnimate::startWithTarget(cocos2d::CCNode *pTarget){
    m_not_done = true;
    CCActionInterval::startWithTarget(pTarget);
    HPLOG("HpAnimate....startWithTarget    isDone %d", this->isDone());
}

void HpAnimate::step(float dt){
    if(m_bFirstTick){
        m_elapsed = m_start;
        m_start = 0;
        m_bFirstTick = false;
    } else {
        m_elapsed += dt;
    }

    HpCharaInst* target = dynamic_cast<HpCharaInst*> (m_pTarget);
    target->setDeltaTime(dt);

    target->setAni(m_anima, m_elapsed * m_fps);

    HPLOG(" HpAnimate.....step isDone %d   m_elapsed %f m_fDuration %f", isDone(), m_elapsed, m_fDuration);
    if(m_not_done && this->isDone()){
        m_not_done = false;
        
        this->retain();
        target->retain();
        
        HPLOG(" HpAnimate.....step     isDone = true  m_repeat_count = %d; m_repeat_num = %d  ", m_repeat_count, m_repeat_number);
        target->onAnimationEnd(getRepeatNumber() == 0 ? false : (++ m_repeat_count == this->getRepeatNumber()) && getAutoDestroy());
        
        target->release();
        this->release();
    }
}

void HpAnimate::setAnima(HpAnimation* p_anima){
    m_anima = p_anima;
}

NS_HPAM_END
