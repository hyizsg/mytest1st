#ifndef _NET_MANAGER_H__
#define _NET_MANAGER_H__

HNAMESPACE_BEGIN

//#define H_CLOSE_NET

#define HNETFAILED                  -10000

#define HLOGIN_LOGIN                                1
#define HLOGIN_ACCOUNT                         2
#define HLOGIN_FAKE_LOGIN                   3
#define HLOGIN_FAKE_ACCOUNT            4
#define HLOGIN_REGISTER                 5


#define HNET_STATUS_NONE                0
#define HNET_STATUS_LOGINEDIN     1
#define HNET_STATUS_USESOCKET    2
#define HNET_STATUS_SERVERLIST   3

#define HNET_MODE_DEFAULT           -1
#define HNET_MODE_HTTP                  0
#define HNET_MODE_SOCKET            1
#define NET_MODE_GAMECENTER 		 2

#define HHEARTBEATINTERVAL          30



CC_DLL int secondsSince1970();
CC_DLL const char *dateFormat(int format, int secsSince1970);

CC_DLL const char *adjustText(const char *content, const char *font, int fontSize, int width, int minTextLength);

CC_DLL void setNetParameters(const char *passportURL, const char *localPassportURL, const char *gameID, const char *socketIPKey, const char *socketPortKey, const char *webSite, const char *version);

//class CC_DLL HNetProtocol: public HObject{
//    CC_SYNTHESIZE(int, m_iCommand, Command);
//    CC_SYNTHESIZE_RETAIN(CCDictionary *, m_pParam, Param);
//    CC_SYNTHESIZE_RETAIN(HObject *, m_pDelegate, Delegate);
//    CC_SYNTHESIZE(bool, m_bIgnoreDuplicaiton, IgnoreDuplicaiton);
//    CC_SYNTHESIZE(int, m_iCommandLevel, CommandLevel);
//    CC_SYNTHESIZE(int, m_iNetMode, NetMode);
//public:
//    HNetProtocol(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel, int netMode):  m_iCommand(command), m_pParam(NULL), m_pDelegate(NULL), m_bIgnoreDuplicaiton(ignoreDuplicaiton), m_iCommandLevel(commandLevel), m_iNetMode(netMode) {
//        setParam(param);
//        setDelegate(delegate);
//    }
//    virtual ~HNetProtocol() { setParam(NULL); setDelegate(NULL); }
//    static HNetProtocol *create(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel = 0, int netMode = HNET_MODE_DEFAULT) {
//        HNetProtocol *protocol = new HNetProtocol(command, param, delegate, ignoreDuplicaiton, commandLevel, netMode);
//        protocol->autorelease();
//        return protocol;
//    }
//    void processProtocol() {
//      HNetManager::getInstance()->postRequestEx(m_iCommand, m_pParam, m_pDelegate, m_bIgnoreDuplicaiton, m_iCommandLevel, m_iNetMode);
//    }
//};

class CC_DLL HNetData: public HObject {
    CC_SYNTHESIZE_RETAIN(HObject *, m_pTarget, Target);
    CC_SYNTHESIZE(int, m_iCommand, Command);
    CC_SYNTHESIZE_RETAIN(CCString *, m_pParam, Param);
public:
    HNetData(HObject *target, int command, CCString *param): HObject(), m_pTarget(NULL), m_iCommand(command), m_pParam(NULL) { setTarget(target); setParam(param); }
    virtual ~HNetData() { setTarget(NULL); setParam(NULL); }
    static HNetData *create(HObject *target, int command, CCString *param) {
        HNetData *pData = new HNetData(target, command, param);
//        pData->autorelease();
        CC_AUTO_RELEASE(pData);
        return pData;
    }
    void processReceivedData();
//    {
//        m_pTarget->onDataReceived(m_iCommand, m_pParam);
//    }
};

class CC_DLL HNetManager: public HObject, public HTimerDelegate, public HTickDelegate {
    HSINGLETON_OBJECT(HNetManager);
    CC_SYNTHESIZE(int, m_iLoginStatus, LoginStatus);
    CC_SYNTHESIZE(bool, m_bIsRegistered, IsRegistered);
    CC_SYNTHESIZE(bool, m_bIsFakeRegistered, IsFakeRegistered);
    CC_SYNTHESIZE(bool, m_bNeedWait, NeedWait);
    CC_SYNTHESIZE(bool, m_bUseSocket, UseSocket);
    CC_SYNTHESIZE(bool, m_bNeedRequestIP, NeedRequestIP);
    CC_SYNTHESIZE(bool, m_bEnableHttpReplaceSocket, EnableHttpReplaceSocket);
    CC_SYNTHESIZE(int, m_iHeartBeatInterval, HeartBeatInterval);
    CC_SYNTHESIZE(int, m_iProtocolTimeoutInterval, ProtocolTimeoutInterval);
    CC_SYNTHESIZE_RETAIN(CCString *, m_pSocketIP, SocketIP);
    CC_SYNTHESIZE(int, m_iSocketPort, SocketPort);
    CC_SYNTHESIZE_RETAIN(CCString *, m_pUID, UID);
    CC_SYNTHESIZE_RETAIN(CCString *, m_pHash, Hash);
    //add user name
    CC_SYNTHESIZE_RETAIN(CCString *, m_pUsername, Username);
    CC_SYNTHESIZE_RETAIN(CCString *, m_pDeviceID, DeviceID);
    CC_SYNTHESIZE_RETAIN(CCString *, m_pAuthKey, AuthKey);
    CC_SYNTHESIZE_RETAIN(HTimer *, m_pTimer, Timer);
    
    //add by weibo
    CC_SYNTHESIZE(int, m_iMaxConnectTime, MaxConnectTime);
    
    
public:
    void closeSocket();
    bool connectWithSocket();
    
    void fakeLoginWithAccount(const char *username, const char *password);
    void fakeLogin();
    void loginWithAccount(const char *username, const char *password);
    void login();
    void resetAccount();
    void visitWeb(const char *webSite = NULL);
    
    void changeUsername(const char *username, const char *authkey);
    
    //Eric Add from get request server list callback
    void requestRegisterWithParam0(int param0);
    void requestRegisterWithParam0(int param0,int param1);
    void requestRegisterWithInviteCode(CCString* code);
    void requestRegisterWithInviteCodeAndSid(CCString* code, int sid);
    void onReceiveServerList(CCArray* serverlist);
    //Eric Add from fetch server list
    static void disableServerList() { m_bDisableServerList = true; }
    CCDictionary*  requestServerList(bool fake);
    
    CCDictionary *getSystemInfo();
    
    void sendMessage(int msgID, CCDictionary *param);
    bool waitingForLogin();
    
    CCObject *receiveServerList(int command, CCObject *param) {
        CCArray *serverlist = dynamic_cast<CCArray *>(param);
        if (serverlist) {
            onReceiveServerList(serverlist);
        }
        return NULL;
    }
    
    bool postRequest(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel = 0, int netMode = HNET_MODE_DEFAULT);
    
//    CCObject *processRequest(int command, CCObject *param) {
//        m_oLock.lock();
//        if (m_pProtocolList->count() > 0) {
//            setNeedWait(true);
//            HNetProtocol *protocol = (HNetProtocol *)m_pProtocolList->objectAtIndex(0);
//            protocol->processProtocol();
//            m_pProtocolList->removeObjectAtIndex(0);
//        }
//        m_oLock.unlock();
//        return NULL;
//    }
    
    virtual void onDataReceived(int command, CCDictionary *result);
    
    void asyncProcessReceivedData(HObject *target, int command, const char *param) {
        m_oLock.lock();
        CCString *pParam = new CCString(param);
        HNetData *pData = new HNetData(target, command, pParam);
        m_pReceivedDataList->addObject(pData);
        pData->release();
        pParam->release();
        HTimerManager::getInstance()->asyncProcess(HInvocation::create(this, hinvocation_selector(HNetManager::processReceivedData), 0, NULL));
        m_oLock.unlock();
    }
    
    CCObject *processReceivedData(int command, CCObject *param) {
        m_oLock.lock();
        int count = m_pReceivedDataList->count();
        for (int i = 0; i < count; ++i) {
            HNetData *pData = (HNetData *)m_pReceivedDataList->objectAtIndex(i);
            pData->processReceivedData();
        }
        m_pReceivedDataList->removeAllObjects();
        m_oLock.unlock();

        // setNeedWait(false);
        // HTimerManager::getInstance()->asyncProcess(HInvocation::create(this, hinvocation_selector(HNetManager::processRequest), 0, NULL));
        
        // HTimerManager::getInstance()->asyncProcess(HInvocation::create(HNetManager::getInstance(), hinvocation_selector(HNetManager::processReceivedData), 0, NULL));
        return NULL;
    }
    
    virtual void onTimeOut(int gid, int count);
    virtual void onTick(int count);
    
    void startHeartBeat();
    void resetHeartBeat();
private:
    static bool m_bDisableServerList;
//private:
//    void sendData(const char *result);
protected:
//    CCArray *m_pProtocolList;
    CCArray *m_pReceivedDataList;
    HLock m_oLock;
    
    int m_iHeartBeatElapsed;
    
    int m_iVersion;
    int m_iBVersion;
    int m_iNotifyInterval;
    int m_reconnectTime;
    
    class HProtocolDelegate: public CCObject {
        CC_SYNTHESIZE(int, m_pAction, Action);
        CC_SYNTHESIZE_RETAIN(HObject *, m_pDelegate, Delegate);
    public:
        HProtocolDelegate(int action, HObject *delegate): m_pAction(action), m_pDelegate(NULL) { setDelegate(delegate); }
        virtual ~HProtocolDelegate() { setDelegate(NULL); }
        static HProtocolDelegate *create(int action, HObject *delegate) {
            HProtocolDelegate *pd = new HProtocolDelegate(action, delegate);
//            pd->autorelease();
            CC_AUTO_RELEASE(pd);
            return pd;
        }
    };
    CCArray *m_pProcotolDelegateStack;
    
    void onDataReceivedEx(int command, CCDictionary *result);
    
public:
    void registerProtocolDelegate(int action, HObject *delegate);
    void unregisterProtocolDelegate(int action, HObject *delegate);
    
    
    static void setPlatFormAndMarket(int platform, int market);
public:
    const char *createJsonWithAction(int action);
    bool postRequestEx(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel, int netMode, int validActionKey);
};

HNAMESPACE_END

#endif // _NET_MANAGER_H__
