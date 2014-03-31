//
//  HDataCenter.cpp
//  card
//
//  Created by zhou gang on 13-4-17.
//
//

#include "../headers.h"
#include "HDataCenter.h"

HDataRequest::HDataRequest()
: HObject()
, m_param(NULL)
, m_result(NULL)
, m_commondID(0)
, m_bError(false)
, m_bIgnoreDup(true)
, m_bNeedShowError(true)
, m_bStartAIV(true)
{
}

HDataRequest::~HDataRequest()
{
    CC_SAFE_RELEASE_NULL(m_param);
    CC_SAFE_RELEASE_NULL(m_result);
}

void HDataRequest::onDataReceived(int command, CCDictionary *result)
{
    //CHECK_ACTION_DIC(result);
    
    int errorcode = 0;
    int importmsg = 0;
    if (result == NULL) {   
        setNotifyError(true);
        errorcode = ERROR_TIMEOUT;
        //CCLOG("%d time out", command);
    }else if (PARSE_INT(result, "ACTION_COM") != 0) {
        setNotifyError(true);
        CCLOGERROR("Action %d error: %s", PARSE_INT(result, "ACTION"), PARSE_STR(result, "ExtraInfo")->getCString());
        
        errorcode = PARSE_INT(result, "ACTION_COM");
        importmsg = PARSE_INT(result, "S");
    } else
    {
        setNotifyError(false);
    }
    
    m_errorCode = errorcode;
    
    setResult(result);
    
    if (!m_bError) {
//        g_Game->ParseUserInfo(result);
    }
    
    if (m_bStartAIV) {
        HRootScene::current()->stopAIV();
    }
    CCNotificationCenter::sharedNotificationCenter()->postNotification(itoa(m_commondID), this);
//    if (errorcode != 0) {
//    switch (errorcode) {
//        case ERROR_USER_NEED_LOGIN:
//            HCommonErrorProcess::getInstance()->showNeedLogin();
//            break;
//        case ERROR_USER_GOLD_NOT_ENOUGH:
//            HCommonErrorProcess::getInstance()->showNeedGold();
//            break;
//        case ERROR_BATTLE_ACTIVE_NOT_ENOUGH:
//            HCommonErrorProcess::getInstance()->showNeedEnergy();
//            break;
//        case ERROR_VIP_NEED:
//            HCommonErrorProcess::getInstance()->showNeedVip();
//            break;
//        case ERROR_VIP_NOT_ENOUGH:
//            HCommonErrorProcess::getInstance()->showVipLevelLow();
//            break;
//        default:
//            if (m_bNeedShowError) {
//                HMessageBox::show(errorcode, result ? PARSE_STR(result, "ExtraInfo")->getCString() : "", importmsg);
//            }
//            break;
//    }
//    }
    release();
};

void HDataCenter::post(HDataRequest* request)
{
    if (request->isNeedStartAIV()) {
        HRootScene::current()->startAIV();
    }
    
    request->retain();
    g_Game->postRequest(request->getCommondID(), request->getParam(), request, request->isIgnoreDuplicaiton(), 0, HNET_MODE_SOCKET);
}
