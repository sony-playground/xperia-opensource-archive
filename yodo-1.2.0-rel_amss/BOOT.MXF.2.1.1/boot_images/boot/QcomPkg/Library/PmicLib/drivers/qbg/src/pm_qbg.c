/*! \file
*
*  \brief  pm_qbg.c driver implementation.
*  \details qguage driver implementation.
*  &copy;
*  Copyright (c) 2020-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/qbg/src/pm_qbg.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when        who    what, where, why
--------    ---    ----------------------------------------------------------
02/21/18    sv     Initial revision
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_qbg.h"
#include "pm_qbg_driver.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/
    
#define QBG_BAT_THRESHOLD_NUMR 49920 //per LSB is 49.92 mV
#define QBG_BAT_THRESHOLD_DENR 1000

#define ADDRESS(x) (qbg_ptr->qbg_register->base_address + qbg_ptr->qbg_register->x)
#define SLAVE_ID   (qbg_ptr->comm_ptr->slave_id)

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/



pm_err_flag_type pm_qbg_irq_enable(uint32 device_index, pm_qbg_irq_type irq, boolean enable)
{
  pm_err_flag_type    err_flag    = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type irq_reg;
  pm_register_data_type data = 1 << irq;

  pm_qbg_data_type *qbg_ptr  = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (irq >= PM_QBG_IRQ_INVALID)
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

    err_flag = pm_comm_write_byte(SLAVE_ID, irq_reg, data);
  }
  return err_flag;
}

pm_err_flag_type pm_qbg_irq_clear(uint32  device_index, pm_qbg_irq_type irq)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 1 << irq;
  pm_qbg_data_type *qbg_ptr = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (irq >= PM_QBG_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = pm_comm_write_byte(SLAVE_ID, ADDRESS(int_latched_clr), data);
  }

  return err_flag;
}


pm_err_flag_type pm_qbg_irq_set_trigger(uint32 device_index, pm_qbg_irq_type irq, pm_irq_trigger_type trigger)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 mask = 1 << irq;
  pm_register_data_type set_type, polarity_high, polarity_low;
  pm_register_address_type int_set_type, int_polarity_high, int_polarity_low;

  pm_qbg_data_type *qbg_ptr  = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (irq >= PM_QBG_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    int_set_type = ADDRESS(int_set_type);
    int_polarity_high = ADDRESS(int_polarity_high);
    int_polarity_low = ADDRESS(int_polarity_low);

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


pm_err_flag_type pm_qbg_irq_status(uint32 device_index, pm_qbg_irq_type irq, pm_irq_status_type type, boolean *status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data;
  uint8 mask = 1 << irq;
  pm_register_address_type int_sts;
  pm_qbg_data_type *qbg_ptr  = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (irq >= PM_QBG_IRQ_INVALID)
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



pm_err_flag_type pm_qbg_get_status(uint32 device_index, pm_qbg_status_type* qbg_status, pm_qbg_fsm_staus_type* qbg_fsm_state)
{
#define STATUS_ARRARY_SIZE   3
  pm_err_flag_type  err_flag  = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data[STATUS_ARRARY_SIZE] = {0};
  pm_register_address_type reg; 

  pm_qbg_data_type *qbg_ptr  = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (NULL == qbg_status || NULL == qbg_fsm_state)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    reg = ADDRESS(status1);
    err_flag = pm_comm_read_byte_array(SLAVE_ID, reg, STATUS_ARRARY_SIZE, data);
    qbg_status->qg_ok                   = (data[0] & 0x80)? TRUE : FALSE;
    qbg_status->battery_present         = (data[1] & 0x04)? FALSE : TRUE;
    qbg_status->adc_conv_fault_occured  = (data[1] & 0x02)? TRUE : FALSE;
    qbg_status->data_reset              = (data[1] & 0x01)? TRUE : FALSE;
    *qbg_fsm_state                      = data[2] & 0x07;
  }

  return err_flag ;
};

pm_err_flag_type pm_qbg_get_pon_ocv_acc_data(uint32 device_index, pm_qbg_acc_index_type acc_index, uint16* data)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg;
  pm_qbg_data_type* qbg_ptr = pm_qbg_get_data(device_index);

  if(NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == data || acc_index >= PM_QBG_ACC_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    reg = ADDRESS(pon_ocv_acc0_data0) + 2 * acc_index;
    err_flag = pm_comm_read_byte_array(SLAVE_ID, reg, 2, (uint8*)data);
  }

  return err_flag;
}

pm_err_flag_type pm_qbg_get_last_burst_avg_acc_data(uint32 device_index, pm_qbg_acc_index_type acc_index, uint16* data)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg;
  pm_qbg_data_type* qbg_ptr = pm_qbg_get_data(device_index);

  if(NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == data || acc_index >= PM_QBG_ACC_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    reg = ADDRESS(last_burst_avg_acc0_data0) + 2 * acc_index;
    err_flag = pm_comm_read_byte_array(SLAVE_ID, reg, 2, (uint8*)data);
  }

  return err_flag;
}

pm_err_flag_type pm_qbg_set_vbat_empty_threshold(uint32 device_index, uint32 vbatEmptyThreshold)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type vbatthreshold =0;
  pm_register_address_type reg; 

  pm_qbg_data_type *qbg_ptr  = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    reg = ADDRESS(vbat_empty_threshold);

    //49920 / 1000 = 49.92 mV per LSB 
    vbatthreshold = ((int64)vbatEmptyThreshold * QBG_BAT_THRESHOLD_DENR)/QBG_BAT_THRESHOLD_NUMR;

    err_flag = pm_comm_write_byte(SLAVE_ID, reg, vbatthreshold);
  }

  return err_flag ;
};

pm_err_flag_type pm_qbg_set_qbg_mode_ctl1_batt_opt(uint32 device_index, pm_chg_battery_type battery_type)
{
  pm_err_flag_type err_flag    = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg = 0;
  pm_register_data_type data   = 0;
  pm_register_data_type mask   = 0xC0;

  pm_qbg_data_type *qbg_ptr = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    reg  = ADDRESS(mode_ctl1);
    data = battery_type << 6;

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, reg, mask, data);
  }

  return err_flag ;
}

pm_err_flag_type pm_qbg_set_qbg_mode_ctl3_batt_opt(uint32 device_index, pm_chg_2s_battery_option_type option_2s)
{
  pm_err_flag_type err_flag    = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg = 0;
  pm_register_data_type data   = 0;
  pm_register_data_type mask   = 0x6;

  pm_qbg_data_type *qbg_ptr = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(option_2s >= PM_CHG_VBAT_2S_OPTION_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    reg  = ADDRESS(mode_ctl3);
    data = option_2s << 1;

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, reg, mask, data);
  }

  return err_flag ;
}

pm_err_flag_type pm_qbg_set_qbg_mode_ctl2_ichg_fs_opt(uint32 device_index, BOOLEAN support_24A)
{
  pm_err_flag_type err_flag    = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg = 0;
  pm_register_data_type data   = 0;
  pm_register_data_type mask   = 0x1;

  pm_qbg_data_type *qbg_ptr = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    reg  = ADDRESS(mode_ctl2);
    data = support_24A ? 0xFF : 0x00;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, reg, mask, data);
  }

  return err_flag ;
}

pm_err_flag_type pm_qbg_get_qbg_mode_ctl1_batt_opt(uint32 device_index, pm_chg_battery_type* battery_type)
{
  pm_err_flag_type err_flag    = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg = 0;
  pm_register_data_type data   = 0;
  pm_register_data_type mask   = 0xC0;

  pm_qbg_data_type *qbg_ptr = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr || NULL == battery_type)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    reg = ADDRESS(mode_ctl1);
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, reg, mask, &data);
    *battery_type = (data >> 6) ? TRUE : FALSE;
  }

  return err_flag ;
}

pm_err_flag_type pm_qbg_get_qbg_mode_ctl3_batt_opt(uint32 device_index, pm_chg_2s_battery_option_type* p_2s_option)
{
  pm_err_flag_type err_flag    = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg = 0;
  pm_register_data_type data   = 0;
  pm_register_data_type mask   = 0x6;

  pm_qbg_data_type *qbg_ptr = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr || NULL == p_2s_option)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    reg = ADDRESS(mode_ctl3);
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, reg, mask, &data);
    *p_2s_option = (data & 0x6) >> 1;
  }

  return err_flag ;
}

pm_err_flag_type pm_qbg_get_qbg_mode_ctl2_ichg_fs_opt(uint32 device_index, BOOLEAN* p_support_24A)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg = 0; 
  pm_register_data_type data = 0;
  pm_register_data_type mask   = 0x1;

  pm_qbg_data_type *qbg_ptr = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr || NULL == p_support_24A)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    reg = ADDRESS(mode_ctl2);
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, reg, mask, &data);
    *p_support_24A = (data & 0x01) ? TRUE : FALSE;
  }

  return err_flag ;
}

pm_err_flag_type pm_qbg_set_tbat_thermal_calibration_method(uint32 device_index, pm_qbg_cal_method fast_chg_sel, pm_qbg_cal_method xpm_sel)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 data = 0;
  uint8 mask = 0x3C; // fast charge sel: bit[5:4], xPM sel: bit[3:2]

  pm_qbg_data_type *qbg_ptr = pm_qbg_get_data(device_index);

  if (NULL == qbg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(fast_chg_sel >= PM_QBG_CAL_METHOD_INVALID || xpm_sel >= PM_QBG_CAL_METHOD_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    // fast charge selection: BIT[5:4], xPM selection: BIT[3:2]
    data = (xpm_sel << 2) | (fast_chg_sel << 4);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, ADDRESS(cmd_adc_ctl7), mask, data);
  }

  return err_flag ;
}

