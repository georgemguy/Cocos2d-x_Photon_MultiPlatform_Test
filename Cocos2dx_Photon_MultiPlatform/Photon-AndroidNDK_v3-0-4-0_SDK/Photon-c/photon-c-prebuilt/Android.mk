# Photon-c

LOCAL_PATH := $(call my-dir)

lib_photon_c_path := $(LOCAL_PATH)

lib_photon_c_includes := $(lib_photon_c_path)/../inc \
                         $(lib_photon_c_path)/../../../inc

lib_common_c_includes := $(lib_photon_c_path)/../../Common-c/inc \
                         $(lib_photon_c_path)/../../../../Common-c/inc \
                         $(lib_photon_c_path)/../../../../Common-c/inc/platform_definitions/android

lib_suffix := ${APP_OPTIM}_android_${APP_ABI}

lib_photon_c_static_name := photon-c-static_${lib_suffix}

include $(CLEAR_VARS)
LOCAL_MODULE := photon-c-static-prebuilt
LOCAL_SRC_FILES := lib$(lib_photon_c_static_name).a
LOCAL_EXPORT_C_INCLUDES := $(lib_common_c_includes) $(lib_photon_c_includes)
LOCAL_STATIC_LIBRARIES  := common-c-static-prebuilt
include $(PREBUILT_STATIC_LIBRARY)

$(call import-add-path-optional, $(shell pwd)/../../../../Common-c/src/android)
$(call import-add-path-optional, $(shell pwd)/../../Common-c)
$(call import-module,common-c-prebuilt)
