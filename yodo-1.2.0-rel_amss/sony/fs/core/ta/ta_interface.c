/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

/*
 * Interface for TA functionality
 */


#include <string.h>
#include <stdbool.h>
#include "fcslog.h"
#include "ta.h"
#include "ta_interface.h"
#include "xboot_pal_types.h"
#include "fcserr.h"
#include "fcs_endian.h"

int format_ta(uint8_t partition)
{
	int res = FCSERR_OK;
	TA_ErrCode_t err;

	/* Open TA */
	(void)lock_ta_open();
	err = TA_OpenPartition(partition, TA_SAFE_WRITE);
	if (err != TA_Success && err != TA_Invalid) {
		FCS_LOG_ERR("Unable to open TA partition %d, err=%d\n",
			partition, err);
		res = -FCSERR_EOPEN;
		goto exit_format_ta;
	}

	/* Format TA */
	err = TA_Format(TA_VERSION);
	if (err != TA_Success) {
		FCS_LOG_ERR("Unable to format TA partition %d, err=%d\n",
			partition, err);
		res = -FCSERR_EFORMAT;
		/* Continue to do TA_Close() */
	}

	/* Close TA */
	(void)TA_Close();

exit_format_ta:
	(void)unlock_ta_open();
	return res;
}

int get_ta_unit_size(uint8_t partition, uint32_t unit, int *unit_size)
{
	int res = FCSERR_OK;
	TA_ErrCode_t err;
	int ta_opened = false;

	if (!unit_size) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* Open TA partition for read */
	(void)lock_ta_open();
	err = TA_OpenPartition(partition, TA_READ);
	if (err == TA_Invalid)
		ta_opened = true;
	if (err != TA_Success) {
		FCS_LOG_ERR("Unable to open TA partition %d, error=%d\n",
			partition, err);
		res = -FCSERR_EINVAL;
		goto exit_get_ta_unit_size;
	}

	ta_opened = true;

	/* Get size of unit */
	*unit_size = TA_GetUnitSize(unit);
	if (*unit_size == 0) {
		/* This is not an error */
		FCS_LOG_INF("Unit does not exist (%d)\n", unit);
		res = FCSERR_OK;
		goto exit_get_ta_unit_size;
	}

	FCS_LOG_INF("Size of unit %d is %d bytes\n", unit, *unit_size);

exit_get_ta_unit_size:
	if (ta_opened)
		TA_Close();
	(void)unlock_ta_open();
	return res;
}

int read_ta(uint8_t partition, uint32_t unit, uint8_t *buf, int buf_size)
{
	int res = FCSERR_OK;
	TA_ErrCode_t err;
	int ta_opened = false;

	/* Open TA partition for read */
	(void)lock_ta_open();
	err = TA_OpenPartition(partition, TA_READ);
	if (err == TA_Invalid)
		ta_opened = true;
	if (err != TA_Success) {
		FCS_LOG_ERR("Unable to open TA partition %d, error=%d\n",
			partition, err);
		res = -FCSERR_EINVAL;
		goto exit_read_ta;
	}

	ta_opened = true;

	err = TA_ReadData(unit, buf, buf_size);
	if (err == TA_UnitNotFound) {
		FCS_LOG_WRN("Unit %d does not exist\n", unit);
		res = -FCSERR_ENOTF;
		goto exit_read_ta;
	}

	if (err != TA_Success) {
		FCS_LOG_WRN("Unable to read TA unit %d, error=%d\n",
			unit, err);
		res = -FCSERR_EIO;
		goto exit_read_ta;
	}

exit_read_ta:
	if (ta_opened)
		TA_Close();
	(void)unlock_ta_open();
	return res;
}

int get_all_ta_size(uint8_t partition, int *ta_size, bool include_hi_ta)
{
	int res = FCSERR_OK;
	TA_ErrCode_t err;
	uint32_t unit, unit_size;
	uint8_t *pData = NULL;

	if (!ta_size) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* Open TA partition for read */
	(void)lock_ta_open();
	err = TA_OpenPartition(partition, TA_READ);
	if (err != TA_Success) {
		if (err == TA_Invalid)
			TA_Close();
		FCS_LOG_ERR("Unable to open TA partition %d, error=%d\n",
			partition, err);
		(void)unlock_ta_open();
		return -FCSERR_EINVAL;
	}

	/* Calculate total size first */
	*ta_size = 0;
	while (TA_Inc_GetSize(&unit_size) == TA_Success) {
		if (unit_size == 0){
			pData = malloc(1);
		}else{
			pData = malloc(unit_size);
		}
		if (pData == NULL) {
			FCS_LOG_ERR("Out of memory\n");
			res = -FCSERR_ENOMEM;
			goto exit_get_all_ta_size;
		}

		TA_Inc_Read(&unit, pData, unit_size);

		/*
		 * Only calculate size of units you are allowed to read.
		 * High ta from MISC_TA requires include_hi_ta to be true.
		 */
		if (partition == TA_MISC_PART && !include_hi_ta &&
				unit > MISC_TA_MAX_PUBLIC_UNIT_ID) {
			free(pData);
			TA_Inc_NextUnit();
			continue;
		}

		*ta_size += 4; /* Unit number 4 bytes */
		*ta_size += 4;/* Unit size 4 bytes */
		*ta_size += unit_size;
		TA_Inc_NextUnit();
		free(pData);
	}


	FCS_LOG_INF("TA total size=%ld\n", *ta_size);

exit_get_all_ta_size:
	TA_Close();
	(void)unlock_ta_open();
	return res;
}

int read_all_ta(uint8_t partition, uint8_t *buf, int buf_size,
		bool include_hi_ta)
{
	uint32_t unit_size;
	int res = FCSERR_OK;
	TA_ErrCode_t err;
	uint8_t *pData = NULL;
	bool ta_opened = false;
	uint32_t unit;
	uint8_t *bufp; /* Pointer into buf */
	int ta_size = 0;

	if (!buf) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* Open TA partition for read */
	(void)lock_ta_open();
	err = TA_OpenPartition(partition, TA_READ);
	if (err == TA_Invalid)
		ta_opened = true;
	if (err != TA_Success) {
		FCS_LOG_ERR("Unable to open TA partition %d, error=%d\n",
			partition, err);
		res = -FCSERR_EINVAL;
		goto exit_read_all_ta;
	}

	ta_opened = true;

	/* Read data and build response */
	bufp = buf;
	while (TA_Inc_GetSize(&unit_size) == TA_Success) {
		if (unit_size == 0){
			pData = malloc(1);
		}else{
			pData = malloc(unit_size);
		}
		if (pData == NULL) {
			FCS_LOG_ERR("malloc failed!\n");
			res = -FCSERR_ENOMEM;
			goto exit_read_all_ta;
		}

		TA_Inc_Read(&unit, pData, unit_size);
		FCS_LOG_INF("TA unit=%ld, size=%ld\n", unit, unit_size);
		/*
		 * High ta from MISC_TA can only be read if include_hi_ta is
		 * true. If partition is not MISC_TA ignore include_hi_ta.
		 */
		if (partition == TA_MISC_PART && !include_hi_ta &&
				unit > MISC_TA_MAX_PUBLIC_UNIT_ID) {
			free(pData);
			TA_Inc_NextUnit();
			continue;
		}

		/*
		 * Check that the buffer has enough space, 8 additional bytes
		 * are needed for unit number and unit size
		 */
		ta_size += 8 + unit_size;
		if (ta_size > buf_size) {
			FCS_LOG_ERR(
				"Provided buffer (%d bytes) is too small\n",
				buf_size);
			res = -FCSERR_EINVAL;
			free(pData);
			goto exit_read_all_ta;
		}

		/* Build string from unit. unit number + unit size + unit */
		write_be_u32(unit, bufp);
		bufp += 4;
		write_be_u32(unit_size, bufp);
		bufp += 4;
		memcpy(bufp, pData, unit_size);
		free(pData);

		bufp += unit_size;
		TA_Inc_NextUnit();
	}

exit_read_all_ta:
	if (ta_opened)
		TA_Close();
	(void)unlock_ta_open();
	return res;
}

int write_ta(uint8_t partition, uint32_t unit, const uint8_t *buf, int buf_size)
{
	int res = FCSERR_OK;
	TA_ErrCode_t err;

	/* Open TA partition for write */
	(void)lock_ta_open();
	err = TA_OpenPartition(partition, TA_SAFE_WRITE);
	if (err != TA_Success) {
		if (err == TA_Invalid)
			TA_Close();
		FCS_LOG_ERR("Unable to open TA partition %d, error=%d\n",
			partition, err);
		res = -FCSERR_EINVAL;
		goto exit_write_ta;
	}

	err = TA_WriteData(unit, buf, buf_size);
	if (err != TA_Success) {
		FCS_LOG_ERR("Unable to write to TA unit %d\n", unit);
		res = -FCSERR_EINVAL;
	}

	TA_Close();

exit_write_ta:
	(void)unlock_ta_open();
	return res;
}

int delete_ta(uint8_t partition, uint32_t unit)
{
	int res = FCSERR_OK;
	TA_ErrCode_t err;

	/* Open TA partition for write */
	(void)lock_ta_open();
	err = TA_OpenPartition(partition, TA_SAFE_WRITE);
	if (err != TA_Success) {
		if (err == TA_Invalid)
			TA_Close();
		FCS_LOG_ERR("Unable to open TA partition %d, error=%d\n",
			partition, err);
		res = -FCSERR_EINVAL;
		goto exit_delete_ta;
	}

	err = TA_DeleteUnit(unit);
	if (err != TA_Success) {
		FCS_LOG_ERR("Unable to delete TA unit %d\n", unit);
		res = -FCSERR_EINVAL;
	}

	TA_Close();

exit_delete_ta:
	(void)unlock_ta_open();
	return res;
}
