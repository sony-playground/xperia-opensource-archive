/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "core.h"
#include "ta_interface.h"
#include "fcslog.h"

#include <stdint.h>

int core_get_hmac_key(uint8_t **hmac_key, uint32_t *hmac_key_len)
{
	int res = FCSERR_OK;

	if (hmac_key == NULL || hmac_key_len == NULL) {
		FCS_LOG_ERR("Invalid arguments\n");
		return -FCSERR_EINVAL;
	}

	/* Get size of unit */
	res = get_ta_unit_size(TA_MISC_PART,
			TA_KEYSTORE_HMAC_KEY_APPLY, (int *)hmac_key_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("get_ta_unit_size returned err=%d\n", res);
		return res;
	}

	if (res == FCSERR_OK && *hmac_key_len != 0) {
		*hmac_key = malloc(*hmac_key_len);

		if (*hmac_key == NULL) {
			FCS_LOG_ERR("Out of memory\n");
			return -FCSERR_ENOMEM;
		}

		res = read_ta(TA_MISC_PART, TA_KEYSTORE_HMAC_KEY_APPLY,
				*hmac_key, (int)*hmac_key_len);
		if (res != FCSERR_OK) {
			FCS_LOG_INF("Unable to read TA unit %d, error=%d\n",
					TA_KEYSTORE_HMAC_KEY_APPLY, res);
			free(*hmac_key);
			return res;
		}
	} else {
		*hmac_key = NULL;
	}
	return res;
}
