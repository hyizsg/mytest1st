/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#ifndef HPNULLKEYFRAME_H
#define HPNULLKEYFRAME_H

#include "HpKeyframe.h"

NS_HPAM_BEGIN
class HpNullKeyframe : public HpContentKeyframe {
public:
    void visitBy(HpAnimVisitor* visitor, HpKeyframe *p_fm, float time);
    HpContentKeyframe* clone();
};


NS_HPAM_END

#endif // HPNULLKEYFRAME_H
