LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

SRC_PATH := ../../Classes

LOCAL_MODULE := game_framework_static

LOCAL_MODULE_FILENAME := libgame_framework

LOCAL_SRC_FILES := gameframework/HaypiJSBFunc.cpp \
									 gameframework/Lock.cpp \
                   gameframework/NetManager.cpp \
                   gameframework/main.cpp \
                   $(SRC_PATH)/AppDelegate.cpp \
                   $(SRC_PATH)/Base.cpp \
                   $(SRC_PATH)/CommonLayer.cpp \
                   $(SRC_PATH)/GameDelegate.cpp \
                   $(SRC_PATH)/GameScene.cpp \
                   $(SRC_PATH)/HFileUtils.cpp \
                   $(SRC_PATH)/HRichLabelTTF.cpp \
                   $(SRC_PATH)/HString.cpp \
                   $(SRC_PATH)/Haypi-Animation/AnimationPlayerMgr.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpAnimBuildVisitor.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpAnimRenderVisitor.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpAnimaKeyframe.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpAnimaStatus.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpAnimate.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpAnimation.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpAttachPoint.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpBinaryReader.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpCharaInst.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpCharactor.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpCharactorBinParser.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpCharactorManager.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpCharactorXmlParser.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpGlobalFunc.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpImageKeyframe.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpInterpHolder.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpKeyframe.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpLayer.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpLinearInterpolator.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpLog.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpNullKeyframe.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpRenderVisitorStack.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpSplineInterpolator.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpStack.cpp \
                   $(SRC_PATH)/Haypi-Animation/ccColorExtension.cpp \
                   $(SRC_PATH)/Haypi-Animation/HpTextureAtlas.cpp \
                   $(SRC_PATH)/Haypi-Crypt/Crypt.cpp \
                   $(SRC_PATH)/Haypi-Update/TriVersion.cpp \
                   $(SRC_PATH)/Haypi-Update/UpdateManager.cpp \
                   $(SRC_PATH)/json/json_value.cpp \
                   $(SRC_PATH)/json/json_reader.cpp \
                   $(SRC_PATH)/json/json_writer.cpp \
                   $(SRC_PATH)/LoadingLayer.cpp \
                   $(SRC_PATH)/MusicManager.cpp \
                   $(SRC_PATH)/NetManager_imp.cpp \
                   $(SRC_PATH)/Object.cpp \
                   $(SRC_PATH)/RootLayer.cpp \
                   $(SRC_PATH)/SourceCache.cpp \
                   $(SRC_PATH)/SpriteFrame.cpp \
                   $(SRC_PATH)/Thread.cpp \
                   $(SRC_PATH)/TimeHelper.cpp \
                   $(SRC_PATH)/Timer.cpp \
                   $(SRC_PATH)/UILayer.cpp \
                   $(SRC_PATH)/ViewExtentions.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
							$(LOCAL_PATH)/../../boost

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
							$(LOCAL_PATH)/../../Classes/Haypi-JSB \
							$(LOCAL_PATH)/../../Classes/Haypi-JSB/others \
							$(LOCAL_PATH)/../../Classes/Haypi-Crypt \
							$(LOCAL_PATH)/../../Classes/Haypi-Update \
							$(LOCAL_PATH)/../../Classes/Haypi-Animation

ifeq ($(NDK_DEBUG),1)
  LOCAL_CFLAGS += -fexceptions -DUSE_FILE32API -DHOS_LINUX -DCOCOS2D_DEBUG=1 -DDEBUG -DHLOGLEVEL=31
else
  LOCAL_CFLAGS += -fexceptions -DUSE_FILE32API -DHOS_LINUX -DCOCOS2D_DEBUG=0 -DHLOGLEVEL=0
endif
$(info LOCAL_CFLAGS = $(LOCAL_CFLAGS))


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += scriptingcore-spidermonkey
LOCAL_WHOLE_STATIC_LIBRARIES += spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static

include $(BUILD_STATIC_LIBRARY)
# include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,extensions)
$(call import-module,scripting/javascript/spidermonkey-android)
$(call import-module,external/chipmunk)
$(call import-module,scripting/javascript/bindings)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
