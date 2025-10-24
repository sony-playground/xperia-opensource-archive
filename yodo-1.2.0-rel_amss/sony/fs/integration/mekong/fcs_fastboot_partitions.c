/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "fcs_fastboot_partitions.h"

/*
 * List of partitions allowed to flash or erase
 * on a fused and unlocked device
 */
const char *allowed_ptns[] = {
				"boot_a",
				"boot_b",
				"system_a",
				"system_b",
				"vendor_a",
				"vendor_b",
				"oem_a",
				"oem_b",
				"userdata"};

const int no_of_allowed_ptns = sizeof(allowed_ptns) /
				sizeof(allowed_ptns[0]);

/* This is taken from tama partition layout from fsconfig
 * but, it will be replaced with the appropriate list.
 */
const char *ext4_ptns[] = {"LTALabel",
				"vendor_a",
				"vendor_b",
				"system_a",
				"system_b",
				"appslog",
				"diag",
				"Qnovo",
				"fsmetadata",
				"userdata"};

const int no_of_ext4_ptns = sizeof(ext4_ptns) /
				sizeof(ext4_ptns[0]);
