/** @file
  Base Library CPU Functions for all architectures.

  Copyright (c) 2006 - 2008, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/



#include <Base.h>
#include <Library/BaseLib.h>

#if defined (QCOM_EDK2_PATCH)
#include <Library/QcomBaseLib.h>
#include <Library/TargetResetLib.h>
#endif
/**
  Executes an infinite loop.

  Forces the CPU to execute an infinite loop. A debugger may be used to skip
  past the loop and the code that follows the loop must execute properly. This
  implies that the infinite loop must not cause the code that follow it to be
  optimized away.

**/
VOID
EFIAPI
CpuDeadLoop (
  VOID
  )
{
  volatile UINTN  Index;

#if defined (QCOM_EDK2_PATCH)
  if (RETAIL)
  {
    TargetPanic();
  }
  SaveSysRegInInfoBlk();
#endif

  for (Index = 0; Index == 0;) {
    CpuPause();
  }
}

#if defined (QCOM_EDK2_PATCH)
VOID
EFIAPI
CpuBreakpoint (
  VOID
  )
{
  CpuDeadLoop();
}
#endif
