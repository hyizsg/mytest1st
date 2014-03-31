//
//  chatObject.h
//  HaypiFramework
//
//  Created by jim kaden on 12-10-8.
//  Copyright (c) 2012年 n/a. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface WordsFilter : NSObject
+(NSString*)replaceBadWords:(NSString*)msg;
+(BOOL)containBadWords:(NSString*)msg;
@end
