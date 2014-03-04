/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#ifndef HPINTERPOLATOR_H
#define HPINTERPOLATOR_H

#include "cocos2d.h"
#include "Hpheaders.h"

USING_NS_CC;

NS_HPAM_BEGIN

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



NS_HPAM_END

#endif // HPINTERPOLATOR_H
