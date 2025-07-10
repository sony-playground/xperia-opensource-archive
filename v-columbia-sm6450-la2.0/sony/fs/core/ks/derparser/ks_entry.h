/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _KS_ENTRY_H_
#define _KS_ENTRY_H_

#include "ks_entry_data.h"

/* KeyStoreEntry */
struct ks_entry {
	long domain;
	struct ks_entry_data data;
};

#endif /* _KS_ENTRY_H_ */

