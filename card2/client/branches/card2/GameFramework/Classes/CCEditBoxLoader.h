#ifndef _CCEDITBOX_LOADER_H_
#define _CCEDITBOX_LOADER_H_

class CC_DLL CCEditBoxLoader: public CCControlButtonLoader {
public:
    virtual ~CCEditBoxLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCEditBoxLoader, loader);
    
protected:
    virtual CCEditBox *createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        CCEditBox *editBox = new CCEditBox();
        editBox->setZoomOnTouchDown(false);
        editBox->autorelease();
//        editBox->initWithSizeAndBackgroundSprite(CCSize(280, 32), CCScale9Sprite::createWithSpriteFrameName("UIEditBG.png"));
        editBox->initWithSizeAndBackgroundSprite(CCSize(280, 32), CCScale9Sprite::createWithSpriteFrame(haypi::HSourceCache::getInstance()->spriteFrameWithName("ui_empty.png")));
        return editBox;
    }
};

#endif // _CCEDITBOX_LOADER_H_
