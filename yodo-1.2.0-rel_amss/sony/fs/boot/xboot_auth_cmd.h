/*
 * Copyright (c) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_XBOOT_AUTH_CMD_H_
#define FCS_XBOOT_AUTH_CMD_H_

#include "sony_boot_context.h"

int xboot_gen_nonce(void);

int xboot_auth_cmd(struct xboot_ctx *ctx);

#endif
