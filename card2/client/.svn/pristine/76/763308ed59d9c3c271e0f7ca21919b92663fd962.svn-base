
/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#include "HpNullKeyframe.h"


using namespace haypi_animation;

void HpNullKeyframe::visitBy(HpAnimVisitor* visitor, HpKeyframe *p_fm, float time){
    visitor->visitNullKey(this, p_fm, time);
}

HpContentKeyframe* HpNullKeyframe::clone(){
    this->retain();
    autorelease();
    return this;
}
