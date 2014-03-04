#ifndef HPATTACHPOINT_H
#define HPATTACHPOINT_H

#include "cocos2d.h"

#include "HpLayer.h"

USING_NS_CC;

NS_HPAM_BEGIN

class HpLayer;

class HpAttachPoint : public CCObject{
private:
    CCArray* m_object_attached;

protected:
    CC_SYNTHESIZE_RETAIN(CCString*, m_animaName, AnimaName);
    CC_SYNTHESIZE_RETAIN(CCString*, m_layerName, LayerName)
    CC_SYNTHESIZE_RETAIN(HpLayer*, m_layerInst, LayerInst)

public:
    HpAttachPoint();
    virtual ~HpAttachPoint();

    void attach(CCNode* p_obj);
    void remove(CCNode* p_obj);

    void apply(const CCAffineTransform& m, const ccColor4F& color);
    
protected:
//    void apply(); 
};

NS_HPAM_END

#endif // HPATTACHPOINT_H
