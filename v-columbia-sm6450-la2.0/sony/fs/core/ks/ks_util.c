/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <ks_util.h>
#include <kspk.h>
#include <eroot.h>
#include <ks.h>
#include <rule_rootcert.h>
#include <kstypes.h>
#include <fcslog.h>
#include <fcserr.h>
#include <core.h>
#include "hwconf.h"
#include "convert.h"
#include "fcs_defines.h"

int ksutil_keystore_load(struct ks_ctx *ks, uint8_t part)
{
	int res;

	if (ks == NULL) {
		FCS_LOG_ERR("Invalid keystore parameter!\n");
		return -FCSERR_EINVAL;
	}

	res = ks_load_keystore(ks, part);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to load keystore\n");
		return -FCSERR_ESTATE;
	}

	return FCSERR_OK;
}

int ksutil_keystore_init(struct ks_ctx **ks, bool load, uint8_t part,
		const uint8_t *hmac_key, uint32_t hmac_key_len)
{
	int res;
	struct embed_rootcert_item *eroot = NULL;
	size_t eroot_count;
	uint8_t *root_buf = NULL;
	size_t root_buf_len;
	uint8_t *die_id = NULL;
	uint32_t die_id_len;
	uint8_t imei[MAX_PHONEID_SIZE];
	size_t imei_len;
	uint8_t  imei_ascii[IMEI_ASCII_SIZE + 1] = {0};
	hwconfig_t hwconf_hdl = NULL;

	die_id_len = core_get_dieid_len();

	die_id = malloc(die_id_len);
	if (die_id == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	res = core_get_dieid(die_id, die_id_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("failed to get die id (%d)\n", res);
		goto err;
	}

	res = get_embedded_roots(&eroot, &eroot_count);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("failed to get embedded roots (%d)\n", res);
		goto err;
	}

	res = rule_get_roots(
		RULE_USAGE_KEYSTORE, eroot, eroot_count, NULL,
		&root_buf, &root_buf_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("failed to create keystore context\n");
		goto err;
	}

	res = setup_hwconfig(die_id, die_id_len, eroot, eroot_count,
		&hwconf_hdl);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("failed to setup hwconfig (%d)\n", res);
		goto ks_create_static;
	}

	/* First IMEI => Index 0 */
	res = get_imei(0, imei, sizeof(imei), &imei_len,
		hwconf_hdl);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("failed to get imei (%d)\n", res);
		goto ks_create_static;
	}

	res = bin_to_ascii((char *)imei_ascii, sizeof(imei_ascii),
			imei, imei_len - 1);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to convert imei (%d)\n", res);
		goto ks_create_static;
	}

ks_create_static:
	res = ks_create_static(
		ks, die_id, die_id_len,
		imei_ascii, sizeof(imei_ascii) - 1,
		root_buf, root_buf_len,
		hmac_key, hmac_key_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to create keystore context\n");
		goto err;
	}

	if (load) {
		res = ks_load_keystore(*ks, part);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to load keystore\n");
			goto err;
		}
	}

	teardown_hwconfig(hwconf_hdl);
	free_embedded_roots(&eroot);
	free(root_buf); /* the caller is responsible to free */
	free(die_id);
	return FCSERR_OK;

err:
	teardown_hwconfig(hwconf_hdl);
	free_embedded_roots(&eroot);
	free(root_buf); /* the caller is responsible to free */
	free(die_id);
	ks_destroy(*ks);
	*ks = NULL;
	return res;
}
