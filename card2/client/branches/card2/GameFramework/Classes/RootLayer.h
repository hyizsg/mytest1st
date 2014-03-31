#ifndef _ROOT_LAYER_H_
#define _ROOT_LAYER_H_

#define HCLICKSHRESHOLD     10

HNAMESPACE_BEGIN

class HTouchEnabledLayerDelegate {
public:
    virtual void onClickInTouchLayer(const CCPoint &pos) = 0;
};

typedef void (CCObject::*SEL_HTutorialEndDismiss)(CCNode *);
#define htutorialenddismiss_selector(_HANDLER) (SEL_HTutorialEndDismiss)(&_HANDLER)

class CC_DLL HTouchEnabledLayerColor: public CCLayerColor, public HTimerDelegate {
    CC_SYNTHESIZE(HTouchEnabledLayerDelegate *, m_pDelegate, Delegate);
    CC_SYNTHESIZE(bool, m_bTipAnimation, TipAnimation);
public:
    HTouchEnabledLayerColor();
    virtual ~HTouchEnabledLayerColor() { HTimerManager::getInstance()->unregisterTimer(m_pTimer); m_pTimer->release();  CC_SAFE_DELETE(m_pBakNodeList); }
    
    static HTouchEnabledLayerColor *create(const ccColor4B& color, float w, float h);
    static HTouchEnabledLayerColor *create();
    void updatePriority(CCNode *node);
    CCObject *updatePriorityEx(int command, CCNode *node);
    int getPriority(CCNode *node);
    void setPriority(CCNode *node, int priority);
    void show();
    void hide();
    
    void presentNode(CCNode *node);
    void dismissNode(CCNode *node, CCObject *pTarget = NULL, SEL_HTutorialEndDismiss notify = NULL, bool immediately = false);
    void dismissAllNodes();
    
    virtual void onEnter();
    virtual void onExit();
    virtual void setParent(CCNode *pParent) {
        CCLayerColor::setParent(pParent);
        setTouchEnabled(true);
    }
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
        bool bRet = isTouchEnabled() && isVisible();
        if (bRet) {
            m_iTouchStatus = HTOUCHSTATUS_BEGIN;
            m_ptTouchBegin = pTouch->getLocation();// convertTouchToNodeSpace(pTouch);
        }
        return bRet;
    }
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
        m_iTouchStatus = HTOUCHSTATUS_MOVE;
    }
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
        if (m_iTouchStatus == HTOUCHSTATUS_NONE) return;
        
        CCPoint ptTouchEnd = pTouch->getLocation();// convertTouchToNodeSpace(pTouch);
        float xOff = ptTouchEnd.x - m_ptTouchBegin.x;
        float yOff = ptTouchEnd.y - m_ptTouchBegin.y;
        if ((xOff >= -HCLICKSHRESHOLD) && (xOff <= HCLICKSHRESHOLD) && (yOff >= -HCLICKSHRESHOLD) && (yOff <= HCLICKSHRESHOLD)) {
//            if (m_pDelegate) {
//                CCPoint *pos = new CCPoint(convertToNodeSpace(ptTouchEnd));
//                HTimerManager::getInstance()->asyncProcess(HInvocation::create(this, hinvocation_selector(HTouchEnabledLayerColor::onAsyncTouch), 0, pos));
//                pos->release();
//            }
        }
        m_iTouchStatus = HTOUCHSTATUS_NONE;
    }
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {
        m_iTouchStatus = HTOUCHSTATUS_NONE;
    }
    virtual void onTimeOut(int gid, int count);
    void setTipString(CCLabelTTF *label, const char *str, bool oneByOne = false);
private:
    CCObject *onAsyncTouch(int command, CCObject *param) {
        if (m_bTipAnimation) {
            HTimerManager::getInstance()->unregisterTimer(m_pTimer);
            m_bTipAnimation = false;
            if (m_pTipLabel) m_pTipLabel->setString(m_str.c_str());
        } else {
            m_pDelegate->onClickInTouchLayer(*(CCPoint *)param);
        }
        return NULL;
    }
    
    class HEndDismissNode: public CCObject {
        CC_SYNTHESIZE_RETAIN(CCObject*, m_pTarget, Target);
        CC_SYNTHESIZE(SEL_HTutorialEndDismiss, m_pAction, Action);
        CC_SYNTHESIZE_RETAIN(CCNode *, m_pNode, Node);
    public:
        HEndDismissNode(CCObject *target, SEL_HTutorialEndDismiss action, CCNode *node): m_pTarget(NULL), m_pNode(NULL) {
            setTarget(target);
            setAction(action);
            setNode(node);
        }
        ~HEndDismissNode() { setTarget(NULL); setNode(NULL); }
        static HEndDismissNode *create(CCObject *target, SEL_HTutorialEndDismiss action, CCNode *node) {
            HEndDismissNode *pRet = new HEndDismissNode(target, action, node);
//            pRet->autorelease();
            CC_AUTO_RELEASE(pRet);
            return pRet;
        }
    };
    CCObject *dismissNodeEx(int command, HEndDismissNode *notify);
    CCObject *dismissAllNodesEx(int command, CCObject *param);
    
    std::string m_str;
    int m_strAdderPos;
    CCLabelTTF *m_pTipLabel;
    HTimer *m_pTimer;
    int m_iTouchStatus;
    CCPoint m_ptTouchBegin;
    class HBakNodeInfo: public CCObject {
    public:
        HBakNodeInfo(CCNode *node, CCNode *parent, CCPoint pos): m_pNode(node), m_pParent(parent), m_ptPos(pos) { m_pPriorities = new CCArray(2); m_iIndex = parent->getChildren()->indexOfObject(node); m_fScaleX = node->getScaleX(); m_fScaleY = node->getScaleY(); }
        virtual ~HBakNodeInfo() { CC_SAFE_DELETE(m_pPriorities); }
        static HBakNodeInfo *create(CCNode *node, CCNode *parent, CCPoint pos) { HBakNodeInfo *pRet = new HBakNodeInfo(node, parent, pos); CC_AUTO_RELEASE(pRet); return pRet; }
        void addPriority(CCNode *node, int priority) { m_pPriorities->addObject(HBakProrityInfo::create(node, priority)); }
        CCNode *m_pNode;
        int m_iIndex;
        CCNode *m_pParent;
        CCPoint m_ptPos;
        float m_fScaleX;
        float m_fScaleY;
        CCArray *m_pPriorities;
    public:
        class HBakProrityInfo: public CCObject {
        public:
            HBakProrityInfo(CCNode *node, int priority): m_pNode(node), m_iPriority(priority) {}
            static HBakProrityInfo *create(CCNode *node, int priority) { HBakProrityInfo *pRet = new HBakProrityInfo(node, priority); CC_AUTO_RELEASE(pRet); return pRet; }
            CCNode *m_pNode;
            int m_iPriority;
        };
    };
    CCArray *m_pBakNodeList;
    void bakAllPriorities(HBakNodeInfo *info, CCNode *node);
    void restoreAllPriorities(HBakNodeInfo *info);
};

class HTouchEnabledLayerColorLoader : public CCLayerColorLoader {
public:
    virtual ~HTouchEnabledLayerColorLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HTouchEnabledLayerColorLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HTouchEnabledLayerColor);
};

class CC_DLL HRootLayer: public HCommonLayer, public CCEditBoxDelegate, public CCBSelectorResolver, public CCBMemberVariableAssigner,public HCountDownDelegate/*, public CCNodeLoaderListener */{
    HCLASSTYPE(HRootLayer, HCommonLayer);
    CC_SYNTHESIZE_RETAIN(CCBAnimationManager *, m_pCCBAnimationManager, CCBAnimationManager);
    CC_SYNTHESIZE_READONLY(HTouchEnabledLayerColor *, m_pTutorialNode, TutorialNode);
    CC_SYNTHESIZE_READONLY(CCSize, m_szDesign, DesignSize);
    CC_SYNTHESIZE(bool, m_bIsFullScreen, IsFullScreen);
public:
    HRootLayer();
    virtual ~HRootLayer();
    
    void needTutorial(bool show);
    
    /*virtual */CCNode *readNodeGraphFromFile(const char* pCCBFileName, bool originalSize = false);
    void AddJSCCBNode(const char *pCCBFileName, CCNode *node, bool originSize);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);

//    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

    void setTitle(const char *pTitle);
    virtual void onBackClick(CCObject*, CCControlEvent);
    virtual void onCloseClick(CCObject*, CCControlEvent);

    void presentRootLayer(bool inQueue = false, bool inUI = true); //inUI: true (in ui layer), false (in game decoration layer)
    void dismissRootLayer(bool inUI = true);
    
    void dismissAllLayers(bool inUI = true);
    
    const char* secondsToString(int seconds);
    const char* secondsToStringNoDay(int seconds);
    
    virtual void onSearchPort();
    
    virtual void onCloseSearch();
    
    virtual void onDispatchFleet(int index);
    
    virtual void onDispatchFleetCancel(int index);
    
    virtual void setParentVisible(bool isVisible);
    CC_SYNTHESIZE(int,m_nRemoteState,RemoteState);
    virtual void onCountTick(HCountDown *sender, int seconds);
    
    CCObject *onOpenKeyboard(int command, CCEditBox *editbox);
    
    void registerEditbox(CCEditBox *editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxReturn(CCEditBox* editBox);
    virtual void onShowEditbox(bool show);
    
    virtual void adjustPostionAndScale(CCNode* node, float scaleX, float scaleY);
    CCNode *getCCBNode() { return m_pCCbNode; }
    
    void updateAndAdjust(CCNode *node);
protected:
    CCLabelTTF *m_pLabelTitle;
    CCControlButton *m_pBtnBack;
    CCControlButton *m_pBtnClose;
    CCArray *m_pEditBoxList;
    HViewPage *m_pViewPage;
    
    CCArray* m_pIgnoreNodeArr;
    CCNode* m_pCCbNode;
    
    void updateAndAdjust(CCNode *node, float scaleX, float scaleY);
    void relayoutAsHorizontal(CCArray *nodes, CCPoint basePos, int interval = 20 * CC_CONTENT_SCALE_FACTOR());
    void relayoutAsVertical(CCArray *nodes, CCPoint basePos, int interval = 20 * CC_CONTENT_SCALE_FACTOR());
public:
    static bool m_sbRatioOfEquality;
    static bool m_sbAdjustForDifferentScreent;
protected:
    float m_fScaleX;
    float m_fScaleY;
};

HNAMESPACE_END

#endif // _ROOT_LAYER_H_
