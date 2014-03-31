//
//  Haypi-JSB.h
//  Haypi-JSB
//
//  Created by jim kaden on 13-4-25.
//
//

#ifndef __Haypi_JSB__
#define __Haypi_JSB__

#include <typeinfo>
#include "ScriptingCore.h"
#include "js_bindings_config.h"
#include "spidermonkey_specifics.h"
//#include "js_bindings_core.h"
//#include "js_bindings_system_functions.h"
#include "js_manual_conversions.h"


#ifdef __cplusplus
extern "C" {
#endif
    JSBool JSPROXY_sendCmd(JSContext *cx, uint32_t argc, jsval *vp);
    JSBool JSPROXY_setCommandHandler(JSContext *cx, uint32_t argc, jsval *vp);
    JSBool JSPROXY_getHashCode(JSContext *cx, uint32_t argc, jsval *vp);
    JSBool JSPROXY_getMemberID(JSContext *cx, uint32_t argc, jsval *vp);
    JSBool JSPROXY_createJsonWithAction(JSContext *cx, uint32_t argc, jsval *vp);
    JSBool JSPROXY_callGSFunction(JSContext *cx, uint32_t argc, jsval *vp);
    JSBool JSPROXY_clearJSContext(JSContext *cx, uint32_t argc, jsval *vp);
    JSBool JSPROXY_getNameByScreen(JSContext *cx, uint32_t argc, jsval *vp);
    void register_haypi_framework_js_extensions(JSContext* cx, JSObject* global);

    typedef jsval (*GS_Func)(int argc, jsval* argvp);
    void register_gs_function(const char* funcName, GS_Func func);
    
#ifdef __cplusplus
}
#endif
#endif /* defined(__MoonWarriors__Haypi_JSB__) */
