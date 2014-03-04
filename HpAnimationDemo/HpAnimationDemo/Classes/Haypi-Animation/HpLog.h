#ifndef HPLOG_H
#define HPLOG_H
//
//#ifdef ANDROID_GAME
//#include <string.h>
//#include <android/log.h>
//
//#define LOG_TAG "Haypi_Animation"
//
//extern const char* skip_file_prefix(const char* path,size_t n);
//
//#define HPLOGD(format, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,  "File:%s\tLine:%04d %16.15s " format "\n",skip_file_prefix(__FILE__,20),__LINE__,__FUNCTION__,##__VA_ARGS__);
//
//#else
//
//
//
//#endif


#include "cocos2d.h"

//#define HP_ANI_DEBUG

#ifdef HP_ANI_DEBUG

#define HPLOG(format, ...)      cocos2d::CCLOG(format, ##__VA_ARGS__)
#define HP_AUTO_RELEASE(p)      p->autorelease()

#else

#define HPLOG(format, ...)      do{}while(0);
#define HP_AUTO_RELEASE(p)      p->autorelease()

#endif

#define NS_HPAM_BEGIN           namespace haypi_animation{
#define NS_HPAM_END             }

#endif // HPLOG_H
