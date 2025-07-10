/**
 * @file:  SpmiHal.c
 * 
 * Copyright (c) 2013-2014 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2020/06/18 10:10:50 $
 * $Header: //components/rel/core.boot/6.0/QcomPkg/Library/SPMILib/src/core/hal/SpmiHal.c#1 $
 * $Change: 24433599 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 1/20/15  Multiple bus support
 * 10/1/13  Initial Version
 */

#include "SpmiHal.h"
#include "SpmiLogs.h"
#include "SpmiOs.h"

//******************************************************************************
// Global Data
//******************************************************************************


//******************************************************************************
// Public API Functions
//******************************************************************************

Spmi_Result SpmiHal_Init()
{
    return SPMI_SUCCESS;
}

