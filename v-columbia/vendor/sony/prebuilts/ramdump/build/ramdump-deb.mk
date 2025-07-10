#
# Copyright (C) 2014 Sony Mobile Communications Inc.
# All rights, including trade secret rights, reserved.
#

# ************************************************
# file: deb.mk
# Make file for creating deb files
# ************************************************

.PHONY: ramdumpdeb

ramdumpdeb: ramdump
	CREATEPACKAGE=$(SYS_CREATEPACKAGE) $(RAMDUMP_TOP_DIR)/build/scripts/create_deb.sh $(SOMC_PLATFORM) $(RAMDUMPER_BUILD_ID)
