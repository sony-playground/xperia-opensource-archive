/*
 * Copyright (c) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <string.h>
#include <xmodem.h>
#include "fcs_defines.h"
#include <fcslog.h>
#include <fcserr.h>
#include "core.h"
#include "ta_interface.h"
#include "eroot.h"
#include "ks.h"
#include "hwconf.h"
#include "simlock.h"

/**
 * Empty Keystore implementation
 *
 * Modem does not need to use KeyStore so a KeyStore implementation
 * reporting no keys (or any compilable function code) is enough.
 */
int ks_get_nof_keys(struct ks_ctx * const context,
			uint32_t domain,
			uint32_t *nof_keys)
{
	FCS_LOG_ERR("ks_get_nof_keys\n");
	if (nof_keys == NULL)
		return -FCSERR_EINVAL;

	*nof_keys = 0;
	return FCSERR_OK;
}

int ks_get_key_by_index(struct ks_ctx * const context,
			const uint32_t domain,
			const uint32_t key_index,
			struct ksstore_blob *keyblob)
{
	FCS_LOG_ERR("ks_get_key_by_index\n");
	return -FCSERR_EINVAL;
}


int xmodem_init(void)
{
	core_crypto_setup();
	return FCSERR_OK;
}

void xmodem_deinit(void)
{
	core_crypto_cleanup();
}

int xmodem_get_phoneid(unsigned int index, unsigned char *phone_data,
		unsigned int phone_data_len)
{
	uint8_t *die_id = NULL;
	uint32_t die_id_len;
	int ret = FCSERR_OK;
	struct embed_rootcert_item *eroot = NULL;
	hwconfig_t hwconf_hdl_p = NULL;
	size_t eroot_count = 0;
	size_t len;

	if (phone_data == NULL || index >= 2) {
		FCS_LOG_ERR("%s: Invalid param\n", __func__);
		return -FCSERR_EINVAL;
	}

	die_id_len = core_get_dieid_len();

	die_id = malloc(die_id_len);
	if (die_id == NULL) {
		FCS_LOG_ERR("malloc failed\n");
		return -FCSERR_ENOMEM;
	}

	ret = core_get_dieid(die_id, die_id_len);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get die id (%d)\n", ret);
		return ret;
	}

	ret = get_embedded_roots(&eroot, &eroot_count);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get embedded roots (%d)\n", ret);
		return ret;
	}

	ret = setup_hwconfig(die_id, die_id_len, eroot, eroot_count,
		&hwconf_hdl_p);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to setup hwconfig (%d)\n", ret);
		goto exit;
	}

	ret = get_imei(index, phone_data, phone_data_len, &len, hwconf_hdl_p);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get IMEI with index (%d)\n", index);
		goto exit;
	}

	if (phone_data_len != len) {
		FCS_LOG_ERR("%s: Unexpected phone_data_len\n", __func__);
		ret = -FCSERR_EINVAL;
		goto exit;
	}

	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get imei (%d)\n", ret);
		goto exit;
	}
exit:
	if (hwconf_hdl_p != NULL)
		teardown_hwconfig(hwconf_hdl_p);
	free_embedded_roots(&eroot);
	if (die_id != NULL)
		free(die_id);
	return ret;
}

int xmodem_verify_simlock(
		unsigned char *data,
		unsigned int data_length,
		unsigned char *signature,
		unsigned int signature_length,
		unsigned int opid,
		unsigned int *range_offset,
		unsigned int *range_length)
{
	int ret = FCSERR_OK;
	hwconfig_t hwconf_hdl_p = NULL;
	uint8_t *die_id;
	uint32_t die_id_len;
	uint8_t imei[MAX_PHONEID_SIZE] = {};
	size_t imei_len = 0;
	struct embed_rootcert_item *eroot = NULL;
	size_t eroot_count = 0;
	size_t range_size = 0;

	if (data == NULL ||
			data_length == 0 ||
			signature == NULL ||
			signature_length == 0 ||
			range_offset == NULL ||
			range_length == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	die_id_len = core_get_dieid_len();

	die_id = malloc(die_id_len);
	if (die_id == NULL) {
		FCS_LOG_ERR("malloc failed\n");
		return -FCSERR_ENOMEM;
	}

	ret = core_get_dieid(die_id, die_id_len);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get die id (%d)\n", ret);
		goto exit;
	}

	ret = get_embedded_roots(&eroot, &eroot_count);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get embedded roots (%d)\n", ret);
		goto exit;
	}

	ret = setup_hwconfig(die_id, die_id_len, eroot, eroot_count,
		&hwconf_hdl_p);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to setup hwconfig (%d)\n", ret);
		goto exit;
	}

	ret = get_imei(0, imei, sizeof(imei), &imei_len, hwconf_hdl_p);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get IMEI with index 0\n");
		goto exit;
	}

	ret = simlock_verify(
			imei, imei_len,
			eroot, eroot_count,
			data, data_length,
			signature, signature_length,
			opid,
			range_offset, &range_size);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify simlock: (%d)\n",
				ret);
	}
	*range_length = range_size;
exit:
	if (hwconf_hdl_p != NULL)
		teardown_hwconfig(hwconf_hdl_p);
	free_embedded_roots(&eroot);
	if (die_id != NULL)
		free(die_id);
	return ret;
}

