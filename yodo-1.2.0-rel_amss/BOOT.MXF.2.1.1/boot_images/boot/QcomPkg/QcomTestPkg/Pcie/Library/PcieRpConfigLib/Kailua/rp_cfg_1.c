/*
 *  PCIe root port target config
 */
/*============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
============================================================================*/

#include "kailua_pcie_1.h"
#include "pcie_cfg_types.h"
#include "pcie_hwio_base.h"

#define REG_OP_TYPE(x)        PCIE_REG_OP_SEQ, {.reg_op_seq = x}}
#define REG_WRITE_TYPE(x)     PCIE_REG_WRITE_SEQ, {.reg_write_val_seq = x}}

#define __msmhwio_offs(hwiosym)                                 HWIO_##hwiosym##_OFFS
#define __msmhwio_mask(reg,mask)                                HWIO_##reg##_##mask##_BMSK
#define HWIO_OFFS(hwiosym)                               __msmhwio_offs(hwiosym)
#define HWIO_REG_MASK(reg,mask)                          __msmhwio_offs(reg),__msmhwio_mask(reg, mask)


/*******************************************************************************
 *
 *                       Controller DBI settings
 *
 *******************************************************************************/
/* Set the max capable lane width */
/* 1 for 1 lane
 * 3 for 2 lane
 * 7 for 4 lane */
#define PORT_4_LANE     4
#define PORT_2_LANE     2
#define PORT_1_LANE     1

/* This macro will NOT work for 8 lanes */
#define PORT_LINK_LANE_CAPABLE_VAL(x) ((x << 1) - 1)

CONST pcie_reg_op_t kailua_port_1_x2_lane_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PORT_LINK_CTRL_OFF), HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_BMSK,
                     (PORT_LINK_LANE_CAPABLE_VAL(PORT_2_LANE) << HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_SHFT)},
   {PCIE_REG_OP_STOP},
};

/*******************************************************************************
 *       Post PHY power ON sequence 
 ******************************************************************************/
CONST pcie_reg_op_t kailua_port_1_post_phy_pwr_up_init_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_DEVICE_TYPE), HWIO_PCIE_PARF_DEVICE_TYPE_DEVICE_TYPE_BMSK, HWIO_PCIE_PARF_DEVICE_TYPE_DEVICE_TYPE_RC_FVAL},
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_PM_CTRL), HWIO_PCIE_PARF_PM_CTRL_REQ_NOT_ENTR_L1_BMSK, 0x0},
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_SYS_CTRL), HWIO_PCIE_PARF_SYS_CTRL_AUX_PWR_DET_BMSK, (0x01 << HWIO_PCIE_PARF_SYS_CTRL_AUX_PWR_DET_SHFT)},
   {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_PARF_SLV_ADDR_SPACE_SIZE), 0, 0x01000000},
   {PCIE_REG_OP_STOP},
};

CONST pcie_reg_op_t kailua_port_1_phy_delay_seq[] =
{
   {PCIE_REG_OP_DELAY, 0, 0, 2000},
   {PCIE_REG_OP_STOP},
};

#define PORT_LINK_SPEED_GEN_1     1
#define PORT_LINK_SPEED_GEN_2     2
#define PORT_LINK_SPEED_GEN_3     3
#define PORT_LINK_SPEED_GEN_4     4

CONST pcie_reg_op_t kailua_port_1_set_link_speed_gen_3[] =
{
    /* Link Speed */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_LINK_CONTROL2_LINK_STATUS2_REG), HWIO_PCIE_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED_BMSK, PORT_LINK_SPEED_GEN_3},
  {PCIE_REG_OP_DSB},
  {PCIE_REG_OP_STOP},
};

CONST pcie_reg_op_t kailua_port_1_set_link_speed_gen_4[] =
{
    /* Link Speed */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_LINK_CONTROL2_LINK_STATUS2_REG), HWIO_PCIE_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED_BMSK, PORT_LINK_SPEED_GEN_4},
  {PCIE_REG_OP_DSB},
  {PCIE_REG_OP_STOP},
};

CONST pcie_reg_op_t kailua_port_1_post_phy_pwr_up_dbi_init_seq[] =
{
    /* Fix NFTS */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_ACK_F_ASPM_CTRL_OFF), HWIO_PCIE_ACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS_BMSK, (0x80 << HWIO_PCIE_ACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS_SHFT)},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_ACK_F_ASPM_CTRL_OFF), HWIO_PCIE_ACK_F_ASPM_CTRL_OFF_ACK_N_FTS_BMSK, (0x80 << HWIO_PCIE_ACK_F_ASPM_CTRL_OFF_ACK_N_FTS_SHFT)},

  /* Treats out-of-bar TLPs as supported request - MUST for RC mode. Data book: Table I-2 */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_SYMBOL_TIMER_FILTER_1_OFF), HWIO_PCIE_SYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1_BMSK, (4 << HWIO_PCIE_SYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1_SHFT)},
  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_AUX_CLK_FREQ_OFF), 0, 19},

  /* Allow establishing connection on one line even if there is a termination on the second line. Othewise the link will go to compliance */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN2_CTRL_OFF), HWIO_PCIE_GEN2_CTRL_OFF_NUM_OF_LANES_BMSK, (0x01 << HWIO_PCIE_GEN2_CTRL_OFF_NUM_OF_LANES_SHFT)},
  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_MISC_CONTROL_1_OFF), 0, 0x1},
  {PCIE_REG_OP_DSB},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_ROOT_CONTROL_ROOT_CAPABILITIES_REG), HWIO_PCIE_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_CRS_SW_VISIBILITY_BMSK, 0},

  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_TYPE1_CLASS_CODE_REV_ID_REG),
    (HWIO_PCIE_TYPE1_CLASS_CODE_REV_ID_REG_BASE_CLASS_CODE_BMSK | HWIO_PCIE_TYPE1_CLASS_CODE_REV_ID_REG_SUBCLASS_CODE_BMSK),
    (PCIE_CLASS_CODE_BRIDGE_DEVICE | PCIE_SUBCLASS_CODE_PCI_2_PCI_BRIDGE)},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_SLOT_CAPABILITIES_REG), HWIO_PCIE_SLOT_CAPABILITIES_REG_PCIE_CAP_HOT_PLUG_CAPABLE_BMSK, 0},
  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_MISC_CONTROL_1_OFF), 0, 0},
  {PCIE_REG_OP_DSB},
  /* 52.08333333333 nano seconds per counter value for a 19.2 MHz clock
   * Programmed counter value = Time Required in seconds / 0.00000005208333333333
   * Begin with 20ms as inactivity timer.
   * Counter = .020 / 0.00000005208333333333 = 0x5DC00
   */

  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF), HWIO_PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_T_MIN_PHASE23_BMSK, 0},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN3_EQ_CONTROL_OFF), HWIO_PCIE_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_VEC_BMSK, 0},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN3_RELATED_OFF), HWIO_PCIE_GEN3_RELATED_OFF_GEN3_ZRXDC_NONCOMPL_BMSK, 0},
   
  {PCIE_REG_OP_DSB},

  {PCIE_REG_OP_STOP},
};

/*******************************************************************************
 *    Core Config:  Gen 4 x2, Hw offset 1
 ******************************************************************************/
/*******************************************************************************
 *    PMIC Power settings
 ******************************************************************************/
#define PMIC_NPA_CLIENT_NODE_PCIE1 "/pmic/client/pcie1" 

static const pcie_pmic_config_t kailua_port_1_pmic_cfg = 
{
   .node_id = PMIC_NPA_CLIENT_NODE_PCIE1,
};

/*******************************************************************************
 *    Register region map
 ******************************************************************************/
static mem_region_t kailua_port_1_mem_region[max_mem_reg] =
{
  /* axi_reg: DBI register space */
  [axi_reg] = {.pa=PCIE_GEN4X2_SPACE_BASE, .sz=PCIE_GEN4X2_SPACE_SIZE},

  /* ahb_reg: PARF register space */
  {.pa=PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_EDMA_BASE, .sz=PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_EDMA_SIZE},
};

/*******************************************************************************
 *   ICB bandwidth request settings
 ******************************************************************************/
STATIC CONST ICBArb_RequestType kailua_pcie_1_icb_request[] =
{
  {
    .arbType = ICBARB_REQUEST_TYPE_3,
    .arbData.type3 =
    {
      .uIb = ((400ULL) << 20), /* Instantaneous bandwidth in Bytes/second */
      .uAb = ((400ULL) << 20), /* Arbitrated bandwidth in Bytes/second */
      .uLatencyNs = 0          /* Latency requirement in nanoseconds */
    }
  },
};

STATIC CONST ICBArb_MasterSlaveType kailua_pcie_1_icb_mstr_slv_lst[] =
{
  {
    .eMaster = ICBID_MASTER_PCIE_1,
    .eSlave = ICBID_SLAVE_EBI1
  },
};

STATIC pcieIcbClkBW_t kailua_pcie_1_icb_bw[] =
{
  {
    .npa_client_name = "pcie_1",
    .ms_list = kailua_pcie_1_icb_mstr_slv_lst,
    .ms_size = sizeof(kailua_pcie_1_icb_mstr_slv_lst),
    .req_list = kailua_pcie_1_icb_request,
    .req_size = sizeof(kailua_pcie_1_icb_request)
  },
};

/*******************************************************************************
 *              PCIe port clk related settings
 ******************************************************************************/
STATIC CONST char * kailua_pcie_reset_clks_rp1[] =
{
  "gcc_pcie_1_aux_clk",
  NULL
};

STATIC CONST char * kailua_pcie_gcc_clks_rp1[] =
{
  "gcc_pcie_1_cfg_ahb_clk",
  "tcsr_pcie_1_clkref_en",
  "gcc_pcie_1_pipe_clk",
  "gcc_pcie_1_aux_clk",
  "gcc_pcie_1_phy_aux_clk",
  "gcc_aggre_noc_pcie_axi_clk",
  "gcc_pcie_1_slv_q2a_axi_clk",
  "gcc_pcie_1_mstr_axi_clk",
  "gcc_pcie_1_slv_axi_clk",
  "gcc_pcie_1_phy_rchng_clk",
  "gcc_ddrss_pcie_sf_qtb_clk",
  "gcc_cnoc_pcie_sf_axi_clk",
  NULL
};

CONST pcie_clk_mux_cfg_t kailua_pcie_1_clk_mux = 
{
   .clk_name = "gcc_pcie_1_pipe_clk",
   .en_mux_val = 0,
   .dis_mux_val = 2,
};

CONST clk_freq_cfg_t kailua_pcie_1_clk_settings[] =
{
  {.freq = 19200000,  .name = "gcc_pcie_1_aux_clk"},
  {.freq = 100000000, .name = "gcc_pcie_1_phy_rchng_clk"},
  {.freq = 0, .name = NULL},
};

STATIC CONST pcie_clocks_cfg_t kailua_pcie_clk_rp1 =
{
   .clk_pwr    = "gcc_pcie_1_gdsc",
   .phy_pwr    = "gcc_pcie_1_phy_gdsc",
   .core_clks  = kailua_pcie_gcc_clks_rp1,
   .clk_reset  = kailua_pcie_reset_clks_rp1,
   .clk_mux    = &kailua_pcie_1_clk_mux,
   .clk_freq   = kailua_pcie_1_clk_settings,
   .icb_bw     = kailua_pcie_1_icb_bw,
};

/*******************************************************************************
 *              PCIe port GPIO settings
 ******************************************************************************/
#define KAILUA_RC_1_GPIO_PCIE_RESET      97
#define KAILUA_RC_1_GPIO_CLK_REQ         98
#define KAILUA_RC_1_GPIO_PCIE_WAKE       99

STATIC CONST pcie_gpio_cfg_t kailua_gpio_config_rp1[] =
{
  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = KAILUA_RC_1_GPIO_CLK_REQ,
    .tlmm.func_sel       = 1,
    .tlmm.direction      = GPIO_INPUT,
    .tlmm.pull           = GPIO_PULL_UP,
    .tlmm.drive_strength = GPIO_2MA,
    .tlmm.value          = GPIO_LOW_VALUE
   }
  },

  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = KAILUA_RC_1_GPIO_PCIE_RESET,
    .tlmm.func_sel       = 0,
    .tlmm.direction      = GPIO_OUTPUT,
    .tlmm.pull           = GPIO_NO_PULL,
    .tlmm.drive_strength = GPIO_2MA,
    .tlmm.value          = GPIO_LOW_VALUE
   }
  },

  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = KAILUA_RC_1_GPIO_PCIE_WAKE,
    .tlmm.func_sel       = 0,
    .tlmm.direction      = GPIO_INPUT,
    .tlmm.pull           = GPIO_PULL_UP,
    .tlmm.drive_strength = GPIO_2MA,
    .tlmm.value          = GPIO_LOW_VALUE
   }
  },

  { .cfg_type = NONE, { .delay_us = NONE}},
};

/*******************************************************************************
 *
 *                           PORT 1 Phy
 *
 *******************************************************************************/
STATIC CONST pcie_reg_write_val_t kailua_port_1_phy_init_seq[] =
{
   {HWIO_OFFS(PCIE_PARF_DEVICE_TYPE),                                 0x04},

   {HWIO_OFFS(PCIE4_PCS_COM_POWER_DOWN_CONTROL),    0x03},  //    Remove PHY from powerdown mode and allow refclk drive
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_TX),    0x1D},  //    Adjust rescode to TX
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_RX),    0x03},  //    Adjust rescode to RX
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_1),    0x01},  //    Lane analog setting adjustment
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_2),    0x00},  //    Lane analog setting adjustment
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_3),    0x51},  //    Lane analog setting adjustment
   {HWIO_OFFS(QSERDES_TX0_TRAN_DRVR_EMP_EN),    0x34},  //    Don't use txdata clk enable from PCS
   {HWIO_OFFS(QSERDES_RX0_UCDR_FO_GAIN_RATE2),    0x0C},  //    Adjust G3 CDR first order gain
   {HWIO_OFFS(QSERDES_RX0_UCDR_FO_GAIN_RATE3),    0x0A},  //    Adjust G4 CDR first order gain
   {HWIO_OFFS(QSERDES_RX0_UCDR_SO_GAIN_RATE2),    0x04},  //    Adjust G3 CDR second order gain
   {HWIO_OFFS(QSERDES_RX0_UCDR_PI_CONTROLS),    0x16},  //    Disable fastlock
   {HWIO_OFFS(QSERDES_RX0_UCDR_SO_ACC_DEFAULT_VAL_RATE3),    0x00},  //    Adjust SO Acc init value for G4
   {HWIO_OFFS(QSERDES_RX0_RX_IVCM_CAL_CTRL2),    0x80},  //    Adjust summer cal ref source
   {HWIO_OFFS(QSERDES_RX0_RX_IVCM_POSTCAL_OFFSET),    0x7C},  //    Adjust IVCM postcal offset
   {HWIO_OFFS(QSERDES_RX0_DFE_3),    0x05},  //    tap2 man mode; tap1 10nm mode with sign flip
   {HWIO_OFFS(QSERDES_RX0_VGA_CAL_MAN_VAL),    0x0A},  //    Adjust starting value
   {HWIO_OFFS(QSERDES_RX0_GM_CAL),    0x0D},  //    Enable GM cal
   {HWIO_OFFS(QSERDES_RX0_RX_EQU_ADAPTOR_CNTRL4),    0x0B},  //    Adjust starting value
   {HWIO_OFFS(QSERDES_RX0_SIGDET_ENABLES),    0x1C},  //    Force use of local bias; bypass pulse width filter
   {HWIO_OFFS(QSERDES_RX0_PHPRE_CTRL),    0x20},  //    Set pre txadapt mode to 0
   {HWIO_OFFS(QSERDES_RX0_DFE_CTLE_POST_CAL_OFFSET),    0x30},  //    Offset CTLE code by -2
   {HWIO_OFFS(QSERDES_RX0_Q_PI_INTRINSIC_BIAS_RATE32),    0x09},  //    Adjust q_pi offset for Gen3/Gen4
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B0),    0x14},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B1),    0xB3},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B2),    0x58},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B3),    0x9A},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B4),    0x26},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B5),    0xB6},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B6),    0xEE},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B0),    0xDB},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B1),    0xDB},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B2),    0xA0},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B3),    0xDF},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B4),    0x78},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B5),    0x76},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B6),    0xFF},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_TX),    0x1D},  //    Adjust rescode to TX
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_RX),    0x03},  //    Adjust rescode to RX
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_1),    0x01},  //    Lane analog setting adjustment
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_2),    0x00},  //    Lane analog setting adjustment
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_3),    0x51},  //    Lane analog setting adjustment
   {HWIO_OFFS(QSERDES_TX1_TRAN_DRVR_EMP_EN),    0x34},  //    Don't use txdata clk enable from PCS
   {HWIO_OFFS(QSERDES_RX1_UCDR_FO_GAIN_RATE2),    0x0C},  //    Adjust G3 CDR first order gain
   {HWIO_OFFS(QSERDES_RX1_UCDR_FO_GAIN_RATE3),    0x0A},  //    Adjust G4 CDR first order gain
   {HWIO_OFFS(QSERDES_RX1_UCDR_SO_GAIN_RATE2),    0x04},  //    Adjust G3 CDR second order gain
   {HWIO_OFFS(QSERDES_RX1_UCDR_PI_CONTROLS),    0x16},  //    Disable fastlock
   {HWIO_OFFS(QSERDES_RX1_UCDR_SO_ACC_DEFAULT_VAL_RATE3),    0x00},  //    Adjust SO Acc init value for G4
   {HWIO_OFFS(QSERDES_RX1_RX_IVCM_CAL_CTRL2),    0x80},  //    Adjust summer cal ref source
   {HWIO_OFFS(QSERDES_RX1_RX_IVCM_POSTCAL_OFFSET),    0x7C},  //    Adjust IVCM postcal offset
   {HWIO_OFFS(QSERDES_RX1_DFE_3),    0x05},  //    tap2 man mode; tap1 10nm mode with sign flip
   {HWIO_OFFS(QSERDES_RX1_VGA_CAL_MAN_VAL),    0x0A},  //    Adjust starting value
   {HWIO_OFFS(QSERDES_RX1_GM_CAL),    0x0D},  //    Enable GM cal
   {HWIO_OFFS(QSERDES_RX1_RX_EQU_ADAPTOR_CNTRL4),    0x0B},  //    Adjust starting value
   {HWIO_OFFS(QSERDES_RX1_SIGDET_ENABLES),    0x1C},  //    Force use of local bias; bypass pulse width filter
   {HWIO_OFFS(QSERDES_RX1_PHPRE_CTRL),    0x20},  //    Set pre txadapt mode to 0
   {HWIO_OFFS(QSERDES_RX1_DFE_CTLE_POST_CAL_OFFSET),    0x30},  //    Offset CTLE code by -2
   {HWIO_OFFS(QSERDES_RX1_Q_PI_INTRINSIC_BIAS_RATE32),    0x09},  //    Adjust q_pi offset for Gen3/Gen4
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B0),    0x14},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B1),    0xB3},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B2),    0x58},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B3),    0x9A},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B4),    0x26},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B5),    0xB6},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B6),    0xEE},  //    Rx setting adjustment for G3
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B0),    0xDB},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B1),    0xDB},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B2),    0xA0},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B3),    0xDF},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B4),    0x78},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B5),    0x76},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B6),    0xFF},  //    Rx setting adjustment for G4
   {HWIO_OFFS(QSERDES_LN_RXCLK_DIV2_CTRL),    0x01},  //    Gen1 clock management
   {HWIO_OFFS(QSERDES_LN_DFE_DAC_ENABLE1),    0x00},  //    Disable DFE tap1 DAC in all speeds
   {HWIO_OFFS(QSERDES_LN_TX_ADAPT_POST_THRESH1),    0x00},  //    Adjust txadpt post low threshold
   {HWIO_OFFS(QSERDES_LN_TX_ADAPT_POST_THRESH2),    0x1F},  //    Adjust txadpt post high threshold
   {HWIO_OFFS(QSERDES_LN_RX_MODE_RATE_0_1_B0),    0x12},  //    Rx setting adjustment for G1/G2
   {HWIO_OFFS(QSERDES_LN_RX_MODE_RATE_0_1_B1),    0x12},  //    Rx setting adjustment for G1/G2
   {HWIO_OFFS(QSERDES_LN_RX_MODE_RATE_0_1_B2),    0xDB},  //    Rx setting adjustment for G1/G2
   {HWIO_OFFS(QSERDES_LN_RX_MODE_RATE_0_1_B3),    0x9A},  //    Rx setting adjustment for G1/G2
   {HWIO_OFFS(QSERDES_LN_RX_MODE_RATE_0_1_B4),    0x38},  //    Rx setting adjustment for G1/G2
   {HWIO_OFFS(QSERDES_LN_RX_MODE_RATE_0_1_B5),    0xB6},  //    Rx setting adjustment for G1/G2
   {HWIO_OFFS(QSERDES_LN_RX_MODE_RATE_0_1_B6),    0x64},  //    Rx setting adjustment for G1/G2
   {HWIO_OFFS(QSERDES_LN_RX_MARG_COARSE_THRESH1_RATE210),    0x1F},  //    Max out value to prevent adjustment
   {HWIO_OFFS(QSERDES_LN_RX_MARG_COARSE_THRESH1_RATE3),    0x1F},  //    Max out value to prevent adjustment
   {HWIO_OFFS(QSERDES_LN_RX_MARG_COARSE_THRESH2_RATE210),    0x1F},  //    Max out value to prevent adjustment
   {HWIO_OFFS(QSERDES_LN_RX_MARG_COARSE_THRESH2_RATE3),    0x1F},  //    Max out value to prevent adjustment
   {HWIO_OFFS(QSERDES_LN_RX_MARG_COARSE_THRESH3_RATE210),    0x1F},  //    Max out value to prevent adjustment
   {HWIO_OFFS(QSERDES_LN_RX_MARG_COARSE_THRESH3_RATE3),    0x1F},  //    Max out value to prevent adjustment
   {HWIO_OFFS(QSERDES_LN_RX_MARG_COARSE_THRESH4_RATE3),    0x1F},  //    Max out value to prevent adjustment
   {HWIO_OFFS(QSERDES_LN_RX_MARG_COARSE_THRESH5_RATE3),    0x1F},  //    Max out value to prevent adjustment
   {HWIO_OFFS(QSERDES_LN_RX_MARG_COARSE_THRESH6_RATE3),    0x1F},  //    Max out value to prevent adjustment
   {HWIO_OFFS(QSERDES_LN_RX_SUMMER_CAL_SPD_MODE),    0x5B},  //    Adjust Gen4 summer speed
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE1),    0x26},  //    "0x97: 19.2Mhz refclk value: set SSC step size for Gen3/4 (4500ppm); 0x26: 38.4Mhz refclk value: set SSC step size for Gen3/4 (4500ppm)"
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE1),    0x03},  //    "0x0C: 19.2Mhz refclk value; 0x03: 38.4Mhz refclk value"
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE1),    0x06},  //    Gen3/4 PLL charge pump adjustment
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE1),    0x16},  //    Gen3/4 PLL RC loop filter adjustment
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE1),    0x36},  //    Gen3/4 PLL 2nd cap loop filter adjustment
   {HWIO_OFFS(QSERDES_PLL_CORECLK_DIV_MODE1),    0x04},  //    Set gen3/4 coreclk divider
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE1),    0x0A},  //    "0x14: 19.2Mhz refclk value: Gen3/4 PLL lock compare value; 0x0A: 38.4Mhz refclk value: Gen3/4 PLL lock compare value"
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE1),    0x1A},  //    "0x34: 19.2Mhz refclk value; 0x1A: 38.4Mhz refclk value"
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE1),    0x68},  //    "0xD0: 19.2Mhz refclk value: Gen3/4 PLL decimal divider value; 0x68: 38.4Mhz refclk value: Gen3/4 PLL decimal divider value"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE1),    0xAB},  //    "0x55: 19.2Mhz refclk value: Gen3/4 PLL fractional divider value; 0xAB: 38.4Mhz refclk value: Gen3/4 PLL fractional divider value"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE1),    0xAA},  //    "0x55: 19.2Mhz refclk value; 0xAA: 38.4Mhz refclk value"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE1),    0x02},  //    "0x05: 19.2Mhz refclk value; 0x02: 38.4Mhz refclk value"
   {HWIO_OFFS(QSERDES_PLL_HSCLK_SEL_1),    0x12},  //    Set HSCLK divider for gen1/2 and gen3/4
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE0),    0xF8},  //    "0xDE: 19.2Mhz refclk value: set SSC step size for Gen1/2 (4500ppm); 0xF8: 38.4Mhz refclk value: set SSC step size for Gen1/2 (4500ppm)"
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE0),    0x01},  //    "0x07: 19.2Mhz refclk value; 0x01: 38.4Mhz refclk value"
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE0),    0x06},  //    Gen1/2 PLL charge pump adjustment
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE0),    0x16},  //    Gen1/2 PLL RC loop filter adjustment
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE0),    0x36},  //    Gen1/2 PLL 2nd cap loop filter adjustment
   {HWIO_OFFS(QSERDES_PLL_CORECLK_DIV_MODE0),    0x0A},  //    Set gen1/2 coreclk divider
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE0),    0x04},  //    "0x0A: 19.2Mhz refclk value: Gen1/2 PLL lock compare value; 0x04: 38.4Mhz refclk value: Gen1/2 PLL lock compare value"
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE0),    0x0D},  //    "0x1A: 19.2Mhz refclk value; 0x0D: 38.4Mhz refclk value"
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE0),    0x41},  //    "0x82: 19.2Mhz refclk value: Gen1/2 PLL decimal divider value; 0x41: 38.4Mhz refclk value: Gen1/2 PLL decimal divider value"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE0),    0xAB},  //    "0x55: 19.2Mhz refclk value: Gen1/2 PLL fractional divider value; 0xAB: 38.4Mhz refclk value: Gen1/2 PLL fractional divider value"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE0),    0xAA},  //    "0x55: 19.2Mhz refclk value; 0xAA: 38.4Mhz refclk value"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE0),    0x01},  //    "0x03: 19.2Mhz refclk value; 0x01: 38.4Mhz refclk value"
   {HWIO_OFFS(QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1),    0x00},  //    
   {HWIO_OFFS(QSERDES_PLL_BG_TIMER),    0x0A},  //    "0x0E: 19.2Mhz refclk value; 0x0A: 38.4Mhz refclk value"
   {HWIO_OFFS(QSERDES_PLL_SSC_EN_CENTER),    0x00},  //    "0x00: Downspread SSC disabled (default, so no write needed); 0x01: Downspread SSC enabled"
   {HWIO_OFFS(QSERDES_PLL_SSC_PER1),    0x62},  //    "0x31: 19.2Mhz refclk value: set SSC frequency to 31.5KHz; 0x62: 38.4Mhz refclk value: set SSC frequency to 31.5KHz"
   {HWIO_OFFS(QSERDES_PLL_SSC_PER2),    0x02},  //    "0x01: 19.2Mhz refclk value; 0x02: 38.4Mhz refclk value"
   {HWIO_OFFS(QSERDES_PLL_POST_DIV_MUX),    0x40},  //    Set HSCLK divider for gen1/2 and gen3/4
   {HWIO_OFFS(QSERDES_PLL_BIAS_EN_CLKBUFLR_EN),    0x14},  //    Enable right side clock buffers
   {HWIO_OFFS(QSERDES_PLL_CLK_ENABLE1),    0x90},  //    Enable endpoint clock drive with pulldown when off
   {HWIO_OFFS(QSERDES_PLL_SYS_CLK_CTRL),    0x82},  //    Select SW endpoint enable
   {HWIO_OFFS(QSERDES_PLL_PLL_IVCO),    0x0f},  //    Adjust VCO current
   {HWIO_OFFS(QSERDES_PLL_SYSCLK_EN_SEL),    0x08},  //    "0x04: select internal diff cml clock inputs; 0x08: select SE cmos clock input"
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP_EN),    0x46},  //    Lock count = 512, lock range = +/-64
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP_CFG),    0x04},  //    Use same range values for all lock iterations
   {HWIO_OFFS(QSERDES_PLL_VCO_TUNE_MAP),    0x14},  //    Set mode0 as gen1/2 and mode1 as gen3/4
   {HWIO_OFFS(QSERDES_PLL_CLK_SELECT),    0x34},  //    Set rchng clock as endpoint refclk source during relock; set endpoint refclk swing
   {HWIO_OFFS(QSERDES_PLL_CORE_CLK_EN),    0xA0},  //    Set PLL lock clock divider
   {HWIO_OFFS(QSERDES_PLL_CMN_CONFIG_1),    0x06},  //    Set gen1/2 PLL feedback divide to 6
   {HWIO_OFFS(QSERDES_PLL_CMN_MISC1),    0x88},  //    Set hs_switch as part of rate change
   {HWIO_OFFS(QSERDES_PLL_CMN_MODE),    0x14},  //    VCCA selected as input to Vreg
   {HWIO_OFFS(QSERDES_PLL_VCO_DC_LEVEL_CTRL),    0x0F},  //    Increase Vreg
   {HWIO_OFFS(PCIE4_PCS_COM_G3S2_PRE_GAIN),    0x2E},  //    Adjust G3 pre gain for P7 compliance
   {HWIO_OFFS(PCIE4_PCS_COM_RX_SIGDET_LVL),    0xCC},  //    Adjust sigdet level
   {HWIO_OFFS(PCIE4_PCS_COM_EQ_CONFIG4),    0x00},  //    Disable G3 Tap345 adaption
   {HWIO_OFFS(PCIE4_PCS_COM_EQ_CONFIG5),    0x22},  //    Disable G3 Tap2 adaption; dfe freeze release w/o align
   {HWIO_OFFS(PCIE4_PCS_PCIE_ENDPOINT_REFCLK_DRIVE),    0xc1},  //    Enable endpoint refclk drive
   {HWIO_OFFS(PCIE4_PCS_COM_FLL_CNTRL2),    0x83},  //    "0x83: default setting (write not needed); 0x87: value for half frequency (required when more than 4 pipeline stages used at SOC)"
   {HWIO_OFFS(PCIE4_PCS_COM_FLL_CNT_VAL_L),    0x09},  //    "0x09: default setting (write not needed); 0x05: value for half frequency (required when more than 4 pipeline stages used at SOC)"
   {HWIO_OFFS(PCIE4_PCS_COM_FLL_CNT_VAL_H_TOL),    0xA2},  //    "0xA2: default setting (write not needed); 0xA1: value for half frequency (required when more than 4 pipeline stages used at SOC)"
   {HWIO_OFFS(PCIE4_PCS_PCIE_INT_AUX_CLK_CONFIG1),    0x02},  //    "0x02: FLL off - PHY aux_clk not generated (default value - write not needed);0x03: FLL on - PHY aux_clk generated (and used internally in L1ss mode); 0x0F: FLL on - PHY aux_clk generated (and used internally in all modes - for Lanai)"
   {HWIO_OFFS(PCIE4_PCS_PCIE_OSC_DTCT_ACTIONS),    0x00},  //    Disable osc detect
   {HWIO_OFFS(PCIE4_PCS_PCIE_EQ_CONFIG1),    0x16},  //    Flip post inc/dec mappings
   {HWIO_OFFS(PCIE4_PCS_PCIE_G4_EQ_CONFIG5),    0x02},  //    Disable G4 Tap2345 adaption
   {HWIO_OFFS(PCIE4_PCS_PCIE_G4_PRE_GAIN),    0x2E},  //    Adjust G4 pre gain for P7 compliance
   {HWIO_OFFS(PCIE4_PCS_PCIE_RX_MARGINING_CONFIG1),    0x03},  //    Enable rx margining in Gen3 and Gen4 (Gen3 needed for FOM)
   {HWIO_OFFS(PCIE4_PCS_PCIE_RX_MARGINING_CONFIG3),    0x28},  //    Enable horizontal and vertical margining
   {HWIO_OFFS(PCIE4_PCS_COM_PCS_TX_RX_CONFIG1),    0x04},  //    "0x04: Si - set Pinf RTB depth to 5 for gen1/2 (evaluate per SOC)0x08: DV - set Pinf RTB depth to 7 for gen1/2 (for 5 deep wc delay)"
   {HWIO_OFFS(PCIE4_PCS_COM_PCS_TX_RX_CONFIG2),    0x02},  //    Set Pinf RTB depth to 7 for gen3 (evaluate per SOC)
   {HWIO_OFFS(PCIE4_PCS_PCIE_PCS_TX_RX_CONFIG),    0xC0},  //    Set Pinf RTB depth to 7 for gen4 (evaluate per SOC)
   {HWIO_OFFS(PCIE4_PCS_PCIE_POWER_STATE_CONFIG2),    0x1D},  //    Keep PLL/EP clock on in P2 until CLKREQ# goes high; allow CLKREQ# to go high in P2.
   {HWIO_OFFS(PCIE4_PCS_PCIE_RX_MARGINING_CONFIG5),    0x0F},  //    Adjust aux offset to center eye
   {HWIO_OFFS(PCIE4_PCS_PCIE_G3_FOM_EQ_CONFIG5),    0xF2},  //    Adjust aux offset to center eye
   {HWIO_OFFS(PCIE4_PCS_PCIE_G4_FOM_EQ_CONFIG5),    0xF2},  //    Adjust aux offset to center eye

   // 0x00 : 2-Lane mode,(default value - write not needed); 
   // 0x01: 1-Lane mode, Lane 1 disabled
#ifdef USE_SINGLE_LANE_DISABLE_UPPER_LANE
   {HWIO_OFFS(PCIE4_PCS_LANE1_INSIG_SW_CTRL2),    0x01},
   {HWIO_OFFS(PCIE4_PCS_LANE1_INSIG_MX_CTRL2),    0x01},
#endif

   // 0x00: Link partner Tx Preset adjusted during RxEq training (default value - write not needed); 
   // 0x50: Link partner Tx Preset fixed (not adjusted during RxEq training)"
   {HWIO_OFFS(PCIE4_PCS_LANE0_OUTSIG_MX_CTRL1),    0x00},
   {HWIO_OFFS(PCIE4_PCS_LANE1_OUTSIG_MX_CTRL1),    0x00},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t kailua_port_1_phy_start_seq[] =
{
  {HWIO_OFFS(PCIE4_PCS_COM_SW_RESET),                    0x00},  //    Release SW_RESET
  {HWIO_OFFS(PCIE4_PCS_COM_START_CONTROL),               0x03},  //    Start PCS and Serdes power SMs
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t kailua_port_1_phy_poll_seq[] =
{
  {PCIE_REG_OP_POLL, HWIO_OFFS(PCIE4_PCS_COM_PCS_STATUS1), HWIO_PCIE4_PCS_COM_PCS_STATUS1_PHYSTATUS_BMSK, FALSE},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t kailua_pcie_1_post_phy_pwr_up_init_seq[] =
{
   // Non-PHY Settings :
   //   [write to both Gen3 CSR (RATE_SHADOW_SEL = 00b) and 
   //                  Gen4 CSR (RATE_SHADOW_SEL = 01b);
   //    write not needed if write value matches default value]:		
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_N_EVALS), 0x0D},
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA), 0x05},
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA), 0x05},
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PHASE23_EXIT_MODE), 0x00},
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PSET_REQ_VEC), 0x00},
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_FB_MODE), 0x00},
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_T_MIN_PHASE23), 0x01},

   // - Set the Downstream Port 8.0 GT/s Transmitter Preset and Upstream Port 8.0 GT/s Transmitter Preset bits in the RC's Lane Equalization Control Register
   //      to appropriate values for the channel (recommend 5 for short channel and 7 for long channel).		
   // - Set the Downstream Port 16.0 GT/s Transmitter Preset and Upstream Port 16.0 GT/s Transmitter Preset bits in the RC's 16.0 GT/s Lane Equalization Control Register
   //      to appropriate values for the channel (recommend 5 for short channel and 7 for long channel).		
#ifdef ENABLE_WHEN_GEN4_SUPPORTED
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_1_OFF, MARGINING_MAX_VOLTAGE_OFFSET),    0x24},
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_1_OFF, MARGINING_NUM_VOLTAGE_STEPS),    0x78},
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_1_OFF, MARGINING_MAX_TIMING_OFFSET),    0x32},
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_1_OFF, MARGINING_NUM_TIMING_STEPS),    0x10},
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_IND_ERROR_SAMPLER),    1},
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_REPORTING_METHOD),    1},
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_IND_LEFT_RIGHT_TIMING),    1},
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_IND_UP_DOWN_VOLTAGE),    1},
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_VOLTAGE_SUPPORTED),    1},
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_MAXLANES),    0x01},
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_RATE_TIMING), 0x3F},
    {PCIE_REG_OP_RMW, HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_RATE_VOLTAGE), 0x3F},
#endif

    {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t kailua_port_1_phy_de_init_seq[] =
{
  {HWIO_OFFS(PCIE4_PCS_COM_POWER_DOWN_CONTROL),             0x00},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t kailua_port_1_phy_de_init_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(kailua_port_1_phy_de_init_seq),
  {PcieSeq_Stop},
};

/*******************************************************************************
 *                       Loopback
 ******************************************************************************/

STATIC CONST pcie_reg_write_val_t kailua_port_1_phy_lpb_en_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                      0x0C},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                      0x0C},
   {HWIO_PCIE4_PCS_LANE0_TEST_CONTROL1_OFFS,            0x03},
   {HWIO_PCIE4_PCS_LANE1_TEST_CONTROL1_OFFS,            0x03},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t kailua_port_1_phy_lpb_dis_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                      0x00},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                      0x00},
   {HWIO_PCIE4_PCS_LANE0_TEST_CONTROL1_OFFS,            0x00},
   {HWIO_PCIE4_PCS_LANE1_TEST_CONTROL1_OFFS,            0x00},
   {HWIO_OFFS(PCIE4_PCS_COM_POWER_DOWN_CONTROL),        0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t kailua_port_1_phy_lpb_en_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(kailua_port_1_phy_lpb_en_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t kailua_port_1_phy_lpb_dis_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(kailua_port_1_phy_lpb_dis_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_loopback_cfg_t kailua_port_1_loopback_seq = 
{
   kailua_port_1_phy_lpb_en_cfg,
   kailua_port_1_phy_lpb_dis_cfg,
};

/*******************************************************************************
 *               Port 1 init Configuration
 ******************************************************************************/
STATIC CONST pcie_reg_init_cfg_t kailua_port_1_phy_init_cfg[] =
{
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(kailua_port_1_phy_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(kailua_port_1_phy_start_seq),

  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(kailua_port_1_phy_delay_seq),

  /* Check if the PHY PLL is locked */
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(kailua_port_1_phy_poll_seq),

  /* Perform post power up sequence */
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(kailua_port_1_x2_lane_seq),
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(kailua_pcie_1_post_phy_pwr_up_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(kailua_port_1_post_phy_pwr_up_init_seq),
     
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(kailua_port_1_set_link_speed_gen_4),
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(kailua_port_1_post_phy_pwr_up_dbi_init_seq),

  {PcieSeq_Stop},
};

/*******************************************************************************
 *               PCIe_1 Driver config definitions
 ******************************************************************************/
STATIC CONST pcie_drvr_cfg_t kailua_port_1_drvr_cfg =
{
  .port_clk_cfg           = &kailua_pcie_clk_rp1, 
  .port_gpio_cfg          = kailua_gpio_config_rp1,
  .iommu_cfg              = "PCIE1",
  .pmic_cfg               = &kailua_port_1_pmic_cfg, 
};

/*******************************************************************************
 *               PCIe_1 config definitions
 ******************************************************************************/
const pcie_port_config_t kailua_port_1_cfg[] =
{
   {
      .hw_rp_index            = 1,
      .driver_config          = &kailua_port_1_drvr_cfg,
      .port_mem_bases         = kailua_port_1_mem_region,
      .port_phy_init_cfg      = kailua_port_1_phy_init_cfg,
      .port_phy_deinit_cfg    = kailua_port_1_phy_de_init_cfg,
      .loopback_cfg           = &kailua_port_1_loopback_seq,
      .perst_pin              = KAILUA_RC_1_GPIO_PCIE_RESET,
      .port_attributes        = aspm_l1_ena_l0s_ena,
   },
};

const uint8_t kailua_port_1_cfg_len = ARRAY_LENGTH(kailua_port_1_cfg);
