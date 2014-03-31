//
//  HMaskedSprite.cpp
//  card
//
//  Created by zhou gang on 13-7-3.
//
//

#include "../../headers.h"
#include "HMaskedSprite.h"

bool HMaskedSprite::initWithFile(const char *pszFilename)
{
    CCSprite::initWithFile(pszFilename);
    
#define kCCShader_PositionTextureUserMask   "ShaderPositionTextureUserMask"
    
    CCGLProgram* pProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureUserMask);
    
    if (pProgram == NULL) {
        
        const GLchar* pszFragSource =
        "#ifdef GL_ES \n \
        precision lowp float; \n \
        #endif \n \
        varying vec4 v_fragmentColor; \n \
        varying vec2 v_texCoord; \n \
        uniform sampler2D u_texture; \n \
        uniform sampler2D u_mask; \n \
        void main(void) \n \
        { \n \
        // Convert to greyscale using NTSC weightings \n \
        vec4 col = texture2D(u_texture, v_texCoord); \n \
        vec4 maskcol = texture2D(u_mask, v_texCoord); \n \
        vec4 finalcol = vec4(col.r, col.g, col.b, col.a * maskcol.a); \n \
        gl_FragColor = v_fragmentColor * finalcol; \n \
        }";
        
        pProgram = new CCGLProgram();
        pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
        CCShaderCache::sharedShaderCache()->addProgram(pProgram, kCCShader_PositionTextureUserMask);
        pProgram->release();
        
        CHECK_GL_ERROR_DEBUG();
        
        pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        CHECK_GL_ERROR_DEBUG();
        
        pProgram->link();
        CHECK_GL_ERROR_DEBUG();
        
        pProgram->updateUniforms();
        CHECK_GL_ERROR_DEBUG();
    }

    setShaderProgram(pProgram);
    
    _textureLocation = glGetUniformLocation( pProgram->getProgram(), "u_texture");
    _maskLocation = glGetUniformLocation( pProgram->getProgram(), "u_mask");
    
    CHECK_GL_ERROR_DEBUG();

    
    return true;
}

void HMaskedSprite::setMaskTexture(CCTexture2D* mask)
{
    _maskTexture = mask;
}

void HMaskedSprite::draw()
{
    
}

