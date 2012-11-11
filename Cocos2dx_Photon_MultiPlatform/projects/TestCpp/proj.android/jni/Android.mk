LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := testcpp_shared

LOCAL_MODULE_FILENAME := libtestcpp

LOCAL_SRC_FILES := testcpp/main.cpp

LOCAL_PHOTON_ROOT := $(LOCAL_PATH)/../../../../Photon-AndroidNDK_v3-0-4-0_SDK
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_CFLAGS := -DEG_DEBUGGER -D__STDINT_LIMITS -D_EG_ANDROID_PLATFORM -lstdc++

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_testcpp_common
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static

LOCAL_STATIC_LIBRARIES := photon-cpp-static-prebuilt common-cpp-static-prebuilt photon-c-static-prebuilt

include $(BUILD_SHARED_LIBRARY)

$(call import-module,projects/TestCpp)
$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)

$(call import-module,android/native_app_glue)
$(call import-add-path-optional, $(LOCAL_PHOTON_ROOT)/Common-c/android/src)
$(call import-add-path-optional, $(LOCAL_PHOTON_ROOT)/Common-c)
$(call import-module,common-c-prebuilt)
$(call import-add-path-optional, $(LOCAL_PHOTON_ROOT)/Common-cpp/android/src)
$(call import-add-path-optional, $(LOCAL_PHOTON_ROOT)/Common-cpp)
$(call import-module,common-cpp-prebuilt)
$(call import-add-path-optional, $(LOCAL_PHOTON_ROOT)/Photon-c/android/src)
$(call import-add-path-optional, $(LOCAL_PHOTON_ROOT)/Photon-c)
$(call import-module,photon-c-prebuilt)
$(call import-add-path-optional, $(LOCAL_PHOTON_ROOT)/Photon-cpp/android/src)
$(call import-add-path-optional, $(LOCAL_PHOTON_ROOT)/Photon-cpp)
$(call import-module,photon-cpp-prebuilt)