/** @file Waipio.h
#
#  Config module for Pwrup Application.
#
#  Copyright (c) 2022 Qualcomm Technologies, Inc. All rights reserved.
#
#==============================================================================
#                              EDIT HISTORY
#
#
# when         who     what, where, why
# ----------   ---     ----------------------------------------------------------
# 01/03/2022   ps      Initial Revision. Fillmore Chip family for cfg selection
#==============================================================================
#**/

#ifndef __PERIPH_PWR_FILLMORE_H__
#define __PERIPH_PWR_FILLMORE_H__

#include "Config.h"

/****** Target Fillmore (MTP)  Start *******************************************/

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
RailsCfgType WlanRailsFillmore [] = 
{
    {.NodeName = "/pm/ldob6",    .MicroVolts =   1200000},
    {.NodeName = "/pm/ldoc10",   .MicroVolts =  880000},
    {.NodeName = "/pm/ldoc11",   .MicroVolts =  2800000},
    {.NodeName = "/pm/smpb8",    .MicroVolts =   1256000},
    {.NodeName = "/pm/smpb1",    .MicroVolts =  1824000},
    {.NodeName = "/pm/smpc1",    .MicroVolts =  2200000},
    {.NodeName = "/pm/smpb7",    .MicroVolts =  952000},
    {.NodeName = NULL,           .MicroVolts = 0},
};

EnGpioCfgType WlanEnGpioFillmore [] = 
{
   {49, 1},  // wlan-en-gpio = <&tlmm 49 0>;
   {0, 0},
};

/*---------------------------------------------  Target Fillmore (MTP) end  ------*/
ModulePwrupConfigType FillmoreWlan = 
   {
      .ConfigLabel = "fillmore_WLan",
      .PeriphName = PERIPH_MODULE_NAME_WLAN,
      .PCIeRCIndex = 0,
      .RailsCfg = WlanRailsFillmore,
      .EnGpio = WlanEnGpioFillmore,
   };

ModulePwrupConfigType* FillmoreModules [] =
{
   &FillmoreWlan,
   NULL,
};

PlatModulePwrupConfigType FillmoreModulesConfig =
{
   .ChipInfoId = 0, // EFICHIPINFO_ID_SM_FILLMORE,
   .ChipFamilyId = EFICHIPINFO_FAMILY_FILLMORE,
   .PeriphModuleCfg = FillmoreModules,
};

#endif  /* __PERIPH_PWR_FILLMORE_H__ */

