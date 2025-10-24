/*! \file pm_coincell.c
*  
*  \brief  pm_coincell.c
*    
*  &copy; Copyright 2014-2020 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/coincell/src/pm_coincell.c#1 $ 

$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
09/16/14   akm     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_coincell.h"
#include "pm_coincell_driver.h"
#include "pm_comm.h"

#define CC_RSET_MASK 0x3
#define CC_VSET_MASK 0x3

#define CC_REG_ADDR(reg) 	((coincell_ptr->base_address) + (coincell_ptr->coincell_reg_table->reg))


pm_err_flag_type 
pm_coincell_enable(uint8 pmic_chip, pm_on_off_type enable)
{
  pm_err_flag_type err_flag           = PM_ERR_FLAG_SUCCESS;
  pm_coincell_data_type *coincell_ptr = pm_coincell_get_data(pmic_chip);
  uint8 data;

  if (coincell_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  if (PM_OFF == enable)
  {
    data = 0;
  }
  else
  {
    data = 0x80;
  }

  err_flag = pm_comm_write_byte_mask(coincell_ptr->comm_ptr->slave_id, CC_REG_ADDR(en_ctl), 0x80, data);
  return err_flag;
}


pm_err_flag_type 
pm_coincell_get_status(uint8 pmic_chip, boolean  *status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_coincell_data_type *coincell_ptr = pm_coincell_get_data(pmic_chip);
  pm_register_data_type en_ctl_val = 0;
 
  if (coincell_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
 
  err_flag  = pm_comm_read_byte(coincell_ptr->comm_ptr->slave_id, CC_REG_ADDR(en_ctl), &en_ctl_val);

  if (en_ctl_val & (0x80))
  {
    *status = TRUE;
  }
  else
  {
    *status = FALSE;
  }
  return err_flag;
}


pm_err_flag_type 
pm_coincell_set_charge_current_limit_resistor(uint8 pmic_chip, uint8 coin_chg_rset_value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_coincell_data_type *coincell_ptr = pm_coincell_get_data(pmic_chip);

  if (coincell_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (coin_chg_rset_value >= PM_COINCELL_RSET_INVALID)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  
  err_flag = pm_comm_write_byte_mask(coincell_ptr->comm_ptr->slave_id,CC_REG_ADDR(coin_chg_rset),CC_RSET_MASK,coin_chg_rset_value);

  return err_flag;
}

pm_err_flag_type 
pm_coincell_set_charging_voltage(uint8 pmic_chip, uint32 coin_chg_vset_value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_coincell_data_type *coincell_ptr = pm_coincell_get_data(pmic_chip);

  if (coincell_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (coin_chg_vset_value >= PM_COINCELL_VSET_INVALID)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag   = pm_comm_write_byte_mask(coincell_ptr->comm_ptr->slave_id,CC_REG_ADDR(coin_chg_vset),CC_VSET_MASK,coin_chg_vset_value);

  return err_flag;
}


