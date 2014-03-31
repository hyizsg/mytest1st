//
//  TimeHelper.h
//  Monster
//
//  Created by Eric Chen on 13-3-28.
//
//

#ifndef __Monster__TimeHelper__
#define __Monster__TimeHelper__

class TimeHelper :public CCObject
{
    //private:
    //    long t0;
public:
    static long timeIntervalSinceDate(long fromDate);
    static long currentTimeInMS();
};
#endif /* defined(__Monster__TimeHelper__) */
