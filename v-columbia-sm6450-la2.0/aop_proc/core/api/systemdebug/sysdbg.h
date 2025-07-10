#ifndef _SYSDBG_H
#define _SYSDBG_H

/*=============================================================================
                        SYSDBG MAIN Header File

GENERAL DESCRIPTION
  This module defines functions for intializing SYSDBG functionalities.

    Copyright 2014-2015,2019 by QUALCOMM Technologies, Inc.  All Rights Reserved.
=============================================================================*/

#include "comdef.h"

/* Format versions for dumps exposed to TZ code */
#define DUMP_MAGIC_NUMBER 0x42445953
#define FCM_DUMP_FORMAT_VERSION  0x10


/* All the formats for the various system debug memory dumps */
/* Generic header for every kind of dump supported */

/* Enum for the type of dump entry provided by HLOS */
typedef enum
{
  MSM_DUMP_TYPE_DATA = 0x0,
  MSM_DUMP_TYPE_TABLE = 0x1,
}msm_dump_entry_type;

/* HLOS Dump Structure */
/* Dump Type */
typedef enum
{
  MSM_CPU_REGS_DUMP   = 0x00,
  MSM_CPU_REGS_DUMP2  = 0x10,
  CPU_L1_INST_TLB_DUMP  = 0x20,
  CPU_L1_INST_TLB_DUMP2 = 0x30,
  CPU_L1_DATA_TLB_DUMP  = 0x40,
  CPU_L1_DATA_TLB_DUMP2 = 0x50,
  CPU_L1_ICACHE_DUMP  = 0x60,
  CPU_L1_ICACHE_DUMP2 = 0x70,
  CPU_L1_DCACHE_DUMP  = 0x80,
  CPU_L1_DCACHE_DUMP2 = 0x90,
  MSM_ETM_DUMP = 0xA0,
  _RESERVED2   = 0xB0,
  CPU_L2_DCACHE_DUMP  = 0xC0,
  CPU_L2_ICACHE_DUMP = CPU_L2_DCACHE_DUMP,
  CPU_L3_CACHE_DUMP = 0xD0,
  CPU_L3_ICACHE_DUMP = CPU_L3_CACHE_DUMP,
  CPU_L3_DCACHE_DUMP = CPU_L3_ICACHE_DUMP,
  _RESERVED1 = 0xE0, // Reserved for OCMEM
  MSM_PMIC_DUMP = 0xE4,
  MSM_DUMP_DATA_DBGUI_REG = 0xE5,
  MSM_DATA_DCC_REG_DUMP = 0xE6,
  MSM_DATA_DCC_SRAM_DUMP = 0xE7,
  MSM_GENERIC_DUMP = 0xE8,
  MSM_DUMP_DATA_VSENSE = 0xE9,
  MSM_DATA_RPM_CODE_RAM_DUMP = 0xEA,
  MSM_DATA_SCANDUMP = 0xEB,
  MSM_DATA_RPMhDUMP = 0xEC,
  MSM_POWER_REGS_DUMP = 0xED,
  MSM_DATA_FCMDUMP  = 0xEE,
  MSM_CPU_DEBUG_DUMP = 0xEF,
  MSM_ETB_DUMP = 0xF0,
  MSM_SWAOETB_DUMP = 0xF1,
  MSM_SSCETB_DUMP = 0xF3,
  MSM_LPASSETB_DUMP = 0xF4,
  MSM_TMC_DUMP = 0x100,
  MSM_L2_TLB_DUMP = 0x120,
  MSM_DATA_APPS_SCANDUMP = 0x130,
  MSM_LLCC_DUMP = 0x140,
  MSM_IPA_DUMP = 0x150,
  MSM_DATA_APPS_MHM_SCANDUMP  = 0x161,
  MSM_DATA_NOC_DUMP = 0x162,
  MSM_MAX_DUMP = 0x800,
  MAX_DUMP_TYPES = 0x7FFFFFFF,
}dump_type;



/* Enums for the various clients in the dump table */
typedef enum
{
  MSM_DUMP_CLIENT_APPS = 0,
  MSM_DUMP_CLIENT_RPM  = 1,
  MSM_DUMP_CLIENT_MPSS = 2,
  MSM_DUMP_CLIENT_ADSP = 3,
  MSM_DUMP_CLIENT_WCSS = 4,
  MSM_DUMP_CLIENT_MAX  = 5,
}msm_dump_clients;

typedef struct
{
  /* Format version of the saved structure */
  uint32 version;
  /* Magic number */
  uint32 magic;
  /* Name of the dump. Currently unused */
  char name[32];
}dump_header_type;

/* Dump data type */
typedef struct
{
  uint32 version;
  uint32 magic;
  char name[32];
  uint64 start_addr;
  uint64 len;
  uint32 reserved;
  uint64 ddr_buffer_addr;  // DDR data buffer address
}dump_data_type;

/* Dump entry in the table */
typedef struct
{
  dump_type id;
  char name[32];
  uint32 type;
  uint64 start_addr;
}dump_entry_type;

/* Dump Table */
typedef struct
{
    uint32 version;
    uint32 num_entries;
    dump_entry_type entries[MSM_MAX_DUMP>>4];
}dump_table_type;

/* Shared structure for Monitor-QSEE handoff in Pass1 */
typedef struct
{
    uint64 enter_ddr_self_refresh_addr;
    uint64 mon_imem_stack_ptr;
}sysdbg_shared_data;



/*===========================================================================
**  Function :  SYSTEM_DEBUG_MAIN
** ==========================================================================
*/
/*!
*
* @brief
*   Main SYSDBG
*
* @param[in]
*   uint32 pass_count
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*
*/
void system_debug_main(void);

/*===========================================================================
**  Function : SYSDBG_RESET_CHECK
** ==========================================================================
*/
/*!
*
* @brief
*   API used to check for whether we're in cold boot or WDT reset boot
*
* @param[in]
*
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*
*
*
*/

boolean sysdbg_reset_check(void);

/*===========================================================================
**  Function : SYSDBG_GET_BUFFER
** ==========================================================================
*/
/*!
*
* @brief
*   API used to get the buffer pointing to a request dump entry
*
* @param[in]
*   Dump name for which buffer is desired
*
* @par Dependencies
*   HLOS Dump table must be populated. If not, it will return NULL
*
* @retval
*   Pointer to buffer where data can be saved
*
* @par Side Effects
*   None
*
*
*/
dump_data_type *sysdbg_get_buffer(dump_type name , uint32 block);

/*===========================================================================
**  Function : SYSDBG_SRB_WRITE_HYDRA
** ==========================================================================
*/
/*!
*
* @brief
*
* @param[in]
*
* @par Dependencies
*
* @retval
*
* @par Side Effects
*   None
*
*
*/
void sysdbg_srb_write_hydra(void);

/*===========================================================================
**  Function : SYSTEM_DEBUG_EL1_EXIT
** ==========================================================================
*/
/*!
*
* @brief
*   When SDI has a component that runs in EL1, this API facilitates the return
*   back into EL3
*
* @param[in]
*
* @par Dependencies
*
* @retval
*
* @par Side Effects
*   None
*
*
*/
void system_debug_el1_exit(void);

#endif /* _SYSDBG_H */
