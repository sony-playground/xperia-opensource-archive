/*
 * Copyright 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

/* @file boot_ramdump_raw_partition.h
 *
 * Struct declarations to read/write the raw partitions
 *
 */

#ifndef _BOOT_RAMDUMP_RAW_PARTITION_H
#define _BOOT_RAMDUMP_RAW_PARTITION_H


#define MAX_NAME_LEN 32

#define RAW_DUMP_HEADER_VER 0x00010000
#define RAW_DUMP_HEADER_SIGNATURE 0xDEADBEEF
#define RAW_DUMP_HEADER_FAIL  0xDEADF00D
#define RAW_DUMP_HEADER_SIZE  (sizeof(struct boot_raw_partition_dump_header))
#define RAW_DUMP_SECTION_HEADER_SIZE  \
                  (sizeof(struct boot_raw_partition_dump_section_header))

/* Size of data to write for each call to hotplug write(2MB) */
#define RAW_DUMP_WRITE_SIZE (0x200000)

#define RAW_DUMP_VALID_MASK 0x00000001
#define RAW_DUMP_INSUFFICIENT_STORAGE_MASK 0x00000002

#define RAW_DUMP_SECTION_INDEX_FLAG(x) ((uint32)x << 4)

/*
 * This struct represents the header of the whole raw parition ram dump
 */
struct PACK(boot_raw_partition_dump_header)
{
  /* Signature indicating presence of ram dump */
  uint32 signature;

  /* Version number */
  uint32 version;

  /* Total size of the actual dump including headers in bytes */
  uint64 dump_size;

  /* Total size required in bytes */
  uint64 dump_size_required;

  /* Number of sections included in this dump */
  uint32 sections_count;
};

/**
 * This struct represents the header of one ram dump section
 *  size is 64 bytes
 */
struct PACK(boot_raw_partition_dump_section_header)
{
  /* Physical address of the section data */
  uint64 phys_addr;

  /* Byte offset to the start of this section's data */
  uint64 section_offset;

  /* Total size of the section's data in bytes */
  uint64 section_size;

  /* bit 0: dump valid
     bit 1: insufficant storage
     bit 31:2 reserved, should be 0 */
  uint32 validity_flag;

  /* Name of this section */
  uint8 section_name[MAX_NAME_LEN];
};

#endif /* _BOOT_RAMDUMP_RAW_PARTITION_H */
