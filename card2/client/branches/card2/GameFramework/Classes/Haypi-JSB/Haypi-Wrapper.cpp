//
//  Haypi-Wrapper.mm
//  Haypi-JSB
//
//  Created by jim kaden on 13-4-25.
//
//
#include <typeinfo>
#include <string>
#include "ScriptingCore.h"
#include "js_bindings_config.h"
#include "spidermonkey_specifics.h"
//#include "js_bindings_core.h"
//#include "js_bindings_system_functions.h"
#include "js_manual_conversions.h"
#include "Haypi-JSBObject.h"
#include "cocos2dxframework.h"
#include "Base.h"
//#ifdef __cplusplus
//extern "C" {
//#endif

int HaypiWrapper_sendCmd(char* context, JSObject* callbackPtr, const char* funcName)
{
    CCDictionary* dictCmd = haypi::dictionaryFromJSON(context, strlen(context));
    HaypiJSBCmd* cmd = new HaypiJSBCmd(dictCmd, callbackPtr, (char*)funcName);
    cmd->send();
    return 0;
}

int HaypiWrapper_setCommandHandler(JSObject* callbackPtr)
{
    HaypiJSBCmd* cmd = new HaypiJSBCmd(NULL, callbackPtr, (char*) "commandHandler");
    HaypiNetCallback::sharedInstance()->setCommonhandler(cmd);
    return 0;
}

char* HaypiWrapper_createJsonWithAction(int action)
{
    return Helper_createJsonWithAction(action);
}

long long HaypiWrapper_getHashCode()
{
    return HaypiNetCallback::sharedInstance()->getHashCode();
}

long long HaypiWrapper_getMemberID()
{
    return HaypiNetCallback::sharedInstance()->getMemberID();
}

char* HaypiWrapper_getNameByScreen(char* resourceName)
{
    std::string fileName = resourceName;
    if ( fileName.size() == 0 )
        return NULL;
    
    haypi::PHSCREENDATA pData = haypi::currentScreenData();

    std::string fileNameRet = fileName + pData->suffix;
    size_t size_dot ;
    if ( (size_dot = fileName.find(".")) != std::string::npos )
    {
        fileNameRet = fileName.substr(0, size_dot) + std::string("-") + std::string(pData->suffix) + fileName.substr(size_dot, fileName.size() - size_dot);
    }
    else
    {
        fileNameRet = fileName + std::string("-") + pData->suffix;
    }
    
    if ( CCFileUtils::sharedFileUtils()->fullPathForFilename(fileNameRet.c_str()) == fileNameRet )
    {
        if ( fileNameRet.data()[0] == '/')
        {
            if ( access(fileNameRet.c_str(), R_OK ) == 0 )
                return strdup(fileNameRet.c_str());
        }
    }
    return strdup(resourceName);
}


//#ifdef __cplusplus
//}
//#endif