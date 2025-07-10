/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef FCS_PROTOCOL_H_
#define FCS_PROTOCOL_H_

struct protocol;
struct loader_ctx;

struct protocol *prot_init(void);

void prot_final(struct protocol *ctx);

int prot_receive_cmd(struct protocol *ctx);

int prot_send_response(struct protocol *ctx);

int prot_proc_cmd(struct loader_ctx *ctx);

#endif
