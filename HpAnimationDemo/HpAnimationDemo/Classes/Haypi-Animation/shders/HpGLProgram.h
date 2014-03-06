//
//  HPGLProgram.h
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-3.
//
//

#ifndef __HpAnimationDemo__HPGLProgram__
#define __HpAnimationDemo__HPGLProgram__

#include "cocos2d.h"
#include "Hpheaders.h"

USING_NS_CC;

NS_HPAM_BEGIN

enum {
    kCCVertexAttrib_Light = kCCVertexAttrib_MAX,
};

enum {
    kCCUniformSamplerAlpha = kCCUniform_MAX
};



#define kCCShader_PositionTextureColorLight_HasPremultipliedAlpha           "UserShader_PositionTextureColorLight_HasPremultipliedAlpha"
#define kCCShader_PositionTextureColorLightAlpha_HasPremultipliedAlpha      "UserShader_PositionTextureColorLightAlpha_HasPremultipliedAlpha"


#define kCCShader_PositionTextureColorLight_NoPremultipliedAlpha            "UserShader_PositionTextureColorLight_NoPremultipliedAlpha"
#define kCCShader_PositionTextureColorLightAlpha_NoPremultipliedAlpha       "UserShader_PositionTextureColorLightAlpha_NoPremultipliedAlpha"

// uniform names
#define kCCUniformSampler_Alpha                     "CC_TexAlpha"
#define kCCUniformSampler_Mask                      "CC_TexMask"


// Attribute names
#define kCCAttributeNameLight                       "a_light"



class HpGLProgram : public CCGLProgram
{
    
#ifdef HP_ENABLE_ALPHA_TEXTURE
    CC_SYNTHESIZE(int, m_alphaLocation, AlphaLocation);
#endif
    
};

NS_HPAM_END


#endif /* defined(__HpAnimationDemo__HPGLProgram__) */
