//
//  HLayerWithConfigButton.h
//  card
//
//  Created by zhou gang on 13-7-19.
//
//

#ifndef __card__HLayerWithConfigButton__
#define __card__HLayerWithConfigButton__

class HLayerWithConfigButton : public HWindow{
    
public:
    
    typedef HLayerWithConfigButton theClass;
    typedef HWindow super;
    
    HLayerWithConfigButton();
    virtual ~HLayerWithConfigButton();
    
    virtual bool init();
    virtual void notifyUserInfo(CCObject* obj);
    
    virtual void onEnter();
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    
    static void setTouchPriorityEx(CCNode* node);
    
    CLICK_SEL_DELARE(onCardGroupClick);
    CLICK_SEL_DELARE(onAddActiveClick);
    CLICK_SEL_DELARE(onShopClick);
    
public:
    __assign CCControlButton* m_pBtnCardGroup;
};

class HLayerWithTabButton : public HWindow {
    
    
public:
    typedef HLayerWithTabButton theClass;
    typedef HWindow super;
    
    HLayerWithTabButton();
    virtual ~HLayerWithTabButton();
    
    virtual bool init();
    virtual void resetUI();
    
    virtual void setCurrentTabIndex(int idx);
    virtual int getCurrentTabIndex() { return m_nSelectTabIndex; }
    virtual bool onTabButtonChanged(CCControlButton* sender, int idx){ return true; };
    virtual CCControlButton* getCurrentTab();
    virtual CCControlButton* getTabByIndex(int idx);
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    
    CLICK_SEL_DELARE(onBtnTabClick);
    
public:
    __assign CCNode* m_pGroupNode;
    __assign int m_nSelectTabIndex;
    
    
    
};

#endif /* defined(__card__HLayerWIthConfigButton__) */
