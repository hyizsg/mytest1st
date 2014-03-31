
#include "cocos2dxframework.h"
#include "GameScene.h"
#include "AppDelegate.h"

HNAMESPACE_BEGIN

static float gfDurationFadeIn = 0.30f;
static float gfDurationFadeOut = 0.30f;
void setDurationOfFadeInOut(float fin, float fout) {
    gfDurationFadeIn = fin;
    gfDurationFadeOut = fout;
}

HUILayer::HUILayer(): m_pCurrentLayer(NULL), m_pPreEndingLayer(NULL) {
    m_pQueneRootLayers = new CCArray(4);
    m_pRecycledRootLayers = new CCArray(8);
    m_pBackupRootLayer = new CCArray(4);
}

HUILayer::~HUILayer() {
    delete m_pBackupRootLayer;
    delete m_pRecycledRootLayers;
    delete m_pQueneRootLayers;
}

void HUILayer::presentRootLayer(HRootLayer *layer, bool inQueue) {
    if (inQueue && (getChildrenCount() > 0)) {
        m_pQueneRootLayers->addObject(layer);
    } else {
        if (!layer->getDisableAnimInOut()) stopMaskAnimation();
        
        CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(false);
        m_pCurrentLayer = layer;
        stopAIV();
        if (getChildrenCount() > 0) {
            HRootLayer *rootLayer = dynamic_cast<HRootLayer *>(getChildren()->objectAtIndex(getChildrenCount() - 1));
            if (rootLayer) {
                rootLayer->onShowEditbox(false);
                rootLayer->onEnterBackground();
            }
        }
        int zOrder = !layer->getIsFullScreen() ? 1000 : 0;
        int iLayerBasePriority = ((this == AppDelegate::getInstance()->getGameScene()->getUILayer()) ? 20 : 10) * -HTOUCHPRIORITY_LAYERSPACE;
        for (int i = getChildrenCount() - 1; i >= 0; --i) {
            HRootLayer *prelayer = (HRootLayer *)getChildren()->objectAtIndex(i);
            if ((prelayer->getIsFullScreen() && layer->getIsFullScreen()) || (!prelayer->getIsFullScreen() && !layer->getIsFullScreen())) {
                iLayerBasePriority = prelayer->getBaseTouchPriority() - HTOUCHPRIORITY_LAYERSPACE;
                zOrder = prelayer->getZOrder() + 1;
                break;
            }
        }
        zOrder = 0;
        iLayerBasePriority = 0;
        addChild(layer, zOrder);
        if (this == AppDelegate::getInstance()->getGameScene()->getUILayer()) {
            if (!layer->getIsFullScreen()) {
                layer->setBaseTouchPriority(iLayerBasePriority);
//                layer->setTouchEnabled(false);
            }
            layer->setTouchEnabled(true);
        } else {
            layer->setBaseTouchPriority(iLayerBasePriority);
            layer->setTouchEnabled(false);
        }
        layer->onEnterForeground();
        if (this == AppDelegate::getInstance()->getGameManager()->getUILayer()) {
            AppDelegate::getInstance()->getGameManager()->onRootLayerCountChanged(getChildrenCount());
        }
        if (!layer->getDisableAnimInOut()) {
            if (layer->getActionIn()) {
                layer->animIn(NULL);
            } else {
                m_spMasklayer->setVisible(true);
                m_spMasklayer->setPresentUI(true);
                layer->setVisible(false);
                CCFadeIn *fadeIn = CCFadeIn::create(gfDurationFadeIn);
                CCCallFunc *cfIn = CCCallFunc::create(this, callfunc_selector(HUILayer::endPresentFadeIn));
                CCFadeOut *fadeOut = CCFadeOut::create(gfDurationFadeOut);
                CCCallFunc *cfOut = CCCallFunc::create(this, callfunc_selector(HUILayer::endPresentFadeOut));
                m_spMasklayer->runAction(CCSequence::create(fadeIn, cfIn, fadeOut, cfOut, NULL));
            }
        } else {
            updateAllRootLayers();
            CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
            layer->didMoveToWindow(layer->getParent());
            layer->onEnterTransitionDidFinish();
        }
        layer->onShowEditbox(true);
    }
}

void HUILayer::dismissRootLayer(HRootLayer *layer) {
    if (!layer->getDisableAnimInOut()) stopMaskAnimation();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(false);
    if (m_pPreEndingLayer && (m_pPreEndingLayer != layer)) {
        m_pPreEndingLayer->onShowEditbox(false);
        m_pPreEndingLayer->onEnterBackground();
        removeChild(m_pPreEndingLayer, true);
        m_pPreEndingLayer = NULL;
    }
    m_pCurrentLayer = NULL;
    m_pPreEndingLayer = layer;
    m_pPreEndingLayer->onShowEditbox(false);
    if (!layer->getDisableAnimInOut()) {
        if (layer->getActionOut()) {
            layer->animOut(this);
        } else {            
//            endDismissFadeOut();
            m_spMasklayer->setVisible(true);
            m_spMasklayer->setPresentUI(false);
            CCFadeIn *fadeIn = CCFadeIn::create(gfDurationFadeIn);
            CCCallFunc *cfIn = CCCallFunc::create(this, callfunc_selector(HUILayer::endDismissFadeIn));
            CCFadeOut *fadeOut = CCFadeOut::create(gfDurationFadeOut);
            CCCallFunc *cfOut = CCCallFunc::create(this, callfunc_selector(HUILayer::endDismissFadeOut));
            m_spMasklayer->runAction(CCSequence::create(fadeIn, cfIn, fadeOut, cfOut, NULL));
        }
    } else {
//        animOutEnd();
        endDismissFadeIn();
        endDismissFadeOut();
//        CCDirector::sharedDirector()->getTouchDispatcher()->setPaused(false);
    }
}

void HUILayer::dismissAllRootLayers() {
    stopMaskAnimation();
    m_pCurrentLayer = NULL;
    m_pPreEndingLayer = NULL;
    m_pQueneRootLayers->removeAllObjects();
    
    int count = getChildrenCount();
    CCArray *children = getChildren();
    for (int i = 0; i < count; ++i) {
        HRootLayer *layer = (HRootLayer *)children->objectAtIndex(i);
        layer->onEnterBackground();
    }
    
    removeAllChildrenWithCleanup(true);
    updateAllRootLayers();
    endPresentFadeOut();
    if (this == AppDelegate::getInstance()->getGameManager()->getUILayer()) {
        AppDelegate::getInstance()->getGameManager()->onRootLayerCountChanged(getChildrenCount());
    }
}

void HUILayer::backupAllRootLayers() {
    m_pBackupRootLayer->removeAllObjects();
    int count = getChildrenCount();
    CCArray *children = getChildren();
    for (int i = 0; i < count; ++i) {
        HRootLayer *layer = (HRootLayer *)children->objectAtIndex(i);
        layer->onShowEditbox(false);
        m_pBackupRootLayer->addObject(layer);
        layer->onEnterBackground();
    }
    removeAllChildrenWithCleanup(false);
    updateAllRootLayers();
}

void HUILayer::restoreAllRootLayers() {
    int count = m_pBackupRootLayer->count();
    for (int i = 0; i < count; ++i) {
        HRootLayer *layer = (HRootLayer *)m_pBackupRootLayer->objectAtIndex(i);
        if (i == count - 1) layer->onShowEditbox(true);
        addChild(layer, layer->getZOrder());
        layer->onEnterForeground();
    }
    m_pBackupRootLayer->removeAllObjects();
    updateAllRootLayers();
}

bool HUILayer::onBackPressed() {
    int count = getChildrenCount();
    if (count < 1) return false;
    HRootLayer *layer = (HRootLayer *)getChildren()->objectAtIndex(count - 1);
    if (count == 1) {
        if ((AppDelegate::getInstance()->getGameScene()->getGameDecorationLayer()->getChildrenCount() < 1) &&
            (AppDelegate::getInstance()->getGameScene()->getGameShowLayer()->getChildrenCount() < 1)) {
            return false;
        }
    }
    if (layer->getClass() == "HLoginMainWindow") return false;
    dismissRootLayer(layer);
    return true;
}

bool HUILayer::onMenuPressed() {
    return false;
}

HRootLayer *HUILayer::findWithClass(const std::string &className) {
    CCArray *children = getChildren();
    int count = children->count();
    int i = 0;
    for (i = 0; i < count; ++i) {
        HRootLayer *layer = (HRootLayer *)children->objectAtIndex(i);
        if (layer->isKindOf(className)) return layer;
    }
    count = m_pQueneRootLayers->count();
    for (i = 0; i < count; ++i) {
        HRootLayer *layer = (HRootLayer *)m_pQueneRootLayers->objectAtIndex(i);
        if (layer->isKindOf(className)) return layer;
    }
    return NULL;
}

void HUILayer::onOK() {
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->end();
}

void HUILayer::animOutEnd() {
    if (m_pPreEndingLayer) {
        m_pPreEndingLayer->onEnterBackground();
        removeChild(m_pPreEndingLayer);
        m_pPreEndingLayer = NULL;
    }
    m_pCurrentLayer = NULL;
    if (getChildrenCount() < 1) {
        if (m_pQueneRootLayers->count() > 0) {
            HRootLayer *layer = (HRootLayer *)m_pQueneRootLayers->objectAtIndex(0);
            presentRootLayer(layer);
//            addChild(layer);
            m_pCurrentLayer = layer;
//            layer->animIn(NULL);
            m_pQueneRootLayers->removeObjectAtIndex(0);
        }
    }
    updateAllRootLayers();
    HCommonLayer::animOutEnd();
    if (getChildrenCount() > 0) {
        HRootLayer *rootLayer = dynamic_cast<HRootLayer *>(getChildren()->objectAtIndex(getChildrenCount() - 1));
        if (rootLayer) {
            rootLayer->onShowEditbox(true);
            rootLayer->onEnterForeground();
            m_pCurrentLayer = rootLayer;
        }
    }
    if (this == AppDelegate::getInstance()->getGameManager()->getUILayer()) {
        AppDelegate::getInstance()->getGameManager()->onRootLayerCountChanged(getChildrenCount());
    }
}

void HUILayer::updateAllRootLayers() {
    if (this == AppDelegate::getInstance()->getGameScene()->getGameDecorationLayer()) return;
    
    HCommonLayer *gameShowLayer = AppDelegate::getInstance()->getGameScene()->getGameShowLayer();
    HCommonLayer *gameDecorationLayer = AppDelegate::getInstance()->getGameScene()->getGameDecorationLayer();
    bool gameShow = false;
    
    int childrenCount = getChildrenCount();
    if (childrenCount > 0) {
        int fullScreenLayerCount = 0;
        int i = childrenCount - 1;
        for (; i >= 0; --i) {
            HRootLayer *layer = (HRootLayer *)getChildren()->objectAtIndex(i);
            if (fullScreenLayerCount < 1) {
                layer->setOutOfScreen(false);
            } else {
                layer->setOutOfScreen(true);
            }
            if (layer->getIsFullScreen()) {
                ++fullScreenLayerCount;
            }
            if (fullScreenLayerCount > 1) break;
        }
        if (fullScreenLayerCount > 0) {
            gameShow = false;
        } else {
            gameShow = true;
        }
        for (; i >= 0; --i) {
            HRootLayer *layer = (HRootLayer *)getChildren()->objectAtIndex(i);
            layer->setOutOfScreen(true);
        }
    } else {
        gameShow = true;
    }
    
    gameShowLayer->setOutOfScreen(!gameShow);
    gameDecorationLayer->setOutOfScreen(!gameShow);
    if (childrenCount < 1) {
        gameShowLayer->onEnter();
        gameDecorationLayer->onEnter();
    } else {
        gameShowLayer->onExit();
        gameDecorationLayer->onExit();
    }
}

void HUILayer::stopMaskAnimation() {
    if (m_spMasklayer->isVisible()) {
        m_spMasklayer->stopAllActions();
        if (m_spMasklayer->getPresentUI()) {
            endPresentFadeIn();
            endPresentFadeOut();
        } else {
            endDismissFadeIn();
            endDismissFadeOut();
        }
    }
}

void HUILayer::endPresentFadeIn() {
//    if (m_pCurrentLayer) m_pCurrentLayer->setVisible(true);
    updateAllRootLayers();
}

void HUILayer::endPresentFadeOut() {
    CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
    m_spMasklayer->setVisible(false);
    
    if (m_pCurrentLayer) {
        m_pCurrentLayer->didMoveToWindow(m_pCurrentLayer->getParent());
        m_pCurrentLayer->onEnterTransitionDidFinish();
    }
}

void HUILayer::endDismissFadeIn() {
    
    if (m_pPreEndingLayer) {
        m_pPreEndingLayer->didMoveToWindow(NULL);
    }
    
    
    animOutEnd();
    m_spMasklayer->setVisible(true);
}

void HUILayer::endDismissFadeOut() {
    CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
    m_spMasklayer->setVisible(false);
    
    if (m_pCurrentLayer) {
        m_pCurrentLayer->didMoveToWindow(m_pCurrentLayer->getParent());
        m_pCurrentLayer = NULL;
    }
}

HNAMESPACE_END
