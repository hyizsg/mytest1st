//
//  Haypi-JSBCmd.h
//  MoonWarriors
//
//  Created by jim kaden on 13-4-27.
//
//

#ifndef __Haypi_JSBCmd__
#define __Haypi_JSBCmd__

#include <typeinfo>
#include "ScriptingCore.h"
#include "js_bindings_config.h"
#include "spidermonkey_specifics.h"
//#include "js_bindings_core.h"
//#include "js_bindings_system_functions.h"
#include "js_manual_conversions.h"
#include "jsapi.h"
#include <map>
#include <stdlib.h>
#include "cocos2dxframework.h"
class HaypiJSBCmd : public haypi::HObject
{
public:
    JSObject* callbackPtr;
    CCDictionary* request;
    char* response;
    char* funcName;
private:
    int _actionKey;
public:
    HaypiJSBCmd(CCDictionary* param, JSObject* ptr, char* func);
    ~HaypiJSBCmd();
    int getActionKey(){return _actionKey;}
    void send();
    void callback(CCDictionary* response);
    virtual void onDataReceived(int, CCDictionary*);
};


#endif /* defined(__MoonWarriors__Haypi_JSBCmd__) */
