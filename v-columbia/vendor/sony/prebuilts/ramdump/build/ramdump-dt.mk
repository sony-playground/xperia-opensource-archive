#
# Copyright (C) 2015 Sony Mobile Communications Inc.
# All rights, including trade secret rights, reserved.
#

# *******************************************
# file: dt.mk
# Make file for compiling the dt
# *******************************************

ifeq ($(strip $(BOARD_KERNEL_SEPARATED_DT)),true)
RAMDUMP_DTIMAGE_TARGET := $(PRODUCT_OUT)/ramdump/ramdump-dt.img
ifeq ($(RAMDUMP_DTB_DIR),)
RAMDUMP_DTB_DIR := $(KBUILD_OUTPUT)/arch/$(TARGET_KERNEL_ARCH)/boot/dts/qcom/
endif
$(RAMDUMP_DTIMAGE_TARGET) : $(DTBTOOL) $(RAMDUMP_KERNEL_IMG)
	@echo "Building dt image"
	$(DTBTOOL) -o $@ -s $(BOARD_KERNEL_PAGESIZE) -p $(KBUILD_OUTPUT)/scripts/dtc/ $(RAMDUMP_DTB_DIR)
endif

