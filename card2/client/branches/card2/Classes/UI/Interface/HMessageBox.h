//
//  HMessageBox.h
//  card
//
//  Created by zhou gang on 13-6-15.
//
//

#ifndef __card__HMessageBox__
#define __card__HMessageBox__


//#define HMB_SHOW_SYNCH      0   // 同步返回
#define HMB_SHOW_ASYN       0   // 异步返回
#define HMB_SHOW_ONFREE     1   // 空闲时显示

typedef enum {
    HMB_OK = 1,
    HMB_CANCEL = 2,
    HMB_OKCANCEL = HMB_OK | HMB_CANCEL,
}HMBBTNTYPE;


class HMessageBox;

class HMessageDelegate {
    
public:
    virtual void onOK(HMessageBox* sender) {}
    virtual void onCancel(HMessageBox* sender) {}
};

class HMessageBox : public HDialog {
    HUICLASS_DELARE(HMessageBox, HDialog)
    
public:
    virtual bool init() { return super::init(); }
    virtual bool init(const char* msg, const char* title, int button, int style, HMessageDelegate* delegate);
    
    // show msg
    static HMessageBox* show(const char* msg, const char* title=NULL, int button=HMB_OK, HMessageDelegate* delegate=NULL, int style=HMB_SHOW_ASYN, int mid = 0);
    static HMessageBox* show(const char* msg, const char* title, int button, CCCallFunc* pOkCallBack, CCCallFunc* pCancelCallBack = NULL);
    
    static HMessageBox *show(int errorcode, const char *defaultvalue, bool usedefault);
    
    // free setting
    static void setFree(bool free);
    static bool isFree();
    
public:
    CC_SYNTHESIZE_RETAIN(CCString*, m_pMessage, Message);
    CC_SYNTHESIZE(HMessageDelegate*, m_pDelegate, Delegate);
    
    void onOkClick(CCObject*, CCControlEvent);
    void onCancelClick(CCObject*, CCControlEvent);
    void setOkButonTitle(const char* title);

    virtual void presentRootLayer(bool inQueue = false, bool inUI = true); //inUI: true (in ui layer), false (in game decoration layer)
    
    virtual void showAction(CCNode* pActionNode);
    
protected:
    
    void present();
    
    int showOnSynchr();
    int showOnFree();
    int showOnAsyn();
    
protected:
    __assign CCLabelTTF * m_pLabelMessage;
    __assign CCControlButton *m_pBtnOk;
    __assign CCControlButton *m_pBtnCancel;
    __assign CCNode* m_pActionNode;
    
    __assign int m_showStyle;
    __assign bool m_bHandled;
    __assign bool m_bUseFree;
    __assign int m_retValue;
    
    __retain CCCallFunc * m_pOkCallBack;
    __retain CCCallFunc * m_pCancelCallBack;
    
    
    static bool s_free;
    static CCArray* msgList;
    
};

#endif /* defined(__card__HMessageBox__) */
