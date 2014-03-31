#include "jsb_cocos2dx_extension_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "cocos-ext.h"
#include "js_bindings_config.h"
#include "ScriptingCore.h"

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

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}


JSClass  *jsb_CCBReader_class;
JSObject *jsb_CCBReader_prototype;





JSClass  *jsb_CCScale9Sprite_class;
JSObject *jsb_CCScale9Sprite_prototype;

JSClass  *jsb_CCScrollView_class;
JSObject *jsb_CCScrollView_prototype;

JSBool js_cocos2dx_extension_CCScrollView_isClippingToBounds(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isClippingToBounds();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_setContainer(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCNode* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setContainer(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_setContentOffsetInDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::CCPoint arg0;
		double arg1;
        arg0 = jsval_to_ccpoint(cx, argv[0]);
		//ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		ok &= JS_ValueToNumber(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setContentOffsetInDuration(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_setZoomScaleInDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		double arg0;
		double arg1;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		ok &= JS_ValueToNumber(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setZoomScaleInDuration(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_addChild(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	cocos2d::extension::CCScrollView* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 2) {
			cocos2d::CCNode* arg0;
			do {
				js_proxy_t *proxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				JS_GET_NATIVE_PROXY(proxy, tmpObj);
				arg0 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->addChild(arg0, arg1);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 3) {
			cocos2d::CCNode* arg0;
			do {
				js_proxy_t *proxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				JS_GET_NATIVE_PROXY(proxy, tmpObj);
				arg0 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			int arg2;
			ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->addChild(arg0, arg1, arg2);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			cocos2d::CCNode* arg0;
			do {
				js_proxy_t *proxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				JS_GET_NATIVE_PROXY(proxy, tmpObj);
				arg0 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->addChild(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_ccTouchBegan(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::CCTouch* arg0;
		cocos2d::CCEvent* arg1;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCTouch*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg1 = (cocos2d::CCEvent*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		bool ret = cobj->ccTouchBegan(arg0, arg1);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_getContainer(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::CCNode* ret = cobj->getContainer();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCNode>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_ccTouchEnded(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::CCTouch* arg0;
		cocos2d::CCEvent* arg1;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCTouch*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg1 = (cocos2d::CCEvent*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->ccTouchEnded(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_getDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::extension::CCScrollViewDirection ret = cobj->getDirection();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_getZoomScale(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		float ret = cobj->getZoomScale();
		jsval jsret;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_updateInset(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->updateInset();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_initWithViewSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCSize arg0;
        arg0 = jsval_to_ccsize(cx, argv[0]);
		//ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		bool ret = cobj->initWithViewSize(arg0, NULL);// ->initWithViewSize(arg0);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	if (argc == 2) {
		cocos2d::CCSize arg0;
		cocos2d::CCNode* arg1;
        arg0 = jsval_to_ccsize(cx, argv[0]);
		//ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg1 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		bool ret = cobj->initWithViewSize(arg0, arg1);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCObject* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCObject*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->pause(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_setDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCScrollViewDirection arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setDirection(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_setBounceable(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setBounceable(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_setContentOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCPoint arg0;
        arg0 = jsval_to_ccpoint(cx, argv[0]);
		//ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setContentOffset(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		cocos2d::CCPoint arg0;
		JSBool arg1;
        arg0 = jsval_to_ccpoint(cx, argv[0]);
		//ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setContentOffset(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_isDragging(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isDragging();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_isBounceable(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isBounceable();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_getContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::CCSize ret = cobj->getContentSize();
		jsval jsret;
		jsret = ccsize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_ccTouchMoved(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::CCTouch* arg0;
		cocos2d::CCEvent* arg1;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCTouch*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg1 = (cocos2d::CCEvent*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->ccTouchMoved(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setTouchEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_getContentOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::CCPoint ret = cobj->getContentOffset();
		jsval jsret;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_resume(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCObject* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCObject*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->resume(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_setClippingToBounds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setClippingToBounds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_setViewSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCSize arg0;
        arg0 = jsval_to_ccsize(cx, argv[0]);
//		ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setViewSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_getViewSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::CCSize ret = cobj->getViewSize();
		jsval jsret;
		jsret = ccsize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_maxContainerOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::CCPoint ret = cobj->maxContainerOffset();
		jsval jsret;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_setContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCSize arg0;
        arg0 = jsval_to_ccsize(cx, argv[0]);
		//ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setContentSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_isTouchMoved(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isTouchMoved();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_isNodeVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCNode* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		bool ret = cobj->isNodeVisible(arg0);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_ccTouchCancelled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::CCTouch* arg0;
		cocos2d::CCEvent* arg1;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCTouch*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg1 = (cocos2d::CCEvent*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->ccTouchCancelled(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_minContainerOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::CCPoint ret = cobj->minContainerOffset();
		jsval jsret;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_registerWithTouchDispatcher(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->registerWithTouchDispatcher();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_setZoomScale(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	cocos2d::extension::CCScrollView* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 2) {
			double arg0;
			ok &= JS_ValueToNumber(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			JSBool arg1;
			ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->setZoomScale(arg0, arg1);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			double arg0;
			ok &= JS_ValueToNumber(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->setZoomScale(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	
	do {
		if (argc == 0) {
			cocos2d::extension::CCScrollView* ret = cocos2d::extension::CCScrollView::create();
			jsval jsret;
			do {
				if (ret) {
					js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCScrollView>(cx, ret);
					jsret = OBJECT_TO_JSVAL(proxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while (0);
	
	do {
		if (argc == 1) {
			cocos2d::CCSize arg0;
            arg0 = jsval_to_ccsize(cx, argv[0]);
			//ok &= jsval_to_ccsize(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cocos2d::extension::CCScrollView* ret = cocos2d::extension::CCScrollView::create(arg0);
			jsval jsret;
			do {
				if (ret) {
					js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCScrollView>(cx, ret);
					jsret = OBJECT_TO_JSVAL(proxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while (0);
	do {
		if (argc == 2) {
			cocos2d::CCSize arg0;
            arg0 = jsval_to_ccsize(cx, argv[0]);
			//ok &= jsval_to_ccsize(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cocos2d::CCNode* arg1;
			do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg1 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
			if (!ok) { ok = JS_TRUE; break; }
			cocos2d::extension::CCScrollView* ret = cocos2d::extension::CCScrollView::create(arg0, arg1);
			jsval jsret;
			do {
				if (ret) {
					js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCScrollView>(cx, ret);
					jsret = OBJECT_TO_JSVAL(proxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while (0);
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCScrollView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCScrollView* cobj = new cocos2d::extension::CCScrollView();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCScrollView> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t *p;
		JS_NEW_PROXY(p, cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCScrollView");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}



extern JSObject *js_cocos2dx_CCLayer_prototype;

void js_cocos2dx_extension_CCScrollView_finalize(JSFreeOp *fop, JSObject *obj) {
}

void js_register_cocos2dx_extension_CCScrollView(JSContext *cx, JSObject *global) {
	jsb_CCScrollView_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCScrollView_class->name = "ScrollView";
	jsb_CCScrollView_class->addProperty = JS_PropertyStub;
	jsb_CCScrollView_class->delProperty = JS_PropertyStub;
	jsb_CCScrollView_class->getProperty = JS_PropertyStub;
	jsb_CCScrollView_class->setProperty = JS_StrictPropertyStub;
	jsb_CCScrollView_class->enumerate = JS_EnumerateStub;
	jsb_CCScrollView_class->resolve = JS_ResolveStub;
	jsb_CCScrollView_class->convert = JS_ConvertStub;
	jsb_CCScrollView_class->finalize = js_cocos2dx_extension_CCScrollView_finalize;
	jsb_CCScrollView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("isClippingToBounds", js_cocos2dx_extension_CCScrollView_isClippingToBounds, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setContainer", js_cocos2dx_extension_CCScrollView_setContainer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setContentOffsetInDuration", js_cocos2dx_extension_CCScrollView_setContentOffsetInDuration, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setZoomScaleInDuration", js_cocos2dx_extension_CCScrollView_setZoomScaleInDuration, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addChild", js_cocos2dx_extension_CCScrollView_addChild, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ccTouchBegan", js_cocos2dx_extension_CCScrollView_ccTouchBegan, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getContainer", js_cocos2dx_extension_CCScrollView_getContainer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ccTouchEnded", js_cocos2dx_extension_CCScrollView_ccTouchEnded, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getDirection", js_cocos2dx_extension_CCScrollView_getDirection, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getZoomScale", js_cocos2dx_extension_CCScrollView_getZoomScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("updateInset", js_cocos2dx_extension_CCScrollView_updateInset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithViewSize", js_cocos2dx_extension_CCScrollView_initWithViewSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("pause", js_cocos2dx_extension_CCScrollView_pause, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDirection", js_cocos2dx_extension_CCScrollView_setDirection, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBounceable", js_cocos2dx_extension_CCScrollView_setBounceable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setContentOffset", js_cocos2dx_extension_CCScrollView_setContentOffset, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isDragging", js_cocos2dx_extension_CCScrollView_isDragging, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_cocos2dx_extension_CCScrollView_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isBounceable", js_cocos2dx_extension_CCScrollView_isBounceable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getContentSize", js_cocos2dx_extension_CCScrollView_getContentSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ccTouchMoved", js_cocos2dx_extension_CCScrollView_ccTouchMoved, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTouchEnabled", js_cocos2dx_extension_CCScrollView_setTouchEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getContentOffset", js_cocos2dx_extension_CCScrollView_getContentOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("resume", js_cocos2dx_extension_CCScrollView_resume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setClippingToBounds", js_cocos2dx_extension_CCScrollView_setClippingToBounds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setViewSize", js_cocos2dx_extension_CCScrollView_setViewSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getViewSize", js_cocos2dx_extension_CCScrollView_getViewSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("maxContainerOffset", js_cocos2dx_extension_CCScrollView_maxContainerOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setContentSize", js_cocos2dx_extension_CCScrollView_setContentSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isTouchMoved", js_cocos2dx_extension_CCScrollView_isTouchMoved, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isNodeVisible", js_cocos2dx_extension_CCScrollView_isNodeVisible, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ccTouchCancelled", js_cocos2dx_extension_CCScrollView_ccTouchCancelled, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("minContainerOffset", js_cocos2dx_extension_CCScrollView_minContainerOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("registerWithTouchDispatcher", js_cocos2dx_extension_CCScrollView_registerWithTouchDispatcher, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setZoomScale", js_cocos2dx_extension_CCScrollView_setZoomScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_extension_CCScrollView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCScrollView_prototype = JS_InitClass(
		cx, global,
		js_cocos2dx_CCLayer_prototype,
		jsb_CCScrollView_class,
		js_cocos2dx_extension_CCScrollView_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ScrollView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCScrollView> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCScrollView_class;
		p->proto = jsb_CCScrollView_prototype;
		p->parentProto = js_cocos2dx_CCLayer_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCBAnimationManager_class;
JSObject *jsb_CCBAnimationManager_prototype;



JSClass  *jsb_CCTableViewCell_class;
JSObject *jsb_CCTableViewCell_prototype;

JSBool js_cocos2dx_extension_CCTableViewCell_reset(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableViewCell* cobj = (cocos2d::extension::CCTableViewCell *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->reset();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableViewCell_setIdx(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableViewCell* cobj = (cocos2d::extension::CCTableViewCell *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		unsigned int arg0;
		ok &= jsval_to_uint32(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setIdx(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableViewCell_setObjectID(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableViewCell* cobj = (cocos2d::extension::CCTableViewCell *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		unsigned int arg0;
		ok &= jsval_to_uint32(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setObjectID(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableViewCell_getObjectID(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableViewCell* cobj = (cocos2d::extension::CCTableViewCell *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		unsigned int ret = cobj->getObjectID();
		jsval jsret;
		jsret = uint32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableViewCell_getIdx(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableViewCell* cobj = (cocos2d::extension::CCTableViewCell *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		unsigned int ret = cobj->getIdx();
		jsval jsret;
		jsret = uint32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableViewCell_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCTableViewCell* cobj = new cocos2d::extension::CCTableViewCell();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCTableViewCell> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t *p;
		JS_NEW_PROXY(p, cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCTableViewCell");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




extern JSObject *js_cocos2dx_CCNode_prototype;

void js_cocos2dx_extension_CCTableViewCell_finalize(JSFreeOp *fop, JSObject *obj) {
}

void js_register_cocos2dx_extension_CCTableViewCell(JSContext *cx, JSObject *global) {
	jsb_CCTableViewCell_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCTableViewCell_class->name = "TableViewCell";
	jsb_CCTableViewCell_class->addProperty = JS_PropertyStub;
	jsb_CCTableViewCell_class->delProperty = JS_PropertyStub;
	jsb_CCTableViewCell_class->getProperty = JS_PropertyStub;
	jsb_CCTableViewCell_class->setProperty = JS_StrictPropertyStub;
	jsb_CCTableViewCell_class->enumerate = JS_EnumerateStub;
	jsb_CCTableViewCell_class->resolve = JS_ResolveStub;
	jsb_CCTableViewCell_class->convert = JS_ConvertStub;
	jsb_CCTableViewCell_class->finalize = js_cocos2dx_extension_CCTableViewCell_finalize;
	jsb_CCTableViewCell_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("reset", js_cocos2dx_extension_CCTableViewCell_reset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setIdx", js_cocos2dx_extension_CCTableViewCell_setIdx, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setObjectID", js_cocos2dx_extension_CCTableViewCell_setObjectID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getObjectID", js_cocos2dx_extension_CCTableViewCell_getObjectID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getIdx", js_cocos2dx_extension_CCTableViewCell_getIdx, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_CCTableViewCell_prototype = JS_InitClass(
		cx, global,
		js_cocos2dx_CCNode_prototype,
		jsb_CCTableViewCell_class,
		js_cocos2dx_extension_CCTableViewCell_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "TableViewCell", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCTableViewCell> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCTableViewCell_class;
		p->proto = jsb_CCTableViewCell_prototype;
		p->parentProto = js_cocos2dx_CCNode_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCTableView_class;
JSObject *jsb_CCTableView_prototype;

JSBool js_cocos2dx_extension_CCTableView_updateCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		unsigned int arg0;
		ok &= jsval_to_uint32(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->updateCellAtIndex(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_setVerticalFillOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCTableViewVerticalFillOrder arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setVerticalFillOrder(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_scrollViewDidZoom(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCScrollView* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::extension::CCScrollView*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->scrollViewDidZoom(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_ccTouchBegan(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::CCTouch* arg0;
		cocos2d::CCEvent* arg1;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCTouch*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg1 = (cocos2d::CCEvent*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		bool ret = cobj->ccTouchBegan(arg0, arg1);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_getVerticalFillOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::extension::CCTableViewVerticalFillOrder ret = cobj->getVerticalFillOrder();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_removeCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		unsigned int arg0;
		ok &= jsval_to_uint32(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->removeCellAtIndex(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_initWithViewSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCSize arg0;
        arg0 = jsval_to_ccsize(cx, argv[0]);
		//ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		bool ret = cobj->initWithViewSize(arg0);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	if (argc == 2) {
		cocos2d::CCSize arg0;
		cocos2d::CCNode* arg1;
        arg0 = jsval_to_ccsize(cx, argv[0]);
		//ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg1 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		bool ret = cobj->initWithViewSize(arg0, arg1);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_scrollViewDidScroll(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCScrollView* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::extension::CCScrollView*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->scrollViewDidScroll(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_reloadData(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->reloadData();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_ccTouchCancelled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::CCTouch* arg0;
		cocos2d::CCEvent* arg1;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCTouch*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg1 = (cocos2d::CCEvent*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->ccTouchCancelled(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_ccTouchEnded(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::CCTouch* arg0;
		cocos2d::CCEvent* arg1;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCTouch*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg1 = (cocos2d::CCEvent*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->ccTouchEnded(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_ccTouchMoved(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::CCTouch* arg0;
		cocos2d::CCEvent* arg1;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCTouch*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg1 = (cocos2d::CCEvent*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->ccTouchMoved(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
/*
JSBool js_cocos2dx_extension_CCTableView__updateContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->_updateContentSize();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}*/
JSBool js_cocos2dx_extension_CCTableView_insertCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		unsigned int arg0;
		ok &= jsval_to_uint32(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->insertCellAtIndex(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_cellAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		unsigned int arg0;
		ok &= jsval_to_uint32(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::extension::CCTableViewCell* ret = cobj->cellAtIndex(arg0);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCTableViewCell>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_dequeueCell(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::extension::CCTableViewCell* ret = cobj->dequeueCell();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCTableViewCell>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_CCTableView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCTableView* cobj = new cocos2d::extension::CCTableView();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCTableView> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t *p;
		JS_NEW_PROXY(p, cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCTableView");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}



extern JSObject *jsb_CCScrollView_prototype;

void js_cocos2dx_extension_CCTableView_finalize(JSFreeOp *fop, JSObject *obj) {
}

void js_register_cocos2dx_extension_CCTableView(JSContext *cx, JSObject *global) {
	jsb_CCTableView_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCTableView_class->name = "TableView";
	jsb_CCTableView_class->addProperty = JS_PropertyStub;
	jsb_CCTableView_class->delProperty = JS_PropertyStub;
	jsb_CCTableView_class->getProperty = JS_PropertyStub;
	jsb_CCTableView_class->setProperty = JS_StrictPropertyStub;
	jsb_CCTableView_class->enumerate = JS_EnumerateStub;
	jsb_CCTableView_class->resolve = JS_ResolveStub;
	jsb_CCTableView_class->convert = JS_ConvertStub;
	jsb_CCTableView_class->finalize = js_cocos2dx_extension_CCTableView_finalize;
	jsb_CCTableView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("updateCellAtIndex", js_cocos2dx_extension_CCTableView_updateCellAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setVerticalFillOrder", js_cocos2dx_extension_CCTableView_setVerticalFillOrder, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollViewDidZoom", js_cocos2dx_extension_CCTableView_scrollViewDidZoom, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ccTouchBegan", js_cocos2dx_extension_CCTableView_ccTouchBegan, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getVerticalFillOrder", js_cocos2dx_extension_CCTableView_getVerticalFillOrder, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeCellAtIndex", js_cocos2dx_extension_CCTableView_removeCellAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithViewSize", js_cocos2dx_extension_CCTableView_initWithViewSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollViewDidScroll", js_cocos2dx_extension_CCTableView_scrollViewDidScroll, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("reloadData", js_cocos2dx_extension_CCTableView_reloadData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ccTouchCancelled", js_cocos2dx_extension_CCTableView_ccTouchCancelled, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ccTouchEnded", js_cocos2dx_extension_CCTableView_ccTouchEnded, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ccTouchMoved", js_cocos2dx_extension_CCTableView_ccTouchMoved, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		//JS_FN("_updateContentSize", js_cocos2dx_extension_CCTableView__updateContentSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("insertCellAtIndex", js_cocos2dx_extension_CCTableView_insertCellAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("cellAtIndex", js_cocos2dx_extension_CCTableView_cellAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("dequeueCell", js_cocos2dx_extension_CCTableView_dequeueCell, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_CCTableView_prototype = JS_InitClass(
		cx, global,
		jsb_CCScrollView_prototype,
		jsb_CCTableView_class,
		js_cocos2dx_extension_CCTableView_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "TableView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCTableView> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCTableView_class;
		p->proto = jsb_CCTableView_prototype;
		p->parentProto = jsb_CCScrollView_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCEditBox_class;
JSObject *jsb_CCEditBox_prototype;

USING_NS_CC_EXT;

class JSInvocationWrapper: public CCInvocation {
private:
    JSCallbackWrapper *callbackWrapper;
    
public:
    JSInvocationWrapper(CCControlEvent ev):CCInvocation(NULL,NULL,ev) {
        callbackWrapper = NULL;
    }
    
    void setCallBackWrapper(JSCallbackWrapper *wrapper) {
        if (callbackWrapper == wrapper)
            return;
        if (callbackWrapper) {
            callbackWrapper->release();
            callbackWrapper = NULL;
        }
        if (wrapper != NULL) {
            callbackWrapper = wrapper;
            callbackWrapper->retain();
        }
    }
    
    virtual ~JSInvocationWrapper(void) {
        if (callbackWrapper != NULL) {
            callbackWrapper->release();
            callbackWrapper = NULL;
        }
    }
    
    void action(CCObject *obj, CCControlEvent ev) {
        invoke(obj);
    }
    
    void invoke(CCObject* sender) {
        if (callbackWrapper == NULL) {
            return;
        }
        
        js_proxy_t *p;
        JS_GET_PROXY(p, sender);
        if (!p) return;
        
        const jsval &jsCallback = callbackWrapper->getJSCallbackFunc();
        if (jsCallback == JSVAL_VOID)
            return;
        
        JSObject* thisObj = JSVAL_IS_VOID(callbackWrapper->getJSCallbackThis()) ? NULL : JSVAL_TO_OBJECT(callbackWrapper->getJSCallbackThis());
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        
        jsval retval;
        jsval valArr[2];
        valArr[0] = OBJECT_TO_JSVAL(p->obj);
        valArr[1] = INT_TO_JSVAL(this->getControlEvent());
        JS_AddValueRoot(cx, valArr);
        JS_CallFunctionValue(cx, thisObj, jsCallback, 2, valArr, &retval);
        JS_RemoveValueRoot(cx, valArr);
    }
};





class JSB_ScrollViewDelegate : public CCScrollViewDelegate
{
public:
    virtual void scrollViewDidScroll(CCScrollView* view)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "scrollViewDidScroll", arg);
    }
    
    virtual void scrollViewDidZoom(CCScrollView* view)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "scrollViewDidZoom", arg);
    }
    
    virtual void scrollViewEndScroll(CCScrollView* view) {
        js_proxy_t * p;
        JS_GET_PROXY(p, view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "scrollViewEndScroll", arg);
    }
        
    void setJSDelegate(JSObject* pJSDelegate)
    {
        m_pJSDelegate = pJSDelegate;
    }
private:
    JSObject* m_pJSDelegate;
};

static JSBool js_cocos2dx_CCScrollView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_ScrollViewDelegate* nativeDelegate = new JSB_ScrollViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setDelegate(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class JSB_TableViewDelegate : public CCTableViewDelegate
{
public:
    virtual void scrollViewDidScroll(CCScrollView* view)
    {
        callJSDelegate(view, "scrollViewDidScroll");
    }
    
    virtual void scrollViewDidZoom(CCScrollView* view)
    {
        callJSDelegate(view, "scrollViewDidZoom");
    }
    
    virtual void scrollViewEndScroll(CCScrollView* view) {
        js_proxy_t * p;
        JS_GET_PROXY(p, view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "scrollViewEndScroll", arg);
    }

    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell)
    {
        callJSDelegate(table, cell, "tableCellTouched");
    }
    
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
    {
        callJSDelegate(table, cell, "tableCellHighlight");
    }
    
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
    {
        callJSDelegate(table, cell, "tableCellUnhighlight");
    }
    
    virtual void tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell)
    {
        callJSDelegate(table, cell, "tableCellWillRecycle");
    }
    
    void setJSDelegate(JSObject* pJSDelegate)
    {
        m_pJSDelegate = pJSDelegate;
    }
    
    
private:
    void callJSDelegate(CCScrollView* view, std::string jsFunctionName)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), jsFunctionName.c_str(), arg);
    }
    
    void callJSDelegate(CCTableView* table, CCTableViewCell* cell, std::string jsFunctionName)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, table);
        if (!p) return;
        
        js_proxy_t * pCellProxy;
        JS_GET_PROXY(pCellProxy, cell);
        if (!pCellProxy) return;
        
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = OBJECT_TO_JSVAL(pCellProxy->obj);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), jsFunctionName.c_str(), 2, args);
    }
    
    JSObject* m_pJSDelegate;
};


static JSBool js_cocos2dx_CCTableView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_TableViewDelegate* nativeDelegate = new JSB_TableViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setDelegate(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class JSB_TableViewDataSource : public CCTableViewDataSource
{
public:
    virtual CCSize cellSizeForTable(CCTableView *table)
    {
        jsval ret;
        bool ok = callJSDelegate(table, "cellSizeForTable", ret);
        if (ok)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            CCSize size;
            size = jsval_to_ccsize(cx, ret);
            return size;
        }
        return CCSizeZero;
    }
    
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx)
    {
        jsval ret;
        bool ok = callJSDelegate(table, idx, "tableCellAtIndex", ret);
        if (ok)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            cocos2d::extension::CCTableViewCell* arg0;
            do {
                js_proxy_t *proxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(ret);
                JS_GET_NATIVE_PROXY(proxy, tmpObj);
                arg0 = (cocos2d::extension::CCTableViewCell*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, NULL, "Invalid Native Object");
            } while (0);
            return arg0;
        }
        return NULL;
    }
    
    virtual unsigned int numberOfCellsInTableView(CCTableView *table)
    {
        jsval ret;
        bool ok = callJSDelegate(table, "numberOfCellsInTableView", ret);
        if (ok)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            uint32_t count = 0;
            JSBool isSucceed = jsval_to_uint32(cx, ret, &count);
            if (isSucceed) return count;
        }
        return 0;
    }
    
    
    void setTableViewDataSource(JSObject* pJSSource)
    {
        m_pJSTableViewDataSource = pJSSource;
    }
    
private:
    bool callJSDelegate(CCTableView* table, std::string jsFunctionName, jsval& retVal)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, table);
        if (!p) return false;
        
        JSBool hasAction;
        jsval temp_retval;
        jsval dataVal = OBJECT_TO_JSVAL(p->obj);
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject* obj = m_pJSTableViewDataSource;
        
        if (JS_HasProperty(cx, obj, jsFunctionName.c_str(), &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, jsFunctionName.c_str(), &temp_retval)) {
                return false;
            }
            if(temp_retval == JSVAL_VOID) {
                return false;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, jsFunctionName.c_str(),
                                1, &dataVal, &retVal);
            return true;
        }
        return false;
    }
    
    bool callJSDelegate(CCTableView* table, int idx, std::string jsFunctionName, jsval& retVal)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, table);
        if (!p) return false;
        
        
        JSBool hasAction;
        jsval temp_retval;
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        dataVal[1] = INT_TO_JSVAL(idx);
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject* obj = m_pJSTableViewDataSource;
        
        if (JS_HasProperty(cx, obj, jsFunctionName.c_str(), &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, jsFunctionName.c_str(), &temp_retval)) {
                return false;
            }
            if(temp_retval == JSVAL_VOID) {
                return false;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, jsFunctionName.c_str(),
                                2, dataVal, &retVal);
            return true;
        }
        return false;
    }
    
private:
    JSObject* m_pJSTableViewDataSource;
};

static JSBool js_cocos2dx_CCTableView_setDataSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 1)
    {
        CCTableViewDataSource* pOldDataSource = cobj->getDataSource();
        CC_SAFE_DELETE(pOldDataSource);
        JSB_TableViewDataSource* pNativeSource = new JSB_TableViewDataSource();
        pNativeSource->setTableViewDataSource(JSVAL_TO_OBJECT(argv[0]));
        cobj->setDataSource(pNativeSource);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_CCTableView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3 || argc == 2) {
        
        JSB_TableViewDataSource* pNativeSource = new JSB_TableViewDataSource();
        pNativeSource->setTableViewDataSource(JSVAL_TO_OBJECT(argv[0]));
        
        cocos2d::CCSize arg1;
        arg1 = jsval_to_ccsize(cx, argv[1]);
        cocos2d::extension::CCTableView* ret = NULL;
        ret = new CCTableView();
        ret->setDataSource(pNativeSource);
        ret->autorelease();
        jsval jsret;
        do {
            if (ret) {
                js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCTableView>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        
        if (argc == 2)
        {
            ret->initWithViewSize(arg1);
        }
        else
        {
            cocos2d::CCNode* arg2;
            do {
                js_proxy_t *proxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
                JS_GET_NATIVE_PROXY(proxy, tmpObj);
                arg2 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, JS_FALSE, "Invalid Native Object");
            } while (0);
            JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
            ret->initWithViewSize(arg1, arg2);
        }
        ret->_updateContentSize();
        
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}

class JSB_EditBoxDelegate : public CCEditBoxDelegate
{
public:
    virtual void editBoxEditingDidBegin(CCEditBox* editBox)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxEditingDidBegin", 1, &arg, NULL);
    }
    
    virtual void editBoxEditingDidEnd(CCEditBox* editBox)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxEditingDidEnd", 1, &arg, NULL);
    }
    
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, editBox);
        if (!p) return;
        
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        std::string arg1 = text;
        dataVal[1] = std_string_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), arg1);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxTextChanged", 2, dataVal, NULL);
    }
    
    virtual void editBoxReturn(CCEditBox* editBox)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxReturn", 1, &arg, NULL);
    }
    
    void setJSDelegate(JSObject* pJSDelegate)
    {
        m_pJSDelegate = pJSDelegate;
    }
private:
    JSObject* m_pJSDelegate;
};

static JSBool js_cocos2dx_CCEditBox_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::extension::CCEditBox* cobj = (cocos2d::extension::CCEditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_EditBoxDelegate* nativeDelegate = new JSB_EditBoxDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setDelegate(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}


JSBool js_cocos2dx_CCControl_setCallback(JSContext *cx, uint32_t argc, jsval *vp) {
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    
    JSB_PRECONDITION(argc==1 || argc==2, "Invalid number of arguments. Expecting 2 or 3 args");
    
    js_proxy_t *proxy;
    JS_GET_NATIVE_PROXY(proxy, obj);
    CCControl* item = (CCControl*)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, item)
    
    
    jsval jsThis = JSVAL_VOID;
    jsval jsFunc = argv[0];
    JSBool ok = JS_TRUE;
    
    //int32_t jsevent;
    //ok &= JS_ValueToInt32(cx, argv[1], &jsevent);
    
    if (argc == 2) {
        jsThis = argv[1];
    }
    
    
    JSInvocationWrapper *invocation = new JSInvocationWrapper(CCControlEventTouchUpInside);
    JSCallbackWrapper *tmpCobj = new JSCallbackWrapper();
    tmpCobj->autorelease();
    tmpCobj->setJSCallbackFunc(jsFunc);
    tmpCobj->setJSCallbackThis(jsThis);
    invocation->autorelease();
    invocation->setCallBackWrapper(tmpCobj);
    
    item->addCCInvocationForControlEvents(invocation, CCControlEventTouchUpInside);
    return ok;
}


extern JSObject* jsb_CCScrollView_prototype;
extern JSObject* jsb_CCTableView_prototype;
extern JSObject* jsb_CCEditBox_prototype;
extern JSObject* jsb_CCControl_prototype;
extern JSObject* js_cocos2dx_CCControlButton_prototype;

void register_all_cocos2dx_extension_manual(JSContext* cx, JSObject* global)
{
    JS_DefineFunction(cx, jsb_CCScrollView_prototype, "setDelegate", js_cocos2dx_CCScrollView_setDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_CCTableView_prototype, "setDelegate", js_cocos2dx_CCTableView_setDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_CCTableView_prototype, "setDataSource", js_cocos2dx_CCTableView_setDataSource, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    //JS_DefineFunction(cx, jsb_CCEditBox_prototype, "setDelegate", js_cocos2dx_CCEditBox_setDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, js_cocos2dx_CCControlButton_prototype, "setCallback", js_cocos2dx_CCControl_setCallback, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JSObject *tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.TableView; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCTableView_create, 3, JSPROP_READONLY | JSPROP_PERMANENT);
}


void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, obj, "cc", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "cc", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	//js_register_cocos2dx_extension_CCBAnimationManager(cx, obj);
	js_register_cocos2dx_extension_CCScrollView(cx, obj);
	js_register_cocos2dx_extension_CCTableView(cx, obj);
	//js_register_cocos2dx_extension_CCControl(cx, obj);
	//js_register_cocos2dx_extension_CCControlButton(cx, obj);
	//js_register_cocos2dx_extension_CCEditBox(cx, obj);
	//js_register_cocos2dx_extension_CCBReader(cx, obj);
	js_register_cocos2dx_extension_CCTableViewCell(cx, obj);    
	//js_register_cocos2dx_extension_CCScale9Sprite(cx, obj);
}

#endif

