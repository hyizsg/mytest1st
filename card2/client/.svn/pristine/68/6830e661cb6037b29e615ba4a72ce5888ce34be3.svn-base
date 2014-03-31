#ifndef _COCOS2DX_FRAMEWORK_H_
#define _COCOS2DX_FRAMEWORK_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Haypi-Animation/HpCharactorManager.h"
#include "Haypi-Animation/HpCharaInst.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace haypi_animation;

#ifdef __cplusplus
#define HNAMESPACE_BEGIN                     namespace haypi {
#define HNAMESPACE_END                       }
#define USING_HNAMESPACE                     using namespace haypi
#else
#define HNAMESPACE_BEGIN
#define HNAMESPACE_END
#define USING_HNAMESPACE
#endif

#define HABS_SUB(a, b) (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))

#define HLOWERCASE(s) for (int i = strlen(s) - 1; i >= 0; --i) if ((s[i] >= 'A') && (s[i] <= 'Z')) s[i] = s[i] + ('a' - 'A')
#define HUPPERCASE(s) for (int i = strlen(s) - 1; i >= 0; --i) if ((s[i] >= 'a') && (s[i] <= 'z')) s[i] = s[i] - ('a' - 'A')

#define HUINT2BYTE(gid, high, medium, normal, low) \
    (high) = ((gid) >> 24) & 0xFF; \
    (medium) = ((gid) >> 16) & 0xFF; \
    (normal) = ((gid) >> 8) & 0xFF; \
    (low) = (gid) & 0xFF;

#define HCLASSTYPE(_CLASS_, _SUPERCLASS_) \
public: \
    virtual std::string getClass() { return #_CLASS_; } \
    virtual bool isKindOf(const std::string &name) { \
        if (name == getClass()) return true; \
        if (std::string(#_CLASS_) == #_SUPERCLASS_) return false; \
        return _SUPERCLASS_::isKindOf(name); \
    }

#define HSINGLETON_OBJECT(_CLASS_) \
public: \
    virtual ~_CLASS_(); \
    static _CLASS_ *getInstance() { if (!m_g##_CLASS_) { m_g##_CLASS_ = new _CLASS_(); } return m_g##_CLASS_; } \
private: \
    _CLASS_(); \
    static _CLASS_ *m_g##_CLASS_

#define HSINGLETON_OBJECT_IMP(_CLASS_)  _CLASS_ *_CLASS_::m_g##_CLASS_ = NULL

#define HCREATE_FUNC(_CLASS_) \
    static _CLASS_* create() { \
        _CLASS_ *pRet = new _CLASS_(); \
        if (pRet) { \
            pRet->autorelease(); \
        } else { \
            delete pRet; \
            pRet = NULL; \
        } \
        return pRet; \
    }

#define GET_SELF(_CLASS_, _OBJECT_) (static_cast<_CLASS_ *>(_OBJECT_->getSelf()))


#define HORIENTATION_LANDSCAPE      1
#define HORIENTATION_PORTRAIT       2
#define HORIENTATION_ALL            3
extern int requestScreenOrientation();

#define HTOUCHSTATUS_NONE  0
#define HTOUCHSTATUS_BEGIN  1
#define HTOUCHSTATUS_MOVE   2
#define HTOUCHSTATUS_END    3

HNAMESPACE_BEGIN

typedef void (*FuncOnPercent)(float percent);

//md5
CC_DLL typedef unsigned long int UINT4;
CC_DLL typedef struct {
    UINT4 state[4];                                   /* state (ABCD) */
    UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

HNAMESPACE_END

const CCPoint HAnchorPointMid = CCPointMake(0.5f, 0.5f); //中间点
const CCPoint HAnchorPointDR = CCPointMake(1.0f, 0.0f); //右下
const CCPoint HAnchorPointUR = CCPointMake(1.0f, 1.0f); //右上
const CCPoint HAnchorPointUL = CCPointMake(0.0f, 1.0f); //左上
const CCPoint HAnchorPointDL = CCPointZero; //左下

#include "Log.h"
#include "Lock.h"
#include "Thread.h"
#include "HString.h"

#include "Object.h"
#include "Invocation.h"
#include "SpriteFrame.h"
#include "Timer.h"
#include "SourceCache.h"

//#include "FileUtils.h"

//#include "HFileUtils.h"
#include "ViewExtentions.h"
#include "CommonLayer.h"
#include "GameShowLayer.h"
#include "GameDecorationLayer.h"
#include "RootLayer.h"
#include "UILayer.h"

#include "GameDelegate.h"

//include action definition header

#include "action_def.h"

//add time helper
#include "TimeHelper.h"

//melon
#include "HRichLabelTTF.h"

//protocol id
#define HPI_NOTIFICATION                    202
#define HPI_SOCKETIP                        211

#endif //_COCOS2DX_FRAMEWORK_H_
