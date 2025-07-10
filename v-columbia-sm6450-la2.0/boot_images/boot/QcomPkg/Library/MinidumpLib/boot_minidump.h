#ifndef BOOT_MINIDUMP_H
#define BOOT_MINIDUMP_H
/*=============================================================================

                               Boot minidump
                               Header File
GENERAL DESCRIPTION
  This file provides the APIs for minidump feature

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

Copyright (c) 2017, 2020-2021 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
08/26/21   rama    added md_ss in boot_add_minidump_region
08/09/21   rama    Added md_ss for xbl_sc and boot
06/22/21   rama    Changes to enable minidump
03/30/20   aus     Added new functions for Boot minidump
12/21/17   aus     Removed packed attribute
12/12/17   aus     Updated structures as packed
10/12/17   aus     Updated structures as per design
01/17/17   bd      Initial version

=============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include "comdef.h"
#include "boot_error_if.h"

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/

#define MD_REVISION                       1
#define SBL_MINIDUMP_SMEM_ID              602
#define MD_SHARED_IMEM_BASE               (SHARED_IMEM_BASE + 0xB88)
#define MD_REGION_NAME_LENGTH             16

#define MD_REGION_VALID                   ('V' << 24 | 'A' << 16 | 'L' << 8 | 'I' << 0)
#define MD_REGION_INVALID                 ('I' << 24 | 'N' << 16 | 'V' << 8 | 'A' << 0)
#define MD_REGION_INIT                    ('I' << 24 | 'N' << 16 | 'I' << 8 | 'T' << 0)
#define MD_REGION_NOINIT                  0

#define MD_SS_TOC_MAGIC                   (0 << 24 | 'T' << 16 | 'O' << 8 | 'C' << 0)
#define MD_SS_ENCR_REQ                    (0 << 24 | 'Y' << 16 | 'E' << 8 | 'S' << 0)
#define MD_SS_ENCR_NOTREQ                 (0 << 24 | 0 << 16 | 'N' << 8 | 'R' << 0)
#define MD_SS_ENCR_DONE                   ('D' << 24 | 'O' << 16 | 'N' << 8 | 'E' << 0)
#define MD_SS_ENCR_NOT_DONE               0
#define MD_SS_ENCR_START                  ('S' << 24 | 'T' << 16 | 'R' << 8 | 'T' << 0)
#define MD_SS_ENABLED                     ('E' << 24 | 'N' << 16 | 'B' << 8 | 'L' << 0)
#define MD_SS_DISABLED                    ('D' << 24 | 'S' << 16 | 'B' << 8 | 'L' << 0)

/* Macros defined to match AES-256 CTR mode encryption */
#define MD_AES_KEY_SIZE                   32
#define MD_AES_IV_SIZE                    16
#define MD_AES_MAC_SIZE                   32
#define MD_HMAC_KEY_SIZE                  32
#define MD_RSA_KEY_LEN                    256 // 2048bits

//sizes in bytes
#define MD_VERSION_SIZE 2
#define MD_AES_PLUS_HMAC_KEY_PLUS_VERSION_SIZE    (MD_AES_KEY_SIZE + MD_HMAC_KEY_SIZE + MD_VERSION_SIZE)

static uint8  ALIGN(32)           minidump_version[MD_VERSION_SIZE] = {0x00,0x01};// format is MSB : LSB -> Major Version : Minor Version

typedef  enum
{
  MD_SS_HLOS       = 0,
  MD_SS_QSEE       = 1,
  MD_SS_QHEE       = 2,
  MD_SS_MPSS       = 3,
  MD_SS_CNSS       = 4,
  MD_SS_LPASS      = 5,
  MD_SS_SLPI       = 6,
  MD_SS_CSS        = 7,
  MD_SS_SP         = 8,
  MD_SS_AOP        = 9,
  MD_SS_HLOS_GVM1  = 10,
  MD_SS_HLOS_GVM2  = 11,
  MD_SS_CPUCP      = 12,
  MD_SS_TME        = 13,
  MD_SS_BOOT       = 14,
  MD_SS_XBL_SC     = 15,
  MD_SS_UEFI       = 16,
  MD_SS_SHRM       = 17,
  MD_SS_MAX        = 18,
  MD_SS_UNKNOWN    = 0x7FFFFFFF,
}md_subsys_type;

/* SMEM region struct */
typedef struct
{
  uint8     region_name[MD_REGION_NAME_LENGTH];
  uint32    seq_num;        /* provision to allow unique naming */
  uint32    md_valid;       /* To dump or not */
  uint64    region_base_address;
  uint64    region_size;
}  md_ss_region;

/* minidump SMEM SubSystem region */
typedef struct  /* SS SMEM ToC struct */
{
   uint32       md_ss_toc_init;
   uint32       md_ss_enable_status;
   uint32       encryption_status;
   uint32       encryption_required;
   uint32       ss_region_count; /*region count */
   uint64       md_ss_smem_regions_baseptr;
}  md_ss_toc;

/* SMEM struct minidump_smem_global region */
typedef struct
 {
   uint32       md_toc_init;
   uint32       md_revision;
   uint32       md_enable_status;
   md_ss_toc    md_ss_toc[MD_SS_MAX];
}  md_global_toc;


/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/
boolean boot_minidump_init(uint32 md_ss, uint32 md_ss_enable_status, uint32 encryption_required, uint32 encryption_status);
bl_error_boot_type  add_minidump_regions(void *handle, void *ramdump_table_handle);
boolean boot_add_minidump_region(uint32 md_ss, char rg_name[MD_REGION_NAME_LENGTH], uint64 rg_base_addr, uint64 rg_size);
md_ss_toc* boot_md_get_subsystem_toc(uint32 ss);

#endif  /* BOOT_MINIDUMP_H */
