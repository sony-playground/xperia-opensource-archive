/** @file Config.c
#
#  Config module for Pwrup Application.
#
#  Copyright (c) 2020 - 2022 Qualcomm Technologies, Inc. All rights reserved.
#
#==============================================================================
#                              EDIT HISTORY
#
#
# when         who     what, where, why
# ----------   ---     ----------------------------------------------------------
# 03/08/2022   ap      Added Netrani
# 03/07/2022   ps      Added Palima
# 01/03/2022   ps      Added Fillmore
# 05/10/2021   yg      Add Waipio
# 07/10/2020   yg      Use Chip family for cfg selection
# 05/27/2020   yg      Initial Revision
#==============================================================================
#**/

#include "Kona.h"
#include "Lahaina.h"
#include "Waipio.h"
#include "fillmore.h"
#include "Palima.h"
#include "Netrani.h"

PlatModulePwrupConfigType* PeripheralDevices[] = 
{
   &FillmoreModulesConfig,
   
   &WaipioModulesConfig,

   &LahainaModulesConfig,

   &KonaModulesConfig,
   
   &PalimaModulesConfig,

   &NetraniModulesConfig,

   NULL,
};

