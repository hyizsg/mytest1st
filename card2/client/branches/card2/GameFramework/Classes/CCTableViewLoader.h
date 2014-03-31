//
//  CCTableViewLoader.h
//  BattleShip
//
//  Created by huangwei on 10/25/12.
//
//

#ifndef __BattleShip__CCTableViewLoader__
#define __BattleShip__CCTableViewLoader__

class CC_DLL CCTableViewLoader: public CCScrollViewLoader {
public:
    virtual ~CCTableViewLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCTableViewLoader, loader);
    
protected:
    virtual CCTableView *createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        CCTableView *tableView = new CCTableView();
        tableView->autorelease();
        tableView->initWithViewSize(CCSizeMake(240, 200));
//        tableView->initWithSizeAndBackgroundSprite(CCSize(240, 200), NULL);//CCScale9Sprite::createWithSpriteFrameName("UIEditBG.png")
        return tableView;
    }
};

#endif /* defined(__BattleShip__CCTableViewLoader__) */
