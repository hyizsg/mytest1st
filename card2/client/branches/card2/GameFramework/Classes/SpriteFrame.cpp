#include "cocos2dxframework.h"

HNAMESPACE_BEGIN

void HSpriteFrame::copyFrom(CCSpriteFrame *frame) {
    if (this == frame) return;
    setRect(frame->getRect());
    setRotated(frame->isRotated());
    setOffset(frame->getOffset());
    setOriginalSize(frame->getOriginalSize());
    setTexture(frame->getTexture());
    if (dynamic_cast<HSpriteFrame *>(frame)) {
        setClickRect(((HSpriteFrame *)frame)->getClickRect());
    }
}

bool HSpriteFrame::hasTexture() {
    return NULL != m_pobTexture;
}

CCTexture2D* HSpriteFrame::getTextureEx() {
    return m_pobTexture;
}

CCTexture2D* HSpriteFrame::getTexture(void) {
    m_bTextureAutoRelease = true;
    if( m_pobTexture ) {
        return m_pobTexture;
    }
    
    if( m_strTextureFilename.length() > 0 ) {
        setTexture(HSourceCache::getInstance()->textureWithFile(m_strTextureFilename.c_str()));
        if (m_pobTexture) {
            HSourceCache::getInstance()->addToAutoManager(this);
        }
        return m_pobTexture;
    }
    // no texture or texture filename
    return NULL;
}

HNAMESPACE_END
