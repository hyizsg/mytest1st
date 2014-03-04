//
//  HpTextureAtlasShader.h
//  HpAnimationDemo
//
//  Created by 周 刚 on 14-3-1.
//
//

#ifndef __HpAnimationDemo__HpTextureAtlasShader__
#define __HpAnimationDemo__HpTextureAtlasShader__

#include "cocos2d.h"
#include "Hpheaders.h"

USING_NS_CC;

NS_HPAM_BEGIN

class HpGLProgram;

class HpTextureAtlasShader : CCObject
{
    
public:
    static HpGLProgram* shaderByTexture(CCTexture2D* tex);
    
    static HpGLProgram* defaultShader();
    static HpGLProgram* programForKey(const char* key);
    
    static void loadDefaultShaders();
    static void reloadDefaultShaders();
    static void loadDefaultShader(HpGLProgram *p, int type);

};

NS_HPAM_END

#endif /* defined(__HpAnimationDemo__HpTextureAtlasShader__) */
