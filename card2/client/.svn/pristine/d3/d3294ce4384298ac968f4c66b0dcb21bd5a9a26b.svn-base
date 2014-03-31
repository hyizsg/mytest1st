//
//  HMaskLayer.h
//  card
//
//  Created by 周 刚 on 13-7-13.
//
//

#ifndef __card__HMaskLayer__
#define __card__HMaskLayer__

class HWindow;
class HRootScene;

class HMaskWindow : public HMaskProtocol {
    
    
public:
    HMaskWindow();
    virtual ~HMaskWindow();
    static HMaskWindow* create();
    
    virtual void maskWithInOut(HWindow* pIn, HWindow* pOut, float fDuration, bool bCleanup);
    
    void beginMask();
    void begin();
    void finish();
    void hideOutShowIn();
    
    void stopMaskAction();
    
    HWindow* inWindow();
    HWindow* outWindow();
    
    bool isWindowWillBeClear(HWindow* wnd);
    
    HRootScene* scene();
    
protected:
    __retain CCArray* m_pInWindow;
    __retain CCArray* m_pOutWindow;
    __retain CCObject* m_pNullObject;
    
    __assign vector<bool> m_bSendCleanup;
    __assign vector<float> m_fDuration;
    
    
};

#endif /* defined(__card__HMaskLayer__) */
