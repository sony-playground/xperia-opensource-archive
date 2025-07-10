/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "crc32.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "fcslog.h"
#include "fcserr.h"

/*
 * Macros and defines
 */
#define P_32 0xEDB88320L

int update_crc_32(
	void *crc_tab32, uint32_t crc_in, uint8_t c, uint32_t *p_crc_out)
{
	uint32_t tmp;
	uint32_t long_c;
	uint32_t *table32;

	if (NULL == p_crc_out || NULL == crc_tab32) {
		FCS_LOG_ERR("invalid input param\n");
		return -FCSERR_EINVAL;
	}

	table32 = (uint32_t *)crc_tab32;
	long_c = (uint32_t) (0x000000ffL &  c);
	tmp = crc_in ^ long_c;
	*p_crc_out = (crc_in >> 8) ^ table32[tmp & 0xff];

	return FCSERR_OK;
}

void deinit_crc32_tab(void *crc_tab32)
{
	free(crc_tab32);
}

void *init_crc32_tab(void)
{
	uint32_t i;
	uint32_t j;
	uint32_t crc;
	uint32_t *crc_tab32;

	crc_tab32 = (uint32_t *)malloc(256 * sizeof(uint32_t));
	if (NULL == crc_tab32) {
		FCS_LOG_ERR("failed to allocate memory\n");
		return NULL;
	}

	for (i = 0; i < 256; i++) {
		crc = (uint32_t) i;

		for (j = 0; j < 8; j++) {
			if (crc & 0x00000001L)
				crc = (crc >> 1) ^ P_32;
			else
				crc = crc >> 1;
		}

		crc_tab32[i] = crc;
	}

	return (void *)crc_tab32;
}
