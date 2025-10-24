/*
 * Copyright 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

/* @file boot_ramdump_target.h
 *
 * Function declarations to detect and init target specific ramdump regions.
 *
 */

#ifndef _BOOT_RAMDUMP_TARGET_H
#define _BOOT_RAMDUMP_TARGET_H

#include "../../SomcPkg/Platform/SomcQcomCmnPkg/Include/Library/XResetReasonLibVendor.h"
#include <boot_framework.h>

#define RAMDUMPER_KERNEL_BASE DDR_MEM_BASE
#define DEBUG_MEM_BASE 0xFFC00000
#define DEBUG_MEM_SIZE (1UL << CONVERT_TO_MB_SHIFT)
#define RAMDUMP_MEM_DESC_BASE DEBUG_MEM_BASE
#define PSTORE_MEM_BASE (DEBUG_MEM_BASE + DEBUG_MEM_SIZE)
#define PSTORE_MEM_SIZE (1UL << CONVERT_TO_MB_SHIFT)

#define DDR_MEM_BASE (UINT64)DDR_MEM_BASE_1
#define DDR_MEM_SIZE (UINT64)DDR_MEM_SIZE_1
#define DDR_MEM_BASE2 (UINT64)DDR_MEM_BASE_2
#define DDR_MEM_SIZE2 (UINT64)DDR_MEM_SIZE_2

#define DUMP_MIN_SIZE (UINT64)(0x100000000)

static const uint32 ramdump_fail_reasons[] =
{
  VENDOR_RREASON_RD_DECFAIL_NO_TL,
  VENDOR_RREASON_RD_DECFAIL_PART_TL,
  VENDOR_RREASON_RD_CRASH_HWWD,
  VENDOR_RREASON_RD_NO_SPACE,
  VENDOR_RREASON_REBOOT_RD_CRASH,
  VENDOR_RREASON_REBOOT_RD_APPERR,
  VENDOR_RREASON_RD_EARLY_CRASH_HWWD,
};

static const uint32 ramdump_reasons[] =
{
  VENDOR_RREASON_CRASH,
  VENDOR_RREASON_CLEAR,
};

#define RAMDUMP_FAIL_REASON_ARRAY_SIZE (sizeof(ramdump_fail_reasons)/ \
                                            sizeof(ramdump_fail_reasons[0]))

#define RAMDUMP_REASONS_ARRAY_SIZE (sizeof(ramdump_reasons)/ \
                                            sizeof(ramdump_reasons[0]))

void boot_ramdump_target_init(boot_handle config_context_handle);
void boot_ramdump_target_secure_init(void);
void boot_ramdump_failed_target_init(void);

#endif /* _BOOT_RAMDUMP_TARGET_H */
