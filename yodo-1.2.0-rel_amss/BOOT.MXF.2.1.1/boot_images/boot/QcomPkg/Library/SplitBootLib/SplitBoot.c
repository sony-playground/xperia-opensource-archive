/** @file UefiSplitBoot.c
  UEFI Split boot library stub.

  Copyright (c) 2017-2020 Qualcomm Technologies, Inc.  All Rights Reserved.

  Qualcomm Technologies Proprietary and Confidential.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/24/20   md      Removed reading uefiplat cfg parameters in sec stage. 
 06/19/17   yg      Created
 
=============================================================================*/

#include <Uefi.h>
#include "Library/SplitBootLib.h"
#include "Library/SysSleepLib.h"
#include "Library/SerialPortShLib.h"
#include "MemRegionInfo.h"
#include "Library/UefiCfgLib.h"
#include "Library/PowerSleepLib.h"
#include "UefiInfoBlk.h"
#include "Uart.h"
#include "SchedTargetConfig.h"
#include "Library/TargetInitLib.h"

extern void* _ModuleEntryPoint;

UefiInfoBlkType* GetInfoBlock (VOID);

//extern VOID* thread_list;

void SchedIntfInit (void);
void SchedSocConfigInit (void);

void SchedSocConfigInit (void)
{
  TargetConfigType* SocConfig;
  sched_target_config SchedTargetConfig;

  SocConfig = GetTargetConfigParams ();

  SchedTargetConfig.version = 1;
  SchedTargetConfig.mpidr_to_cpu_num_bits = SocConfig->MpidrToCpuNumBits;
  SchedTargetConfig.mpidr_to_cpu_num_shift = SocConfig->MpidrToCpuNumShift;
  SchedTargetConfig.mpidr_to_clust_num_shift = SocConfig->MpidrToClustNumShift;
  SchedTargetConfig.ipi_sgi_base_num = SocConfig->IpiSgiIntrBaseNum;
  SchedTargetConfig.arch_timer_interrupt_num = SocConfig->ArchTimerInterruptNum;
  SchedTargetConfig.gic_distributor_offset = SocConfig->GicDistributorOffset;
  SchedTargetConfig.gic_redistributor_offset = SocConfig->GicRedistributorOffset;
  SchedTargetConfig.gic_redistributor_stride = SocConfig->GicRedistributorStride;

  if (update_sched_target_config (&SchedTargetConfig) != 0)
  {
    DEBUG((EFI_D_WARN, "Scheduler target config failed\n"));
  }
}

void kern_init (void (*tfn)(void*),    void* arg, 
                void* heap_base,       unsigned long heap_size,
                void* aux_entry_func,  unsigned max_core_count,
                unsigned early_init_core_count);

uint32_t get_sched_lib_version (void);

/* This function doesn't return if succeeds, instead continues the execution
 * from BootContinue function */
EFI_STATUS InitSplitBoot (BootContinueFnPtr BootContinueFn, VOID* Arg)
{
  EFI_STATUS Status;
  UINT32 MaxCoreCnt = 0, EarlyInitCoreCnt = 0;
  UINT32 LibVer;
  BootContinueParameterBlkType *BootContinueParameterBlkPtr;

  if (Arg == NULL)
   BootContinueFn ((void*)0);
  else
  {
    BootContinueParameterBlkPtr = (BootContinueParameterBlkType *)Arg;
    MaxCoreCnt = BootContinueParameterBlkPtr->MaxCoreCnt;
    EarlyInitCoreCnt = BootContinueParameterBlkPtr->EarlyInitCoreCnt;

    /* For now fall back to non split booting */
    MemRegionInfo    KernHeapMemInfo;

    Status = GetMemRegionInfoByName("Sched Heap", &KernHeapMemInfo);
    if (Status != EFI_SUCCESS)
    {
    /* Continue booting */
     BootContinueFn ((void*)0);
    }

    LibVer = get_sched_lib_version ();

    DEBUG((EFI_D_WARN, "Multithread   : ON (Lib ver %d.%d)\r\nCPU Cores     : %d (init %d)\r\n", 
                       LibVer >> 16, LibVer & 0xFFFF, MaxCoreCnt, EarlyInitCoreCnt));

    /* Make the scheduler interface available */
    SchedIntfInit ();

    SchedSocConfigInit ();

    {
     UefiInfoBlkType* InfoBlkPtr;
     InfoBlkPtr = GetInfoBlock ();

//  InfoBlkPtr->ThreadList = thread_list;
    }

    SystemSleepInit (MaxCoreCnt);

    power_sleep_init ();

  /* Launch Scheduler */
    kern_init (BootContinueFn, 0, (void*)KernHeapMemInfo.MemBase, KernHeapMemInfo.MemSize, &_ModuleEntryPoint, MaxCoreCnt, EarlyInitCoreCnt);
  }

  /* Doesn't return on success */
  return EFI_NOT_FOUND;
}

