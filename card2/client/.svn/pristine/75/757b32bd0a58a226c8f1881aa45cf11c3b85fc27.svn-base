/*
 *  Keychains.h
 *  
 *
 *  Created by jim kaden on 10-5-20.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __KEYCHAIN_H__
#define __KEYCHAIN_H__

#import <Foundation/Foundation.h>

@interface NSMutableDictionary(CheckKey)
-(id)objectForKey:(id)aKey defValue:(id)defValue;
-(id)objectForCStrKey:(char*)key defValue:(id)defValue;
-(id)valueForKey:(id)aKey defValue:(id)defValue;
-(id)valueForCStrKey:(char*)key defValue:(id)defValue;
@end

#ifdef __cplusplus
extern "C" {
#endif
NSString* getStoredString(NSString* account, NSString* service);
NSData* getStoredData(NSString* account, NSString* service);
int setStoredString(NSString * str, NSString* account, NSString* service);
int setStoredData(NSData * storedData, NSString* account, NSString* service);
int deleteService(NSString* account, NSString* service);

NSString* getLastUser();
NSString* getAuthKey(NSString* userName, int gameMode);
NSString* getLastAuthKey(int gameMode);
#ifdef __cplusplus
}
#endif
#endif
