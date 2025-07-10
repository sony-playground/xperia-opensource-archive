/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_XBPAL_H_
#define INTEGRATION_XBPAL_H_

#include "xboot_pal_types.h"
#include <stdarg.h>

struct integration_xbpal_context;

struct integration_xbpal_func {
	int (*gpio_get_pin)(
		struct integration_xbpal_context *context,
		uint8_t chip, uint32_t pin, uint8_t *state);
	int (*gpio_set_config)(
		struct integration_xbpal_context *context,
		uint8_t chip, uint32_t pin, struct xbpal_gpio_cfg *cfg);
	uint32_t (*get_boot_time)(
		struct integration_xbpal_context *context);
	int (*timer_register)(
		struct integration_xbpal_context *context,
		void **ctx,
		void (*timer_cb)(void *arg),
		uint32_t timeout,
		void *arg);
	int (*timer_deregister)(
		struct integration_xbpal_context *context,
		void *timer_context);
	void (*delay_us)(
		struct integration_xbpal_context *context,
		uint32_t time_us);
	uint32_t (*get_startup_bits)(
		struct integration_xbpal_context *context);
	uint32_t (*get_wb_reason)(
		struct integration_xbpal_context *context);
	enum xbpal_warmboot_t (*translate_wb_reason)(
		struct integration_xbpal_context *context,
		uint32_t raw_reason);
	void (*clear_wb_reason)(
		struct integration_xbpal_context *context);
	bool (*usb_vbus_detect)(
		struct integration_xbpal_context *context);
	bool (*usb_otg_detect)(
		struct integration_xbpal_context *context,
		enum xbpal_ServiceOtgRid_t *otg_state);
	bool (*boot_into_recovery)(
		struct integration_xbpal_context *context);
	bool (*pwr_button_pressed)(
		struct integration_xbpal_context *context);
	bool (*rst_button_pressed)(
		struct integration_xbpal_context *context);
	bool (*kbd_button_pressed)(
		struct integration_xbpal_context *context,
		uint8_t row, uint8_t col);
	bool (*erase_user_sensitive)(
		struct integration_xbpal_context *context);
	int (*unlock_bootloader)(
		struct integration_xbpal_context *context);
	int (*lock_bootloader)(
		struct integration_xbpal_context *context);
	bool (*reset_detect)(
		struct integration_xbpal_context *context);
	void (*vibrate)(
		struct integration_xbpal_context *context,
		uint32_t when_us, uint32_t duration_us);
	bool (*rgb_led_ctl)(
		struct integration_xbpal_context *context,
		enum xbpal_rgb_led_cfg_t cfg);
	void (*shutdown)(
		struct integration_xbpal_context *context,
		enum xbpal_shutdown_reason_t reason);
	int (*get_version_string)(
		struct integration_xbpal_context *context,
		char **version_string);
	void (*log)(
		struct integration_xbpal_context *context,
		const char *fmt, va_list ap);
	int (*copy_hw_conf_to_shared_mem)(
		struct integration_xbpal_context *context,
		uint8_t *hw_conf_data,
		uint32_t hw_conf_length);
	int (*get_frp_data_size)(
		struct integration_xbpal_context *context,
		uint32_t *data_sz);
	int (*read_frp_data)(
		struct integration_xbpal_context *context,
		uint8_t *data,
		uint32_t data_sz);
	int (*reset_vbmeta_counters)(
		struct integration_xbpal_context *context);
	int (*read_vbmeta_counters)(
		struct integration_xbpal_context *context,
		uint64_t *cnt_buf,
		uint32_t vector_size);
	int (*fcs_urand)(
		struct integration_xbpal_context *context,
		uint8_t *buf,
		uint16_t len);

};

struct integration_xbpal_context {
	struct integration_xbpal_func *functions;
};

extern struct integration_xbpal_context *g_integration_xbpal_context_ptr;

#endif

