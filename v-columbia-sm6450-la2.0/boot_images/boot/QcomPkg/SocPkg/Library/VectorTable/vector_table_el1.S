//*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
//
//                              el1_vector_table.s
//
// GENERAL DESCRIPTION
//   This file captures 64-bit vector table for ARMV8
//
// Copyright 2013, 2016, 2017, 2019 - 2021 by Qualcomm Technologies, Incorporated.All Rights Reserved.
//*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

//*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
//
//                           EDIT HISTORY FOR FILE
//
// This section contains comments describing changes made to the module.
// Notice that changes are listed in reverse chronological order.
//
//
// when       who     what, where, why
// --------   ---     --------------------------------------------------------
// 04/30/21   rama    rename get_sync_type to get_el1_sync_type
// 06/25/20   rama    Removed boot_query_xpu_violation
// 02/28/20   rama    Moved boot_vector_table.s to BootVectorTable library
// 06/04/19   yps     Removed palign for text region
// 01/22/19   yps     Removed specific sections
// 02/24/17   kpa     fix exception handler size overflow
// 01/26/17   yepings Fixed LLVM384 compiling issue    
// 06/23/16   digant  register save and exception handling updates
// 06/02/16   digant  xpu violation query for sync,serror
// 12/08/13   dhaval  vector table creation for ARMV8 64-bit mode
//*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*


//============================================================================
//
//                            MODULE INCLUDES
//
//============================================================================
#include "error_handler.h"

//============================================================================
//
//                             MODULE IMPORTS
//
//============================================================================

//////////// For now, symbols are branched to itself in first version, those will 
//////////// be implemented and imported in these files eventually.
    .extern boot_sys_c_handler
    .extern boot_sync_c_handler
    .extern boot_irq_c_handler
    .extern boot_fiq_c_handler
    .extern boot_nested_exception_c_handler
    .extern exception_context
	
//============================================================================
//
//                             MODULE EXPORTS
//
//============================================================================

    // Export the el1_vector_table for VBAR configuration in initial boot 
	// assembly init routines.
    .global vector_table_el1
    .global get_el1_sync_type

//============================================================================
//                             MODULE MACRO
//============================================================================
#define ESR_EC_BITS 0x1A  //EC field(6 bits in size) starts at bit 26(0x1A) in ESR_ELx
#define ESR_EL_EC_MASK 0x3F //EC field mask
//============================================================================
//
//                             MODULE DATA AREA
//
//============================================================================

    .section VECTOR_TABLE_EL1, "ax", %progbits
    .p2align 11

//for SBL, vector table is same for all ELs(EL3 and EL1)
vector_table_el1:
  //--------------------------------------
  // +0x180 SError/vSError	 	
  // +0x100 FIQ/vFIQ
  // +0x080 IRQ/vIRQ	
  // VBAR_ELn+0x000 Synchronous (at base)
  //--------Current EL with SP0-----------
  //--------------------------------------
el1_csp0_sync:
  b el1_csp0_sync

  .align 7
//el1_csp0_irq  b el1_csp0_irq
el1_csp0_irq:
  b el1_csp0_irq 

  .align 7
el1_csp0_fiq:
  b el1_csp0_fiq 

  .align 7
el1_csp0_serror:
  b el1_csp0_serror 

  //--------------------------------------
  // +0x380 SError/vSError	 	
  // +0x300 FIQ/vFIQ
  // +0x280 IRQ/vIRQ	
  // +0x200 Synchronous 
  //--------Current EL with SPx-----------
  //--------------------------------------

//-----------------------------------
// Save the exception context
//----------------------------------------  
  .align 7
el1_cspx_sync:
  // explicitly save link reg on stack
  // A macro is used for register push since the inline
  // expansion shall consume exception handler space
  // A api is used for register pop to avoid overflowing
  // handler size (128 bytes). Goal is to consume optimum
  // handler space and not waste any. However this forces 
  // link register push-pop to be handled explicitly.
  mov x14, x30
  bl  save_exception_context
  bl  check_re_entry
  ldr x5,=boot_sync_c_handler
  br  x5
  
  .align 7
el1_cspx_irq:
  mov x14, x30
  bl  save_exception_context
  bl  check_re_entry
  ldr x5,=boot_irq_c_handler
  br  x5
  
  .align 7
el1_cspx_fiq:
  mov x14, x30
  bl  save_exception_context
  bl  check_re_entry
  ldr x5,=boot_fiq_c_handler
  br  x5
  
//-----------------------------------
// Save the exception context
//----------------------------------------
  .align 7
el1_cspx_serror:
  mov x14, x30 
  bl  save_exception_context
  bl  check_re_entry
  ldr x5,=boot_sys_c_handler
  br  x5
  
  //--------------------------------------
  // +0x580 SError/vSError	 	
  // +0x500 FIQ/vFIQ
  // +0x480 IRQ/vIRQ	
  // +0x400 Synchronous 
  //--------Lower EL using AArch64-----------
  //--------------------------------------
  .align 7
el1_lel64_sync:
  b el1_lel64_sync

  .align 7
el1_lel64_irq:
  b el1_lel64_irq

  .align 7
el1_lel64_fiq:
  b el1_lel64_fiq

  .align 7
el1_lel64_serror:
 b el1_lel64_serror

  //--------------------------------------
  // +0x780 SError/vSError	 	
  // +0x700 FIQ/vFIQ
  // +0x680 IRQ/vIRQ	
  // +0x600 Synchronous 
  //--------Lower EL using AArch32-----------
  //--------------------------------------
  .align 7
el1_lel32_sync:
  b el1_lel32_sync

  .align 7
el1_lel32_irq:
  b el1_lel32_irq

  .align 7
el1_lel32_fiq:
  b el1_lel32_fiq

  .align 7
el1_lel32_serror:
  b el1_lel32_serror


    .text
    
//============================================================================
// get_el1_sync_type
//  INPUT       -      
//  DESCRIPTION -
//        Reads exception syndrome in ESR_EL1 register, bits 26-31
//        Return this value in X0 register
//============================================================================
get_el1_sync_type:
  MRS X0, ESR_EL1
  LSR X0,X0,#ESR_EC_BITS
  AND X0,X0,#ESR_EL_EC_MASK
  ret

//============================================================================
// check_re_entry
//  INPUT       -
//  DESCRIPTION -
//        checks if we have re-entered from an exception,
//        and if we have then go to nested handler
//============================================================================  
check_re_entry:
  MOV x20, #1
  LDR x21, =re_entry
  LDR x22, [x21]
  CMP x20, x22
  BNE not_nested
  LDR X5,=boot_nested_exception_c_handler// we require nested handler
  BR  X5
not_nested:
  STR x20, [x21]
  ret
    
//============================================================================
// save_exception_context
//  INPUT       -
//  DESCRIPTION -
//        Saves important registers to boot_exception_context[] structure, 
//        to be dumped in debug log later
//============================================================================
save_exception_context:
  // First save used registers to stack, so they can be restored and saved
  STP     x20, x21, [sp, #-16]!
  
  // Load address of exception context, and set cookie
  LDR     x20, =exception_context
  LDR     x21, =SBL1_EXC_CONTEXT_VALID_COOKIE
  STR     x21, [x20], #8
  
  STP     x0, x1, [x20], #16

  // Restore saved x20 register and use X0 as the pointer into structure
  MOV     x0, x20
  LDP     x20, x21, [sp], #16
  STP     x2, x3, [x0], #16
  STP     x4, x5, [x0], #16
  STP     x6, x7, [x0], #16
  STP     x8, x9, [x0], #16
  STP     x10, x11, [x0], #16
  STP     x12, x13, [x0], #16
  STP     x14, x15, [x0], #16
  STP     x16, x17, [x0], #16
  STP     x18, x19, [x0], #16
  STP     x20, x21, [x0], #16
  STP     x22, x23, [x0], #16
  STP     x24, x25, [x0], #16
  STP     x26, x27, [x0], #16
  STP     x28, x29, [x0], #16

  MRS     x20, ELR_EL1  

  // Restore x30 contents which caller saved in x14, so exception context can be dumped  
  MOV     x29, x30
  MOV     x30, x14  
  STP     x30, x20, [x0], #16

  // Now restore the valid return address of the caller into this function
  MOV     x30, x29
  
  MRS     x20, ESR_EL1
  
  STR     x20, [x0], #8
  
  ret  
  
.data
  re_entry:
         .4byte 0

  .end 
