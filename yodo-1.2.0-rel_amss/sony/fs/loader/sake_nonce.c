/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <string.h>
#include "sake_nonce.h"
#include "xflattest.h"
#include "xflattest_int.h"
#include "fcslog.h"
#include "fcserr.h"

int sake_get_nonce(uint8_t *nonce, size_t nonce_len)
{
	int ret;
	struct xfl_sec_data xfl_sec_data;

	memset(&xfl_sec_data, 0, sizeof(struct xfl_sec_data));

	if (nonce == NULL) {
		FCS_LOG_INF("Invalid parameters\n");
		return -FCSERR_EINVAL;
	}

	if (nonce_len < SAKE_NONCE_LEN)
		return -FCSERR_EINVAL;

	ret = read_xfl_sec_data(&xfl_sec_data);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get secdata\n");
		return -FCSERR_EINVAL;
	}

	memcpy(nonce, xfl_sec_data.sake_nonce, SAKE_NONCE_LEN);

	return ret;
}
