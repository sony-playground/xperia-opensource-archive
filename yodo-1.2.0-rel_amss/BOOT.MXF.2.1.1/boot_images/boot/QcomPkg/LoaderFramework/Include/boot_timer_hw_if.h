#ifndef BOOT_TIMER_HW_IF_H
#define BOOT_TIMER_HW_IF_H

/*===========================================================================

                             boot timer if
                               Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for Boot Logger
  Timer functionality.Time unit in boot logger is microsecond(10^-6 second).

Copyright 2019 by Qualcomm Technologies Inc.  All Rights Reserved.
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

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/


typedef struct boot_timer_hw_if_type
{
	uint32 (*get_timestamp)(void);
} boot_timer_hw_if_type;


extern boot_timer_hw_if_type timer_hw_if;
#endif  /* BOOT_TIMER_HW_IF_H */
