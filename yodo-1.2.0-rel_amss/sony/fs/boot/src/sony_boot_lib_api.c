/*
 * Copyright 2016, 2021, 2022 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */
#include <string.h>

#include "xboot_glue.h"
#include "sony_boot_lib_api.h"

/* Internal bootlib header files */
#include "sony_boot_context.h"
#include "sony_boot_config_parser.h"
#include "sony_boot_customer_id.h"
#include "sony_boot_color_id.h"
#include "sony_boot_utils.h"
#include "sony_boot_service_detect.h"
#include "xboot_pal_types.h"
#include "sony_libc.h"
#include "ta_interface.h"
#include "fcs_endian.h"
#include "fcslog.h"

#define STARTUP_INDICATION_DURATION 75000

static int sony_boot_parse_bootconfig(struct xboot_ctx *boot_context);
static int sony_boot_get_customer_id(struct xboot_ctx *boot_context);
static int sony_boot_get_color_id(struct xboot_ctx *boot_context);
static void sony_boot_bootinfo_store_miscTa(struct xboot_ctx *boot_context);
static void sony_boot_populate_commandline(struct xboot_ctx *boot_context);
static void sony_boot_populate_backlight(struct xboot_ctx *boot_context);
static void ta_update_bootversion(struct xboot_ctx *boot_context);
static void vbus_vibration_ctl(struct xboot_ctx *boot_context);
/* Function sony_boot_get_ta_buffer reads ta_unit into buffer which has size
 * buf_size. The buffer should be allocated by the caller.
 */
static uint8_t *sony_boot_get_ta_buffer(int ta_unit, uint8_t *buffer,
	int buf_size);

LOG_BLOCK(
static void pretty_log_startup(struct xboot_ctx *boot_context);
static void pretty_log_warmboot(struct xboot_ctx *boot_context);
static void pretty_log_servicemode(struct xboot_ctx *boot_context);
)
static void longpress_cb(void *arg);

int sony_boot_init(struct xboot_ctx *boot_context)
{
	char *version_string = NULL;
	uint32_t version_string_sz = 0;

	if (!boot_context) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_ESTATE;
	}

	boot_context->curr_service_mode = SERVICE_MODE_DETECT_NONE;
	boot_context->longpress_state = LONG_PRESS_OK;

	/*
	 * Obtain XBOOT version string
	 */
	if ((xbpal_get_version_string(&version_string) != FCSERR_OK) ||
		!version_string) {
		version_string = NULL;
		version_string_sz = strlen("UNDEFINED") + 1;
	} else {
		version_string_sz = strlen(version_string) + 1;
	}

	boot_context->version_string = malloc(version_string_sz);
	if (boot_context->version_string == NULL) {
		FCS_LOG_ERR("Allocation failure for version string!\n");
		return -FCSERR_ENOMEM;
	}

	if (!version_string) {
		memcpy(boot_context->version_string, "UNDEFINED\0",
			version_string_sz);
	} else {
		/* We retain a local copy of the version string provided by
		 * integration
		 */
		memcpy(boot_context->version_string, version_string,
			version_string_sz);
	}

	/*
	 * Update the boot version unit in TA
	 */
	ta_update_bootversion(boot_context);

	/*
	 * Present ourselves
	 */
	FCS_LOG("XBOOT (%s)\n", boot_context->version_string);

	return FCSERR_OK;
}

static int sony_boot_goto_service_mode(
	struct xboot_ctx *boot_context)
{
	if (!boot_context) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_ESTATE;
	}

	/* No hwconfig found. Enter service mode if possible. */
	if (!xbpal_usb_vbus_detect()) {
		FCS_LOG("VBUS not detected\n");
		xbpal_shutdown(XBPAL_SHUTDOWN_REASON_OTHER);
	}

	FCS_LOG("Will invoke Sony service\n");
	(void)xbpal_rgb_led_ctl(XBPAL_LED_TURN_OFF);
	(void)xbpal_rgb_led_ctl(XBPAL_LED_TURN_ON_GREEN);
	boot_context->boot_mode = XBOOT_BOOT_SONY_SERVICE_MODE;

	return FCSERR_OK;
}

int sony_boot_make_decisions(
	struct xboot_ctx *boot_context)
{
	int result = FCSERR_OK;
	bool startup_indication_done = false;
	uint32_t longpress_time = 0;
	uint32_t time_since_boot = xbpal_get_boot_time();
	enum reset_state_t reset_state;
	uint8_t pba_space_id[PBA_SPACE_NR_MAX_SZ];
	uint8_t pba_space_rev[PBA_SPACE_REV_MAX_SZ];

	if (!boot_context) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_ESTATE;
	}

	/* Initiate pointer to command line */
	boot_context->sony_cmdline_additions = NULL;
	boot_context->sony_cmdline_additions_v2 = NULL;

	/* Set default boot mode */
	boot_context->boot_mode = XBOOT_BOOT_SONY_SERVICE_MODE;

	if (boot_context->curr_service_mode == SERVICE_MODE_DETECT_USB_SONY)
		return sony_boot_goto_service_mode(boot_context);

	boot_context->curr_service_mode = SERVICE_MODE_DETECT_NONE;

	/*
	 * Print PBA ID and revision in bootlog
	 */
	FCS_LOG("PBA ID: %s (%s)\n",
		(char *)sony_boot_get_ta_buffer(TA_PBA_SPACE_NUMBER_UNIT,
			pba_space_id, PBA_SPACE_NR_MAX_SZ),
		(char *)sony_boot_get_ta_buffer(TA_PBA_SPACE_REVISION_UNIT,
			pba_space_rev, PBA_SPACE_REV_MAX_SZ));

	/*
	 * Get warmboot and startup flags and present them in the bootlog
	 */
	boot_context->warmboot_reason = xbpal_get_wb_reason();
	boot_context->startup_flags = xbpal_get_startup_bits();
	/* Set reset reason to HWWD so we are prepared for possible crashes */
	xbpal_clear_wb_reason();
	LOG_BLOCK(
		FCS_LOG("Startup flags:");
		pretty_log_startup(boot_context);
		FCS_LOG("Warmboot reason:");
		pretty_log_warmboot(boot_context);
	)

	if (xbpal_translate_wb_reason(boot_context->warmboot_reason) ==
		XBPAL_WB_NONE &&
		boot_context->startup_flags == 0) {

		FCS_LOG("No reason for startup, shutting down.\n");
		xbpal_shutdown(XBPAL_SHUTDOWN_REASON_OTHER);
		/* NOTREACHED */
	}

	/* Shutdown in any case when a unit boot-up by RTC */
	if (xbpal_translate_wb_reason(boot_context->warmboot_reason) ==
		XBPAL_WB_NONE &&
		boot_context->startup_flags & XBPAL_STARTUP_MASK_RTC) {

		FCS_LOG("RTC alarm is set, shutting down.\n");
		xbpal_shutdown(XBPAL_SHUTDOWN_REASON_OTHER);
		/* NOTREACHED */
	}

	/*
	 * Apply JTAG settings
	 */
#ifdef JTAG_CONTROL
/* Enable this if JTAG control is available */
	result = xbpal_get_debug_permissions(&normal_allowed, &secure_allowed);
	if (result == FCSERR_OK) {
		if (!normal_allowed && !secure_allowed) {
			if (!xbpal_jtag_ctl(JTAG_OFF))
				FCS_LOG_WRN("Failed to disable JTAG!\n");
		}
		if (normal_allowed) {
			if (!xbpal_jtag_ctl(JTAG_ON))
				FCS_LOG_WRN("Failed to enable JTAG!\n");
		}
		if (secure_allowed) {
			if (!xbpal_jtag_ctl(JTAG_ON_SECURE))
				FCS_LOG_WRN("Failed to enable secure JTAG!\n");
		}
	} else {
		if (!xbpal_jtag_ctl(JTAG_OFF))
			FCS_LOG_WRN("Failed to disable JTAG!\n");
	}
#endif

	/*
	 * Try to obtain and parse the bootconfig unit
	 */
	result = sony_boot_parse_bootconfig(boot_context);
	result |= sony_boot_get_customer_id(boot_context);
	result |= sony_boot_get_color_id(boot_context);
	if (result != FCSERR_OK) {
		FCS_LOG("Will invoke Sony service to obtain a bootconfig\n");
		return sony_boot_goto_service_mode(boot_context);
	}

	/*
	 * Store Booting information to MiscTA
	 */
	sony_boot_bootinfo_store_miscTa(boot_context);

	if ((boot_context->startup_flags & XBPAL_STARTUP_MASK_VBUS) ||
	    (boot_context->startup_flags & XBPAL_STARTUP_MASK_WALLCHARGER)) {
		vbus_vibration_ctl(boot_context);
	}

	/*
	 * Attempt reset detection
	 */
	result = sony_boot_service_reset_detect(boot_context, &reset_state);
	if (result != FCSERR_OK)
		FCS_LOG_ERR("Reset detection failed!\n");
	else if (reset_state == RESET_DET_VIBRATION_DONE)
		startup_indication_done = true;

	/*
	 * Attempt service detection
	 */
	result = sony_boot_service_detect(boot_context,
		xbpal_translate_wb_reason(boot_context->warmboot_reason));
	if (result != FCSERR_OK) {
		FCS_LOG_ERR("Service mode detection failed!\n");
		boot_context->curr_service_mode = SERVICE_MODE_DETECT_NONE;
		result = FCSERR_OK;
	}

	LOG_BLOCK(
		FCS_LOG("Service mode detected:");
		pretty_log_servicemode(boot_context);
	)

	switch (boot_context->curr_service_mode) {
	case SERVICE_MODE_DETECT_USB_SONY:
		boot_context->boot_mode = XBOOT_BOOT_SONY_SERVICE_MODE;
		break;

	case SERVICE_MODE_DETECT_USB_FASTBOOT:
		boot_context->boot_mode = XBOOT_BOOT_FASTBOOT_MODE;
		break;
	default:
		break;
	}


	/*
	 * Determine the image to boot using warmboot reasons and startup flags
	 * in case no service mode is requested.
	 */
	if (boot_context->curr_service_mode == SERVICE_MODE_DETECT_NONE) {

		/* default to normal boot */
		boot_context->boot_mode = XBOOT_BOOT_DEFAULT_MODE;

		switch (xbpal_translate_wb_reason(
				boot_context->warmboot_reason)) {
		case XBPAL_WB_FOTA_CRASH:
		case XBPAL_WB_FOTA_HWWD:
		case XBPAL_WB_CRASH:
		case XBPAL_WB_CLEAR:
			boot_context->boot_mode = XBOOT_BOOT_DUMPER_MODE;
			break;
		case XBPAL_WB_FOTA:
			boot_context->boot_mode = XBOOT_BOOT_FOTA_MODE;
			break;
		case XBPAL_WB_SONY_SVC:
			if (xbpal_usb_vbus_detect())
				boot_context->boot_mode =
						XBOOT_BOOT_SONY_SERVICE_MODE;
			else if (xbpal_boot_into_recovery())
				boot_context->boot_mode =
						XBOOT_BOOT_RECOVERY_MODE;
			break;
		case XBPAL_WB_FB_SVC:
			if (xbpal_usb_vbus_detect())
				boot_context->boot_mode =
						XBOOT_BOOT_FASTBOOT_MODE;
			else if (xbpal_boot_into_recovery())
				boot_context->boot_mode =
						XBOOT_BOOT_RECOVERY_MODE;
			break;
		case XBPAL_WB_RECOVERY:
			boot_context->boot_mode = XBOOT_BOOT_RECOVERY_MODE;
			break;
		case XBPAL_WB_NONE:
		case XBPAL_WB_FOTA_CACHE:
		case XBPAL_WB_NORMAL:
		case XBPAL_WB_CRASH_ND:
		case XBPAL_WB_OTHER:
		case XBPAL_WB_SYSTEM:
		case XBPAL_WB_DMV_EIO:
		case XBPAL_WB_DMV_ENFORCE:
		case XBPAL_WB_DMV_KEYCLEAR:
		case XBPAL_WB_RD_OK:
		case XBPAL_WB_RD_DECFAIL_NO_TL:
		case XBPAL_WB_RD_DECFAIL_PART_TL:
		case XBPAL_WB_RD_CRASH_EARLY_HWWD:
		case XBPAL_WB_RD_CRASH_LATE_HWWD:
		case XBPAL_WB_RD_NO_SPACE:
		case XBPAL_WB_REBOOT_RD_CRASH:
		case XBPAL_WB_REBOOT_RD_APPERR:
			boot_context->boot_mode = XBOOT_BOOT_DEFAULT_MODE;
			break;
		default:
			/* If any of the startup flags indicate crash,
			 * and we do not have a proper wb reason
			 *  we will always attempt to boot the dumper
			 */
			if (boot_context->startup_flags &
					XBPAL_STARTUP_MASK_PLF_CRASHES) {
				FCS_LOG(
					"Startup bits indicate system crash.\n");
				FCS_LOG("Will attempt dumper boot.\n");
				boot_context->boot_mode =
						XBOOT_BOOT_DUMPER_MODE;
			}
			break;
		}

	} else if (boot_context->curr_service_mode ==
			SERVICE_MODE_DETECT_RECOVERY) {
		boot_context->boot_mode = XBOOT_BOOT_RECOVERY_MODE;
	}

	/*
	 * If we are coldbooting with a onkey as startup indication,
	 * start the longpress timer for vibration indication.
	 * Shutdown if the key is not pressed long enough.
	 */
	if (xbpal_translate_wb_reason(boot_context->warmboot_reason) ==
			XBPAL_WB_NONE &&
			boot_context->startup_flags & XBPAL_STARTUP_MASK_ONKEY
			&& !startup_indication_done) {

		if (!xbpal_pwr_button_pressed()) {
			FCS_LOG("Longpress too short, shutdown.\n");
			xbpal_shutdown(XBPAL_SHUTDOWN_REASON_OTHER);
			/* Will not reach here */
		}

		if (boot_context->bootconfig != NULL)
			longpress_time =
				boot_context->bootconfig->longPressTimeMS;

		if (longpress_time > time_since_boot) {
			result = xbpal_timer_register_cb(
					&(boot_context->timer_context),
					longpress_cb, longpress_time -
					time_since_boot,
					boot_context);
			if (result != FCSERR_OK) {
				FCS_LOG_ERR("Timer reg failed!\n");
			} else {
				/* Schedule a vibration to occur at a
				 * time matching the timeout
				 */
				boot_context->longpress_state =
						LONG_PRESS_RUNNING;
				xbpal_vibrate(1000 * (longpress_time -
						time_since_boot),
						STARTUP_INDICATION_DURATION);
			}
		} else {
			/* We have spent more time than the indication
			 * requirement so we indicate immediately
			 */
			xbpal_vibrate(0, STARTUP_INDICATION_DURATION);
			boot_context->longpress_state = LONG_PRESS_OK;
		}
	} else {
		boot_context->longpress_state = LONG_PRESS_OK;
	}

	/*
	 * Collect the necessary information for the commandline
	 * additions
	 */
	FCS_LOG("Collect command line additions\n");
	sony_boot_populate_commandline(boot_context);

	FCS_LOG("Obtain backlight config\n");
	sony_boot_populate_backlight(boot_context);

	/*
	 * Enable LED for Sony service or fastboot modes and VBUS insertion
	 */
	switch (boot_context->boot_mode) {
	case XBOOT_BOOT_SONY_SERVICE_MODE:
		(void)xbpal_rgb_led_ctl(XBPAL_LED_TURN_OFF);
		(void)xbpal_rgb_led_ctl(XBPAL_LED_TURN_ON_GREEN);
		break;
	case XBOOT_BOOT_FASTBOOT_MODE:
		(void)xbpal_rgb_led_ctl(XBPAL_LED_TURN_OFF);
		(void)xbpal_rgb_led_ctl(XBPAL_LED_TURN_ON_BLUE);
		break;
	default:
		if (boot_context->startup_flags &
		(XBPAL_STARTUP_MASK_VBUS | XBPAL_STARTUP_MASK_WALLCHARGER)) {
			(void)xbpal_rgb_led_ctl(XBPAL_LED_TURN_OFF);
			(void)xbpal_rgb_led_ctl(XBPAL_LED_TURN_ON_RED);
		}
		break;
	}
	return result;
}

int sony_boot_finalize_longpress(struct xboot_ctx *boot_context)
{
	if (!boot_context) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_ESTATE;
	}

	while (1) {
		if (boot_context->longpress_state == LONG_PRESS_FAILED) {
			FCS_LOG("Longpress too short, shutting down.\n");
			xbpal_shutdown(XBPAL_SHUTDOWN_REASON_OTHER);
			/* Added for test purposes,
			 * xbpal_shutdown() will not return
			 */
			break;
		} else if (boot_context->longpress_state == LONG_PRESS_OK) {
			break;
		}
	}
	return FCSERR_OK;
}

static uint8_t *sony_boot_get_ta_buffer(int ta_unit, uint8_t *buffer,
	int buf_size)
{
	int id_sz;

	if (!buffer) {
		FCS_LOG_ERR("Invalid argument\n");
		return NULL;
	}

	if (get_ta_unit_size(TA_MISC_PART, ta_unit, &id_sz) != FCSERR_OK) {
		buffer[0] = '\0';
	} else if (id_sz == 0) {
		buffer[0] = '\0';
	} else if (id_sz >= buf_size - 1) {
		buffer[0] = '\0';
	} else {
		memset(buffer, 0, buf_size);

		if (read_ta(TA_MISC_PART, ta_unit, buffer, id_sz) != FCSERR_OK)
			buffer[0] = '\0';
	}
	return buffer;
}

static int sony_boot_parse_bootconfig(
	struct xboot_ctx *boot_context)
{
	uint32_t ta_unit_sz;
	uint8_t *ta_unit;
	int result = FCSERR_OK;

	if (!boot_context) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_ESTATE;
	}

	result = sony_boot_ta_simple_read(
		TA_BOOT_CONFIGURATION_UNIT, &ta_unit, &ta_unit_sz);
	if (result == FCSERR_OK) {
		result = bootconfig_parse(boot_context, ta_unit, ta_unit_sz);
		free(ta_unit);
	}

	if (result != FCSERR_OK)
		FCS_LOG_ERR("Bootconfig parsing failed (%08X)!\n", result);

	return result;
}

static int sony_boot_get_customer_id(
	struct xboot_ctx *boot_context)
{
	uint32_t ta_unit_sz;
	uint8_t *ta_unit;
	int result = FCSERR_OK;

	if (!boot_context) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_ESTATE;
	}

	/* Append "androidboot.hardware.sku" from TA_CUSTOMER_ID(MiscTA#2171) */
	result = sony_boot_ta_simple_read(
		TA_CUSTOMER_ID, &ta_unit, &ta_unit_sz);
	if ((result == FCSERR_OK) && (ta_unit != NULL)) {
		for (int cnt = 0; cnt < ta_unit_sz; cnt++) {
			if (ta_unit[cnt] == '\0') {
				ta_unit_sz = cnt;
				if (cnt == 0) {
					free(ta_unit);
					ta_unit = NULL;
				}
				break;
			}
			if ((ta_unit[cnt] == ' ') || (ta_unit[cnt] == '\n')) {
				free(ta_unit);
				ta_unit = NULL;
				break;
			}
		}
		if (ta_unit != NULL) {
#if defined(FEATURE_SM4350) || defined(FEATURE_SM6375)
			result = cmdline_append_customer_id(boot_context, ta_unit, ta_unit_sz);
#else
			result = bootconfig_append_customer_id(boot_context, ta_unit, ta_unit_sz);
#endif
			free(ta_unit);
		} else {
			FCS_LOG_ERR("MiscTA%d is invalid strings\n", TA_CUSTOMER_ID);
		}
	} else {
		FCS_LOG_ERR("Cannot read MiscTA%d \n", TA_CUSTOMER_ID);
		result = FCSERR_OK; /* Set OK even if MiscTa2171 is nothing */
	}

	if (result != FCSERR_OK)
		FCS_LOG_ERR("sony_boot_get_customer_id failed (%08X)!\n", result);

	return result;
}

static int sony_boot_get_color_id(
	struct xboot_ctx *boot_context)
{
	uint32_t ta_unit_sz;
	uint8_t *ta_unit;
	int result = FCSERR_OK;

	if (!boot_context) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_ESTATE;
	}

	/* Append "androidboot.hardware.color" from TA_HW_COLOR_ID(MiscTA#4990) */
	result = sony_boot_ta_simple_read(
		TA_HW_COLOR_ID, &ta_unit, &ta_unit_sz);
	if ((result == FCSERR_OK) && (ta_unit != NULL)) {
		for (int cnt = 0; cnt < ta_unit_sz; cnt++) {
			if (ta_unit[cnt] == '\0') {
				ta_unit_sz = cnt;
				if (cnt == 0) {
					free(ta_unit);
					ta_unit = NULL;
				}
				break;
			}
			if ((ta_unit[cnt] == ' ') || (ta_unit[cnt] == '\n')) {
				free(ta_unit);
				ta_unit = NULL;
				break;
			}
		}
		if (ta_unit != NULL) {
#if defined(FEATURE_SM6375)
			result = cmdline_append_color_id(boot_context, ta_unit, ta_unit_sz);
#elif defined(FEATURE_SM8550)
			result = bootconfig_append_color_id(boot_context, ta_unit, ta_unit_sz);
#endif
			free(ta_unit);
		} else {
			FCS_LOG_ERR("MiscTA%d is invalid strings\n", TA_HW_COLOR_ID);
		}
	} else {
		FCS_LOG_ERR("Cannot read MiscTA%d \n", TA_HW_COLOR_ID);
		result = FCSERR_OK; /* Set OK even if MiscTa4990 is nothing */
	}

	if (result != FCSERR_OK)
		FCS_LOG_ERR("sony_boot_get_color_id failed (%08X)!\n", result);

	return result;
}

static void sony_boot_bootinfo_store_miscTa(struct xboot_ctx *boot_context)
{
	uint32_t startup_bits;
	uint32_t warmboot_reason;
	char *tmp;
	int  storeLen = 0;
	char storeData[MAX_STRING_SIZE] = "";

	write_be_u32((uint32_t)boot_context->startup_flags,
		(uint8_t *)&startup_bits);
	write_be_u32(boot_context->warmboot_reason,
		(uint8_t *)&warmboot_reason);

	/* convert startup flags to string */
	strlcat(storeData, "startup=0x", sizeof(storeData));
	tmp = bin2ascii((const uint8_t *)&(startup_bits), sizeof(uint32_t));
	if (tmp) {
		strlcat(storeData, tmp, sizeof(storeData));
		free(tmp);
	} else {
		FCS_LOG_ERR("Out of memory for converted startup bits!\n");
	}

	/* change warmboot reason to string */
	strlcat(storeData, ",warmboot=0x", sizeof(storeData));
	tmp = bin2ascii((const uint8_t *)&(warmboot_reason), sizeof(uint32_t));
	if (tmp) {
		strlcat(storeData, tmp, sizeof(storeData));
		free(tmp);
	} else {
		FCS_LOG_ERR("Out of memory for converted warmboot reason!\n");
	}

	/* Store MiscTA 2016 */
	storeLen = strlen(storeData);
	if (write_ta(TA_MISC_PART, TA_SIMPINCACHE_REASON,
		(uint8_t *)storeData, storeLen)
		!= FCSERR_OK) {
		FCS_LOG_ERR("Failed to write boot version unit!\n");
	}
}

static void ta_update_bootversion(struct xboot_ctx *boot_context)
{
	uint32_t curr_boot_version_sz = 0;
	uint8_t *curr_boot_version = NULL;
	uint32_t new_boot_version_sz = strlen(boot_context->version_string);
	bool need_update = true;
	int res;
	int unit_size;

	res = sony_boot_ta_simple_read(TA_S1_BOOT_VERSION_UNIT,
		&curr_boot_version, &curr_boot_version_sz);
	if (res != FCSERR_OK) {
		FCS_LOG_WRN("Failed to read TA boot version unit, update\n");
		need_update = true;
	}

	if (curr_boot_version_sz > 0) {
		if (curr_boot_version_sz != new_boot_version_sz) {
			need_update = true;
		} else {
			need_update = (bool)memcmp(curr_boot_version,
				boot_context->version_string,
				new_boot_version_sz);
		}
	}

	free(curr_boot_version);

	if (need_update) {
		if ((get_ta_unit_size(TA_MISC_PART,
			TA_S1_BOOT_VERSION_UNIT, &unit_size) == FCSERR_OK) &&
			(unit_size != 0)) {

			if (delete_ta(TA_MISC_PART,
				TA_S1_BOOT_VERSION_UNIT) != FCSERR_OK)

				FCS_LOG_WRN("Failed to delete boot version\n");
		}

		if (write_ta(TA_MISC_PART,
			TA_S1_BOOT_VERSION_UNIT,
			(uint8_t *)(boot_context->version_string),
			new_boot_version_sz)  != FCSERR_OK) {
			FCS_LOG_ERR("Failed to write boot version unit!\n");
		}
	}
}

static void sony_boot_populate_commandline(struct xboot_ctx *boot_context)
{
	char *tmp_str = NULL;
	uint8_t *msn = NULL;
	int msn_sz = 0;
	uint32_t cnt = 0;
	char *buf;

	/* Warmboot and startup bits on commandline are stored in big endian */
	uint32_t my_startup_bits;
	uint32_t my_warmboot_reason;

	/* Notice: sony_cmdline_additions_v2 is already added string. */
	/*         So, sony_cmdline_additions_v2 do not checked here. */
	if (boot_context->sony_cmdline_additions != NULL) {
		/* Someone have already populated the additions */
		FCS_LOG_ERR("Someone have already populated the additions!\n");
		return;
	}

	if (boot_context->bootconfig == NULL) {
		FCS_LOG_ERR("bootconfig is NULL\n");
		return;
	}

	write_be_u32((uint32_t)boot_context->startup_flags,
		(uint8_t *)&my_startup_bits);
	write_be_u32(boot_context->warmboot_reason,
		(uint8_t *)&my_warmboot_reason);

	/* Add bootloader type */
	boot_context->sony_cmdline_additions = sony_alloc_strcat(
		boot_context->sony_cmdline_additions,
		" androidboot.bootloader=xboot");

	/* Add bootloader version */
	boot_context->sony_cmdline_additions = sony_alloc_strcat(
		boot_context->sony_cmdline_additions, " oemandroidboot.xboot=");
	boot_context->sony_cmdline_additions = sony_alloc_strcat(
		boot_context->sony_cmdline_additions,
		boot_context->version_string);

	/* Replace all spaces in the appended string with '_' */
	buf = strnstr(boot_context->sony_cmdline_additions,
		boot_context->version_string,
		strlen(boot_context->sony_cmdline_additions));
	if (buf && *buf) {
		do {
			if (buf[cnt] == ' ')
				buf[cnt] = '_';
		} while (buf[cnt++] != '\0');
	}

	/* Add serial number */
	boot_context->sony_cmdline_additions = sony_alloc_strcat(
		boot_context->sony_cmdline_additions, " androidboot.serialno=");
	boot_context->bootconfig->taCommandLineArgs = sony_alloc_strcat(
		boot_context->bootconfig->taCommandLineArgs, " androidboot.serialno=");

	if ((get_ta_unit_size(TA_MISC_PART, TA_MSN_UNIT, &msn_sz) == FCSERR_OK)
		&& (msn_sz != 0)) {

		/* auto NULL terminate */
		msn = calloc(msn_sz + 1, sizeof(uint8_t));

		if (!msn) {
			FCS_LOG_ERR("Out of memory for serial number!\n");
		} else if (read_ta(TA_MISC_PART, TA_MSN_UNIT,
			msn, msn_sz) != FCSERR_OK) {
			free(msn);
			msn = NULL;
		} else {
			/* If it contains spaces, it can be considered tampered with. */
			cnt = 0;
			do {
				if (msn[cnt] == ' ') {
					free(msn);
					msn = NULL;
					break;
				}
			} while (msn[cnt++] != '\0');
			if (msn != NULL) {
				boot_context->sony_cmdline_additions =
					sony_alloc_strcat(
						boot_context->sony_cmdline_additions,
						(char *)msn);
				boot_context->bootconfig->taCommandLineArgs =
					sony_alloc_strcat(
						boot_context->bootconfig->taCommandLineArgs,
						(char *)msn);
			}
		}
		if (msn == NULL) {
			FCS_LOG_WRN("Failed to read ser number from MiscTA\n");
			boot_context->sony_cmdline_additions =
				sony_alloc_strcat(
					boot_context->sony_cmdline_additions,
					"INVALID");
			boot_context->bootconfig->taCommandLineArgs =
				sony_alloc_strcat(
					boot_context->bootconfig->taCommandLineArgs,
					"INVALID");
		} else {
			free(msn);
		}
	} else {
		FCS_LOG_WRN("Failed to read serial number from MiscTA.\n");
		boot_context->sony_cmdline_additions = sony_alloc_strcat(
			boot_context->sony_cmdline_additions, "INVALID");
		boot_context->bootconfig->taCommandLineArgs = sony_alloc_strcat(
			boot_context->bootconfig->taCommandLineArgs, "INVALID");
	}

	/* Add startup flags */
	boot_context->sony_cmdline_additions = sony_alloc_strcat(
		boot_context->sony_cmdline_additions, " startup=");
	boot_context->sony_cmdline_additions_v2 = sony_alloc_strcat(
		boot_context->sony_cmdline_additions_v2, " oembootloader.startup=");

	tmp_str = bin2ascii((const uint8_t *)&(my_startup_bits),
		sizeof(uint32_t));
	if (tmp_str) {
		boot_context->sony_cmdline_additions = sony_alloc_strcat(
			boot_context->sony_cmdline_additions, "0x");
		boot_context->sony_cmdline_additions = sony_alloc_strcat(
			boot_context->sony_cmdline_additions, tmp_str);
		boot_context->sony_cmdline_additions_v2 = sony_alloc_strcat(
			boot_context->sony_cmdline_additions_v2, "0x");
		boot_context->sony_cmdline_additions_v2 = sony_alloc_strcat(
			boot_context->sony_cmdline_additions_v2, tmp_str);
		free(tmp_str);
	} else {
		FCS_LOG_ERR("Out of memory for converted startup bits!\n");
		boot_context->sony_cmdline_additions = sony_alloc_strcat(
			boot_context->sony_cmdline_additions, "INVALID");
		boot_context->sony_cmdline_additions_v2 = sony_alloc_strcat(
			boot_context->sony_cmdline_additions_v2, "INVALID");
	}

	/* Add warmboot reason */
	boot_context->sony_cmdline_additions = sony_alloc_strcat(
		boot_context->sony_cmdline_additions, " warmboot=");
	boot_context->sony_cmdline_additions_v2 = sony_alloc_strcat(
		boot_context->sony_cmdline_additions_v2, " oembootloader.warmboot=");
	tmp_str = bin2ascii((const uint8_t *)&my_warmboot_reason,
		sizeof(uint32_t));
	if (tmp_str) {
		boot_context->sony_cmdline_additions = sony_alloc_strcat(
			boot_context->sony_cmdline_additions, "0x");
		boot_context->sony_cmdline_additions = sony_alloc_strcat(
			boot_context->sony_cmdline_additions, tmp_str);
		boot_context->sony_cmdline_additions_v2 = sony_alloc_strcat(
			boot_context->sony_cmdline_additions_v2, "0x");
		boot_context->sony_cmdline_additions_v2 = sony_alloc_strcat(
			boot_context->sony_cmdline_additions_v2, tmp_str);
		free(tmp_str);
	} else {
		FCS_LOG_ERR("Out of memory for converted warmboot value!\n");
		boot_context->sony_cmdline_additions = sony_alloc_strcat(
			boot_context->sony_cmdline_additions, "INVALID");
		boot_context->sony_cmdline_additions_v2 = sony_alloc_strcat(
			boot_context->sony_cmdline_additions_v2, "INVALID");
	}

	/* Add TA units from the bootconfig */
	boot_context->sony_cmdline_additions = sony_alloc_strcat(
		boot_context->sony_cmdline_additions, " ");
	boot_context->sony_cmdline_additions = sony_alloc_strcat(
		boot_context->sony_cmdline_additions,
		boot_context->bootconfig->taCommandLineArgs);
}

static void sony_boot_populate_backlight(struct xboot_ctx *boot_context)
{
	if (boot_context->bootconfig != NULL) {
		boot_context->backlight_enable =
			boot_context->bootconfig->backlightEnable;
	} else {
		boot_context->backlight_enable = false;
	}
}

LOG_BLOCK(
static void pretty_log_startup(struct xboot_ctx *boot_context)
{
	if (boot_context->startup_flags & XBPAL_STARTUP_MASK_ONKEY)
		FCS_LOG(" [ONKEY PRESSED]");

	if (boot_context->startup_flags & XBPAL_STARTUP_MASK_WATCHDOG)
		FCS_LOG(" [WATCHDOG EXPIRED]");

	if (boot_context->startup_flags & XBPAL_STARTUP_MASK_VBUS)
		FCS_LOG(" [USB INSERTED]");

	if (boot_context->startup_flags & XBPAL_STARTUP_MASK_SMPL)
		FCS_LOG(" [SMPL REBOOT]");

	if (boot_context->startup_flags & XBPAL_STARTUP_MASK_RTC)
		FCS_LOG(" [RTC ALARM WAKEUP]");

	if (boot_context->startup_flags & XBPAL_STARTUP_MASK_WALLCHARGER)
		FCS_LOG(" [CHARGER INSERTED]");

	if (boot_context->startup_flags & XBPAL_STARTUP_MASK_POWERLOCK)
		FCS_LOG(" [POWER LOCKED]");

	if (boot_context->startup_flags & XBPAL_STARTUP_MASK_HARD_RESET)
		FCS_LOG(" [HARD RESET]");

	if (boot_context->startup_flags &
	    XBPAL_STARTUP_MASK_WATCHDOG_BYPASS_PWK)
		FCS_LOG(" [WATCHDOG BYPASS POWER KEY]");

	if (boot_context->startup_flags & XBPAL_STARTUP_MASK_TOOL_BYPASS_PWK)
		FCS_LOG(" [TOOL BYPASS POWER KEY]");

	if (boot_context->startup_flags & ~(
		XBPAL_STARTUP_MASK_ONKEY |
		XBPAL_STARTUP_MASK_WATCHDOG |
		XBPAL_STARTUP_MASK_VBUS |
		XBPAL_STARTUP_MASK_SMPL |
		XBPAL_STARTUP_MASK_RTC |
		XBPAL_STARTUP_MASK_WALLCHARGER |
		XBPAL_STARTUP_MASK_POWERLOCK |
		XBPAL_STARTUP_MASK_HARD_RESET |
		XBPAL_STARTUP_MASK_WATCHDOG_BYPASS_PWK |
		XBPAL_STARTUP_MASK_TOOL_BYPASS_PWK))

		FCS_LOG(" [BITS UNKNOWN TO XBOOT (0x%08X)]",
			(unsigned int)boot_context->startup_flags);

	FCS_LOG("\n");
}

static void pretty_log_warmboot(struct xboot_ctx *boot_context)
{
	switch (xbpal_translate_wb_reason(boot_context->warmboot_reason)) {
	case XBPAL_WB_NORMAL:
		FCS_LOG(" [NORMAL]\n");
		break;
	case XBPAL_WB_SYSTEM:
		FCS_LOG(" [SYSTEM]\n");
		break;
	case XBPAL_WB_CRASH:
		FCS_LOG(" [CRASH]\n");
		break;
	case XBPAL_WB_CRASH_ND:
		FCS_LOG(" [CRASH W/O DUMPER]\n");
		break;
	case XBPAL_WB_FOTA:
		FCS_LOG(" [FOTA]\n");
		break;
	case XBPAL_WB_SONY_SVC:
		FCS_LOG(" [SONY SERVICE]\n");
		break;
	case XBPAL_WB_FB_SVC:
		FCS_LOG(" [FASTBOOT]\n");
		break;
	case XBPAL_WB_RECOVERY:
		FCS_LOG(" [RECOVERY]\n");
		break;
	case XBPAL_WB_CLEAR:
		FCS_LOG(" [CLEARED]\n");
		break;
	case XBPAL_WB_NONE:
		FCS_LOG(" [COLDBOOT]\n");
		break;
	case XBPAL_WB_FOTA_CRASH:
		FCS_LOG(" [FOTA CRASH]\n");
		break;
	case XBPAL_WB_FOTA_HWWD:
		FCS_LOG(" [FOTA HWWD]\n");
		break;
	case XBPAL_WB_FOTA_CACHE:
		FCS_LOG(" [FOTA CACHE]\n");
		break;
	case XBPAL_WB_DMV_EIO:
		FCS_LOG(" [DM VERITY EIO]\n");
		break;
	case XBPAL_WB_DMV_ENFORCE:
		FCS_LOG(" [DM VERITY ENFORCE]\n");
		break;
	case XBPAL_WB_DMV_KEYCLEAR:
		FCS_LOG(" [DM VERITY KEYCLEAR]\n");
		break;
	case XBPAL_WB_RD_OK:
		FCS_LOG(" [RAMDUMP OK]\n");
		break;
	case XBPAL_WB_RD_DECFAIL_NO_TL:
		FCS_LOG(" [RAMDUMP NO TLCORE]\n");
		break;
	case XBPAL_WB_RD_DECFAIL_PART_TL:
		FCS_LOG(" [RAMDUMP PARTIAL TLCORE]\n");
		break;
	case XBPAL_WB_RD_CRASH_EARLY_HWWD:
		FCS_LOG(" [RAMDUMP EARLY HWWD]\n");
		break;
	case XBPAL_WB_RD_CRASH_LATE_HWWD:
		FCS_LOG(" [RAMDUMP LATE HWWD]\n");
		break;
	case XBPAL_WB_RD_NO_SPACE:
		FCS_LOG(" [RAMDUMP NO SPACE]\n");
		break;
	case XBPAL_WB_REBOOT_RD_CRASH:
		FCS_LOG(" [RAMDUMP KERNEL PANIC]\n");
		break;
	case XBPAL_WB_REBOOT_RD_APPERR:
		FCS_LOG(" [RAMDUMP APP FAILURE]\n");
		break;
	default: /* XBPAL_WB_OTHER or real other reason */
		FCS_LOG(" [UNKNOWN TO XBOOT (0x%08X)]\n",
			boot_context->warmboot_reason);
		break;
	}
}

static void pretty_log_servicemode(struct xboot_ctx *boot_context)
{
	switch (boot_context->curr_service_mode) {
	case SERVICE_MODE_DETECT_NONE:
		FCS_LOG(" [NONE]\n");
		break;
	case SERVICE_MODE_DETECT_USB_SONY:
		FCS_LOG(" [SONY - USB]\n");
		break;
	case SERVICE_MODE_DETECT_USB_FASTBOOT:
		FCS_LOG(" [FASTBOOT]\n");
		break;
	case SERVICE_MODE_DETECT_RECOVERY:
		FCS_LOG(" [RECOVERY]\n");
		break;
	default:
		FCS_LOG(" [UNKNOWN TO XBOOT (0x%08X)]\n",
			(unsigned int)boot_context->curr_service_mode);
		break;
	}
}
) /* LOG_BLOCK */

static void longpress_cb(void *arg)
{
	struct xboot_ctx *boot_context = (struct xboot_ctx *)arg;

	if (!xbpal_pwr_button_pressed()) {
		boot_context->longpress_state = LONG_PRESS_FAILED;
	} else {
		(void)xbpal_timer_deregister_cb(boot_context->timer_context);
		/* Vibration is handled by the delay argument when longpress
		 * was started
		 */
		boot_context->longpress_state = LONG_PRESS_OK;
	}
}


static void vbus_vibration_ctl(struct xboot_ctx *boot_context)
{
	uint16_t *array = NULL;
	uint16_t i, nof_pulses;

	if (boot_context->bootconfig != NULL)
		array = boot_context->bootconfig->vbus_pulse_array;

	if (array) {
		nof_pulses = array[0] & 0xFF;
		if (nof_pulses == 0)
			return;

		for (i = 1; i <= nof_pulses; i += 2) {
			xbpal_vibrate(0, array[i] * 1000);
			if ((i + 1) <= nof_pulses)
				xbpal_delay_us(array[i + 1] * 1000);
		}
	}
}


