/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _KS_MAIN_H_
#define _KS_MAIN_H_

#include <string.h>
#include <stdint.h>

#include "ks_db.h"

/* KeyStore */
struct ks_main {
	long version;
	uint32_t xcs;
	struct ks_db db;
};

#endif /* _KS_MAIN_H_ */

