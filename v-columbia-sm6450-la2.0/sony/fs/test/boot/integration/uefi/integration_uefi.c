/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "integration_uefi.h"
#include "integration_main.h"
#include "fcserr.h"
#include "fcstest_defines.h"
#include "mt_xb_common.h"
#include <string.h>
#include <stddef.h>
#include <stdint.h>

/* Integrated interfaces */
#include "xboot_pal_types.h"
#include "xboot_pal_include.h"
#include "ks.h"
#include "ksio.h"
#include "nvio.h"

/* Internal Core interfaces */
#include "ta_interface.h"

/* UEFI Environment */
#include <Library/MemoryAllocationLib.h>

static int intuefi_check_miscTA(uint32_t unit,
		const void *value,
		unsigned int value_len);

static int intuefi_update_miscTA(uint32_t unit,
		const void *value,
		unsigned int value_len);

static int intuefi_update_keystore(int original,
		const void *value,
		unsigned int value_len);

static int intuefi_check_rpbm(const void *value,
		unsigned int value_len);

struct intuefi_data {
	struct iterator_info *it;
	void (*export_hwstate)(
		struct integration_hwstate *state);
	struct integration_context context;
};

static int intuefi_set_property(
		struct integration_context *context,
		unsigned int id,
		const void *value,
		unsigned int value_len)
{
	int res = FCSERR_OK;
	bool is_fused = true;
	bool req_is_fuse = true;
	unsigned char *dieid = NULL;
	unsigned int dieid_len = 0;

	if ((context == NULL) ||
			(value == NULL) ||
			(value_len == 0)) {
		return -FCSERR_EINVAL;
	}
	switch (id) {
	case INTG_PROP_FUSED:
		/* Is_Fused is fixed => Is_Fused must match value */
		if (value_len != sizeof(unsigned char))
			return -FCSERR_EINVAL;
		res = core_is_fused(&is_fused);
		if (res != FCSERR_OK)
			return res;
		req_is_fuse = (0 != *(unsigned char *)value);
		if (is_fused != req_is_fuse)
			return -FCSERR_ENIMP;
		break;
	case INTG_PROP_DEV_ID:
		/* DevId is fixed => DevId must match value */
		res = core_get_dieid_len();
		if (res <= 0)
			return -FCSERR_EOPFAIL;
		dieid_len = (unsigned int)res;
		dieid = AllocatePool(dieid_len);
		if (dieid == NULL)
			return -FCSERR_ENOMEM;
		res = core_get_dieid(dieid, dieid_len);
		if (res == FCSERR_OK)
			if ((dieid_len != value_len) ||
				(memcmp(dieid, value, value_len) != 0))
				res = -FCSERR_ENIMP;
		FreePool(dieid);
		return res;
	case INTG_PROP_HWCONFIG:
		return intuefi_update_miscTA(
			TA_HWCONFIG_UNIT, value, value_len);
	case INTG_PROP_MISCTA_DK:
		return intuefi_update_miscTA(
			TA_DK_NUMBER_UNIT, value, value_len);
	case INTG_PROP_KS:
		return intuefi_update_keystore(1, value, value_len);
	case INTG_PROP_KS_BAK:
		return intuefi_update_keystore(0, value, value_len);
	case INTG_PROP_KS_RPMB:
		/* We can't change rpmb so we just check it has
		 * the expected value
		 */
		return intuefi_check_rpbm(value, value_len);
	case INTG_PROP_SW_VERSION:
		/* We can't change SW_VERSION */
		break;
	case INTG_PROP_TA_VERSION:
		return intuefi_update_miscTA(
			TA_S1_BOOT_VERSION_UNIT, value, value_len);
	case INTG_PROP_BOOT_CONFIG:
		return intuefi_update_miscTA(
			TA_BOOT_CONFIGURATION_UNIT, value, value_len);
	case INTG_PROP_LED:
		/* We can't change LED */
		break;
	case INTG_PROP_FACTORY_MODE:
		return intuefi_update_miscTA(
			TA_FACTORY_MODE_UNIT, value, value_len);
	case INTG_PROP_RESET_FRP:
		return intuefi_update_miscTA(
			TA_RL_DATA_LOW_UNIT, value, value_len);
	default:
		return -FCSERR_EINVAL;
	}
	return FCSERR_OK;
}

static int intuefi_clear_property(
		struct integration_context *context,
		unsigned int id)
{
	if (context == NULL)
		return -FCSERR_EINVAL;

	switch (id) {
	case INTG_PROP_FACTORY_MODE:
		return intuefi_update_miscTA(
			TA_FACTORY_MODE_UNIT, NULL, 0);
		break;
	case INTG_PROP_RESET_FRP:
		return intuefi_update_miscTA(
			TA_RL_DATA_LOW_UNIT, NULL, 0);
		break;
	case INTG_PROP_HWCONFIG:
		return intuefi_update_miscTA(
			TA_HWCONFIG_UNIT, NULL, 0);
		break;
	case INTG_PROP_COUNTERS:
		break;
	default:
		return -FCSERR_EINVAL;
	}
	return FCSERR_OK;
}

static int intuefi_is_equal_property(
		struct integration_context *context,
		unsigned int id,
		const void *value,
		unsigned int value_len)
{
	if ((context == NULL) ||
			((value == NULL) && (value_len > 0)) ||
			((value != NULL) && (value_len == 0)))
		return -FCSERR_EINVAL;

	switch (id) {
	case INTG_PROP_COUNTERS:
		integration_log("Call counter ignored.\n");
		break;
	case INTG_PROP_LED:
		if (value == NULL)
			return -FCSERR_EINVAL;
		if (value_len != sizeof(enum xbpal_rgb_led_cfg_t))
			return -FCSERR_EINVAL;
		if (!memcmp(value,
				&const_led_off, sizeof(const_led_off)))
			integration_log("Check LED is off.\n");
		else if (!memcmp(value,
				&const_led_red, sizeof(const_led_red)))
			integration_log("Check LED is RED.\n");
		else if (!memcmp(value,
				&const_led_green, sizeof(const_led_green)))
			integration_log("Check LED is GREEN.\n");
		else if (!memcmp(value,
				&const_led_blue, sizeof(const_led_blue)))
			integration_log("Check LED is BLUE.\n");
		else
			return -FCSERR_EINVAL;
		break;
	case INTG_PROP_RESET_FRP:
		return intuefi_check_miscTA(
			TA_RL_DATA_LOW_UNIT, value, value_len);
	default:
		return -FCSERR_EINVAL;
	}
	return FCSERR_OK;
}

static int intuefi_prepare_hwstate(
		struct integration_context *context,
		struct integration_hwstate *state)
{
	struct intuefi_data *data = NULL;
	uint32_t boot_time = 0;

	if ((context == NULL) || (state == NULL))
		return -FCSERR_EINVAL;

	data = (struct intuefi_data *)
		fcstest_container_of(context,
					struct intuefi_data,
					context);
	if (data->export_hwstate == NULL)
		return -FCSERR_ENIMP;

	/* Adjust timeouts to compensate for boot time */
	/* For this integration we assume long press timeout: 1200 */
	boot_time = xbpal_get_boot_time();

	if (state->pwr_button_pressed_time >= 1200)
		state->pwr_button_pressed_time += boot_time;
	if (state->vldwn_button_pressed_time >= 1200)
		state->vldwn_button_pressed_time += boot_time;
	if (state->vlup_button_pressed_time >= 1200)
		state->vlup_button_pressed_time += boot_time;

	data->export_hwstate(state);

	return FCSERR_OK;
}

static const struct integration_func intuefi_func = {
	.set_property = intuefi_set_property,
	.clear_property = intuefi_clear_property,
	.is_equal_property = intuefi_is_equal_property,
	.prepare_hwstate = intuefi_prepare_hwstate
};

int integration_uefi_setup(
		void (*log)(const char *fmt, ...),
		struct iterator_info *it,
		void (*export_hwstate)(
			struct integration_hwstate *state))
{
	struct intuefi_data *data = NULL;

	if (log == NULL || it == NULL || export_hwstate == NULL)
		return -FCSERR_EINVAL;

	data = (struct intuefi_data *)AllocatePool(
			sizeof(struct intuefi_data));
	if (data == NULL)
		return -FCSERR_ENOMEM;

	memset(data, 0, sizeof(struct intuefi_data));
	data->it = it;
	data->export_hwstate = export_hwstate;
	data->context.functions = (struct integration_func *)&intuefi_func;
	data->context.log = log;

	g_integration_context_ptr = &(data->context);

	return FCSERR_OK;
}

void integration_uefi_teardown(void)
{
	struct intuefi_data *data = NULL;

	if (g_integration_context_ptr != NULL) {
		data = (struct intuefi_data *)
			fcstest_container_of(g_integration_context_ptr,
					struct intuefi_data,
					context);

		FreePool(data);
	}
	g_integration_context_ptr = NULL;
}

static int intuefi_check_miscTA(uint32_t unit,
		const void *value,
		unsigned int value_len)
{
	int res = FCSERR_OK;
	int unit_size;
	uint8_t *unit_buf = NULL;

	/* Check current content of misc TA unit */
	res = get_ta_unit_size(TA_MISC_PART, unit, &unit_size);
	if (res != FCSERR_OK)
		return res;
	if (unit_size == 0) {
		if (value == NULL)
			goto exit;
		else {
			res = -FCSERR_EDATA;
			goto exit;
		}
	}
	unit_buf = (uint8_t *)AllocatePool(unit_size);
	if (unit_buf == NULL)
		return -FCSERR_ENOMEM;
	res = read_ta(TA_MISC_PART, unit, unit_buf, unit_size);
	if (res != FCSERR_OK)
		goto exit;

	/* Compare current content with new
	 */
	if ((unit_size == value_len) &&
		(value != NULL) &&
		(memcmp(unit_buf, value, value_len) == 0)) {
		goto exit;
	}
	res = -FCSERR_EDATA;

exit:
	if (unit_buf != NULL)
		FreePool(unit_buf);
	return res;
}

static int intuefi_update_miscTA(uint32_t unit,
		const void *value,
		unsigned int value_len)
{
	int res = FCSERR_OK;

	/* Check current content of misc TA unit.
	 * Compare current content with new and
	 * if equal no need to write to unit
	 */
	res = intuefi_check_miscTA(unit, value, value_len);
	if (res != -FCSERR_EDATA)
		goto exit;

	/* Write or delete unit */
	if (value != NULL) {
		res = write_ta(TA_MISC_PART,
				unit, (uint8_t *)value, value_len);
	} else {
		res = delete_ta(TA_MISC_PART, unit);
	}
exit:
	return res;
}

static int intuefi_update_keystore(int primary,
		const void *value,
		unsigned int value_len)
{
	int res = FCSERR_OK;
	struct nvio_state state = { .partition = KS_NV_BAK };
	uint32_t data_sz = 0;
	uint8_t *data = NULL;

	if ((value == NULL) || (value_len == 0))
		return -FCSERR_EINVAL;

	if (primary)
		state.partition = KS_NV_ORG;

	/* Check current content of keystore */
	res = plf_nv_read_cb(
			(ks_io_state_t *)&state, NULL, &data_sz);
	if (res != FCSERR_OK)
		return res;

	data = (uint8_t *)AllocatePool(data_sz);
	if (data == NULL)
		return -FCSERR_ENOMEM;

	res = plf_nv_read_cb(
			(ks_io_state_t *)&state, data, &data_sz);
	if (res != FCSERR_OK)
		goto exit;

	/* Compare current content with new and
	 * if equal no need to write keystore
	 */
	if ((data_sz >= value_len) &&
		(memcmp(data, value, value_len) == 0)) {
		goto exit;
	}

	res = plf_nv_write_cb(
			(ks_io_state_t *)&state,
			(uint8_t *)value, value_len);

exit:
	if (data != NULL)
		FreePool(data);
	return res;
}

static int intuefi_check_rpbm(const void *value,
		unsigned int value_len)
{
	int res = FCSERR_OK;
	uint32_t data_sz = 0;
	uint8_t *data = NULL;
	bool is_fused = false;

	if ((value == NULL) || (value_len == 0))
		return -FCSERR_EINVAL;

	data_sz = value_len;
	data = (uint8_t *)AllocatePool(data_sz);
	if (data == NULL)
		return -FCSERR_ENOMEM;

	res = core_is_fused(&is_fused);
	if (res != FCSERR_OK)
		goto exit;

	if (is_fused) {
		res = plf_rpmb_read_cb(
			NULL, data, &data_sz);
		if (res != FCSERR_OK)
			goto exit;
	} else {
		memset(data, 0, data_sz);
	}

	/* Compare current content with expected */
	if ((data_sz == value_len) &&
		(memcmp(data, value, value_len) == 0)) {
	} else {
		res = -FCSERR_EDATA;
	}

exit:
	if (data != NULL)
		FreePool(data);
	return res;
}

