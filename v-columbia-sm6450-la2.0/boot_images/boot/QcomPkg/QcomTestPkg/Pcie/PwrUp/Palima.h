/** @file Palima.h
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
# 04/04/2022   Ps      Initial Revision, Power up configurations for Palima
#==============================================================================
#**/

#ifndef __PERIPH_PWR_PALIMA_H__
#define __PERIPH_PWR_PALIMA_H__

#include "Config.h"

/****** Target Palima (MTP)  Start *******************************************/

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
RailsCfgType WlanRailsPalima [] = 
{
   {.NodeName = "/pm/smpe2",   .MicroVolts =  1012000},
   {.NodeName = "/pm/smpb11",  .MicroVolts =   966000},
   {.NodeName = "/pm/smpb10",  .MicroVolts =  1800000},
   {.NodeName = "/pm/smpc1",   .MicroVolts =  1900000},
   {.NodeName = "/pm/smpb12",  .MicroVolts =  1350000},
   {.NodeName = "/pm/ldoe7",   .MicroVolts =  2800000},
   {.NodeName = NULL,  .MicroVolts = 0},
};

EnGpioCfgType WlanEnGpioPalima [] = 
{
   {80, 1},  // wlan-en-gpio = <&tlmm 80 0>;
   {0, 0},
};


/* PCIe 1 */
/*
 *  vdd-s1c-supply = <&S1C>;
 * 
 */
RailsCfgType SdxRailsPalima [] = 
{
   {.NodeName = "/pm/smpc1",   .MicroVolts = 0},
   {.NodeName = NULL,  .MicroVolts = 0},
};

EnGpioCfgType SdxEnGpioPalima  [] = 
{
   {47, 1},  // Sdx-en-gpio = <&tlmm 47 0>;
   {0, 0},
};

ClockCfgType SdxClksPalima [] = 
{
   {.ClockName = "rpmh_rf_clk1"},
   {.ClockName = NULL}
};

/*---------------------------------------------  Target Palima (MTP) end  ------*/
ModulePwrupConfigType PalimaWlan = 
   {
      .ConfigLabel = "Palima_WLan",
      .PeriphName = PERIPH_MODULE_NAME_WLAN,
      .PCIeRCIndex = 0,
      .RailsCfg = WlanRailsPalima,
      .EnGpio = WlanEnGpioPalima,
   };

ModulePwrupConfigType PalimaSdx = 
   {
      .ConfigLabel = "Palima_Sdx",
      .PeriphName = PERIPH_MODULE_NAME_SDX,
      .PCIeRCIndex = 1,
      .RailsCfg = SdxRailsPalima,
      .EnGpio = SdxEnGpioPalima,
   };

ModulePwrupConfigType* PalimaModules [] =
{
   &PalimaWlan,
   &PalimaSdx,
   NULL,
};

PlatModulePwrupConfigType PalimaModulesConfig =
{
   .ChipInfoId = 0, // EFICHIPINFO_ID_SM_PALIMA,
   .ChipFamilyId = EFICHIPINFO_FAMILY_PALIMA,
   .PeriphModuleCfg = PalimaModules,
};

#endif  /* __PERIPH_PWR_PALIMA_H__ */

