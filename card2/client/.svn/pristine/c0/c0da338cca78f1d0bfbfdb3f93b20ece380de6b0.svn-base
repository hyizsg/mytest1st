/*
 *  resource_utilities.h
 *  HaypiNet
 *
 *  Created by jim kaden on 11-2-19.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _RESOURCE_UTILITIES_H_
#define _RESOURCE_UTILITIES_H_
#import <Foundation/Foundation.h>
#ifdef __cplusplus
extern "C" {
#endif
NSString* regularNameByDevice(NSString* name, NSBundle* bundle);
BOOL isDeviceIPad();
/*
 4寸屏的xib，添加 -568h
 iPad的xib，添加 -ipad
 */
#define REGULAR_NAME(x) regularNameByDevice((x),nil)
#ifdef __cplusplus
}
#endif
#endif
