/*! \file rgb_api.c
*  \n
*  \details This file contains the top-level API wrappers for the RGB
*           peripheral.
*
*  \n &copy; Copyright 2015-2020 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/rgb/src/pm_rgb.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
0/15/20    xp      Remove unused APIs
11/02/15   al      Updaing RGB with latest
04/06/15   aab     Updating pm_rgb_enable
08/20/14   al      Updating comm lib
05/20/14   al      Architecture update
===========================================================================*/

/*===========================================================================
INCLUDE FILES
===========================================================================*/
#include "pm_rgb.h"
#include "pm_rgb_driver.h"

#define ADDRESS(x) (rgb_ptr->base_address + rgb_ptr->rgb_reg_table->x)
#define SLAVE_ID   (rgb_ptr->comm_ptr->slave_id)

pm_err_flag_type pm_rgb_enable
(
  uint32 pmic_chip,
  uint32 rgb_mask,
  boolean enable
)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rgb_data_type *rgb_ptr = pm_rgb_get_data(pmic_chip);
  pm_register_address_type reg = 0;
  pm_register_data_type rgb_en_ctl_val;

  if (rgb_ptr == NULL)
  {
    err_flag =  PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (rgb_mask > PM_RGB_SEGMENT_ALL)
  {
    err_flag =  PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    reg = ADDRESS(en_ctl);
    rgb_en_ctl_val = enable ? (rgb_mask << 5) : 0x00; /*<R: Bit 7, G: Bit6, B: Bit 5>*/
    rgb_mask = rgb_mask << 5;

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, reg, rgb_mask, rgb_en_ctl_val);
  }

  return err_flag;
}

