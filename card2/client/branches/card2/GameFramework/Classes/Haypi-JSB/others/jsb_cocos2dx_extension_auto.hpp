#ifndef __cocos2dx_extension_h__
#define __cocos2dx_extension_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_CCBReader_class;
extern JSObject *jsb_CCBReader_prototype;

JSBool js_cocos2dx_extension_CCBReader_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_CCBReader_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_CCBReader(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_extension_CCBReader_getOwnerCallbackNames(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_setCCBRootPath(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_getOwnerCallbackNodes(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_readSoundKeyframesForSeq(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_getCCBRootPath(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_getOwnerOutletNodes(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_readUTF8(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_getOwnerOutletNames(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_setAnimationManager(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_readCallbackKeyframesForSeq(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_getAnimationManagersForNodes(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_getNodesWithAnimationManagers(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_getAnimationManager(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBReader_CCBReader(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCControl_class;
extern JSObject *jsb_CCControl_prototype;

JSBool js_cocos2dx_extension_CCControl_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_CCControl_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_CCControl(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_extension_CCControl_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_getState(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_isOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_sendActionsForControlEvents(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_setSelected(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_getTouchLocation(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_isEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_isTouchInside(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_setOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_needsLayout(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_hasVisibleParents(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_isSelected(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_getTouchPriority(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_setHighlighted(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_registerWithTouchDispatcher(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_isHighlighted(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_setTouchPriority(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCControl_CCControl(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCScale9Sprite_class;
extern JSObject *jsb_CCScale9Sprite_prototype;

JSBool js_cocos2dx_extension_CCScale9Sprite_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_CCScale9Sprite_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_CCScale9Sprite(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_extension_CCScale9Sprite_getCapInsets(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_setOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_updateWithBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_setInsetBottom(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_isOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_initWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_setInsetTop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_setPreferredSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_setSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_initWithBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_getInsetBottom(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_resizableSpriteWithCapInsets(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_setContentSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_getInsetRight(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_getOriginalSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_initWithFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_getInsetTop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_setInsetLeft(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_initWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_getPreferredSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_getInsetLeft(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_setInsetRight(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_createWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScale9Sprite_CCScale9Sprite(JSContext *cx, uint32_t argc, jsval *vp);


extern JSClass  *jsb_CCScrollView_class;
extern JSObject *jsb_CCScrollView_prototype;

JSBool js_cocos2dx_extension_CCScrollView_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_CCScrollView_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_CCScrollView(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_extension_CCScrollView_isClippingToBounds(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_setContainer(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_setContentOffsetInDuration(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_setZoomScaleInDuration(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_addChild(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_ccTouchBegan(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_getContainer(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_ccTouchEnded(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_getDirection(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_getZoomScale(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_updateInset(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_initWithViewSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_pause(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_setDirection(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_setBounceable(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_setContentOffset(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_isDragging(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_isBounceable(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_getContentSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_ccTouchMoved(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_getContentOffset(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_resume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_setClippingToBounds(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_setViewSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_getViewSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_maxContainerOffset(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_setContentSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_isTouchMoved(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_isNodeVisible(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_ccTouchCancelled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_minContainerOffset(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_registerWithTouchDispatcher(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_setZoomScale(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCScrollView_CCScrollView(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCBAnimationManager_class;
extern JSObject *jsb_CCBAnimationManager_prototype;

JSBool js_cocos2dx_extension_CCBAnimationManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_CCBAnimationManager_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_CCBAnimationManager(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_extension_CCBAnimationManager_moveAnimationsFromNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_setAutoPlaySequenceId(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNames(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_actionForSoundChannel(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_setBaseValue(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNodes(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_addNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getLastCompletedSequenceName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_setRootNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_addDocumentOutletName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getSequences(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getRootContainerSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_setDocumentControllerName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getContainerSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_actionForCallbackChannel(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNames(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getKeyframeCallbacks(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_setRootContainerSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getRunningSequenceName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getAutoPlaySequenceId(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getRootNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_addDocumentOutletNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_setDelegate(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_setCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getDelegate(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_runAnimations(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamed(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNodes(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_setSequences(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_debug(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_getDocumentControllerName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCBAnimationManager_CCBAnimationManager(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCTableViewCell_class;
extern JSObject *jsb_CCTableViewCell_prototype;

JSBool js_cocos2dx_extension_CCTableViewCell_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_CCTableViewCell_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_CCTableViewCell(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_extension_CCTableViewCell_reset(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableViewCell_setIdx(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableViewCell_setObjectID(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableViewCell_getObjectID(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableViewCell_getIdx(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableViewCell_CCTableViewCell(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCTableView_class;
extern JSObject *jsb_CCTableView_prototype;

JSBool js_cocos2dx_extension_CCTableView_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_CCTableView_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_CCTableView(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_extension_CCTableView_updateCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_setVerticalFillOrder(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_scrollViewDidZoom(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_ccTouchBegan(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_getVerticalFillOrder(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_removeCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_initWithViewSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_scrollViewDidScroll(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_reloadData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_ccTouchCancelled(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_ccTouchEnded(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_ccTouchMoved(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView__updateContentSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_insertCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_cellAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_dequeueCell(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCTableView_CCTableView(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCEditBox_class;
extern JSObject *jsb_CCEditBox_prototype;

JSBool js_cocos2dx_extension_CCEditBox_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_extension_CCEditBox_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_extension_CCEditBox(JSContext *cx, JSObject *global);
void register_all_cocos2dx_extension(JSContext* cx, JSObject* obj);
JSBool js_cocos2dx_extension_CCEditBox_setAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_getText(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setContentSize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_getPlaceHolder(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setInputMode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setPlaceholderFontColor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setFontColor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setPlaceholderFont(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_initWithSizeAndBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setPlaceHolder(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setPosition(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setReturnType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_getMaxLength(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setInputFlag(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setText(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setMaxLength(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setFont(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_setVisible(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_cocos2dx_extension_CCEditBox_CCEditBox(JSContext *cx, uint32_t argc, jsval *vp);
#endif

