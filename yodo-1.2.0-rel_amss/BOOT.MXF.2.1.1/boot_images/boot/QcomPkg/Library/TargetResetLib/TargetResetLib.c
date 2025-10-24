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
11/09/18   kpa     TargetPanic to loop directly instead of calling CpuDeadLoop.
10/01/13   vk      Shutdown on ASSERT
06/17/13   vishalo Initial version
========================================================================*/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/QcomBaseLib.h>
#include <Include/UefiInfoBlk.h>
#include "Library/TargetInitLib.h"
#include "ReadSystemRegisters.h"
#include <Library/CacheMaintenanceLib.h>
#include <Library/KernelLib.h>

#define SMP_MAX_CPUS 8
#define CNTPCT_LO_OFFSET             0x08
#define CNTPCT_HI_OFFSET             0x0C
#define CNTP_CVAL_LO_OFFSET          0x30
#define CNTP_CVAL_HI_OFFSET          0x34

static volatile BOOLEAN SaveSysRegRecursiveFault;

VOID
SaveSysRegInInfoBlk (VOID)
{
  // If fault occured during this function
  // TODO: Shift to using HoB or some mechanism
  // to make this global across all instances of TargetResetLib
  // Currently works for recursive faults
  // occuring in same instance of this lib
  if (SaveSysRegRecursiveFault)
    return;
  
  SaveSysRegRecursiveFault = TRUE;
  
  UefiInfoBlkType* UefiInfoBlkPtr = NULL;
  TargetConfigType *SocConfig = NULL;
  UINTN CpuNum = 0;
  UINTN Mpidr = 0;
  
  UefiInfoBlkPtr = GetInfoBlkPtr ();
  if (UefiInfoBlkPtr == NULL)
    return;

  SocConfig = GetTargetConfigParams ();
  if (SocConfig == NULL)
    return;

  Mpidr = READ_MPIDR_EL1 ();
  CpuNum = (Mpidr & ((1 << SocConfig->MpidrToCpuNumBits) - 1)) >> SocConfig->MpidrToCpuNumShift;
  if (CpuNum >= SMP_MAX_CPUS)
    return;

  UefiInfoBlkPtr->VBAR_EL1[CpuNum]  = READ_VBAR_EL1 ();
  UefiInfoBlkPtr->TPIDR_EL1[CpuNum] = READ_TPIDR_EL1 ();
  UefiInfoBlkPtr->TTBR0_EL1[CpuNum] = READ_TTBR0_EL1 ();
  UefiInfoBlkPtr->TCR_EL1[CpuNum]   = READ_TCR_EL1 ();
  UefiInfoBlkPtr->MAIR_EL1[CpuNum]  = READ_MAIR_EL1 ();
  UefiInfoBlkPtr->CPACR_EL1[CpuNum] = READ_CPACR_EL1 ();
  UefiInfoBlkPtr->SCTLR_EL1[CpuNum] = READ_SCTLR_EL1 ();
  UefiInfoBlkPtr->CntvTval[CpuNum]  = READ_CNTVTVAL ();
  UefiInfoBlkPtr->CntvCval[CpuNum]  = READ_CNTVCVAL ();
  UefiInfoBlkPtr->CntvCtl[CpuNum]   = READ_CNTVCTL ();
  UefiInfoBlkPtr->ISR_EL1[CpuNum]   = READ_ISR_EL1 ();
  UefiInfoBlkPtr->QTMR_CTNV_CVAL_LO = *((volatile UINT32*)(SocConfig->TimerFrameBaseAddr + CNTP_CVAL_LO_OFFSET));
  UefiInfoBlkPtr->QTMR_CTNV_CVAL_HI = *((volatile UINT32*)(SocConfig->TimerFrameBaseAddr + CNTP_CVAL_HI_OFFSET));
  UefiInfoBlkPtr->QTMR_CTNV_LO      = *((volatile UINT32*)(SocConfig->TimerFrameBaseAddr + CNTPCT_LO_OFFSET));
  UefiInfoBlkPtr->QTMR_CTNV_HI      = *((volatile UINT32*)(SocConfig->TimerFrameBaseAddr + CNTPCT_HI_OFFSET));

  return;
}

/**
  Precondition: PmicShutdownBootLib has been called to set target reset behavior. Currently, this is done SEC.
**/
VOID
TargetPanic (VOID)
{
  volatile UINTN  Index;
  UefiInfoBlkType* UefiInfoBlkPtr = NULL;

  SaveSysRegInInfoBlk ();
  
  UefiInfoBlkPtr = GetInfoBlkPtr ();
  if (UefiInfoBlkPtr != NULL)
  {
    WriteBackInvalidateDataCacheRange ((VOID*)UefiInfoBlkPtr, sizeof (UefiInfoBlkType));
  }
  
  WatchDogForceBite();
  #if 0
  if (Status != EFI_SUCCESS)
  {
      /* This register controls the PSHOLD value. 
     1: Asserted
     0: Deasserted */
     MmioWrite32 (PcdGet32 (PcdPsHoldAddress), 0);
  }
  #endif
 
  /* Loop here until reset is complete */
  for (Index = 0; Index == 0;);
}

