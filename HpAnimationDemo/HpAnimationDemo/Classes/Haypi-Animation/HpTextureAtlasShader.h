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

#include "HPGLProgram.h"
#include "hpShaders.h"

USING_NS_CC;

class HpTextureAtlasShader : CCObject
{
    
public:
    static CCGLProgram* shaderByTexture(CCTexture2D* tex);
    
    static CCGLProgram* defaultShader();
    static CCGLProgram* programForKey(const char* key);
    
    static void loadDefaultShaders();
    static void reloadDefaultShaders();
    static void loadDefaultShader(CCGLProgram *p, int type);

};


#endif /* defined(__HpAnimationDemo__HpTextureAtlasShader__) */
