LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(fsobjs:.o=.c)
LOCAL_SRC_FILES += $(fsobjs_asm:.o=.S)
LOCAL_CFLAGS := -Wall\
                -Werror\
                $(EXTRA_CPPFLAGS) \
                -DTBASE_API_LEVEL=3

LOCAL_STATIC_LIBRARIES := \
    $(CFG_CRYPTOLIB)_libcrypto_static

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libc \
    liblog \
    libMcClient

LOCAL_ADDITIONAL_DEPENDENCIES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

LOCAL_C_INCLUDES := $(addprefix $(LOCAL_PATH)/, $(include_dirs))
LOCAL_C_INCLUDES += $(call include-path-for, system-core)/cutils
LOCAL_C_INCLUDES += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_C_INCLUDES += external/$(CFG_CRYPTOLIB)/include
LOCAL_C_INCLUDES += \
                    $(TOPDIR)vendor/sony/trustlets/sonytzappxflattest/inc \
                    $(TOPDIR)vendor/mediatek/proprietary/trustzone/trustonic/source/bsp/platform/mt6757/t-sdk/TlcSdk/Out/Public \
                    $(TOPDIR)vendor/mediatek/proprietary/trustzone/trustonic/source/bsp/platform/mt6757/t-sdk/TlcSdk/Out/Public/GP/ \
                    $(TOPDIR)vendor/mediatek/proprietary/trustzone/trustonic/source/bsp/platform/mt6757/t-sdk/TlSdk/Out/Public/MobiCore/inc

include $(BUILD_EXECUTABLE)
