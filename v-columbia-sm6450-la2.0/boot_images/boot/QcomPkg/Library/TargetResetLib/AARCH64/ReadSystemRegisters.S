//============================================================================
//
//             ReadSystemRegisters.S
//
// GENERAL DESCRIPTION
//   Read system registers routines in assembly for AArch64
//
// Copyright 2021 by Qualcomm Technologies, Inc.  All Rights Reserved 
//============================================================================

//============================================================================
//
//                       EDIT HISTORY FOR MODULE
//
//
// This section contains comments describing changes made to the module.
// Notice that changes are listed in reverse chronological order.
//
//
// when      who     what, where, why
// --------  -----   ----------------------------------------------------------
// 04/27/21  am      Created new file
//=============================================================================

.text
.align 3

#include <ProcessorBind.h>

//=============================================================================
//                             MODULE EXPORTS
//=============================================================================
  ASM_GLOBAL ASM_PFX(READ_MPIDR_EL1)
  ASM_GLOBAL ASM_PFX(READ_VBAR_EL1)
  ASM_GLOBAL ASM_PFX(READ_TPIDR_EL1)
  ASM_GLOBAL ASM_PFX(READ_TTBR0_EL1)
  ASM_GLOBAL ASM_PFX(READ_TCR_EL1)
  ASM_GLOBAL ASM_PFX(READ_MAIR_EL1)
  ASM_GLOBAL ASM_PFX(READ_CPACR_EL1)
  ASM_GLOBAL ASM_PFX(READ_SCTLR_EL1)
  ASM_GLOBAL ASM_PFX(READ_CNTVTVAL)
  ASM_GLOBAL ASM_PFX(READ_CNTVCVAL)
  ASM_GLOBAL ASM_PFX(READ_CNTVCTL)
  ASM_GLOBAL ASM_PFX(READ_ISR_EL1)

//=============================================================================
//
//                        MACROS AND FUNCTIONS
//
//=============================================================================


//=============================================================================
//
//  UINTN READ_MPIDR_EL1 (void)//
//
//=============================================================================
ASM_PFX(READ_MPIDR_EL1):
  mrs x0, mpidr_el1
  isb
  ret

//=============================================================================
//
//  UINTN READ_VBAR_EL1 (void)//
//
//=============================================================================
ASM_PFX(READ_VBAR_EL1):
  mrs x0, vbar_el1
  isb
  ret

//=============================================================================
//
//  UINTN READ_TPIDR_EL1 (void)//
//
//=============================================================================
ASM_PFX(READ_TPIDR_EL1):
  mrs x0, tpidr_el1
  isb
  ret

//=============================================================================
//
//  UINTN READ_TTBR0_EL1 (void)//
//
//=============================================================================
ASM_PFX(READ_TTBR0_EL1):
  mrs x0, ttbr0_el1
  isb
  ret

//=============================================================================
//
//  UINTN READ_TCR_EL1 (void)//
//
//=============================================================================
ASM_PFX(READ_TCR_EL1):
  mrs x0, tcr_el1
  isb
  ret

//=============================================================================
//
//  UINTN READ_MAIR_EL1 (void)//
//
//=============================================================================
ASM_PFX(READ_MAIR_EL1):
  mrs x0, mair_el1
  isb
  ret

//=============================================================================
//
//  UINTN READ_CPACR_EL1 (void)//
//
//=============================================================================
ASM_PFX(READ_CPACR_EL1):
  mrs x0, cpacr_el1
  isb
  ret

//=============================================================================
//
//  UINTN READ_SCTLR_EL1 (void)//
//
//=============================================================================
ASM_PFX(READ_SCTLR_EL1):
  mrs x0, sctlr_el1
  isb
  ret

//=============================================================================
//
//  UINTN READ_CNTVTVAL (void)//
//
//=============================================================================
ASM_PFX(READ_CNTVTVAL):
  mrs x0, cntv_tval_el0
  isb
  ret

//=============================================================================
//
//  UINTN READ_CNTVCVAL (void)//
//
//=============================================================================
ASM_PFX(READ_CNTVCVAL):
  mrs x0, cntv_cval_el0
  isb
  ret

//=============================================================================
//
//  UINTN READ_CNTVCTL (void)//
//
//=============================================================================
ASM_PFX(READ_CNTVCTL):
  mrs x0, cntv_ctl_el0
  isb
  ret

//=============================================================================
//
//  UINTN READ_ISR_EL1 (void)//
//
//=============================================================================
ASM_PFX(READ_ISR_EL1):
  mrs x0, isr_el1
  isb
  ret
