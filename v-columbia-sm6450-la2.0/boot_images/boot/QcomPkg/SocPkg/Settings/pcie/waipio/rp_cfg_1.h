#ifndef __WAIPIO_ROOT_PORT_1_CONFIG_H__
#define __WAIPIO_ROOT_PORT_1_CONFIG_H__
/*
 *  PCIe root port target config
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   01/03/22   Ps      Changed the file location
   10/20/20   Yg      Created New

*/
/*============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
============================================================================*/

/*******************************************************************************
 *    Core Config:  Gen 4 x2, Hw offset 1
 ******************************************************************************/
/*******************************************************************************
 *    PMIC Power settings
 ******************************************************************************/

#define PMIC_NPA_CLIENT_NODE_PCIE1 "/pmic/client/pcie1" 
static const pcie_pmic_config_t waipio_port_1_pmic_cfg = 
{
   .node_id = PMIC_NPA_CLIENT_NODE_PCIE1,
};

/*******************************************************************************
 *    Register region map
 ******************************************************************************/
static mem_region_t waipio_port_1_mem_region[max_mem_reg] =
{
  /* axi_reg: DBI register space */
  {.pa=PCIE_GEN4X2_SPACE_BASE, .sz=PCIE_GEN4X2_SPACE_SIZE},

  /* ahb_reg: PARF register space */
  {.pa=PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_EDMA_BASE, .sz=PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_EDMA_SIZE},

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
STATIC CONST ICBArb_RequestType waipio_pcie_1_icb_request[] =
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

STATIC CONST ICBArb_MasterSlaveType waipio_pcie_1_icb_mstr_slv_lst[] =
{
  {
    .eMaster = ICBID_MASTER_PCIE_1,
    .eSlave = ICBID_SLAVE_EBI1
  }
};

STATIC pcieIcbClkBW_t waipio_pcie_1_icb_bw[] =
{
  {
    .npa_client_name = "pcie_1",
    .ms_list = waipio_pcie_1_icb_mstr_slv_lst,
    .ms_size = sizeof(waipio_pcie_1_icb_mstr_slv_lst),
    .req_list = waipio_pcie_1_icb_request,
    .req_size = sizeof(waipio_pcie_1_icb_request)
  }
};

/*******************************************************************************
 *              PCIe port clk related settings
 ******************************************************************************/
STATIC CONST char * waipio_pcie_reset_clks_rp1[] =
{
  "gcc_pcie_1_aux_clk",
  NULL
};

STATIC CONST char * waipio_pcie_gcc_clks_rp1[] =
{
//  "gcc_aggre_noc_pcie_south_sf_axi_clk",
  "gcc_pcie_1_cfg_ahb_clk",
  "gcc_pcie_1_clkref_en",
  "gcc_pcie_1_pipe_clk",
  "gcc_pcie_1_aux_clk",
  "gcc_pcie_1_phy_aux_clk",
  "gcc_aggre_noc_pcie_1_axi_clk",
  "gcc_pcie_1_slv_q2a_axi_clk",
  "gcc_pcie_1_mstr_axi_clk",
  "gcc_pcie_1_slv_axi_clk",
//  "gcc_pcie_1_phy_rchng_clk",
  NULL
};

CONST pcie_clk_mux_cfg_t waipio_pcie_1_clk_mux = 
{
   .clk_name = "gcc_pcie_1_pipe_clk",
   .en_mux_val = 0,
   .dis_mux_val = 2,
};

CONST clk_freq_cfg_t waipio_pcie_1_clk_settings[] =
{
  {.freq = 19200000,  .name = "gcc_pcie_1_aux_clk"},
  {.freq = 100000000, .name = "gcc_pcie_1_phy_rchng_clk"},
  {.freq = 0, .name = NULL}
};

STATIC CONST pcie_clocks_cfg_t waipio_pcie_clk_rp1 =
{
   .clk_pwr    = "gcc_pcie_1_gdsc",
   .core_clks  = waipio_pcie_gcc_clks_rp1,
   .clk_reset  = waipio_pcie_reset_clks_rp1,
   .clk_mux    = &waipio_pcie_1_clk_mux,
   .clk_freq   = waipio_pcie_1_clk_settings,
   .icb_bw     = waipio_pcie_1_icb_bw,
};

/*******************************************************************************
 *              PCIe port GPIO settings
 ******************************************************************************/
#define WAIPIO_RC_1_GPIO_PCIE_RESET      97
#define WAIPIO_RC_1_GPIO_CLK_REQ         98
#define WAIPIO_RC_1_GPIO_PCIE_WAKE       99

STATIC CONST pcie_gpio_cfg_t waipio_gpio_config_rp1[] =
{
  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = WAIPIO_RC_1_GPIO_CLK_REQ,
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
    .tlmm.gpio_num       = WAIPIO_RC_1_GPIO_PCIE_RESET,
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
    .tlmm.gpio_num       = WAIPIO_RC_1_GPIO_PCIE_WAKE,
    .tlmm.func_sel       = 0,
    .tlmm.direction      = GPIO_INPUT,
    .tlmm.pull           = GPIO_PULL_UP,
    .tlmm.drive_strength = GPIO_2MA,
    .tlmm.value          = GPIO_LOW_VALUE
   }
  },

  { .cfg_type = NONE, { .delay_us = NONE}}
};

/*******************************************************************************
 *
 *                           PORT 1 Phy
 *
 *******************************************************************************/
STATIC CONST pcie_reg_write_val_t waipio_port_1_phy_init_seq[] =
{
   {HWIO_OFFS(PCIE_PARF_DEVICE_TYPE),                                 0x04},

   {HWIO_OFFS(PCIE4_PCS_COM_POWER_DOWN_CONTROL),    0x03},
   {HWIO_OFFS(QSERDES_PLL_SSC_EN_CENTER),    0x00},         // SSC diabled
   {HWIO_OFFS(QSERDES_PLL_SSC_PER1),    0x31},
   {HWIO_OFFS(QSERDES_PLL_SSC_PER2),    0x01},
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE0),    0xde},
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE0),    0x07},
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE1),    0x97},
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE1),    0x0c},
   {HWIO_OFFS(QSERDES_PLL_BIAS_EN_CLKBUFLR_EN),    0x14},
   {HWIO_OFFS(QSERDES_PLL_CLK_ENABLE1),    0x90},
   {HWIO_OFFS(QSERDES_PLL_PLL_IVCO),    0x0f},
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE0),    0x06},
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE1),    0x06},
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE0),    0x16},
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE1),    0x16},
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE0),    0x36},
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE1),    0x36},
   {HWIO_OFFS(QSERDES_PLL_SYSCLK_EN_SEL),    0x08},  // "0x04: select internal diff cml clock inputs; 0x08: select SE cmos clock input"
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP_EN),    0x46},
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP_CFG),    0x04},
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE0),    0x0a},
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE0),    0x1a},
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE1),    0x14},
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE1),    0x34},
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE0),    0x82},
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE1),    0xd0},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE0),    0x55},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE0),    0x55},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE0),    0x03},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE1),    0x55},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE1),    0x55},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE1),    0x05},
   {HWIO_OFFS(QSERDES_PLL_VCO_TUNE_MAP),    0x02},
   {HWIO_OFFS(QSERDES_PLL_CLK_SELECT),    0x34},
   {HWIO_OFFS(QSERDES_PLL_HSCLK_SEL),    0x12},
   {HWIO_OFFS(QSERDES_PLL_HSCLK_HS_SWITCH_SEL),    0x00},
   {HWIO_OFFS(QSERDES_PLL_CORECLK_DIV_MODE0),    0x0A},
   {HWIO_OFFS(QSERDES_PLL_CORECLK_DIV_MODE1),    0x04},
   {HWIO_OFFS(QSERDES_PLL_CMN_MISC1),    0x88},
   {HWIO_OFFS(QSERDES_PLL_CORE_CLK_EN),    0x20},
   {HWIO_OFFS(QSERDES_PLL_CMN_CONFIG),    0x06},
   {HWIO_OFFS(QSERDES_PLL_CMN_MODE),    0x14},
   {HWIO_OFFS(QSERDES_PLL_VCO_DC_LEVEL_CTRL),    0x0F},
   {HWIO_OFFS(QSERDES_RX0_UCDR_PI_CONTROLS),    0x16},
   {HWIO_OFFS(QSERDES_RX0_DFE_CTLE_POST_CAL_OFFSET),    0x38},
   {HWIO_OFFS(QSERDES_RX1_UCDR_PI_CONTROLS),    0x16},
   {HWIO_OFFS(QSERDES_RX1_DFE_CTLE_POST_CAL_OFFSET),    0x38},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE_0_1_B1),    0xCC},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE_0_1_B2),    0x12},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE_0_1_B3),    0xCC},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE_0_1_B5),    0x4A},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE_0_1_B6),    0x29},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B0),    0xC5},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B1),    0xAD},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B2),    0xB6},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B3),    0xC0},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B4),    0x1F},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B5),    0xFB},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B6),    0x0F},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B0),    0xC7},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B1),    0xEF},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B2),    0xBF},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B3),    0xA0},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B4),    0x81},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B5),    0xDE},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B6),    0x7F},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE_0_1_B1),    0xCC},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE_0_1_B2),    0x12},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE_0_1_B3),    0xCC},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE_0_1_B5),    0x4A},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE_0_1_B6),    0x29},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B0),    0xC5},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B1),    0xAD},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B2),    0xB6},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B3),    0xC0},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B4),    0x1F},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B5),    0xFB},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B6),    0x0F},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B0),    0xC7},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B1),    0xEF},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B2),    0xBF},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B3),    0xA0},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B4),    0x81},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B5),    0xDE},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B6),    0x7F},
   {HWIO_OFFS(QSERDES_RX0_PHPRE_CTRL),    0x20},
   {HWIO_OFFS(QSERDES_RX0_AUX_DATA_THRESH_BIN_RATE_0_1),    0x3F},
   {HWIO_OFFS(QSERDES_RX0_AUX_DATA_THRESH_BIN_RATE_2_3),    0x37},
   {HWIO_OFFS(QSERDES_RX1_PHPRE_CTRL),    0x20},
   {HWIO_OFFS(QSERDES_RX1_AUX_DATA_THRESH_BIN_RATE_0_1),    0x3F},
   {HWIO_OFFS(QSERDES_RX1_AUX_DATA_THRESH_BIN_RATE_2_3),    0x37},
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_1),    0x05},
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_2),    0xF6},
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_1),    0x05},
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_2),    0xF6},
   {HWIO_OFFS(QSERDES_RX0_DFE_3),    0x05},
   {HWIO_OFFS(QSERDES_RX1_DFE_3),    0x05},
   {HWIO_OFFS(QSERDES_RX0_RX_MARG_COARSE_THRESH1_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX0_RX_MARG_COARSE_THRESH2_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX0_RX_MARG_COARSE_THRESH3_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX0_RX_MARG_COARSE_THRESH4_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX0_RX_MARG_COARSE_THRESH5_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX0_RX_MARG_COARSE_THRESH6_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX0_RX_MARG_COARSE_THRESH1_RATE210),    0x1F},
   {HWIO_OFFS(QSERDES_RX0_RX_MARG_COARSE_THRESH2_RATE210),    0x1F},
   {HWIO_OFFS(QSERDES_RX0_RX_MARG_COARSE_THRESH3_RATE210),    0x1F},
   {HWIO_OFFS(QSERDES_RX1_RX_MARG_COARSE_THRESH1_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX1_RX_MARG_COARSE_THRESH2_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX1_RX_MARG_COARSE_THRESH3_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX1_RX_MARG_COARSE_THRESH4_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX1_RX_MARG_COARSE_THRESH5_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX1_RX_MARG_COARSE_THRESH6_RATE3),    0x1F},
   {HWIO_OFFS(QSERDES_RX1_RX_MARG_COARSE_THRESH1_RATE210),    0x1F},
   {HWIO_OFFS(QSERDES_RX1_RX_MARG_COARSE_THRESH2_RATE210),    0x1F},
   {HWIO_OFFS(QSERDES_RX1_RX_MARG_COARSE_THRESH3_RATE210),    0x1F},
   {HWIO_OFFS(QSERDES_RX0_UCDR_FO_GAIN_RATE2),    0x0C},
   {HWIO_OFFS(QSERDES_RX1_UCDR_FO_GAIN_RATE2),    0x0C},
   {HWIO_OFFS(QSERDES_RX0_UCDR_FO_GAIN_RATE3),    0x0A},
   {HWIO_OFFS(QSERDES_RX1_UCDR_FO_GAIN_RATE3),    0x0A},
   {HWIO_OFFS(QSERDES_RX0_VGA_CAL_MAN_VAL),    0x0A},
   {HWIO_OFFS(QSERDES_RX1_VGA_CAL_MAN_VAL),    0x0A},
   {HWIO_OFFS(QSERDES_RX0_RX_EQU_ADAPTOR_CNTRL4),    0x0B},
   {HWIO_OFFS(QSERDES_RX1_RX_EQU_ADAPTOR_CNTRL4),    0x0B},
   {HWIO_OFFS(QSERDES_RX0_RX_IDAC_SAOFFSET),    0x10},
   {HWIO_OFFS(QSERDES_RX1_RX_IDAC_SAOFFSET),    0x10},
   {HWIO_OFFS(QSERDES_RX0_DFE_DAC_ENABLE1),    0x00},
   {HWIO_OFFS(QSERDES_RX1_DFE_DAC_ENABLE1),    0x00},
   {HWIO_OFFS(QSERDES_RX0_GM_CAL),    0x0F},
   {HWIO_OFFS(QSERDES_RX1_GM_CAL),    0x0F},
   {HWIO_OFFS(QSERDES_RX0_TX_ADAPT_POST_THRESH1),    0x00},
   {HWIO_OFFS(QSERDES_RX0_TX_ADAPT_POST_THRESH2),    0x1F},
   {HWIO_OFFS(QSERDES_RX1_TX_ADAPT_POST_THRESH1),    0x00},
   {HWIO_OFFS(QSERDES_RX1_TX_ADAPT_POST_THRESH2),    0x1F},
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_TX),    0x1A},
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_RX),    0x0C},
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_TX),    0x1A},
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_RX),    0x0C},
   {HWIO_OFFS(PCIE4_PCS_PCIE_ENDPOINT_REFCLK_DRIVE),    0xc1},
   {HWIO_OFFS(PCIE4_PCS_PCIE_OSC_DTCT_ACTIONS),    0x00},
   {HWIO_OFFS(PCIE4_PCS_COM_EQ_CONFIG4),    0x16},
   {HWIO_OFFS(PCIE4_PCS_COM_EQ_CONFIG5),    0x22},
   {HWIO_OFFS(PCIE4_PCS_PCIE_G4_EQ_CONFIG5),    0x02},
   {HWIO_OFFS(PCIE4_PCS_PCIE_EQ_CONFIG1),    0x16},
   {HWIO_OFFS(PCIE4_PCS_PCIE_RX_MARGINING_CONFIG3),    0x28},
   {HWIO_OFFS(PCIE4_PCS_COM_G3S2_PRE_GAIN),    0x2E},
   {HWIO_OFFS(PCIE4_PCS_PCIE_G4_PRE_GAIN),    0x2E},
   {HWIO_OFFS(PCIE4_PCS_COM_RX_SIGDET_LVL),   0x99},

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

STATIC CONST pcie_reg_write_val_t waipio_port_1_phy_start_seq[] =
{
  {HWIO_OFFS(PCIE4_PCS_COM_SW_RESET),                    0x00}, // Release software reset
  {HWIO_OFFS(PCIE4_PCS_COM_START_CONTROL),               0x03}, // Start PCS and Serdes power SMs
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t waipio_port_1_phy_poll_seq[] =
{
  {PCIE_REG_OP_POLL, HWIO_OFFS(PCIE4_PCS_COM_PCS_STATUS1), HWIO_PCIE4_PCS_COM_PCS_STATUS1_PHYSTATUS_BMSK, FALSE},
  {PCIE_REG_OP_STOP},
};


STATIC CONST pcie_reg_op_t waipio_pcie_1_post_phy_pwr_up_init_seq[] =
{
   // Non-PHY Settings :
   //   [write to both Gen3 CSR (RATE_SHADOW_SEL = 00b) and 
   //                  Gen4 CSR (RATE_SHADOW_SEL = 01b);
   //    write not needed if write value matches default value]:		
   {HWIO_REG_MASK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_N_EVALS), 0x0D},
   {HWIO_REG_MASK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA), 0x05},
   {HWIO_REG_MASK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA), 0x05},
   {HWIO_REG_MASK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PHASE23_EXIT_MODE), 0x00},
   {HWIO_REG_MASK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PSET_REQ_VEC), 0x00},
   {HWIO_REG_MASK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_FB_MODE), 0x00},
   {HWIO_REG_MASK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_T_MIN_PHASE23), 0x01},

   // - Set the Downstream Port 8.0 GT/s Transmitter Preset and Upstream Port 8.0 GT/s Transmitter Preset bits in the RC's Lane Equalization Control Register
   //      to appropriate values for the channel (recommend 5 for short channel and 7 for long channel).		
   // - Set the Downstream Port 16.0 GT/s Transmitter Preset and Upstream Port 16.0 GT/s Transmitter Preset bits in the RC's 16.0 GT/s Lane Equalization Control Register
   //      to appropriate values for the channel (recommend 5 for short channel and 7 for long channel).		
#ifdef ENABLE_WHEN_GEN4_SUPPORTED
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_1_OFF, MARGINING_MAX_VOLTAGE_OFFSET),    0x24},
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_1_OFF, MARGINING_NUM_VOLTAGE_STEPS),    0x78},
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_1_OFF, MARGINING_MAX_TIMING_OFFSET),    0x32},
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_1_OFF, MARGINING_NUM_TIMING_STEPS),    0x10},
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_IND_ERROR_SAMPLER),    1},
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_REPORTING_METHOD),    1},
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_IND_LEFT_RIGHT_TIMING),    1},
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_NUM_UP_DOWN_VOLTAGE),    0},
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_VOLTAGE_SUPPORTED),    1},
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_MAXLANES),    0x02},
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_RATE_TIMING), 0x3F},
    {HWIO_REG_MASK(GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_RATE_VOLTAGE), 0x3F},
#endif

    {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t waipio_port_1_phy_de_init_seq[] =
{
  {HWIO_OFFS(PCIE4_PCS_COM_POWER_DOWN_CONTROL),             0x00},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t waipio_port_1_phy_de_init_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(waipio_port_1_phy_de_init_seq),
  {PcieSeq_Stop},
};

/*******************************************************************************
 *                       Loopback
 ******************************************************************************/

STATIC CONST pcie_reg_write_val_t waipio_port_1_phy_lpb_en_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                      0x0C},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                      0x0C},
   {HWIO_PCIE4_PCS_LANE0_TEST_CONTROL1_OFFS,            0x03},
   {HWIO_PCIE4_PCS_LANE1_TEST_CONTROL1_OFFS,            0x03},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t waipio_port_1_phy_lpb_dis_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                      0x00},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                      0x00},
   {HWIO_PCIE4_PCS_LANE0_TEST_CONTROL1_OFFS,            0x00},
   {HWIO_PCIE4_PCS_LANE1_TEST_CONTROL1_OFFS,            0x00},
   {HWIO_OFFS(PCIE4_PCS_COM_POWER_DOWN_CONTROL),        0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t waipio_port_1_phy_lpb_en_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(waipio_port_1_phy_lpb_en_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t waipio_port_1_phy_lpb_dis_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(waipio_port_1_phy_lpb_dis_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_loopback_cfg_t waipio_port_1_loopback_seq = 
{
   waipio_port_1_phy_lpb_en_cfg,
   waipio_port_1_phy_lpb_dis_cfg,
};

/*******************************************************************************
 * Register set reset sequences
 ******************************************************************************/
static const pcie_reg_op_t waipio_port_1_reg_reset_seq[] = 
{
#if 0
  /* Register Base, Operation, Offset, Mask & Value */
  { PCIE_REG_OP_WRITE, GCC_PCIE_1_BCR_OFF,       0x00,  0x01 },
  { PCIE_REG_OP_DELAY, 0, 0, 1 },
  { PCIE_REG_OP_WRITE, GCC_PCIE_1_BCR_OFF,       0x00,  0x00 },

  { PCIE_REG_OP_WRITE, GCC_PCIE_1_PHY_BCR_OFF,   0x00,  0x01 },
  { PCIE_REG_OP_DELAY, 0, 0, 1 },
  { PCIE_REG_OP_WRITE, GCC_PCIE_1_PHY_BCR_OFF,   0x00,  0x00 },
#endif

  { PCIE_REG_OP_STOP, 0, 0, 0 },
};

#endif   /* __PCIE_TARGET_PORT_1_CONFIG_H__ */
