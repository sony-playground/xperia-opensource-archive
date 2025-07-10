/*! \file pm_config_target.c
 *
 *  \brief This file contains customizable target specific driver settings & PMIC registers.
 *         This file info is taken from Target Component Resource Specific Settings from PDM
 *         that is maintained for each of the targets separately.
 *
 *  &copy; Copyright 2013 - 2021 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header:

when        who         what, where, why													 CR
--------    ---         ---------------------------------------------------        		--------------
27/09/21    bde      Created by PMIC config tool V. PGA V. CR#
08/03/22    bde      PGA 4.1 updated min max voltage. Rumi+DC validated changes 		CR: 3146940
29/03/22	bde		 VRM Bug SW WA1: S4A vmin = 912+70HR, S5A vmin = 1800+74HR 			CR: 3162133	
06/04/22	bde		 PGA 4.4 updated min max voltage. Rumi+DC validated changes 		CR: 3167297
12/04/22    bde		 Wailua GPIO9 & GPIO6 added for moselle PON trigger					CR: 3164733
19/04/22	bde		 PSTM all ack WA 													CR: 3177675
09/05/22	bde		 L04A resource created/Exposed										CR: 3191756
17/05/22	bde		 [Aurora]VRM Bug SW WA4 changes 									CR: 3198345
23/05/22	bde		 S5A & it's child regs Vmax updated									CR: 3203214
21/07/22	bde		 PSTM all ack changes revert[PSI CR 3248396]						CR: 3249583
02/08/22	bde		 L2A is made AON[WA: USB repeater is leaking current in RBSC state]	CR: 3258727
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
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 830,  .MaxVoltage = 920,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // LDO1 USB SS 0.9V
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 200, .MinVoltage = 2700, .MaxVoltage = 3544, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // LDO2 3V_USB Repeater
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 1080, .MaxVoltage = 1304, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS|PM_DRV_ARC, .Reserved = 0}, // LDO3 MSIP 1.2V
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 8,   .MinVoltage = 1080, .MaxVoltage = 1304, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // LDO4 PX11_1.25V
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 100, .MinVoltage = 1010, .MaxVoltage = 1170, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // LDO5 PX1, LPDDR4x_VDD2
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 100, .MinVoltage = 570,  .MaxVoltage = 650,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR,  .Reserved = 0}, // LDO6 LPDDR4x_VDDQ
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 1700, .MaxVoltage = 1950, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // LDO7 EMMC 1.8V
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 720,  .MaxVoltage = 950,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS|PM_DRV_ARC, .Reserved = 0}, // LDO8 MSIP_0.88V
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 352,  .MaxVoltage = 1100, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // LDO9 LPI_CX
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 344, .MinVoltage = 2700, .MaxVoltage = 3544, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // LDO10 EMMC 3V
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 470,  .MaxVoltage = 1100, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // LDO11 LPI_MX
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 16,  .MinVoltage = 1504, .MaxVoltage = 1980, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // LDO12 DMIC_VDD
   {.AccessAllowed = PM_ACCESS_DISALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 350, .MinVoltage = 1504, .MaxVoltage = 3544, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // LDO13 SPARE
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 40,  .MinVoltage = 1620, .MaxVoltage = 1900, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD, .Reserved = 0}, // LDO14 PPG_VDD, VDDIO
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 64,  .MinVoltage = 1800, .MaxVoltage = 1845, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // LDO15 PX_1.8V, LPDDRx_VDD1, EUSB_1P8, WSA_1P8, WCD_IO, TX_RX
   {.AccessAllowed = PM_ACCESS_DISALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 1504, .MaxVoltage = 3544, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // LDO16 Enable for external LPDDR4x_VDD2 buck (backup option)
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 160, .MinVoltage = 3200, .MaxVoltage = 3544, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD, .Reserved = 0}, // LDO17 PPG_VDDLED
   {.AccessAllowed = PM_ACCESS_ALLOWED, 	.RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 1200,  .MaxVoltage = 1200, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // LDO18 PX_1.2V
};

/*[AccessAllowed, RsrcCategory, AlwaysOn, MinMode, SafetyHR, MinVoltage, MaxVoltage, EnableFixedTime, EnableStepperWarmUpTime, VoltFixedUpTime, VoltFixedDownTime, VoltStepperExtraUpTime, VoltStepperExtraDownTime, VoltDischargeTime, ModeFixedTime , VregReadyEn, VregReadyErrEn, VregWdogTimer]*/
/*[VoltSeqType, EnableSeqType, ModeSeqType, DrvOwnMask, Reserved]*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_a[] =
{
   {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_RET_MODE_VAL,  .SafetyHR = 0, .MinVoltage = 352,  .MaxVoltage = 1100, .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // SMPS1 VDD_CX
   {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_RET_MODE_VAL,  .SafetyHR = 0, .MinVoltage = 352,  .MaxVoltage = 1004,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // SMPS2 GFX, Hamilton_cx optional
   {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_AUTO_MODE_VAL, .SafetyHR = 0, .MinVoltage = 352,  .MaxVoltage = 904,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // SMPS3 NSP
   {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_AUTO_MODE_VAL, .SafetyHR = 0, .MinVoltage = 470,  .MaxVoltage = 1980, .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0}, // SMPS4 LV SUB-REG LDO
   {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_AUTO_MODE_VAL, .SafetyHR = 0, .MinVoltage = 1504, .MaxVoltage = 2040, .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0}, // SMPS5 HV SUB-REG LDO
   {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL,  .SafetyHR = 0, .MinVoltage = 350,  .MaxVoltage = 1100, .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // SMPS6 MXA
   {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_AUTO_MODE_VAL, .SafetyHR = 0, .MinVoltage = 352,  .MaxVoltage = 1100, .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // SMPS7 MM
   {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_AUTO_MODE_VAL, .SafetyHR = 0, .MinVoltage = 490,  .MaxVoltage = 1100, .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // SMPS8 MXC
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_AUTO_MODE_VAL, .SafetyHR = 0, .MinVoltage = 352,  .MaxVoltage = 1100, .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0}, // SMPS9 APC0
   {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL,  .SafetyHR = 0, .MinVoltage = 352,  .MaxVoltage = 952,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime  = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // SMPS10 VDDA_EBI, VDDA_PLL_EBI, VDD_D_EBI
};

/*[AccessAllowed, RsrcCategory, AlwaysOn, EnableFixedTime, EnableSeqType, Reserved, DrvOwnMask, ClkReadyEn, ClkReadyErrEn, ClkWdogTimer, Reserved1]*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_clk_info_type clk_info_a[] =
{
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // LN_BB_CLK1
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // LN_BB_CLK2
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // LN_BB_CLK3
   {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // RF_CLK1 Supply to MSM
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // RF_CLK2
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // RF_CLK3
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // EMPTY
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // EMPTY
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK_DIST
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // SLEEP_CLK1
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // DIV_CLK1
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // DIV_CLK2
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // EMPTY
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // EMPTY
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // EMPTY
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // EMPTY
   {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 0, 	.EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // EMPTY
};

/*Name, PmicIndex, PeriphType, PeriphId, AccessAllowed, SlaveId, BaseAddr, RsrcCategory, EnableAddrOff, EnableFixedTime, EnableSeqType, ModeAddrOff, ModeFixedTime, ModeSeqType,
  VoltAddrOff, VoltFixedTime, VoltSeqType, MaxVoltage, DrvOwnMask, Reserved*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_target_rsrc_info_type target_rsrc_info[] =
{
  {"gpioa6", 0, PM_VRM_PERIPH_GPIO, 6, {PM_ACCESS_ALLOWED, 0x0, 0xC500, VRM_RSRC_XO_BUFFER, 0x46, 20, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_WPSS, 0}},
  {"gpioa9", 0, PM_VRM_PERIPH_GPIO, 9, {PM_ACCESS_ALLOWED, 0x0, 0xC800, VRM_RSRC_XO_BUFFER, 0x44, 20, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_WPSS, 0}},
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_pstm_rsrc_info_type pstm_a[] =
{
  {.pbs_name = "vrm.aoss", .LowVal = 0x01, .HighVal = 0x02, .SettlingTime = 900, .DrvOwnMask = PM_DRV_AOP,                                   .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-AOSS_Sleep 1-AOSS_Wake
  {.pbs_name = "vrm.soc",  .LowVal = 0x03, .HighVal = 0x04, .SettlingTime = 900, .DrvOwnMask = PM_DRV_DDR|PM_DRV_TZ|PM_DRV_AUD,				 .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-SOC_Sleep 1-SOC_Wake
  {.pbs_name = "vrm.wlan", .LowVal = 0x06, .HighVal = 0x05, .SettlingTime = 900, .DrvOwnMask = PM_DRV_AOP,                              	 .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-WLAN_WA_DISENGAGE 1- WLAN_ENGAGE
};

uint32   num_of_target_rsrc[]= {sizeof(target_rsrc_info)/sizeof(target_rsrc_info[0])} ;
uint32   num_of_pstm_seq[]   = {sizeof(pstm_a)/sizeof(pstm_a[0]),0,0,0,0,0,0,0,0,0,0,0,0,0};
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
    pstm_a, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
uint32 rpmh_drv_id[] = {(uint32)RSC_DRV_AOP};

/*Set 0 = No work-around applied, 1 = Disable Parent Child Handling, 2 = Sequencer Bsased WA */
__attribute__((section("pm_dram_reclaim_pool")))
uint32 vrm_sw_wa[] = {(uint32)2};

