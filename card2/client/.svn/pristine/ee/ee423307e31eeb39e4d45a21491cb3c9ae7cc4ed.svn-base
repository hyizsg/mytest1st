//
//  Haypi-JSBEngine.cpp
//  GameFramework
//
//  Created by jim kaden on 13-5-7.
//  Copyright (c) 2013年 cxj. All rights reserved.
//

#include "Haypi-JSBEngine.h"

#include "cocos2d.h"
#include "ScriptingCore.h"
// delete by zg
//#include "generated/cocos2dx.hpp"
#include "cocos2d_specifics.hpp"
#include "js_bindings_ccbreader.h"
#include "Haypi-JSB.h"
#include "SimpleAudioEngine.h"
#include "UpdateManager.h"
#include "jsb_haypi_ui.h"
#include "jsb_cocos2dx_extension_manual.h"

std::vector<sc_register_sth> _registrationList;
char defaultJs[255] = {0};

void HaypiJSBScriptEngine::startScriptEngine()
{
    if ( CCScriptEngineManager::sharedManager()->getScriptEngine() != NULL )
        return;
    
    ScriptingCore* sc = ScriptingCore::getInstance();
    
    //delete by zg
    
//    sc->addRegisterCallback(register_all_cocos2dx);
//    sc->addRegisterCallback(register_cocos2dx_js_extensions);
//    sc->addRegisterCallback(register_all_cocos2dx_extension);
//    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
//    sc->addRegisterCallback(register_CCBuilderReader);
//    sc->addRegisterCallback(register_haypi_framework_js_extensions);
//    sc->addRegisterCallback(register_all_haypi_ui);
    
    for (std::vector<sc_register_sth>::iterator it = _registrationList.begin(); it != _registrationList.end(); it++) {
        sc_register_sth callback = *it;
        sc->addRegisterCallback(callback);
    }
    
    sc->start();
    
    CCScriptEngineManager::sharedManager()->setScriptEngine(sc);
}

void HaypiJSBScriptEngine::addRegisterCallback(sc_register_sth callback)
{
    _registrationList.push_back(callback);
}

void HaypiJSBScriptEngine::runJavaScript(char* name)
{
    startScriptEngine();
    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->runScript(name);
}

void HaypiJSBScriptEngine::endScriptEngine()
{
    CCScriptEngineManager::sharedManager()->purgeSharedManager();
}

void HaypiJSBScriptEngine::setDefaultJS(char *name)
{
    int length = strlen(name);
    memcpy(defaultJs, name, length);
    defaultJs[length] = '\0';
}