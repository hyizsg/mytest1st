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


#define NS_HPAM_BEGIN           namespace haypi_animation{
#define NS_HPAM_END             }

NS_HPAM_BEGIN

/** For android ECT Texture with a same name Alpha texture.
 * To suport it, you must define HP_ENABLE_ALPHA_TEXTURE;
 * And modify CCTexture ori source to add a mothed [CCTexture* getAlphaTexture()]
 * Or modify the define [getAlphaTexture(p)] to return a right texture
 */
// zg to do ...


//#define HP_ANI_DEBUG
//#define HP_ENABLE_ALPHA_TEXTURE


#ifdef HP_ENABLE_ALPHA_TEXTURE
#define getAlphaTexture(p) ((p)->getAlphaTexture())
#else
#define getAlphaTexture(p) (NULL)
#endif


#ifdef HP_ANI_DEBUG

#define HPLOG(format, ...)      cocos2d::CCLOG(format, ##__VA_ARGS__)
#define HP_AUTO_RELEASE(p)      p->autorelease()

#else

#define HPLOG(format, ...)      do{}while(0);
#define HP_AUTO_RELEASE(p)      p->autorelease()

#endif


NS_HPAM_END


#endif // HPLOG_H
