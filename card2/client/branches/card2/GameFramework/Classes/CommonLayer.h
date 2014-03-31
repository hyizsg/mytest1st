#ifndef _COMMON_LAYER_H_
#define _COMMON_LAYER_H_

#define HTOUCHPRIORITY_LAYERSPACE       1000

HNAMESPACE_BEGIN

class CC_DLL HMaskLayer: public CCLayerColor {
    CC_SYNTHESIZE(bool, m_bPresentUI, PresentUI);
public:
    //    HMaskLayer() {
    //        setTouchPriority(-1000);
    //    }
    
    static HMaskLayer *create() {
        HMaskLayer *pRet = new HMaskLayer();
        pRet->init();
        pRet->autorelease();
        return pRet;
    }
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
        return false;
    }
};

class CC_DLL HCommonLayer: public CCLayer {
    //    CC_PROPERTY(bool, m_bEnableTouch, EnableTouch);
    CC_SYNTHESIZE(bool, m_bIsInForeground, InForeground);
    CC_SYNTHESIZE(bool, m_bDisableAnimInOut, DisableAnimInOut);
    CC_PROPERTY(bool, m_bOutOfScreen, OutOfScreen);
    CC_PROPERTY(int, m_iBaseTouchPriority, BaseTouchPriority);
    CC_SYNTHESIZE_RETAIN(CCFiniteTimeAction *, m_pActionIn, ActionIn);
    CC_SYNTHESIZE_RETAIN(CCFiniteTimeAction *, m_pActionOut, ActionOut);
public:
    HCommonLayer();
    virtual ~HCommonLayer();
    
    CCObject *onNeedRegisterTouchDispatcher(int command, CCObject *param);

    virtual CCAffineTransform nodeToParentTransform(void);
    
//    virtual void setTouchEnabled(bool value);
//    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void onEnterForeground();
    virtual void onEnterBackground();
    
    // add to or remove from parent when masking
    // set parent value or NULL, as equel to onEnterForeground or onEnterBackground
    virtual void willMoveToWindow(CCNode* parent) {}
    
    // after mask calling
    // set parent value or NULL, as truely display or hide
    virtual void didMoveToWindow(CCNode* parent) {}
    
    virtual std::string getClass() { return "HCommonLayer"; }
    virtual bool isKindOf(const std::string &name) { return name == "HCommonLayer"; }
    
    virtual bool init();
    
    void startAIV(bool bLockTouch = false);
    void stopAIV();
    
    virtual void onOK() {}
    virtual void onCancel() {}
    
    virtual bool refresh(int which) { return false; }
    
    void setActions(const char *inKey, const char *outKey);
    virtual void animIn(HCommonLayer *endReceiver);
    virtual void animOut(HCommonLayer *endReceiver);
    virtual void animInEnd() { CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true); }
    virtual void animOutEnd() { CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true); }
    
    static void registerAction(CCFiniteTimeAction *action, const char *key);
    static void unregisterAction(const char *key);
    
public:
    virtual void updatePriorityTouchLayer(CCNode *node);
    
private:
//    void updateEditboxTouchLayer(CCNode *node, bool enable);
//    void updateEnabledTouchLayer(CCNode *node);
    
    static CCDictionary *m_spAllActions;
    
protected:    
    static HMaskLayer *m_spMasklayer;
    
public:
    static void setMaskLayer(HMaskLayer *layer) { m_spMasklayer = layer; }
};

HNAMESPACE_END

#endif // _COMMON_LAYER_H_
