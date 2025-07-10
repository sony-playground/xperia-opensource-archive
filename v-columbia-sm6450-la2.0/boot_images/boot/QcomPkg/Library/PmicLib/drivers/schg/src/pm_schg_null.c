/*! \file
*
*  \brief  pm_schg_null.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2021-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    -------------------------------------------------------------
=============================================================================== */

/*=============================================================================

                    INCLUDE FILES

===============================================================================*/
#include "pm_schg_driver.h"
#include "pm_schg_usb.h"
#include "pm_schg_chgr.h"
#include "pm_schg_typec.h"
#include "pm_schg_dcdc.h"
#include "pm_schg_batif.h"
#include "pm_schg_misc.h"

/*===========================================================================
                      MACRO DECLARATIONS
===========================================================================*/

pm_err_flag_type pm_schg_usb_get_typec_vbus_status(uint32 pmic_index, boolean *vbus_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_get_chgr_status(uint32 pmic_index, pm_schg_chgr_status_type *schg_chgr_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_enable_charging(uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_get_apsd_result_status(uint32 pmic_index, pm_chg_charger_port_type *apsd_result)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_typec_get_port_role(uint32 pmic_index, pm_chg_typec_port_role_type *port_role)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_get_typec_status(uint32 pmic_index, pm_chg_typec_status_type *typec_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_dcdc_get_power_path_status(uint32 pmic_index, pm_schg_dcdc_power_path_status *power_path_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_set_float_volt(uint32 pmic_index, uint32 float_volt_mv)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_dcdc_configure_vsysmin(uint32 pmic_index, uint32 vsysmin_mv)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_set_charge_current(uint32 pmic_index, pm_schg_chgr_current_type charge_current_type, uint32 current)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_set_usbin_suspend(uint32 pmic_index, boolean set_value)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_typec_get_dam_connect_sts(uint32 pmic_index, boolean *ConnectSts)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_dcdc_get_icl_status(uint32 pmic_index, pm_schg_dcdc_icl_status_type *icl_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_configure_usbin_icl_options(uint32 pmic_index, pm_schg_usb_icl_options_type icl_options, boolean set_value)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_enable_icl_override_after_apsd(uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_set_usbin_current_limit_cfg(uint32 pmic_index, uint32 usbin_current_limit)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_get_apsd_status(uint32 pmic_index, pm_schg_usb_apsd_status_type apsd_status_type, boolean *result)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_aicl_options_cfg(uint32 pmic_index, pm_schg_usb_aicl_cfg_type aicl_cfg_type, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_batif_cfg_batt_missing_src(uint32 pmic_index, pm_schg_batif_bat_miss_src_cfg_type bat_miss_cfg, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_set_jeita_threshold_value(uint32 pmic_index, pm_schg_chgr_jeita_threshold_type threshold_type, uint32 jeita_threshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_get_jeita_threshold_value(uint32 pmic_index, pm_schg_chgr_jeita_threshold_type threshold_type, uint16* jeita_threshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_jeita_en_cfg(uint32 pmic_index, pm_schg_chgr_jeita_cfg_type jeita_cfg_type, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_typec_en_chg_on_dam_snk(uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_aicl_cmd(uint32 device_index, pm_schg_misc_aicl_cmd_type cmd)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_batif_set_adc_internal_pull_up(uint32 device_index, pm_schg_batif_adc_pull_up_type pull_up_type,pm_schg_batif_adc_pull_up_res_type resistance)
{
	return PM_ERR_FLAG_SUCCESS;	
}
