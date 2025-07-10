/**
 * @file:  SpmiOsTarget.h
 * @brief: Implements platform specific functionality
 * 
 * Copyright (c) 2013 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2020/06/18 10:10:50 $
 * $Header: //components/rel/core.boot/6.0/QcomPkg/Library/SPMILib/src/platform/os/bare/SpmiOsTarget.h#1 $
 * $Change: 24433599 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 10/1/13  Initial Version
 */
#ifndef SPMIOSTARGET_H
#define	SPMIOSTARGET_H

#include "SpmiTypes.h"

typedef struct {
    char   *hwioAddrStr;
    uint32  interruptVec;
} SpmiTargetConfig;

#endif
