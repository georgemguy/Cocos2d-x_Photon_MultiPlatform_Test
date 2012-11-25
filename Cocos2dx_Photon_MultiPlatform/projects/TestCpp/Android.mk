LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_testcpp_common

LOCAL_MODULE_FILENAME := libtestcppcommon

LOCAL_PHOTON_ROOT := $(LOCAL_PATH)/../../Photon-AndroidNDK_v3-0-4-0_SDK

LOCAL_SRC_FILES := \
Classes/PhotonTest/Photon_lib.cpp \
Classes/PhotonTest/PhotonTest.cpp \
Classes/PhotonTest/StdIO_UIListener.cpp \
Classes/PhotonTest/ControlPhoton.cpp \
Classes/PhotonLoadBalancingTest/NetworkLogic.cpp \
Classes/PhotonLoadBalancingTest/CCLobbyView.cpp \
Classes/PhotonLoadBalancingTest/CCNetworkLogic.cpp \
Classes/PhotonLoadBalancingTest/PhotonLoadBalancingTest.cpp \
Classes/PhotonLoadBalancingTest/CCRoomTableCell.cpp \
Classes/PhotonLoadBalancingTest/CCControlConfirmMessage.cpp \
Classes/PhotonLoadBalancingTest/CCChatRoom.cpp \
Classes/PhotonLoadBalancingTest/CCChatTableCell.cpp \
Classes/PhotonLoadBalancingTest/CCRoomInfo.cpp \
Classes/PhotonLoadBalancingTest/CCRemoveFromParent.cpp \
Classes/PhotonLoadBalancingTest/CCEnable.cpp \
Classes/PhotonLoadBalancingTest/CCRecursiveAction.cpp \
Classes/controller.cpp \
Classes/testBasic.cpp \
Classes/AppDelegate.cpp 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

LOCAL_STATIC_LIBRARIES := photon-cpp-static-prebuilt common-cpp-static-prebuilt photon-c-static-prebuilt loadbalancing-cpp-static-prebuilt

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
            
include $(BUILD_STATIC_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,cocos2dx)
$(call import-module,extensions)

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
$(call import-add-path-optional, $(LOCAL_PHOTON_ROOT)/LoadBalancing-cpp/android/src)
$(call import-add-path-optional, $(LOCAL_PHOTON_ROOT)/LoadBalancing-cpp)
$(call import-module,loadbalancing-cpp-prebuilt)