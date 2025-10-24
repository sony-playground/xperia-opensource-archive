deps-pf-qsee-objs := qsee.o
deps-pf-qsee-objs += otp_rw.o
ifeq ($(CFG_STUB_QSEE),y)
deps-pf-qsee-objs := $(addprefix integration/$(PLATFORM_VENDOR)_stubs/,$(deps-pf-qsee-objs))
else
deps-pf-qsee-objs := $(addprefix integration/$(PLATFORM_VENDOR)/,$(deps-pf-qsee-objs))
endif
fsobjs += $(deps-pf-qsee-objs)