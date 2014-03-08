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
    
    CCLayerColor* layer = CCLayerColor::create(ccc4(100, 100, 0, 255), 2000, 2000);
    addChild(layer);

    
    /** chr文件的加载速度是xml的10倍，推荐chr文件
     * 请保持各个chr文件中的动画名称唯一，加前缀以区分。<参考CCSpriteFrame类>
     * 可以把HpCharaInstLoader与CCB结合使用，在CCBuilder中使用HpCharaInst自定义类
     */
    HpCharactorManager::sharedManager()->addCharactorsWithFile("test.chr");
    
    HpCharaInst* inst = HpCharaInst::create();
    addChild(inst);
    
//    inst->playAniByName("动画   0", true);
    
//    inst->runAction(HpPlay::create("动画   0", "动画   0", "动画   0", NULL));
    inst->playAniByName("动画   0", 0.f);
    inst->runAction(CCRepeatForever::create(CCSequence::create(HpShineTo::create(0.2, 255, 0, 0), HpShineTo::create(0.2, 0, 0, 0), NULL)));
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
