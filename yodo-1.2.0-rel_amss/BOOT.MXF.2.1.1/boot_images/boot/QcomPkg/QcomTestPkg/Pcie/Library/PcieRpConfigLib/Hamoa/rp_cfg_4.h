#ifndef __PCIE_TARGET_PORT_4_CONFIG_H__
#define __PCIE_TARGET_PORT_4_CONFIG_H__
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

/*******************************************************************************
 *    Register region map
 ******************************************************************************/
static const mem_region_t port_4_mem_region[max_mem_reg] =
{
  /**< axi_reg: DBI register space */
  {.pa=PCIE_4PCIE_WRAPPER_AXI_G3X1_AUTO_BASE, .sz=PCIE_4PCIE_WRAPPER_AXI_G3X1_AUTO_BASE_SIZE},

  /**< ahb_reg: PARF register space */
  {.pa=PCIE4_CFGPCIE_WRAPPER_AHB_W_PHY_G3X1_AUTO_BASE, .sz=PCIE4_CFGPCIE_WRAPPER_AHB_W_PHY_G3X1_AUTO_BASE_SIZE},

  /**< tcsr_reg: Access TCSR register space */
  {.pa=CORE_TOP_CSR_BASE, .sz=CORE_TOP_CSR_BASE_SIZE},

};

/*******************************************************************************
 *   ICB bandwidth request settings
 ******************************************************************************/
STATIC CONST ICBArb_RequestType pcie_4_icb_request[] =
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

STATIC CONST ICBArb_MasterSlaveType pcie_4_icb_mstr_slv_lst[] =
{
  {
    .eMaster = ICBID_MASTER_PCIE_4,
    .eSlave = ICBID_SLAVE_EBI1
  }
};

STATIC pcieIcbClkBW_t pcie_4_icb_bw[] =
{
  {
    .npa_client_name = "pcie_4",
    .ms_list = pcie_4_icb_mstr_slv_lst,
    .ms_size = sizeof(pcie_4_icb_mstr_slv_lst),
    .req_list = pcie_4_icb_request,
    .req_size = sizeof(pcie_4_icb_request)
  }
};

/*******************************************************************************
 *              PCIe port clk related settings
 ******************************************************************************/
STATIC CONST char * pcie_reset_clks_rp4[] =
{
  "gcc_pcie_4_aux_clk",
  NULL
};

STATIC CONST char * pcie_gcc_clks_rp4[] =
{
  "gcc_pcie_4_pipe_clk",
  "gcc_pcie_4_pipediv2_clk",
  "gcc_aggre_noc_pcie_4_axi_clk",
  "gcc_cnoc_pcie4_qx_clk",
  "gcc_pcie_4_aux_clk",
  "gcc_pcie_4_slv_axi_clk",
  "gcc_pcie_4_slv_q2a_axi_clk",
  "gcc_pcie_4_mstr_axi_clk",
  "gcc_pcie_4_cfg_ahb_clk",
  "gcc_pcie4_phy_rchng_clk",
  "gcc_pcie_4_clkref_en",
  NULL
};

STATIC CONST pcie_clk_mux_cfg_t pcie_4_clk_mux = 
{
   .clk_name = "gcc_pcie_4_pipe_clk",
   .en_mux_val = 0,
   .dis_mux_val = 2,
};

STATIC CONST clk_freq_cfg_t pcie_4_clk_settings[] =
{
  {.freq = 19200000,  .name = "gcc_pcie_4_aux_clk"},
  {.freq = 100000000, .name = "gcc_pcie4_phy_rchng_clk"},
  {.freq = 0, .name = NULL}
};

STATIC CONST pcie_clocks_cfg_t pcie_clk_rp4 =
{
   .clk_pwr    = "gcc_pcie_4_gdsc",
   .core_clks  = pcie_gcc_clks_rp4,
   .clk_reset  = pcie_reset_clks_rp4,
   .clk_mux    = &pcie_4_clk_mux,
   .clk_freq   = pcie_4_clk_settings,
   .icb_bw     = pcie_4_icb_bw,
};

/*******************************************************************************
 *              PCIe port GPIO settings
 ******************************************************************************/
#define RC_4_GPIO_PCIE_RESET      141
#define RC_4_GPIO_CLK_REQ         140
#define RC_4_GPIO_PCIE_WAKE       139

STATIC CONST pcie_gpio_cfg_t gpio_config_rp4[] =
{
  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = RC_4_GPIO_CLK_REQ,
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
    .tlmm.gpio_num       = RC_4_GPIO_PCIE_RESET,
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
    .tlmm.gpio_num       = RC_4_GPIO_PCIE_WAKE,
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
 *                           PORT 4 Phy
 *
 *******************************************************************************/
STATIC CONST pcie_reg_write_val_t port_4_phy_init_seq[] =
{
  {HWIO_OFFS(PCIE_PARF_DEVICE_TYPE),                                 0x04},

  {HWIO_OFFS(PCIE_BPCS_COM_POWER_DOWN_CONTROL),                      0x03},  // Release powerdown mode and allow endpoint refclk drive

  {HWIO_OFFS(PCIE_BQSERDES_PLL_SYSCLK_EN_SEL),                       0x08},  // 0x04: select internal diff cml clock inputs; 0x08: select SE cmos clock input

  {HWIO_OFFS(PCIE_BQSERDES_PLL_CLK_SELECT),                          0x34},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_CORECLK_DIV_MODE1),                   0x08},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_PLL_IVCO),                            0x0F},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_LOCK_CMP_EN),                         0x42},  // PLL lock count = 512
  {HWIO_OFFS(PCIE_BQSERDES_PLL_VCO_TUNE1_MODE0),                     0x24},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_VCO_TUNE2_MODE1),                     0x03},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_VCO_TUNE1_MODE1),                     0xB4},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_VCO_TUNE_MAP),                        0x02},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_BIN_VCOCAL_HSCLK_SEL),                0x11},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_DEC_START_MODE0),                     0x82},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START3_MODE0),               0x03},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START2_MODE0),               0x55},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START1_MODE0),               0x55},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_LOCK_CMP2_MODE0),                     0x1A},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_LOCK_CMP1_MODE0),                     0x0A},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_DEC_START_MODE1),                     0x68},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START3_MODE1),               0x02},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START2_MODE1),               0xAA},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_DIV_FRAC_START1_MODE1),               0xAB},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_LOCK_CMP2_MODE1),                     0x34},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_LOCK_CMP1_MODE1),                     0x14},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_HSCLK_SEL),                           0x01},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_CP_CTRL_MODE0),                       0x06},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_PLL_RCTRL_MODE0),                     0x16},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_PLL_CCTRL_MODE0),                     0x36},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_CP_CTRL_MODE1),                       0x06},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_PLL_RCTRL_MODE1),                     0x16},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_PLL_CCTRL_MODE1),                     0x36},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0),          0x1E},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0),          0xB9},  // Downspread SSC disabled; 0xCA: when Downspread SSC enabled
  {HWIO_OFFS(PCIE_BQSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1),          0x18},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1),          0x94},  // Downspread SSC disabled; 0xA2: when Downspread SSC enabled
  {HWIO_OFFS(PCIE_BQSERDES_PLL_SYSCLK_BUF_ENABLE),                   0x07},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_EN_CENTER),                       0x00},  // Downspread SSC disabled (default, so no write needed); 0x01: Downspread SSC enabled
  {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_PER1),                            0x31},  // Set SSC frequency to 31.5KHz
  {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_PER2),                            0x01},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_STEP_SIZE1_MODE0),                0xDE},  // Set SSC step size for Gen1/2 (4500ppm)
  {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_STEP_SIZE2_MODE0),                0x07},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_STEP_SIZE1_MODE1),                0x4C},  // Set SSC step size for Gen3 (4500 ppm)
  {HWIO_OFFS(PCIE_BQSERDES_PLL_SSC_STEP_SIZE2_MODE1),                0x06},
  {HWIO_OFFS(PCIE_BQSERDES_TX0_PI_QEC_CTRL),                         0x20},
  {HWIO_OFFS(PCIE_BQSERDES_TX0_LANE_MODE_1),                         0x75},
  {HWIO_OFFS(PCIE_BQSERDES_TX0_LANE_MODE_4),                         0x3F},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_00_LOW),                      0x7F},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_00_HIGH),                     0xFF},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_00_HIGH2),                    0xBF},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_00_HIGH3),                    0x3F},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_00_HIGH4),                    0xD8},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_01_LOW),                      0xDC},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_01_HIGH),                     0xDC},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_01_HIGH2),                    0x5C},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_01_HIGH3),                    0x34},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_01_HIGH4),                    0xA6},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_RX_MODE_10_HIGH3),                    0x34},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_VGA_CAL_CNTRL2),                      0x07},
  {HWIO_OFFS(PCIE_BQSERDES_TX0_RES_CODE_LANE_OFFSET_TX),             0x1D},
  {HWIO_OFFS(PCIE_BQSERDES_TX0_RES_CODE_LANE_OFFSET_RX),             0x0C},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_GM_CAL),                              0x00},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_UCDR_SB2_THRESH1),                    0x08},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_UCDR_SB2_THRESH2),                    0x08},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_UCDR_PI_CONTROLS),                    0xF0},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_DFE_CTLE_POST_CAL_OFFSET),            0x38},
  {HWIO_OFFS(PCIE_BQSERDES_RX0_TX_ADAPT_POST_THRESH),                0xF0},   // Adjust post curser adaptation
  {HWIO_OFFS(PCIE_BPCS_PCIE_OSC_DTCT_ACTIONS),                       0x00},
  {HWIO_OFFS(PCIE_BPCS_PCIE_INT_AUX_CLK_CONFIG1),                    0x00},   // Turn off int aux clock usage in Lahaina
  {HWIO_OFFS(PCIE_BPCS_PCIE_EQ_CONFIG2),                             0x0F},
  {HWIO_OFFS(PCIE_BQSERDES_PLL_CLK_ENABLE1),                         0x90},
  {HWIO_OFFS(PCIE_BPCS_PCIE_ENDPOINT_REFCLK_DRIVE),                  0xC1},
  {HWIO_OFFS(PCIE_BPCS_COM_RX_SIGDET_LVL),                           0x77},
  {HWIO_OFFS(PCIE_BPCS_COM_RATE_SLEW_CNTRL1),                        0x0B},
  {HWIO_OFFS(PCIE_BPCS_COM_REFGEN_REQ_CONFIG1),                      0x05},

  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_4_phy_start_seq[] =
{
  {HWIO_OFFS(PCIE_BPCS_COM_SW_RESET),                    0x00}, // Release software reset
  {HWIO_OFFS(PCIE_BPCS_COM_START_CONTROL),               0x03}, // Start PCS and Serdes power SMs
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t port_4_phy_poll_seq[] =
{
  {PCIE_REG_OP_POLL, HWIO_OFFS(PCIE_BPCS_COM_PCS_STATUS1), HWIO_PCIE_BPCS_COM_PCS_STATUS1_PHYSTATUS_BMSK, FALSE},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_4_phy_de_init_seq[] =
{
  {HWIO_OFFS(PCIE_BPCS_COM_POWER_DOWN_CONTROL),             0x00},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t port_4_phy_de_init_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(port_4_phy_de_init_seq),
  {PcieSeq_Stop},
};

/*******************************************************************************
 *                       Loopback
 ******************************************************************************/

STATIC CONST pcie_reg_write_val_t port_4_phy_lpb_en_seq[] =
{
   {HWIO_OFFS(PCIE_BQSERDES_TX0_LPB_EN),                      0x0C},
   {HWIO_OFFS(PCIE_BPCS_LANE0_PCS_LANE_TEST_CONTROL1),        0x03},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_4_phy_lpb_dis_seq[] =
{
   {HWIO_OFFS(PCIE_BQSERDES_TX0_LPB_EN),                      0x00},
   {HWIO_OFFS(PCIE_BPCS_LANE0_PCS_LANE_TEST_CONTROL1),        0x00},
   {HWIO_OFFS(PCIE_BPCS_COM_POWER_DOWN_CONTROL),              0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t port_4_phy_lpb_en_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(port_4_phy_lpb_en_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t port_4_phy_lpb_dis_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(port_4_phy_lpb_dis_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_loopback_cfg_t port_4_loopback_seq = 
{
   port_4_phy_lpb_en_cfg,
   port_4_phy_lpb_dis_cfg,
};

/*******************************************************************************
 * Register set reset sequences
 ******************************************************************************/
static const pcie_reg_op_t port_4_reg_reset_seq[] = 
{
  /* Register Base, Operation, Offset, Mask & Value */
  {PCIE_REG_OP_WRITE, GCC_PCIE_4_BCR_OFF,       0x00,  0x01 },
  {PCIE_REG_OP_DELAY, 0, 0, 1 },
  {PCIE_REG_OP_WRITE, GCC_PCIE_4_BCR_OFF,       0x00,  0x00 },

  {PCIE_REG_OP_WRITE, GCC_PCIE_4_PHY_BCR_OFF,   0x00,  0x01 },
  {PCIE_REG_OP_DELAY, 0, 0, 1 },
  {PCIE_REG_OP_WRITE, GCC_PCIE_4_PHY_BCR_OFF,   0x00,  0x00 },

  {PCIE_REG_OP_STOP},
};

#endif   /* __PCIE_TARGET_PORT_4_CONFIG_H__ */
