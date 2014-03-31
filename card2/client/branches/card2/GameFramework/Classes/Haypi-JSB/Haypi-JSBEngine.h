//
//  Haypi-JSBEngine.h
//
//  Created by jim kaden on 13-5-7.
//

#ifndef __HAYPI_JSB_ENGINE_H__
#define __HAYPI_JSB_ENGINE_H__
#import "ScriptingCore.h"

class HaypiJSBScriptEngine
{
public:
    static void startScriptEngine();
    static void runJavaScript(char* name);
    static void endScriptEngine();
    static void addRegisterCallback(sc_register_sth callback);
    static void setDefaultJS(char *name);
    static void runJsStr(char *str);
};

#endif /* defined(__GameFramework__Haypi_JSBEngine__) */
