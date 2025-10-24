/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "integration_xbpal.h"
#include "fcserr.h"
#include "fcslog.h"
#include <stddef.h>
#include <stdio.h>

struct integration_xbpal_context *g_integration_xbpal_context_ptr = NULL;

/* Implemented function from xboot_pal_types.h */
int xbpal_gpio_get_pin(
	uint8_t chip, uint32_t pin, uint8_t *state)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->gpio_get_pin))
		return context->functions->gpio_get_pin(context,
						chip, pin, state);

	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}

int xbpal_gpio_set_config(
		uint8_t chip, uint32_t pin, struct xbpal_gpio_cfg *cfg)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->gpio_set_config))
		return context->functions->gpio_set_config(context,
						chip, pin, cfg);
	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}

uint32_t xbpal_get_boot_time(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->get_boot_time))
		return context->functions->get_boot_time(context);

	printf("Not handled!\n");
	return 0;
}

int xbpal_timer_register_cb(
	void **ctx, void (*xbpal_timer_cb)(void *arg), uint32_t timeout,
	void *arg)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->timer_register))
		return context->functions->timer_register(context,
							ctx,
							xbpal_timer_cb,
							timeout,
							arg);

	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}

int xbpal_timer_deregister_cb(void *timer_context)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->timer_deregister))
		return context->functions->timer_deregister(context,
						timer_context);

	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}

void xbpal_delay_us(uint32_t time_us)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->delay_us)) {
		context->functions->delay_us(context,
						time_us);
		return;
	}

	printf("Not handled!\n");
}

uint32_t xbpal_get_startup_bits(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->get_startup_bits))
		return context->functions->get_startup_bits(context);

	printf("Not handled!\n");
	return 0;
}

uint32_t xbpal_get_wb_reason(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->get_wb_reason))
		return context->functions->get_wb_reason(context);

	printf("Not handled!\n");
	return 0;
}

enum xbpal_warmboot_t xbpal_translate_wb_reason(uint32_t raw_reason)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->translate_wb_reason))
		return context->functions->translate_wb_reason(context,
								raw_reason);

	printf("Not handled!\n");
	return XBPAL_WB_INVALID;
}

void xbpal_clear_wb_reason(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->clear_wb_reason)) {
		context->functions->clear_wb_reason(context);
		return;
	}

	printf("Not handled!\n");
}

bool xbpal_usb_vbus_detect(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->usb_vbus_detect))
		return context->functions->usb_vbus_detect(context);

	printf("Not handled!\n");
	return false;
}

bool xbpal_usb_otg_detect(enum xbpal_ServiceOtgRid_t *otg_state)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->usb_otg_detect))
		return context->functions->usb_otg_detect(context,
								otg_state);

	printf("Not handled!\n");
	return false;
}

bool xbpal_boot_into_recovery(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->boot_into_recovery != NULL))
		return context->functions->boot_into_recovery(context);

	printf("Not handled!\n");
	return false;
}

bool xbpal_pwr_button_pressed(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->pwr_button_pressed))
		return context->functions->pwr_button_pressed(context);

	printf("Not handled!\n");
	return false;
}

bool xbpal_rst_button_pressed(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->rst_button_pressed))
		return context->functions->rst_button_pressed(context);

	printf("Not handled!\n");
	return false;
}

bool xbpal_kbd_button_pressed(uint8_t row, uint8_t col)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->kbd_button_pressed))
		return context->functions->kbd_button_pressed(context,
								row, col);

	printf("Not handled!\n");
	return false;
}

bool xbpal_erase_user_sensitive(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->erase_user_sensitive))
		return context->functions->erase_user_sensitive(context);

	printf("Not handled!\n");
	return false;
}

int xbpal_unlock_bootloader(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->unlock_bootloader))
		return context->functions->unlock_bootloader(context);

	printf("Not handled!\n");
	return false;
}

int xbpal_lock_bootloader(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->lock_bootloader))
		return context->functions->lock_bootloader(context);

	printf("Not handled!\n");
	return false;
}

bool xbpal_reset_detect(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->reset_detect))
		return context->functions->reset_detect(context);

	printf("Not handled!\n");
	return false;
}

void xbpal_vibrate(uint32_t when_us, uint32_t duration_us)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->vibrate)) {
		context->functions->vibrate(context,
					when_us, duration_us);
		return;
	}

	printf("Not handled!\n");
}

bool xbpal_rgb_led_ctl(enum xbpal_rgb_led_cfg_t cfg)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->rgb_led_ctl))
		return context->functions->rgb_led_ctl(context,
							cfg);

	printf("Not handled!\n");
	return false;
}

void xbpal_shutdown(enum xbpal_shutdown_reason_t reason)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->shutdown)) {
		context->functions->shutdown(context,
					reason);
		return;
	}

	printf("Not handled!\n");
}

int xbpal_get_version_string(char **version_string)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->get_version_string))
		return context->functions->get_version_string(context,
						version_string);

	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}

int xbpal_get_frp_data_size(
	uint32_t *data_sz)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->get_frp_data_size != NULL))
		return context->functions->get_frp_data_size(context,
				data_sz);

	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}

int xbpal_read_frp_data(uint8_t *data, uint32_t data_sz)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->read_frp_data != NULL))
		return context->functions->read_frp_data(context,
				data,
				data_sz);

	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}

int xbpal_reset_vbmeta_counters(void)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->reset_vbmeta_counters != NULL))
		return context->functions->reset_vbmeta_counters(context);

	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}

int xbpal_read_vbmeta_counters(uint64_t *cnt_buf, uint32_t vector_size)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->read_vbmeta_counters != NULL))
		return context->functions->read_vbmeta_counters(
			context, cnt_buf, vector_size);

	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}

int fcs_urand(uint8_t *buf, uint16_t len)
{
	struct integration_xbpal_context *context =
		g_integration_xbpal_context_ptr;

	if ((context != NULL) &&
		(context->functions != NULL) &&
		(context->functions->fcs_urand != NULL))
		return context->functions->fcs_urand(
			context, buf, len);

	printf("Not handled!\n");
	return -FCSERR_ENIMP;
}

int xbpal_get_avb_version(void)
{
	FCS_LOG_WRN("%s: Test not implemented\n", __func__);
	return FCSERR_OK;
}
