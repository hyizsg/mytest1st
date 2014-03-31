
#include "cocos2dxframework.h"
#include "GameScene.h"
#include "AppDelegate.h"

HNAMESPACE_BEGIN

//HTouchEnabledLayerColor
HTouchEnabledLayerColor::HTouchEnabledLayerColor(): CCLayerColor(), m_pDelegate(NULL), m_bTipAnimation(false), m_pTipLabel(NULL), m_pTimer(NULL), m_iTouchStatus(HTOUCHSTATUS_NONE) {
    m_pBakNodeList = new CCArray(2);
    setTouchMode(kCCTouchesOneByOne);
    setTouchPriority(-256);
    setZOrder(100000);
    m_pTimer = new HTimer;
    m_pTimer->registerTimer(this, 0, 0.1f, -1);
}

HTouchEnabledLayerColor *HTouchEnabledLayerColor::create(const ccColor4B& color, float w, float h) {
    HTouchEnabledLayerColor *pRet = new HTouchEnabledLayerColor();
//    pRet->autorelease();
    CC_AUTO_RELEASE(pRet);
    if (pRet->initWithColor(color, w, h)) {
//        CCControlButton *btn = CCControlButton::create("abcdefg", "arial", 32);
//        btn->setPreferredSize(CCSizeMake(100, 100));
//        btn->setPosition(CCPointMake(100, 100));
//        pRet->addChild(btn, 100);
//        btn->setTouchPriority(-257);
        return pRet;
    }
    return NULL;
}

HTouchEnabledLayerColor *HTouchEnabledLayerColor::create() {
    PHSCREENDATA pData = currentScreenData();
    return HTouchEnabledLayerColor::create(ccc4(0, 0, 0, 128), pData->width, pData->height);
}

void HTouchEnabledLayerColor::onTimeOut(int gid, int count) {
    if (!m_bTipAnimation) {
        HTimerManager::getInstance()->unregisterTimer(m_pTimer);
        return;
    }
    if (m_strAdderPos < m_str.length()) {
        char c = m_str[m_strAdderPos];
        m_strAdderPos += ((c & 0xE0)==0xE0) ? 3 : (((c & 0xC0)==0xC0) ? 2 : 1); //support unicode 32, not support unicode 64
        m_pTipLabel->setString(m_str.substr(0, m_strAdderPos).c_str());
    }
    if (m_strAdderPos >= m_str.length()) {
        HTimerManager::getInstance()->unregisterTimer(m_pTimer);
        m_bTipAnimation = false;
    }
}

void HTouchEnabledLayerColor::setTipString(CCLabelTTF *label, const char *str, bool oneByOne) {
    if (!label || !str) return;
    m_bTipAnimation = oneByOne;
    if (str[0] == '\0') m_bTipAnimation = false;
    if (m_bTipAnimation) {
        m_pTipLabel = label;
        m_str = str;
        m_strAdderPos = 0;
        HTimerManager::getInstance()->registerTimer(m_pTimer);
    } else {
        label->setString(str);
    }
}

void HTouchEnabledLayerColor::show() {
    setVisible(true);
//    setTouchEnabled(true);
//    setVisible(true);
//    CCLayerColor::onEnter();
}

void HTouchEnabledLayerColor::hide() {
    setVisible(false);
//    setTouchEnabled(false);
//    setVisible(false);
//    CCLayerColor::onExit();
}

void HTouchEnabledLayerColor::bakAllPriorities(HBakNodeInfo *info, CCNode *node) {
    if (dynamic_cast<CCControl *>(node)) {
        int priority = ((CCControl *)node)->getTouchPriority();
        info->addPriority(node, priority);
    } else if (dynamic_cast<CCScrollView *>(node)) {
        int priority = ((CCScrollView *)node)->getTouchPriority();
        info->addPriority(node, priority);
    } else if (dynamic_cast<CCMenu *>(node)) {
        int priority = ((CCMenu *)node)->getTouchPriority();
        info->addPriority(node, priority);
    } else if (dynamic_cast<CCLayer *>(node)) {
        int priority = ((CCLayer *)node)->getTouchPriority();
        info->addPriority(node, priority);
    }
    CCArray *children = node->getChildren();
    if (children) {
        int count = children->count();
        for (int i = 0; i < count; ++i) {
            CCNode *child = (CCNode *)children->objectAtIndex(i);
            bakAllPriorities(info, child);
        }
    }
}

void HTouchEnabledLayerColor::restoreAllPriorities(HBakNodeInfo *info) {
    for (int i = info->m_pPriorities->count() - 1; i >= 0; --i) {
        HBakNodeInfo::HBakProrityInfo *bak = (HBakNodeInfo::HBakProrityInfo *)info->m_pPriorities->objectAtIndex(i);
        setPriority(bak->m_pNode, bak->m_iPriority);
    }
}

void HTouchEnabledLayerColor::presentNode(CCNode *node) {
    if (node->getParent() == this) return;
    
    HBakNodeInfo *info = HBakNodeInfo::create(node, node->getParent(), node->getPosition());
    bakAllPriorities(info, node);
    m_pBakNodeList->addObject(info);
    
    CCPoint pos = node->getPosition();
    pos = node->getParent()->convertToWorldSpace(pos);
    pos = convertToNodeSpace(pos);
    node->retain();
    node->removeFromParentAndCleanup(false);
    addChild(node);
//    pos = node->convertToNodeSpace(pos);
    node->setPosition(pos);
    node->release();
    updatePriority(node);
}


CCObject *HTouchEnabledLayerColor::dismissNodeEx(int command, HEndDismissNode *notify) {
    CCNode *node = notify->getNode();
    do {
        if (node->getParent() != this) break;
        HBakNodeInfo *info = NULL;
        for (int i = m_pBakNodeList->count() - 1; i >= 0; --i) {
            info = (HBakNodeInfo *)m_pBakNodeList->objectAtIndex(i);
            if (node == info->m_pNode) {
                break;
            }
            info = NULL;
        }
        if (!info) break;
        
        node->retain();
        node->removeFromParentAndCleanup(false);
        info->m_pParent->addChild(node, info->m_iIndex);
        node->setScaleX(info->m_fScaleX);
        node->setScaleY(info->m_fScaleY);
        node->setPosition(info->m_ptPos);
        node->release();
        
        restoreAllPriorities(info);
        m_pBakNodeList->removeObject(info);
    } while (false);
    if (notify->getTarget() && notify->getAction()) {
        (notify->getTarget()->*notify->getAction())(node);
    }
    return NULL;
}

void HTouchEnabledLayerColor::dismissNode(CCNode *node, CCObject *pTarget, SEL_HTutorialEndDismiss notify, bool immediately) {
    if (immediately) {
        dismissNodeEx(0, HEndDismissNode::create(pTarget, notify, node));
    } else {
        HTimerManager::getInstance()->asyncProcess(HInvocation::create(this,
                                                                       hinvocation_selector(HTouchEnabledLayerColor::dismissNodeEx),
                                                                       0,
                                                                       HEndDismissNode::create(pTarget, notify, node)), false);
    }
}

CCObject *HTouchEnabledLayerColor::dismissAllNodesEx(int command, CCObject *param) {
    HBakNodeInfo *info = NULL;
    for (int i = m_pBakNodeList->count() - 1; i >= 0; --i) {
        info = (HBakNodeInfo *)m_pBakNodeList->objectAtIndex(i);
        CCNode *node = info->m_pNode;
        node->retain();
        node->removeFromParentAndCleanup(false);
        info->m_pParent->addChild(node, info->m_iIndex);
        node->setScaleX(info->m_fScaleX);
        node->setScaleY(info->m_fScaleY);
        node->setPosition(info->m_ptPos);
        node->release();
        restoreAllPriorities(info);
    }
    m_pBakNodeList->removeAllObjects();
    return NULL;
}

void HTouchEnabledLayerColor::dismissAllNodes() {
    dismissAllNodesEx(0, NULL);
//    HTimerManager::getInstance()->asyncProcess(HInvocation::create(this,
//                                                                   hinvocation_selector(HTouchEnabledLayerColor::dismissAllNodesEx),
//                                                                   0,
//                                                                   NULL));
}

void HTouchEnabledLayerColor::onEnter() {
    if (isVisible()) CCLayerColor::onEnter();
}

void HTouchEnabledLayerColor::onExit() {
    if (isVisible()) CCLayerColor::onExit();
}

void HTouchEnabledLayerColor::updatePriority(CCNode *node) {
    HTimerManager::getInstance()->asyncProcess(HInvocation::create(this, hinvocation_selector(HTouchEnabledLayerColor::updatePriorityEx), 0, node), false);
}

CCObject *HTouchEnabledLayerColor::updatePriorityEx(int command, CCNode *node) {
    int iBasePriority = getTouchPriority();
    
    if (dynamic_cast<CCControl *>(node)) {
        CCControl *control = (CCControl *)node;
        int priority = control->getTouchPriority();
        priority = iBasePriority - 9;
        control->setTouchPriority(priority);
        if (control->isTouchEnabled()) {
            control->setTouchEnabled(false);
            control->setTouchEnabled(true);
        }
    } else if (dynamic_cast<CCScrollView *>(node)) {
        CCScrollView *scrollView = (CCScrollView *)node;
        int priority = scrollView->getTouchPriority();
        priority = iBasePriority - 11;
        scrollView->setTouchPriority(priority);
        if (scrollView->isTouchEnabled()) {
            scrollView->setTouchEnabled(false);
            scrollView->setTouchEnabled(true);
        }
    } else if (dynamic_cast<CCMenu *>(node)) {
        CCMenu *menu = (CCMenu *)node;
        int priority = menu->getTouchPriority();
        priority = iBasePriority - 128;
        menu->setTouchPriority(priority);
        if (menu->isTouchEnabled()) {
            menu->setTouchEnabled(false);
            menu->setTouchEnabled(true);
        }
    } else if (dynamic_cast<CCLayer *>(node)) {
        CCLayer *layer = (CCLayer *)node;
        int priority = layer->getTouchPriority();
        priority = iBasePriority;
        layer->setTouchPriority(priority);
        if (layer->isTouchEnabled()) {
            layer->setTouchEnabled(false);
            layer->setTouchEnabled(true);
        }
    }

    CCArray *children = node->getChildren();
    if (children) {
        int count = children->count();
        for (int i = 0; i < count; ++i) {
            CCNode *child = (CCNode *)children->objectAtIndex(i);
            updatePriorityEx(command, child);
        }
    }
    
    return NULL;
}

int HTouchEnabledLayerColor::getPriority(CCNode *node) {
    int priority = 0;
    if (dynamic_cast<CCControl *>(node)) {
        priority = ((CCControl *)node)->getTouchPriority();
    } else if (dynamic_cast<CCScrollView *>(node)) {
        priority = ((CCScrollView *)node)->getTouchPriority();
    } else if (dynamic_cast<CCMenu *>(node)) {
        priority = ((CCMenu *)node)->getTouchPriority();
    } else if (dynamic_cast<CCLayer *>(node)) {
        priority = ((CCLayer *)node)->getTouchPriority();
    }
    return priority;
}

void HTouchEnabledLayerColor::setPriority(CCNode *node, int priority) {
    if (dynamic_cast<CCControl *>(node)) {
        CCControl *control = (CCControl *)node;
        control->setTouchPriority(priority);
        if (control->isTouchEnabled()) {
            control->setTouchEnabled(false);
            control->setTouchEnabled(true);
        }
    } else if (dynamic_cast<CCScrollView *>(node)) {
        CCScrollView *scrollView = (CCScrollView *)node;
        scrollView->setTouchPriority(priority);
        if (scrollView->isTouchEnabled()) {
            scrollView->setTouchEnabled(false);
            scrollView->setTouchEnabled(true);
        }
    } else if (dynamic_cast<CCMenu *>(node)) {
        CCMenu *menu = (CCMenu *)node;
        menu->setTouchPriority(priority);
        if (menu->isTouchEnabled()) {
            menu->setTouchEnabled(false);
            menu->setTouchEnabled(true);
        }
    } else if (dynamic_cast<CCLayer *>(node)) {
        CCLayer *layer = (CCLayer *)node;
        layer->setTouchPriority(priority);
        if (layer->isTouchEnabled()) {
            layer->setTouchEnabled(false);
            layer->setTouchEnabled(true);
        }
    }
}



bool HRootLayer::m_sbRatioOfEquality = false;
bool HRootLayer::m_sbAdjustForDifferentScreent = false;

HRootLayer::HRootLayer():HCommonLayer(), m_pCCBAnimationManager(NULL), CCEditBoxDelegate(), m_pTutorialNode(NULL), m_bIsFullScreen(true), m_pLabelTitle(NULL), m_pBtnBack(NULL), m_pBtnClose(NULL), m_pViewPage(NULL), m_fScaleX(1.0f), m_fScaleY(1.0) {
    PHSCREENDATA pData = currentScreenData();
    m_szDesign = CCSizeMake(pData->width, pData->height);
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
//    this->setTouchEnabled(true);
    m_nRemoteState = 0;
    m_pEditBoxList = new CCArray(8);
    m_pIgnoreNodeArr = new CCArray;
    m_pCCbNode = NULL;
}

HRootLayer::~HRootLayer() {
    delete m_pEditBoxList;
    if (m_pViewPage) {
        m_pViewPage->remove();
//        HViewPageManager::getInstance()->unregisterView(m_pViewPage);
        delete m_pViewPage;
    }
    setCCBAnimationManager(NULL);
    CC_SAFE_RELEASE_NULL(m_pIgnoreNodeArr);
    CC_SAFE_RELEASE_NULL(m_pCCbNode);
}

void HRootLayer::needTutorial(bool show) {
    if (m_pTutorialNode) {
        if (show) m_pTutorialNode->show();
        else {
//            m_pTutorialNode->hide();
            m_pTutorialNode->removeFromParent();
            m_pTutorialNode = NULL;
        }
//        HTouchEnabledLayerColor *layer = dynamic_cast<HTouchEnabledLayerColor *>(m_pTutorialNode);
//        if (layer) {
//            if (show) layer->show();
//            else {
////                layer->hide();
//                layer->removeFromParent();
//                m_pTutorialNode = NULL;
//            }
//        }
    }
}

void HRootLayer::AddJSCCBNode(const char *pCCBFileName, cocos2d::CCNode *node, bool originSize)
{
//    HFileUtils::resetInUI(true);
    PHSCREENDATA pData = NULL;
    std::string filename = getUILayout(pCCBFileName, &pData);
//    HFileUtils::resetInUI(false);
    
    m_fScaleX = 1.0f;
    m_fScaleY = 1.0f;
    if (node != NULL) {
        if (originSize) {
            node->setAnchorPoint(CCPointZero);
            node->setPosition(CCPointZero);
            setContentSize(node->getContentSize());
//            updateAndAdjust(node, 1, 1);
            addChild(node);
        } else {
            node->setAnchorPoint(CCPointMake(0.5f, 0.5f));
            node->setPosition(CCPointMake((getContentSize().width - node->getContentSize().width) / 2, (getContentSize().height - node->getContentSize().height) / 2));
            if (pData) {
                if (m_sbRatioOfEquality) {
//                    float scale = (pData->scaleX < pData->scaleY) ? pData->scaleX : pData->scaleY;
//                    m_fScaleX = m_fScaleY = scale;
//                    node->setScale(scale);
//                    updateAndAdjust(node, scale, scale);
                } else {
//                    m_fScaleX = pData->scaleX;
//                    m_fScaleY = pData->scaleY;
//                    node->setScaleX(pData->scaleX);
//                    node->setScaleY(pData->scaleY);
//                    updateAndAdjust(node, pData->scaleX, pData->scaleY);
                }
            } else {
//                updateAndAdjust(node, 1, 1);
            }
            addChild(node);
        }
        updateAndAdjust(node);
    }
}

CCNode *HRootLayer::readNodeGraphFromFile(const char* pCCBFileName, bool originalSize)
{
   
    CCNodeLoaderLibrary *library = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader reader(library);
    
//    HFileUtils::resetInUI(true);
    PHSCREENDATA pData = NULL;
    std::string filename = getUILayout(pCCBFileName, &pData);
    CCNode *node = reader.readNodeGraphFromFile(filename.c_str(), this, AppDelegate::getInstance()->getGameManager()->getScreenSize());
//    HFileUtils::resetInUI(false);
    
    setCCBAnimationManager(reader.getAnimationManager());
    
    m_fScaleX = 1.0f;
    m_fScaleY = 1.0f;
    if (node != NULL) {
        if (originalSize) {
            node->setAnchorPoint(CCPointZero);
            node->setPosition(CCPointZero);
            setContentSize(node->getContentSize());
//            updateAndAdjust(node, 1, 1);
            addChild(node);
        } else {
            node->setAnchorPoint(CCPointMake(0.5f, 0.5f));
            node->setPosition(CCPointMake((getContentSize().width - node->getContentSize().width) / 2, (getContentSize().height - node->getContentSize().height) / 2));
            if (pData) {
                if (m_sbRatioOfEquality) {
//                    float scale = (pData->scaleX < pData->scaleY) ? pData->scaleX : pData->scaleY;
//                    m_fScaleX = m_fScaleY = scale;
//                    node->setScale(scale);
//                    updateAndAdjust(node, scale, scale);
                } else if (m_sbAdjustForDifferentScreent) {
                    node->setAnchorPoint(CCPointZero);
                    node->setPosition(CCPointZero);
                    
//                    float scale = (pData->scaleX < pData->scaleY) ? pData->scaleX : pData->scaleY;
//                    m_fScaleX = m_fScaleY = scale;
//                    node->setScale(scale);
//                    updateAndAdjust(node, scale, scale);                    
                } else {
//                    m_fScaleX = pData->scaleX;
//                    m_fScaleY = pData->scaleY;
//                    node->setScaleX(pData->scaleX);
//                    node->setScaleY(pData->scaleY);
//                    updateAndAdjust(node, pData->scaleX, pData->scaleY);
                }
            } else {
//                updateAndAdjust(node, 1, 1);
            }
            addChild(node);
        }
        node->setScaleX(m_fScaleX);
        node->setScaleY(m_fScaleY);
        updateAndAdjust(node);
    }
    
    if (m_pViewPage) {
        m_pViewPage->create();
    }
    if (m_pTutorialNode) {
        m_pTutorialNode->updatePriority(m_pTutorialNode);
//        HTouchEnabledLayerColor *layer = dynamic_cast<HTouchEnabledLayerColor *>(m_pTutorialNode);
//        if (layer) layer->updatePriority(layer);
    }
    m_pCCbNode = node;
    CC_SAFE_RETAIN(m_pCCbNode);
    
    onShowEditbox(false);
    return node;
}

void HRootLayer::adjustPostionAndScale(CCNode* node, float scaleX, float scaleY) {
    
    for (int i = 0; i < m_pIgnoreNodeArr->count(); i ++) {
        CCNode* node = dynamic_cast<CCNode*>(m_pIgnoreNodeArr->objectAtIndex(i));
        if (node) {
            node->setScaleX(scaleX);
            node->setScaleY(scaleY);
        }
    }
    
    CCArray *children = node->getChildren();
    if (children) {
        for (int i = children->count() - 1; i >= 0; --i) {
            CCNode *child = (CCNode *)children->objectAtIndex(i);
            if (!m_pIgnoreNodeArr->containsObject(child)) {
                
                CCPoint pos = child->getPosition();
                child->setPosition(ccp(pos.x * scaleX, pos.y * scaleY));
                
            }
        }
    }

}

SEL_MenuHandler HRootLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}

SEL_CCControlHandler HRootLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    SEL_CCControlHandler pRet = NULL;
    if (pSelectorName) {
        if (0 == strcmp(pSelectorName, "onBackClick:")) {
            pRet = cccontrol_selector(HRootLayer::onBackClick);
        } else if (0 == strcmp(pSelectorName, "onCloseClick:")) {
            pRet = cccontrol_selector(HRootLayer::onCloseClick);
        }
    }
    return pRet;
}

bool HRootLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    if (pMemberVariableName) {
        if (0 == strcmp(pMemberVariableName, "label_title")) {
            m_pLabelTitle = (CCLabelTTF *)pNode;
        } else if (0 == strcmp(pMemberVariableName, "btn_back"))  {
            m_pBtnBack = (CCControlButton *)pNode;
             m_pBtnBack->setTouchPriority(m_iBaseTouchPriority-200);
        } else if (0 == strcmp(pMemberVariableName, "btn_close"))  {
            m_pBtnClose = (CCControlButton *)pNode;
            m_pBtnClose->setTouchPriority(m_iBaseTouchPriority-200);
        } else if (0 == strcmp(pMemberVariableName, "tutorial_layer")) {
            m_pTutorialNode = (HTouchEnabledLayerColor *)pNode;
        }
    }
    return true;
}

//void HRootLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader) {
//    updateLocalStrings();
//}

void HRootLayer::setTitle(const char *pTitle) {
    if (m_pLabelTitle) {
        m_pLabelTitle->setString(pTitle);
    }
}

void HRootLayer::onBackClick(CCObject*, CCControlEvent) {
    dismissRootLayer();
}

void HRootLayer::onCloseClick(CCObject*, CCControlEvent) {
    dismissAllLayers();
}

void HRootLayer::presentRootLayer(bool inQueue, bool inUI) {
    if (!inUI) {
        setDisableAnimInOut(true);
    }
    HUILayer *uiLayer = inUI ? AppDelegate::getInstance()->getGameScene()->getUILayer() : AppDelegate::getInstance()->getGameScene()->getGameDecorationLayer();
//    CCDirector::sharedDirector()->getRunningScene();
    uiLayer->presentRootLayer(this, inQueue);
    
    if (m_pViewPage) {
        m_pViewPage->show();
    }
    
    if (m_sbAdjustForDifferentScreent && m_pCCbNode) {
        adjustPostionAndScale(m_pCCbNode, 1, 1);
    }
}

void HRootLayer::dismissRootLayer(bool inUI) {
    if (m_pViewPage) {
        m_pViewPage->hide();
    }
    
    if (!inUI) {
        setDisableAnimInOut(true);
    }
    HUILayer *uiLayer = inUI ? AppDelegate::getInstance()->getGameScene()->getUILayer() : AppDelegate::getInstance()->getGameScene()->getGameDecorationLayer();
    uiLayer->dismissRootLayer(this);
}

void HRootLayer::dismissAllLayers(bool inUI) {
    HUILayer *uiLayer = inUI ? AppDelegate::getInstance()->getGameScene()->getUILayer() : AppDelegate::getInstance()->getGameScene()->getGameDecorationLayer();
    uiLayer->dismissAllRootLayers();
}

void HRootLayer::updateAndAdjust(CCNode *node) {
    node->setScaleX(m_fScaleX);
    node->setScaleY(m_fScaleY);
    updateAndAdjust(node, m_fScaleX, m_fScaleY);
}

void HRootLayer::updateAndAdjust(CCNode *node, float scaleX, float scaleY) {
    CCArray *children = node->getChildren();
    if (children) {
        for (int i = children->count() - 1; i >= 0; --i) {
            CCNode *child = (CCNode *)children->objectAtIndex(i);
            if (dynamic_cast<CCLabelTTF *>(child)) {
                CCLabelTTF *label = (CCLabelTTF *)child;
                label->setString(HLocalizedString(label->getString()));
            } else if (dynamic_cast<CCEditBox *>(child)) {
//                CCEditBox *editBox = (CCEditBox *)child;
//                editBox->setScaleX(scaleX);
//                editBox->setScaleY(scaleY);
            } else if (dynamic_cast<CCControlButton *>(child)) {
                CCControlButton *button = (CCControlButton *)child;
                CCString *title = button->getTitleForState(CCControlStateNormal);
                button->setTitleForState(CCString::create(HLocalizedString(title->getCString())), CCControlStateNormal);
            } else if (dynamic_cast<CCScrollView *>(child)) {
//                CCScrollView *scrollview = (CCScrollView *)child;
//                scrollview->setScaleX(scaleX);
//                scrollview->setScaleY(scaleY);
                updateAndAdjust(child, scaleX, scaleY);
            } else {
                updateAndAdjust(child, scaleX, scaleY);
            }
        }
    }
}

void HRootLayer::relayoutAsHorizontal(CCArray *nodes, CCPoint basePos, int interval) {
    for (int i = 0; i < nodes->count(); ++i) {
        CCNode *node = (CCNode *)nodes->objectAtIndex(i);
        node->setPosition(CCPointMake(basePos.x + node->getAnchorPoint().x * node->getContentSize().width * node->getScaleX(), basePos.y));
        basePos.x += node->getContentSize().width * node->getScaleX() + interval;
    }
}

void HRootLayer::relayoutAsVertical(CCArray *nodes, CCPoint basePos, int interval) {
    for (int i = 0; i < nodes->count(); ++i) {
        CCNode *node = (CCNode *)nodes->objectAtIndex(i);
        node->setPosition(CCPointMake(basePos.x, basePos.y + node->getAnchorPoint().y * node->getContentSize().height));
        basePos.y += node->getContentSize().height + interval;
    }
}

CCObject *HRootLayer::onOpenKeyboard(int command, CCEditBox *editbox) {
    // modify by zg
//    if (editbox) editbox->openKeyboard();
    if (editbox) {
#ifndef ANDROID
        editbox->touchDownAction(editbox, 0);
#endif
    }
    return NULL;
}

void HRootLayer::registerEditbox(CCEditBox *editBox) {
    m_pEditBoxList->addObject(editBox);
#ifdef HOS_APPLE
#else
    HEditBox *heditbox = dynamic_cast<HEditBox *>(editBox);
    if (heditbox) {
        if (!m_pViewPage) {
            m_pViewPage = new HViewPage;
        }
        m_pViewPage->registerView(heditbox);
    }
#endif
}

void HRootLayer::editBoxEditingDidEnd(CCEditBox* editBox) {
    int count = m_pEditBoxList->count();
    for (int i = 0; i < count; ++i) {
        if (editBox == m_pEditBoxList->objectAtIndex(i)) {
            do {
                ++i;
                if (i < count) {
                    CCEditBox *eb = (CCEditBox *)m_pEditBoxList->objectAtIndex(i);
                    if (eb->isVisible()) {
                        HTimerManager::getInstance()->asyncProcess(HInvocation::create(this, hinvocation_selector(HRootLayer::onOpenKeyboard), 0, eb));
                        break;
                    }
                } else {
                    //delete by zg
//                    editBox->closeKeyboard();
                    break;
                }
            } while (true);
            break;
        }
    }
//    if (editBox == m_pEditUsername) {
//        HTimerManager::getInstance()->asyncProcess(HInvocation::create(this, hinvocation_selector(HRootLayer::onOpenKeyboard), 0, m_pEditPassword));
////        m_pEditPassword->openKeyboard();
//    }
}

void HRootLayer::editBoxReturn(CCEditBox* editBox) {
    
}

void HRootLayer::onShowEditbox(bool show) {
    int count = m_pEditBoxList->count();
    for (int i = 0; i < count; ++i) {
        CCNode *editBox = (CCNode *)m_pEditBoxList->objectAtIndex(i);
        if (!show) {
            HEditBox *heditbox = dynamic_cast<HEditBox *>(editBox);
            if (heditbox) heditbox->bakVisible();
            editBox->setVisible(show);
        } else {
            HEditBox *heditbox = dynamic_cast<HEditBox *>(editBox);
            if (heditbox) {
                editBox->setVisible(heditbox->getBakVisible());
            } else {
                editBox->setVisible(show);
            }
        }
    }
    if (m_pViewPage) {
        if (show) m_pViewPage->show();
        else m_pViewPage->hide();
    }
}

void HRootLayer::onSearchPort()
{
    
}

void HRootLayer::onCloseSearch()
{
    
}

void HRootLayer::onDispatchFleet(int index)
{
    
}

void HRootLayer::onDispatchFleetCancel(int index)
{
    
}

void HRootLayer::setParentVisible(bool isVisible)
{
    this->setVisible(isVisible);
    HRootLayer* parent;
    parent = (HRootLayer*)this->getParent();
    while ((parent != NULL)&&(parent->getParent() != NULL)) {
        std::string name = parent->getClass();
        parent->setVisible(isVisible);
        parent = (HRootLayer*)parent->getParent();
    } 
}

void HRootLayer::onCountTick(HCountDown *sender, int seconds)
{
    
}

const char* HRootLayer::secondsToString(int seconds)
{
    int s = seconds % 60;
    seconds /= 60;
    int m = seconds % 60;
    seconds /= 60;
    if (seconds > 24) {
        int day = seconds / 24;
        int hour = seconds % 24;
        return CCString::createWithFormat(HLocalizedString("ui_time_day_tip"),day,hour)->getCString();
    }
    return CCString::createWithFormat("%02d:%02d:%02d", seconds, m, s)->getCString();
}

const char* HRootLayer::secondsToStringNoDay(int seconds)
{
    int s = seconds % 60;
    seconds /= 60;
    int m = seconds % 60;
    seconds /= 60;
    return CCString::createWithFormat("%02d:%02d", m, s)->getCString();
}

HNAMESPACE_END
