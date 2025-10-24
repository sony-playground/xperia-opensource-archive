/*
 * Copyright 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

/* @file boot_ramdump.h
 *
 * Function declarations to detect and init ramdump.
 *
 */

#ifndef _BOOT_RAMDUMP_H
#define _BOOT_RAMDUMP_H

#include "boot_comdef.h"
#include "boot_sbl_shared.h"
#include "boot_ramdump_target.h"
#include <boot_config_context.h>

#define MAX_NUM_REGIONS 64
#define MAX_NAME_LEN 32

#define RAW_PARTITION_DUMP_FLAG (1UL << 31)
#define RAW_SDCARD_DUMP_FLAG (1UL << 30)

#define PLATFORM_DUMP_REGION_FLAG 0
#define CORE_DUMP_REGION_FLAG 1
#define REGISTER_DUMP_REGION_FLAG 2

#define RAMDUMP_MEM_DESC_MAGIC 0x42972468
#define RAMDUMP_MEM_DESC_VERSION 0x00010000
#define RAMDUMP_MEM_DESC_SIZE  sizeof(struct ramdump_memdesc)

struct PACK(ramdump_memdesc_header)
{
  /* Signature indicating presence of mem desc*/
  uint32 magic;

  /* Version number */
  uint32 version;

  /* Total number of memory descriptors */
  uint32 num_regions;

  /* Reserved for future usage */
  uint32 reserved;
};

struct PACK(ramdump_memdesc_region)
{
  /* physical address base of the dump region */
  uint64 phys_addr;

 /* Total size of the dump region */
  uint64 size;

  /* Name of the dump region */
  uint8 name[MAX_NAME_LEN];

 /* dump flags to describe the region
  * bit 0-3   : dump type (platform/core/register)
  * bit 4-8   : section index (valid when Non-volatile is set)
  * bit 9-16  : Partition index (valid when Non-volatile is set)
  * bit 17-30 : Reserved
  * bit 31    : Indicates the dump to be stored to raw eMMC partition
  */
  uint32 flags;

 /* reserved for future usage */
  uint32 reserved;
};

struct PACK(ramdump_memdesc)
{
  struct ramdump_memdesc_header hdr;
  struct ramdump_memdesc_region region[MAX_NUM_REGIONS];
};

void boot_ramdump_init(boot_handle config_context_handle);
void boot_ramdump_add_region(struct ramdump_memdesc_region *region);
uint64 boot_ramdump_get_hlos_end_addr(void);
boot_boolean boot_is_ramdump_to_rddata_allowed(boot_handle config_context_handle);

#endif /* _BOOT_RAMDUMP_H */
