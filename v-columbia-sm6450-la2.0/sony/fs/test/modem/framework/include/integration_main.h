/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_MAIN_H_
#define INTEGRATION_MAIN_H_

#define INTG_PROP_COUNTERS	1	/* all call counters */
#define INTG_PROP_CNT_PWRBUTPRS	2	/* call count pwr_button_pressed */
#define INTG_PROP_CNT_CPHWCONF	3	/* call count copy_hw_conf */
#define INTG_PROP_CNT_CLRWBRSN	4	/* call count clear_wb_reason */
#define INTG_PROP_CNT_VIBRATE	5	/* call count vibrate */
#define INTG_PROP_CNT_WRSECDATA	7	/* call count write sec data */
#define INTG_PROP_CNT_WRKSORG	8	/* call count write org ks */
#define INTG_PROP_CNT_WRKSBAK	9	/* call count write bak ks */
#define INTG_PROP_CNT_ERASEUSER 10
#define INTG_PROP_CNT_ERASETADK 11
#define INTG_PROP_CNT_LOCK	12
#define INTG_PROP_CNT_RSTVBMARB 13	/* call count reset vbmeta arb */
#define INTG_PROP_FUSED		20
#define INTG_PROP_DEV_ID	21
#define INTG_PROP_HWCONFIG	22
#define INTG_PROP_KS		23
#define INTG_PROP_KS_BAK	24
#define INTG_PROP_BOOTCONFIG	25
#define INTG_PROP_MISCTA_DK	26
#define INTG_PROP_SD_VERSION	27	/* sec data version (uint) */
#define INTG_PROP_SD_UNLOCK	28	/* sec data unlock (uint) */
#define INTG_PROP_SD_KS_COUNT	29	/* sec data KS Counter (uint) */
#define INTG_PROP_SD_KS_XCS	30	/* sec data KS XCS Root (uint) */
#define INTG_PROP_SD_KS_HASH	31	/* sec data KS Hash (HASH Size) */
#define INTG_PROP_SD_NONCE	32	/* sec data Sake Nonce (20 bytes) */
#define INTG_PROP_SD_VBM_RB	33	/* sec data VBMeta Rollback Counters */
#define INTG_PROP_SW_VERSION	34
#define INTG_PROP_TA_VERSION	35
#define INTG_PROP_BOOT_CONFIG	36
#define INTG_PROP_USB_OTG	37
#define INTG_PROP_LED		38
#define INTG_PROP_FACTORY_MODE	39
#define INTG_PROP_RESET_FRP	40
#define INTG_PROP_SL_SIGNATURE	41
#define INTG_PROP_SL_DATA	42
#define INTG_PROP_AUTHCH_CMD	43
#define INTG_PROP_URAND		44
#define INTG_PROP_TA_HMAC_LOW	45
#define INTG_PROP_TA_HMAC_HIGH	46
#define INTG_PROP_MAX		46

#include "fcserr.h"

struct integration_context;

struct integration_hwstate {
	unsigned int startup_flags;
	unsigned int wb_reason;
	unsigned char reset_detect;
	unsigned char usb_vbus_detect;
	unsigned char usb_otg_detect;
	unsigned int pwr_button_pressed_time;
	unsigned int vldwn_button_pressed_time;
	unsigned int vlup_button_pressed_time;
};

struct integration_func {
	int (*set_property)(
		struct integration_context *context,
		unsigned int id,
		const void *value,
		unsigned int value_len);
	int (*clear_property)(
		struct integration_context *context,
		unsigned int id);
	int (*is_equal_property)(
		struct integration_context *context,
		unsigned int id,
		const void *value,
		unsigned int value_len);
	int (*prepare_hwstate)(
		struct integration_context *context,
		struct integration_hwstate *state);
};

struct integration_context {
	struct integration_func *functions;
	void (*log)(const char *fmt, ...);
};

extern struct integration_context *g_integration_context_ptr;

#define integration_log(fmt, args...) ({ \
	if (g_integration_context_ptr != NULL && \
			g_integration_context_ptr->log != NULL) \
		g_integration_context_ptr->log(fmt, ##args); })

int integration_set_property(
		unsigned int id,
		const void *value,
		unsigned int value_len);

int integration_clear_property(
		unsigned int id);

int integration_is_equal_property(
		unsigned int id,
		const void *value,
		unsigned int value_len);

int integration_prepare_hwstate(
		struct integration_hwstate *state);


#endif
