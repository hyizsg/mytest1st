//
//  Haypi-JSBObject.h
//  MoonWarriors
//
//  Created by jim kaden on 13-4-27.
//
//
#ifndef __HAYPI_JSBOBJECT_H__
#define __HAYPI_JSBOBJECT_H__
#include <typeinfo>
#include "ScriptingCore.h"
#include "js_bindings_config.h"
#include "spidermonkey_specifics.h"
//#include "js_bindings_core.h"
//#include "js_bindings_system_functions.h"
#include "js_manual_conversions.h"
#include <map>
#include <stdlib.h>


#include "Haypi-JSBCmd.h"
#include "Haypi-JSB.h"

class HaypiNetCallback
{
public:
    HaypiNetCallback();
    ~HaypiNetCallback();
    
public:
    bool addCallback(std::string funcName, GS_Func);
    bool removeCallback(std::string funcName);
    GS_Func getCallback(std::string funcName);
    
    HaypiJSBCmd* getCommonHandler(){return _commandHandler;}
    bool setCommonhandler(HaypiJSBCmd*);
    
    long long getHashCode();
    long long getMemberID();
public:
    static HaypiNetCallback* sharedInstance();
    
private:
    void routine();
//    pthread_t _thread;
//    pthread_rwlock_t _rwLock;
    
protected:
    typedef std::map<int, int> ActionKeytoHashMap;
    typedef std::map<std::string, GS_Func> NetCallbackMap;
    typedef std::pair<std::string, GS_Func> NetCallbackPair;
    
    NetCallbackMap      _netCallbackMap;
    ActionKeytoHashMap  _netActionKeyMap;
    HaypiJSBCmd*        _commandHandler;
    
    
    friend void* HaypiNetCallback_routine(void* param);
};

extern void* HaypiNetCallback_routine(void* param);
extern bool callback_JSB(int actionkey, int action, CCDictionary* response);
extern char* Helper_createJsonWithAction(int action);
extern int Helper_getIntFromJson(const char* jsonStr, const char* key);
extern int Helper_getSocketHashCode();
extern int Helper_getSocketMemberID();
extern bool Helper_sendCmd(const char* request);
#endif
