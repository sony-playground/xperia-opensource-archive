/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdlib.h>
#include <string.h>

#include "fcslog.h"
#include "fcserr.h"
#include "fcs_defines.h"
#include "ta_interface.h"
#include "hwconf.h"
#include "hwconf_x_parser.h"
#include "cms_verifier.h"
#include "rule_rootcert.h"

static int verify(
	uint8_t *devid,
	size_t devid_len,
	struct embed_rootcert_item *embed_rootcert_list,
	size_t embed_rootcert_list_count,
	uint8_t *hwconf,
	int unit_size,
	uint8_t **embedded_payload,
	size_t *embedded_payload_length)
{
	int res = -FCSERR_EINVAL;
	uint8_t *rootcerts = NULL;
	size_t rootcerts_length = 0;
	struct rule_verifier *rule_handle = NULL;
	struct dev_binding binding = {};

	binding.die_id = devid;
	binding.die_id_sz = devid_len;

	res = rule_get_roots(RULE_USAGE_HWCONFIG,
			embed_rootcert_list,
			embed_rootcert_list_count,
			NULL,
			&rootcerts,
			&rootcerts_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get roots: (%d)\n", res);
		goto endfunction_verify;
	}

	res = rule_init(&rule_handle, &binding, RULE_USAGE_HWCONFIG);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init rule session\n");
		goto endfunction_verify;
	}

	res = cms_verify(hwconf, unit_size,
			rule_handle,
			rootcerts, rootcerts_length,
			NULL, 0,
			embedded_payload, embedded_payload_length);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("CMS signature verification fail: (%d)\n", res);

endfunction_verify:
	rule_deinit(rule_handle);
	free(rootcerts);
	return res;
}

int setup_hwconfig(
	uint8_t *devid,
	size_t devid_len,
	struct embed_rootcert_item *embed_rootcert_list,
	size_t embed_rootcert_list_count,
	hwconfig_t *handle_p)
{
	int res, unit_size;
	uint8_t *hwconf = NULL;
	uint8_t *payload = NULL;
	size_t payload_length = 0;
	hwconf_x_handle_t hwconf_hdl = NULL;

	if (handle_p == NULL ||
			devid == NULL ||
			embed_rootcert_list == NULL) {
		FCS_LOG_ERR("Invalid parameter.\n");
		return -FCSERR_EINVAL;
	}

	res = get_ta_unit_size(TA_MISC_PART, TA_HWCONFIG_UNIT, &unit_size);
	if (res != FCSERR_OK || unit_size == 0) {
		FCS_LOG_ERR("No hardware config found\n");
		return -FCSERR_ENOHWC;
	}

	hwconf = malloc(unit_size);
	if (hwconf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	res = read_ta(TA_MISC_PART, TA_HWCONFIG_UNIT, hwconf, unit_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Read hardware config FAIL\n");
		goto endfunction_init_hwconf;
	}

	res = verify(devid, devid_len,
			embed_rootcert_list,
			embed_rootcert_list_count,
			hwconf, unit_size,
			&payload,
			&payload_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify CMS: (%d)\n", res);
		goto endfunction_init_hwconf;
	}

	res = hwconf_x_parser_init(&hwconf_hdl, payload, payload_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("hwconf_x_parser_init FAIL\n");
		goto endfunction_init_hwconf;
	}

	*handle_p = hwconf_hdl;
endfunction_init_hwconf:
	if (res != FCSERR_OK)
		hwconf_x_parser_deinit(hwconf_hdl);
	free(payload);
	free(hwconf);

	return res;
}

void teardown_hwconfig(hwconfig_t handle)
{
	hwconf_x_parser_deinit(handle);
}

int get_imei_count(uint8_t *count, hwconfig_t handle)
{
	int res = FCSERR_OK;
	hwconf_x_handle_t hwconf = handle;

	if (count == NULL || hwconf == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	res = hwconf_x_parser_get_imei_count(hwconf, count);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Get imei count failed with error=%d\n",
			res);
	}

exit:
	return res;
}

int get_imei(uint8_t index, uint8_t *buf, size_t buf_size, size_t *id_length,
		hwconfig_t handle)
{
	int res = FCSERR_OK;
	uint8_t *hwconf_buffer = NULL;
	size_t hwconf_buffer_len = 0;
	hwconf_x_handle_t hwconf = handle;

	if (buf == NULL || id_length == NULL || hwconf == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	res = hwconf_x_parser_get_imei(hwconf, index,
		&hwconf_buffer, &hwconf_buffer_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("hwconf_x_parser_get_imei returned error=%d\n",
			res);
		goto exit;
	}

	if (hwconf_buffer_len > buf_size) {
		FCS_LOG_ERR("Buffer to small\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	memcpy(buf, hwconf_buffer, hwconf_buffer_len);
	*id_length = hwconf_buffer_len;

exit:
	return res;
}

int get_hwconf_dk(uint8_t **device_key, size_t *device_key_len,
	hwconfig_t handle)
{
	int res = FCSERR_OK;
	uint8_t *buf_out = NULL;
	uint8_t *hwc_dk = NULL;
	size_t hwc_dk_len = 0;
	hwconf_x_handle_t hwconf = handle;

	if (device_key == NULL || device_key_len == NULL || hwconf == NULL) {
		FCS_LOG_ERR("Invalid argument,\n");
		res = -FCSERR_EINVAL;
		goto error;
	}

	res = hwconf_x_parser_get_hwc_dk(hwconf, &hwc_dk, &hwc_dk_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("hwconf_x_parser_get_hwc_dk returned err=%d\n",
			res);
		goto error;
	}

	if (hwc_dk_len == 0) {
		FCS_LOG_ERR("Device Key length in HWConfig is zero\n");
		res = -FCSERR_ESIZE;
		goto error;
	}

	buf_out = malloc(hwc_dk_len);
	if (buf_out == NULL) {
		FCS_LOG_ERR("Failed to allocate memory for Device Key\n");
		res = -FCSERR_ENOMEM;
		goto error;
	}

	memcpy(buf_out, hwc_dk, hwc_dk_len);

	*device_key = buf_out;
	*device_key_len = hwc_dk_len;

	return res;
error:
	free(buf_out);
	return res;
}

int get_is_prototype(int *is_prototype, hwconfig_t handle)
{
	int res = FCSERR_OK;
	bool flag = false;
	hwconf_x_handle_t hwconf = handle;

	if (is_prototype == NULL || hwconf == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	res = hwconf_x_parser_get_isprototype(hwconf, &flag);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("hwconf_x_parser_get_isprototype returned err=%d\n",
			res);
		goto exit;
	}

	*is_prototype = flag;

exit:
	return res;
}

