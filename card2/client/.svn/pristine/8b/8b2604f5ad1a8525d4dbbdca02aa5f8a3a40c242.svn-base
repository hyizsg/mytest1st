#ifndef _THREAD_H_
#define _THREAD_H_

HNAMESPACE_BEGIN

class HThread;

typedef void (CCObject::*SEL_HThreadExecute)(HThread *);
#define hthread_selector(_HANDLER) (SEL_HThreadExecute)(&_HANDLER)

class CC_DLL HThread: public CCObject {
    CC_SYNTHESIZE_RETAIN(CCObject*, m_pTarget, Target);
    CC_SYNTHESIZE(SEL_HThreadExecute, m_pAction, Action);
    CC_SYNTHESIZE(int, m_iLoopCount, LoopCount);
public:
    HThread();
    virtual ~HThread();
    
    bool init();
    void finish();
    
    void setExecuteBody(CCObject *pTarget, SEL_HThreadExecute pAction, int loopCount = -1) { setTarget(pTarget); setAction(pAction); m_iLoopCount = loopCount; m_iLoopIndex = 0; }
    void clearExecuteBody() { setAction(NULL); setTarget(NULL); m_iLoopCount = 0; m_iLoopIndex = 0; }
    
    void mainLoop();
    
    static HThread *createThreadAutoRelease(CCObject *pTarget, SEL_HThreadExecute pAction, int loopCount = -1);
    
    static void sleepWithMilliSeconds(long milliseconds);
private:
    int m_iLoopIndex;
    bool m_bFinished;
};

HNAMESPACE_END

#endif //_THREAD_H_
