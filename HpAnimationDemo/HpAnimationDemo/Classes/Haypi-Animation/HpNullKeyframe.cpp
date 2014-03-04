
/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#include "HpNullKeyframe.h"


NS_HPAM_BEGIN

void HpNullKeyframe::visitBy(HpAnimVisitor* visitor, HpKeyframe *p_fm, float time){
    visitor->visitNullKey(this, p_fm, time);
}

HpContentKeyframe* HpNullKeyframe::clone(){
    this->retain();
    autorelease();
    return this;
}


NS_HPAM_END