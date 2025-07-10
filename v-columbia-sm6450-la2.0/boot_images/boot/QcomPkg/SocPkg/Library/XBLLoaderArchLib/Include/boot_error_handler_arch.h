#ifndef BOOT_ERROR_HANDLER_ARCH_H
#define BOOT_ERROR_HANDLER_ARCH_H

/*===========================================================================

                       Boot Error Handler Arch Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for the BOOT
  error handler.  It is called in the event a BOOT failure is detected.
  Once this boot_error_handler is called. It will never return. 
    
Copyright 2020-2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
04/30/21   rama    add current_el argument to boot_err_dump_exc_context
04/21/20   rama    Initial revision
============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"

/*==========================================================================
                          PUBLIC DATA DECLARATIONS
===========================================================================*/

typedef struct
{
  uint32 exc_cookie;     // Exception context dump magic cookie
  uint32 svc_r0;                           // R0 register contents
  uint32 svc_r1;                           // R1 register contents
  uint32 svc_r2;                           // R2 register contents
  uint32 svc_r3;                           // R3 register contents
  uint32 svc_r4;                           // R4 register contents
  uint32 svc_r5;                           // R5 register contents
  uint32 svc_r6;                           // R6 register contents
  uint32 svc_r7;                           // R7 register contents  
  uint32 svc_r8;                           // R8 register contents
  uint32 svc_r9;                           // R9 register contents
  uint32 svc_r10;                          // R10 register contents
  uint32 svc_r11;                          // R11 register contents
  uint32 svc_r12;                          // R12 register contents
  uint32 svc_sp;                           // R13 register contents
  uint32 svc_lr;                          // R14 register contents
  uint32 svc_spsr; 
  uint32 svc_pc;                          // R15 register contents
  uint32 cpsr;
  uint32 sys_sp;
  uint32 sys_lr;
  uint32 irq_sp;
  uint32 irq_lr;
  uint32 irq_spsr;
  uint32 abt_sp;
  uint32 abt_lr;
  uint32 abt_spsr;
  uint32 udf_sp;
  uint32 udf_lr;
  uint32 udf_spsr;
  uint32 fiq_r8;
  uint32 fiq_r9;
  uint32 fiq_r10;
  uint32 fiq_r11;
  uint32 fiq_r12;
  uint32 fiq_sp;
  uint32 fiq_lr;
  uint32 fiq_spsr;
} exc_context_arm;

typedef struct
{
  uint64 exc_cookie;     // Exception context dump magic cookie
  uint64 x0;                           // X0 register contents
  uint64 x1;                           // X1 register contents
  uint64 x2;                           // X2 register contents
  uint64 x3;                           // X3 register contents
  uint64 x4;                           // X4 register contents
  uint64 x5;                           // X5 register contents
  uint64 x6;                           // X6 register contents
  uint64 x7;                           // X7 register contents  
  uint64 x8;                           // X8 register contents
  uint64 x9;                           // X9 register contents
  uint64 x10;                          // X10 register contents
  uint64 x11;                          // X11 register contents
  uint64 x12;                          // X12 register contents
  uint64 x13;                          // X13 register contents
  uint64 x14;                          // X14 register contents
  uint64 x15;                          // X15 register contents
  uint64 x16;                          // X16 register contents
  uint64 x17;                          // X17 register contents
  uint64 x18;                          // X18 register contents
  uint64 x19;                          // X19 register contents
  uint64 x20;                          // X20 register contents
  uint64 x21;                          // X21 register contents
  uint64 x22;                          // X22 register contents
  uint64 x23;                          // X23 register contents  
  uint64 x24;                          // X24 register contents
  uint64 x25;                          // X25 register contents
  uint64 x26;                          // X26 register contents
  uint64 x27;                          // X27 register contents
  uint64 x28;                          // X28 register contents
  uint64 x29;                          // X29 register contents
  uint64 x30;                          // X30 register contents
  uint64 elr;                          // ELR_EL1 exception link register contents
  uint64 esr;                          // ESR_EL1 exception syndrome reg contents
} exc_context_aarch64;

typedef union  
{
  exc_context_arm exception_context_arm;
  exc_context_aarch64 exception_context_aarch64;
}exc_context;

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
void boot_err_dump_exc_context(exc_context* exc_context_ptr, char* error_message, uint32 buffer_size, uint32 current_el);

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
uintnt boot_get_exc_cookie(exc_context* exc_context_ptr);

#endif  /* BOOT_ERROR_HANDLER_ARCH_H */
