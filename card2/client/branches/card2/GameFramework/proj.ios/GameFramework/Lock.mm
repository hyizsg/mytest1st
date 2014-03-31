
#include "../../Classes/cocos2dxframework.h"

HNAMESPACE_BEGIN

//#define H_USE_CONDITION
//HLock::HLock() {
//#ifdef H_USE_CONDITION
//    m_pCriticalSection = [[NSCondition alloc] init];
//#else
//    m_pCriticalSection = [[NSLock alloc] init];
//#endif
//}
//
//HLock::~HLock() {
//#ifdef H_USE_CONDITION
//    [((NSCondition *)m_pCriticalSection) release];
//#else
//    [((NSLock *)m_pCriticalSection) release];
//#endif
//}
//
//void HLock::lock() {
//#ifdef H_USE_CONDITION
//    [((NSCondition *)m_pCriticalSection) lock];
//#else
//    [((NSLock *)m_pCriticalSection) lock];
//#endif
//}
//
//void HLock::unlock() {
//#ifdef H_USE_CONDITION
//    [((NSCondition *)m_pCriticalSection) unlock];
//#else
//    [((NSLock *)m_pCriticalSection) unlock];
//#endif
//}

//HLock
HLock::HLock() {
	m_pCriticalSection = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)); // new pthread_mutex_t;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(m_pCriticalSection, &attr);
}

HLock::~HLock() {
	pthread_mutex_destroy(m_pCriticalSection);
	free(m_pCriticalSection);
}

void HLock::lock() {
	pthread_mutex_lock(m_pCriticalSection);
}

void HLock::unlock() {
	pthread_mutex_unlock(m_pCriticalSection);
}

HNAMESPACE_END
