//
//  HRichSprite.h
//  card
//
//  Created by zhou gang on 13-12-2.
//
//

#ifndef __card__HRichSprite__
#define __card__HRichSprite__

class HRichSprite : public CCSprite, public HGrayProtocol
{
public:
    
    CC_PROPERTY_BOOL(bool, m_bBlack, Black);
    CC_PROPERTY(CCTexture2D*, m_pMask, Mask);
    
    virtual void setTexture(CCTexture2D *texture);
    virtual void setTextureBgThread(const char* fileName);
    virtual void setTexture(const char* fileName, bool inThread);
    
    
public:
    GLuint _textureLocation;
    GLuint _maskLocation;
    GLuint _alphaLocation;
    
    static HRichSprite* create();
    static HRichSprite* create(CCSpriteFrame *pNewFrame);
    static HRichSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
    
public:
    HRichSprite();
    virtual ~HRichSprite();
    
    virtual void draw();
    
    void updateShader();
    bool hasAlphaTexture();
    
public:
    
    struct settingtexture : public HSettingFun {
        virtual void operator() (CCObject* sprite, CCObject* tex){
            ((CCSprite*)sprite)->setTexture((CCTexture2D*)tex);
        }
    };
    
    static HSettingFun* s_settingTexture;
};

class HRichSpriteLoader : public CCSpriteLoader {
    
    
public:
    virtual ~HRichSpriteLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HRichSpriteLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HRichSprite);
    
};

class HRichSpriteShader
{
public:
    static CCGLProgram* getDefaultShaderProgram();
    static CCGLProgram* getAlphaShaderProgram();
    
    static CCGLProgram* getGrayShaderProgram();
    static CCGLProgram* getGrayAlphaShaderProgram();
    
    static CCGLProgram* getMaskShaderProgram();
    static CCGLProgram* getMaskAlphaShaderProgram();
    
    static CCGLProgram* getMaskGrayShaderProgram();
    static CCGLProgram* getMaskGrayAlphaShaderProgram();
    
public:
    static CCGLProgram* createShadeProgram(const char* src, const char* key);
    static CCTexture2D* getWhiteTexture();
    
};

#endif /* defined(__card__HRichSprite__) */
