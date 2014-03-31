//
//  HRichLabelTTF2.cpp
//  card
//
//  Created by zhou gang on 13-5-24.
//
//

#include "../../headers.h"

#define PROPERTY_STROKECOLOR "Stroke Color"
#define PROPERTY_STROKESIZE     "Stroke Size"

#define PROPERTY_SHADOWCOLOR    "Shadow Color"
#define PROPERTY_SHADOWOFFSET   "Shadow Offset"


HRichLabelTTF2::HRichLabelTTF2()
: HRichLabelTTF()
, m_bBlack(false)
{
    
}

HRichLabelTTF2::~HRichLabelTTF2()
{

}

HRichLabelTTF2* HRichLabelTTF2::create(const char *string, const char *fontName, float fontSize, ccColor3B color)
{
    HRichLabelTTF2* plabel = new HRichLabelTTF2();
    if(plabel && plabel->initWithString(string, fontName, fontSize))
    {
        plabel->setColor(color);
//        plabel->autorelease();
        CC_AUTO_RELEASE(plabel);
        return plabel;
    }
    else
    {
        delete plabel;
        plabel = NULL;
        return NULL;
    }
}


void HRichLabelTTF2::setBlack(bool var)
{
    if (m_bBlack != var) {
        m_bBlack = var;
        if (var) {
            m_intendedColor = getColor();
            GLubyte gray = m_intendedColor.r*0.299 + m_intendedColor.g*0.587 + m_intendedColor.b*0.114;
            setColor(ccc3(gray, gray, gray));
        }else{
            setColor(m_intendedColor);
        }
    }
}

bool HRichLabelTTF2::isBlack()
{
    return m_bBlack;
}

/// ---

void HRichLabelTTF2Loader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader)
{
    HRichLabelTTF2* label = ((HRichLabelTTF2 *)pNode);
    
    if(strcmp(pPropertyName, PROPERTY_STROKECOLOR) == 0) {
        ccColor4B color = cc4FromString(pString);
        label->setStroke(ccc3(color.r, color.g, color.g), label->getStrokeSize(), color.a);
    } else if(strcmp(pPropertyName, PROPERTY_STROKESIZE) == 0) {
        HFontManager::getInstance()->replaceFont(pNode);
        label->setStroke(label->getStrokeColor(), atof(pString), label->getStrokeOpacity());
    }else if(strcmp(pPropertyName, PROPERTY_SHADOWCOLOR) == 0) {
        ccColor4B color = cc4FromString(pString);
        label->setShadow(ccc3(color.r, color.g, color.g), label->getShadowOffset(), color.a);
    } else if(strcmp(pPropertyName, PROPERTY_SHADOWOFFSET) == 0) {
        HFontManager::getInstance()->replaceFont(pNode);
        label->setShadow(label->getShadowColor(), ccpFromString(pString), label->getShadowOpacity());
    } else {
        HRichLabelTTFLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
    }
}


void HRichLabelTTF2Loader::parseProperties(cocos2d::CCNode *pNode, cocos2d::CCNode *pParent, cocos2d::extension::CCBReader *pCCBReader)
{
    HRichLabelTTFLoader::parseProperties(pNode, pParent, pCCBReader);
    ((CCLabelTTF *)pNode)->setString(m_str.c_str());
}

#define PROPERTY_STRING "string"

void HRichLabelTTF2Loader::onHandlePropTypeText(cocos2d::CCNode *pNode, cocos2d::CCNode *pParent, const char *pPropertyName, const char *pText, cocos2d::extension::CCBReader *pCCBReader)
{
    if(strcmp(pPropertyName, PROPERTY_STRING) == 0) {
        //((CCLabelTTF *)pNode)->setString(pText);
        m_str = pText;
    } else {
        CCNodeLoader::onHandlePropTypeText(pNode, pParent, pPropertyName, pText, pCCBReader);
    }
}



