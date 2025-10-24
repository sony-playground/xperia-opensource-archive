/*! \file
*  
*  \brief  pm_chg_null.c
*  \details Implementation file for charger API which is able to be used outside PMIC code.
*    
*  &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
29/07/22   xp      Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_chg.h"
#include "pm_scpq_typec.h"
#include "pm_scpq_usb.h"
#include "pm_scpq_chgr.h"
#include "pm_scpq_chgr2.h"
#include "pm_scpq_dcdc.h"
#include "pm_scpq_driver.h"
#include "pm_qbg_driver.h"
#include "pm_schg_typec.h"
#include "pm_schg_usb.h"
#include "pm_schg_chgr.h"
#include "pm_schg_dcdc.h"
#include "pm_schg_driver.h"
#include "pm_qbg.h"
#include "pm_app_chg.h"
#include "pm_bmd.h"
#include "pm_log_utils.h"
#include "CoreVerify.h"
#include "pm_version.h"
#include "pm_sdam.h"
#include "adc.h"


pm_err_flag_type 
pm_chg_get_primary_charger_pmic_index(uint32 *pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  static pm_dt_charger_config *charger_dt_config = NULL;
  
  if(NULL == pmic_index)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(NULL == charger_dt_config)
  {
    charger_dt_config = (pm_dt_charger_config*)pm_dt_get_node(PMIC_DT_NODE_PM_CHARGER);
    CORE_VERIFY_PTR(charger_dt_config);
  }

  if (charger_dt_config != NULL)
  {
    *pmic_index = charger_dt_config->charger_pmic_index;
    err_flag = (*pmic_index > PM_MAX_NUM_PMICS)? PM_ERR_FLAG_FAILURE : PM_ERR_FLAG_SUCCESS;
  }
  else
  {  
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  return err_flag;
}


pm_err_flag_type 
pm_chg_is_vbus_present(boolean* present)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}


pm_err_flag_type 
pm_chg_is_charging_ongoing(boolean* charging)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type 
pm_chg_enable_usb_charging(boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type 
pm_chg_enable_wireless_charging(boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}


pm_err_flag_type 
pm_chg_is_battery_present(boolean* present)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type 
pm_chg_get_charger_port_type(pm_chg_charger_port_type* charger_type)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type 
pm_chg_get_vbatt(uint32* voltage_in_mv)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}


pm_err_flag_type 
pm_chg_get_ibatt(int32* current_in_ma)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type 
pm_chg_get_battery_ocv(uint32* voltage_in_mv)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}


pm_err_flag_type 
pm_chg_typec_get_port_role(pm_chg_typec_port_role_type* role)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type 
pm_chg_get_typec_status(pm_chg_typec_status_type* typec_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}

pm_err_flag_type
pm_chg_get_power_path(pm_chg_power_path_type* power_path)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}
  
pm_err_flag_type pm_chg_is_2s_batt(boolean* battery_type_is_2s)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  return err_flag;
}


