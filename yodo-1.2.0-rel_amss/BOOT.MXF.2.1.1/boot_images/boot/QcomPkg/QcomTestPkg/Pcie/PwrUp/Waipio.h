/** @file Waipio.h
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

#ifndef __PERIPH_PWR_WAIPIO_H__
#define __PERIPH_PWR_WAIPIO_H__

#include "Config.h"

/****** Target Waipio (MTP)  Start *******************************************/

/* WLAN powerup configuration data */
/*
 * vdd-wlan-aon-supply = <&S2E>; qcom,vdd-wlan-aon-config = <1012000 1012000 0 0 1>;
 * vdd-wlan-dig-supply = <&S11B>; qcom,vdd-wlan-dig-config = <966000 966000 0 0 1>;
 * vdd-wlan-io-supply = <&S10B>; qcom,vdd-wlan-io-config = <1800000 1800000 0 0 1>;
 * vdd-wlan-rfa1-supply = <&S1C>; qcom,vdd-wlan-rfa1-config = <1900000 2100000 0 0 1>;
 * vdd-wlan-rfa2-supply = <&S12B>; qcom,vdd-wlan-rfa2-config = <1350000 1350000 0 0 1>;
 * wlan-ant-switch-supply = <&L7E>; qcom,wlan-ant-switch-config = <2800000 2800000 0 0 1>;
 * 
 * */
RailsCfgType WlanRailsWaipio [] = 
{
   {.NodeName = "/pm/smpe2",   .MicroVolts =  1012000},
   {.NodeName = "/pm/smpb11",  .MicroVolts =   966000},
   {.NodeName = "/pm/smpb10",  .MicroVolts =  1800000},
   {.NodeName = "/pm/smpc1",   .MicroVolts =  1900000},
   {.NodeName = "/pm/smpb12",  .MicroVolts =  1350000},
   {.NodeName = "/pm/ldoe7",   .MicroVolts =  2800000},
   {.NodeName = NULL,  .MicroVolts = 0},
};

EnGpioCfgType WlanEnGpioWaipio [] = 
{
   {80, 1},  // wlan-en-gpio = <&tlmm 80 0>;
   {0, 0},
};


/* PCIe 1 */
/*
 *  vdd-s1c-supply = <&S1C>;
 * 
 */
RailsCfgType SdxRailsWaipio [] = 
{
//   {.NodeName = "/pm/smpc1",   .MicroVolts = 0},
   {.NodeName = NULL,  .MicroVolts = 0},
};

EnGpioCfgType SdxEnGpioWaipio  [] = 
{
//   {47, 1},  // Sdx-en-gpio = <&tlmm 47 0>;
   {0, 0},
};

ClockCfgType SdxClksWaipio [] = 
{
//   {.ClockName = "rpmh_rf_clk1"},
   {.ClockName = NULL}
};

/*---------------------------------------------  Target Waipio (MTP) end  ------*/
ModulePwrupConfigType WaipioWlan = 
   {
      .ConfigLabel = "Waipio_WLan",
      .PeriphName = PERIPH_MODULE_NAME_WLAN,
      .PCIeRCIndex = 0,
      .RailsCfg = WlanRailsWaipio,
      .EnGpio = WlanEnGpioWaipio,
   };

ModulePwrupConfigType WaipioSdx = 
   {
      .ConfigLabel = "Waipio_Sdx",
      .PeriphName = PERIPH_MODULE_NAME_SDX,
      .PCIeRCIndex = 1,
      .RailsCfg = SdxRailsWaipio,
      .EnGpio = SdxEnGpioWaipio,
   };

ModulePwrupConfigType* WaipioModules [] =
{
   &WaipioWlan,
//   &WaipioSdx,
   NULL,
};

PlatModulePwrupConfigType WaipioModulesConfig =
{
   .ChipInfoId = 0, // EFICHIPINFO_ID_SM_WAIPIO,
   .ChipFamilyId = EFICHIPINFO_FAMILY_WAIPIO,
   .PeriphModuleCfg = WaipioModules,
};

#endif  /* __PERIPH_PWR_WAIPIO_H__ */

