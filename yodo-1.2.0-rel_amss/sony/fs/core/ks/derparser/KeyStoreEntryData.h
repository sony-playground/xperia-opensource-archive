/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef _KeyStoreEntryData_H_
#define _KeyStoreEntryData_H_

#include "ks_entry_data.h"

/* Dependencies */
typedef enum ks_entry_data_pr KeyStoreEntryData_PR;
#define KeyStoreEntryData_PR_NOTHING KS_ENTRY_DATA_PR_NOTHING
#define KeyStoreEntryData_PR_certificate KS_ENTRY_DATA_PR_CERTIFICATE
#define KeyStoreEntryData_PR_publickey KS_ENTRY_DATA_PR_PUBLICKEY

/* KeyStoreEntryData */
typedef struct ks_entry_data KeyStoreEntryData_t;

#endif /* _KeyStoreEntryData_H_ */

