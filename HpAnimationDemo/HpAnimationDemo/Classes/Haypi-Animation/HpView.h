//
//  HpView.h
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-18.
//
//

#ifndef __HpAnimationDemo__HpView__
#define __HpAnimationDemo__HpView__

#include "Hpheaders.h"
#include "cocos2d.h"
#include "HpLightProtocol.h"

USING_NS_CC;

NS_HPAM_BEGIN

class HpView : public CCNodeRGBA, public HpLightObject, public CCBlendProtocol {
    
    
public:
    HpView();
    virtual ~HpView();
    
    /**
     * Determines whether it clips its children or not.
     */
    bool isClippingToBounds() { return m_bClippingToBounds; }
    void setClippingToBounds(bool bClippingToBounds) { m_bClippingToBounds = bClippingToBounds; }
    
    void visit();
    
    virtual void setBlendFunc(ccBlendFunc blendFunc);
    virtual ccBlendFunc getBlendFunc(void);
    
    
protected:
    void beforeDraw();
    void afterDraw();
    
    CCRect getViewRect();
    
protected:
    
    bool m_bClippingToBounds;
    CCRect m_tParentScissorRect;
    bool m_bScissorRestored;
    
    ccBlendFunc m_tBlendFunc;
};

NS_HPAM_END

#endif /* defined(__HpAnimationDemo__HpView__) */
