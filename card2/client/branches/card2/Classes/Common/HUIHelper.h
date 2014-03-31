//
//  HUIHelper.h
//  card
//
//  Created by zhou gang on 13-6-4.
//
//

#ifndef __card__HUIHelper__
#define __card__HUIHelper__

typedef enum {
    CC_COLOR_YELLOW,
    CC_COLOR_GREEN,
    CC_COLOR_BLUE,
    CC_COLOR_MEAT,
    CC_COLOR_GREY,
    CC_COLOR_DARKBROWN,
    CC_COLOR_RED,
    CC_COLOR_TAB,
    CC_COLOR_BLACK,
    CC_COLOR_WHITE    
} CC_UI_COLOR;

#define HC_COLOR_YELLOW         ccc3(254, 174, 2)
#define HC_COLOR_GREEN          ccc3(223, 254, 0)
#define HC_COLOR_BLUE           ccc3(16, 195, 239)
#define HC_COLOR_MEAT           ccc3(249, 187, 106)
#define HC_COLOR_GREY           ccc3(127, 133, 137)
#define HC_COLOR_DARKBROWN      ccc3(42, 31, 25)
#define HC_COLOR_RED            ccc3(234, 44, 0)
#define HC_COLOR_TAB            ccc3(179, 140, 90)
#define HC_COLOR_BLACK          ccc3(0,0,0)
#define HC_COLOR_WHITE          ccc3(255, 255, 255)
#define HC_COLOR_MEATWHITE      ccc3(209, 192, 165)
#define HC_COLOR_PURPLE         ccc3(245, 84, 255)
#define HC_COLOR_YELLOW3        ccc3(255, 195, 37)

#define HC_NORMAL_ALPHA         "normal_alpha_hd.png"

class HCommonCellDelegate
{
public:
    virtual void onCellClick(HTableViewCell *cell) {}
    virtual void onCellClick(HTableViewCell *cell, int param) {}
};

class HUIHelper : public CCObject, public HMessageDelegate, public HpCharaInstObserver, public HCommonObject {
    HSINGLETON_OBJECT(HUIHelper);
    
public:
    
    static void onAddActive();
    static void showReward(CCDictionary* reward, HMessageDelegate* delegate);
    static void showLevelUp(int lv);
    
    static void dumpAllTexture();
    
    virtual void onOK(HMessageBox* sender);
    virtual void onCancel(HMessageBox* sender);
    
    
    static HpCharaInst* playUIAnima(const char* name, CCNode* world);
    static HpCharaInst* playUIEffect(const char* name, CCNode* world, bool autodestroy = true);
    
    static HpCharaInst* playUIAnimWithTag(const char *name, CCNode *world, int tag = HPANIMATION_ACTION_TAG);
    static void removeUIAnimByTag(CCNode *world, int tag=HPANIMATION_ACTION_TAG);
    
    static void clearRewardInfo() { HC_SET(getInstance()->m_lastRewardMsg, NULL); HC_SET(getInstance()->m_lastRewardInfo, NULL); HC_SET(getInstance()->m_heavenRewardInfo, NULL); }
    static const char* lastRewardString() { return  getInstance()->m_lastRewardMsg ?  getInstance()->m_lastRewardMsg->getCString() : "" ; } ;
    static CCDictionary* getLastRewardInfo() {return getInstance()->m_lastRewardInfo; };
    static void setLastRewardInfo(CCDictionary* value){ HC_SET(getInstance()->m_lastRewardInfo, value); }
    static int getLastWinner() {return getInstance()->m_lastWinner;}
    static void setLastWinner(int value){ getInstance()->m_lastWinner = value;}
    static CCDictionary* getExtraRewardInfo() {return getInstance()->m_heavenRewardInfo; };
    static void setHeavenRewardInfo(CCDictionary* value){ HC_SET(getInstance()->m_heavenRewardInfo, value); }
    static void parseRewardInfo(CCDictionary* info);
    
    static void setLabelColor(CCLabelTTF* label, CC_UI_COLOR color);
    static ccColor3B getColor(CC_UI_COLOR color);
    
    static void setButtonString(const char *str, CCControlButton* btn);
    static void setButtonTitleImg(const char* img, CCControlButton *btn);
    static void setButtonImg(const char *img, CCControlButton *btn);
    static void setButtonPic(const char *pic, CCControlButton *btn);
    
    static void setStars(CCNode *stars, int starcount, int starmax = MAX_STAR);
    static void setCardConfigButton(CCControlButton* btn);
    static void addChild(CCNode* parent, CCNode* child);
    static void addChild(CCNode* parent, CCNode* child, int zOrder);
    
    void notifyGetCardGroup(CCObject*);
    static void showPlayerCardGroup(CCDictionary* info);
    static void showPlayerCardGroup(int uid, int battleType, int OtherID = 0);
    
    static void adjustScale(CCSprite* sprite, float scale = 2);
    static CCNode* getFirstChildWithDeep(CCNode* pNode, int deep = 1);
    static void addToTopMost(CCNode* node);
    
    static void enableMusicBackGround(bool enable);
    static void enableMusicEffect(bool enable);
    
    virtual void actionOnAnimationEnd(HpAnimation* p_ani, HpCharaInst* p_sender);
    virtual void actionOnCustomEvent(CCString* p_event, HpCharaInst* p_sender);
    
    static bool checkSeniorCard(const vector<int>& cards, CCCallFunc* callback, const char* msg = NULL);
    static bool checkSeniorMagic(const vector<int>& magics, CCCallFunc* callback, const char* msg = NULL);
    
    static const char* getDataString(time_t nTime);
    static void clipLayer(HRootLayer* layer);
    static const ccColor3B colorLevel(int lv);
    
    static bool checkBuyActiveGuide(HRootLayer* parent, CCNode* addbtn);
    static const char* rank2str(int rank, int limitRank);
    
protected:
    
    map<void*, string> messageMap;
    
    CCString* m_effectId;
    CCString* m_lastRewardMsg;
    CCDictionary* m_lastRewardInfo;
    CCDictionary* m_heavenRewardInfo;
    
    int m_lastWinner;
    HPlayer* m_player;
};

#endif /* defined(__card__HUIHelper__) */
