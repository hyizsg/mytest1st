//
//  HpTextureAtlas.cpp
//  GameFramework
//
//  Created by zhou gang on 13-12-3.
//  Copyright (c) 2013年 cxj. All rights reserved.
//

#include "HpTextureAtlas.h"
#include "cocos2dxframework.h"
#include "SourceCache.h"

HpTextureAtlas::HpTextureAtlas()
: m_shaderProgram(NULL)
, _textureLocation(0)
, _alphaLocation(1)
{
    
    
}

HpTextureAtlas::~HpTextureAtlas()
{
    CC_SAFE_RELEASE_NULL(m_shaderProgram);
}

#define kCCShader_PositionTextureUserAlpha              "kCCShader_PositionTextureUserAlpha_Atlas"

void HpTextureAtlas::setTexture(CCTexture2D * var)
{
    CCTextureAtlas::setTexture(var);
    
    if (var) {
        if (var->getMaskTexture() == NULL) {
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
        }else{
            CCGLProgram* pProgram = haypi::HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserAlpha);
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
                // Convert to greyscale using NTSC weightings \n \
                vec4 finalcol = texture2D(u_texture, v_texCoord); \n \
                finalcol.a = texture2D(u_alpha, v_texCoord).a; \n \
                gl_FragColor = v_fragmentColor * finalcol; \n \
                }";
                
                haypi::HShaderCache::getInstance()->addProgram(kCCShader_PositionTextureUserAlpha, ccPositionTextureColor_vert, pszFragSource, HSHADERTYPE_POSITIONTEXTIRECOLOR);
                
                pProgram = haypi::HShaderCache::getInstance()->getProgram(kCCShader_PositionTextureUserAlpha);
            }
            
            setShaderProgram(pProgram);
            _textureLocation = glGetUniformLocation( pProgram->getProgram(), "u_texture");
            _alphaLocation = glGetUniformLocation( pProgram->getProgram(), "u_alpha");
        }
    }
}

void HpTextureAtlas::drawNumberOfQuads(unsigned int n, unsigned int start)
{
    if (0 == n)
    {
        return;
    }
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
    
    this->getShaderProgram()->use();
    this->getShaderProgram()->setUniformsForBuiltins();
    
    if (getTexture()->getMaskTexture()) {
        
        // 2
        glActiveTexture(GL_TEXTURE0);
        glBindTexture( GL_TEXTURE_2D,  getTexture()->getName());
        glUniform1i(_textureLocation, 0);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture( GL_TEXTURE_2D, getTexture()->getMaskTexture()->getName());
        glUniform1i(_alphaLocation, 1);
        ccGLBindTexture2D(m_pTexture->getName());
     
        
//        ccGLBindTexture2DN(1, getTexture()->getMaskTexture()->getName());
//        glUniform1i(_alphaLocation, 1);
//        
//        ccGLBindTexture2DN(0, m_pTexture->getName());
//        glUniform1i(_textureLocation, 0);
        
    }else{
        
        ccGLBindTexture2D(m_pTexture->getName());
    }
    
    
    
#if CC_TEXTURE_ATLAS_USE_VAO
    
    //
    // Using VBO and VAO
    //
    
    // XXX: update is done in draw... perhaps it should be done in a timer
    if (m_bDirty)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_pBuffersVBO[0]);
        // option 1: subdata
        //glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0])*start, sizeof(m_pQuads[0]) * n , &m_pQuads[start] );
		
		// option 2: data
        //		glBufferData(GL_ARRAY_BUFFER, sizeof(quads_[0]) * (n-start), &quads_[start], GL_DYNAMIC_DRAW);
		
		// option 3: orphaning + glMapBuffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0]) * (n-start), NULL, GL_DYNAMIC_DRAW);
		void *buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		memcpy(buf, m_pQuads, sizeof(m_pQuads[0])* (n-start));
		glUnmapBuffer(GL_ARRAY_BUFFER);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        m_bDirty = false;
    }
    
    ccGLBindVAO(m_uVAOname);
    
#if CC_REBIND_INDICES_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBuffersVBO[1]);
#endif
    
#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
    glDrawElements(GL_TRIANGLE_STRIP, (GLsizei) n*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(m_pIndices[0])) );
#else
    glDrawElements(GL_TRIANGLES, (GLsizei) n*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(m_pIndices[0])) );
#endif // CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
    
#if CC_REBIND_INDICES_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
    
    //    glBindVertexArray(0);
    
#else // ! CC_TEXTURE_ATLAS_USE_VAO
    
    //
    // Using VBO without VAO
    //
    
#define kQuadSize sizeof(m_pQuads[0].bl)
    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffersVBO[0]);
    
    // XXX: update is done in draw... perhaps it should be done in a timer
    if (m_bDirty)
    {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0])*start, sizeof(m_pQuads[0]) * n , &m_pQuads[start] );
        m_bDirty = false;
    }
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
    
    // vertices
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(ccV3F_C4B_T2F, vertices));
    
    // colors
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof(ccV3F_C4B_T2F, colors));
    
    // tex coords
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(ccV3F_C4B_T2F, texCoords));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pBuffersVBO[1]);
    
#if CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
    glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)n*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(m_pIndices[0])));
#else
    glDrawElements(GL_TRIANGLES, (GLsizei)n*6, GL_UNSIGNED_SHORT, (GLvoid*) (start*6*sizeof(m_pIndices[0])));
#endif // CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
#endif // CC_TEXTURE_ATLAS_USE_VAO
    
    CC_INCREMENT_GL_DRAWS(1);
    CHECK_GL_ERROR_DEBUG();
    
}