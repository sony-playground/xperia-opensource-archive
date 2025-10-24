/*
 *  PCIe root port target config
 */
/*============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
============================================================================*/

#include "kailua_pcie_0.h"
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

CONST pcie_reg_op_t kailua_port_0_x2_lane_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBIPORT_LINK_CTRL_OFF), HWIO_PCIE_0_DBIPORT_LINK_CTRL_OFF_LINK_CAPABLE_BMSK,
                     (PORT_LINK_LANE_CAPABLE_VAL(PORT_2_LANE) << HWIO_PCIE_0_DBIPORT_LINK_CTRL_OFF_LINK_CAPABLE_SHFT)},
   {PCIE_REG_OP_STOP},
};

/*******************************************************************************
 *       Post PHY power ON sequence 
 ******************************************************************************/
CONST pcie_reg_op_t kailua_port_0_post_phy_pwr_up_init_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_DEVICE_TYPE), HWIO_PCIE_PARF_DEVICE_TYPE_DEVICE_TYPE_BMSK, HWIO_PCIE_PARF_DEVICE_TYPE_DEVICE_TYPE_RC_FVAL},
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_PM_CTRL), HWIO_PCIE_PARF_PM_CTRL_REQ_NOT_ENTR_L1_BMSK, 0x0},
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_SYS_CTRL), HWIO_PCIE_PARF_SYS_CTRL_AUX_PWR_DET_BMSK, (0x01 << HWIO_PCIE_PARF_SYS_CTRL_AUX_PWR_DET_SHFT)},
   {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_PARF_SLV_ADDR_SPACE_SIZE), 0, 0x01000000},
   //Writes to PCIE_PARF_CFG_BITS_3 needed to prevent NoC errors in L1ss when accessing MHI
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_CFG_BITS_3), HWIO_PCIE_PARF_CFG_BITS_3_PCIE_FAL10_OVERRIDE_EN_BMSK, (0x01 << HWIO_PCIE_PARF_CFG_BITS_3_PCIE_FAL10_OVERRIDE_EN_SHFT)},
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_CFG_BITS_3), HWIO_PCIE_PARF_CFG_BITS_3_PCIE_FAL10_OVERRIDE_VALUE_BMSK, (0x01 << HWIO_PCIE_PARF_CFG_BITS_3_PCIE_FAL10_OVERRIDE_VALUE_SHFT)},
   {PCIE_REG_OP_STOP},
};

CONST pcie_reg_op_t kailua_port_0_phy_delay_seq[] =
{
   {PCIE_REG_OP_DELAY, 0, 0, 2000},
   {PCIE_REG_OP_STOP},
};

#define PORT_LINK_SPEED_GEN_1     1
#define PORT_LINK_SPEED_GEN_2     2
#define PORT_LINK_SPEED_GEN_3     3
#define PORT_LINK_SPEED_GEN_4     4

CONST pcie_reg_op_t kailua_port_0_set_link_speed_gen_3[] =
{
    /* Link Speed */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBILINK_CONTROL2_LINK_STATUS2_REG), HWIO_PCIE_0_DBILINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED_BMSK, PORT_LINK_SPEED_GEN_3},
  {PCIE_REG_OP_DSB},
  {PCIE_REG_OP_STOP},
};

CONST pcie_reg_op_t kailua_port_0_set_link_speed_gen_4[] =
{
    /* Link Speed */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBILINK_CONTROL2_LINK_STATUS2_REG), HWIO_PCIE_0_DBILINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED_BMSK, PORT_LINK_SPEED_GEN_4},
  {PCIE_REG_OP_DSB},
  {PCIE_REG_OP_STOP},
};

CONST pcie_reg_op_t kailua_port_0_post_phy_pwr_up_dbi_init_seq[] =
{
    /* Fix NFTS */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBIACK_F_ASPM_CTRL_OFF), HWIO_PCIE_0_DBIACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS_BMSK, (0x80 << HWIO_PCIE_0_DBIACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS_SHFT)},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBIACK_F_ASPM_CTRL_OFF), HWIO_PCIE_0_DBIACK_F_ASPM_CTRL_OFF_ACK_N_FTS_BMSK, (0x80 << HWIO_PCIE_0_DBIACK_F_ASPM_CTRL_OFF_ACK_N_FTS_SHFT)},

  /* Treats out-of-bar TLPs as supported request - MUST for RC mode. Data book: Table I-2 */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBISYMBOL_TIMER_FILTER_1_OFF), HWIO_PCIE_0_DBISYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1_BMSK, (4 << HWIO_PCIE_0_DBISYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1_SHFT)},
  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_0_DBIAUX_CLK_FREQ_OFF), 0, 19},

  /* Allow establishing connection on one line even if there is a termination on the second line. Othewise the link will go to compliance */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBIGEN2_CTRL_OFF), HWIO_PCIE_0_DBIGEN2_CTRL_OFF_NUM_OF_LANES_BMSK, (0x01 << HWIO_PCIE_0_DBIGEN2_CTRL_OFF_NUM_OF_LANES_SHFT)},
  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_0_DBIMISC_CONTROL_1_OFF), 0, 0x1},
  {PCIE_REG_OP_DSB},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBIROOT_CONTROL_ROOT_CAPABILITIES_REG), HWIO_PCIE_0_DBIROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_CRS_SW_VISIBILITY_BMSK, 0},

  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBITYPE1_CLASS_CODE_REV_ID_REG),
    (HWIO_PCIE_0_DBITYPE1_CLASS_CODE_REV_ID_REG_BASE_CLASS_CODE_BMSK | HWIO_PCIE_0_DBITYPE1_CLASS_CODE_REV_ID_REG_SUBCLASS_CODE_BMSK),
    (PCIE_CLASS_CODE_BRIDGE_DEVICE | PCIE_SUBCLASS_CODE_PCI_2_PCI_BRIDGE)},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBISLOT_CAPABILITIES_REG), HWIO_PCIE_0_DBISLOT_CAPABILITIES_REG_PCIE_CAP_HOT_PLUG_CAPABLE_BMSK, 0},
  {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_0_DBIMISC_CONTROL_1_OFF), 0, 0},
  {PCIE_REG_OP_DSB},
  /* 52.08333333333 nano seconds per counter value for a 19.2 MHz clock
   * Programmed counter value = Time Required in seconds / 0.00000005208333333333
   * Begin with 20ms as inactivity timer.
   * Counter = .020 / 0.00000005208333333333 = 0x5DC00
   */

  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBIGEN3_EQ_FB_MODE_DIR_CHANGE_OFF), HWIO_PCIE_0_DBIGEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_T_MIN_PHASE23_BMSK, 0},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBIGEN3_EQ_CONTROL_OFF), HWIO_PCIE_0_DBIGEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_VEC_BMSK, 0},
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_0_DBIGEN3_RELATED_OFF), HWIO_PCIE_0_DBIGEN3_RELATED_OFF_GEN3_ZRXDC_NONCOMPL_BMSK, 0},
   
  {PCIE_REG_OP_DSB},

  {PCIE_REG_OP_STOP},
};


/*******************************************************************************
 *    Core Config:  Gen 3 x2, Hw offset 0
 ******************************************************************************/
/*******************************************************************************
 *    PMIC Power settings
 ******************************************************************************/
#define PMIC_NPA_CLIENT_NODE_PCIE0 "/pmic/client/pcie0"


static const pcie_pmic_config_t kailua_port_0_pmic_cfg = 
{
   .node_id = PMIC_NPA_CLIENT_NODE_PCIE0,
};

/*******************************************************************************
 *    Register region map
 ******************************************************************************/
static const mem_region_t kailua_port_0_mem_region[max_mem_reg] =
{
  /* axi_reg: DBI register space */
  {.pa=PCIE_GEN3X2_SPACE_BASE, .sz=PCIE_GEN3X2_SPACE_SIZE},

  /* ahb_reg: PARF register space */
  {.pa=PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_EDMA_BASE, .sz=PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_EDMA_SIZE},
};

/*******************************************************************************
 *   ICB bandwidth request settings
 ******************************************************************************/
STATIC CONST ICBArb_RequestType kailua_pcie_0_icb_request[] =
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

STATIC CONST ICBArb_MasterSlaveType kailua_pcie_0_icb_mstr_slv_lst[] =
{
  {
    .eMaster = ICBID_MASTER_PCIE_0,
    .eSlave = ICBID_SLAVE_EBI1
  },
};

STATIC pcieIcbClkBW_t kailua_pcie_0_icb_bw[] =
{
  {
    .npa_client_name = "pcie_0",
    .ms_list = kailua_pcie_0_icb_mstr_slv_lst,
    .ms_size = sizeof(kailua_pcie_0_icb_mstr_slv_lst),
    .req_list = kailua_pcie_0_icb_request,
    .req_size = sizeof(kailua_pcie_0_icb_request)
  },
};

/*******************************************************************************
 *              PCIe port clk related settings
 ******************************************************************************/
STATIC CONST char * kailua_pcie_reset_clks_rp0[] =
{
  "gcc_pcie_0_aux_clk",
  NULL
};

STATIC CONST char * kailua_pcie_gcc_clks_rp0[] =
{
  "gcc_pcie_0_cfg_ahb_clk",
  "tcsr_pcie_0_clkref_en",
  "gcc_pcie_0_pipe_clk",
  "gcc_pcie_0_aux_clk",
  "gcc_aggre_noc_pcie_axi_clk",
  "gcc_pcie_0_slv_q2a_axi_clk",
  "gcc_pcie_0_mstr_axi_clk",
  "gcc_pcie_0_slv_axi_clk",
  "gcc_pcie_0_phy_rchng_clk",
  "gcc_ddrss_pcie_sf_qtb_clk",
  NULL
};

CONST pcie_clk_mux_cfg_t kailua_pcie_0_clk_mux = 
{
   .clk_name = "gcc_pcie_0_pipe_clk",
   .en_mux_val = 0,
   .dis_mux_val = 2,
};

CONST clk_freq_cfg_t kailua_pcie_0_clk_settings[] =
{
  {.freq = 19200000,  .name = "gcc_pcie_0_aux_clk"},
  {.freq = 100000000, .name = "gcc_pcie_0_phy_rchng_clk"},
  {.freq = 0, .name = NULL},
};

STATIC CONST pcie_clocks_cfg_t kailua_pcie_clk_rp0 =
{
   .clk_pwr    = "gcc_pcie_0_gdsc",
   .phy_pwr    = "gcc_pcie_0_phy_gdsc",
   .core_clks  = kailua_pcie_gcc_clks_rp0,
   .clk_reset  = kailua_pcie_reset_clks_rp0,
   .clk_mux    = &kailua_pcie_0_clk_mux,
   .clk_freq   = kailua_pcie_0_clk_settings,
   .icb_bw     = kailua_pcie_0_icb_bw,
};

/*******************************************************************************
 *              PCIe port GPIO settings
 ******************************************************************************/
#define KAILUA_RC_0_GPIO_PCIE_RESET      94
#define KAILUA_RC_0_GPIO_CLK_REQ         95
#define KAILUA_RC_0_GPIO_PCIE_WAKE       96

STATIC CONST pcie_gpio_cfg_t kailua_gpio_config_rp0[] =
{
  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = KAILUA_RC_0_GPIO_CLK_REQ,
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
    .tlmm.gpio_num       = KAILUA_RC_0_GPIO_PCIE_RESET,
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
    .tlmm.gpio_num       = KAILUA_RC_0_GPIO_PCIE_WAKE,
    .tlmm.func_sel       = 0,
    .tlmm.direction      = GPIO_INPUT,
    .tlmm.pull           = GPIO_PULL_UP,
    .tlmm.drive_strength = GPIO_2MA,
    .tlmm.value          = GPIO_LOW_VALUE
   }
  },

  { .cfg_type = NONE, { .delay_us = NONE } },
};

/*******************************************************************************
 *
 *                           PORT 0 Phy
 *
 *******************************************************************************/
STATIC CONST pcie_reg_write_val_t kailua_port_0_phy_init_seq[] =
{
   {HWIO_OFFS(PCIE_PARF_DEVICE_TYPE),                                 0x04},

   {HWIO_OFFS(PCIE3_PCS_COM_POWER_DOWN_CONTROL),    0x03},
   {HWIO_OFFS(QSERDES_PLL_SSC_EN_CENTER),    0x00},  //    "0x00: Downspread SSC disabled (default, so no write needed); 0x01: Downspread SSC enabled"
   {HWIO_OFFS(QSERDES_PLL_SSC_PER1),    0x62},  //    "0x31: 19.2MHz refclk - set SSC frequency to 31.5KHz; 0x62: 38.4MHz refclk - set SSC frequency to 31.5KHz"
   {HWIO_OFFS(QSERDES_PLL_SSC_PER2),    0x02},  //    "0x01: 19.2MHz refclk; 0x02: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE0),    0xF8},  //    "0xFF: 19.2MHz refclk - set SSC step size for Gen1/2 (4000ppm); 0xF8: 38.4MHz refclk - set SSC step size for Gen1/2 (4500ppm)"
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE0),    0x01},  //    "0x06: 19.2MHz refclk; 0x01: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE1),    0x93},  //    "0x4C: 19.2MHz refclk - set SSC step size for Gen3 (4500ppm); 0x93: 38.4MHz refclk - set SSC step size for Gen3 (4500ppm)"
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE1),    0x01},  //    "0x06: 19.2MHz refclk; 0x01: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_CLK_ENABLE1),    0x90},
   {HWIO_OFFS(QSERDES_PLL_SYS_CLK_CTRL),    0x82},  //    Select SW endpoint enable
   {HWIO_OFFS(QSERDES_PLL_PLL_IVCO),    0x07},
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE0),    0x02},
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE1),    0x02},
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE0),    0x16},
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE1),    0x16},
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE0),    0x36},
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE1),    0x36},
   {HWIO_OFFS(QSERDES_PLL_SYSCLK_EN_SEL),    0x08},  //    "0x04: select internal diff cml clock inputs; 0x08: select SE cmos clock input"
   {HWIO_OFFS(QSERDES_PLL_BG_TIMER),    0x0A},  //    "0x0E: 19.2MHz refclk value; 0x0A: 38.4MHz refclk value"
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP_EN),    0x42},
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE0),    0x04},  //    "0x0A: 19.2MHz refclk; 0x04: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE0),    0x0D},  //    "0x1A: 19.2MHz refclk; 0x0D: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE1),    0x0A},  //    "0x14: 19.2MHz refclk; 0x0A: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE1),    0x1A},  //    "0x34: 19.2MHz refclk; 0x1A: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE0),    0x41},  //    "0x82: 19.2MHz refclk; 0x41: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE1),    0x34},  //    "0x68: 19.2MHz refclk; 0x34: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE0),    0xAB},  //    "0xAB: 19.2MHz refclk; 0xAB: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE0),    0xAA},  //    "0xEA: 19.2MHz refclk; 0xAA: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE0),    0x01},  //    "0x02: 19.2MHz refclk; 0x01: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE1),    0x55},  //    "0xAB: 19.2MHz refclk; 0x55: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE1),    0x55},  //    "0xAA: 19.2MHz refclk; 0x55: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE1),    0x01},  //    "0x02: 19.2MHz refclk; 0x01: 38.4MHz refclk"
   {HWIO_OFFS(QSERDES_PLL_VCO_TUNE_MAP),    0x14},  //    Set mode0 as gen1/2 and mode1 as gen3/4
   {HWIO_OFFS(QSERDES_PLL_CLK_SELECT),    0x34},
   {HWIO_OFFS(QSERDES_PLL_HSCLK_SEL_1),    0x01},
   {HWIO_OFFS(QSERDES_PLL_CORECLK_DIV_MODE1),    0x04},
   {HWIO_OFFS(QSERDES_PLL_CMN_CONFIG_1),    0x16},
   {HWIO_OFFS(QSERDES_PLL_ADDITIONAL_MISC_3),    0x0F},
   {HWIO_OFFS(QSERDES_PLL_CORE_CLK_EN),    0xA0},  //    Set PLL lock clock divider
   {HWIO_OFFS(QSERDES_RX0_DFE_CTLE_POST_CAL_OFFSET),    0x38},
   {HWIO_OFFS(QSERDES_RX0_GM_CAL),    0x11},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH),    0xBF},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH2),    0xBF},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH3),    0xB7},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH4),    0xEA},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_LOW),    0x3F},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH),    0x5C},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH2),    0x9C},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH3),    0x1A},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH4),    0x89},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_LOW),    0xDC},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH),    0x94},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH2),    0x5B},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH3),    0x1A},
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH4),    0x89},
   {HWIO_OFFS(QSERDES_RX0_TX_ADAPT_POST_THRESH),    0x00},  //    Adjust post cursor adaptation (Palima can keep 0xF0)
   {HWIO_OFFS(QSERDES_RX0_UCDR_FO_GAIN),    0x09},
   {HWIO_OFFS(QSERDES_RX0_UCDR_SO_GAIN),    0x05},
   {HWIO_OFFS(QSERDES_RX0_UCDR_SB2_THRESH1),    0x08},
   {HWIO_OFFS(QSERDES_RX0_UCDR_SB2_THRESH2),    0x08},
   {HWIO_OFFS(QSERDES_RX0_VGA_CAL_CNTRL2),    0x0F},
   {HWIO_OFFS(QSERDES_RX0_SIGDET_ENABLES),    0x1C},  //    Force use of local bias; bypass pulse width filter
   {HWIO_OFFS(QSERDES_RX0_RX_IDAC_TSETTLE_LOW),    0x07},
   {HWIO_OFFS(QSERDES_RX0_SIGDET_CAL_TRIM),    0x08},  //    Adjust sigdet cal trim
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_1),    0x15},
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_4),    0x3F},
   {HWIO_OFFS(QSERDES_TX0_PI_QEC_CTRL),    0x02},
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_RX),    0x06},
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_TX),    0x18},
   {HWIO_OFFS(QSERDES_RX1_DFE_CTLE_POST_CAL_OFFSET),    0x38},
   {HWIO_OFFS(QSERDES_RX1_GM_CAL),    0x11},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH),    0xBF},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH2),    0xBF},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH3),    0xB7},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH4),    0xEA},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_LOW),    0x3F},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH),    0x5C},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH2),    0x9C},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH3),    0x1A},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH4),    0x89},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_LOW),    0xDC},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH),    0x94},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH2),    0x5B},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH3),    0x1A},
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH4),    0x89},
   {HWIO_OFFS(QSERDES_RX1_TX_ADAPT_POST_THRESH),    0x00},  //    Adjust post cursor adaptation (Palima can keep 0xF0)
   {HWIO_OFFS(QSERDES_RX1_UCDR_FO_GAIN),    0x09},
   {HWIO_OFFS(QSERDES_RX1_UCDR_SO_GAIN),    0x05},
   {HWIO_OFFS(QSERDES_RX1_UCDR_SB2_THRESH1),    0x08},
   {HWIO_OFFS(QSERDES_RX1_UCDR_SB2_THRESH2),    0x08},
   {HWIO_OFFS(QSERDES_RX1_VGA_CAL_CNTRL2),    0x0F},
   {HWIO_OFFS(QSERDES_RX1_SIGDET_ENABLES),    0x1C},  //    Force use of local bias; bypass pulse width filter
   {HWIO_OFFS(QSERDES_RX1_RX_IDAC_TSETTLE_LOW),    0x07},
   {HWIO_OFFS(QSERDES_RX1_SIGDET_CAL_TRIM),    0x08},  //    Adjust sigdet cal trim
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_1),    0x15},
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_4),    0x3F},
   {HWIO_OFFS(QSERDES_TX1_PI_QEC_CTRL),    0x02},
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_RX),    0x06},
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_TX),    0x18},
   {HWIO_OFFS(PCIE3_PCS_COM_REFGEN_REQ_CONFIG1),    0x05},
   {HWIO_OFFS(PCIE3_PCS_COM_RX_SIGDET_LVL),    0x77},
   {HWIO_OFFS(PCIE3_PCS_COM_RATE_SLEW_CNTRL1),    0x0B},
   {HWIO_OFFS(PCIE3_PCS_PCIE_EQ_CONFIG1),    0x1E},  //    Flip post inc/dec mapping
   {HWIO_OFFS(PCIE3_PCS_COM_EQ_CONFIG2),    0x0F},
   {HWIO_OFFS(PCIE3_PCS_PCIE_POWER_STATE_CONFIG2),    0x1D},
   {HWIO_OFFS(PCIE3_PCS_PCIE_POWER_STATE_CONFIG4),    0x07},
   {HWIO_OFFS(PCIE3_PCS_PCIE_ENDPOINT_REFCLK_DRIVE),    0xC1},
   {HWIO_OFFS(PCIE3_PCS_PCIE_OSC_DTCT_ACTIONS),    0x00},
   {HWIO_OFFS(PCIE3_PCS_COM_PCS_TX_RX_CONFIG),    0x8C},  //    Set Pinf RTB depth to 5 for all gens (evaluate per SOC)

   // 0x00 : 2-Lane mode,(default value - write not needed); 
   // 0x01: 1-Lane mode, Lane 1 disabled
#ifdef USE_SINGLE_LANE_DISABLE_UPPER_LANE
   {HWIO_OFFS(PCIE3_PCS_LANE1_INSIG_SW_CTRL2),    0x01},
   {HWIO_OFFS(PCIE3_PCS_LANE1_INSIG_MX_CTRL2),    0x01},
#endif
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t kailua_port_0_phy_start_seq[] =
{
   {HWIO_OFFS(PCIE3_PCS_COM_SW_RESET),    0x00},  //    Release software reset
   {HWIO_OFFS(PCIE3_PCS_COM_START_CONTROL),    0x03},  //    Start PCS and Serdes power SMs
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t kailua_port_0_phy_poll_seq[] =
{
  {PCIE_REG_OP_POLL, HWIO_OFFS(PCIE3_PCS_COM_PCS_STATUS1), HWIO_PCIE3_PCS_COM_PCS_STATUS1_PHYSTATUS_BMSK, FALSE},
  {PCIE_REG_OP_STOP},
};


STATIC CONST pcie_reg_op_t kailua_pcie_0_post_phy_pwr_up_init_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_0_DBIGEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_N_EVALS), 0x0D},
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_0_DBIGEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA), 0x05},
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_0_DBIGEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA), 0x05},
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_0_DBIGEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_T_MIN_PHASE23), 0x00},
   /* TODO: Check if the following is the right ones to reference for this setting
    *  GEN3_RELATED.EQ_PHASE_2_3 or
    *  GEN3_EQ_CONTROL.GEN3_EQ_PHASE23_EXIT_MODE */
//   {HWIO_REG_MASK(PCIE_DBI_GEN3_RELATED_OFF, GEN3_EQ_PHASE23_EXIT_MODE), 0x00},    // 0x890
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_0_DBIGEN3_EQ_CONTROL_OFF, GEN3_EQ_PHASE23_EXIT_MODE), 0x00},
   {PCIE_REG_OP_RMW, HWIO_REG_MASK(PCIE_0_DBIGEN3_EQ_CONTROL_OFF, GEN3_EQ_PSET_REQ_VEC), 0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t kailua_port_0_phy_de_init_seq[] =
{
   {HWIO_OFFS(PCIE3_PCS_COM_POWER_DOWN_CONTROL),    0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t kailua_port_0_phy_de_init_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(kailua_port_0_phy_de_init_seq),
  {PcieSeq_Stop},
};

/*******************************************************************************
 *                       Loopback
 ******************************************************************************/

STATIC CONST pcie_reg_write_val_t kailua_port_0_phy_lpb_en_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                      0x0C},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                      0x0C},
   {HWIO_PCIE3_PCS_LANE0_TEST_CONTROL1_OFFS,            0x03},
   {HWIO_PCIE3_PCS_LANE1_TEST_CONTROL1_OFFS,             0x03},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t kailua_port_0_phy_lpb_dis_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                      0x00},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                      0x00},
   {HWIO_PCIE3_PCS_LANE0_TEST_CONTROL1_OFFS,            0x00},
   {HWIO_PCIE3_PCS_LANE1_TEST_CONTROL1_OFFS,            0x00},
   {HWIO_OFFS(PCIE3_PCS_COM_POWER_DOWN_CONTROL),   0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t kailua_port_0_phy_lpb_en_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(kailua_port_0_phy_lpb_en_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t kailua_port_0_phy_lpb_dis_cfg[] =
{
  {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(kailua_port_0_phy_lpb_dis_seq),
  {PcieSeq_Stop},
};

STATIC CONST pcie_loopback_cfg_t kailua_port_0_loopback_seq = 
{
   kailua_port_0_phy_lpb_en_cfg,
   kailua_port_0_phy_lpb_dis_cfg,
};

/*******************************************************************************
 *               Port 0 init Configuration
 ******************************************************************************/
STATIC CONST pcie_reg_init_cfg_t kailua_port_0_phy_init_cfg[] =
{
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(kailua_port_0_phy_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(kailua_port_0_phy_start_seq),

  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(kailua_port_0_phy_delay_seq),

  /* Check if the PHY PLL is locked */
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(kailua_port_0_phy_poll_seq),

  /* Perform post power up sequence */
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(kailua_port_0_x2_lane_seq),
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(kailua_pcie_0_post_phy_pwr_up_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(kailua_port_0_post_phy_pwr_up_init_seq),

  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(kailua_port_0_set_link_speed_gen_3),
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(kailua_port_0_post_phy_pwr_up_dbi_init_seq),

  {PcieSeq_Stop},
};


/*******************************************************************************
 *               PCIe_0 Driver config definitions
 ******************************************************************************/
STATIC CONST pcie_drvr_cfg_t kailua_port_0_drvr_cfg =
{
  .port_clk_cfg           = &kailua_pcie_clk_rp0, 
  .port_gpio_cfg          = kailua_gpio_config_rp0,
  .iommu_cfg              = "PCIE0",
  .pmic_cfg               = &kailua_port_0_pmic_cfg, 
};

/*******************************************************************************
 *               PCIe_0 config definitions
 ******************************************************************************/
const pcie_port_config_t kailua_port_0_cfg[] =
{
   {
      .hw_rp_index            = 0,
      .driver_config          = &kailua_port_0_drvr_cfg,
      .port_mem_bases         = kailua_port_0_mem_region,
      .port_phy_init_cfg      = kailua_port_0_phy_init_cfg,
      .port_phy_deinit_cfg    = kailua_port_0_phy_de_init_cfg,
      .loopback_cfg           = &kailua_port_0_loopback_seq,
      .perst_pin              = KAILUA_RC_0_GPIO_PCIE_RESET,
      .port_attributes        = aspm_l1_ena_l0s_ena,
   },
};

const uint8_t kailua_port_0_cfg_len = ARRAY_LENGTH(kailua_port_0_cfg);
