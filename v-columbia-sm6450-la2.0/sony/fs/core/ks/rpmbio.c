/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */


#include <rpmbio.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <fcslog.h>
#include <fcserr.h>
#include <xflattest.h>
#include <xflattest_int.h>

static int plf_rpmb_read_cb(
	ks_io_state_t *state, uint8_t *data, uint32_t *data_sz)
{
	int ret;
	(void)(state); /* Unused parameter */
	struct xfl_sec_data xfl_sec_data;
	struct ks_rpmb_data ks_data;

	memset(&xfl_sec_data, 0, sizeof(struct xfl_sec_data));
	memset(&ks_data, 0, sizeof(struct ks_rpmb_data));

	if (data_sz == NULL || data == NULL) {
		FCS_LOG_ERR("invalid pointer\n");
		return -FCSERR_EINVAL;
	}

	if (*data_sz < sizeof(struct ks_rpmb_data)) {
		FCS_LOG_ERR("buffer too small\n");
		return -FCSERR_ESIZE;
	}

	ret = read_xfl_sec_data(&xfl_sec_data);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to read xfl_sec_data\n");
		return ret;
	}
	ks_data.ks_counter = xfl_sec_data.rpmb_ks_counter;
	ks_data.xcs_rot = xfl_sec_data.xcs_rot;
	memcpy(ks_data.ks_hash_sha256,
		xfl_sec_data.keystore_hash_sha256,
		SHA256_HASH_OUT_SIZE);

	*(struct ks_rpmb_data *)data = ks_data;
	*data_sz = sizeof(struct ks_rpmb_data);

	return FCSERR_OK;
}

static int plf_rpmb_write_cb(
	ks_io_state_t *state, uint8_t *data, uint32_t data_sz)
{
	int ret;
	(void)(state); /* Unused parameter */
	struct xfl_sec_data xfl_sec_data;
	struct ks_rpmb_data ks_data;

	if (data == NULL) {
		FCS_LOG_ERR("invalid pointer\n");
		return -FCSERR_EINVAL;
	}

	if (data_sz > sizeof(struct ks_rpmb_data)) {
		FCS_LOG_ERR("buffer too big\n");
		return -FCSERR_ESIZE;
	}

	ret = read_xfl_sec_data(&xfl_sec_data);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to read xfl_sec_data\n");
		return ret;
	}

	ks_data = *(struct ks_rpmb_data *)data;

	xfl_sec_data.rpmb_ks_counter = ks_data.ks_counter;
	xfl_sec_data.xcs_rot = ks_data.xcs_rot;
	memcpy(xfl_sec_data.keystore_hash_sha256,
		ks_data.ks_hash_sha256,
		SHA256_HASH_OUT_SIZE);

	ret = write_xfl_sec_data(&xfl_sec_data);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to write xfl_sec_data\n");
		return ret;
	}

	return FCSERR_OK;
}

/* Destructor */
static int rpmb_destroy_cb(ks_io_state_t *state)
{
	(void)(state); /* Unused parameter */

	/* Nothing to do since no state is allocated by "constructor" */
	return FCSERR_OK;
}

/* Constructor */
int rpmb_open(struct ks_io_handle **handle)
{
	if (handle == NULL)
		return -FCSERR_EINVAL;

	*handle = (struct ks_io_handle *)malloc(sizeof(struct ks_io_handle));
	if (*handle == NULL) {
		FCS_LOG_ERR("malloc failed\n");
		return -FCSERR_ENOMEM;
	}

	(*handle)->read = plf_rpmb_read_cb;
	(*handle)->write = plf_rpmb_write_cb;
	(*handle)->destroy = rpmb_destroy_cb;
	(*handle)->state = NULL;

	return FCSERR_OK;
}
