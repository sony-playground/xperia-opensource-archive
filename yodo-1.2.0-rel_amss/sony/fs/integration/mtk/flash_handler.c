/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fcserr.h"
#include "fcslog.h"
#include "write_image.h"

#define ID_NUM1 12
#define ID_NUM2 8
#define MAX_BL_NUM 8
#define BROM_CONFIG_SIZE  0x800

/* EMMC header */
#define SDMMC_HEADER_SIZE       (0x200)
#define SDMMC_HEADER_ADDR  0x0
#define SDMMC_HEADER_IDENT "EMMC_BOOT"
#define SDMMC_HEADER_VER   1
#define SDMMC_HEADER_RW_SZ SDMMC_HEADER_SIZE

/* boot region layout block */
#define BR_IDENT          "BRLYT"
#define BR_VER            1
#define BR_DEV_ADDR       0x800
#define MR_DEV_ADDR       0x40800
#define BL_EXIST_MAGIC    0x42424242
#define BL_EMMC_DEV       0x5
#define BL_TYPE_BL        0x1
#define BL_ATTR           0x1

/* BROM boot descriptor block */
struct bl_descr_t {
	uint32_t m_bl_exist_magic;
	uint16_t m_bl_dev;
	uint16_t m_bl_type;
	uint32_t m_bl_begin_dev_addr;
	uint32_t m_bl_boundary_dev_addr;
	uint32_t m_bl_attributes;
};

struct br_layout_t {
	char m_identifier[ID_NUM2];
	uint32_t m_ver;
	uint32_t m_boot_region_dev_addr;
	uint32_t m_main_region_dev_addr;
	struct bl_descr_t m_bl_desc[MAX_BL_NUM];
};

/* MTK BROM header block */
struct sdmmc_header_t {
	char m_identifier[ID_NUM1];
	uint32_t m_ver;
	uint32_t m_dev_rw_unit;
};


static int write_brom_header(struct storage_ctx *sctx, uint32_t *offset)
{
	int ret = FCSERR_OK;
	uint8_t *buffer = NULL;
	struct sdmmc_header_t *sdmmc_header = NULL;
	struct br_layout_t *br_layout = NULL;

	buffer = malloc(BROM_CONFIG_SIZE);
	if (buffer == NULL) {
		FCS_LOG_ERR("Out of memory\n");
		return -FCSERR_ENOMEM;
	}

	memset(buffer, 0xFF, BROM_CONFIG_SIZE/2);
	memset(buffer + BROM_CONFIG_SIZE/2, 0x00, BROM_CONFIG_SIZE/2);
	sdmmc_header = (struct sdmmc_header_t *)buffer;

	/* Create a SDMMC header block */
	strncpy(sdmmc_header->m_identifier,
			SDMMC_HEADER_IDENT,
			sizeof(sdmmc_header->m_identifier));
	sdmmc_header->m_ver = SDMMC_HEADER_VER;
	sdmmc_header->m_dev_rw_unit = SDMMC_HEADER_SIZE;

	/* Create the boot region block layout */
	br_layout = (struct br_layout_t *)(buffer + SDMMC_HEADER_SIZE);
	memset(br_layout->m_identifier, 0x00, sizeof(struct br_layout_t));
	strncpy(br_layout->m_identifier, BR_IDENT,
			sizeof(br_layout->m_identifier));
	br_layout->m_ver = BR_VER;
	br_layout->m_boot_region_dev_addr = BR_DEV_ADDR;
	br_layout->m_main_region_dev_addr = MR_DEV_ADDR;
	br_layout->m_bl_desc[0].m_bl_exist_magic = BL_EXIST_MAGIC;
	br_layout->m_bl_desc[0].m_bl_dev = BL_EMMC_DEV;
	br_layout->m_bl_desc[0].m_bl_type = BL_TYPE_BL;
	br_layout->m_bl_desc[0].m_bl_begin_dev_addr = BR_DEV_ADDR;
	br_layout->m_bl_desc[0].m_bl_boundary_dev_addr = MR_DEV_ADDR;
	br_layout->m_bl_desc[0].m_bl_attributes = BL_ATTR;

	/* Write BROM header to partition */
	ret = write_image(sctx, buffer, 0, BROM_CONFIG_SIZE);
	if (ret != FCSERR_OK)
		FCS_LOG_ERR("Failed to write image\n");

	*offset = BROM_CONFIG_SIZE;

	free(buffer);
	return ret;
}

int pre_flash_handler(struct storage_ctx *sctx, const char *partition,
		uint32_t *offset)
{
	int ret = FCSERR_OK;

	/* On MTK platform add BROM header before preloader image */
	if (strncmp(partition, PRELOADER, strlen(PRELOADER)) == 0) {
		ret = write_brom_header(sctx, offset);
		if (ret != FCSERR_OK)
			FCS_LOG_ERR("Failed to create BROM header\n");
	} else
		*offset = 0;

	return ret;
}

