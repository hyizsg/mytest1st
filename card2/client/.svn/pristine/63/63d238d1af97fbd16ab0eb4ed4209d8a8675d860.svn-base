
#include "cocos2dxframework.h"

#include <sys/sysctl.h>

#include "NetManager.h"
#include "Base.h"
#include "GameScene.h"
#include "AppDelegate.h"

#include "Haypi-JSBObject.h"
#import "Haypi/net.h"
#import "Haypi/LoginFunctions.h"

USING_HNAMESPACE;

int haypi::secondsSince1970() {
    return (int)[[NSDate date] timeIntervalSince1970];
}

const char *haypi::dateFormat(int format, int secsSince1970) {
	NSDateFormatter* dateFormat = [[NSDateFormatter alloc] init];
	[dateFormat setLocale:[NSLocale currentLocale]];
	[dateFormat setTimeStyle:format];
	[dateFormat setDateStyle:format];
    
    NSDate * dateTime = [NSDate dateWithTimeIntervalSince1970:secsSince1970];
    NSString * stringTime = [dateFormat stringFromDate:dateTime];
    
    [dateFormat release];
    
    return [stringTime UTF8String];
}

const char *haypi::adjustText(const char *content, const char *font, int fontSize, int width, int minTextLength) {
    if (minTextLength < 1) minTextLength = 1;
    NSString *c = [NSString stringWithUTF8String:content];
    if ([c length] <= minTextLength) return content;
    UIFont *f = [UIFont fontWithName:[NSString stringWithUTF8String:font] size:fontSize];
    if (!f) {
        f = [UIFont systemFontOfSize:fontSize];
        if (!f) return content;
    }
    CGSize tmp = [c sizeWithFont:f];
    if (tmp.width <= width) return content;
    
    CGSize dotSize = [@"..." sizeWithFont:f];
    width -= dotSize.width;
    NSRange r = {0, minTextLength};
    NSString *sub = [c substringWithRange:r];
    int w = [sub sizeWithFont:f].width;
    r.location = minTextLength;
    r.length = 1;
    while (r.location < [c length]) {
        sub = [c substringWithRange:r];
        tmp = [sub sizeWithFont:f];
        w += tmp.width;
        if (w >= width) {
            r.location -= 1;
            break;
        }
        r.location += 1;
    }
    sub = [c substringToIndex:r.location];
    sub = [NSString stringWithFormat:@"%@%@", sub, @"..."];
    return [sub UTF8String];
}

static void updateUserInfo(HNetManager *netManager) {
    netManager->setIsRegistered(true);
    
    char *user = getCLastUser();
    if (user) netManager->setUsername(CCString::create(user));
    char *deviceID = getHaypiDeviceID();
    if (deviceID) netManager->setDeviceID(CCString::create(deviceID));
    char *authKey = getCLastUserAuthKey(getLastGameMode());
    if (authKey) netManager->setAuthKey(CCString::create(authKey));
    
#if ((HLOGLEVEL & HLOG_MASK_INFO) != 0)
    if (netManager->getUsername()) {
		HLOGI("Username: %s ", netManager->getUsername()->getCString());
    } else {
        HLOGI("Username: null ");
    }
    if (netManager->getDeviceID()) {
		HLOGI("DeviceID: %s ", netManager->getDeviceID()->getCString());
    } else {
        HLOGI("DeviceID: null ");
    }
    if (netManager->getAuthKey()) {
		HLOGI("Authkey: %s ", netManager->getAuthKey()->getCString());
    } else {
        HLOGI("Authkey: null ");
    }
#endif
}

static char *gpPassportURL = NULL;
static char *gpLocalPassportURL = NULL;
static char *gpGameID = NULL;
static char *gpSocketIPKey = NULL;
static char *gpSocketPortKey = NULL;
static char *gpWebSite = NULL;
static char *gpVersion = NULL;

void haypi::setNetParameters(const char *passportURL, const char *localPassportURL, const char *gameID, const char *socketIPKey, const char *socketPortKey, const char *webSite, const char *version) {
    if (gpPassportURL) return; //this function is called only once.
    
    gpPassportURL = strdup(passportURL);
    gpLocalPassportURL = strdup(localPassportURL);
    gpGameID = strdup(gameID);
    gpSocketIPKey = strdup(socketIPKey);
    gpSocketPortKey = strdup(socketPortKey);
    gpWebSite = strdup(webSite);
    gpVersion = strdup(version);
}

class HProtocolData: public CCObject {
    CC_SYNTHESIZE(short, m_iNetMode, NetMode);
    CC_SYNTHESIZE(short, m_iRequestTime, RequestTime);
    CC_SYNTHESIZE(int, m_iActionKey, ActionKey);
    CC_SYNTHESIZE(int, m_iCommand, Command);
    CC_SYNTHESIZE_RETAIN(haypi::HObject *, m_pDelegate, Delegate);
    CC_SYNTHESIZE_RETAIN(CCDictionary *, m_pParam, Param);
    CC_SYNTHESIZE(bool, m_bNeedReSend, NeedReSend);
public:
    HProtocolData(): CCObject(), m_iNetMode(0), m_iRequestTime(0), m_iActionKey(0), m_iCommand(0), m_pDelegate(NULL), m_pParam(NULL), m_bNeedReSend(false) {}
    virtual ~HProtocolData() { setDelegate(NULL); setParam(NULL); }
};

static CCArray *g_pProtocols = NULL;

static HaypiSocket g_pGameSocket = NULL;

void informSocketState(AS_STATE state) {
    if (!g_pGameSocket) return;
    alterApplicationState(g_pGameSocket, state);
}

static int g_iNetStatus = HNET_STATUS_NONE;

//NSMutableDictionary *CCDictToNSDict(CCDictionary *dict) {
//    NSMutableDictionary *params = [NSMutableDictionary dictionaryWithCapacity:16];
//    if (dict) {
//        CCArray *keys = dict->allKeys();
//        int count = dict->count();
//        for (int i = 0; i < count; ++i) {
//            CCString *key = (CCString *)keys->objectAtIndex(i);
//            const CCString *value = dict->valueForKey(key->getCString());
//            [params setObject:[NSString stringWithUTF8String:value->getCString()] forKey:[NSString stringWithUTF8String:key->getCString()]];
//        }
//    }
//    return params;
//}
//
//CCDictionary *NSDictToCCDict(NSDictionary *dict) {
//    
//}

@interface HNetReceiver: NSObject <NetReceiveDelegate, SocketReceiveDelegate> {
    char *_data;
    CCDictionary *_dict;
    
    int UID;
    long long Hash;    
}

@property (nonatomic, assign) int reconnectTime;
@property (nonatomic, assign) int enabledReconnect;
-(void) reconnect:(NSObject*)obj;

@end

@implementation HNetReceiver
- (id)init
{
    self = [super init];
    if (self) {
        self.reconnectTime = 0;
        self.enabledReconnect = 0;
    }
    return self;
}

-(void)onNetFail:(char*)context {
    
}

-(void)onCommonNotification:(HaypiJson)context {
    
}

-(void)onReceive:(char*)context {
    @synchronized(self) {
#if ((HLOGLEVEL & HLOG_MASK_INFO) != 0)
        if (strlen(context) < 12 * 1024) HLOGI(context);
#endif
        HNetManager::getInstance()->asyncProcessReceivedData(NULL, -1, context);
    }
}

-(void)onUserLoggedIn:(NSNumber*)uid withHashCode:(NSNumber*)hashCode {
    informSocketState(AS_Foreground);
//    int ud = [uid intValue];
//    int hc = [hashCode longLongValue];
   // AppDelegate::getInstance()->getGameManager()->onUserLoggedIn(ud,hc);
    
   // CCDictionary *param = CCDictionary::create();
  //  HNetManager::getInstance()->postRequest(301, param, HNetManager::getInstance(), true, 0, HNET_MODE_SOCKET);

}

-(void) reconnect:(NSObject*)obj
{
    if (self.enabledReconnect <= 0)
        return;
    
    self.reconnectTime++;
    if (self.reconnectTime >= HNetManager::getInstance()->getMaxConnectTime())
    {
        AppDelegate::getInstance()->getGameManager()->onNetworkFailed();
        return;
    }
    CCString *pSocketIP = HNetManager::getInstance()->getSocketIP();
    int iSocketPport = HNetManager::getInstance()->getSocketPort();
    if (pSocketIP && (iSocketPport > 0)) {
        HNetManager::getInstance()->setUID(NULL);
        HNetManager::getInstance()->setHash(NULL);
        
        g_pGameSocket = connectServer((char *)pSocketIP->getCString(), iSocketPport, CM_Plain, self, ST_HaypiServer,PT_TCP, YES);
        if (g_pGameSocket) {
            [g_pGameSocket retain];
        }
    }
}

-(void)onReceiveJsonWithBase64Decoding:(HaypiJson)json withSocket:(HaypiSocket)socket {    // 如果可以解析为Json结构，则调用此回调，否则调用
    @synchronized(self) {
        char *context = jsonToStr(json);
#if ((HLOGLEVEL & HLOG_MASK_INFO) != 0)
        if (strlen(context) < 12 * 1024) HLOGI(context);
#endif
        HNetManager::getInstance()->asyncProcessReceivedData(NULL, -1, context);
    }
}

-(void)onReceive:(char*)context withSocket:(HaypiSocket)socket {
    @synchronized(self) {
        if (!context) return;
        int len = strlen(context);
        char *data = (char *)malloc(len + 1);
        len = base64_decode_(data, context, len);
        data[len] = '\0';
#if ((HLOGLEVEL & HLOG_MASK_INFO) != 0)
        if (strlen(data) < 12 * 1024) HLOGI(data);
#endif
        HNetManager::getInstance()->asyncProcessReceivedData(NULL, -1, data);
        free(data);
    }
}

-(void)socketDisconnected:(HaypiSocket)socket forceClose:(BOOL)forceClose {
    if (forceClose) {
        if (socket == g_pGameSocket) AppDelegate::getInstance()->getGameManager()->onForceCloseByServer();
        return;
    }
    
    disconnect(g_pGameSocket);
    g_pGameSocket = nil;
   
   [self performSelector:@selector(reconnect:) withObject:nil afterDelay:0.5];
}

-(void)socketConfirmError:(char*)context withSocket:(HaypiSocket)socket {
    
}

-(NSString*)socketReconnected:(HaypiSocket)socket needConfirm:(BOOL*)needConfirm timer:(float*)timer {
//    HLOGI("socketReconnected : %x = %x", g_pGameSocket, socket);
    if(g_pGameSocket) {
        loginHaypiSocketServer(g_pGameSocket, ST_GameServer);
    }
    return nil;
}

@end

static HNetReceiver *g_pNetReceiver = nil;

@interface LoginMainWindow: NSObject <LoginMainWindowDelegate>
-(void) onAccountClicked:(id)sender;
-(void)showProgressView;
-(void)startGame:(NSNumber*)startFlag;
@end

@implementation LoginMainWindow
-(void) onAccountClicked:(id)sender {
    HNetManager::getInstance()->setLoginStatus(0);
    AppDelegate::getInstance()->getGameManager()->onNeedAccount();
}
- (void)showProgressView {
    AppDelegate::getInstance()->getGameScene()->startAIV();
}
-(void)startGame:(NSNumber*)startFlag {
    updateUserInfo(HNetManager::getInstance());
    
    HNetManager *manager = HNetManager::getInstance();
    
    //modify by weibo, user do not need to register again
    manager->setIsFakeRegistered(true);
    manager->setIsRegistered(true);
    
    if (manager->getUseSocket()) {
        if (manager->getNeedRequestIP()) {
            CCDictionary *param = CCDictionary::create();
            param->setObject(HString::create(gpVersion), "Version");
            HNetManager::getInstance()->postRequest(HPI_SOCKETIP, param, HNetManager::getInstance(), true, 0, HNET_MODE_HTTP);
        } else {
#if 1
            manager->setSocketIP(CCString::create(getCLastUserGC(getLastGameMode())));
            manager->setSocketPort(getCLastUserGCPort(getLastGameMode()));
            manager->setUID(NULL);
            manager->setHash(NULL);
            manager->connectWithSocket();
#else
            if ((manager->getLoginStatus() == HLOGIN_FAKE_LOGIN) || (manager->getLoginStatus() == HLOGIN_FAKE_ACCOUNT)) {
                manager->setSocketIP(CCString::create(getCLastUserGC(getLastGameMode())));
                manager->setSocketPort(getCLastUserGCPort(getLastGameMode()));
                manager->setUID(NULL);
                manager->setHash(NULL);
                manager->connectWithSocket();
            } else {
                CCDictionary *param = CCDictionary::create();
                param->setObject(HString::create(gpVersion), "Version");
                HNetManager::getInstance()->postRequest(HPI_SOCKETIP, param, HNetManager::getInstance(), true, 0, HNET_MODE_HTTP);
            }
#endif            
        }
    } else {
        HNetManager::getInstance()->setLoginStatus(0);
        g_iNetStatus = HNET_STATUS_LOGINEDIN;
        AppDelegate::getInstance()->getGameScene()->startGame();
    }
    
    if (HNetManager::getInstance()->getTimer()) HTimerManager::getInstance()->unregisterTimer(HNetManager::getInstance()->getTimer());
    HNetManager::getInstance()->setTimer(HTimer::create(HNetManager::getInstance(), 0, 1, 0));
    
//    CCDictionary *param = CCDictionary::create();
//    param->setObject(CCString::create("1"), "H_ID");
//    param->setObject(CCString::create("0"), "X_S");
//    param->setObject(CCString::create("0"), "Y_S");
//    param->setObject(CCString::create("7"), "X_E");
//    param->setObject(CCString::create("7"), "Y_E");
//    HNetManager::getInstance()->postRequest(1200, param, HNetManager::getInstance(), true, 0);
//    HNetManager::getInstance()->postRequest(4005, NULL, HNetManager::getInstance(), false, 0);
}
@end

@interface LoginWindow: NSObject <LoginWindowDelegate>
-(void)onNetFail:(char*)context;
@end

@implementation LoginWindow
-(void)onNetFail:(char*)context {
    HNetManager::getInstance()->setLoginStatus(0);
    HLOGI("onNetFail: %s", context);
    CCString *errStr = new CCString(context);
    HTimerManager::getInstance()->asyncProcess(HInvocation::create(AppDelegate::getInstance()->getGameManager(), hinvocation_selector(HGameDelegate::asyncLoginError), HNETFAILED, errStr));
//    AppDelegate::getInstance()->getGameManager()->onMessageBox("General network error.", "error");
//    HMessageBox *msgBox = HMessageBox::create("General network error.", "error", HMB_OK, NULL);
//    msgBox->presentRootLayer();
}
@end


@interface LoginFunctionDelegate: NSObject<LoginFunctionProtocol>
- (void)loginErrorWithCode:(NSDictionary *)code;
- (void)changeUserNameTo:(NSString *)newName;
- (void)onReceiveServerList:(NSDictionary *)serverlist;
- (void)onReceiveLastUserState:(USER_STATE)state;
@end

@implementation LoginFunctionDelegate
-(void) onReceiveLastUserState:(USER_STATE)state
{
    HTimerManager::getInstance()->asyncProcess(HInvocation::create(AppDelegate::getInstance()->getGameManager(), hinvocation_selector(HGameDelegate::asyncReceiveLastUserState), state, NULL));
}

- (void)loginErrorWithCode:(NSDictionary *)code
{
    int errorCode = [[code valueForKey:@"ACTION_COM"] integerValue];
    char *str = jsonToStr((HaypiJson)code);
    CCString *errStr = new CCString(str);
    HTimerManager::getInstance()->asyncProcess(HInvocation::create(AppDelegate::getInstance()->getGameManager(), hinvocation_selector(HGameDelegate::asyncLoginError), errorCode, errStr));
    HNetManager::getInstance()->setLoginStatus(0);
}
- (void)changeUserNameTo:(NSString *)newName{NSLog(@"changeUserNameTo %@",newName);}
- (void)onReceiveServerList:(NSDictionary *)serverlist
{
    CCArray* serverCCarray=new CCArray();
    NSArray* serverArray= [serverlist objectForKey:@"ServerList"];
    if (!serverArray || ([serverArray count] < 1)) {
        for (NSDictionary* serverdict in serverArray)
        {
            CCDictionary* newServer=new CCDictionary();
            const char* serverStr=[[serverdict valueForKey:@"Desc"] cStringUsingEncoding:[NSString defaultCStringEncoding]];
            int serverID=[[serverdict valueForKey:@"SID"] integerValue];
            
            CCString* serverDesc=new CCString(serverStr);
            newServer->setObject(serverDesc, "Desc");
            
            HString* serverIDSting=new HString();
            serverIDSting->initWithFormat("%d",serverID);
            
            newServer->setObject(serverIDSting, "SID");
            
            serverCCarray->addObject(serverDesc);
            serverIDSting->release();
            serverDesc->release();
            newServer->release();
        }
    }
    
    HTimerManager::getInstance()->asyncProcess(HInvocation::create(HNetManager::getInstance(), hinvocation_selector(HNetManager::receiveServerList), 0, serverCCarray));
    serverCCarray->release();

//    
}


@end

static LoginMainWindow * loginMainWindow = nil;
static LoginWindow * loginWindow = nil;
static LoginFunctionDelegate * loginFunctionDelegate = nil;

HNAMESPACE_BEGIN

//HNetProtocol
//void HNetProtocol::processProtocol() {
//    HNetManager::getInstance()->postRequestEx(m_iCommand, m_pParam, m_pDelegate, m_bIgnoreDuplicaiton, m_iCommandLevel, m_iNetMode);
//}

//HNetData
void HNetData::processReceivedData() {
    CCDictionary *dict = m_pParam ? dictionaryFromJSON(m_pParam->getCString(), 0) : NULL;
    
    if (dict) { //dictionary data
        m_iCommand = dict->valueForKey("ACTION")->intValue();
//        if (m_iCommand == 2401) {
//            HLOGI("m_iCommand == 2401 ---------");
//        }
        CCString *uid = (CCString *)dict->valueForKey("UID");
        CCString *hash = (CCString *)dict->valueForKey("Hash");
        CCString *name = (CCString *)dict->valueForKey("Name");
        if (name->length() > 0&&(!HNetManager::getInstance()->getUsername())) {
            HNetManager::getInstance()->setUsername(name);
        }
        if ((uid->length() > 0) && (hash->length() > 0)) {
            HNetManager::getInstance()->setUID(uid);
            HNetManager::getInstance()->setHash(hash);
            
            if (HNetManager::getInstance()->getLoginStatus() > 0) {
                AppDelegate::getInstance()->getGameScene()->startGame();
                HNetManager::getInstance()->setLoginStatus(0);
            } else {
                AppDelegate::getInstance()->getGameManager()->onNeedUpdateData();
            }
            g_iNetStatus = HNET_STATUS_USESOCKET;
            HTimerManager::getInstance()->resumeAllTimers();
        } else {
            if (!AppDelegate::getInstance()->getGameManager()->processFailedNetResult(m_iCommand, dict)) {
                bool bFind = false;
                int key = dict->valueForKey("ACTION_KEY")->intValue();
                if (key > 0) {
                    int size = g_pProtocols->count();
                    for (int i = 0; i < size; ++i) {
                        HProtocolData *data  = (HProtocolData *)g_pProtocols->objectAtIndex(i);
                        if (data->getActionKey() == key) {
                            bFind = true;
                            setTarget(data->getDelegate());
                            setCommand(data->getCommand());
                            g_pProtocols->removeObjectAtIndex(i);
                            break;
                        }
                    }
                }
                AppDelegate::getInstance()->getGameManager()->preProcessNetResult(m_iCommand, dict);
                if (bFind) {
                    if (m_pTarget) {
                        m_pTarget->onDataReceived(m_iCommand, dict);
                    } else {
                        HNetManager::getInstance()->onDataReceived(m_iCommand, dict);
                    }
                } else {
                    if (m_iCommand > 0) {
                        HNetManager::getInstance()->onDataReceived(m_iCommand, dict);
                    }
                }
            }
        }
    } else {
    	AppDelegate::getInstance()->getGameManager()->receiveDataTimeout(m_iCommand);
        if (m_pTarget) {
            m_pTarget->onDataReceived(m_iCommand, dict);
        }
    }
//    if (m_pTarget) {
//		AppDelegate::getInstance()->getGameManager()->preProcessNetResult(m_iCommand, dict);
//		m_pTarget->onDataReceived(m_iCommand, dict);
//	} else {
//		HNetManager::getInstance()->onDataReceived(m_iCommand, dict);
//	}
//    m_pTarget->onDataReceived(m_iCommand, dict);
}

HSINGLETON_OBJECT_IMP(HNetManager);

HNetManager::HNetManager(): m_iLoginStatus(0), m_bIsRegistered(false), m_bIsFakeRegistered(false), m_bNeedWait(false), m_bUseSocket(false), m_bNeedRequestIP(false), m_bEnableHttpReplaceSocket(false), m_pSocketIP(NULL), m_pUID(NULL), m_pHash(NULL), m_pUsername(NULL), m_pDeviceID(NULL), m_pAuthKey(NULL), m_pTimer(NULL), m_iHeartBeatInterval(HHEARTBEATINTERVAL), m_iProtocolTimeoutInterval(15), m_iMaxConnectTime(10000000) {
    if (getCLastUser()) {
        m_bIsRegistered = true;
        m_bIsFakeRegistered = true;
    }
    m_iVersion = 0;
    m_iBVersion = 0;
    m_iNotifyInterval = 6;
    
//    updateUserInfo(this);
    
//    m_pProtocolList = new CCArray(8);
    m_pReceivedDataList = new CCArray(8);
    m_pProcotolDelegateStack = new CCArray(8);
    
#ifdef DEBUG
    eanbleNetLog(1);
#else
    eanbleNetLog(0);
#endif
    
//    enableNetFeature(net_feature_formdata | net_feature_zip);
    enableNetFeature(net_feature_formdata);
    
    g_pProtocols = new CCArray(8);
    g_pNetReceiver = [[HNetReceiver alloc] init];
    
    loginMainWindow = [[LoginMainWindow alloc] init];
  
    loginWindow = [[LoginWindow alloc] init];
    loginFunctionDelegate=[[LoginFunctionDelegate alloc] init];
    
    
    [LoginFunctions setLoginMainWindow:loginMainWindow];
    [LoginFunctions setLoginWindow:loginWindow];
    [LoginFunctions setDelegate:loginFunctionDelegate];
    
    [LoginFunctions setRegisterURL:[[NSString stringWithFormat:@"%s",  gpPassportURL] retain]];
    [LoginFunctions setFakeRegisterURL:[[NSString stringWithFormat:@"%s",  gpLocalPassportURL] retain]];

    [LoginFunctions setNeedRegisterWindow:FALSE];
    
    [LoginFunctions setRegisterServerUrl:false];
    
    if (!m_bDisableServerList) [LoginFunctions requestServerList];

    setCommonNotificationHandler(g_pNetReceiver);
}

HNetManager::~HNetManager() {
    [LoginFunctions setLoginMainWindow:nil];
    [LoginFunctions setLoginWindow:nil];
    [loginWindow release];
    [loginMainWindow release];
    
    setSocketIP(NULL);
    [g_pNetReceiver release];
    setUID(NULL);
    setHash(NULL);
    setTimer(NULL);
    setUsername(NULL);
    setDeviceID(NULL);
    setAuthKey(NULL);
    delete g_pProtocols;
    
    delete m_pProcotolDelegateStack;
    delete m_pReceivedDataList;
//    delete m_pProtocolList;
}

void HNetManager::closeSocket() {
    if (g_pGameSocket) {
        disconnect(g_pGameSocket);
        g_pGameSocket = nil;
    }
    g_pNetReceiver.reconnectTime = 0;
    g_pNetReceiver.enabledReconnect = 0;
    m_iLoginStatus = 0;
    
    //add by weibo
    if (g_pProtocols != NULL)
    {
        g_pProtocols->removeAllObjects();
    }
}

bool HNetManager::connectWithSocket() {
//    if (m_iLoginStatus > 0) return false;
    
    CCString *pSocketIP = HNetManager::getInstance()->getSocketIP();
    int iSocketPport = HNetManager::getInstance()->getSocketPort();
    if (pSocketIP && (iSocketPport > 0)) {
        setUID(NULL);
        setHash(NULL);
        
        g_pNetReceiver.enabledReconnect = 1;
        
        //modified by weibo, reset connecttime before manual connect
        g_pNetReceiver.reconnectTime = 0;
        
        g_pGameSocket = connectServer((char *)m_pSocketIP->getCString(), m_iSocketPort, CM_Plain, g_pNetReceiver, ST_HaypiServer,PT_TCP, YES);
        if (g_pGameSocket) {
            [g_pGameSocket retain];
        }
    } else {
        AppDelegate::getInstance()->getGameManager()->onNeedReLogin();
    }
    return true;
}

void HNetManager::fakeLoginWithAccount(const char *username, const char *password) {
    [LoginFunctions setRegisterServerUrl:true];
    if ([LoginFunctions isWaitingForLoginWithAccount]) return;
    if (m_iLoginStatus > 0) return;
    m_iLoginStatus = HLOGIN_FAKE_ACCOUNT;
    [LoginFunctions requestLoginWithName:[[NSString stringWithUTF8String:username] retain] Password:[[NSString stringWithUTF8String:password] retain]];
    
    g_iNetStatus = HNET_STATUS_NONE;
}

void HNetManager::fakeLogin() {
    if ([LoginFunctions isWaitingForLogin]) return;
    if (m_iLoginStatus > 0) return;
    m_iLoginStatus = HLOGIN_FAKE_LOGIN;
    [LoginFunctions fakeStart];
    
    g_iNetStatus = HNET_STATUS_NONE;
}

void HNetManager::loginWithAccount(const char *username, const char *password) {
    [LoginFunctions setRegisterServerUrl:false];
    if ([LoginFunctions isWaitingForLoginWithAccount]) return;
    if (m_iLoginStatus > 0) return;
    m_iLoginStatus = HLOGIN_ACCOUNT;
    [LoginFunctions requestLoginWithName:[[NSString stringWithUTF8String:username] retain] Password:[NSString stringWithUTF8String:password]];
    
    
    g_iNetStatus = HNET_STATUS_NONE;
}
bool HNetManager::waitingForLogin()
{
    return [LoginFunctions isWaitingForLogin];
}
void HNetManager::login() {
    if ([LoginFunctions isWaitingForLogin]) return;
    if (m_iLoginStatus > 0) return;
    m_iLoginStatus = HLOGIN_LOGIN;
    [LoginFunctions start];
    
    g_iNetStatus = HNET_STATUS_NONE;
}

//Eric Add from get request server list callback

void HNetManager::onReceiveServerList(CCArray* serverlist)
{
    
    AppDelegate::getInstance()->getGameManager()->onReceiveServerList(serverlist);
    
    
}
//Eric Add from fetch server list

CCDictionary*  HNetManager::requestServerList(bool fake)
{
    if (m_bDisableServerList) return NULL;
    
//    if ([LoginFunctions isWaitingForLogin]) return;
 
    [LoginFunctions setRegisterServerUrl:fake];
    
    NSDictionary* nsserverLists=[LoginFunctions requestServerList];
   // NSLog("%@",nsserverLists);
    
    if (nsserverLists==nil) {
        return NULL;
    } else {
        NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithDictionary:nsserverLists];
        [dic removeObjectForKey:@"Date"];
        char *str = jsonToStr((HaypiJson)dic);
        return str ? dictionaryFromJSON(str, 0) : NULL;
//        NSArray* serverArray= [nsserverLists objectForKey:@"ServerList"];
//        
//        CCArray* serverCCarray=CCArray::create();
//        for (NSDictionary* serverdict in serverArray)
//        {
//            CCDictionary* newServer=CCDictionary::create();
//            NSString* nsStr = [serverdict valueForKey:@"Desc"] ;
//            //const char* serverStr=[nsStr cStringUsingEncoding:[NSString defaultCStringEncoding]];
//            const char* serverStr = [nsStr UTF8String];
//            int serverID=[[serverdict valueForKey:@"SID"] integerValue];
//            
//            CCString* serverDesc=CCString::create(serverStr);
//            newServer->setObject(serverDesc, "Desc");
//            newServer->setObject(HString::createWithInteger(serverID), "SID");
//            
//
//            serverCCarray->addObject(newServer);
//        }
//        return serverCCarray;
    }
}

CCDictionary *HNetManager::getSystemInfo() {    
    size_t size = sizeof(long long);
	long long results = 0;
	int mib[2] = {CTL_HW, HW_PHYSMEM};
	sysctl(mib, 2, &results, &size, NULL, 0);
    
    CCDictionary *ret = CCDictionary::create();
    ret->setObject(HString::createWithInteger(results / 1000 / 1000), "totalMemory");
	return ret;
}

void HNetManager::resetAccount() {
    [LoginFunctions resetAccount];
    
    m_bIsRegistered = false;
    m_bIsFakeRegistered = false;
}

void HNetManager::visitWeb(const char *webSite) {
    if ([LoginFunctions isWaitingForLogin]) return;
    if (!webSite) webSite = gpWebSite;
	[[UIApplication sharedApplication] openURL: [NSURL URLWithString:[NSString stringWithUTF8String:webSite]]];
}

void HNetManager::changeUsername(const char *username, const char *authkey) {
    [LoginFunctions onChangeUserName:[NSString stringWithUTF8String:username] WithAuthKey:[NSString stringWithUTF8String:authkey]];
    updateUserInfo(this);
}

void HNetManager::sendMessage(int msgID, CCDictionary *param) {
    
}

//bool HNetManager::postRequest(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel, int netMode) {
//    return postRequestEx(command, param, delegate, ignoreDuplicaiton, commandLevel, netMode);
//}

//bool HNetManager::postRequestEx(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel, int netMode) {
//#ifdef H_CLOSE_NET
//    return false;
//#endif
//    HLOGI("Net mode %d",netMode);
//    if (netMode == HNET_MODE_DEFAULT) {
//        netMode = m_bUseSocket ? HNET_MODE_SOCKET : HNET_MODE_HTTP;
//    }
//    NSMutableDictionary *params = nil;//[NSMutableDictionary dictionaryWithCapacity:16];
//    if (param) {
//        std::string str = dictionaryToJSON(param);
//        params =  (NSMutableDictionary*)strToJson((char *)str.c_str());
//    }
//    if (!params) {
//        params = [NSMutableDictionary dictionaryWithCapacity:16];
//    }
//    
//    if (command >= 1000) {
//        static long seconds = 0;
//        if (seconds < 1) {
//            struct timeval tv;
//            if (gettimeofday(&tv, NULL) == 0) {
//                seconds = tv.tv_sec;
//            }
//        }
//        if (seconds > 1) {
//            ++seconds;
//            long s = (seconds & (~0x0F000FFF)) |  ((seconds >> 24) & 0x0F) | ((seconds & 0x0F) << 24) | (((seconds >> 12) & 0x0FF0) ^ (seconds & 0x0FF0));
//            [params setObject:[NSNumber numberWithLong:s] forKey:@"TIMESTAMP"];
//        }
//    }
//    [params setObject:[NSNumber numberWithInt:commandLevel] forKey:@"PackageLevel"];
//    
//    NSMutableDictionary *actionData = (NSMutableDictionary*)createJsonOnlyWithAction( command, getLastGameMode());
//    if (actionData) {
//        NSArray *keys = [actionData allKeys];
//        for (NSString *key in keys) {
//            [params setObject:[actionData objectForKey:key] forKey:key];
//        }
//    }
//    int key = [[params objectForKey:@"ACTION_KEY"] intValue];
//    
//    if (delegate) {
//        HProtocolData *data = new HProtocolData();
//        data->setRequestTime(32);
//        data->setActionKey(key);
//        data->setCommand(command);
//        data->setDelegate(delegate);
//        g_pProtocols->addObject(data);
//        data->autorelease();
//    }
//    
//    if ((netMode == HNET_MODE_SOCKET) && m_pUID && m_pHash) {
//        NSMutableDictionary* dictionary = [NSMutableDictionary dictionary];
//        [dictionary setObject:[NSString stringWithFormat:@"%s", m_pUID->getCString()] forKey:@"DE_USER_ID"];
//        [dictionary setObject:@"1" forKey:@"COM_TYPE"];
////        [dictionary setObject:[NSString stringWithFormat:@"%s", m_pUID->getCString()] forKey:@"DE_ID"];
//        [dictionary setObject:[NSString stringWithFormat:@"%s", m_pHash->getCString()] forKey:@"Hash"];
////        if (m_pUsername) [dictionary setObject:[NSString stringWithFormat:@"%s", m_pUsername->getCString()] forKey:@"DE_USER_NAME"];
////        [dictionary setObject:@"1111111111111" forKey:@"DE_TIME"];
//        [dictionary setObject:[params objectForKey:@"ACTION"] forKey:@"ACTION"];
//        [params removeObjectForKey:@"AUTH_KEY"];
//        [params removeObjectForKey:@"PackageLevel"];
//        [params removeObjectForKey:@"GAMEPLAY_ID"];
//        [dictionary setObject:[NSString stringWithFormat:@"%s", jsonToStr((HaypiJson)params)] forKey:@"DE_VALUE"];
//#if ((HLOGLEVEL & HLOG_MASK_INFO) != 0)
//        char *pData = jsonToStr((HaypiJson)dictionary);
//        if (strlen(pData) < 12 * 1024) HLOGI("sending:%s", jsonToStr((HaypiJson)dictionary));
//#endif
//        sendCmdToHaypiServer(g_pGameSocket, (HaypiJson)dictionary);
//        resetHeartBeat();
//        HLOGI("sending: over!");
//    } else {
////        if (m_pUsername) [params setObject:[NSString stringWithFormat:@"%s", m_pUsername->getCString()] forKey:@"DE_USER_NAME"];
//        [params setObject:@"0" forKey:@"COM_TYPE"];
//        char* clientUrl = getCLastClientUrl( getLastGameMode() );
//        char* cmdStr = jsonToStr((HaypiJson)params);
//        sendCmd(key, cmdStr, clientUrl, g_pNetReceiver, 30);
//    }
//    
//    return true;
//}

void HNetManager::requestRegisterWithInviteCode(CCString* code)
{
    if ([LoginFunctions isWaitingForLogin]) return;
    if (m_iLoginStatus > 0) return;
    m_iLoginStatus = HLOGIN_LOGIN;
    [LoginFunctions requestRegisterWithInviteUID:[NSString stringWithUTF8String:code->getCString()]];
}

void HNetManager::requestRegisterWithInviteCodeAndSid(cocos2d::CCString *code, int sid)
{
    if ([LoginFunctions isWaitingForLogin]) return;
    if (m_iLoginStatus > 0) return;
    m_iLoginStatus = HLOGIN_LOGIN;
    [LoginFunctions requestRegisterWithInviteUID:[NSString stringWithUTF8String:code->getCString()] ServerID:sid];
}

void HNetManager::requestRegisterWithParam0(int param0) {
    if ([LoginFunctions isWaitingForLogin]) return;
    if (m_iLoginStatus > 0) return;
    m_iLoginStatus = HLOGIN_LOGIN;
    [LoginFunctions requestRegisterWithParam0:param0];
}

void HNetManager::requestRegisterWithParam0(int param0,int param1) {
    if ([LoginFunctions isWaitingForLogin]) return;
    if (m_iLoginStatus > 0) return;
    m_iLoginStatus = HLOGIN_LOGIN;
    [LoginFunctions requestRegisterWithParam0:param0 Param1:param1];
}

void HNetManager::onDataReceived(int command, CCDictionary *result) {
//    if (!result) return;
    
    switch (command) {
        case HPI_SOCKETIP: {
            if (!result || (result->valueForKey("ACTION_COM")->intValue() != 0)) { //error
                if (result) {
                    AppDelegate::getInstance()->getGameManager()->onMessageBox(result->valueForKey("ExtraInfo")->getCString(), "error");
                } else {
                    AppDelegate::getInstance()->getGameManager()->onMessageBox("Login failed, please do it again.", "error");
                }
                m_iLoginStatus = 0;
            } else {
                setSocketIP((CCString *)result->valueForKey(gpSocketIPKey));
                setSocketPort(result->valueForKey(gpSocketPortKey)->intValue());
                if (m_pSocketIP && (m_iSocketPort > 0)) {
                    setUID(NULL);
                    setHash(NULL);
                    g_pGameSocket = connectServer((char *)m_pSocketIP->getCString(), m_iSocketPort, CM_Plain, g_pNetReceiver, ST_HaypiServer,PT_TCP, YES);
                    if (g_pGameSocket) {
                        [g_pGameSocket retain];
                    }
//                    HLOGI("HPI_SOCKETIP socket: %x", g_pGameSocket);
                }
            }
        }
            break;
        default:
            onDataReceivedEx(command, result);
            break;
    }
}

//void HNetManager::asyncProcessReceivedData(HObject *target, int command, CCDictionary *param) {
//    m_oLock.lock();
//    m_pReceivedDataList->addObject(HNetData::create(target, command, param));
//    HTimerManager::getInstance()->asyncProcess(HInvocation::create(this, hinvocation_selector(HNetManager::processReceivedData), 0, NULL));
//    m_oLock.unlock();
//}
//
//CCObject *HNetManager::processReceivedData(int command, CCObject *param) {
//    m_oLock.lock();
//    int count = m_pReceivedDataList->count();
//    for (int i = 0; i < count; ++i) {
//        HNetData *pData = (HNetData *)m_pReceivedDataList->objectAtIndex(i);
//        pData->processReceivedData();
//    }
//    m_pReceivedDataList->removeAllObjects();
//    m_oLock.unlock();
//}

//void HNetManager::sendData(const char *result) {
//
//}

void HNetManager::onTimeOut(int gid, int count) {
    if (g_iNetStatus == HNET_STATUS_NONE) return;
    m_iNotifyInterval -= count;
    if (m_iNotifyInterval < 0) {
        CCDictionary *param = CCDictionary::create();
        param->setObject(HString::createWithInteger(m_iVersion), "Version");
        param->setObject(HString::createWithInteger(m_iBVersion), "BVersion");
//        postRequest(HPI_NOTIFICATION, param, this, false, 0, HNET_MODE_HTTP);
        m_iNotifyInterval = 6;
    }
        
    for (int i = g_pProtocols->count() - 1; i >= 0; --i) {
        HProtocolData *data  = (HProtocolData *)g_pProtocols->objectAtIndex(i);
        if (data->getNeedReSend()) {
            if ((data->getNetMode() == HNET_MODE_SOCKET) && m_pUID && m_pHash) {
                if (m_pUID) data->getParam()->setObject(HString::create(m_pUID->m_sString), "DE_USER_ID");
                if (m_pHash) data->getParam()->setObject(HString::create(m_pHash->m_sString), "Hash");
                std::string content = dictionaryToJSON(data->getParam());
                sendCmdToHaypiServer(g_pGameSocket, (HaypiJson)strToJson((char *)content.c_str()));
                data->setNeedReSend(false);
                data->setRequestTime(m_iProtocolTimeoutInterval);
            }
        } else {
            int leftSeconds = data->getRequestTime() - count;
            if (leftSeconds < 1) { //timeout
                if (data->getDelegate() != NULL) {
                    AppDelegate::getInstance()->getGameManager()->receiveDataTimeout(data->getCommand());
                    data->getDelegate()->onDataReceived(data->getCommand(), NULL);
                }
                g_pProtocols->removeObjectAtIndex(i);
                
                setNeedWait(false);
            } else {
                data->setRequestTime(leftSeconds);
            }
        }
    }
}

const char *HNetManager::createJsonWithAction(int action) {
    NSMutableDictionary *actionData = (NSMutableDictionary*)createJsonOnlyWithAction(action, getLastGameMode());
    if (actionData) {
        const char *pRet = jsonToStr((HaypiJson)actionData);
        deleteJson((HaypiJson)actionData);
        return pRet;
    }
    return NULL;
}

bool HNetManager::postRequestEx(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel, int netMode, int validActionKey) {
//    if (delegate) {
    if (ignoreDuplicaiton) { //add by weibo, ignore duplicate message
        for(int i=0;i<g_pProtocols->count();i++)
        {
            HProtocolData *item = (HProtocolData *)g_pProtocols->objectAtIndex(i);
            if (item->getCommand() == command)
                return false;
        }
    }
    
        HProtocolData *data = new HProtocolData();
        data->setNetMode(netMode);
        data->setRequestTime(m_iProtocolTimeoutInterval);
        data->setActionKey(validActionKey);
        data->setCommand(command);
        data->setDelegate(delegate);
        data->setParam(param);
        g_pProtocols->addObject(data);
//        data->autorelease();
        CC_AUTO_RELEASE(data);
//    }
    
    if (netMode == HNET_MODE_SOCKET) {
        if (m_pUID && m_pHash) {
            std::string content = dictionaryToJSON(param);
            
            #if ((HLOGLEVEL & HLOG_MASK_INFO) != 0)
                if (content.length() < 12 * 1024) HLOGI("sending:%s", content.c_str());
            #endif
            
            if (!sendCmdToHaypiServer(g_pGameSocket, (HaypiJson)strToJson((char *)content.c_str()))) {
                data->setNeedReSend(true);
            }
        } else {
            data->setNeedReSend(true);
        }
    } else {
        std::string content = dictionaryToJSON(param);
        char* clientUrl = getCLastClientUrl(getLastGameMode());
        sendCmd(validActionKey, (char *)content.c_str(), clientUrl, g_pNetReceiver, 30);
    }
//#if ((HLOGLEVEL & HLOG_MASK_INFO) != 0)
//    if (content.length() < 12 * 1024) HLOGI("sending:%s", content.c_str());
//#endif
    return true;
}

void HNetManager::setPlatFormAndMarket(int platform, int market)
{
    [LoginFunctions setPlatform:(PASSPORT_PLATFORM)platform market:(PASSPORT_MARKET)market];
    if (platform > 0)
    {
        [LoginFunctions setPlatformAccount:@"" token:@""];
    }
}

HNAMESPACE_END
