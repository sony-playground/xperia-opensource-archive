#------------------------------------------------------------------------------
#
# CpuFlushTlb() for ARM
#
# Copyright (c) 2017, 2020 Qualcomm Technologies, Inc. All rights reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
# Portions:
# Copyright (c) 2006 - 2009, Intel Corporation. All rights reserved.<BR>
# Portions copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>
# Portions copyright (c) 2011 - 2013, ARM Ltd. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause-Patent
#
#------------------------------------------------------------------------------

.text
.p2align 2
GCC_ASM_EXPORT(CpuFlushTlb)

#/**
#  Flushes all the Translation Lookaside Buffers(TLB) entries in a CPU.
#
#  Flushes all the Translation Lookaside Buffers(TLB) entries in a CPU.
#
#**/
#VOID
#EFIAPI
#CpuFlushTlb (
#  VOID
#  )#
#
ASM_PFX(CpuFlushTlb):
#if defined(QCOM_EDK2_PATCH)
  tlbi  vmalle1is                // Invalidate Inst TLB and Data TLB
#else
  tlbi  vmalle1                 // Invalidate Inst TLB and Data TLB
#endif  
  dsb   sy
  isb
  ret
