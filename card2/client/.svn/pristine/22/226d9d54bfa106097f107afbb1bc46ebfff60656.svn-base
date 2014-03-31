//
//  HpTextureAtlas.h
//  GameFramework
//
//  Created by zhou gang on 13-12-3.
//  Copyright (c) 2013年 cxj. All rights reserved.
//

#ifndef __GameFramework__HpTextureAtlas__
#define __GameFramework__HpTextureAtlas__

#include "cocos2d.h"

USING_NS_CC;

class HpTextureAtlas : public CCTextureAtlas {
    
    
public:
    HpTextureAtlas();
    virtual ~HpTextureAtlas();
    
    virtual bool init(){ return true; }
    
    virtual void setTexture(CCTexture2D* tex);
    virtual void drawNumberOfQuads(unsigned int n, unsigned int start);
    
    CC_SYNTHESIZE_RETAIN(CCGLProgram*, m_shaderProgram, ShaderProgram);
    
    CREATE_FUNC(HpTextureAtlas);
    
protected:
    
    GLuint _textureLocation;
    GLuint _alphaLocation;
    
};


#endif /* defined(__GameFramework__HpTextureAtlas__) */
