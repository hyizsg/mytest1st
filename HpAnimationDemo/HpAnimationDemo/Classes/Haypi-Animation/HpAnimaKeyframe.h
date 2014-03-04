/**
 * @author mingjiang.bai
 * @date 20121214
 *
 */
#ifndef HPANIMAKEYFRAME_H
#define HPANIMAKEYFRAME_H

#include "HpKeyframe.h"
#include "HpAnimation.h"

#include "cocos2d.h"
USING_NS_CC;

namespace haypi_animation{

class HpAnimaKeyframe : public HpContentKeyframe{
protected:
    CC_SYNTHESIZE_RETAIN(HpAnimation*, m_anima, Anima)
    CC_SYNTHESIZE(bool, m_isTimeInherited, IsTimeInherited);
public:
    HpAnimaKeyframe();
    HpAnimaKeyframe(HpAnimaKeyframe* p_akf);
    virtual ~HpAnimaKeyframe();
    
    void visitBy(HpAnimVisitor *p_visitor, HpKeyframe *p_fm, float time);
    HpContentKeyframe* clone();

};
}

#endif // HPANIMAKEYFRAME_H
