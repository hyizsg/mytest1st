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

    HpCharactorManager* mgr = HpCharactorManager::SharedCharactorManager();
    mgr->loadCharactorForId(CCString::create("test"), CCString::create("test.chr"));
    
    HpCharaInst* inst = mgr->createInstanceOfId(CCString::create("test"), this);
//    inst->setPosition(300, 300);
//    inst->playAniByName(CCString::create("hudie_1"), true);
    inst->playAniByName(CCString::create("动画   0"), true);
    inst->setScale(3);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
