//
//  HGameManager.h
//  card2
//
//  Created by zhou gang on 14-2-10.
//
//

#ifndef __card2__HGameManager__
#define __card2__HGameManager__

#include "headers.h"

class  HGameManager: public HGameDelegate
{
    HSINGLETON_OBJECT(HGameManager);
    
public:
    
    virtual void preloadLoaders();
    virtual void initGame();
    virtual void enterBackground();
    virtual void enterForeground();
    
    virtual void onNeedHeartBeat();
    virtual void onNeedUpdateData();
    virtual void onNeedReLogin();
    virtual void onNetworkFailed();
    virtual void onForceCloseByServer();
    virtual void onNeedAccount();
    virtual void startGame();
    virtual void initDirector();
    
    virtual void onMessageBox(const char *message, const char *titile);
    virtual void receiveDataTimeout(int command);
    virtual void onDataReceived(int command, CCDictionary *result);
    virtual void preProcessNetResult(int command, CCDictionary *result);
    
    virtual void onUpdateFinished();
    
    void initCCBLoader();
    void loadConfig();
    void initResources();
    
    void GetUserInfo();
    bool ParseUserInfo(CCDictionary *result);
    
};

#endif /* defined(__card2__HGameManager__) */
