#ifndef __NETRANI_ROOT_PORT_0_CONFIG_H__
#define __NETRANI_ROOT_PORT_0_CONFIG_H__
/*
 *  PCIe root port target config
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   03/08/22   Ap      Updated settings for netrani
   12/07/21   Ps      Created New

*/
/*============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
============================================================================*/

/*******************************************************************************
 *    Core Config:  Gen 3 x1, Hw offset 0
 ******************************************************************************/
/*******************************************************************************
 *    PMIC Power settings
 ******************************************************************************/
#define PMIC_NPA_CLIENT_NODE_PCIE0 "/pmic/client/pcie0" 
static const pcie_pmic_config_t netrani_port_0_pmic_cfg = 
{
  .node_id = PMIC_NPA_CLIENT_NODE_PCIE0,
};

/*******************************************************************************
 *    Register region map
 ******************************************************************************/
static const mem_region_t netrani_port_0_mem_region[max_mem_reg] =
{
  /* axi_reg: DBI register space */
  {.pa=PCIE_GEN3X1_SPACE_BASE, .sz=PCIE_GEN3X1_SPACE_SIZE},

  /* ahb_reg: PARF register space */
  {.pa=PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X1_EDMA_BASE, .sz=PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X1_EDMA_SIZE},

  /* tcsr_reg: Access TCSR register space */
//  {.pa=CORE_TOP_CSR_BASE, .sz=CORE_TOP_CSR_BASE_SIZE},

  /* TODO: SOD gcc_reg: Access GCC register space */
//  {.pa=CLK_CTL_BASE, .sz=CLK_CTL_BASE_SIZE},

  /* tunnel_router_reg: No tunneling on this port */
  {.pa=0, .sz=0},
};

/*******************************************************************************
 *   ICB bandwidth request settings
 ******************************************************************************/
STATIC CONST ICBArb_RequestType netrani_pcie_0_icb_request[] =
{
  {
    .arbType = ICBARB_REQUEST_TYPE_3,
    .arbData.type3 =
    {
      .uIb = ((400ULL) << 20), /* Instantaneous bandwidth in Bytes/second */
      .uAb = ((400ULL) << 20), /* Arbitrated bandwidth in Bytes/second */
      .uLatencyNs = 0          /* Latency requirement in nanoseconds */
    }
  }
};

STATIC CONST ICBArb_MasterSlaveType netrani_pcie_0_icb_mstr_slv_lst[] =
{
  {
    .eMaster = ICBID_MASTER_PCIE_0,
    .eSlave = ICBID_SLAVE_EBI1
  }
};

STATIC pcieIcbClkBW_t netrani_pcie_0_icb_bw[] =
{
  {
    .npa_client_name = "pcie_0",
    .ms_list = netrani_pcie_0_icb_mstr_slv_lst,
    .ms_size = sizeof(netrani_pcie_0_icb_mstr_slv_lst),
    .req_list = netrani_pcie_0_icb_request,
    .req_size = sizeof(netrani_pcie_0_icb_request)
  }
};

/*******************************************************************************
 *              PCIe port clk related settings
 ******************************************************************************/
STATIC CONST char * netrani_pcie_reset_clks_rp0[] =
{
  "gcc_pcie_0_aux_clk",
  NULL
};

STATIC CONST char * netrani_pcie_gcc_clks_rp0[] =
{
  "gcc_pcie_0_cfg_ahb_clk",
  "gcc_pcie_0_clkref_en",
  "gcc_pcie_0_pipe_clk",
  "gcc_pcie_0_aux_clk",
  "gcc_pcie_0_pipe_div2_clk",
  "gcc_aggre_noc_pcie_0_axi_clk",
  "gcc_pcie_0_slv_q2a_axi_clk",
  "gcc_pcie_0_mstr_axi_clk",
  "gcc_pcie_0_slv_axi_clk",
  "gcc_pcie_0_phy_rchng_clk",
  NULL
};

CONST pcie_clk_mux_cfg_t netrani_pcie_0_clk_mux = 
{
  .clk_name = "gcc_pcie_0_pipe_clk",
  .en_mux_val = 0,
  .dis_mux_val = 2,
};

CONST clk_freq_cfg_t netrani_pcie_0_clk_settings[] =
{
  {.freq = 19200000,  .name = "gcc_pcie_0_aux_clk"},
  {.freq = 100000000, .name = "gcc_pcie_0_phy_rchng_clk"},
  {.freq = 0, .name = NULL}
};

STATIC CONST pcie_clocks_cfg_t netrani_pcie_clk_rp0 =
{
  .clk_pwr    = "gcc_pcie_0_gdsc",
  .core_clks  = netrani_pcie_gcc_clks_rp0,
  .clk_reset  = netrani_pcie_reset_clks_rp0,
  .clk_mux    = &netrani_pcie_0_clk_mux,
  .clk_freq   = netrani_pcie_0_clk_settings,
  .icb_bw     = netrani_pcie_0_icb_bw,
};

/*******************************************************************************
 *              PCIe port GPIO settings
 ******************************************************************************/
#define netrani_RC_0_GPIO_PCIE_RESET      33
#define netrani_RC_0_GPIO_CLK_REQ         113
#define netrani_RC_0_GPIO_PCIE_WAKE       32

STATIC CONST pcie_gpio_cfg_t netrani_gpio_config_rp0[] =
{
  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = netrani_RC_0_GPIO_CLK_REQ,
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
    .tlmm.gpio_num       = netrani_RC_0_GPIO_PCIE_RESET,
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
    .tlmm.gpio_num       = netrani_RC_0_GPIO_PCIE_WAKE,
    .tlmm.func_sel       = 0,
    .tlmm.direction      = GPIO_INPUT,
    .tlmm.pull           = GPIO_PULL_UP,
    .tlmm.drive_strength = GPIO_2MA,
    .tlmm.value          = GPIO_LOW_VALUE
   }
  },

  { .cfg_type = NONE, { .delay_us = NONE } }
};

/*******************************************************************************
 *
 *                           PORT 0 Phy
 *
 *******************************************************************************/
STATIC CONST pcie_reg_write_val_t netrani_port_0_phy_init_seq[] =
{
  {HWIO_OFFS(PCIE_PARF_DEVICE_TYPE),                        0x04},
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_POWER_DOWN_CONTROL),         0x03},  //    Release powerdown mode and allow endpoint refclk drive        
  {HWIO_OFFS(QSERDES_COM_SYSCLK_EN_SEL),                    0x08},  //    "0x04: select internal diff cml clock inputs; 0x08: select SE cmos clock input"
  {HWIO_OFFS(QSERDES_COM_CLK_SELECT),                       0x34},
  {HWIO_OFFS(QSERDES_COM_CORECLK_DIV_MODE1),                0x08},
  {HWIO_OFFS(QSERDES_COM_PLL_IVCO),                         0x0F},
  {HWIO_OFFS(QSERDES_COM_LOCK_CMP_EN),                      0x42},  //    PLL lock count = 512
  {HWIO_OFFS(QSERDES_COM_VCO_TUNE1_MODE0),                  0x24},
  {HWIO_OFFS(QSERDES_COM_VCO_TUNE2_MODE1),                  0x03},
  {HWIO_OFFS(QSERDES_COM_VCO_TUNE1_MODE1),                  0xB4},
  {HWIO_OFFS(QSERDES_COM_VCO_TUNE_MAP),                     0x02},
  {HWIO_OFFS(QSERDES_COM_BIN_VCOCAL_HSCLK_SEL),             0x11},
  {HWIO_OFFS(QSERDES_COM_DEC_START_MODE0),                  0x82},
  {HWIO_OFFS(QSERDES_COM_DIV_FRAC_START3_MODE0),            0x03},
  {HWIO_OFFS(QSERDES_COM_DIV_FRAC_START2_MODE0),            0x55},
  {HWIO_OFFS(QSERDES_COM_DIV_FRAC_START1_MODE0),            0x55},
  {HWIO_OFFS(QSERDES_COM_LOCK_CMP2_MODE0),                  0x1A},
  {HWIO_OFFS(QSERDES_COM_LOCK_CMP1_MODE0),                  0x0A},
  {HWIO_OFFS(QSERDES_COM_DEC_START_MODE1),                  0x68},
  {HWIO_OFFS(QSERDES_COM_DIV_FRAC_START3_MODE1),            0x02},
  {HWIO_OFFS(QSERDES_COM_DIV_FRAC_START2_MODE1),            0xAA},
  {HWIO_OFFS(QSERDES_COM_DIV_FRAC_START1_MODE1),            0xAB},
  {HWIO_OFFS(QSERDES_COM_LOCK_CMP2_MODE1),                  0x34},
  {HWIO_OFFS(QSERDES_COM_LOCK_CMP1_MODE1),                  0x14},
  {HWIO_OFFS(QSERDES_COM_HSCLK_SEL),                        0x01},
  {HWIO_OFFS(QSERDES_COM_CP_CTRL_MODE0),                    0x06},
  {HWIO_OFFS(QSERDES_COM_PLL_RCTRL_MODE0),                  0x16},
  {HWIO_OFFS(QSERDES_COM_PLL_CCTRL_MODE0),                  0x36},
  {HWIO_OFFS(QSERDES_COM_CP_CTRL_MODE1),                    0x06},
  {HWIO_OFFS(QSERDES_COM_PLL_RCTRL_MODE1),                  0x16},
  {HWIO_OFFS(QSERDES_COM_PLL_CCTRL_MODE1),                  0x36},
  {HWIO_OFFS(QSERDES_COM_BIN_VCOCAL_CMP_CODE2_MODE0),       0x1E},
  {HWIO_OFFS(QSERDES_COM_BIN_VCOCAL_CMP_CODE1_MODE0),       0xca}, // 0xB9},  //    "0xB9:when Downspread SSC disabled; 0xCA: when Downspread SSC enabled"
  {HWIO_OFFS(QSERDES_COM_BIN_VCOCAL_CMP_CODE2_MODE1),       0x18},
  {HWIO_OFFS(QSERDES_COM_BIN_VCOCAL_CMP_CODE1_MODE1),       0xa2},// 0x94},  //    "0x94:when Downspread SSC disabled; 0xA2: when Downspread SSC enabled"
  {HWIO_OFFS(QSERDES_COM_SYSCLK_BUF_ENABLE),                0x07},
  {HWIO_OFFS(QSERDES_COM_SSC_EN_CENTER),                    0x01},  //    "0x00: Downspread SSC disabled (default, so no write needed); 0x01: Downspread SSC enabled"
  {HWIO_OFFS(QSERDES_COM_SSC_PER1),                         0x31},  //    Set SSC frequency to 31.5KHz
  {HWIO_OFFS(QSERDES_COM_SSC_PER2),                         0x01},
  {HWIO_OFFS(QSERDES_COM_SSC_STEP_SIZE1_MODE0),             0xDE},  //    Set SSC step size for Gen1/2 (4500ppm)
  {HWIO_OFFS(QSERDES_COM_SSC_STEP_SIZE2_MODE0),             0x07},
  {HWIO_OFFS(QSERDES_COM_SSC_STEP_SIZE1_MODE1),             0x4C},  //    Set SSC step size for Gen3 (4500 ppm)
  {HWIO_OFFS(QSERDES_COM_SSC_STEP_SIZE2_MODE1),             0x06},
  {HWIO_OFFS(QSERDES_TX_PI_QEC_CTRL),                       0x20},
  {HWIO_OFFS(QSERDES_TX_LANE_MODE_1),                       0x75},
  {HWIO_OFFS(QSERDES_TX_LANE_MODE_4),                       0x3F},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_00_LOW),                    0x7F},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_00_HIGH),                   0xFF},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_00_HIGH2),                  0xBF},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_00_HIGH3),                  0x3F},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_00_HIGH4),                  0xD8},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_01_LOW),                    0xDC},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_01_HIGH),                   0xDC},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_01_HIGH2),                  0x5C},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_01_HIGH3),                  0x34},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_01_HIGH4),                  0xA6},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_10_HIGH3),                  0x34},
  {HWIO_OFFS(QSERDES_RX_RX_MODE_10_HIGH4),                  0x38},
  {HWIO_OFFS(QSERDES_RX_VGA_CAL_CNTRL2),                    0x0F},
  {HWIO_OFFS(QSERDES_TX_RES_CODE_LANE_OFFSET_TX),           0x12},
  {HWIO_OFFS(QSERDES_TX_RES_CODE_LANE_OFFSET_RX),           0x01},
  {HWIO_OFFS(QSERDES_RX_GM_CAL),                            0x00},
  {HWIO_OFFS(QSERDES_RX_UCDR_SB2_THRESH1),                  0x08},
  {HWIO_OFFS(QSERDES_RX_UCDR_SB2_THRESH2),                  0x08},
  {HWIO_OFFS(QSERDES_RX_UCDR_PI_CONTROLS),                  0xF0},
  {HWIO_OFFS(QSERDES_RX_DFE_CTLE_POST_CAL_OFFSET),          0x38},
  {HWIO_OFFS(QSERDES_RX_TX_ADAPT_POST_THRESH),              0xF0},  //    Adjust post curser adaptation
  {HWIO_OFFS(QSERDES_RX_RX_EQU_ADAPTOR_CNTRL4),             0x07},
  {HWIO_OFFS(QSERDES_RX_UCDR_FO_GAIN),                      0x09},
  {HWIO_OFFS(QSERDES_RX_UCDR_SO_GAIN),                      0x05},
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_PCIE_OSC_DTCT_ACTIONS),      0x00},
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_PCIE_INT_AUX_CLK_CONFIG1),   0x00},  //    Turn off int aux clock usage in Lahaina
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_PCIE_EQ_CONFIG2),            0x0F},
  {HWIO_OFFS(QSERDES_COM_CLK_ENABLE1),                      0x90},
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_PCIE_ENDPOINT_REFCLK_DRIVE), 0xC1},
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_RX_SIGDET_LVL),              0x77},
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_RATE_SLEW_CNTRL1),           0x0B},
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_REFGEN_REQ_CONFIG1),         0x05},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t netrani_port_0_phy_start_seq[] =
{
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_SW_RESET),                  0x00},  //    Release software reset
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_START_CONTROL),             0x03},  //    Start PCS and Serdes power SMs
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t netrani_port_0_phy_poll_seq[] =
{
  {PCIE_REG_OP_POLL, HWIO_OFFS(PCIE_USB3_UNI_PCS_PCS_STATUS1), HWIO_PCIE_USB3_UNI_PCS_PCS_STATUS1_PHYSTATUS_BMSK, FALSE},
  {PCIE_REG_OP_STOP},
};


STATIC CONST pcie_reg_op_t netrani_pcie_0_post_phy_pwr_up_init_seq[] =
{
  {HWIO_REG_MASK(PCIE_DBIGEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_N_EVALS),               0x0D},
  {HWIO_REG_MASK(PCIE_DBIGEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA),  0x05},
  {HWIO_REG_MASK(PCIE_DBIGEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA), 0x05},
  {HWIO_REG_MASK(PCIE_DBIGEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_T_MIN_PHASE23),         0x00},
  /* TODO: Check if the following is the right ones to reference for this setting
  *  GEN3_RELATED.EQ_PHASE_2_3 or
  *  GEN3_EQ_CONTROL.GEN3_EQ_PHASE23_EXIT_MODE */
//   {HWIO_REG_MASK(PCIE_DBI_GEN3_RELATED_OFF, GEN3_EQ_PHASE23_EXIT_MODE), 0x00},    // 0x890
  {HWIO_REG_MASK(PCIE_DBIGEN3_EQ_CONTROL_OFF, GEN3_EQ_PHASE23_EXIT_MODE),                     0x00},
  {HWIO_REG_MASK(PCIE_DBIGEN3_EQ_CONTROL_OFF, GEN3_EQ_PSET_REQ_VEC),                          0x00},
};

STATIC CONST pcie_reg_write_val_t netrani_port_0_phy_de_init_seq[] =
{
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_POWER_DOWN_CONTROL),    0x00},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t netrani_port_0_phy_de_init_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(netrani_port_0_phy_de_init_seq),
  {PcieSeq_Stop},
};

/*******************************************************************************
 *                       Loopback
 ******************************************************************************/

STATIC CONST pcie_reg_write_val_t netrani_port_0_phy_lpb_en_seq[] =
{
  {HWIO_OFFS(QSERDES_TX_LPB_EN),                      0x0C},
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_LN_TEST_CONTROL1),     0x03},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t netrani_port_0_phy_lpb_dis_seq[] =
{
  {HWIO_OFFS(QSERDES_TX_LPB_EN),                      0x00},
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_LN_TEST_CONTROL1),     0x00},
  {HWIO_OFFS(PCIE_USB3_UNI_PCS_POWER_DOWN_CONTROL),   0x00},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t netrani_port_0_phy_lpb_en_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(netrani_port_0_phy_lpb_en_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t netrani_port_0_phy_lpb_dis_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(netrani_port_0_phy_lpb_dis_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_loopback_cfg_t netrani_port_0_loopback_seq = 
{
  netrani_port_0_phy_lpb_en_cfg,
  netrani_port_0_phy_lpb_dis_cfg,
};

/*******************************************************************************
 * Register set reset sequences
 ******************************************************************************/
static const pcie_reg_op_t netrani_port_0_reg_reset_seq[] = 
{
#if 0
  /* Register Base, Operation, Offset, Mask & Value */
  {PCIE_REG_OP_WRITE, GCC_PCIE_0_BCR_OFF,       0x00,  0x01 },
  {PCIE_REG_OP_DELAY, 0, 0, 1 },
  {PCIE_REG_OP_WRITE, GCC_PCIE_0_BCR_OFF,       0x00,  0x00 },

  {PCIE_REG_OP_WRITE, GCC_PCIE_0_PHY_BCR_OFF,   0x00,  0x01 },
  {PCIE_REG_OP_DELAY, 0, 0, 1 },
  {PCIE_REG_OP_WRITE, GCC_PCIE_0_PHY_BCR_OFF,   0x00,  0x00 },
#endif
  {PCIE_REG_OP_STOP},
};

#endif   /* __PCIE_TARGET_PORT_0_CONFIG_H__ */