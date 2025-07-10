TA_DIR = ../../system/core/miscta/

include $(LOCAL_PATH)/build/linux/$(FCS_PLATFORM)/cfg.mk
include $(LOCAL_PATH)/build/objs.mk
include $(LOCAL_PATH)/build/linux/deps.mk

# Include vendor specific integration code
-include $(LOCAL_PATH)/build/linux/$(PLATFORM_VENDOR)/deps.mk
#$(hide $(shell ($(LOCAL_PATH)/tools/asn1c_compiler/asn1c.sh)))
#include $(LOCAL_PATH)/tools/asn1c_compiler/autogen_obj.mk
