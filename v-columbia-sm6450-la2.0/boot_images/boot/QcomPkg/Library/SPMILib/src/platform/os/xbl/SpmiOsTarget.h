/**
 * @file:  SpmiOsTarget.h
 * @brief: Implements platform specific functionality
 * 
 * Copyright (c) 2013 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2021/02/01 23:43:58 $
 * $Header: //components/rel/core.boot/6.0/QcomPkg/Library/SPMILib/src/platform/os/xbl/SpmiOsTarget.h#2 $
 * $Change: 28601830 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 10/1/13  Initial Version
 */
#ifndef SPMIOSTARGET_H
#define	SPMIOSTARGET_H

#include "SpmiTypes.h"
#include "DALSys.h"

typedef struct {
    char   *hwioAddrStr;
    uint32  interruptVec;
} SpmiTargetConfig;

extern DALResult Spmi_ConfigureFetcherChannel(
    DalDeviceHandle *h,
    uint16 periph,
    DALBOOL enableInt,
    uint32 *pChannel);

#endif
