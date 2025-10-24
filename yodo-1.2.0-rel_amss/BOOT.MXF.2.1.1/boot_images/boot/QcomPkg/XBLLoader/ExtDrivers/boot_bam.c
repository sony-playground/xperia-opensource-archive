/*===========================================================================

                    BOOT BAM WRAPPER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external bam driver

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/02/20   ck      Initial revision
===========================================================================*/

#include "boot_error_if.h"
#include "boot_bam_if.h"
#include "bam_drv.h"


boot_bam_if_type bam_if =
{
  bam_drv_init,
  bam_drv_deinit
};
