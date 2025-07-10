/*! \file
*
*  \brief  pm_scpq_misc.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2020-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
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
#include "pm_scpq_misc.h"
#include "pm_scpq_driver.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/
#define ADDRESS(x) (scpq_ptr->base_address + \
                    scpq_ptr->misc_register->peripheral_offset + \
                    scpq_ptr->misc_register->x)

#define SLAVE_ID   (scpq_ptr->comm_ptr->slave_id)

/*===========================================================================

FUNCTION DEFINITIONS

===========================================================================*/


pm_err_flag_type pm_scpq_misc_irq_enable(uint32 pmic_index, pm_scpq_misc_irq_type irq, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type irq_reg;
  pm_register_data_type data = 1 << irq;
  pm_scpq_data_type *scpq_ptr  = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (irq >= PM_SCPQ_MISC_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    if (enable)
    {
      irq_reg = ADDRESS(int_en_set);
    }
    else
    {
      irq_reg = ADDRESS(int_en_clr);
    }

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, irq_reg, data, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_misc_irq_clear(uint32 pmic_index, pm_scpq_misc_irq_type irq)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 1 << irq;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (irq >= PM_SCPQ_MISC_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type int_latched_clr = ADDRESS(int_latched_clr);

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, int_latched_clr, data, data);
  }

  return err_flag;
}


pm_err_flag_type pm_scpq_misc_irq_set_trigger(uint32 pmic_index, pm_scpq_misc_irq_type irq, pm_irq_trigger_type trigger)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 mask = 1 << irq;
  pm_register_data_type set_type, polarity_high, polarity_low;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (irq >= PM_SCPQ_MISC_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type int_set_type = ADDRESS(int_set_type);
    pm_register_address_type int_polarity_high = ADDRESS(int_polarity_high);
    pm_register_address_type int_polarity_low = ADDRESS(int_polarity_low);

    switch (trigger)
    {
    case PM_IRQ_TRIGGER_ACTIVE_LOW:
      set_type = 0x00;
      polarity_high = 0x00;
      polarity_low = 0xFF;
      break;
    case PM_IRQ_TRIGGER_ACTIVE_HIGH:
      set_type = 0x00;
      polarity_high = 0xFF;
      polarity_low = 0x00;
      break;
    case PM_IRQ_TRIGGER_RISING_EDGE:
      set_type = 0xFF;
      polarity_high = 0xFF;
      polarity_low = 0x00;
      break;
    case PM_IRQ_TRIGGER_FALLING_EDGE:
      set_type = 0xFF;
      polarity_high = 0x00;
      polarity_low = 0xFF;
      break;
    case PM_IRQ_TRIGGER_DUAL_EDGE:
      set_type = 0xFF;
      polarity_high = 0xFF;
      polarity_low = 0xFF;
      break;
    default:
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, int_set_type, mask, set_type);
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, int_polarity_high, mask, polarity_high);
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, int_polarity_low, mask, polarity_low);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_misc_irq_status(uint32 pmic_index, pm_scpq_misc_irq_type irq, pm_irq_status_type type, boolean *status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data;
  uint8 mask = 1 << irq;
  pm_register_address_type int_sts;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (NULL == status || irq >= PM_SCPQ_MISC_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    switch (type)
    {
    case PM_IRQ_STATUS_RT:
      int_sts = ADDRESS(int_rt_sts);
      break;
    case PM_IRQ_STATUS_LATCHED:
      int_sts = ADDRESS(int_latched_sts);
      break;
    case PM_IRQ_STATUS_PENDING:
      int_sts = ADDRESS(int_pending_sts);
      break;
    default:
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }

    err_flag = pm_comm_read_byte_mask(SLAVE_ID, int_sts, mask, &data);
    *status = data ? TRUE : FALSE;
  }

  return err_flag;
}


pm_err_flag_type pm_scpq_misc_get_sysok_reason(uint32 pmic_index, pm_scpq_misc_sysok_reason_type *sysok_reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (NULL == sysok_reason)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type sysok_reason_status = ADDRESS(sysok_reason_status);
    err_flag = pm_comm_read_byte(SLAVE_ID, sysok_reason_status, &data);

    *sysok_reason = (pm_scpq_misc_sysok_reason_type)(data & 0x03);
  }

  return err_flag;
}


/*This API returns When bark/bite watchdog interrupt trips, this status bit can be used to determine which of the two wdog timer expired*/
pm_err_flag_type pm_scpq_misc_get_misc_wdog_status(uint32 pmic_index, pm_scpq_misc_wdog_status *misc_wdog_sts)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data  = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (NULL == misc_wdog_sts)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type misc_wdog_sts_reg = ADDRESS(wdog_status);
    err_flag = pm_comm_read_byte(SLAVE_ID, misc_wdog_sts_reg, &data);
    *misc_wdog_sts = (data & 0x01 )? PM_SCPQ_MISC_BITE : PM_SCPQ_MISC_BARK;
  }

  return err_flag;
}

/* Writing to this register will pet (reset) BARK and BITE watchdog timers */
pm_err_flag_type pm_scpq_misc_bark_bite_wdog_pet(uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type wdog_pet = ADDRESS(bark_bite_wdog_pet);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, wdog_pet, 0x01, 0x01);
  }

  return err_flag;
}

/*This API configures the charger watchdog */
pm_err_flag_type pm_scpq_misc_config_wdog(uint32 pmic_index, pm_scpq_misc_wdog_cfg_type misc_wd_cfg)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data  = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type wd_cfg_reg = ADDRESS(wd_cfg);
    data |= (misc_wd_cfg.bite_wdog_disable_charging_cfg << 0x7);
    data |= (misc_wd_cfg.bite_wdog_int_en << 0x5);
    data |= (misc_wd_cfg.bark_wdog_int_en << 0x4);
    data |= (misc_wd_cfg.wdog_timer_en_on_plugin << 0x1);
    data |= (misc_wd_cfg.wdog_timer_en << 0x0);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, wd_cfg_reg, 0xB3, data);
  }

  return err_flag;
}


/*This API configures the charger watchdog */
pm_err_flag_type pm_scpq_misc_get_config_wdog(uint32 pmic_index, pm_scpq_misc_wdog_cfg_type *misc_wd_cfg)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data  = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (NULL == misc_wd_cfg)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type wd_cfg_reg = ADDRESS(wd_cfg);
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, wd_cfg_reg, 0xB3, &data);

    misc_wd_cfg->bite_wdog_disable_charging_cfg = (data & 0x80) >> 7;
    misc_wd_cfg->bite_wdog_int_en               = (data & 0x20) >> 5;
    misc_wd_cfg->bark_wdog_int_en               = (data & 0x10) >> 4;
    misc_wd_cfg->wdog_timer_en_on_plugin        = (data & 0x02) >> 1;
    misc_wd_cfg->wdog_timer_en                  = (data & 0x01);
  }

  return err_flag;
}


/*This API configures the charger snarl bark bite watchdog */
pm_err_flag_type pm_scpq_misc_set_wd_time_sel(uint32 pmic_index, pm_scpq_misc_wd_time_sel misc_wd_time_sel)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data  = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if ((misc_wd_time_sel.bite_wdog_timeout >= PM_SCPQ_MISC_BITE_WDOG_TMOUT_INVALID )||
          (misc_wd_time_sel.bark_wdog_timeout  >= PM_SCPQ_MISC_BARK_WDOG_TMOUT_INVALID )||
          (misc_wd_time_sel.snarl_wdog_timeout >= PM_SCPQ_MISC_SNARL_WDOG_TMOUT_INVALID))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type wd_sbb_cfg_reg = ADDRESS(wd_time_sel);
    data = ((misc_wd_time_sel.snarl_wdog_timeout) | (misc_wd_time_sel.bark_wdog_timeout << 4) | (misc_wd_time_sel.bite_wdog_timeout << 6));
    err_flag = pm_comm_write_byte(SLAVE_ID, wd_sbb_cfg_reg, data);
  }

  return err_flag;
}


/*This API gets the charger snarl bark bite watchdog cfg*/
pm_err_flag_type pm_scpq_misc_get_wd_time_sel(uint32 pmic_index, pm_scpq_misc_wd_time_sel *misc_wd_time_sel)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data  = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (NULL == misc_wd_time_sel)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type wd_sbb_cfg_reg = ADDRESS(wd_time_sel);
    err_flag = pm_comm_read_byte(SLAVE_ID, wd_sbb_cfg_reg, &data);

    misc_wd_time_sel->snarl_wdog_timeout = (data & 0x07);
    misc_wd_time_sel->bark_wdog_timeout  = (data & 0x18) >> 4;
    misc_wd_time_sel->bite_wdog_timeout  = (data & 0xC0) >> 6;
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_misc_aicl_cmd_enable(uint32 pmic_index, pm_scpq_misc_aicl_cmd_type cmd)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);
  pm_register_data_type data = 0x1 << cmd;
  pm_register_data_type mask = 0x1 << cmd;

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (PM_SCPQ_MISC_AICL_CMD_INVALID <= cmd)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type aicl_cmd_reg = ADDRESS(aicl_cmd);
    err_flag = pm_comm_write_byte_mask(pmic_index, aicl_cmd_reg, data, mask);
  }

  return err_flag;
}


/*This API configures misc aicl rerun time */
pm_err_flag_type pm_scpq_misc_set_aicl_rerun_time_cfg(uint32 pmic_index, pm_scpq_misc_aicl_rerun_time_cfg aicl_rerun_time)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (PM_SCPQ_MISC_AICL_RERUN_TIME_CFG_INVALID < aicl_rerun_time)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type aicl_cfg_reg = ADDRESS(aicl_rerun_time_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, aicl_cfg_reg, 0x03, aicl_rerun_time);
  }

  return err_flag;
}


/* This API sets thermistor source configuration for charging thermal mitigation (inov)*/
pm_err_flag_type pm_scpq_misc_set_thermreg_src_cfg(uint32 pmic_index, pm_scpq_misc_therm_src_cfg_type src_cfg_type, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 mask = 1 << src_cfg_type;
  pm_register_data_type data = enable << src_cfg_type;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (PM_SCPQ_MISC_THERM_SRC_CFG_INVALID <= src_cfg_type)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type misc_therm_src_cfg = ADDRESS(therm_reg_src_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, misc_therm_src_cfg, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_misc_set_die_temp_thresholds(uint32 pmic_index, int32 hot_threshold, int32 too_hot_threshold)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 mask = 0xFF;

  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    /* Set the die temp thresholds */
    pm_register_address_type die_temp_h_msb = ADDRESS(die_temp_h_thd_msb);
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, die_temp_h_msb, mask, (uint8)((hot_threshold & 0xFF00) >> 8));

    pm_register_address_type die_temp_h_lsb = ADDRESS(die_temp_h_thd_lsb);
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, die_temp_h_lsb, mask, (uint8)(hot_threshold & 0xFF));

    pm_register_address_type die_temp_l_msb = ADDRESS(die_temp_l_thd_msb);
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, die_temp_l_msb, mask, (uint8)((too_hot_threshold & 0xFF00) >> 8));

    pm_register_address_type die_temp_l_lsb = ADDRESS(die_temp_l_thd_lsb);
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, die_temp_l_lsb, mask, (uint8)(too_hot_threshold & 0xFF));
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_misc_set_batt_therm_ch_id_cfg(uint32 pmic_index, uint8 channel_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if (NULL == scpq_ptr)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type reg_addr = ADDRESS(batt_therm_ch_id);
    err_flag = pm_comm_write_byte(SLAVE_ID, reg_addr, channel_id);
  }

  return err_flag;
}


pm_err_flag_type pm_scpq_misc_set_eng_sdcdc_spare_cfg(uint32 pmic_index, pm_scpq_misc_eng_sdcdc_spare_cfg_type sdcdc_cfg, boolean set_value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);
  pm_register_data_type mask = 0x1 << sdcdc_cfg;
  pm_register_data_type data = set_value ? 0xFF : 0x0;

  if (NULL == scpq_ptr)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (sdcdc_cfg >= PM_SCPQ_MISC_ENG_SDCDC_SPARE_CFG_INVALID)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type reg_addr = ADDRESS(eng_sdcdc_spare);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, reg_addr, mask, data);
  }

  return err_flag;
}
