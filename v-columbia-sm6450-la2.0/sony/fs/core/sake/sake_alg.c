/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "sake_engine.h"
#include "sake_engine_internal.h"
#include "sake_alg.h"
#include "fcserr.h"
#include "string.h"
#include <stdlib.h>
#include "fcslog.h"

/*
 * create_asn_rsa_public_key
 *
 * @param [in] public_key
 * @param [in] nkey
 * @param [in] nlen
 * @param [in] ekey
 * @param [in] elen
 *
 * @return The function returns S1RESULT_NO_ERROR on success
 *  and a negative error code otherwise.
 */
static int create_asn_rsa_public_key(asn_rsa_public_key_t *public_key,
				     const uint8_t *nkey, int32_t nlen,
				     const uint8_t *ekey, int32_t elen);

int sake_add_padding(
	const uint8_t *data, int32_t dataLen, uint8_t *padded, int sigLen)
{
	int32_t k = 0;
	int32_t a;
	int result = FCSERR_OK;

	if (!data || !padded) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	do {
		if (dataLen > (sigLen - 4)) {
			result = -FCSERR_ESTATE;
			break;
		}
		padded[k++] = 0;
		padded[k++] = 1;
		for (a = 0; a < sigLen - dataLen - 3; a++)
			padded[k++] = 0xff;
		padded[k++] = 0;
		if ((sigLen - k) != dataLen) {
			result = -FCSERR_ESTATE;
			break;
		}

		memcpy(&padded[k], data, dataLen);
	} while (0);

	return result;
}

int sake_pub_key_encrypt(struct sake_internal_handle *handle,
			 const uint8_t *from, int32_t length, uint8_t *to,
			 const uint8_t *nkey, int32_t nlen,
			 const uint8_t *ekey, int32_t elen)
{
	int res = FCSERR_OK;
	asn_rsa_public_key_t public_key = NULL;

	do {
		/* assuming all input parameters are set properly since not
		 * public function
		 */
		res = create_asn_rsa_public_key(&public_key, nkey, nlen, ekey,
						elen);
		if (res != FCSERR_OK)
			break;

		res = handle->funcs.rsa_functions.encrypt_no_pad(from, length,
								 to, length,
								 public_key);
		if (res != FCSERR_OK)
			break;
	} while (0);

	free(public_key);
	return res;
}

static int create_asn_rsa_public_key(asn_rsa_public_key_t *public_key,
				     const uint8_t *nkey, int32_t nlen,
				     const uint8_t *ekey, int32_t elen)
{
	int result = FCSERR_OK;
	uint8_t *raw_key = NULL;
	uint32_t key_idx = 0;
	uint32_t tot_payload_len = 0;

	if (!public_key || !nkey || !ekey) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	do {
		/* +10 for the asn.1 container overhead */
		raw_key = (uint8_t *)malloc(sizeof(uint8_t) * (nlen + elen +
							      10));
		if (!raw_key) {
			result = -FCSERR_ENOMEM;
			break;
		}
		tot_payload_len = nlen + elen + 6;

		if (((tot_payload_len >> 16) != 0) ||
		   ((nlen >> 16) != 0) ||
		   ((elen >> 8) != 0)) {
			/*
			 * failing because this hardcoded asn.1 string cannot
			 * handle integers > 65535
			 */
			result = -FCSERR_ESTATE;
			break;
		}

		raw_key[key_idx++] = 0x30; /* asn1 sequence tag */
		raw_key[key_idx++] = 0x82; /* asn1 length of length tag */
		raw_key[key_idx++] = (tot_payload_len >> 8) & 0xff;/*lenTotHi*/
		raw_key[key_idx++] = tot_payload_len & 0xff; /* lenTotLo */
		raw_key[key_idx++] = 0x02; /* asn1 integer tag */
		raw_key[key_idx++] = 0x82; /*asn1 length of length tag */
		raw_key[key_idx++] = (nlen >> 8) & 0xff; /* lenHiMod */
		raw_key[key_idx++] = nlen & 0xff; /* lenLoMod */
		memcpy(&raw_key[key_idx], nkey, nlen); /* modulus */
		key_idx += nlen;
		raw_key[key_idx++] = 0x02; /* asn1 integer tag */
		raw_key[key_idx++] = elen & 0xff; /* lenExp */
		memcpy(&raw_key[key_idx], ekey, elen); /* modulus */
		key_idx += elen;

		if (key_idx != (tot_payload_len + 4)) {
			result = -FCSERR_ESTATE;
			break;
		}

		*public_key = (asn_rsa_public_key_t) raw_key;
	} while (0);

	if (result != FCSERR_OK)
		free(raw_key);

	return result;
}

