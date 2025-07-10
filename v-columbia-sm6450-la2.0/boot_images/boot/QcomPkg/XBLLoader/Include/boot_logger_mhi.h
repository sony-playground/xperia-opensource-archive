#ifndef BOOT_LOGGER_MHI_H
#define BOOT_LOGGER_MHI_H
/*===========================================================================

                    BOOT LOGGER MHI HEADER FILE

DESCRIPTION
   This file contains the function interface for logging messages during boot
   over the MHI interface.

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
08/10/20   ck      Initial creation leveraged from existing boot_logger_uart.h

===========================================================================*/

/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "boot_comdef.h"
#include "boot_logger_if.h"


/*===========================================================================
                      PUBLIC FUNCTION DECLARATIONS
===========================================================================*/
bl_error_boot_type boot_logger_mhi_get_interface(boot_registered_logger_if_type **logger_if);


#endif /*#ifndef BOOT_LOGGER_MHI_H*/

