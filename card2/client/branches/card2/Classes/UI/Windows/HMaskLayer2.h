//
//  HMaskLayer2.h
//  card
//
//  Created by zhou gang on 13-10-31.
//
//

#ifndef __card__HMaskLayer2__
#define __card__HMaskLayer2__

class HWindow;
class HRootScene;

class HMaskWindow2 : public HMaskProtocol{
    
public:
    
    typedef struct _tMaskData : public CCObject
    {
        CC_SYNTHESIZE_RETAIN(HWindow*, m_inWnd, InWnd);
        CC_SYNTHESIZE_RETAIN(HWindow*, m_outWnd, OutWnd);
        CC_SYNTHESIZE(float, m_fDuration, Duration);
        CC_SYNTHESIZE_BOOL(bool, m_bSendCleanup, SendCleanup);
        
        _tMaskData(): m_inWnd(NULL), m_outWnd(NULL), m_fDuration(0.f), m_bSendCleanup(false){
            
        }
        virtual ~_tMaskData(){
            CC_SAFE_RELEASE_NULL(m_inWnd);
            CC_SAFE_RELEASE_NULL(m_outWnd);
        }
        
        static _tMaskData* create(HWindow* pIn, HWindow* pOut, float fDuration, bool bCleanup){
            _tMaskData* data = new _tMaskData;
            data->setInWnd(pIn);
            data->setOutWnd(pOut);
            data->setDuration(fDuration);
            data->setSendCleanup(bCleanup);
            CC_AUTO_RELEASE(data);
            return data;
        }
        
    }HMaskData;
    
public:
    HMaskWindow2();
    virtual ~HMaskWindow2();
    static HMaskWindow2* create();
    
    virtual void maskWithInOut(HWindow* pIn, HWindow* pOut, float fDuration, bool bCleanup);
    virtual void update(float dt);
    
    void beginMask();
    
    void begin();
    void hideOutShowIn();
    void finish();
    
    
    HRootScene* scene();
 
protected:

    __retain CCArray* m_pTaskList;
    __retain CCArray* m_pSecondTaskList;
    
    __assign bool m_bMasking;
    __assign int m_nFrameCount;
    
    __assign static int tolerant_frame;
        
    
};

#endif /* defined(__card__HMaskLayer2__) */
