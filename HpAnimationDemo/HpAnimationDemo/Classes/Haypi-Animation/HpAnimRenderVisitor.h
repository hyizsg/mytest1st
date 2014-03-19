#ifndef HPANIMRENDERVISITOR_H
#define HPANIMRENDERVISITOR_H

#include "math.h"

#include "cocos2d.h"

#include "HpAnimVisitor.h"
#include "HpRenderVisitorStack.h"
#include "HpStack.h"
#include "HpCharaInst.h"
#include "HpKeyframe.h"
#include "HpCharactorManager.h"
#include "HpTextureAtlas.h"
#include "Hpheaders.h"

#include "ccColorExtension.h"

#define RENDER_IN_SUBPIXEL(_x) _x


USING_NS_CC;

NS_HPAM_BEGIN

class HpCharaInst;
class HpKeyframe;

class HpAnimRenderVisitor : public HpAnimVisitor{
private:
    int m_cur_atlas_id;
    HpTextureAtlas* m_cur_atlas;
    HpCharaInst* m_chr_instance;

    ccV3F_C4B_T2F_L4B_G1F_Quad m_quad;
    HpRenderStack* m_render_stack;
    
    HpStack* m_status_stack;

    float m_delta_time;
    
protected:
    CC_SYNTHESIZE(float, m_local_scale, LocalScale)
    CC_SYNTHESIZE(float, m_global_scale, GlobalScale)
    CC_SYNTHESIZE(CCPoint, m_global_translate, GlobalTranslate)
    CC_SYNTHESIZE(HpRenderInfo, m_layer_render, LayerRender);
    CC_SYNTHESIZE(ccColor4F, m_layer_color, LayerColor);

private:
    void fireEventPassed(HpLayer* p_layer, HpKeyframe* p_last, HpKeyframe* p_kf);

public:
    HpAnimRenderVisitor();
    virtual ~HpAnimRenderVisitor();

    
    void visitAnima(HpAnimation* p_ani, bool p_first, float p_time, bool p_inherited);
    
    void visitAnima(HpAnimation *p_ani, bool p_first, float p_frm);
    void visitLayer(HpLayer *p_layer, bool p_first, float p_frm);
    void visitImageKey(HpImageKeyframe *p_ikf, HpKeyframe *p_frm, float time);
    void visitAnimaKey(HpAnimaKeyframe *p_akf, HpKeyframe *p_frm, float time);
    void visitNullKey(HpNullKeyframe *p_nkf, HpKeyframe *p_frm, float time);

    void begin(CCObject *p_map);
    void end();

    CCAffineTransform* makeTransform(CCAffineTransform* p_in, HpKeyframe* p_key, float time);

};

NS_HPAM_END




#endif // HPANIMRENDERVISITOR_H
