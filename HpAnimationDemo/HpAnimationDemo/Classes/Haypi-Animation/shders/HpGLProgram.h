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
    kCCVertexAttrib_Gray,
};

enum {
    kCCUniformSamplerAlpha = kCCUniform_MAX
};



#define kCCShader_PositionTextureColorLightGray_HasPremultipliedAlpha           "UserShader_PositionTextureColorLightGray_HasPremultipliedAlpha"
#define kCCShader_PositionTextureColorLightGrayAlpha_HasPremultipliedAlpha      "UserShader_PositionTextureColorLightGrayAlpha_HasPremultipliedAlpha"


#define kCCShader_PositionTextureColorLightGray_NoPremultipliedAlpha            "UserShader_PositionTextureColorLightGray_NoPremultipliedAlpha"
#define kCCShader_PositionTextureColorLightGrayAlpha_NoPremultipliedAlpha       "UserShader_PositionTextureColorLightGrayAlpha_NoPremultipliedAlpha"

// uniform names
#define kCCUniformSampler_Alpha                     "CC_TexAlpha"
#define kCCUniformSampler_Mask                      "CC_TexMask"


// Attribute names
#define kCCAttributeNameLight                       "a_light"
#define kCCAttributeNameGray                        "a_gray"



class HpGLProgram : public CCGLProgram
{
    
#ifdef HP_ENABLE_ALPHA_TEXTURE
    CC_SYNTHESIZE(int, m_alphaLocation, AlphaLocation);
#endif
    
};

NS_HPAM_END


#endif /* defined(__HpAnimationDemo__HPGLProgram__) */
