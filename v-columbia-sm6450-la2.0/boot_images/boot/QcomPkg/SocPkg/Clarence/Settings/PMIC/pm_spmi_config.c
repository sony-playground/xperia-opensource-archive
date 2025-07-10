  
/*! \file
*  \n
*  \brief  pm_spmi_config.c
*  \n
*  \n This file contains pmic configuration data specific for SPMI Controller's
      Peripheral for SDM855 device..
*  \n
*  \n &copy; Copyright 2015-2023 QUALCOMM Technologies, Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.0.2/QcomPkg/SocPkg/Netrani/Settings/PMIC/pm_spmi_config.c#4 $

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
  /* PM6450(Bompoka)#B */
  /* PMI632B(Nebula)#C */
  /* PM80109(Leica2)#E */
  /* PMG1110(SecoJr)#G */
  /* PM7250B (Tioman) #I, #J */
  {0, 0, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 0, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
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
  {0, 0, 0x16, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS1_CORE  */
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
  {0, 0, 0xB2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO03 Core Leica2 Reset */
  {0, 0, 0xB3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO04 Tokei Option */
  {0, 0, 0xFE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRST_MSTR  */
  {0, 1, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID_BASE  */
  {0, 1, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS_BASE  */
  {0, 1, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT_BASE  */
  {0, 1, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_BASE  */
  {0, 1, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PON_PBS_BASE  */
  {0, 1, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_BASE  */
  {0, 1, 0x0B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG1_BASE  */
  {0, 1, 0x0D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VREG_1P8_SYS_PLV_BASE  */
  {0, 1, 0x0E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN_BASE  */
  {0, 1, 0x0F, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_MONITOR_BASE  */
  {0, 1, 0x14, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN_VREG_PMV20_BASE  */
  {0, 1, 0x15, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN_COINCELL_BASE  */
  {0, 1, 0x1C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS1_BASE  */
  {0, 1, 0x1D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS2_BASE  */
  {0, 1, 0x1E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS3_BASE  */
  {0, 1, 0x36, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_PBS_BASE  */
  {0, 1, 0x39, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_CMN_BASE  */
  {0, 1, 0x40, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VREF_MSM_BASE  */
  {0, 1, 0x51, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_DIST_BASE  */
  {0, 1, 0x5E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* DIV_CLK_BASE  */
  {0, 1, 0x90, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO09_BASE AOSS Sleep Indicator */
  {0, 1, 0x99, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BCAL_VIRTUAL_SLAVE_BASE  */
  {0, 1, 0x9A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUCK_CMN_MOD_BASE  */
  {0, 1, 0x9B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_CTRL_BASE  */
  {0, 1, 0x9C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_PS_BASE  */
  {0, 1, 0x9D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_FREQ_BASE  */
  {0, 1, 0x9E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S2_CTRL_BASE  */
  {0, 1, 0x9F, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S2_PS_BASE  */
  {0, 1, 0xA0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S2_FREQ_BASE  */
  {0, 1, 0xA1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_CTRL_BASE  */
  {0, 1, 0xA2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_PS_BASE  */
  {0, 1, 0xA3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S3_FREQ_BASE  */
  {0, 1, 0xA4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S4_CTRL_BASE  */
  {0, 1, 0xA5, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S4_PS_BASE  */
  {0, 1, 0xA6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S4_FREQ_BASE  */
  {0, 1, 0xA7, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S5_CTRL_BASE  */
  {0, 1, 0xA8, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S5_PS_BASE  */
  {0, 1, 0xA9, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S5_FREQ_BASE  */
  {0, 1, 0xAA, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S6_CTRL_BASE  */
  {0, 1, 0xAB, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S6_PS_BASE  */
  {0, 1, 0xAC, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S6_FREQ_BASE  */
  {0, 1, 0xAD, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S7_CTRL_BASE  */
  {0, 1, 0xAE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S7_PS_BASE  */
  {0, 1, 0xAF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S7_FREQ_BASE  */
  {0, 1, 0xB0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S8_CTRL_BASE  */
  {0, 1, 0xB1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S8_PS_BASE  */
  {0, 1, 0xB2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S8_FREQ_BASE  */
  {0, 1, 0xB3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S9_CTRL_BASE  */
  {0, 1, 0xB4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S9_PS_BASE  */
  {0, 1, 0xB5, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S9_FREQ_BASE  */
  {0, 1, 0xC1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO01_BASE  */
  {0, 1, 0xC2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO02_BASE  */
  {0, 1, 0xC3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO03_BASE  */
  {0, 1, 0xC4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO04_BASE  */
  {0, 1, 0xC5, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO05_BASE  */
  {0, 1, 0xC6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO06_BASE  */
  {0, 1, 0xC7, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO07_BASE  */
  {0, 1, 0xC8, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO08_BASE  */
  {0, 1, 0xC9, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO09_BASE  */
  {0, 1, 0xCA, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO10_BASE  */
  {0, 1, 0xCB, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO11_BASE  */
  {0, 1, 0xCC, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO12_BASE  */
  {0, 1, 0xCD, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO13_BASE  */
  {0, 1, 0xCE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO14_BASE  */
  {0, 1, 0xCF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO15_BASE  */
  {0, 1, 0xD0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO16_BASE  */
  {0, 1, 0xD1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO17_BASE  */
  {0, 1, 0xD2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO18_BASE  */
  {0, 1, 0xD3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO19_BASE  */
  {0, 1, 0xD4, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO20_BASE  */
  {0, 1, 0xD5, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO21_BASE  */
  {0, 1, 0xD6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO22_BASE  */
  {0, 1, 0xD7, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO23_BASE  */
  {0, 1, 0xD8, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO24_BASE  */
  {0, 1, 0xD9, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO25_BASE  */
  {0, 1, 0xDA, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO26_BASE  */
  {0, 1, 0xDB, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO27_BASE  */
  {0, 1, 0xDC, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO28_BASE  */
  {0, 1, 0xE1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* AHC_AGGR1_BASE  */
  {0, 1, 0xE2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* AHC_AGGR2_BASE  */
  {0, 1, 0xFE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRST_MSTR_BASE  */
  {0, 1, 0xFF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM_BASE  */
  {0, 2, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 2, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 2, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 2, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_S  */
  {0, 2, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PON  */
  {0, 2, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 2, 0x3C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN  */
  {0, 2, 0x3E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BCLBIG_PLM  */
  {0, 2, 0x59, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_DIST  */
  {0, 2, 0x71, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS_CLIENT0  */
  {0, 2, 0x72, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS_CLIENT1 SLEEP ENTRY/EXIT */
  {0, 2, 0x75, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS1  */
  {0, 2, 0x76, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS2  */
  {0, 2, 0x77, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS3  */
  {0, 2, 0xB2, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM3 AOP */
  {0, 2, 0xB3, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SDAM4 SPARE */
  {0, 3, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID1  */
  {0, 4, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 4, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 4, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 4, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 4, 0x07, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM  */
  {0, 4, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 4, 0x2C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG  */
  {0, 4, 0x40, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO01  */
  {0, 4, 0x41, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO02  */
  {0, 4, 0x42, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO03  */
  {0, 4, 0x43, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO04  */
  {0, 4, 0x44, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO05  */
  {0, 4, 0x45, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO06  */
  {0, 4, 0x46, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* LDO07  */
  {0, 4, 0x51, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_LEICA2  */
  {0, 4, 0xC0, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO01 spare */
  {0, 4, 0xC1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO02 spare */
  {0, 4, 0xE1, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* AHC_AGGR  */
  {0, 6, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 6, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 6, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 6, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 6, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PON_PBS  */
  {0, 6, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 6, 0x0B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG1  */
  {0, 6, 0x0E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN  */
  {0, 6, 0x1C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS1  */
  {0, 6, 0x1D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS2  */
  {0, 6, 0x51, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_DIST  */
  {0, 6, 0x5E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* DIV_CLK  */
  {0, 6, 0x8B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO04  */
  {0, 6, 0x99, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BCAL_VIRTUAL_SLAVE  */
  {0, 6, 0x9A, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUCK_CMN_MOD  */
  {0, 6, 0x9B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_CTRL  */
  {0, 6, 0x9C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_PS  */
  {0, 6, 0x9D, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* S1_FREQ  */
  {0, 6, 0xFE, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRST_MSTR  */
  {0, 6, 0xFF, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* TRIM  */
  {0, 8, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID  */
  {0, 8, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BUS  */
  {0, 8, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT  */
  {0, 8, 0x06, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI  */
  {0, 8, 0x08, SPMI_OWNER_APPS,    SPMI_OWNER_AOP},   /* PON  */
  {0, 8, 0x09, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC  */
  {0, 8, 0x1E, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* BCLBIG_PLM  */
  {0, 8, 0x2C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MBG1  */
  {0, 8, 0x30, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_FG7_CMN2  */
  {0, 8, 0x36, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_FG3_PBS  */
  {0, 8, 0x37, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_FG4_CAL  */
  {0, 8, 0x39, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* ADC_FG6_CMN  */
  {0, 8, 0x3C, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* VDDGEN  */
  {0, 8, 0x59, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* CLK_DIST  */
  {0, 8, 0x5B, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* DIV_CLK1  */
  {0, 8, 0x66, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* SPMI_MONITOR  */
  {0, 8, 0x71, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS_CLIENT0  */
  {0, 8, 0x72, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* PBS_CLIENT1  */
  {0, 8, 0x73, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS1  */
  {0, 8, 0x74, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS2  */
  {0, 8, 0x75, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* MISC_PBS3  */
  {0, 8, 0xC6, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO07  */
  {0, 8, 0xC8, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO09 FMB1 (Forced USB Boot ) */
  {0, 8, 0xC9, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* GPIO10 FMB2 (Select between DP/DM and UART) */
  {0, 9, 0x01, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* REVID1  */
  {0, 0, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 0, 0x33, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* ADC_ADSP  */
  {0, 0, 0x38, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* ADC_TM_PBS  */
  {0, 0, 0x7E, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM15 Owner ADSP */
  {0, 0, 0x7F, SPMI_OWNER_APPS,    SPMI_OWNER_ADSP},   /* SDAM16 as per charger team UEFI needs to write to it and ADSP needs to read it */
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
  {0, 1, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},    /* BUS_BASE  */
  {0, 1, 0x8A, SPMI_OWNER_APPS,    SPMI_OWNER_ADSP},   /* GPIO03_BASE UFCS_ELDO_EN */
  {0, 2, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},    /* BUS  */
  {0, 2, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},    /* PON  */
  {0, 2, 0x10, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_CHGR  */
  {0, 2, 0x11, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_DCDC  */
  {0, 2, 0x12, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_BATIF  */
  {0, 2, 0x13, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_USB  */
  {0, 2, 0x15, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_TYPE_C  */
  {0, 2, 0x16, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_MISC  */
  {0, 2, 0x18, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_FREQ  */
  {0, 2, 0x19, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_OTP_HDR  */
  {0, 2, 0x1A, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* BMD  */
  {0, 2, 0x32, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* ADC_QG2_MDM  */
  {0, 2, 0x37, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* ADC_QG4_CAL  */
  {0, 2, 0x48, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* QGAUGE  */
  {0, 2, 0xB0, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM1 SCHG/FLASH */
  {0, 2, 0xB1, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM2 QG */
  {0, 2, 0xC0, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO01 Type C Connector Therm/FMB1 */
  {0, 2, 0xC1, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO02 SMB Charger Enable */
  {0, 2, 0xC2, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO03 Charger Skin Therm */
  {0, 2, 0xC3, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO04 SMB Therm */
  {0, 2, 0xC6, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO07 SMB_VCHG_P / Vsync */
  {0, 2, 0xC7, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO08 SMB_VCHG_N / Factory Mode boot 2 */
  {0, 4, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 6, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 8, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_ADSP},   /* BUS  */
  {0, 8, 0x08, SPMI_OWNER_APPS,    SPMI_OWNER_ADSP},   /* PON  */
  {0, 8, 0x10, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_P_CHGR  */
  {0, 8, 0x11, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_P_DCDC  */
  {0, 8, 0x12, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_P_BATIF  */
  {0, 8, 0x13, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_P_USB  */
  {0, 8, 0x14, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_P_DC  */
  {0, 8, 0x15, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_P_TYPEC  */
  {0, 8, 0x16, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_P_MISC  */
  {0, 8, 0x17, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* USB_PD_PHY  */
  {0, 8, 0x18, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_P_FREQ  */
  {0, 8, 0x19, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SCHG_P_OTP_HDR  */
  {0, 8, 0x1A, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* BMD  */
  {0, 8, 0x32, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* ADC_FG2_MDM  */
  {0, 8, 0x48, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* QGAUGE  */
  {0, 8, 0xB0, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM1  */
  {0, 8, 0xB1, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* SDAM2  */
  {0, 8, 0xC5, SPMI_OWNER_ADSP,    SPMI_OWNER_ADSP},   /* GPIO06 SMB Status */
  {0, 0, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 0, 0x13, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PON_HLOS  */
  {0, 0, 0x31, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* ADC_APP  */
  {0, 0, 0x34, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* ADC_TM_APP  */
  {0, 0, 0x62, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* RTC_ALARM  */
  {0, 0, 0x63, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* RTC_TIMER  */
  {0, 0, 0x71, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM02  */
  {0, 0, 0x7C, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM13 for ECM */
  {0, 0, 0x7D, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM14 for ECM */
  {0, 0, 0x7F, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM16 as per charger team UEFI needs to write to it and ADSP needs to read it */
  {0, 0, 0x84, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM21  */
  {0, 0, 0x85, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM22  */
  {0, 0, 0x92, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM35 haptics */
  {0, 0, 0x93, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM36 haptics */
  {0, 0, 0x94, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM37 haptics */
  {0, 0, 0x95, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM38 haptics */
  {0, 0, 0x96, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM39 haptics */
  {0, 0, 0x97, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM40 haptics */
  {0, 0, 0x98, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM41 for display systems */
  {0, 0, 0x9A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM43 systems will write with debug builds */
  {0, 0, 0x9B, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM44 haptics */
  {0, 0, 0x9C, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM45 haptics */
  {0, 0, 0x9D, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM46 haptics */
  {0, 0, 0xB0, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO01 Rear Camera Thermistor */
  {0, 0, 0xB1, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},
  {0, 1, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS_BASE  */
  {0, 1, 0x0A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM_BASE  */
  {0, 1, 0x88, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO01_BASE SD Card Detect */
  {0, 1, 0x89, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO02_BASE Quite Thermistor */
  {0, 1, 0x8A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO03_BASE UFCS_ELDO_EN */
  {0, 1, 0x8B, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},
  {0, 1, 0x8C, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO05_BASE Rear Camera FLASH Thermistor */
  {0, 1, 0x8D, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO06_BASE 3rd party WLED enable */
  {0, 1, 0x8E, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO07_BASE 3rd party WLED PWM control */
  {0, 1, 0x8F, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO08_BASE External PON Trgger/Charger Insertion PON Trigger */
  {0, 1, 0xE8, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PWM1_BASE  */
  {0, 2, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 2, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* PON  */
  {0, 2, 0x10, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_CHGR  */
  {0, 2, 0x11, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_DCDC  */
  {0, 2, 0x12, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_BATIF  */
  {0, 2, 0x13, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_USB  */
  {0, 2, 0x15, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_TYPE_C  */
  {0, 2, 0x16, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_MISC  */
  {0, 2, 0x18, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_FREQ  */
  {0, 2, 0x19, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_OTP_HDR  */
  {0, 2, 0x1A, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* BMD  */
  {0, 2, 0x24, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {0, 2, 0x2C, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* MBG1  */
  {0, 2, 0x30, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* ADC_QG7_CMN2 Can be assigned to AOP */
  {0, 2, 0x31, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* ADC_QG1_USR  */
  {0, 2, 0x32, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* ADC_QG2_MDM  */
  {0, 2, 0x35, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* ADC_QG5_BTM4  */
  {0, 2, 0x37, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* ADC_QG4_CAL  */
  {0, 2, 0x39, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* ADC_QG6_CMN Can be assigned to AOP */
  {0, 2, 0x3D, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* BCLBIG_COMP  */
  {0, 2, 0x48, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* QGAUGE  */
  {0, 2, 0x5B, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* DIV_CLK1  */
  {0, 2, 0x73, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PBS_CLIENT2  */
  {0, 2, 0x74, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PBS_CLIENT3  */
  {0, 2, 0xA6, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SCHG_M_FLASH  */
  {0, 2, 0xB0, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SDAM1 SCHG/FLASH */
  {0, 2, 0xB1, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SDAM2 QG */
  {0, 2, 0xB4, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM5 BTM4 */
  {0, 2, 0xB5, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM6 BTM2 */
  {0, 2, 0xB6, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM7 PPG */
  {0, 2, 0xB7, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM8 LCDB */
  {0, 2, 0xC0, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO01 Type C Connector Therm/FMB1 */
  {0, 2, 0xC2, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO03 Charger Skin Therm */
  {0, 2, 0xC3, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO04 SMB Therm */
  {0, 2, 0xC4, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO05 Display VDDIO eLDO enable/FMB2 */
  {0, 2, 0xC5, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO06 Display DDIC eLDO enable */
  {0, 3, 0x57, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* VIB_LDO  */
  {0, 3, 0xB3, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PWM1  */
  {0, 3, 0xB4, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PWM2  */
  {0, 3, 0xB5, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PWM3  */
  {0, 3, 0xB6, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PWM4  */
  {0, 3, 0xB7, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PWM5  */
  {0, 3, 0xD0, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* RGB  */
  {0, 3, 0xD3, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* MVFLASH  */
  {0, 3, 0xEC, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* LCDB  */
  {0, 4, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 4, 0x24, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {0, 6, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 6, 0x0A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {0, 6, 0x88, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO01  */
  {0, 6, 0x89, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO02  */
  {0, 6, 0x8A, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO03  */
  {0, 8, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_APPS},   /* BUS  */
  {0, 8, 0x08, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* PON  */
  {0, 8, 0x10, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_P_CHGR  */
  {0, 8, 0x11, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_P_DCDC  */
  {0, 8, 0x12, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_P_BATIF  */
  {0, 8, 0x13, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_P_USB  */
  {0, 8, 0x14, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_P_DC  */
  {0, 8, 0x15, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_P_TYPEC  */
  {0, 8, 0x16, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_P_MISC  */
  {0, 8, 0x17, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* USB_PD_PHY  */
  {0, 8, 0x18, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_P_FREQ  */
  {0, 8, 0x19, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* SCHG_P_OTP_HDR  */
  {0, 8, 0x1A, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* BMD  */
  {0, 8, 0x1D, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* BCLBIG_COMP  */
  {0, 8, 0x24, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* TEMP_ALARM  */
  {0, 8, 0x31, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* ADC_FG1_USR  */
  {0, 8, 0x32, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* ADC_FG2_MDM  */
  {0, 8, 0x35, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* ADC_FG5_BTM_4  */
  {0, 8, 0x48, SPMI_OWNER_ADSP,    SPMI_OWNER_APPS},   /* QGAUGE  */
  {0, 8, 0xB2, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM3  */
  {0, 8, 0xB3, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* SDAM4  */
  {0, 8, 0xC0, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO01 USB Port External Boost and OVP IC enable */
  {0, 8, 0xC1, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO02 Camera Flash Strobe */
  {0, 8, 0xC2, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO03 Camera Flash TX */
  {0, 8, 0xC3, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO04 Camera Flash Enable */
  {0, 8, 0xC4, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO05 Camera Flash Torch */
  {0, 8, 0xC7, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO08 USB Port VBUS detect */
  {0, 8, 0xCA, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO11 Display VDDIO eLDO enable */
  {0, 8, 0xCB, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* GPIO12 Display DDIC eLDO enable */
  {0, 9, 0x53, SPMI_OWNER_APPS,    SPMI_OWNER_APPS},   /* VIB_LDO  */
  {0, 0, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 0, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* PON_PBS  */
  {0, 0, 0x61, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* RTC_RW  */
  {0, 0, 0x70, SPMI_OWNER_TZ,    SPMI_OWNER_TZ},   /* SDAM01  */
  {0, 1, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS_BASE  */
  {0, 1, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* PON_PBS_BASE  */
  {0, 2, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 2, 0x08, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* PON  */
  {0, 2, 0x70, SPMI_OWNER_TZ,    SPMI_OWNER_TZ},   /* PBS_CORE  */
  {0, 4, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 6, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 8, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_TZ},   /* BUS  */
  {0, 8, 0x08, SPMI_OWNER_APPS,    SPMI_OWNER_TZ},   /* PON  */
  {0, 8, 0x70, SPMI_OWNER_TZ,    SPMI_OWNER_TZ},   /* PBS_CORE  */
  {0, 0, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 0, 0x32, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* ADC_MDM  */
  {0, 0, 0x35, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* ADC_TM_MDM  */
  {0, 0, 0x50, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* XO  */
  {0, 0, 0x54, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* RF_CLK1 for SDR */
  {0, 0, 0x73, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* SDAM04  */
  {0, 0, 0x79, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* SDAM10  */
  {0, 0, 0x7A, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* SDAM11  */
  {0, 0, 0x7B, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* SDAM12  */
  {0, 0, 0xB1, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* GPIO02 PA1 Thermistor */
  {0, 1, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS_BASE  */
  {0, 1, 0x8B, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* GPIO04_BASE Core Leica2 VPH Series Switch Enable */
  {0, 2, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 2, 0x32, SPMI_OWNER_ADSP,    SPMI_OWNER_MSS},   /* ADC_QG2_MDM  */
  {0, 2, 0x38, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* ADC_QG5_BTM2  */
  {0, 2, 0x3F, SPMI_OWNER_MSS,    SPMI_OWNER_MSS},   /* BCL_COMP_MDM  */
  {0, 4, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 6, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 8, 0x04, SPMI_OWNER_AOP,    SPMI_OWNER_MSS},   /* BUS  */
  {0, 8, 0x32, SPMI_OWNER_ADSP,    SPMI_OWNER_MSS},   /* ADC_FG2_MDM  */

  {0, 0xE, 0x05, SPMI_OWNER_AOP,    SPMI_OWNER_AOP},   /* INT Broadcast Channel */
};

/* Number of spmi channels config entries. . */
uint32 pm_spmi_channel_cfg_size[] = {sizeof(pm_spmi_channel_cfg) / sizeof(SpmiCfg_ChannelCfg)};
