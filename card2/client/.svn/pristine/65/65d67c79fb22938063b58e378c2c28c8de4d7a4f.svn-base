
#include "cocos2dxframework.h"

HNAMESPACE_BEGIN

//HObject
#ifdef HOS_WIN32
static DWORD WINAPI threadLoop(LPVOID pThread) {
#else
static void *threadLoop(void *pThread) {
#endif
    HThread *thread = dynamic_cast<HThread *>((HThread *)pThread);
    if (thread) {
        thread->mainLoop();
    }
    return 0;
}

HThread::HThread(): CCObject(), m_pTarget(NULL), m_pAction(NULL), m_iLoopCount(0), m_iLoopIndex(0), m_bFinished(false) {
}

HThread::~HThread() {
    clearExecuteBody();
}

bool HThread::init() {
#ifdef HOS_WIN32
    DWORD thread;
    CreateThread(0, 0, threadLoop, this, 0, &thread);
#else
    pthread_t thread;
    return 0 == pthread_create(&thread, NULL, threadLoop, this);
#endif
}

void HThread::finish() {
    m_bFinished = true;
}

void HThread::mainLoop() {
//    CCPoolManager *poolManager = addPoolManager();
    m_bFinished = false;
    while (!m_bFinished) {
        if ((m_iLoopCount < 0) || (m_iLoopIndex < m_iLoopCount)) {
            if (m_pTarget && m_pAction) {
                (m_pTarget->*m_pAction)(this);
                ++m_iLoopIndex;
                if ((m_iLoopCount > 0) && (m_iLoopIndex >= m_iLoopCount)) {
//                    clearExecuteBody();
                    break;
                }
//                poolManager->pop();
            }
        }
        
        sleepWithMilliSeconds(1);
        
        // modify by zg
        CCPoolManager::sharedPoolManager()->pop();
    }
    
//    removeCurrentPoolManager();
    
    
    release();
}

HThread *HThread::createThreadAutoRelease(CCObject *pTarget, SEL_HThreadExecute pAction, int loopCount) {
    HASSERT(pTarget && pAction, "createThreadAutoRelease the params must be not NULL.");
    HThread *pThread = new HThread();
    pThread->setExecuteBody(pTarget, pAction, loopCount);
    pThread->init();
    return pThread;
}

void HThread::sleepWithMilliSeconds(long milliseconds) {
#ifdef HOS_WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

HNAMESPACE_END
