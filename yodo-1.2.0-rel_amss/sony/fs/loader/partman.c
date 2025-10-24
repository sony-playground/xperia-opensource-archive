/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "core.h"
#include "partman.h"
#include "fcslog.h"
#include "fcserr.h"
#include "gpt.h"
#include "storage.h"
#include "sparse.h"
#include "protocol_util.h"
#include <string.h>
#include "fcs_sbu.h"
#include <errno.h>

#include <stdio.h>

/*
 * This function returns true if both new_guid_id and old_guid_id are found
 * in the list of boot partitions subject to safe boot upgrade.
 *
 * Those partitions should not be erased.
 */
static bool is_boot_partition(
		const uint8_t *new_guid_id, const uint8_t *old_guid_id)
{
	int i;
	bool new_is_boot = false, old_is_boot = false;

	if (new_guid_id == NULL || old_guid_id == NULL) {
		FCS_LOG_ERR("Invalid input parameters\n");
		return false;
	}

	for (i = 0; i < num_boot_partitions; i++) {
		if (boot_partitions[i].key_length != GPT_PART_ID_SIZE)
			continue;
		if (boot_partitions[i].key != NULL &&
				memcmp(boot_partitions[i].key, new_guid_id,
					GPT_PART_ID_SIZE) == 0)
			new_is_boot = true;
		if (boot_partitions[i].key != NULL &&
				memcmp(boot_partitions[i].key, old_guid_id,
					GPT_PART_ID_SIZE) == 0)
			old_is_boot = true;
		/* Both found already, bail out */
		if (old_is_boot && new_is_boot)
			break;
	}

	return (new_is_boot && old_is_boot);
}

static int partman_erase_range(
	struct storage_ctx *sctx, off_t start, long long count)
{
	int ret;
	off_t offset;

	FCS_LOG_INF("erase: %llx %llx\n", start, count);

	offset = storage_lseek(sctx, start, STORAGE_SEEK_SET);
	if (offset != start) {
		FCS_LOG_ERR("seek failed (errno=%d)\n", errno);
		return -FCSERR_EIO;
	}

	ret = storage_erase(sctx, count, STORAGE_ERASE_NORMAL);
	if (ret != FCSERR_OK)
		FCS_LOG_ERR("erase failed (%d)\n", ret);

	return ret;
}

int partman_erase_sector(int lun, ssize_t start, ssize_t end, bool secure_erase)
{
	int res = FCSERR_OK;
	char clun[3];
	struct storage_ctx *sctx;
	int flags = 0;
	ssize_t ssize, psize;
	ssize_t bytes_to_erase;
	off_t offset;

	/*
	 * lun can only be a value between 0 and 7, but it will be set to
	 * -1 in the case of it being omitted by caller.
	 */
	if (start > end || lun < -1 || lun > 7) {
		FCS_LOG_ERR("Bad input parameters\n");
		return -FCSERR_EINVAL;
	}

	snprintf(clun, sizeof(clun), "%d", lun);
	sctx = storage_open_by_name(NULL, (lun != -1) ? clun : NULL);
	if (sctx == NULL) {
		FCS_LOG_ERR("%s does not exist\n", clun);
		return -FCSERR_EINVAL;
	}

	/* get sector size */
	ssize = storage_get_ssz(sctx);
	if (ssize < 0) {
		FCS_LOG_ERR("get sector size falied\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	/* lun/device size in sectors */
	psize = pu_get_part_size(sctx)/ssize;
	if (start > psize || end > psize) {
		FCS_LOG_ERR("Bad input parameters\n");
		res = -FCSERR_EINVAL;
		goto exit;
	}

	if (secure_erase)
		flags |= STORAGE_ERASE_SECURE;

	bytes_to_erase = (end - start + 1)*ssize;

	/* Skip to the place where erase should start */
	offset = storage_lseek(sctx, (off_t)start*ssize, STORAGE_SEEK_SET);
	if (offset != start*ssize) {
		FCS_LOG_ERR("Failed to move file pointer (errno=%d)\n", errno);
		res = -FCSERR_EIO;
		goto exit;
	}
	res = storage_erase(sctx, bytes_to_erase, flags);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("erase failed (%d)\n", res);
		goto exit;
	}

exit:
	if (sctx)
		storage_close(sctx);
	return res;
}

int partman_erase(const char *pname, bool secure_erase)
{
	int res = FCSERR_OK;
	ssize_t psize;
	int flags = 0;
	struct storage_ctx *sctx;

	sctx = storage_open_by_name(NULL, pname);
	if (sctx == NULL) {
		FCS_LOG_ERR("Storage does not exist\n");
		if (pname)
			FCS_LOG_ERR("Storage name: %s\n", pname);
		return -FCSERR_ENOENT;
	}

	psize = pu_get_part_size(sctx);
	if (psize < 0) {
		FCS_LOG_ERR("IO Error\n");
		res = -FCSERR_EIO;
		goto exit;
	}

	if (secure_erase)
		flags |= STORAGE_ERASE_SECURE;

	res = storage_erase(sctx, psize, flags);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("erase failed (%d)\n", res);
		goto exit;
	}

exit:
	if (sctx)
		storage_close(sctx);
	return res;
}

int partman_erase_overlap(uint8_t *buf, ssize_t buf_sz, const char *lun)
{
	struct gpt_ctx *nctx = NULL; /* new gpt context */
	struct gpt_ctx *octx = NULL; /* old (on flash) gpt context */
	struct storage_ctx *sctx = NULL;
	int ret;
	ssize_t ssize, obuf_size;
	uint8_t *obuf = NULL; /* old gpt on flash */
	int nbr_part;
	int part_size;
	int i;
	struct gpt_part_info ninf;
	struct gpt_part_info oinf;
	off_t offset;

	sctx = storage_open_by_name(NULL, lun);
	if (!sctx) {
		FCS_LOG_ERR("Could not open partition\n");
		return -FCSERR_EINVAL;
	}

	/* get sector size */
	ssize = storage_get_ssz(sctx);
	if (ssize < 0) {
		FCS_LOG_ERR("get sector size falied\n");
		ret = -FCSERR_EIO;
		goto exit;
	}

	/* parse input partition list */
	nctx = gpt_parse_init(buf, buf_sz, ssize);
	if (!nctx) {
		FCS_LOG_ERR("could not parse new partition table\n");
		ret = -FCSERR_EINVAL;
		goto exit;
	}

	/*
	 * read head to find out the size of the whole gpt
	 */
	obuf_size = ssize * 2;
	obuf = malloc(obuf_size);
	if (!obuf) {
		FCS_LOG_ERR("malloc falied\n");
		ret = -FCSERR_ENOMEM;
		goto exit;
	}

	ret = storage_read(sctx, obuf, obuf_size);
	if (ret != obuf_size) {
		FCS_LOG_ERR("read failed (%d)\n", ret);
		if (ret >= 0)
			ret = -FCSERR_EIO;
		goto exit;
	}

	octx = gpt_parse_init_head(obuf, obuf_size, ssize);
	if (!octx) {
		/*
		 * this is currently an error, we need a valid gpt to get to
		 * the loader. This might change later on.
		 */
		FCS_LOG_ERR("could not parse old partition table head\n");
		ret = -FCSERR_EINFOR;
		goto exit;
	}

	part_size = gpt_get_parttbl_size(octx);
	if (part_size < 0) {
		FCS_LOG_ERR("could not retrieve size of partition table\n");
		ret = part_size;
		goto exit;
	}

	/*
	 * read the whole gpt
	 */
	free(obuf);
	obuf_size = ssize * 2 + part_size;
	obuf = malloc(obuf_size);
	if (!obuf) {
		FCS_LOG_ERR("malloc falied\n");
		ret = -FCSERR_ENOMEM;
		goto exit;
	}

	offset = storage_lseek(sctx, 0, STORAGE_SEEK_SET);
	if (offset != 0) {
		FCS_LOG_ERR("seek failed (errno=%d)\n", errno);
		ret = -FCSERR_EIO;
		goto exit;
	}

	ret = storage_read(sctx, obuf, obuf_size);
	if (ret != obuf_size) {
		FCS_LOG_ERR("read failed (%d)\n", ret);
		if (ret >= 0)
			ret = -FCSERR_EIO;
		goto exit;
	}

	gpt_parse_final(octx);
	octx = gpt_parse_init(obuf, obuf_size, ssize);
	if (!octx) {
		/*
		 * this is currently an error, we need a valid gpt to get to
		 * the loader. This might change later on.
		 */
		FCS_LOG_ERR("could not parse old partition table head\n");
		ret = -FCSERR_EINFOR;
		goto exit;
	}

	/*
	 * loop through all partitions
	 * RULE: If partition has changed is will be erased
	 */
	nbr_part = gpt_get_nbr_part(nctx);
	if (nbr_part < 0) {
		FCS_LOG_ERR("failed to get nbr partitions\n");
		goto exit;
	}

	for (i = 0; i < nbr_part; i++) {
		/* get new partition info */
		ret = gpt_get_part_info_byidx(nctx, i, &ninf);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("could not get partition %d\n", i);
			goto exit;
		}

		/* get old partition info */
		ret = gpt_get_part_info_byname(octx, ninf.name, &oinf);
		if (ret == -FCSERR_ENODEV) {
			/*
			 * the partition in the new table is not present on
			 * flash, do erase and move on to next partition.
			 */
			ret = partman_erase_range(
				sctx, ninf.start * ssize,
				(ninf.end - ninf.start + 1) * ssize);
			if (ret != FCSERR_OK) {
				FCS_LOG_ERR("failed to erase %s\n", ninf.name);
				goto exit;
			}
			continue;
		} else if (ret != FCSERR_OK) {
			FCS_LOG_ERR("could not get partition %s\n", ninf.name);
			goto exit;
		}

		/* if partition position is the same continue */
		if (ninf.start == oinf.start && ninf.end == oinf.end)
			continue;

		/* Do not erase if both partitions are boot partitions */
		if (is_boot_partition(ninf.guid_id, oinf.guid_id))
			continue;

		ret = partman_erase_range(
			sctx, ninf.start * ssize,
			(ninf.end - ninf.start + 1) * ssize);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("failed to erase %s\n", ninf.name);
			goto exit;
		}
	}

	/* all done */
	ret = FCSERR_OK;

exit:
	free(obuf);
	if (sctx)
		storage_close(sctx);
	if (nctx)
		gpt_parse_final(nctx);
	if (octx)
		gpt_parse_final(octx);

	return ret;
}

int partman_patch_primary_gpt(uint8_t *buf, ssize_t buf_sz, const char *lun)
{
	int ret = FCSERR_OK;
	struct storage_ctx *sctx = NULL;
	ssize_t part_size_in_sectors, ssize;

	if (buf == NULL || buf_sz == 0) {
		FCS_LOG_ERR("Buffer uninitialized\n");
		return -FCSERR_EINVAL;
	}

	sctx = storage_open_by_name(NULL, lun);
	if (sctx == NULL) {
		FCS_LOG_ERR("Failed to open storage\n");
		if (lun)
			FCS_LOG_ERR("%s does not exist\n", lun);
		return -FCSERR_EINVAL;
	}

	/* get sector size */
	ssize = storage_get_ssz(sctx);
	if (ssize < 0) {
		FCS_LOG_ERR("get sector size falied\n");
		ret = -FCSERR_EIO;
		goto exit;
	}

	part_size_in_sectors = pu_get_part_size(sctx)/ssize;
	if (part_size_in_sectors <= 0) {
		FCS_LOG_ERR("IO Error\n");
		ret = -FCSERR_EIO;
		goto exit;
	}

	ret = gpt_patch_primary_gpt(buf, buf_sz, part_size_in_sectors, ssize);
	if (ret < 0) {
		FCS_LOG_ERR("Patching primary gpt fail\n");
		ret = -FCSERR_EINVAL;
		goto exit;
	}

exit:
	storage_close(sctx);

	return ret;
}

int partman_prepare_secondary_gpt(struct storage_ctx *rdctx,
		uint8_t *buf, ssize_t buf_sz, const char *lun)
{
	int ret = FCSERR_OK;
	struct storage_ctx *sctx = NULL;
	ssize_t part_size_in_sectors, ssize;
	uint8_t *hdr = NULL;
	ssize_t gpt_size, hdr_sz = 0;

	if (buf == NULL || buf_sz == 0 || rdctx == NULL) {
		FCS_LOG_ERR("Buffer uninitialized\n");
		return -FCSERR_EINVAL;
	}

	sctx = storage_open_by_name(NULL, lun);
	if (sctx == NULL) {
		FCS_LOG_ERR("Failed to open storage\n");
		if (lun)
			FCS_LOG_ERR("%s does not exist\n", lun);
		return -FCSERR_EINVAL;
	}

	/* get sector size */
	ssize = storage_get_ssz(sctx);
	if (ssize < 0) {
		FCS_LOG_ERR("Get sector size failed\n");
		ret = -FCSERR_EIO;
		goto exit;
	}

	part_size_in_sectors = pu_get_part_size(sctx)/ssize;
	if (part_size_in_sectors <= 0) {
		FCS_LOG_ERR("IO Error\n");
		ret = -FCSERR_EIO;
		goto exit;
	}

	ret = gpt_get_secondary_gpt(buf, buf_sz, part_size_in_sectors, ssize);
	if (ret < 0) {
		FCS_LOG_ERR("Failed to get secondary gpt: (%d)\n", ret);
		goto exit;
	}

	/*
	 * Adding sparse header so that we can flash the secondary gpt header
	 * at the end of the flash/lun.
	 */
	gpt_size = buf_sz/ssize;
	hdr = get_sparse_headers_to_offset(&hdr_sz, ssize,
			part_size_in_sectors - gpt_size, gpt_size);
	if (!hdr) {
		FCS_LOG_ERR("Failed to get sparse headers\n");
		ret = -FCSERR_EINVAL;
		goto exit;
	}
	if (storage_write(rdctx, hdr, hdr_sz) < 0) {
		FCS_LOG_ERR("Failed to write (errno=%d)\n", errno);
		ret = -FCSERR_EIO;
		goto exit;
	}

	if (storage_write(rdctx, buf, buf_sz) < 0) {
		FCS_LOG_ERR("Failed to write (errno=%d)\n", errno);
		ret = -FCSERR_EIO;
	}
exit:
	destroy_sparse_headers(hdr);
	storage_close(sctx);

	return ret;
}

int partman_get_gpt_info(uint8_t *buf, ssize_t *buf_sz, const char *name)
{
	int ret = FCSERR_OK;
	struct storage_ctx *sctx = NULL;

	if (buf_sz == NULL || name == NULL) {
		FCS_LOG_ERR("Faulty input parameters\n");
		return -FCSERR_EINVAL;
	}

	sctx = storage_open_by_name(NULL, NULL);
	if (!sctx) {
		FCS_LOG_ERR("Failed to open device\n");
		return -FCSERR_EIO;
	}

	ret = storage_get_gpt_info(sctx, name, buf, buf_sz);
	if (ret < 0) {
		FCS_LOG_ERR("get gpt info fail: %d)\n", ret);
		ret = -FCSERR_EIO;
		goto exit;
	}

exit:
	storage_close(sctx);

	return ret;
}

int partman_gpt_sanity_check(uint8_t *buf, ssize_t buf_sz, const char *name,
		int *nbr_part)
{
	int ret = FCSERR_OK;
	struct storage_ctx *sctx = NULL;
	struct gpt_ctx *pctx = NULL;
	struct gpt_part_info pentry;
	ssize_t ssize, psize;
	int i;

	if (!nbr_part) {
		FCS_LOG_ERR("Invalid argument\n");
		return -FCSERR_EINVAL;
	}

	sctx = storage_open_by_name(NULL, name);
	if (!sctx) {
		FCS_LOG_ERR("Failed to open storage\n");
		if (name)
			FCS_LOG_ERR("Storage name: %s\n", name);
		return -FCSERR_EIO;
	}

	/* Get sector size */
	ssize = storage_get_ssz(sctx);
	if (ssize < 0) {
		FCS_LOG_ERR("Get sector size failed\n");
		ret = -FCSERR_EIO;
		goto exit;
	}

	/* Get lun/flash size (that is, number of sectors) */
	psize = pu_get_part_size(sctx) / ssize;
	if (psize < 0) {
		FCS_LOG_ERR("Failed to get lun/flash size (nbr of sectors)\n");
		goto exit;
	}

	/* Parse input partition list */
	pctx = gpt_parse_init(buf, buf_sz, ssize);
	if (!pctx) {
		FCS_LOG_ERR("Could not parse new partition table\n");
		ret = -FCSERR_EINVAL;
		goto exit;
	}

	/* Get number of partitions */
	*nbr_part = gpt_get_nbr_part(pctx);
	if (*nbr_part < 0) {
		FCS_LOG_ERR("Failed to get number of partitions\n");
		ret = -FCSERR_EINVAL;
		goto exit;
	}

	for (i = 0; i < *nbr_part; i++) {
		ret = gpt_get_part_info_byidx(pctx, i, &pentry);
		if (ret < 0) {
			FCS_LOG_ERR("Failed to get partition entry. (%d)\n",
				ret);
			goto exit;
		}

		if (pentry.start > (uint64_t)psize ||
				pentry.end > (uint64_t)psize) {
			FCS_LOG_ERR(
				"Partition table doesn't match current provisioning. Partition %s is out of bounds.",
				pentry.name);
			ret = -FCSERR_EPART;
			goto exit;
		}
	}

exit:
	storage_close(sctx);
	if (pctx)
		gpt_parse_final(pctx);

	return ret;
}

int partman_has_slot(const char *part_name, bool *has_slot)
{
	int res = FCSERR_OK;
	struct storage_dir *d;
	struct storage_dirent dent;
	bool found_a = false;
	bool found_b = false;
	bool found_part_name = false;
	size_t part_name_len;

	if (!part_name || !has_slot) {
		FCS_LOG_ERR("Invalid input values\n");
		return -FCSERR_EINVAL;
	}

	part_name_len = strlen(part_name);
	if (part_name_len < 2 || part_name_len > PATH_MAX - 2) {
		FCS_LOG_ERR("Bad partition name %s\n", part_name);
		return -FCSERR_EINVAL;
	}

	*has_slot = false;

	d = storage_opendir(NULL);
	if (d == NULL) {
		FCS_LOG_ERR("Invalid dir\n");
		return -FCSERR_EIO;
	}

	do {
		res = storage_readdir(d, &dent);
		if (res != FCSERR_OK) {
			FCS_LOG_ERR("Failed to read directory (%d)\n", res);
			break;
		}

		/*
		 * In order to distinguish between partitions that exists but
		 * having no slots and partitions that does not exist we keep
		 * track of whether or not input partition is in partition list.
		 */
		if (strncmp(dent.d_name, part_name, part_name_len + 1) == 0)
			found_part_name = true;

		if (strlen(dent.d_name) != part_name_len + 2)
			continue;
		/* Look for <partition>_a or <partition>_b */
		if (strncmp(dent.d_name, part_name, part_name_len) == 0 &&
				dent.d_name[part_name_len] == '_') {
			if (dent.d_name[part_name_len + 1] == 'a')
				found_a = true;
			else if (dent.d_name[part_name_len + 1] == 'b')
				found_b = true;
		}
		if (found_a && found_b) {
			*has_slot = true;
			break;
		}
	} while (dent.d_name[0]);

	res = storage_closedir(d);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("Failed to close directory (%d)\n", res);

	/* Invalid partition, return error */
	if (!found_part_name && !*has_slot) {
		FCS_LOG_WRN("Partition does not exist\n");
		res = -FCSERR_ENOTF;
	}

	return res;
}

int partman_get_slot_count(size_t *slot_count)
{
	int res = FCSERR_OK, ret = FCSERR_OK;
	struct storage_dir *d;
	struct storage_dirent dent;
	char spart[] = "boot_?";
	char i;

	if (slot_count == NULL) {
		FCS_LOG_ERR("Invalid input values\n");
		return -FCSERR_EINVAL;
	}
	*slot_count = 0;

	/* Contains a list of all partitions */
	d = storage_opendir(NULL);
	if (d == NULL) {
		FCS_LOG_ERR("Invalid dir\n");
		return -FCSERR_EIO;
	}

	do {

		/* Go through all partitions in the list */
		/* Returns FCSERR_OK and dent.d_name[0]==0 when no more files */
		ret = storage_readdir(d, &dent);
		if (ret != FCSERR_OK) {
			FCS_LOG_ERR("Failed to read directory (%d)\n", ret);
			/* Exit while loop */
			break;
		}

		/* Look for slots */
		for (i = 'a'; i < 'z'; i++) {
			spart[strlen(spart) - 1] = i;
			if (strncmp(dent.d_name, spart, sizeof(spart)) == 0) {
				(*slot_count)++;
				/* Exit for loop */
				break;
			}
		}
	} while (dent.d_name[0]);

	res = storage_closedir(d);
	if (res != FCSERR_OK)
		FCS_LOG_ERR("Failed to close director (%d)\n", res);

	/*
	 * if ret contains an error, return that since it's the first error
	 * that occurred. Otherwise return res since that is either fine or
	 * contains an error that occurred later.
	 */
	return (ret != FCSERR_OK) ? ret : res;
}
