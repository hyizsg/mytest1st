//
//  Haypi-JSB.cpp
//  Haypi-JSB
//
//  Created by jim kaden on 13-4-25.
//
//

#include "Haypi-JSB.h"
#include "Haypi-Wrapper.h"
#include "Haypi-JSBObject.h"

jsval HaypiWrapper_callGSFunction(const char* funcName, int argc, jsval* argvp);

// sendCmd(cmd, callbackObj[.onReceive])
JSBool JSPROXY_sendCmd(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION( argc == 1 || argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	//const char* context;
    char* context;
    const char* funcName = NULL;
    JSObject* callbackPtr = NULL;
    ok &= jsval_to_charptr(cx, argvp[0], (const char**)&context);
	if( ! ok )
        return JS_FALSE;
    if ( argc > 1)
    {
        ok &= JS_ValueToObject(cx, argvp[1], (JSObject**)&callbackPtr);
        if( ! ok )
            return JS_FALSE;
        ok &= jsval_to_charptr(cx, argvp[2], (const char**)&funcName);
        if( ! ok )
            return JS_FALSE;
    }
    JSBool ret = (JSBool)HaypiWrapper_sendCmd(context, callbackPtr, funcName);
	JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
	return JS_TRUE;
}

JSBool JSPROXY_setCommandHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION( argc == 1 , "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
    JSObject* callbackPtr;
    struct jsb_c_proxy_s* proxy;
    
    ok &= jsval_to_c_class( cx, *argvp++, (void**)&callbackPtr, &proxy );
    
    if( ! ok )
        return JS_FALSE;
    
    JSBool ret = (JSBool)HaypiWrapper_setCommandHandler(callbackPtr);
	JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
	return JS_TRUE;
}

JSBool JSPROXY_createJsonWithAction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION( argc == 1 , "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
    uint32_t action;
    
    ok &= jsval_to_uint( cx, *argvp++, (uint32_t*)&action );
    
    if( ! ok )
        return JS_FALSE;
    
    char* ret = HaypiWrapper_createJsonWithAction(action);
	JS_SET_RVAL(cx, vp, charptr_to_jsval(cx, (const char*)ret));
    free(ret);
	return JS_TRUE;
}

JSBool JSPROXY_getHashCode(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION( argc == 0, "Invalid number of arguments" );
    
	long long ret_val = HaypiWrapper_getHashCode();
    
	JS_SET_RVAL(cx, vp, longlong_to_jsval(cx, ret_val));
	return JS_TRUE;
}

JSBool JSPROXY_getMemberID(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION( argc == 0, "Invalid number of arguments" );
    
	long long ret_val = HaypiWrapper_getMemberID();
    
	JS_SET_RVAL(cx, vp, longlong_to_jsval(cx, ret_val));
	return JS_TRUE;
}

JSBool JSPROXY_clearJSContext(JSContext *cx, uint32_t argc, jsval *vp)
{
    //CCScriptEngineManager::sharedManager()->removeScriptEngine();
	return JS_TRUE;
}

JSBool JSPROXY_getNameByScreen(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION( argc == 1 , "Invalid number of arguments! getNameByScreen " );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
    char* resourceName;
    ok &= jsval_to_charptr(cx, argvp[0], (const char**)&resourceName);
	if( ! ok )
        return JS_FALSE;
    
    char* ret = HaypiWrapper_getNameByScreen(resourceName);
    if ( ret )
    {
        JS_SET_RVAL(cx, vp, charptr_to_jsval(cx, (const char*)ret));
        free(ret);
        return JS_TRUE;
    }
    return JS_FALSE;
}


JSBool JSPROXY_callGSFunction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION( argc >= 1 , "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	//const char* context;
    const char* funcName = NULL;
    ok &= jsval_to_charptr(cx, *argvp++, (const char**)&funcName);
	if( ! ok )
        return JS_FALSE;
    jsval ret = HaypiWrapper_callGSFunction(funcName, argc-1, argvp);
	JS_SET_RVAL(cx, vp, ret);
	return JS_TRUE;
}
jsval HaypiWrapper_callGSFunction(const char* funcName, int argc, jsval* argvp)
{
    jsval ret = JSVAL_VOID;
    GS_Func pfn = HaypiNetCallback::sharedInstance()->getCallback(std::string(funcName));
    if ( pfn )
    {
        ret = pfn(argc, argvp);
    }
    return ret;
}

void register_gs_function(const char* funcName, GS_Func func)
{
    HaypiNetCallback::sharedInstance()->addCallback(std::string(funcName), func);
}
void register_haypi_framework_js_extensions(JSContext* cx, JSObject* global)
{
	jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, global, "haypi", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, global, "haypi", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
    
	JS_DefineFunction(cx, global, "sendCmd", JSPROXY_sendCmd, 3, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, global, "setCommandHandler", JSPROXY_setCommandHandler, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, global, "createJsonWithAction", JSPROXY_createJsonWithAction, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, global, "getHashCode", JSPROXY_getHashCode, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, global, "getMemberID", JSPROXY_getMemberID, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, global, "callGS", JSPROXY_callGSFunction, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "clearJSContext", JSPROXY_clearJSContext, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "getNameByScreen", JSPROXY_getNameByScreen, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}

