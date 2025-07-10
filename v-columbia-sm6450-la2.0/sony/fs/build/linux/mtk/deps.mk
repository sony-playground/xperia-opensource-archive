deps-v-objs := xfl_tz.o
deps-v-objs := $(addprefix integration/$(PLATFORM_VENDOR)/,$(deps-v-objs))
fsobjs += $(deps-v-objs)
