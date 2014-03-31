
#include "cocos2dxframework.h"
#include "GameScene.h"
#include "AppDelegate.h"
#include "Base.h"

#include "CCEditBoxLoader.h"
#include "CCTableViewLoader.h"
#include "CCSliderButtonLoader.h"
#include "HRichLabelTTF.h"

#include "SimpleAudioEngine.h"
#include "NetManager.h"

#include "HFileUtils.h"

using namespace CocosDenshion;

#define HRELOGININTERVAL          180

USING_HNAMESPACE;

//HKeypadDelegate
void HKeypadDelegate::keyBackClicked() {
    AppDelegate::getInstance()->getGameManager()->onBackPressed();
}
void HKeypadDelegate::keyMenuClicked() {
    AppDelegate::getInstance()->getGameManager()->onMenuPressed();
}

extern HGameDelegate *requestGameDelegate();

AppDelegate *AppDelegate::m_sAppDelegate = NULL;

AppDelegate *AppDelegate::getInstance() {
    return m_sAppDelegate;
}

AppDelegate::AppDelegate(): m_pGameScene(NULL), m_bIsRetinaScreen(false), m_iReloginInterval(HRELOGININTERVAL), m_lTimeEnterBackground(0) {
    setRandomSeed(time(NULL));
    m_sAppDelegate = this;
}

AppDelegate::~AppDelegate() {
    if (m_pGameScene)  delete m_pGameScene;
    m_sAppDelegate = NULL;
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    HFileUtils::initUserFileUtils();
    CCFileUtils::sharedFileUtils()->setPopupNotify(false);
    
    // initialize director
//    CCEGLView::sharedOpenGLView()->setFrameSize(960, 640);
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    m_pGameDelegate = requestGameDelegate();
    m_pGameDelegate->initDirector();
    
    
    updateLocaleStrings();
    
    // turn on display FPS
#ifdef DEBUG
    pDirector->setDisplayStats(true);
#endif
    
    HASSERT(m_pGameDelegate != NULL, "Game Delegate should not be NULL..."); 

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    pDirector->setProjection(kCCDirectorProjection2D);
    pDirector->setDepthTest(false);

    HSourceCache::getInstance();
    HTimerManager::getInstance();
    
    if (pDirector->getKeypadDispatcher()) {
        pDirector->getKeypadDispatcher()->addDelegate(&m_oKaypadDeletage);
        HLOGI("support keypad dispatcher...");
    }
    
    if (!m_pGameScene) m_pGameScene = new HGameScene();
    pDirector->runWithScene(m_pGameScene);
    preLoadLoaders();
    
    //HTimerManager::getInstance()->asyncProcess(HInvocation::create(m_pGameDelegate, hinvocation_selector(HGameDelegate::asyncInitGame), 0, NULL));
    m_pGameDelegate->initGame();
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    HTimerManager::getInstance()->pauseAllTimers();
//    CCDirector::sharedDirector()->setDrawStopped(true);
    
    m_pGameDelegate->enterBackground();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    
    HNetManager::getInstance()->closeSocket();
    
    struct timeval now;
    gettimeofday(&now, NULL);
    m_lTimeEnterBackground = now.tv_sec;
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    struct timeval now;
    gettimeofday(&now, NULL);
    if (now.tv_sec - m_lTimeEnterBackground > m_iReloginInterval) {
        getGameManager()->onNeedReLogin();
    } else {
        if (getGameManager()->HasLogin()) {
            HNetManager::getInstance()->connectWithSocket();
        }
    }
    
//    CCDirector::sharedDirector()->setDrawStopped(false);
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    
    AppDelegate::getInstance()->getGameManager()->updateScissors();
    
    m_pGameDelegate->enterForeground();
    
    
    HTimerManager::getInstance()->resumeAllTimers();
}

//private

void AppDelegate::preLoadLoaders() {
    CCNodeLoaderLibrary *library = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    library->registerCCNodeLoader("CCEditBox", CCEditBoxLoader::loader());
    library->registerCCNodeLoader("CCTableView", CCTableViewLoader::loader());
    library->registerCCNodeLoader("CCControlSlider", CCSliderButtonLoader::loader());
    library->registerCCNodeLoader("HRichLabelTTF", HRichLabelTTFLoader::loader());
    library->registerCCNodeLoader("HTouchEnabledLayerColor", HTouchEnabledLayerColorLoader::loader());
    m_pGameDelegate->preloadLoaders();
}
