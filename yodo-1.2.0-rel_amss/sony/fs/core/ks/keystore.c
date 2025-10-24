/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */


/* The exported API definitions based on s1_doc */
#include "kspk.h"

#include <stdbool.h>

/* The auto-generated (asn1c) stuff		*/
#include "digest.h"
#include "KeyStore.h"
#include "KeyStoreEntryData.h"
#include "kstypes.h"
#include "digest_types.h"
#include "kscrypto.h"
#include "ksnvio.h"
#include "rpmbio.h"
#include "kscrypto.h"

#include "fcslog.h"
#include "fcserr.h"
#include "fcs_defines.h"
#include "rule_verifier.h"
#include "cms_verifier.h"
#include "ta_interface.h"
#include "rooting_status.h"
#include "convert.h"

struct ks_ctx
{
	struct dev_binding binding;
	struct ks_io_handle *nv_orgh;
	struct ks_io_handle *nv_bakh;
	struct ks_io_handle *rpmbh;
	KeyStore_t *ks;
	uint8_t *rot;
	uint32_t rot_sz;
	uint8_t *sha256hash;
	uint32_t cms_counter;
	uint8_t *hmac_key;
	uint32_t hmac_key_len;
	uint32_t verified_with_hmac;
	uint32_t ks_counter_updated;
	uint32_t ks_updated;
	uint32_t ks_xcs_updated;
	uint32_t ks_revert;
	uint32_t update_hmac_key;
};

int ks_verified_with_hmac(struct ks_ctx *const context, int *retval)
{
	if (!context || !retval) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	*retval = context->verified_with_hmac;
	return FCSERR_OK;
}

int ks_get_xcs_updated(struct ks_ctx *const context, uint32_t *xcs_updated)

{
	if (context == NULL || xcs_updated == NULL) {
		FCS_LOG_ERR("Invalid input\n");
		return -FCSERR_EINVAL;
	}

	*xcs_updated = context->ks_xcs_updated;

	return FCSERR_OK;
}

int ks_set_update_hmac_key(struct ks_ctx *const context)
{
	if (context == NULL) {
		FCS_LOG_ERR("Invalid input\n");
		return -FCSERR_EINVAL;
	}

	context->update_hmac_key = 1;
	return FCSERR_OK;
}

int ks_set_hmac_key(struct ks_ctx *const context, const uint8_t *hmac_key,
		uint32_t hmac_key_len)
{
	if (context == NULL || hmac_key == NULL || hmac_key_len == 0) {
		FCS_LOG_ERR("Invalid input\n");
		return -FCSERR_EINVAL;
	}

	/*
	 * context->hmac_key should always be NULL here.
	 * Doing a free just in case.
	 */
	if (context->hmac_key != NULL)
		free(context->hmac_key);

	context->hmac_key = malloc(hmac_key_len);
	if (context->hmac_key == NULL) {
		FCS_LOG_ERR("malloc failed\n");
		return -FCSERR_ENOMEM;
	}
	context->hmac_key_len = hmac_key_len;
	memcpy(context->hmac_key, hmac_key, hmac_key_len);

	return FCSERR_OK;
}

int ks_is_loaded(struct ks_ctx *const context)
{

	if (context == NULL)
		return 0;

	if (context->ks)
		return 1;
	else
		return 0;
}

static int ks_get_sha256(
	uint8_t *buf, uint32_t buf_sz, uint8_t *hash)
{
	int res;
	struct digest *dgst = NULL;
	uint32_t calc_hash_length;
	uint8_t *calc_hash;

	if (hash == NULL || buf == NULL || buf_sz == 0) {
		FCS_LOG_ERR("Wrong input values\n");
		return -FCSERR_EINVAL;
	}

	res = digest_sha256_init(&dgst);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init digest session\n");
		goto exit;
	}

	res = digest_sha256_update(dgst, buf, buf_sz);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to update digest session\n");
		goto exit;
	}

	res = digest_sha256_final(dgst, &calc_hash, &calc_hash_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to finalize digest session\n");
		goto exit;
	}

	memcpy(hash, calc_hash, calc_hash_length);

exit:
	digest_sha256_deinit(dgst);

	return res;
}

static int ks_hmac_sha256(const uint8_t *key, uint32_t key_len,
		const uint8_t *data, uint32_t data_len,
		uint8_t *mac)
{
	uint8_t k_pad[SHA256_BLOCK_SIZE];
	uint8_t i;
	uint8_t *msg = NULL;
	uint8_t final_msg[SHA256_HASH_OUT_SIZE + SHA256_BLOCK_SIZE];
	int res = FCSERR_OK;

	if (key == NULL || data == NULL || mac == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return -FCSERR_EINVAL;
	}

	if (key_len > SHA256_BLOCK_SIZE || key_len == 0) {
		FCS_LOG_ERR("Invalid hmac key length\n");
		return -FCSERR_EINVAL;
	}

	/* the HMAC_SHA256 transform looks like:
	*
	* SHA256(K XOR opad, SHA256(K XOR ipad, text))
	*
	* where K is an n byte key
	* ipad is the byte 0x36 repeated 64 times
	* opad is the byte 0x5c repeated 64 times
	* and text is the data being protected
	*/
	memset(k_pad, 0, sizeof(k_pad));
	memcpy(k_pad, key, key_len);

	for (i = 0; i < SHA256_BLOCK_SIZE; i++)
		k_pad[i] ^= 0x36;

	msg = malloc(data_len + SHA256_BLOCK_SIZE);

	if (msg == NULL) {
		FCS_LOG_ERR("malloc failed\n");
		return -FCSERR_ENOMEM;
	}

	memcpy(msg, k_pad, SHA256_BLOCK_SIZE);
	memcpy(msg + SHA256_BLOCK_SIZE, data, data_len);

	res = ks_get_sha256(msg, data_len + SHA256_BLOCK_SIZE, mac);

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to calculate sha256\n");
		goto exit;
	}

	memset(k_pad, 0, sizeof(k_pad));
	memcpy(k_pad, key, key_len);

	for (i = 0; i < SHA256_BLOCK_SIZE; i++)
		k_pad[i] ^= 0x5c;

	memcpy(final_msg, k_pad, SHA256_BLOCK_SIZE);
	memcpy(final_msg + SHA256_BLOCK_SIZE, mac, SHA256_HASH_OUT_SIZE);

	res = ks_get_sha256(final_msg,
			SHA256_BLOCK_SIZE + SHA256_HASH_OUT_SIZE, mac);

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to calculate sha256\n");
		goto exit;
	}

exit:
	free(msg);
	return res;
}

int ks_get_hash(struct ks_ctx *const context, uint8_t *hash,
		uint32_t hash_len)
{
	int ret = FCSERR_OK;

	if (context == NULL || hash == NULL ||
			hash_len < SHA256_HASH_OUT_SIZE) {
		FCS_LOG_ERR("Invalid input parameters\n");
		ret = -FCSERR_EINVAL;
		goto exit;
	}

	memcpy(hash, context->sha256hash, SHA256_HASH_OUT_SIZE);
exit:

	return ret;
}

static int ks_hash_zeros(const uint8_t *hash, uint32_t hash_sz, bool *all_zeros)
{
	uint32_t i;

	if (!hash || hash_sz == 0 || !all_zeros) {
		FCS_LOG_ERR("Wrong input values\n");
		return -FCSERR_EINVAL;
	}

	*all_zeros = true;

	for (i = 0; i < hash_sz; i++) {
		if (hash[i] != 0) {
			*all_zeros = false;
			return FCSERR_OK;
		}
	}

	return FCSERR_OK;
}

static int ks_get(struct ks_io_handle *hdl, uint8_t **buf, uint32_t *buf_len)
{
	int ret;

	if (hdl == NULL || buf == NULL ||
	    buf_len == NULL) {
		FCS_LOG_ERR("Invalid input\n");
		return -FCSERR_EINVAL;
	}

	/* Read Keystore from NV*/
	ret = ks_io_read(hdl, NULL, buf_len);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("read failed\n");
		return ret;
	}
	*buf = malloc(*buf_len);
	if (*buf == NULL) {
		FCS_LOG_ERR("malloc failed\n");
		return -FCSERR_ENOMEM;
	}
	ret = ks_io_read(hdl, *buf, buf_len);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("read failed\n");
		free(*buf);
		return ret;
	}

	return FCSERR_OK;
}

static int ks_check(struct ks_ctx *const ctx, uint8_t *buf, uint32_t buf_len)
{
	int ret;
	struct ks_rpmb_data rpmb_data;
	uint32_t rpmb_sz;
	uint8_t *payload = NULL;
	uint32_t payload_len;
	asn_dec_rval_t rval;
	bool hash_all_zeros;
	uint8_t unlock_status;
	uint8_t rck_h[RCK_H_LENGTH];

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (ks_is_loaded(ctx)) {
		ASN_STRUCT_FREE(asn_DEF_KeyStore, (void *) (ctx->ks));
		ctx->ks = NULL;
	}

	/* Read the RPMB data */
	rpmb_sz = sizeof(struct ks_rpmb_data);
	ret = ks_io_read(ctx->rpmbh, (uint8_t *)&rpmb_data, &rpmb_sz);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("rpmb read failed\n");
		return ret;
	}

	/* plf_cms_cb() verifies signature and Device Binding */
	/* keystore counter is output from the CMS attributes */
	ret = plf_cms_cb(
			ctx->rot, ctx->rot_sz, buf, buf_len,
			&ctx->binding,
			&ctx->verified_with_hmac, &ctx->cms_counter,
			&payload, &payload_len);

	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("cms verify failed\n");
		return -FCSERR_ESTATE;
	}

	ret = ks_get_sha256(payload, payload_len, ctx->sha256hash);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to hash ks payload: %d\n", ret);
		goto exit;
	}

	ret = ks_hash_zeros(rpmb_data.ks_hash_sha256, SHA256_HASH_OUT_SIZE,
			&hash_all_zeros);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to check hash for all zeros\n");
		goto exit;
	}
	/*
	 * If the keystore SHA256 hash is equal to the stored SHA256 hash,
	 * it means it is the same keystore as the last one which was
	 * verified. In that case keystore counter equal or larger than the
	 * stored ks counter is allowed.
	 * Otherwise, the keystore counter must be larger than the stored one.
	 */
	if (!memcmp(rpmb_data.ks_hash_sha256, ctx->sha256hash,
				SHA256_HASH_OUT_SIZE)) {
		if (rpmb_data.ks_counter > ctx->cms_counter) {
			FCS_LOG_ERR("Invalid counter rpmb: %d, cms: %d\n",
				rpmb_data.ks_counter, ctx->cms_counter);
			ret = -FCSERR_ESTATE;
			goto exit;
		}
		if (ctx->cms_counter > rpmb_data.ks_counter)
			ctx->ks_counter_updated = 1;
	} else {
		if ((rpmb_data.ks_counter > ctx->cms_counter) ||
			((rpmb_data.ks_counter == ctx->cms_counter) &&
			 !hash_all_zeros)) {
			FCS_LOG_ERR("Invalid counter rpmb: %u, cms: %u\n",
				rpmb_data.ks_counter, ctx->cms_counter);
			ret = -FCSERR_ESTATE;
			goto exit;
		}
		if (rpmb_data.xcs_rot != 0) {
			FCS_LOG_ERR(
				"Updating keystore not allowed if XCS keystore has been set previously\n");
			ret = -FCSERR_ESTATE;
			goto exit;
		}
		ctx->ks_updated = 1;
	}

	/* Use asn1c generated decoder to decode */
	rval = ber_decode(0, &asn_DEF_KeyStore, (void **)&ctx->ks,
			payload, payload_len);
	if (rval.code != RC_OK) {
		FCS_LOG_ERR("decode failed\n");
		ASN_STRUCT_FREE(asn_DEF_KeyStore, (void *) (ctx->ks));
		ctx->ks = NULL;
		ret = -FCSERR_EDATA;
		goto exit;
	}

	ctx->ks_xcs_updated = 0;
	if (ctx->ks->xcs && ctx->ks_updated) {
		ret = get_simlock_unlock_data(&unlock_status, rck_h);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("Failed to read SIMLock unlock data: %d\n",
					ret);
			goto exit;
		}
		if (unlock_status != BOOT_UNLOCKABLE &&
			unlock_status != BOOT_UNLOCKABLE_SIMLOCK_UNLOCKED) {
			FCS_LOG_ERR(
				"XCS keystore not allowed if bootloader unlock is not allowed\n");
			ret = -FCSERR_ESTATE;
			goto exit;
		}
		ctx->ks_xcs_updated = 1;
	}

exit:
	free(payload);
	return ret;
}

int ks_load_keystore(struct ks_ctx *const context, uint8_t part)
{
	uint8_t *buf = NULL;
	uint32_t buf_len;
	struct ks_io_handle *nv_hdl = NULL;
	int ret;

	if (!context) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (part == XFLKEYSTORE_PRIM)
		nv_hdl = context->nv_orgh;
	else if (part == XFLKEYSTORE_BAK)
		nv_hdl = context->nv_bakh;

	ret = ks_get(nv_hdl, &buf, &buf_len);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("ks_get failed\n");
		return ret;
	}

	ret = ks_check(context, buf, buf_len);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("keystore check failed\n");
		if (part == XFLKEYSTORE_BAK)
			goto exit;

		nv_hdl = context->nv_bakh;
		free(buf);
		buf = NULL;

		ret = ks_get(nv_hdl, &buf, &buf_len);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("ks_get failed\n");
			goto exit;
		}

		ret = ks_check(context, buf, buf_len);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("keystore check failed\n");
			goto exit;
		}

		context->ks_revert = 1;
	}

exit:
	free(buf);
	return ret;
}

int ks_set_keystore(struct ks_ctx * const context)
{
	int ret;
	struct ks_rpmb_data rpmb_data;
	uint8_t *buf = NULL;
	uint32_t buf_len;
	uint8_t *buf_bak = NULL;
	uint32_t buf_bak_len;

	if (!ks_is_loaded(context)) {
		FCS_LOG_ERR("trying to set keystore without prior load\n");
		return -FCSERR_ESTATE;
	}

	ret = ks_get(context->nv_orgh, &buf, &buf_len);
	if (ret != FCSERR_OK)
		return ret;

	ret = ks_get(context->nv_bakh, &buf_bak, &buf_bak_len);
	if (ret != FCSERR_OK) {
		free(buf);
		return ret;
	}

	if (buf_len != buf_bak_len) {
		FCS_LOG_ERR("invalid partition layout\n");
		ret = -FCSERR_EPART;
		goto exit;
	}

	if (context->ks_revert == 1) {
		/* Copy xflkeystorebak to xflkeystore */
		ret = ks_io_write(context->nv_orgh, buf_bak, buf_bak_len);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("unable to write keystore\n");
			goto exit;
		}
	} else {
		if (memcmp(buf, buf_bak, buf_len)) {
			/* Copy xflkeystore to xflkeystorebak */
			ret = ks_io_write(context->nv_bakh, buf,
						buf_len);
			if (ret != FCSERR_OK) {
				FCS_LOG_ERR("unable to write keystore\n");
				goto exit;
			}
		}
	}

	if (context->ks_updated || context->ks_counter_updated) {
		rpmb_data.ks_counter = context->cms_counter;
		rpmb_data.xcs_rot = context->ks->xcs;
		memcpy(rpmb_data.ks_hash_sha256, context->sha256hash,
				SHA256_HASH_OUT_SIZE);
		ret = ks_io_write(context->rpmbh, (uint8_t *)&rpmb_data,
				sizeof(struct ks_rpmb_data));
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("failed to write to rpmb\n");
			goto exit;
		}
	}
	if (context->update_hmac_key) {
		ret = write_ta(TA_MISC_PART, TA_KEYSTORE_HMAC_KEY_APPLY,
				context->hmac_key, context->hmac_key_len);
		if (ret != FCSERR_OK)
			FCS_LOG_ERR("failed to write to miscTA\n");
	}

exit:
	free(buf);
	free(buf_bak);
	return ret;
}

int ks_compare_partitions(struct ks_ctx * const context, int *equal)
{
	int ret;
	uint8_t *buf = NULL;
	uint32_t buf_len;
	uint8_t *buf_bak = NULL;
	uint32_t buf_bak_len;

	if (!context || !equal) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	*equal = 0;

	ret = ks_get(context->nv_orgh, &buf, &buf_len);
	if (ret != FCSERR_OK)
		return ret;

	ret = ks_get(context->nv_bakh, &buf_bak, &buf_bak_len);
	if (ret != FCSERR_OK)
	{
		free(buf);
		return ret;
	}

	if (buf_len != buf_bak_len) {
		FCS_LOG_ERR("invalid partition layout\n");
		ret = -FCSERR_EPART;
		goto exit;
	}

	if (!memcmp(buf, buf_bak, buf_len))
		*equal = 1;

exit:
	free(buf);
	free(buf_bak);
	return ret;
}

int ks_create_static(
	struct ks_ctx **keystore_handle,
	uint8_t *dev_id, uint32_t dev_id_sz,
	uint8_t *imei, uint32_t imei_sz,
	uint8_t *rot, uint32_t rot_sz,
	const uint8_t *hmac_key, uint32_t hmac_key_len)
{
	int res;
	struct ks_io_handle *hdl;
	uint8_t die_id_hmac[SHA256_HASH_OUT_SIZE];
	uint8_t imei_hmac_bin[SHA256_HASH_OUT_SIZE];

	if (keystore_handle == NULL || dev_id == NULL || (imei == NULL &&
			imei_sz > 0) || rot == NULL || dev_id_sz == 0
			|| rot_sz == 0) {
		FCS_LOG_ERR("invalid parameters\n");
		return -FCSERR_EINVAL;
	}

	if (((hmac_key_len != 0) && hmac_key == NULL) ||
		((hmac_key_len == 0) && (hmac_key != NULL))) {
		FCS_LOG_ERR("Invalid input\n");
		return -FCSERR_EINVAL;
	}

	/* Create keystore handle */
	*keystore_handle = (struct ks_ctx *)calloc(1, sizeof(struct ks_ctx));
	if (*keystore_handle == NULL) {
		FCS_LOG_ERR("calloc failed\n");
		return -FCSERR_ENOMEM;
	}

	(*keystore_handle)->binding = (struct dev_binding) {};
	(*keystore_handle)->rot = NULL;
	(*keystore_handle)->sha256hash = NULL;
	(*keystore_handle)->ks = NULL;
	(*keystore_handle)->verified_with_hmac = 0;
	(*keystore_handle)->hmac_key = NULL;
	(*keystore_handle)->hmac_key_len = 0;
	(*keystore_handle)->ks_counter_updated = 0;
	(*keystore_handle)->ks_updated = 0;
	(*keystore_handle)->ks_xcs_updated = 0;
	(*keystore_handle)->ks_revert = 0;
	(*keystore_handle)->update_hmac_key = 0;

	/* Set the handles */
	nv_open(&hdl, KS_NV_ORG);
	(*keystore_handle)->nv_orgh = hdl;
	nv_open(&hdl, KS_NV_BAK);
	(*keystore_handle)->nv_bakh = hdl;
	rpmb_open(&hdl);
	(*keystore_handle)->rpmbh = hdl;

	/* Set the Device ID */
	(*keystore_handle)->binding.die_id = malloc(dev_id_sz);
	if ((*keystore_handle)->binding.die_id == NULL) {
		FCS_LOG_ERR("malloc failed %u\n", dev_id_sz);
		res = -FCSERR_ENOMEM;
		goto exit_invalid;
	}
	memcpy((*keystore_handle)->binding.die_id, dev_id, dev_id_sz);
	(*keystore_handle)->binding.die_id_sz = dev_id_sz;

	if (imei_sz == 0)
		goto set_rot;

	/* Set the IMEI */
	(*keystore_handle)->binding.imei = malloc(imei_sz);
	if ((*keystore_handle)->binding.imei == NULL) {
		FCS_LOG_ERR("malloc failed %u\n", imei_sz);
		res = -FCSERR_ENOMEM;
		goto exit_invalid;
	}
	memcpy((*keystore_handle)->binding.imei, imei, imei_sz);
	(*keystore_handle)->binding.imei_sz = imei_sz;

	if (hmac_key == NULL || hmac_key_len == 0)
		goto set_rot;

	/* Set the Device ID HMAC*/
	res = ks_hmac_sha256(hmac_key, hmac_key_len,
			(*keystore_handle)->binding.die_id,
			(*keystore_handle)->binding.die_id_sz,
			die_id_hmac);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("ks_hmac_sha256 failed\n");
		goto exit_invalid;
	}

	(*keystore_handle)->binding.die_id_hmac = malloc(SHA256_HASH_OUT_SIZE);
	if ((*keystore_handle)->binding.die_id_hmac == NULL) {
		FCS_LOG_ERR("malloc failed\n");
		res = -FCSERR_ENOMEM;
		goto exit_invalid;
	}

	memcpy((*keystore_handle)->binding.die_id_hmac, die_id_hmac,
			SHA256_HASH_OUT_SIZE);
	(*keystore_handle)->binding.die_id_hmac_sz = SHA256_HASH_OUT_SIZE;

	/* Set the IMEI HMAC*/
	res = ks_hmac_sha256(hmac_key, hmac_key_len,
			(*keystore_handle)->binding.imei,
			(*keystore_handle)->binding.imei_sz,
			imei_hmac_bin);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("ks_hmac_sha256 failed\n");
		goto exit_invalid;
	}
	(*keystore_handle)->binding.imei_hmac = malloc(SHA256_HASH_STRING_SIZE);
	if ((*keystore_handle)->binding.imei_hmac == NULL) {
		FCS_LOG_ERR("malloc failed\n");
		res = -FCSERR_ENOMEM;
		goto exit_invalid;
	}
	res = bin_to_ascii(
			(char *)(*keystore_handle)->binding.imei_hmac,
			SHA256_HASH_STRING_SIZE,
			imei_hmac_bin,
			sizeof(imei_hmac_bin));
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to convert imei hmac(%d)\n", res);
		goto exit_invalid;
	}
	(*keystore_handle)->binding.imei_hmac_sz = SHA256_HASH_STRING_SIZE - 1;

set_rot:
	/* Set the ROT */
	(*keystore_handle)->rot = malloc(rot_sz);
	if ((*keystore_handle)->rot == NULL) {
		FCS_LOG_ERR("malloc failed %u\n", rot_sz);
		res = -FCSERR_ENOMEM;
		goto exit_invalid;
	}
	memcpy((*keystore_handle)->rot, rot, rot_sz);
	(*keystore_handle)->rot_sz = rot_sz;

	/* Init memory for hash */
	(*keystore_handle)->sha256hash = malloc(SHA256_HASH_OUT_SIZE);
	if ((*keystore_handle)->sha256hash == NULL) {
		FCS_LOG_ERR("malloc failed\n");
		res = -FCSERR_ENOMEM;
		goto exit_invalid;
	}

	return FCSERR_OK;

exit_invalid:
	ks_destroy(*keystore_handle);
	*keystore_handle = NULL;
	return res;
}

void ks_destroy(struct ks_ctx * const context)
{
	if (context == NULL)
		return;

	if (context->ks != NULL) {
		ASN_STRUCT_FREE(asn_DEF_KeyStore, (void *) (context->ks));
		context->ks = NULL;
	}

	ks_io_delete(context->nv_orgh);
	ks_io_delete(context->nv_bakh);
	ks_io_delete(context->rpmbh);

	free(context->nv_orgh);
	free(context->nv_bakh);
	free(context->rpmbh);
	free(context->binding.die_id);
	free(context->binding.die_id_hmac);
	free(context->binding.imei);
	free(context->binding.imei_hmac);
	free(context->rot);
	free(context->sha256hash);
	free(context->hmac_key);
	free(context);
}

int ks_get_nof_keys(struct ks_ctx * const context,
			uint32_t domain,
			uint32_t *nof_keys)
{
	int i;
	KeyStoreEntry_t *ks_entry;

	if (!context || !nof_keys) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* Sanity check that keystore is initialized */
	if (!context->ks)
		return -FCSERR_EINVAL;

	*nof_keys = 0;
	/* Iterate over all entries */
	for (i = 0; i < context->ks->db.list.count; i++) {
		ks_entry = context->ks->db.list.array[i];
		/* Check if entry is in domain */
		if (ks_entry->domain == domain)
			(*nof_keys)++;
	}

	return FCSERR_OK;
}


static void copy_ks_entry(struct ksstore_blob *keyblob,
	KeyStoreEntry_t *ks_entry)
{
	keyblob->domain = ks_entry->domain;

	switch ( ks_entry->data.present ){
	case KeyStoreEntryData_PR_certificate:
		keyblob->type = KS_KEY_TYPE_CERT;
		keyblob->size = ks_entry->data.choice.certificate.size;
		keyblob->blob = ks_entry->data.choice.certificate.buf;
		break;
	case KeyStoreEntryData_PR_publickey:
		keyblob->type = KS_KEY_TYPE_PUB_KEY;
		keyblob->size = ks_entry->data.choice.publickey.size;
		keyblob->blob = ks_entry->data.choice.publickey.buf;
		break;
	default:
		break;
	}

}

int ks_get_key_by_index(struct ks_ctx * const context,
			const uint32_t domain,
			const uint32_t key_index,
			struct ksstore_blob *keyblob)
{
	int i;
	uint32_t nof_keys_domain, domain_index;
	KeyStoreEntry_t *ks_entry;
	int ret;

	if (!context) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* Check that <key_index> exists  in <domain> */
	ret = ks_get_nof_keys(context, domain, &nof_keys_domain);
	if (ret != FCSERR_OK)
		return ret;

	if (key_index > (nof_keys_domain - 1))
		return -FCSERR_EINVAL;

	domain_index = 0;
	/* Iterate over all entries */
	for (i = 0; i < context->ks->db.list.count; i++) {
		ks_entry = context->ks->db.list.array[i];
		/* Check if entry is in <domain> */
		if (ks_entry->domain == domain) {
			if (domain_index  == key_index) {
				/* Found the indexed entry */
				if (!keyblob)
					return -FCSERR_ENOMEM;
				/*  Entry/domain found Copy the data */
				copy_ks_entry(keyblob, ks_entry);
			}
			domain_index++;
		}
	}

	return FCSERR_OK;
}

int ks_get_counter(struct ks_ctx *ctx, uint32_t *counter)
{
	int ret;
	struct ks_rpmb_data rpmb_data;
	uint32_t rpmb_sz;

	if (ctx == NULL || counter == NULL) {
		FCS_LOG_ERR("Invalid input\n");
		return -FCSERR_EINVAL;
	}

	rpmb_sz = sizeof(struct ks_rpmb_data);
	ret = ks_io_read(ctx->rpmbh, (uint8_t *)&rpmb_data, &rpmb_sz);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Could not read rpmb\n");
		return ret;
	}

	*counter = rpmb_data.ks_counter;

	return FCSERR_OK;
}

int ks_get_is_xcs_rot(struct ks_ctx *ctx, uint32_t *is_xcs_rot)
{
	if (ctx == NULL || is_xcs_rot == NULL) {
		FCS_LOG_ERR("Invalid input\n");
		return -FCSERR_EINVAL;
	}

	*is_xcs_rot = 0;

	if (ks_is_loaded(ctx))
		*is_xcs_rot = ctx->ks->xcs;

	return FCSERR_OK;
}

int ks_get_sec_stor_xcs_rot(struct ks_ctx *ctx, uint32_t *is_xcs_set)
{
	int ret;
	struct ks_rpmb_data rpmb_data;
	uint32_t rpmb_sz;

	if (ctx == NULL || is_xcs_set == NULL) {
		FCS_LOG_ERR("Invalid input\n");
		return -FCSERR_EINVAL;
	}

	/* Read the RPMB data */
	rpmb_sz = sizeof(struct ks_rpmb_data);
	ret = ks_io_read(ctx->rpmbh, (uint8_t *)&rpmb_data, &rpmb_sz);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("rpmb read failed\n");
		return ret;
	}

	*is_xcs_set = rpmb_data.xcs_rot;

	return FCSERR_OK;
}

int plf_cms_cb(
	const uint8_t *const rot, const uint32_t rot_sz,
	const uint8_t *const msg, const uint32_t msg_sz,
	struct dev_binding *binding,
	uint32_t *verified_with_hmac, uint32_t *counter,
	uint8_t **payload, uint32_t *payload_len)
{
	int res;
	struct rule_verifier *rule;
	size_t len = 0;

	FCS_LOG_INF("plf_cms_cb called\n");

	res = rule_init(&rule, binding, RULE_USAGE_KEYSTORE);
	if (res) {
		FCS_LOG_ERR("rule_init failed (%d)\n", res);
		return res;
	}

	res = cms_verify(
		(uint8_t *)msg, msg_sz, rule, (uint8_t *)rot, rot_sz,
		NULL, 0, payload, &len);
	if (res) {
		FCS_LOG_ERR("cms_verify failed (%d)\n", res);
		goto exit;
	}
	*payload_len = len;
	res = rule_get_sequence(rule, counter);
	if (res) {
		FCS_LOG_ERR("rule_get_sequence failed (%d)\n", res);
		goto exit;
	}

	res = rule_verified_with_hmac(rule, verified_with_hmac);
	if (res)
		FCS_LOG_ERR("rule_verified_with_hmac failed (%d)\n",
				res);

exit:
	rule_deinit(rule);
	return res;
}
