#ifndef __PM_SBL_BOOT__H__
#define __PM_SBL_BOOT__H__

/*! \file pm_sbl_boot.h
*  \n
*  \brief This header file contains enums and helper function declarations needed
*  \n during PMIC device initialization and during initial PMIC SBL settings configured
*  \n through the PDM auto-generated code.
*  \n
*  \n &copy; Copyright 2018, 2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/framework/inc/pm_sbl_boot.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/25/15   aab     Renamed pm_target_information_spmi_chnl_cfg() to pm_bus_init()
06/25/15   al      moving loader specific API to loader specific file
07/03/13   kt      Added Comment header for this file. 
 
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_err_flags.h"
#include "pm_boot.h"
#include "pm_version.h"
#include "bare_metal_info.h"
#include "pm_config_target.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/
typedef enum
{
  PM_ASWIRE_MAP_SEL_0,
  PM_ASWIRE_MAP_SEL_1,
  PM_ASWIRE_MAP_SEL_2,
  PM_ASWIRE_MAP_SEL_3,
  PM_ASWIRE_MAP_SEL_4,
  PM_ASWIRE_MAP_SEL_5,
  PM_ASWIRE_MAP_SEL_6,
  PM_ASWIRE_MAP_SEL_7,
  PM_ASWIRE_MAP_SEL_8,
  PM_ASWIRE_MAP_SEL_INVALID
}pm_aswire_map_sel_type;

typedef enum
{
  PM_ESWIRE_MAP_SEL_0,
  PM_ESWIRE_MAP_SEL_1,
  PM_ESWIRE_MAP_SEL_2,
  PM_ESWIRE_MAP_SEL_3,
  PM_ESWIRE_MAP_SEL_4,
  PM_ESWIRE_MAP_SEL_5,
  PM_ESWIRE_MAP_SEL_6,
  PM_ESWIRE_MAP_SEL_7,
  PM_ESWIRE_MAP_SEL_8,
  PM_ESWIRE_MAP_SEL_INVALID
}pm_eswire_map_sel_type;

typedef struct
{
  boolean   default_config_supported; /*feature support*/
  int32     elvss_default_volt; 
  uint32    elvdd_default_volt;
  uint32    oledb_default_volt;
  
}pm_oledb_default_cfg;

typedef struct
{
  uint8 aswire : 4;   // <7: 4>
  uint8 eswire : 4;   // <3: 0>
} pm_swire_data;

typedef enum
{
  PM_SWIRE_MAP_A,       //0
  PM_SWIRE_MAP_B,       //1
  PM_SWIRE_MAP_C,       //2
  PM_SWIRE_MAP_D,       //3
  PM_SWIRE_MAP_E,       //4
  PM_SWIRE_MAP_F,       //5
  PM_SWIRE_MAP_G,       //6
  PM_SWIRE_MAP_H,       //7
  PM_SWIRE_MAP_I,       //8
  PM_SWIRE_MAP_NUMBER,  //9
  PM_SWIRE_MAP_INVALID = PM_SWIRE_MAP_NUMBER,
} pm_swire_map_sel_type;

typedef struct
{
  boolean                  supported; /*feature support*/
  pm_swire_map_sel_type    swire_map; /*MAP_A by default*/
  uint8                    pmic_sid;  /*SID of PMIC for flag*/
  pm_register_address_type map_reg;  /*flag register*/    
  pm_oledb_default_cfg     oledb_default_volt_cfg;
}pm_swire_map_cfg;

typedef struct
{
  boolean supported; 
  uint8   cfg_value;
  uint8   pmic_sid;
  uint16  reg_addr;
}custom_inductor_cfg;


typedef struct
{
  boolean             verbose_uart_logging;  // Used to enable/disable verbose UART logging
  boolean             rfclk2_config_flag;    // FALSE: Default for all customer; TRUE: Disable RFCLK2
  pm_swire_map_cfg    swire_cfg;
  custom_inductor_cfg inductor_cfg;
}pm_sbl_specific_data_type;

typedef struct
{
  uint32                       timer_value_ms;
  pm_app_pon_reset_source_type reset_source_type;
  pm_param_config_enable_type  enable_config;
} pm_pon_s3_reset_timer_cfg_type;

typedef struct
{
  uint32  pmic_index;
  uint32  thresh_mv;
  uint32  hyst_mv;
  boolean enable;
} pm_pon_uvlo_ovlo_cfg_type;

typedef struct
{
  pm_pon_s3_reset_timer_cfg_type  s3_reset_timer_cfg;
  pm_pon_uvlo_ovlo_cfg_type       uvlo_cfg[PM_MAX_NUM_PMICS];
}pm_sbl_pon_specific_data_type;


/*===========================================================================

                        FUNCTION PROTOTYPES 

===========================================================================*/

unsigned int pm_clk_busy_wait (unsigned int mS);

pm_err_flag_type pm_boot_tcxo_config (void);

pm_err_flag_type pm_clk_tcxo_config(void);

pm_err_flag_type pm_pon_init(void);

/*! \brief This function configures the spmi channel for the PMIC peripherals.
 *  \param[in] .
 *
 *  \return Error flag.
 *
 *  <b>Dependencies</b>
 *  \li pm_processor_init_comms() .
 */ 
pm_err_flag_type pm_bus_init(void);

#endif // __PM_SBL_BOOT__H__
