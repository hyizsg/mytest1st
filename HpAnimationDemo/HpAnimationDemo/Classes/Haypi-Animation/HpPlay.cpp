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

HpPlay* HpPlay::createWithName(const char *animName)
{
    HpAnimation* anima = HpCharactorManager::sharedManager()->charaAnimaByName(animName);
    HpPlay* play = new HpPlay(anima);
    play->m_aniame = animName;
    play->autorelease();
    return play;
}


CCSequence* HpPlay::create(const char* animName, ...)
{
    va_list params;
    va_start(params, animName);
    
    CCArray* array = CCArray::create();
    array->addObject(HpPlay::createWithName(animName));
    
    const char* p = va_arg(params, const char*);
    while (p != NULL) {
        array->addObject(HpPlay::createWithName(p));
        p = va_arg(params, const char*);
    }
    
    va_end(params);
    
    return CCSequence::create(array);
}

CCSequence* HpPlay::createWithTwo(const char* animName1, const char* animName2)
{
    return CCSequence::createWithTwoActions(HpPlay::create(animName1), HpPlay::create(animName2));
}

CCSequence* HpPlay::create(CCArray *arrayOfNames)
{
    CCArray* arr = CCArray::create();
    for (int i=0; i<arrayOfNames->count(); i++) {
        CCObject* obj = arrayOfNames->objectAtIndex(i);
        if (dynamic_cast<CCString*>(obj)) {
            arr->addObject(HpPlay::create(((CCString*)obj)->getCString()));
        }
        else if(dynamic_cast<CCFiniteTimeAction*>(obj)){
            arr->addObject(obj);
        }
    }
    
    return CCSequence::create(arr);
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