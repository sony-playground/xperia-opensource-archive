/*! \file pm_pon.c
*  \n
*  \brief This file contains the implementation of the PowerON peripheral driver APIs.
*  \n
*  \n &copy; Copyright 2012-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/pon/src/pm_pon_key_reset.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/03/18   akm     Updated pm_err_flags
02/02/17   akm     Moved PMIC,SPMI out to Systemdrivers
11/14/16   akt     Removed compiler warnings(CR-1038901)
07/17/16   aab     Updated pm_pon_ps_hold_cfg() to support xbl_sec_image
03/28/16   aab     Added pm_pon_gp_reset_cfg() and pm_pon_get_reset_config_val()
02/16/15   vtw     Updated for the APPs level API support.
06/24/13   ps      Added PON Stage3 reset config API CR#495834
02/27/13   kt      Added PON Reasons and IRQ related APIs
01/24/13   umr     Add new version support.
11/20/12   umr     Created
========================================================================== */

/*===========================================================================
                  INCLUDE
===========================================================================*/
#include "pm_pon.h"
#include "pmio_pon.h"
#include "hw_module_type.h"
#include "device_info.h"
#include "DALSys.h"
#include "pm_comm.h"
#include "pm_pon_cfg.h"
#include "pm_target_information.h"
#include "pm_utils.h"
#include "bare_metal_info.h"
#include "time_service.h"

/*===========================================================================
                        TYPE DEFINITIONS
===========================================================================*/

#define PON_PBS_SUBTYPE 0x8

/* length of array */
#define ARRAY_LENGTH(x)  (sizeof(x) / sizeof(x[0]))

#define PON_RESET_CFG_INVALID_VAL                         0xFF

/*===========================================================================
                        GLOBAL
===========================================================================*/

typedef enum {
  PM_PON_IRQ_KPDPWR_N_S2          = 0, /* S2 PowerKey */
  PM_PON_IRQ_RESIN_N_S2           = 1, /* S2 Resin*/
  PM_PON_IRQ_RESIN_AND_KPDPWR_S2  = 2, /* S2 Resin and PowerKey */
  PM_PON_IRQ_PMIC_WDOG_S2         = 3, /* S2 Watchdog */
  PM_PON_IRQ_PS_HOLD              = 4, /* PS HOLD */
  PM_PON_IRQ_SW_RESET             = 5, /* SW Reset */
  PM_PON_IRQ_RESIN_N_DEB          = 6, /* Resin Debounce */
  PM_PON_IRQ_KPD_PWR_N_DEB        = 7, /* */
  PM_PON_IRQ_INVALID                   /* */
}pm_pon_irq_type;

typedef struct 
{
  uint16 s1_timer_addr; 
  uint16 s1_timer_mask; 
  uint16 s2_timer_addr;
  uint16 s2_timer_mask;
  uint16 reset_ctl_addr;
  uint16 reset_ctl2_addr;
  uint16 reset_en_mask;
  uint16 reset_type_mask;
  pm_pon_irq_type     irq         :8;
  pm_irq_trigger_type trigger_type:8;
}pon_reset_reg_info_type;

static pon_reset_reg_info_type
pon_kpdpwr_reg =
{
  .s1_timer_addr     = PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_ADDR,
  .s1_timer_mask     = PMIO_PON_PBS_KPDPWR_N_RESET_S1_TIMER_S1_TIMER_BMSK,
  .s2_timer_addr     = PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_ADDR,
  .s2_timer_mask     = PMIO_PON_PBS_KPDPWR_N_RESET_S2_TIMER_S2_TIMER_BMSK,
  .reset_ctl_addr    = PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_ADDR,
  .reset_ctl2_addr   = PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_ADDR,
  .reset_en_mask     = PMIO_PON_PBS_KPDPWR_N_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  .reset_type_mask   = PMIO_PON_PBS_KPDPWR_N_RESET_S2_SW_CTL_RESET_TYPE_BMSK,
  .irq               = PM_PON_IRQ_KPDPWR_N_S2,
  .trigger_type      = PM_IRQ_TRIGGER_ACTIVE_HIGH,
};

static pon_reset_reg_info_type
pon_resin_reg =
{
  .s1_timer_addr     = PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_ADDR,
  .s1_timer_mask     = PMIO_PON_PBS_RESIN_N_RESET_S1_TIMER_S1_TIMER_BMSK,
  .s2_timer_addr     = PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_ADDR,
  .s2_timer_mask     = PMIO_PON_PBS_RESIN_N_RESET_S2_TIMER_S2_TIMER_BMSK,
  .reset_ctl_addr    = PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_ADDR,
  .reset_ctl2_addr   = PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_ADDR,
  .reset_en_mask     = PMIO_PON_PBS_RESIN_N_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  .reset_type_mask   = PMIO_PON_PBS_RESIN_N_RESET_SW_CTL_RESET_TYPE_BMSK,
  .irq               = PM_PON_IRQ_RESIN_N_S2,
  .trigger_type      = PM_IRQ_TRIGGER_ACTIVE_HIGH,
};

static pon_reset_reg_info_type
pon_resin_and_kpdpwr_reg =
{
  .s1_timer_addr   = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_ADDR,
  .s1_timer_mask   = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S1_TIMER_S1_TIMER_BMSK,
  .s2_timer_addr   = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_ADDR,
  .s2_timer_mask   = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_TIMER_S2_TIMER_BMSK,
  .reset_ctl_addr  = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_ADDR,
  .reset_ctl2_addr = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_ADDR,
  .reset_en_mask   = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_S2_CTL2_S2_RESET_EN_BMSK,
  .reset_type_mask = PMIO_PON_PBS_RESIN_AND_KPDPWR_RESET_SW_CTL_RESET_TYPE_BMSK,
  .irq             = PM_PON_IRQ_RESIN_AND_KPDPWR_S2,
  .trigger_type    = PM_IRQ_TRIGGER_ACTIVE_HIGH,
};

static pon_reset_reg_info_type *pon_reset_reg[] =
{
  [PM_PON_RESET_SOURCE_KPDPWR]           = &pon_kpdpwr_reg,
  [PM_PON_RESET_SOURCE_RESIN]            = &pon_resin_reg,
  [PM_PON_RESET_SOURCE_RESIN_AND_KPDPWR] = &pon_resin_and_kpdpwr_reg,
  [PM_PON_RESET_SOURCE_RESIN_OR_KPDPWR]  = NULL,
  [PM_PON_RESET_SOURCE_GP1]              = NULL,
  [PM_PON_RESET_SOURCE_GP2]              = NULL,
};

static pm_register_data_type pon_reset_cfg_val[] =
{
  [PM_PON_RESET_CFG_WARM_RESET]                                         = 0x01,
  [PM_PON_RESET_CFG_HARD_RESET]                                         = 0x07,
  [PM_PON_RESET_CFG_NORMAL_SHUTDOWN]                                    = 0x04,
  [PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET]                       = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN]                         = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN]                    = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET]                  = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN]          = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_SHUTDOWN]         = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_SHUTDOWN]    = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_SHUTDOWN]                           = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_HARD_RESET]                         = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_HARD_RESET]       = PON_RESET_CFG_INVALID_VAL,
  [PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_HARD_RESET]  = PON_RESET_CFG_INVALID_VAL,
};

static uint32
pon_s1_timer_val[] =
{ 0, 32, 56, 80, 128, 184, 272, 408, 608, 904, 1352, 2048, 3072, 4480, 6720, 10256 }; //Unit:ms

static uint32
pon_s2_timer_val[] =
{ 0, 10, 50, 100, 250, 500, 1000, 2000 }; //Unit:ms

static uint32
pon_s3_timer_val[] =
{ 0, 8, 16, 32, 63, 125, 250, 500, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 }; //For Tokei 2.0 and later S3_TIMER, unit:ms

static uint32
pon_s3_timer_tokei_v1_val[] =
{ 0, 2000, 4000, 8000, 16000, 32000, 64000, 128000 }; //For Tokei 1.x S3_TIMER, unit:ms


/*=========================================================================
      Function Prototypes
==========================================================================*/

pm_err_flag_type
pm_pon_irq_enable(uint32 pmic_device_index, pm_pon_irq_type irq, boolean enable);

pm_err_flag_type
pm_pon_irq_clear(uint32  pmic_device_index, pm_pon_irq_type irq);

pm_err_flag_type
pm_pon_irq_set_trigger(uint32 pmic_device_index, pm_pon_irq_type irq, pm_irq_trigger_type trigger);

uint8
pm_pon_get_upper_idx(uint32 data_value, uint32 *data_list, uint8 list_count);

/*=========================================================================
      Functions
==========================================================================*/

/*internal function to return slave id*/
static pm_err_flag_type pm_pon_get_pon_info(uint8 pmic_device_index, uint32 *pon_slave_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if (NULL == pon_slave_id)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  
  err_flag = pm_pon_init();

  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    err_flag = pm_get_slave_id(pmic_device_index, 0, pon_slave_id);
  }

  return err_flag;
}

/* =========================================================================
**  Function : pm_pon_reset_source_cfg
** =========================================================================*/

pm_err_flag_type
pm_pon_reset_source_cfg(uint32 pmic_device_index, pm_pon_reset_source_type reset_source,
                        uint32 s1_timer_ms, uint32 s2_timer_ms, pm_pon_reset_cfg_type reset_cfg)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 reset_en, reset_val = 0;
  uint8 s1_timer_id = 0;
  uint8 s2_timer_id = 0;
  uint32 slave_id = 0;
  pon_reset_reg_info_type *reset_reg = NULL;

  if (reset_cfg >= PM_PON_RESET_CFG_INVALID)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  reset_reg = pon_reset_reg[reset_source];
  if (reset_reg == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /*read current enabled status*/
  err_flag = pm_comm_read_byte(slave_id, reset_reg->reset_ctl2_addr, &reset_en, 0);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /*isable and wait for 8 sleep clock cycle*/
  err_flag = pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, 0x0, 0);

  //disable and clear irq
  err_flag |= pm_pon_irq_clear(PMIC_A, reset_reg->irq);
  err_flag |= pm_pon_irq_enable(PMIC_A, reset_reg->irq, FALSE);


  /* Calc and configure S1 and S2 timer. Get the upper limit if a value falls in between */
  s1_timer_id = pm_pon_get_upper_idx(s1_timer_ms, pon_s1_timer_val, ARRAY_LENGTH(pon_s1_timer_val));
  s2_timer_id = pm_pon_get_upper_idx(s2_timer_ms, pon_s2_timer_val, ARRAY_LENGTH(pon_s2_timer_val));
  err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->s1_timer_addr, reset_reg->s1_timer_mask, s1_timer_id,0);
  busywait(300);
  err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->s2_timer_addr, reset_reg->s2_timer_mask, s2_timer_id,0);
  busywait(300);

  //set type
  err_flag |= pm_pon_irq_set_trigger(PMIC_A, reset_reg->irq, reset_reg->trigger_type);

  //reenable s2 reset_reset_en
  /* Configure reset value */
  reset_val = pon_reset_cfg_val[reset_cfg];
  if (reset_val < PON_RESET_CFG_INVALID_VAL)
  {
    err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl_addr, reset_reg->reset_type_mask, reset_val, 0);
    busywait(300);
  }
  else
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  /* Enable reset if it was already in enable state */
  //disable and clear irq
    err_flag |= pm_pon_irq_enable(PMIC_A, reset_reg->irq, FALSE);
    err_flag |= pm_pon_irq_clear(PMIC_A, reset_reg->irq);

    err_flag |= pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, 0xFF, 0);

  //disable irq, clear irq, enable irq
    err_flag |= pm_pon_irq_clear(PMIC_A, reset_reg->irq);
    err_flag |= pm_pon_irq_enable(PMIC_A, reset_reg->irq, FALSE);
    err_flag |= pm_pon_irq_enable(PMIC_A, reset_reg->irq, TRUE);

  return err_flag;
}

pm_err_flag_type
pm_pon_reset_source_ctl(uint32 pmic_device_index, pm_pon_reset_source_type reset_source, pm_on_off_type on_off)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  pon_reset_reg_info_type *reset_reg = NULL;
  uint8 data = (on_off == PM_ON) ? 0xFF : 0;

  reset_reg = pon_reset_reg[reset_source];

  if (NULL == reset_reg)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);

    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      err_flag = pm_comm_write_byte_mask(slave_id, reset_reg->reset_ctl2_addr, reset_reg->reset_en_mask, data, 0);
      busywait(300);
    }
  }

  return err_flag;
}

pm_err_flag_type
pm_pon_stage3_reset_source_cfg(uint32 pmic_device_index, pm_pon_reset_source_type reset_source, uint32 s3_timer_ms)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 s3_timer_id = 0;
  uint32 slave_id = 0;
  pm_register_data_type pon_pbs_revision[2];
  pm_register_data_type pon_perph_type[2];

  if (reset_source > PM_PON_RESET_SOURCE_RESIN_OR_KPDPWR)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }


  /* Write to Set Stage 3 reset source, write once register */
  err_flag = pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_RESET_S3_SRC_ADDR, PMIO_PON_PBS_RESET_S3_SRC_RMSK, reset_source, 0);
  busywait(300);

  /* Calc S3 timer id, unlock secure register and set stage 3 reset timer*/
  pm_comm_read_byte_array(slave_id, PMIO_PON_PBS_REVISION1_ADDR, 2, pon_pbs_revision, 0);
  pm_comm_read_byte_array(slave_id, PMIO_PON_PBS_PERPH_TYPE_ADDR, 2, pon_perph_type, 0);
  if((pon_perph_type[0] == PM_HW_MODULE_PON) && (pon_perph_type[1] == PON_PBS_SUBTYPE)
      && (pon_pbs_revision[0] < 2) && (pon_pbs_revision[1] < 2))
  {
    // For Tokei v1.x chip
    s3_timer_id = pm_pon_get_upper_idx(s3_timer_ms, pon_s3_timer_tokei_v1_val, ARRAY_LENGTH(pon_s3_timer_tokei_v1_val));
  }
  else
  {
    s3_timer_id = pm_pon_get_upper_idx(s3_timer_ms, pon_s3_timer_val, ARRAY_LENGTH(pon_s3_timer_val));
  }

  err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_RESET_S3_TIMER_ADDR, PMIO_PON_PBS_RESET_S3_TIMER_RMSK, s3_timer_id, 0);
  busywait(300);
  
  return err_flag;
}

pm_err_flag_type
pm_pon_irq_enable(uint32 pmic_device_index, pm_pon_irq_type irq, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 mask = 1 << irq;
  pm_register_address_type irq_reg = enable ? PMIO_PON_PBS_INT_EN_SET_ADDR : PMIO_PON_PBS_INT_EN_CLR_ADDR;

  uint32 slave_id = 0;

  if (irq >= PM_PON_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      err_flag = pm_comm_write_byte(slave_id, irq_reg, mask, 0);
    }
  }

  return err_flag;
}

pm_err_flag_type
pm_pon_irq_clear(uint32  pmic_device_index, pm_pon_irq_type irq)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1 << irq;

  if (irq >= PM_PON_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);
    if (err_flag == PM_ERR_FLAG_SUCCESS)
    {
      err_flag = pm_comm_write_byte(slave_id, PMIO_PON_PBS_INT_LATCHED_CLR_ADDR, mask, 0);
    }
  }

  return err_flag;
}

pm_err_flag_type
pm_pon_irq_set_trigger(uint32 pmic_device_index, pm_pon_irq_type irq, pm_irq_trigger_type trigger)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  uint8 mask = 1 << irq;
  uint8 set_type = 0;
  uint8 polarity_high = 0;
  uint8 polarity_low = 0;

  if (irq >= PM_PON_IRQ_INVALID)
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

  err_flag = pm_pon_get_pon_info(pmic_device_index, &slave_id);

  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    err_flag = pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_INT_SET_TYPE_ADDR, mask, set_type, 0);
    err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_INT_POLARITY_HIGH_ADDR, mask, polarity_high, 0);
    err_flag |= pm_comm_write_byte_mask(slave_id, PMIO_PON_PBS_INT_POLARITY_LOW_ADDR, mask, polarity_low, 0);
  }

  return err_flag;
}

uint8
pm_pon_get_upper_idx(uint32 data_value, uint32 *data_list, uint8 list_count)
{
  uint8 idx = 0;

  if ((data_list == NULL ) || (list_count == 0 ))
  {
    CORE_VERIFY(0);
  }

  for (idx = 0; idx < list_count-1; idx++)
  {
    if (data_value <= data_list[idx])
      break;
  }

  return idx;
}