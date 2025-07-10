//============================================================================
//
//             ReadSystemRegisters.h
//
// GENERAL DESCRIPTION
//   Read system registers routines
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

#include <ProcessorBind.h>

/* Read Multiprocessor Affinity register */
UINTN READ_MPIDR_EL1 (VOID);

/* Read Vector Base Address register */
UINTN READ_VBAR_EL1 (VOID);

/* Read Software Thread ID register */
UINTN READ_TPIDR_EL1 (VOID);

/* Read Translation Table Base register 0 */
UINTN READ_TTBR0_EL1 (VOID);

/* Read Translation Control register */
UINTN READ_TCR_EL1 (VOID);

/* Read Memory Address Indirection register */
UINTN READ_MAIR_EL1 (VOID);

/* Read Architectural Feature Access Control register */
UINTN READ_CPACR_EL1 (VOID);

/* Read System Control register */
UINTN READ_SCTLR_EL1 (VOID);

/* Read Counter-timer Virtual Timer TimerValue register */
UINTN READ_CNTVTVAL (VOID);

/* Read Counter-timer Virtual Timer CompareValue register */
UINTN READ_CNTVCVAL (VOID);

/* Read Counter-timer Virtual Timer Control register */
UINTN READ_CNTVCTL (VOID);

/* Read Interrupt Status register */
UINTN READ_ISR_EL1 (VOID);
