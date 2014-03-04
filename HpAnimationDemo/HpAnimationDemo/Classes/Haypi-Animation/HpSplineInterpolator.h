#ifndef HPSPLINEINTERPOLATOR_H
#define HPSPLINEINTERPOLATOR_H

#include "HpInterpolator.h"

#include "cocos2d.h"

USING_NS_CC;


NS_HPAM_BEGIN
class HpSplineInterp : public HpInterp{
private:
    CCPoint     P0;
    CCPoint     P3;

    
public:
    CCPoint     P1;
    CCPoint     P2;

private:
    double conventX2Time(double x);
    static CCDictionary* tires;

public:
    static HpSplineInterp* interp(CCString* p_ctrlpts);
    static HpSplineInterp* interp(float x1, float y1, float x2, float y2);
    
    static void Purge();

    float getFactorWithStart(int p_t1, int p_t2, float p_t);

};


NS_HPAM_END

#endif // HPSPLINEINTERPOLATOR_H
