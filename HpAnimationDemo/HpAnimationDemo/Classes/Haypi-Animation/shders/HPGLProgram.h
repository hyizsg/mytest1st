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
USING_NS_CC;


enum {
    kCCVertexAttrib_Extra = kCCVertexAttrib_MAX,
};

enum {
    kCCUniformSamplerAlpha = kCCUniform_MAX
};



#define kCCShader_PositionTextureColorExtra_HasPremultipliedAlpha           "UserShader_PositionTextureColorExtra_HasPremultipliedAlpha"
#define kCCShader_PositionTextureColorExtraAlpha_HasPremultipliedAlpha      "UserShader_PositionTextureColorExtraAlpha_HasPremultipliedAlpha"


#define kCCShader_PositionTextureColorExtra_NoPremultipliedAlpha            "UserShader_PositionTextureColorExtra_NoPremultipliedAlpha"
#define kCCShader_PositionTextureColorExtraAlpha_NoPremultipliedAlpha       "UserShader_PositionTextureColorExtraAlpha_NoPremultipliedAlpha"

// uniform names
#define kCCUniformSampler_Alpha                     "CC_TexAlpha"
#define kCCUniformSampler_Mask                      "CC_TexMask"


// Attribute names
#define kCCAttributeNameExtra                       "a_extra"



class HPGLProgram : public CCGLProgram {
    

};


#endif /* defined(__HpAnimationDemo__HPGLProgram__) */
