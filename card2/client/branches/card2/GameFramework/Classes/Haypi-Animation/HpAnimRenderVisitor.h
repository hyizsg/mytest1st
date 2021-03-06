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

#include "ccColorExtension.h"

#define RENDER_IN_SUBPIXEL(_x) _x


USING_NS_CC;

namespace haypi_animation{
    
template<typename T>
class CCNumber : public CCObject
{
public:
    template< typename Y>
    CCNumber(Y v)
    : m_nValue(v) {}
    T getValue() const {return m_nValue;}
    
    virtual bool isEqual(const CCObject* pObject)
    {
        CCNumber* p = (CCNumber*)pObject;
        return fabs(m_nValue - p->m_nValue) < 1e-6;
    }
    
    template< typename Y>
    static CCNumber<T>* create(Y v)
    {
        CCNumber<T>* pRet = new CCNumber<T>(v);
//        pRet->autorelease();
        CC_AUTO_RELEASE(pRet);
        return pRet;
    }
private:
    T m_nValue;
};

class HpCharaInst;
class HpKeyframe;

class HpAnimRenderVisitor : public HpAnimVisitor{
private:
    int m_cur_atlas_id;
    CCTextureAtlas* m_cur_atlas;
    HpCharaInst* m_chr_instance;

    ccV3F_C4B_T2F_Quad m_quad;
    HpAffineTransformStack* m_tf_stack;
    HpColorStack* m_color_stack;
    HpStack* m_status_stack;
    
    HpStack* m_object_stack;
    CCDictionary* m_anim_helper;
    CCDictionary* m_cur_dic;
    
    double m_delta_time;
    CCString* s_elapsed;

protected:
    CC_SYNTHESIZE(float, m_local_scale, LocalScale)
    CC_SYNTHESIZE(float, m_global_scale, GlobalScale)
    CC_SYNTHESIZE(CCPoint, m_global_translate, GlobalTranslate)
    CC_SYNTHESIZE(CCAffineTransform, m_layer_transform, LayerTransform)
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
    
    template <class T>
    CCDictionary* currentDictionaryOfclass();
    
    void setElapsed(double value);
    double getElapsed(void);

};
}




#endif // HPANIMRENDERVISITOR_H
