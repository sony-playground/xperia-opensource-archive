#ifndef __CORE_DRVR_CONFIG_H__
#define __CORE_DRVR_CONFIG_H__
/*
 *  pcie_cfg_types.h
 *
 *  Defines the Pcie Root Port configuration structures data layout
 */
/*============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
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


/*******************************************************************************
 *                    GPIO pin configuration types
 *******************************************************************************/
typedef enum
{
  NONE          = 0,
  MSM_GPIO      = 1,
  PMIC_GPIO     = 2,
  PMIC_MPP      = 3,
  DELAY         = 4      /* Delay in micro seconds b/w GPIO init sequence */
}pin_type_cfg_t;

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
   const char                *phy_pwr;
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

typedef struct
{
   const char                  *port_name;
   const pcie_clocks_cfg_t     *port_clk_cfg;
   const pcie_gpio_cfg_t       *port_gpio_cfg;
   const char                  *iommu_cfg;
   const pcie_pmic_config_t    *pmic_cfg;

}pcie_drvr_cfg_t;

/*******************************************************************************
 *    Optional Any end point device specific configuration attached to port
 *******************************************************************************/
typedef struct
{
   uint32  enum_delay_ms;
}pcie_port_dev_cfg_t;



#endif   /* __CORE_DRVR_CONFIG_H__ */

