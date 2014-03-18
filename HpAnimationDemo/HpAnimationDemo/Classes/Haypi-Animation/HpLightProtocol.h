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
    
    
    /**
     * Returns the displayed gray.
     *
     * @return  The gray of sprite, from 0 ~ 255
     */
    virtual GLubyte getDisplayedGray(void) = 0;
    /**
     * Returns the gray.
     *
     * The gray which indicates how transparent or opaque this node is.
     * 0 indicates fully transparent and 255 is fully opaque.
     *
     * @return  The gray of sprite, from 0 ~ 255
     */
    virtual GLubyte getGray(void) = 0;
    
    /**
     * Changes the gray.
     *
     * @param   value   Goes from 0 to 255, where 255 means fully opaque and 0 means fully transparent.
     */
    virtual void setGray(GLubyte gray) = 0;
    
    
    /**
     *  whether or not gray should be propagated to its children.
     */
    virtual bool isCascadeGrayEnabled(void) = 0;
    virtual void setCascadeGrayEnabled(bool cascadeGrayEnabled) = 0;
    
    /**
     *  recursive method that updates the displayed gray.
     */
    virtual void updateDisplayedGray(GLubyte gray) = 0;
    

};


class HpLightObject : public HpLightProtocol
{
public:
    HpLightObject();
    virtual ~HpLightObject();
    
    // Light
    virtual void setLight(const ccColor3B& light);
    virtual const ccColor3B& getLight(void);
    virtual const ccColor3B& getDisplayedLight(void);
    
    virtual bool isCascadeLightEnabled(void);
    virtual void setCascadeLightEnabled(bool cascadeLightEnabled);
    
    virtual void updateDisplayedLight(const ccColor3B& parentLight);
    
    // Gray
    virtual GLubyte getDisplayedGray(void);
    virtual GLubyte getGray(void);
    virtual void setGray(GLubyte gray);
    
    virtual bool isCascadeGrayEnabled(void);
    virtual void setCascadeGrayEnabled(bool cascadeGrayEnabled);
    
    virtual void updateDisplayedGray(GLubyte parentGray);


protected:
	ccColor3B	_displayedLight;
    ccColor3B   _realLight;
	bool		_cascadeLightEnabled;
    
    GLubyte		_displayedGray;
    GLubyte     _realGray;
    bool        _cascadeGrayEnabled;
};


class HpNodeLight : public CCNode, public HpLightObject {
    
    
    
};

NS_HPAM_END


#endif /* defined(__HpAnimationDemo__HpLightProtocol__) */
