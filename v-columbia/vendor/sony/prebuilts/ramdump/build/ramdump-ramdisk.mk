#
# Copyright (C) 2015 Sony Mobile Communications Inc.
# All rights, including trade secret rights, reserved.
#

# *************************************
# file: ramdisk.mk
# makefile for prebuilt ramdisk image
# *************************************


RAMDUMP_PREBUILT_RAMDISK_TARGET := $(RAMDUMP_PLATFORM_DIR)/prebuilt/ramdump-ramdisk.img
RAMDUMP_RAMDISK_TARGET := $(OUT_DIR)/ramdump-ramdisk.img

$(RAMDUMP_RAMDISK_TARGET) : $(OUT_DIR) $(RAMDUMP_PREBUILT_RAMDISK_TARGET)
	$(hide) cp -f $(RAMDUMP_PREBUILT_RAMDISK_TARGET) $@
