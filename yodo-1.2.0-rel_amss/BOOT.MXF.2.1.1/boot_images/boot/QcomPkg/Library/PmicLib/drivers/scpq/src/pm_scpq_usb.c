/*! \file
*
*  \brief  pm_scpq_usb.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2020 - 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    -------------------------------------------------------------
12/02/19    zzx    Initial revision
=============================================================================== */

/*=============================================================================

                        INCLUDE FILES

===============================================================================*/
#include "pm_scpq_driver.h"
#include "pm_scpq_usb.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/
#define ADDRESS(x) (scpq_ptr->base_address + \
                    scpq_ptr->usb_register->peripheral_offset + \
                    scpq_ptr->usb_register->x)

#define SLAVE_ID   (scpq_ptr->comm_ptr->slave_id)

#define PM_SCPQ_USB_USBIN_MAX_CURRENT_LIMIT_CFG_MV      5000
#define PM_SCPQ_USB_USBIN_CURRENT_LIMIT_CFG_STEP_SIZE   50

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
pm_err_flag_type pm_scpq_usb_irq_enable(uint32 pmic_index, pm_scpq_usb_irq_type irq, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type irq_reg = 0;
  pm_register_data_type data = 1 << irq;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(irq >= PM_SCPQ_USB_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    if(enable)
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

pm_err_flag_type pm_scpq_usb_irq_clear(uint32  pmic_index, pm_scpq_usb_irq_type irq)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 1 << irq;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(irq >= PM_SCPQ_USB_IRQ_INVALID)
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

pm_err_flag_type pm_scpq_usb_irq_set_trigger(uint32 pmic_index, pm_scpq_usb_irq_type irq, pm_irq_trigger_type trigger)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 mask = 1 << irq;
  pm_register_data_type set_type = 0, polarity_high = 0, polarity_low = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(irq >= PM_SCPQ_USB_IRQ_INVALID || trigger >= PM_IRQ_TRIGGER_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
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
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, int_set_type, mask, set_type);
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, int_polarity_high, mask, polarity_high);
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, int_polarity_low, mask, polarity_low);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_irq_status(uint32 pmic_index, pm_scpq_usb_irq_type irq, pm_irq_status_type type, boolean *status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  uint8 mask = 1 << irq;
  pm_register_address_type int_sts = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(irq >= PM_SCPQ_USB_IRQ_INVALID || type >= PM_IRQ_STATUS_INVALID || NULL == status)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    switch(type)
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
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    err_flag = pm_comm_read_byte_mask(SLAVE_ID, int_sts, mask, &data);
    *status = data ? TRUE : FALSE;
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_set_usbin_adptr_allowance(uint32 pmic_index, pm_scpq_usb_usbin_adapter_allowance_type adptr_allowance)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if((adptr_allowance >= PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_INVALID) ||
        (adptr_allowance == PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_RESERVED) ||
        (adptr_allowance > PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_LV_TO_MV && adptr_allowance <PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_LV_TO_HV))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type usbin_adapter_allow_cfg = ADDRESS(usbin_adapter_allow_cfg);
    data = (pm_register_data_type)adptr_allowance;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, usbin_adapter_allow_cfg, 0x0F, data);
  }

  return err_flag;
}


pm_err_flag_type pm_scpq_usb_get_usbin_adptr_allowance(uint32 pmic_index, pm_scpq_usb_usbin_adapter_allowance_type *adptr_allowance)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == adptr_allowance)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type usbin_adapter_allow_cfg = ADDRESS(usbin_adapter_allow_cfg);
    err_flag = pm_comm_read_byte(SLAVE_ID, usbin_adapter_allow_cfg, &data);
    if(PM_ERR_FLAG_SUCCESS == err_flag)
    {
      *adptr_allowance = (pm_scpq_usb_usbin_adapter_allowance_type)(data & 0xF);
    }
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_get_apsd_status(uint32 pmic_index, pm_scpq_usb_apsd_status_type apsd_status_type, boolean *result)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == result || apsd_status_type >= PM_SCPQ_USB_APSD_STATUS_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type apsd_status = ADDRESS(apsd_status);
    err_flag = pm_comm_read_byte(SLAVE_ID, apsd_status, &data);
    if(PM_ERR_FLAG_SUCCESS == err_flag)
    {
      *result = (data & (0x1 << apsd_status_type)) ? TRUE : FALSE;
    }
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_get_apsd_result_status(uint32 pmic_index, pm_chg_charger_port_type *apsd_result)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);
  pm_register_address_type apsd_result_status;
  int8 usb_type = 0x06;

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == apsd_result)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    *apsd_result = PM_CHARGER_PORT_TYPE_INVALID;
    apsd_result_status = ADDRESS(apsd_result_status);

    err_flag = pm_comm_read_byte(SLAVE_ID, apsd_result_status, &data);
    if(PM_ERR_FLAG_SUCCESS == err_flag)
    {
      /*Check for charger port type starting from bit 6 to 0*/
      while(usb_type >= 0)
      {
        if(data & (1 << usb_type))
        {
          *apsd_result = (pm_chg_charger_port_type)usb_type;
          break;
        }
        usb_type--;
      }
    }
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_configure_usb_icl_options(uint32 pmic_index, pm_scpq_usb_icl_options_type icl_options, boolean set_value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);
  pm_register_data_type data = (set_value) ? 0xFF : 0x00;
  pm_register_data_type mask = 0x1 << icl_options ;

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(icl_options >= PM_SCPQ_USB_ICL_OPTIONS_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type usbin_icl_options = ADDRESS(usb_icl_options);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, usbin_icl_options, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_set_icl_cfg(uint32 pmic_index, uint32 usbin_current_limit)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0x0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    if(usbin_current_limit > PM_SCPQ_USB_USBIN_MAX_CURRENT_LIMIT_CFG_MV)
    {
      data = 100;
    }
    else
    {
      data = (usbin_current_limit + (PM_SCPQ_USB_USBIN_CURRENT_LIMIT_CFG_STEP_SIZE / 2)) / PM_SCPQ_USB_USBIN_CURRENT_LIMIT_CFG_STEP_SIZE;
    }
    pm_register_address_type usbin_current_limit_cfg = ADDRESS(usb_icl_cfg);

    err_flag = pm_comm_write_byte(SLAVE_ID, usbin_current_limit_cfg, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_rerun_apsd(uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type apsd_cfg_reg = ADDRESS(apsd_cmd);
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, apsd_cfg_reg, 1, 1);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_set_inov_cfg(uint32 pmic_index, pm_scpq_usb_inov_cfg_type inov_cfg, boolean enable,
                                          pm_scpq_usb_inov_vadp_decr_timer_type timer_sel)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = enable ? 0xFF : 0x00;

  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);
  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(inov_cfg >= PM_SCPQ_USB_INOV_CFG_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else if(inov_cfg == PM_SCPQ_USB_VADP_DECR_TIMER_SEL)
  {
    if(timer_sel < 0x0 || timer_sel > 0x3)
    {
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }
    pm_register_address_type usbin_inov_cfg = ADDRESS(inov_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, usbin_inov_cfg, (3 << inov_cfg), timer_sel);
  }
  else
  {
    pm_register_address_type usbin_inov_cfg = ADDRESS(inov_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, usbin_inov_cfg, (1 << inov_cfg), data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_get_inov_cfg(uint32 pmic_index, pm_scpq_usb_inov_cfg_type inov_cfg, boolean *enable,
                                          pm_scpq_usb_inov_vadp_decr_timer_type *timer_sel)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;

  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);
  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(inov_cfg >= PM_SCPQ_USB_INOV_CFG_INVALID || enable == NULL || timer_sel == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else if(inov_cfg == PM_SCPQ_USB_VADP_DECR_TIMER_SEL)
  {
    pm_register_address_type usbin_inov_cfg = ADDRESS(inov_cfg);
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, usbin_inov_cfg, (3 << inov_cfg), &data);
    *timer_sel = (pm_scpq_usb_inov_vadp_decr_timer_type)data;
  }
  else
  {
    pm_register_address_type usbin_inov_cfg = ADDRESS(inov_cfg);
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, usbin_inov_cfg, (1 << inov_cfg), &data);
    *enable = data? TRUE : FALSE;
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_set_usbin_suspend(uint32 pmic_index, pm_scpq_usb_usb_suspend_type usb_suspend_cfg, boolean set_value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(usb_suspend_cfg >= PM_SCPQ_USB_USB_SUSPEND_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type usb_suspend = ADDRESS(usb_suspend);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, usb_suspend, (1 << usb_suspend_cfg), set_value ? 0x01 : 0x00);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_aicl_options_cfg(uint32 pmic_index, pm_scpq_usb_aicl_cfg_type aicl_cfg_type, boolean enable,
                                              pm_scpq_usb_aicl_collapse_gf_sel_type collapse_gf_sel,
                                              pm_scpq_usb_aicl_step_timming_sel_type step_timming_sel)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(aicl_cfg_type >= PM_SCPQ_USB_AICL_INVALID || aicl_cfg_type < PM_SCPQ_USB_AICL_START_AT_MAX)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type usb_aicl_cfg = ADDRESS(usb_aicl_cfg);
    pm_register_data_type mask = 0x1 << aicl_cfg_type;
    pm_register_data_type data = enable ? 0xFF : 0x00;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, usb_aicl_cfg, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_enable_icl_override_after_apsd(uint32 pmic_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type usb_icl_override = ADDRESS(usb_icl_override);
    pm_register_data_type mask = PM_BIT(4);
    pm_register_data_type data = enable << 4;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, usb_icl_override, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_usb_set_input_priority(uint32 pmic_index, pm_scpq_usb_input_priority_type priority)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(priority >= PM_SCPQ_USB_INPUT_PRIORITY_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_data_type mask = PM_BIT(7);
    pm_register_data_type data = (PM_SCPQ_USB_INPUT_PRIORITY_USB == priority) ? mask : 0;

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, ADDRESS(input_swap_ctl), mask, data);
  }

  return err_flag;
}


