#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

/*===========================================================================

                       Error Handler Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for the BOOT
  error handler.  It is called in the event a BOOT failure is detected.
  Once this boot_error_handler is called. It will never return. 
    
Copyright 2020 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
06/25/20   rama    Removed boot_query_xpu_violation API
05/29/20   rama    Removed crashdump version and cookie macros
05/14/20   rama    Move Arch-specific APIs to XBLLoaderArchLib
08/29/18   msantos updated boot_crash_dump_type to version 2 (Aarch64)
06/23/16   digant  exception context struct to save registers
06/02/16   digant  xpu violation query update
10/29/14   kpa     Support 64 bit memory map
10/21/14   ck      Updated BOOT_VALID_ADDR_INC_IMEM to 64 bit
03/25/14   kedara  Added sbl_pcie_coredump_addr, sbl_pcie_coredump_size
03/18/14   kedara  Moved sbl_save_regs() definition
11/12/13   kedara  Added changes to support SBL crash dumps
07/10/13   aus     Added support to save the registers and flush the L2 TCM to DDR
                   on SBL errors
08/04/10   aus     Clean-up secboot 3.0
05/26/10   plc     Initial port to secboot 3.0 common code  
01/28/10   ty      Initial revision

============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#ifndef _ARM_ASM_
#include "boot_comdef.h"
#include "boot_error_if.h"

/*==========================================================================
                          PUBLIC DATA DECLARATIONS
===========================================================================*/
#define SBL1_EXC_CONTEXT_VALID_COOKIE 0x45584320 // Cookie "EXC "
#define BOOT_ERROR_MSG_LEN 256

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/
       
/*===========================================================================

**  Function :  boot_err_fatal

** ==========================================================================
*/
/*!
* 
* @brief
*   This function calls the SBL error handler.
*   
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   None
*/
void boot_err_fatal( void );


/*===========================================================================

**  Function :  boot_init_stack_chk_canary

** ==========================================================================
*/
/*!
* 
* @brief
*   Initialize stack protection canary to a random number  
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
void boot_init_stack_chk_canary(void);


#endif


#endif  /* BOOT_ERROR_HANDLER_H */
