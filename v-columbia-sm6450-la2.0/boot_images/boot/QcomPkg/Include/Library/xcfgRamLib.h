#ifndef XCFG_RAM_LIB_H
#define XCFG_RAM_LIB_H

/*=============================================================================

                            XBLConfig Ram Module Sources

GENERAL DESCRIPTION
  This file defines XBL config api's to support initializing XBLconfig module
  and access a config item.

Copyright 2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
10/15/20     rama      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "XBLConfig.h"



/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================
**  Function :  xblconfig_ramlib_init
** ==========================================================================
*/
/*!
* 
* @brief
*   This function sets start address of pre-loaded xbl config.
*   
* @param[in]
*   xcfg_ram_start_address   Start address of loaded xbl config.
*
* @param[out] 
*   None
*        
* @par Dependencies
*   None
*   
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
* 
* @par Side Effects
*   None
* 
*/
xblconfig_status_type xblconfig_ramlib_init
(
  uintnt* xcfg_ram_start_address
);

#endif /* XCFG_RAM_LIB_H */

