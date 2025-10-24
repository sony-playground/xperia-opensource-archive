/*! \file pm_clk_calrc.c
*  \n
*  \brief Implementation file for CAL RC resource type.
*  \n  
*  &copy; Copyright 2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/clk/src/pm_clk_calrc.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who      what, where, why
--------   ---      ----------------------------------------------------------
05/10/2021   dvaddem  New CALRC driver file is created. Moved sleep_clk API's and 
                    added SMPL API's to the driver.
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_clk_calrc.h"
#include "pm_clk_driver.h"

/*===========================================================================

                        TYPE DEFINE AND ENUMS

===========================================================================*/
#define SLAVE_ID        (clk_ptr->comm_ptr->slave_id)

#define CALRC_REG(reg)  ((clk_ptr->clk_calrc_reg_table->base_address) + \
            (pm_register_address_type)(clk_ptr->clk_calrc_reg_table->calrc_register.reg))

/*===========================================================================

                     ACCESS LAYER

===========================================================================*/

pm_err_flag_type 
pm_clk_calrc_smpl_enable(uint32 pmic_index, pm_on_off_type enable_smpl)
{
  pm_err_flag_type          err_flag = PM_ERR_FLAG_SUCCESS;
  pm_clk_data_type          *clk_ptr = pm_clk_get_data(pmic_index);
  pm_register_data_type     data = 0;
  
  if ((clk_ptr == NULL) || (clk_ptr->comm_ptr == NULL) || 
      (clk_ptr->clk_calrc_reg_table == NULL))
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(enable_smpl >= PM_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    data = (enable_smpl == PM_OFF) ? 0x0 : 0xFF;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, CALRC_REG(smpl_ctl1), 0x80, data);
  }

  return err_flag;  
}

pm_err_flag_type 
pm_clk_calrc_set_smpl_delay(uint32 pmic_index, uint32 delay_setting)
{
  pm_err_flag_type          err_flag = PM_ERR_FLAG_SUCCESS;
  pm_clk_data_type          *clk_ptr = pm_clk_get_data(pmic_index);
  pm_register_data_type     data = 0;
  
  if ((clk_ptr == NULL) || (clk_ptr->comm_ptr == NULL) || 
      (clk_ptr->clk_calrc_reg_table == NULL))
  {
      err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (delay_setting <= 100)
  {
    data = 0x0;
  }
  else if (delay_setting <= 200)
  {
    data = 0x1;
  }
  else if (delay_setting <= 400)
  {
    data = 0x2;
  }
  else if (delay_setting <= 800)
  {
    data = 0x3;
  }
  else if ((clk_ptr->clk_calrc_reg_table->dig_maj_min == 0x80) && 
           (delay_setting <= 1600))
  {
    data = 0x4;
  }
  else
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  
  if(err_flag == PM_ERR_FLAG_SUCCESS)
  {
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, CALRC_REG(smpl_ctl1), 0x07, data);
  }

  return err_flag;  
}

pm_err_flag_type 
pm_clk_calrc_enable(uint32 pmic_index, pm_on_off_type enable_calrc)
{
  pm_err_flag_type          err_flag = PM_ERR_FLAG_SUCCESS;
  pm_clk_data_type          *clk_ptr = pm_clk_get_data(pmic_index);
  
  if ((clk_ptr == NULL) || (clk_ptr->comm_ptr == NULL) || 
      (clk_ptr->clk_calrc_reg_table == NULL))
  {
    err_flag = PM_ERR_FLAG_INVALID_PERIPHERAL;
  }
  else if(enable_calrc >= PM_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    err_flag = pm_comm_write_byte(SLAVE_ID, CALRC_REG(calrc_enable), enable_calrc);
  }

  return err_flag;  
}

pm_err_flag_type 
pm_clk_calrc_coincell_config(uint32 pmic_index, pm_clk_calrc_coincap_type coincap_type)
{
  pm_err_flag_type          err_flag = PM_ERR_FLAG_SUCCESS;
  pm_clk_data_type          *clk_ptr = pm_clk_get_data(pmic_index);
  pm_register_data_type     data = 0;
  
  if ((clk_ptr == NULL) || (clk_ptr->comm_ptr == NULL) || 
      (clk_ptr->clk_calrc_reg_table == NULL))
  {
      err_flag = PM_ERR_FLAG_INVALID_PERIPHERAL;
  }
  else if(coincap_type >= PM_COINCAP_TYPE_INVALID)
  {
      err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    data = (coincap_type == PM_COINCAP_TYPE_WEAK) ? 0x0 : 0xFF; 
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, CALRC_REG(calrc_cfg), 0x02, data);
  }

  return err_flag;  
}

