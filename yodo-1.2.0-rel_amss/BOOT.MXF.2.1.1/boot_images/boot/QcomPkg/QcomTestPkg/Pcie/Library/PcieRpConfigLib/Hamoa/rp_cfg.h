#ifndef __PCIE_TARGET_PORT_CONFIG_H__
#define __PCIE_TARGET_PORT_CONFIG_H__
/*
 *  PCIe root port target config
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   10/20/20   Yg      Created New

*/
/*============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
============================================================================*/

#include "pcie_cfg_types.h"
#include "pcie_hwio_base.h"

#define REG_OP_TYPE(x)        PCIE_REG_OP_SEQ, {.reg_op_seq = x}}
#define REG_WRITE_TYPE(x)     PCIE_REG_WRITE_SEQ, {.reg_write_val_seq = x}}

#define PCIE_PORT_0_INDEX      0
#define PCIE_PORT_1_INDEX      1
#define PCIE_PORT_2A_INDEX     2
#define PCIE_PORT_2B_INDEX     3
#define PCIE_PORT_3A_INDEX     4
#define PCIE_PORT_3B_INDEX     5
#define PCIE_PORT_4_INDEX      6

#include "rp_cfg_2a.h"
#include "rp_cfg_2b.h"
#include "rp_cfg_3a.h"
#include "rp_cfg_3b.h"
#include "rp_cfg_4.h"

/*******************************************************************************
 *  Maximum index of actual ports the target supports. (Should be equal to max
 *   HW port index)
 *******************************************************************************/
#define TARGET_MAX_PORT_INDEX    6

/* Macro to define a number using chars for easy readability */
#define STR_ID(a,b,c,d)     (a | (b << 8) | (c << 16) | (d << 24))

/*******************************************************************************
 *
 *                           PORT A Phy
 *
 *******************************************************************************/
STATIC CONST pcie_reg_write_val_t port_A_pwrup_seq[] =
{
   {HWIO_OFFS(PCIE_APCS_COM_POWER_DOWN_CONTROL),      0x03},//  Release powerdown mode and allow endpoint refclk drive
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_A_x2_bias_init_seq[] =
{
   {HWIO_OFFS(PCIE_AQSERDES_PLL_BIAS_EN_CLKBUFLR_EN),        0x14}, //    (2x2 mode)
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_A_x4_bias_init_seq[] =
{
   {HWIO_OFFS(PCIE_AQSERDES_PLL_BIAS_EN_CLKBUFLR_EN),        0x1C},//     (1x4 mode)
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_A_phy_init_seq[] =
{
   {HWIO_OFFS(PCIE_PARF_DEVICE_TYPE),                        0x04},

   {HWIO_OFFS(PCIE_AQSERDES_PLL_SSC_PER1),                   0x31},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_SSC_PER2),                   0x01},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_SSC_STEP_SIZE1_MODE0),       0xDE},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_SSC_STEP_SIZE2_MODE0),       0x07},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_SSC_STEP_SIZE1_MODE1),       0x4C},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_SSC_STEP_SIZE2_MODE1),       0x06},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_CLK_ENABLE1),                0x90},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_PLL_IVCO),                   0x0F},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_CP_CTRL_MODE0),              0x06},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_CP_CTRL_MODE1),              0x06},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_PLL_RCTRL_MODE0),            0x16},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_PLL_RCTRL_MODE1),            0x16},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_PLL_CCTRL_MODE0),            0x36},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_PLL_CCTRL_MODE1),            0x36},
                                                             
   {HWIO_OFFS(PCIE_AQSERDES_PLL_SYSCLK_EN_SEL),              0x08},
                                                             
   {HWIO_OFFS(PCIE_AQSERDES_PLL_LOCK_CMP_EN),                0x42},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_LOCK_CMP1_MODE0),            0x0A},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_LOCK_CMP2_MODE0),            0x1A},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_LOCK_CMP1_MODE1),            0x14},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_LOCK_CMP2_MODE1),            0x34},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_DEC_START_MODE0),            0x82},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_DEC_START_MODE1),            0x68},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_DIV_FRAC_START1_MODE0),      0x55},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_DIV_FRAC_START2_MODE0),      0x55},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_DIV_FRAC_START3_MODE0),      0x03},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_DIV_FRAC_START1_MODE1),      0xAB},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_DIV_FRAC_START2_MODE1),      0xAA},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_DIV_FRAC_START3_MODE1),      0x02},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_VCO_TUNE_MAP),               0x02},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_VCO_TUNE1_MODE0),            0x24},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_VCO_TUNE1_MODE1),            0xB4},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_VCO_TUNE2_MODE1),            0x03},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_CLK_SELECT),                 0x34},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_HSCLK_SEL),                  0x01},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_CORECLK_DIV_MODE1),          0x08},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0), 0xB9},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0), 0x1E},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1), 0x94},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1), 0x18},
   {HWIO_OFFS(PCIE_AQSERDES_PLL_BIN_VCOCAL_HSCLK_SEL),       0x11},
   {HWIO_OFFS(PCIE_AQSERDES_TX0_PI_QEC_CTRL),                0x02},
   {HWIO_OFFS(PCIE_AQSERDES_TX1_PI_QEC_CTRL),                0x04},
   {HWIO_OFFS(PCIE_AQSERDES_TX0_LANE_MODE_1),                0xD5},
   {HWIO_OFFS(PCIE_AQSERDES_TX1_LANE_MODE_1),                0xD5},
   {HWIO_OFFS(PCIE_AQSERDES_TX0_LANE_MODE_4),                0x3F},
   {HWIO_OFFS(PCIE_AQSERDES_TX1_LANE_MODE_4),                0x3F},
   {HWIO_OFFS(PCIE_AQSERDES_TX0_RES_CODE_LANE_OFFSET_TX),    0x11},
   {HWIO_OFFS(PCIE_AQSERDES_TX1_RES_CODE_LANE_OFFSET_TX),    0x11},
   {HWIO_OFFS(PCIE_AQSERDES_TX0_RES_CODE_LANE_OFFSET_RX),    0x0C},
   {HWIO_OFFS(PCIE_AQSERDES_TX1_RES_CODE_LANE_OFFSET_RX),    0x0C},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_RX_MODE_00_LOW),             0x7F},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_RX_MODE_00_HIGH),            0xFF},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_RX_MODE_00_HIGH2),           0x7F},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_RX_MODE_00_HIGH3),           0x34},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_RX_MODE_00_HIGH4),           0xD8},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_RX_MODE_00_LOW),             0x7F},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_RX_MODE_00_HIGH),            0xFF},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_RX_MODE_00_HIGH2),           0x7F},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_RX_MODE_00_HIGH3),           0x34},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_RX_MODE_00_HIGH4),           0xD8},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_RX_MODE_01_LOW),             0xDC},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_RX_MODE_01_HIGH),            0xDC},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_RX_MODE_01_HIGH2),           0x5C},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_RX_MODE_01_HIGH3),           0x34},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_RX_MODE_01_HIGH4),           0xA6},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_RX_MODE_01_LOW),             0xDC},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_RX_MODE_01_HIGH),            0xDC},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_RX_MODE_01_HIGH2),           0x5C},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_RX_MODE_01_HIGH3),           0x34},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_RX_MODE_01_HIGH4),           0xA6},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_RX_MODE_10_HIGH3),           0x34},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_RX_MODE_10_HIGH3),           0x34},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_VGA_CAL_CNTRL2),             0x0F},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_VGA_CAL_CNTRL2),             0x0F},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_GM_CAL),                     0x00},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_GM_CAL),                     0x00},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_UCDR_SB2_THRESH1),           0x08},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_UCDR_SB2_THRESH1),           0x08},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_UCDR_SB2_THRESH2),           0x08},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_UCDR_SB2_THRESH2),           0x08},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_UCDR_PI_CONTROLS),           0xF0},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_UCDR_PI_CONTROLS),           0xF0},
   {HWIO_OFFS(PCIE_AQSERDES_RX0_DFE_CTLE_POST_CAL_OFFSET),   0x38},
   {HWIO_OFFS(PCIE_AQSERDES_RX1_DFE_CTLE_POST_CAL_OFFSET),   0x38},
   {HWIO_OFFS(PCIE_APCS_COM_REFGEN_REQ_CONFIG1),             0x05},
   {HWIO_OFFS(PCIE_APCS_COM_RX_SIGDET_LVL),                  0x88},
   {HWIO_OFFS(PCIE_APCS_COM_RATE_SLEW_CNTRL1),               0x0B},
   {HWIO_OFFS(PCIE_APCS_COM_EQ_CONFIG2),                     0x0F},
   {HWIO_OFFS(PCIE_APCS_PCIE_POWER_STATE_CONFIG2),           0x1D},
   {HWIO_OFFS(PCIE_APCS_PCIE_POWER_STATE_CONFIG4),           0x07},
   {HWIO_OFFS(PCIE_APCS_PCIE_ENDPOINT_REFCLK_DRIVE),         0xC1},
   {HWIO_OFFS(PCIE_APCS_PCIE_OSC_DTCT_ACTIONS),              0x00},
 
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_A_start_seq[] =
{
   {HWIO_OFFS(PCIE_APCS_COM_SW_RESET),             0x00},  // Release software reset
   {HWIO_OFFS(PCIE_APCS_COM_START_CONTROL),        0x03},  // Start PCS and Serdes power SMs
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t port_A_phy_poll_seq[] =
{
  {PCIE_REG_OP_POLL, HWIO_OFFS(PCIE_APCS_COM_PCS_STATUS1), HWIO_PCIE_APCS_COM_PCS_STATUS1_PHYSTATUS_BMSK, FALSE},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_A_phy_de_init_seq[] =
{
  {HWIO_OFFS(PCIE_APCS_COM_POWER_DOWN_CONTROL),     0x00},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t port_A_phy_de_init_cfg[] =
{
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_A_phy_de_init_seq),
  {PcieSeq_Stop},
};

/*******************************************************************************
 *
 *                           PORT B Phy
 *
 *******************************************************************************/

STATIC CONST pcie_reg_write_val_t port_B_pwrup_seq[] =
{
   {HWIO_OFFS(PCIE_BPCS_COM_POWER_DOWN_CONTROL),    0x03},//	Release powerdown mode and allow endpoint refclk drive
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_B_x4_bias_init_seq[] =
{
   {HWIO_OFFS(PCIE_BQSERDES_PLL_BIAS_EN_CLKBUFLR_EN),  0x1C},//     (1x4 mode)
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_B_x2_bias_init_seq[] =
{
   {HWIO_OFFS(PCIE_BQSERDES_PLL_BIAS_EN_CLKBUFLR_EN),  0x14}, //    (2x2 mode)
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_B_phy_init_seq[] =
{
   {HWIO_OFFS(PCIE_PARF_DEVICE_TYPE),                          0x04},

   {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_PER1),                     0x31},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_PER2),                     0x01},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_STEP_SIZE1_MODE0),         0xDE},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_STEP_SIZE2_MODE0),         0x07},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_STEP_SIZE1_MODE1),         0x4C},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_STEP_SIZE2_MODE1),         0x06},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_CLK_ENABLE1),                  0x90},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_PLL_IVCO),                     0x0F},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_CP_CTRL_MODE0),                0x06},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_CP_CTRL_MODE1),                0x06},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_PLL_RCTRL_MODE0),              0x16},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_PLL_RCTRL_MODE1),              0x16},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_PLL_CCTRL_MODE0),              0x36},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_PLL_CCTRL_MODE1),              0x36},
                                                              
   {HWIO_OFFS(PCIE_BQSERDES_PLL_SYSCLK_EN_SEL),                0x08},
                                                              
   {HWIO_OFFS(PCIE_BQSERDES_PLL_LOCK_CMP_EN),                  0x42},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_LOCK_CMP1_MODE0),              0x0A},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_LOCK_CMP2_MODE0),              0x1A},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_LOCK_CMP1_MODE1),              0x14},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_LOCK_CMP2_MODE1),              0x34},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_DEC_START_MODE0),              0x82},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_DEC_START_MODE1),              0x68},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START1_MODE0),        0x55},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START2_MODE0),        0x55},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START3_MODE0),        0x03},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START1_MODE1),        0xAB},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START2_MODE1),        0xAA},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START3_MODE1),        0x02},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_VCO_TUNE_MAP),                 0x02},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_VCO_TUNE1_MODE0),              0x24},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_VCO_TUNE1_MODE1),              0xB4},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_VCO_TUNE2_MODE1),              0x03},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_CLK_SELECT),                   0x34},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_HSCLK_SEL),                    0x01},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_CORECLK_DIV_MODE1),            0x08},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0),   0xB9},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0),   0x1E},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1),   0x94},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1),   0x18},
   {HWIO_OFFS(PCIE_BQSERDES_PLL_BIN_VCOCAL_HSCLK_SEL),         0x11},
   {HWIO_OFFS(PCIE_BQSERDES_TX0_PI_QEC_CTRL),                  0x02},
   {HWIO_OFFS(PCIE_BQSERDES_TX1_PI_QEC_CTRL),                  0x04},
   {HWIO_OFFS(PCIE_BQSERDES_TX0_LANE_MODE_1),                  0xD5},
   {HWIO_OFFS(PCIE_BQSERDES_TX1_LANE_MODE_1),                  0xD5},
   {HWIO_OFFS(PCIE_BQSERDES_TX0_LANE_MODE_4),                  0x3F},
   {HWIO_OFFS(PCIE_BQSERDES_TX1_LANE_MODE_4),                  0x3F},
   {HWIO_OFFS(PCIE_BQSERDES_TX0_RES_CODE_LANE_OFFSET_TX),      0x11},
   {HWIO_OFFS(PCIE_BQSERDES_TX1_RES_CODE_LANE_OFFSET_TX),      0x11},
   {HWIO_OFFS(PCIE_BQSERDES_TX0_RES_CODE_LANE_OFFSET_RX),      0x0C},
   {HWIO_OFFS(PCIE_BQSERDES_TX1_RES_CODE_LANE_OFFSET_RX),      0x0C},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_00_LOW),               0x7F},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_00_HIGH),              0xFF},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_00_HIGH2),             0x7F},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_00_HIGH3),             0x34},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_00_HIGH4),             0xD8},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_RX_MODE_00_LOW),               0x7F},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_RX_MODE_00_HIGH),              0xFF},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_RX_MODE_00_HIGH2),             0x7F},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_RX_MODE_00_HIGH3),             0x34},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_RX_MODE_00_HIGH4),             0xD8},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_01_LOW),               0xDC},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_01_HIGH),              0xDC},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_01_HIGH2),             0x5C},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_01_HIGH3),             0x34},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_01_HIGH4),             0xA6},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_RX_MODE_01_LOW),               0xDC},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_RX_MODE_01_HIGH),              0xDC},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_RX_MODE_01_HIGH2),             0x5C},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_RX_MODE_01_HIGH3),             0x34},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_RX_MODE_01_HIGH4),             0xA6},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_10_HIGH3),             0x34},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_RX_MODE_10_HIGH3),             0x34},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_VGA_CAL_CNTRL2),               0x0F},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_VGA_CAL_CNTRL2),               0x0F},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_GM_CAL),                       0x00},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_GM_CAL),                       0x00},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_UCDR_SB2_THRESH1),             0x08},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_UCDR_SB2_THRESH1),             0x08},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_UCDR_SB2_THRESH2),             0x08},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_UCDR_SB2_THRESH2),             0x08},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_UCDR_PI_CONTROLS),             0xF0},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_UCDR_PI_CONTROLS),             0xF0},
   {HWIO_OFFS(PCIE_BQSERDES_RX0_DFE_CTLE_POST_CAL_OFFSET),     0x38},
   {HWIO_OFFS(PCIE_BQSERDES_RX1_DFE_CTLE_POST_CAL_OFFSET),     0x38},
   {HWIO_OFFS(PCIE_BPCS_COM_REFGEN_REQ_CONFIG1),               0x05},
   {HWIO_OFFS(PCIE_BPCS_COM_RX_SIGDET_LVL),                    0x88},
   {HWIO_OFFS(PCIE_BPCS_COM_RATE_SLEW_CNTRL1),                 0x0B},
   {HWIO_OFFS(PCIE_BPCS_COM_EQ_CONFIG2),                       0x0F},
   {HWIO_OFFS(PCIE_BPCS_PCIE_POWER_STATE_CONFIG2),             0x1D},
   {HWIO_OFFS(PCIE_BPCS_PCIE_POWER_STATE_CONFIG4),             0x07},
   {HWIO_OFFS(PCIE_BPCS_PCIE_ENDPOINT_REFCLK_DRIVE),           0xC1},
   {HWIO_OFFS(PCIE_BPCS_PCIE_OSC_DTCT_ACTIONS),                0x00},
 
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_B_start_seq[] =
{
   {HWIO_OFFS(PCIE_BPCS_COM_SW_RESET),               0x00},  // Release software reset
   {HWIO_OFFS(PCIE_BPCS_COM_START_CONTROL),          0x03},  // Start PCS and Serdes power SMs
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t port_B_phy_poll_seq[] =
{
   {PCIE_REG_OP_POLL, HWIO_OFFS(PCIE_BPCS_COM_PCS_STATUS1), HWIO_PCIE_BPCS_COM_PCS_STATUS1_PHYSTATUS_BMSK, FALSE},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t phy_delay_seq[] =
{
   {PCIE_REG_OP_DELAY, 0, 0, 2000},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_B_phy_de_init_seq[] =
{
   {HWIO_OFFS(PCIE_BPCS_COM_POWER_DOWN_CONTROL),      0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t port_B_phy_de_init_cfg[] =
{
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_B_phy_de_init_seq),
  {PcieSeq_Stop}
};

STATIC CONST pcie_reg_init_cfg_t port_x4_phy_de_init_cfg[] =
{
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_B_phy_de_init_seq),
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_A_phy_de_init_seq),
  {PcieSeq_Stop}
};

/**************** Loopback **************************/

STATIC CONST pcie_reg_write_val_t port_A_phy_lpb_en_seq[] =
{
   {HWIO_OFFS(PCIE_AQSERDES_TX0_LPB_EN),                 0x0C},
   {HWIO_OFFS(PCIE_AQSERDES_TX1_LPB_EN),                 0x0C},
   {HWIO_OFFS(PCIE_APCS_LANE0_PCS_LANE_TEST_CONTROL1),   0x03},
   {HWIO_OFFS(PCIE_APCS_LANE1_TEST_CONTROL1),            0x03},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_A_phy_lpb_dis_seq[] =
{
   {HWIO_OFFS(PCIE_AQSERDES_TX0_LPB_EN),                 0x00},
   {HWIO_OFFS(PCIE_AQSERDES_TX1_LPB_EN),                 0x00},
   {HWIO_OFFS(PCIE_APCS_LANE0_PCS_LANE_TEST_CONTROL1),   0x00},
   {HWIO_OFFS(PCIE_APCS_LANE1_TEST_CONTROL1),            0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_B_phy_lpb_en_seq[] =
{
   {HWIO_OFFS(PCIE_BQSERDES_TX0_LPB_EN),                 0x0C},
   {HWIO_OFFS(PCIE_BQSERDES_TX1_LPB_EN),                 0x0C},
   {HWIO_OFFS(PCIE_BPCS_LANE0_PCS_LANE_TEST_CONTROL1),   0x03},
   {HWIO_OFFS(PCIE_BPCS_LANE1_TEST_CONTROL1),            0x03},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_B_phy_lpb_dis_seq[] =
{
   {HWIO_OFFS(PCIE_BQSERDES_TX0_LPB_EN),                 0x00},
   {HWIO_OFFS(PCIE_BQSERDES_TX1_LPB_EN),                 0x00},
   {HWIO_OFFS(PCIE_BPCS_LANE0_PCS_LANE_TEST_CONTROL1),   0x00},
   {HWIO_OFFS(PCIE_BPCS_LANE1_TEST_CONTROL1),            0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t port_A_phy_lpb_en_cfg[] =
{
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_A_phy_lpb_en_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t port_A_phy_lpb_dis_cfg[] =
{
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_A_phy_lpb_dis_seq),
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_A_phy_de_init_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t port_B_phy_lpb_en_cfg[] =
{
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_B_phy_lpb_en_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t port_B_phy_lpb_dis_cfg[] =
{
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_B_phy_lpb_dis_seq),
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_B_phy_de_init_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t port_x4_phy_lpb_en_cfg[] =
{
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_A_phy_lpb_en_seq),
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_B_phy_lpb_en_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t port_x4_phy_lpb_dis_cfg[] =
{
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_A_phy_lpb_dis_seq),
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_B_phy_lpb_dis_seq),
  {PcieQcSoCVer_All,   ahb_reg,  REG_WRITE_TYPE(port_A_phy_de_init_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_loopback_cfg_t port_A_loopback_seq = 
{
   port_A_phy_lpb_en_cfg,
   port_A_phy_lpb_dis_cfg,
};

STATIC CONST pcie_loopback_cfg_t port_B_loopback_seq = 
{
   port_B_phy_lpb_en_cfg,
   port_B_phy_lpb_dis_cfg,
};

STATIC CONST pcie_loopback_cfg_t port_x4_loopback_seq = 
{
   port_x4_phy_lpb_en_cfg,
   port_x4_phy_lpb_dis_cfg,
};

/*******************************************************************************
 *
 *                       Controller DBI settings
 *
 *******************************************************************************/
/* Set the max capable lane width */
/* 1 for 1 lane
 * 3 for 2 lane
 * 7 for 4 lane
 * following may NOT work for 8 lanes */
#define PORT_4_LANE     4
#define PORT_2_LANE     2

#define PORT_LINK_4_LANE_CAPABLE_VAL ((PORT_4_LANE << 1) - 1)
#define PORT_LINK_2_LANE_CAPABLE_VAL ((PORT_2_LANE << 1) - 1)
#define PORT_LINK_1_LANE_CAPABLE_VAL (1)

STATIC CONST pcie_reg_op_t port_x4_lane_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PORT_LINK_CTRL_OFF), HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_BMSK,
                              (PORT_LINK_4_LANE_CAPABLE_VAL << HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_SHFT)},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t port_x2_lane_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PORT_LINK_CTRL_OFF), HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_BMSK,
                                       (PORT_LINK_2_LANE_CAPABLE_VAL << HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_SHFT)},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t port_x1_lane_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PORT_LINK_CTRL_OFF), HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_BMSK,
                                       (PORT_LINK_1_LANE_CAPABLE_VAL << HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_SHFT)},
   {PCIE_REG_OP_STOP},
};

/*******************************************************************************
 *       Post PHY power ON sequence 
 ******************************************************************************/
STATIC CONST pcie_reg_op_t post_phy_pwr_up_init_seq[] =
{
   // WARNING..!!: Only PARF registers in this set
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_DEVICE_TYPE), HWIO_PCIE_PARF_DEVICE_TYPE_DEVICE_TYPE_BMSK, HWIO_PCIE_PARF_DEVICE_TYPE_DEVICE_TYPE_RC_FVAL},
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_PM_CTRL), HWIO_PCIE_PARF_PM_CTRL_REQ_NOT_ENTR_L1_BMSK, 0x0},
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_SYS_CTRL), HWIO_PCIE_PARF_SYS_CTRL_AUX_PWR_DET_BMSK, (0x01 << HWIO_PCIE_PARF_SYS_CTRL_AUX_PWR_DET_SHFT)},
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_SLAVE_AXI_ERROR_REPORT), HWIO_PCIE_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_CRS_BRESP_EN_BMSK, 0x0},
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_AMBA_ERROR_RESPONSE_DEFAULT_OFF), HWIO_PCIE_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_CRS_BMSK, 0x10},

   {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_PARF_AXI_MSTR_WR_ADDR_HALT), 0x00, 0x00},
   {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_PARF_SLV_ADDR_SPACE_SIZE), 0x00, 0x01000000},
   {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_SRIS_MODE), 0x00, 0x0},

   {PCIE_REG_OP_STOP},
};

#define PORT_LINK_SPEED_GEN_1     1
#define PORT_LINK_SPEED_GEN_2     2
#define PORT_LINK_SPEED_GEN_3     3

STATIC CONST pcie_reg_op_t post_phy_pwr_up_dbi_init_seq[] =
{
   // WARNING..!!: Only DBI registers in this set
    /* Fix NFTS */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_LINK_CONTROL2_LINK_STATUS2_REG), HWIO_PCIE_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED_BMSK, PORT_LINK_SPEED_GEN_3},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_ACK_F_ASPM_CTRL_OFF), HWIO_PCIE_ACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS_BMSK, (0x80 << HWIO_PCIE_ACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS_SHFT)},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_ACK_F_ASPM_CTRL_OFF), HWIO_PCIE_ACK_F_ASPM_CTRL_OFF_ACK_N_FTS_BMSK, (0x80 << HWIO_PCIE_ACK_F_ASPM_CTRL_OFF_ACK_N_FTS_SHFT)},

  /* Treats out-of-bar TLPs as supported request - MUST for RC mode. Data book: Table I-2 */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_SYMBOL_TIMER_FILTER_1_OFF), HWIO_PCIE_SYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1_BMSK, (0x0004 << HWIO_PCIE_SYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1_SHFT)},
  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_AUX_CLK_FREQ_OFF), 0x00, 19},

  /* Allow establishing connection on one line even if there is a termination on the second line. Othewise the link will go to compliance */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN2_CTRL_OFF), HWIO_PCIE_GEN2_CTRL_OFF_NUM_OF_LANES_BMSK, (0x01 << HWIO_PCIE_GEN2_CTRL_OFF_NUM_OF_LANES_SHFT)},

  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_MISC_CONTROL_1_OFF), 0x00, 0x1},   // DBI_RO_RW Enable
  {PCIE_REG_OP_DSB},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_ROOT_CONTROL_ROOT_CAPABILITIES_REG), HWIO_PCIE_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_CRS_SW_VISIBILITY_BMSK,
                                                                        HWIO_PCIE_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_CRS_SW_VISIBILITY_BMSK},

  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_ROOT_CONTROL_ROOT_CAPABILITIES_REG), HWIO_PCIE_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_CRS_SW_VISIBILITY_EN_BMSK,
                                                                        HWIO_PCIE_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_CRS_SW_VISIBILITY_EN_BMSK},

  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_TYPE1_CLASS_CODE_REV_ID_REG),
    (HWIO_PCIE_TYPE1_CLASS_CODE_REV_ID_REG_BASE_CLASS_CODE_BMSK | HWIO_PCIE_TYPE1_CLASS_CODE_REV_ID_REG_SUBCLASS_CODE_BMSK),
    (PCIE_CLASS_CODE_BRIDGE_DEVICE | PCIE_SUBCLASS_CODE_PCI_2_PCI_BRIDGE)},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_SLOT_CAPABILITIES_REG), HWIO_PCIE_SLOT_CAPABILITIES_REG_PCIE_CAP_HOT_PLUG_CAPABLE_BMSK, 0x00000000},
  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_MISC_CONTROL_1_OFF), 0x00, 0x0},     // DBI_RO_RW Disable
  {PCIE_REG_OP_DSB},

  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF), HWIO_PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_T_MIN_PHASE23_BMSK, 0x00000000},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN3_EQ_CONTROL_OFF), HWIO_PCIE_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_VEC_BMSK, 0x00000000},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN3_RELATED_OFF), HWIO_PCIE_GEN3_RELATED_OFF_GEN3_ZRXDC_NONCOMPL_BMSK, 0x00000000},

/*  MaxPayloadSize : 0 => 128 bytes, 1 => 256 bytes, for now leave it to default value */
//  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_DEVICE_CAPABILITIES_REG), HWIO_PCIE_DEVICE_CAPABILITIES_REG_PCIE_CAP_MAX_PAYLOAD_SIZE_BMSK, 0x0},

  {PCIE_REG_OP_DSB},

/*************************************************
 *  Payload
 *   Size       x1    x2    x4
 *    128      333   224   169
 *    256      512   313   214
 *    512      655   385   250
 *   1024     1167   641   378
***************************************************/
#define UPDATE_FC_VALUE_TO_USE                        64
#define UPDATE_FC_OVERRIDE_VALUE    (((UINT32)1 << HWIO_PCIE_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_EN_SHFT) | (UPDATE_FC_VALUE_TO_USE << HWIO_PCIE_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_SHFT))

  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_QUEUE_STATUS_OFF), 0x0, UPDATE_FC_OVERRIDE_VALUE},

  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_TYPE1_STATUS_COMMAND_REG), 0x6, 0x6},

  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t link_speed_limit_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_LINK_CONTROL2_LINK_STATUS2_REG), HWIO_PCIE_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED_BMSK, PORT_LINK_SPEED_GEN_2},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t init_plim_seq[] =
{
  /* For 1000 ms => counter value = 19,200,000 @ 19.2MHz
   * for x ms => 19200 * x */
#define L1SS_TIMEOUT_COUNTER_MILLI_SEC(x)    (19200 * (x))

  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_PARF_L1SUB_AHB_CLK_MAX_TIMER), 0x0, L1SS_TIMEOUT_COUNTER_MILLI_SEC(20)},
  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_PARF_PLIM_CTRL), 0x0, 0x01},

  {PCIE_REG_OP_DSB},

  {PCIE_REG_OP_DELAY, 0, 0, 2000},

  {PCIE_REG_OP_POLL, HWIO_OFFS(PCIE_PARF_PLIM_STATUS), 0x4, TRUE},

  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t port_plim_init_cfg[] =
{
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(init_plim_seq),

  {PcieSeq_Stop}
};

/*******************************************************************************
 *               Port A init Configuration
 ******************************************************************************/
STATIC CONST pcie_reg_init_cfg_t port_A_x2_phy_init_cfg[] =
{
  {PcieQcSoCVer_All,  ahb_reg,  REG_WRITE_TYPE(port_A_pwrup_seq),
  {PcieQcSoCVer_All,  ahb_reg,  REG_WRITE_TYPE(port_A_x2_bias_init_seq),
  {PcieQcSoCVer_All,  ahb_reg,  REG_WRITE_TYPE(port_A_phy_init_seq),
  {PcieQcSoCVer_All,  ahb_reg,  REG_WRITE_TYPE(port_A_start_seq),

  {PcieQcSoCVer_All,  ahb_reg,  REG_OP_TYPE(phy_delay_seq),

  {PcieQcSoCVer_All,  ahb_reg,  REG_OP_TYPE(port_A_phy_poll_seq),

  {PcieQcSoCVer_All,  axi_reg,  REG_OP_TYPE(port_x2_lane_seq),
  {PcieQcSoCVer_All,  ahb_reg,  REG_OP_TYPE(post_phy_pwr_up_init_seq),
  {PcieQcSoCVer_All,  axi_reg,  REG_OP_TYPE(post_phy_pwr_up_dbi_init_seq),

  {PcieQcSoCVer_All,  ahb_reg,  REG_OP_TYPE(init_plim_seq),

  {PcieSeq_Stop}
};

/*******************************************************************************
 *               Port B init Configuration
 ******************************************************************************/
STATIC CONST pcie_reg_init_cfg_t port_B_x2_phy_init_cfg[] =
{
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_B_pwrup_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_B_x2_bias_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_B_phy_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_B_start_seq),

  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(phy_delay_seq),

  /* Check if the PHY PLL is locked */
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(port_B_phy_poll_seq),

  /* Perform post power up sequence */
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(port_x2_lane_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(post_phy_pwr_up_init_seq),
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(post_phy_pwr_up_dbi_init_seq),

  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(init_plim_seq),

  {PcieSeq_Stop}
};

/*******************************************************************************
 *               Port A/B x4 init Configuration
 ******************************************************************************/
STATIC CONST pcie_reg_init_cfg_t port_x4_phy_init_cfg[] =
{
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_A_pwrup_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_A_x4_bias_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_A_phy_init_seq),

  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_B_x4_bias_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_B_phy_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_A_start_seq),

  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(phy_delay_seq),

  /* Check if the PHY PLL is locked */
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(port_A_phy_poll_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(port_B_phy_poll_seq),

  /* Perform post power up sequence */
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(port_x4_lane_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(post_phy_pwr_up_init_seq),
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(post_phy_pwr_up_dbi_init_seq),

  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(init_plim_seq),

  {PcieSeq_Stop}
};

/*******************************************************************************
 *               Port 4 init Configuration
 ******************************************************************************/
#if 1
STATIC CONST pcie_reg_init_cfg_t port_4_phy_init_cfg[] =
{
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_4_phy_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_4_phy_start_seq),

  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(phy_delay_seq),

  /* Check if the PHY PLL is locked */
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(port_4_phy_poll_seq),

  /* Perform post power up sequence */
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(port_x1_lane_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(post_phy_pwr_up_init_seq),
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(post_phy_pwr_up_dbi_init_seq),

  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(link_speed_limit_seq),

  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(init_plim_seq),

  {PcieSeq_Stop}
};
#endif

/*******************************************************************************
 *     Env specific driver config per port
 ******************************************************************************/
static const pcie_drvr_cfg_t pcie_2a_drvr_cfg = {
      .port_clk_cfg           = &pcie_clk_rp2a,
      .port_gpio_cfg          = gpio_config_rp2a,
};

static const pcie_drvr_cfg_t pcie_2b_drvr_cfg = {
      .port_clk_cfg           = &pcie_clk_rp2b,
      .port_gpio_cfg          = gpio_config_rp2b,
};

static const pcie_drvr_cfg_t pcie_3a_drvr_cfg = {
      .port_clk_cfg           = &pcie_clk_rp3a,
      .port_gpio_cfg          = gpio_config_rp3a,
};

static const pcie_drvr_cfg_t pcie_3b_drvr_cfg = {
      .port_clk_cfg           = &pcie_clk_rp3b,
      .port_gpio_cfg          = gpio_config_rp3b,
};

static const pcie_drvr_cfg_t pcie_4_drvr_cfg = {
      .port_clk_cfg           = &pcie_clk_rp4,
      .port_gpio_cfg          = gpio_config_rp4,
};

/*******************************************************************************
 *               Target port lane settings
 ******************************************************************************/
  /* TCSR_PCIE_CTRL_4LN_CONFIG_SEL[1:0]:
   *
   * [0]  :  0  : 2A x2, 2B x2
   *      :  1  : 2A x4, 2B NA
   *
   * [1]  :  0  : 3A x2, 3B x2
   *      :  1  : 3A x4, 3B NA
   *
   */

static const pcie_reg_field_val_t port_option_set_2A_x4_2B_NA =
{
   .reg_base_addr = (uint32*)HWIO_PCIE_CTRL_4LN_CONFIG_SEL_ADDR, .reg_offset = 0,
   .fld_shift = 0, .fld_mask = 0x1, .fld_val = 0x1,
};

static const pcie_reg_field_val_t port_option_set_2A_x2_2B_x2 =
{
   .reg_base_addr = (uint32*)HWIO_PCIE_CTRL_4LN_CONFIG_SEL_ADDR, .reg_offset = 0,
   .fld_shift = 0, .fld_mask = 0x1, .fld_val = 0x0,
};

static const pcie_reg_field_val_t port_option_set_3A_x4_3B_NA =
{
   .reg_base_addr = (uint32*)HWIO_PCIE_CTRL_4LN_CONFIG_SEL_ADDR, .reg_offset = 0,
   .fld_shift = 1, .fld_mask = 0x1, .fld_val = 0x1,
};

static const pcie_reg_field_val_t port_option_set_3A_x2_3B_x2 =
{
   .reg_base_addr = (uint32*)HWIO_PCIE_CTRL_4LN_CONFIG_SEL_ADDR, .reg_offset = 0,
   .fld_shift = 1, .fld_mask = 0x1, .fld_val = 0x0,
};

#define RP_CONFIG_2A_X4      "2A_x4_2B_NA"
#define RP_CONFIG_2A_X2      "2A_x2_2B_x2"
#define RP_CONFIG_3A_X4      "3A_x4_3B_NA"
#define RP_CONFIG_3A_X2      "3A_x2_3B_x2"

/*******************************************************************************
 *               Port 2A/2B config definitions
 ******************************************************************************/
static const pcie_port_config_t port_2A_x4_cfg[] =
{
   {
      .hw_rp_index            = 2,
      .driver_config          = &pcie_2a_drvr_cfg,
      .port_mem_bases         = port_2a_mem_region,
      .port_phy_init_cfg      = port_x4_phy_init_cfg,
      .port_phy_deinit_cfg    = port_x4_phy_de_init_cfg,
      .loopback_cfg           = &port_x4_loopback_seq,
      .perst_pin              = RC_2A_GPIO_PCIE_RESET,
      .entp_mgmt_idx          = 0,

      .port_attributes        = (PORT_ATTRIB_ASPM_EN_L1_EN_L0)

//      .ltr_threshold_scale    = LTR_TH_SCALE_1us,
//      .ltr_threshold_val      = 150,
   },
};

const uint8_t port_2A_x4_cfg_len = ARRAY_LENGTH(port_2A_x4_cfg);

static const pcie_port_config_t port_2A_x2_2B_x2_cfg[] =
{
   {
      .hw_rp_index            = 2,
      .driver_config          = &pcie_2a_drvr_cfg,
      .port_mem_bases         = port_2a_mem_region,
      .port_phy_init_cfg      = port_A_x2_phy_init_cfg,
      .port_phy_deinit_cfg    = port_A_phy_de_init_cfg,
      .loopback_cfg           = &port_A_loopback_seq,
      .perst_pin              = RC_2A_GPIO_PCIE_RESET,
      .entp_mgmt_idx          = 0,
      .port_attributes        = (PORT_ATTRIB_ASPM_EN_L1_EN_L0)

//      .ltr_threshold_scale    = LTR_TH_SCALE_1us,
//      .ltr_threshold_val      = 150,
   },
   {
      .hw_rp_index            = 3,
      .driver_config          = &pcie_2b_drvr_cfg,
      .port_mem_bases         = port_2b_mem_region,
      .port_phy_init_cfg      = port_B_x2_phy_init_cfg,
      .port_phy_deinit_cfg    = port_B_phy_de_init_cfg,
      .loopback_cfg           = &port_B_loopback_seq,
      .perst_pin              = RC_2B_GPIO_PCIE_RESET,
      .entp_mgmt_idx          = 1,
      .port_attributes        = (PORT_ATTRIB_ASPM_EN_L1_EN_L0)
   },
};

const uint8_t port_2A_x2_2B_x2_cfg_len = ARRAY_LENGTH(port_2A_x2_2B_x2_cfg);

/*******************************************************************************
 *               Port 3A/3B config definitions
 ******************************************************************************/
static const pcie_port_config_t port_3A_x4_cfg[] =
{
   {
      .hw_rp_index            = 4,
      .driver_config          = &pcie_3a_drvr_cfg,
      .port_mem_bases         = port_3a_mem_region,
      .port_phy_init_cfg      = port_x4_phy_init_cfg,
      .port_phy_deinit_cfg    = port_x4_phy_de_init_cfg,
      .loopback_cfg           = &port_x4_loopback_seq,
      .perst_pin              = RC_3A_GPIO_PCIE_RESET,
      .entp_mgmt_idx          = 2,
      .port_attributes        = (PORT_ATTRIB_ASPM_EN_L1_EN_L0)
   },
};

const uint8_t port_3A_x4_cfg_len = ARRAY_LENGTH(port_3A_x4_cfg);

static const pcie_port_config_t port_3A_x2_3B_x2_cfg[] =
{
   {
      .hw_rp_index            = 4,
      .driver_config          = &pcie_3a_drvr_cfg,
      .port_mem_bases         = port_3a_mem_region,
      .port_phy_init_cfg      = port_A_x2_phy_init_cfg,
      .port_phy_deinit_cfg    = port_A_phy_de_init_cfg,
      .loopback_cfg           = &port_A_loopback_seq,
      .perst_pin              = RC_3A_GPIO_PCIE_RESET,
      .entp_mgmt_idx          = 2,
      .port_attributes        = (PORT_ATTRIB_ASPM_EN_L1_EN_L0)
   },
   {
      .hw_rp_index            = 5,
      .driver_config          = &pcie_3b_drvr_cfg,
      .port_mem_bases         = port_3b_mem_region,
      .port_phy_init_cfg      = port_B_x2_phy_init_cfg,
      .port_phy_deinit_cfg    = port_B_phy_de_init_cfg,
      .loopback_cfg           = &port_B_loopback_seq,
      .perst_pin              = RC_3B_GPIO_PCIE_RESET,
      .entp_mgmt_idx          = 3,
      .port_attributes        = (PORT_ATTRIB_ASPM_EN_L1_EN_L0)
   },
};

const uint8_t port_3A_x2_3B_x2_cfg_len = ARRAY_LENGTH(port_3A_x2_3B_x2_cfg);

/*******************************************************************************
 *               Port 4 config definitions
 ******************************************************************************/
static const pcie_port_config_t port_4_cfg[] =
{
   {
      .hw_rp_index            = 6,
      .driver_config          = &pcie_4_drvr_cfg,
      .port_mem_bases         = port_4_mem_region,
      .port_phy_init_cfg      = port_4_phy_init_cfg,
      .port_phy_deinit_cfg    = port_4_phy_de_init_cfg,
      .loopback_cfg           = &port_4_loopback_seq,
      .perst_pin              = RC_4_GPIO_PCIE_RESET,
      .entp_mgmt_idx          = 4,
      .port_attributes        = (PORT_ATTRIB_ASPM_EN_L1_EN_L0)
   },
};

const uint8_t port_4_cfg_len = ARRAY_LENGTH(port_4_cfg);


/*******************************************************************************
 *               Makena port configurations for public
 ******************************************************************************/
/* Let ports 2AB/3AB be selected by 4Lane config register based conditional */
/* NOTE: Customize the port option support required, *only* in this array,
 *       for the minimal footprint image as required. All other data will be
 *       automatically excluded by linker if not referenced and saves space */
static const pcie_port_options_config_t target_port_options[] = 
{
   {
      .port_config_name = RP_CONFIG_2A_X4,
      .exclusive_key = STR_ID('2', 'A', '2', 'B'),
      .default_enable = 0,
      .config_select_condition = &port_option_set_2A_x4_2B_NA,
      .ports_config_cnt = &port_2A_x4_cfg_len,
      .ports_config_list = port_2A_x4_cfg,
   },

   {
      .port_config_name = RP_CONFIG_2A_X2,
      .exclusive_key = STR_ID('2', 'A', '2', 'B'),
      .default_enable = 0,
      .config_select_condition = &port_option_set_2A_x2_2B_x2,
      .ports_config_cnt = &port_2A_x2_2B_x2_cfg_len,
      .ports_config_list = port_2A_x2_2B_x2_cfg,
   },

   {
      .port_config_name = RP_CONFIG_3A_X4,
      .exclusive_key = STR_ID('3', 'A', '3', 'B'),
      .default_enable = 0,
      .config_select_condition = &port_option_set_3A_x4_3B_NA,
      .ports_config_cnt = &port_3A_x4_cfg_len,
      .ports_config_list = port_3A_x4_cfg,
   },

   {
      .port_config_name = RP_CONFIG_3A_X2,
      .exclusive_key = STR_ID('3', 'A', '3', 'B'),
      .default_enable = 0,
      .config_select_condition = &port_option_set_3A_x2_3B_x2,
      .ports_config_cnt = &port_3A_x2_3B_x2_cfg_len,
      .ports_config_list = port_3A_x2_3B_x2_cfg,
   },

   {
      .port_config_name = "4x1",
      .exclusive_key = STR_ID('4', 'x', '1', ' '),
      .default_enable = 1,   // No HW conditional, so enable it by default
      .config_select_condition = NULL,
      .ports_config_cnt = &port_4_cfg_len,
      .ports_config_list = port_4_cfg,
   },

#if 0
   {
      .port_config_name = "USB4_Tunn_0_1",
      .exclusive_key = STR_ID('U', 'T', '0', '1'),
      .default_enable = 1,
      .config_select_condition = NULL,
      // .ports_config_cnt = ARRAY_LENGTH(port_0_1_usb_tunnel_cfg),
      .ports_config_list = port_0_1_usb_tunnel_cfg,
   },

#endif
};

static const mem_region_t target_common_mem_regions[] =
{
  /* TCSR register space */
  {.pa=TCSR_TCSR_REGS_REG_BASE, .sz=TCSR_TCSR_REGS_REG_BASE_SIZE},
  {.pa=0, .sz=0},
};

#endif   /* __PCIE_TARGET_PORT_CONFIG_H__ */

