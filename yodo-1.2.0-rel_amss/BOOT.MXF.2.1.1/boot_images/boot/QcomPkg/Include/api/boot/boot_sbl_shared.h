#ifndef BOOT_SBL_SHARED_H
#define BOOT_SBL_SHARED_H

/*===========================================================================

                          Boot Shared Header File

GENERAL DESCRIPTION
 Contains common defintion used by BOOT module.

Copyright 2019-2021 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/30/21   rama    Added get_el1_sync_type and get_el3_sync_type
08/24/20   rama    removed bl_shared_data_if definition
============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"
#include "boot_build_component.h"

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/

#define EL_3 0x3
#define EL_1 0x1

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/
 
/*===========================================================================

**  Function :  sbl_loop_here

** ==========================================================================
*/
/*!
* 
* @brief
*  This function is called by boot_error_handler only. We perform
*  clean up of the registers and loop until JTAG is connected.
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
void sbl_loop_here( void );

/*===========================================================================

**  Function :  sbl1_get_current_el

** ==========================================================================
*/
/*!
* 
* @brief
*  This function returns the value of the current exception level 
*  we are operating in 
* 
* @par Dependencies
*   None
*   
* @retval
*   uint32  -  value of current exception level
* 
* @par Side Effects
*   None
* 
*/
uint32 sbl1_get_current_el( void );

/*===========================================================================

**  Function :  get_el1_sync_type

** ==========================================================================
*/
/*!
* 
* @brief
*  This function is called by boot_sync_c_handler only. We check the 
*  synchronous exception type by reading the ESR_EL1 register.  The ISS 
*  bits of this register are dependent upon exception type, and could be 
*  made use of in future improvements.
* 
* @par Dependencies
*   None
*   
* @retval
*   uint32 sync_type
* 
* @par Side Effects
*   None
* 
*/
uint32 get_el1_sync_type( void );

/*===========================================================================

**  Function :  get_el3_sync_type

** ==========================================================================
*/
/*!
* 
* @brief
*  This function is called by boot_sync_c_handler only. We check the 
*  synchronous exception type by reading the ESR_EL3 register.  The ISS 
*  bits of this register are dependent upon exception type, and could be 
*  made use of in future improvements.
* 
* @par Dependencies
*   None
*   
* @retval
*   uint32 sync_type
* 
* @par Side Effects
*   None
* 
*/
uint32 get_el3_sync_type( void );

#endif /* BOOT_SBL_SHARED_H */
