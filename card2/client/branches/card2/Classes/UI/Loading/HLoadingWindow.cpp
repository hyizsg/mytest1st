
#include "headers.h"
#include "HLoadingWindow.h"
#include "HTips.h"

HSINGLETON_OBJECT_IMP(HLoadingWindow);

CCScene* HLoadingWindow::scene()
{
	CCScene* scene = CCScene::create();
	HLoadingWindow* layer = new HLoadingWindow();
	scene->addChild(layer);
	layer->release();

	return scene;
}

HLoadingWindow::HLoadingWindow()
: loadingQueue(NULL)
{
    readNodeGraphFromFile("Loading2.ccbi");

	totalPngNum = 1;
	curPngLoadingNum = 0;
    bEnterForeground = false;
    bLoadingCompleted = false;

	error = 0;
	errorPrompt = NULL;
}

HLoadingWindow::~HLoadingWindow()
{
    
}

BEGIN_MEMBER_MAP(HLoadingWindow)
    MEMBER(m_pLoadingTip)
    MEMBER(m_pLoadingLine)
END_MEMBER_MAP()

void HLoadingWindow::onExit()
{
    super::onExit();
    
    totalPngNum = 1;
	curPngLoadingNum = 0;
    bEnterForeground = false;
    bLoadingCompleted = false;
    
	error = 0;
	errorPrompt = NULL;
    
    CC_SAFE_RELEASE_NULL(loadingQueue);
}

void HLoadingWindow::onEnterTransitionDidFinish()
{
    super::onEnterTransitionDidFinish();
    
    bEnterForeground = true;
    
    if (loadingQueue && loadingQueue->count() > 0) {
        FOREACH(LoadingAction*, action, loadingQueue) {
            action->begin();
        }
    }
}

void HLoadingWindow::pushAction(LoadingAction* action)
{
    if (loadingQueue == NULL) {
        loadingQueue = new CCArray;
    }
    
    loadingQueue->addObject(action);
}

void HLoadingWindow::end()
{
    bLoadingCompleted = true;
    if (!loadingQueue) {
        schedule(schedule_selector(HLoadingWindow::ScheduleCreateSpritesAfterLoadingData), 0.03f);
    }
}

void HLoadingWindow::start()
{
    
    
    if (loadingQueue) {
        
        //registher the schedule
        schedule(schedule_selector(HLoadingWindow::ScheduleCreateSpritesAfterLoadingData), 0.03f);
        schedule(schedule_selector(HLoadingWindow::ScheduleUpdateLoadingLabel), 0.03f);
        
        totalPngNum = loadingQueue->count();
        bLoadingCompleted = false;
        
        if (bEnterForeground) {
            FOREACH(LoadingAction*, action, loadingQueue) {
                action->begin();
            }
        }
    }
    
    if (!getParent()) {
        
        m_pLoadingLine->setPercentage(0);
        m_pLoadingTip->setString(HTips::roll());
        
        CCScene* scene = CCScene::create();
        CCScene* sceneFade = CCTransitionFade::create(0.5, scene);
        
        scene->addChild(this);
        CCDirector::sharedDirector()->pushScene(sceneFade);
    }
    
}


void HLoadingWindow::ScheduleUpdateLoadingLabel(float dt)
{
	if(error != 0) return;
    
	char msg[32];
    float per = curPngLoadingNum*100.f/totalPngNum;
    
	sprintf(msg,"Loading...%d%%",(int)(per));
    
    m_pLoadingLine->setPercentage(per);
    
}

void HLoadingWindow::LoadingData(HThread *)
{
    CCThread thread;
    thread.createAutoreleasePool();
    
	bLoadingCompleted = false;
    error = 0;
    
    while (!bLoadingCompleted)
    {
        FOREACH(LoadingAction*, action, loadingQueue) {
            if (action->isNeedAsynCall()) {
                action->asynAction();
            }
        }
        
        usleep(50);
    }
    
}

void HLoadingWindow::ScheduleCreateSpritesAfterLoadingData(float dt)
{
	if(error != 0)
	{
		PromptError();
		return;
	}
    
    if (bLoadingCompleted) {
        if (bEnterForeground) {
            unscheduleAllSelectors();
            CCDirector::sharedDirector()->replaceScene(PopLayer::scene());
        }
        
        return;
    }
    
    int loaded = 0;
    if (loadingQueue && loadingQueue->count() > 0) {
        FOREACH(LoadingAction*, action, loadingQueue){
            if (action->isDone()) {
                loaded++;
            }
        }
    }
    
    curPngLoadingNum = loaded;
    bLoadingCompleted = (curPngLoadingNum == totalPngNum);
    
    
    if (loadingQueue && loadingQueue->count() > 0)
    {
        for (int i=0; i<loadingQueue->count(); i++) {
            LoadingAction* action = (LoadingAction*)loadingQueue->objectAtIndex(i);
            if (i == 0) {
                if (!action->isDone()) {
                    if (action->isNeedSynCall()) {
                        action->synAction();
                    }
                    break;
                }
            }else{
                LoadingAction* preAction = (LoadingAction*)loadingQueue->objectAtIndex(i-1);
                if (preAction->isDone() && !action->isDone()) {
                    if (action->isNeedSynCall()) {
                        action->synAction();
                    }
                    break;
                }
            }
        }
    }
}

void HLoadingWindow::RemoveAllImages()
{
	
}

void HLoadingWindow::PromptError()
{
	
}


void HLoadingWindow::buttonCallback(CCObject* pSender)
{

    
}


////----

PlistLoadingAction::PlistLoadingAction()
: m_plist(NULL)
, m_texture(NULL)
, m_image(NULL)
{
    
}

PlistLoadingAction::~PlistLoadingAction()
{
    CC_SAFE_RELEASE(m_plist);
    CC_SAFE_RELEASE_NULL(m_texture);
    CC_SAFE_RELEASE_NULL(m_image);
}

PlistLoadingAction* PlistLoadingAction::create(const char* plist, CCSpriteFrameCache* frameCache)
{
    PlistLoadingAction* ac = new PlistLoadingAction;
//    ac->autorelease();
    CC_AUTO_RELEASE(ac);
    ac->setPlistFile(CCString::create(plist));
    ac->m_frameCache = frameCache == NULL ? CCSpriteFrameCache::sharedSpriteFrameCache() : frameCache;
    
    return ac;
}

void PlistLoadingAction::asynAction()
{
//    if (m_texture) {
//        m_frameCache->addSpriteFramesWithFile(m_plist->getCString(), m_texture);
//    }
//    
//    setNeedAsynCall(false);
//    setNeedSynCall(true);
    
}

void PlistLoadingAction::synAction()
{
//    g_SourceCache->addSpriteFramesWithPList(m_plist->getCString());
    setDone(true);
}

void PlistLoadingAction::begin()
{
    setNeedSynCall(true);
    
//    m_fullPngPath = m_fullPlistPath;
//    m_fullPngPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(m_plist->getCString());
//    
//    // remove .xxx
//    size_t startPos = m_fullPngPath.find_last_of(".");
//    m_fullPngPath = m_fullPngPath.erase(startPos);
//    
//    // append .png
//    m_fullPngPath = m_fullPngPath.append(".png");
//    
//    CCTextureCache::sharedTextureCache()->addImageAsync(m_fullPngPath.c_str(),
//                                                        this, callfuncO_selector(PlistLoadingAction::loadedTexture));
}

void PlistLoadingAction::loadedTexture(CCTexture2D* tex)
{
//    setTexture(tex);
//    setNeedAsynCall(true);
}


//------



ImageFileLoadingAction::ImageFileLoadingAction()
{
    
}

ImageFileLoadingAction::~ImageFileLoadingAction()
{
    
}

ImageFileLoadingAction* ImageFileLoadingAction::create(const char* file)
{
    ImageFileLoadingAction* ac = new ImageFileLoadingAction;
//    ac->autorelease();
    CC_AUTO_RELEASE(ac);
    ac->m_fullImagePath = file; //CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(file);
    return ac;
}

void ImageFileLoadingAction::begin()
{
//    CCTextureCache::sharedTextureCache()->addImageAsync(m_fullImagePath.c_str(),
//                                                        this, callfuncO_selector(ImageFileLoadingAction::loadedTexture));
    
    HThreadTextureCache::getInstance()->loadTexture(this, m_fullImagePath.c_str(), new loadingimage());

//    setNeedSynCall(true);
}

void ImageFileLoadingAction::asynAction()
{
    
}
void ImageFileLoadingAction::synAction()
{
    
//    getCurrBag()->textureWithName(m_fullImagePath.c_str());
    setDone(true);
}

void ImageFileLoadingAction::loadedTexture(CCTexture2D* tex)
{
    setDone(true);
}





