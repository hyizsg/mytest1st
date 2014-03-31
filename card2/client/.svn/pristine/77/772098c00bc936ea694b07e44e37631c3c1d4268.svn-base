//
//  HMessageBox.cpp
//  card
//
//  Created by zhou gang on 13-6-15.
//
//

#include "headers.h"
#include "HLanguage.h"

HMessageBox::HMessageBox()
: m_pLabelMessage(NULL)
, m_pMessage(NULL)
, m_pDelegate(NULL)
, m_bHandled(false)
, m_showStyle(0)
, m_bUseFree(false)
, m_retValue(HMB_OK)
, m_pOkCallBack(NULL)
, m_pCancelCallBack(NULL)
, m_pActionNode(NULL)
{
    setDisableAnimInOut(true);
    setIsFullScreen(false);
}

HMessageBox::~HMessageBox()
{
    CC_SAFE_RELEASE_NULL(m_pOkCallBack);
    CC_SAFE_RELEASE_NULL(m_pCancelCallBack);
    CC_SAFE_RELEASE(m_pMessage);
}

BEGIN_PLIST(HMessageBox)

END_PLIST()


BEGIN_MEMBER_MAP(HMessageBox)
    MEMBER(m_pLabelMessage)
    MEMBER(m_pBtnOk)
    MEMBER(m_pBtnCancel)
    MEMBER(m_pActionNode)
END_MEMBER_MAP()

BEGIN_CLICK_MAP(HMessageBox)
    CLICK(onOkClick)
    CLICK(onCancelClick)
END_CLICK_MAP()

bool HMessageBox::init(const char* msg, const char* title, int buttons, int style, HMessageDelegate* delegate)
{
    m_pLabelMessage->setString(msg);
    if (title && strlen(title) > 0) m_pLabelTitle->setString(title);
    m_pDelegate = delegate;
    m_showStyle = style;
    setMessage(CCString::create(msg));
    
    if (HNewbieGuide::isPass(214, 5) && !HNewbieGuide::isPass(214, 6)) {
        HNewbieGuide* guide = HNewbieGuide::create(214, 6);
        if (guide) {
            guide->showIn(this);
            guide->runAction(HGuideClick::create(6, m_pBtnOk));
            guide->hiddenAfterActionWithoutAnima();
        }
    }
 
    m_pBtnOk->setVisible(buttons != HMB_CANCEL);
    m_pBtnCancel->setVisible(buttons != HMB_OK);
    
    m_pBtnOk->setTouchPriority(-500);
    m_pBtnCancel->setTouchPriority(-500);
    
    setTouchMode(kCCTouchesOneByOne);
    setTouchPriority(-200);
    
    if (buttons == HMB_OK || buttons == HMB_CANCEL) {
        m_pBtnOk->setPositionX(240);
        m_pBtnCancel->setPositionX(240);
    }
    
    
    return true;
}

HMessageBox* HMessageBox::show(int errorcode, const char *defaultvalue, bool usedefault)
{
    const char *str = HLanguage::getError(errorcode, defaultvalue, usedefault);
    return HMessageBox::show(str);
}

HMessageBox* HMessageBox::show(const char* msg, const char* title, int button, HMessageDelegate* delegate, int style, int mid)
{
    HMessageBox* box = HMessageBox::create();
    box->init(msg, title, button, style, delegate);
    box->setTag(mid);
    box->present();
    
    return box;
}

HMessageBox* HMessageBox::show(const char* msg, const char* title, int button, CCCallFunc* pOkCallBack, CCCallFunc* pCancelCallBack)
{
    HMessageBox* box = show(msg, title, button);
    HC_SET(box->m_pOkCallBack, pOkCallBack);
    HC_SET(box->m_pCancelCallBack, pCancelCallBack);
    return box;
}

void HMessageBox::present()
{
    msgList->addObject(this);
    
    switch (this->m_showStyle) {
//        case HMB_SHOW_SYNCH:
//            return box->showOnSynchr();
            
        case HMB_SHOW_ASYN:
            this->showOnAsyn();
            break;
        case HMB_SHOW_ONFREE:
            this->m_bUseFree = true;
            HAnimaCenter::getInstance()->runAction(CCCallFunc::create(this, callfunc_selector(HMessageBox::showOnFree)));
            break;
        default:
            break;
    }
}

int HMessageBox::showOnSynchr()
{
    setFree(s_free);
    
//    while (!m_bHandled) {
//        HThread::sleepWithMilliSeconds(10);
//    }
//    
    return m_retValue;
}

int HMessageBox::showOnFree()
{
    m_bUseFree = true;
    setFree(s_free);
    return -1;
}

int HMessageBox::showOnAsyn()
{
    setFree(s_free);
    
    return -1;
}

void HMessageBox::setOkButonTitle(const char* title)
{
//    HUIHelper::setButtonString(title, m_pBtnOk);
}


void HMessageBox::onOkClick(CCObject*, CCControlEvent) {
    HGameManager::getInstance()->playSoundEffect(HMUSIC_BUTTON);
    if (!m_bHandled) {
        m_retValue = HMB_OK;
        m_bHandled = true;
        dismissRootLayer();
        
        retain(); autorelease();
        msgList->removeObject(this);
        
        if (m_pDelegate) m_pDelegate->onOK(this);
        if (m_pOkCallBack) m_pOkCallBack->execute();
        
        setFree(s_free);
    }
}

void HMessageBox::onCancelClick(CCObject*, CCControlEvent) {
    HGameManager::getInstance()->playSoundEffect(HMUSIC_BUTTON);
    if (!m_bHandled) {
        m_retValue = HMB_CANCEL;
        m_bHandled = true;
        dismissRootLayer();
        
        retain(); autorelease();
        msgList->removeObject(this);
        
        if (m_pDelegate) m_pDelegate->onCancel(this);
        if (m_pCancelCallBack) m_pCancelCallBack->execute();
        
        setFree(s_free);
    }
}


bool HMessageBox::s_free = true;
CCArray* HMessageBox::msgList = new CCArray;

void HMessageBox::setFree(bool var)
{
    s_free = var;
    
    FOREACH(HMessageBox*, msg, msgList) {
        if (msg->getParent()) {
            break;
        }else if(!msg->m_bUseFree){
            msg->presentRootLayer();
            break;
        }else if(s_free){
            msg->presentRootLayer();
            break;
        }
    }
}

bool HMessageBox::isFree()
{
    return s_free;
}

void HMessageBox::showAction(CCNode* pActionNode)
{
    if (pActionNode) {
        pActionNode->setScale(0.2);
        CCScaleTo* scale1 = CCScaleTo::create(0.1, 0.8);
        CCScaleTo* scale2 = CCScaleTo::create(0.5, 1);
        m_pActionNode->runAction(CCSequence::create(scale1, CCEaseElasticOut::create(scale2, 0.5), NULL));
    }
}


void HMessageBox::presentRootLayer(bool inQueue, bool inUI)
{
//    CCLOG("MessageBox -- present: 0x%x: %s", this, m_pMessage ? m_pMessage->getCString() : "");
    
    super::presentRootLayer();
    showAction(m_pActionNode);
    
    return;

}


