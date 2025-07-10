/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "ab_int.h"
#include "fcserr.h"
#include "fcslog.h"
#include "gpt.h"
#include "partman.h"
#include "protocol_util.h"
#include "storage.h"
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define SLOT_ATTR_PRIORITY_BIT (48)
#define SLOT_ATTR_ACTIVE_BIT (50)
#define SLOT_ATTR_MAX_RETRY_BIT (51)
#define SLOT_ATTR_SUCCESSFUL_BIT (54)
#define SLOT_ATTR_UNBOOTABLE_BIT (55)
#define PRIORITY ((uint64_t)0x3 << SLOT_ATTR_PRIORITY_BIT)
#define ACTIVE ((uint64_t)0x1 << SLOT_ATTR_ACTIVE_BIT)
#define MAX_RETRY ((uint64_t)0x7 << SLOT_ATTR_MAX_RETRY_BIT)
#define SUCCESSFUL ((uint64_t)0x1 << SLOT_ATTR_SUCCESSFUL_BIT)
#define UNBOOTABLE ((uint64_t)0x1 << SLOT_ATTR_UNBOOTABLE_BIT)

static int get_slot_pentry(char slot, struct gpt_part_info *pentry)
{
	int res = FCSERR_OK;
	struct storage_ctx *sctx = NULL;
	struct gpt_ctx *gctx = NULL;
	uint8_t *buf = NULL;
	ssize_t ssize, buf_sz;
	char lun[] = "x";
	char boot[] = "boot_x";
	int idx;
	bool has_slot;

	res = partman_has_slot("boot", &has_slot);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to look up slot\n");
		return res;
	}

	if (!has_slot) {
		FCS_LOG_INF("No slot support\n");
		return -FCSERR_ENOTF;
	}

	boot[strlen(boot) - 1] = slot;
	res = fcs_get_lun_and_index_of_partition(boot, strlen(boot),
			lun, strlen(lun), &idx);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get partition index\n");
		goto exit;
	}

	/* Open the lun we are interested in and read the gpt info */
	sctx = storage_open_by_name(NULL, lun);
	if (!sctx) {
		FCS_LOG_ERR("Failed to open device\n");
		return -FCSERR_EIO;
	}

	/* Get size of gpt */
	res = storage_get_gpt_info(sctx, lun, NULL, &buf_sz);
	if (res < 0) {
		FCS_LOG_ERR("Failed to read gpt table\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	if (buf_sz == 0) {
		FCS_LOG_ERR("Invalid size\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	buf = malloc(buf_sz);
	if (!buf) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	/* Get gpt */
	res = storage_get_gpt_info(sctx, lun, buf, &buf_sz);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read GPT table\n");
		goto exit;
	}

	ssize = storage_get_ssz(sctx);
	if (ssize < 0) {
		FCS_LOG_ERR("Failed to get sector size\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	gctx = gpt_parse_init(buf, buf_sz, ssize);
	if (!gctx) {
		FCS_LOG_ERR("Failed to parse partition table\n");
		res = -FCSERR_EINVAL;
		goto exit;

	}

	res = gpt_get_part_info_byidx(gctx, idx, pentry);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get partition info\n");
		goto exit;
	}

exit:
	if (sctx)
		storage_close(sctx);
	if (gctx)
		gpt_parse_final(gctx);
	free(buf);

	return res;
}

static int is_slot_active(char slot, bool *is_active)
{
	int res;
	struct gpt_part_info pentry;

	res = get_slot_pentry(slot, &pentry);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get the partition entry of the slot\n");
		return res;
	}

	*is_active = pentry.attribute & ACTIVE;

	return FCSERR_OK;
}

int ab_set_active(char new_active_slot)
{
	/* We will use boot-partition as reference for finding active slot */
	char boot_part[] = "boot_x";
	/* Active boot partition lun */
	char lun_boot_a[] = "x";
	/* Inactive boot partition lun */
	char lun_boot_i[] = "x";
	/* Get active slot */
	char get_active_slot[] = "x";
	uint8_t *buf = NULL;
	struct storage_ctx *sctx = NULL;
	ssize_t ssize, buf_sz, device_size, data_write;
	struct gpt_ctx *gctx = NULL;
	struct gpt_part_info *pentry = NULL;
	/* New active partition entry */
	struct gpt_part_info *new_a = NULL;
	/* New inactive partition entry */
	struct gpt_part_info *new_i = NULL;
	int res, idx, idy, nbr_of_part;
	/* Index of active and inactive boot-partition respectively */
	int idx_boot_a, idx_boot_i;
	bool is_new_slot_active;
	uint8_t inactive_guid[GPT_PART_ID_SIZE];
	char *pname;
	size_t plen;
	off_t off;

	res = ab_get_active(get_active_slot);
	if (res == -FCSERR_ESLOT) {
		FCS_LOG_WRN("No active slot found, \n");
		FCS_LOG_WRN("Treat the new slot as active\n");
		is_new_slot_active = true;
	} else if (res == FCSERR_OK) {
		/*
		 * If is_new_slot_active is true then the new_active_slot
		 * is active prior to active_slot cmd.
		 */
		res = is_slot_active(new_active_slot, &is_new_slot_active);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get active slot, %d\n", res);
			return res;
		}
	} else {
		FCS_LOG_ERR("Failed to get active slot, %d\n", res);
		return res;
	}

	/* Find out where new active boot partition is */
	boot_part[strlen(boot_part) - 1] = new_active_slot;
	res = fcs_get_lun_and_index_of_partition(boot_part, strlen(boot_part),
			lun_boot_a, strlen(lun_boot_a), &idx_boot_a);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get partition index of boot_a\n");
		return res;
	}

	/* Find out where new inactive boot partition is */
	boot_part[strlen(boot_part) - 1] = (new_active_slot == 'a') ? 'b' : 'a';
	res = fcs_get_lun_and_index_of_partition(boot_part, strlen(boot_part),
			lun_boot_i, strlen(lun_boot_i), &idx_boot_i);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get partition index of boot_b\n");
		return res;
	}

	/*
	 * Sanity check that we support layout of partitions. Currently we
	 * do not support switching of guid_type or gpt attribute between
	 * two or more devices or LUNs.
	 */
	if (lun_boot_a[0] != lun_boot_i[0]) {
		FCS_LOG_ERR(
			"Switching between multiple LUNs/devices not supported\n");
		return -FCSERR_ENIMP;
	}

	/* Open the lun we are interested in and read the gpt info */
	sctx = storage_open_by_name(NULL, lun_boot_a);
	if (!sctx) {
		FCS_LOG_ERR("Failed to open device/LUN %s\n", lun_boot_a);
		return -FCSERR_EIO;
	}

	/* Get gpt size */
	res = storage_get_gpt_info(sctx, lun_boot_a, NULL, &buf_sz);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read GPT table on LUN/device %s\n",
				lun_boot_a);
		goto exit;
	}

	buf = malloc(buf_sz);
	if (!buf) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	/* Get gpt */
	res = storage_get_gpt_info(sctx, lun_boot_a, buf, &buf_sz);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read GPT table\n");
		goto exit;
	}

	/* Get sector size of flash */
	ssize = storage_get_ssz(sctx);
	if (ssize < 0) {
		FCS_LOG_ERR("Failed to get sector size\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	/* Parse GPT header */
	gctx = gpt_parse_init(buf, buf_sz, ssize);
	if (!gctx) {
		FCS_LOG_ERR("Failed to parse partition table\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	/* Read all partitions into pentry */
	nbr_of_part = gpt_get_nbr_part(gctx);
	pentry = malloc(sizeof(struct gpt_part_info)*nbr_of_part);
	for (idx = 0; idx < nbr_of_part; idx++) {
		res = gpt_get_part_info_byidx(gctx, idx, &pentry[idx]);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get partition info\n");
			goto exit;
		}
	}

	/*
	 * If is_new_slot_active is true then new active is already active and
	 * therefore new inactive is inactive.
	 * This is done to figure out which guid_type is the inactive one.
	 */
	if (is_new_slot_active)
		memcpy(inactive_guid, pentry[idx_boot_i].guid_type,
				GPT_PART_ID_SIZE);
	else
		memcpy(inactive_guid, pentry[idx_boot_a].guid_type,
				GPT_PART_ID_SIZE);

	/*
	 * Loop through all partitions and toggle all slots according to the new
	 * active configuration.
	 */
	for (idx = 0; idx < nbr_of_part; idx++) {
		pname = pentry[idx].name;
		plen = strlen(pname);

		/* If partition does not have slots, skip to next */
		if (pname[plen - 2] != '_' || pname[plen - 1] !=
				new_active_slot)
			continue;

		for (idy = 0; idy < nbr_of_part; idy++) {
			/* Look for the other slot */
			if (strncmp(pname, pentry[idy].name, plen - 1))
				continue;
			if (pentry[idy].name[plen - 1] == new_active_slot)
				continue;
			/*
			 * Pair located, idx point at new active, idy point at
			 * new inactive.
			 */
			new_a = &pentry[idx];
			new_i = &pentry[idy];

			/*
			 * Check if new inactive slot has inactive guid. If the
			 * inactive guid is found in new inactive slot then we
			 * have to assume that the guid_types for respective
			 * partition is already correct, or the partition table
			 * is broken which we cannot detect at this point.
			 */
			if (memcmp(inactive_guid, new_i->guid_type,
						GPT_PART_ID_SIZE)) {
				/*
				 * The new inactive slot does not have the
				 * inactive guid_type so we switch.
				 */
				res = gpt_switch_guid_type_byidx(buf, buf_sz,
						idx, new_a, idy, new_i, ssize);
				if (res) {
					FCS_LOG_ERR("Failed to swap guid\n");
					goto exit;
				}
			}

			/* Update attributes for new active partition */
			new_a->attribute = (new_a->attribute | ACTIVE) &
				(~SUCCESSFUL & ~UNBOOTABLE);

			/* If boot partition then set some more bits */
			if (!strncmp("boot_", new_a->name, strlen("boot_")))
				new_a->attribute |= (PRIORITY | MAX_RETRY);

			/*  Clear active bit for new inactive partition */
			new_i->attribute = new_i->attribute & ~ACTIVE;

			/* Set attributes for new active partition */
			res = gpt_set_attribute_byidx(buf, buf_sz, idx, ssize,
					new_a->attribute);
			if (res) {
				FCS_LOG_ERR("Failed to update guid_type\n");
				goto exit;
			}

			/* Set attributes for new inactive partition */
			res = gpt_set_attribute_byidx(buf, buf_sz, idy, ssize,
					new_i->attribute);
			if (res) {
				FCS_LOG_ERR("Failed to update guid_type\n");
				goto exit;
			}
			break;
		}
	}

	/* Get device size in sectors */
	device_size = pu_get_part_size(sctx)/ssize;
	if (device_size <= 0) {
		FCS_LOG_ERR("Failed to get device size\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	/* Recalculates GPT header crc and partition table crc */
	res = gpt_patch_primary_gpt(buf, buf_sz, device_size, ssize);
	if (res) {
		FCS_LOG_ERR("Patching primary gpt fail\n");
		goto exit;
	}

	/* Move file pointer to flash start */
	off = storage_lseek(sctx, 0, STORAGE_SEEK_SET);
	if (off < 0) {
		FCS_LOG_ERR("Failed to seek (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}

	/* Write primary partition table to flash */
	data_write = storage_write(sctx, buf, buf_sz);
	if (data_write < 0) {
		FCS_LOG_ERR(
			"Failed to write primary ptable (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}

	/* This will convert the primary gpt in buf to the secondary gpt */
	res = gpt_get_secondary_gpt(buf, buf_sz, device_size, ssize);
	if (res) {
		FCS_LOG_ERR("Failed to get secondary gpt: (%d)\n", res);
		goto exit;
	}

	/* Move file pointer to end of flash (minus the gpt size) */
	off = storage_lseek(sctx, device_size*ssize - buf_sz, STORAGE_SEEK_SET);
	if (off < 0) {
		FCS_LOG_ERR("Failed to seek (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}

	/* Write secondary partition table to flash */
	data_write = storage_write(sctx, buf, buf_sz);
	if (data_write < 0) {
		FCS_LOG_ERR(
			"Failed to set secondary ptable (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}

	/* Slot a is in lun 1 and slot b is in lun 2 */
	res = storage_set_bootdevice(sctx, (new_active_slot == 'a') ? 1 : 2);
	if (res)
		FCS_LOG_ERR("Failed to set bootdevice\n");

exit:
	if (gctx)
		gpt_parse_final(gctx);
	if (sctx)
		storage_close(sctx);
	free(buf);
	free(pentry);

	return res;
}

int ab_get_active(char *active_slot)
{
	int res = FCSERR_OK;
	bool is_active;

	if (!active_slot) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	/* Check if 'a' is the active slot. Return if it is. */
	*active_slot = 'a';
	res = is_slot_active(*active_slot, &is_active);
	if (res != FCSERR_OK)
		goto err;
	if (is_active)
		return res;

	/* Check if 'b' is the active slot. Return if it is. */
	*active_slot = 'b';
	res = is_slot_active(*active_slot, &is_active);
	if (res != FCSERR_OK)
		goto err;
	if (is_active)
		return res;

	/*
	 * If neither 'a' nor 'b' are active slots, return error
	 * and '?' for active_slot.
	 */
	res = -FCSERR_ESLOT;

err:
	*active_slot = '?';
	return res;
}

int ab_get_retry_count(char slot, int *retry_count)
{
	int res = FCSERR_OK;
	struct gpt_part_info pentry;

	res = get_slot_pentry(slot, &pentry);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get the partition entry of the slot\n");
		return res;
	}

	*retry_count = (pentry.attribute & MAX_RETRY) >>
		SLOT_ATTR_MAX_RETRY_BIT;

	return FCSERR_OK;
}

int ab_get_unbootable(char slot, bool *unbootable)
{
	int res;
	struct gpt_part_info pentry;

	res = get_slot_pentry(slot, &pentry);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get the partition entry of the slot\n");
		return res;
	}

	*unbootable = pentry.attribute & UNBOOTABLE;

	return FCSERR_OK;
}

int ab_get_successful(char slot, bool *successful)
{
	int res;
	struct gpt_part_info pentry;

	res = get_slot_pentry(slot, &pentry);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to get the partition entry of the slot\n");
		return res;
	}

	*successful = pentry.attribute & SUCCESSFUL;

	return FCSERR_OK;
}

int ab_reset_slot(char *slot)
{
	int res;
	struct storage_ctx *sctx = NULL;
	ssize_t ssize, buf_sz, device_size, data_write;
	struct gpt_ctx *gctx = NULL;
	uint8_t *buf = NULL;
	struct gpt_part_info pentry;
	size_t plen;
	char *pname;
	int idx, nbr_of_part;
	off_t off;

	if (!slot || strlen(slot) != 1) {
		FCS_LOG_ERR("Bad input parameters\n");
		return -FCSERR_EINVAL;
	}

	/*
	 * Open the lun we are interested in and read the gpt info.
	 * Here we assume that all slot partitions are located on lun 0,
	 * so this needs updating in the case of slots being spread out
	 * on two or more devices.
	 */
	sctx = storage_open_by_name(NULL, "0");
	if (!sctx) {
		FCS_LOG_ERR("Failed to open device/LUN 0\n");
		return -FCSERR_EIO;
	}

	/* Get gpt size */
	res = storage_get_gpt_info(sctx, "0", NULL, &buf_sz);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read GPT table on LUN/device 0\n");
		goto exit;
	}

	buf = malloc(buf_sz);
	if (!buf) {
		FCS_LOG_ERR("Out of memory\n");
		res = -FCSERR_ENOMEM;
		goto exit;
	}

	/* Get gpt */
	res = storage_get_gpt_info(sctx, "0", buf, &buf_sz);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to read GPT table\n");
		goto exit;
	}

	/* Get sector size of flash */
	ssize = storage_get_ssz(sctx);
	if (ssize < 0) {
		FCS_LOG_ERR("Failed to get sector size\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	/* Parse GPT header */
	gctx = gpt_parse_init(buf, buf_sz, ssize);
	if (!gctx) {
		FCS_LOG_ERR("Failed to parse partition table\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	/* Get number of partitions */
	nbr_of_part = gpt_get_nbr_part(gctx);

	for (idx = 0; idx < nbr_of_part; idx++) {
		res = gpt_get_part_info_byidx(gctx, idx, &pentry);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to get partition info\n");
			goto exit;
		}

		pname = pentry.name;
		plen = strlen(pname);

		/* If partition does not have slots, skip to next */
		if (pname[plen - 2] != '_' || pname[plen - 1] != slot[0])
			continue;

		/*
		 * Clear successful bit, clear unbootable bit and reset retry
		 * counter to max.
		 */
		pentry.attribute = (pentry.attribute | MAX_RETRY) &
				(~SUCCESSFUL & ~UNBOOTABLE);
		res = gpt_set_attribute_byidx(buf, buf_sz, idx, ssize,
				pentry.attribute);
		if (res) {
			FCS_LOG_ERR("Failed to update guid_type\n");
			goto exit;
		}
	}

	/* Get device size in sectors */
	device_size = pu_get_part_size(sctx)/ssize;
	if (device_size <= 0) {
		FCS_LOG_ERR("Failed to get device size\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	/* Recalculates GPT header crc and partition table crc */
	res = gpt_patch_primary_gpt(buf, buf_sz, device_size, ssize);
	if (res) {
		FCS_LOG_ERR("Patching primary gpt fail\n");
		goto exit;
	}

	/* Move file pointer to flash start */
	off = storage_lseek(sctx, 0, STORAGE_SEEK_SET);
	if (off < 0) {
		FCS_LOG_ERR("Failed to seek (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}

	/* Write primary partition table to flash */
	data_write = storage_write(sctx, buf, buf_sz);
	if (data_write < 0) {
		FCS_LOG_ERR(
			"Failed to write primary ptable (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}

	/* This will convert the primary gpt in buf to the secondary gpt */
	res = gpt_get_secondary_gpt(buf, buf_sz, device_size, ssize);
	if (res) {
		FCS_LOG_ERR("Failed to get secondary gpt: (%d)\n", res);
		goto exit;
	}

	/* Move file pointer to end of flash (minus the gpt size) */
	off = storage_lseek(sctx, device_size*ssize - buf_sz, STORAGE_SEEK_SET);
	if (off < 0) {
		FCS_LOG_ERR("Failed to seek (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}

	/* Write secondary partition table to flash */
	data_write = storage_write(sctx, buf, buf_sz);
	if (data_write < 0) {
		FCS_LOG_ERR(
			"Failed to set secondary ptable (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}


exit:
	free(buf);
	if (gctx)
		gpt_parse_final(gctx);
	if (sctx)
		storage_close(sctx);

	return res;
}

