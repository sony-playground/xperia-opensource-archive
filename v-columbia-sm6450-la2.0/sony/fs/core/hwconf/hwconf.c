/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdlib.h>
#include <string.h>

#include "fcslog.h"
#include "fcserr.h"
#include "fcs_defines.h"
#include "ta_interface.h"
#include "hwconf.h"
#include "hwconf_parser.h"
#include "sin_parser.h"
#include "sin_verifier.h"
#include "rule_rootcert.h"
#include "digest.h"

static int verify_header(
	uint8_t *devid,
	size_t devid_len,
	struct embed_rootcert_item *embed_rootcert_list,
	size_t embed_rootcert_list_count,
	uint8_t *hwconf,
	int unit_size,
	struct sin_header **sinparser)
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
		goto endfunction_verify_header;
	}

	res = rule_init(&rule_handle, &binding, RULE_USAGE_HWCONFIG);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init rule session\n");
		goto endfunction_verify_header;
	}

	res = sin_verify(rule_handle,
			rootcerts,
			rootcerts_length,
			hwconf, unit_size,
			sinparser);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("Sin signature verification fail: (%d)\n", res);

endfunction_verify_header:
	rule_deinit(rule_handle);
	free(rootcerts);
	return res;
}

static int verify_payload(
	struct sin_header *sinparser,
	int unit_size,
	uint8_t *hwconf)
{
	int res = -FCSERR_EINVAL;
	struct sin_header_static_field *sin_static_header = NULL;
	struct sin_block_info *block_info = NULL;
	uint32_t nof_blocks = 0;

	res = sinparser_get_header(sinparser, &sin_static_header);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get sin header: (%d)\n", res);
		goto endfunction_verify_payload;
	}

	if (sin_static_header->type_payload !=
			SIN_PAYLOAD_TYPE__PLT_HWCONFIG) {
		FCS_LOG_ERR("Unexpected payload type: %d\n",
			sin_static_header->type_payload);
		res = -FCSERR_EINFOR;
		goto endfunction_verify_payload;
	}

	if (sin_static_header->type_payload_hash !=
			SIN_SHA256_RSA) {
		FCS_LOG_ERR("Unexpected payload hash type: %d\n",
			sin_static_header->type_payload_hash);
		res = -FCSERR_EINFOR;
		goto endfunction_verify_payload;
	}

	res = sinparser_get_nof_hash_blocks(sinparser, &nof_blocks);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get number of blocks\n");
		goto endfunction_verify_payload;
	}

	if (nof_blocks != 1) {
		FCS_LOG_ERR("Unexpected number of payload blocks: %d\n",
			nof_blocks);
		res = -FCSERR_EINFOR;
		goto endfunction_verify_payload;
	}

	res = sinparser_get_hash_block_info(sinparser, 0, &block_info);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get first block\n");
		goto endfunction_verify_payload;
	}

	res = digest_sha256_verify(
		hwconf + sin_static_header->size_header,
		unit_size - sin_static_header->size_header,
		block_info->payload_block_hash);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("Failed to verify hwconfig\n");

endfunction_verify_payload:
	return res;
}

static int verify_device_binding(
	hwconf_handle_t hwconf_hdl,
	uint8_t *devid,
	size_t devid_len)
{
	int res = -FCSERR_EINVAL;
	uint8_t nr_ins_devid = 0;
	uint16_t hwc_devid_len = 0;
	uint8_t *hwc_devid = NULL;

	res = hwconf_parser_get_dev_id_nr_ins(&nr_ins_devid, hwconf_hdl);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get nr of devid inst. from hwc: %d\n",
			res);
		goto endfunction_verify_device_binding;
	}
	if (nr_ins_devid == 0) {
		res = -FCSERR_EDEVID;
		FCS_LOG_ERR("Failed to find dev id\n");
		goto endfunction_verify_device_binding;
	}

	res = hwconf_parser_get_dev_id_length(0, &hwc_devid_len, hwconf_hdl);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get length of dev id from hwc: (%d)\n",
			res);
		goto endfunction_verify_device_binding;
	}

	hwc_devid = malloc(hwc_devid_len);
	if (hwc_devid == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto endfunction_verify_device_binding;
	}

	res = hwconf_parser_get_dev_id(
		0, hwc_devid, hwc_devid_len, hwconf_hdl);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get dev id from hwc: (%d)\n", res);
		goto endfunction_verify_device_binding;
	}

	if ((hwc_devid_len != devid_len) ||
		(0 != memcmp(hwc_devid, devid, hwc_devid_len))) {
		res = -FCSERR_EDEVID;
		FCS_LOG_ERR("Failed to match dev id for hwc and input\n");
	}

endfunction_verify_device_binding:
	free(hwc_devid);
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
	struct sin_header *sinparser = NULL;
	struct sin_header_static_field *sin_static_header = NULL;
	hwconf_handle_t hwconf_hdl = NULL;

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

	res = verify_header(devid, devid_len,
			embed_rootcert_list,
			embed_rootcert_list_count,
			hwconf, unit_size,
			&sinparser);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify sin header: (%d)\n", res);
		goto endfunction_init_hwconf;
	}

	res = verify_payload(sinparser, unit_size, hwconf);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify payload: (%d)\n", res);
		goto endfunction_init_hwconf;
	}

	res = sinparser_get_header(sinparser, &sin_static_header);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get sin header: (%d)\n", res);
		goto endfunction_init_hwconf;
	}

	res = hwconf_parser_init(hwconf + sin_static_header->size_header,
		unit_size - sin_static_header->size_header, &hwconf_hdl);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("hwconf_parser_init FAIL\n");
		goto endfunction_init_hwconf;
	}

	res = verify_device_binding(hwconf_hdl, devid, devid_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify device binding: (%d)\n", res);
		goto endfunction_init_hwconf;
	}
	*handle_p = hwconf_hdl;
endfunction_init_hwconf:
	if (res != FCSERR_OK)
		hwconf_parser_deinit(hwconf_hdl);
	(void)sinparser_deinit(sinparser);
	free(hwconf);

	return res;
}

void teardown_hwconfig(hwconfig_t handle)
{
	hwconf_handle_t hwconf = (hwconf_handle_t)handle;

	if (hwconf != NULL)
		hwconf_parser_deinit(hwconf);
}

int get_imei_count(uint8_t *count, hwconfig_t handle)
{
	int res = FCSERR_OK;
	hwconf_handle_t hwconf = (hwconf_handle_t)handle;

	if (count == NULL || hwconf == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	/* 0 == IMEI */
	res = hwconf_parser_get_phone_id_nr_ins(0, count, hwconf);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Unable to parse number of phone ids error=%d\n",
			res);
	}

exit:
	return res;
}

int get_imei(uint8_t index, uint8_t *buf, size_t buf_size, size_t *id_length,
		hwconfig_t handle)
{
	int res = FCSERR_OK;
	uint8_t id_count = 0;
	uint16_t id_length16;
	hwconf_handle_t hwconf = (hwconf_handle_t)handle;

	if (buf == NULL || id_length == NULL || hwconf == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	/* 0 == IMEI */
	res = hwconf_parser_get_phone_id_nr_ins(0, &id_count,
			hwconf);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Unable to parse number of phone ids error=%d\n",
			res);
		goto exit;
	}

	if (id_count == 0) {
		FCS_LOG_ERR("No IMEI found in hwconfig.\n");
		res = -FCSERR_ENOTF;
		goto exit;
	}

	if (id_count > index) {
		/*
		 * Reads length of IMEI from index
		 */
		if (FCSERR_OK != hwconf_parser_get_phone_id_length(0,
					index,
					&id_length16,
					hwconf)) {
			FCS_LOG_ERR("Could not get phone id length\n");
			goto exit;
		}

		*id_length = id_length16;
		if (*id_length < 7) {
			FCS_LOG_ERR("ID length invalid\n");
			res = -FCSERR_EINVAL;
			goto exit;
		}
	} else {
		res = -FCSERR_ENOTF;
		goto exit;
	}

	if (*id_length > buf_size) {
		FCS_LOG_ERR("Buffer to small\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	/* Reads IMEI info at index into buf */
	res = hwconf_parser_get_phone_id(0, index, buf, *id_length, hwconf);
	if (FCSERR_OK != res) {
		FCS_LOG_ERR("Unable to parse phone id, error=%d\n", res);
		goto exit;
	}

exit:
	return res;
}

int get_hwconf_dk(uint8_t **device_key, size_t *device_key_len,
	hwconfig_t handle)
{
	int res = FCSERR_OK;
	uint8_t *hwc_dk = NULL;
	uint16_t hwc_dk_len;
	hwconf_handle_t hwconf = (hwconf_handle_t)handle;

	if (device_key == NULL || device_key_len == NULL || hwconf == NULL) {
		FCS_LOG_ERR("Invalid argument,\n");
		res = -FCSERR_EINVAL;
		goto error;
	}

	res = hwconf_parser_get_hwc_dk_length(&hwc_dk_len, hwconf);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("hwconf_parser_get_hwc_dk_length returned err=%d\n",
			res);
		goto error;
	}

	if (hwc_dk_len == 0) {
		FCS_LOG_ERR("Device Key length in HWConfig is zero\n");
		res = -FCSERR_ESIZE;
		goto error;
	}

	hwc_dk = (uint8_t *)malloc(hwc_dk_len);
	if (hwc_dk == NULL) {
		FCS_LOG_ERR("Failed to allocate memory for Device Key\n");
		res = -FCSERR_ENOMEM;
		goto error;
	}

	res = hwconf_parser_get_hwc_dk(hwc_dk, hwc_dk_len, hwconf);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("hwconf_parser_get_hwc_dk returned err=%d\n", res);
		goto error;
	}

	*device_key = hwc_dk;
	*device_key_len = hwc_dk_len;

	return res;
error:
	if (hwc_dk)
		free(hwc_dk);
	return res;
}

int get_is_prototype(int *is_prototype, hwconfig_t handle)
{
	if (is_prototype == NULL || handle == NULL) {
		FCS_LOG_ERR("Invalid argument,\n");
		return -FCSERR_EINVAL;
	}

	/* Is not present in this hwconfig version */
	*is_prototype = false;

	return FCSERR_OK;
}

