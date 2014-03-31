//
//  Haypi-JSBCmd.cpp
//  MoonWarriors
//
//  Created by jim kaden on 13-4-27.
//
//

#include "Haypi-JSBCmd.h"
//#include "Haypi-JSBObject.h"
#include "cocos2dxframework.h"
#include "NetManager.h"
#include "Base.h"

HaypiJSBCmd::HaypiJSBCmd(CCDictionary* para, JSObject* callback, char* func)
{
    request = NULL;
    response = NULL;
    funcName = NULL;
    _actionKey = 0;
    if ( para )
    {
        request = para;
        request->retain();
        _actionKey = request->m_uID;
//        _actionKey = ((CCString*)request->objectForKey(std::string("ACTION_KEY")))->intValue();
    }
    if ( func )
        funcName = strdup(func);
    callbackPtr = callback;
}


HaypiJSBCmd::~HaypiJSBCmd()
{
    
    if ( request )
        request->release();
    if ( response )
        free(response);
    if ( funcName )
        free(funcName);
}

void HaypiJSBCmd::send()
{
    // to do: implement
//    callback_JSB(0,0,"received this data");
//    callback(request);
//    Helper_sendCmd(request);
    CCLOG("Sending command from JSB\n");
    int action = ((CCString*)request->objectForKey(std::string("ACTION")))->intValue();
    haypi::HNetManager::getInstance()->postRequest(action, request, this, true,0, HNET_MODE_SOCKET);
}
void HaypiJSBCmd::onDataReceived(int, CCDictionary* ret)
{
    callback(ret);
}

void HaypiJSBCmd::callback(CCDictionary *response_)
{
    // to do: implement
    if ( response_ == NULL )
        return ;
    if ( funcName == NULL )
        return ;
    std::string str = haypi::dictionaryToJSON(response_);
    response = strdup(str.c_str());
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();

    jsval data = c_string_to_jsval(cx, response);
    
    JSBool ok = JS_AddValueRoot(cx, &data);
    if (!ok)
    {
        CCLOG("scheduleFunc: Root value fails.");
        return;
    }

    jsval jsThisObj = OBJECT_TO_JSVAL(callbackPtr);
    
    //delete by zg
//    ScriptingCore::getInstance()->executeFunctionWithOwner(jsThisObj, funcName, data);
    
    JS_RemoveValueRoot(cx, &data);
}

