#
# Copyright (C) 2015 Sony Mobile Communications Inc.
# All rights, including trade secret rights, reserved.
#

# ************************************************
# file: image.mk
# Make file for composing the ramdump flash image
# ************************************************

# Target partition can be overridden by config.mk
ifeq ($(RAMDUMP_TARGET_PARTITION), )
RAMDUMP_TARGET_PARTITION := rdimage
endif

RAMDUMP_MKBOOTIMG := $(HOST_OUT_EXECUTABLES)/mkbootimg
SEMCSC := $(HOST_OUT_EXECUTABLES)/semcsc.py

$(TARGET_OUT_DEBIAN):
	$(hide) mkdir -p $@

RAMDUMP_TARGET_DEPENDS := $(TARGET_PREBUILT_KERNEL)
RAMDUMP_TARGET_DEPENDS += $(RAMDUMP_RAMDISK_TARGET)

RAMDUMP_MKBOOTIMG_ARGS= \
	--kernel $(TARGET_PREBUILT_KERNEL) \
	--base $(RAMDUMP_KERNEL_BASE) \
	--ramdisk $(RAMDUMP_RAMDISK_TARGET) \
	--pagesize $(BOARD_KERNEL_PAGESIZE) \
	--header_version $(BOARD_BOOT_HEADER_VERSION)

ifdef RAMDUMP_KERNEL_TAGS_OFFSET
RAMDUMP_MKBOOTIMG_ARGS += --tags_offset $(RAMDUMP_KERNEL_TAGS_OFFSET)
endif

ifdef RAMDUMP_KERNEL_CMDLINE
RAMDUMP_MKBOOTIMG_ARGS += --cmdline "$(RAMDUMP_KERNEL_CMDLINE)"
endif

ifdef RAMDUMP_KERNEL_OFFSET
RAMDUMP_MKBOOTIMG_ARGS += --kernel_offset $(RAMDUMP_KERNEL_OFFSET)
endif

RAMDUMP_MKBOOTIMG_ARGS += --dtb $(INSTALLED_DTBIMAGE_TARGET)
RAMDUMP_TARGET_DEPENDS += $(INSTALLED_DTBIMAGE_TARGET)
ifeq ($(strip $(BOARD_KERNEL_SEPARATED_DT)),true)
RAMDUMP_MKBOOTIMG_ARGS += --dt $(RAMDUMP_DTIMAGE_TARGET)
RAMDUMP_TARGET_DEPENDS += $(RAMDUMP_DTIMAGE_TARGET)
endif

RAMDUMP_TARGET_IMAGE_NAME=$(PRODUCT_OUT)/ramdump/ramdump.img
$(RAMDUMP_TARGET_IMAGE_NAME) : $(RAMDUMP_TARGET_DEPENDS)
	@echo "Building ramdump.img"
	$(RAMDUMP_MKBOOTIMG) $(RAMDUMP_MKBOOTIMG_ARGS) --output $@
	$(hide) cp $@ $(PRODUCT_OUT)/ramdump.img

ifeq ($(TARGET_QC_SIGNED),true)
RAMDUMP_TARGET_IMAGE_SEC_NAME := $(PRODUCT_OUT)/ramdump/ramdump.img.secure

ifndef TARGET_SHA_TYPE
TARGET_SHA_TYPE := sha256
endif

ifndef TARGET_PRIVATE_KEY
TARGET_PRIVATE_KEY := device/qcom/common/qcom.key
endif

define build-secure-image
	$(hide) mv -f $(1) $(1).nonsecure
	$(hide) openssl dgst -$(TARGET_SHA_TYPE) -binary $(1).nonsecure > $(1).$(TARGET_SHA_TYPE)
	$(hide) openssl rsautl -sign -in $(1).$(TARGET_SHA_TYPE) -inkey $(TARGET_PRIVATE_KEY) -out $(1).sig
	$(hide) dd if=/dev/zero of=$(1).sig.padded bs=$(BOARD_KERNEL_PAGESIZE) count=1
	$(hide) dd if=$(1).sig of=$(1).sig.padded conv=notrunc
	$(hide) cat $(1).nonsecure $(1).sig.padded > $(1).secure
	$(hide) rm -rf $(1).$(TARGET_SHA_TYPE) $(1).sig $(1).sig.padded
	$(hide) mv -f $(1).secure $(1)
endef

$(RAMDUMP_TARGET_IMAGE_SEC_NAME) : $(RAMDUMP_TARGET_IMAGE_NAME)
	$(call build-secure-image,$(RAMDUMP_TARGET_IMAGE_NAME))
endif

ifeq ($(RAMDUMP_TARGET_IMAGE_FORMAT),qct_boot)
.PHONY: ramdump
ramdump: $(RAMDUMP_TARGET_IMAGE_SEC_NAME)
else ifeq ($(RAMDUMP_TARGET_IMAGE_FORMAT),s1_boot)
# S1 boot image target

ifeq ($(RAMDUMP_TARGET_INTERNAL_SIGNING),true)
$(PRODUCT_OUT)/ramdump/ramdump.elf: $(RAMDUMP_TARGET_IMAGE_NAME) $(RAMDUMP_TARGET_IMAGE_SEC_NAME) $(PRODUCT_PARTITION_CONFIG)
	@echo "Internal signing ramdump image"
	$(SEMCSC) -c $(PRODUCT_PARTITION_CONFIG) -p $(RAMDUMP_TARGET_PARTITION) -t internal \
		-i $< -o $@ --createheader
	$(hide) cp $@ $(PRODUCT_OUT)/ramdump.elf

$(PRODUCT_OUT)/ramdump/ramdump.sin: $(PRODUCT_OUT)/ramdump/ramdump.elf $(PRODUCT_PARTITION_CONFIG)
	@echo "External signing ramdump image"
	@echo target SIN: $(notdir $@)
	$(hide) $(SEMCSC) -c $(PRODUCT_PARTITION_CONFIG) -p $(RAMDUMP_TARGET_PARTITION) -t external \
		-i $< -o $@ --createheader
	$(hide) cp $@ $(PRODUCT_OUT)/ramdump.sin
else
$(PRODUCT_OUT)/ramdump/ramdump.sin: $(RAMDUMP_TARGET_IMAGE_NAME) $(RAMDUMP_TARGET_IMAGE_SEC_NAME) $(PRODUCT_PARTITION_CONFIG)
	@echo "External signing ramdump image"
	@echo target SIN: $(notdir $@)
	$(hide) $(SEMCSC) -c $(PRODUCT_PARTITION_CONFIG) -p $(RAMDUMP_TARGET_PARTITION) -t external \
		-i $< -o $@ --createheader
	$(hide) cp $@ $(PRODUCT_OUT)/ramdump.sin
endif

.PHONY: ramdump
ifeq ($(RAMDUMP_TARGET_SIN), true)
ramdump: $(PRODUCT_OUT)/ramdump/ramdump.sin sin-tools
else
ramdump: $(RAMDUMP_TARGET_IMAGE_NAME)
endif
else
$(error Output format not defined or wrong = $(RAMDUMP_TARGET_IMAGE_FORMAT))
endif

.PHONY: ramdumpclean
ramdumpclean:
	@echo Cleaning ramdump dir...
	$(hide) rm -rf $(PRODUCT_OUT)/ramdump/*
