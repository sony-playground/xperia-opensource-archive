TA_DIR = ../ta/

include $(MAIN_DIR)/build/linux/$(FCS_PLATFORM)/cfg_lnx.mk
include $(MAIN_DIR)/build/objs.mk
include $(MAIN_DIR)/build/linux/deps.mk

src = $(fsobjs:.o=.c)
src := $(addprefix $(MAIN_DIR)/,$(src))
fsobjs := $(addprefix $(OUT_DIR)/xfl_obj/,$(fsobjs))

CC = $(CROSS_DIR)/$(CROSS_PREFIX)gcc

cflags = -Wall -Werror -Wno-unused-function -march=armv8-a -fPIE
cflags += $(EXTRA_CPPFLAGS)

ldflags = -lssl -lcrypto -lQSEEComAPI -llog -pie
ldflags += -L$(OPENSSL_DIR)
ldflags += --sysroot=$(SYSROOT_DIR)
ldflags += -L$(PREBUILT_DIR)/vendor/lib64/

include_dirs := $(addprefix -I$(MAIN_DIR)/,$(include_dirs))
include_dirs += -I$(OPENSSL_DIR)/include
include_dirs += -I$(TA_ROOT_DIR)/libmiscta/inc
include_dirs += -I$(TA_ROOT_DIR)/tad/src
include_dirs += -I$(TA_ROOT_DIR)/tad/common
include_dirs += -I$(SECMSM_DIR)/QSEEComAPI

$(OUT_DIR)/xfl_obj/%.o:$(MAIN_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(cflags) $(include_dirs)

$(OUT_DIR)/xfl: $(fsobjs) $(fsobjs_asm)
	$(CC) -o $@ $^ $(cflags) $(ldflags)

.PHONY: xfl
xfl: $(OUT_DIR)/xfl
