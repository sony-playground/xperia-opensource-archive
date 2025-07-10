/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <string.h>
#include <stdbool.h>

#include "rooting_status.h"
#include "fcslog.h"
#include "fcserr.h"
#include "fcs_defines.h"
#include "fcsenv_def.h"
#include "ta_interface.h"
#include "digest.h"
#include "hwconf.h"
#include "simlock.h"
#include "simlock_engine.h"
#include "convert.h"
#include "core.h"
#include "eroot.h"
#ifdef BUILD_XFL
#include "storage.h"
#include "protocol_util.h"
#else
#include "xboot_pal_types.h"
#endif

#define MAX_BUF_SIZE 64

static int buflbuf(uint8_t *buf, uint32_t buf_size, uint8_t *tag,
		uint32_t tag_size, uint32_t *index);
static int internal_get_rooting_status(uint8_t *sl_data, int sl_size,
		uint8_t simlock_rooting_tag, uint8_t *rooting_status);

static int get_simlock_rooting_status(uint8_t *device_id,
		size_t device_id_length,
		struct embed_rootcert_item *embed_rootcert_list,
		size_t embed_rootcert_list_count,
		uint8_t *rooting_status,
		uint8_t *rck_h)
{
	int res, sl_size, sls_size;
	uint8_t *sl_buf = NULL;
	uint8_t *sls_buf = NULL;
	unsigned int range_offset;
	size_t range_length;
	uint8_t *sl_parameters = NULL;
	uint32_t sl_parameters_size;
	uint8_t buf[MAX_BUF_SIZE];
	size_t id_length;
	uint32_t index = 0;
	uint8_t simlock_rooting_tag = 0;
	char rck_h_ascii[RCK_H_ASCII_LENGTH] = {0};
	hwconfig_t hwconf_hdl = NULL;

	if (embed_rootcert_list == NULL ||
			rooting_status == NULL ||
			rck_h == NULL) {
		FCS_LOG_ERR("Invalid parameters\n");
		res = -FCSERR_EINVAL;
		goto grs_fail;
	}

	res = setup_hwconfig(device_id, device_id_length,
			embed_rootcert_list,
			embed_rootcert_list_count,
			&hwconf_hdl);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to init hwconfig\n");
		goto grs_fail;
	}

	res = get_ta_unit_size(TA_MISC_PART, TA_SIMLOCK_UNIT, &sl_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read simlock unit: (%d)\n", res);
		goto grs_fail;
	}
	if (sl_size == 0) {
		FCS_LOG_ERR("No simlock unit found\n");
		goto grs_fail;
	}
	res = get_ta_unit_size(TA_MISC_PART, TA_SIMLOCK_SIGNATURE_UNIT,
			&sls_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read simlock signature unit: (%d)\n",
			res);
		goto grs_fail;
	}
	if (sls_size == 0) {
		FCS_LOG_ERR("No simlock signature unit found\n");
		goto grs_fail;
	}

	sl_buf = malloc(sl_size);
	if (sl_buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto grs_fail;
	}
	sls_buf = malloc(sls_size);
	if (sls_buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto grs_fail;
	}

	res = read_ta(TA_MISC_PART, TA_SIMLOCK_UNIT, sl_buf, sl_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read simlock unit: (%d)\n", res);
		goto grs_fail;
	}
	res = read_ta(TA_MISC_PART, TA_SIMLOCK_SIGNATURE_UNIT, sls_buf,
			sls_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read simlock signature unit: (%d)\n",
			res);
		goto grs_fail;
	}

	/* First IMEI => Index 0 */
	res = get_imei(0, buf, MAX_BUF_SIZE, &id_length, hwconf_hdl);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get phone_id (%d)\n", res);
		goto grs_fail;
	}

	/* OPID=0 for SOMC Simlock */
	res = simlock_verify(buf, id_length,
				embed_rootcert_list,
				embed_rootcert_list_count,
				sl_buf, sl_size,
				sls_buf, sls_size,
				0,
				&range_offset, &range_length);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to verify simlock: (%d)\n", res);
		goto grs_fail;
	}

	/* Read out the parameter part of the simlock data unit */
	sl_parameters = &sl_buf[range_offset];
	sl_parameters_size = range_length;

	/* Look for ROOTING_ALLOWED="x" tag */
	res = buflbuf(sl_parameters, sl_parameters_size,
			(uint8_t *)"ROOTING_ALLOWED",
			strlen("ROOTING_ALLOWED"), &index);
	if (res == -FCSERR_ENOTF) {
		/* If tag is not found then bootloader can't be unlocked */
		FCS_LOG_INF("ROOTING_ALLOWED tag not found in simlock\n");
		*rooting_status = BOOT_NOT_UNLOCKABLE;
		res = FCSERR_OK;
		goto grs_fail;
	} else if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get tag: (%d)\n", res);
		goto grs_fail;
	}

	/* Save the x in the tag and remove the ascii-ness of it */
	if (index + sizeof("ROOTING_ALLOWED=\"x\"") <= sl_parameters_size &&
			res == FCSERR_OK) {
		simlock_rooting_tag = sl_parameters[index +
			strlen("ROOTING_ALLOWED=\"")] - '0';
	}

	res = internal_get_rooting_status(sl_buf, sl_size,
			simlock_rooting_tag, rooting_status);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get rooting status: (%d)\n", res);
		goto grs_fail;
	}

	/* Look for RCK_H="xxxxxxxxxxxxxxxx" tag */
	res = buflbuf(sl_parameters, sl_parameters_size,
			(uint8_t *)"RCK_H",
			strlen("RCK_H"), &index);
	if (res == -FCSERR_ENOTF) {
		/* If tag is not found then bootloader can't be unlocked */
		FCS_LOG_INF("RCK_H tag not found in simlock\n");
		*rooting_status = BOOT_NOT_UNLOCKABLE;
		res = FCSERR_OK;
		goto grs_fail;
	} else if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get tag: (%d)\n", res);
		goto grs_fail;
	}

	if (index + sizeof("RCK_H=\"xxxxxxxxxxxxxxxx\"") <= sl_parameters_size
			&& res == FCSERR_OK) {
		memcpy(rck_h_ascii,
			((const void *)(sl_parameters + index +
				strlen("RCK_H=\""))),
			sizeof(rck_h_ascii));
		res = FCSERR_OK;
	}

	res = ascii_to_bin(rck_h, RCK_H_LENGTH,
		rck_h_ascii, sizeof(rck_h_ascii));
	if (res != FCSERR_OK)
		FCS_LOG_ERR("ascii_to_bin failed (%d)\n", res);

grs_fail:
	if (hwconf_hdl)
		teardown_hwconfig(hwconf_hdl);
	free(sl_buf);
	free(sls_buf);

	return res;
}

int get_simlock_unlock_data(uint8_t *unlock_status, uint8_t *rck_h)
{
	int ret;
	uint8_t die_id[DIE_ID_LEN];
	uint32_t die_id_len = DIE_ID_LEN;
	struct embed_rootcert_item *embed_rootcert_list = NULL;
	size_t embed_rootcert_list_count = 0;

	ret = core_get_dieid(die_id, die_id_len);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("failed to get die id (%d)\n", ret);
		return ret;
	}

	ret = get_embedded_roots(
		&embed_rootcert_list, &embed_rootcert_list_count);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get embedded_roots from env: (%d)\n",
				ret);
		goto exit;
	}

	ret = get_simlock_rooting_status(die_id, die_id_len,
					embed_rootcert_list,
					embed_rootcert_list_count,
					unlock_status,
					rck_h);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get unlock data: (%d)\n", ret);
		goto exit;
	}

exit:
	free_embedded_roots(&embed_rootcert_list);
	return ret;
}

int verify_rck(uint8_t *rck_h_bin, const uint8_t *rck_ascii,
		uint32_t rck_ascii_len)
{
	int res;
	uint8_t rck_bin[RCK_H_LENGTH] = {0};

	if (rck_h_bin == NULL || rck_ascii == NULL || rck_ascii_len == 0) {
		FCS_LOG_ERR("Invalid parameters\n");
		return -FCSERR_EINVAL;
	}

	res = ascii_to_bin(rck_bin, sizeof(rck_bin), (char *)rck_ascii,
		rck_ascii_len);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Invalid data format\n");
		return res;
	}

	res = digest_sha256_verify(rck_bin, rck_ascii_len >> 1, rck_h_bin);

	return res;
}

int google_allow_unlock(uint8_t *allow_unlock)
{
	uint32_t frp_part_size = 0;
	int res = FCSERR_OK;
	uint8_t *frp_part_buf = NULL;
#ifdef BUILD_XFL
	struct storage_ctx *sctx = NULL;
	uint32_t data_read = 0;
	const char *frp_part_name = FRP_PARTITION_NAME;
#endif

	if (!allow_unlock) {
		FCS_LOG_ERR("Invalid argument\n");
	return -FCSERR_EINVAL;
	}

	*allow_unlock = 0;

#ifdef BUILD_XFL
	sctx = storage_open_by_name(NULL, frp_part_name);
	if (sctx == NULL) {
		FCS_LOG_ERR("Failed to open %s\n", frp_part_name);
		return -FCSERR_EINVAL;
	}

	frp_part_size = pu_get_part_size(sctx);
	if (frp_part_size < 0) {
		FCS_LOG_ERR("IO Error\n");
		return -FCSERR_EIO;
	}

	frp_part_buf = malloc(frp_part_size);
	if (frp_part_buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	data_read = storage_read(sctx, frp_part_buf, frp_part_size);
	if (data_read != frp_part_size) {
		FCS_LOG_ERR("IO Error\n");
		res = -FCSERR_EIO;
		goto exit;
	}
#else
	res = xbpal_get_frp_data_size(&frp_part_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR(
		"Failed to read frp data size err=%d\n", res);
		goto exit;
	}

	frp_part_buf = malloc(frp_part_size);
	if (frp_part_buf == NULL) {
		FCS_LOG_ERR("Failed to allocate memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	res = xbpal_read_frp_data(frp_part_buf, frp_part_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("xbpal_read_frp returned err=%d\n", res);
		goto exit;
	}

#endif
	*allow_unlock = (unsigned char)(frp_part_buf[frp_part_size - 1] & 0x01);

exit:
#ifdef BUILD_XFL
	if(sctx)
		storage_close(sctx);
#endif
	free(frp_part_buf);

	return res;
}

int delete_dk(void)
{
	int res = FCSERR_OK;
	int ta_dk_number_size;

	res = get_ta_unit_size(TA_MISC_PART, TA_DK_NUMBER_UNIT,
			       &ta_dk_number_size);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get size of TA_DK_NUMBER_UNIT\n");
		return res;
	}

	if (ta_dk_number_size > 0) {
		res = delete_ta(TA_MISC_PART, TA_DK_NUMBER_UNIT);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to delete DK\n");
			return res;
		}
	}

	return res;
}

/* Looks for tag in buf. If found the offset in buf where tag starts
   is stored in index and FCSERR_OK is returned, otherwise index is 0
   and -FCSERR_NOTF is returned. */
static int buflbuf(uint8_t *buf, uint32_t buf_size, uint8_t *tag,
		uint32_t tag_size, uint32_t *index)
{
	int res = FCSERR_OK;
	unsigned int i;
	bool found = false;

	if ((tag_size > buf_size) || buf == NULL || tag == NULL ||
			tag_size == 0) {
		FCS_LOG_ERR("Invalid input parameters\n");
		res = -FCSERR_EINVAL;
		goto buflbuf_fail;
	}

	*index = 0;
	for (i = 0; i + tag_size < buf_size; i++)
		if (memcmp(buf + i, tag, tag_size) == 0) {
			found = true;
			break;
		}

	if (found)
		*index = i;
	else
		res = -FCSERR_ENOTF;

buflbuf_fail:
	return res;
}

static int internal_get_rooting_status(uint8_t *sl_data, int sl_size,
		uint8_t simlock_rooting_tag, uint8_t *rooting_status)
{
	int res = FCSERR_OK;
	int lock_status = 1;
	int i;

	if (!rooting_status) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	switch (simlock_rooting_tag) {
	case 0: /* ROOTING_ALLOWED="0" in SimLock =>
		   bootloader unlock not allowed */
		*rooting_status = BOOT_NOT_UNLOCKABLE;
		break;
	case 1: /* ROOTING_ALLOWED="1" in SimLock =>
		   bootloader unlock allowed */
		*rooting_status = BOOT_UNLOCKABLE;
		break;
	case 2: /* ROOTING_ALLOWED="2" in SimLock =>
		   bootloader unlock allowed if SimLock is unlocked */
		/* Go through all four locks */
		for (i = 0; i < 4; i++) {
			res = simlock_engine_get_lock_status(
					i + 1,
					sl_data,
					sl_size,
					&lock_status);
			if (res != FCSERR_OK) {
				FCS_LOG_ERR(
				"Failed to get SimLock lock status: (%d)\n",
				res);
				goto exit;
			}
			/* It's enough if one lock is locked
			 * to not allow rooting */
			if (lock_status != 0)
				break;
		}

		if (lock_status == 0)
			*rooting_status = BOOT_UNLOCKABLE_SIMLOCK_UNLOCKED;
		else
			*rooting_status = BOOT_UNLOCKABLE_SIMLOCK_LOCKED;
		break;
	default:
		FCS_LOG_ERR("Invalid tag in SimLock: ROOTING_ALLOWED=\"%d\"\n",
				simlock_rooting_tag);
		res = -FCSERR_EDATA;
		break;
	}
exit:
	return res;
}
