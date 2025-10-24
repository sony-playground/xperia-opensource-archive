/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_WRITE_IMAGE_H_
#define FCS_WRITE_IMAGE_H_

#include <stdint.h>
#include <stdbool.h>
#include "storage.h"

/*
 * struct storage_ctx *sctx	Pointer to storage context
 * uint8_t *buf			Pointer to buffer we work with
 * uint32_t offset		Offset in the partition
 * size_t bytes_read		Amount of data to write to storage
 */
int write_image(struct storage_ctx *sctx,
		uint8_t *buf, uint32_t offset,
		size_t bytes_read);

#endif
