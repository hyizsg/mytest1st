//
//  HNewbieGuide.h
//  card
//
//  Created by zhou gang on 13-7-3.
//
//

#ifndef __card__HNewbieGuide__
#define __card__HNewbieGuide__

#define ACTION_NEWBIE_LOG               2402


class HNewbieGuideDelegate {
    
    
public:
    virtual void onNewbieGuideEnd(int id, CCObject* obj) = 0 ;
};

class HNewbieChatDialog;

#define kNewbieActionTag    166

class HNewbieGuide : public HWindow , public HRGBObject , public HAnimaDelegate, public HAnimaObject {
    HUICLASS_DELARE(HNewbieGuide, HWindow)
    
public:
    typedef enum {
        GF_Arrow, GF_TipBox,
    }HGuideFlag;
    
    typedef struct {
        int id;
        vector<int> step;
    }HNewbieLog;
    
public:

    // tag <==> id, default step is 1 in configing
    static HNewbieGuide* create(int tag, int step = 1, HNewbieGuideDelegate* delegate = NULL);
    
    static bool loadLog();
    static void reset();
    static void log(int tag);
    static void log(int tag, int step);
    static void logToSvr(int tag, int step);
    static bool isPass(int tag);
    static bool isPass(int tag, int step);
    static bool isRuning();
    static void updateLog(CCArray* array);
    
    virtual bool init();
    virtual void onExit();
    
    void showIn(HRootLayer* parent);
    void hiddenAfterActionWithoutAnima();
    void hiddenInActionWithoutAnima();
    void hidden();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void onAnimaEnd(HAnimaCommand* cmd);

    
public:
    void begin();
    void end();
    virtual void clear();
    
    void visit(HGuideFlag flag, CCNode* node, const CCSize& exSize);
    void visit(HGuideFlag flag, float width,float height,CCPoint point);
    
    virtual CCAction* runAction(CCAction* action);
    virtual void onNewbieActionEnd(CCAction* action);
    
    virtual void showChatDlg(bool bShow);
    
    CLICK_SEL_DELARE(onSkipClick);
    
public:
    __retain CCSprite* m_pBackgrd;
    __retain CCRenderTexture *m_pTarget; // render texture
    __retain CCSprite* m_pArrow;
    __assign CCSprite * m_pMask;
    __assign CCLayerColor* m_pTipMask;
    __assign CCLayerColor* m_pTipBox;
    
    __retain CCArray* m_pActions;
    
    __assign HNewbieChatDialog* m_pChatDlg;
    __assign CCControlButton* m_pBtnSkip;
    
    __assign HNewbieGuideDelegate* m_delegate;
    
public:
    
    static HNewbieLog s_newbieLog;
    static HNewbieGuide* s_newbieSingle;
};

class HNewbieChatDialog : public CCNode
{
public:
    union{
        struct{
            __assign HRichSprite* iconLeft;
            __assign HRichSprite* iconRight;
        };
        __assign HRichSprite* icon[2];
    };
    __assign CCLabelTTF* msg;
    
    HCREATE_FUNC(HNewbieChatDialog);
};

class HNewbieChatDialogLoader : public CCNodeLoader {
public:
    virtual ~HNewbieChatDialogLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HNewbieChatDialogLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HNewbieChatDialog);
};

#endif /* defined(__card__HNewbieGuide__) */
