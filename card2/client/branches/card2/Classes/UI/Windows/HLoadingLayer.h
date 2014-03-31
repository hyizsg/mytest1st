//
//  HLoadingLayer.h
//  card
//
//  Created by zhou gang on 13-8-26.
//
//

#ifndef __card__HLoadingLayer__
#define __card__HLoadingLayer__

class HLoadingLayer2: public HWindow {
    HCLASSTYPE(HLoadingLayer2, HWindow);
    CC_SYNTHESIZE(bool, m_bLockTouch, LockTouch);
public:
    HLoadingLayer2();
    virtual ~HLoadingLayer2();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    static HLoadingLayer2 *create();
};

#endif /* defined(__card__HLoadingLayer__) */
