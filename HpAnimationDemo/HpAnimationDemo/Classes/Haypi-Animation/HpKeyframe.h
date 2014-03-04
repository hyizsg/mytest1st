#ifndef HPKEYFRAME_H
#define HPKEYFRAME_H

/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#include "sys/types.h"
#include "cstring"

#include "cocos2d.h"

#include "HpAnimVisitor.h"
#include "HpInterpHolder.h"


USING_NS_CC;
using namespace std;

NS_HPAM_BEGIN

//class HpInterpHolder;

enum HpContentType{
    HPCONTENTTYPE_NULL,
    HPCONTENTTYPE_IMAGE,
    HPCONTENTTYPE_ANIMA,
    HPCONTENTTYPE_NUM
};

class HpKeyframe : public CCObject{
public:
    CC_SYNTHESIZE(int, m_iTime, Time)
    CC_SYNTHESIZE(bool, m_isTimeInherited, IsTimeInherited);
    CC_SYNTHESIZE(uint, m_uArrayIndex, ArrayIndex)
    CC_SYNTHESIZE(CCPoint, m_cCenter, Center)
    CC_SYNTHESIZE(CCPoint, m_cTrans, Trans)
    CC_SYNTHESIZE(float, m_fRot, Rot)
    CC_SYNTHESIZE(CCPoint, m_cSkew, Skew)
    CC_SYNTHESIZE(CCPoint, m_cScale, Scale)
    CC_SYNTHESIZE(ccColor4F, m_cColor, Color)
    CC_SYNTHESIZE(ccColor4F, m_cColorEx, ColorEx)
    CC_SYNTHESIZE_RETAIN(CCString*, m_pContent, Content)
    CC_SYNTHESIZE(HpContentType, m_eContentType, ContentType)
    CC_SYNTHESIZE_RETAIN(CCString*, m_pEvent, Event)

    CC_PROPERTY(HpInterpHolder*, m_pInterps, Interps);


public:
    HpKeyframe();
    virtual ~HpKeyframe();

public:
    CCPoint getCenterAt(float p_t);
    CCPoint getTransAt(float p_t);
    float getRotAt(float p_t);
    CCPoint getSkewAt(float p_t);
    CCPoint getScaleAt(float p_t);

    ccColor4F getColorAt(float p_t);
    ccColor4F getColorExAt(float p_t);
};

class HpContentKeyframe : public CCObject{
public:
    HpContentKeyframe();
    ~HpContentKeyframe();
public:
    CC_SYNTHESIZE(int, m_iTime,Time)
    CC_SYNTHESIZE(bool, m_bFirstVisitFlag, FirstVisitFlag)
    CC_SYNTHESIZE_RETAIN(CCString*, m_pContentName, ContentName)

    virtual void visitBy(HpAnimVisitor* p_visitor, HpKeyframe* p_fm, float time) = 0;
    virtual HpContentKeyframe* clone() = 0;
};


NS_HPAM_END

#endif // HPKEYFRAME_H
