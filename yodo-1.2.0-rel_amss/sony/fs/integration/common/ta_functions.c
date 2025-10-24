/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
/**
 * @file ta_functions.c
 *
 * @brief Implementation to connect TA library with a flashdriver
 */
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include "fcserr.h"
#include "ta_public_types.h"
#include "ta_types.h"
#include "ta.h"
#include "storage.h"
#include "fcslog.h"
#include "storage_file.h"
#include "fcsenv_def.h"

#define TA_CODEID_LOADER 0x40

/**
 * This function shall read data from flash memory. The data buffer
 * supplied from the caller (TA) can be of any size.
 *
 * @param[in] addr The start byte address.
 * @param[in] p_data Pointer to the data buffer.
 * @param[in] size size of data (should always be a multiple of the sector size)
 *
 * @returns true for success, and false if an error occurred.
 */
static bool ta_read_block(uint32_t addr, void *p_data, uint32_t size)
{
	bool result = false;
	struct storage_ctx *ctx;
	ssize_t count;

	FCS_LOG_INF("%s: Read %u bytes at address %08X\n", __func__,
		size, addr);

	/* Open TA partition */
	ctx = storage_open_by_name(NULL, TA_PARTITION_NAME);
	if (!ctx) {
		FCS_LOG_ERR("Cannot open partition %s!\n", TA_PARTITION_NAME);
		goto ta_read_block_exit;
	}

	/* Seek to the given address */
	if (storage_lseek(ctx, addr, STORAGE_SEEK_SET) < 0) {
		FCS_LOG_ERR("Cannot seek to address %08X!\n", addr);
		goto ta_read_block_exit;
	}

	/* Read requested data */
	count = storage_read(ctx, p_data, (ssize_t)size);
	if (count < (ssize_t)size) {
		FCS_LOG_ERR("Cannot read, error %zd!\n", count);
		goto ta_read_block_exit;
	}

	result = true;

ta_read_block_exit:
	if (ctx)
		if (storage_close(ctx))
			FCS_LOG_ERR("Cannot close partition %s!\n",
				TA_PARTITION_NAME);

	return result;
}

/**
 * This function shall write data to the flash memory. The data buffer
 * supplied from the caller (TA) will always be a multiple of a eMMC sector.
 *
 * @param[in] addr The start byte address.
 * @param[in] p_data Pointer to the data buffer.
 * @param[in] size Size of data (should always be a multiple of the sector size)
 *
 * @returns true for success, and false if an error occurred.
 */
static bool ta_write_block(uint32_t addr, const void *p_data, uint32_t size)
{
	bool result = false;
	struct storage_ctx *ctx;
	ssize_t count;

	FCS_LOG_INF("%s: Write %u bytes at address %08X\n", __func__,
		size, addr);

	/* Open TA partition */
	ctx = storage_open_by_name(NULL, TA_PARTITION_NAME);
	if (!ctx) {
		FCS_LOG_ERR("Cannot open partition %s!\n", TA_PARTITION_NAME);
		goto ta_write_block_exit;
	}

	/* Seek to the given address */
	if (storage_lseek(ctx, addr, STORAGE_SEEK_SET) < 0) {
		FCS_LOG_ERR("Cannot seek to address %08X!\n", addr);
		goto ta_write_block_exit;
	}

	/* Write given data */
	count = storage_write(ctx, p_data, (ssize_t)size);
	if (count < (ssize_t)size) {
		FCS_LOG_ERR("Cannot write, error %zd!\n", count);
		goto ta_write_block_exit;
	}

	result = true;

ta_write_block_exit:
	if (ctx)
		if (storage_close(ctx))
			FCS_LOG_ERR("Cannot close partition %s!\n",
				TA_PARTITION_NAME);

	return result;
}

/**
 * This function shall erase one flash erase block, located at the supplied
 * address. Blocks tried unsuccessfully with the function TA_IsBadBlock, will
 * not be erased by the TA.
 *
 * @param[in] addr The address of the block to be erased.
 *
 * @returns true for success, and false if an error occurred.
 */
static bool ta_erase_block(uint32_t addr)
{
	bool result = false;
	struct storage_ctx *ctx;
	int ret;

	FCS_LOG_INF("%s: Erase block at address 0x%08X\n", __func__, addr);

	/* Open TA partition */
	ctx = storage_open_by_name(NULL, TA_PARTITION_NAME);
	if (!ctx) {
		FCS_LOG_ERR("Cannot open partition %s!\n", TA_PARTITION_NAME);
		goto ta_erase_block_exit;
	}

	/* Seek to the given address */
	if (storage_lseek(ctx, addr, STORAGE_SEEK_SET) < 0) {
		FCS_LOG_ERR("Cannot seek to address %08X!\n", addr);
		goto ta_erase_block_exit;
	}

	/* Write 0's instead of using erase. Erase uses BLKDISCARD
	 * which does not guarantee that the data will be erased and
	 * and set to 0xOO
	 */
	ret = storage_file_fill(ctx, 0, TA_BLOCK_SIZE);
	if (ret < 0) {
		FCS_LOG_ERR("Cannot write, error %d!\n", ret);
		goto ta_erase_block_exit;
	}

	result = true;

ta_erase_block_exit:
	if (ctx)
		if (storage_close(ctx))
			FCS_LOG_ERR("Cannot close partition %s!\n",
				TA_PARTITION_NAME);

	return result;
}

/**
 * This function shall give information whether or not a block is valid for
 * use by the TA. Blocks that is marked as bad according to this function
 * will be completely ignored by the TA.
 *
 * @param[in] addr The address of the block to tried.
 *
 * @returns true for bad block, and false otherwise.
 */
static bool ta_is_bad_block(uint32_t addr)
{
	(void)(addr); /* Unused parameter */
	return false;
}

static void ta_crash(void)
{
	FCS_LOG_ERR("%s CALLED!!!\n", __func__);
}

static uint8_t ta_getcodeid(void)
{
	return TA_CODEID_LOADER;
}


int ta_init(void)
{
	int result = FCSERR_OK;
	struct storage_ctx *ctx;
	off_t partition_size;

	const TA_Functions_t ta_funcs = {
		(TA_ReadBlock_t)ta_read_block,
		(TA_WriteBlock_t)ta_write_block,
		(TA_EraseBlock_t)ta_erase_block,
		(TA_IsBadBlock_t)ta_is_bad_block,
		(TA_Malloc_t)&malloc,
		(TA_Free_t)&free,
		(TA_ReadVerify_t)ta_read_block,
		(TA_Crash_t)ta_crash,
		(TA_GetCodeID_t)ta_getcodeid
	};

	/* Make sure TA is in the correct state. */
	(void)TA_Close();

	/* Open TA partition to find out size */
	ctx = storage_open_by_name(NULL, TA_PARTITION_NAME);
	if (!ctx) {
		FCS_LOG_ERR("Cannot open partition %s!\n", TA_PARTITION_NAME);
		goto failure;
	}

	/* Seek to the end of the partition */
	partition_size = storage_lseek(ctx, 0, STORAGE_SEEK_END);
	if (partition_size < 0) {
		FCS_LOG_ERR("Broken TA-partition: %d\n", (int)partition_size);
		(void)storage_close(ctx);
		goto failure;
	}

	if (storage_close(ctx)) {
		FCS_LOG_ERR("Cannot close partition %s!\n", TA_PARTITION_NAME);
		goto failure;
	}

	uint8_t ta_nbr_of_blocks = partition_size / TA_BLOCK_SIZE;

	FCS_LOG_INF("%s has size %d bytes (%d blocks)\n", TA_PARTITION_NAME,
		partition_size, ta_nbr_of_blocks);

	if (TA_Success != TA_SetConfig(&ta_funcs, 0, TA_BLOCK_SIZE,
		ta_nbr_of_blocks)) {
		FCS_LOG_ERR("Cannot configure TrimArea!\n");
		result = -FCSERR_ENIMP;
		goto failure;
	}

failure:
	/* Make sure TA is in the correct state. */
	(void)TA_Close();

	return result;
}

