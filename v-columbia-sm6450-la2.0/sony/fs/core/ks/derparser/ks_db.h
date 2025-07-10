/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _KS_DB_H_
#define _KS_DB_H_

#include "ks_entry.h"

/* KeyStoreDB */
struct ks_db {
	struct {
		int count;
		struct ks_entry **array;
	} list;
};

#endif /* _KS_DB_H_ */

