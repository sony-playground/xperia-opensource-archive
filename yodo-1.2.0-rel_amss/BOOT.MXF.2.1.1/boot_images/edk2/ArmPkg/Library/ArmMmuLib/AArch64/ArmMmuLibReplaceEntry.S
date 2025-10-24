#------------------------------------------------------------------------------
#
# Copyright (c) 2017, 2020 Qualcomm Technologies, Inc. All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
# Portions:
# Copyright (c) 2016, Linaro Limited. All rights reserved.
#
# SPDX-License-Identifier: BSD-2-Clause-Patent
#
#------------------------------------------------------------------------------

#include <AsmMacroIoLibV8.h>

  .set CTRL_M_BIT,      (1 << 0)
#if defined (QCOM_EDK2_PATCH)
  .set CTRL_C_BIT,      (1 << 2)
  .set CTRL_I_BIT,      (1 << 12)
#endif

  .macro __replace_entry, el

  // disable the MMU
  mrs   x8, sctlr_el\el
#if defined (QCOM_EDK2_PATCH)
  mov   x9, #~(CTRL_M_BIT | CTRL_C_BIT | CTRL_I_BIT) // also disable D&I cache
  and   x9, x8, x9
#else
  bic   x9, x8, #CTRL_M_BIT
#endif
  msr   sctlr_el\el, x9
  isb

  // write updated entry
  str   x1, [x0]

  // invalidate again to get rid of stale clean cachelines that may
  // have been filled speculatively since the last invalidate
  dmb   sy
#if defined (QCOM_EDK2_PATCH)
  dsb   sy
#endif
  dc    ivac, x0

#if defined (QCOM_EDK2_PATCH)
  isb
#endif

  // flush translations for the target address from the TLBs
  lsr   x2, x2, #12
  .if   \el == 1
#if defined (QCOM_EDK2_PATCH)
  tlbi  vaae1is, x2
#else
  tlbi  vaae1, x2
#endif
  .else
  tlbi  vae\el, x2
  .endif
  dsb   nsh

#if defined (QCOM_EDK2_PATCH)
  isb

  // re-enable the MMU and D&I cache
  mov   x9, #(CTRL_M_BIT | CTRL_C_BIT | CTRL_I_BIT)
  orr   x9, x8, x9
  msr   sctlr_el\el, x9  
#else
  // re-enable the MMU
  msr   sctlr_el\el, x8
#endif
  isb
  .endm

//VOID
//ArmReplaceLiveTranslationEntry (
//  IN  UINT64  *Entry,
//  IN  UINT64  Value,
//  IN  UINT64  Address
//  )
ASM_FUNC(ArmReplaceLiveTranslationEntry)

  // disable interrupts
  mrs   x4, daif
  msr   daifset, #0xf
  isb

  // clean and invalidate first so that we don't clobber
  // adjacent entries that are dirty in the caches
  dc    civac, x0
  dsb   nsh

  EL1_OR_EL2_OR_EL3(x3)
1:__replace_entry 1
  b     4f
2:__replace_entry 2
  b     4f
3:__replace_entry 3

4:msr   daif, x4
  ret

ASM_GLOBAL ASM_PFX(ArmReplaceLiveTranslationEntrySize)

ASM_PFX(ArmReplaceLiveTranslationEntrySize):
  .long   . - ArmReplaceLiveTranslationEntry
