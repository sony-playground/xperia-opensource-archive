/** @file Lahaina.h
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

#ifndef __PERIPH_PWR_LAHAINA_H__
#define __PERIPH_PWR_LAHAINA_H__

#include "Config.h"

/****** Target Lahaina (MTP)  Start *******************************************/

/* WLAN powerup configuration data */
/*
 * vdd-wlan-aon-supply = <&S2E>; qcom,vdd-wlan-aon-config = <950000 952000 0 0 1>;
 * vdd-wlan-dig-supply = <&S11B>; qcom,vdd-wlan-dig-config = <950000 952000 0 0 1>;
 * vdd-wlan-io-supply = <&S10B>; qcom,vdd-wlan-io-config = <1800000 1800000 0 0 1>;
 * vdd-wlan-rfa1-supply = <&S1C>; qcom,vdd-wlan-rfa1-config = <1880000 1880000 0 0 1>;
 * vdd-wlan-rfa2-supply = <&S12B>; qcom,vdd-wlan-rfa2-config = <1350000 1350000 0 0 1>;
 * wlan-ant-switch-supply = <&L7E>; qcom,wlan-ant-switch-config = <2800000 2800000 0 0 0>;
 * 
 * */
RailsCfgType WlanRailsLahaina [] = 
{
   {.NodeName = "/pm/smpe2",   .MicroVolts =   950000},
   {.NodeName = "/pm/smpb11",  .MicroVolts =   950000},
   {.NodeName = "/pm/smpb10",  .MicroVolts =  1800000},
   {.NodeName = "/pm/smpc1",   .MicroVolts =  1880000},
   {.NodeName = "/pm/smpb12",  .MicroVolts =  1350000},
   {.NodeName = "/pm/ldoe7",   .MicroVolts =  2800000},
   {.NodeName = NULL,  .MicroVolts = 0},
};

EnGpioCfgType WlanEnGpioLahaina [] = 
{
   {64, 1},  // wlan-en-gpio = <&tlmm 64 0>;
   {0, 0},
};


/* Wigig */
/*
 *  vdd-s1c-supply = <&S1C>;
 * 
 */
RailsCfgType WigigRailsLahaina [] = 
{
   {.NodeName = "/pm/smpc1",   .MicroVolts = 0},
   {.NodeName = NULL,  .MicroVolts = 0},
};

EnGpioCfgType WigigEnGpioLahaina  [] = 
{
   {47, 1},  // wigig-en-gpio = <&tlmm 47 0>;
   {0, 0},
};

ClockCfgType WigigClksLahaina [] = 
{
   {.ClockName = "rpmh_rf_clk1"},
   {.ClockName = NULL}
};

/*---------------------------------------------  Target Lahaina (MTP) end  ------*/
ModulePwrupConfigType LahainaWlan = 
   {
      .ConfigLabel = "Lahaina_WLan",
      .PeriphName = PERIPH_MODULE_NAME_WLAN,
      .PCIeRCIndex = 0,
      .RailsCfg = WlanRailsLahaina,
      .EnGpio = WlanEnGpioLahaina,
   };

ModulePwrupConfigType LahainaWigig = 
   {
      .ConfigLabel = "Lahaina_Wigig",
      .PeriphName = PERIPH_MODULE_NAME_WIGIG,
      .PCIeRCIndex = 1,
      .RailsCfg = WigigRailsLahaina,
      .EnGpio = WigigEnGpioLahaina,
   };

ModulePwrupConfigType* LahainaModules [] =
{
   &LahainaWlan,
   &LahainaWigig,
   NULL,
};

PlatModulePwrupConfigType LahainaModulesConfig =
{
   .ChipInfoId = 0, // EFICHIPINFO_ID_SM_LAHAINA,
   .ChipFamilyId = EFICHIPINFO_FAMILY_LAHAINA,
   .PeriphModuleCfg = LahainaModules,
};

#endif  /* __PERIPH_PWR_LAHAINA_H__ */

