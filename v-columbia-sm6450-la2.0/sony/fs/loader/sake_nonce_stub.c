/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "sake_nonce.h"
#include "core.h"
#include "fcslog.h"
#include "fcserr.h"

int sake_get_nonce(uint8_t *nonce, size_t nonce_len)
{
	static uint8_t buf[SAKE_NONCE_LEN];
	static bool initiated;
	uint8_t *devid = NULL;
	size_t devid_len = 0;
	int res = FCSERR_OK;

	if (nonce == NULL) {
		FCS_LOG_INF("Invalid parameters\n");
		return -FCSERR_EINVAL;
	}

	if (nonce_len < SAKE_NONCE_LEN)
		return -FCSERR_EINVAL;

	if (initiated) {
		memcpy(nonce, buf, SAKE_NONCE_LEN);
		return FCSERR_OK;
	}

	devid_len = core_get_dieid_len();
	devid = malloc(devid_len);
	if (devid == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto error;
	}

	res = core_get_dieid(devid, devid_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get dev id from env: (%d)\n", res);
		res = -FCSERR_ESTATE;
		goto error;
	}

	res = fcs_srand(*devid);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Seed failed\n");
		goto error;
	}

	fcs_urand(nonce, SAKE_NONCE_LEN);
	memcpy(buf, nonce, SAKE_NONCE_LEN);
	initiated = true;
error:
	free(devid);
	return res;
}
