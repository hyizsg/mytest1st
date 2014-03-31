#ifndef HPANIMBUILDVISITOR_H
#define HPANIMBUILDVISITOR_H


#include "cocos2d.h"

#include "HpAnimVisitor.h"

USING_NS_CC;

namespace haypi_animation{

class HpCharactor;

class HpAnimBuildVisitor : public HpAnimVisitor{
private:
    CCDictionary* m_anima_map;

protected:
    CC_SYNTHESIZE(bool, m_hdmode, HDMode)
    CC_SYNTHESIZE_RETAIN(CCString*, m_hdpostfix, HDpostfix)

public:
    HpAnimBuildVisitor();
    virtual ~HpAnimBuildVisitor();

    void visitAnima(HpAnimation *p_ani, bool p_first, float p_frm);
    void visitLayer(HpLayer *p_layer, bool p_first, float p_frm);
    void visitImageKey(HpImageKeyframe *p_ikf, HpKeyframe *p_frm, float time);
    void visitAnimaKey(HpAnimaKeyframe *p_akf, HpKeyframe *p_frm, float time);
    void visitNullKey(HpNullKeyframe *p_nkf, HpKeyframe *p_frm, float time){}

    void begin(CCObject* p_map);
    void end();
};
}

#endif // HPANIMBUILDVISITOR_H
