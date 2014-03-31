//
//  HRichButton.h
//  card
//
//  Created by zhou gang on 13-5-27.
//
//

#ifndef __card__HRichButton__
#define __card__HRichButton__

class HCardEditBox: public CCEditBox
{
public:
    
    HCardEditBox();
    virtual ~HCardEditBox(){};
    virtual bool initWithSizeAndBackgroundSprite(const CCSize& size, CCScale9Sprite* pNormal9SpriteBg);
    
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    virtual void setVisible(bool bVisible);
    virtual void setPosition(const CCPoint& pos);
    
    CC_SYNTHESIZE_BOOL(bool, m_bVisibleBak, VisibleBak);
};

class CC_DLL HCardEditBoxLoader: public CCEditBoxLoader {
public:
    virtual ~HCardEditBoxLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HCardEditBoxLoader, loader);
    
protected:
    virtual HCardEditBox *createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader);
    virtual void onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCSize pSize, CCBReader * pCCBReader);
};

class HControlButton: public CCControlButton
{
public:
    static HControlButton *create();
    
    bool getParentInited() {
        return m_bParentInited;
    }
    void setParentInited(bool value) {
        m_bParentInited = value;
    }
};

class HRichButton : public CCControlButton {
    
    
public:
    virtual bool init();
    virtual bool initWithTitleAndFontNameAndFontSize(std::string title, const char * fontName, float fontSize);
    virtual bool initWithBackgroundSprite(CCScale9Sprite* sprite);
    
    virtual void setBackgroundSpriteFrameForState(CCSpriteFrame * spriteFrame, CCControlState state);
    virtual void setBackgroundSpriteForState(CCSprite* sprite, CCControlState state);

    virtual void setTitleTTFForState(const char * fntFile, CCControlState state);
    
    virtual void needsLayout(void);

    CREATE_FUNC(HRichButton);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    bool isInScrollView();
    
public:
    virtual HRichLabelTTF* getRichLabel();
    
};


class HControlButtonLoader : public CCControlButtonLoader {

public:
    virtual ~HControlButtonLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HControlButtonLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HControlButton);
    
    //virtual void onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader);
//    virtual void onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader);
//    virtual void onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * pCCBReader);
    virtual void parseProperties(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
    
//    std::string m_str;
//    std::string m_font;
};


class HRichButtonLoader : public CCControlButtonLoader {
    
public:
    virtual ~HRichButtonLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HRichButtonLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HRichButton);
    
    virtual void onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader);
};

#endif /* defined(__card__HRichButton__) */
