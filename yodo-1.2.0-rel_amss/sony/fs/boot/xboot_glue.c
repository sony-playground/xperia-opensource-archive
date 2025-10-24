/*
 * Copyright 2016,2021,2022 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

#include <string.h>
#include <xboot_glue.h>
#include <kstypes.h>
#include <fcslog.h>
#include <fcserr.h>
#include <rooting_status.h>
#include <ks_util.h>
#include "fcs_endian.h"
#include "ta_interface.h"
#include "rule_types.h"
#include "eroot.h"
#include "hwconf.h"
#include "ks.h"
#include "fcs_defines.h"
#include "convert.h"
#include "oemunlock_flag.h"
#include "xboot_pal_include.h"
#include "xboot_pal_types.h"
#include "sony_boot_context.h"
#include "sony_boot_lib_api.h"
#include "xboot_auth_cmd.h"
#include "xboot_pal_types.h"
/* Internal integration header files */
#include <fcsenv_def.h>
#include "xflattest.h"
#include "xflattest_int.h"
#include "core.h"
#include <rng.h>

static unsigned char imei_buffer[MAX_PHONEID_SIZE];
static unsigned char imei2_buffer[MAX_PHONEID_SIZE];

static int get_e_signer_count(unsigned int usage, unsigned int *count);
static int get_e_signer(unsigned int usage, unsigned int index,
		const unsigned char **cert, unsigned int *len);
static int get_domain(unsigned int usage, unsigned int *domain);
static int get_ks_signer_count(struct ks_ctx *ks,
		unsigned int usage, unsigned int *count);
static int get_ks_signer(struct ks_ctx *ks,
		unsigned int usage, unsigned int index,
		const unsigned char **cert, unsigned int *len);
static int get_ks_pub_key(struct ks_ctx *ks,
		unsigned int usage, unsigned int index,
		const unsigned char **pub_key, unsigned int *len);
static int keystore_init(struct ks_ctx **ks);
static int keystore_load(struct ks_ctx *ks);


static int get_dk(unsigned char **device_key, unsigned int *device_key_len,
	hwconfig_t handle)
{
	int ret = FCSERR_OK;
	int i;
	uint8_t *hwc_dk = NULL;
	size_t hwc_dk_len;
	uint8_t *ta_dk_buf = NULL;
	int ta_dk_unit_size;

	if (!device_key || !device_key_len) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ret = get_hwconf_dk(&hwc_dk, &hwc_dk_len, handle);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_hwconf_dk returned err=%d\n", ret);
		goto exit_get_dk;
	}

	ret = get_ta_unit_size(TA_MISC_PART, TA_DK_NUMBER_UNIT,
		&ta_dk_unit_size);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_ta_unit_size returned err=%d\n", ret);
		goto exit_get_dk;
	}

	if (ta_dk_unit_size == 0) {
		FCS_LOG_ERR("Device Key MiscTA unit size is zero\n");
		ret = -FCSERR_ESIZE;
		goto exit_get_dk;
	}

	ta_dk_buf = (uint8_t *)malloc(ta_dk_unit_size);
	if (ta_dk_buf == NULL) {
		FCS_LOG_ERR("Failed to allocate memory for Device Key\n");
		ret = -FCSERR_ENOMEM;
		goto exit_get_dk;
	}


	ret = read_ta(TA_MISC_PART, TA_DK_NUMBER_UNIT, ta_dk_buf,
		ta_dk_unit_size);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("read_ta returned err=%d\n", ret);
		goto exit_get_dk;
	}

	*device_key_len = hwc_dk_len;
	if (ta_dk_unit_size != hwc_dk_len) {
		FCS_LOG_ERR("Device keys not of equal length!\n");
		ret = -FCSERR_EINVAL;
		goto exit_get_dk;
	}

	*device_key = (unsigned char *)malloc(*device_key_len);
	if (*device_key == NULL) {
		FCS_LOG_ERR("Failed to allocate memory for Device Key\n");
		ret = -FCSERR_ENOMEM;
		goto exit_get_dk;
	}

	for (i = 0; i < *device_key_len; i++)
		(*device_key)[i] = hwc_dk[i] ^ ta_dk_buf[i];

exit_get_dk:
	free(hwc_dk);
	free(ta_dk_buf);
	return ret;
}

static int read_hmac_key(uint32_t ta_unit, uint8_t **hmac_key, int hmac_key_len)
{
	int res;

	if (hmac_key == NULL || hmac_key_len == 0) {
		FCS_LOG_ERR("Invalid parameter\n");
		return -FCSERR_EINVAL;
	}

	if (*hmac_key != NULL)
		free(*hmac_key);

	*hmac_key = malloc(hmac_key_len);
	if (*hmac_key == NULL) {
		FCS_LOG_ERR("Failed to allocate memory\n");
		return -FCSERR_ENOMEM;
	}

	res = read_ta(TA_MISC_PART,
			ta_unit,
			*hmac_key,
			hmac_key_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("read_ta returned err=%d\n", res);
		return res;
	}

	return res;
}

static int keystore_init(struct ks_ctx **ks)
{
	int res;
	uint8_t *hmac_key = NULL;
	uint8_t *hmac_key_tmp = NULL;
	int hmac_key_len = 0;
	int hmac_key_len_low_ta = 0;
	int hmac_key_len_high_ta = 0;
	struct ks_ctx *keystore_ctx = NULL;
	struct xfl_sec_data xfl_sec_data;
	bool update_hmac_key = false;
	bool identical_hmac_keys_len = false;

	if (ks == NULL) {
		FCS_LOG_ERR("Invalid parameter\n");
		return -FCSERR_EINVAL;
	}

	res = get_ta_unit_size(TA_MISC_PART,
			TA_KEYSTORE_HMAC_KEY,
			&hmac_key_len_low_ta);

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("get_ta_unit_size returned err=%d\n", res);
		goto exit;
	}

	res = get_ta_unit_size(TA_MISC_PART,
			TA_KEYSTORE_HMAC_KEY_APPLY,
			&hmac_key_len_high_ta);

	if (res != FCSERR_OK) {
		FCS_LOG_ERR("get_ta_unit_size returned err=%d\n", res);
		goto exit;
	}

	if ((hmac_key_len_low_ta > 0) &&
			(hmac_key_len_high_ta == hmac_key_len_low_ta))
		identical_hmac_keys_len = true;

	res = read_xfl_sec_data(&xfl_sec_data);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read xfl_sec_data (%d)\n", res);
		goto exit;
	}

	/*
	 * If XCS keystore has never been applied, and there's data
	 * in MiscTA 2164, try to verify the keystore against the HMAC key
	 * in MiscTA 2164.
	 */
	if (!xfl_sec_data.xcs_rot && hmac_key_len_low_ta > 0) {
		int verified_with_hmac = 0;

		hmac_key_len = hmac_key_len_low_ta;
		res = read_hmac_key(TA_KEYSTORE_HMAC_KEY,
				&hmac_key, hmac_key_len);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to read HMAC key\n", res);
			goto exit;
		}

		/*
		 * If MiscTA units 2164 and 66673 are of the same size,
		 * read the 66673 unit as well, so they can be compared
		 * later on.
		 */
		if (identical_hmac_keys_len) {
			res = read_hmac_key(TA_KEYSTORE_HMAC_KEY_APPLY,
					&hmac_key_tmp, hmac_key_len);
			if (res != FCSERR_OK) {
				FCS_LOG_ERR("Failed to read HMAC key\n", res);
				goto exit;
			}
		}

		res = ksutil_keystore_init(&keystore_ctx, true,
				XFLKEYSTORE_PRIM, hmac_key,
				hmac_key_len);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Init ks: err=%d\n", res);
			free(hmac_key);
			hmac_key = NULL;
			hmac_key_len = 0;
			goto check_high_ta;
		}

		res = ks_verified_with_hmac(keystore_ctx, &verified_with_hmac);
		if (res != FCSERR_OK)
			goto exit;

		if (verified_with_hmac) {
			/*
			 * The update_hmac_key flag is set if the data
			 * in MiscTA 2164 is not identical to the data
			 * in MiscTA 66673, and the keystore was
			 * successfully verified using the HMAC key in
			 * MiscTA 2164.
			 */
			if (!identical_hmac_keys_len)
				update_hmac_key = true;
			else if (memcmp(hmac_key, hmac_key_tmp, hmac_key_len))
				update_hmac_key = true;

			/* If the keystore was successfully verified
			 * using the HMAC key in MiscTA 2164, skip
			 * to the keystore_init call for the main
			 * keystore context.
			 */
			goto keystore_init;
		}
	}

check_high_ta:
	/*
	 * If the keystore was not verified using the HMAC key in MiscTA
	 * 2164, check whether there's an HMAC key in MiscTA 66673.
	 */
	if (hmac_key_len_high_ta > 0) {
		hmac_key_len = hmac_key_len_high_ta;
		res = read_hmac_key(TA_KEYSTORE_HMAC_KEY_APPLY,
				&hmac_key, hmac_key_len);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to read HMAC key\n", res);
			goto exit;
		}
	}

keystore_init:
	res = ksutil_keystore_init(ks, false, XFLKEYSTORE_PRIM,
			hmac_key, hmac_key_len);
	if (res != FCSERR_OK)
		goto exit;

	if (update_hmac_key) {
		res = ks_set_update_hmac_key(*ks);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("ks_set_update_hmac_key failed\n");
			goto exit;
		}

		res = ks_set_hmac_key(*ks, hmac_key, hmac_key_len);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("ks_set_hmac_key failed\n");
			goto exit;
		}
	}

exit:
	/* Delete the key in low TA. */
	if (hmac_key_len_low_ta > 0) {
		if (delete_ta(TA_MISC_PART, TA_KEYSTORE_HMAC_KEY))
			FCS_LOG_WRN("delete_ta returned err=%d\n", res);
	}

	ks_destroy(keystore_ctx);
	free(hmac_key);
	free(hmac_key_tmp);
	return res;
}

static int keystore_load(struct ks_ctx *ks)
{
	int res;
	uint32_t xcs_updated;

	if (ks == NULL) {
		FCS_LOG_ERR("Invalid keystore parameter!\n");
		return -FCSERR_EINVAL;
	}

	res = ksutil_keystore_load(ks, XFLKEYSTORE_PRIM);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to load keystore\n");
		goto exit;
	}

	res = ks_get_xcs_updated(ks, &xcs_updated);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get xcs_updated flag\n");
		goto exit;
	}

	/*
	 * If the device is NOT about to apply a NEW XCS keystore, jump to
	 * set_keystore.
	 */
	if (!xcs_updated)
		goto set_keystore;

	/*
	 * If we reach this point, it means that the keystore in the primary
	 * partition is new and valid, and that it contains an xcs rot.
	 * Lock the bootloader which will reset the device.
	 * If the operation is not successful, return error.
	 */
	if (xboot_lock_bootloader() != FCSERR_OK) {
		FCS_LOG_ERR("Failed to lock bootloader\n");
		goto exit;
	}

set_keystore:
	res = ks_set_keystore(ks);

exit:
	return res;
}

static void xboot_deinit(struct xboot_ctx *ctx)
{
	if (ctx != NULL) {
		ks_destroy(ctx->ks);
		free(ctx->device_key);
		free(ctx->version_string);
		free(ctx->bootconfig);
		free(ctx->timer_context);
		free(ctx->sony_cmdline_additions);
		free(ctx);
	}
}

int xboot_init(struct xboot_ctx **ctx)
{
	int ret = FCSERR_OK;
	uint8_t *die_id;
	uint32_t die_id_len;
	struct embed_rootcert_item *eroot = NULL;
	size_t eroot_count = 0;
	hwconfig_t handle = NULL;
	size_t id_length;
	uint8_t phoneid_count = 0;

	if (ctx == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	(*ctx) = malloc(sizeof(struct xboot_ctx));
	if ((*ctx) == NULL) {
		FCS_LOG_ERR("failed to allocate context (%d)\n", ret);
		return -FCSERR_ENOMEM;
	}
	memset((*ctx), 0, sizeof(struct xboot_ctx));

	ret = sony_boot_init((*ctx));
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("sony_boot_init returned %d\n", ret);
		return ret;
	}
	(*ctx)->boot_mode = XBOOT_BOOT_INVALID_MODE;
	(*ctx)->sony_cmdline_additions = "";

	core_crypto_setup();

	ret = xboot_get_die_id(&die_id, &die_id_len);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get die id (%d)\n", ret);
		xboot_deinit((*ctx));
		return ret;
	}

	ret = get_embedded_roots(&eroot, &eroot_count);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get embedded roots (%d)\n", ret);
		xboot_deinit((*ctx));
		return ret;
	}

	ret = setup_hwconfig(die_id, die_id_len, eroot, eroot_count,
		&handle);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to setup hwconfig (%d)\n", ret);
		/* If hwconfig setup fails, force boot into SW Service */
		(*ctx)->curr_service_mode = SERVICE_MODE_DETECT_USB_SONY;
		goto xboot_init_keystore;
	}

	ret = get_imei_count(&phoneid_count, handle);
	if (ret != FCSERR_OK || phoneid_count > MAX_PHONEID_COUNT) {
		FCS_LOG_ERR("failed to get imei count (%d)\n", ret);
		(*ctx)->curr_service_mode = SERVICE_MODE_DETECT_USB_SONY;
		goto xboot_init_keystore;
	}
	(*ctx)->imei_count = phoneid_count;

	/* First IMEI => Index 0 */
	ret = get_imei(0, imei_buffer, sizeof(imei_buffer), &id_length,
		handle);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get imei (%d)\n", ret);
		(*ctx)->curr_service_mode = SERVICE_MODE_DETECT_USB_SONY;
		ret = FCSERR_OK;
		goto exit;
	}
	(*ctx)->imei = imei_buffer;
	(*ctx)->imei_len = id_length;

	if ((*ctx)->imei_count > 1) {
		/* Second IMEI => Index 1 */
		ret = get_imei(1, imei2_buffer, sizeof(imei2_buffer),
				&id_length, handle);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("failed to get imei (%d)\n", ret);
			(*ctx)->curr_service_mode =
				SERVICE_MODE_DETECT_USB_SONY;
			ret = FCSERR_OK;
			goto exit;
		}
		(*ctx)->imei2 = imei2_buffer;
		(*ctx)->imei2_len = id_length;
	} else {
		(*ctx)->imei2 = NULL;
		(*ctx)->imei2_len = 0;
	}

	ret = get_dk(&((*ctx)->device_key),
			&((*ctx)->device_key_len),
			handle);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_dk returned err=%d\n", ret);
		(*ctx)->device_key = NULL;
		(*ctx)->device_key_len = 0;
	}

	ret = get_is_prototype(&(*ctx)->is_prototype, handle);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_is_prototype returned err=%d\n", ret);
		(*ctx)->is_prototype = false;
	}

xboot_init_keystore:
	ret = keystore_init(&((*ctx)->ks));
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR(
			"keystore_init returned err=%d; forcing SW service\n",
			ret);
		/* If keystore_init failed force boot into SW Service */
		(*ctx)->curr_service_mode = SERVICE_MODE_DETECT_USB_SONY;
		ret = FCSERR_OK;
		goto exit;
	}

	/* Load Keystore */
	if (keystore_load((*ctx)->ks) != FCSERR_OK) {
		FCS_LOG_ERR("keystore_load failed, forcing SW service\n");
		/* If loading of keystore failed force boot into SW Service */
		(*ctx)->curr_service_mode = SERVICE_MODE_DETECT_USB_SONY;
	}

exit:
	(void)teardown_hwconfig(handle);
	free_embedded_roots(&eroot);
	return ret;
}

int xboot_get_ks_counter(struct xboot_ctx *ctx, uint32_t *counter)
{
	if (ctx == NULL || counter == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}
	if (ctx->ks == NULL) {
		FCS_LOG_ERR("Keystore not initiated\n");
		return -FCSERR_ENOTF;
	}
	return ks_get_counter(ctx->ks, counter);
}

int xboot_get_ks_is_xcs_rot(struct xboot_ctx *ctx, uint32_t *is_xcs_rot)
{
	if (ctx == NULL || is_xcs_rot == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}
	if (ctx->ks == NULL) {
		FCS_LOG_ERR("Keystore not initiated\n");
		return -FCSERR_ENOTF;
	}
	return ks_get_is_xcs_rot(ctx->ks, is_xcs_rot);
}

int xboot_get_sec_stor_xcs_rot(struct xboot_ctx *ctx, uint32_t *is_xcs_set)
{
	if (ctx == NULL || is_xcs_set == NULL) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	return ks_get_sec_stor_xcs_rot(ctx->ks, is_xcs_set);
}

int xboot_get_die_id(unsigned char **id, unsigned int *len)
{
	int res = FCSERR_OK;
	static uint8_t buf[DIE_ID_LEN];

	if (!id || !len) {
		FCS_LOG_ERR("Invalid param\n");
		return -FCSERR_EINVAL;
	}

	res = core_get_dieid(buf, DIE_ID_LEN);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get die_id\n");
		return res;
	}

	*id = buf;
	*len = DIE_ID_LEN;

	return FCSERR_OK;
}

int xboot_get_simlock_unlock_data(unsigned char *unlock_status,
				unsigned char *rck_h)
{
	int ret;

	ret = get_simlock_unlock_data(unlock_status, rck_h);
	if (ret)
		FCS_LOG_ERR("Failed to get unlock data: (%d)\n", ret);

	return ret;
}

int xboot_compare_rck(unsigned char *rck_h_sl,
			const unsigned char *rck_fb,
			unsigned int rck_fb_len)
{
	return verify_rck(rck_h_sl, rck_fb, rck_fb_len);
}

int xboot_google_allow_unlock(unsigned char *allow_unlock)
{
	return google_allow_unlock(allow_unlock);
}

int xboot_delete_dk(void)
{
	return delete_dk();
}

int xboot_get_pub_key_count(struct xboot_ctx *ctx,
		unsigned int usage, unsigned int *count)
{
	int ret = FCSERR_OK;
	struct ks_ctx *ks = NULL;

	if (!ctx || !count) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ks = ctx->ks;

	if (usage != RULE_USAGE_VBMETA) {
		FCS_LOG_ERR("unsupported usage (%u)\n", usage);
		return -FCSERR_EINVAL;
	}

	ret = get_ks_signer_count(ks, usage, count);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_ks_signer_count failed (%d)\n", ret);
		return -FCSERR_ESTATE;
	}

	return FCSERR_OK;
}

int xboot_get_signer_cert_count(struct xboot_ctx *ctx,
		unsigned int usage, unsigned int *count)
{
	int ret = FCSERR_OK;
	unsigned int ks_count = 0;
	unsigned int e_count = 0;
	struct ks_ctx *ks = NULL;

	if (usage == 0 || !count) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* If no boot context present there is no keystore context =>
	 * use embedded root certs
	 */
	if (ctx != NULL)
		ks = ctx->ks;

	/* If kernel verify usage :
	 * - RULE_USAGE_LOADER_KERNEL, fetch from both keystore and embedded
	 *	- OTHERS, fetch only from keystore
	 */
	if (usage == RULE_USAGE_LOADER_KERNEL ||
			usage == RULE_USAGE_NORMAL_KERNEL ||
			usage == RULE_USAGE_FOTA_KERNEL ||
			usage == RULE_USAGE_RAMDUMP_KERNEL) {
		ret = get_ks_signer_count(ks, usage, &ks_count);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR(
				"failed to get ks_signer for loader (%d)\n",
				ret);
			return ret;
		}
		if (usage == RULE_USAGE_LOADER_KERNEL) {
			ret = get_e_signer_count(usage, &e_count);
			if (ret != FCSERR_OK) {
				FCS_LOG_ERR(
				"failed to get e_signer for loader (%d)\n",
				ret);
				return ret;
			}
		}
		*count = ks_count + e_count;
	} else {
		FCS_LOG_ERR(
			"unsupported usage (%u)\n",
			usage);
		return -FCSERR_EINVAL;
	}

	return FCSERR_OK;
}

int xboot_get_pub_key(struct xboot_ctx *ctx,
		unsigned int usage, unsigned int index,
		const unsigned char **pub_key,
		unsigned int *len)
{
	int ret = FCSERR_OK;
	unsigned int ks_count = 0;
	struct ks_ctx *ks = NULL;

	if (!ctx || !pub_key || !len) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ks = ctx->ks;

	if (usage != RULE_USAGE_VBMETA) {
		FCS_LOG_ERR("unsupported usage (%u)\n", usage);
		return -FCSERR_EINVAL;
	}

	ret = xboot_get_pub_key_count(ctx, usage, &ks_count);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("xboot_get_pub_key_count failed (%d)",
				ret);
		return ret;
	}

	if (index >= ks_count) {
		FCS_LOG_ERR("index out of range\n");
		return -FCSERR_EINVAL;
	}

	ret = get_ks_pub_key(ks, usage, index,
			pub_key, len);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_ks_pub_key failed (%d)\n", ret);
		return ret;
	}

	return FCSERR_OK;
}

int xboot_get_signer_cert(struct xboot_ctx *ctx,
		unsigned int usage, unsigned int index,
		const unsigned char **cert, unsigned int *len)
{
	int ret = FCSERR_OK;
	unsigned int ks_count = 0;
	unsigned int e_count = 0;
	struct ks_ctx *ks = NULL;

	if (usage == 0 || !cert || !len) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* If no boot context present there is no keystore context =>
	 * use embedded root certs
	 */
	if (ctx != NULL)
		ks = ctx->ks;

	/* If kernel verify usage :
	 * - RULE_USAGE_LOADER_KERNEL, fetch from both keystore and embedded
	 *- OTHERS, fetch only from keystore
	 */
	if (usage == RULE_USAGE_LOADER_KERNEL ||
			usage == RULE_USAGE_NORMAL_KERNEL ||
			usage == RULE_USAGE_FOTA_KERNEL ||
			usage == RULE_USAGE_RAMDUMP_KERNEL) {
		ret = get_ks_signer_count(
			ks, usage, &ks_count);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR(
				"get_ks_signer_count failed (%d)\n",
				ret);
			return ret;
		}
		if (usage == RULE_USAGE_LOADER_KERNEL) {
			ret = get_e_signer_count(
				usage, &e_count);
			if (ret != FCSERR_OK) {
				FCS_LOG_ERR(
				"get_e_signer_count failed (%d)\n",
				ret);
				return ret;
			}
		}
		if (index < ks_count) {
			ret = get_ks_signer(ks,
					usage, index,
					cert, len);
			if (ret != FCSERR_OK) {
				FCS_LOG_ERR(
				"get_ks_signer failed (%d)\n",
				ret);
				return ret;
			}
		} else if ((index - ks_count) < e_count) {
			ret = get_e_signer(usage, index - ks_count,
					cert, len);
			if (ret != FCSERR_OK) {
				FCS_LOG_ERR(
				"get_e_signer failed (%d)\n",
				ret);
				return ret;
			}
		} else {
			FCS_LOG_ERR(
				"index out of range\n",
				usage);
			return -FCSERR_EINVAL;
		}
	} else {
		FCS_LOG_ERR(
			"unsupported usage (%u)\n",
			usage);
		return -FCSERR_EINVAL;
	}

	return FCSERR_OK;
}

/* Internal functions */

static int get_e_signer_count(unsigned int usage, unsigned int *count)
{
	int ret;
	struct embed_rootcert_item *eroot = NULL;
	size_t eroot_count;
	unsigned int i;

	if (!count) {
		FCS_LOG_ERR("Invalid argument\n");
		ret = -FCSERR_EINVAL;
		goto get_e_signer_count_end;
	}
	ret = get_embedded_roots(&eroot, &eroot_count);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get embedded roots (%d)\n", ret);
		goto get_e_signer_count_end;
	}

	*count = 0;
	for (i = 0; i < eroot_count; i++)
		if ((eroot[i].usage_flags & usage) == usage)
			(*count)++;

	ret = FCSERR_OK;

get_e_signer_count_end:
	free_embedded_roots(&eroot);
	return ret;
}

static int get_e_signer(unsigned int usage, unsigned int index,
		const unsigned char **cert, unsigned int *len)
{
	int ret;
	struct embed_rootcert_item *eroot = NULL;
	size_t eroot_count;
	unsigned int count;
	unsigned int i;

	if (!cert || !len) {
		FCS_LOG_ERR("Invalid argument\n");
		ret = -FCSERR_EINVAL;
		goto get_e_signer_end;
	}

	ret = get_embedded_roots(&eroot, &eroot_count);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get embedded roots (%d)\n", ret);
		goto get_e_signer_end;
	}

	count = 0;
	for (i = 0; i < eroot_count; i++)
		if ((eroot[i].usage_flags & usage) == usage) {
			if (index == count) {
				*cert = eroot[i].rootcerts;
				*len = eroot[i].rootcerts_length;
				ret = FCSERR_OK;
				goto get_e_signer_end;
			}
			count++;
		}

	FCS_LOG_ERR("index out of range\n");
	ret = -FCSERR_EINVAL;

get_e_signer_end:
	free_embedded_roots(&eroot);
	return ret;
}

static int get_domain(unsigned int usage, unsigned int *domain)
{
	if (!domain) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (usage == RULE_USAGE_LOADER_KERNEL)
		*domain = KEYSTORE_DOMAIN_XFL;
	else if (usage == RULE_USAGE_NORMAL_KERNEL ||
			usage == RULE_USAGE_FOTA_KERNEL ||
			usage == RULE_USAGE_RAMDUMP_KERNEL)
		*domain = KEYSTORE_DOMAIN_KERNEL;
	else if (usage == RULE_USAGE_VBMETA)
		*domain = KEYSTORE_DOMAIN_VBMETA;
	else {
		*domain = 0;
		FCS_LOG_ERR("Invalid usage\n");
		return -FCSERR_EINVAL;
	}

	return FCSERR_OK;
}

static int get_ks_signer_count(struct ks_ctx *ks,
		unsigned int usage, unsigned int *count)
{
	int ret;
	unsigned int domain;
	uint32_t nof_keys;

	if (!count) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ret = get_domain(usage, &domain);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_domain failed (%d)\n", ret);
		return ret;
	}

	*count = 0;

	if (!ks_is_loaded(ks))
		return FCSERR_OK;

	ret = ks_get_nof_keys(ks, domain, &nof_keys);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("ks_get_nof_keys failed (%d)\n", ret);
		return ret;
	}

	*count = nof_keys;

	return FCSERR_OK;
}

static int get_ks_pub_key(struct ks_ctx *ks,
		unsigned int usage, unsigned int index,
		const unsigned char **pub_key, unsigned int *len)
{
	int ret;
	unsigned int domain;
	uint32_t nof_keys;
	struct ksstore_blob keyblob;

	if (!ks || !pub_key || !len) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ret = get_domain(usage, &domain);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_domain failed (%d)\n", ret);
		return ret;
	}

	ret = ks_get_nof_keys(ks, domain, &nof_keys);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("ks_get_nof_keys failed (%d)\n", ret);
		return -FCSERR_ESTATE;
	}

	if (index >= nof_keys) {
		FCS_LOG_ERR("Index out of range\n");
		return -FCSERR_EINVAL;
	}

	ret = ks_get_key_by_index(ks,
			domain,
			index,
			&keyblob);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("ks_get_key_by_index failed (%d)\n", ret);
		return ret;
	}

	if (keyblob.type != KS_KEY_TYPE_PUB_KEY) {
		FCS_LOG_ERR("Not a public key type (%u)\n", keyblob.type);
		return -FCSERR_ESTATE;
	}
	*len = keyblob.size;
	*pub_key = keyblob.blob;

	return FCSERR_OK;
}

static int get_ks_signer(struct ks_ctx *ks,
		unsigned int usage, unsigned int index,
		const unsigned char **cert, unsigned int *len)
{
	int ret;
	unsigned int domain;
	uint32_t nof_keys;
	struct ksstore_blob keyblob;

	if (!ks || !cert || !len) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	ret = get_domain(usage, &domain);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_domain failed (%d)\n", ret);
		return ret;
	}

	ret = ks_get_nof_keys(ks, domain, &nof_keys);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("ks_get_nof_keys failed (%d)\n", ret);
		return ret;
	}

	if (index >= nof_keys) {
		FCS_LOG_ERR("Index out of range\n");
		return -FCSERR_EINVAL;
	}

	ret = ks_get_key_by_index(ks,
			domain,
			index,
			&keyblob);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("ks_get_key_by_index failed (%d)\n", ret);
		return ret;
	}

	if (keyblob.type != KS_KEY_TYPE_CERT) {
		FCS_LOG_ERR("Not a certificate type (%u)\n", keyblob.type);
		return -FCSERR_ESTATE;
	}
	*len = keyblob.size;
	*cert = keyblob.blob;

	return FCSERR_OK;
}

int xboot_check_auto_set_oem_unlock(struct xboot_ctx *ctx)
{
	int ret;
	uint8_t *unit_buf = NULL;
	int unit_size = 0;
	struct embed_rootcert_item *eroot = NULL;
	size_t eroot_count;
	uint8_t *frp_data = NULL;
	uint32_t frp_data_size;
	uint8_t imei_ascii[IMEI_ASCII_SIZE + 1] = {0};

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		ret = -FCSERR_EINVAL;
		goto end_function;
	} else if (!ctx->imei || ctx->imei_len == 0) {
		FCS_LOG_INF("IMEI missing, skip check\n");
		ret = FCSERR_OK;
		goto end_function;
	}

	ret = get_ta_unit_size(TA_MISC_PART, TA_RL_DATA_LOW_UNIT,
		&unit_size);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("get_ta_unit_size returned err=%d\n", ret);
		goto end_function;
	}

	/* If unit_size <= 0 there is no request to handle =>
	 * End with OK.
	 */
	if (unit_size <= 0) {
		ret = FCSERR_OK;
		goto end_function;
	}

	unit_buf = malloc(unit_size);
	if (unit_buf == NULL) {
		FCS_LOG_ERR("Failed to allocate memory\n");
		ret = -FCSERR_ENOMEM;
		goto end_function;
	}

	ret = read_ta(TA_MISC_PART, TA_RL_DATA_LOW_UNIT, unit_buf,
		unit_size);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("read_ta returned err=%d\n", ret);
		goto end_function;
	}

	ret = get_embedded_roots(&eroot, &eroot_count);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get embedded roots (%d)\n", ret);
		goto end_function;
	}

	FCS_LOG("trying to verify set OEM unlock flag request\n");

	ret = xbpal_get_frp_data_size(&frp_data_size);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR(
			"Failed to read frp data size err=%d\n", ret);
		goto end_function;
	}

	frp_data = malloc(frp_data_size);
	if (frp_data == NULL) {
		FCS_LOG_ERR("Failed to allocate memory\n");
		ret = -FCSERR_ENOMEM;
		goto end_function;
	}

	ret = xbpal_read_frp_data(frp_data, frp_data_size);

	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("xbpal_read_frp returned err=%d\n", ret);
		goto end_function;
	}

	ret = bin_to_ascii((char *)imei_ascii, sizeof(imei_ascii),
		ctx->imei, ctx->imei_len - 1);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to convert imei (%d)\n", ret);
		goto end_function;
	}

	ret = oemunlock_flag_verify(ctx->ks,
			imei_ascii, IMEI_ASCII_SIZE,
			eroot, eroot_count,
			unit_buf, unit_size,
			frp_data, frp_data_size);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR(
			"Failed to verify set OEM unlock flag request err=(%d)\n",
			ret);
		goto end_function;
	}
	ret = delete_ta(TA_MISC_PART, TA_GOOGLE_LOCK_STATE);
	if (ret != FCSERR_OK)
		FCS_LOG_ERR("delete_ta failed, returned err=%d\n", ret);

end_function:
	free(unit_buf);
	/* Remove request if present */
	if (unit_size > 0)
		delete_ta(TA_MISC_PART, TA_RL_DATA_LOW_UNIT);
	free_embedded_roots(&eroot);
	free(frp_data);
	return ret;
}

int xboot_check_auth_cmd(struct xboot_ctx *ctx)
{
	int ret;

	ret = xboot_auth_cmd(ctx);
	/* this is not a hard error. Lets try and boot anyway */
	if (ret != FCSERR_OK)
		FCS_LOG_INF("sony_boot_check_auth_cmd failed, err=%d\n", ret);

	return FCSERR_OK;

}

int xboot_gen_auth_ch_nonce(struct xboot_ctx *ctx)
{
	int ret = FCSERR_OK;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	if (ctx->boot_mode == XBOOT_BOOT_SONY_SERVICE_MODE) {
		/* we should not boot further if nonce generation fails */
		ret = xboot_gen_nonce();
		if (ret != FCSERR_OK)
			FCS_LOG_ERR("nonce generation failed, err=%d\n", ret);
	}

	return ret;
}

int xboot_get_auth_ch_nonce(uint8_t *nonce)
{
	int res;
	struct xfl_sec_data data;
	bool is_fused;

	if (!nonce) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = core_is_fused(&is_fused);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Get fused info failed (%d)\n", res);
		return res;
	}

	res = read_xfl_sec_data(&data);
	if (res != FCSERR_OK) {
		if (!is_fused) {
			/* If the device is not fused, xfl_sec_data is read
			 * from MiscTA. Invalid MiscTA should not cause
			 * this function to fail. Generate nonce and return.
			 */
			fcs_urand(nonce, sizeof(data.sake_nonce));
			return FCSERR_OK;
		}
		FCS_LOG_ERR("Failed to read xfl_sec_data (%d)\n", res);
		return res;
	}

	memcpy(nonce, data.sake_nonce, sizeof(data.sake_nonce));

	return FCSERR_OK;
}

unsigned char *xboot_get_phoneid(struct xboot_ctx *ctx, unsigned int *len)
{
	if (!ctx || !len) {
		FCS_LOG_ERR("Invalid argument\n");
		return NULL;
	}
	*len = ctx->imei_len;
	return ctx->imei;
}

unsigned char *xboot_get_second_phoneid(struct xboot_ctx *ctx,
		unsigned int *len)
{
	if (!ctx || !len) {
		FCS_LOG_ERR("Invalid argument\n");
		return NULL;
	}
	*len = ctx->imei2_len;
	return ctx->imei2;
}

uint8_t xboot_get_phoneid_count(struct xboot_ctx *ctx)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return 0;
	}
	return ctx->imei_count;
}

unsigned char *xboot_get_devicekey(struct xboot_ctx *ctx, unsigned int *len)
{
	if (!ctx || !len) {
		FCS_LOG_ERR("Invalid argument\n");
		return NULL;
	}
	*len = ctx->device_key_len;
	return ctx->device_key;
}

int xboot_is_prototype(struct xboot_ctx *ctx)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return 0;
	}
	return ctx->is_prototype;
}

/* Deprecated */
unsigned char *xboot_get_hwconf_rev(struct xboot_ctx *ctx, unsigned int *len)
{
	if (!ctx || !len) {
		FCS_LOG_ERR("Invalid argument\n");
		return NULL;
	}
	/* Always return nothing */
	*len = 0;
	return NULL;
}

char *xboot_get_cmdline_additions(struct xboot_ctx *ctx)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return "";
	}
	return ctx->sony_cmdline_additions;
}

char *xboot_get_cmdline_additions_v2(struct xboot_ctx *ctx)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return "";
	}
	return ctx->sony_cmdline_additions_v2;
}

int xboot_is_backlight_enable(struct xboot_ctx *ctx)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}
	return ctx->backlight_enable;
}

unsigned int xboot_get_boot_mode(struct xboot_ctx *ctx)
{
	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return XBOOT_BOOT_INVALID_MODE;
	}
	return ctx->boot_mode;
}

int xboot_make_decisions(struct xboot_ctx *ctx)
{
	int res;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = sony_boot_make_decisions(ctx);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("MakeDecisions returned error %d\n", res);
		return res;
	}

	return FCSERR_OK;
}

int xboot_finalize_longpress(struct xboot_ctx *ctx)
{
	int res;

	if (!ctx) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	res = sony_boot_finalize_longpress(ctx);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Finalize Longpress returned error %d\n", res);
		return -FCSERR_ESTATE;
	}

	return FCSERR_OK;
}

int xboot_get_rollback_counters(uint64_t *cnt_buf, uint32_t vector_size)
{
	if (!cnt_buf) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	return xbpal_read_vbmeta_counters(cnt_buf, vector_size);
}

int xboot_reset_rollback_counters(void)
{
	return xbpal_reset_vbmeta_counters();
}

int xboot_get_avb_version(void)
{
	return xbpal_get_avb_version();
}

int xboot_unlock_bootloader(uint8_t *rck_hash, uint8_t *rck, uint8_t rck_len)
{
	int ret;
	struct xfl_sec_data xfl_sec_data = {0};

	ret = xboot_compare_rck(rck_hash, rck, rck_len);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Invalid RCK\n");
		return ret;
	}

	ret = xboot_delete_dk();
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Unable to delete dk\n");
		return ret;
	}

	if (!xbpal_erase_user_sensitive()) {
		FCS_LOG_ERR("Failed to delete user sensitive partitions\n");
		return ret;
	}

	/* Reset rollback counters in secure storage */
	ret = xboot_reset_rollback_counters();
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to reset rollback counters, error:%d\n",
				ret);
		return ret;
	}

	ret = read_xfl_sec_data(&xfl_sec_data);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read xfl_sec_data, error:%d\n", ret);
		return ret;
	}

	ret = xbpal_unlock_bootloader();
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to unlock the bootloader: %d\n", ret);
		return ret;
	} else if (xfl_sec_data.has_been_unlocked != HAS_BEEN_UNLOCKED_MAGIC) {
		/* Unlocking was successful, update has_been_unlocked flag. */
		xfl_sec_data.has_been_unlocked = HAS_BEEN_UNLOCKED_MAGIC;
		ret = write_xfl_sec_data(&xfl_sec_data);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("Failed to write xfl_sec_data, error:%d\n",
					ret);
			/* Try to lock back the bootloader. */
			ret = xbpal_lock_bootloader();
			if (ret != FCSERR_OK) {
				/*
				 * This should be an impossible scenario, where
				 * both reading from RPMB and unlocking the
				 * bootloader are successful, but both writing
				 * to RPMB and locking the bootloader are
				 * unsuccessful. In case it happens, just
				 * print out the error and return.
				 */
				FCS_LOG_ERR(
					"Bootloader is unlocked but has_been_unlocked flag is not set!\n");
			} else {
				/*
				 * Bootloader is locked again.
				 * Unlock command did not succeed.
				 */
				FCS_LOG_ERR(
					"Bootloader locked. Unlocking not successful\n");
				return -FCSERR_ESTATE;
			}
		}
	}

	return FCSERR_OK;
}

int xboot_lock_bootloader(void)
{
	int ret;

	ret = xboot_delete_dk();
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Unable to delete dk\n");
		return ret;
	}

	if (!xbpal_erase_user_sensitive()) {
		FCS_LOG_ERR("Failed to delete user sensitive partitions\n");
		return ret;
	}

	/* Reset rollback counters in secure storage */
	ret = xboot_reset_rollback_counters();
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to reset rollback counters, error:%d\n",
				ret);
		return ret;
	}

	ret = xbpal_lock_bootloader();
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to lock the bootloader: %d\n", ret);
		return ret;
	}

	return FCSERR_OK;
}

int xboot_rng(uint8_t *buf, char *additional, uint16_t len)
{
	return mbedtls_rng(buf, additional, len);
}

char *xboot_bootconfig_get_taCommandLine(struct xboot_ctx *ctx)
{
	return ctx->bootconfig->taCommandLineArgs;
}

char *xboot_bootconfig_get_taCustomerId(struct xboot_ctx *ctx)
{
	return ctx->bootconfig->taCustomerId;
}

void xboot_bootconfig_clear_taCustomerId(struct xboot_ctx *ctx)
{
	if (ctx->bootconfig->taCustomerId != NULL) {
		free(ctx->bootconfig->taCustomerId);
		ctx->bootconfig->taCustomerId = NULL;
	}
}

char *xboot_bootconfig_get_taColorId(struct xboot_ctx *ctx)
{
	return ctx->bootconfig->taColorId;
}

void xboot_bootconfig_clear_taColorId(struct xboot_ctx *ctx)
{
	if (ctx->bootconfig->taColorId != NULL) {
		free(ctx->bootconfig->taColorId);
		ctx->bootconfig->taColorId = NULL;
	}
}
