LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(fsobjs:.o=.c)
LOCAL_SRC_FILES += $(fsobjs_asm:.o=.S)
LOCAL_SRC_FILES += $(fsobjs_cc:.o=.cc)

LOCAL_CFLAGS := -Wall\
                -Werror\
                -Wno-unused-function\
                $(EXTRA_CPPFLAGS)
LOCAL_PROPRIETARY_MODULE := true

ifeq ($(CFG_STUB_UFS_PURGE),y)
LOCAL_CFLAGS += -DCFG_STUB_UFS_PURGE
endif

LOCAL_STATIC_LIBRARIES := \
    $(CFG_CRYPTOLIB)_libcrypto_static

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libc \
    liblog

ifneq ($(CFG_STUB_QSEE),y)
LOCAL_SHARED_LIBRARIES += \
    libQSEEComAPI
endif

LOCAL_ADDITIONAL_DEPENDENCIES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

LOCAL_C_INCLUDES := $(addprefix $(LOCAL_PATH)/, $(include_dirs))
LOCAL_C_INCLUDES += $(call include-path-for, system-core)/cutils
LOCAL_C_INCLUDES += vendor/qcom/proprietary/securemsm/QSEEComAPI
LOCAL_C_INCLUDES += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_C_INCLUDES += external/$(CFG_CRYPTOLIB)/include

LOCAL_CPP_EXTENSION := .cc

ifeq ($(CFG_GFX),y)
LOCAL_SHARED_LIBRARIES += libminui_fcs
LOCAL_SHARED_LIBRARIES += libbase libpng
LOCAL_C_INCLUDES += bootable/recovery/minui/include/minui
endif

include $(BUILD_EXECUTABLE)
