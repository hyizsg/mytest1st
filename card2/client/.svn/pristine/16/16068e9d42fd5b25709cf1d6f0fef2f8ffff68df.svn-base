//
//  HRootScence.h
//  card
//
//  Created by zhou gang on 13-7-12.
//
//

#ifndef __card__HRootScence__
#define __card__HRootScence__

class HWindow;
class HMaskWindow;
class HDialog;


class HMaskProtocol : public CCLayerColor
{
public:
    virtual void maskWithInOut(HWindow* pIn, HWindow* pOut, float fDuration, bool bCleanup) = 0;
    virtual void beginMask() = 0;
    
};

class HRootScene : public CCScene {
    
    
public:
    static bool isAddSlib;
    
    HRootScene();
    virtual ~HRootScene();
    
    virtual bool init();
    virtual void visit();
    
    static HRootScene* create();
    
    HWindow* getGameShowLayer() { return m_pGameNode; }
    HWindow* getUIShowLayer() { return m_pUINode; }
    HWindow* getTopShowLayer() { return m_pTopNode; }
    
    HWindow* getRunningLayer() {return m_pRunningWindow;}
    
    void presentWindow(HWindow* window, bool bAnima);
    void dissmisWindow(HWindow* window, bool bAnima);
    void dissmisAllWinodw(bool bAnima);
    void replaceWindow(HWindow* window, bool bAnima);
    
    void presentDialog(HDialog* dlg, bool bAnima);
    void presentDialog(HWindow* parent, HDialog* dlg, bool bAnima);
    void dissmisDialog(HDialog* dlg, bool bAnima);
    
    void pressentGame(CCNode* game);
    
    void setNextWindow();
    void finish();
    void updateAllWindows(HWindow* outWnd = NULL);
    
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    static HRootScene* current();
    static HWindow* currentWindowByType(const char* className);
    
    void startAIV();
    void stopAIV();
    
    static bool isEnterBackgroud() { return s_bEnterBackgroud; }
    static void setEnterBackgroud(bool backgroud);
    
protected:
    __assign HWindow* m_pRunningWindow;
    __assign HWindow* m_pNextWindw;
    __assign bool m_bSendCleanupToWindow;
    
protected:
    __assign CCNode* m_pScaleNode;
    __assign HWindow* m_pGameNode;
    __assign HWindow* m_pUINode;
    __assign HWindow* m_pTopNode;
    __assign HWindow* m_pLoading;
    __assign HMaskProtocol* m_pMaskNode;
    
    static HRootScene* s_pCurrentScene;
    static bool s_bEnterBackgroud;
    
public:
    const static float gfDurationFadeInOut;
};


#endif /* defined(__card__HRootScence__) */
