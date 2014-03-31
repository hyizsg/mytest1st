//
//  HDataCenter.h
//  card
//
//  Created by zhou gang on 13-4-16.
//
//

#ifndef __card__HDataCenter__
#define __card__HDataCenter__


#include "NetManager.h"

class HDataRequest : public HObject {
    HCLASSTYPE(HDataRequest, HObject);
    
public:
    HDataRequest();
    virtual ~HDataRequest();
    virtual void onDataReceived(int command, CCDictionary *result);    
    
    static HDataRequest* create(int command, CCDictionary* param, bool startaiv=true, bool showerror=true)
    {
        HDataRequest* request = new HDataRequest;
        request->setCommondID(command);
        request->setParam(param);
        request->setNeedStartAIV(startaiv);
        request->setNeedShowError(showerror);
        CC_AUTO_RELEASE(request);
        return request;
    }
    
    CC_SYNTHESIZE(int , m_commondID, CommondID);
    CC_SYNTHESIZE_RETAIN(CCDictionary*, m_param, Param);
    CC_SYNTHESIZE_RETAIN(CCDictionary*, m_result, Result);
    CC_SYNTHESIZE_BOOL(bool, m_bError, NotifyError);
    CC_SYNTHESIZE_BOOL(bool, m_bIgnoreDup, IgnoreDuplicaiton);
    CC_SYNTHESIZE_BOOL(bool, m_bStartAIV, NeedStartAIV);
    CC_SYNTHESIZE_BOOL(bool, m_bNeedShowError, NeedShowError);
    CC_SYNTHESIZE(int, m_errorCode, ErrorCode);
};


class HDataCenter  {
    
public:
    static void post(HDataRequest* request);
};


enum {
    ERROR_TIMEOUT  = 100,
    ERROR_CANNOTLOGIN = 2000,
    ERROR_USER_NEED_LOGIN = 10011,
    ERROR_USER_GOLD_NOT_ENOUGH = 30021,
    ERROR_BATTLE_ACTIVE_NOT_ENOUGH = 40006,
    ERROR_VIP_NEED = 230004,
    ERROR_VIP_NOT_ENOUGH = 230005
};


#define ACTION_UPDATE_USERINFO_STR      "userInfoChaged"

#define NOTIFY_ADD_USERINFO()             NOTIFY_ADD_OBSERVER(theClass::notifyUserInfo, ACTION_UPDATE_USERINFO_STR)
#define NOTIFY_REMOVE_USERINFO()          NOTIFY_REMOVE_OBSERVER(ACTION_UPDATE_USERINFO_STR);


#endif /* defined(__card__HDataCenter__) */
