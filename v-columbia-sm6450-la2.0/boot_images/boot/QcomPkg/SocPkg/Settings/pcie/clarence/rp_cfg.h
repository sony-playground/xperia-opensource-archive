#ifndef __CLARENCE_ROOT_PORT_CONFIG_H__
#define __CLARENCE_ROOT_PORT_CONFIG_H__
/*
 *  PCIe root port target config
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   04/20/23   ms      Created New

*/
/*============================================================================
            Copyright (c) 2023 Qualcomm Technologies, Inc. 
                        All Rights Reserved.
        Confidential and Proprietary – Qualcomm Technologies, Inc.
============================================================================*/

#include "pcie_cfg_types.h"
#include "pcie_hwio.h"
#include "pcie_hwio_base.h"
#include <Library/pmapp_npa.h>

#define REG_OP_TYPE(x)        PCIE_REG_OP_SEQ, {.reg_op_seq = x}}
#define REG_WRITE_TYPE(x)     PCIE_REG_WRITE_SEQ, {.reg_write_val_seq = x}}

#define __msmhwio_offs(hwiosym)                                 HWIO_##hwiosym##_OFFS
#define __msmhwio_mask(reg,mask)                                HWIO_##reg##_##mask##_BMSK
#define HWIO_OFFS(hwiosym)                               __msmhwio_offs(hwiosym)
#define HWIO_REG_MASK(reg,mask)                          __msmhwio_offs(reg),__msmhwio_mask(reg, mask)

#include "rp_cfg_0.h"

#define STR_ID(a,b,c,d)     (a | (b << 8) | (c << 16) | (d << 24))

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

STATIC CONST pcie_reg_op_t clarence_port_x2_lane_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PORT_LINK_CTRL_OFF), HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_BMSK,
                     (PORT_LINK_LANE_CAPABLE_VAL(PORT_2_LANE) << HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_SHFT)},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t clarence_port_x1_lane_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PORT_LINK_CTRL_OFF), HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_BMSK,
                     (PORT_LINK_LANE_CAPABLE_VAL(PORT_1_LANE) << HWIO_PCIE_PORT_LINK_CTRL_OFF_LINK_CAPABLE_SHFT)},
   {PCIE_REG_OP_STOP},
};

/*******************************************************************************
 *       Post PHY power ON sequence 
 ******************************************************************************/
STATIC CONST pcie_reg_op_t clarence_post_phy_pwr_up_init_seq[] =
{
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_DEVICE_TYPE), HWIO_PCIE_PARF_DEVICE_TYPE_DEVICE_TYPE_BMSK, HWIO_PCIE_PARF_DEVICE_TYPE_DEVICE_TYPE_RC_FVAL},
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_PM_CTRL), HWIO_PCIE_PARF_PM_CTRL_REQ_NOT_ENTR_L1_BMSK, 0x0},
   {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_PARF_SYS_CTRL), HWIO_PCIE_PARF_SYS_CTRL_AUX_PWR_DET_BMSK, (0x01 << HWIO_PCIE_PARF_SYS_CTRL_AUX_PWR_DET_SHFT)},
   {PCIE_REG_OP_WRITE, HWIO_OFFS(PCIE_PARF_SLV_ADDR_SPACE_SIZE), 0, 0x01000000},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t clarence_phy_delay_seq[] =
{
   {PCIE_REG_OP_DELAY, 0, 0, 2000},
   {PCIE_REG_OP_STOP},
};

#define PORT_LINK_SPEED_GEN_1     1
#define PORT_LINK_SPEED_GEN_2     2
#define PORT_LINK_SPEED_GEN_3     3
#define PORT_LINK_SPEED_GEN_4     4

STATIC CONST pcie_reg_op_t clarence_set_link_speed_gen_3[] =
{
    /* Link Speed */
  {PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_LINK_CONTROL2_LINK_STATUS2_REG), HWIO_PCIE_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED_BMSK, PORT_LINK_SPEED_GEN_3},
  {PCIE_REG_OP_DSB},
  {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t clarence_post_phy_pwr_up_dbi_init_seq[] =
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
 *               Port 0 init Configuration
 ******************************************************************************/
STATIC CONST pcie_reg_init_cfg_t clarence_port_0_phy_init_cfg[] =
{
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(clarence_port_0_phy_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(clarence_port_0_phy_start_seq),

  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(clarence_phy_delay_seq),

  /* Check if the PHY PLL is locked */
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(clarence_port_0_phy_poll_seq),

  /* Perform post power up sequence */
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(clarence_port_x1_lane_seq),
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(clarence_pcie_0_post_phy_pwr_up_init_seq),
  {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(clarence_post_phy_pwr_up_init_seq),

  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(clarence_set_link_speed_gen_3),
  {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(clarence_post_phy_pwr_up_dbi_init_seq),

  {PcieSeq_Stop}
};

/*******************************************************************************
 *               PCIe_0 config definitions
 ******************************************************************************/
static pcie_port_config_t clarence_port_0_cfg[] =
{
   {
      .hw_rp_index            = 0,
      .port_clk_cfg           = &clarence_pcie_clk_rp0,
      .port_gpio_cfg          = clarence_gpio_config_rp0,
      .port_mem_bases         = clarence_port_0_mem_region,
      .port_phy_init_cfg      = clarence_port_0_phy_init_cfg,
      .port_phy_deinit_cfg    = clarence_port_0_phy_de_init_cfg,
      .loopback_cfg           = &clarence_port_0_loopback_seq,
      .perst_pin              = CLARENCE_RC_0_GPIO_PCIE_RESET,
      .iommu_cfg              = "PCIE0",
      .pmic_cfg               = &clarence_port_0_pmic_cfg,
      .aspm                   = aspm_l1_ena_l0s_ena,
   },
};


/*******************************************************************************
 *               Clarence port configurations for public
 ******************************************************************************/
pcie_port_options_config_t clarence_target_port_options[] = 
{
   {
      .port_config_name = "P0x1Gen3",
      .exclusive_key = STR_ID('x', '1', 'G', '3'),
      .default_enable = 1,   // No HW conditional, so enable it by default
      .config_select_condition = NULL,
      .ports_config_cnt = ARRAY_LENGTH(clarence_port_0_cfg),
      .ports_config_list = clarence_port_0_cfg,
   },

};

static mem_region_t clarence_target_common_mem_regions[] =
{
  {.pa=0, .sz=0},
};

#define TARGET_MAX_PORT_INDEX    1

#endif   /* __PCIE_TARGET_PORT_CONFIG_H__ */

