//
//  HRGBObject.cpp
//  card
//
//  Created by zhou gang on 13-7-3.
//
//

#include "../../headers.h"

HRGBObject::HRGBObject()
: m_cOpacity(255)
, m_tColor(ccWHITE)
, m_bIsOpacityModifyRGB(true)
{
    
}

HRGBObject::~HRGBObject()
{
    
}

//CRGBA protocol
void HRGBObject::setColor(const ccColor3B& color)
{
    m_tColor=color;
    setColorOnChildren(color, dynamic_cast<CCNode*>(this));
}

const ccColor3B& HRGBObject::getColor(void)
{
    return m_tColor;
}

void HRGBObject::setOpacity(GLubyte opacity)
{
    if (m_cOpacity != opacity) {
        m_cOpacity = opacity;
        setOpacityOnChildren(opacity, dynamic_cast<CCNode*>(this));
    }
}

GLubyte HRGBObject::getOpacity()
{
    return m_cOpacity;
}


void HRGBObject::setOpacityModifyRGB(bool bOpacityModifyRGB)
{
    m_bIsOpacityModifyRGB = bOpacityModifyRGB;

}

bool HRGBObject::isOpacityModifyRGB()
{
    return m_bIsOpacityModifyRGB;
}


#define kArrayMakeObjectsPerformSelectorWithValue(pArray, funcCall, funcSet, value)   do{\
CCObject* child;    \
CCARRAY_FOREACH(pArray, child)    \
{   \
    CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);   \
    if (pNode)  \
    {   \
        pNode->funcSet(value); \
        CCSprite* sprite = dynamic_cast<CCSprite*>(child);  \
        if (sprite) {   \
            funcCall(value, sprite);  \
        }   \
    }   \
    else    \
    {   \
        funcCall(value, (CCNode*)child);  \
    }   \
}}while(0)



void HRGBObject::setOpacityOnChildren(GLubyte opacity, CCNode* root)
{
    CCArray* children = root->getChildren();
    kArrayMakeObjectsPerformSelectorWithValue(children, setOpacityOnChildren, setOpacity, opacity);    
}

void HRGBObject::setColorOnChildren(const ccColor3B& color, CCNode* root)
{
    CCArray* children = root->getChildren();
    kArrayMakeObjectsPerformSelectorWithValue(children, setColorOnChildren, setColor, color);
}

void HRGBObject::setOpacityModifyRGBOnChildren(bool bModify, CCNode* root)
{
    CCArray* children = root->getChildren();
    kArrayMakeObjectsPerformSelectorWithValue(children, setOpacityModifyRGBOnChildren, setOpacityModifyRGB, bModify);
}
