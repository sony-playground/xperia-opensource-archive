/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _KS_ENTRY_DATA_H_
#define _KS_ENTRY_DATA_H_

#include "ks_certificate.h"
#include "ks_publickey.h"

/* Dependencies */
enum ks_entry_data_pr {
	KS_ENTRY_DATA_PR_NOTHING,
	KS_ENTRY_DATA_PR_CERTIFICATE,
	KS_ENTRY_DATA_PR_PUBLICKEY
};

/* KeyStoreEntryData */
struct ks_entry_data {
	enum ks_entry_data_pr present;
	union {
		struct ks_certificate certificate;
		struct ks_publickey publickey;
	} choice;
};

#endif /* _KS_ENTRY_DATA_H_ */

