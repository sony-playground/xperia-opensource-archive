/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef INCLUSION_GUARD_SONY_BOOT_CONFIG_PARSER
#define INCLUSION_GUARD_SONY_BOOT_CONFIG_PARSER

#include "sony_boot_context.h"

#define MISC_TA_MAXIMUM_PUBLIC_UNIT_ID 65535

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
int bootconfig_parse(struct xboot_ctx *context,
	const uint8_t *config_data, const size_t config_size);

#endif /* INCLUSION_GUARD_SONY_BOOT_CONFIG_PARSER */

