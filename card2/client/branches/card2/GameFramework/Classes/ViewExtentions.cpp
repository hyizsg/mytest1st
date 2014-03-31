
#include "cocos2dxframework.h"

#include "NetManager.h"
#include "GameScene.h"
#include "AppDelegate.h"

HNAMESPACE_BEGIN

static inline bool HColor3BEqual(ccColor3B a, ccColor3B b) {
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

static inline unsigned int HColor3BToInt(ccColor3B a) {
    return 0xFF000000 | (((unsigned int)a.r) << 16) | (((unsigned int)a.g) << 8) | (((unsigned int)a.b));
}

//HEditBox
HEditBox::HEditBox(): CCEditBox(), m_nFontSize(14), m_bCreated(false) {
//    m_pDict = new CCDictionary;
}

HEditBox::~HEditBox() {
//    delete  m_pDict;
}

bool HEditBox::initWithSizeAndBackgroundSprite(const CCSize& size, CCScale9Sprite* pNormal9SpriteBg) {
#ifdef HOS_APPLE
    return CCEditBox::initWithSizeAndBackgroundSprite(size, pNormal9SpriteBg);
#else
    if (CCControlButton::initWithBackgroundSprite(pNormal9SpriteBg)) {
        this->setPreferredSize(size);
        this->setPosition(ccp(0, 0));
//        this->addTargetWithActionForControlEvent(this, cccontrol_selector(CCEditBox::touchDownAction), CCControlEventTouchUpInside);
        return true;
    }
    return false;
#endif
}

//void HEditBox::setFontname(const char *pFontname) {
//    m_strFontname = pFontname;
//}

void HEditBox::setFontSize(int size) {
    m_nFontSize = size;
    CCEditBox::setFontSize(size);
}

void HEditBox::setContentSize(const CCSize& size) {
    CCEditBox::setContentSize(size);
    
    if (m_bCreated) {
        CCDictionary *dict = CCDictionary::create();
        CCArray *array = CCArray::create();
        dict->setObject(array, HVIEWKEY_ALL);
        array->addObject(toDictionary(HVIEWCMD_UPDATE));
        HNetManager::getInstance()->sendMessage(HVIEWCMD_UPDATE, dict);
    }
}

void HEditBox::setVisible(bool visible) {
    CCEditBox::setVisible(visible);
//    if (m_bVisible == visible) return;
    
    
    if (m_bCreated) {
        CCDictionary *dict = CCDictionary::create();
        CCArray *array = CCArray::create();
        dict->setObject(array, HVIEWKEY_ALL);
        int command = visible ? HVIEWCMD_SHOW : HVIEWCMD_HIDE;
        array->addObject(toDictionary(command));
        
        HNetManager::getInstance()->sendMessage(command, dict);
    }
}

void HEditBox::setText(const char* pText) {
    CCEditBox::setText(pText);
    if (m_strText == pText) return;
    
    
    if (m_bCreated) {
        CCDictionary *dict = CCDictionary::create();
        CCArray *array = CCArray::create();
        dict->setObject(array, HVIEWKEY_ALL);
        int command = HVIEWCMD_SETTEXT;
        array->addObject(toDictionary(command));
        
        HNetManager::getInstance()->sendMessage(command, dict);
    }
}

//void HEditBox::onEnter(void) {
//    CCEditBox::onEnter();
//}

void HEditBox::setTextEx(const char* pText) {
    if (m_strText == pText) return;
    CCEditBox::setText(pText);
}

void HEditBox::refresh() {
    
}

CCDictionary *HEditBox::toDictionary(int command) {
    CCDictionary *pRet = CCDictionary::create();
    pRet->setObject(HString::createWithInteger((int)this), HVIEWKEY_ID);
    pRet->setObject(HString::createWithInteger(HVIEWTYPE_EDITBOX), HVIEWKEY_TYPE);
    pRet->setObject(HString::createWithBoolean(isVisible()), HVIEWKEY_VISIBLE);
    
    do {
        if (command == HVIEWCMD_REMOVE) break;
        if (command == HVIEWCMD_GETTEXT) break;
        if (command == HVIEWCMD_SHOW) break;
        if (command == HVIEWCMD_HIDE) break;
        if (command == HVIEWCMD_SETTEXT) {
            if (m_strText.length() > 0) pRet->setObject(HString::create(m_strText.c_str()), HVIEWKEY_TEXT);
            break;
        }
            
        CCRect rect = AppDelegate::getInstance()->getGameManager()->rectToDeviceInPixels(this);
        pRet->setObject(HString::createWithInteger((int)rect.origin.x), HVIEWKEY_X);
        pRet->setObject(HString::createWithInteger((int)rect.origin.y), HVIEWKEY_Y);
        pRet->setObject(HString::createWithInteger((int)rect.size.width), HVIEWKEY_W);
        pRet->setObject(HString::createWithInteger((int)rect.size.height), HVIEWKEY_H);
        
        int feature = 0;
        switch (m_eEditBoxInputMode) {
            case kEditBoxInputModeSingleLine:
                feature |= HVIEWFEATURE_SINGLINE;
                break;
            case kEditBoxInputModeEmailAddr:
                feature |= HVIEWFEATURE_SINGLINE | HVIEWFEATURE_EMAIL;
                break;
            case kEditBoxInputModeNumeric:
                feature |= HVIEWFEATURE_SINGLINE | HVIEWFEATURE_NUMERIC;
                break;
            default:
                break;
        }
        switch (m_eEditBoxInputFlag) {
            case kEditBoxInputFlagPassword:
                feature |= HVIEWFEATURE_SINGLINE | HVIEWFEATURE_PASSWORD;
                break;
                
            default:
                break;
        }
        if (feature != 0) pRet->setObject(HString::createWithInteger(feature), HVIEWKEY_FEATURE);
        
        if (m_strText.length() > 0) pRet->setObject(HString::create(m_strText.c_str()), HVIEWKEY_TEXT);
        if (m_strPlaceHolder.length() > 0) pRet->setObject(HString::create(m_strPlaceHolder.c_str()), HVIEWKEY_HINT);
        
        //if (m_pFontName && (m_pFontName->length() > 0)) pRet->setObject(HString::create(m_pFontName->c_str()), HVIEWKEY_FONTNAME);
//        if (m_nFontSize != 20) {
//            pRet->setObject(HString::createWithInteger(m_nFontSize), HVIEWKEY_FONTSIZE);
//        }
        pRet->setObject(HString::createWithInteger((int)(m_nFontSize * CC_CONTENT_SCALE_FACTOR())), HVIEWKEY_FONTSIZE);
        //if (!HColor3BEqual(m_colText, ccWHITE)) {
            pRet->setObject(HString::createWithInteger(HColor3BToInt(m_colText)), HVIEWKEY_FONTCOLOR);
        //}
        //if (!HColor3BEqual(m_colPlaceHolder, ccGRAY)) {
            pRet->setObject(HString::createWithInteger(HColor3BToInt(m_colPlaceHolder)), HVIEWKEY_HINTCOLOR);
        //}
        if (m_nMaxLength > 0) {
            pRet->setObject(HString::createWithInteger(m_nMaxLength), HVIEWKEY_MAXLEN);
        }
    } while (0);
    m_bCreated = true;
    return pRet;
}

//HViewPage
HViewPage::HViewPage() {
    m_pViews = new CCArray(8);
    HViewPageManager::getInstance()->registerViewPage(this);
}

HViewPage::~HViewPage() {
    HViewPageManager::getInstance()->unregisterView(this);
    delete m_pViews;
}

void HViewPage::registerView(HEditBox *view) {
    if (CC_INVALID_INDEX == m_pViews->indexOfObject(view)) {
        m_pViews->addObject(view);
    }
}

void HViewPage::unregisterView(HEditBox *view) {
    for (int i = m_pViews->count() - 1; i >= 0; --i) {
        if (view == m_pViews->objectAtIndex(i)) {
            m_pViews->removeObjectAtIndex(i);
            break;
        }
    }
}

void HViewPage::create() {
    CCDictionary *dict = toDictionary(HVIEWCMD_CREATE);
    if (dict) {
        HNetManager::getInstance()->sendMessage(HVIEWCMD_CREATE, dict);
    }
}

void HViewPage::remove() {
    CCDictionary *dict = toDictionary(HVIEWCMD_REMOVE);
    if (dict) {
        HNetManager::getInstance()->sendMessage(HVIEWCMD_REMOVE, dict);
    }
}

void HViewPage::show() {
    CCDictionary *dict = toDictionary(HVIEWCMD_SHOW);
    if (dict) {
        HNetManager::getInstance()->sendMessage(HVIEWCMD_SHOW, dict);
    }
}

void HViewPage::hide() {
    CCDictionary *dict = toDictionary(HVIEWCMD_HIDE);
    if (dict) {
        HNetManager::getInstance()->sendMessage(HVIEWCMD_HIDE, dict);
    }
}

void HViewPage::refreshView(HEditBox *view) {
    CCDictionary *dict = CCDictionary::create();
    CCArray *array = CCArray::create();
    dict->setObject(array, HVIEWKEY_ALL);
    array->addObject(view->toDictionary(HVIEWCMD_UPDATE));
    HNetManager::getInstance()->sendMessage(HVIEWCMD_UPDATE, dict);
}

void HViewPage::refresh() {
    CCDictionary *dict = toDictionary(HVIEWCMD_UPDATE);
    if (dict) {
        HNetManager::getInstance()->sendMessage(HVIEWCMD_UPDATE, dict);
    }
}

CCDictionary *HViewPage::toDictionary(int command) {
    int count = m_pViews->count();
    if (count < 1) return NULL;
    CCDictionary *pRet = CCDictionary::create();
    CCArray *array = CCArray::create();
    pRet->setObject(array, HVIEWKEY_ALL);
    for (int i = 0; i < m_pViews->count(); ++i) {
        HEditBox *view = (HEditBox *)m_pViews->objectAtIndex(i);
        array->addObject(view->toDictionary(command));
    }
    HLOGI("views: %s", AppDelegate::getInstance()->getGameManager()->dictionaryToJSON(pRet).c_str());
    return pRet;
}

bool HViewPage::checkView(int viewID, const char *text) {
    for (int i = m_pViews->count() - 1; i >= 0; --i) {
        HEditBox *view = (HEditBox *)m_pViews->objectAtIndex(i);
        if ((int)view == viewID) {
            HLOGI("HViewPage::checkView:id(%x),text(%s)", viewID, text);
            view->setText(text);
            if (view->getDelegate()) view->getDelegate()->editBoxEditingDidEnd(view);
            return true;
        }
    }
    return false;
}

bool HViewPage::setText(int viewID, const char *text) {
    for (int i = m_pViews->count() - 1; i >= 0; --i) {
        HEditBox *view = (HEditBox *)m_pViews->objectAtIndex(i);
        if ((int)view == viewID) {
            HLOGI("HViewPage::setText:id(%x),text(%s)", viewID, text);
            view->setTextEx(text);
            if (view->getDelegate()) view->getDelegate()->editBoxTextChanged(view, text);
            return true;
        }
    }
    return false;
}

//HViewPageManager
HSINGLETON_OBJECT_IMP(HViewPageManager);

HViewPageManager::HViewPageManager() {
    m_pViewPages = new CCArray(2);
}

HViewPageManager::~HViewPageManager() {
    delete m_pViewPages;
}

void HViewPageManager::registerViewPage(HViewPage *viewPage) {
    if (CC_INVALID_INDEX == m_pViewPages->indexOfObject(viewPage)) {
        m_pViewPages->addObject(viewPage);
    }
}

void HViewPageManager::unregisterView(HViewPage *viewPage) {
    for (int i = m_pViewPages->count() - 1; i >= 0; --i) {
        if (viewPage == m_pViewPages->objectAtIndex(i)) {
            m_pViewPages->removeObjectAtIndex(i);
            break;
        }
    }
}

void HViewPageManager::checkView(int viewID, const char *text) {
    for (int i = m_pViewPages->count() - 1; i >= 0; --i) {
        HViewPage *viewPage = (HViewPage *)m_pViewPages->objectAtIndex(i);
        if (viewPage->checkView(viewID, text)) break;
    }
}

void HViewPageManager::setText(int viewID, const char *text) {
    for (int i = m_pViewPages->count() - 1; i >= 0; --i) {
        HViewPage *viewPage = (HViewPage *)m_pViewPages->objectAtIndex(i);
        if (viewPage->setText(viewID, text)) break;
    }
}

//HPlatformViewManager
//HPlatformViewManager::HPlatformViewManager(): m_pOwner(NULL) {
//    
//}
//
//HPlatformViewManager::~HPlatformViewManager() {
//    
//}

HNAMESPACE_END
