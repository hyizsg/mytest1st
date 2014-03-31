//
//  functions.h
//  loginFunctions
//
//  Created by Royal on 11-6-16.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "login_def.h"
/*
 此为帐号管理方式，由哪一方管理帐号，
 对应文档中的GameCenter，此为历史原因，名称不对应
 */
typedef enum
{
    PPP_Apple = 0,
    PPP_GameCenter = 1,
    PPP_91 = 2,
    PPP_Neowiz = 3,
    PPP_Gree = 4,
    PPP_Tencent = 5,
    PPP_PP = 11,
    PPP_JINGQI = 12,
}
PASSPORT_PLATFORM;

/*
 此为市场，由指定平台下哪一方市场发布
 */
typedef enum
{
    PMK_Apple = 0,
    PMK_Venide = 1010,
    PMK_Adwo = 1011,
    PMK_Kuaiyong = 1022,
    PMK_AlipayCommon = 1023,
    PMK_Kaku = 1024,
    PMK_ILead = 1025,
    PMK_TFJoy = 1030,
    PMK_TFJoyDE = 1031,
}
PASSPORT_MARKET;

typedef enum
{
    US_Error        = 0,
    US_Unregistered = 1,
    US_Registered   = 2,
    US_Banned       = 3,
}
USER_STATE;


/*
 控制主登录窗口的流程
 */
@protocol LoginMainWindowDelegate <NSObject>

@required
-(void)onAccountClicked:(NSObject*)sender;
-(void)startGame:(NSNumber*)from;

@optional
-(void)showProgressView;
@end

/*
 填写用户名密码进行登陆的窗口的流程
 */
@protocol LoginWindowDelegate <NSObject>
@optional
-(void)onNetFail:(char*)context;
@end

/*
 一般性登录流程回调
 */
@protocol LoginFunctionProtocol <NSObject>
@required
- (void)loginErrorWithCode:(NSDictionary *)code;

@optional
- (void)changeUserNameTo:(NSString *)newName;
- (void)onReceiveServerList:(NSDictionary *)serverlist;
- (void)onReceiveLastUserState:(USER_STATE)state;
- (void)onReceiveGCNameResponse:(NSDictionary*)response;
@end


@interface LoginFunctions : NSObject
{
    
}
+ (void)setDelegate:(NSObject<LoginFunctionProtocol> *)delegate;
+ (void)setLoginMainWindow:(NSObject<LoginMainWindowDelegate> *)window;
+ (void)setLoginWindow:(NSObject<LoginWindowDelegate> *)window;

+ (void)setNeedRegisterWindow:(bool)isNeed;
+ (void)setRegisterServerUrl:(bool)isFake;
+ (void)setRegisterURL:(NSString*)newUrl;
+ (void)setFakeRegisterURL:(NSString*)newUrl;
+ (void)setPlatform:(PASSPORT_PLATFORM)platform;
+ (void)setPlatform:(PASSPORT_PLATFORM)platform market:(PASSPORT_MARKET)market;
+ (void)setPartnerID:(NSString*)pid;
+ (void)setPlatformAccount:(NSString*)account token:(NSString*)token;
+ (NSString*)getRegisterServerUrl;

+ (int)fakeStart;
+ (int)start;
+ (void)resetAccount;


+ (void)requestRegisterWithParam0:(int)param0;
+ (void)requestRegisterWithParam0:(int)param0 Param1:(int)param1;
+ (void)requestRegisterWithInviteUID:(NSString*)inviteUID;
+ (void)requestRegisterWithInviteUID:(NSString*)inviteUID ServerID:(int)sid;
+ (void)requestLoginWithName:(NSString *)userName Password:(NSString *)password;
+ (NSDictionary*)requestServerList;
+ (void)loginToPassportServer;
+ (void)requestLastUserState;
+ (void)requestGCName:(NSString*)url AuthCode:(NSString*)authCode Debug:(bool)debug;
+ (void)requestGCName:(NSString*)url AuthCode:(NSString*)authCode Debug:(bool)debug Delegate:(id<LoginFunctionProtocol>)delegate;

+ (bool)isWaitingForLogin;
+ (bool)isWaitingForRegister;
+ (bool)isWaitingForNetRequest;
+ (bool)isWaitingForLoginWithAccount;

+ (void)clearCurrentServerUrl;
+ (void)onChangeUserName:(NSString*)newUserName WithAuthKey:(NSString*)newAuthKey;
@end
