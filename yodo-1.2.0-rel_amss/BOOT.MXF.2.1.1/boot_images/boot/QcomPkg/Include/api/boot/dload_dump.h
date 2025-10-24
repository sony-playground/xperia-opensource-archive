#ifndef DLOAD_DUMP_H
#define DLOAD_DUMP_H
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

              M E M O R Y   D E B U G   I N F O R M A T I O N 

GENERAL DESCRIPTION
  This module dumps security memory region to destinition address

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

Copyright 2019 by Qualcomm Technologies Incorporated. All Rights Reserved.


*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*===========================================================================

                           EDIT HISTORY FOR FILE
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/boot/dload_dump.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------

===========================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "comdef.h"
#include "boot_config_context.h"
/*===========================================================================

                     EXTERNAL DEFINITIONS FOR MODULE

===========================================================================*/



/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS
                      
===========================================================================*/


/*===========================================================================
**  Function :  boot_dload_dump_security_regions
** ==========================================================================
*/
/*!
* 
* @brief
*   This function will dump backup qsee and qhee regions according to 
*   information passed by qsee/qhee's shared imem cookies, so they can be 
*   ramdumped later.
*
* @param[in] shared_data Pointer to shared data
*        
* @par Dependencies
*   Called only in dload path
* 
*/
bl_error_boot_type boot_dload_dump_security_regions(boot_handle config_context_handle);

/*===========================================================================
**  Function :  boot_dload_is_security_region_dump_allowed
** ==========================================================================
*/
/*!
* 
* @brief
*   This function will determine if sbl can dump tz in dload mode
*
* @param[in] shared_data Pointer to shared data
*        
* @par Dependencies
*   None
* 
*/
bl_error_boot_type boot_dload_is_security_region_dump_allowed(boot_handle config_context_handle, uint8 *mem_dump_supported) ;

#endif  /* DLOAD_DEBUG_DUMP_H */
