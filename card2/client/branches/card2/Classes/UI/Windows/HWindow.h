//
//  HWindow.h
//  card
//
//  Created by zhou gang on 13-7-11.
//
//

#ifndef __card__HWindow__
#define __card__HWindow__

class HRootScene;
class HDialog;

class HWindow : public HRootLayer, public HCommonObject {
    
public:
    CC_SYNTHESIZE_BOOL(bool, m_bEnableAnimaInOut, EnableAnimaInOut);
    
    HCLASSTYPE(HWindow, HRootLayer);
    typedef HRootLayer super;
    
public:
    
    HWindow();
    virtual ~HWindow();
    
    virtual bool init();
    virtual bool loadPlistCCBI(const char* ccbi);
    
    virtual void loadPlist();
    virtual void disposPlist();
    
    virtual void release(void);
    
    virtual void presentRootLayer(bool bAnima = true); 
    virtual void dismissRootLayer(bool bAnima = true);
    virtual void replaceRootLayer(bool bAnima = true);
    virtual void dismissLater(bool banima=false, float delay=0.3);
    virtual void dismissAllLayers(bool bAnima = false);
    
    virtual void onPresented();
    virtual void onDismissed();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    
    virtual void onEnterForeground();
    virtual void onEnterBackground();
    
    virtual void onBackClick(CCObject*, CCControlEvent);
    virtual void onCloseClick(CCObject*, CCControlEvent);
    
    virtual bool isDialog();
    
    HRootScene* scene();
    static bool isDialog(CCObject* obj);
    
    static HWindow* current();
    CREATE_FUNC(HWindow);
    
    CCNode *readNodeGraphFromFile(const char* pCCBFileName, bool originalSize = false);

};


#endif /* defined(__card__HWindow__) */
