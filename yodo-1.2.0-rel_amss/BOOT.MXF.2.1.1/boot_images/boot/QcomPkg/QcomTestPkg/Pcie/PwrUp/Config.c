/** @file Config.c
#
#  Config module for Pwrup Application.
#
#  Copyright (c) 2020 - 2022 Qualcomm Technologies, Inc. All rights reserved.
**/

#include "Kona.h"
#include "Lahaina.h"
#include "Waipio.h"
#include "Kailua.h"

PlatModulePwrupConfigType* PeripheralDevices[] = 
{
   &KailuaModulesConfig,

   &WaipioModulesConfig,

   &LahainaModulesConfig,

   &KonaModulesConfig,

   NULL,
};

