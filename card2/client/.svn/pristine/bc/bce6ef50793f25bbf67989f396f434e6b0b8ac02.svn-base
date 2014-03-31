//
//  HPlayerGuide.cpp
//  card
//
//  Created by zhou gang on 13-7-3.
//
//

#include "HPlayerGuide.h"

PlayerGuide::PlayerGuide()
{
    m_layerWidth = 0.0f;
    m_layerHeight = 0.0f;
}

PlayerGuide::~PlayerGuide()
{
    
}

bool PlayerGuide::init()
{
//    if (!super::init()) {
//        return false;
//    }
    
    return true;
}

void PlayerGuide::onEnter()
{
    //since v2.0
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -201000, true);
    //当进入这个对象时，设置touch事件的响应权限，menu的响应级别是-128，我们要获取比这个要高的权限，（设置的数值越低，权限越高）
//    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, -201, true);
    super::onEnter();
}

void PlayerGuide::onExit()
{
    //since v2.0
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    //退出时，把touch响应的事件 移除
//    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    super::onExit();
}
#pragma mark  --------------------------setSpriteAndPosition----------------------------

/*******************************************************************************
 *@param width 设置高亮区域的宽度，height 高亮区域的高度，point 设置layer的position
 *
 *
 *******************************************************************************/

void PlayerGuide::onSetSpriteAndPosition(float width,float height, CCPoint point)
{
    if (width != 0 && height != 0) {
        m_layerWidth = width;
        m_layerHeight = height;
        m_layer = CCLayerColor::create(ccc4(0x00, 0x00, 0x00, 0xff), width, height);
        m_layer->retain();
        ccBlendFunc ccb = {GL_ZERO,GL_ONE_MINUS_SRC_ALPHA};
        
        m_layer->setBlendFunc(ccb);
        m_layer->setPosition(point);
        
//        CCSprite *topright = CCSprite::spriteWithFile("yourfile");//自己设置圆角的小图，如果不需要圆角，可以直接把sprite去掉
//        topright->getTexture()->setAliasTexParameters();
//        ccBlendFunc cbf = {GL_ONE,GL_ONE_MINUS_DST_ALPHA};
//        topright->setBlendFunc(cbf);
//        topright->setPosition(ccp(m_layer->getContentSize().width - topright->getContentSize().width/2,m_layer->getContentSize().height - topright->getContentSize().height/2));
//        topright->setOpacity(255*0.5);
//        m_layer->addChild(topright,1);
//        
//        CCSprite *topleft = CCSprite::spriteWithFile(IMG_PATH(IMAGE_PLAYERGUIDE_ROUNDED));
//        topleft->getTexture()->setAliasTexParameters();
//        ccBlendFunc cbf1 = {GL_ONE,GL_ONE_MINUS_DST_ALPHA};
//        topleft->setBlendFunc(cbf1);
//        topleft->setPosition(ccp(topleft->getContentSize().width/2,m_layer->getContentSize().height - topleft->getContentSize().height/2));
//        topleft->setOpacity(255*0.5);
//        topleft->setFlipX(true);
//        m_layer->addChild(topleft,1);
//        
//        CCSprite *buttomleft = CCSprite::spriteWithFile(IMG_PATH(IMAGE_PLAYERGUIDE_ROUNDED));
//        buttomleft->getTexture()->setAliasTexParameters();
//        ccBlendFunc cbf2 = {GL_ONE,GL_ONE_MINUS_DST_ALPHA};
//        buttomleft->setBlendFunc(cbf2);
//        buttomleft->setPosition(ccp(buttomleft->getContentSize().width/2,buttomleft->getContentSize().height/2));
//        buttomleft->setOpacity(255*0.5);
//        buttomleft->setFlipX(true);
//        buttomleft->setFlipY(true);
//        m_layer->addChild(buttomleft,1);
//        
//        CCSprite *buttomright = CCSprite::spriteWithFile(IMG_PATH(IMAGE_PLAYERGUIDE_ROUNDED));
//        buttomright->getTexture()->setAliasTexParameters();
//        ccBlendFunc cbf3 = {GL_ONE,GL_ONE_MINUS_DST_ALPHA};
//        buttomright->setBlendFunc(cbf3);
//        buttomright->setPosition(ccp(m_layer->getContentSize().width - buttomleft->getContentSize().width/2,buttomright->getContentSize().height/2));
//        buttomright->setOpacity(255*0.5);
//        buttomright->setFlipY(true);
//        m_layer->addChild(buttomright,1);
    }
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    m_pTarget = CCRenderTexture::create(s.width, s.height);
    ccBlendFunc ccb1 = {GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};
    m_pTarget->getSprite()->setBlendFunc(ccb1);
    m_pTarget->clear(0.0f, 0.0f, 0.0f, 0.5f);
    
    m_pTarget->setPosition(ccp(s.width/2,s.height/2));
    
    this->addChild(m_pTarget);
    
    m_pTarget->begin();
    if (width != 0 && height != 0) {
        m_layer->visit();
    }
    
    m_pTarget->end();
}

bool PlayerGuide::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCPoint touchpoint = touch->getLocationInView();
    touchpoint = CCDirector::sharedDirector()->convertToGL(touchpoint);
    
    if (m_layerWidth != 0 && m_layerHeight != 0) {
        //如果点击高亮区域，则响应下层的区域
        CCRect rect = m_layer->boundingBox();
        if (rect.containsPoint(touchpoint)) {
            return false;
        }
        
    }
    
    return true;
}


void PlayerGuide::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
}

void PlayerGuide::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
}
