/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#ifndef HPINTERPOLATOR_H
#define HPINTERPOLATOR_H
#include "cocos2d.h"
USING_NS_CC;

class HpInterp : public cocos2d::CCObject{
public:
    virtual float getFactorWithStart(int p_t1, int p_t2, float p_t) = 0;

};

enum HpInterpTarget {
    HPINTERP_BASE = 0,
    HPINTERP_CENTER = 0,
    HPINTERP_SCALE,
    HPINTERP_SKEW,
    HPINTERP_ROT,
    HPINTERP_TRANS,
    HPINTERP_COLOR,
    HPINTERP_NUM
};

#endif // HPINTERPOLATOR_H
