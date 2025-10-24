#ifndef BOOT_RAMDUMP_WRAPPER_APIS_H
#define BOOT_RAMDUMP_WRAPPER_APIS_H

/*===========================================================================

                                Boot Shared Functions Consumer
                                Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for Ramdump must 
  functions . 

Copyright  2020 by QUALCOMM Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   --------     ------------------------------------------------------
05/27/20   yps          Initial creation
============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_comdef.h"
  
#include "boot_crashdump.h"
#include <boot_reset_if.h>
#include "pm_ldo.h"
#include "pm_pon.h"
#include "pm_lab.h"
#include "pm_wled.h"
#include "pm_lcdb.h"
#include "pm_ibb.h"
#include "pm_pbs.h"
#include "smem_type.h"
#include "smem.h"



/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
boolean boot_check_display_allowed();

bl_error_boot_type  read_ddr_training_data_from_partition(uint8 * ddr_training_data_buf, uint64 offset , uint64 size);

/* SONY_BEGIN(Ramdumper support) */
#ifdef FEATURE_SONY_RAMDUMP
pm_err_flag_type boot_pm_dev_get_power_on_reason(unsigned pmic_device_index,
                                                 uint64 * pwr_on_reason);
uint32 sbl1_hw_get_reset_status(void);
#endif /* FEATURE_SONY_RAMDUMP */
/* SONY_END(Ramdumper support) */

#endif /* BOOT_SHARED_FUNCTIONS_CONSUMER_H */


