/*
 *  multiLang.h
 *  
 *
 *  Created by jim kaden on 10-5-21.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __MULTILANG_H__
#define __MULTILANG_H__

#ifdef __cplusplus
extern "C" {
#endif
    
const char* getCurrentRegionID();

const char* getLocalString(int code, const char* default_value);

const char* getLocalGoodsName(int code, const char* default_value);

const char* getLocalUI(const char* name);

const char* getLocalCustomString(const char* name);

#ifdef __cplusplus
}
#endif
#endif
