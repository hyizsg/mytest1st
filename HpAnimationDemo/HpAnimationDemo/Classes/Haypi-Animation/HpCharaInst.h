#ifndef HPCHARAINST_H
#define HPCHARAINST_H

#include "cocos2d.h"

#include "HpCharactor.h"
#include "HpAnimation.h"
#include "HpLayer.h"
#include "HpCharaInstObserver.h"
#include "HpAttachPoint.h"
#include "HpTextureAtlas.h"
#include "Hpheaders.h"


USING_NS_CC;

NS_HPAM_BEGIN

#define HPANIMATION_ACTION_TAG 255

class HpAnimaStatus;

class HpCharaInst : public cocos2d::CCNodeRGBA
{
public:
    HpCharaInst();
    virtual ~HpCharaInst();
    
public:
    static HpCharaInst *create();

public:
    /** Show an Animation by name, which has loaded by CharactorManager
     @param p_ani_name  The Animation name
     @param start_frm  Which frame play from
     @param fps  The playing speed
     @param num  The play times, it will play repeat forever if num is 0
     @param auto_destroy  this will remove from parent after playing ended if true
     */
    void playAniByName(const char *p_ani_name, float start_frm, int fps, unsigned int num, bool auto_destroy, float delaytime = 0.0f);
    
    /** Show an Animation as repeat forever or not, by frm & fps */
    void playAniByName(const char *p_ani_name, float start_frm, int fps, bool forever_repeat);
    
    /** Show an Animation as repeat forever or not */
    void playAniByName(const char *p_ani_name, bool forever_repeat);
    
    /** Show an Animation start from a frame */
    void playAniByName(const char *p_ani_name, float start_frm);
    
    /** Show an Animation once and autodestroy as an effect */
    void playEffectByName(const char * p_ani_name);

    /** The Animation event of Ended */
    void onAnimationEnd(bool destroy);
    
    /** The Animation event of Custom */
    void onCustomEvent(CCString* p_event);

    void draw();
    
public:
    void replaceContent(CCString* p_content, CCString* p_layer, CCString* p_ani, CCString* p_image);
    void replaceContent(CCString *p_content, CCString *p_layer, CCString *p_ani, CCSpriteFrame* p_sprite);
    void replaceContent(CCString *p_content, CCString *p_layer, CCString *p_ani, CCString* p_anima, CCString* p_char);
    void replaceContent(CCString *p_content, CCString *p_layer, CCString *p_ani, HpContentKeyframe* p_ckf);
    
    void appendLayer(CCString* p_src_layer, CCString* p_src_ani, CCString* p_char, CCString* p_dst_ani);
    void insertLayer(CCString* p_src_layer, CCString* p_src_ani, CCString* p_char, CCString* p_dst_ani, CCString* p_dst_layer);
    void replaceLayer(CCString* p_dst_layer, CCString* p_dst_ani, CCString* p_src_layer, CCString* p_src_ani, CCString* p_char);
    HpLayer* getlayerWhile(bool caring_dst_l, CCString* p_dst_layer, CCString* p_dst_ani, CCString* p_src_layer, CCString* p_src_ani, CCString* p_src_chr);
    
public:
    void attach(CCNode* p_child, CCString* p_layer);
    void unattach(CCNode* p_child);
    void applyAttath(HpLayer* layer, const CCAffineTransform& m, const ccColor4F& color);
    
    void updateAttaches();

public:
    //friend void setAni(HpAnimation* p_ani, float frm);
    void setAni(HpAnimation* p_ani, float frm);
    
    HpAnimation* getAnimationByName(CCString* p_ani);
    bool hasContent(CCString* contentName);
    
    void createLocalAnimation();
    void ensureLocalAnimation();

protected:
    CC_SYNTHESIZE_READONLY(CCArray*, m_atlas_list, Atlases)
    CC_SYNTHESIZE_READONLY(HpAnimaStatus*, m_anima_status, Status)
    
    CC_SYNTHESIZE(bool, m_firstAniamtionFrame, FirstAnimationFrame)
    CC_SYNTHESIZE(bool, m_flipx, FlipX)
    CC_SYNTHESIZE_RETAIN(CCString*, m_cur_anima_name, CurrentAnimationName)
    CC_SYNTHESIZE(unsigned char, m_opacity, Opacity)
    CC_SYNTHESIZE(double, m_fps, Fps);
    CC_SYNTHESIZE(double, m_deltaTime, DeltaTime);
    
    CC_SYNTHESIZE(HpCharaInstObserver*, m_delegate, Delegate);
    
    
private:
    HpCharactor* m_charator;
    HpAnimation* m_cur_anima;
    float m_cur_frame;
    bool m_dirty;
    
    CCDictionary* m_local_anims;
    CCArray* m_attach_list;
    
    static const double s_default_fps;

};

NS_HPAM_END

#endif // HPCHARAINST_H
