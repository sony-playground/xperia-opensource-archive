/** @file TargetInitLib.h
   
  Contains TargetInit specific library functions.

  Copyright (c) 2013,2017 - 2018, 2020, 2021 by Qualcomm Technologies, Inc. All Rights Reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 12/16/20   cm      Updated TimerFrameBaseAddr to UINTN
 02/27/18   yg      Add TargetConfig Params API
 02/27/17   vk      Remove unused API
 01/22/13   vk      Initial Version
=============================================================================*/
#ifndef __TARGET_INIT_LIB_H__
#define __TARGET_INIT_LIB_H__

#include <Uefi.h>

typedef struct
{
    UINT32    MpidrToCpuNumBits;
    UINT32    MpidrToCpuNumShift;
    UINT32    MpidrToClustNumShift;

    // Need 2 consecutive SGI interrupts accessible from NS side
    UINT32    IpiSgiIntrBaseNum;
    UINT32    ArchTimerInterruptNum;

    UINT64    GicDistributorOffset;
    UINT64    GicRedistributorOffset;
    UINT64    GicRedistributorStride;

    UINTN     TimerFrameBaseAddr;
    UINTN     TimerFrameIntrNum;

}TargetConfigType;

VOID
TargetEarlyInit (VOID);

VOID
TargetLateInit (VOID);

TargetConfigType*
GetTargetConfigParams (VOID);

INT32
GetTargetBootCore (VOID);

#endif /* __TARGET_INIT_LIB_H_ */
