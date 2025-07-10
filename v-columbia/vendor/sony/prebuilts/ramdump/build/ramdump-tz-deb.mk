#
# Copyright (C) 2015 Sony Mobile Communications Inc.
# All rights, including trade secret rights, reserved.
#

# ************************************************
# file: Android-ramdump-deb.mk
# Makefile for downloading prebuilt ramdump images
# ************************************************

debian_rd_pkgdownloadlist_file  := $(PRODUCT_OUT)/downloaded-ramdump-packages.txt
RAMDUMP_DEB_SIN_PKG_FILES := $(TOPDIR)vendor/semc/build/system-snapshot/packages.xml
RAMDUMP_PACKAGES_AMSS_NAME := $(TARGET_AMSS_NAME)
RAMDUMP_REQUIRED_PACKAGE_NAMES := fw-tztpm-$(RAMDUMP_PACKAGES_AMSS_NAME) \
				   fw-commonlib-$(RAMDUMP_PACKAGES_AMSS_NAME)
RAMDUMP_DEB_SIN_PKG_LIST := $(addprefix -p,$(RAMDUMP_REQUIRED_PACKAGE_NAMES))

define download-ramdump-deb-packages-from-file
$(SEMC_SYSTEM_PATH)/download_packages.py -o $(TARGET_OUT_DEBIAN) \
	-l $(1) --exclude-label-component android \
	--exclude-label-component android-debug \
	--exclude-label-component android-test $(2) \
	$(if $(C2D_REPO),-r $(C2D_REPO)) \
	--listdownload $(PRODUCT_OUT)/downloaded-ramdump-packages.txt
endef

download-ramdump-deb: $(TARGET_OUT_DEBIAN)
	$(hide) $(call download-ramdump-deb-packages-from-file,$(RAMDUMP_DEB_SIN_PKG_FILES),$(RAMDUMP_DEB_SIN_PKG_LIST)) > /dev/null

extract-ramdump-deb: SEMC_SYSTEM_PATH := $(TOPDIR)vendor/semc/build/semcsystem
extract-ramdump-deb: $(TARGET_OUT_DEBIAN) download-ramdump-deb
	$(hide) $(call extract-deb-for-sin,$(RAMDUMP_REQUIRED_PACKAGE_NAMES),$(PRODUCT_OUT)/semc/system/etc/firmware,'img*/*')
