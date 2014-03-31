/**
 * @author mingjiang.bai@gmail.com
 * @date 20121214
 *
 */
#ifndef HPANIMATION_H
#define HPANIMATION_H


//#include "HpKeyframe.h"

#include "cocos2d.h"
USING_NS_CC;

namespace haypi_animation{

class HpLayer;
class HpContentKeyframe;

class HpAnimation : public CCObject{
public:
    CC_SYNTHESIZE_READONLY(int, m_iLen, Length)
    CC_SYNTHESIZE_READONLY(CCArray*, m_pLayer_array, Layers)
public:

    HpAnimation(int len);
    HpAnimation(HpAnimation* p_ani);
    virtual ~HpAnimation();

    HpAnimation* clone();
    HpLayer* getLayerByName(CCString* p_name);

    bool insertLayer(HpLayer* p_layer, CCString* p_target);
    bool replaceLayer(CCString* p_target, HpLayer* p_layer);
    void replaceContent(CCString* p_content, CCString* p_layer, HpContentKeyframe* p_ckf);

private:
    int findLayerByName(CCString* p_name);

};
}

#endif // HPANIMATION_H
