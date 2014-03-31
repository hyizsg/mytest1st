//
//  jsb_haypi_ui.cpp
//  GameFramework
//
//  Created by bo wei on 13-6-26.
//  Copyright (c) 2013年 cxj. All rights reserved.
//

#include "jsb_haypi_ui.h"
#include "jsb_haypi_ui.hpp"
#include "cocos2d_specifics.hpp"
#include "js_bindings_config.h"
#include "ScriptingCore.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocos2dxframework.h"
#include "RootLayer.h"

USING_HNAMESPACE;

#if 0

template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	TypeTest<T> t;
	T* cobj = new T();
	cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
	if (_ccobj) {
		_ccobj->autorelease();
	}
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	assert(p);
	JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
	js_proxy_t *pp;
	JS_NEW_PROXY(pp, cobj, _tmp);
	JS_AddObjectRoot(cx, &pp->obj);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
    
	return JS_TRUE;
}

JSBool js_HRootLayer_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    HRootLayer *cobj = new HRootLayer();
    CCObject *_ccobj = dynamic_cast<CCObject*>(cobj);
    if (_ccobj)
    {
        _ccobj->autorelease();
    }
    
    js_proxy_t *proxy = js_get_or_create_proxy<HRootLayer>(cx, cobj);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(proxy->obj));
    return JS_TRUE;
}

JSBool js_HRootLayer_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        HRootLayer *cobj = new HRootLayer();
        CCObject *_ccobj = dynamic_cast<CCObject*>(cobj);
        if (_ccobj)
        {
            _ccobj->autorelease();
        }
        
        js_proxy_t *proxy = js_get_or_create_proxy<HRootLayer>(cx, cobj);        
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(proxy->obj));        
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}

void js_HRootLayer_finalize(JSFreeOp *fop, JSObject *obj) 
{
    
}


JSBool js_HRootLayer_AddJSCCBNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    HRootLayer* cobj = (HRootLayer*)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    const char* arg0;
    std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
    
    
    cocos2d::CCNode* arg1;    
    do {
        js_proxy_t *proxy;
        JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
        JS_GET_NATIVE_PROXY(proxy, tmpObj);
        arg1 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
        TEST_NATIVE_OBJECT(cx, arg1);
    } while(0);
    
    bool arg2 = false;
    if (argc >= 3) {
        arg2 = JSVAL_TO_BOOLEAN(argv[2]);
    }

    
    cobj->AddJSCCBNode(arg0, arg1, arg2);
    
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

JSBool js_HRootLayer_readNodeGraphFromFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    HRootLayer* cobj = (HRootLayer*)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");     
    
    const char* arg0;
    std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
    
    bool arg1 = false;
    if (argc > 1) {
        arg1 = JSVAL_TO_BOOLEAN(argv[1]);
    }
    
    CCNode *ret = cobj->readNodeGraphFromFile(arg0, arg1);
    jsval jsret;
    if (ret) {
        js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCNode>(cx, ret);
        jsret = OBJECT_TO_JSVAL(proxy->obj);
    } else {
        jsret = JSVAL_NULL;
    }
    JS_SET_RVAL(cx, vp, jsret);
    return JS_TRUE;
}



JSBool js_HRootLayer_presentRootLayer(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    HRootLayer* cobj = (HRootLayer*)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    bool arg0 = false;
    bool arg1 = true;
    if (argc >= 1)
    {
        arg0 = JSVAL_TO_BOOLEAN(argv[0]);
    }
    if (argc >= 2)
    {
        arg1 = JSVAL_TO_BOOLEAN(argv[1]);
    }
    cobj->presentRootLayer(arg0,arg1);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

JSBool js_HRootLayer_dismissRootLayer(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    HRootLayer* cobj = (HRootLayer*)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    bool arg0 = true;
    if (argc >= 1)
    {
        arg0 = JSVAL_TO_BOOLEAN(argv[0]);
    }
    cobj->dismissRootLayer(arg0);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

JSBool js_HRootLayer_dismissAllLayer(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    HRootLayer* cobj = (HRootLayer*)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    bool arg0 = true;
    if (argc >= 1)
    {
        arg0 = JSVAL_TO_BOOLEAN(argv[0]);
    }
    cobj->dismissAllLayers(arg0);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

JSBool js_HRootLayer_onBackClick(JSContext *cx, uint32_t argc, jsval *vp)
{
    //jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    HRootLayer* cobj = (HRootLayer*)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    cobj->onBackClick(NULL, 0);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

extern JSObject *js_cocos2dx_CCLayer_prototype;

JSClass  *jsb_HRootLayer_class;
JSObject *jsb_HRootLayer_prototype;

void js_register_HRootLayer(JSContext *cx, JSObject *global)
{
    jsb_HRootLayer_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_HRootLayer_class->name = "HRootLayer";
	jsb_HRootLayer_class->addProperty = JS_PropertyStub;
	jsb_HRootLayer_class->delProperty = JS_PropertyStub;
	jsb_HRootLayer_class->getProperty = JS_PropertyStub;
	jsb_HRootLayer_class->setProperty = JS_StrictPropertyStub;
	jsb_HRootLayer_class->enumerate = JS_EnumerateStub;
	jsb_HRootLayer_class->resolve = JS_ResolveStub;
	jsb_HRootLayer_class->convert = JS_ConvertStub;
	jsb_HRootLayer_class->finalize = js_HRootLayer_finalize;
	jsb_HRootLayer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};
    
	static JSFunctionSpec funcs[] = {
		JS_FN("readNodeGraphFromFile", js_HRootLayer_readNodeGraphFromFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("AddJSCCBNode", js_HRootLayer_AddJSCCBNode, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("presentRootLayer", js_HRootLayer_presentRootLayer, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("dismissRootLayer", js_HRootLayer_dismissRootLayer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("dismissAllLayer", js_HRootLayer_dismissAllLayer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("onBackClick", js_HRootLayer_onBackClick, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),		
		JS_FS_END
	};
    
	static JSFunctionSpec st_funcs[] = 
    {
		JS_FN("create", js_HRootLayer_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};
    
	jsb_HRootLayer_prototype = JS_InitClass(
                                              cx, global,
                                              js_cocos2dx_CCLayer_prototype,
                                              jsb_HRootLayer_class,
                                              //js_HRootLayer_constructor, 0, // constructor
                                              dummy_constructor<HRootLayer>,0,
                                              properties,
                                              funcs,
                                              NULL, // no static properties
                                              st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "HRootLayer", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
	// add the proto and JSClass to the type->js info hash table
	TypeTest<HRootLayer> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_HRootLayer_class;
		p->proto = jsb_HRootLayer_prototype;
		p->parentProto = js_cocos2dx_CCLayer_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_haypi_ui(JSContext* cx, JSObject* global)
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
    
    js_register_HRootLayer(cx, ns);
}

#endif