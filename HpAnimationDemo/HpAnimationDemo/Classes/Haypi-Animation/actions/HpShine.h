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

/** @brief Grays In an object that implements the HpLightProtocol protocol. It modifies the Gray from 0 to 255.
 The "reverse" of this action is GrayOut
 */
class CC_DLL HpGrayIn : public CCActionInterval
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);
    
public:
    /** creates the action */
    static HpGrayIn* create(float d);
};

/** @brief Grays Out an object that implements the HpLightProtocol protocol. It modifies the Gray from 255 to 0.
 The "reverse" of this action is GrayIn
 */
class CC_DLL HpGrayOut : public CCActionInterval
{
public:
    virtual void update(float time);
    virtual CCActionInterval* reverse(void);
    virtual CCObject* copyWithZone(CCZone* pZone);
    
public:
    
    /** creates the action */
    static HpGrayOut* create(float d);
};

/** @brief Grays an object that implements the HpLightProtocol protocol. It modifies the Gray from the current value to a custom one.
 @warning This action doesn't support "reverse"
 */
class CC_DLL HpGrayTo : public CCActionInterval
{
public:
    /** initializes the action with duration and Gray */
    bool initWithDuration(float duration, GLubyte gray);
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    
public:
    /** creates an action with duration and Gray */
    static HpGrayTo* create(float duration, GLubyte gray);
protected:
    GLubyte m_toGray;
    GLubyte m_fromGray;
};


NS_HPAM_END


#endif /* defined(__HpAnimationDemo__HpShineTo__) */
