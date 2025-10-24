#ifndef UFS_PHY_SEQ_H
#define UFS_PHY_SEQ_H
 /**********************************************************************
 * ufs_phy_sequence.h
 *
 * UFS PHY sequence 
 *
 * Copyright (c) 2018-2022
 * Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *********************************************************************

                             Edit History

when         who     what, where, why
----------   ---     ----------------------------------------------------------  
2022-09-16   jt      Update for Eye Monitor 
2022-08-30   jt      Update for Kailua version 9.0 
2022-03-22   jt      Update for Kailua version 7.0 
2022-02-23   sa      Move from Setting to Library Folder.
2022-01-13   jt      Update for Kailua version 5.0 
2021-05-19   sa      Update for Kailua PHY.
2020-10-07   jt      Update for PHY version 24.0 
2020-07-08   jt      Update for PHY version 23.0
2020-04-01   jt      Update for PHY version 22.0 
2020-01-17   jt      Update for PHY version 19.0
2019-07-31   jt      Fix RX_MODE_01 settings  
2019-05-14   jt      Kona Updates 
2019-02-14   jt      Update for HSG4 
2018-09-20   jt      Initial version.
-----------------------------------------------------------------------------*/

#include "ufs_bsp.h"
#include "UfsPhyHwio.h"
#include "aang_phy_hwio.h"

// Constant table for UFS-PHY initialization
static struct ufs_mphy_init_item ufs_bsp_mphy_init_table[] = {
   { 0x00, HWIO_UFS_MEM_UFS_PHY_SW_RESET_OFFS,                          0x01},
   { 0x00, HWIO_UFS_MEM_UFS_PHY_POWER_DOWN_CONTROL_OFFS,                0x01},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_SYSCLK_EN_SEL_OFFS,                 0xD9},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_CMN_CONFIG_1_OFFS,                  0x16},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_HSCLK_SEL_1_OFFS,                   0x11}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_HSCLK_HS_SWITCH_SEL_1_OFFS,         0x00}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_LOCK_CMP_EN_OFFS,                   0x01},
   { CONDITIONAL_FLAG(RATE_A, HS_G4), 
           HWIO_UFS_MEM_QSERDES_COM_VCO_TUNE_MAP_OFFS,                  0x04},
   { CONDITIONAL_FLAG(RATE_B, HS_G4),
           HWIO_UFS_MEM_QSERDES_COM_VCO_TUNE_MAP_OFFS,                  0x44}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_PLL_IVCO_OFFS,                      0x0F}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_VCO_TUNE_INITVAL2_OFFS,             0x00}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_DEC_START_MODE0_OFFS,               0x41}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_CP_CTRL_MODE0_OFFS,                 0x0A}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_PLL_RCTRL_MODE0_OFFS,               0x18}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_PLL_CCTRL_MODE0_OFFS,               0x14}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_LOCK_CMP1_MODE0_OFFS,               0x7F}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_LOCK_CMP2_MODE0_OFFS,               0x06},    
   { CONDITIONAL_FLAG(0, HS_G4),
		   HWIO_UFS_MEM_QSERDES_COM_DEC_START_MODE1_OFFS,               0x4C}, 
   { CONDITIONAL_FLAG(0, HS_G4),
		   HWIO_UFS_MEM_QSERDES_COM_CP_CTRL_MODE1_OFFS,                 0x0A}, 
   { CONDITIONAL_FLAG(0, HS_G4),
		   HWIO_UFS_MEM_QSERDES_COM_PLL_RCTRL_MODE1_OFFS,               0x18}, 
   { CONDITIONAL_FLAG(0, HS_G4),
		   HWIO_UFS_MEM_QSERDES_COM_PLL_CCTRL_MODE1_OFFS,               0x14}, 
   { CONDITIONAL_FLAG(0, HS_G4),
		   HWIO_UFS_MEM_QSERDES_COM_LOCK_CMP1_MODE1_OFFS,               0x99}, 
   { CONDITIONAL_FLAG(0, HS_G4),
		   HWIO_UFS_MEM_QSERDES_COM_LOCK_CMP2_MODE1_OFFS,               0x07},    
   { 0x00, HWIO_UFS_MEM_QSERDES_TX0_LANE_MODE_1_OFFS,                   0x05},
   { CONDITIONAL_FLAG(0, HS_G4), 
           HWIO_UFS_MEM_QSERDES_TX0_TX_FR_DCC_CTRL_OFFS,                0x4C}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_TX0_RES_CODE_LANE_OFFSET_TX_OFFS,       0x07}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_UCDR_FO_GAIN_RATE2_OFFS,            0x0C},
   { CONDITIONAL_FLAG(0, HS_G5),
           HWIO_UFS_MEM_QSERDES_RX0_UCDR_FO_GAIN_RATE4_OFFS,            0x0F},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_VGA_CAL_MAN_VAL_OFFS,               0x0E}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE_0_1_B0_OFFS,           0xC2},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE_0_1_B1_OFFS,           0xC2},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE_0_1_B3_OFFS,           0x1A},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE_0_1_B6_OFFS,           0x60},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE2_B3_OFFS,              0x9E},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE2_B6_OFFS,              0x60},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE3_B3_OFFS,              0x9E},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE3_B4_OFFS,              0x0E},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE3_B5_OFFS,              0x36},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE3_B8_OFFS,              0x02},
   { CONDITIONAL_FLAG(0, HS_G5), 
           HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE4_B3_OFFS,              0xB9}, 
   { CONDITIONAL_FLAG(0, HS_G5), 
           HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE4_B6_OFFS,              0xFF},  
   { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_init_end_table[] = {
   { 0x00, HWIO_UFS_MEM_UFS_PHY_TX_MID_TERM_CTRL1_OFFS,            0x43},
   { CONDITIONAL_FLAG(0, HS_G4), 
           HWIO_UFS_MEM_UFS_PHY_PLL_CNTL_OFFS,                     0x2B},		   
   { CONDITIONAL_FLAG(0, HS_G5), 
           HWIO_UFS_MEM_UFS_PHY_PLL_CNTL_OFFS,                     0x33},
   { 0x00, HWIO_UFS_MEM_UFS_PHY_TX_LARGE_AMP_DRV_LVL_OFFS,         0x0F},
   { 0x00, HWIO_UFS_MEM_UFS_PHY_RX_SIGDET_CTRL2_OFFS,              0x69},
   { CONDITIONAL_FLAG(0, HS_G4), 
          HWIO_UFS_MEM_UFS_PHY_TX_HSGEAR_CAPABILITY_OFFS,          0x04},
   { CONDITIONAL_FLAG(0, HS_G4),
          HWIO_UFS_MEM_UFS_PHY_RX_HSGEAR_CAPABILITY_OFFS,          0x04},
   { 0x00, HWIO_UFS_MEM_UFS_PHY_SW_RESET_OFFS,                     0x00}, 
   { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_eom_table[] = {
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_VTHRESH_CAL_CNTRL1_OFFS,            0x04},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_VTHRESH_CAL_MAN_VAL_RATE4_OFFS,     0x00},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_VTHRESH_CAL_MAN_VAL_RATE3_OFFS,     0x00},
   { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_2_lane_eom_table[] = {
   { 0x00, HWIO_UFS_MEM_QSERDES_RX1_VTHRESH_CAL_CNTRL1_OFFS,            0x04},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX1_VTHRESH_CAL_MAN_VAL_RATE4_OFFS,     0x00},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX1_VTHRESH_CAL_MAN_VAL_RATE3_OFFS,     0x00},
   { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_init_table_rumi[] = {
     { 0x00, HWIO_UFS_PHY_PHY_START_OFFS,                     0x00}, 
     { 0x00, HWIO_UFS_PHY_POWER_DOWN_CONTROL_OFFS,            0x00}, 
     { 0x00, HWIO_UFS_PHY_RX_SYM_RESYNC_CTRL_OFFS,            0x03}, 
     { 0x00, HWIO_UFS_PHY_TIMER_20US_CORECLK_STEPS_MSB_OFFS,  0x0F}, 
     { 0x00, HWIO_UFS_PHY_TIMER_20US_CORECLK_STEPS_LSB_OFFS,  0x00}, 
     { 0x00, HWIO_QSERDES_COM_BIAS_EN_CLKBUFLR_EN_OFFS,       0x3F}, 
     { 0x00, HWIO_QSERDES_COM_SYSCLK_EN_SEL_OFFS,             0x03}, 
     { 0x00, HWIO_QSERDES_COM_SYS_CLK_CTRL_OFFS,              0x16}, 
     { 0x00, HWIO_QSERDES_COM_RES_CODE_TXBAND_OFFS,           0xC0}, 
     { 0x00, HWIO_QSERDES_COM_PLL_VCOTAIL_EN_OFFS,            0x03}, 
     { 0x00, HWIO_QSERDES_COM_PLL_CNTRL_OFFS,                 0x24}, 
     { 0x00, HWIO_QSERDES_COM_PLL_CLKEPDIV_OFFS,              0x03}, 
     { 0x00, HWIO_QSERDES_COM_RESETSM_CNTRL_OFFS,             0x10}, 
     { 0x00, HWIO_QSERDES_COM_PLL_RXTXEPCLK_EN_OFFS,          0x13}, 
     { 0x00, HWIO_QSERDES_COM_PLL_CRCTRL_OFFS,                0x43}, 
     { 0x00, HWIO_QSERDES_TX0_CLKBUF_ENABLE_OFFS,             0x29},
     { 0x00, HWIO_QSERDES_TX1_CLKBUF_ENABLE_OFFS,             0x29},
     { 0x00, HWIO_QSERDES_COM_DEC_START1_OFFS,                0x98}, 
     { 0x00, HWIO_QSERDES_COM_DEC_START2_OFFS,                0x03}, 
     { 0x00, HWIO_QSERDES_COM_DIV_FRAC_START1_OFFS,           0x80}, 
     { 0x00, HWIO_QSERDES_COM_DIV_FRAC_START2_OFFS,           0x80}, 
     { 0x00, HWIO_QSERDES_COM_DIV_FRAC_START3_OFFS,           0x10}, 
     { 0x00, HWIO_QSERDES_COM_PLLLOCK_CMP1_OFFS,              0x65}, 
     { 0x00, HWIO_QSERDES_COM_PLLLOCK_CMP2_OFFS,              0x1E}, 
     { 0x00, HWIO_QSERDES_COM_PLLLOCK_CMP3_OFFS,              0x00}, 
     { 0x00, HWIO_QSERDES_COM_PLLLOCK_CMP_EN_OFFS,            0x03}, 
     { 0x00, HWIO_QSERDES_COM_PLL_IP_SETI_OFFS,               0x07}, 
     { 0x00, HWIO_QSERDES_COM_PLL_CP_SETI_OFFS,               0x0F}, 
     { 0x00, HWIO_QSERDES_COM_PLL_IP_SETP_OFFS,               0x07}, 
     { 0x00, HWIO_QSERDES_COM_PLL_CP_SETP_OFFS,               0x01}, 
     { 0x00, HWIO_QSERDES_RX0_PWM_CNTRL1_OFFS,                0x08}, 
     { 0x00, HWIO_QSERDES_RX0_PWM_CNTRL2_OFFS,                0x40}, 
     { 0x00, HWIO_QSERDES_RX0_PWM_NDIV_OFFS,                  0x30}, 
     { 0x00, HWIO_QSERDES_RX0_CDR_CONTROL_OFFS,               0x40}, 
     { 0x00, HWIO_QSERDES_RX0_CDR_CONTROL_HALF_OFFS,          0x0C}, 
     { 0x00, HWIO_QSERDES_RX0_CDR_CONTROL_QUARTER_OFFS,       0x12}, 
     { 0x00, HWIO_QSERDES_RX0_SIGDET_CNTRL_OFFS,              0xC0}, 
     { 0x00, HWIO_QSERDES_RX0_SIGDET_CNTRL2_OFFS,             0x07}, 
     { 0x00, HWIO_QSERDES_RX0_RX_BAND_OFFS,                   0x06}, 
     { 0x00, HWIO_QSERDES_RX0_UFS_CNTRL_OFFS,                 0x00}, 
     { 0x00, HWIO_QSERDES_RX0_RX_IQ_RXDET_EN_OFFS,            0xF3},
     { 0x00, HWIO_UFS_PHY_POWER_DOWN_CONTROL_OFFS,            0x01}, 
     { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_2_lane_init_table[] = {
     { 0x00, HWIO_UFS_MEM_QSERDES_TX1_LANE_MODE_1_OFFS,                   0x05},
     { CONDITIONAL_FLAG(0, HS_G4),   
           HWIO_UFS_MEM_QSERDES_TX1_TX_FR_DCC_CTRL_OFFS,                  0x4C},
     { 0x00, HWIO_UFS_MEM_QSERDES_TX1_RES_CODE_LANE_OFFSET_TX_OFFS,       0x07},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_UCDR_FO_GAIN_RATE2_OFFS,            0x0C},
     { CONDITIONAL_FLAG(0, HS_G5),
           HWIO_UFS_MEM_QSERDES_RX1_UCDR_FO_GAIN_RATE4_OFFS,              0x0F},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_VGA_CAL_MAN_VAL_OFFS,               0x0E},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE_0_1_B0_OFFS,           0xC2},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE_0_1_B1_OFFS,           0xC2},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE_0_1_B3_OFFS,           0x1A},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE_0_1_B6_OFFS,           0x60},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE2_B3_OFFS,              0x9E},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE2_B6_OFFS,              0x60},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE3_B3_OFFS,              0x9E},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE3_B4_OFFS,              0x0E},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE3_B5_OFFS,              0x36},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE3_B8_OFFS,              0x02},
     { CONDITIONAL_FLAG(0, HS_G5), 
           HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE4_B3_OFFS,                0xB9},
     { CONDITIONAL_FLAG(0, HS_G5), 
           HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE4_B6_OFFS,                0xFF},
	 { 0x00, HWIO_UFS_MEM_UFS_PHY_MULTI_LANE_CTRL1_OFFS,                  0x02},
     { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_2_lane_init_table_rumi[] = {
     { 0x00, HWIO_QSERDES_RX1_PWM_CNTRL1_OFFS,                        0x08},
     { 0x00, HWIO_QSERDES_RX1_PWM_CNTRL2_OFFS,                        0x40},
     { 0x00, HWIO_QSERDES_RX1_PWM_NDIV_OFFS,                          0x30},
     { 0x00, HWIO_QSERDES_RX1_CDR_CONTROL_OFFS,                       0x40},
     { 0x00, HWIO_QSERDES_RX1_CDR_CONTROL_HALF_OFFS,                  0x0C},
     { 0x00, HWIO_QSERDES_RX1_CDR_CONTROL_QUARTER_OFFS,               0x12},
     { 0x00, HWIO_QSERDES_RX1_SIGDET_CNTRL_OFFS,                      0xc0},
     { 0x00, HWIO_QSERDES_RX1_SIGDET_CNTRL2_OFFS,                     0x07},
     { 0x00, HWIO_QSERDES_RX1_RX_BAND_OFFS,                           0x06},
     { 0x00, HWIO_QSERDES_RX1_UFS_CNTRL_OFFS,                         0x00},
     { 0x00, HWIO_QSERDES_RX1_RX_IQ_RXDET_EN_OFFS,                    0xf3},
     { 0x00, HWIO_UFS_PHY_MULTI_LANE_CTRL1_OFFS,                      0x02},
     { STOP_CONDITION, 0,0}};

#endif /* #ifndef UFS_PHY_SEQ_H */

