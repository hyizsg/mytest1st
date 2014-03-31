//
//  HTableViewCell.cpp
//  BattleShip
//
//  Created by huangwei on 10/26/12.
//
//


#include "../../headers.h"

CCDictionary* HCellHelper::s_cellCache = new CCDictionary;
HSINGLETON_OBJECT_IMP(HCellHelper);

HTableViewCell::HTableViewCell(const char*fileName):CCTableViewCell()//  HRootLayer(),
, m_iBaseTouchPriority(0)
{
    readNodeGraphFromFile(fileName);
}

HTableViewCell::HTableViewCell():CCTableViewCell()
, m_iBaseTouchPriority(0)
{

}


HTableViewCell *HTableViewCell::create(const char*fileName) {
    HTableViewCell *cell = new HTableViewCell(fileName);
//    cell->autorelease();
    CC_AUTO_RELEASE(cell);
    return cell;
}

HTableViewCell *HTableViewCell::create() {
    HTableViewCell *cell = new HTableViewCell();
//    cell->autorelease();
    CC_AUTO_RELEASE(cell);
    return cell;
}

void HTableViewCell::setBaseTouchPriority(int var)
{
    if (m_iBaseTouchPriority != var) {
        m_iBaseTouchPriority = var;
        
        updatePriorityTouchLayer(this);

    }
}

int HTableViewCell::getBaseTouchPriority()
{
    return m_iBaseTouchPriority;
}

HTableViewCell::~HTableViewCell()
{
    removeAllChildren();
}

CCSize HTableViewCell::GetCellSize(const char*fileName)
{
    CCSize cellSize;
    HTableViewCell *cell = new HTableViewCell(fileName);
    cellSize = cell->CellSize();
    cell->release();
    return cellSize;
}

void HTableViewCell::updateAndAdjust(CCNode *node, float scaleX, float scaleY) {
    CCArray *children = node->getChildren();
    if (children) {
        for (int i = children->count() - 1; i >= 0; --i) {
            CCNode *child = (CCNode *)children->objectAtIndex(i);
            if (dynamic_cast<CCLabelTTF *>(child)) {
                CCLabelTTF *label = (CCLabelTTF *)child;
                label->setString(HLocalizedString(label->getString()));
            } else if (dynamic_cast<CCEditBox *>(child)) {
                CCEditBox *editBox = (CCEditBox *)child;
                editBox->setScaleX(scaleX);
                editBox->setScaleY(scaleY);
            } else if (dynamic_cast<CCControlButton *>(child)) {
                CCControlButton *button = (CCControlButton *)child;
                CCString *title = button->getTitleForState(CCControlStateNormal);
                button->setTitleForState(CCString::create(HLocalizedString(title->getCString())), CCControlStateNormal);
            }else if (dynamic_cast<CCSprite *>(child)) {
                CCSprite *sprite = (CCSprite *)child;
                if (noHDResource()) {
                    sprite->setScaleX(sprite->getScaleX() * 2);
                    sprite->setScaleY(sprite->getScaleY() * 2);
                }
            } else {
                updateAndAdjust(child, scaleX, scaleY);
            }
        }
    }
}

bool HTableViewCell::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {

    return true;
}

SEL_MenuHandler HTableViewCell::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}

SEL_CCControlHandler HTableViewCell::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}


CCSize HTableViewCell::CellSize()
{
    return m_cellSize;
}

void HTableViewCell::AddJSCCBNode(const char *ccbfile, cocos2d::CCNode *node)
{
    // delete by zg
//    HFileUtils::resetInUI(true);
    PHSCREENDATA pData = NULL;
    std::string filename = getUILayout(ccbfile, &pData);
//    HFileUtils::resetInUI(false);

    CCLayer* layer = dynamic_cast<CCLayer *>(node);
    layer->setAnchorPoint(CCPointZero);
    m_cellSize =  layer->getContentSize();
    setContentSize(m_cellSize);
    m_pRootChild = node;
    
    if (node != NULL) {
        this->setAnchorPoint(CCPointZero);
        this->addChild(node);
//        if (pData) {
//            if (HRootLayer::m_sbRatioOfEquality) {
//                float scale = (pData->scaleX < pData->scaleY) ? pData->scaleX : pData->scaleY;
//                node->setScale(scale);
//                updateAndAdjust(node, scale, scale);
//            } else {
//                node->setScaleX(pData->scaleX);
//                node->setScaleY(pData->scaleY);
//                updateAndAdjust(node, pData->scaleX, pData->scaleY);
//            }
//        } else {
//            updateAndAdjust(node, 1, 1);
//        }
    }
}

void HTableViewCell::readNodeGraphFromFile(const char *pFileName)
{
    //    readNodeGraphFromFile("TableViewTestCell_iphone.ccbi");
//    CCLOG("HTableViewCell::readNodeGraphFromFile: %s", pFileName);
    CC_PROFILER_START("HTableViewCell::readNodeGraphFromFile");
    CCNodeLoaderLibrary *library = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    //    library->registerCCNodeLoader("HLoginMainWindow", HLoginMainWindow::loader());
    CCBReader reader(library);
    
    // delete by zg
//    HFileUtils::resetInUI(true);
    PHSCREENDATA pData = NULL;
    std::string filename = getUILayout(pFileName, &pData);
    CCNode *node = reader.readNodeGraphFromFile(filename.c_str(), this);
//    HFileUtils::resetInUI(false);
    
    CCLayer* layer = dynamic_cast<CCLayer *>(node);
    layer->setAnchorPoint(CCPointZero);
    m_cellSize =  layer->getContentSize();
    setContentSize(m_cellSize);
    m_pRootChild = node;
    
    if (node != NULL) {
        this->setAnchorPoint(CCPointZero);
        this->addChild(node);
//        if (pData) {
//            if (HRootLayer::m_sbRatioOfEquality) {
//                float scale = (pData->scaleX < pData->scaleY) ? pData->scaleX : pData->scaleY;
//                node->setScale(scale);
//                updateAndAdjust(node, scale, scale);
//            } else {
//                node->setScaleX(pData->scaleX);
//                node->setScaleY(pData->scaleY);
//                updateAndAdjust(node, pData->scaleX, pData->scaleY);
//            }
//        } else {
//            updateAndAdjust(node, 1, 1);
//        }
    }
    CC_PROFILER_STOP("HTableViewCell::readNodeGraphFromFile");
//    CC_PROFILER_DISPLAY("HTableViewCell::readNodeGraphFromFile");
}

void HTableViewCell::ReadCell(HTableViewCell*oldCell)
{
    CCNode *node = (CCNode*)oldCell->getChildren()->objectAtIndex(0);

    CCLayer* layer = dynamic_cast<CCLayer *>(node);
    m_cellSize =  layer->getContentSize();
    if (node != NULL) {
        this->addChild(node);
        this->updateAndAdjust(node, oldCell->getScaleX(),oldCell->getScaleY());
    }
    
    {
        this->setScaleX(oldCell->getScaleX());
        this->setScaleY(oldCell->getScaleY());
    }
}

CCSprite *HTableViewCell::cloneSprite(CCSprite *pPrototype) {
    CCSprite *sprite = HRichSprite::createWithTexture(pPrototype->getTexture(), pPrototype->getTextureRect());
    sprite->setAnchorPoint(pPrototype->getAnchorPoint());
    sprite->setPosition(pPrototype->getPosition());
    sprite->setScaleX(pPrototype->getScaleX());
    sprite->setScaleY(pPrototype->getScaleY());
    sprite->setRotation(pPrototype->getRotation());
    return sprite;
}

CCLabelTTF *HTableViewCell::cloneLabelTTF(CCLabelTTF *pPrototype) {
    CCLabelTTF *label = CCLabelTTF::create();
    label->setFontName(pPrototype->getFontName());
    label->setFontSize(pPrototype->getFontSize());
    label->setColor(pPrototype->getColor());
    label->setHorizontalAlignment(pPrototype->getHorizontalAlignment());
    label->setVerticalAlignment(pPrototype->getVerticalAlignment());
    
    label->setAnchorPoint(pPrototype->getAnchorPoint());
    label->setPosition(pPrototype->getPosition());
    label->setScaleX(pPrototype->getScaleX());
    label->setScaleY(pPrototype->getScaleY());
    label->setRotation(pPrototype->getRotation());
    return label;
}

void HTableViewCell::clear()
{
    setVisible(true);
    setOpacity(255);
    setBlack(false);
    m_iBaseTouchPriority = 0;
    setPosition(0, 0);
    setAnchorPoint(CCPointZero);
    setScale(1);
    setTag(-1);
    getRootChild()->setScale(1);
    getRootChild()->setPosition(CCPointZero);
}

void HTableViewCell::updatePriorityTouchLayer(CCNode *node) {
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

HCellHelper::HCellHelper()
{
    
}

HCellHelper::~HCellHelper()
{
    
}


