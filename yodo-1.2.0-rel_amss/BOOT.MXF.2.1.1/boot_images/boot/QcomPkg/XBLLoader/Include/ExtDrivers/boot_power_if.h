#ifndef BOOT_POWER_IF_H
#define BOOT_POWER_IF_H
/*===========================================================================

                    BOOT EXTERN POWER DRIVER DEFINITIONS

DESCRIPTION
  Contains definition for external power if 

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when        who     what, where, why
--------   ---     ----------------------------------------------------------
08/05/19   ep       Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"



typedef struct boot_power_if_type
{
  void (*railway_init)(void);
  void (*cpr_init)(void);
  void (*populate_cpr_settings)(void);
  void (*aop_mini_dump_init)(void);
} boot_power_if_type;


/*===========================================================================
**  Function :  boot_power_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_power_get_interface
*
* @par Dependencies
*   None 
* 
*/

//bl_error_boot_type boot_power_get_interface(void *ptr);

extern boot_power_if_type power_if;


#endif /* BOOT_POWER_IF_H */
