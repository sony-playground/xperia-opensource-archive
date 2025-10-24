/**
 * @file:  SpmiMaster.h
 * @brief: Configures the Spmi Master Controller
 * 
 * Copyright (c) 2013-2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2022/08/18 10:15:46 $
 * $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SPMILib/src/core/hal/hoya7/SpmiMaster.h#1 $
 * $Change: 39147961 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 10/1/13  Initial Version
 */
#ifndef SPMIMASTER_H
#define	SPMIMASTER_H

#include "SpmiBusCfg.h"
#include "SpmiUtils.h"
#include "SpmiInfo.h"

Spmi_Result SpmiMaster_ConfigHW(SpmiDevInfo *pDev, uint8 masterId, SpmiBusCfg_ConfigType cfgType);
void SpmiMaster_LoadRadixTree(SpmiDevInfo *pDev, SpmiBusCfg_ChannelCfg* entries, uint32 numEntries);

#endif

