deps-li-objs := main.o
deps-li-objs += input_args.o
deps-li-objs += log.o
ifeq ($(CFG_TR_FILE),y)
deps-li-objs += tr_file.o
else ifeq ($(CFG_TR_PIPE),y)
deps-li-objs += tr_pipe.o
else
deps-li-objs += ffs.o
endif
deps-li-objs += power.o
deps-li-objs += uevent_handler.o
deps-li-objs += linux_util.o
deps-li-objs += fcsenv_int.o
deps-li-objs += safe_boot.o
deps-li-objs += ks_int.o
ifeq ($(CFG_SHIP_MODE),y)
deps-li-objs += shipmode.o
else
deps-li-objs += shipmode_stub.o
endif
deps-li-objs += ext_modem.o
deps-li-objs := $(addprefix integration/linux/,$(deps-li-objs))
fsobjs += $(deps-li-objs)

deps-cm-objs := eroot.o
deps-cm-objs += qfprom_fec.o
deps-cm-objs += tar_utils.o
deps-cm-objs := $(addprefix integration/common/,$(deps-cm-objs))
fsobjs += $(deps-cm-objs)

deps-prop-objs := fcs_prop.o
ifeq ($(CFG_ANDROID), y)
deps-prop-objs := $(addprefix integration/android/,$(deps-prop-objs))
else
deps-prop-objs := $(addprefix integration/linux/,$(deps-prop-objs))
endif
fsobjs += $(deps-prop-objs)

ifeq ($(CFG_ANDROID), y)
include_dirs += integration/android/include
else
include_dirs += integration/linux/include_weak
endif

ifeq ($(CFG_TEST),y)
mt-objs := module_test.o
mt-objs += module_derparser.o
mt-objs += module_asahi.o
mt-objs := $(addprefix test/module_test/,$(mt-objs))
fsobjs += $(mt-objs)

include_dirs += test/include

endif

deps-st-objs := init.o
deps-st-objs += emmc.o
deps-st-objs += ufs.o
deps-st-objs += file.o
deps-st-objs += ram.o
deps-st-objs += heap.o
deps-st-objs := $(addprefix integration/linux/storage/,$(deps-st-objs))
fsobjs += $(deps-st-objs)

deps-ta-objs := ta.o
deps-ta-objs := $(addprefix $(TA_DIR)/tad/src/,$(deps-ta-objs))
fsobjs += $(deps-ta-objs)

include_dirs += integration/common/include
include_dirs += integration/linux/include
include_dirs += integration/linux/arch/include
include_dirs += integration/linux/storage/include
include_dirs += ../../system/core/miscta/tad/src
include_dirs += ../../system/core/miscta/tad/common
include_dirs += ../../system/core/miscta/libmiscta/inc
include_dirs += core/util/include
include_dirs += ../certs

include_dirs += integration/$(FCS_PLATFORM)/include
include_dirs += integration/$(PLATFORM_VENDOR)/include

include_dirs += integration/crypto/$(CFG_CRYPTOLIB)/include

deps-pf-see-objs := xflattest_int.o
ifeq ($(CFG_STUB_QSEE),y)
deps-pf-see-objs := $(addprefix integration/$(PLATFORM_VENDOR)_stubs/,$(deps-pf-see-objs))
else
deps-pf-see-objs := $(addprefix integration/$(PLATFORM_VENDOR)/,$(deps-pf-see-objs))
endif
fsobjs += $(deps-pf-see-objs)

deps-pf-objs := ab_int.o
deps-pf-objs += core_int.o
deps-pf-objs += flash_handler.o
deps-pf-objs += otp.o
deps-pf-objs += ufs_int.o
deps-pf-objs += emmc_int.o
deps-pf-objs := $(addprefix integration/$(PLATFORM_VENDOR)/,$(deps-pf-objs))
fsobjs += $(deps-pf-objs)

deps-fb-objs := core_xfl.o
deps-fb-objs += fcs_roots.o
deps-fb-objs += fcs_sbu.o
deps-fb-objs += fcs_fastboot_partitions.o
deps-fb-objs := $(addprefix integration/$(FCS_PLATFORM)/,$(deps-fb-objs))
fsobjs += $(deps-fb-objs)

deps-crypto-objs := authenticate.o
deps-crypto-objs += digest.o
deps-crypto-objs += certificate_chain.o
deps-crypto-objs += rule.o
deps-crypto-objs += core.o
deps-crypto-objs += cryp_util.o
deps-crypto-objs += signature.o
deps-crypto-objs := $(addprefix integration/crypto/$(CFG_CRYPTOLIB)/,$(deps-crypto-objs))
fsobjs += $(deps-crypto-objs)

ifeq ($(CFG_GFX),y)
fsobjs_cc := loader/gfx/fcsgfx.o
else
fsobjs += loader/gfx/fcsgfx_stub.o
endif
include_dirs += loader/gfx/include
