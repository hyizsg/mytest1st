//
//  CCProgressTimerLoader.cpp
//  card
//
//  Created by zhou gang on 13-5-22.
//
//


#include "../../headers.h"
#include "CCProgressTimerLoader.h"
#include "HRichSprite.h"

#define PROPERTY_FLIP "flip"
#define PROPERTY_DISPLAYFRAME "displayFrame"
#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"

HProgressTimer* HProgressTimer::create(CCSprite* sp)
{
    HProgressTimer *pProgressTimer = new HProgressTimer();
    if (pProgressTimer->initWithSprite(sp))
    {
        pProgressTimer->autorelease();
    }
    else
    {
        delete pProgressTimer;
        pProgressTimer = NULL;
    }
    
    return pProgressTimer;
}

void HProgressTimer::setSprite(CCSprite *pSprite)
{
    CCProgressTimer::setSprite(pSprite);
    if (pSprite && pSprite->getTexture() && pSprite->getTexture()->getMaskTexture()) {
        setShaderProgram(HRichSpriteShader::getAlphaShaderProgram());
    }else{
        setShaderProgram(HRichSpriteShader::getDefaultShaderProgram());
    }
}

void HProgressTimer::draw()
{
    if( ! m_pVertexData || ! m_pSprite || !m_pSprite->getTexture())
        return;
    
    CC_NODE_DRAW_SETUP();
    
    ccGLBlendFunc( m_pSprite->getBlendFunc().src, m_pSprite->getBlendFunc().dst );
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
    

    if (m_pSprite->getTexture()->getMaskTexture()) {
        glActiveTexture(GL_TEXTURE0 );
        glBindTexture(GL_TEXTURE_2D, m_pSprite->getTexture()->getName());
        glUniform1i(glGetUniformLocation(getShaderProgram()->getProgram(), "u_texture"), 0);
        
        glActiveTexture(GL_TEXTURE2 );
        glBindTexture(GL_TEXTURE_2D, m_pSprite->getTexture()->getMaskTexture()->getName());
        glUniform1i(glGetUniformLocation(getShaderProgram()->getProgram(), "u_alpha"), 2);
    }
    
    ccGLBindTexture2D( m_pSprite->getTexture()->getName() );
    
    
#ifdef EMSCRIPTEN
    setGLBufferData((void*) m_pVertexData, (m_nVertexDataCount * sizeof(ccV2F_C4B_T2F)), 0);
    
    int offset = 0;
    glVertexAttribPointer( kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, sizeof(ccV2F_C4B_T2F), (GLvoid*)offset);
    
    offset += sizeof(ccVertex2F);
    glVertexAttribPointer( kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ccV2F_C4B_T2F), (GLvoid*)offset);
    
    offset += sizeof(ccColor4B);
    glVertexAttribPointer( kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(ccV2F_C4B_T2F), (GLvoid*)offset);
#else
    glVertexAttribPointer( kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, sizeof(m_pVertexData[0]) , &m_pVertexData[0].vertices);
    glVertexAttribPointer( kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(m_pVertexData[0]), &m_pVertexData[0].texCoords);
    glVertexAttribPointer( kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(m_pVertexData[0]), &m_pVertexData[0].colors);
#endif // EMSCRIPTEN
    
    if(m_eType == kCCProgressTimerTypeRadial)
    {
        glDrawArrays(GL_TRIANGLE_FAN, 0, m_nVertexDataCount);
    }
    else if (m_eType == kCCProgressTimerTypeBar)
    {
        if (!m_bReverseDirection)
        {
            glDrawArrays(GL_TRIANGLE_STRIP, 0, m_nVertexDataCount);
        }
        else
        {
            glDrawArrays(GL_TRIANGLE_STRIP, 0, m_nVertexDataCount/2);
            glDrawArrays(GL_TRIANGLE_STRIP, 4, m_nVertexDataCount/2);
            // 2 draw calls
            CC_INCREMENT_GL_DRAWS(1);
        }
    }
    CC_INCREMENT_GL_DRAWS(1);
}


CCProgressTimer * CCProgressTimerLoader::createCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    return HProgressTimer::create(NULL);
}

void CCProgressTimerLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_DISPLAYFRAME) == 0) {
        CCProgressTimer* progress = ((CCProgressTimer *)pNode);
        progress->setSprite(CCSprite::createWithSpriteFrame(pCCSpriteFrame));
        //默认设置成从左到右的进度条
        progress->setType(kCCProgressTimerTypeBar);
        progress->setMidpoint(ccp(0, 0.5f));
        progress->setBarChangeRate(ccp(1, 0));
    } else {
        CCNodeLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
    }
}

void CCProgressTimerLoader::onHandlePropTypeFlip(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool * pFlip, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_FLIP) == 0) {
        ((CCProgressTimer *)pNode)->getSprite()->setFlipX(pFlip[0]);
        ((CCProgressTimer *)pNode)->getSprite()->setFlipY(pFlip[1]);
    } else {
        CCNodeLoader::onHandlePropTypeFlip(pNode, pParent, pPropertyName, pFlip, pCCBReader);
    }
}

void CCProgressTimerLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((CCProgressTimer*)pNode)->getSprite()->setColor(pCCColor3B);
    } else {
        CCNodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void CCProgressTimerLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        ((CCProgressTimer *)pNode)->setOpacity(pByte);
    } else {
        CCNodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void CCProgressTimerLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((CCProgressTimer *)pNode)->getSprite()->setBlendFunc(pCCBlendFunc);
    } else {
        CCNodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}
