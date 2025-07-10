/*=============================================================================

                             Boot Error Handler

GENERAL DESCRIPTION
  This file contains Boot Loader AArch64 specific error handler.
  The BOOT error handler is called in the event an error is detected.

Copyright 2020-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
04/30/21   rama    add current_el argument to boot_err_dump_exc_context
05/29/20   rama    Remove boot_dload.h
04/21/20   rama    Initial revision
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_logger.h"
#include <stdio.h>
#include <boot_error_handler_arch.h>
#include <boot_sbl_shared.h>

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
/*=============================================================================
   
                              FUNCTION DEFINITIONS

=============================================================================*/

/*===========================================================================

**  Function :  boot_err_dump_exc_context

** ==========================================================================
*/
/*!
* 
* @brief
*   Dump the contents of the saved exception context structure to boot_log 
*
* @par Dependencies
*   None
*   
* @param[in] exc_context* exc_context_ptr The pointer to the exception 
&            context structure to be dumped
*
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
void boot_err_dump_exc_context(exc_context* exc_context_ptr, char* error_message, uint32 buffer_size, uint32 current_el)
{
  if(exc_context_ptr==NULL || error_message == NULL || buffer_size == 0 || current_el < EL_1 || current_el > EL_3)
  {
    return;
  }
  snprintf(error_message, buffer_size, 
    "Exception caught by SBL1 vector table!!");
  boot_log_message(error_message);
   
  snprintf(error_message, buffer_size, 
    "ELR-EL%1d: %16lx (Exception Link Register) *PC at exc", current_el, (uintnt)exc_context_ptr->exception_context_aarch64.elr);
  boot_log_message(error_message);
	
  snprintf(error_message, buffer_size, 
    "ESR-EL%d: %16lx (Exception Syndrome Register)", current_el, (uintnt)exc_context_ptr->exception_context_aarch64.esr);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X0 : %16lx, X1 : %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x0, (uintnt)exc_context_ptr->exception_context_aarch64.x1);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X2 : %16lx, X3 : %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x2, (uintnt)exc_context_ptr->exception_context_aarch64.x3);
  boot_log_message(error_message);
	
  snprintf(error_message, buffer_size, 
    "X4 : %16lx, X5 : %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x4, (uintnt)exc_context_ptr->exception_context_aarch64.x5);
  boot_log_message(error_message);
	
  snprintf(error_message, buffer_size, 
    "X6 : %16lx, X7 : %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x6, (uintnt)exc_context_ptr->exception_context_aarch64.x7);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X8 : %16lx, X9 : %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x8, (uintnt)exc_context_ptr->exception_context_aarch64.x9);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X10: %16lx, X11: %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x10, (uintnt)exc_context_ptr->exception_context_aarch64.x11);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X12: %16lx, X13: %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x12, (uintnt)exc_context_ptr->exception_context_aarch64.x13);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X14: %16lx, X15: %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x14, (uintnt)exc_context_ptr->exception_context_aarch64.x15);
  boot_log_message(error_message);		

  snprintf(error_message, buffer_size, 
    "X16: %16lx, X17: %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x16, (uintnt)exc_context_ptr->exception_context_aarch64.x17);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X18: %16lx, X19: %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x18, (uintnt)exc_context_ptr->exception_context_aarch64.x19);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X20: %16lx, X21: %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x20, (uintnt)exc_context_ptr->exception_context_aarch64.x21);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X22: %16lx, X23: %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x22, (uintnt)exc_context_ptr->exception_context_aarch64.x23);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X24: %16lx, X25: %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x24, (uintnt)exc_context_ptr->exception_context_aarch64.x25);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X26: %16lx, X27: %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x26, (uintnt)exc_context_ptr->exception_context_aarch64.x27);
  boot_log_message(error_message);

  snprintf(error_message, buffer_size, 
    "X28: %16lx, X29: %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x28, (uintnt)exc_context_ptr->exception_context_aarch64.x29);
  boot_log_message(error_message);	

  snprintf(error_message, buffer_size, 
    "X30: %16lx", (uintnt)exc_context_ptr->exception_context_aarch64.x30);
  boot_log_message(error_message);	
}

/*===========================================================================
**  Function :  boot_get_exc_cookie
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
uintnt boot_get_exc_cookie(exc_context* exc_context_ptr)
{
  if(exc_context_ptr != NULL)
    return exc_context_ptr->exception_context_aarch64.exc_cookie;
  else
    return 0;
}