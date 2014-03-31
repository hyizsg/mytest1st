//
//  net.h
//  haypi_Net
//
//  Created by jim kaden on 08-12-11.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#ifndef __NET__H__
#define __NET__H__

#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif

    
@protocol NetReceiveDelegate;
@protocol SocketReceiveDelegate;
        
typedef enum
{
    CM_Plain = 0,
    CM_DES,
    CM_RC4,
    CM_Base64,
    CM_RC5,
    CM_RC6,
}
CRYPT_METHOD;

typedef enum
{
    ST_NW,
    ST_Memcached,
    ST_HaypiServer,
}
SERVER_TYPE;

typedef enum
{
    PT_TCP,
    PT_UDP,
}
PROTOCOL_TYPE;
    
typedef enum
{
    AS_Foreground,
    AS_Background,
    AS_Suspended,
}
AS_STATE;

typedef enum
{
    DT_IOS = 1,
    DT_ANDROID = 2,
    DT_WMP = 3,
    DT_MAC = 4,
    DT_PC = 5,
    DT_FLASH = 6,
}
DEVICE_TYPE;
    
typedef enum
{
    ST_GameServer = 0,
    ST_GameCenter = 1,
}
GAME_SERVER_TYPE;

@protocol UrlDataDelegate <NSObject>
@optional
-(void)pathForUrl:(NSDictionary*)url; /* download file automatically */
-(void)uploadToYoutube:(NSDictionary*)urls;
@end

#if __has_feature(objc_arc)
#define OBJC_ARC_ENABLED
typedef NSMutableDictionary* HaypiJson;
typedef NSObject* HaypiSocket;
typedef id<NetReceiveDelegate> NetReceiver;
typedef id<SocketReceiveDelegate> SocketReceiver;
typedef id<UrlDataDelegate> UrlDataReceiver;
typedef NSArray* Array;

#else

#undef OBJC_ARC_ENABLED
typedef int HaypiJson;
typedef int HaypiSocket;
typedef void* NetReceiver;
typedef void* SocketReceiver;
typedef void* UrlDataReceiver;
typedef int Array;

#endif

int setCommonNotificationHandler(NetReceiver receiver);

int sendJsonCmdWithAttachments(HaypiJson jsonData, Array fileNames, int gameMode, NetReceiver receiver, int timeout);
int sendCmdWithAttachments(int actionKey, Array fileNames, char* context, char* server, NetReceiver receiver, int timeout);

int sendJsonCmd(HaypiJson jsonData, int gameMode, NetReceiver receiver, int timeout);
int sendCmd(int actionKey, char* context, char* server, NetReceiver receiver, int timeout);

char* getPathForUrl(char* url, UrlDataReceiver receiver);
void uploadToYoutube(char* filepath, char* username, char* password, char* videotitle, char* videodescription, UrlDataReceiver receiver);
HaypiSocket connectServer(char* server, short port, CRYPT_METHOD cryptMethod, SocketReceiver receiver, SERVER_TYPE st, PROTOCOL_TYPE pt, BOOL persistConnection);
void disconnect(HaypiSocket sock);
void sendSocketCmd(HaypiSocket sock, char* context, BOOL needConfirm, float confirmTimer);
int socketUnsentCmd(HaypiSocket socket);
char* getSocketServer(HaypiSocket socket);
short getSocketPort(HaypiSocket socket);
int getNativeSocket(HaypiSocket socket);

void loginHaypiSocketServer(HaypiSocket socket, GAME_SERVER_TYPE st);
int alterApplicationState(HaypiSocket socket, AS_STATE ast);
    
bool sendCmdToHaypiServer(HaypiSocket socket, HaypiJson cmd);
void sendCmdToMember(HaypiSocket socket, HaypiJson cmd, int memberID, int64_t hashCode);
uint64_t getHashCodeFromHaypiSocketServer(HaypiSocket socket);
int getMemberIDFromHaypiSocketServer(HaypiSocket socket);
    
@protocol NetReceiveDelegate <NSObject>
@optional
-(void)onNetFail:(char*)context;
-(void)onCommonNotification:(HaypiJson)context;
-(void)onReceive:(char*)context;
@end

@protocol SocketReceiveDelegate <NSObject>
@optional
-(void)onUserLoggedIn:(NSNumber*)uid withHashCode:(NSNumber*)hashCode;
-(void)onReceiveJsonWithBase64Decoding:(HaypiJson)json withSocket:(HaypiSocket)socket;    // 如果可以解析为Json结构，则调用此回调，否则调用onReceive
-(void)onReceive:(char*)context withSocket:(HaypiSocket)socket;
-(void)socketDisconnected:(HaypiSocket)socket forceClose:(BOOL)forceClose;
-(void)socketConfirmError:(char*)context withSocket:(HaypiSocket)socket;
-(NSString*)socketReconnected:(HaypiSocket)socket needConfirm:(BOOL*)needConfirm timer:(float*)timer;
-(void)socketError:(char*)error withSocket:(HaypiSocket)socket;
@end
    
#define ENABLE_TRY_CATCH

HaypiJson createJson();
HaypiJson createJsonWithAction(int action, char* auth);
HaypiJson createJsonOnlyWithAction(int action, int gameMode);
void jsonAddString(HaypiJson ref, char*, char*);
void jsonAddInt(HaypiJson ref, char*, int);
void jsonAddFloat(HaypiJson ref, char*, float);
char* jsonGetString(HaypiJson ref, char*);
int jsonGetInt(HaypiJson ref, char*);
float jsonGetFloat(HaypiJson ref, char*);
char* jsonToStr(HaypiJson ref);
void deleteJson(HaypiJson ref);
HaypiJson strToJson(char* str);
int deleteJsonInt(HaypiJson ref, char* name);

char* md5_Encode(char* text, int withChecker); /* caller must free the returned string */
void* netThreadProc(void* arg);
int getNetDataNow();
int eanbleNetLog(int enable);

char* getHaypiDeviceID();

int base64_encode_(void * dst, const void * src, unsigned long len);
int base64_decode_(void * dst, const void * src, unsigned long len);


int getGameplayID();
int getActionKey();
int getLastGameMode();
char* getCLastUser();
char* getCAuthKey(char* userName, int gameMode);
char* getCLastUserAuthKey(int gameMode);
char* getCLastClientUrl(int gameMode);
char* getCLastUserGC(int gameMode);
short getCLastUserGCPort(int gameMode);
    
void refreshAllLastObject();
uint64_t getDownloadBytesCount();
uint64_t getUploadBytesCount();
void getUploadBytesProgress(uint64_t* transferred, uint64_t* total);

#define CALLING         1
#define DEBUGOUT		2
#define RUNNING         3

#define NET_CHECK_TIME 6.0f

typedef enum 
{
    net_feature_formdata = 0x01,
    net_feature_zip = 0x02,
}
NET_FEATURE;

int enableNetFeature(int features);


typedef struct
{
	int status_code;
	char* context;
}
NET_RETURN_STRUCT;

#define kPackageLevel       "PackageLevel"
#define objcPackageLevel	@"PackageLevel"
    
typedef enum
{
	Package_Normal=0,
	Package_Warning=1,
	Package_Fatal=2,
	Package_Restart=3,
}
PACKAGE_LEVEL;

#define kNetworkStatus      "NetworkStatus"
#define objcNetworkStatus	@"NetworkStatus"
typedef enum
{
	NetworkStatus_Off=0,
	NetworkStatus_On=1,
}
NETWORK_STATUS;
/*
 getNetworkStatus 异步调用，返回本地网络状态
 sync_getNetworkStatus： 同步调用，返回到指定的host的网络连接情况，NULL为检查本地网络连接情况
 */
NETWORK_STATUS getNetworkStatus();
NETWORK_STATUS sync_getNetworkStatus(char* host);

#define VideoWatchUrl   "WatchUrl"
#define VideoThumbUrl   "ThumbUrl"

#ifdef __cplusplus
}
#endif

    
#endif

