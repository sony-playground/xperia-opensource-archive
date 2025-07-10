/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_GPT_H_
#define FCS_GPT_H_

#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#define GPT_PART_ID_SIZE (16)
#define GPT_MAX_NAME_SIZE (72)

struct gpt_ctx;

struct gpt_part_info {
	uint8_t guid_type[GPT_PART_ID_SIZE];
	uint8_t guid_id[GPT_PART_ID_SIZE];
	uint64_t start;
	uint64_t end;
	uint64_t attribute;
	char name[GPT_MAX_NAME_SIZE / 2];
};

struct gpt_ctx *gpt_parse_init_head(uint8_t *buf, ssize_t buf_sz,
	uint32_t ssize);
struct gpt_ctx *gpt_parse_init(uint8_t *buf, ssize_t buf_sz, uint32_t ssize);
void gpt_parse_final(struct gpt_ctx *tbl);

/* get the size of the partition table, negative values indicate error code */
int gpt_get_parttbl_size(struct gpt_ctx *tbl);

/* get number of partitions, negative values indicate error code */
int gpt_get_nbr_part(struct gpt_ctx *tbl);

int gpt_get_part_info_byname(
	struct gpt_ctx *tbl, const char *name, struct gpt_part_info *inf);
int gpt_get_part_info_byidx(
	struct gpt_ctx *tbl, const int idx, struct gpt_part_info *inf);
int gpt_get_secondary_gpt(
		uint8_t *buf, ssize_t buf_sz, ssize_t part_size_in_sectors,
		ssize_t ssize);
int gpt_patch_primary_gpt(uint8_t *buf, ssize_t buf_sz,
		ssize_t part_size_in_sectors, ssize_t ssize);
int gpt_switch_guid_type_byidx(
		uint8_t *buf, ssize_t buf_sz, const int idx1,
		struct gpt_part_info *inf1, const int idx2,
		struct gpt_part_info *inf2, ssize_t ssize);
int gpt_set_attribute_byidx(
		uint8_t *buf, ssize_t buf_sz, const int idx, ssize_t ssize,
		uint64_t attr);
#endif
