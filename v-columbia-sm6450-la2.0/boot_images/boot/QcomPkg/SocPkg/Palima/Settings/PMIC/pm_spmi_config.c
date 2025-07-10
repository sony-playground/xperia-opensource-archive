  
/*! \file
*  \n
*  \brief  pm_spmi_config.c
*  \n
*  \n This file contains pmic configuration data specific for SPMI Controller's
      Peripheral for SDM855 device..
*  \n
*  \n &copy; Copyright 2015-2021 QUALCOMM Technologies, Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Palima/Settings/PMIC/pm_spmi_config.c#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------
========================================================================== */

/*-------------------------------------------------------------------------
* Include Files
* ----------------------------------------------------------------------*/

#include "pm_device.h"
#include "SpmiCfg.h"
#include "SpmiBusCfg.h" 

/*-------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
* Static Variable Definitions
* ----------------------------------------------------------------------*/

/* PMIC MMU/SMMU configuration table. */
SpmiCfg_ChannelCfg pm_spmi_channel_cfg [] =
{
/*BID, SID, Periph ID, IRQ Owner, Periph Owner */ 
  /* PMK8350(Tokei)#A */
  /* PM8350(Papio)#B */
  /* PM8350C(Palani)#C */
  /* PM8350B(Puhi)#D */
  /* PMR735A(Seco)#E */
  /* PMR735B(Nalol)#F */
  /* PM8450(Hapuna)#H */
  /* PM80109(Leica2_1)#I */
  /* PM80109(Leica2_2)#J */
  /* PM_SMB1398(Interlagos)_#J */
  /* PM_cota_Interlagos_#K */
  /* PM_cota_Interlagos_#M */
  /* PM_SMB1398(Interlagos)_#N */

  {0, 0, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 0, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 0, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 0, 0x07, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_MASTER  */
  {0, 0, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PON_PBS  */
  {0, 0, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 0, 0x0B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG1  */
  {0, 0, 0x0E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CORE_REG  */
  {0, 0, 0x0F, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_MONITOR1  */
  {0, 0, 0x10, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* RCS_MSGR1  */
  {0, 0, 0x11, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI2  */
  {0, 0, 0x12, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_MASTER2  */
  {0, 0, 0x15, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_MONITOR2  */
  {0, 0, 0x16, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS1_CORE change static table in TZ build */
  {0, 0, 0x17, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS1_CLIENT0  */
  {0, 0, 0x18, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS1_CLIENT1  */
  {0, 0, 0x19, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS1_CLIENT2  */
  {0, 0, 0x1A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS2_CORE  */
  {0, 0, 0x1B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS2_CLIENT0  */
  {0, 0, 0x1C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS2_CLIENT1  */
  {0, 0, 0x1D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS2_CLIENT2  */
  {0, 0, 0x1E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS3_CORE  */
  {0, 0, 0x1F, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS3_CLIENT0  */
  {0, 0, 0x20, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS3_CLIENT1  */
  {0, 0, 0x21, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS3_CLIENT2  */
  {0, 0, 0x22, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* RCS_MSGR2  */
  {0, 0, 0x23, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* RCS_MSGR3  */
  {0, 0, 0x24, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* RCS_MSGR4  */
  {0, 0, 0x25, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS1  */
  {0, 0, 0x26, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS2  */
  {0, 0, 0x27, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS3  */
  {0, 0, 0x28, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS4  */
  {0, 0, 0x29, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PSTM1  */
  {0, 0, 0x2B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS_TIMERS1  */
  {0, 0, 0x2C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS_TIMERS2  */
  {0, 0, 0x2D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS_TIMERS3  */
  {0, 0, 0x36, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_PBS  */
  {0, 0, 0x37, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_CAL  */
  {0, 0, 0x39, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_CMN  */
  {0, 0, 0x50, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* XO  */
  {0, 0, 0x51, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_DIST  */
  {0, 0, 0x54, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* RF_CLK1 for SDR */
  {0, 0, 0x55, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* RF_CLK2 for SDR */
  {0, 0, 0x56, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* RF_CLK3  */
  {0, 0, 0x57, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* RF_CLK4 for Caster */
  {0, 0, 0x58, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* RF_CLK5  */
  {0, 0, 0x59, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LN_BB_CLK1  */
  {0, 0, 0x5A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LN_BB_CLK2  */
  {0, 0, 0x5B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LN_BB_CLK3  */
  {0, 0, 0x5E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* DIV_CLK1  */
  {0, 0, 0x60, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SLEEP_CLK1  */
  {0, 0, 0x61, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* RTC_RW  */
  {0, 0, 0x64, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CALRC3  */
  {0, 0, 0x68, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM_CORE01  */
  {0, 0, 0x69, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM_CORE02  */
  {0, 0, 0x6A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM_CORE03  */
  {0, 0, 0x6B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM_CORE04  */
  {0, 0, 0x6C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM_CORE05  */
  {0, 0, 0x6D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM_CORE06  */
  {0, 0, 0x72, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM03  */
  {0, 0, 0x74, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM05  */
  {0, 0, 0x75, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM06  */
  {0, 0, 0x76, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM07  */
  {0, 0, 0x77, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM08  */
  {0, 0, 0x78, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM09  */
  {0, 0, 0x80, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM17 for SWIRE */
  {0, 0, 0x81, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM18 for SWIRE */
  {0, 0, 0x82, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM19  */
  {0, 0, 0x83, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM20  */
  {0, 0, 0x99, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM42 for display systems */
  {0, 0, 0x9E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM47 spare; previously for QUP */
  {0, 0, 0x9F, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM48 for pon trigger */
  {0, 0, 0xB0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO01 SPMI CLK */
  {0, 0, 0xB1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO02 SPMI DATA */
  {0, 0, 0xB2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO03 Diagnostic GPIO */
  {0, 0, 0xB3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO04 OPTION1 */
  {0, 0, 0xFE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRST_MSTR  */
  {0, 1, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 1, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 1, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 1, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PON_PBS  */
  {0, 1, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 1, 0x0B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG1  */
  {0, 1, 0x0D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VREG_1P8_SYS_PLV  */
  {0, 1, 0x0E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN  */
  {0, 1, 0x0F, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_MONITOR  */
  {0, 1, 0x14, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN_VREG_PMV20  */
  {0, 1, 0x15, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN_COINCELL  */
  {0, 1, 0x1C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS1  */
  {0, 1, 0x1D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS2  */
  {0, 1, 0x1E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS3  */
  {0, 1, 0x36, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_PBS  */
  {0, 1, 0x39, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_CMN  */
  {0, 1, 0x3E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN_VREG_SP  */
  {0, 1, 0x40, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VREF_MSM  */
  {0, 1, 0x5E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* DIV_CLK  */
  {0, 1, 0x8C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO05 Charger insertion PON Trigger */
  {0, 1, 0x8E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO07 Tie to MSM SP block */
  {0, 1, 0x91, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO10 OPTION1 */
  {0, 1, 0x99, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BCAL_VIRTUAL_SLAVE  */
  {0, 1, 0x9A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUCK_CMN_MOD  */
  {0, 1, 0x9B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_CTRL  */
  {0, 1, 0x9D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_FREQ  */
  {0, 1, 0x9E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S2_CTRL  */
  {0, 1, 0xA0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S2_FREQ  */
  {0, 1, 0xA1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_CTRL  */
  {0, 1, 0xA3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_FREQ  */
  {0, 1, 0xA4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S4_CTRL  */
  {0, 1, 0xA6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S4_FREQ  */
  {0, 1, 0xA7, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S5_CTRL  */
  {0, 1, 0xA9, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S5_FREQ  */
  {0, 1, 0xAA, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S6_CTRL  */
  {0, 1, 0xAC, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S6_FREQ  */
  {0, 1, 0xAD, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S7_CTRL  */
  {0, 1, 0xAF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S7_FREQ  */
  {0, 1, 0xB0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S8_CTRL  */
  {0, 1, 0xB2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S8_FREQ  */
  {0, 1, 0xB3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S9_CTRL  */
  {0, 1, 0xB5, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S9_FREQ  */
  {0, 1, 0xB6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S10_CTRL  */
  {0, 1, 0xB7, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S10_PS  */
  {0, 1, 0xB8, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S10_FREQ  */
  {0, 1, 0xB9, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S11_CTRL  */
  {0, 1, 0xBA, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S11_PS  */
  {0, 1, 0xBB, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S11_FREQ  */
  {0, 1, 0xBC, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S12_CTRL  */
  {0, 1, 0xBD, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S12_PS  */
  {0, 1, 0xBE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S12_FREQ  */
  {0, 1, 0xC1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO01  */
  {0, 1, 0xC2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO02  */
  {0, 1, 0xC3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO03  */
  {0, 1, 0xC4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO04  */
  {0, 1, 0xC5, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO05  */
  {0, 1, 0xC6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO06  */
  {0, 1, 0xC7, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO07  */
  {0, 1, 0xC8, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO08  */
  {0, 1, 0xC9, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO09  */
  {0, 1, 0xCA, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO10  */
  {0, 1, 0xE1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* AHC_AGGR  */
  {0, 1, 0xFE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRST_MSTR  */
  {0, 1, 0xFF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM  */
  {0, 2, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 2, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 2, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 2, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PON_PBS  */
  {0, 2, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 2, 0x0B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG1  */
  {0, 2, 0x0E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN  */
  {0, 2, 0x0F, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_MONITOR  */
  {0, 2, 0x1C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS1  */
  {0, 2, 0x1D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS2  */
  {0, 2, 0x1E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS3  */
  {0, 2, 0x48, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BCLBIG_PLM  */
  {0, 2, 0x4A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BCLMDM_PLM  */
  {0, 2, 0x51, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_DIST  */
  {0, 2, 0x5E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* DIV_CLK  */
  {0, 2, 0x8C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO05 AOSS Sleep Indication (for internal RCM usage) */
  {0, 2, 0x99, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BCAL_VIRTUAL_SLAVE  */
  {0, 2, 0x9A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUCK_CMN_MOD  */
  {0, 2, 0x9B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_CTRL  */
  {0, 2, 0x9C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_PS  */
  {0, 2, 0x9D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_FREQ  */
  {0, 2, 0x9E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S2_CTRL  */
  {0, 2, 0xA0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S2_FREQ  */
  {0, 2, 0xA1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_CTRL  */
  {0, 2, 0xA3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_FREQ  */
  {0, 2, 0xA4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S4_CTRL  */
  {0, 2, 0xA6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S4_FREQ  */
  {0, 2, 0xA7, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S5_CTRL  */
  {0, 2, 0xA9, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S5_FREQ  */
  {0, 2, 0xAA, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S6_CTRL  */
  {0, 2, 0xAC, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S6_FREQ  */
  {0, 2, 0xAD, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S7_CTRL  */
  {0, 2, 0xAF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S7_FREQ  */
  {0, 2, 0xB0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S8_CTRL  */
  {0, 2, 0xB2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S8_FREQ  */
  {0, 2, 0xB3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S9_CTRL  */
  {0, 2, 0xB5, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S9_FREQ  */
  {0, 2, 0xB6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S10_CTRL  */
  {0, 2, 0xB8, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S10_FREQ  */
  {0, 2, 0xC1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO01  */
  {0, 2, 0xC2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO02  */
  {0, 2, 0xC3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO03  */
  {0, 2, 0xC4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO04  */
  {0, 2, 0xC5, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO05  */
  {0, 2, 0xC6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO06  */
  {0, 2, 0xC7, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO07  */
  {0, 2, 0xC8, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO08  */
  {0, 2, 0xC9, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO09  */
  {0, 2, 0xCA, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO10  */
  {0, 2, 0xCB, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO11  */
  {0, 2, 0xCC, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO12  */
  {0, 2, 0xCD, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO13  */
  {0, 2, 0xE1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* AHC_AGGR  */
  {0, 2, 0xE4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BOB_CONFIG  */
  {0, 2, 0xE5, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BOB_MONITORING  */
  {0, 2, 0xFE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRST_MSTR  */
  {0, 2, 0xFF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM  */
  {0, 3, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 3, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 3, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 3, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PON_PBS Tokei PON can't write to locked and so leave it unlocked */
  {0, 3, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 3, 0x0B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG1  */
  {0, 3, 0x0E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN  */
  {0, 3, 0x0F, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_MONITOR  */
  {0, 3, 0x14, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN_VREG_AVDD  */
  {0, 3, 0x16, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS_CORE  */
  {0, 3, 0x17, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS_CLIENT0  */
  {0, 3, 0x18, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS_CLIENT1  */
  {0, 3, 0x1C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS1  */
  {0, 3, 0x1D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS2  */
  {0, 3, 0x1E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS3  */
  {0, 3, 0x1F, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS4  */
  {0, 3, 0x36, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_PBS  */
  {0, 3, 0x3A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_CAL  */
  {0, 3, 0x48, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BCLBIG_PLM  */
  {0, 3, 0x4E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* QBG_IRQ  */
  {0, 3, 0x51, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_DIST  */
  {0, 3, 0x5E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* DIV_CLK  */
  {0, 3, 0x88, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO01 VBATT_2S_MID2 */
  {0, 3, 0xC1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO01  */
  {0, 3, 0xFE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRUSTED_PBUS_MASTER  */
  {0, 4, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 4, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 4, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 4, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PON_PBS  */
  {0, 4, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 4, 0x0B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG1  */
  {0, 4, 0x0E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN  */
  {0, 4, 0x0F, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_MONITOR  */
  {0, 4, 0x1C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS1  */
  {0, 4, 0x1D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS2  */
  {0, 4, 0x36, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_CORE_PBS  */
  {0, 4, 0x39, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_CMN  */
  {0, 4, 0x51, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_DIST  */
  {0, 4, 0x5E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* DIV_CLK  */
  {0, 4, 0x8B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO04 OPTION1 */
  {0, 4, 0x99, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BCAL_VIRTUAL_SLAVE  */
  {0, 4, 0x9A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUCK_CMN_MOD  */
  {0, 4, 0x9B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_CTRL  */
  {0, 4, 0x9D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_FREQ  */
  {0, 4, 0x9E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S2_CTRL  */
  {0, 4, 0xA0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S2_FREQ  */
  {0, 4, 0xA1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_CTRL  */
  {0, 4, 0xA2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_PS  */
  {0, 4, 0xA3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_FREQ  */
  {0, 4, 0xC1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO01  */
  {0, 4, 0xC2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO02  */
  {0, 4, 0xC3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO03  */
  {0, 4, 0xC4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO04  */
  {0, 4, 0xC5, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO05  */
  {0, 4, 0xC6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO06  */
  {0, 4, 0xC7, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO07  */
  {0, 4, 0xE1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* AHC_AGGR  */
  {0, 4, 0xFE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRST_MSTR  */
  {0, 4, 0xFF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM  */
  {0, 5, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 5, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 5, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 5, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PON_PBS  */
  {0, 5, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 5, 0x0B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG1  */
  {0, 5, 0x0E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN  */
  {0, 5, 0x1C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS1  */
  {0, 5, 0x1D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS2  */
  {0, 5, 0x36, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_CORE_PBS  */
  {0, 5, 0x39, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_CMN  */
  {0, 5, 0x51, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_DIST  */
  {0, 5, 0x5E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* DIV_CLK  */
  {0, 5, 0x8B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO04 OPTION1 */
  {0, 5, 0xC1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO01  */
  {0, 5, 0xC2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO02  */
  {0, 5, 0xC3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO03  */
  {0, 5, 0xC4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO04  */
  {0, 5, 0xC5, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO05  */
  {0, 5, 0xC6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO06  */
  {0, 5, 0xC7, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO07  */
  {0, 5, 0xC8, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO08  */
  {0, 5, 0xC9, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO09  */
  {0, 5, 0xCA, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO10  */
  {0, 5, 0xCB, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO11  */
  {0, 5, 0xCC, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO12  */
  {0, 5, 0xE1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* AHC_AGGR  */
  {0, 5, 0xFE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRST_MSTR  */
  {0, 5, 0xFF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM  */
  {0, 7, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 7, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 7, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 7, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PON_PBS  */
  {0, 7, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 7, 0x0B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG1  */
  {0, 7, 0x0E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN  */
  {0, 7, 0x0F, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_MONITOR  */
  {0, 7, 0x1C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS1  */
  {0, 7, 0x1D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS2  */
  {0, 7, 0x51, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_DIST  */
  {0, 7, 0x5E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* DIV_CLK  */
  {0, 7, 0x89, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO02 Option Pin decode */
  {0, 7, 0x8A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO03 Option Pin decode */
  {0, 7, 0x8B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO04 Option Pin decode */
  {0, 7, 0x99, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BCAL_VIRTUAL_SLAVE  */
  {0, 7, 0x9A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUCK_CMN_MOD  */
  {0, 7, 0x9B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_CTRL  */
  {0, 7, 0x9D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_FREQ  */
  {0, 7, 0x9E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S2_CTRL  */
  {0, 7, 0xA0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S2_FREQ  */
  {0, 7, 0xA1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_CTRL  */
  {0, 7, 0xA3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_FREQ  */
  {0, 7, 0xA4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S4_CTRL  */
  {0, 7, 0xA6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S4_FREQ  */
  {0, 7, 0xA7, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S5_CTRL  */
  {0, 7, 0xA9, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S5_FREQ  */
  {0, 7, 0xAA, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S6_CTRL  */
  {0, 7, 0xAC, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S6_FREQ  */
  {0, 7, 0xC1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO01  */
  {0, 7, 0xC2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO02  */
  {0, 7, 0xC3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO03  */
  {0, 7, 0xC4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO04  */
  {0, 7, 0xE1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* AHC_AGGR  */
  {0, 7, 0xFE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRST_MSTR  */
  {0, 7, 0xFF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM  */  
  {0, 8, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 8, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 8, 0x07, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM  */
  {0, 8, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 8, 0x2C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG  */
  {0, 8, 0x40, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO01  */
  {0, 8, 0x41, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO02  */
  {0, 8, 0x42, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO03  */
  {0, 8, 0x43, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO04  */
  {0, 8, 0x44, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO05  */
  {0, 8, 0x45, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO06  */
  {0, 8, 0x46, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO07  */
  {0, 8, 0x51, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_LEICA2  */
  {0, 8, 0xC0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO01 switch between I2C and SPMI. When used in I2C mode then also captures I2C interrupts */
  {0, 8, 0xC1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO02 PM8010 Reset */
  {0, 8, 0xE1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* AHC_AGGR  */
  {0, 9, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 8, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 9, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 9, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 9, 0x07, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM  */
  {0, 9, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 9, 0x2C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG  */
  {0, 9, 0x40, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO01  */
  {0, 9, 0x41, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO02  */
  {0, 9, 0x42, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO03  */
  {0, 9, 0x43, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO04  */
  {0, 9, 0x44, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO05  */
  {0, 9, 0x45, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO06  */
  {0, 9, 0x46, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO07  */
  {0, 9, 0x51, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_LEICA2  */
  {0, 9, 0xC0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO01 switch between I2C and SPMI. When used in I2C mode then also captures I2C interrupts */
  {0, 9, 0xC1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO02 PM8010 Reset */
  {0, 9, 0xE1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* AHC_AGGR  */
  {1, 9, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {1, 9, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {1, 9, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {1, 9, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {1, 9, 0xFF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM_CTRL  */
  {1, 11, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {1, 11, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 0xE, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT Broadcast Channel */
  {1, 11, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {1, 11, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {1, 11, 0xFF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM_CTRL  */
  {1, 13, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {1, 13, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {1, 13, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {1, 13, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {1, 13, 0xFF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM_CTRL  */
  {1, 13, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {1, 13, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {1, 13, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {1, 13, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {1, 13, 0xFF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM_CTRL  */
  {0, 0, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 0, 0x33, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* ADC_ADSP  */
  {0, 0, 0x38, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* ADC_TM_PBS  */
  {0, 0, 0x7E, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM15 Owner ADSP */
  {0, 0, 0x7F, SPMI_OWNER_APPS,    SPMI_OWNER_ADSP},   /* SDAM16 */
  {0, 0, 0x86, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM23 for fuel gague */
  {0, 0, 0x87, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM24 for fuel gague */
  {0, 0, 0x88, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM25 for fuel gague */
  {0, 0, 0x89, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM26 for fuel gague */
  {0, 0, 0x8A, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM27 for fuel gague */
  {0, 0, 0x8B, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM28 for fuel gague */
  {0, 0, 0x8C, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM29 for fuel gague */
  {0, 0, 0x8D, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM30 for fuel gague */
  {0, 0, 0x8E, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM31 for fuel gague */
  {0, 0, 0x8F, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM32 for fuel gague */
  {0, 0, 0x90, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM33 for fuel gague */
  {0, 0, 0x91, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM34 for fuel gague */
  {0, 1, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 2, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 2, 0x8A, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO03 OCP Enable 1 */
  {0, 2, 0x8B, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO04 OCP Enable 2 */
  {0, 2, 0x90, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO09 Ext BOOST enable */
  {0, 3, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 3, 0x26, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCPQ_P_CHGR  */
  {0, 3, 0x27, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCPQ_P_DCDC  */
  {0, 3, 0x28, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCPQ_P_BATIF  */
  {0, 3, 0x29, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCPQ_P_USB  */
  {0, 3, 0x2A, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCPQ_P_WLS  */
  {0, 3, 0x2B, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCPQ_P_TYPEC  */
  {0, 3, 0x2C, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCPQ_P_MISC  */
  {0, 3, 0x2D, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* USB_PD_PHY  */
  {0, 3, 0x30, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* ADC_CMN2  */
  {0, 3, 0x39, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* ADC_CMN  */
  {0, 3, 0x3C, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* BMD  */
  {0, 3, 0x3D, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* BSI  */
  {0, 3, 0x4F, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* QBG_MAIN  */
  {0, 3, 0x89, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO02 Wireless Charger Thermistor */
  {0, 3, 0x8A, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO03 AFC_PHY or TA communication(USB_DP_GPIO) */
  {0, 3, 0x8B, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO04 AFC_PHY or TA communication(USB_DM_GPIO) */
  {0, 3, 0x8C, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO05 Type-C Connector Insertion */
  {0, 3, 0x8D, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO06 DAM_FORCE_USB_BOOT */
  {0, 3, 0x8E, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO07 SMB_EN1 */
  {0, 3, 0x8F, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO08 SMB_EN2 */
  {0, 3, 0xF2, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* HAPTICS_BOOST  */
  {0, 4, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 5, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 7, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 8, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 9, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {1, 9, 0x26, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_PERPH0  */
  {1, 9, 0x27, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_PERPH1  */
  {1, 9, 0x28, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_PERPH2  */
  {1, 11, 0x26, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_PERPH0  */
  {1, 11, 0x27, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_PERPH1  */
  {1, 11, 0x28, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_PERPH2  */
  {1, 13, 0x26, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_PERPH0  */
  {1, 13, 0x27, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_PERPH1  */
  {1, 13, 0x28, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_PERPH2  */
  {0, 0, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 0, 0x13, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PON_HLOS  */
  {0, 0, 0x31, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* ADC_APP  */
  {0, 0, 0x34, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* ADC_TM_APP  */
  {0, 0, 0x62, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* RTC_ALARM  */
  {0, 0, 0x63, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* RTC_TIMER  */
  {0, 0, 0x71, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM02  */
  {0, 0, 0x7C, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM13 for ECM */
  {0, 0, 0x7D, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM14 for ECM */
  {0, 0, 0x7F, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM16 */
  {0, 0, 0x84, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM21  */
  {0, 0, 0x85, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM22  */
  {0, 0, 0x92, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM35 haptics */
  {0, 0, 0x93, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM36 haptics */
  {0, 0, 0x94, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM37 haptics */
  {0, 0, 0x95, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM38 haptics */
  {0, 0, 0x96, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM39 haptics */
  {0, 0, 0x97, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM40 haptics */
  {0, 0, 0x98, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM41 HLOS*/
  {0, 0, 0x9A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM43 systems will write with debug builds */
  {0, 0, 0x9B, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM44 haptics */
  {0, 0, 0x9C, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM45 haptics */
  {0, 0, 0x9D, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM46 haptics */
  {0, 1, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 1, 0x0A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {0, 1, 0x88, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO01 Thermistor for ToF */
  {0, 1, 0x89, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO02 Test Purpose VBUS1_DET */
  {0, 1, 0x8B, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO04 DAM_MUX_SEL */
  {0, 1, 0x8D, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO06 Volume (+) Key */
  {0, 1, 0x8F, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO08 USB1 Host_EN */
  {0, 1, 0x90, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO09 BAT_ID */
  {0, 2, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 2, 0x0A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {0, 2, 0x47, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* BCLBIG_COMP  */
  {0, 2, 0x88, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO01 Camera Flash Strobe 1 */
  {0, 2, 0x89, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO02 Camera Flash Strobe 2 */
  {0, 2, 0x8D, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO06 Spare GPIO but used by some OEM for UIM removal detection */
  {0, 2, 0x8E, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO07 PM8003_Enable */
  {0, 2, 0x8F, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO08 TOF BOOST */
  {0, 2, 0x90, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* GPIO09 Ext BOOST enable */
  {0, 2, 0xE8, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PWM1 follow with sandeep if should not be locked */
  {0, 2, 0xE9, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PWM2 follow with sandeep if should not be locked */
  {0, 2, 0xEA, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PWM3 follow with sandeep if should not be locked */
  {0, 2, 0xEB, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PWM4 follow with sandeep if should not be locked */
  {0, 2, 0xEE, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* MVFLASH1 follow with sandeep if should not be locked */
  {0, 2, 0xEF, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* LED follow with sandeep if should not be locked */
  {0, 3, 0x04, SPMI_OWNER_AOP,     SPMI_OWNER_APPS},   /* BUS  */
  {0, 3, 0x0A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {0, 3, 0x19, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PBS_CLIENT2 requested for haptics */
  {0, 3, 0x26, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCPQ_P_CHGR  */
  {0, 3, 0x27, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCPQ_P_DCDC  */
  {0, 3, 0x28, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCPQ_P_BATIF  */
  {0, 3, 0x29, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCPQ_P_USB  */
  {0, 3, 0x2A, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCPQ_P_WLS  */
  {0, 3, 0x2B, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCPQ_P_TYPEC  */
  {0, 3, 0x2C, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCPQ_P_MISC  */
  {0, 3, 0x3C, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* BMD  */
  {0, 3, 0x47, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* BCLBIG_COMP  */
  {0, 3, 0x4F, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* QBG_MAIN  */
  {0, 3, 0xF0, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* HAPTICS_CFG  */
  {0, 3, 0xF1, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* HAPTICS_PATTERN  */
  {0, 3, 0xF8, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* IBB  */
  {0, 3, 0xF9, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* AB  */
  {0, 3, 0xFA, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* OLEDB  */
  {0, 4, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 4, 0x0A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {0, 4, 0x8A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO03 SPARE */
  {0, 5, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 5, 0x0A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {0, 7, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 7, 0x0A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {0, 7, 0x88, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO01 Spare */
  {0, 8, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 8, 0x24, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {0, 9, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 9, 0x24, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {1, 13, 0x26, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_PERPH0  */
  {1, 13, 0x27, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_PERPH1  */
  {1, 13, 0x28, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_PERPH2  */
  {0, 0, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 0, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* PON_PBS  */
  {0, 0, 0x61, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* RTC_RW  */
  {0, 0, 0x70, SPMI_OWNER_TZ,    SPMI_OWNER_TZ},   /* SDAM01  */
  {0, 1, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 1, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* PON_PBS  */
  {0, 1, 0x51, SPMI_OWNER_TZ,    SPMI_OWNER_TZ},   /* CLK_DIST  */
  {0, 3, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* PON_PBS Tokei PON can't write to locked and so leave it unlocked */
  {0, 2, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 3, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */  
  {0, 4, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 5, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 7, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 8, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 9, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 0, 0x32, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* ADC_MDM  */
  {0, 0, 0x35, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* ADC_TM_MDM  */
  {0, 0, 0x50, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* XO  */
  {0, 0, 0x54, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* RF_CLK1 for SDR */
  {0, 0, 0x55, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* RF_CLK2 for SDR */
  {0, 0, 0x57, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* RF_CLK4 for Caster */
  {0, 0, 0x73, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* SDAM04  */
  {0, 0, 0x79, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* SDAM10  */
  {0, 0, 0x7A, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* SDAM11  */
  {0, 0, 0x7B, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* SDAM12  */
  {0, 1, 0x8A, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* GPIO03 Millimeter Wave IC Thermistor (ADC MSS managaes PX_THERM) */  
  {0, 2, 0x49, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* BCL_COMP_MDM  */
  {0, 4, 0x88, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* GPIO01 PA_THERM1 */
  {0, 4, 0x89, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* GPIO02 PA_THERM2  (sbl configs and modem adc used it) */  
  {0, 5, 0x88, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* GPIO01 North Blaster Thermistor */
  {0, 5, 0x89, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* GPIO02 East Blaster Thermistor */
  {0, 5, 0x8A, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* GPIO03 West Blaster Thermistor */
  {0, 0, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 7, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 8, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 9, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 1, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 2, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 3, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 4, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 5, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 0, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 1, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 2, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 3, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 4, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 5, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 7, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 8, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 9, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  
};

/* Number of spmi channels config entries. . */
uint32 pm_spmi_channel_cfg_size[] = {sizeof(pm_spmi_channel_cfg) / sizeof(SpmiCfg_ChannelCfg)};
