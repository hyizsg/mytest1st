#ifndef HPCHARAINST_H
#define HPCHARAINST_H

#include "cocos2d.h"

#include "HpCharactor.h"
#include "HpAnimation.h"
#include "HpLayer.h"
#include "HpCharaInstObserver.h"
#include "HpAttachPoint.h"


USING_NS_CC;

#define HPANIMATION_ACTION_TAG 255
namespace haypi_animation{
//void setAni(HpAnimation* p_ani, float frm);
class HpAnimaStatus;

class HpCharaInst : public cocos2d::CCNodeRGBA {
private:
    HpCharactor* m_charator;
    HpAnimation* m_cur_anima;
    float m_cur_frame;
    bool m_dirty;

    CCDictionary* m_local_anims;
    CCArray* m_attach_list;

    static const double s_default_fps;

protected:
    CC_SYNTHESIZE_READONLY(CCArray*, m_atlas_list, Atlases)
    CC_SYNTHESIZE_READONLY(HpAnimaStatus*, m_anima_status, Status)

    CC_SYNTHESIZE(bool, m_firstAniamtionFrame, FirstAnimationFrame)
    CC_SYNTHESIZE(bool, m_flipx, FlipX)
    CC_SYNTHESIZE_RETAIN(CCString*, m_cur_anima_name, CurrentAnimationName)
    CC_SYNTHESIZE(unsigned char, m_opacity, Opacity)
    CC_SYNTHESIZE(double, m_fps, Fps);
    CC_SYNTHESIZE(double, m_deltaTime, DeltaTime);

    CC_PROPERTY(HpCharaInstObserver*, m_delegate, Delegate);
public:
    HpCharaInst();
    HpCharaInst(HpCharactor* p_char);
    virtual ~HpCharaInst();
    static HpCharaInst *create(HpCharactor *p_char);
public:

    HpAnimation* getAnimationByName(CCString* p_ani);
    void createLocalAnimation();
    void ensureLocalAnimation();
    HpLayer* getlayerWhile(bool caring_dst_l, CCString* p_dst_layer, CCString* p_dst_ani, CCString* p_src_layer, CCString* p_src_ani, CCString* p_src_chr);
    void replaceContent(CCString *p_content, CCString *p_layer, CCString *p_ani, HpContentKeyframe* p_ckf);
    void updateAttaches();

public:
    void addToWorld(CCNode* world);
    void playAniByName(CCString* p_ani_name, float start_time, int fps, unsigned int num, bool auto_destroy, float delaytime = 0.0f);
    void playAniByName(CCString *p_ani_name, float start_time, int fps, bool forever_repeat);
    void playAniByName(CCString *p_ani_name, bool forever_repeat);
    void playAniByName(CCString *p_ani_name, float frm);

    void appendLayer(CCString* p_src_layer, CCString* p_src_ani, CCString* p_char, CCString* p_dst_ani);
    void insertLayer(CCString* p_src_layer, CCString* p_src_ani, CCString* p_char, CCString* p_dst_ani, CCString* p_dst_layer);
    void replaceLayer(CCString* p_dst_layer, CCString* p_dst_ani, CCString* p_src_layer, CCString* p_src_ani, CCString* p_char);

    void replaceContent(CCString* p_content, CCString* p_layer, CCString* p_ani, CCString* p_image);
    void replaceContent(CCString *p_content, CCString *p_layer, CCString *p_ani, CCSpriteFrame* p_sprite);
    void replaceContent(CCString *p_content, CCString *p_layer, CCString *p_ani, CCString* p_anima, CCString* p_char);

    void onAnimationEnd(bool destroy);
    void onCustomEvent(CCString* p_event);

    void attach(CCNode* p_child, CCString* p_layer);
    void unattach(CCNode* p_child);

    bool hasContent(CCString* contentName);

    void draw();
    
    virtual void visit(void);
    void applyAttath(HpLayer* layer, const CCAffineTransform& m, const ccColor4F& color);

public:
    //friend void setAni(HpAnimation* p_ani, float frm);
    void setAni(HpAnimation* p_ani, float frm);


};
}

#endif // HPCHARAINST_H
