//
//  SystemObject.h
//  Haypi
//
//  Created by jim kaden on 11-10-25.
//  Copyright (c) 2011年 n/a. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "net.h"

@protocol HaypiCmdDelegate ;

@interface HaypiSocketObject : NSObject <HaypiCmdDelegate, SocketReceiveDelegate>
{
    BOOL isRunning;
    
    HaypiSocket haypisocket;
    unsigned int memberID;
    
}
@property (assign, readonly, nonatomic) BOOL running;
@property (assign, nonatomic) bool isLoginOK;

+(HaypiSocketObject*)sharedInstance;

-(void)start;
-(void)stop;
-(void)connectPushServer:(NSString*)server port:(short)port;
-(void)sendHeartbeat:(HaypiJson)hearbeat;
-(void)disconnectPush;

-(void)sendCmd:(HaypiJson)dict;
-(void)sendCmd:(HaypiJson)dict toMember:(int)memberID;
-(void)connectPushServer;
-(void)alterApplicationState:(AS_STATE)ast;
-(unsigned int)getMemberID;
@end

