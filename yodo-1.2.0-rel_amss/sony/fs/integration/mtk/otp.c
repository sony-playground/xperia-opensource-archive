/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "otp.h"
#include "security_properties.h"
#include "handler_list.h"
#include "write_image.h"
#include "partman.h"
#include "protocol_util.h"
#include "fcserr.h"
#include "fcslog.h"
#include "core.h"

#define EFUSE_IMAGE_PARTITION "efuse"

static int efuseimg_flash(const uint8_t *data, uint16_t prop_len)
{
	int res;
	ssize_t partition_size;
	struct storage_ctx *sctx;
	bool is_fused;

	res = core_is_fused(&is_fused);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get fuse status (%d)\n", res);
		return res;
	}
	if (is_fused) {
		FCS_LOG_ERR("Security properties already written\n");
		return -FCSERR_EINVAL;
	}

	/*
	 * Open partition if it exists, do nothing if it is already opened
	 * and return error if it isn't open and doesn't exist.
	 */
	sctx = storage_open_by_name(NULL, EFUSE_IMAGE_PARTITION);
	if (sctx == NULL) {
		FCS_LOG_ERR("Partition %s does not exist\n",
				EFUSE_IMAGE_PARTITION);
		return -FCSERR_EINVAL;
	}

	partition_size = pu_get_part_size(sctx);
	if (partition_size < 0) {
		FCS_LOG_ERR("IO Error\n");
		return -FCSERR_EIO;
	}

	if (prop_len > partition_size) {
		FCS_LOG_ERR("Property data does not fit in partition\n");
		return -FCSERR_EPART;
	}

	res = write_image(sctx, (uint8_t *)data, 0, prop_len);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("efuse image write fail\n");

	return res;
}

int otp_init(void *handle)
{
	int res = FCSERR_OK;

	res = handler_list_add_handler(handle, &efuseimg_flash,
			(void *)S1_OTP_DATA);
	if (res < 0)
		FCS_LOG_ERR("Failed to add handler\n");

	return res;
}
