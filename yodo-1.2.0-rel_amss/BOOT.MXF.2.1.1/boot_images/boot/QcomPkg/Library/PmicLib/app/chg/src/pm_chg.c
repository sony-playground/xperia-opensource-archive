/*! \file
*  
*  \brief  pm_chg.c
*  \details Implementation file for charger API which is able to be used outside PMIC code.
*    
*  &copy; Copyright 2020-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
01/06/20   xp      Creation
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


#define QBG_VBAT_NUMR (194637)   //LSB value 194.637uV
#define QBG_VBATT_DENR (1000)

#define QBG_IBAT_NUMR (305185)  //LSB value is 305.185uA
#define QBG_IBATT_DENR (1000)


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
  }

  if(charger_dt_config != NULL)
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
  uint32 pmic_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL == present)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  // Check and use the available charger driver
  if(NULL != pm_scpq_get_data(pmic_index))
  {
    err_flag = pm_scpq_usb_get_typec_vbus_status(pmic_index, present);
  }
  else if(NULL != pm_schg_get_data(pmic_index))
  {
    err_flag = pm_schg_usb_get_typec_vbus_status(pmic_index, present);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


pm_err_flag_type 
pm_chg_is_charging_ongoing(boolean* charging)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL == charging)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  // Check and use the available charger driver
  if(NULL != pm_scpq_get_data(pmic_index))
  {
    pm_scpq_chgr_status_type scpq_chgr_status;
    err_flag = pm_scpq_chgr_get_chgr_status(pmic_index, &scpq_chgr_status);
    if(PM_ERR_FLAG_SUCCESS == err_flag)
    {
      // valid power source only means VBUS or wireless charger is connected.
      // We still need to read if charging is disabled/inhibit or not.
      *charging = scpq_chgr_status.chg_en_status.charging_enable;
    }
  }
  else if(NULL != pm_schg_get_data(pmic_index))
  {
    pm_schg_chgr_status_type schg_chgr_status;
    err_flag = pm_schg_chgr_get_chgr_status(pmic_index, &schg_chgr_status);
    if(PM_ERR_FLAG_SUCCESS == err_flag)
    {
      // valid power source only means VBUS or wireless charger is connected.
      // We still need to read if charging is disabled/inhibit or not.
      *charging = schg_chgr_status.status_5.charging_enable;
    }
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}

pm_err_flag_type 
pm_chg_enable_usb_charging(boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  // Check and use the available charger driver
  if(NULL != pm_scpq_get_data(pmic_index))
  {
    err_flag = pm_scpq_chgr_enable_charging(pmic_index, enable);
  }
  else if(NULL != pm_schg_get_data(pmic_index))
  {
    err_flag = pm_schg_chgr_enable_charging(pmic_index, enable);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

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
  boolean battery_missing = TRUE;
  uint32 pmic_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL == present)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_bmd_get_battery_missing_rt_status(pmic_index, PM_BMD_BAT_MISS_STS_DEB, &battery_missing);
  if(PM_ERR_FLAG_SUCCESS == err_flag)
  {
    *present = battery_missing ? FALSE : TRUE;
  }

  return err_flag;
}

pm_err_flag_type 
pm_chg_get_charger_port_type(pm_chg_charger_port_type* charger_type)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL == charger_type)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  // Check and use the available charger driver
  if(NULL != pm_scpq_get_data(pmic_index))
  {
    err_flag = pm_scpq_usb_get_apsd_result_status(pmic_index, charger_type);
  }
  else if(NULL != pm_schg_get_data(pmic_index))
  {
    err_flag = pm_schg_usb_get_apsd_result_status(pmic_index, charger_type);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}

pm_err_flag_type 
pm_chg_get_vbatt(uint32* voltage_in_mv)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = PMIC_INDEX_MAX;
  adc_status_type adc_status = ADC_STATUS_SUCCESS;
  adc_result_type adc_vbat = {0};
  boolean battery_is_2s = FALSE;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL == voltage_in_mv)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_chg_is_2s_batt(&battery_is_2s);
    if(err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
    
    if(battery_is_2s)
    {
      // Get 2s battery S+ volt, sum of two cells voltage
      adc_status |= adc_read(ADC_INPUT_VBATT_2S, &adc_vbat);
    }
    else
    {
      adc_status |= adc_read(ADC_INPUT_VBATT, &adc_vbat);
    }

    if(adc_status != ADC_STATUS_SUCCESS)
    {
      pm_log_message("adc_read error: %d. %s %d", adc_status, __func__, __LINE__);
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    
    *voltage_in_mv = adc_vbat.microvolts / 1000;
  }

  return err_flag;
}

// Multiply the scale with 10 and then divided by 10.
static pm_err_flag_type pm_chg_get_ibat_scale_factor_10x(uint8 *scale)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 data = 0;

  if(NULL == scale)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  pm_dt_charger_config* charger_dt_config = (pm_dt_charger_config*)pm_dt_get_node(PMIC_DT_NODE_PM_CHARGER);
  CORE_VERIFY_PTR(charger_dt_config);

  *scale = 10;

  if(charger_dt_config->ibat_via_ext_sense)
  {
    // Get IBAT scale type
    pm_qbg_ext_rsns_scale_loc_type *scale_location = 
        (pm_qbg_ext_rsns_scale_loc_type*)pm_target_information_get_specific_info(PM_PROP_QBG_EXT_RSNS_SCALE_LOCATION);
    CORE_VERIFY_PTR(scale_location);
    
    err_flag = pm_sdam_mem_read(scale_location->pmic_index, scale_location->sdam_index, scale_location->mem_index, 1, &data);
    
    if(err_flag == PM_ERR_FLAG_SUCCESS)
    {
      if(data == PM_CHG_EXT_RSNS_SCALE_2X)
      {
        *scale = 20;
      }
      else if(data == PM_CHG_EXT_RSNS_SCALE_2P5X)
      {
        *scale = 25;
      }
    }
  }

  return err_flag;
}

pm_err_flag_type 
pm_chg_get_ibatt(int32* current_in_ma)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint16 data = 0;
  int64 temp = 0;
  uint32 pmic_index = PMIC_INDEX_MAX;
  uint8 scale = 10;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL == current_in_ma)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  //todo for now assume it is 10A, we should read the configure data to check if it support 20A or not.
  err_flag = pm_qbg_get_last_burst_avg_acc_data(pmic_index, PM_QBG_ACC2, &data);
  err_flag |= pm_chg_get_ibat_scale_factor_10x(&scale);
  if(PM_ERR_FLAG_SUCCESS == err_flag)
  {
    temp = (int64)((int16)data);
    // bit weight = QBG_IBAT_NUMR / QBG_IBATT_DENR, in the unit of uA. divide by 1000 to convert to mA
    // * scale / 10
    *current_in_ma = (temp * QBG_IBAT_NUMR * scale) / (QBG_IBATT_DENR * 1000 * 10);
  }

  return err_flag;
}

pm_err_flag_type 
pm_chg_get_battery_ocv(uint32* voltage_in_mv)
{
#define MIN_CELL_OCV   3000
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint16 data0 = 0, data1 = 0;
  pm_chg_battery_type battery_type = PM_CHG_BATT_TYPE_INVALID;
  pm_chg_2s_battery_option_type batt_2s_option = PM_CHG_DIS_VBAT_2S_MID; //mid disabled
  uint32 cell1_vbatt = MIN_CELL_OCV, cell2_vbatt = MIN_CELL_OCV;
  uint32 pmic_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL == voltage_in_mv)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else if(NULL != pm_qbg_get_data(pmic_index))
  {
    err_flag = pm_qbg_get_qbg_mode_ctl1_batt_opt(pmic_index, &battery_type);
    err_flag |= pm_qbg_get_qbg_mode_ctl3_batt_opt(pmic_index, &batt_2s_option);
    if(PM_ERR_FLAG_SUCCESS != err_flag)
    {
      pm_log_message("pon_ocv get batt opt failed");
      return err_flag;
    }
    
    err_flag = pm_qbg_get_pon_ocv_acc_data(pmic_index, PM_QBG_ACC0, &data0);
    
    if(PM_ERR_FLAG_SUCCESS != err_flag)
    {
      pm_log_message("pon_ocv get acc0 Failed");
      return err_flag;
    }
    
    //pon ocv data is in 2's complement, representing negative value if data > 0x7FFF for 1S
    //for 2S battery if there is no mid pin, this value will be > 0x7FFF
    if(data0 > 0x7FFF && battery_type == PM_CHG_1S_BATT_TYPE)
    {
      pm_log_message("pon_ocv acc0 invalid value");
      data0 = 0;
    }
      // bit weight = QBG_VBAT_NUMR / QBG_VBATT_DENR, in the unit of uV. divide by 1000 to convert to mV
    *voltage_in_mv = cell1_vbatt = (uint64)data0 * QBG_VBAT_NUMR / QBG_VBATT_DENR / 1000;
    if(cell1_vbatt < MIN_CELL_OCV)
    {
      *voltage_in_mv = cell1_vbatt = MIN_CELL_OCV;
    }
    
    if(battery_type == PM_CHG_1S_BATT_TYPE || batt_2s_option == PM_CHG_DIS_VBAT_2S_MID)
    {
      //voltage_in_mv is already calculated from ACC_data0
      return err_flag;
    }
    else
    {
      err_flag = pm_qbg_get_pon_ocv_acc_data(pmic_index, PM_QBG_ACC1, &data1);
      if(data1 > 0x7FFF)
      {
        pm_log_message("pon_ocv acc1 invalid value");
        data1 = 0;
      }
      cell2_vbatt = (uint64)data1 * QBG_VBAT_NUMR / QBG_VBATT_DENR / 1000;
      if(cell2_vbatt < MIN_CELL_OCV)
        cell2_vbatt = MIN_CELL_OCV;
      *voltage_in_mv = cell2_vbatt + cell1_vbatt;
    }
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


pm_err_flag_type 
pm_chg_typec_get_port_role(pm_chg_typec_port_role_type* role)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL == role)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  // Check and use the available charger driver
  if(NULL != pm_scpq_get_data(pmic_index))
  {
    err_flag = pm_scpq_usb_typec_get_port_role(pmic_index, role);
  }
  else if(NULL != pm_schg_get_data(pmic_index))
  {
    err_flag = pm_schg_usb_typec_get_port_role(pmic_index, role);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}

pm_err_flag_type 
pm_chg_get_typec_status(pm_chg_typec_status_type* typec_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL == typec_status)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  // Check and use the available charger driver
  if(NULL != pm_scpq_get_data(pmic_index))
  {
    err_flag = pm_scpq_usb_get_typec_status(pmic_index, typec_status);
  }
  else if(NULL != pm_schg_get_data(pmic_index))
  {
    err_flag = pm_schg_usb_get_typec_status(pmic_index, typec_status);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}

pm_err_flag_type
pm_chg_get_power_path(pm_chg_power_path_type* power_path)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = PMIC_INDEX_MAX;

  if(NULL == power_path)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  // Check and use the available charger driver
  if(NULL != pm_scpq_get_data(pmic_index))
  {
    pm_scpq_dcdc_power_path_status scpq_power_path_status = {0};
    err_flag = pm_scpq_dcdc_get_power_path_status(pmic_index, &scpq_power_path_status);
    *power_path = (pm_chg_power_path_type)scpq_power_path_status.power_path;
  }
  else if(NULL != pm_schg_get_data(pmic_index))
  {
    pm_schg_dcdc_power_path_status schg_power_path_status = {0};
    err_flag = pm_schg_dcdc_get_power_path_status(pmic_index, &schg_power_path_status);
    *power_path = (pm_chg_power_path_type)schg_power_path_status.power_path;
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  return err_flag;
}

pm_err_flag_type
pm_chg_is_2s_batt(boolean* battery_type_is_2s)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean is_2s_batt = FALSE;
  uint32 charger_index = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&charger_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag |= pm_scpq_chgr2_get_bat_2s_chg_cfg(charger_index, &is_2s_batt);
  }
  else
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  *battery_type_is_2s = is_2s_batt;
  
  return err_flag;
}

