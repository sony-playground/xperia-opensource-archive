/** @file Kona.h
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

#ifndef __PERIPH_PWR_KONA_H__
#define __PERIPH_PWR_KONA_H__

#include "Config.h"

/****** Target 8250 (Kona) MTP  Start *******************************************/

/* WLAN powerup configuration data
 *  vdd-wlan-aon-supply = <&pm8150_s6>; qcom,vdd-wlan-aon-config = <950000 950000 0 0 1>;  S6A
 *  vdd-wlan-dig-supply = <&pm8009_s2>; qcom,vdd-wlan-dig-config = <950000 952000 0 0 1>;  S2F
 *  vdd-wlan-io-supply = <&pm8150_s4>; qcom,vdd-wlan-io-config = <1800000 1800000 0 0 1>;  S4A
 *  vdd-wlan-rfa1-supply = <&pm8150_s5>; qcom,vdd-wlan-rfa1-config = <1900000 1900000 0 0 1>; S5A
 *  vdd-wlan-rfa2-supply = <&pm8150a_s8>; qcom,vdd-wlan-rfa2-config = <1350000 1350000 0 0 1>; S8C
 *  wlan-ant-switch-supply = <&pm8150a_l5>; qcom,wlan-ant-switch-config = <1800000 1800000 0 0 0>; L5C
 */
RailsCfgType WlanRailsKona [] =
{
   {.NodeName = "/pm/smpa6",  .MicroVolts =  950000},
   {.NodeName = "/pm/smpf2",  .MicroVolts =  950000},
   {.NodeName = "/pm/smpa4",  .MicroVolts = 1800000},
   {.NodeName = "/pm/smpa5",  .MicroVolts = 1900000},
   {.NodeName = "/pm/smpc8",  .MicroVolts = 1350000},
   {.NodeName = "/pm/ldoc5",  .MicroVolts = 1800000},
   {.NodeName = NULL,  .MicroVolts = 0},
};

EnGpioCfgType WlanEnGpioKona [] = 
{
   {20, 1},  // wlan-en-gpio = <&tlmm 20 0> 
   {0, 0},
};

/* Wigig */
/*
 * vdd-ldo-supply = <&pm8150_l15>; =>  L15A
 * vddio-supply = <&pm8150_s5>;  => S5A
 */
RailsCfgType WigigRailsKona [] = 
{
   {.NodeName = "/pm/ldoa15", .MicroVolts =   0}, // just use the default values
   {.NodeName = "/pm/smpa5",  .MicroVolts =   0}, // just use the default values
   {.NodeName = NULL,  .MicroVolts = 0},
};

EnGpioCfgType WigigEnGpioKona [] = 
{
   {14, 1}, // Pull down, 2mA
   {0, 0},
};

ClockCfgType WigigClksKona [] = 
{
   {.ClockName = "rpmh_rf_clk1"},
   {.ClockName = NULL}
};

/*---------------------------------------------  Target 8250 (MTP) end  ------*/
ModulePwrupConfigType KonaWlan = 
   {
      .ConfigLabel = "8250_WLan",
      .PeriphName = PERIPH_MODULE_NAME_WLAN,
      .PCIeRCIndex = 0,
      .RailsCfg = WlanRailsKona,
      .EnGpio = WlanEnGpioKona,
   };

ModulePwrupConfigType KonaWigig = 
   {
       .ConfigLabel = "8250_Wigig",
       .PeriphName = PERIPH_MODULE_NAME_WIGIG,
       .PCIeRCIndex = 1,
       .RailsCfg = WigigRailsKona,
       .EnGpio = WigigEnGpioKona,
   };

ModulePwrupConfigType* KonaModules [] = 
{
   &KonaWlan,
   &KonaWigig,
   NULL,
};

PlatModulePwrupConfigType KonaModulesConfig =
{
   .ChipInfoId = 0, // EFICHIPINFO_ID_SM8250,
   .ChipFamilyId = EFICHIPINFO_FAMILY_SM8250,
   .PeriphModuleCfg = KonaModules,
};

#endif  /* __PERIPH_PWR_KONA_H__ */

