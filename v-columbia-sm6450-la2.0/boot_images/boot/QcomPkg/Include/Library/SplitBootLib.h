/** @file UefiSplitBoot.h
  UEFI Split boot interface.

  Copyright (c) 2017, 2020 Qualcomm Technologies, Inc.  All Rights Reserved.

  Qualcomm Technologies Proprietary and Confidential.

**/
#ifndef __UEFI_SPLITBOOT_H__
#define __UEFI_SPLITBOOT_H__

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/24/20   md      Added structure that will be passed to InitSplitBoot()
 06/19/17   yg      Created
 
=============================================================================*/

#include <Uefi.h>

#define Boot_Continue_Parameter_Blk_Init_Version   0x00010000
#define Boot_Continue_Parameter_Blk_Version        Boot_Continue_Parameter_Blk_Init_Version

typedef VOID (*BootContinueFnPtr) (VOID*);

/* This function doesn't return if succeeds, instead continues the execution
 * from BootContinue function */
EFI_STATUS InitSplitBoot (BootContinueFnPtr BootContinueFn, VOID* Arg);

VOID AuxCpuCEntry (UINT64 cpu);

typedef struct 
{
   UINT64 Version;
   UINT32 MaxCoreCnt;
   UINT32 EarlyInitCoreCnt;
   UINT32 AvailMaxCoreMask;
}BootContinueParameterBlkType;

#endif  /* __UEFI_SPLITBOOT_H__ */


