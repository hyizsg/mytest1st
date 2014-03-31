//
//  chatObject.h
//  HaypiFramework
//
//  Created by jim kaden on 12-10-8.
//  Copyright (c) 2012年 n/a. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "net.h"
#import "command.h"
typedef enum
{
    CT_NONE         = -1,
    CT_WORLD        = 0,        /*世界聊天*/
    CT_GROUP        = 1,        /*组聊天*/
    CT_PRIVATE      = 2,        /*私聊*/
    CT_CHANNEL      = 3,        /*频道聊天*/
}
CHAT_TYPE;

typedef enum
{
    CSE_NONE        = 0,        /*成功*/
    CSE_TIME_OUT    = -1,       /*发送间隔太短*/
    CSE_NO_TO       = -2,       /*没有指定发送对象*/
    CSE_NO_CHANNEL  = -3,       /*没有指定频道*/
}
CHAT_SEND_ERROR;

typedef enum
{
    CUT_NORMAL      = 0,        /*普通用户*/
    CUT_VIP         = 1,        /*VIP*/
    CUT_ADMIN       = 2,        /*Admin*/
    CUT_SUPPORT_LEADER = 3,     /*Support leader*/
    CUT_EXPERT      = 4,        /*Expert*/
    CUT_SUPPORT     = 5,        /*Support*/
    CUT_DEVELOPER   = 6,        /*Developer--GM专用*/
    CUT_OBSERVER    = 7,        /*观察员--GM专用*/
}
CHAT_USER_TYPE;

@protocol ChatDelegate <NSObject>
@optional
-(void)messageSent:(BOOL)isOK;
-(void)newMessageReceived:(NSDictionary*)info;

@end

//私聊1永远是自己
@interface ChatMessageItem : NSObject
{
}
@property (readwrite, assign) int messageId;            /*消息编号（旧称：版本号）*/
@property (copy) NSString* from;
@property (copy) NSString* to;
@property (readwrite, assign) CHAT_USER_TYPE userType1;            /*聊天说者类型，私聊中我的类型*/
@property (readwrite, assign) CHAT_USER_TYPE userType2;            /*另一个人的类型*/
@property (readwrite, assign) int rank1;                /*排名*/
@property (readwrite, assign) int rank2;                /*另一个人的排名*/
@property (readwrite, assign) bool isMyself;            /*是否是我说的话*/
@property (copy) NSString* message;
#ifdef OBJC_ARC_ENABLED
@property (nonatomic, strong) NSDate* time;                 /*发言时间*/
@property (nonatomic, strong) NSMutableDictionary* info1;   /*用户数据、服务器扩展*/
@property (nonatomic, strong) NSMutableDictionary* info2;   /*另一个用户的数据、服务器扩展*/
@property (nonatomic, assign) NSObject* customObject;         /*客户端自由扩展*/
#else
@property (nonatomic, retain) NSDate* time;
@property (nonatomic, retain) NSMutableDictionary* info1;
@property (nonatomic, retain) NSMutableDictionary* info2;
@property (nonatomic, assign) NSObject* customObject;
#endif
@end

@interface ChatRoom : NSObject
{
    NSMutableArray* chatItems;
    int latestVersion;
    CHAT_TYPE ct;
}
-(id)initWithChatType:(CHAT_TYPE)ct_;
-(int)addChatItems:(NSArray*)items;
-(int)verifyChatItem;
-(void)fillChatRequest:(NSMutableDictionary*)dictRequest;
-(void)refreshVersion:(int)version;
-(NSArray*)getItems;
@end

@interface ChatObject : NSObject
{
    bool paused;
    NSDate* timeLatestVersion;
    NSDate* timeLatestSentChat;
    BOOL waitingForVersions;
    NSMutableArray* observers;
    NSString* channelName_;
}
@property (nonatomic, copy) NSString* channelName;
#ifdef OBJC_ARC_ENABLED
@property (nonatomic, strong) NSMutableArray* chatRooms;
#else
@property (nonatomic, retain) NSMutableArray* chatRooms;
#endif
+(ChatObject*)sharedInstance;
-(void)start;
-(void)stop;
-(void)clear;
-(void)addObserver:(NSObject<ChatDelegate> *)observer;
-(void)removeObserver:(NSObject<ChatDelegate> *)observer;

/*
 获得该聊天室的发言列表，返回值为包含ChatMessageItem的Array
 */
-(NSArray*)getChatItems:(CHAT_TYPE)ct;
/*
 timeout: 该类型用户发言的时间间隔，用于控制用户发言速度, support、support_leader,admin传入-1，同时support、support_leader,admin的发言将不进行脏词过滤
 to: 私聊时设置，其他为nil
 */
-(CHAT_SEND_ERROR)sendMessage:(NSString*)msg to:(NSString*)to chatType:(CHAT_TYPE)ct timeout:(float)timeout;

@end
