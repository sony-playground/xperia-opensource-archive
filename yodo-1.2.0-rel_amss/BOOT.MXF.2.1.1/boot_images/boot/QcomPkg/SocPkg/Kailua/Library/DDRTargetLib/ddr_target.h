#ifndef __DDR_TARGET_H__
#define __DDR_TARGET_H__

/*=============================================================================
                              DDR HAL
                            Header File
GENERAL DESCRIPTION
This is the target header file for DDR HAL.

Copyright 2014,2020-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.

===========================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
02/12/21   mkma    add function to share mode get_boot_mode
03/12/14   sr      Initial revision.
=============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include "ddr_common.h"
#include "boot_modes.h"
#include "HALhwio.h"

//Intermediate training buffer is at the start of AOP Code RAM
#define INTERMEDIATE_TRAINING_BUF      0x0B000000
#define DDR_INTERLEAVE_CHANNEL_SIZE    512

typedef struct 
{
  DDR_CHIPSELECT rank_detected;
  uint64 remap_size;
  uint64 bimc_remapper_cs0; /* BIMC Remapper CS0 */
  uint64 bimc_remapper_cs1; /* BIMC Remapper CS1 */
} RemapperTable;

typedef struct ddr_target_dt_entries_struct{
        uint32 ddr_trng_always_en;
        uint32 extnd_term_log_flag;
        uint32 ddr_boot_freq;
        uint32 ddr_tr_led_flag;
}ddr_target_dt_entries_struct;
ddr_target_dt_entries_struct dt_target_entries;
/*==============================================================================
                                  MACROS
==============================================================================*/

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/
boot_mode_type ddr_get_boot_mode( void );

/* define the maximum partition size for saving ddr training logs and result */
#define DDR_MAX_LOG_SIZE 1*1024*1024 /* 1 MB space */
#endif /* __DDR_TARGET_H__ */
