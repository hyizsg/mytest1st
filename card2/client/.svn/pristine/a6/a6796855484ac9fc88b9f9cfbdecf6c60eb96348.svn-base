#ifndef _INVOCATION_H_
#define _INVOCATION_H_

HNAMESPACE_BEGIN

typedef CCObject *(CCObject::*SEL_HInvocationHandler)(int, CCObject *);
#define hinvocation_selector(_HANDLER) (SEL_HInvocationHandler)(&_HANDLER)

class CC_DLL HInvocation: public CCObject {
    CC_SYNTHESIZE_READONLY(CCObject*, m_pTarget, Target);
    CC_SYNTHESIZE_READONLY(SEL_HInvocationHandler, m_pAction, Action);
    CC_SYNTHESIZE_READONLY(int, m_iCommand, Command);
    CC_SYNTHESIZE_READONLY(CCObject *, m_pParam, Param);
    CC_SYNTHESIZE_READONLY(CCObject *, m_pResult, Result);
    CC_SYNTHESIZE(float, m_fDelay, Delay);
    CC_SYNTHESIZE(bool, m_bIsEnd, IsEnd);
public:
    HInvocation(CCObject* target, SEL_HInvocationHandler action, int command, CCObject *param, float delay = 0.0f): m_pTarget(target), m_pAction(action), m_iCommand(command), m_pParam(param), m_pResult(NULL), m_fDelay(delay), m_bIsEnd(false) {
        m_pTarget->retain();
        if (m_pParam) m_pParam->retain();
    }
    virtual ~HInvocation() {
        m_pTarget->release();
        if (m_pParam) m_pParam->release();
        if (m_pResult) m_pResult->release();
    }
    
    static HInvocation* create(CCObject* target, SEL_HInvocationHandler action, int command, CCObject *param, float delay = 0.0f) {
        HInvocation *pRet = new HInvocation(target, action, command, param, delay);
//        pRet->autorelease();
        CC_AUTO_RELEASE(pRet);
        return pRet;
    }
    
    void invoke() {
        if (m_pTarget && m_pAction) {
            m_pResult = (m_pTarget->*m_pAction)(m_iCommand, m_pParam);
            if (m_pResult) m_pResult->retain();
        }
        m_bIsEnd = true;
    }
};

HNAMESPACE_END

#endif //_INVOCATION_H_
