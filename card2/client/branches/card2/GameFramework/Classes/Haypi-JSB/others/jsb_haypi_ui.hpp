//
//  jsb_haypi_ui.hpp
//  GameFramework
//
//  Created by bo wei on 13-6-26.
//  Copyright (c) 2013年 cxj. All rights reserved.
//

#ifndef GameFramework_jsb_haypi_ui_hpp
#define GameFramework_jsb_haypi_ui_hpp

#include "jsapi.h"
#include "jsfriendapi.h"



JSBool js_HRootLayer_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_HRootLayer_finalize(JSFreeOp *fop, JSObject *obj);

void js_register_HRootLayer(JSContext *cx, JSObject *global);

JSBool js_HRootLayer_readNodeGraphFromFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_HRootLayer_presentRootLayer(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_HRootLayer_dismissRootLayer(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_HRootLayer_dismissAllLayer(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_HRootLayer_onBackClick(JSContext *cx, uint32_t argc, jsval *vp);

#endif
