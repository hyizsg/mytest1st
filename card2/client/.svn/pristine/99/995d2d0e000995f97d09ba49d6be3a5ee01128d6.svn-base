
#include "cocos2dxframework.h"
#include "LoadingLayer.h"

HNAMESPACE_BEGIN

HLoadingLayer::HLoadingLayer(): m_bLockTouch(false) {
    m_bIsFullScreen = false;
    readNodeGraphFromFile("Loading.ccbi");
    
    setTouchMode(kCCTouchesOneByOne);
    setTouchPriority(-512);
    setTouchEnabled(true);
}

HLoadingLayer::~HLoadingLayer() {
    
}

bool HLoadingLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    return m_bLockTouch && isVisible();
}

HLoadingLayer *HLoadingLayer::create() {
    HLoadingLayer *layer = new HLoadingLayer();
//    layer->autorelease();
    CC_AUTO_RELEASE(layer);
    return layer;
}

HNAMESPACE_END
