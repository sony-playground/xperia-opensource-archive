LOCAL_PATH:= $(call my-dir)/../..

include $(CLEAR_VARS)

include $(LOCAL_PATH)/build/linux/android_inc.mk
LOCAL_MODULE := lilo
include $(LOCAL_PATH)/build/linux/$(FCS_PLATFORM)/android_build.mk

include $(CLEAR_VARS)
CFG_TR_FILE := y
CFG_TR_PIPE := n
CFG_TEST := y
include $(LOCAL_PATH)/build/linux/android_inc.mk
LOCAL_MODULE := lilo_test
include $(LOCAL_PATH)/build/linux/$(FCS_PLATFORM)/android_build.mk
