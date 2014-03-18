//
//  HpLightProtocol.cpp
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-6.
//
//

#include "HpLightProtocol.h"

NS_HPAM_BEGIN

HpLightObject::HpLightObject()
: _displayedLight(ccBLACK)
, _realLight(ccBLACK)
, _cascadeLightEnabled(true)
, _displayedGray(0)
, _realGray(0)
, _cascadeGrayEnabled(true)
{
    
}

HpLightObject::~HpLightObject()
{
    
}

// Light
void HpLightObject::setLight(const ccColor3B &light)
{
    _displayedLight = _realLight = light;
	
	if (_cascadeLightEnabled)
    {
		ccColor3B parentLight = ccBLACK;
        CCNode* pThis = dynamic_cast<CCNode*>(this);
        HpLightProtocol *parent = dynamic_cast<HpLightProtocol*>(pThis->getParent());
		if (parent && parent->isCascadeLightEnabled())
        {
            parentLight = parent->getDisplayedLight();
        }
        
        updateDisplayedLight(parentLight);
	}
}

const ccColor3B& HpLightObject::getLight()
{
    return _realLight;
}

const ccColor3B& HpLightObject::getDisplayedLight()
{
    return _displayedLight;
}

bool HpLightObject::isCascadeLightEnabled()
{
    return _cascadeLightEnabled;
}

void HpLightObject::setCascadeLightEnabled(bool cascadeLightEnabled)
{
    _cascadeLightEnabled = cascadeLightEnabled;
}

void HpLightObject::updateDisplayedLight(const ccColor3B &parentLight)
{
    _displayedLight.r = clampf(_realLight.r + parentLight.r, 0, 255);
	_displayedLight.g = clampf(_realLight.g + parentLight.g, 0, 255);
	_displayedLight.b = clampf(_realLight.b + parentLight.b, 0, 255);
    
    if (_cascadeLightEnabled)
    {
        CCObject *obj = NULL;
        CCNode* pThis = dynamic_cast<CCNode*>(this);
        CCArray* children = pThis->getChildren();
        CCARRAY_FOREACH(children, obj)
        {
            HpLightProtocol *item = dynamic_cast<HpLightProtocol*>(obj);
            if (item)
            {
                item->updateDisplayedLight(_displayedLight);
            }
        }
    }
}

// Gray
GLubyte HpLightObject::getGray(void)
{
	return _realGray;
}

GLubyte HpLightObject::getDisplayedGray(void)
{
	return _displayedGray;
}

void HpLightObject::setGray(GLubyte gray)
{
    _displayedGray = _realGray = gray;
    
	if (_cascadeGrayEnabled)
    {
		GLubyte parentGray = 0;
        CCNode* pThis = dynamic_cast<CCNode*>(this);
        HpLightProtocol *pParent = dynamic_cast<HpLightProtocol*>(pThis->getParent());
        if (pParent && pParent->isCascadeGrayEnabled())
        {
            parentGray = pParent->getDisplayedGray();
        }
        this->updateDisplayedGray(parentGray);
	}
}

void HpLightObject::updateDisplayedGray(GLubyte parentGray)
{
    _displayedGray = 255 - (255-_realGray) * (1-parentGray/255.0);
	
    if (_cascadeGrayEnabled)
    {
        CCObject* pObj;
        CCNode* pThis = dynamic_cast<CCNode*>(this);
        CCArray* children = pThis->getChildren();
        CCARRAY_FOREACH(children, pObj)
        {
            HpLightProtocol* item = dynamic_cast<HpLightProtocol*>(pObj);
            if (item)
            {
                item->updateDisplayedGray(_displayedGray);
            }
        }
    }
}

bool HpLightObject::isCascadeGrayEnabled(void)
{
    return _cascadeGrayEnabled;
}

void HpLightObject::setCascadeGrayEnabled(bool cascadeGrayEnabled)
{
    _cascadeGrayEnabled = cascadeGrayEnabled;
}



NS_HPAM_END
