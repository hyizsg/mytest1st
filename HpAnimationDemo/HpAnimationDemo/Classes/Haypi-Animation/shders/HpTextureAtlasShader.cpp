//
//  HpTextureAtlasShader.cpp
//  HpAnimationDemo
//
//  Created by 周 刚 on 14-3-1.
//
//

#include "HpTextureAtlasShader.h"

enum {
    kCCShaderType_PositionTextureColorExtra_HasPremultipliedAlpha =  10,
    kCCShaderType_PositionTextureColorExtraAlpha_HasPremultipliedAlpha,
    
    kCCShaderType_PositionTextureColorExtra_NoPremultipliedAlpha,
    kCCShaderType_PositionTextureColorExtraAlpha_NoPremultipliedAlpha,
};

CCGLProgram* HpTextureAtlasShader::defaultShader()
{
    return programForKey(kCCShader_PositionTextureColorExtra_HasPremultipliedAlpha);
}

CCGLProgram* HpTextureAtlasShader::programForKey(const char* key)
{
    CCGLProgram* p = CCShaderCache::sharedShaderCache()->programForKey(key);
    if (p == NULL) {
        loadDefaultShaders();
    }
    return CCShaderCache::sharedShaderCache()->programForKey(key);
}


CCGLProgram* HpTextureAtlasShader::shaderByTexture(CCTexture2D* tex)
{
#ifdef CC_PLATFORM_IOS
    if (!tex || tex->hasPremultipliedAlpha()) {
         return defaultShader();
    }
    else{
        return programForKey(kCCShader_PositionTextureColorExtra_NoPremultipliedAlpha);
    }
   
#else
    
#endif
    
}

void HpTextureAtlasShader::loadDefaultShaders()
{
    // 1st
    CCGLProgram* p = new HPGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtra_HasPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorExtra_HasPremultipliedAlpha);
    p->release();
    
    // 2nd
    p = new HPGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtraAlpha_HasPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorExtraAlpha_HasPremultipliedAlpha);
    p->release();
    
    // 3rd
    p = new HPGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtra_NoPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorExtra_NoPremultipliedAlpha);
    p->release();
    
    // 4th
    p = new HPGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtraAlpha_NoPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorExtraAlpha_NoPremultipliedAlpha);
    p->release();
}


void HpTextureAtlasShader::reloadDefaultShaders()
{
    CCGLProgram* p = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorExtra_HasPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtra_HasPremultipliedAlpha);
    
    p = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorExtraAlpha_HasPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtraAlpha_HasPremultipliedAlpha);
    
    p = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorExtra_NoPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtra_HasPremultipliedAlpha);
    
    p = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorExtraAlpha_NoPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtraAlpha_HasPremultipliedAlpha);
}

void HpTextureAtlasShader::loadDefaultShader(CCGLProgram *p, int type)
{
    switch (type) {
        case kCCShaderType_PositionTextureColorExtra_HasPremultipliedAlpha:
            p->initWithVertexShaderByteArray(ccPositionTextureColorExtra_vert, ccPositionTextureColorExtra_HasPremultipliedAlpha_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            p->addAttribute(kCCAttributeNameExtra, kCCVertexAttrib_Extra);
            
            break;
        case kCCShaderType_PositionTextureColorExtraAlpha_HasPremultipliedAlpha:
            p->initWithVertexShaderByteArray(ccPositionTextureColorExtra_vert, ccPositionTextureColorExtraAlpha_HasPremultipliedAlpha_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            p->addAttribute(kCCAttributeNameExtra, kCCVertexAttrib_Extra);
            
            break;
            
        case kCCShaderType_PositionTextureColorExtra_NoPremultipliedAlpha:
            p->initWithVertexShaderByteArray(ccPositionTextureColorExtra_vert, ccPositionTextureColorExtra_NoPremultipliedAlpha_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            p->addAttribute(kCCAttributeNameExtra, kCCVertexAttrib_Extra);
            
            break;
        case kCCShaderType_PositionTextureColorExtraAlpha_NoPremultipliedAlpha:
            p->initWithVertexShaderByteArray(ccPositionTextureColorExtra_vert, ccPositionTextureColorExtraAlpha_NoPremultipliedAlpha_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            p->addAttribute(kCCAttributeNameExtra, kCCVertexAttrib_Extra);
            
            break;
        
        default:
            CCLOG("cocos2d: %s:%d, error shader type", __FUNCTION__, __LINE__);
            return;
    }
    
    p->link();
    p->updateUniforms();
    
    CHECK_GL_ERROR_DEBUG();
}

