/*! \file vib_api.c
*  \n
*  \details This file contains the top-level API wrappers for the Vib
*           peripheral.
*
*  \n &copy; Copyright 2014-2019, 2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
$Header: //components/rel/core.boot/6.0/QcomPkg/Library/PmicLib/drivers/vib/src/pm_vib.c#3 $
$Author: pwbldsvc $
$DateTime: 2021/11/25 13:43:41 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/20/14   al       Updating comm lib 
05/20/14   al       Architecture update  
========================================================================== */

/*===========================================================================
INCLUDE FILES
===========================================================================*/

#include "pm_resource_manager.h"
#include "pm_vib.h"
#include "pm_vib_driver.h"
#include "pm_comm.h"

pm_err_flag_type pm_vib_enable
(
uint32            pmic_chip,
pm_vib_which_type vib,
pm_vib_mode_type  mode,
boolean           enable
)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg_vib_en_ctl = 0;
  pm_register_data_type reg_data = 0;
  pm_register_address_type periph_index = (pm_register_address_type)vib;
  pm_vib_data_type *vib_ptr = pm_vib_get_data(pmic_chip);

  if((NULL == vib_ptr) || (mode != PM_VIB_MODE__MANUAL))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if(periph_index >= vib_ptr->num_of_peripherals)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  
  reg_vib_en_ctl = vib_ptr->base_address + (vib_ptr->vib_reg_table->peripheral_offset * periph_index) + vib_ptr->vib_reg_table->en_ctl;
  reg_data = (enable == TRUE ? 0x80 : 0x00);
  err_flag |= pm_comm_write_byte(vib_ptr->comm_ptr->slave_id, reg_vib_en_ctl, reg_data);
  
  return err_flag;

}


pm_err_flag_type pm_vib_set_volt
(
uint32             pmic_chip,
pm_vib_which_type  vib,
uint16             voltage
)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type reg_vib_vset_lb = 0;
  pm_register_address_type reg_vib_vset_ub = 0;
  pm_register_address_type periph_index = (pm_register_address_type)vib;
  pm_vib_data_type *vib_ptr = pm_vib_get_data(pmic_chip);

  if(NULL == vib_ptr) 
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if(periph_index >= vib_ptr->num_of_peripherals) 
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(voltage < vib_ptr->vib_data->min_voltage ||
      voltage > vib_ptr->vib_data->max_voltage)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  
  reg_vib_vset_lb = vib_ptr->base_address + (vib_ptr->vib_reg_table->peripheral_offset * periph_index) + vib_ptr->vib_reg_table->vset_lb;
  reg_vib_vset_ub = vib_ptr->base_address + (vib_ptr->vib_reg_table->peripheral_offset * periph_index) + vib_ptr->vib_reg_table->vset_ub;
  
  err_flag |= pm_comm_write_byte(vib_ptr->comm_ptr->slave_id, reg_vib_vset_lb, (voltage & 0xFF));
  err_flag |= pm_comm_write_byte(vib_ptr->comm_ptr->slave_id, reg_vib_vset_ub, ((voltage >> 8) & 0xFF));
  

  return err_flag;

}

pm_err_flag_type pm_vib_init(pm_vib_data_type *vib_ptr, pm_vib_which_type vib)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

/*Vib perepheral do not exist PMI8994.  Need to use Haptics instead

  pm_register_address_type reg_vib =  0x0;
  pm_register_data_type data = 0x0;


  reg_vib = VIB_CFG1_REG;
  //select Vib Actuator type
  errFlag = pm_comm_write_byte_mask(vib_ptr->comm_ptr->slave_id, reg_vib, VIB_CFG1_REG_MASK, VIB_CFG1_ACTUATOR_TYPE_VALUE, 0);
  if (errFlag != PM_ERR_FLAG_SUCCESS)
  {
      goto pm_vib_init_exit;
  }

  if (VIB_CFG1_ACTUATOR_TYPE_VALUE == 1) // ERM actuator
  {
      //disable auto resonance
      reg_vib = VIB_AUTO_RES_CFG_REG;
      data = (VIB_AUTO_RES_CFG_LRA_NO_AUTO_RES_VAL << VIB_AUTO_RES_CFG_LRA_AUTO_RES_MODE_BIT_SHIFT);

      //Configure Auto Resonance configuration
      errFlag = pm_comm_write_byte_mask(vib_ptr->comm_ptr->slave_id, reg_vib, 0x7F, data, 0);
      if (errFlag != PM_ERR_FLAG_SUCCESS)
      {
        goto pm_vib_init_exit;
      }
  }

  else
  {
      // if the mode is QWD, then set ZXD Calibration freq as 0
      if (2 == VIB_AUTO_RES_CFG_LRA_AUTO_RES_MODE_VAL)
      {
        data = ((VIB_AUTO_RES_CFG_LRA_AUTO_RES_MODE_VAL << VIB_AUTO_RES_CFG_LRA_AUTO_RES_MODE_BIT_SHIFT) |
                    (VIB_AUTO_RES_CFG_LRA_HIGH_Z_VAL << VIB_AUTO_RES_CFG_LRA_HIGH_Z_BIT_SHIFT) |
                    (0));
      }
      else
      {
        data = ((VIB_AUTO_RES_CFG_LRA_AUTO_RES_MODE_VAL << VIB_AUTO_RES_CFG_LRA_AUTO_RES_MODE_BIT_SHIFT) |
                    (VIB_AUTO_RES_CFG_LRA_HIGH_Z_VAL << VIB_AUTO_RES_CFG_LRA_HIGH_Z_BIT_SHIFT) |
                    (VIB_AUTO_RES_CFG_LRA_RES_CALIB_VAL));
      }

      reg_vib = VIB_AUTO_RES_CFG_REG;

      //Configure Auto Resonance configuration
      errFlag = pm_comm_write_byte_mask(vib_ptr->comm_ptr->slave_id, reg_vib, 0x7F, data, 0);
      if (errFlag != PM_ERR_FLAG_SUCCESS)
      {
        goto pm_vib_init_exit;
      }

      //Configure CFG2 LRA_RES_TYPE to Square type
      reg_vib = VIB_CFG2_REG;
      data = VIB_CFG2_LRA_RES_TYPE_VAL;
      errFlag = pm_comm_write_byte_mask(vib_ptr->comm_ptr->slave_id, reg_vib, 0x01, data, 0);
      if (errFlag != PM_ERR_FLAG_SUCCESS)
      {
        goto pm_vib_init_exit;
      }

      //Configure Rate_CFG1 and Rate_CFG2 for LRA resonant freq of 205 Hz
      //Rate_CFG1 will be 207 and Rate_CFG2 will be 3 for LRA resonant (205 Hz - Value 975)
      reg_vib = VIB_RATE_CFG1_REG;
      data = VIB_RATE_CFG1_VAL;
      errFlag = pm_comm_write_byte_mask(vib_ptr->comm_ptr->slave_id, reg_vib, 0xFF, data, 0);
      if (errFlag != PM_ERR_FLAG_SUCCESS)
      {
        goto pm_vib_init_exit;
      }

      reg_vib = VIB_RATE_CFG2_REG;
      data = VIB_RATE_CFG2_VAL;
      errFlag = pm_comm_write_byte_mask(vib_ptr->comm_ptr->slave_id, reg_vib, 0xFF, data, 0);
      if (errFlag != PM_ERR_FLAG_SUCCESS)
      {
        goto pm_vib_init_exit;
      }

  }

  //Configure Slew rate
  reg_vib = VIB_SLEW_CFG;
  data = VIB_SLEW_RATE_VAL;
  errFlag = pm_comm_write_byte_mask(vib_ptr->comm_ptr->slave_id, reg_vib, 0x01, data, 0);
  if (errFlag != PM_ERR_FLAG_SUCCESS)
  {
      goto pm_vib_init_exit;
  }

  //Configure ILIM
  reg_vib = VIB_ILIM_REG;
  errFlag = pm_comm_write_byte_mask(vib_ptr->comm_ptr->slave_id, reg_vib, VIB_ILIM_SEL_MASK, VIB_ILIM_SEL_VAL, 0);
  if (errFlag != PM_ERR_FLAG_SUCCESS)
  {
      goto pm_vib_init_exit;
  }

  //Configure Internal PWM Freq Sel
  reg_vib = VIB_INTERNAL_PWM_REG;
  errFlag = pm_comm_write_byte_mask(vib_ptr->comm_ptr->slave_id, reg_vib, VIB_INTERNAL_PWM_FREQ_SEL_MASK, VIB_INTERNAL_PWM_FREQ_SEL_VAL, 0);
  if (errFlag != PM_ERR_FLAG_SUCCESS)
  {
      goto pm_vib_init_exit;
  }

  //Configure External PWM Freq Sel
  reg_vib = VIB_EXTERNAL_PWM_REG;
  errFlag = pm_comm_write_byte_mask(vib_ptr->comm_ptr->slave_id, reg_vib, VIB_EXTERNAL_PWM_FREQ_SEL_MASK, VIB_EXTERNAL_PWM_FREQ_SEL_VAL, 0);
  if (errFlag != PM_ERR_FLAG_SUCCESS)
  {
      goto pm_vib_init_exit;
  }

  //Configure PWM Capacitance
  reg_vib = VIB_PWM_CAP_REG;
  errFlag = pm_comm_write_byte_mask(vib_ptr->comm_ptr->slave_id, reg_vib, VIB_PWM_CAP_SEL_MASK, VIB_PWM_CAP_SEL_VAL, 0);
  if (errFlag != PM_ERR_FLAG_SUCCESS)
  {
      goto pm_vib_init_exit;
  }

pm_vib_init_exit:
*/
  return errFlag;
}
