
#include "cocos2dxframework.h"
#include "NetManager.h"
#include "Base.h"
#include "GameScene.h"
#include "AppDelegate.h"
//#include <time.h>

//#include "Haypi-JSBObject.h"

//USING_HNAMESPACE;

HNAMESPACE_BEGIN

//int secondsSince1970() {
//    time_t lTime;
//    time(&lTime);
//    return lTime;
//}
//
//const char *dateFormat(int format, int secsSince1970) {
//    return ctime(&secsSince1970);
//}

bool HNetManager::m_bDisableServerList = false;

void HNetManager::startHeartBeat() {
    m_iHeartBeatElapsed = m_iHeartBeatInterval;
    HTimerManager::getInstance()->registerTick(this);
}

void HNetManager::resetHeartBeat() {
    m_iHeartBeatElapsed = m_iHeartBeatInterval;
}

void HNetManager::onTick(int count) {
    --m_iHeartBeatElapsed;
    if (m_iHeartBeatElapsed < 1) {
        AppDelegate::getInstance()->getGameManager()->onNeedHeartBeat();
        m_iHeartBeatElapsed = m_iHeartBeatInterval;
    }
    onTimeOut(0, 1);
}

bool HNetManager::postRequest(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel, int netMode) {
#ifdef H_CLOSE_NET
    return false;
#endif
    if (netMode == HNET_MODE_DEFAULT) {
        netMode = m_bUseSocket ? HNET_MODE_SOCKET : HNET_MODE_HTTP;
    }
    HLOGI("Net mode %d, uid(0x%x), hash(0x%x)",netMode, m_pUID, m_pHash);
    
    CCDictionary *params = NULL;
    const char *json = this->createJsonWithAction(command);
    if (json) {
        params = dictionaryFromJSON(json, 0);
    }
    if (!params) {
        params = CCDictionary::create();
    }
    if (param) {
        CCArray *keys = param->allKeys();
        int count = param->count();
        for (int i = 0; i < count; ++i) {
            CCString *key = (CCString *)keys->objectAtIndex(i);
            params->setObject(param->objectForKey(key->m_sString), key->m_sString);
        }
    }
    int key = params->valueForKey("ACTION_KEY")->intValue();
    
    if (netMode == HNET_MODE_SOCKET) {
        params->removeObjectForKey("AUTH_KEY");
        params->removeObjectForKey("GAMEPLAY_ID");
        
        CCDictionary *dict = CCDictionary::create();
        if (m_pUID) dict->setObject(HString::create(m_pUID->m_sString), "DE_USER_ID");
        if (m_pHash) dict->setObject(HString::create(m_pHash->m_sString), "Hash");
        dict->setObject(HString::createWithInteger(1), "COM_TYPE");
        dict->setObject(HString::createWithInteger(command), "ACTION");
        
        AppDelegate::getInstance()->getGameManager()->updateNetDictionary(true, params, dict);
        dict->setObject(HString::create(dictionaryToJSON(params)), "DE_VALUE");
        postRequestEx(command, dict, delegate, ignoreDuplicaiton, commandLevel, HNET_MODE_SOCKET, key);
        resetHeartBeat();
        HLOGI("sendingWithSocket: over!");
        return true;
        
//        if (m_pUID && m_pHash) {
//        } else {
//            HNetManager::getInstance()->connectWithSocket();
//            return false;
//            if (!m_bEnableHttpReplaceSocket) {
//                HLOGI("sendingWithSocket: failed!");
//                return false;
//            }
//        }
    }
    
    params->setObject(HString::createWithInteger(commandLevel), "PackageLevel");
    params->setObject(HString::createWithInteger(0), "COM_TYPE");
    AppDelegate::getInstance()->getGameManager()->updateNetDictionary(false, params, NULL);
    postRequestEx(command, params, delegate, ignoreDuplicaiton, commandLevel, HNET_MODE_HTTP, key);
    HLOGI("sendingWithHttp: over!");
    
    return true;
}

void HNetManager::registerProtocolDelegate(int action, HObject *delegate) {
    for (int i = m_pProcotolDelegateStack->count() - 1; i >= 0; --i) {
        HProtocolDelegate *protocolDelegate = (HProtocolDelegate *)m_pProcotolDelegateStack->objectAtIndex(i);
        if ((protocolDelegate->getAction() == action) && (protocolDelegate->getDelegate() == delegate)) return;
    }
    m_pProcotolDelegateStack->addObject(HProtocolDelegate::create(action, delegate));
}

void HNetManager::unregisterProtocolDelegate(int action, HObject *delegate) {
    for (int i = m_pProcotolDelegateStack->count() - 1; i >= 0; --i) {
        HProtocolDelegate *protocolDelegate = (HProtocolDelegate *)m_pProcotolDelegateStack->objectAtIndex(i);
        if ((protocolDelegate->getAction() == action) && (protocolDelegate->getDelegate() == delegate)) {
            m_pProcotolDelegateStack->removeObjectAtIndex(i);
            return;
        }
    }
}

void HNetManager::onDataReceivedEx(int command, CCDictionary *result) {
    if (!result) {
    		AppDelegate::getInstance()->getGameManager()->receiveDataTimeout(command);
    		return;
    }
    switch (command) {
        case HPI_NOTIFICATION: {
            m_iVersion = result->valueForKey("Version")->intValue();
            m_iBVersion = result->valueForKey("BVersion")->intValue();
            CCDictionary *notifies = (CCDictionary *)result->objectForKey("Notify");
            if (notifies && (notifies->count() > 0)) {
                CCArray *keys = notifies->allKeys();
                int size = notifies->count();
                for (int i = 0; i < size; ++i) {
                    switch (((CCString *)keys->objectAtIndex(i))->intValue()) {
                        case 99: //new mail
                            break;
                        case 98: // private chat
                            break;
                        case 101: //system broadcast
                            break;
                        case 102: //system maintain
                            break;
                        default:
                            break;
                    }
                }
            }
        }
            break;
        default: {
            bool bProcessed = false;
            for (int i = m_pProcotolDelegateStack->count() - 1; i >= 0; --i) {
                HProtocolDelegate *protocolDelegate = (HProtocolDelegate *)m_pProcotolDelegateStack->objectAtIndex(i);
                if (protocolDelegate->getAction() == command) {
                    protocolDelegate->getDelegate()->onDataReceived(command, result);
                    bProcessed = true;
                    break;
                }
            }
            if (!bProcessed) {
                //callback_JSB(0, command, result);
                AppDelegate::getInstance()->getGameManager()->onDataReceived(command, result);
            }
        }
            break;
    }
}

HNAMESPACE_END
