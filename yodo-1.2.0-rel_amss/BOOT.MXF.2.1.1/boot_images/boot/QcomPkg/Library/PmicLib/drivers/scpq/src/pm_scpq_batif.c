/*! \file
*
*  \brief  pm_scpq_bat_if.c driver implementation.
*  \details charger driver implementation.
*  &copy; Copyright 2020-2022 QUALCOMM Technologies, Inc All Rights Reserved
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
#include "pm_scpq_batif.h"
#include "pm_scpq_driver.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/
#define ADDRESS(x) (scpq_ptr->base_address + \
                    scpq_ptr->batif_register->peripheral_offset + \
                    scpq_ptr->batif_register->x)

#define SLAVE_ID   (scpq_ptr->comm_ptr->slave_id)

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/


pm_err_flag_type pm_scpq_batif_enable_shipmode(uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, ADDRESS(ship_mode), PM_BIT(0), PM_BIT(0));
  }

  return err_flag;
}

/*This API enables automatic fault protection */
pm_err_flag_type pm_scpq_batif_enable_afp(uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, ADDRESS(afp_mode), PM_BIT(0), PM_BIT(0));
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_batif_irq_enable(uint32 pmic_index, pm_scpq_batif_irq_type irq, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type irq_reg = 0;
  pm_register_data_type mask = 1 << irq;
  pm_register_data_type data = 0xFF;

  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(irq >= PM_SCPQ_BATIF_IRQ_INVALID)
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

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, irq_reg, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_batif_irq_clear(uint32 pmic_index, pm_scpq_batif_irq_type irq)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type mask = 1 << irq;
  pm_register_data_type data = 0xFF;
  pm_register_address_type int_latched_clr = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(irq >= PM_SCPQ_BATIF_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    int_latched_clr = ADDRESS(int_latched_clr);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, int_latched_clr, mask, data);
  }

  return err_flag;
}


pm_err_flag_type pm_scpq_batif_irq_set_trigger(uint32 pmic_index, pm_scpq_batif_irq_type irq, pm_irq_trigger_type trigger)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 mask = 1 << irq;
  pm_register_data_type set_type = 0, polarity_high = 0, polarity_low = 0;
  pm_register_address_type int_set_type = 0, int_polarity_high = 0, int_polarity_low = 0;

  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if((irq >= PM_SCPQ_BATIF_IRQ_INVALID) || (trigger >= PM_IRQ_TRIGGER_INVALID))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    int_set_type      = ADDRESS(int_set_type);
    int_polarity_high = ADDRESS(int_polarity_high);
    int_polarity_low  = ADDRESS(int_polarity_low);

    switch(trigger)
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


pm_err_flag_type pm_scpq_batif_irq_status(uint32 pmic_index, pm_scpq_batif_irq_type irq, pm_irq_status_type type, boolean *status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  pm_register_data_type mask = 1 << irq;
  pm_register_address_type int_sts = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if((irq >= PM_SCPQ_BATIF_IRQ_INVALID) || (type >= PM_IRQ_TRIGGER_INVALID) || (NULL == status))
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
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }

    err_flag = pm_comm_read_byte_mask(SLAVE_ID, int_sts, mask, &data);
    *status = data ? TRUE : FALSE;
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_batif_cfg_batt_missing_src(uint32 pmic_index, pm_scpq_batif_bat_miss_src_cfg_type bat_miss_cfg, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(bat_miss_cfg >= PM_SCPQ_BAT_MISS_SRC_CFG_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_data_type mask = 1 << bat_miss_cfg;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, ADDRESS(bpd_cfg), mask, enable ? 0xFF : 0x00);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_batif_set_jeita_threshold_value(uint32 device_index, pm_scpq_batif_jeita_threshold_type threshold_type, uint32 jeita_threshold)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(device_index);
  uint8 jeita_threshold_lsb = (jeita_threshold & 0xFF);
  uint8 jeita_threshold_msb = jeita_threshold >> 8;
  pm_register_address_type addr_msb = 0, addr_lsb = 0;


  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(threshold_type >= PM_SCPQ_BATIF_JEITA_THRESHOLD_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    switch(threshold_type)
    {
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_WARM:
      addr_msb = ADDRESS(jeita_warm_thd_msb);
      addr_lsb = ADDRESS(jeita_warm_thd_lsb);
      break;
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_COOL:
      addr_msb = ADDRESS(jeita_cool_thd_msb);
      addr_lsb = ADDRESS(jeita_cool_thd_lsb);
      break;
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_HOT:
      addr_msb = ADDRESS(jeita_thot_thd_msb);
      addr_lsb = ADDRESS(jeita_thot_thd_lsb);
      break;
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_COLD:
      addr_msb = ADDRESS(jeita_tcold_thd_msb);
      addr_lsb = ADDRESS(jeita_tcold_thd_lsb);
      break;
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_HOT_AFP:
      addr_msb = ADDRESS(jeita_thot_afp_thd_msb);
      addr_lsb = ADDRESS(jeita_thot_afp_thd_lsb);
      break;
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_COLD_AFP:
      addr_msb = ADDRESS(jeita_tcold_afp_thd_msb);
      addr_lsb = ADDRESS(jeita_tcold_afp_thd_lsb);
      break;
    default:
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    err_flag = pm_comm_write_byte(SLAVE_ID, addr_msb, jeita_threshold_msb);
    err_flag |= pm_comm_write_byte(SLAVE_ID, addr_lsb, jeita_threshold_lsb);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_batif_get_jeita_threshold_value(uint32 device_index, pm_scpq_batif_jeita_threshold_type threshold_type, uint16* jeita_threshold)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(device_index);
  pm_register_address_type addr_msb = 0, addr_lsb = 0;

  uint8 jeita_threshold_msb = 0, jeita_threshold_lsb = 0;

  if (NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(threshold_type >= PM_SCPQ_BATIF_JEITA_THRESHOLD_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    switch (threshold_type)
    {
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_WARM:
      addr_msb = ADDRESS(jeita_warm_thd_msb);
      addr_lsb = ADDRESS(jeita_warm_thd_lsb);
      break;
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_COOL:
      addr_msb = ADDRESS(jeita_cool_thd_msb);
      addr_lsb = ADDRESS(jeita_cool_thd_lsb);
      break;
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_HOT:
      addr_msb = ADDRESS(jeita_thot_thd_msb);
      addr_lsb = ADDRESS(jeita_thot_thd_lsb);
      break;
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_COLD:
      addr_msb = ADDRESS(jeita_tcold_thd_msb);
      addr_lsb = ADDRESS(jeita_tcold_thd_lsb);
      break;
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_HOT_AFP:
      addr_msb = ADDRESS(jeita_thot_afp_thd_msb);
      addr_lsb = ADDRESS(jeita_thot_afp_thd_lsb);
      break;
    case PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_COLD_AFP:
      addr_msb = ADDRESS(jeita_tcold_afp_thd_msb);
      addr_lsb = ADDRESS(jeita_tcold_afp_thd_lsb);
      break;
    default:
      return err_flag;
    }
    err_flag |= pm_comm_read_byte(SLAVE_ID, addr_msb, &jeita_threshold_msb);
    err_flag |= pm_comm_read_byte(SLAVE_ID, addr_lsb, &jeita_threshold_lsb);
    *jeita_threshold = (jeita_threshold_msb << 8) | jeita_threshold_lsb;
  }
  return err_flag;
}

pm_err_flag_type pm_scpq_batif_jeita_en_cfg(uint32 device_index, pm_scpq_batif_jeita_cfg_type jeita_cfg_type, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(device_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(jeita_cfg_type >= PM_SCPQ_BATIF_JEITA_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type jeita_en_cfg = ADDRESS(jeita_en_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, jeita_en_cfg, (uint8)(1 << jeita_cfg_type), (enable ? 0xFF : 0x00));
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_batif_enable_batt_diff_sense(uint32 device_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(device_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type address = ADDRESS(batt_diffsense_cfg);
    pm_register_data_type data = enable ? 1 : 0;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, address, 0x01, data);
  }

  return err_flag;
}


