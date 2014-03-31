#ifndef _UI_LOADING_LAYER_H_
#define _UI_LOADING_LAYER_H_

HNAMESPACE_BEGIN

class CC_DLL HLoadingLayer: public HRootLayer {
    HCLASSTYPE(HLoadingLayer, HRootLayer);
    CC_SYNTHESIZE(bool, m_bLockTouch, LockTouch);
public:
    HLoadingLayer();
    virtual ~HLoadingLayer();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    static HLoadingLayer *create();
};

HNAMESPACE_END

#endif // _UI_LOADING_LAYER_H_
