/*! \file
*
*  \brief  pm_eusb.c driver implementation.
*  &copy;
*  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/eusb/src/pm_eusb.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who      what, where, why
--------   ---      -------------------------------------------------------------
01/06/22   akm     Implement EUSB driver
=============================================================================== */

/*=============================================================================

          INCLUDE FILES

===============================================================================*/
#include "pm_eusb.h"
#include "pm_eusb_driver.h"

/*===========================================================================
                       MACRO DECLARATIONS
===========================================================================*/

#define ADDRESS(x) (eusb_ptr->base_address + eusb_ptr->eusb_reg_table->x)
#define SLAVE_ID   (eusb_ptr->comm_ptr->slave_id)

/*===========================================================================

FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type 
pm_eusb_enable(uint32 pmic_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_eusb_data_type *eusb_ptr  = pm_eusb_get_data(pmic_index);

  if(NULL == eusb_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_data_type mask = 0x80;  // <0>
    pm_register_data_type data = enable ? 0x80 : 0;

    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, ADDRESS(eusb_eusb_en), mask, data);
  }

  return err_flag;
}


