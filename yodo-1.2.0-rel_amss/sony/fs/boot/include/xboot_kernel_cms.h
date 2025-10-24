/*
 * Copyright (c) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef XBOOT_KERNEL_CMS_H_
#define XBOOT_KERNEL_CMS_H_

#include "sony_boot_context.h"

#define CMS_MIN_SZ 4

/**
 * @brief Get the cms length
 *
 *
 * @param[in] cms_hdr Pointer to a cms message which contains at least 4 bytes.
 * @param[out] cms_len The cms length.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int xboot_get_cms_len(uint8_t *cms_hdr, uint16_t *cms_len);

/**
 * @brief Verify the cms signature of a kernel image
 *
 *
 * @param[in] kernel_buf Buffer containing the kernel image data.
 * @param[in] kernel_len The size of the kernel image.
 * @param[in] cms_buf Buffer containing the cms signature data.
 * @param[in] cms_len The length of the cms signature.
 * @param[in] usage Usage of the kernel cms.
 * @param[in] boot_ctx The boot context.
 *
 * @returns #FCSERR_OK for success, else an  error occurred.
 */
int xboot_verify_kernel_cms(uint8_t *kernel_buf, size_t kernel_len,
		uint8_t *cms_buf, uint16_t cms_len,
		uint32_t usage, struct xboot_ctx *boot_ctx);
#endif
