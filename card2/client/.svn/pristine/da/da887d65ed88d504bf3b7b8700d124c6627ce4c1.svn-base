//
//  CCProgressTimerLoader.h
//  card
//
//  Created by zhou gang on 13-5-22.
//
//

#ifndef __card__CCProgressTimerLoader__
#define __card__CCProgressTimerLoader__

#include <iostream>

class HProgressTimer : public CCProgressTimer
{
public:
    virtual void setSprite(CCSprite *pSprite);
    virtual void draw(void);
    
    CREATE_FUNC(HProgressTimer);
    
    static HProgressTimer* create(CCSprite* sp);
};

class CCProgressTimerLoader : public CCNodeLoader {
    
    
public:
    virtual ~CCProgressTimerLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCProgressTimerLoader, loader);
    
protected:
    
    virtual CCProgressTimer * createCCNode(CCNode * pParent, CCBReader * pCCBReader);
    
    virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader);
    virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
    virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBBlendFunc, CCBReader * pCCBReader);
    virtual void onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader);
    virtual void onHandlePropTypeFlip(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool * pFlip, CCBReader * pCCBReader);
};

#endif /* defined(__card__CCProgressTimerLoader__) */
