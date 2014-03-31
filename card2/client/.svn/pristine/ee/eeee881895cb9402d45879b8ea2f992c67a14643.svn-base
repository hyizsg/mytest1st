#ifndef HPANIMATE_H
#define HPANIMATE_H

#include "cocos2d.h"

#include "HpAnimation.h"
#include "HpAnimBuildVisitor.h"


USING_NS_CC;

namespace haypi_animation{

class HpAnimate : public CCActionInterval{
private:
    HpAnimation* m_anima;
    float m_fps;
    float m_start;
    bool m_not_done;
    unsigned int m_repeat_count;

protected:
    CC_SYNTHESIZE(unsigned int, m_repeat_number, RepeatNumber)
    CC_SYNTHESIZE(bool, m_auto_destroy, AutoDestroy)

public:
    HpAnimate(HpAnimation* p_anima, float p_offset, int p_fps);
    virtual ~HpAnimate();

    virtual void startWithTarget(cocos2d::CCNode *pTarget);
    virtual void step(float dt);
    void setAnima(HpAnimation* p_anima);

};
}

#endif // HPANIMATE_H
