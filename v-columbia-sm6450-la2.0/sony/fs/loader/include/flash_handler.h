/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FLASH_HANDLER_H
#define FLASH_HANDLER_H

/**
 * Called before each partition is flashed to allow custom handling
 * of the flash data. Used in e.g. MTK to prepend the preloader
 * with the BROM config header.
 *
 * @param sctx storage context.
 * @param partition the partition about to be flashed
 * @param offset out parameter that contains offset into partition
 *               where the image data should be written.
 */
int pre_flash_handler(struct storage_ctx *sctx, const char *partition,
		uint32_t *offset);

#endif
