//
//  HMaskedSprite.h
//  card
//
//  Created by zhou gang on 13-7-3.
//
//

#ifndef __card__HMaskedSprite__
#define __card__HMaskedSprite__

class HMaskedSprite : public CCSprite {
    
public:
    
    virtual bool initWithFile(const char *pszFilename);
    virtual void draw();
    
    void setMaskTexture(CCTexture2D* mask);
    
public:
    CCTexture2D * _maskTexture;
    GLuint _textureLocation;
    GLuint _maskLocation;
};

#endif /* defined(__card__HMaskedSprite__) */
