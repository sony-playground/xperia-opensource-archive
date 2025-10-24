/*! \file
*
*  \brief  pm_rtc.c ----File contains the implementation of the public APIs for RTC resource type.
*  \details Implementation file for RTC resourece type.
*  Each of the APIs checks for access and then if necessary directs
*  the call to Driver implementation or to RPC function for the master processor.
*
*    PMIC code generation Version: 2.0.0.22
*    This file contains code for Target specific settings and modes.
*
*  &copy; Copyright 2012 - 2020, 2022 QUALCOMM Technologies, Inc All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/rtc/src/pm_rtc.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
4/24/19    cg      Restructuring the APis and adding ARTC alaram API's
05/21/15   al      Adding API to read RTC alarm and interrupt
08/20/14   al      Updating comm lib
05/20/14   al      Architecture update
08/03/12   al      New arch

===========================================================================*/

/*===========================================================================

INCLUDE FILES

===========================================================================*/
#include "pm_rtc.h"
#include "pm_rtc_driver.h"
/*===========================================================================

                        GLOBAL DEFINITIONS

===========================================================================*/
#define RTC_TIME_SEC_BYTE_SIZE              4
#define BIT_7_MASK                          0x80
#define BIT_0_MASK                          0x01
#define TIME_ADJ_MASK                       0x7F
#define MAX_TIME_ADJ                        0x7F
#define RTC_ALARM_DATA                      0x2
#define RTC_RW_DATA                         0x1
#define RTC_ALARM_MASK                      0x2
#define RTC_RW_MASK                         0x1
#define RTC_RESET                           0x00
#define RTC_RESET_DETECTION_HW_SUPPORT_REV  0x51

// macros for alarm and rw msec timer
#define RTC_TIME_MSEC_BYTE_SIZE 2
#define RTC_ALARM_MSEC_CFG_EN_MASK 0x11
#define RTC_MSEC_DATA_MASK 0x03FF //only 10 bits used in the register to store the 32bit msec value

#define SLAVE_ID                rtc_ptr->comm_ptr->slave_id

#define RTC_REG(periph_index, reg) rtc_ptr->base_address + \
    (pm_register_address_type)(rtc_ptr->rtc_reg_table->peripheral_offset * periph_index) + rtc_ptr->rtc_reg_table->reg

/*************************************
RTC Api Implementaions
**************************************/
static pm_err_flag_type 
pm_rtc_get_status(uint32 slave_id, uint32 address, uint8 status_mask, boolean *status_val)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 data = 0;

  if (status_val == NULL)
  {
  err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
  err_flag = pm_comm_read_byte(slave_id, address, &data);

  *status_val = (data & status_mask ? TRUE : FALSE);
  }

  return err_flag;
}


/*Get Enable status of RTC */
pm_err_flag_type 
pm_rtc_enable_status(uint32 pmic_index, boolean *enable_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_index);

  if (rtc_ptr == NULL || enable_status == NULL)
  {
  err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
  err_flag = pm_rtc_get_status(SLAVE_ID, RTC_REG(PM_RTC_RW, rw_status1), BIT_7_MASK, enable_status);
  }

  return err_flag;
}


/*Get Reset status of RTC */
pm_err_flag_type 
pm_rtc_reset_status(uint32 pmic_index, boolean *reset_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_index);

  if (rtc_ptr == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PERIPHERAL;
  }
  else if (reset_status == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else if (rtc_ptr->dig_maj_min_ver < RTC_RESET_DETECTION_HW_SUPPORT_REV)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = pm_rtc_get_status(SLAVE_ID, RTC_REG(PM_RTC_RW, rw_status2), BIT_0_MASK, reset_status);
  }

  return err_flag;
}


/* Enable/Disable RTC */
pm_err_flag_type 
pm_rtc_enable(uint32 pmic_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_index);
  uint8 data = 0;

  if (rtc_ptr == NULL)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    data = (enable) ? 0x80: 0x0;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, RTC_REG(PM_RTC_RW, rtc_en_ctl), BIT_7_MASK, data);
  }

  return err_flag;
}

/*To reset the bit0 of rw_status2 regsiter*/
pm_err_flag_type 
pm_rtc_clear_reset_status(uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_index);

  if (rtc_ptr == NULL)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (rtc_ptr->dig_maj_min_ver < RTC_RESET_DETECTION_HW_SUPPORT_REV)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  { 
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, RTC_REG(PM_RTC_RW, rw_status2), BIT_0_MASK, RTC_RESET);
  }

  return err_flag;
}


/*Set RTC time */
pm_err_flag_type 
pm_rtc_set_time_raw(uint32 pmic_index, pm_rtc_time_type * start_time)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_index);
  uint32 data = 0;
  boolean enable_status = FALSE;

  if (rtc_ptr == NULL)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    if (start_time == NULL)
    {
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    data = start_time->sec + ((start_time->msec) + 999) / 1000; //Rounding msec value to seconds

    err_flag = pm_rtc_enable_status(pmic_index, &enable_status);

    if (enable_status == FALSE)
    {
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }

    err_flag = pm_comm_write_byte_array(SLAVE_ID, RTC_REG(PM_RTC_RW, wdata0), RTC_TIME_SEC_BYTE_SIZE, (uint8 *) (&data));
  }

  return err_flag;
}

/* get RTC time*/
pm_err_flag_type 
pm_rtc_get_time_raw(uint32 pmic_index, pm_rtc_time_type * time_ptr)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_index);
  uint32 data = 0;

  if (rtc_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    if (NULL == time_ptr)
    {
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }
    else
    {
      data = time_ptr->sec;
      err_flag = pm_comm_read_byte_array(SLAVE_ID, RTC_REG(PM_RTC_RW, rdata0), RTC_TIME_SEC_BYTE_SIZE, (uint8 *) (&data));
      time_ptr->sec = data;
    }
  }

  //reading the msec data registers on rtc_rw peripheral based on the dig major
  //minor version update.
  if((err_flag == PM_ERR_FLAG_SUCCESS) && (rtc_ptr->dig_maj_min_ver >= 0x50))
  {
    data = 0;
    err_flag = pm_comm_read_byte_array(SLAVE_ID,RTC_REG(PM_RTC_RW,msec_rdata0),RTC_TIME_MSEC_BYTE_SIZE,(uint8 *)(&data));
    time_ptr->msec = (data & RTC_MSEC_DATA_MASK);
  }
  else
  {
    time_ptr->msec = 0;
  }

  return err_flag;
}


/*Set time adjust value*/
pm_err_flag_type 
pm_rtc_set_time_adjust(uint32 pmic_index, uint8 time_adjust)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_index);

  if (rtc_ptr == NULL)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    // As 7th bit is not used, the value of time adj register cannot accept anything greater than 0x7F
    if (time_adjust > MAX_TIME_ADJ)
      {
        return PM_ERR_FLAG_INVALID_PARAMETER;
      }

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, RTC_REG(PM_RTC_RW, time_adj), TIME_ADJ_MASK, time_adjust);
  }

  return err_flag;
}


/* check Alarm status */
pm_err_flag_type 
pm_rtc_alarm_enable_status(uint32 pmic_chip, boolean * enabled)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_chip);
  pm_register_data_type data = 0;

  if (rtc_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (enabled == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_comm_read_byte(SLAVE_ID, RTC_REG(PM_RTC_ALARM, alarm_status1), &data);
  *enabled = (data & BIT_7_MASK) ? TRUE: FALSE;

  return err_flag;
}


/* Enable/disable Alarm */
pm_err_flag_type 
pm_rtc_alarm_enable(uint32 pmic_chip, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_chip);
  pm_register_data_type rtc_enable = 0;

  if (rtc_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  rtc_enable = (enable) ? 0x80: 0x0;
  err_flag = pm_comm_write_byte_mask(SLAVE_ID, RTC_REG(PM_RTC_ALARM, alrm_en_ctl), BIT_7_MASK, rtc_enable);

  return err_flag;
}


/* Set rtc alarm time*/
pm_err_flag_type 
pm_rtc_alarm_set_time(uint32 pmic_chip, pm_rtc_time_type * set_time)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_chip);
  uint32 seconds = 0;
  pm_rtc_time_type current_time;

  //defining local vars for msec_cfg data and msec_alarm
  uint32 msec = 0;
  uint8 read_data = 0;

  if (rtc_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (set_time == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_rtc_get_time_raw(pmic_chip, &current_time);

  // Check if the alarm_msec_cfg register is set; to store the msec value to
  // alarm_msec_data0/1 registers else just program the sec alarm

  //read the alarm_msec_cfg reg to check if msec_alarm is enabled
  //based on digital major minor version update
  if(rtc_ptr->dig_maj_min_ver >= 0x50)
  {
  err_flag = pm_comm_read_byte_mask(SLAVE_ID,RTC_REG(PM_RTC_ALARM,alarm_msec_rtc_cfg),RTC_ALARM_MSEC_CFG_EN_MASK,&read_data);
  }

  // check if bits bit 0 and bit 4 are set before writing to alarm msec registers
  if((rtc_ptr->dig_maj_min_ver >= 0x50) && (RTC_ALARM_MSEC_CFG_EN_MASK == (read_data & RTC_ALARM_MSEC_CFG_EN_MASK)))
  {
    seconds = current_time.sec + set_time->sec;
    msec = current_time.msec + set_time->msec;
    msec &= RTC_MSEC_DATA_MASK;
    err_flag = pm_comm_write_byte_array(SLAVE_ID, RTC_REG(PM_RTC_ALARM, alarm_msec_data0), RTC_TIME_MSEC_BYTE_SIZE, (uint8 *) (&msec));
  }
  else
  {
  seconds = current_time.sec + set_time->sec + (((set_time->msec) + 999) / 1000); //Rounding  off millisec value to seconds
  }

  err_flag = pm_comm_write_byte_array(SLAVE_ID, RTC_REG(PM_RTC_ALARM, alrm_data0), RTC_TIME_SEC_BYTE_SIZE, (uint8 *) (&seconds));

  return err_flag;
}


/* Enable/disable IRQ*/
pm_err_flag_type 
pm_rtc_irq_enable(uint32 pmic_chip, pm_rtc_periph_type periph_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_chip);
  pm_register_address_type irq_reg;
  pm_register_data_type data;

  if (periph_index == PM_RTC_TIMER)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  //0x2 sets '1' bit position 1 which is for RTC Alarm And 0x1 sets '1' to bit position 0 which for RTC RW
  data = (periph_index == PM_RTC_ALARM) ? RTC_ALARM_DATA: RTC_RW_DATA;

  if (rtc_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  irq_reg = enable ? RTC_REG(periph_index, int_en_set): RTC_REG(periph_index, int_en_clr);
  err_flag = pm_comm_write_byte(rtc_ptr->comm_ptr->slave_id, irq_reg, data);

  return err_flag;
}


/*Clear IRQ interrupt */
pm_err_flag_type 
pm_rtc_irq_clear(uint32 pmic_chip, pm_rtc_periph_type periph_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_chip);
  pm_register_data_type data;

  if (periph_index == PM_RTC_TIMER)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  //0x2 sets '1' bit position 1 which is for RTC Alarm And 0x1 sets '1' to bit position 0 which for RTC RW
  data = (periph_index == PM_RTC_ALARM) ? RTC_ALARM_DATA: RTC_RW_DATA;

  if (rtc_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  err_flag = pm_comm_write_byte(rtc_ptr->comm_ptr->slave_id, RTC_REG(periph_index, int_latched_clr), data);
  return err_flag;
}


/* Set IRQ Trigger*/
pm_err_flag_type 
pm_rtc_irq_set_trigger(uint32 pmic_chip, pm_rtc_periph_type periph_index, pm_irq_trigger_type trigger)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type set_type, polarity_high, polarity_low;
  pm_register_data_type mask;
  pm_rtc_data_type * rtc_ptr;

  if (periph_index == PM_RTC_TIMER)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  //0x2 exposes bit position 1 which is for RTC Alarm And 0x1 exposes bit position 0 which for RTC RW
  mask = (periph_index == PM_RTC_ALARM) ? RTC_ALARM_MASK: RTC_RW_MASK;
  rtc_ptr = pm_rtc_get_data(pmic_chip);

  if (rtc_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

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

  err_flag = pm_comm_write_byte_mask(rtc_ptr->comm_ptr->slave_id, RTC_REG(periph_index, int_set_type), mask, set_type);
  err_flag |= pm_comm_write_byte_mask(rtc_ptr->comm_ptr->slave_id, RTC_REG(periph_index, int_polarity_high), mask, polarity_high);
  err_flag |= pm_comm_write_byte_mask(rtc_ptr->comm_ptr->slave_id, RTC_REG(periph_index, int_polarity_low), mask, polarity_low);

  return err_flag;
}


/* get IRQ status */
pm_err_flag_type 
pm_rtc_irq_status(uint32 pmic_chip, pm_rtc_periph_type periph_index, pm_irq_status_type type,
   boolean * status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data;
  pm_register_address_type int_sts;

  if (periph_index == PM_RTC_TIMER)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (status == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  //0x2 exposes bit position 1 which is for RTC Alarm And 0x1 exposes bit position 0 which for RTC RW
  pm_register_data_type mask = (periph_index == PM_RTC_ALARM) ? RTC_ALARM_MASK: RTC_RW_MASK;
  pm_rtc_data_type * rtc_ptr = pm_rtc_get_data(pmic_chip);

  if (rtc_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  switch (type)
  {
    case PM_IRQ_STATUS_RT:
      int_sts = RTC_REG(periph_index, int_rt_sts);
      break;

    case PM_IRQ_STATUS_LATCHED:
      int_sts = RTC_REG(periph_index, int_latched_sts);
      break;

    case PM_IRQ_STATUS_PENDING:
      int_sts = RTC_REG(periph_index, int_pending_sts);
      break;

    default:
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  err_flag = pm_comm_read_byte_mask(SLAVE_ID, int_sts, mask, &data);
  *status = data ? TRUE: FALSE;

  return err_flag;
}


