/*! \file
*  
*  \brief  pm_app_haptics.c
*  \details Implementation file for rgb led resourece type.
*    
*  &copy; Copyright 2017-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.0/QcomPkg/Library/PmicLib/app/haptics/src/pm_app_haptics.c#2 $
$Author: pwbldsvc $
$DateTime: 2021/12/15 06:23:30 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
04/24/19   pxm     Add haptics vdd control into app API.
04/26/17   aab     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_haptics.h"
#include "pm_app_haptics.h"
#include "pm_target_information.h"
#include "pm_gpio.h"
#include "pm_device.h"
#include "pm_haptics_cfg_driver.h"
#include "pm_vib_driver.h"
#define PM_VIB_ON            3000
#define PM_VIB_OFF           1200

static pm_err_flag_type haptics_vdd_control(pm_haptics_app_config* config, pm_on_off_type on)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if((NULL == config) || (on >= PM_INVALID))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(FALSE == config->is_external_boost_vdd)
  {
    return err_flag; // do nothing if haptics VDD is connected to VPH_PWR
  }

  // For targets like Kona, we need to configure GPIO05B to output HIGH to enable external boost.
  // Output high to enable external boost
  // Output low to disable external boost to avoid leakage
  if(PM_ON == on)
  {
    err_flag |= pm_gpio_enable(config->haptics_gpio_pmic, config->gpio, TRUE); // in case peripheral hasn't been enabled
    err_flag |= pm_gpio_cfg_mode(config->haptics_gpio_pmic, config->gpio, PM_GPIO_DIG_OUT); // configure as Digital Output mode
    err_flag |= pm_gpio_set_out_buf_cfg(config->haptics_gpio_pmic, config->gpio, PM_GPIO_OUT_BUF_CFG_CMOS); // configure output buf to CMOS
    err_flag |= pm_gpio_set_out_src_cfg(config->haptics_gpio_pmic, config->gpio, PM_GPIO_SRC_GND);
    err_flag |= pm_gpio_set_output_level(config->haptics_gpio_pmic, config->gpio, PM_GPIO_LEVEL_HIGH);
  }
  else
  {
    err_flag |= pm_gpio_set_output_level(config->haptics_gpio_pmic, config->gpio, PM_GPIO_LEVEL_LOW);
  }

  return err_flag;
}

pm_err_flag_type  
pm_app_haptics_vib_ctrl(pm_on_off_type state) 
{ 
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  pm_haptics_vibrate_type vib_type = PM_HAPTICS_INVALID;
  uint16 pm_vib_drv_volt = 0;
  boolean enable = FALSE;
  uint32 pmic_index = 0;
  pm_haptics_app_config* haptics_config_ptr = NULL;
  
  if( (pm_is_target_pre_silicon() == TRUE) && (pm_is_pmic_present(PMIC_A) == FALSE) )
  {    
    return err_flag = PM_ERR_FLAG_SUCCESS;
  }

  if((state != PM_ON) && (state != PM_OFF))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER; 
  }

  haptics_config_ptr = (pm_haptics_app_config*)pm_target_information_get_specific_info(PM_PROP_HAPTICS_APP_CONFIG);
  if(NULL == haptics_config_ptr)
  {
    return PM_ERR_FLAG_INVALID_CONFIG_SETTING; 
  }

  pmic_index = haptics_config_ptr->haptics_pmic;

  pm_haptics_data_type *haptics_ptr = pm_haptics_get_data(pmic_index);
  pm_vib_data_type *vib_ptr = pm_vib_get_data(pmic_index);
  if(haptics_ptr != NULL)
  {
    vib_type = (PM_ON == state) ? PM_HAPTICS_PLAY : PM_HAPTICS_PAUSE;
    
    err_flag |= haptics_vdd_control(haptics_config_ptr, state);
    err_flag |= pm_haptics_play(pmic_index, vib_type);
    err_flag |= pm_haptics_enable(pmic_index, state);
  }
  else if(vib_ptr != NULL)
  { 
    pm_vib_drv_volt = (state == PM_ON) ? PM_VIB_ON : PM_VIB_OFF;
    enable = (state == PM_ON) ? TRUE : FALSE;
    err_flag |= pm_vib_set_volt(pmic_index, PM_VIB__1, pm_vib_drv_volt);
    err_flag |= pm_vib_enable(pmic_index, PM_VIB__1, PM_VIB_MODE__MANUAL, enable);
  } 
  
  return err_flag; 
}

