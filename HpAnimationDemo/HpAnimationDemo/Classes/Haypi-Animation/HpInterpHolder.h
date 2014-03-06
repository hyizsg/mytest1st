/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#ifndef HPINTERPHOLDER_H
#define HPINTERPHOLDER_H

#include "cocos2d.h"

#include "HpInterpolator.h"

USING_NS_CC;

NS_HPAM_BEGIN

class HpKeyframe;

class HpInterpHolder : public CCObject{
private:
    HpKeyframe* m_pTarget;
public:

    CC_SYNTHESIZE_RETAIN(HpInterp*, m_pCenterInterp, CenterInterp)
    CC_SYNTHESIZE_RETAIN(HpInterp*, m_pTransInterp, TransInterp)
    CC_SYNTHESIZE_RETAIN(HpInterp*, m_pSkewInterp, SkewInterp)
    CC_SYNTHESIZE_RETAIN(HpInterp*, m_pScaleInterp, ScaleInterp)
    CC_SYNTHESIZE_RETAIN(HpInterp*, m_pRotInterp, RotInterp)
    CC_SYNTHESIZE_RETAIN(HpInterp*, m_pColorInterp, ColorInterp)

    HpInterpHolder();
    virtual ~HpInterpHolder();

public:
    CCPoint getCenterAt(float time, HpKeyframe* p_self);
    CCPoint getTransAt(float time, HpKeyframe* p_self);
    CCPoint getSkewAt(float time, HpKeyframe* p_self);
    CCPoint getScaleAt(float time, HpKeyframe* p_self);
    float getRotAt(float time, HpKeyframe* p_self);
    ccColor4F getColorAt(float time, HpKeyframe* p_self);
    ccColor4F getLightAt(float time, HpKeyframe* p_self);
    
    void setTarget(HpKeyframe* p_fm);

};


NS_HPAM_END

#endif // HPINTERPHOLDER_H
