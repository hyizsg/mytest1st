/**
 * @author mingjiang.bai@gmail.com
 * @date 20121214
 *
 */
#ifndef HPLINEARINTERPOLATOR_H
#define HPLINEARINTERPOLATOR_H

#include "HpInterpolator.h"


namespace haypi_animation{
class HpLinearInterp : public HpInterp {
private:
    static HpLinearInterp* s_instance;
public:

    float getFactorWithStart(int p_t1, int p_t2, float p_t);

    static HpLinearInterp* Interp();
    static void Purge();

};

}

#endif // HPLINEARINTERPOLATOR_H
