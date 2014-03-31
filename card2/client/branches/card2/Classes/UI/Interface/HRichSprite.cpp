//
//  HRichSprite.cpp
//  card
//
//  Created by zhou gang on 13-12-2.
//
//

#include "../../headers.h"
#include "HRichSprite.h"

HSettingFun* HRichSprite::s_settingTexture = new HRichSprite::settingtexture();


HRichSprite::HRichSprite()
: m_bBlack(false)
, m_pMask(NULL)
{
}

HRichSprite::~HRichSprite()
{
    if (m_pobBatchNode == NULL) {
        setTexture(NULL);
    }
    
    CC_SAFE_RELEASE_NULL(m_pMask);
}

HRichSprite* HRichSprite::create()
{
    HRichSprite* sprite = new HRichSprite;
    if (sprite && sprite->init()){
        CC_AUTO_RELEASE(sprite);
        return sprite;
    }else{
        CC_SAFE_RELEASE(sprite);
        return NULL;
    }
}

HRichSprite* HRichSprite::create(CCSpriteFrame *pNewFrame)
{
    return createWithSpriteFrame(pNewFrame);
}

HRichSprite* HRichSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    HRichSprite *pobSprite = new HRichSprite();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        CC_AUTO_RELEASE(pobSprite);
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

bool HRichSprite::isBlack()
{
    return m_bBlack;
}

void HRichSprite::setBlack(bool var)
{
    if (m_bBlack != var)
    {
        m_bBlack = var;
        updateShader();
    }
}


CCTexture2D* HRichSprite::getMask()
{
    return m_pMask;
}

void HRichSprite::setMask(cocos2d::CCTexture2D *var)
{
    HC_SET(m_pMask, var);
    updateShader();
}

bool HRichSprite::hasAlphaTexture()
{
    if (getTexture() == NULL) {
        return NULL;
    }
    
    return (getMask() ? getMask() : getTexture())->getMaskTexture() != NULL;
}

void HRichSprite::setTexture(CCTexture2D *texture)
{
    if (texture != getTexture()) {
        HThreadTextureCache::getInstance()->lockTexture();
        {
            if (getTexture() != NULL && getTexture()->retainCount() == 2) {
                HThreadTextureCache::getInstance()->removeTexture(getTexture());
            }
            CCSprite::setTexture(texture);
        }
        HThreadTextureCache::getInstance()->unlockTexture();
        
        if (texture) {
            CCRect rect = CCRectZero;
            rect.size = (texture)->getContentSize();
            setTextureRect(rect);
        }else{
            setTextureRect(CCRectZero);
        }
        
        updateShader();
    }
}

void HRichSprite::setTextureBgThread(const char* fileName)
{
    if (fileName && strlen(fileName) > 0) {
        HSettingFun* func = new HRichSprite::settingtexture();
        HThreadTextureCache::getInstance()->loadTexture(this, fileName, func);
    }else{
        setTexture(NULL);
    }
}


void HRichSprite::setTexture(const char* fileName, bool inThread)
{
    inThread ? setTextureBgThread(fileName) : setTexture(_U(fileName));
}

void HRichSprite::draw()
{
    // 1
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
    
    this->getShaderProgram()->use();
    this->getShaderProgram()->setUniformsForBuiltins();
    
    // 2
    
    if (getMask() || hasAlphaTexture()) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture( GL_TEXTURE_2D,  getTexture()->getName());
        glUniform1i(_textureLocation, 0);
    }
    
    if (getMask()) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture( GL_TEXTURE_2D, m_pMask->getName());
        glUniform1i(_maskLocation, 1);
    }
    
    if (hasAlphaTexture()) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture( GL_TEXTURE_2D, (m_pMask ? m_pMask : getTexture())->getMaskTexture()->getName());
        glUniform1i(_alphaLocation, 2);
    }
    
    ccGLBindTexture2D(getTexture() ? this->getTexture()->getName() : 0);
    
    // 3
#define kQuadSize sizeof(m_sQuad.bl)
    long offset = (long)&m_sQuad;
    
    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    // 4
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CC_INCREMENT_GL_DRAWS(1);
    
}

void HRichSprite::updateShader()
{
    int mask = getMask() != NULL;
    int gray = isBlack() << 1;
    int alpha = hasAlphaTexture() << 2;
    
    int shadertype = mask | gray | alpha;
    CCGLProgram* pProgram = NULL;
    
    switch (shadertype) {
        case 0b000: pProgram = HRichSpriteShader::getDefaultShaderProgram(); break;
        case 0b001: pProgram = HRichSpriteShader::getMaskShaderProgram(); break;
        case 0b010: pProgram = HRichSpriteShader::getGrayShaderProgram(); break;
        case 0b011: pProgram = HRichSpriteShader::getMaskGrayShaderProgram(); break;
        case 0b100: pProgram = HRichSpriteShader::getAlphaShaderProgram(); break;
        case 0b101: pProgram = HRichSpriteShader::getMaskAlphaShaderProgram(); break;
        case 0b110: pProgram = HRichSpriteShader::getGrayAlphaShaderProgram(); break;
        case 0b111: pProgram = HRichSpriteShader::getMaskGrayAlphaShaderProgram(); break;
    }
    
    setShaderProgram(pProgram);
    _textureLocation = glGetUniformLocation( pProgram->getProgram(), "u_texture");
    _maskLocation = glGetUniformLocation( pProgram->getProgram(), "u_mask");
    _alphaLocation = glGetUniformLocation( pProgram->getProgram(), "u_alpha");
}


#define kCCShader_PositionTextureUserAlpha              "kCCShader_PositionTextureUserAlpha"
#define kCCShader_PositionTextureUserGray               "kCCShader_PositionTextureUserGray"
#define kCCShader_PositionTextureUserGrayAlpha          "kCCShader_PositionTextureUserGrayAlpha"
#define kCCShader_PositionTextureUserMask               "kCCShader_PositionTextureUserMask"
#define kCCShader_PositionTextureUserMaskAlpha          "kCCShader_PositionTextureUserMaskAlpha"
#define kCCShader_PositionTextureUserMaskGray           "kCCShader_PositionTextureUserMaskGray"
#define kCCShader_PositionTextureUserMaskGrayAlpha      "kCCShader_PositionTextureUserMaskGrayAlpha"


CCGLProgram* HRichSpriteShader::getDefaultShaderProgram()
{
    return CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor);
}


CCGLProgram* HRichSpriteShader::getAlphaShaderProgram()
{
    CCGLProgram* pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserAlpha);
    if (pProgram == NULL) {
        const GLchar* pszFragSource =
        "#ifdef GL_ES \n \
        precision lowp float; \n \
        #endif \n \
        varying vec4 v_fragmentColor; \n \
        varying vec2 v_texCoord; \n \
        uniform sampler2D u_texture; \n \
        uniform sampler2D u_alpha; \n \
        void main(void) \n \
        { \n \
        vec4 finalCol = texture2D(u_texture, v_texCoord); \n \
        vec4 alphaCol = texture2D(u_alpha, v_texCoord); \n \
        finalCol.a = finalCol.a * alphaCol.a; \n \
        gl_FragColor = v_fragmentColor * finalCol; \n \
        }";
        
        HShaderCache::getInstance()->addProgram(kCCShader_PositionTextureUserAlpha, ccPositionTextureColor_vert, pszFragSource, HSHADERTYPE_POSITIONTEXTIRECOLOR);
        pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserAlpha);
        
    }
    
    return pProgram;
}

CCGLProgram* HRichSpriteShader::getGrayShaderProgram()
{
    CCGLProgram* pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserGray);
    if (pProgram == NULL) {
        const GLchar* pszFragSource =
        "#ifdef GL_ES \n \
        precision lowp float; \n \
        #endif \n \
        varying vec4 v_fragmentColor; \n \
        varying vec2 v_texCoord; \n \
        uniform sampler2D u_texture; \n \
        void main(void) \n \
        { \n \
        vec4 origCol = texture2D(u_texture, v_texCoord); \n \
        float grey = dot(origCol.rgb, vec3(0.299, 0.587, 0.114)); \n \
        vec4 finalCol = vec4(grey, grey, grey, origCol.a); \n \
        gl_FragColor = v_fragmentColor * finalCol; \n \
        }";
        
        HShaderCache::getInstance()->addProgram(kCCShader_PositionTextureUserGray, ccPositionTextureColor_vert, pszFragSource, HSHADERTYPE_POSITIONTEXTIRECOLOR);
        pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserGray);
    }
    
    return pProgram;
}

CCGLProgram* HRichSpriteShader::getGrayAlphaShaderProgram()
{
    CCGLProgram* pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserGrayAlpha);
    if (pProgram == NULL) {
        const GLchar* pszFragSource =
        "#ifdef GL_ES \n \
        precision lowp float; \n \
        #endif \n \
        varying vec4 v_fragmentColor; \n \
        varying vec2 v_texCoord; \n \
        uniform sampler2D u_texture; \n \
        uniform sampler2D u_alpha; \n \
        void main(void) \n \
        { \n \
        vec4 origCol = texture2D(u_texture, v_texCoord); \n \
        vec4 alphaCol = texture2D(u_alpha, v_texCoord); \n \
        float grey = dot(origCol.rgb, vec3(0.299, 0.587, 0.114)); \n \
        vec4 finalCol = vec4(grey, grey, grey, origCol.a * alphaCol.a); \n \
        gl_FragColor = v_fragmentColor * finalCol; \n \
        }";
        
        HShaderCache::getInstance()->addProgram(kCCShader_PositionTextureUserGrayAlpha, ccPositionTextureColor_vert, pszFragSource, HSHADERTYPE_POSITIONTEXTIRECOLOR);
        pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserGrayAlpha);
    }
    
    return pProgram;
}

CCGLProgram* HRichSpriteShader::getMaskShaderProgram()
{
    CCGLProgram* pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserMask);
 
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
        vec4 finalCol = texture2D(u_texture, v_texCoord); \n \
        vec4 maskCol = texture2D(u_mask, v_texCoord); \n \
        finalCol.a = finalCol.a * maskCol.a; \n \
        gl_FragColor = v_fragmentColor * finalCol; \n \
        }";
        
        HShaderCache::getInstance()->addProgram(kCCShader_PositionTextureUserMask, ccPositionTextureColor_vert, pszFragSource, HSHADERTYPE_POSITIONTEXTIRECOLOR);
        pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserMask);
    }
    
    return pProgram;
}

CCGLProgram* HRichSpriteShader::getMaskGrayShaderProgram()
{
    CCGLProgram* pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserMaskGray);
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
        vec4 origCol = texture2D(u_texture, v_texCoord); \n \
        vec4 maskCol = texture2D(u_mask, v_texCoord); \n \
        float grey = dot(origCol.rgb, vec3(0.299, 0.587, 0.114)); \n \
        vec4 finalCol = vec4(grey, grey, grey, origCol.a * maskCol.a); \n \
        gl_FragColor = v_fragmentColor * finalCol; \n \
        }";
        
        HShaderCache::getInstance()->addProgram(kCCShader_PositionTextureUserMaskGray, ccPositionTextureColor_vert, pszFragSource, HSHADERTYPE_POSITIONTEXTIRECOLOR);
        pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserMaskGray);
    }

    return pProgram;
}

CCGLProgram* HRichSpriteShader::getMaskAlphaShaderProgram()
{
    CCGLProgram* pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserMaskAlpha);
    if (pProgram == NULL) {
        const GLchar* pszFragSource =
        "#ifdef GL_ES \n \
        precision lowp float; \n \
        #endif \n \
        varying vec4 v_fragmentColor; \n \
        varying vec2 v_texCoord; \n \
        uniform sampler2D u_texture; \n \
        uniform sampler2D u_mask; \n \
        uniform sampler2D u_alpha; \n \
        void main(void) \n \
        { \n \
        vec4 finalCol = texture2D(u_texture, v_texCoord); \n \
        vec4 maskCol = texture2D(u_mask, v_texCoord); \n \
        vec4 alphaCol = texture2D(u_alpha, v_texCoord); \n \
        finalCol.a = finalCol.a * maskCol.a * alphaCol.a; \n \
        gl_FragColor = v_fragmentColor * finalCol; \n \
        }";
        
        HShaderCache::getInstance()->addProgram(kCCShader_PositionTextureUserMaskAlpha, ccPositionTextureColor_vert, pszFragSource, HSHADERTYPE_POSITIONTEXTIRECOLOR);
        pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserMaskAlpha);
       
    }
    
    return pProgram;
}

CCGLProgram* HRichSpriteShader::getMaskGrayAlphaShaderProgram()
{
    CCGLProgram* pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserMaskGrayAlpha);
    if (pProgram == NULL) {
        const GLchar* pszFragSource =
        "#ifdef GL_ES \n \
        precision lowp float; \n \
        #endif \n \
        varying vec4 v_fragmentColor; \n \
        varying vec2 v_texCoord; \n \
        uniform sampler2D u_texture; \n \
        uniform sampler2D u_mask; \n \
        uniform sampler2D u_alpha; \n \
        void main(void) \n \
        { \n \
        vec4 origCol = texture2D(u_texture, v_texCoord); \n \
        vec4 maskCol = texture2D(u_mask, v_texCoord); \n \
        vec4 alphaCol = texture2D(u_alpha, v_texCoord); \n \
        float grey = dot(origCol.rgb, vec3(0.299, 0.587, 0.114)); \n \
        vec4 finalCol = vec4(grey, grey, grey, origCol.a * maskCol.a * alphaCol.a); \n \
        gl_FragColor = v_fragmentColor * finalCol; \n \
        }";
        
        HShaderCache::getInstance()->addProgram(kCCShader_PositionTextureUserMaskGrayAlpha, ccPositionTextureColor_vert, pszFragSource, HSHADERTYPE_POSITIONTEXTIRECOLOR);
        pProgram = HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserMaskGrayAlpha);
    }
    
    return pProgram;
}

CCGLProgram* HRichSpriteShader::createShadeProgram(const char* pszFragSource, const char* pShadekey)
{
    CCGLProgram* pProgram = new CCGLProgram();
    pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
    CCShaderCache::sharedShaderCache()->addProgram(pProgram, pShadekey);
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
    
    return pProgram;
}

#define CC_2x2_WHITE_IMAGE_KEY  "cc_2x2_white_image"

CCTexture2D* HRichSpriteShader::getWhiteTexture()
{
    CCTexture2D* tex = CCTextureCache::sharedTextureCache()->textureForKey(CC_2x2_WHITE_IMAGE_KEY);
    if (tex == NULL){
        CCSprite::create()->setTexture(NULL);
    }
    
    return CCTextureCache::sharedTextureCache()->textureForKey(CC_2x2_WHITE_IMAGE_KEY);
}

