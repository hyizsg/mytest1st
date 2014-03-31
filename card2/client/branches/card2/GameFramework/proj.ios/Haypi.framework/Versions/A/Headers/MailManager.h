//
//  MailManager.h
//  FishBowl
//
//  Created by Royal on 11-3-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "command.h"

typedef enum
{
    UNKNOWN = -1,
	SYSTEM_NOTICE = 1,
	PRIVATE_MAIL = 2,
	COMMON_HTML = 999,
}
MAIL_TYPE;

@class MailManager;

@protocol MailManagerProtocal <NSObject>
- (void)onReceiveMailList:(MailManager *)manager;
- (void)onRemoveMail:(MailManager *)manager;
- (void)onSendMail:(MailManager *)manager;
- (void)onReceiveMailDetail:(MailManager *)manager;

@end

@interface MailItem : NSObject
{
    int _ID;
    MAIL_TYPE _type;
    NSString * _body;
}
@property (assign, nonatomic) int ID;
@property (assign, nonatomic) MAIL_TYPE type;
@property (assign, nonatomic) int flag;
@property (copy, nonatomic) NSString * from;
@property (copy, nonatomic) NSString * to;

#ifndef OBJC_ARC_ENABLED
@property (retain, nonatomic) NSDate * time;
#else
@property (strong, nonatomic) NSDate * time;
#endif

@property (copy, nonatomic) NSString * subject;
@property (copy, nonatomic) NSString * body;
@property (readonly, nonatomic) bool isRead;

@end

@interface MailManager : NSObject<HaypiCmdDelegate>
{
	NSMutableArray * mails;
    NSMutableArray * observers;
}

//type == 0 : All Mail
+ (int)getMailCount:(MAIL_TYPE)mailType;
//type == 0 : All Mail
+ (NSArray *)getMailsByType:(MAIL_TYPE)type;
+ (void)requestMailList;
+ (void)requestRemoveMailByID:(int)mailID andType:(MAIL_TYPE)type;
+ (void)requestSendMail:(NSString *)mailBody To:(NSString *)mailTo withSubject:(NSString *)mailSubject;
+ (void)requestMailDetailByID:(int)mailID withType:(int)type;

+ (void)addObserver:(NSObject<MailManagerProtocal> *)observer;
+ (void)removeObserver:(NSObject<MailManagerProtocal> *)observer;

@end
