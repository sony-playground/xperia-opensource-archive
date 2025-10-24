;/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
;
;                      S T A R T U P   C O D E
;
; GENERAL DESCRIPTION
;   This module contains the entry point for our Flash Programming Plug-In 
;   for Lauterbach JTAG/ICD TRACE32. All it does is setups stack and calls
;   our main 'C' function "main_c".
;
;   The C function does return and expects a breakpoint there. This is the
;   case because the FLASH programming plug-in specification requires it.
;   The break-point is used to give control back to TRACE32 Debugger so 
;   that it may fill up the buffer and call our plug-in again. This cycle
;   continues until FLASH programming is complete.
;
; EXTERNALIZED FUNCTIONS
;   None.  
;
;  Copyright (c) 2020 Qualcomm Technologies, Inc.
;  All Rights Reserved.
;*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*======================================================================

                           EDIT HISTORY FOR FILE
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when          who     what, where, why
-----------   ---     -----------------------------------------------------
06/11/20      sa      Initial Version
===========================================================================*/

;/*============================================================================
;
;                  STARTUP CODE
;
;============================================================================*/

.text
.align 3

GCC_ASM_IMPORT (main_loop_c)
GCC_ASM_IMPORT (Image$$NAND_PROGRAMMER_STACK$$Start)
GCC_ASM_EXPORT (_ModuleEntryPoint)

//TODO Check what is the significance of this

// Needed to enable neon
.macro enable_neon_sec_and_nonsec
    mrc     p15, 0, r0, c1, c1, 2
    ldr     r1, =(0x3 << 10)
    orr     r0, r0, r1              // enable neon
    ldr     r1, =(0x3 << 14)
    bic     r0, r0, r1              // clear nsasedis/nsd32dis
    mcr     p15, 0, r0, c1, c1, 2
    ldr     r0, =(0xF << 20)
    mcr     p15, 0, r0, c1, c0, 2
    mov     r0, #0x40000000 
    vmsr    fpexc, r0
.endm

  
_ModuleEntryPoint:
  //enable_neon_sec_and_nonsec
  LDR x0, =Image$$NAND_PROGRAMMER_STACK$$Start
  //adr x0, Image$$NAND_PROGRAMMER_STACK$$Start
  //mov x0, #0x14840000
  mov sp, x0
  b main_loop_c

dead:  
  b dead                      /* We should never get here */
  
