#ifndef BOOT_TIMER_IF_H
#define BOOT_TIMER_IF_H

/*===========================================================================

                             boot timer if
                               Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for Boot Logger
  Timer functionality.Time unit in boot logger is microsecond(10^-6 second).

Copyright 2019, 2022 by Qualcomm Technologies Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/19/19   ep      Initial Version 
============================================================================*/
#include "boot_comdef.h"
#include "boot_timer_hw_if.h"

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

#define LOG_TIMESTAMP_OVERFLOW  0xFFFFFFFF


typedef struct boot_timer_if_type
{
  bl_error_boot_type (*init)(boot_timer_hw_if_type *);
  bl_error_boot_type (*get_time_count)(uint32 *);
  bl_error_boot_type (*get_time)(uint32, uint32 *);
} boot_timer_if_type;


/*===========================================================================
**  Function :  boot_logger_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_logger_get_interface object 
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_timer_get_interface(void *ptr);
uint32 boot_get_time_count(void);

#endif  /* BOOT_TIMER_IF_H */
