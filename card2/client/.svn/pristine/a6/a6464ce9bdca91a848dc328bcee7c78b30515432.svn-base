//
//  HRichButton.cpp
//  card
//
//  Created by zhou gang on 13-5-27.
//
//

#define PROPERTY_STROKECOLOR "Stroke Color"
#define PROPERTY_STROKESIZE     "Stroke Size"

#define PROPERTY_SHADOWCOLOR    "Shadow Color"
#define PROPERTY_SHADOWOFFSET   "Shadow Offset"

#include "../../headers.h"

HCardEditBox::HCardEditBox()
: m_bVisibleBak(true)
{
    m_bTouchEnabled = true;
}

bool HCardEditBox::initWithSizeAndBackgroundSprite(const CCSize& size, CCScale9Sprite* pNormal9SpriteBg)
{
    CCEditBox::initWithSizeAndBackgroundSprite(size, pNormal9SpriteBg);
    CCEditBox::setVisible(false);
    
    return true;
}

void HCardEditBox::setPosition(const cocos2d::CCPoint &pos)
{
    CCEditBox::setPosition(pos);
}

void HCardEditBox::setVisible(bool bVisible)
{
    CCEditBox::setVisible(bVisible);
    m_bVisibleBak = bVisible;
}

void HCardEditBox::onEnter()
{    
    CCEditBox::onEnter();
}

void HCardEditBox::onExit()
{    
    CCEditBox::onExit();
}

void HCardEditBox::onEnterTransitionDidFinish()
{
    CCEditBox::setVisible(m_bVisibleBak);
    CCEditBox::onEnterTransitionDidFinish();
}

void HCardEditBox::onExitTransitionDidStart()
{
    CCEditBox::onExitTransitionDidStart();
    m_bVisibleBak = isVisible();
    CCEditBox::setVisible(false);
}


HCardEditBox * HCardEditBoxLoader::createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
    HCardEditBox *editBox = new HCardEditBox();
    editBox->setZoomOnTouchDown(false);
    //        editBox->autorelease();
    CC_AUTO_RELEASE(editBox);
    editBox->initWithSizeAndBackgroundSprite(CCSize(280, 32), CCScale9Sprite::createWithSpriteFrame(HSourceCache::getInstance()->spriteFrameWithName("normal_alpha_hd.png")));
    return editBox;
}

void HCardEditBoxLoader::onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCSize pSize, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
        ((HCardEditBox *)pNode)->setPreferredSize(pSize);
    } else {
        CCEditBoxLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, pCCBReader);
    }
}

///****************************************************************************************

bool HRichButton::init()
{
    return this->initWithLabelAndBackgroundSprite(HRichLabelTTF::create(), CCScale9Sprite::create());
}

bool HRichButton::initWithTitleAndFontNameAndFontSize(string title, const char * fontName, float fontSize)
{
    HRichLabelTTF *label = HRichLabelTTF::create(title.c_str(), fontName, fontSize);
    return initWithLabelAndBackgroundSprite(label, CCScale9Sprite::create());
}

bool HRichButton::initWithBackgroundSprite(CCScale9Sprite* sprite)
{
    HRichLabelTTF *label = HRichLabelTTF::create();//
    return initWithLabelAndBackgroundSprite(label, sprite);
}

void HRichButton::setTitleTTFForState(const char * fntFile, CCControlState state)
{
    CCString * title = this->getTitleForState(state);
    if (!title)
    {
        title = CCString::create("");
    }
    this->setTitleLabelForState(HRichLabelTTF::create(title->getCString(), fntFile, 12), state);
}

void HRichButton::setBackgroundSpriteFrameForState(CCSpriteFrame * spriteFrame, CCControlState state)
{
    HRichSprite* sprite = HRichSprite::createWithSpriteFrame(spriteFrame);
    this->setBackgroundSpriteForState(sprite, state);
}

void HRichButton::setBackgroundSpriteForState(CCSprite* sprite, CCControlState state)
{
    CCSize oldPreferredSize = m_preferredSize;
    
    CCNode* previousBackgroundSprite = (CCNode*)getBackgroundSpriteDispatchTable()->objectForKey(state);
    if (previousBackgroundSprite)
    {
        removeChild(previousBackgroundSprite, true);
        getBackgroundSpriteDispatchTable()->removeObjectForKey(state);
    }
    
    getBackgroundSpriteDispatchTable()->setObject(sprite, state);
    sprite->setVisible(false);
    sprite->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(sprite);
    
    if (this->m_preferredSize.width != 0 || this->m_preferredSize.height != 0)
    {
        sprite->setScaleX(m_preferredSize.width / sprite->getContentSize().width);
        sprite->setScaleY(m_preferredSize.height / sprite->getContentSize().height);
    }
    
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

HRichLabelTTF* HRichButton::getRichLabel()
{
    return dynamic_cast<HRichLabelTTF*>(getTitleLabel());
}

bool HRichButton::isInScrollView()
{
    CCNode* parent = getParent();
    CCScrollView* scroll = NULL;
    
    while (parent)
    {
        scroll = dynamic_cast<CCScrollView*>(parent);
        if (scroll) {
            break;
        }else{
            parent = parent->getParent();
        }
    }
    
    return scroll && scroll->isTouchEnabled();
}

void HRichButton::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isInScrollView()) {
        
        m_isPushed = false;
        setHighlighted(false);
        
        CCPoint bp = pTouch->getStartLocation();
        CCPoint ep = pTouch->getLocation();
        
        float distance = bp.getDistance(ep);
        CCLOG("%f", distance);
        
        if (bp.getDistance(ep) < 15.f * CC_CONTENT_SCALE_FACTOR())
        {
            if (isTouchInside(pTouch))
            {
                sendActionsForControlEvents(CCControlEventTouchUpInside);
            }
            else
            {
                sendActionsForControlEvents(CCControlEventTouchUpOutside);
            }
        }
    }else{
        CCControlButton::ccTouchEnded(pTouch, pEvent);
    }
}

void HRichButton::needsLayout()
{
    if (!m_bParentInited) {
        return;
    }
    
    CCNode* titleLabel = getTitleLabel();
    
    // Hide the background and the label
    if (titleLabel != NULL) {
        titleLabel->setVisible(false);
    }
    
    CCNode* backgroundSprite = getBackgroundSprite();
    
    if (backgroundSprite) {
        backgroundSprite->setVisible(false);
    }
    // Update anchor of all labels
    this->setLabelAnchorPoint(this->m_labelAnchorPoint);
    
    // Update the label to match with the current state
    CC_SAFE_RELEASE(m_currentTitle);
    m_currentTitle = getTitleForState(m_eState);
    CC_SAFE_RETAIN(m_currentTitle);
    
    m_currentTitleColor = getTitleColorForState(m_eState);
    
    this->setTitleLabel(getTitleLabelForState(m_eState));
    
    
    titleLabel = getTitleLabel();
    
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(titleLabel);
    if (label && m_currentTitle)
    {
        label->setString(m_currentTitle->getCString());
    }
    
    CCRGBAProtocol* rgbaLabel = dynamic_cast<CCRGBAProtocol*>(titleLabel);
    if (rgbaLabel)
    {
        rgbaLabel->setColor(m_currentTitleColor);
    }
    if (titleLabel != NULL)
    {
        titleLabel->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
    }
    
    // Update the background sprite
    this->setBackgroundSprite(this->getBackgroundSpriteForState(m_eState));
    backgroundSprite = getBackgroundSprite();
    
    if (backgroundSprite != NULL)
    {
        backgroundSprite->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
    }
    
    // Get the title label size
    CCSize titleLabelSize;
    if (titleLabel != NULL)
    {
        titleLabelSize = titleLabel->boundingBox().size;
    }
    
    // delete by zg
    // remove ccscale9sprite suported
//    // Adjust the background image if necessary
//    if (m_doesAdjustBackgroundImage)
//    {
//        // Add the margins
//        if (m_backgroundSprite != NULL)
//        {
//            m_backgroundSprite->setContentSize(CCSizeMake(titleLabelSize.width + m_marginH * 2, titleLabelSize.height + m_marginV * 2));
//        }
//    }
//    else
//    {
//        //TODO: should this also have margins if one of the preferred sizes is relaxed?
//        if (m_backgroundSprite != NULL)
//        {
//            CCSize preferredSize = m_backgroundSprite->getPreferredSize();
//            if (preferredSize.width <= 0)
//            {
//                preferredSize.width = titleLabelSize.width;
//            }
//            if (preferredSize.height <= 0)
//            {
//                preferredSize.height = titleLabelSize.height;
//            }
//            
//            m_backgroundSprite->setContentSize(preferredSize);
//        }
//    }
//
    
    // Set the content size
    CCRect rectTitle;
    if (titleLabel != NULL)
    {
        // modify by zg, ingore effect of label size
//        rectTitle = titleLabel->boundingBox();
    }
    CCRect rectBackground;
    if (backgroundSprite != NULL)
    {
        rectBackground = backgroundSprite->boundingBox();
    }
    
    CCRect maxRect = CCControlUtils::CCRectUnion(rectTitle, rectBackground);
    setContentSize(CCSizeMake(maxRect.size.width, maxRect.size.height));
    
    if (titleLabel != NULL)
    {
        titleLabel->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
        // Make visible the background and the label
        titleLabel->setVisible(true);
    }
    
    if (backgroundSprite != NULL)
    {
        backgroundSprite->setScaleX(m_preferredSize.width / backgroundSprite->getContentSize().width);
        backgroundSprite->setScaleY(m_preferredSize.height / backgroundSprite->getContentSize().height);
        backgroundSprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
        backgroundSprite->setVisible(true);
    }   
}

///--

void HRichButtonLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader)
{
    HRichLabelTTF* label = ((HRichButton *)pNode)->getRichLabel();
    
    if(strcmp(pPropertyName, PROPERTY_STROKECOLOR) == 0) {
        ccColor4B color = cc4FromString(pString);
        label->setStroke(ccc3(color.r, color.g, color.g), label->getStrokeSize(), color.a);
    } else if(strcmp(pPropertyName, PROPERTY_STROKESIZE) == 0) {
        HFontManager::getInstance()->replaceFont(pNode);
        label->setStroke(label->getStrokeColor(), atof(pString), label->getStrokeOpacity());
    } else if(strcmp(pPropertyName, PROPERTY_SHADOWCOLOR) == 0) {
        ccColor4B color = cc4FromString(pString);
        label->setShadow(ccc3(color.r, color.g, color.g), label->getShadowOffset(), color.a);
    } else if(strcmp(pPropertyName, PROPERTY_SHADOWOFFSET) == 0) {
        HFontManager::getInstance()->replaceFont(pNode);
        label->setShadow(label->getShadowColor(), ccpFromString(pString), label->getShadowOpacity());
    }else {
        CCControlButtonLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
    }
}


//****************************************************************************************************************

#define PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL "backgroundSpriteFrame|1"
#define PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED "backgroundSpriteFrame|2"
#define PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED "backgroundSpriteFrame|3"

//void HControlButtonLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {
//    if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL) == 0) {
//        if(pCCSpriteFrame != NULL) {
//            ((CCControlButton *)pNode)->setBackgroundSpriteFrameForState(pCCSpriteFrame, CCControlStateNormal);
//            bool old = CCControlButton::m_sNoZoomResetHightlightBg;
//            CCControlButton::m_sNoZoomResetHightlightBg = true;
//            ((CCControlButton *)pNode)->setBackgroundSpriteFrameForState(pCCSpriteFrame, CCControlStateHighlighted);
//            CCControlButton::m_sNoZoomResetHightlightBg = old;
//        }
//    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED) == 0) {
//        if(pCCSpriteFrame != NULL) {
//            static const CCSpriteFrame* hitFrame = _M("ccbButtonHilite.png");
//            if (pCCSpriteFrame == hitFrame) {
//                ((CCControlButton *)pNode)->setBackgroundSpriteFrameForState(pCCSpriteFrame, CCControlStateHighlighted);
//            }else{
//                return;
//            }
//        }
//    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED) == 0) {
//        if(pCCSpriteFrame != NULL) {
//            ((CCControlButton *)pNode)->setBackgroundSpriteFrameForState(pCCSpriteFrame, CCControlStateDisabled);
//        }
//    } else {
//        CCControlButtonLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
//    }
//}



HControlButton* HControlButton::create()
{    
    HControlButton *pControlButton = new HControlButton();
    if (pControlButton && pControlButton->init())
    {
//        pControlButton->autorelease();
        CC_AUTO_RELEASE(pControlButton);
        return pControlButton;
    }
    CC_SAFE_DELETE(pControlButton);
    return NULL;
    
}

//#define PROPERTY_TITLE_NORMAL "title|1"
//#define PROPERTY_TITLE_HIGHLIGHTED "title|2"
//#define PROPERTY_TITLE_DISABLED "title|3"
//#define PROPERTY_TITLECOLOR_NORMAL "titleColor|1"
//#define PROPERTY_TITLECOLOR_HIGHLIGHTED "titleColor|2"
//#define PROPERTY_TITLECOLOR_DISABLED "titleColor|3"
//#define PROPERTY_TITLETTF_NORMAL "titleTTF|1"
//#define PROPERTY_TITLETTF_HIGHLIGHTED "titleTTF|2"
//#define PROPERTY_TITLETTF_DISABLED "titleTTF|3"
//#define PROPERTY_TITLETTFSIZE_NORMAL "titleTTFSize|1"
//#define PROPERTY_TITLETTFSIZE_HIGHLIGHTED "titleTTFSize|2"
//#define PROPERTY_TITLETTFSIZE_DISABLED "titleTTFSize|3"
//
//void HControlButtonLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader) {
//    if(strcmp(pPropertyName, PROPERTY_TITLE_NORMAL) == 0) {
//        ((CCControlButton *)pNode)->setTitleForState(CCString::create(pString), CCControlStateNormal);
//    } else if(strcmp(pPropertyName, PROPERTY_TITLE_HIGHLIGHTED) == 0) {
//        ((CCControlButton *)pNode)->setTitleForState(CCString::create(pString), CCControlStateHighlighted);
//    } else if(strcmp(pPropertyName, PROPERTY_TITLE_DISABLED) == 0) {
//        ((CCControlButton *)pNode)->setTitleForState(CCString::create(pString), CCControlStateDisabled);
//    } else {
//        CCControlLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
//    }
//}
//
//void HControlButtonLoader::onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * pCCBReader) {
//    if(strcmp(pPropertyName, PROPERTY_TITLETTF_NORMAL) == 0) {
//        ((CCControlButton *)pNode)->setTitleTTFForState(pFontTTF, CCControlStateNormal);
//    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_HIGHLIGHTED) == 0) {
//        ((CCControlButton *)pNode)->setTitleTTFForState(pFontTTF, CCControlStateHighlighted);
//    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_DISABLED) == 0) {
//        ((CCControlButton *)pNode)->setTitleTTFForState(pFontTTF, CCControlStateDisabled);
//    } else {
//        CCControlLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, pCCBReader);
//    }
//}

void HControlButtonLoader::parseProperties(cocos2d::CCNode *pNode, cocos2d::CCNode *pParent, cocos2d::extension::CCBReader *pCCBReader)
{
    HControlButton *btn = (HControlButton*)pNode;
    btn->setParentInited(false);
    CCControlButtonLoader::parseProperties(pNode, pParent, pCCBReader);
    btn->setParentInited(true);
    btn->needsLayout();
}
