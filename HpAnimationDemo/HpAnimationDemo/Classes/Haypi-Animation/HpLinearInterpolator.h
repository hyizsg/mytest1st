/**
 * @author mingjiang.bai@gmail.com
 * @date 20121214
 *
 */
#ifndef HPLINEARINTERPOLATOR_H
#define HPLINEARINTERPOLATOR_H

#include "HpInterpolator.h"


NS_HPAM_BEGIN
class HpLinearInterp : public HpInterp {
private:
    static HpLinearInterp* s_instance;
public:

    float getFactorWithStart(int p_t1, int p_t2, float p_t);

    static HpLinearInterp* Interp();
    static void Purge();

};


NS_HPAM_END

#endif // HPLINEARINTERPOLATOR_H
