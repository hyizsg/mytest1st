
#include "cocos2dxframework.h"
#include "GameScene.h"
#include "AppDelegate.h"

HNAMESPACE_BEGIN

static const CCAffineTransform gTransformOutOfScreen = CCAffineTransformMake(1, 0, 0, 1, -10000, 0);

CCDictionary *HCommonLayer::m_spAllActions = new CCDictionary();
HMaskLayer *HCommonLayer::m_spMasklayer = NULL;

HCommonLayer::HCommonLayer(): CCLayer(), /*m_bEnableTouch(true), */m_bIsInForeground(true), m_bDisableAnimInOut(false), m_bOutOfScreen(false), m_iBaseTouchPriority(0), m_pActionIn(NULL), m_pActionOut(NULL) {
    setTouchMode(kCCTouchesOneByOne);
    init();
    setActionIn((CCFiniteTimeAction *)m_spAllActions->objectForKey("in"));
    setActionOut((CCFiniteTimeAction *)m_spAllActions->objectForKey("out"));
//    HTimerManager::getInstance()->asyncProcess(HInvocation::create(this, hinvocation_selector(HCommonLayer::animIn), 0, NULL));
    setTouchPriority(HTOUCHPRIORITY_LAYERSPACE / 2);
}

HCommonLayer::~HCommonLayer() {
//    stopAllActions();
    setActionIn(NULL);
    setActionOut(NULL);
}

int HCommonLayer::getBaseTouchPriority() {
    return m_iBaseTouchPriority;
}

void HCommonLayer::setBaseTouchPriority(int priority) {
    m_iBaseTouchPriority = priority;
//    updatePriorityTouchLayer(this);
}

//bool HCommonLayer::getEnableTouch() {
//    return m_bEnableTouch;
//}
//
//void HCommonLayer::setEnableTouch(bool enabled) {
//    if (m_bEnableTouch == enabled) return;
//    setTouchEnabled(enabled);
//    m_bEnableTouch = enabled;
//    updateEnabledTouchLayer(this);
//}

CCObject *HCommonLayer::onNeedRegisterTouchDispatcher(int command, CCObject *param) {
    registerWithTouchDispatcher();
    return NULL;
}

bool HCommonLayer::getOutOfScreen() {
    return m_bOutOfScreen;
}

void HCommonLayer::setOutOfScreen(bool var) {
//    if (m_bOutOfScreen == var) return;
    
    m_bOutOfScreen = var;
    CCLayer::m_bTransformDirty = true;
    setVisible(!m_bOutOfScreen);
//    if (m_bOutOfScreen) {
//        onExit();
//    } else {
//        onEnter();
//    }
//    if (!m_bOutOfScreen) {
//        setVisible(!m_bOutOfScreen);
//    }
}

CCAffineTransform HCommonLayer::nodeToParentTransform(void) {
//    if (m_bOutOfScreen) {
//        setVisible(!m_bOutOfScreen);
//    }
    return CCAffineTransformConcat(CCLayer::nodeToParentTransform(), m_bOutOfScreen ? gTransformOutOfScreen : CCAffineTransformIdentity);
}

//void HCommonLayer::setTouchEnabled(bool enabled) {
//    CCLayer::setTouchEnabled(enabled);
//    if (enabled) {
//        HTimerManager::getInstance()->asyncProcess(HInvocation::create(this, hinvocation_selector(HCommonLayer::onNeedRegisterTouchDispatcher), 0, NULL));
//    }
//}

//void HCommonLayer::registerWithTouchDispatcher() {
////    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
////    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_iBaseTouchPriority + HTOUCHPRIORITY_LAYERSPACE / 2, true);
//    CCLayer::registerWithTouchDispatcher();
//}

bool HCommonLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    return isTouchEnabled();
}

void HCommonLayer::onEnterForeground() {
//    updateEditboxTouchLayer(this, true);
    
    willMoveToWindow(getParent());
    
//    setTouchEnabled(true);
//    if (!m_bIsInForeground) {
//        m_bIsInForeground = true;
//        onEnter();
//    }
    onEnter();
}

void HCommonLayer::onEnterBackground() {
//    if (m_bIsInForeground) {
//        m_bIsInForeground = false;
//        onExit();
//    }
    onExit();
//    setTouchEnabled(false);
//    updateEditboxTouchLayer(this, false);
    
    willMoveToWindow(NULL);
}

bool HCommonLayer::init() {
    if (!CCLayer::init()) return false;
    CCDirector *pDirect = CCDirector::sharedDirector();
    CCSize sScreen = pDirect->getWinSize();
    CCSize sUI = AppDelegate::getInstance()->getGameManager()->getScreenSize();
    setContentSize(sUI);
    setAnchorPoint(CCPointZero);
//    setPosition(CCPointZero);
//    setPosition(CCPointMake(sScreen.width / 2, sScreen.height / 2));
    CCPoint pos = CCPointZero;
    //delete by zg
//    if (pDirect->hasDefaultScissor()) {
//        pos = pDirect->defaultScissor()->origin;
//    }
    setPosition(CCPointMake(pos.x / 2, pos.y / 2));
    setTouchEnabled(false);
    return true;
}

void HCommonLayer::startAIV(bool bLockTouch) {
    AppDelegate::getInstance()->getGameScene()->startAIV(bLockTouch);
}

void HCommonLayer::stopAIV() {
    AppDelegate::getInstance()->getGameScene()->stopAIV();
}

void HCommonLayer::setActions(const char *inKey, const char *outKey) {
    if (inKey) {
        setActionIn((CCFiniteTimeAction *)m_spAllActions->objectForKey(inKey));
    }
    if (outKey) {
        setActionOut((CCFiniteTimeAction *)m_spAllActions->objectForKey(outKey));
    }
}

void HCommonLayer::animIn(HCommonLayer *endReceiver) {
    if (!getDisableAnimInOut() && m_pActionIn) {
        if (!endReceiver) endReceiver = this;
        runAction(CCSequence::createWithTwoActions(m_pActionIn, CCCallFunc::create(endReceiver, callfunc_selector(HCommonLayer::animInEnd))));
    }
}

void HCommonLayer::animOut(HCommonLayer *endReceiver) {
    if (!getDisableAnimInOut() && m_pActionOut) {
        if (!endReceiver) endReceiver = this;
        runAction(CCSequence::createWithTwoActions(m_pActionOut, CCCallFunc::create(endReceiver, callfunc_selector(HCommonLayer::animOutEnd))));
    }
}

void HCommonLayer::updatePriorityTouchLayer(CCNode *node) {
    CCArray *children = node->getChildren();
    if (children) {
        int count = children->count();
        for (int i = 0; i < count; ++i) {
            CCNode *child = (CCNode *)children->objectAtIndex(i);
            if (dynamic_cast<CCControl *>(child)) {
                CCControl *control = (CCControl *)child;
                int priority = control->getTouchPriority();
                priority += m_iBaseTouchPriority;
                while (priority > m_iBaseTouchPriority + HTOUCHPRIORITY_LAYERSPACE / 2) priority -= HTOUCHPRIORITY_LAYERSPACE;
                while (priority < m_iBaseTouchPriority - HTOUCHPRIORITY_LAYERSPACE / 2) priority += HTOUCHPRIORITY_LAYERSPACE;
                control->setTouchPriority(priority);
                if (control->isTouchEnabled()) {
                    control->setTouchEnabled(false);
                    control->setTouchEnabled(true);
                }
            } else if (dynamic_cast<CCScrollView *>(child)) {
                CCScrollView *scrollView = (CCScrollView *)child;
                int priority = scrollView->getTouchPriority();
                priority += m_iBaseTouchPriority;
                while (priority > m_iBaseTouchPriority + HTOUCHPRIORITY_LAYERSPACE / 2) priority -= HTOUCHPRIORITY_LAYERSPACE;
                while (priority < m_iBaseTouchPriority - HTOUCHPRIORITY_LAYERSPACE / 2) priority += HTOUCHPRIORITY_LAYERSPACE;
                scrollView->setTouchPriority(priority);
                if (scrollView->isTouchEnabled()) {
                    scrollView->setTouchEnabled(false);
                    scrollView->setTouchEnabled(true);
                }
            } else if (dynamic_cast<CCMenu *>(child)) {
                CCMenu *menu = (CCMenu *)child;
                int priority = menu->getTouchPriority();
                priority += m_iBaseTouchPriority;
                while (priority > m_iBaseTouchPriority + HTOUCHPRIORITY_LAYERSPACE / 2) priority -= HTOUCHPRIORITY_LAYERSPACE;
                while (priority < m_iBaseTouchPriority - HTOUCHPRIORITY_LAYERSPACE / 2) priority += HTOUCHPRIORITY_LAYERSPACE;
                menu->setTouchPriority(priority);
                if (menu->isTouchEnabled()) {
                    menu->setTouchEnabled(false);
                    menu->setTouchEnabled(true);
                }
            } else if (dynamic_cast<CCLayer *>(child)) {
                CCLayer *layer = (CCLayer *)child;
                int priority = layer->getTouchPriority();
                priority += m_iBaseTouchPriority;
                while (priority > m_iBaseTouchPriority + HTOUCHPRIORITY_LAYERSPACE / 2) priority -= HTOUCHPRIORITY_LAYERSPACE;
                while (priority < m_iBaseTouchPriority - HTOUCHPRIORITY_LAYERSPACE / 2) priority += HTOUCHPRIORITY_LAYERSPACE;
                layer->setTouchPriority(priority);
                if (layer->isTouchEnabled()) {
                    layer->setTouchEnabled(false);
                    layer->setTouchEnabled(true);
                }
            }
            updatePriorityTouchLayer(child);
        }
    }
}

//void HCommonLayer::updateEditboxTouchLayer(CCNode *node, bool enable) {
//    CCArray *children = node->getChildren();
//    if (children) {
//        int count = children->count();
//        for (int i = 0; i < count; ++i) {
//            CCNode *child = (CCNode *)children->objectAtIndex(i);
//            if (dynamic_cast<CCEditBox *>(child)) {
//                CCEditBox *editBox = (CCEditBox *)child;
//                editBox->setEnabled(enable);
//            }
//            updateEditboxTouchLayer(child, enable);
//        }
//    }
//}

//void HCommonLayer::updateEnabledTouchLayer(CCNode *node) {
//    if (dynamic_cast<CCEditBox *>(node)) {
//        CCEditBox *editBox = (CCEditBox *)node;
//        editBox->setEnabled(m_bEnableTouch);
//    } else if (dynamic_cast<CCLayer *>(node)) {
//        CCLayer *layer = (CCLayer *)node;
//        layer->setTouchEnabled(m_bEnableTouch);
//    }
//    
//    CCArray *children = node->getChildren();
//    if (children) {
//        int count = children->count();
//        for (int i = 0; i < count; ++i) {
//            CCNode *child = (CCNode *)children->objectAtIndex(i);
//            updateEnabledTouchLayer(child);
//        }
//    }
//}

void HCommonLayer::registerAction(CCFiniteTimeAction *action, const char *key) {
    m_spAllActions->setObject(action, key);
}

void HCommonLayer::unregisterAction(const char *key) {
    m_spAllActions->removeObjectForKey(key);
}

HNAMESPACE_END
