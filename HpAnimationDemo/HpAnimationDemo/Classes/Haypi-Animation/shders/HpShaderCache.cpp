//
//  HpShaderCache.cpp
//  HpAnimationDemo
//
//  Created by 周 刚 on 14-3-1.
//
//

#include "Hpheaders.h"
#include "HpGLProgram.h"
#include "hpShaders.h"
#include "HpShaderCache.h"
#include "HpView.h"

NS_HPAM_BEGIN

enum {
    kCCShaderType_PositionTextureColorLight_HasPremultipliedAlpha =  10,
    kCCShaderType_PositionTextureColorLightAlpha_HasPremultipliedAlpha,
    
    kCCShaderType_PositionTextureColorLight_NoPremultipliedAlpha,
    kCCShaderType_PositionTextureColorLightAlpha_NoPremultipliedAlpha,
};

HpGLProgram* HpShaderCache::defaultShader()
{
    return programForKey(kCCShader_PositionTextureColorLight_HasPremultipliedAlpha);
}

HpGLProgram* HpShaderCache::programForKey(const char* key)
{
    HpGLProgram* p = (HpGLProgram*)CCShaderCache::sharedShaderCache()->programForKey(key);
    if (p == NULL) {
        loadDefaultShaders();
        return programForKey(key);
    }
    
    return p;
}

HpGLProgram* HpShaderCache::shaderByView(HpView* view, CCTexture2D* tex)
{
#ifndef CC_PLATFORM_IOS
    if (!tex || tex->hasPremultipliedAlpha()) {
         return defaultShader();
    }
    else{
        return programForKey(kCCShader_PositionTextureColorLight_NoPremultipliedAlpha);
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
        case 0b00: return programForKey(kCCShader_PositionTextureColorLight_NoPremultipliedAlpha);
        case 0b10: return programForKey(kCCShader_PositionTextureColorLight_HasPremultipliedAlpha);
        case 0b01: return programForKey(kCCShader_PositionTextureColorLightAlpha_NoPremultipliedAlpha);
        case 0b11: return programForKey(kCCShader_PositionTextureColorLightAlpha_HasPremultipliedAlpha);
        default: return defaultShader();
    }
    
#endif
    
}

void HpShaderCache::loadDefaultShaders()
{
    // 1st
    HpGLProgram* p = new HpGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorLight_HasPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorLight_HasPremultipliedAlpha);
    p->release();
    
    // 2nd
    p = new HpGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorLightAlpha_HasPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorLightAlpha_HasPremultipliedAlpha);
    p->release();
    
    // 3rd
    p = new HpGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorLight_NoPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorLight_NoPremultipliedAlpha);
    p->release();
    
    // 4th
    p = new HpGLProgram;
    loadDefaultShader(p, kCCShaderType_PositionTextureColorLightAlpha_NoPremultipliedAlpha);
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorLightAlpha_NoPremultipliedAlpha);
    p->release();
}


void HpShaderCache::reloadDefaultShaders()
{
    HpGLProgram* p = programForKey(kCCShader_PositionTextureColorLight_HasPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorLight_HasPremultipliedAlpha);
    
    p = programForKey(kCCShader_PositionTextureColorLightAlpha_HasPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorLightAlpha_HasPremultipliedAlpha);
    
    p = programForKey(kCCShader_PositionTextureColorLight_NoPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorLight_HasPremultipliedAlpha);
    
    p = programForKey(kCCShader_PositionTextureColorLightAlpha_NoPremultipliedAlpha);
    p->reset();
    loadDefaultShader(p, kCCShaderType_PositionTextureColorLightAlpha_HasPremultipliedAlpha);
}

void HpShaderCache::loadDefaultShader(HpGLProgram *p, int type)
{
    switch (type) {
        case kCCShaderType_PositionTextureColorLight_HasPremultipliedAlpha:
            p->initWithVertexShaderByteArray(ccPositionTextureColorLight_vert, ccPositionTextureColorLight_HasPremultipliedAlpha_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            p->addAttribute(kCCAttributeNameLight, kCCVertexAttrib_Light);
            p->addAttribute(kCCAttributeNameGray, kCCVertexAttrib_Gray);
            
            break;
        case kCCShaderType_PositionTextureColorLightAlpha_HasPremultipliedAlpha:
            p->initWithVertexShaderByteArray(ccPositionTextureColorLight_vert, ccPositionTextureColorLightAlpha_HasPremultipliedAlpha_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            p->addAttribute(kCCAttributeNameLight, kCCVertexAttrib_Light);
            p->addAttribute(kCCAttributeNameGray, kCCVertexAttrib_Gray);
            
            break;
            
        case kCCShaderType_PositionTextureColorLight_NoPremultipliedAlpha:
            p->initWithVertexShaderByteArray(ccPositionTextureColorLight_vert, ccPositionTextureColorLight_NoPremultipliedAlpha_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            p->addAttribute(kCCAttributeNameLight, kCCVertexAttrib_Light);
            p->addAttribute(kCCAttributeNameGray, kCCVertexAttrib_Gray);
            
            break;
        case kCCShaderType_PositionTextureColorLightAlpha_NoPremultipliedAlpha:
            p->initWithVertexShaderByteArray(ccPositionTextureColorLight_vert, ccPositionTextureColorLightAlpha_NoPremultipliedAlpha_frag);
            
            p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            p->addAttribute(kCCAttributeNameLight, kCCVertexAttrib_Light);
            p->addAttribute(kCCAttributeNameGray, kCCVertexAttrib_Gray);
            
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
