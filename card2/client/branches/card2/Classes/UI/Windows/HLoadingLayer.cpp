//
//  HLoadingLayer.cpp
//  card
//
//  Created by zhou gang on 13-8-26.
//
//

#include "../../headers.h"
#include "HLoadingLayer.h"

HLoadingLayer2::HLoadingLayer2(): m_bLockTouch(false) {
    m_bIsFullScreen = false;
    readNodeGraphFromFile("Loading.ccbi");
    
    setTouchMode(kCCTouchesOneByOne);
    setTouchPriority(-512);
    setTouchEnabled(true);
}

HLoadingLayer2::~HLoadingLayer2() {
    
}

bool HLoadingLayer2::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    return m_bLockTouch && isVisible();
}

HLoadingLayer2 *HLoadingLayer2::create() {
    HLoadingLayer2 *layer = new HLoadingLayer2();
//    layer->autorelease();
    CC_AUTO_RELEASE(layer);
    return layer;
}
