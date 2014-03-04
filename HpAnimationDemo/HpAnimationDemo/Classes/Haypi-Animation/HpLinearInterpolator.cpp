#include "HpLinearInterpolator.h"



NS_HPAM_BEGIN

HpLinearInterp* HpLinearInterp::s_instance = NULL;

float HpLinearInterp::getFactorWithStart(int p_t1, int p_t2, float p_t){
    return (float)(p_t - p_t1) / (p_t2 - p_t1);
}


HpLinearInterp* HpLinearInterp::Interp(){
    if(s_instance == NULL){
        s_instance = new HpLinearInterp;
    }

    return s_instance;
}

void HpLinearInterp::Purge(){
    s_instance->release();
    s_instance = NULL;
}



NS_HPAM_END