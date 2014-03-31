//
//  HNewbieAction.h
//  card
//
//  Created by zhou gang on 13-7-4.
//
//

#ifndef __card__HNewbieAction__
#define __card__HNewbieAction__

class HNewbieAction : public CCActionInstant, public CCTouchDelegate {
    
    
public:
    HNewbieAction(){ setTag(kNewbieActionTag); }
    virtual ~HNewbieAction() {};
    
    virtual bool init() { return true ; }
    virtual void stop(void)
    {
        HNewbieGuide* guide = dynamic_cast<HNewbieGuide*>(m_pTarget);
        if(guide) guide->onNewbieActionEnd(this);
    }
    
    virtual void step(float dt){}
    virtual void update(float fdelta) {}
    
    CC_SYNTHESIZE(int, m_newbieStep, NewbieStep);
};

class HChatContent {
    
    
public:
    int id;
    int icon;
    string msg;
};

class HGuideTipBox : public CCObject {

public:
    CCSize size;
    CCPoint point;
    HNewbieGuide::HGuideFlag flag;
    
public:
    static HGuideTipBox* create(CCNode* node, const CCSize& exSize = CCSizeMake(1, 1));
    static HGuideTipBox* create(const CCSize& size, const CCPoint& point);
    
};

class HGuideArrow : public HGuideTipBox {
    
public:
    static HGuideArrow* create(CCNode* node, const CCSize& exSize = CCSizeMake(10, 10));
    static HGuideArrow* create(const CCSize& size, const CCPoint& point);
    
};

class HGuideTipBoxDelegate {
    
    
public:
    
    HGuideTipBoxDelegate() : m_tips(NULL) {}
    virtual ~HGuideTipBoxDelegate() { CC_SAFE_RELEASE_NULL(m_tips); }
    
    virtual void addTipBox(int key, HGuideTipBox* tip);
    virtual void addTipBox(int key, CCNode* node, const CCSize& exSize = CCSizeMake(1, 1));
    virtual void addTipArrow(int key, CCNode* node, const CCSize& exSize = CCSizeMake(10, 10));
    
protected:
    
    __retain CCDictionary* m_tips;
    
};

class HNewbieChatDialog;

class HGuideChat : public HNewbieAction, public HGuideTipBoxDelegate {
    
    
public:
    static HGuideChat* create(int beginStep, int endStep);
    static HGuideChat* create(int beginStep, int endStep, HGuideTipBox* tip);
    
    CREATE_FUNC(HGuideChat);
    
    virtual bool init();
    virtual bool initWithNewbieStep(int step);
    
    virtual bool isDone(void);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void step(float dt);
    virtual void stop(void);
    
    
    void showChatByStep(int step);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) { return true; };
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;
    
    
    CC_SYNTHESIZE_BOOL(bool, m_bAutoDone, AutoDone);
    
protected:
    __assign HNewbieChatDialog* m_chatDlg;
    __assign HChatContent m_content;
    
    __assign const char* m_chat;
    __assign int m_curStep;
    __assign int m_pos;
    
    __assign float m_delta;
    __assign bool m_isDone;
    
    __assign int m_begin;
    __assign int m_end;
};

class HGuideClick : public HNewbieAction, public HGuideTipBoxDelegate  {
    
    
public:
    static HGuideClick* create(int setp, CCNode* pClickTarget, const CCSize& exSize = CCSizeMake(10, 10));
    
    virtual void stop();
    virtual bool isDone(void) { return m_isDone; }
    virtual void startWithTarget(CCNode *pTarget);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
protected:
    __assign CCNode* m_pClickTarget;
    __assign bool m_isDone;
    __assign CCSize m_exSize;
};

class HGuideReward : public HNewbieAction {
    
    
public:
    static HGuideReward* create(int step);
    
    HGuideReward();
    ~HGuideReward();
    
    virtual bool isDone(void) { return m_isDone; }
    virtual void startWithTarget(CCNode *pTarget);
    
    void showReward(CCLabelTTF* label, int i);
    void notifyGuideReward(CCObject* obj);
    
protected:
    __assign bool m_isDone;
    
    typedef HGuideReward theClass;
};


#endif /* defined(__card__HNewbieAction__) */
