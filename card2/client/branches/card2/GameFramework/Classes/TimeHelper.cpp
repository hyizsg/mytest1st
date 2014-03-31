//
//  TimeHelper.cpp
//  Monster
//
//  Created by Eric Chen on 13-3-28.
//
//
#include "cocos2dxframework.h"


long TimeHelper::currentTimeInMS() {
    
    struct cocos2d::cc_timeval now;
    
    cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec /1000.0)/10;
}

long TimeHelper::timeIntervalSinceDate(long fromDate)
{

    return (currentTimeInMS()-fromDate);
}