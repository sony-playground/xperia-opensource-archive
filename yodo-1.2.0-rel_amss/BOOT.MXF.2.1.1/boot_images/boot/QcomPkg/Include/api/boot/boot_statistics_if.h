#ifndef BOOT_STATISTICS_IF_H
#define BOOT_STATISTICS_IF_H

/*===========================================================================

                          Boot Statistics Interface

GENERAL DESCRIPTION
 Contains common data used for boot statistics

Copyright 2020 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/23/20   ck      Added init
02/15/20   ds      Initial creation
============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include "boot_framework.h"
#include "boot_error_if.h"

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/


/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================

**  Function : boot_statistics_flash_read_start

** ==========================================================================
*/
/*!
* 
* @brief  
*   Called before reading from flash.  This gets the current timer value and
*   stores it for use when boot_statistics_flash_read_stop is called.
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
*/

typedef struct boot_statistics_if_type
{
  bl_error_boot_type (*init)();
  bl_error_boot_type (*statistics_start)();
  bl_error_boot_type (*statistics_stop)(uint32);
  bl_error_boot_type (*get_bytes_read)(uint32 *);
  bl_error_boot_type (*reset_bytes_read)();
  bl_error_boot_type (*log_total_statistics)();
} boot_statistics_if_type;

extern boot_statistics_if_type boot_statistics_if;

#endif /* BOOT_STATISTICS_H */
