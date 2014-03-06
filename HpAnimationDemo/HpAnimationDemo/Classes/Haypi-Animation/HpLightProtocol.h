//
//  HpLightProtocol.h
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-6.
//
//

#ifndef __HpAnimationDemo__HpLightProtocol__
#define __HpAnimationDemo__HpLightProtocol__

#include "cocos2d.h"
#include "Hpheaders.h"

using namespace cocos2d;

NS_HPAM_BEGIN

class HpLightProtocol  {
    
    
public:
    /**
     * Changes the Light with R,G,B bytes
     *
     * @param Light Example: ccc3(255,100,0) means R=255, G=100, B=0
     */
    virtual void setLight(const ccColor3B& light) = 0;
    
    /**
     * Returns Light that is currently used.
     *
     * @return The ccColor3B contains R,G,B bytes.
     */
    virtual const ccColor3B& getLight(void) = 0;
    
    /**
     * Returns the displayed Light.
     *
     * @return The ccColor3B contains R,G,B bytes.
     */
    virtual const ccColor3B& getDisplayedLight(void) = 0;
    
    /**
     *  whether or not Light should be propagated to its children.
     */
    virtual bool isCascadeLightEnabled(void) = 0;
    virtual void setCascadeLightEnabled(bool cascadeLightEnabled) = 0;
    
    /**
     *  recursive method that updates display Light
     */
    virtual void updateDisplayedLight(const ccColor3B& parentLight) = 0;
    

};


class HpLightObject : HpLightProtocol
{
public:
    HpLightObject();
    virtual ~HpLightObject();
    
    virtual void setLight(const ccColor3B& Light);
    virtual const ccColor3B& getLight(void);
    virtual const ccColor3B& getDisplayedLight(void);
    
    virtual bool isCascadeLightEnabled(void);
    virtual void setCascadeLightEnabled(bool cascadeLightEnabled);
    
    virtual void updateDisplayedLight(const ccColor3B& Light);

protected:
	ccColor3B	_displayedLight;
    ccColor3B   _realLight;
	bool		_cascadeLightEnabled;
};


class HpNodeLight : public CCNode, public HpLightObject {
    
    
    
};

NS_HPAM_END


#endif /* defined(__HpAnimationDemo__HpLightProtocol__) */
