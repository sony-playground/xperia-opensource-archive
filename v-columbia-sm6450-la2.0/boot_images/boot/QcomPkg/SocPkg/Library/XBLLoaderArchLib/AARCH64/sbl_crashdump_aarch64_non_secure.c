/*=============================================================================

                             Boot Error Handler

GENERAL DESCRIPTION
  This file contains Boot Loader AArch64 specific crashdump handler.
  The BOOT crashdump handler is called in the event an error is detected.

Copyright 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
06/25/21   rama    Initial revision
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <sbl_crashdump_arch.h>

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
#define FUNCTION_POINTER boot_crash_dump_data.boot_crash_dump_aarch64_data.regs[29];

boot_crash_dump_type boot_crash_dump_data;
/*=============================================================================
   
                              FUNCTION DEFINITIONS

=============================================================================*/

/*===========================================================================
**  Function :  boot_get_fp
** ==========================================================================
*/
/*!
* 
* @brief
*   This gets the function pointer from boot_crashdump_data
*
* @param[in] None
*        
* @par Dependencies
*  none
*   
*/
uintnt boot_get_frame_pointer(void)
{
	return FUNCTION_POINTER;
}


