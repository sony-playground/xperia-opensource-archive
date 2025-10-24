/*
 * Copyright 2021 Sony Corporation
 * All rights, including trade secret rights, reserved.
 */
#ifndef INCLUSION_GUARD_SONY_BOOT_CUSTOMER_ID
#define INCLUSION_GUARD_SONY_BOOT_CUSTOMER_ID

#include "sony_boot_context.h"

/**
 * Parse the supplied bootconfig data and store the result in the context.
 *
 * The provided databuffers can be released by the caller when this
 * function returns.
 *
 * @param[in] context XBoot context.
 * @param[in] config_data Boot config data from Misc TA.
 * @param[in] config_size Size of the boot config data.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int bootconfig_append_customer_id(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size);

int cmdline_append_customer_id(struct xboot_ctx *boot_context,
	const uint8_t *ta_buf, const size_t ta_Size);

#endif /* INCLUSION_GUARD_SONY_BOOT_CUSTOMER_ID */

