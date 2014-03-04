//
//  HpTextureAtlasShader.cpp
//  HpAnimationDemo
//
//  Created by 周 刚 on 14-3-1.
//
//

#include "Hpheaders.h"
#include "HpGLProgram.h"
#include "hpShaders.h"
#include "HpTextureAtlasShader.h"

NS_HPAM_BEGIN

enum {
    kCCShaderType_PositionTextureColorExtra_HasPremultipliedAlpha =  10,
    kCCShaderType_PositionTextureColorExtraAlpha_HasPremultipliedAlpha,
    
    kCCShaderType_PositionTextureColorExtra_NoPremultipliedAlpha,
    kCCShaderType_PositionTextureColorExtraAlpha_NoPremultipliedAlpha,
};

HpGLProgram* HpTextureAtlasShader::defaultShader()
{
    return programForKey(kCCShader_PositionTextureColorExtra_HasPremultipliedAlpha);
}

HpGLProgram* HpTextureAtlasShader::programForKey(const char* key)
{
    HpGLProgram* p = (HpGLProgram*)CCShaderCache::sharedShaderCache()->programForKey(key);
    if (p == NULL) {
        loadDefaultShaders();
    }
    return programForKey(key);
}


HpGLProgram* HpTextureAtlasShader::shaderByTexture(CCTexture2D* tex)
{
#ifndef CC_PLATFORM_IOS
    if (!tex || tex->hasPremultipliedAlpha()) {
         return defaultShader();
    }
    else{
        return programForKey(kCCShader_PositionTextureColorExtra_NoPremultipliedAlpha);
    }
   
#else
    /** For android ECT Texture with a same name Alpha texture.
     * To suport it, you must define HP_ENABLE_ALPHA_TEXTURE;
     * And modify CCTexture ori source to add a mothed [CCTexture* getAlphaTexture()]
     * Or modify the define [getAlphaTexture(p)] to return a right texture
     */
    // zg to do ...
    
    if (!tex) {
        return defaultShader();
    }
    
    int type = (tex->hasPremultipliedAlpha() << 1) | (getAlphaTexture(tex) != NULL);
    switch (type) {
        case 0b00: return programForKey(kCCShader_PositionTextureColorExtra_NoPremultipliedAlpha);
        case 0b10: return programForKey(kCCShader_PositionTextureColorExtra_HasPremultipliedAlpha);
        case 0b01: return programForKey(kCCShader_PositionTextureColorExtraAlpha_NoPremultipliedAlpha);
        case 0b11: return programForKey(kCCShader_PositionTextureColorExtraAlpha_HasPremultipliedAlpha);
        default: return defaultShader();
    }
    
#endif
    
}

void HpTextureAtlasShader::loadDefaultShaders()
{
    // 1st
    HpGLProgram* p = new HpGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtra_HasPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorExtra_HasPremultipliedAlpha);
    p->release();
    
    // 2nd
    p = new HpGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtraAlpha_HasPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorExtraAlpha_HasPremultipliedAlpha);
    p->release();
    
    // 3rd
    p = new HpGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtra_NoPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorExtra_NoPremultipliedAlpha);
    p->release();
    
    // 4th
    p = new HpGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtraAlpha_NoPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorExtraAlpha_NoPremultipliedAlpha);
    p->release();
}


void HpTextureAtlasShader::reloadDefaultShaders()
{
    HpGLProgram* p = programForKey(kCCShader_PositionTextureColorExtra_HasPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtra_HasPremultipliedAlpha);
    
    p = programForKey(kCCShader_PositionTextureColorExtraAlpha_HasPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtraAlpha_HasPremultipliedAlpha);
    
    p = programForKey(kCCShader_PositionTextureColorExtra_NoPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtra_HasPremultipliedAlpha);
    
    p = programForKey(kCCShader_PositionTextureColorExtraAlpha_NoPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorExtraAlpha_HasPremultipliedAlpha);
}

void HpTextureAtlasShader::loadDefaultShader(HpGLProgram *p, int type)
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
    
#ifdef HP_ENABLE_ALPHA_TEXTURE
    p->setAlphaLocation(glGetUniformLocation(p->getProgram(), kCCUniformSampler_Alpha));
#endif
    
    CHECK_GL_ERROR_DEBUG();
}


NS_HPAM_END
