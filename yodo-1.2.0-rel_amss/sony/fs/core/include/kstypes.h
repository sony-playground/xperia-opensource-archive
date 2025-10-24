/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef KS_TYPES_H_
#define KS_TYPES_H_

#include <stdint.h>

#define KS_KEY_TYPE_PUB_KEY		(0)
#define KS_KEY_TYPE_PRIV_KEY		(1)
#define KS_KEY_TYPE_CERT		(2)


struct ks_ctx;
struct ks_io_handle;

struct ksstore_blob {
	uint32_t      type;	      /* PUB_KEY|PRIV_KEY|CERT		   */
	uint32_t      domain;         /* Domain SONY|XCS|NONE		   */
	uint32_t      size;	      /* Size of keyblob			   */
	uint8_t*      blob;           /* Raw  data			   */
};

#endif
