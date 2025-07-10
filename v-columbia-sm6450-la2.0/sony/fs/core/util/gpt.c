/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "gpt.h"
#include "fcs_endian.h"
#include "fcslog.h"
#include "fcserr.h"
#include "crc32.h"

#include <stdbool.h>
#include <string.h>

#define GPT_REVISION (0x00000100)
#define GPT_ENTRY_SIZE (128)
#define GPT_HEADER_SIZE (92)
#define GPT_MAGIC_SIZE (8)
#define PARTITION_LIST_OFFSET_512 (33)
#define PARTITION_LIST_OFFSET_4096 (4)
#define PARTITION_LIST_SIZE_512 (33)
#define PARTITION_LIST_SIZE_4096 (5)
#define GPT_PART_ENTRY_ATTR_OFFSET (48)
#define GPT_LBA_LST_EMMC (34)
#define GPT_LBA_LST_UFS (6)

struct gpt_header {
	char magic[GPT_MAGIC_SIZE];
	uint32_t revision;
	uint32_t hdr_size;
	uint32_t hdr_crc;
	uint32_t reserved;
	uint64_t lba_cur;
	uint64_t lba_bkp;
	uint64_t lba_1st;
	uint64_t lba_lst;
	uint8_t disk_guid[GPT_PART_ID_SIZE];
	uint64_t lba_part_entries;
	uint32_t nbr_part;
	uint32_t size_part_entry;
	uint32_t pa_crc;
};

struct gpt_ctx {
	uint32_t ssize; /* sector size */
	struct gpt_header hdr;
	uint8_t *pent; /* partition entries */
};

static int gpt_calc_partition_list_crc(uint8_t *buf, ssize_t buf_sz,
		uint32_t *crc);
static int gpt_calc_header_crc(uint8_t *buf, ssize_t buf_sz, uint32_t *crc);

static int gpt_parse_header(struct gpt_header *hdr, uint8_t *buf,
	ssize_t buf_sz)
{
	if (hdr == NULL || buf == NULL) {
		FCS_LOG_ERR("invalid param, (%x, %x)\n", hdr, buf);
		return -FCSERR_EINVAL;
	}

	if (buf_sz < (ssize_t)sizeof(struct gpt_header)) {
		FCS_LOG_ERR("Provided buffer too small, (%d < %d)\n",
			buf_sz, sizeof(struct gpt_header));
		return -FCSERR_EINVAL;
	}

	hdr->revision = read_be_u32(buf + 8);
	hdr->hdr_size = read_le_u32(buf + 0xc);
	hdr->hdr_crc = read_le_u32(buf + 0x10);
	hdr->lba_cur = read_le_u64(buf + 0x18);
	hdr->lba_bkp = read_le_u64(buf + 0x20);
	hdr->lba_1st = read_le_u64(buf + 0x28);
	hdr->lba_lst = read_le_u64(buf + 0x30);
	memcpy(hdr->disk_guid, buf + 0x38, GPT_PART_ID_SIZE);
	hdr->lba_part_entries = read_le_u64(buf + 0x48);
	hdr->nbr_part = read_le_u32(buf + 0x50);
	hdr->size_part_entry = read_le_u32(buf + 0x54);
	hdr->pa_crc = read_le_u32(buf + 0x58);

	/* sanity check some known fields */
	if (hdr->revision != GPT_REVISION ||
	    hdr->size_part_entry != GPT_ENTRY_SIZE ||
	    hdr->hdr_size != GPT_HEADER_SIZE) {
		FCS_LOG_ERR("invalid gpt header (%x, %x, %x)\n",
			hdr->revision, hdr->size_part_entry, hdr->hdr_size);
		return -FCSERR_EINVAL;
	}
	return FCSERR_OK;
}

static uint8_t *gpt_get_partition_byname(
	struct gpt_ctx *tbl, const char *name)
{
	unsigned int i;
	uint32_t nent = 0;
	uint8_t *pent = tbl->pent;
	char pname8[GPT_MAX_NAME_SIZE / 2];

	for (; nent < tbl->hdr.nbr_part; nent++) {
		/* convert name from UTF-16  */
		for (i = 0; i < sizeof(pname8); i++)
			pname8[i] = (pent + 56)[i * 2];

		/* check if name matches */
		if (!strncmp(name, pname8, strlen(name)) &&
		    !pname8[strlen(name)])
			return pent;

		pent += tbl->hdr.size_part_entry;
	}

	return NULL;
}

static uint64_t gpt_get_partition_start(uint8_t *part)
{
	return read_le_u64(part + 32);
}

static uint64_t gpt_get_partition_end(uint8_t *part)
{
	return read_le_u64(part + 40);
}

static uint64_t gpt_get_partition_attribute(uint8_t *part)
{
	return read_le_u64(part + GPT_PART_ENTRY_ATTR_OFFSET);
}

struct gpt_ctx *gpt_parse_init_head(uint8_t *buf, ssize_t buf_sz,
	uint32_t ssize)
{
	int ret;
	struct gpt_ctx *tbl;

	tbl = malloc(sizeof(struct gpt_ctx));
	if (!tbl) {
		FCS_LOG_ERR("malloc failed!\n");
		return NULL;
	}
	tbl->ssize = ssize;
	tbl->pent = NULL;

	/* init header */
	ret = gpt_parse_header(&tbl->hdr, buf + ssize, buf_sz - ssize);
	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("parse header failed!\n");
		free(tbl);
		return NULL;
	}

	return tbl;
}

struct gpt_ctx *gpt_parse_init(uint8_t *buf, ssize_t buf_sz, uint32_t ssize)
{
	struct gpt_ctx *tbl;
	ssize_t required_buf_sz;

	tbl = gpt_parse_init_head(buf, buf_sz, ssize);
	if (!tbl)
		return NULL; /* error log done in gpt_parse_init_head */

	required_buf_sz = 2 * ssize +
		tbl->hdr.nbr_part * tbl->hdr.size_part_entry;

	if (buf_sz < required_buf_sz) {
		FCS_LOG_ERR("Provided buffer too small, (%d < %d)\n",
			buf_sz, required_buf_sz);
		free(tbl);
		return NULL;
	}

	/* init patrition entries buffer */
	tbl->pent = malloc(tbl->hdr.nbr_part * tbl->hdr.size_part_entry);
	if (!tbl->pent) {
		FCS_LOG_ERR("malloc failed!\n");
		free(tbl);
		return NULL;
	}
	memcpy(tbl->pent, buf + (2 * ssize),
	       tbl->hdr.nbr_part * tbl->hdr.size_part_entry);

	return tbl;
}

void gpt_parse_final(struct gpt_ctx *tbl)
{
	free(tbl->pent);
	free(tbl);
}

int gpt_get_nbr_part(struct gpt_ctx *tbl)
{
	if (!tbl) {
		FCS_LOG_ERR("invalid param\n");
		return -FCSERR_EINVAL;
	}

	return tbl->hdr.nbr_part;
}

int gpt_get_parttbl_size(struct gpt_ctx *tbl)
{
	if (!tbl) {
		FCS_LOG_ERR("invalid param\n");
		return -FCSERR_EINVAL;
	}

	return tbl->hdr.nbr_part * tbl->hdr.size_part_entry;
}


int gpt_get_part_info_byname(
	struct gpt_ctx *tbl, const char *name, struct gpt_part_info *inf)
{
	uint8_t *part_info;

	if (!tbl || !name || !inf) {
		FCS_LOG_ERR("invalid param\n");
		return -FCSERR_EINVAL;
	}

	part_info = gpt_get_partition_byname(tbl, name);
	if (!part_info) {
		/* this might not be a "hard" error, i.e. dont spam error log */
		FCS_LOG_WRN("could not find partition %s\n", name);
		return -FCSERR_ENODEV;
	}

	memcpy(inf->guid_type, part_info, 16);
	memcpy(inf->guid_id, part_info + 16, 16);
	inf->start = gpt_get_partition_start(part_info);
	inf->end = gpt_get_partition_end(part_info);
	inf->attribute = gpt_get_partition_attribute(part_info);
	strlcpy(inf->name, name, GPT_MAX_NAME_SIZE / 2);

	return FCSERR_OK;
}

int gpt_get_part_info_byidx(
	struct gpt_ctx *tbl, const int idx, struct gpt_part_info *inf)
{
	uint8_t *pent;
	unsigned int i;

	if (!tbl || !inf) {
		FCS_LOG_ERR("invalid param\n");
		return -FCSERR_EINVAL;
	}

	if (idx < 0 || (uint32_t)idx >= tbl->hdr.nbr_part) {
		FCS_LOG_ERR("idx (%d) out of range, %d partitions available\n",
			idx, tbl->hdr.nbr_part);
		return -FCSERR_EINDEX;
	}

	pent = tbl->pent + idx * tbl->hdr.size_part_entry;

	memcpy(inf->guid_type, pent, 16);
	memcpy(inf->guid_id, pent + 16, 16);
	inf->start = gpt_get_partition_start(pent);
	inf->end = gpt_get_partition_end(pent);
	inf->attribute = gpt_get_partition_attribute(pent);
	/* convert name from UTF-16  */
	for (i = 0; i < GPT_MAX_NAME_SIZE / 2; i++)
		inf->name[i] = (pent + 56)[i * 2];

	return FCSERR_OK;
}

static int gpt_set_guid_type_byidx(
		uint8_t *buf, ssize_t buf_sz, const int idx,
		struct gpt_part_info *inf, ssize_t ssize, uint8_t *guid_type)
{
	int offset;

	if (buf == NULL || buf_sz == 0 || idx < 0 || inf == NULL) {
		FCS_LOG_ERR("Bad input parameters\n");
		return -FCSERR_EINVAL;
	}

	/* Update partition info and write to buffer */
	memcpy(inf->guid_type, guid_type, GPT_PART_ID_SIZE);
	offset = (ssize * 2) + (idx * GPT_ENTRY_SIZE);
	memcpy(buf + offset, &inf->guid_type, GPT_PART_ID_SIZE);

	return FCSERR_OK;
}

int gpt_switch_guid_type_byidx(
		uint8_t *buf, ssize_t buf_sz, const int idx1,
		struct gpt_part_info *inf1, const int idx2,
		struct gpt_part_info *inf2, ssize_t ssize)
{
	int res;
	uint8_t temp_guid[GPT_PART_ID_SIZE];

	if (!buf || buf_sz == 0 || !inf1 || !inf2 || ssize == 0) {
		FCS_LOG_ERR("Bad input parameters\n");
		return -FCSERR_EINVAL;
	}

	memcpy(temp_guid, inf2->guid_type, GPT_PART_ID_SIZE);
	res = gpt_set_guid_type_byidx(buf, buf_sz, idx2, inf2, ssize,
			inf1->guid_type);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to set guid_type of %s\n", inf2->name);
		return res;
	}
	res = gpt_set_guid_type_byidx(buf, buf_sz, idx1, inf1, ssize,
			temp_guid);
	if (res != FCSERR_OK) {
		FCS_LOG_ERR("Failed to set guid_type of %s\n", inf1->name);
		return res;
	}

	return FCSERR_OK;
}

int gpt_set_attribute_byidx(
		uint8_t *buf, ssize_t buf_sz, const int idx, ssize_t ssize,
		uint64_t attr)
{
	ssize_t offset;

	if (!buf) {
		FCS_LOG_ERR("Bad input parameters\n");
		return -FCSERR_EINVAL;
	}

	offset = (ssize * 2) + (idx * GPT_ENTRY_SIZE) +
		GPT_PART_ENTRY_ATTR_OFFSET;

	if (buf_sz < (offset + (ssize_t)sizeof(uint64_t))) {
		FCS_LOG_ERR("Buffer too small\n");
		return -FCSERR_ENOBUFS;
	}

	memcpy(buf + offset, &attr, sizeof(uint64_t));

	return FCSERR_OK;
}

int gpt_patch_primary_gpt(uint8_t *buf, ssize_t buf_sz,
		ssize_t part_size_in_sectors, ssize_t ssize)
{
	int ret;
	struct gpt_ctx *pgpt = NULL;
	ssize_t all_part_size;

	if (buf == NULL || ssize == 0 || buf_sz < ssize + GPT_HEADER_SIZE) {
		FCS_LOG_ERR("Input parameters fail\n");
		return -FCSERR_EINVAL;
	}

	pgpt = gpt_parse_init(buf, buf_sz, ssize);
	if (pgpt == NULL) {
		FCS_LOG_ERR("Failed to parse primary gpt\n");
		return -FCSERR_EINVAL;
	}

	all_part_size = pgpt->hdr.nbr_part * pgpt->hdr.size_part_entry;

	/* Write backup partition location */
	memset(&buf[ssize] + 16, 0, 4);
	pgpt->hdr.lba_bkp = part_size_in_sectors - 1;
	memcpy(&buf[ssize] + 32, &pgpt->hdr.lba_bkp, 8);
	/* Write last usable block in partition */
	if (ssize == 512) {
		pgpt->hdr.lba_lst = part_size_in_sectors - GPT_LBA_LST_EMMC;
	} else if (ssize == 4096) {
		pgpt->hdr.lba_lst = part_size_in_sectors - GPT_LBA_LST_UFS;
	} else {
		ret = -FCSERR_EINVAL;
		goto exit;
	}

	memcpy(&buf[ssize] + 48, &pgpt->hdr.lba_lst, 8);
	all_part_size = pgpt->hdr.nbr_part * pgpt->hdr.size_part_entry;

	/* Write partition list crc */
	ret = gpt_calc_partition_list_crc(&buf[2*ssize],
			all_part_size, &pgpt->hdr.pa_crc);
	if (ret) {
		FCS_LOG_ERR("Failed to calculate crc for partition table\n");
		goto exit;
	}
	memcpy(&buf[ssize] + GPT_HEADER_SIZE - 4, &pgpt->hdr.pa_crc, 4);

	/* Write gpt header crc */
	ret = gpt_calc_header_crc(&buf[ssize], GPT_HEADER_SIZE,
			&pgpt->hdr.hdr_crc);
	if (ret)
		FCS_LOG_ERR("Failed to calculate GPT header crc\n");
	memcpy(&buf[ssize] + 16, &pgpt->hdr.hdr_crc, 4);

exit:
	gpt_parse_final(pgpt);

	return ret;
}

int gpt_get_secondary_gpt(
		uint8_t *buf, ssize_t buf_sz, ssize_t part_size_in_sectors,
		ssize_t ssize)
{
	int ret = FCSERR_OK;
	uint8_t *part_buf = NULL;
	struct gpt_ctx *sgpt = NULL;
	ssize_t all_part_size;

	sgpt = gpt_parse_init(buf, buf_sz, ssize);
	if (sgpt == NULL) {
		FCS_LOG_ERR("Failed to parse secondary gpt\n");
		ret = -FCSERR_EINVAL;
		goto exit;
	}

	all_part_size = sgpt->hdr.nbr_part * sgpt->hdr.size_part_entry;
	sgpt->hdr.revision = 0x10000;
	memcpy(sgpt->hdr.magic, "EFI PART", GPT_MAGIC_SIZE);
	sgpt->hdr.lba_cur = part_size_in_sectors - 1;
	sgpt->hdr.lba_bkp = 1;

	if (ssize == 512)
		sgpt->hdr.lba_part_entries = part_size_in_sectors -
			PARTITION_LIST_OFFSET_512;
	else if (ssize == 4096)
		sgpt->hdr.lba_part_entries = sgpt->hdr.lba_cur -
			PARTITION_LIST_OFFSET_4096;
	else /* Unsupported sector size */
		ret = -FCSERR_EINVAL;

	if (ret != FCSERR_OK) {
		FCS_LOG_ERR("Unsupported sector size\n");
		goto exit;
	}

	sgpt->hdr.hdr_crc = 0;

	ret = gpt_calc_partition_list_crc(&buf[2*ssize],
			all_part_size, &sgpt->hdr.pa_crc);
	ret = gpt_calc_header_crc((uint8_t *)&sgpt->hdr, GPT_HEADER_SIZE,
			&sgpt->hdr.hdr_crc);

	/* store away the partitions */
	part_buf = malloc(all_part_size);
	if (part_buf == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		ret = -FCSERR_ENOMEM;
		goto exit;
	}

	memcpy(part_buf, buf + 2*ssize, all_part_size);

	/* Clear buffer */
	memset(buf, 0, buf_sz);

	/* Copy partition table to buf */
	memcpy(buf + ssize, part_buf, all_part_size);
	if (ssize == 512)
		memcpy(buf + PARTITION_LIST_SIZE_512 * ssize, &sgpt->hdr,
				GPT_HEADER_SIZE);
	else if (ssize == 4096)
		memcpy(buf + PARTITION_LIST_SIZE_4096 * ssize, &sgpt->hdr,
				GPT_HEADER_SIZE);

exit:
	free(part_buf);
	if (sgpt)
		gpt_parse_final(sgpt);

	return ret;
}

static int gpt_calc_partition_list_crc(uint8_t *buf, ssize_t buf_sz,
		uint32_t *crc)
{
	void *crc_hdl = NULL;
	int i = 0;
	int res = FCSERR_OK;

	*crc = 0 ^ 0xffffffffL;
	if (buf == NULL || buf_sz == 0) {
		FCS_LOG_ERR("Buffer uninitialized\n");
		return -FCSERR_EINVAL;
	}
	/* Calculate CRC over partition list */
	crc_hdl = init_crc32_tab();
	for (i = 0; i < buf_sz; i++)
		res = update_crc_32(crc_hdl, *crc, buf[i], crc);
	deinit_crc32_tab(crc_hdl);
	*crc = *crc ^ 0xffffffffL;

	return res;
}

static int gpt_calc_header_crc(uint8_t *buf, ssize_t buf_sz, uint32_t *crc)
{
	void *crc_hdl = NULL;
	int i = 0;
	int res = FCSERR_OK;

	if (buf == NULL || buf_sz == 0) {
		FCS_LOG_ERR("Buffer uninitialized\n");
		return -FCSERR_EINVAL;
	}

	crc_hdl = init_crc32_tab();
	*crc = 0 ^ 0xffffffffL;
	for (i = 0; i < GPT_HEADER_SIZE; i++) {
		/* Do not include the CRC (if any) in CRC calculation */
		if (i >= 16 && i <= 19)
			res = update_crc_32(crc_hdl, *crc, 0, crc);
		else
			res = update_crc_32(crc_hdl, *crc, buf[i], crc);
	}
	deinit_crc32_tab(crc_hdl);
	*crc = *crc ^ 0xffffffffL;

	return res;
}
