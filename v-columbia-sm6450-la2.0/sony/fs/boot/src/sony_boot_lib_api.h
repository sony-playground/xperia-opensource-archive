/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
/**
 * @defgroup sony_boot_lib Sony Boot library
 * @{
 * @brief Interface to set up and take generic Sony decisions for the boot
 *
 * This module defines the API for making Sony related decisions for the boot.
 * Example of such decisions are whether fastboot operations are allowed, or
 * which service mode the boot should enter.
 *
 * @file sony_boot_lib_api.h
 */
#ifndef INCLUSION_GUARD_SONY_BOOT_DECISIONS
#define INCLUSION_GUARD_SONY_BOOT_DECISIONS

#include <stdlib.h>
#include <stdbool.h>
#include "sony_boot_context.h"


/**
 * @brief Initialize the part of the XBoot library that makes Sony
 * related decisions for the boot.
 *
 *
 * @param[in] ctx XBoot context.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int sony_boot_init(struct xboot_ctx *ctx);

/**
 * @brief Take Sony boot related decisions and return them.
 *
 * It is required that the #sony_boot_init has executed successfully).
 * The function will populate a structure with information that will
 * be used at various points in the bootflow.
 *
 * Reset detection, service mode detection and Sony specific startup
 * indications are all managed by this function.
 *
 *
 * @param[in] ctx XBoot context.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int sony_boot_make_decisions(struct xboot_ctx *ctx);

/**
 * @brief Returns when long press management is finalised or shuts down.
 *
 * This function should be called before the boot leaves the current runtime
 * environment in order to ensure that all startup indications have finished
 * processing.
 *
 * @param[in] ctx XBoot context.
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int sony_boot_finalize_longpress(struct xboot_ctx *ctx);

#endif /* INCLUSION_GUARD_SONY_BOOT_DECISIONS */
/** @}*/

