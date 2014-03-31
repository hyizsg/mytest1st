#ifndef _LOCK_H_
#define _LOCK_H_

HNAMESPACE_BEGIN

class CC_DLL HLock {
public:
    HLock();
    ~HLock();
    void lock();
    void unlock();
private:
    pthread_mutex_t *m_pCriticalSection;
};

class CC_DLL HSmartLock {
public:
    HSmartLock(HLock *pLock): m_pLock(pLock) { m_pLock->lock(); }
    ~HSmartLock() { m_pLock->unlock(); }
private:
    HLock *m_pLock;
};

HNAMESPACE_END

#endif //_LOCK_H_
