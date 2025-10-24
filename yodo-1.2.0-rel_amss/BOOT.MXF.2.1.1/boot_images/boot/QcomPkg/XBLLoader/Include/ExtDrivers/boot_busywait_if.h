#ifndef BOOT_BUSYWAIT_IF_H
#define BOOT_BUSYWAIT_IF_H
/*===========================================================================

                    BOOT EXTERN BUSYWAIT DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external busy wait drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/01/19   ep      File created

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"
#include "DALStdDef.h"
#include "boot_comdef.h"
#include "boot_error_if.h"


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


typedef struct boot_busywait_if_type
{
  DALResult (*init)(void);
  void (*busywait)(uint32 pause_time_us);
} boot_busywait_if_type;


/*===========================================================================
**  Function :  boot_busywait_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_crypto_if
*
* @par Dependencies
*   None 
* 
*/

//bl_error_boot_type boot_busywait_get_interface(void *ptr);

extern boot_busywait_if_type busywait_if;


#endif /* BOOT_BUSYWAIT_IF_H */

