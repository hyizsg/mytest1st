#ifndef _SPRITEFRAME_H_
#define _SPRITEFRAME_H_

HNAMESPACE_BEGIN

class CC_DLL HSpriteFrame: public CCSpriteFrame {
    CC_SYNTHESIZE(CCRect, m_rectClick, ClickRect);
    CC_SYNTHESIZE(bool, m_bTextureAutoRelease, TextureAutoRelease);
public:
    HSpriteFrame(const char *key = NULL): m_bTextureAutoRelease(false) {
        if (key) m_strTextureFilename = key;
    }
    
    static HSpriteFrame *create(const char *key = NULL) {
        HSpriteFrame *pSpriteFrame = new HSpriteFrame(key);
//        pSpriteFrame->autorelease();
        CC_AUTO_RELEASE(pSpriteFrame);
        return pSpriteFrame;
    }
    
    static HSpriteFrame* create(const char* filename, const CCRect& rect) {
        HSpriteFrame *pSpriteFrame = new HSpriteFrame();
        pSpriteFrame->initWithTextureFilename(filename, rect);
//        pSpriteFrame->autorelease();
        CC_AUTO_RELEASE(pSpriteFrame);
        return pSpriteFrame;
    }
    static HSpriteFrame* create(const char* filename, const CCRect& rect, bool rotated, const CCPoint& offset, const CCSize& originalSize) {
        HSpriteFrame *pSpriteFrame = new HSpriteFrame();
        pSpriteFrame->initWithTextureFilename(filename, rect, rotated, offset, originalSize);
//        pSpriteFrame->autorelease();
        CC_AUTO_RELEASE(pSpriteFrame);
        return pSpriteFrame;
    }
    static HSpriteFrame* createWithTexture(CCTexture2D* pobTexture, const CCRect& rect) {
        HSpriteFrame *pSpriteFrame = new HSpriteFrame();
        pSpriteFrame->initWithTexture(pobTexture, rect);
//        pSpriteFrame->autorelease();
        CC_AUTO_RELEASE(pSpriteFrame);
        return pSpriteFrame;
    }
    static HSpriteFrame* createWithTexture(CCTexture2D* pobTexture, const CCRect& rect, bool rotated, const CCPoint& offset, const CCSize& originalSize) {
        HSpriteFrame *pSpriteFrame = new HSpriteFrame();
        pSpriteFrame->initWithTexture(pobTexture, rect, rotated, offset, originalSize);
//        pSpriteFrame->autorelease();
        CC_AUTO_RELEASE(pSpriteFrame);
        return pSpriteFrame;
    }
    
    const char *getTextureFilename() {
        return m_strTextureFilename.c_str();
    }
    
    void copyFrom(CCSpriteFrame *frame);
    
    bool hasTexture();
    CCTexture2D* getTextureEx();
    virtual CCTexture2D* getTexture(void);
    
//    virtual void release(void) {        
//        if (((m_uReference - m_uAutoReleaseCount) == 2) && m_bTextureAutoRelease) {
//            CCTexture2D *texture = getTexture();
//            if (texture) {
//                CCTextureCache::sharedTextureCache()->removeTexture(texture);
//                setTexture(NULL);
//            }
//        }
//        CCSpriteFrame::release();
//    }
    
//    virtual void retain(void) {
//        CCSpriteFrame::retain();
//        if (((m_uReference - m_uAutoReleaseCount) == 2) && m_bTextureAutoRelease && (m_strTextureFilename.length() > 0)) {
//            if (!getTexture()) {
//                setTexture(CCTextureCache::sharedTextureCache()->addImage(m_strTextureFilename.c_str()));
//            }
//        }
//    }
};

HNAMESPACE_END

#endif //_SPRITEFRAME_H_
