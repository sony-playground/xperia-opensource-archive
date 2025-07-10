#
# Copyright (C) 2020 Sony Mobile Communications Inc.
# All rights, including trade secret rights, reserved.
#

# ******************************************************************
# Make file to copy ramdump prebuilt dtbo file into dtbo directory
# ******************************************************************

# Copy ramdump prebuilt dtbo to build as part of dtbo.img
KERNEL_OUT_DIR := out/target/product/$(TARGET_PRODUCT)/obj/kernel/msm-$(TARGET_KERNEL_VERSION)
RAMDUMP_DTBO_DIR := vendor/semc/ramdump/platforms/$(SOMC_PLATFORM)/$(SOMC_TARGET_PRODUCT)

RAMDUMP_PREBUILT_DTBO := $(KERNEL_OUT_DIR)/arch/$(TARGET_KERNEL_ARCH)/boot/dts/vendor/somc/zramdump-$(SOMC_TARGET_PRODUCT)-overlay.dtbo

$(RAMDUMP_PREBUILT_DTBO) : $(INSTALLED_KERNEL_TARGET)
	echo "copying ramdump dtbo $@"
ifneq ($(wildcard $(RAMDUMP_DTBO_DIR)),)
	cp -f $(RAMDUMP_DTBO_DIR)/*.dtbo $@
endif
