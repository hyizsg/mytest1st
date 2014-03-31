/**
 * @author mingjiang.bai@gmail.com
 * @date 20121214
 */
#ifndef HPIMAGEKEYFRAME_H
#define HPIMAGEKEYFRAME_H

#include "HpKeyframe.h"
#include "HpAnimVisitor.h"

#include "cocos2d.h"

USING_NS_CC;


namespace haypi_animation{

class HpImageKeyframe : public HpContentKeyframe {
public:
    HpImageKeyframe();
    HpImageKeyframe(HpImageKeyframe* p_image);
    virtual ~HpImageKeyframe();

private:
    CC_PROPERTY(CCSpriteFrame*, m_pSpriteFrame, SpriteFrame);

public:
    void visitBy(HpAnimVisitor *p_visitor, HpKeyframe *p_fm, float time);
    HpContentKeyframe* clone();
};
}

#endif // HPIMAGEKEYFRAME_H
