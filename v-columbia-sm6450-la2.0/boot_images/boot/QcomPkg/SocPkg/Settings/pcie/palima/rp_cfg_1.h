#ifndef __PALIMA_ROOT_PORT_1_CONFIG_H__
#define __PALIMA_ROOT_PORT_1_CONFIG_H__
/*
 *  PCIe root port target config
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   03/07/22   Ps      Palima port 1 specific config changes
   01/03/22   Ps      Changed file location
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
static const pcie_pmic_config_t palima_port_1_pmic_cfg = 
{
   .node_id = PMIC_NPA_CLIENT_NODE_PCIE1,
};

/*******************************************************************************
 *    Register region map
 ******************************************************************************/
static mem_region_t palima_port_1_mem_region[max_mem_reg] =
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
STATIC CONST ICBArb_RequestType palima_pcie_1_icb_request[] =
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

STATIC CONST ICBArb_MasterSlaveType palima_pcie_1_icb_mstr_slv_lst[] =
{
  {
    .eMaster = ICBID_MASTER_PCIE_1,
    .eSlave = ICBID_SLAVE_EBI1
  }
};

STATIC pcieIcbClkBW_t palima_pcie_1_icb_bw[] =
{
  {
    .npa_client_name = "pcie_1",
    .ms_list = palima_pcie_1_icb_mstr_slv_lst,
    .ms_size = sizeof(palima_pcie_1_icb_mstr_slv_lst),
    .req_list = palima_pcie_1_icb_request,
    .req_size = sizeof(palima_pcie_1_icb_request)
  }
};

/*******************************************************************************
 *              PCIe port clk related settings
 ******************************************************************************/
STATIC CONST char * palima_pcie_reset_clks_rp1[] =
{
  "gcc_pcie_1_aux_clk",
  NULL
};

STATIC CONST char * palima_pcie_gcc_clks_rp1[] =
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

CONST pcie_clk_mux_cfg_t palima_pcie_1_clk_mux = 
{
   .clk_name = "gcc_pcie_1_pipe_clk",
   .en_mux_val = 0,
   .dis_mux_val = 2,
};

CONST clk_freq_cfg_t palima_pcie_1_clk_settings[] =
{
  {.freq = 19200000,  .name = "gcc_pcie_1_aux_clk"},
  {.freq = 100000000, .name = "gcc_pcie_1_phy_rchng_clk"},
  {.freq = 0, .name = NULL}
};

STATIC CONST pcie_clocks_cfg_t palima_pcie_clk_rp1 =
{
   .clk_pwr    = "gcc_pcie_1_gdsc",
   .core_clks  = palima_pcie_gcc_clks_rp1,
   .clk_reset  = palima_pcie_reset_clks_rp1,
   .clk_mux    = &palima_pcie_1_clk_mux,
   .clk_freq   = palima_pcie_1_clk_settings,
   .icb_bw     = palima_pcie_1_icb_bw,
};

/*******************************************************************************
 *              PCIe port GPIO settings
 ******************************************************************************/
#define PALIMA_RC_1_GPIO_PCIE_RESET      97
#define PALIMA_RC_1_GPIO_CLK_REQ         98
#define PALIMA_RC_1_GPIO_PCIE_WAKE       99

STATIC CONST pcie_gpio_cfg_t palima_gpio_config_rp1[] =
{
  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = PALIMA_RC_1_GPIO_CLK_REQ,
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
    .tlmm.gpio_num       = PALIMA_RC_1_GPIO_PCIE_RESET,
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
    .tlmm.gpio_num       = PALIMA_RC_1_GPIO_PCIE_WAKE,
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
STATIC CONST pcie_reg_write_val_t palima_port_1_phy_init_seq[] =
{
   {HWIO_OFFS(PCIE_PARF_DEVICE_TYPE),                                 0x04},

   {HWIO_OFFS(PCS_COM_POWER_DOWN_CONTROL),    0x03},  //    Release powerdown mode and allow endpoint refclk drive        
   {HWIO_OFFS(QSERDES_PLL_SSC_EN_CENTER),    0x01},  //    "0x04: select internal diff cml clock inputs; 0x08: select SE cmos clock input"
   {HWIO_OFFS(QSERDES_PLL_SSC_PER1),    0x31},
   {HWIO_OFFS(QSERDES_PLL_SSC_PER2),    0x01},
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE0),    0xde},
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE0),    0x07},  //    PLL lock count = 512
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE1),    0x4c},
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE1),    0x06},
   {HWIO_OFFS(QSERDES_PLL_CLK_ENABLE1),    0x90},
   {HWIO_OFFS(QSERDES_PLL_SYS_CLK_CTRL),    0x82},
   {HWIO_OFFS(QSERDES_PLL_PLL_IVCO),    0x07},
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE0),    0x02},
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE1),    0x02},
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE0),    0x16},
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE1),    0x16},
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE0),    0x36},
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE1),    0x36},
   {HWIO_OFFS(QSERDES_PLL_SYSCLK_EN_SEL),    0x08},
   {HWIO_OFFS(QSERDES_PLL_BG_TIMER),    0x0e},
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP_EN),    0x42},
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE0),    0x0a},
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE0),    0x1a},
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE1),    0x14},
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE1),    0x34},
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE0),    0x82},
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE1),    0x68},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE0),    0x55},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE0),    0x55},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE0),    0x03},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE1),    0xab},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE1),    0xaa},
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE1),   0x02}, // 0xB9},  //    "0xB9:when Downspread SSC disabled; 0xCA: when Downspread SSC enabled"
   {HWIO_OFFS(QSERDES_PLL_VCO_TUNE_MAP),    0x14},
   {HWIO_OFFS(QSERDES_PLL_CLK_SELECT),    0x34},// 0x94},  //    "0x94:when Downspread SSC disabled; 0xA2: when Downspread SSC enabled"
   {HWIO_OFFS(QSERDES_PLL_HSCLK_SEL_1),    0x01},
   {HWIO_OFFS(QSERDES_PLL_CORECLK_DIV_MODE1),    0x04},  //    "0x00: Downspread SSC disabled (default, so no write needed); 0x01: Downspread SSC enabled"
   {HWIO_OFFS(QSERDES_PLL_CMN_CONFIG_1),    0x16},  //    Set SSC frequency to 31.5KHz
   {HWIO_OFFS(QSERDES_PLL_ADDITIONAL_MISC_3),    0x0f},
   {HWIO_OFFS(QSERDES_PLL_CORE_CLK_EN),    0xa0},  //    Set SSC step size for Gen1/2 (4500ppm)
   {HWIO_OFFS(QSERDES_RX0_DFE_CTLE_POST_CAL_OFFSET),    0x38},
   {HWIO_OFFS(QSERDES_RX0_GM_CAL),    0x11},  //    Set SSC step size for Gen3 (4500 ppm)
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH),    0xbf},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH2),    0xbf},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH3),    0xb7},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH4),    0xea},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_LOW),    0x3f},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH),    0x5c},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH2),    0x9c},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH3),    0x1a},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH4),    0x89},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_LOW),    0xdc},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH),    0x94},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH2),    0x5b},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH3),    0x1a},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH4),    0x89},
   {HWIO_OFFS(QSERDES_RX0_TX_ADAPT_POST_THRESH),    0xf0},
   {HWIO_OFFS(QSERDES_RX0_UCDR_FO_GAIN),    0x09},
   {HWIO_OFFS(QSERDES_RX0_UCDR_SO_GAIN),    0x05},
   {HWIO_OFFS(QSERDES_RX0_UCDR_SB2_THRESH1),    0x08},
   {HWIO_OFFS(QSERDES_RX0_UCDR_SB2_THRESH2),    0x08},
   {HWIO_OFFS(QSERDES_RX0_VGA_CAL_CNTRL2),    0x0f},
   {HWIO_OFFS(QSERDES_RX0_SIGDET_ENABLES),    0x1c},
   {HWIO_OFFS(QSERDES_RX0_RX_IDAC_TSETTLE_LOW),    0x07},
   {HWIO_OFFS(QSERDES_RX0_SIGDET_CAL_TRIM),    0x08},
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_1),    0x15},
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_4),    0x3f},  //    Adjust post curser adaptation
   {HWIO_OFFS(QSERDES_TX0_PI_QEC_CTRL),    0x02},
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_RX),    0x06},
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_TX),    0x17},
   {HWIO_OFFS(QSERDES_RX1_DFE_CTLE_POST_CAL_OFFSET),    0x38},
   {HWIO_OFFS(QSERDES_RX1_GM_CAL),    0x11},  //    Turn off int aux clock usage in Lahaina
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH),    0xbf},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH2),    0xbf},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH3),    0xb7},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH4),    0xea},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_LOW),    0x3f},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH),    0x5c}, 
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH2),    0x9c},  //    Adjust post curser adaptation
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH3),    0x1a},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH4),    0x89},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_LOW),    0xdc},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH),    0x94},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH2),    0x5b},  //    Turn off int aux clock usage in Lahaina
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH3),    0x1a},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH4),    0x89},
   {HWIO_OFFS(QSERDES_RX1_TX_ADAPT_POST_THRESH),    0xf0},
   {HWIO_OFFS(QSERDES_RX1_UCDR_FO_GAIN),    0x09},
   {HWIO_OFFS(QSERDES_RX1_UCDR_SO_GAIN),    0x05},
   {HWIO_OFFS(QSERDES_RX1_UCDR_SB2_THRESH1),    0x08}, 
   {HWIO_OFFS(QSERDES_RX1_UCDR_SB2_THRESH2),    0x08},  //    Adjust post curser adaptation
   {HWIO_OFFS(QSERDES_RX1_VGA_CAL_CNTRL2),    0x0f},
   {HWIO_OFFS(QSERDES_RX1_SIGDET_ENABLES),    0x1c},
   {HWIO_OFFS(QSERDES_RX1_RX_IDAC_TSETTLE_LOW),    0x07},
   {HWIO_OFFS(QSERDES_RX1_SIGDET_CAL_TRIM),    0x08},
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_1),    0x15},  //    Turn off int aux clock usage in Lahaina
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_4),    0x3f},
   {HWIO_OFFS(QSERDES_TX1_PI_QEC_CTRL),    0x02},
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_RX),    0x06},
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_TX),    0x17},
   {HWIO_OFFS(PCS_COM_REFGEN_REQ_CONFIG1),    0x05},
   {HWIO_OFFS(PCS_COM_RX_SIGDET_LVL),    0x77}, 
   {HWIO_OFFS(PCS_COM_RATE_SLEW_CNTRL1),    0x0b},
   {HWIO_OFFS(PCS_COM_EQ_CONFIG2),    0x0f},
   {HWIO_OFFS(PCS_PCIE_POWER_STATE_CONFIG2),    0x1d},
   {HWIO_OFFS(PCS_PCIE_POWER_STATE_CONFIG4),    0x07}, 
   {HWIO_OFFS(PCS_PCIE_ENDPOINT_REFCLK_DRIVE),    0xc1},  //    Adjust post curser adaptation
   {HWIO_OFFS(PCS_PCIE_OSC_DTCT_ACTIONS),    0x00},
   {HWIO_OFFS(PCS_COM_PCS_TX_RX_CONFIG),    0x8c},
   {HWIO_OFFS(PCS_LANE1_INSIG_SW_CTRL2),    0x00},
   {HWIO_OFFS(PCS_LANE1_INSIG_MX_CTRL2),    0x00},

  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t palima_port_1_phy_start_seq[] =
{
   {HWIO_OFFS(PCS_COM_SW_RESET),    0x00},  //    Release software reset
   {HWIO_OFFS(PCS_COM_START_CONTROL),    0x03},  //    Start PCS and Serdes power SMs
  {PCIE_REG_OP_STOP},
};



STATIC CONST pcie_reg_op_t palima_port_1_phy_poll_seq[] =
{
  {PCIE_REG_OP_POLL, HWIO_OFFS(PCS_COM_PCS_STATUS1), HWIO_PCS_COM_PCS_STATUS1_PHYSTATUS_BMSK, FALSE},
  {PCIE_REG_OP_STOP},
};


STATIC CONST pcie_reg_op_t palima_pcie_1_post_phy_pwr_up_init_seq[] =
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

STATIC CONST pcie_reg_write_val_t palima_port_1_phy_de_init_seq[] =
{
   {HWIO_OFFS(PCS_COM_POWER_DOWN_CONTROL),    0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t palima_port_1_phy_de_init_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(palima_port_1_phy_de_init_seq),
  {PcieSeq_Stop},
};

/*******************************************************************************
 *                       Loopback
 ******************************************************************************/

STATIC CONST pcie_reg_write_val_t palima_port_1_phy_lpb_en_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                      0x0C},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                      0x0C},
   {HWIO_OFFS(PCS_LANE0_TEST_CONTROL1),                 0x03},
   {HWIO_OFFS(PCS_LANE1_TEST_CONTROL1),                 0x03},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t palima_port_1_phy_lpb_dis_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                      0x00},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                      0x00},
   {HWIO_OFFS(PCS_LANE0_TEST_CONTROL1),                 0x00},
   {HWIO_OFFS(PCS_LANE1_TEST_CONTROL1),           0x00},
   {HWIO_OFFS(PCS_COM_POWER_DOWN_CONTROL),        0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t palima_port_1_phy_lpb_en_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(palima_port_1_phy_lpb_en_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t palima_port_1_phy_lpb_dis_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(palima_port_1_phy_lpb_dis_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_loopback_cfg_t palima_port_1_loopback_seq = 
{
   palima_port_1_phy_lpb_en_cfg,
   palima_port_1_phy_lpb_dis_cfg,
};

/*******************************************************************************
 * Register set reset sequences
 ******************************************************************************/
static const pcie_reg_op_t palima_port_1_reg_reset_seq[] = 
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
