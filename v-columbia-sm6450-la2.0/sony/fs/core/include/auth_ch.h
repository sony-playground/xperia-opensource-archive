/*
 * Copyright (c) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef AUTH_CH_H_
#define AUTH_CH_H_

/* auth_ch_cmd->magic */
#define AUTH_CH_MAGIC 0x11770112
/* auth_ch_cmd->version */
#define AUTH_CH_VERSION 1

/* auth_ch_cmd->id */
#define AUTH_CH_SAKE_AUTH        0
#define AUTH_CH_RESET_VBMETA_ARB 1
#define AUTH_CH_OEM_LOCK         2

struct auth_ch_cmd {
	uint32_t magic;   /* set to AUTH_CH_MAGIC */
	uint32_t version; /* set to AUTH_CH_VERSION */
	uint32_t id;      /* set to any cmd above */
	uint32_t sz;      /* size of cmd */
} __attribute__ ((packed));

/* AUTH_CH_SAKE_AUTH */
struct auth_ch_auth {
	uint32_t ssn;
	uint32_t rev_str_sz;
	uint32_t response_sz;
} __attribute__ ((packed));

#endif
