//
//  HNewbieStart.h
//  card
//
//  Created by zhou gang on 13-7-25.
//
//

#ifndef __card__HNewbieStart__
#define __card__HNewbieStart__

#define ACTION_SETTING_ORIGINICON       2306
#define ACTION_REPLAY_LEVEL             1205


class HNewbieStart : public HNewbieGuide , public HpCharaInstObserver {
    HUICLASS_DELARE(HNewbieStart, HNewbieGuide);
    
public:
    
    virtual bool init();
    void beginMaskToGuide(int idx);
    void onMaskFadeInEnd();
    void onMaskFadeOutEnd();
    
    void beginMaskToStory();
    void onMaskFadeInStroy();
    void onMaskFadeOutStroy();
    
    void beginMaskToReplay();
    void onMaskFadeInReplay();
    void onMaskFadeOutReplay();
    
    
    virtual void clear() {}
    virtual void showChatDlg(bool bShow);
    virtual void onNewbieActionEnd(CCAction* action);
    virtual void onAnimaEnd(HAnimaCommand* cmd);
    
    
    void onBattleDelay();
    void onBattleFadeEnd();
    void onLastInfoShowEnd();
    
    virtual void actionOnAnimationEnd(HpAnimation* p_ani, HpCharaInst* p_sender);
    virtual void actionOnCustomEvent(CCString* p_event, HpCharaInst* p_sender);
    
    
    void notifySaveIcon(CCObject * obj);
    void notifyReplaylRequest(CCObject* obj);
    
    CLICK_SEL_DELARE(onOKClick);
    CLICK_SEL_DELARE(onSelectIconClick);
    
public:
    __assign CCLayerColor* m_pMaskLayer;
    __assign HRichSprite* m_pIcon[2];
    
    __assign CCNode* m_pSelectIconNode;
    __assign CCSprite* m_pLightBg;
    __assign CCNode* m_pGuideNode;
    
    __assign HRichSprite* m_pGuideBg;
    __assign HRichLabelTTF* m_pLastTipInfo;
    __assign CCControlButton* m_pSelectBtn[3];
    
    __assign int m_selectIndex;
};

#endif /* defined(__card__HNewbieStart__) */


