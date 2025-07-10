/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef INCLUSION_GUARD_SONY_BOOT_SERVICE_DETECT
#define INCLUSION_GUARD_SONY_BOOT_SERVICE_DETECT
#include "sony_boot_context.h"
#include "xboot_pal_types.h"


enum reset_state_t {
	NO_RESET_DET, /* No reset detected */
	/* Reset detected but keys were released before vibration triggered */
	RESET_DET_VIBRATION_NOT_DONE,
	/* Reset detected and restart-vibration indicated, used to bypass
	 * longpress
	 */
	RESET_DET_VIBRATION_DONE
};

/**
 * Use the parsed boot configuration to determine if a forced reset/shutdown
 * sequence is requested, and act accordingly.
 * This function will not return if keys are pressed long enough to trigger
 * forced shutdown.
 *
 * @param[in] ctx XBoot context.
 * @param[out] reset_state, the detected reset state
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int sony_boot_service_reset_detect(
	struct xboot_ctx *ctx, enum reset_state_t *reset_state);

/**
 * Use the provided platform API and parsed boot configuration to determine
 * if a valid service mode is requested.
 *
 * @param[in] ctx XBoot context.
 * @param[in] warmboot_reason The current warmboot reason
 *
 * @returns #FCSERR_OK for success, else an error occurred.
 */
int sony_boot_service_detect(struct xboot_ctx *ctx,
	const enum xbpal_warmboot_t warmboot_reason);

#endif /* INCLUSION_GUARD_SONY_BOOT_SERVICE_DETECT */
