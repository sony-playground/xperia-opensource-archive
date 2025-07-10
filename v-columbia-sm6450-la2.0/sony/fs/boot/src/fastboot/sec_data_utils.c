/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdint.h>
#include <string.h>
#include "xflattest_int.h"
#include "fcslog.h"
#include "fcserr.h"
#include "fcsenv_def.h"
#include "digest_types.h"


int sec_data_get_rooting_status(uint8_t *data)
{
	int ret;
	struct xfl_sec_data xfl_sec_data_var;

	memset(&xfl_sec_data_var, 0, sizeof(struct xfl_sec_data));

	if (data == NULL) {
		FCS_LOG_ERR("Invalid parameters\n");
		return -FCSERR_EINVAL;
	}

	ret = read_xfl_sec_data(&xfl_sec_data_var);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read xfl_sec_data\n");
		return ret;
	}

	*data = xfl_sec_data_var.bl_unlock_status;

	FCS_LOG_INF("Rooting status read: (%d)\n", *data);

	return FCSERR_OK;
}

int sec_data_get_keystore_hash(uint8_t *data, size_t data_sz)
{
	int ret;
	struct xfl_sec_data xfl_sec_data_var;

	memset(&xfl_sec_data_var, 0, sizeof(struct xfl_sec_data));

	if (data == NULL) {
		FCS_LOG_ERR("Invalid parameters\n");
		return -FCSERR_EINVAL;
	}

	if (data_sz < SHA256_HASH_OUT_SIZE) {
		FCS_LOG_ERR("data_sz is not big enough\n");
		return -FCSERR_ENOMEM;
	}

	ret = read_xfl_sec_data(&xfl_sec_data_var);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read xfl secdata\n");
		return ret;
	}

	memcpy(data, xfl_sec_data_var.keystore_hash_sha256,
			SHA256_HASH_OUT_SIZE);

	return FCSERR_OK;
}

uint32_t sec_data_get_num_rollback_counters(void)
{
	return NUM_OF_RB_INDEX;
}

int sec_data_get_rollback_counter(uint32_t index, uint64_t *val)
{
	int ret;
	struct xfl_sec_data xfl_sec_data;

	memset(&xfl_sec_data, 0, sizeof(struct xfl_sec_data));

	if (val == NULL ||
			index >= XFLATTEST_MAX_NUM_OF_RB_INDEX ||
			index >= NUM_OF_RB_INDEX) {
		FCS_LOG_ERR("Invalid parameters\n");
		return -FCSERR_EINVAL;
	}

	ret = read_xfl_sec_data(&xfl_sec_data);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get secdata\n");
		return ret;
	}

	*val = xfl_sec_data.rollback_counter[index];
	return ret;
}

int sec_data_get_xcs_rot(uint32_t *is_xcs_rot)
{
	int ret;
	struct xfl_sec_data xfl_sec_data;

	if (is_xcs_rot == NULL) {
		FCS_LOG_ERR("Invalid parameters\n");
		return -FCSERR_EINVAL;
	}

	memset(&xfl_sec_data, 0, sizeof(struct xfl_sec_data));

	ret = read_xfl_sec_data(&xfl_sec_data);
	if (ret < 0) {
		FCS_LOG_ERR("Failed to get secdata\n");
		return ret;
	}

	*is_xcs_rot = xfl_sec_data.xcs_rot;

	return FCSERR_OK;
}

int sec_data_get_ks_counter(uint32_t *ks_counter)
{
	int ret;
	struct xfl_sec_data xfl_sec_data;

	if (ks_counter == NULL) {
		FCS_LOG_ERR("Invalid parameters\n");
		return -FCSERR_EINVAL;
	}

	memset(&xfl_sec_data, 0, sizeof(struct xfl_sec_data));

	ret = read_xfl_sec_data(&xfl_sec_data);
	if (ret < 0) {
		FCS_LOG_ERR("Failed to get secdata\n");
		return ret;
	}

	*ks_counter = xfl_sec_data.rpmb_ks_counter;

	return FCSERR_OK;
}

int sec_data_get_has_been_unlocked(uint32_t *has_been_unlocked)
{
	int ret;
	struct xfl_sec_data xfl_sec_data;

	if (has_been_unlocked == NULL) {
		FCS_LOG_ERR("Invalid parameters\n");
		return -FCSERR_EINVAL;
	}

	memset(&xfl_sec_data, 0, sizeof(struct xfl_sec_data));

	ret = read_xfl_sec_data(&xfl_sec_data);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read xfl_sec_data\n");
		return ret;
	}

	if (((xfl_sec_data.version & 0xFFFF0000) !=
			(PROTOCOL_VERSION_2_XFL_SEC_DATA & 0xFFFF0000))) {
		FCS_LOG_ERR("Bad xfl_sec_data protocol version magic\n");
		return -FCSERR_EBADVER;
	}

	if (xfl_sec_data.version < PROTOCOL_VERSION_2_XFL_SEC_DATA) {
		FCS_LOG_ERR("Unsupported xfl_sec_data protocol version\n");
		return -FCSERR_EBADVER;
	}

	*has_been_unlocked = xfl_sec_data.has_been_unlocked;

	return FCSERR_OK;
}
