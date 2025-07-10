/*! \file
*
*  \brief  pm_scpq_chgr.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2020-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    ----------------------------------------------------------
12/02/19    zzx    Initial revision
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_scpq_chgr.h"
#include "pm_scpq_driver.h"
#include "pm_utils.h"
#include "hw_module_type.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/

#define ADDRESS(x) (scpq_ptr->base_address + \
                    scpq_ptr->chgr_register->peripheral_offset + \
                    scpq_ptr->chgr_register->x)

#define SLAVE_ID   (scpq_ptr->comm_ptr->slave_id)

#define PM_SCPQ_FLOAT_VOLTAGE_STEP_CONSTANT           10
#define PM_SCPQ_JEITA_FLOAT_VOLTAGE_STEP_CONSTANT     10
#define PM_SCPQ_JEITA_CHARGE_CURRENT_STEP_CONSTANT    50
#define FLOAT_VOLTAGE_MIN 3600
/*===========================================================================
                        CONSTANTS
===========================================================================*/
#define VSYSMIN_CFG_COUNT 8
#define IPRE_CFG_COUNT 8
static uint32
vsys_min_vals[VSYSMIN_CFG_COUNT] = {2800, 3000, 3200, 3400, 4000, 4200, 4400, 4600};
static uint32
ipre_vals_h[IPRE_CFG_COUNT] = {100, 150, 200, 250, 300, 400, 500, 600};
static uint32
ipre_vals_p[IPRE_CFG_COUNT] = {250, 300, 350, 400, 450, 500, 550, 600};

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type pm_scpq_chgr_set_charge_current(uint32 pmic_index, pm_scpq_chgr_current_type charge_current_type, uint32 current_in_ma)
{
  pm_err_flag_type err_flag  = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  pm_register_data_type mask = 0;
  pm_register_address_type reg = 0;
  uint32 step_size = 0;
  uint32 max_value = 0;
  uint32 min_value = 0;
  uint8 idx = 0;

  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag =  PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (charge_current_type >= PM_SCPQ_CHGR_CURRENT_TYPE_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    switch (charge_current_type)
    {
    case PM_SCPQ_CHGR_PRE_CHARGE_CURRENT:
      reg = ADDRESS(ipre_cfg);
      mask = 0x07;  // BIT<2:0>
      if(scpq_ptr->charger_subtype == PM_HW_MODULE_CHARGER_SCPQ_P_CHGR)  //PM8350B(Puhi) -> SCPQ_P_CHGR_PERPH_SUBTYPE | 0x2605 = 0x80
      {
        idx = pm_utils_get_upper_idx(current_in_ma, ipre_vals_p, IPRE_CFG_COUNT);
      }
      else if(scpq_ptr->charger_subtype == PM_HW_MODULE_CHARGER_SCPQ_H_CHGR)  //PM7325B(Cortes) -> SCPQ_H_CHGR_PERPH_SUBTYPE | 0x2605 = 0x90
      {
        idx = pm_utils_get_upper_idx(current_in_ma, ipre_vals_h, IPRE_CFG_COUNT);
      }    
      err_flag = pm_comm_write_byte_mask(SLAVE_ID, reg, mask, idx);
      break;

    case PM_SCPQ_CHGR_FAST_CHARGE_CURRENT:
      reg = ADDRESS(ichg_cfg);
      mask = 0xFF;  // BIT<7:0>
      step_size = 50;
      max_value = 10000;  // max 10A for the case SMB is connected.
      min_value = 0;
      break;

    case PM_SCPQ_CHGR_TERMINATION_CURRENT:
      reg = ADDRESS(chg_term_cfg);
      mask = 0x07;   // BIT<2:0>
      step_size = 50;
      max_value = 450;
      min_value = 100;
      break;

    default:
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
      break;
    }

    if (current_in_ma < min_value)
    {
      current_in_ma = min_value;
    }
    else if (current_in_ma > max_value)
    {
      current_in_ma = max_value;
    }

    if(charge_current_type != PM_SCPQ_CHGR_PRE_CHARGE_CURRENT)
    { 
      /*rounding and getting corresponding register value*/
      data = ((current_in_ma - min_value) + (step_size / 2)) / step_size;
      err_flag = pm_comm_write_byte_mask(SLAVE_ID, reg, mask, data);
    }

  }

  return err_flag;
}


pm_err_flag_type pm_scpq_chgr_get_charge_current_cfg(uint32 pmic_index, pm_scpq_chgr_current_type charge_current_type, uint32* current_in_ma)
{
  pm_err_flag_type err_flag  = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  pm_register_data_type mask = 0;
  pm_register_address_type reg = 0;
  uint32 step_size = 0;
  uint32 max_value = 0;
  uint32 min_value = 0;

  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if ((charge_current_type >= PM_SCPQ_CHGR_CURRENT_TYPE_INVALID) || (NULL == current_in_ma))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    switch (charge_current_type)
    {
    case PM_SCPQ_CHGR_PRE_CHARGE_CURRENT:
      reg = ADDRESS(ipre_cfg);
      mask = 0x07;  // BIT<2:0>
      step_size = 50;
      max_value = 600;
      min_value = 250;
      break;

    case PM_SCPQ_CHGR_FAST_CHARGE_CURRENT:
      reg = ADDRESS(ichg_cfg);
      mask = 0xFF;  // BIT<7:0>
      step_size = 50;
      max_value = 10000;  // max 10A for the case SMB is connected.
      min_value = 0;
      break;

    case PM_SCPQ_CHGR_TERMINATION_CURRENT:
      reg = ADDRESS(chg_term_cfg);
      mask = 0x07;   // BIT<2:0>
      step_size = 50;
      max_value = 450;
      min_value = 100;
      break;

    default:
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
      break;
    }

    err_flag = pm_comm_read_byte_mask(SLAVE_ID, reg, mask, &data);
    *current_in_ma = min_value + (data * step_size);
  }

  return err_flag;
}


pm_err_flag_type pm_scpq_chgr_enable_charging(uint32 pmic_index, boolean enable)
{
  pm_err_flag_type  err_flag  = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag =  PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type reg = ADDRESS(chg_en);
    pm_register_data_type data = enable ? 0x01 : 0x00;
    pm_register_data_type mask = 0x01;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, reg, mask, data);
  }

  return err_flag;
}


pm_err_flag_type pm_scpq_chgr_get_chgr_status(uint32 pmic_index, pm_scpq_chgr_status_type *chgr_status)
{
  pm_err_flag_type   err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);
  pm_register_data_type data[8] = {0};

  if (NULL == scpq_ptr)
  {
    err_flag =  PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == chgr_status)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type status_set = ADDRESS(charger_status);
    /*read 8 status register*/
    err_flag = pm_comm_read_byte_array(SLAVE_ID, status_set, 8, data);

    /*charger_status related*/
    chgr_status->charger_status.battery_charger_status = (pm_scpq_battery_charger_status)(data[0] & 0x7);
    chgr_status->charger_status.charger_error_status_bat_ov     = (data[0] & 0x10) ? TRUE : FALSE;
    chgr_status->charger_status.charger_error_status_sft_expire = (data[0] & 0x20) ? TRUE : FALSE;
    chgr_status->charger_status.valid_input_power_source        = (data[0] & 0x80) ? TRUE : FALSE;

    /*chg_en_status related*/
    chgr_status->chg_en_status.enable_chg_sensors  = (data[1] & 0x01) ? TRUE : FALSE;
    chgr_status->chg_en_status.enable_trickle      = (data[1] & 0x02) ? TRUE : FALSE;
    chgr_status->chg_en_status.enable_pre_charging = (data[1] & 0x04) ? TRUE : FALSE;
    chgr_status->chg_en_status.enable_fullon_mode  = (data[1] & 0x08) ? TRUE : FALSE;
    chgr_status->chg_en_status.charging_enable     = (data[1] & 0x10) ? TRUE : FALSE;
    chgr_status->chg_en_status.disable_charging    = (data[1] & 0x20) ? TRUE : FALSE;

    /*vbat_status related*/
    chgr_status->vbat_status.vbatt_lt_2v         = (data[2] & 0x01) ? TRUE : FALSE;
    chgr_status->vbat_status.vbatt_gt_full_on    = (data[2] & 0x02) ? TRUE : FALSE;
    chgr_status->vbat_status.vbatt_gtet_inhibit  = (data[2] & 0x04) ? TRUE : FALSE;
    chgr_status->vbat_status.vbatt_ltet_recharge = (data[2] & 0x08) ? TRUE : FALSE;
    chgr_status->vbat_status.taper_region        = (data[2] & 0x10) ? TRUE : FALSE;
    chgr_status->vbat_status.vbatt_drop_in_fv    = (data[2] & 0x20) ? TRUE : FALSE;
    chgr_status->vbat_status.gf_batt_ov          = (data[2] & 0x80) ? TRUE : FALSE;

    /*vbat_status2 related*/
    chgr_status->vbat_status2.pre_fullon  = (data[3] & 0x02) ? TRUE : FALSE;
    chgr_status->vbat_status2.pre_inhibit = (data[3] & 0x08) ? TRUE : FALSE;
    chgr_status->vbat_status2.taper       = (data[3] & 0x20) ? TRUE : FALSE;
    chgr_status->vbat_status2.pre_ovrv    = (data[3] & 0x80) ? TRUE : FALSE;

    /*ibat_status related*/
    chgr_status->ibat_status.zero_charge_current       = (data[4] & 0x01) ? TRUE : FALSE;
    chgr_status->ibat_status.force_zero_charge_current = (data[4] & 0x02) ? TRUE : FALSE;
    chgr_status->ibat_status.pre_term                  = (data[4] & 0x04) ? TRUE : FALSE;
    chgr_status->ibat_status.icl_incr_req_for_prechg   = (data[4] & 0x80) ? TRUE : FALSE;

    /*vflt_status related*/
    chgr_status->vflt_status = data[5];

    /*not use data[6] for SCPQ_P_CHGR_ICHG_B4_VPH_ALARM*/

    /*ichg_status related*/
    chgr_status->ichg_status = data[7];
  }

  return err_flag;
}


/*This API configures the floating voltage. Valid range is 3600mV to 4790 mv for 1S battery*/
pm_err_flag_type pm_scpq_chgr_set_float_volt(uint32 pmic_index, uint32 float_volt_mv)
{
  pm_err_flag_type  err_flag  = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data  = 0x00;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type fv_cfg = ADDRESS(vflt_cfg);
    if (float_volt_mv < FLOAT_VOLTAGE_MIN)
    {
      data = 0x0;
    }
    else if (float_volt_mv >= 4790)
    {
      data = 0x77;
    }
    else
    {
      /* Float voltage setting = 3.6V + (DATA x 10mV) */
      data = (float_volt_mv - FLOAT_VOLTAGE_MIN) / PM_SCPQ_FLOAT_VOLTAGE_STEP_CONSTANT;
    }

    err_flag = pm_comm_write_byte(SLAVE_ID, fv_cfg, data);
  }

  return err_flag;
}

/*This API get the floating voltage config. Valid range is 3600mV to 4790 mv for 1S battery*/
pm_err_flag_type pm_scpq_chgr_get_float_volt_cfg(uint32 pmic_index, uint32 *float_volt_mv)
{
  pm_err_flag_type  err_flag  = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data  = 0x00;
  pm_register_data_type mask  = 0xFF;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (NULL == float_volt_mv)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, ADDRESS(vflt_cfg), mask, &data);

    /* Float voltage setting = 3.6V + (DATA x 10mV) */
    *float_volt_mv = FLOAT_VOLTAGE_MIN + (data * PM_SCPQ_FLOAT_VOLTAGE_STEP_CONSTANT);
  }

  return err_flag;
}


pm_err_flag_type pm_scpq_chgr_get_scpq_pmic_info(uint32 *pmic_index, uint32 *slave_id, uint32* charger_count, uint32 max_charger)
{
  uint32 i = 0;

  if (NULL == pmic_index || NULL == slave_id || NULL == charger_count)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *charger_count = 0;
  pm_scpq_get_pmic_info(pmic_index, slave_id, charger_count, max_charger);

  for (i = 0; i < *charger_count; i++)
  {
    if (pmic_index[i] >= PM_MAX_NUM_PMICS || slave_id[i] >= PM_MAX_NUM_SLAVE_IDS)
    {
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
  }

  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type pm_scpq_chgr_configure_vsysmin(uint32 pmic_index, uint32 vsysmin_mv)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type address = ADDRESS(vsys_min_cfg);
    pm_register_data_type mask = 0x07; // BIT<2:0>

    uint8 idx = pm_utils_get_upper_idx(vsysmin_mv, vsys_min_vals, VSYSMIN_CFG_COUNT);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, address, mask, idx);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_chgr_get_vsysmin_cfg(uint32 pmic_index, uint32* vsysmin_mv)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == vsysmin_mv)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type address = ADDRESS(vsys_min_cfg);
    pm_register_data_type mask = 0x07; // BIT<2:0>
    pm_register_data_type data = 0x0;
    err_flag = pm_comm_read_byte(SLAVE_ID, address, &data);

    *vsysmin_mv = vsys_min_vals[data & mask];
  }

  return err_flag;
}


pm_err_flag_type pm_scpq_chgr_vph_track_threshold_sel(uint32 pmic_index, pm_scpq_chgr_vph_track_sel_type track_sel)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(track_sel >= PM_SCPQ_VPH_TRACK_SEL_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type address = ADDRESS(vph_pre_chg_cfg);
    pm_register_data_type mask = 0x07; // BIT<2:0>
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, address, mask, track_sel);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_chgr_vph_prechg_alg_en(uint32 pmic_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type address = ADDRESS(vph_pre_chg_cfg);
    pm_register_data_type data = enable ? 0x80 : 0x00;
    pm_register_data_type mask = 0x80; // BIT<7>
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, address, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_chgr_get_bat_2s_chg_cfg(uint32 pmic_index, boolean* is_2s_bat)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (NULL == is_2s_bat)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type address = ADDRESS(bat_2s_charge_cfg);
    pm_register_data_type mask = 0x1; // BIT<0>
    pm_register_data_type data = 0x0;
    err_flag |= pm_comm_read_byte_mask(SLAVE_ID, address, mask, &data);

    *is_2s_bat = (data & mask) ? TRUE : FALSE;
  }

  return err_flag;
}

