/*! \file pm_config_target.c
 *
 *  \brief This file contains customizable target specific driver settings & PMIC registers.
 *         This file info is taken from Target Component Resource Specific Settings from PDM
 *         that is maintained for each of the targets separately.
 *
 *  &copy; Copyright 2013 - 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header:

when        who         what, where, why
--------    ---         ---------------------------------------------------
11/30/22    rajivr      clk resources update
11/25/22    rajivr      FR83960 changes, enhancements in XO Crystal OFF
11/21/22    rajivr      Buck Min mode updated, Dyn ACC LDO DrvOwner updated
11/10/22    rajivr      Added VRM resource vref_txdac
10/31/22    rajivr      Initial regulators settings update
08/11/22    rajivr      Created, PMIC stubbing code change
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_config_interface.h"
#include "pm_config_target.h"

/*[AccessAllowed, RsrcCategory, AlwaysOn, MinMode, SafetyHR, MinVoltage, MaxVoltage, EnableFixedTime, EnableStepperWarmUpTime, VoltFixedUpTime, VoltFixedDownTime, VoltStepperExtraUpTime, VoltStepperExtraDownTime, VoltDischargeTime, ModeFixedTime , VregReadyEn, VregReadyErrEn, VregWdogTimer]*/
/*[VoltSeqType, EnableSeqType, ModeSeqType, DrvOwnMask, Reserved]*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_a[] =
{
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL,     .SafetyHR = 64 , .MinVoltage = 460 ,      .MaxVoltage = 1100,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0},  // LDO1 MX_A/EBI VDDA
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL,     .SafetyHR = 56 , .MinVoltage = 540 ,      .MaxVoltage = 1000,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0},  // LDO2 MX_C
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL,     .SafetyHR = 48 , .MinVoltage = 720 ,      .MaxVoltage = 950 ,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_HLOS | PM_DRV_ARC,  .Reserved = 0},  // LDO3 PCIe, USB, SGMII 0.9V
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL,     .SafetyHR = 64 , .MinVoltage = 570 ,      .MaxVoltage = 650 ,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_DDR,   .Reserved = 0},  // LDO4 EBI-VDDIO
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL,     .SafetyHR = 40 , .MinVoltage = 1620,      .MaxVoltage = 1980,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0},  // LDO5 SDR_VDDAH,  BBTX_VDDAH,GPS, LNAs, USB-HS
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_ON,   .MinMode = PM_NPM_MODE_VAL,     .SafetyHR = 64 , .MinVoltage = 1800,      .MaxVoltage = 1980,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_AOP,   .Reserved = 0},  // LDO6 PX3,PX7x_1p8
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_ON,   .MinMode = PM_LPM_MODE_VAL,     .SafetyHR = 56 , .MinVoltage = 1620,      .MaxVoltage = 1980,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_DDR,  .Reserved = 0},  // LDO7 PX0, LPDDR4x_VDD1
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL,     .SafetyHR = 40 , .MinVoltage = 552 ,      .MaxVoltage = 904 ,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0},  // LDO8 VDD_NAV
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL,     .SafetyHR = 64 , .MinVoltage = 960 ,      .MaxVoltage = 1300,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_DDR,   .Reserved = 0},  // LDO9 LP4X=1.128, LP2=1.2V
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL,     .SafetyHR = 80 , .MinVoltage = 2970,      .MaxVoltage = 3544,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0},  // LDO10 USB-HS
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL,     .SafetyHR = 256, .MinVoltage = 1650,      .MaxVoltage = 3300,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0},  // LDO11 SIM 1
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL,     .SafetyHR = 32 , .MinVoltage = 1100,      .MaxVoltage = 1304,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_MDMS,   .Reserved = 0},  // LDO12 SDX 1.2V domain, SDR_VDD_PX
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL,     .SafetyHR = 56 , .MinVoltage = 312 ,      .MaxVoltage = 800 ,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0},  // LDO13 SDR_VDDAL
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL,     .SafetyHR = 80 , .MinVoltage = 1100,      .MaxVoltage = 1300,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_HLOS | PM_DRV_ARC,  .Reserved = 0},  // LDO14 VDD_PX11, RefGEN_1p2
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL,     .SafetyHR = 256, .MinVoltage = 1650,      .MaxVoltage = 3000,  .EnableFixedTime = 300,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 0,   .VoltStepperExtraDownTime = 0,   .VoltDischargeTime = 0,   .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0},  // LDO15 SIM 2
};

/*[AccessAllowed, RsrcCategory, AlwaysOn, MinMode, SafetyHR, MinVoltage, MaxVoltage, EnableFixedTime, EnableStepperWarmUpTime, VoltFixedUpTime, VoltFixedDownTime, VoltStepperExtraUpTime, VoltStepperExtraDownTime, VoltDischargeTime, ModeFixedTime , VregReadyEn, VregReadyErrEn, VregWdogTimer]*/
/*[VoltSeqType, EnableSeqType, ModeSeqType, DrvOwnMask, Reserved]*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_a[] =
{
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL,    .SafetyHR = 0,  .MinVoltage = 435,   .MaxVoltage = 1100,  .EnableFixedTime = 500,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 20,  .VoltStepperExtraDownTime = 20,  .VoltDischargeTime = 50,  .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0},  // SMPS1 CX, Q6 and Modem
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_ON,  .MinMode = PM_AUTO_MODE_VAL,   .SafetyHR = 0,  .MinVoltage = 830,   .MaxVoltage = 1414,  .EnableFixedTime = 500,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 20,  .VoltStepperExtraDownTime = 20,  .VoltDischargeTime = 50,  .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0},  // SMPS2 MV 1.224 buck
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL,    .SafetyHR = 0,  .MinVoltage = 382,   .MaxVoltage = 1170,  .EnableFixedTime = 500,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 20,  .VoltStepperExtraDownTime = 20,  .VoltDischargeTime = 50,  .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0},  // SMPS3 LV1 0.824V buck
    {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR,  .AlwaysOn = PM_ON,  .MinMode = PM_AUTO_MODE_VAL,   .SafetyHR = 0,  .MinVoltage = 1574,  .MaxVoltage = 2040,  .EnableFixedTime = 500,  .EnableStepperWarmUpTime = 0,  .VoltFixedUpTime = 0,  .VoltFixedDownTime = 0,  .VoltStepperExtraUpTime = 20,  .VoltStepperExtraDownTime = 20,  .VoltDischargeTime = 50,  .ModeFixedTime  = 20,  .VregReadyEn = PM_SETTLING_EN,  .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_8X_SETTLING_TIMER,  .AopHandling = 0,  .VoltSeqType = VRM_GENERIC_SEQ,  .EnableSeqType = VRM_GENERIC_SEQ,  .ModeSeqType = VRM_GENERIC_SEQ,  .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0},  // SMPS4 HV 1.824V buck
};

/*[AccessAllowed, RsrcCategory, AlwaysOn, EnableFixedTime, EnableSeqType, Reserved, DrvOwnMask, ClkReadyEn, ClkReadyErrEn, ClkWdogTimer, Reserved1]*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_clk_info_type clk_info_a[] =
{
    {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // CLK_DIST
    {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // EMPTY
    {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // EMPTY
    {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // CLK1_RF
    {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // CLK2_RF
    {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // CLK3_RF
	{.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // EMPTY
	{.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // EMPTY
    {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // CLK4_LN
    {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // CLK5_LN
	{.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // EMPTY
	{.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // EMPTY
	{.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // EMPTY
    {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // DIV_CLK1
	{.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // EMPTY
    {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // SLEEP_CLK1
    {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // SLEEP_CLK2
	{.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER,  .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ,  .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,  .ClkReadyEn = PM_SETTLING_DIS,  .ClkReadyErrEn = PM_SETTLING_ERR_DIS,  .ClkWdogTimer = VRM_4X_SETTLING_TIMER,  .Reserved1 = 0},  // TXCO CAL
};

/*Name, PmicIndex, PeriphType, PeriphId, AccessAllowed, SlaveId, BaseAddr, RsrcCategory, EnableAddrOff, EnableFixedTime, EnableSeqType, ModeAddrOff, ModeFixedTime, ModeSeqType,
  VoltAddrOff, VoltFixedTime, VoltSeqType, MaxVoltage, DrvOwnMask, Reserved*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_target_rsrc_info_type target_rsrc_info[] =
{
  //{"vreg.sp", 0, PM_VRM_PERIPH_VREG, 1, {PM_ACCESS_ALLOWED, 0x1, 0x3E00, VRM_RSRC_XO_BUFFER, 0x80, 420, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_SEC, 0}},
  //{"gpio.sp", 0, PM_VRM_PERIPH_GPIO, 7, {PM_ACCESS_ALLOWED, 0x1, 0x8E00, VRM_RSRC_XO_BUFFER, 0x46, 20, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_SEC, 0}},
  //{"rclkha1", 0, PM_VRM_PERIPH_CLK,  5, {PM_ACCESS_ALLOWED, 0x0, 0x5400, VRM_RSRC_XO_BUFFER, 0x45, 20, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_MDMS, 0}},
  {"vrefa0",    0, PM_VRM_PERIPH_CLK,  5, {PM_ACCESS_ALLOWED, 0x0, 0x4100, VRM_RSRC_XO_BUFFER, 0x46, 20, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_MDMS, 0}},
};

/*
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_pstm_rsrc_info_type pstm_a[] =
{
  {.pbs_name = "vrm.aoss", .LowVal = 0x01, .HighVal = 0x02, .SettlingTime = 900, .DrvOwnMask = PM_DRV_AOP ,                                  .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-AOSS_Sleep 1-AOSS_Wake
  {.pbs_name = "vrm.soc",  .LowVal = 0x03, .HighVal = 0x04, .SettlingTime = 900, .DrvOwnMask = PM_DRV_DDR|PM_DRV_TZ|PM_DRV_SEN|PM_DRV_MDMS , .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-SOC_Sleep 1-SOC_Wake
  {.pbs_name = "vrm.wlan", .LowVal = 0x06, .HighVal = 0x05, .SettlingTime = 900, .DrvOwnMask = PM_DRV_WLANBB,                                .DefaultVal = 0, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-WLAN_WA_DISENGAGE 1- WLAN_ENGAGE
};
*/

uint32   num_of_target_rsrc[]= {sizeof(target_rsrc_info)/sizeof(target_rsrc_info[0])} ;
uint32   num_of_pstm_seq[]   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32   num_of_ldo[]        = {sizeof(ldo_rail_a)/sizeof(ldo_rail_a[0]), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32   num_of_smps[]       = {sizeof(smps_rail_a)/sizeof(smps_rail_a[0]), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32   num_of_bob[]        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* ldo_rail[]=
{
    ldo_rail_a, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* smps_rail[]=
{
    smps_rail_a, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* bob_rail[]=
{
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_clk_info_type* clk_info[]=
{
    clk_info_a, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};


__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_pstm_rsrc_info_type* pstm_info[]=
{
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};


__attribute__((section("pm_dram_reclaim_pool")))
uint32 rpmh_drv_id[] = {(uint32)RSC_DRV_AOP};

