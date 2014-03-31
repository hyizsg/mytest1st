
#include "cocos2dxframework.h"

HNAMESPACE_BEGIN

//HTimerInfo
HTimerInfo *HTimerInfo::create(HTimerDelegate *host, int gid, float interval, int times) {
    HTimerInfo *info = new HTimerInfo();
    if (info && info->init(host, gid, interval, times)) {
//        info->autorelease();
        CC_AUTO_RELEASE(info);
    } else {
        CC_SAFE_DELETE(info);
    }
    return info;
}

bool HTimerInfo::init(HTimerDelegate *host, int gid, float interval, int times) {
    setHost(host);
    m_iGID = gid;
    m_fInterval = interval;
    m_fTimeAdder = 0.0f;
    m_iTimeOutCount = 0;
    m_iTimeOutMaxTimes = times;
    return true;
}

bool HTimerInfo::reachTimes() {
    if (m_iTimeOutMaxTimes <= 0) return false;
    return m_iTimeOutCount >= m_iTimeOutMaxTimes;
}

bool HTimerInfo::reachTime() {
    return m_fTimeAdder >= m_fInterval;
}

void HTimerInfo::onTimeOut(int count) {
    if (m_iTimeOutMaxTimes <= 0) {
        if (m_pHost) m_pHost->onTimeOut(m_iGID, count);
        return;
    }
    if (m_iTimeOutCount + count > m_iTimeOutMaxTimes) {
        count = m_iTimeOutMaxTimes - m_iTimeOutCount;
    }
    m_iTimeOutCount += count;
    if (m_pHost) m_pHost->onTimeOut(m_iGID, count);
}

//HTimer

HTimer::~HTimer() {
    delete m_pTimers;
}

HTimer *HTimer::create(HTimerDelegate *host, int gid, float interval, int times) {
    HTimer *timer = new HTimer();
    timer->registerTimer(host, gid, interval, times);
//    timer->autorelease();
    CC_AUTO_RELEASE(timer);
    return timer;
}

void HTimer::registerTimer(HTimerDelegate *host, int gid, float interval, int times) {
    bool bFound = false;
    for (int i = m_pTimers->count() - 1; i >= 0; --i) {
        HTimerInfo *ti = (HTimerInfo *)m_pTimers->objectAtIndex(i);
        if ((ti->getHost() == host) && (ti->getGID() == gid)) {
            bFound = true;
            break;
        }
    }
    if (!bFound) m_pTimers->addObject(HTimerInfo::create(host, gid, interval, times));
}

void HTimer::unregisterTimer(HTimerDelegate *host, int gid) {
    for (int i = m_pTimers->count() - 1; i >= 0; --i) {
        HTimerInfo *ti = (HTimerInfo *)m_pTimers->objectAtIndex(i);
        if ((ti->getHost() == host) && (ti->getGID() == gid)) {
            m_pTimers->removeObject(ti);
            break;
        }
    }
}

void HTimer::updateTimerInfo(HTimerDelegate *host, int gid, float interval, int times) {
    for (int i = m_pTimers->count() - 1; i >= 0; --i) {
        HTimerInfo *ti = (HTimerInfo *)m_pTimers->objectAtIndex(i);
        if ((ti->getHost() == host) && (ti->getGID() == gid)) {
            ti->setInterval(interval);
            ti->setTimeOutCount(0);
            ti->setTimeOutMaxTimes(times);
            ti->setTimerAdder(0);
            break;
        }
    }
}

void HTimer::clearTimerAdder() {
}

void HTimer::update(float dt) {
    for (int i = m_pTimers->count() - 1; i >= 0; --i) {
        HTimerInfo *ti = (HTimerInfo *)m_pTimers->objectAtIndex(i);
        if (!ti->reachTimes()) {
            ti->setTimerAdder(ti->getTimerAdder() + dt);
            if (ti->reachTime()) {
                int timeOutCount = (int)(ti->getTimerAdder() / ti->getInterval());
                ti->setTimerAdder(ti->getTimerAdder() - (ti->getInterval() * timeOutCount));
                ti->onTimeOut(timeOutCount);
            }
        }
    }
}

//HCountDown
void HCountDown::onTimeOut(int gid, int count) {
    if (m_iSeconds < 1) return;
    m_iSeconds -= count;
    if (m_iSeconds < 0) m_iSeconds = 0;
    if (m_pDelegate) m_pDelegate->onCountTick(this, m_iSeconds);
}

HCountDown *HCountDown::create(int seconds, HCountDownDelegate *delegate) {
    HCountDown *cd = new HCountDown();
    cd->init(seconds, delegate);
//    cd->autorelease();
    CC_AUTO_RELEASE(cd);
    return cd;
}

bool HCountDown::init(int seconds, HCountDownDelegate *delegate) {
    setSeconds(seconds);
    setDelegate(delegate);
    m_pTimer->setAlwaysCount(true);
    enableTimer();
    return true;
}

void HCountDown::updateSeconds(int seconds) {
    setSeconds(seconds);
}

void HCountDown::enableTimer() {
    HTimerManager::getInstance()->registerTimer(m_pTimer);
}

void HCountDown::disableTimer() {
    HTimerManager::getInstance()->unregisterTimer(m_pTimer);
}

//HTimerManager
HSINGLETON_OBJECT_IMP(HTimerManager);

HTimerManager::HTimerManager(): CCNode(), m_bPaused(false), m_pTickTimer(NULL), m_iTickCount(0) {
    //modify by zg
    m_lMainThreadID = CCPoolManager::sharedPoolManager()->getCurThreadID();
    
    m_pTimers = new CCArray(32);
    m_pUpdaters = new CCArray(32);
    
//    m_pRecycledTimers = new CCArray(8);
    m_pAsyncFunctions = new CCArray(8);
    m_pRecordFunctions = new CCArray(8);
    
    m_pTickTimer = new HTimer();
    m_pTickTimer->registerTimer(this, 0, 1.0f, -1);
    registerTimer(m_pTickTimer);
    
    CCDirector::sharedDirector()->setNotificationNode(this);
}

HTimerManager::~HTimerManager() {
    delete m_pRecordFunctions;
    delete m_pAsyncFunctions;
//    delete m_pRecycledTimers;
    delete m_pUpdaters;
    delete m_pTimers;
    delete m_pTickTimer;
}

void HTimerManager::registerTimer(HTimer *timer) {
    HSmartLock sl(&m_oLock);
    if (CC_INVALID_INDEX == m_pTimers->indexOfObject(timer)) {
        timer->setIsDirty(false);
        m_pTimers->addObject(timer);
    }
}

void HTimerManager::unregisterTimer(HTimer *timer) {
    HSmartLock sl(&m_oLock);
    for (int i = m_pTimers->count() - 1; i >= 0; --i) {
        if (timer == m_pTimers->objectAtIndex(i)) {
            timer->setIsDirty(true);
//            m_pTimers->removeObjectAtIndex(i);
            break;
        }
    }
}

void HTimerManager::unregisterAllTimers() {
    HSmartLock sl(&m_oLock);
    for (int i = m_pTimers->count() - 1; i >= 0; --i) {
        HTimer *timer = (HTimer *)m_pTimers->objectAtIndex(i);
        timer->setIsDirty(true);
    }
//    m_pTimers->removeAllObjects();
//    registerTimer(m_pTickTimer);
    m_pTickTimer->setIsDirty(false);
}

void HTimerManager::registerTick(HTickDelegate *tick) {
    HSmartLock sl(&m_oLock);
    HASSERT(m_iTickCount <= HMAXTICKCOUNT, "The count of ticks must be not larger then 8");
    for (int i = 0; i < m_iTickCount; ++i) {
        if (m_pTicks[i] == tick) return;
    }
    m_pTicks[m_iTickCount++] = tick;
}

void HTimerManager::unregisterTick(HTickDelegate *tick) {
    HSmartLock sl(&m_oLock);
    int i = 0;
    for (; i < m_iTickCount; ++i) {
        if (m_pTicks[i] == tick) break;
    }
    for (; i < m_iTickCount - 1; ++i) {
        m_pTicks[i] = m_pTicks[i + 1];
    }
    --m_iTickCount;
}

void HTimerManager::unresgisterAllTicks() {
    m_iTickCount = 0;
}

void HTimerManager::registerUpdater(HUpdateDelegate *updater) {
    HSmartLock sl(&m_oLock);
    bool bFind = false;
    for (int i = m_pUpdaters->count() - 1; i >= 0; --i) {
        HUpdater *u = (HUpdater *)m_pUpdaters->objectAtIndex(i);
        if (u->getUpdateDelegate() == updater) {
            bFind = true;
            break;
        }
    }
    if (!bFind) {
        m_pUpdaters->addObject(HUpdater::create(updater));
    }
}

void HTimerManager::unregisterUpdater(HUpdateDelegate *updater) {
    HSmartLock sl(&m_oLock);
    for (int i = m_pUpdaters->count() - 1; i >= 0; --i) {
        HUpdater *u = (HUpdater *)m_pUpdaters->objectAtIndex(i);
        if (u->getUpdateDelegate() == updater) {
            u->setIsDirty(true);
            break;
        }
    }
}

void HTimerManager::unregisterAllUpdaters() {
    HSmartLock sl(&m_oLock);
    m_pUpdaters->removeAllObjects();
}

void HTimerManager::onTimeOut(int gid, int count) {
    for (int i = 0; i < m_iTickCount; ++i) {
        m_pTicks[i]->onTick(count);
    }
}

void HTimerManager::pauseAllTimers() {
    m_bPaused = true;
}

void HTimerManager::resumeAllTimers() {
    m_bPaused = false;
}

void HTimerManager::udpateTimer(float dt) {
    int i;
    for (i = m_pUpdaters->count() - 1; i >= 0; --i) {
        HUpdater *u = (HUpdater *)m_pUpdaters->objectAtIndex(i);
        if (u->getIsDirty()) {
            m_pUpdaters->removeObjectAtIndex(i);
        } else {
            u->getUpdateDelegate()->onUpdate(dt);
        }
    }
    for (i = m_pTimers->count() - 1; i >= 0; --i) {
        HTimer *timer = (HTimer *)m_pTimers->objectAtIndex(i);
        if (timer->getIsDirty()) {
            m_pTimers->removeObjectAtIndex(i);
        } else {
            timer->update(dt);
        }
//        if (!m_bPaused || timer->getAlwaysCount()) {
//            timer->update(dt);
//        }
    }
}

void HTimerManager::visit(void) {
    int i = 0;
    int count = 0;
    {
        HSmartLock sl(&m_oLock);
        count = m_pRecordFunctions->count();
        while (i < count) {
            HInvocation *inv = (HInvocation *)m_pRecordFunctions->objectAtIndex(i);
            if (inv->getDelay() > 0.0f) {
                ++i;
                continue;
            }
            m_pAsyncFunctions->addObject(inv);
            m_pRecordFunctions->removeObjectAtIndex(i);
            --count;
        }
//        if (count > 0) {
//            for (i = 0; i < count; ++i) {
//                HInvocation *inv = (HInvocation *)m_pRecordFunctions->objectAtIndex(i);
//                m_pAsyncFunctions->addObject(m_pRecordFunctions->objectAtIndex(i));
//            }
//            m_pRecordFunctions->removeAllObjects();
//        }
    }
    
    count = m_pAsyncFunctions->count();
    if (count > 0) {
        for (i = 0; i < count; ++i) {
            HInvocation *inv = (HInvocation *)m_pAsyncFunctions->objectAtIndex(i);
            inv->retain();
            inv->invoke();
            inv->release();
        }
        m_pAsyncFunctions->removeAllObjects();
    }
    
    if (m_bPaused) return;
    float dt = calculateDeltaTime();
    if (dt > 0) {
        udpateTimer(dt);
    }
    
    if (dt < 0.5f) {
        i = 0;
        count = m_pRecordFunctions->count();
        while (i < count) {
            HInvocation *inv = (HInvocation *)m_pRecordFunctions->objectAtIndex(i);
            inv->setDelay(inv->getDelay() - dt);
            if (inv->getDelay() > 0.0f) {
                ++i;
                continue;
            }
            m_pAsyncFunctions->addObject(inv);
            m_pRecordFunctions->removeObjectAtIndex(i);
            --count;
        }
    }
}

void HTimerManager::asyncProcess(HInvocation *pInvocation, bool ignoreDuplicate) {
    pInvocation->retain();
    HSmartLock sl(&m_oLock);
    bool bExists = false;
    if (ignoreDuplicate) {
        for (int i = m_pRecordFunctions->count() - 1; i >= 0; --i) {
            HInvocation *inv = (HInvocation *)m_pRecordFunctions->objectAtIndex(i);
            if ((inv->getTarget() == pInvocation->getTarget()) && (inv->getAction() == pInvocation->getAction())) {
                m_pRecordFunctions->replaceObjectAtIndex(i, pInvocation);
                bExists = true;
                break;
            }
        }
    }
    if (!bExists) m_pRecordFunctions->addObject(pInvocation);
    pInvocation->release();
}

CCObject *HTimerManager::processOnMainThread(HInvocation *pInvocation, bool bWaitReturn) {
    //modify by zg
    if (m_lMainThreadID == CCPoolManager::sharedPoolManager()->getCurThreadID()) {
        pInvocation->invoke();
    } else
    {
        pInvocation->retain();
        m_oLock.lock();
        m_pRecordFunctions->addObject(pInvocation);
        m_oLock.unlock();
        if (bWaitReturn) { //wait 30 seconds top most
            int i = 0;
            while (i < 3000) {
                HThread::sleepWithMilliSeconds(1);
                if (pInvocation->getIsEnd()) break;
                ++i;
            }
        }
        pInvocation->release();
    }
    return pInvocation->getResult();
}

float HTimerManager::calculateDeltaTime() {
    float dt = 0.0f;
    struct timeval now;

    if (m_timeval.tv_sec == 0) {
        gettimeofday( &m_timeval, NULL);
        return dt;
    }
    
	if( gettimeofday( &now, NULL) != 0 ) {
		HLOGI("cocos2d: error in gettimeofday");
		return dt;
	}
	
	// new delta time
    dt = (now.tv_sec - m_timeval.tv_sec) + (now.tv_usec - m_timeval.tv_usec) / 1000000.0f;
    dt = MAX(0,dt);
    
	m_timeval = now;
    
    return dt;
}

HNAMESPACE_END
