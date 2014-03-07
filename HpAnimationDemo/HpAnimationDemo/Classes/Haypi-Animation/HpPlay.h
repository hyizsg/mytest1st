//
//  HpPlay.h
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-7.
//
//

#ifndef __HpAnimationDemo__HpPlay__
#define __HpAnimationDemo__HpPlay__

#include "cocos2d.h"
#include "Hpheaders.h"
#include "HpAnimate.h"

USING_NS_CC;
NS_HPAM_BEGIN

class HpPlay : public HpAnimate{
    
    
public:
    static HpPlay* create(const char* animName);
    
    HpPlay(HpAnimation* anima);
    virtual ~HpPlay();
    
    virtual void startWithTarget(cocos2d::CCNode *pTarget);
    virtual void step(float dt);
    virtual void update(float time);
    
protected:
    std::string m_aniame;
};

NS_HPAM_END
#endif /* defined(__HpAnimationDemo__HpPlay__) */
