//
//  HpPlay.cpp
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-7.
//
//

#include "HpPlay.h"
#include "HpCharaInst.h"
#include "HpCharactorManager.h"

NS_HPAM_BEGIN


HpPlay::HpPlay(HpAnimation* anima)
: HpAnimate(anima, 0, 30)
{
    
}

HpPlay::~HpPlay()
{
    
}

HpPlay* HpPlay::create(const char *animName)
{
    HpAnimation* anima = HpCharactorManager::sharedManager()->charaAnimaByName(animName);
    HpPlay* play = new HpPlay(anima);
    play->m_aniame = animName;
    play->autorelease();
    return play;
}

void HpPlay::startWithTarget(cocos2d::CCNode *pTarget)
{
    HpAnimate::startWithTarget(pTarget);
    
    HpCharaInst* inst = (HpCharaInst*)pTarget;
    inst->playAniByName(m_aniame.c_str(), 0.f);
    setTag(HPANIMATION_ACTION_TAG);
}

void HpPlay::step(float dt)
{
    HpAnimate::step(dt);
}

void HpPlay::update(float time)
{
    HpAnimate::step(time * getDuration() - m_elapsed);
}

NS_HPAM_END