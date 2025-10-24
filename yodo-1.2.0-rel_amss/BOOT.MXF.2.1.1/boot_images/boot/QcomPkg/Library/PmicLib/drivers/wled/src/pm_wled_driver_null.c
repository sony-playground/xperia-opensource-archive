/*! \file pm_wled_driver_null.c 
*  \n
*  \brief This file contains WLED peripheral driver NULL services.
*  \n
*  \n &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


$Header: $
$Author: $
$DateTime: $
when        who     what, where, why
--------    ---     ----------------------------------------------------------
========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_wled.h"
#include "pm_wled_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        STATIC VARIABLES 

===========================================================================*/

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void 
pm_wled_driver_init (pm_comm_info_type *comm_ptr, 
                     peripheral_info_type *peripheral_info, 
                     uint8 pmic_index)
{
  return;
}

pm_wled_data_type* 
pm_wled_get_data (uint8 pmic_index)
{
  return NULL;
}

uint8 
pm_wled_get_num_peripherals (uint8 pmic_index)
{
  return 0;
}

pm_err_flag_type 
pm_wled_sel_ovp_thr (uint32 pmic_device_index, 
                     uint32 resource_index, 
                     pm_wled_ovp_threshold_type ovp_threshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_sel_bst_ilimit (uint32 pmic_device_index, 
                        uint32 resource_index, 
                        pm_wled_bst_ilimit_type bst_ilimit_type)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_set_fsw_ctrl (uint32 pmic_device_index, 
                      uint32 resource_index, 
                      uint32 fsw_khz)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_set_led_duty_cycle (uint32 pmic_device_index, 
                            pm_wled_modulator_type modulator, 
                            uint16 duty_cycle)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_enable_current_sink (uint32 pmic_device_index, 
                             pm_wled_led_type led_type)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_enable_modulator (uint32 pmic_device_index, 
                          pm_wled_modulator_type modulator, 
                          boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_enable_module (uint32 pmic_device_index, 
                       uint32 resource_index, 
                       boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_en_sync (uint32 pmic_device_index, 
                 pm_wled_led_type led_type, 
                 boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_modulator_src_sel (uint32 pmic_device_index, 
                           pm_wled_modulator_type modulator, 
                           pm_wled_modulator_src_type src)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_irq_enable (uint32 pmic_device_index, 
                    pm_wled_irq_type irq, 
                    boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_set_led_full_scale_current (uint32 pmic_device_index, 
                                    pm_wled_led_type led_type, 
                                    uint32 current_microamp)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_get_status (uint32 pmic_device_index, 
                    pm_wled_status_type *wled_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_modulator_brightness_width(uint32 pmic_device_index,  
                                   pm_wled_modulator_type modulator, 
                                   pm_wled_modulator_brightness_width_type  width )
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_wled_led_modulator_src_sel (uint32 pmic_device_index, 
                               pm_wled_led_type led_type, 
                               pm_wled_modulator_type modulator)
{
  return PM_ERR_FLAG_SUCCESS;
}

