
#include "cocos2dxframework.h"

HNAMESPACE_BEGIN

//HLock
HLock::HLock() {
	m_pCriticalSection = new pthread_mutex_t;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init((pthread_mutex_t *)m_pCriticalSection, &attr);
}

HLock::~HLock() {
	pthread_mutex_destroy((pthread_mutex_t *)m_pCriticalSection);
	delete (pthread_mutex_t *)m_pCriticalSection;
}

void HLock::lock() {
	// HLOGI("HLock::lock threadID(%ld)", pthread_self());
	pthread_mutex_lock((pthread_mutex_t *)m_pCriticalSection);
	// HLOGI("HLock::lock end threadID(%ld)", pthread_self());
}

void HLock::unlock() {
	// HLOGI("HLock::unlock threadID(%ld)", pthread_self());
	pthread_mutex_unlock((pthread_mutex_t *)m_pCriticalSection);
	// HLOGI("HLock::unlock end threadID(%ld)", pthread_self());
}

HNAMESPACE_END
