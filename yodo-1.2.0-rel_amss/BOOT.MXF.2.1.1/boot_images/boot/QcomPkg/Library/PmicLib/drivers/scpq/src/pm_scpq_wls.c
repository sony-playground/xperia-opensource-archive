/*! \file
*
*  \brief  pm_scpq_dc.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2020-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
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

#include "pm_scpq_wls.h"
#include "pm_scpq_driver.h"
// #include "pm_resource_manager.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/
#define ADDRESS(x) (scpq_ptr->base_address + \
                    scpq_ptr->wls_register->peripheral_offset + \
                    scpq_ptr->wls_register->x)

#define SLAVE_ID   (scpq_ptr->comm_ptr->slave_id)

#define PM_SCPQ_WLS_MAX_CURRENT_LIMIT_CFG_MA    5000
#define PM_SCPQ_WLS_CURRENT_LIMIT_CFG_STEP_SIZE 50
#define PM_SCPQ_WLS_ICL_MAX_CFG (PM_SCPQ_WLS_MAX_CURRENT_LIMIT_CFG_MA / PM_SCPQ_WLS_CURRENT_LIMIT_CFG_STEP_SIZE)

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/


pm_err_flag_type pm_scpq_wls_irq_status(uint32 pmic_index, pm_scpq_wls_irq_type irq, pm_irq_status_type type, boolean *status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  uint8 mask = 1 << irq;
  pm_register_address_type int_sts = 0;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if((NULL == scpq_ptr))
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(irq >= PM_SCPQ_WLS_IRQ_INVALID || type >= PM_IRQ_STATUS_INVALID || NULL == status)
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


pm_err_flag_type pm_scpq_wls_icl_cfg(uint32 pmic_index, uint32 current_limit)
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
    if(current_limit > PM_SCPQ_WLS_MAX_CURRENT_LIMIT_CFG_MA)
    {
      data = PM_SCPQ_WLS_ICL_MAX_CFG; // 60
    }
    else
    {
      data = (current_limit + (PM_SCPQ_WLS_CURRENT_LIMIT_CFG_STEP_SIZE / 2)) / PM_SCPQ_WLS_CURRENT_LIMIT_CFG_STEP_SIZE;
    }

    pm_register_address_type wls_icl_cfg_addr = ADDRESS(wls_icl_cfg);

    err_flag = pm_comm_write_byte(SLAVE_ID, wls_icl_cfg_addr, data);
  }

  return err_flag;
}


pm_err_flag_type pm_scpq_wls_set_suspend(uint32 pmic_index, pm_scpq_wls_suspend_type set_type, boolean set_value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(set_type >= PM_SCPQ_WLS_SUSPEND_INVALID)
  {
    err_flag =  PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {  
    pm_register_address_type suspend_addr = ADDRESS(wls_suspend);
    pm_register_data_type data = (set_value) ? 0xFF : 0x00;
    pm_register_data_type mask = 0x1 << set_type;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, suspend_addr, mask, data);
  }

  return err_flag;
}

