
#include "cocos2dxframework.h"
#include "LoadingLayer.h"
#include "GameScene.h"
#include "AppDelegate.h"
#include "NetManager.h"

HNAMESPACE_BEGIN

static HMaskLayer *generateLayerColor() {
    HMaskLayer *layer = HMaskLayer::create();
    layer->retain();
    return layer;
}

HGameScene::HGameScene(): CCScene(), m_pGameShowLayer(NULL),  m_pGameDecorationLayer(NULL), m_pUILayer(NULL), m_pLoadingLayer(NULL) {
    init();
    
    HMaskLayer *pMaskLayer = generateLayerColor();
    addChild(pMaskLayer, 3);
    pMaskLayer->setVisible(false);
    HCommonLayer::setMaskLayer(pMaskLayer);
    
    m_pGameShowLayer = new HGameShowLayer();
    addChild(m_pGameShowLayer, -1);
    m_pGameDecorationLayer = new HUILayer();//HGameDecorationLayer();
    addChild(m_pGameDecorationLayer, 0);
    m_pUILayer = new HUILayer();
    addChild(m_pUILayer, 1);
}

HGameScene::~HGameScene() {
    if (m_pLoadingLayer) delete m_pLoadingLayer;
    delete m_pUILayer;
    delete m_pGameShowLayer;
    delete m_pGameDecorationLayer;
}

bool HGameScene::init() {
    if (!CCScene::init()) return false;
    
    return true;
}

void HGameScene::startAIV(bool bLockTouch) {
    if (!m_pLoadingLayer) {
        m_pLoadingLayer = new HLoadingLayer();
        addChild(m_pLoadingLayer, 2);
    }
    m_pLoadingLayer->setLockTouch(bLockTouch);
    m_pLoadingLayer->setVisible(true);
}

void HGameScene::stopAIV() {
    if (m_pLoadingLayer) {
        m_pLoadingLayer->setVisible(false);
        m_pLoadingLayer->setLockTouch(false);
    }
}

void HGameScene::startGame() {
    stopAIV();
//    m_pUILayer->dismissAllRootLayers();

    AppDelegate::getInstance()->getGameManager()->startGame();
    
    HNetManager::getInstance()->startHeartBeat();
}

HNAMESPACE_END
