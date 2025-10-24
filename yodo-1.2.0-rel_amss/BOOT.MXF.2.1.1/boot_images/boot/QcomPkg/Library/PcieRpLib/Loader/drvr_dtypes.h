#ifndef __LOADER_DRVR_CONFIG_H__
#define __LOADER_DRVR_CONFIG_H__
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
   const uint16_t             gpio_num;
   const uint16_t             value;
   const uint8_t             func_sel;
   const uint8_t             direction;
   const uint8_t             pull;
   const uint8_t             drive_strength;
}tlmm_gpio_cfg_t;

typedef union
{
   const tlmm_gpio_cfg_t          tlmm;
   const uint32_t                 delay_us;
}pcie_pin_cfg_t;

typedef struct
{
   const pin_type_cfg_t       cfg_type;
   const pcie_pin_cfg_t       pcie_pin;
}pcie_gpio_cfg_t;

/*******************************************************************************
 *                    Clock configurations
 *******************************************************************************/
typedef struct
{
   const uint8_t                clk_idx;
}pcie_clocks_cfg_t;

/*******************************************************************************
 *    Optional resources context for drivers private handle/data storage
 *******************************************************************************/
typedef struct
{
   const uint8   pmic_chip;
   const uint8   ldo_num;
}pcie_ldo_config_t;

typedef struct{
   const uint32               num_ldos;
   const pcie_ldo_config_t*   ldo_cfg;
}pcie_pwr_rails_config_t;

typedef struct
{
   /* Initialize only once for the port */
   boolean              gpio_initialized;
   boolean              ldo_on;

}pcie_resources_ctxt_t;

/*******************************************************************************
 *    Optional Any end point device specific configuration attached to port
 *******************************************************************************/
typedef struct
{
//   const char                      *port_name;
   const pcie_clocks_cfg_t         *port_clk_cfg;
   const pcie_gpio_cfg_t           *port_gpio_cfg;
   const pcie_pwr_rails_config_t   *pwr_rails_cfg;

}pcie_drvr_cfg_t;



#endif   /* __LOADER_DRVR_CONFIG_H__ */

