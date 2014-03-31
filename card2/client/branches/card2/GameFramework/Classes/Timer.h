#ifndef _TIMER_H_
#define _TIMER_H_

#define HMAXTICKCOUNT   8

HNAMESPACE_BEGIN

class CC_DLL HTimerDelegate {
public: virtual void onTimeOut(int gid, int count) = 0;
};

class CC_DLL HTimerInfo: public HObject {
    CC_SYNTHESIZE(HTimerDelegate *, m_pHost,  Host);
    CC_SYNTHESIZE(int, m_iGID, GID);
    CC_SYNTHESIZE(float, m_fInterval, Interval);
    CC_SYNTHESIZE(float, m_fTimeAdder, TimerAdder);
    CC_SYNTHESIZE(int, m_iTimeOutCount, TimeOutCount);
    CC_SYNTHESIZE(int, m_iTimeOutMaxTimes, TimeOutMaxTimes);
    
public:
    HTimerInfo(): HObject(), m_pHost(NULL) {}
    virtual ~HTimerInfo() { setHost(NULL); }
    
    static HTimerInfo *create(HTimerDelegate *host, int gid, float interval, int times);
    bool init(HTimerDelegate *host, int gid, float interval, int times);
    
    bool reachTimes();
    bool reachTime();
    void onTimeOut(int count);
};

class CC_DLL HTimer: public HObject {
    CC_SYNTHESIZE(bool, m_bPaused, Paused);
    CC_SYNTHESIZE(bool, m_bAlwaysCount,  AlwaysCount);
    CC_SYNTHESIZE(bool, m_bIsDirty, IsDirty);
public:
    HTimer(): HObject(), m_pTimers(NULL), m_bPaused(false), m_bAlwaysCount(false), m_bIsDirty(false) { m_pTimers = new CCArray(1); }
    virtual ~HTimer();
    
    static HTimer *create(HTimerDelegate *host, int gid, float interval, int times);
    
    void registerTimer(HTimerDelegate *host, int gid, float interval, int times);
    void unregisterTimer(HTimerDelegate *host, int gid);
    
    void updateTimerInfo(HTimerDelegate *host, int gid, float interval, int times);
    void clearTimerAdder();
    virtual void update(float dt);
private:
    CCArray *m_pTimers;
};

class HCountDown;
class CC_DLL HCountDownDelegate {
public: virtual void onCountTick(HCountDown *sender, int seconds) = 0;
};

class CC_DLL HCountDown: public HObject, public HTimerDelegate {
    CC_SYNTHESIZE(HCountDownDelegate *, m_pDelegate,  Delegate);
    CC_SYNTHESIZE(int, m_iSeconds, Seconds);
public:
    HCountDown(): HObject(), m_pDelegate(NULL), m_iSeconds(0) { m_pTimer = new HTimer(); m_pTimer->registerTimer(this, 0, 1.0f, 0); }
    virtual ~HCountDown() { disableTimer(); m_pTimer->release(); }
    
    virtual void onTimeOut(int gid, int count);
    
    static HCountDown *create(int seconds, HCountDownDelegate *delegate);
    bool init(int seconds, HCountDownDelegate *delegate);
    void updateSeconds(int seconds);
    
    void enableTimer();
    void disableTimer();
private:
    HTimer *m_pTimer;
};

class CC_DLL HTickDelegate {
public: virtual void onTick(int count) = 0;
};

class CC_DLL HUpdateDelegate {
public: virtual void onUpdate(float dt) = 0;
};

class CC_DLL HUpdater: public CCObject {
    CC_SYNTHESIZE(HUpdateDelegate *, m_pUpdateDelegate, UpdateDelegate);
    CC_SYNTHESIZE(bool, m_bIsDirty, IsDirty);
public:
    HUpdater(HUpdateDelegate *delegate): m_pUpdateDelegate(delegate), m_bIsDirty(false) { HASSERT(m_pUpdateDelegate != NULL, "update delegate is null."); }
    static HUpdater *create(HUpdateDelegate *delegate) {
        HUpdater *pRet = new HUpdater(delegate);
//        pRet->autorelease();
        CC_AUTO_RELEASE(pRet);
        return pRet;
    }
};

class CC_DLL HTimerManager: public CCNode, public HTimerDelegate {
    HSINGLETON_OBJECT(HTimerManager);
    
    CC_SYNTHESIZE(bool, m_bPaused, Paused);
public:
    void registerTimer(HTimer *timer);
    void unregisterTimer(HTimer *timer);
    void unregisterAllTimers();
    
    void registerTick(HTickDelegate *tick);
    void unregisterTick(HTickDelegate *tick);
    void unresgisterAllTicks();
    
    void registerUpdater(HUpdateDelegate *updater);
    void unregisterUpdater(HUpdateDelegate *updater);
    void unregisterAllUpdaters();
    
    virtual void onTimeOut(int gid, int count);
    
    void pauseAllTimers();
    void resumeAllTimers();
    
    void udpateTimer(float dt);
    
    virtual void visit(void);
    
    void asyncProcess(HInvocation *pInvocation, bool ignoreDuplicate = true);
    CCObject *processOnMainThread(HInvocation *pInvocation, bool bWaitReturn = false);
private:
    HLock m_oLock;
    CCArray *m_pTimers;
    HTimer *m_pTickTimer;
    HTickDelegate *m_pTicks[HMAXTICKCOUNT];
    int m_iTickCount;
    CCArray *m_pUpdaters;
//    CCArray *m_pRecycledTimers;
    CCArray *m_pAsyncFunctions;
    CCArray *m_pRecordFunctions;
    int m_lMainThreadID;
    
    struct timeval m_timeval;
    
    float calculateDeltaTime();
};

HNAMESPACE_END

#endif //_TIMER_H_
