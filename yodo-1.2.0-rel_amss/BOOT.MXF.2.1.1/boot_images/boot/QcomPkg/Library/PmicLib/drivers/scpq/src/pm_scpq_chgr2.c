/*! \file
*
*  \brief  pm_scpq_chgr2.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    ----------------------------------------------------------
14/01/22    xp     Initial revision
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_scpq_chgr.h"
#include "pm_scpq_driver.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/

#define ADDRESS(x) (scpq_ptr->base_address + \
                    scpq_ptr->chgr2_register->peripheral_offset + \
                    scpq_ptr->chgr2_register->x)

#define SLAVE_ID   (scpq_ptr->comm_ptr->slave_id)

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type pm_scpq_chgr2_get_bat_2s_chg_cfg(uint32 pmic_index, boolean* is_2s_bat)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_data_type *scpq_ptr = pm_scpq_get_data(pmic_index);

  if(NULL == scpq_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == is_2s_bat)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type address = ADDRESS(bat_2s_charge_cfg);
    pm_register_data_type data = 0x0;
    err_flag = pm_comm_read_byte(SLAVE_ID, address, &data);

    *is_2s_bat = (data & 0x01) ? TRUE : FALSE;
  }

  return err_flag;
}

