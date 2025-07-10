ifndef XFL_BUILD_NUMBER
  XFL_BUILD_NUMBER := $(shell echo $${USER:0:8}).$(shell $(DATE) +%Y%m%d.%H%M%S)
endif

PLATFORM_VENDOR=qc
CFG_STUB_QSEE := n
CFG_SHIP_MODE := y
# Config used to enable the display in xfl
CFG_GFX := y

# Set CFG_STUB_UFS_PURGE to n when the PURGE_STATUS_ constants are available
CFG_STUB_UFS_PURGE := n
CFG_ANDROID := y
CFG_CRYPTOLIB := mbedtls
CFG_PRELOADER := ""
EXTRA_CPPFLAGS += \
-DCFG_ENABLE_FCS_LOG -DCFG_USB3 -DPRELOADER=\"$(CFG_PRELOADER)\"

EXTRA_CPPFLAGS += \
-DBUILD_NUMBER=\"$(XFL_BUILD_NUMBER)\"
