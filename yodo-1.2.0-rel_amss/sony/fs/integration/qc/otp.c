/*
 * Copyright (C) 2013 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "tar_utils.h"
#include "otp.h"
#include "qfprom_fec.h"
#include "otp_rw.h"
#include "security_properties.h"
#include "handler_list.h"
#include "fcserr.h"
#include "fcslog.h"
#include <string.h>
#include <ext_modem.h>
#include <qsee.h>

enum qfprom_row {
	QFPROM_ROW_LSB = 0,
	QFPROM_ROW_MSB,
};

#define FUSE_NBR_ENTRIES 128
#define OTP_EXT_MODEM_MAGIC {0x42, 0x55, 0x52, 0x4e}

static struct otp_rw_entry fuse_cfg[FUSE_NBR_ENTRIES];
static uint32_t fuse_cfg_pos;

static int otp_burn_add_row(
		const uint8_t *data, uint16_t prop_len, uint32_t flags)
{
	int res = -FCSERR_EBURN;

	if (fuse_cfg_pos >= FUSE_NBR_ENTRIES) {
		FCS_LOG_ERR("fuse data overflow");
		return res;
	}

	if (prop_len != 12) {
		/*
		 * All fuse operations consist of 4 byte address and
		 * 8 byte data (LSB:MSB)
		 */
		res = -FCSERR_EINVAL;
		return res;
	}

	memcpy(&(fuse_cfg[fuse_cfg_pos].addr), data, 4);
	memcpy(&(fuse_cfg[fuse_cfg_pos].data[QFPROM_ROW_MSB]), &data[4], 4);
	memcpy(&(fuse_cfg[fuse_cfg_pos].data[QFPROM_ROW_LSB]), &data[8], 4);

	fuse_cfg[fuse_cfg_pos].flags = flags;
	fuse_cfg_pos++;

	return FCSERR_OK;
}

static int otp_burn_fec(const uint8_t *data, uint16_t prop_len)
{
	return otp_burn_add_row(data, prop_len, OTP_RW_BURN_FEC);
}

static int otp_burn_no_fec(const uint8_t *data, uint16_t prop_len)
{
	return otp_burn_add_row(data, prop_len, OTP_RW_BURN_NO_FEC);
}

static int otp_burn_rand_fec(const uint8_t *data, uint16_t prop_len)
{
	return otp_burn_add_row(data, prop_len, OTP_RW_BURN_RAND_FEC);
}

static int otp_burn_rand_no_fec(const uint8_t *data, uint16_t prop_len)
{
	return otp_burn_add_row(data, prop_len, OTP_RW_BURN_RAND_NO_FEC);
}

static int otp_burn_ext_modem(const uint8_t *data, uint16_t prop_len)
{
	int res;
	uint8_t magic[] = OTP_EXT_MODEM_MAGIC;

	/* check data, magic and config */
	/* size of data excluding magic is one byte */
	if (prop_len != sizeof(magic) + 1) {
		FCS_LOG_ERR("Invalid secprop data len (%d)\n", prop_len);
		return -FCSERR_EINVAL;
	}

	if (memcmp(data, magic, sizeof(magic))) {
		FCS_LOG_ERR("Invalid secprop magic\n");
		return -FCSERR_EINVAL;
	}

	/* probe if external modem exist */
	if (!ext_modem_probe()) {
		FCS_LOG_ERR("No modem detected\n");
		return -FCSERR_ENODEV;
	}

	/* fuse modem */
	res = ext_modem_fuse(data[sizeof(magic)]);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Modem fuse failed (%d, %d)\n", res,
			    data[sizeof(magic)]);
		return res;
	}

	return FCSERR_OK;
}

static int otp_burn_final(const uint8_t *data, uint16_t prop_len)
{
	int res = FCSERR_OK;

	(void)(data); /* Unused parameter */
	(void)(prop_len); /* Unused parameter */

#ifndef CONFIG_ENABLE_FUSE_DRY_RUN
	/* Attempt to blow the fuse */
	if (fuse_cfg_pos != 0)
		res = otp_write_cfg(
			fuse_cfg, fuse_cfg_pos * sizeof(struct otp_rw_entry));
	else
		FCS_LOG_INF("Nothing to burn, skipping otp blowing fuse");
#else /* CONFIG_ENABLE_FUSE_DRY_RUN */
#warning FUSE_DRY_RUN
	LOG_WRN("NOT ACTUALLY BLOWING FUSE!\n");
#endif /* CONFIG_ENABLE_FUSE_DRY_RUN */

	fuse_cfg_pos = 0;

	return res;
}

int otp_init(void *handle)
{
	int res = FCSERR_OK;

	res = handler_list_add_handler(handle, &otp_burn_fec,
			(void *)OTP_DATA_WITH_ADDRESS);
	if (res < 0) {
		FCS_LOG_ERR("Failed to add handler\n");
		goto exit;
	}

	res = handler_list_add_handler(handle, &otp_burn_no_fec,
				(void *)OTP_DATA_WITH_ADDRESS_NO_FEC);
	if (res < 0) {
		FCS_LOG_ERR("Failed to add handler\n");
		goto exit;
	}

	res = handler_list_add_handler(handle, &otp_burn_rand_fec,
				(void *)RANDOM_DATA);
	if (res < 0) {
		FCS_LOG_ERR("Failed to add handler\n");
		goto exit;
	}

	res = handler_list_add_handler(handle, &otp_burn_rand_no_fec,
				(void *)RANDOM_DATA_NO_FEC);
	if (res < 0) {
		FCS_LOG_ERR("Failed to add handler\n");
		goto exit;
	}

	res = handler_list_add_handler(handle, &otp_burn_ext_modem,
				(void *)OTP_BURN_EXT_MODEM);
	if (res < 0) {
		FCS_LOG_ERR("Failed to add handler\n");
		goto exit;
	}

	res = handler_list_add_handler(handle, &otp_burn_final,
				(void *)OTP_DATA_FINAL);
	if (res < 0) {
		FCS_LOG_ERR("Failed to add handler\n");
		goto exit;
	}

#ifndef CFG_STUB_FUSE_APP
	/* Will load the fuse app from flash to ramdisk */
	res = extract_tar_from_partition("/etc/firmware", "tzxfl");
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to extract fuse application\n");
		goto exit;
	}
#endif

	/* Make sure qseecomd is started */
	res = qsee_start_qseecomd();
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("qsee_start_qseecomd failed (%d)\n", res);
		return res;
	}

	res = otp_rw_init();
	if (res) {
		FCS_LOG_ERR("opt_rw_init failed\n");
		return res;
	}

exit:
	return res;
}
