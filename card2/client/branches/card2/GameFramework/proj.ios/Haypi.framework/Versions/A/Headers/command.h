//
//  Command.h
//  Haypi
//
//  Created by jim kaden on 11-10-16.
//  Copyright (c) 2011年 n/a. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "net.h"
@class HaypiCmd;
@class HaypiCmdUserInfo;

typedef enum
{
    HCS_kCommandWaiting = 0,
    HCS_kCommandRequesting,
    HCS_kCommandDone,
    HCS_kCommandFailed,
}
HAYPI_COMMAND_STATUS;

typedef enum
{
    HCP_HTTP = 0,
    HCP_TCP = 1,
}
HAYPI_COMMAND_PROTOCOL;
@protocol HaypiCmdDelegate <NSObject>

@required
-(void)command:(HaypiCmd*)cmd didRecieveData:(NSDictionary*)data;
-(void)command:(HaypiCmd*)cmd failedWithError:(NSError*)error;

@optional

@end


@interface HaypiCmd : NSObject<NetReceiveDelegate>
{
    HAYPI_COMMAND_STATUS status;
    double createdTime;
}
#ifdef OBJC_ARC_ENABLED
@property (strong, nonatomic) NSMutableDictionary* request;
@property (strong, nonatomic) id userInfo;
@property (strong, nonatomic) id<HaypiCmdDelegate> delegate;
@property (assign, nonatomic) int timeOut;
@property (strong, nonatomic) NSArray* attachments;
@property (strong, nonatomic) NSError* error;
#else
@property (retain, nonatomic) NSMutableDictionary* request;
@property (retain, nonatomic) id userInfo;
@property (retain, nonatomic) id<HaypiCmdDelegate> delegate;
@property (assign, nonatomic) int timeOut;
@property (retain, nonatomic) NSArray* attachments;
@property (retain, nonatomic) NSError* error;
#endif
@property (assign, readwrite) HAYPI_COMMAND_PROTOCOL commandProtocol;

/*
 request:               发送的命令
 actionID:              命令类型
 timeOut:               超时
 parseDataImp:          系统保留，指定delegate中用于处理返回值的函数，可为nil
 netCallbackImp:        指定在command center中广播的调用接口。命令成功返回并处理以后，将在所有注册过的观察者中广播
 withDelegate:          delegate，必须实现 HaypiCmdDelegate
 commandProtocol:       使用何种网络协议
 */

-(BOOL)start;
-(void)onReceiveJson:(HaypiJson)json;
-(BOOL)expired;
-(void)response:(id)obj;
@end

@interface HaypiCmd (NetError)
+(NSError*)errorWithCode:(int)errorCode;
+(NSError*)errorWithCode:(int)errorCode userInfo:(NSDictionary*)info;
+(NSError*)errorWithCode:(int)errorCode description:(NSString*)description userInfo:(NSDictionary*)info;
+(NSError*)errorWithCode:(int)errorCode description:(NSString*)description domain:(NSString*)domain userInfo:(NSDictionary*)info;
@end

@interface HaypiCmdCenter : NSObject 
{
    NSMutableDictionary* commands;
    NSMutableSet* observers;
    NSTimer* watchdog_timer;
}

+(HaypiCmdCenter*)sharedInstance;
+(HaypiCmd*)detachCommand:(NSMutableDictionary*)request userInfo:(id)userinfo timeOut:(int)timeOut withDelegate:(id<HaypiCmdDelegate>)delegate;
+(HaypiCmd*)detachCommand:(NSMutableDictionary*)request actionID:(int)actionID timeOut:(int)timeOut parseDataImp:(SEL)imp1 netCallbackImp:(SEL)imp2 withDelegate:(id<HaypiCmdDelegate>)delegate;
+(HaypiCmd*)detachCommand:(NSMutableDictionary*)request actionID:(int)actionID timeOut:(int)timeOut attachments:(NSArray*)files parseDataImp:(SEL)imp1 netCallbackImp:(SEL)imp2 withDelegate:(id<HaypiCmdDelegate>)delegate;
+(HaypiCmd*)detachCommand:(NSMutableDictionary*)request userInfo:(id)userinfo timeOut:(int)timeOut withDelegate:(id<HaypiCmdDelegate>)delegate commandProtocol:(HAYPI_COMMAND_PROTOCOL)commandProtocol;
+(HaypiCmd*)detachCommand:(NSMutableDictionary*)request actionID:(int)actionID timeOut:(int)timeOut parseDataImp:(SEL)imp1 netCallbackImp:(SEL)imp2 withDelegate:(id<HaypiCmdDelegate>)delegate commandProtocol:(HAYPI_COMMAND_PROTOCOL)commandProtocol;
+(HaypiCmd*)detachCommand:(NSMutableDictionary*)request actionID:(int)actionID timeOut:(int)timeOut attachments:(NSArray*)files parseDataImp:(SEL)imp1 netCallbackImp:(SEL)imp2 withDelegate:(id<HaypiCmdDelegate>)delegate commandProtocol:(HAYPI_COMMAND_PROTOCOL)commandProtocol;
+(void)setDefaultCommandProtocol:(HAYPI_COMMAND_PROTOCOL)hcp;
+(void)setActionsWithAuthKey:(NSArray*)array;
+(void)setActionsWithHTTP:(NSArray*)array;
+(void)setActionsAllowedInBackground:(NSArray*)array;

-(HaypiCmd*)commandForActionKey:(int)actionKey;
-(BOOL)addObserver:(NSObject*)obj;
-(void)removeObserver:(NSObject*)obj;
-(void)invokeObserversMethod:(SEL)imp error:(NSError*)error;
-(void)invokeObserversMethod:(SEL)imp withArg:(id)arg error:(NSError*)error;
@end


@interface HaypiCmdUserInfo : NSObject 
//@property (copy, nonatomic) NSString* description;
@property (assign, nonatomic) int actionKey;
@property (assign, nonatomic) int gameplayID;
@property (assign, nonatomic) int actionID;
@property (assign, nonatomic) HaypiCmd* command;
@property (assign, nonatomic) SEL netCallbackImp;
@property (assign, nonatomic) SEL parseDataImp;
#ifdef OBJC_ARC_ENABLED
@property (strong, readonly) NSDictionary* info;
#else
@property (retain, readonly) NSDictionary* info;
#endif

+(HaypiCmdUserInfo*)infoWithJson:(HaypiJson)json;
+(HaypiCmdUserInfo*)infoWithJson:(HaypiJson)json toSelector:(SEL)aSelector;
@end
