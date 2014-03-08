//
//  HpShineTo.h
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-8.
//
//

#ifndef __HpAnimationDemo__HpShineTo__
#define __HpAnimationDemo__HpShineTo__

#include "cocos2d.h"
#include "Hpheaders.h"

using namespace cocos2d;

NS_HPAM_BEGIN

class HpShineTo : public CCActionInterval
{
public:
    /** initializes the action with duration and color */
    bool initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue);
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    
public:
    /** creates an action with duration and color */
    static HpShineTo* create(float duration, GLubyte red, GLubyte green, GLubyte blue);
protected:
    ccColor3B m_to;
    ccColor3B m_from;
};


class HpShineBy : public CCActionInterval
{
public:
    /** initializes the action with duration and color */
    bool initWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    
public:
    /** creates an action with duration and color */
    static HpShineBy* create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);
protected:
    GLshort m_deltaR;
    GLshort m_deltaG;
    GLshort m_deltaB;
    
    GLshort m_fromR;
    GLshort m_fromG;
    GLshort m_fromB;
};


NS_HPAM_END


#endif /* defined(__HpAnimationDemo__HpShineTo__) */
