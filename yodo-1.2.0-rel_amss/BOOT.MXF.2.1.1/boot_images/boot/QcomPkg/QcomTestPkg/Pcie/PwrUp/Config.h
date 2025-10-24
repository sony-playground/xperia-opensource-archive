/** @file Config.h
#
#  Config module for Pwrup Application.
#
#  Copyright (c) 2020 Qualcomm Technologies, Inc. All rights reserved.
#
#==============================================================================
#                              EDIT HISTORY
#
#
# when         who     what, where, why
# ----------   ---     ----------------------------------------------------------
# 07/10/2020   yg      Use Chip family for cfg selection
# 05/27/2020   yg      Initial Revision
#==============================================================================
#**/

#ifndef __PERIPH_PWR_CONFIG_H__
#define __PERIPH_PWR_CONFIG_H__

#include <Uefi.h>
#include <Library/npa.h>
#include <Protocol/EFIChipInfo.h>

typedef struct {
   CHAR8* NodeName;
   UINTN  MicroVolts;
   npa_client_handle mvSetHandle;
   npa_client_handle EnHandle;
}RailsCfgType;

typedef struct {
   UINT32  GpioNum;
   UINT32  EnableLevel;
}EnGpioCfgType;

typedef struct {
   const char* ClockName;
   UINTN ClkId;
}ClockCfgType;

typedef struct {
   CHAR8*  ConfigLabel;    // Just reference string to help print info
   CHAR8*  PeriphName;     // Match to argument to turn it ON.
   UINTN   PCIeRCIndex;
   RailsCfgType* RailsCfg;
   EnGpioCfgType* EnGpio;
   ClockCfgType* ClkCfg;
}ModulePwrupConfigType;

typedef struct {
   EFIChipInfoIdType  ChipInfoId;
   EFIChipInfoFamilyType  ChipFamilyId;

   ModulePwrupConfigType **PeriphModuleCfg;
}PlatModulePwrupConfigType;

#define PERIPH_MODULE_NAME_WLAN      "wlan"
#define PERIPH_MODULE_NAME_WIGIG     "wigig"
#define PERIPH_MODULE_NAME_SDX       "sdx"

#endif

