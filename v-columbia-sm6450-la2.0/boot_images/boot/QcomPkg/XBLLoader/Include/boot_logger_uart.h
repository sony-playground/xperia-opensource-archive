#ifndef BOOT_LOGGER_UART_H
#define BOOT_LOGGER_UART_H
/*===========================================================================

                    BOOT LOGGER UART HEADER FILE

DESCRIPTION
   This file contains the function interface for logging messages during boot
   to the uart buffer.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2013-2015 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/18/15   elt     Added boot_log_ram_to_uart
05/28/14   ck      Added optional data argument to boot_log_message_uart
08/20/13   lm      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"
#include "boot_logger_if.h"

/*===========================================================================
                      PUBLIC DATA DECLARATIONS
===========================================================================*/


/*===========================================================================
                      PUBLIC FUNCTION DECLARATIONS
===========================================================================*/



bl_error_boot_type boot_logger_uart_get_interface(boot_registered_logger_if_type **logger_if);


#endif /*#ifndef BOOT_LOGGER_UART_H*/

