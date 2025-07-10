/**
  @file TargetResetLib.c
 
  @brief Target Specific Reset Functions
 
  Copyright (c) 2013,2018,2021 by Qualcomm Technologies, Inc. All Rights Reserved.
**/

/*=======================================================================
                        Edit History

when       who     what, where, why
--------   ----    --------------------------------------------------- 
04/27/21   am      Added SaveSysRegInInfoBlk function
06/17/13   vishalo Initial version
========================================================================*/

#include <Uefi.h>
#include <Library/BaseLib.h>

/**
  Empty function for NULLLib
**/
VOID 
SaveSysRegInInfoBlk (VOID)
{
  return;
}

/**
  Target panic
**/
VOID
TargetPanic (VOID)
{
  SaveSysRegInInfoBlk();
  /* Loop here indefinitely */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfor-loop-analysis"
  for (UINTN Index = 0; Index == 0;);
#pragma clang diagnostic pop
}

