/** @file Kailua.h
#
#  Config module for Pwrup Application.
#
#  Copyright (c) 2022 Qualcomm Technologies, Inc. All rights reserved.
**/

#ifndef __PERIPH_PWR_KAILUA_H__
#define __PERIPH_PWR_KAILUA_H__

#include "Config.h"

RailsCfgType WlanRailsKailua[] = 
{
   {.NodeName = "/pm/ldob15", .MicroVolts =  1800000},
   {.NodeName = "/pm/smpg5",  .MicroVolts =  1000000},
   {.NodeName = "/pm/smpg2",  .MicroVolts =   980000},
   {.NodeName = "/pm/smpe4",  .MicroVolts =   950000},
   {.NodeName = "/pm/smpg6",  .MicroVolts =  1900000},
   {.NodeName = "/pm/smpg4",  .MicroVolts =  1350000},
   {.NodeName = NULL,         .MicroVolts = 0},
};

EnGpioCfgType WlanEnGpioKailua[] = 
{
   {.GpioNum = 80, .EnableLevel = 1},
   {.GpioNum = 0,  .EnableLevel = 0},
};

ModulePwrupConfigType KailuaWlan = 
{
   .ConfigLabel = "Kailua_WLan",
   .PeriphName = PERIPH_MODULE_NAME_WLAN,
   .PCIeRCIndex = 0,
   .RailsCfg = WlanRailsKailua,
   .EnGpio = WlanEnGpioKailua,
};

ModulePwrupConfigType* KailuaModules[] =
{
   &KailuaWlan,
   NULL,
};

PlatModulePwrupConfigType KailuaModulesConfig =
{
   .ChipInfoId = 0,
   .ChipFamilyId = EFICHIPINFO_FAMILY_KAILUA,
   .PeriphModuleCfg = KailuaModules,
};

#endif  /* __PERIPH_PWR_KAILUA_H__ */

