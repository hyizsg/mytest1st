#ifndef _VIEW_EXTENTIONS_H_
#define _VIEW_EXTENTIONS_H_

#include "CCEditBoxLoader.h"

#define HVIEWCMD_DONE	 -100
#define HVIEWCMD_CREATE	 -101
#define HVIEWCMD_REMOVE	 -102
#define HVIEWCMD_SHOW	 -103
#define HVIEWCMD_HIDE	 -104
#define HVIEWCMD_UPDATE	 -105
#define HVIEWCMD_CHECK	 -106
#define HVIEWCMD_GETTEXT -107
#define HVIEWCMD_SETTEXT -108

#define HVIEWFEATURE_SINGLINE   		(1<<1)
#define HVIEWFEATURE_PASSWORD   		(1<<2)
#define HVIEWFEATURE_NUMERIC    		(1<<3)
#define HVIEWFEATURE_EMAIL              (1<<4)
#define HVIEWFEATURE_STYPE_BOLD    		(1<<5)
#define HVIEWFEATURE_STYPE_ITALIC    	(1<<6)
#define HVIEWFEATURE_STYPE_BOLDITALIC   (HVIEWFEATURE_STYPE_BOLD | HVIEWFEATURE_STYPE_ITALIC)
#define HVIEWFEATURE_TYPEFACE_MONO 		(1<<7)
#define HVIEWFEATURE_TYPEFACE_SANS 		(1<<8)
#define HVIEWFEATURE_TYPEFACE_SERIF    	(1<<9)
#define HVIEWFEATURE_TYPEFACE_SANSSERIF (HVIEWFEATURE_TYPEFACE_SANS | HVIEWFEATURE_TYPEFACE_SERIF)
#define HVIEWFEATURE_NORMAL             (HVIEWFEATURE_SINGLINE | HVIEWFEATURE_TYPEFACE_SERIF)

#define HVIEWTYPE_EDITBOX      1
#define HVIEWTYPE_LABEL        2
#define HVIEWTYPE_BUTTON       3
#define HVIEWTYPE_IMAGE        4

#define HVIEWKEY_ALL            "all"
#define HVIEWKEY_ID             "id"
#define HVIEWKEY_TYPE           "type"
#define HVIEWKEY_VISIBLE        "visible"
#define HVIEWKEY_X              "x"
#define HVIEWKEY_Y              "y"
#define HVIEWKEY_W              "w"
#define HVIEWKEY_H              "h"
#define HVIEWKEY_FEATURE        "feature"
#define HVIEWKEY_TEXT           "text"
#define HVIEWKEY_HINT           "hint"
#define HVIEWKEY_FONTNAME       "fn"
#define HVIEWKEY_FONTSIZE       "fs"
#define HVIEWKEY_FONTCOLOR      "fc"
#define HVIEWKEY_HINTCOLOR      "hc"
#define HVIEWKEY_MAXLEN         "len"

HNAMESPACE_BEGIN

//class CC_DLL HView {
//    CC_SYNTHESIZE_RETAIN(HString *, m_pID, ID);
//public:
//    HView(): m_pID(NULL) {}
//    virtual ~HView() { setID(NULL); }
//    
//    virtual void refresh() {}
//    virtual CCDictionary *toDictionary(int command) { return NULL; }
//};

class CC_DLL HEditBox: public CCEditBox {
    CC_SYNTHESIZE(bool, m_bBakVisible, BakVisible);
public:
    HEditBox();
    virtual ~HEditBox();
    
    CCEditBoxDelegate *getDelegate() { return m_pDelegate; }
    
    bool initWithSizeAndBackgroundSprite(const CCSize& size, CCScale9Sprite* pNormal9SpriteBg);
    
//    void setFontname(const char *pFontname);
    void setFontSize(int size);
    
    void bakVisible() { m_bBakVisible = isVisible(); }
    
    virtual void setContentSize(const CCSize& size);
    virtual void setVisible(bool visible);
    virtual void setText(const char* pText);
//    virtual void onEnter(void);
    void setTextEx(const char* pText);
    
    virtual void refresh();
    virtual CCDictionary *toDictionary(int command);
protected:
//    std::string m_strFontname;
    int m_nFontSize;
    bool m_bCreated;
};

//#ifdef HOS_APPLE
//#define HEditBox    CCEditBox
//#else
//#define HEditBox    HEditBoxImp
//#endif

class CC_DLL HViewPage: public HObject {
public:
    HViewPage();
    virtual ~HViewPage();
    
    void registerView(HEditBox *view);
    void unregisterView(HEditBox *view);
    
    void create();
    void remove();
    void show();
    void hide();
    
    void refreshView(HEditBox *view);
    
    void refresh();
    virtual CCDictionary *toDictionary(int command);
    
    bool checkView(int viewID, const char *text);
    bool setText(int viewID, const char *text);
private:
    CCArray *m_pViews;
};

class CC_DLL HViewPageManager {
    HSINGLETON_OBJECT(HViewPageManager);
public:
    void registerViewPage(HViewPage *viewPage);
    void unregisterView(HViewPage *viewPage);
    
    void checkView(int viewID, const char *text);
    void setText(int viewID, const char *text);
    
    int count() { return m_pViewPages->count(); }
    
private:
    CCArray *m_pViewPages;
};

class CC_DLL HEditBoxLoader: public CCEditBoxLoader {
public:
    virtual ~HEditBoxLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HEditBoxLoader, loader);
    
protected:
    virtual HEditBox *createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        HEditBox *editBox = new HEditBox();
        editBox->setZoomOnTouchDown(false);
        editBox->autorelease();
        editBox->initWithSizeAndBackgroundSprite(CCSize(280, 32), CCScale9Sprite::createWithSpriteFrame(HSourceCache::getInstance()->spriteFrameWithName("ui_empty.png")));
        return editBox;
    }
};

//class CC_DLL HPlatformViewManager: public CCObject {
//    HSINGLETON_OBJECT(HPlatformViewManager);
//    CC_SYNTHESIZE(void *, m_pOwner, Owner);
//public:    
//    void createViewPage(HViewPage *viewpage);
//    void deleteViewPage(HViewPage *viewpage);
//    void refreshView(HView *view);
//    void updateViewPage(HViewPage *viewpage);
//    
//    void checkViews(CCDictionary *views);
//    void done();
//};

HNAMESPACE_END

#endif // _VIEW_EXTENTIONS_H_
