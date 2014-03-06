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
{
    
}

HpLightObject::~HpLightObject()
{
    
}

void HpLightObject::setLight(const ccColor3B &light)
{
    _displayedLight = _realLight = light;
	
	if (_cascadeLightEnabled)
    {
		ccColor3B parentLight = ccBLACK;
        HpLightProtocol *parent = dynamic_cast<HpLightProtocol*>(((CCNode*)this)->getParent());
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
        CCArray* children = ((CCNode*)this)->getChildren();
        CCARRAY_FOREACH(children, obj)
        {
            CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(obj);
            if (item)
            {
                item->updateDisplayedColor(_displayedLight);
            }
        }
    }
}

NS_HPAM_END
