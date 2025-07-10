#ifndef __PCIE_ROOT_PORT_CONFIG_H__
#define __PCIE_ROOT_PORT_CONFIG_H__
/*
 *  pcie_cfg_types.h
 *
 *  Defines the Pcie Root Port configuration structures data layout
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   10/20/20   Yg      Moved old lib implementation to new design/interface

*/
/*============================================================================
         Copyright (c) 2020 - 2021 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
============================================================================*/

#include "com_dtypes.h"
#include <Uefi.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFITlmm.h>
#include <Protocol/EFIChipInfo.h>
#include <api/systemdrivers/icbarb.h>
#include "HALhwio.h"
#include "pcie_dtypes.h"


#define PCIE_INVALID_REG_VAL   0xFFFFFFFFUL

#define ARRAY_LENGTH(a)                     (sizeof(a) / sizeof((a)[0]))
#define PCIE_CLASS_CODE_BRIDGE_DEVICE       (0x06000000)
#define PCIE_SUBCLASS_CODE_PCI_2_PCI_BRIDGE (0x00040000)

/*******************************************************************************
 *     Config structure design:
 *
 * Level 0 : pcie_target_config_t
 * 
 *  contains multiple configurations for a target SOC, which can be filtered
 *  based on chip ID/family/platform, either by specific combo or a wild card
 *  search
 *
 * Output : pcie_port_options_config_t (target_ports_list)
 *
 *   eg: PcieMakenaTargetConfig can contain configurations for 
 *     Makena, Rumi (specific args Makena family + Rumi platform)
 *     Makena family (wildcard that applies to all Makena platforms unless a spcific
 *                    config is available)
 *
 * Fn: pcie_target_config_t (chip id, family, platform) => pcie_port_options_config_t
 *  eg: PcieMakenaTargetConfig (CDP/MTP) => target_port_configurations
 *
 * Level 1 : pcie_port_options_config_t
 *
 *    Contains lists of various combinations each port can have. This can be
 *    filtered using a config string which can pick a specific port config like
 *    2 lane/4 lane config. Since there could be multiple ports involved in each
 *    config, a unique exclusive key is used to exclude some configuration combo.
 *    Multiple configurations can be picked as long as they don't have clash in
 *    the exclusive key.
 *
 *  Output : pcie_port_config_t (ports_config_list)
 *
 *    eg: target_port_configurations can contain configurations for ports, 
 *        0,1,2A,2B,3A,3B,4. 2A can be x4 in which case 2B won't be available
 *
 *  Fn: pcie_port_options_config_t (multiple config strings) => pcie_port_config_t
 *    eg: target_port_configurations ("2A_x4_2B_NA") => port_2A_x4_cfg
 *        target_port_configurations ("3A_x2_3B_x2") => port_3A_x2_3B_x2_cfg
 *        target_port_configurations ("4x1") => port_4_cfg
 *    All above can be enabled together since the exclusive key between them
 *    don't match
 *
 * Level 2 : pcie_port_config_t
 *
 *     Contains all the relevant configurations for the Controller/Phy
 *
 *******************************************************************************/

/* For any config structure changes bump up the version number.  The change should
 * be backward/forward compatible so that old code should work with new data
 * and new code should be able to work with old data.
 *
 * Name the version macro which can identify the specific config change, which
 * would help code check for that specific version before it makes use of that
 * specific modification/addition */
#define PCIE_DATA_CONFIG_INITIAL_VER                                 0x010000

/*******************************************************************************
 * Document the version changes here in concise detail for reference.
 *  v 1.0 : First version of configuration
 *  
 *******************************************************************************/

/* Assign the version macro to the latest version declared above */
#define PCIE_CONFIG_DATA_VERSION      PCIE_DATA_CONFIG_INITIAL_VER

/* Chip, platform selection wildcards */
#define PCIE_TARGET_CHIP_ID_IGNORE       0xFFFFFFFFUL
#define PCIE_TARGET_CHIP_FAMILY_IGNORE   0xFFFFFFFFUL
#define PCIE_TARGET_PLATFORM_IGNORE      0xFFFFFFFFUL

/*******************************************************************************
 *    Type enums
 *******************************************************************************/

typedef enum
{
   PCIE_REG_OP_NOP       = 0,
   PCIE_REG_OP_DELAY     = 1,
   PCIE_REG_OP_WRITE     = 2,
   PCIE_REG_OP_RMW       = 3,
   PCIE_REG_OP_DSB       = 4,
   PCIE_REG_OP_POLL      = 5,
   PCIE_REG_OP_SET_GPIO  = 6,

   PCIE_REG_OP_STOP      = 0xFFFFFFFF,
}pcie_reg_operation;

typedef enum
{
  NONE          = 0,
  MSM_GPIO      = 1,
  PMIC_GPIO     = 2,
  PMIC_MPP      = 3,
  DELAY         = 4      /* Delay in micro seconds b/w GPIO init sequence */
}pin_type_cfg_t;

typedef enum
{
  PcieQcSoCVer_All   = 0x00000000,
  PcieQcSoCVer_1     = 0x00010000,
  PcieQcSoCVer_2     = 0x00020000,
  PcieQcSoCVer_3     = 0x00030000,
  PcieQcSoCVer_4     = 0x00040000,

  PcieSeq_Stop       = 0xFFFFFFFF, /* STOP sequence */
}pcie_soc_version_number;

typedef enum
{
  aspm_l1_dis_l0s_dis    = 0,    /* L1 & L0s disable */
  aspm_l1_dis_l0s_ena    = 1,    /* L1 disable & L0s enable */
  aspm_l1_ena_l0s_dis    = 2,    /* L1 enable & L0s disable */
  aspm_l1_ena_l0s_ena    = 3     /* L1 & L0s enable */
}pcie_aspm_support;

typedef enum
{
  LTR_TH_SCALE_1ns      = 0x00,  /*         1 ns units */
  LTR_TH_SCALE_32ns     = 0x01,  /*        32 ns units */
  LTR_TH_SCALE_1us      = 0x02,  /*      1024 ns units */
  LTR_TH_SCALE_32us     = 0x03,  /*     32768 ns units */
  LTR_TH_SCALE_1ms      = 0x04,  /*   1048576 ns units */
  LTR_TH_SCALE_32ms     = 0x05   /*  33554432 ns units */
}ltr_threshold_scale_t;

/*******************************************************************************
 *    Memory region types
 *******************************************************************************/
typedef enum
{
  axi_reg                = 0,
  ahb_reg                = 1,
  tcsr_reg               = 2,
  gcc_reg                = 3,
  tunnel_router_reg      = 4,

  max_mem_reg            = 5 
}mem_reg_index;

typedef struct
{
  const uint64_t             pa;
  const uint64_t             sz;
}mem_region_t;

/*******************************************************************************
 *         PCIe DBI Register mapping per core
 *
 *  Used to manage differences of register offsets across cores
 *******************************************************************************/
typedef enum {
   PCIE_TARGET_REG_MAP_COUNT = 0,
} pcie_target_reg_map_t;

/*******************************************************************************
 *                  HW Register initialization types
 *******************************************************************************/

/* Register initialization config which can do various reg operations */
typedef struct
{
  const pcie_reg_operation   opflag;
  const uint32_t             offset;
  const uint32_t             mask;
  const uint32_t             val;
} pcie_reg_op_t;


/* Register value parameters to be written unconditionally */
typedef struct
{
  const uint32_t             offset;
  const uint32_t             val;
} pcie_reg_write_val_t;

/* Specify a field level parameter */
typedef struct
{
   const uint32_t*  reg_base_addr;
   const uint32_t   reg_offset;
   const uint32_t   fld_shift;
   const uint32_t   fld_mask;
   const uint32_t   fld_val;
}pcie_reg_field_val_t;

typedef enum
{
   PCIE_SEQ_NONE       = 0,
   PCIE_REG_WRITE_SEQ  = 1,
   PCIE_REG_OP_SEQ     = 2,
   PCIE_FIELD_VAL_SEQ  = 3,

   PCIE_REG_SEQ_MAX    = 4,
}pcie_seq_type_t;

typedef union
{
   const pcie_reg_field_val_t    *reg_field_val_seq;
   const pcie_reg_write_val_t    *reg_write_val_seq;
   const pcie_reg_op_t           *reg_op_seq;
}pcie_seq_spec_t;

typedef struct
{
   const EFIChipInfoVersionType       version;
   const mem_reg_index                mem_rgn_idx;
   const pcie_seq_type_t              seq_type;
   const pcie_seq_spec_t              seq_spec;
} pcie_reg_init_cfg_t;

/*******************************************************************************
 *                    GPIO pin configuration types
 *******************************************************************************/
typedef struct
{
   const uint32_t             gpio_num;
   const uint32_t             func_sel;
   const uint32_t             direction;
   const uint32_t             pull;
   const uint32_t             drive_strength;
   const TLMM_ValueType       value;
}tlmm_gpio_cfg_t;

typedef struct
{
   const uint32_t                       pmic_index;
   const EFI_PM_GPIO_PERIPH_INDEX       gpio_num;
   const EFI_PM_GPIO_OUT_BUF_CFG_TYPE   buff_cfg;
   const EFI_PM_GPIO_VOLT_SRC_TYPE      vsrc;
   const EFI_PM_GPIO_SRC_CFG_TYPE       src_cfg;
   const EFI_PM_GPIO_OUT_DRV_STR_TYPE   drv_str;
   const EFI_PM_GPIO_LEVEL_TYPE         gpio_level;
}pmic_gpio_cfg_t;

typedef union
{
   const tlmm_gpio_cfg_t          tlmm;
   const pmic_gpio_cfg_t          pmic;
   const uint32_t                 delay_us;
}pcie_gpio_pin_cfg_t;

typedef struct
{
   const pin_type_cfg_t       cfg_type;
   const pcie_gpio_pin_cfg_t  pcie_pin;
}pcie_gpio_cfg_t;

/*******************************************************************************
 *                    Clock configurations
 *******************************************************************************/
typedef struct
{
   const char                     *npa_client_name;
   const ICBArb_MasterSlaveType   *ms_list;
   const uint32_t                  ms_size;
   const ICBArb_RequestType       *req_list;
   const uint32_t                  req_size;
}pcieIcbClkBW_t;

typedef struct
{
   const char           *name;
   const uint32_t        freq;
}clk_freq_cfg_t;

typedef struct
{
   const char              *clk_name;
   const uint32_t           en_mux_val;
   const uint32_t           dis_mux_val;
}pcie_clk_mux_cfg_t;

typedef struct
{
   const char                *clk_pwr;
   const char               **clk_reset;
   const char               **core_clks;
   const pcie_clk_mux_cfg_t  *clk_mux;
   const clk_freq_cfg_t      *clk_freq;
   const pcieIcbClkBW_t      *icb_bw;
}pcie_clocks_cfg_t;

/*******************************************************************************
 *    Pmic power resources to track per port
 *******************************************************************************/
typedef struct
{
   const char*       node_id;
}pcie_pmic_config_t;

/*******************************************************************************
 *    Optional resources context for drivers private handle/data storage
 *******************************************************************************/
typedef struct
{
   // Count of handles required per port. Pick the max of pcieIcbClkBW_t
   // count among all the ports
   npa_client_handle    icb_handles[1];

   /* Initialize only once for the port */
   boolean              gpio_initialized;
   boolean              smmu_initialized;
   boolean              ldo_on;

   npa_client_handle    pmic_handle;
}pcie_resources_ctxt_t;

/*******************************************************************************
 *    Optional Any end point device specific configuration attached to port
 *******************************************************************************/
typedef struct
{
   uint32  enum_delay_ms;
}pcie_port_dev_cfg_t;

/*******************************************************************************
 *        Loopback
 *******************************************************************************/
typedef struct
{
   const pcie_reg_init_cfg_t   *loopback_enable_cfg;
   const pcie_reg_init_cfg_t   *loopback_disable_cfg;
}pcie_loopback_cfg_t;

/*******************************************************************************
 *        PCIe Port specific configuration
 *******************************************************************************/
typedef struct
{
   uint32_t                     hw_rp_index;
   const char                  *port_name;
   const pcie_clocks_cfg_t     *port_clk_cfg;
   const pcie_gpio_cfg_t       *port_gpio_cfg;
   const mem_region_t          *port_mem_bases;
   const pcie_reg_init_cfg_t   *port_phy_init_cfg;
   const pcie_reg_init_cfg_t   *port_phy_deinit_cfg;
   const pcie_loopback_cfg_t   *loopback_cfg;
   const char                  *iommu_cfg;
   const pcie_pmic_config_t    *pmic_cfg;
   const pcie_port_dev_cfg_t   *port_ep_settings;
   const pcie_aspm_support      aspm;

   const uint32                 ltr_threshold_val;
   const ltr_threshold_scale_t  ltr_threshold_scale;
   const uint32_t               entp_mgmt_idx;
   const uint32_t               perst_pin;
   const boolean                io_coherency_en;
   const boolean                plim_en;
   const boolean                is_usb4_tunneled;
}pcie_port_config_t;

/*******************************************************************************
 *          PCIe Port related options
 *******************************************************************************/
typedef struct
{
   const char*                 port_config_name;
   const uint32_t              exclusive_key;   // Non zero exclusive key
   const uint32_t              default_enable; // Set only based on the default port option setting
   const pcie_reg_field_val_t *config_select_condition; // value to set/check to enable this port
   const uint32_t              ports_config_cnt;
   const pcie_port_config_t   *ports_config_list;
}pcie_port_options_config_t;

/*******************************************************************************
 *      Target configuration
 *******************************************************************************/
typedef struct
{
   const uint32_t           config_data_version;
   const uint32_t           target_chip_id;
   const uint32_t           target_chip_family;
   const uint32_t           target_platform_type;

   const uint32_t           max_port_index;   // Index of the last port in SOC
   const uint32_t          *entp_mgmt_addr;
   const mem_region_t      *common_mem_regions;

   const uint32_t           target_port_option_cnt;
   const pcie_port_options_config_t *target_port_option_list;

}pcie_target_config_t;


#endif   /* __PCIE_ROOT_PORT_CONFIG_H__ */

/*

  pcie_target_config_t                  pcie_port_options_config_t                          pcie_port_config_t

    MakenaChipId
    MakenaFamily
    Rumi
    MakenaRumiPortsList --------------> 2A_x4, 2A_x4_config_list
                                        2A_x2_2B_x2, 2A_x2_2B_x2_config_list
                                        3A_x4, 3A_x2_3B_x2_config_list
                                        3A_x2_3B_x2, 3A_x2_3B_x2_config_list



  pcie_target_config_t                  pcie_port_options_config_t                         pcie_port_config_t
  ----------------------               ----------------------------                      ---------------------
    MakenaChipId
    MakenaFamily
    CDP
    MakenaTargetPortsList --------->  En    2A_x4, 2A_x4_config_list -------------------> [2A_x4_port_config]
                                      Dis   2A_x2_2B_x2, 2A_x2_2B_x2_config_list
                                      Dis   3A_x4, 3A_x2_3B_x2_config_list
                                      En    3A_x2_3B_x2, 3A_x2_3B_x2_config_list ------> [3A_x2_port_config, 3B_x2_port_config]
                                      En    4x1, 4x1_config_list  ----------------------> [4x1_port_config]


*/

