/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdint.h>
#include <ksio.h>
#include <ksnvio.h>
#include <storage.h>
#include <fcslog.h>
#include <fcserr.h>

#define MIN(x, y) ((x) < (y)?(x):(y))

#define KS_PARTITION_NAME "xflkeystore"
#define KS_BAK_PARTITION_NAME "xflkeystorebak"

int plf_nv_read_cb(
	ks_io_state_t *state, uint8_t *data, uint32_t *data_sz)
{
	struct nvio_state *nv_state = (struct nvio_state *)state;
	struct storage_ctx *ctx;
	off_t sz;
	int res;
	ssize_t ret;

	if (nv_state == NULL || data_sz == NULL) {
		FCS_LOG_ERR("invalid param\n");
		return -FCSERR_EINVAL;
	}

	if (nv_state->partition == KS_NV_ORG)
		ctx = storage_open_by_name(NULL, KS_PARTITION_NAME);
	else if (nv_state->partition == KS_NV_BAK)
		ctx = storage_open_by_name(NULL, KS_BAK_PARTITION_NAME);
	else {
		FCS_LOG_ERR("invalid partition: %u\n", nv_state->partition);
		return -FCSERR_EIO;
	}
	if (ctx == NULL) {
		FCS_LOG_ERR("could not open partition\n");
		return -FCSERR_EOPEN;
	}

	sz = storage_lseek(ctx, 0, STORAGE_SEEK_END);
	if (sz < 0) {
		FCS_LOG_ERR("seek failed (%d)\n", sz);
		res = -FCSERR_EIO;
		goto exit;
	}

	if (data == NULL) {
		res = FCSERR_OK;
		*data_sz = (uint32_t)sz;
		goto exit;
	}

	if (storage_lseek(ctx, 0, STORAGE_SEEK_SET) < 0) {
		FCS_LOG_ERR("seek failed (%d)\n", sz);
		res = -FCSERR_EIO;
		goto exit;
	}

	ret = storage_read(ctx, data, MIN(sz, *data_sz));
	if (ret != MIN(sz, *data_sz)) {
		FCS_LOG_ERR("read failed (%d)\n", ret);
		res = -FCSERR_EIO;
		goto exit;
	}
	res = FCSERR_OK;

exit:
	storage_close(ctx);
	return res;
}

int plf_nv_write_cb(
	ks_io_state_t *state, uint8_t *data, const uint32_t data_sz)
{
	struct nvio_state *nv_state = (struct nvio_state *)state;
	struct storage_ctx *ctx;
	int res;
	ssize_t ret;

	if (nv_state == NULL) {
		FCS_LOG_ERR("invalid param\n");
		return -FCSERR_EINVAL;
	}

	if (nv_state->partition == KS_NV_ORG)
		ctx = storage_open_by_name(NULL, KS_PARTITION_NAME);
	else if (nv_state->partition == KS_NV_BAK)
		ctx = storage_open_by_name(NULL, KS_BAK_PARTITION_NAME);
	else {
		FCS_LOG_ERR("invalid partition: %u\n", nv_state->partition);
		return -FCSERR_EPART;
	}
	if (ctx == NULL) {
		FCS_LOG_ERR("could not open partition\n");
		return -FCSERR_EOPEN;
	}

	ret = storage_write(ctx, data, data_sz);
	if (ret != data_sz) {
		FCS_LOG_ERR("write failed (%zd)\n", ret);
		res = -FCSERR_EIO;
		goto exit;
	}
	res = FCSERR_OK;

exit:
	storage_close(ctx);
	return res;
}

