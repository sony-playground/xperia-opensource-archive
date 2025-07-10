#ifndef BOOT_BAM_IF_H
#define BOOT_BAM_IF_H
/*===========================================================================

                    BOOT EXTERN BAM DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external bam driver

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/02/20   ck      Initial revision
===========================================================================*/

#include "boot_comdef.h"
#include "boot_error_if.h"
#include "bam_drv.h"


typedef struct boot_bam_if_type
{
  bam_status_type (*init)(void);
  bam_status_type (*deinit)(void);
} boot_bam_if_type;


extern boot_bam_if_type bam_if;


#endif /* BOOT_BAM_IF_H */

