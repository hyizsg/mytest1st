#ifndef _LOADING_LAYER_H
#define _LOADING_LAYER_H

#include <map>
#include "cocos2d.h"
//#include "PListCollect.h"
//#include "CCMWSprite.h"

using namespace cocos2d;
using namespace std;

class LoadingAction;

class HLoadingWindow: public HWindow
{
    HSINGLETON_OBJECT(HLoadingWindow);
    
public:
	static CCScene* scene();
    
    CC_SYNTHESIZE_RETAIN(CCArray*, loadingQueue, LoadingQueue);
    CC_SYNTHESIZE_BOOL(bool, bEnterForeground, EnterForeground);
    
    void pushAction(LoadingAction* action);
    void start();
    void end();
    
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    CREATE_FUNC(HLoadingWindow);
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    
    typedef HRootLayer super;
    
private:
	void LoadingData(HThread *); //run it in a working thread
	void ScheduleUpdateLoadingLabel(float dt);
    void ScheduleCreateSpritesAfterLoadingData(float dt);
	void RemoveAllImages();

	void PromptError();
	void buttonCallback(CCObject* pSender);
private:
    CCLabelTTF* m_pLoadingTip;
    CCProgressTimer* m_pLoadingLine;
    
    int curPngLoadingNum;
	int totalPngNum;

	bool bLoadingCompleted;

	int error;
    
	string errorMsg;
	CCLabelTTF* errorPrompt;
  
};

class PopLayer : public CCLayer {
    
    
public:
    static CCScene* scene(float dt = 0.5)
    {
        CCScene* scene = CCScene::create();
        CCScene* fade = CCTransitionFade::create(dt, scene);
        PopLayer* layer = PopLayer::create();
        scene->addChild(layer);
        
        layer->setContentSize(CCSizeZero);
        scene->setContentSize(CCSizeZero);
        
        return fade;
    }

    
    CREATE_FUNC(PopLayer);
    
    virtual void onEnterTransitionDidFinish()
    {
        CCLayer::onEnterTransitionDidFinish();
        this->schedule(schedule_selector(PopLayer::onPop));
    }
    
    void onPop(float dt){
        unscheduleAllSelectors();
        CCDirector::sharedDirector()->popScene();
    }
};


class LoadingAction : public CCObject {
    
    
public:
    virtual void begin() = 0;
    virtual void asynAction() = 0;
    virtual void synAction() = 0; 
    
    CC_SYNTHESIZE_BOOL(bool, m_needAsynCall, NeedAsynCall);
    CC_SYNTHESIZE_BOOL(bool, m_needSynCall, NeedSynCall);
    CC_SYNTHESIZE_BOOL(bool, m_isDone, Done);
    
    virtual ~LoadingAction() {}
    LoadingAction(): m_needAsynCall(false), m_needSynCall(false), m_isDone(false){}

};

class DismissAction : public LoadingAction {
    
public:
    typedef enum{
        Self, All
    }HDisMissType;
    
public:
    virtual void begin() { setNeedSynCall(true); }
    virtual void asynAction() {}
    virtual void synAction() {
        m_disLayer->setDisableAnimInOut(true);
        m_disType == Self ? m_disLayer->dismissRootLayer() : m_disLayer->dismissAllLayers();
        setDone(true);
    }
    
    static DismissAction* create(HRootLayer* layer, HDisMissType type = Self)
    {
        DismissAction* diss = new DismissAction;
//        diss->autorelease();
        CC_AUTO_RELEASE(diss);
        diss->m_disLayer = layer;
        diss->m_disType = type;
        return diss;
    }
    
protected:
    
    HRootLayer* m_disLayer;
    HDisMissType m_disType;
};


class PlistLoadingAction : public LoadingAction {
    
    
public:
    PlistLoadingAction();
    virtual ~PlistLoadingAction();
    
    static PlistLoadingAction* create(const char* plist, CCSpriteFrameCache* frameCache = NULL);
    
    virtual void begin();
    virtual void asynAction();
    virtual void synAction();
    
    void loadedTexture(CCTexture2D* tex);
    
protected:
    CC_SYNTHESIZE_RETAIN(CCString*, m_plist, PlistFile);
    CC_SYNTHESIZE_RETAIN(CCTexture2D*, m_texture, Texture);
    CC_SYNTHESIZE_RETAIN(CCImage*, m_image, Image);
    
protected:
    string m_fullPlistPath;
    string m_fullPngPath;
    
    CCSpriteFrameCache* m_frameCache;
    
};

class ImageFileLoadingAction : public LoadingAction {
    
    
public:
    ImageFileLoadingAction();
    virtual ~ImageFileLoadingAction();
    
    static ImageFileLoadingAction* create(const char* file);
    
    virtual void begin();
    virtual void asynAction();
    virtual void synAction();
    
    void loadedTexture(CCTexture2D* tex);
    
    struct loadingimage : public HSettingFun {
        virtual void operator() (CCObject* target, CCObject* tex) {
            ((ImageFileLoadingAction*) target)->loadedTexture((CCTexture2D*)tex);
        };
        HCREATE_FUNC(loadingimage);
    };
    
protected:
    string m_fullImagePath;
};

template <typename T>
class CCBLoadingAction : public LoadingAction {
    
    
public:
    static CCBLoadingAction* create(HLoadingWindow* loading)
    {
        CCBLoadingAction<T> * la = new CCBLoadingAction<T>;
//        la->autorelease();
        CC_AUTO_RELEASE(la);
        la->m_curHLoadingWindow = loading;
        la->m_node = NULL;
        la->n = 0;
        return la;
    }
    
    virtual void begin(){ setNeedSynCall(true); }
    virtual void asynAction() {  }
    virtual void synAction()
    {
        if (m_node == NULL) {
            
            m_node = T::create();
            m_node->retain();
        }
        
        if (m_curHLoadingWindow->isEnterForeground()) {
            m_node->setDisableAnimInOut(true);
            m_node->presentRootLayer();
            m_node->setDisableAnimInOut(false);
            
            setDone(true);
            m_node->release();
        }
    }
    
protected:
    HLoadingWindow* m_curHLoadingWindow;
    T* m_node;
    
    int n ;
};


template <typename T>
class CellLoadingAction : public LoadingAction {
    
    
public:
    static CellLoadingAction* create()
    {
        CellLoadingAction<T> * la = new CellLoadingAction<T>;
//        la->autorelease();
        CC_AUTO_RELEASE(la);
        return la;
    }
    
    virtual void begin(){ setNeedSynCall(true); }
    virtual void asynAction() {  }
    virtual void synAction()
    {
        T* node = popCell<T>();
        node->visit();
        setDone(true);
    }
};

#endif
