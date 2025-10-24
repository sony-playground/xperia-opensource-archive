/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcs_fastboot_partitions.h"

/*
 * List of partitions allowed to flash or erase
 * on a fused and unlocked device
 */
const char *allowed_ptns[] = {"boot_a",
			      "boot_b",
			      "odmdtbo_a",
			      "odmdtbo_b",
			      "system_a",
			      "system_b",
			      "vendor_a",
			      "vendor_b",
			      "oem_a",
			      "oem_b",
			      "userdata",
			      "vbmeta_a",
			      "vbmeta_b"};

const int no_of_allowed_ptns = sizeof(allowed_ptns) /
				sizeof(allowed_ptns[0]);

const char *ext4_ptns[] = {"appslog",
			   "diag",
			   "ltalabel",
			   "nvcfg",
			   "vendor_a",
			   "vendor_b",
			   "persist",
			   "protect1",
			   "protect2",
			   "system_a",
			   "system_b",
			   "userdata"};

const int no_of_ext4_ptns = sizeof(ext4_ptns) /
				sizeof(ext4_ptns[0]);
