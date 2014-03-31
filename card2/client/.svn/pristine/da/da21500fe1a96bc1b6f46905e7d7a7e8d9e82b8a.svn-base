
#include "cocos2dxframework.h"
#include "NetManager.h"
#include "Base.h"
#include "GameScene.h"
#include "AppDelegate.h"

#include "platform/android/jni/JniHelper.h"
#include <jni.h>
//#include <android/log.h>
//#include "Haypi-JSBObject.h"
#include <time.h>

#define HCOMMAND_SETLOCALE    -1000

USING_HNAMESPACE;

static char *gpPassportURL = NULL;
static char *gpLocalPassportURL = NULL;
static char *gpGameID = NULL;
static char *gpSocketIPKey = NULL;
static char *gpSocketPortKey = NULL;
static char *gpWebSite = NULL;
static char *gpVersion = NULL;

#define getStaticMethodInfo(a, b, c, d) if (!JniHelper::getStaticMethodInfo(a, b, c, d)) HASSERT(0, c " does not exist in java")

extern "C" {
void jniInitialize(const char *gameID, const char *registerURL, const char *fakeRegisterURL, const char *keySocketIP, const char *keySocketPort, const char *version, bool useSocket);
}

void haypi::setNetParameters(const char *passportURL, const char *localPassportURL, const char *gameID, const char *socketIPKey, const char *socketPortKey, const char *webSite, const char *version) {
    if (gpPassportURL) return; //this function is called only once.

    gpPassportURL = strdup(passportURL);
    gpLocalPassportURL = strdup(localPassportURL);
    gpGameID = strdup(gameID);
    gpSocketIPKey = strdup(socketIPKey);
    gpSocketPortKey = strdup(socketPortKey);
    gpWebSite = strdup(webSite);
    gpVersion = strdup(version);

	jniInitialize(gpGameID, gpPassportURL, gpLocalPassportURL, gpSocketIPKey, gpSocketPortKey, gpVersion, true);
}

#define HJAVA_NET_MANAGER    "com/haypi/gameframework/GameFramework"

int haypi::secondsSince1970() {
    return time(NULL);
    //time_t lTime;
    //time(&lTime);
    //return lTime;
}

const char *haypi::dateFormat(int format, int secsSince1970) {
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "formatDate", "(II)Ljava/lang/String;");
	JNIEnv *env = info.env;
	jstring json = (jstring)env->CallStaticObjectMethod(info.classID, info.methodID, format, secsSince1970);
	CCString *pRet = NULL;
	if (json) {
		const char* chars = env->GetStringUTFChars(json, NULL);
		pRet = CCString::create(chars);
		env->ReleaseStringUTFChars(json, chars);
	}

	//detachEnv();
	return pRet ? pRet->getCString() : NULL;
    //return ctime(&secsSince1970);
}

const char *haypi::adjustText(const char *content, const char *font, int fontSize, int width, int minTextLength) {
    return content;
}

#define LOGIN_WITH_NEW_ACCOUNT 	-1
#define LOGIN_NEED_ACCOUNT 		-2
#define LOGIN_SHOW_PROGRESS 	-3
#define LOGIN_FAILED 			-4
#define LOGIN_TO_SOCKET 		-5
#define LOGIN_SUCCESS 			-6
#define LOGIN_TO_SOCKET_FAILED  -7
#define LOGIN_TO_GAMECENTER_FAILED  	-8
#define LOGIN_TO_SOCKET_NEED_RELOGIN 	-9
#define LOGIN_TO_GAMECENTER_NEED_RELOGIN  -10
#define LOGIN_TO_GAMECENTER_BROKEN -11
#define SNS_LOGIN_RESULT -12
#define NEED_RELOGIN -14

#define COMMAON_PROTOCOL		-100

static int g_iNetStatus = HNET_STATUS_NONE;

extern "C" {
//static jobject gJavaNetManager = NULL;
static JavaVM *gVM = NULL;
static JNIEnv *gENV = NULL;
JNIEnv *attachEnv() {
	JNIEnv *env = NULL;
	JavaVM *vm = JniHelper::getJavaVM();
	if (vm) {
		if (vm->AttachCurrentThread(&env, NULL) < 0) env = NULL;
	}
//	HLOGI("attachEnv: %x", env);
	return env;
}
void detachEnv() {
	JavaVM *vm = JniHelper::getJavaVM();
	if (vm) {
//		vm->DetachCurrentThread();
	}
//	HLOGI("detachEnv");
}

static void updateUserInfo(HNetManager *netManager) {
	netManager->setIsRegistered(true);

	//if (!gJavaNetManager) return;
	JniMethodInfo info;
	HLOGI("updateUserInfo");
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "getUserInfo", "()Ljava/lang/String;");
	JNIEnv *env = info.env;
	jstring userinfo = (jstring)env->CallStaticObjectMethod(info.classID, info.methodID);
	if (userinfo) {
		const char* chars = env->GetStringUTFChars(userinfo, NULL);
		HLOGI("updateUserInfo: %s", chars);
		CCDictionary *dict = dictionaryFromJSON(chars, 0);
		if (dict) {
			const CCString *username = dict->valueForKey("username");
			const CCString *deviceid = dict->valueForKey("deviceid");
			const CCString *authkey = dict->valueForKey("authkey");
			if (username) netManager->setUsername(CCString::create(username->m_sString));
			if (deviceid) netManager->setDeviceID(CCString::create(deviceid->m_sString));
			if (authkey) netManager->setAuthKey(CCString::create(authkey->m_sString));
		}
		env->ReleaseStringUTFChars(userinfo, chars);
	}
	detachEnv();
	
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

JNIEXPORT jbyteArray JNICALL Java_com_haypi_gameframework_GameFramework_GetFileData(JNIEnv* env, jobject thiz, jstring filename) {
	const char* chars = env->GetStringUTFChars(filename, NULL);
	if (!chars) return NULL;
	jbyteArray pRet = NULL;
	unsigned long size = 0;
    unsigned char *pData = CCFileUtils::sharedFileUtils()->getFileData(chars, "rb", &size);
    if (pData && (size > 0)) {
        pRet = env->NewByteArray(size);
        env->SetByteArrayRegion(pRet, 0, size, (const jbyte *)pData);
        delete [] pData;
    }
	env->ReleaseStringUTFChars(filename, chars);
	return pRet;
}

JNIEXPORT int JNICALL Java_com_haypi_gameframework_GameFramework_requestScreenOrientation(JNIEnv*  env, jobject thiz) {
	return requestScreenOrientation();
}

JNIEXPORT void JNICALL Java_com_haypi_gameframework_GameFramework_registerToNative(JNIEnv*  env, jobject thiz, jobject netManager, jboolean isRegistered, jboolean isFakeRegistered) {
//	HLOGI("registerToNative: %x. registered:%d, fake registered:%d", netManager, isRegistered, isFakeRegistered);
	//gJavaNetManager = netManager;
	HNetManager::getInstance()->setIsRegistered(isRegistered);
	HNetManager::getInstance()->setIsFakeRegistered(isFakeRegistered);
	//jniInitialize(gpGameID, gpPassportURL, gpLocalPassportURL, gpSocketIPKey, gpSocketPortKey, gpVersion, true);
}

JNIEXPORT void JNICALL Java_com_haypi_gameframework_GameFramework_commandToNative(JNIEnv*  env, jobject thiz, int command, jstring data) {
	const char* chars = env->GetStringUTFChars(data, NULL);
	switch (command) {
	case HCOMMAND_SETLOCALE: {
		haypi::setLocaleCode(chars);
	}
		break;
	default:
		AppDelegate::getInstance()->getGameManager()->onCommand(command, chars);
		break;
	}
	env->ReleaseStringUTFChars(data, chars);
}

JNIEXPORT void JNICALL Java_com_haypi_gameframework_GameFramework_notifyForLoginToNative(JNIEnv*  env, jobject thiz, int notify, jstring data) {
	switch (notify) {
	case LOGIN_WITH_NEW_ACCOUNT:
		HLOGI("login: with new account.");
	    //HNetManager::getInstance()->setLoginStatus(0);
		break;
	case LOGIN_NEED_ACCOUNT: {
		HLOGI("login: need one account.");
    	HNetManager::getInstance()->setLoginStatus(0);
	    AppDelegate::getInstance()->getGameManager()->onNeedAccount();
	}
		break;
	case LOGIN_SHOW_PROGRESS: {
		AppDelegate::getInstance()->getGameScene()->startAIV();
	}
		break;
	case LOGIN_FAILED: {
		HLOGI("login: failed.");
    	HNetManager::getInstance()->setLoginStatus(0);
	    //AppDelegate::getInstance()->getGameManager()->onMessageBox("General network error.", "error");
		const char* chars = env->GetStringUTFChars(data, NULL);
		CCString *errStr = new CCString(chars);
		CCDictionary *dict = dictionaryFromJSON(chars, 0);
		int errorCode = ((CCString *)dict->valueForKey("ACTION_COM"))->intValue();
		HTimerManager::getInstance()->asyncProcess(HInvocation::create(AppDelegate::getInstance()->getGameManager(), hinvocation_selector(HGameDelegate::asyncLoginError), errorCode, errStr));
		env->ReleaseStringUTFChars(data, chars);
	}
		break;
	case LOGIN_TO_SOCKET: {
		HLOGI("login: with socket.");
	    if (data) {
	    	const char* chars = env->GetStringUTFChars(data, NULL);
	    	CCDictionary *dict = dictionaryFromJSON(chars, 0);
	    	if (dict) {
	    	    CCString *uid = (CCString *)dict->valueForKey("UID");
	    	    CCString *hash = (CCString *)dict->valueForKey("Hash");
	    	    //CCString *deviceID = (CCString *)dict->valueForKey("DeviceID");
	    	    if (uid->length() > 0) HNetManager::getInstance()->setUID(uid);
	    	    if (hash->length() > 0) HNetManager::getInstance()->setHash(hash);
	    	   // if (deviceID->length() > 0) HNetManager::getInstance()->setDeviceID(deviceID);
	    	}
	    	env->ReleaseStringUTFChars(data, chars);
	    }

        if (HNetManager::getInstance()->getLoginStatus() > 0) {
            AppDelegate::getInstance()->getGameScene()->startGame();
        } else {
        	AppDelegate::getInstance()->getGameManager()->onNeedUpdateData();
        }    	
        HNetManager::getInstance()->setLoginStatus(0);
        g_iNetStatus = HNET_STATUS_USESOCKET;

		updateUserInfo(HNetManager::getInstance());
				
        HTimerManager::getInstance()->resumeAllTimers();
//		JSONObject dict = mManager.CreateJsonWithAction(301);
//		sendDataWithSocket(301, dict);
	}
		break;
	case LOGIN_SUCCESS: {
		HLOGI("login: success.");
    	HNetManager::getInstance()->setLoginStatus(0);
	}
		break;
	case LOGIN_TO_SOCKET_FAILED: {
		HLOGI("LOGIN_TO_SOCKET_FAILED");
	}
		break;
	case LOGIN_TO_GAMECENTER_FAILED: {
		HLOGI("LOGIN_TO_GAMECENTER_FAILED");
	}
		break;
	case LOGIN_TO_SOCKET_NEED_RELOGIN: {
		HLOGI("LOGIN_TO_SOCKET_NEED_RELOGIN");
		AppDelegate::getInstance()->getGameManager()->onForceCloseByServer();
	}
		break;
	case LOGIN_TO_GAMECENTER_NEED_RELOGIN: {
		HLOGI("LOGIN_TO_GAMECENTER_NEED_RELOGIN");
	}
		break;
	case LOGIN_TO_GAMECENTER_BROKEN: {
		HLOGI("LOGIN_TO_GAMECENTER_BROKEN");
	}
		break;
	case SNS_LOGIN_RESULT: {
		const char* chars = env->GetStringUTFChars(data, NULL);
		HLOGI("SNS_LOGIN_RESULT: %s", chars);
		CCDictionary *dict = dictionaryFromJSON(chars, 0);
		int state = ((CCString *)dict->valueForKey("STATE"))->intValue();
		AppDelegate::getInstance()->getGameManager()->onReceiveLastUserState(state);
		env->ReleaseStringUTFChars(data, chars);
		break;
	}
	case NEED_RELOGIN: {
		AppDelegate::getInstance()->getGameManager()->onNeedReLogin();
		break;
	}
	}
}

JNIEXPORT void JNICALL Java_com_haypi_gameframework_GameFramework_startGameToNative(JNIEnv*  env, jobject thiz) {
	HLOGI("startGameToNative: .......");
	if (!HNetManager::getInstance()->getUseSocket()) {
    	HNetManager::getInstance()->setLoginStatus(0);
		g_iNetStatus = HNET_STATUS_LOGINEDIN;
		HLOGI("startGameToNative: ...startGame....");
		updateUserInfo(HNetManager::getInstance());
		AppDelegate::getInstance()->getGameScene()->startGame();


    if (HNetManager::getInstance()->getTimer()) HTimerManager::getInstance()->unregisterTimer(HNetManager::getInstance()->getTimer());
		HNetManager::getInstance()->setTimer(HTimer::create(HNetManager::getInstance(), 0, 1, 0));
	}
}

JNIEXPORT void JNICALL Java_com_haypi_gameframework_GameFramework_notificationToNative(JNIEnv*  env, jobject thiz, int identifier, jstring result) {
	switch (identifier) {
	case 98: // private chat
		HLOGI("notification: private chat");
		break;
	case 99: //new email
		HLOGI("notification: new email");
		break;
	case 101: //system broadcast
		HLOGI("recieved notification: system broadcast: ");
		break;
	case 102: //server maintain
		HLOGI("notification: server maintain: start after ");
		break;
	}
}

JNIEXPORT void JNICALL Java_com_haypi_gameframework_GameFramework_dataReceivedToNative(JNIEnv*  env, jobject thiz, int command, jstring result, jlong delegate) {
//	HLOGI("dataReceivedToNative:cmd(%d), delegate(0x%x), threadID(%ld)", command, (long)delegate, pthread_self());
//	HLOGI("dataReceivedToNative: delegate type(0x%x)", dynamic_cast<HObject *>((HObject *)delegate));
	HObject *receiver = (HObject *)delegate;
//	CCString *content = NULL;
	if (result) {
		const char* chars = env->GetStringUTFChars(result, NULL);
		HNetManager::getInstance()->asyncProcessReceivedData(receiver, command, chars);
//		content = CCString::create(chars);
		env->ReleaseStringUTFChars(result, chars);
	} else {
		HNetManager::getInstance()->asyncProcessReceivedData(receiver, command, "");
	}
}

void jniInitialize(const char *gameID, const char *registerURL, const char *fakeRegisterURL, const char *keySocketIP, const char *keySocketPort, const char *version, bool useSocket) {
	//if (!gJavaNetManager) return;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "initialize", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID, env->NewStringUTF(gameID), env->NewStringUTF(registerURL), env->NewStringUTF(fakeRegisterURL), env->NewStringUTF(keySocketIP), env->NewStringUTF(keySocketPort), env->NewStringUTF(version), useSocket ? JNI_TRUE : JNI_FALSE);
	detachEnv();
}

const char *jniCreateJsonWithAction(int action) {
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "CreateJsonWithAction", "(I)Ljava/lang/String;");
	JNIEnv *env = info.env;
	jstring json = (jstring)env->CallStaticObjectMethod(info.classID, info.methodID, action);
	CCString *pRet = NULL;
	if (json) {
		const char* chars = env->GetStringUTFChars(json, NULL);
		HLOGI("json with action: %s", chars);
		pRet = CCString::create(chars);
		env->ReleaseStringUTFChars(json, chars);
	}

	detachEnv();
	return pRet ? pRet->getCString() : NULL;
}

static void jniChangeUsername(const char *username, const char *authkey) {
	//if (!gJavaNetManager) return;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "changeUserInfo", "(Ljava/lang/String;Ljava/lang/String;)V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID, env->NewStringUTF(username), env->NewStringUTF(authkey));
	detachEnv();
}

void jniFakeLoginWithAccount(const char *username, const char *password) {
	//if (!gJavaNetManager) return;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "FakeLoginWithAccount", "(Ljava/lang/String;Ljava/lang/String;)V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID, env->NewStringUTF(username), env->NewStringUTF(password));
	detachEnv();
}

void jniFakeLogin() {
	//if (!gJavaNetManager) return;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "FakeLogin", "()V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID);
	detachEnv();
}

void jniLoginWithAccount(const char *username, const char *password) {
	//if (!gJavaNetManager) return;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "LoginWithAccount", "(Ljava/lang/String;Ljava/lang/String;)V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID, env->NewStringUTF(username), env->NewStringUTF(password));
	detachEnv();
}

void jniLogin() {
	//if (!gJavaNetManager) return;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "Login", "()V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID);
	detachEnv();
}

void jniResetAccount() {
	//if (!gJavaNetManager) return;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "ResetAccount", "()V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID);
	detachEnv();
}

void jniVisitWeb(const char *webSite) {
	//if (!gJavaNetManager) return;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "VisitWeb", "(Ljava/lang/String;)V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID, env->NewStringUTF(webSite));
	detachEnv();
}

void jniSendMessage(int msgID, const char *param) {
	//if (!gJavaNetManager) return;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "ReceiveMessage", "(ILjava/lang/String;)V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID, msgID, env->NewStringUTF(param));
	detachEnv();
}

int jniNewActionKey() {
	//if (!gJavaNetManager) return 0;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "NewActionKey", "()I");
	JNIEnv *env = info.env;
	int ret = env->CallStaticIntMethod(info.classID, info.methodID);
	detachEnv();
	return ret;
}

int jniPostRequest(int command, const char *param, jlong delegate, jboolean ignoreDuplicaiton, int commandLevel, int netMode, int validActionKey) {
//	HLOGI("jniPostRequest:cmd(%d), delegate(0x%x), threadID(%ld)", command, delegate, pthread_self());
//	HLOGI("jniPostRequest: delegate type(0x%x)", dynamic_cast<HObject *>((HObject *)delegate));
#ifdef H_CLOSE_NET
    return 0;
#endif
	//if (!gJavaNetManager) return 0;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "PostRequest", "(ILjava/lang/String;JZIII)I");
	JNIEnv *env = info.env;
	int ret = env->CallStaticIntMethod(info.classID, info.methodID, command, env->NewStringUTF(param), delegate, ignoreDuplicaiton, commandLevel, netMode, validActionKey);
	detachEnv();
	return ret;
}

void jniClearAll() {
	//if (!gJavaNetManager) return;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "ClearAll", "()V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID);
	detachEnv();
}

void jniRequestRegisterWithInviteUIDAndSid(const char *inviteUID, int sid) {
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "register", "(ILjava/lang/String;)V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID, sid, env->NewStringUTF(inviteUID));
	detachEnv();
}

void jniRequestRegisterWithInviteCode(const char *inviteCode) {
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "registerWithInviteCode", "(Ljava/lang/String;)V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID, env->NewStringUTF(inviteCode));
	detachEnv();
}

void jniRequestRegisterWithParam0(int param0, int param1) {
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "registerWithServerID", "(II)V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID, param0, param1);
	detachEnv();
}

void jniCloseSocket() {
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "closeSocket", "()V");
	JNIEnv *env = info.env;
	env->CallStaticVoidMethod(info.classID, info.methodID);
	detachEnv();
}

bool jniConnectWithSocket() {
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "connectWithSocket", "()Z");
	JNIEnv *env = info.env;
	bool bRet = env->CallStaticBooleanMethod(info.classID, info.methodID);
	detachEnv();
	return bRet;
}

/*
int notifyToJava(int command, const char *data) {
	//if (!gJavaNetManager) return 0;
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "onCommand", "(ILjava/lang/String;)I");
	JNIEnv *env = info.env;
	int ret = 0;
	if (data) {
		ret = env->CallStaticIntMethod(info.classID, info.methodID, command, env->NewStringUTF(data));
	} else {
		ret = env->CallStaticIntMethod(info.classID, info.methodID, command, NULL);
	}
	detachEnv();
	return ret;
}*/
}

//HNetData
void HNetData::processReceivedData() {
	// HLOGI("HNetData::processReceivedData begin");
    CCDictionary *dict = m_pParam ? dictionaryFromJSON(m_pParam->getCString(), 0) : NULL;
    if (dict) {
    	if (!AppDelegate::getInstance()->getGameManager()->processFailedNetResult(m_iCommand, dict)) {
				AppDelegate::getInstance()->getGameManager()->preProcessNetResult(m_iCommand, dict);
    		if (m_pTarget) {
					m_pTarget->onDataReceived(m_iCommand, dict);
				} else {
					HNetManager::getInstance()->onDataReceived(m_iCommand, dict);
				}
    	}
    } else {
    	AppDelegate::getInstance()->getGameManager()->receiveDataTimeout(m_iCommand);
    	if (m_pTarget) {
				m_pTarget->onDataReceived(m_iCommand, dict);
			}
    }
    // m_pTarget->onDataReceived(m_iCommand, dict);
	// HLOGI("HNetData::processReceivedData end");
}

//NetManager
HSINGLETON_OBJECT_IMP(HNetManager);

HNetManager::HNetManager(): m_iLoginStatus(0),  m_bIsRegistered(false), m_bIsFakeRegistered(false), m_bNeedWait(false), m_bUseSocket(true), m_bNeedRequestIP(false), m_bEnableHttpReplaceSocket(false), m_pSocketIP(NULL), m_pUID(NULL), m_pHash(NULL), m_pUsername(NULL), m_pDeviceID(NULL), m_pAuthKey(NULL), m_pTimer(NULL), m_iHeartBeatInterval(HHEARTBEATINTERVAL) {
	//if (getCLastUser()) m_bIsRegistered = true;

//	m_pProtocolList = new CCArray(8);
    m_pReceivedDataList = new CCArray(8);
    m_pProcotolDelegateStack = new CCArray(8);
}

HNetManager::~HNetManager() {
    setSocketIP(NULL);
    setUID(NULL);
    setHash(NULL);
    setTimer(NULL);
    setUsername(NULL);
    setDeviceID(NULL);
    setAuthKey(NULL);

    delete m_pProcotolDelegateStack;
    delete m_pReceivedDataList;
//    delete m_pProtocolList;
}

void HNetManager::closeSocket() {    
    m_iLoginStatus = 0;
	jniCloseSocket();
}

bool HNetManager::connectWithSocket() {
    if (m_iLoginStatus > 0) return false;
    return jniConnectWithSocket();
}


void HNetManager::setPlatFormAndMarket(int platform, int market)
{

}

void HNetManager::fakeLoginWithAccount(const char *username, const char *password) {
    if (m_iLoginStatus > 0) return;
    m_iLoginStatus = HLOGIN_FAKE_ACCOUNT;
	jniFakeLoginWithAccount(username, password);
	g_iNetStatus = HNET_STATUS_NONE;
}

void HNetManager::fakeLogin() {
	if (m_iLoginStatus > 0) return;
	m_iLoginStatus = HLOGIN_FAKE_LOGIN;
	jniFakeLogin();
	g_iNetStatus = HNET_STATUS_NONE;
}

void HNetManager::loginWithAccount(const char *username, const char *password) {
	if (m_iLoginStatus > 0) return;
	m_iLoginStatus = HLOGIN_ACCOUNT;
	jniLoginWithAccount(username, password);
	g_iNetStatus = HNET_STATUS_NONE;
}

void HNetManager::login() {
	if (m_iLoginStatus > 0) return;
	m_iLoginStatus = HLOGIN_LOGIN;
	jniLogin();
	g_iNetStatus = HNET_STATUS_NONE;
}

CCDictionary* HNetManager::requestServerList(bool fake) {
    if (m_bDisableServerList) return NULL;

	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "getServerList", "(Z)Ljava/lang/String;");
	JNIEnv *env = info.env;
	jstring serverList = (jstring)env->CallStaticObjectMethod(info.classID, info.methodID, fake);
	CCDictionary *ret = NULL;
	if (serverList) {
		const char* chars = env->GetStringUTFChars(serverList, NULL);
		HLOGI("serverList: %s", chars);
		ret = dictionaryFromJSON(chars, 0);
		env->ReleaseStringUTFChars(serverList, chars);
	}
	detachEnv();
	return ret;
}

CCDictionary *HNetManager::getSystemInfo() {
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "getSystemInfo", "()Ljava/lang/String;");
	JNIEnv *env = info.env;
	jstring serverList = (jstring)env->CallStaticObjectMethod(info.classID, info.methodID);
	CCDictionary *ret = NULL;
	if (serverList) {
		const char* chars = env->GetStringUTFChars(serverList, NULL);
		HLOGI("system info: %s", chars);
		ret = dictionaryFromJSON(chars, 0);
		env->ReleaseStringUTFChars(serverList, chars);
	}
	detachEnv();
	return ret;
}

void HNetManager::resetAccount() {
    jniResetAccount();

    m_bIsRegistered = false;
    m_bIsFakeRegistered = false;
}

void HNetManager::visitWeb(const char *webSite) {
	if (!webSite) webSite = gpWebSite;
	jniVisitWeb(webSite);
}

void HNetManager::changeUsername(const char *username, const char *authkey) {
	jniChangeUsername(username, authkey);
	updateUserInfo(this);
}

void HNetManager::sendMessage(int msgID, CCDictionary *param) {
	std::string params = param ? dictionaryToJSON(param) : "";
    jniSendMessage(msgID, params.c_str());
}

bool HNetManager::waitingForLogin() {
	return false;
}

//bool HNetManager::postRequestEx(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel, int netMode) {
//	if (netMode == HNET_MODE_DEFAULT) {
//		netMode = m_bUseSocket ? HNET_MODE_SOCKET : HNET_MODE_HTTP;
//	}
//	if (netMode == HNET_MODE_SOCKET) resetHeartBeat();
//	std::string params = param ? dictionaryToJSON(param) : "";
//	return jniPostRequest(command, params.c_str(), (jlong)delegate, ignoreDuplicaiton, commandLevel, netMode);
//}

void HNetManager::onDataReceived(int command, CCDictionary *result) {
	//if (!result) return;
    onDataReceivedEx(command, result);
}

//void HNetManager::asyncProcessReceivedData(HObject *target, int command, CCDictionary *param) {
//    m_oLock.lock();
//    m_pReceivedDataList->addObject(HNetData::create(target, command, param));
//    HTimerManager::getInstance()->processOnMainThread(HInvocation::create(this, hinvocation_selector(HNetManager::processReceivedData), 0, NULL));
//    m_oLock.unlock();
//}
//
//void HNetManager::processReceivedData(int command, CCObject *param) {
//    m_oLock.lock();
//    int count = m_pReceivedDataList->count();
//    for (int i = 0; i < count; ++i) {
//        HNetData *pData = (HNetData *)m_pReceivedDataList->objectAtIndex(i);
//        pData->processReceivedData();
//    }
//    m_pReceivedDataList->removeAllObjects();
//    m_oLock.unlock();
//}

void HNetManager::onTimeOut(int gid, int count) {
	if (g_iNetStatus == HNET_STATUS_NONE) return;
	m_iNotifyInterval -= count;
	if (m_iNotifyInterval < 0) {
		CCDictionary *param = CCDictionary::create();
		param->setObject(CCString::createWithFormat("%d", m_iVersion), "Version");
		param->setObject(CCString::createWithFormat("%d", m_iBVersion), "BVersion");
		postRequest(HPI_NOTIFICATION, param, this, false, 0, HNET_MODE_HTTP);
		m_iNotifyInterval = 6;
	}
}

void HNetManager::requestRegisterWithInviteCode(CCString* code)
{
    if (m_iLoginStatus > 0) return;
	m_iLoginStatus = HLOGIN_REGISTER;
	jniRequestRegisterWithInviteCode(code->getCString());
}

void HNetManager::requestRegisterWithInviteCodeAndSid(CCString *inviteUID, int sid)
{
    if (m_iLoginStatus > 0) return;
	m_iLoginStatus = HLOGIN_REGISTER;
	jniRequestRegisterWithInviteUIDAndSid(inviteUID->getCString(), sid);
}

void HNetManager::requestRegisterWithParam0(int param0) {
    if (m_iLoginStatus > 0) return;
	m_iLoginStatus = HLOGIN_REGISTER;
	requestRegisterWithParam0(param0, -1);
}

void HNetManager::requestRegisterWithParam0(int param0,int param1) {
	if (m_iLoginStatus > 0) return;
	m_iLoginStatus = HLOGIN_REGISTER;
	jniRequestRegisterWithParam0(param0, param1);
	g_iNetStatus = HNET_STATUS_NONE;
}


//void HNetManager::onDataReceived(const char *result) {
//
//}

//private
//void HNetManager::sendData(const char *result) {
//
//}

const char *HNetManager::createJsonWithAction(int action) {
	return jniCreateJsonWithAction(action);
}

bool HNetManager::postRequestEx(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel, int netMode, int validActionKey) {
    std::string content = dictionaryToJSON(param);
    return jniPostRequest(command, content.c_str(), (jlong)delegate, ignoreDuplicaiton, commandLevel, netMode, validActionKey);
}

char *loadFileFromAssets(char* filename, int& len){
	JniMethodInfo info;
	getStaticMethodInfo(info, HJAVA_NET_MANAGER, "loadFileFromAssets", "(Ljava/lang/String;)[B");
	JNIEnv *env = info.env;
	jbyteArray bytearry = (jbyteArray) (env->CallStaticObjectMethod(info.classID, info.methodID, env->NewStringUTF(filename)));
	char* array;
	if (bytearry) {
		len = env->GetArrayLength(bytearry);
		array = new char[len+1];
		jbyte *bytes = env->GetByteArrayElements(bytearry,0); 
		memcpy(array,bytes,len);
		env->ReleaseByteArrayElements(bytearry,bytes,0);
	} else {
		len = 0;
		array = new char[len+1];
	}
	array[len]=0;
	return array;
}
