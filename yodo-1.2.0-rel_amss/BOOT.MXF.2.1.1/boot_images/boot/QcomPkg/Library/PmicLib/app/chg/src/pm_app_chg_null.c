/*! \file
*  
*  \brief  pm_app_chg_null.c
*  \details Implementation file for charger stub for some images doens need
*           charging. For example: Ramdump and JtagProgrammer
*  &copy; Copyright 2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/12/21   zxz     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_app_chg.h"
#include "pm_chg.h"
#include "pm_target_information.h"
#include "CoreVerify.h"
#include "pm_dt_parser.h"

pm_err_flag_type 
pm_chg_get_pmic_index(uint32 *pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  static pm_dt_charger_config *charger_dt_config  = NULL;
  
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


// As a Workaround for Puhi/PM8350B reverse boost OCP issue
// This change is to limit IBAT to <4A and IOTG to <3A.
pm_err_flag_type 
pm_app_chg_trim_otg_offset_and_gain(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}

pm_err_flag_type 
pm_app_chg_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}

// This function should be called if charging taking place. internall use only
static pm_err_flag_type 
pm_app_chg_output_charging_status(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}


pm_err_flag_type 
pm_app_chg_check_weak_battery_status(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}

pm_err_flag_type 
pm_app_chg_configure_usb_icl(uint32 icl_ma)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}


pm_err_flag_type 
pm_app_chg_battery_uv_oc_detection()
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}

pm_err_flag_type 
pm_app_chg_is_debug_board_present(boolean *present)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}

pm_err_flag_type
pm_app_chg_enable_charger_wdog(boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}

pm_err_flag_type 
pm_app_chg_dbc_condition_check(boolean* status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}


pm_err_flag_type
pm_app_chg_dead_battery_charging(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}

