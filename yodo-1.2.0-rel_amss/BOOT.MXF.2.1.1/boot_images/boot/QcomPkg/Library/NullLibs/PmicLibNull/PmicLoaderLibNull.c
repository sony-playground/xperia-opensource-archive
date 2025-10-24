/** @file PmicLibNull.c
  
  Stub functions for PmicLib

  Copyright (c) 2014-2022, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/17/22   jt      Added pm_ldo_sw_mode
 10/24/17   ra      Adding TypeC header
 07/19/16   kpa     Added pm_schg_usb_get_typec_status
 06/20/16   kpa     Added pmic api stubs
 05/14/15   plc     Updated for latest API's needed for basetarget compilation
 10/03/14   al      Updated for compilation
 05/30/14   kedara  Initial revision

=============================================================================*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/



#include "pm.h"
#include "com_dtypes.h"
#include "pm_uefi.h"

#include "pm_gpio.h"
#include "pm_ibb.h"
#include "pm_lab.h"
#include "pm_wled.h"
#include "pm_lcdb.h"
#include "pm_pon.h"
#include "pm_app_haptics.h"
#include "pm_chg.h"
#include "pm_pbus.h"
#include "pm_pbs.h"
pm_err_flag_type pm_ldo_sw_mode(uint8 pmic_chip, uint8 ldo_peripheral_index, pm_sw_mode_type mode)
{
   return PM_ERR_FLAG_SUCCESS; 
}

pm_err_flag_type pm_ldo_sw_enable(uint8 pmic_chip, uint8 ldo_peripheral_index, pm_on_off_type on_off, boolean wait_for_settle)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_smps_sw_enable(uint8 pmic_chip, uint8 smps_peripheral_index, pm_on_off_type on_off, boolean wait_for_settle)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_ldo_volt_level(uint8 pmic_chip, uint8 ldo_peripheral_index, pm_volt_level_type volt_level, boolean wait_for_settle)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_ibb_ibb_module_rdy(uint32 device_index, boolean ibb_rdy)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_ibb_config_ibb_ctrl(uint32 device_index, boolean en_module, boolean swire_rdy)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_ibb_get_ibb_status(uint32 device_index, pm_ibb_status_type *ibb_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_lab_config_current_sense(uint32 device_index, pm_lab_isense_type isense_tap, pm_lab_isense_type isense_gain)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_lab_config_pulse_skip_ctrl(uint32 device_index, uint32 ps_threshold, boolean select_ps_table, boolean select_digital_ps, boolean enable_ps)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_lab_lcd_amoled_sel(uint32 device_index, boolean en_amoled_mode)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_lab_lab_module_rdy(uint32 device_index, boolean lab_rdy)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_lab_ibb_rdy_en(uint32 device_index, boolean ibb_en_rdy)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_lab_get_lab_status(uint32 device_index, pm_lab_status_type *lab_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_wled_sel_ovp_thr(uint32 pmic_device_index, uint32 resource_index, pm_wled_ovp_threshold_type ovp_threshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_wled_sel_bst_ilimit(uint32 pmic_device_index, uint32 resource_index, pm_wled_bst_ilimit_type bst_ilimit_type)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_wled_set_fsw_ctrl(uint32 pmic_device_index, uint32 resource_index, uint32 fsw_khz)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_wled_set_led_duty_cycle(uint32 pmic_device_index, pm_wled_modulator_type modulator, uint16 duty_cycle)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_wled_enable_current_sink(uint32 pmic_device_index, pm_wled_led_type led_type)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_wled_enable_modulator(uint32 pmic_device_index, pm_wled_modulator_type modulator, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_wled_enable_module(uint32 pmic_device_index, uint32 resource_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_wled_en_sync(uint32 pmic_device_index, pm_wled_led_type led_type, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_wled_modulator_src_sel(uint32 pmic_device_index, pm_wled_modulator_type modulator, pm_wled_modulator_src_type src)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_lcdb_config_enable_ctrl(uint32 device_index, pm_lcdb_enable_ctl_type ctl_type, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_lcdb_set_output_volt(uint32 pmic_chip, int32 mv, int32 ncp, boolean symmetry)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_lcdb_vreg_ok(uint32 pmic_chip, boolean *vreg_ok)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_model_type pm_get_pmic_model(uint8 pmic_chip)
{
  return PMIC_IS_UNKNOWN;
}

pm_err_flag_type pm_app_haptics_vib_ctrl(pm_on_off_type state)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_smps_volt_level(uint8 pmic_chip, uint8 smps_peripheral_index, pm_volt_level_type volt_level, boolean settle)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_chg_get_vbatt(uint32 *batt_vol)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_chg_get_typec_status(pm_chg_typec_status_type *typec_status)
{
  return PM_ERR_FLAG_FAILURE;
}

pm_err_flag_type pm_chg_is_vbus_present(boolean *present)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_smps_volt_level_status(uint8 pmic_chip, uint8 smps_peripheral_index, pm_volt_level_type *volt_level)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_ldo_volt_level_status(uint8 pmic_chip, uint8 ldo_peripheral_index, pm_volt_level_type *volt_level)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_gpio_set_pull_sel(uint32 pmic_chip, pm_gpio_perph_index gpio, pm_gpio_pull_sel_type pull)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_pbus_logger(uint8 device_index, pm_pbus_data_type *pbus_log_data)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_pmic_dump_entry(uint8 *buf, uint64 offset, uint64 size)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_pbs_get_pon_reason_history(pm_pbs_pon_reason_history_data_type *pon_reason_history_ptr )
{
  return PM_ERR_FLAG_SUCCESS;
}