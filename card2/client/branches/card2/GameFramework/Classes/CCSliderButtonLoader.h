//
//  CCSliderButtonLoader.h
//  GameFramework
//
//  Created by huangwei on 5/3/13.
//  Copyright (c) 2013 cxj. All rights reserved.
//

#ifndef GameFramework_CCSliderButtonLoader_h
#define GameFramework_CCSliderButtonLoader_h

class CC_DLL CCSliderButtonLoader: public CCControlLoader {
public:
    virtual ~CCSliderButtonLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCSliderButtonLoader, loader);
    
protected:
    virtual CCControlSlider *createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        CCControlSlider *slider = new CCControlSlider();
        slider->autorelease();
        //        editBox->initWithSizeAndBackgroundSprite(CCSize(280, 32), CCScale9Sprite::createWithSpriteFrameName("UIEditBG.png"));
        slider->initWithSprites(haypi::HSourceCache::getInstance()->spriteWithFrameName("ui_empty.png"),haypi::HSourceCache::getInstance()->spriteWithFrameName("ui_empty.png"),haypi::HSourceCache::getInstance()->spriteWithFrameName("ui_empty.png"));
        return slider;
    }
};

#endif
