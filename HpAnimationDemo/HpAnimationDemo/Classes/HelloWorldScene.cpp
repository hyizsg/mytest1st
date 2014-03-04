#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "HpCharactorManager.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace haypi_animation;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    
    CCLayerColor* layer = CCLayerColor::create(ccc4(100, 100, 0, 255), 2000, 2000);
    addChild(layer);

    HpCharactorManager* mgr = HpCharactorManager::SharedCharactorManager();
    mgr->loadCharactorForId(CCString::create("test"), CCString::create("test.xml"));
    
    HpCharaInst* inst = mgr->createInstanceOfId(CCString::create("test"), this);
    inst->playAniByName(CCString::create("动画   0"), true);
    inst->setPosition(0, 0);
    inst->setScale(1);
    
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
