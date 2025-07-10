/*
 * Copyright 2023 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

#include "fcs_fastboot_partitions.h"

/*
 * List of partitions allowed to flash or erase
 * on a fused and unlocked device
 */
const char *allowed_ptns[] = {"boot_a",
                                "boot_b",
                                "dtbo_a",
                                "dtbo_b",
                                "oem_a",
                                "oem_b",
                                "userdata",
                                "vbmeta_a",
                                "vbmeta_b",
                                "recovery_a",
                                "recovery_b",
                                "vendor_boot_a",
                                "vendor_boot_b",
                                "vbmeta_system_a",
                                "vbmeta_system_b",
                                "super"};

const int no_of_allowed_ptns = sizeof(allowed_ptns) /
                                sizeof(allowed_ptns[0]);

/* This is taken from tama partition layout from fsconfig
 * but, it will be replaced with the appropriate list.
 */
const char *ext4_ptns[] = {"LTALabel",
                                "appslog",
                                "diag",
                                "super",
                                "userdata",
                                "rdlog"};

const int no_of_ext4_ptns = sizeof(ext4_ptns) /
                                sizeof(ext4_ptns[0]);
