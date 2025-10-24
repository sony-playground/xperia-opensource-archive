#ifndef BOOT_RAMDUMP_IF_H
#define BOOT_RAMDUMP_IF_H
/*===========================================================================

                    BOOT SDI IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for SDI image functionality

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
 
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/09/22   ck      Updated get_external_heap_size return type
07/08/21   ck      Updated transition_pbl_forced_dload return type
06/25/21   rhy     Added boot_clear_second_pass_complete
08/06/19   ep      Initial Creation.
===========================================================================*/

#include "boot_comdef.h"
#include "boot_error_if.h"


typedef struct boot_ramdump_if_type
{
  uint32 (*get_saved_cookie)(void);
  void (*set_dload_cookie)( void );
  bl_error_boot_type (*transition_pbl_forced_dload)(void* config_context);
  byte* (*get_external_heap_addr)(void);
  uintnt (*get_external_heap_size)(void);
  void (*clear_second_pass_complete)(void);
} boot_ramdump_if_type;


/*===========================================================================
**  Function :  boot_ramdump_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_ramdump_get_interface
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_ramdump_get_interface(void* ramdump_if);


#endif /* BOOT_RAMDUMP_IF_H */
