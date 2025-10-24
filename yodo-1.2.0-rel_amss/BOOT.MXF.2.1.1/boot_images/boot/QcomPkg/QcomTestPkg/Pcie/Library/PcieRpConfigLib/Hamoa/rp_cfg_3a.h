#ifndef __PCIE_TARGET_PORT_3A_CONFIG_H__
#define __PCIE_TARGET_PORT_3A_CONFIG_H__
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
static const mem_region_t port_3a_mem_region[max_mem_reg] =
{
  /**< axi_reg: DBI register space */
  {.pa=PCIE_3APCIE_WRAPPER_AXI_G3X4_EDMA_AUTO_BASE, .sz=PCIE_3APCIE_WRAPPER_AXI_G3X4_EDMA_AUTO_BASE_SIZE},

  /**< ahb_reg: PARF register space */
  {.pa=PCIE3A_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE, .sz=PCIE3A_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE_SIZE},

  /**< tcsr_reg: Access TCSR register space */
  {.pa=CORE_TOP_CSR_BASE, .sz=CORE_TOP_CSR_BASE_SIZE},

  /* prefetchable_mem_space: prefetchable mem space */
  {.pa=PCIE_3A_SPACE_BASE, .sz=PCIE_3A_SPACE_SIZE_BASE},
};

/*******************************************************************************
 *   ICB bandwidth request settings
 ******************************************************************************/
STATIC CONST ICBArb_RequestType pcie_3a_icb_request[] =
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

STATIC CONST ICBArb_MasterSlaveType pcie_3a_icb_mstr_slv_lst[] =
{
  {
    .eMaster = ICBID_MASTER_PCIE_3A,
    .eSlave = ICBID_SLAVE_EBI1
  }
};

STATIC pcieIcbClkBW_t pcie_3a_icb_bw[] =
{
  {
    .npa_client_name = "pcie_3a",
    .ms_list = pcie_3a_icb_mstr_slv_lst,
    .ms_size = sizeof(pcie_3a_icb_mstr_slv_lst),
    .req_list = pcie_3a_icb_request,
    .req_size = sizeof(pcie_3a_icb_request)
  }
};

/*******************************************************************************
 *              PCIe port clk related settings
 ******************************************************************************/
STATIC CONST char * pcie_reset_clks_rp3a[] =
{
  "gcc_pcie_3a_aux_clk",
  NULL
};

STATIC CONST char * pcie_gcc_clks_rp3a[] =
{
  "gcc_aggre_noc_pcie_south_sf_axi_clk",
  "gcc_pcie_3a_pipe_clk",
  "gcc_pcie_3a_pipediv2_clk",
  "gcc_pcie_3a_aux_clk",
  "gcc_pcie_3a_slv_axi_clk",
  "gcc_pcie_3a_slv_q2a_axi_clk",
  "gcc_pcie_3a_mstr_axi_clk",
  "gcc_pcie_3a_cfg_ahb_clk",
  "gcc_pcie3a_phy_rchng_clk",
  "gcc_pcie_3a3b_clkref_en",
  NULL
};

STATIC CONST pcie_clk_mux_cfg_t pcie_3a_clk_mux = 
{
   .clk_name = "gcc_pcie_3a_pipe_clk",
   .en_mux_val = 0,
   .dis_mux_val = 2,
};

STATIC CONST clk_freq_cfg_t pcie_3a_clk_settings[] =
{
  {.freq = 19200000,  .name = "gcc_pcie_3a_aux_clk"},
  {.freq = 100000000, .name = "gcc_pcie3a_phy_rchng_clk"},
  {.freq = 0, .name = NULL}
};

STATIC CONST pcie_clocks_cfg_t pcie_clk_rp3a =
{
   .clk_pwr    = "gcc_pcie_3a_gdsc",
   .core_clks  = pcie_gcc_clks_rp3a,
   .clk_reset  = pcie_reset_clks_rp3a,
   .clk_mux    = &pcie_3a_clk_mux,
   .clk_freq   = pcie_3a_clk_settings,
   .icb_bw     = pcie_3a_icb_bw,
};

/*******************************************************************************
 *              PCIe port GPIO settings
 ******************************************************************************/
#define RC_3A_GPIO_PCIE_RESET      151
#define RC_3A_GPIO_CLK_REQ         150
#define RC_3A_GPIO_PCIE_WAKE       148

STATIC CONST pcie_gpio_cfg_t gpio_config_rp3a[] =
{
  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = RC_3A_GPIO_CLK_REQ,
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
    .tlmm.gpio_num       = RC_3A_GPIO_PCIE_RESET,
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
    .tlmm.gpio_num       = RC_3A_GPIO_PCIE_WAKE,
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
 * Register set reset sequences
 ******************************************************************************/
static const pcie_reg_op_t port_3a_x2_reg_reset_seq[] = 
{
  /* Register Base, Operation, Offset, Mask & Value */
  { PCIE_REG_OP_WRITE, GCC_PCIE_3A_BCR_OFF,       0x00,  0x01 },
  { PCIE_REG_OP_DELAY, 0, 0, 1 },
  { PCIE_REG_OP_WRITE, GCC_PCIE_3A_BCR_OFF,       0x00,  0x00 },

  { PCIE_REG_OP_WRITE, GCC_PCIE_3A_PHY_BCR_OFF,   0x00,  0x01 },
  { PCIE_REG_OP_DELAY, 0, 0, 1 },
  { PCIE_REG_OP_WRITE, GCC_PCIE_3A_PHY_BCR_OFF,   0x00,  0x00 },

  { PCIE_REG_OP_STOP, 0, 0, 0 },
};

static const pcie_reg_op_t port_3a_x4_reg_reset_seq[] = 
{
  /* Register Base, Operation, Offset, Mask & Value */
  {  PCIE_REG_OP_WRITE, GCC_PCIE_3A_BCR_OFF,       0x00,  0x01 },
  {  PCIE_REG_OP_DELAY, 0, 0, 1 },
  {  PCIE_REG_OP_WRITE, GCC_PCIE_3A_BCR_OFF,       0x00,  0x00 },

  {  PCIE_REG_OP_WRITE, GCC_PCIE_3A_PHY_BCR_OFF,   0x00,  0x01 },
  {  PCIE_REG_OP_DELAY, 0, 0, 1 },
  {  PCIE_REG_OP_WRITE, GCC_PCIE_3A_PHY_BCR_OFF,   0x00,  0x00 },
  
  {  PCIE_REG_OP_WRITE, GCC_PCIE_3B_PHY_BCR_OFF,   0x00,  0x01 },
  {  PCIE_REG_OP_DELAY, 0, 0, 1 },
  {  PCIE_REG_OP_WRITE, GCC_PCIE_3B_PHY_BCR_OFF,   0x00,  0x00 },

  {  PCIE_REG_OP_STOP, 0, 0, 0 },
};

#endif   /* __PCIE_TARGET_PORT_3A_CONFIG_H__ */
