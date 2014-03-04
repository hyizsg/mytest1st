#ifndef HPCHARAINSTOBSERVER_H
#define HPCHARAINSTOBSERVER_H

#include "cocos2d.h"


USING_NS_CC;

NS_HPAM_BEGIN

class HpCharaInst;
class HpAnimation;

class HpCharaInstObserver{
public:
    virtual void actionOnAnimationEnd(HpAnimation* p_ani, HpCharaInst* p_sender) = 0;
    virtual void actionOnCustomEvent(CCString* p_event, HpCharaInst* p_sender) = 0;
};

NS_HPAM_END

#endif // HPCHARAINSTOBSERVER_H
