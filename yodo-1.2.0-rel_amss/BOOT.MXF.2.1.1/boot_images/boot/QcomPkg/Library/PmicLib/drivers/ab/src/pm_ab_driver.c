/*! \file
*
*  \brief  pm_ab_driver.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2018 - 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/ab/src/pm_ab_driver.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when        who          what, where, why
--------    ---          ----------------------------------------------------------
02/06/18     al        Initial revision
========================================================================== */

/*===========================================================================

                    INCLUDE FILES

===========================================================================*/
#include "pm_ab_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACRO AND TYPE DEFINITIONS

===========================================================================*/
#define PMIC_AB_MAX_HW_VER 0x10

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the IBB data */
static pm_ab_data_type *pm_ab_data_arr[PM_MAX_NUM_PMICS];

static pm_ab_register_info_type  ab_reg =
{
  .status1        = 0x08,
  .output_voltage = 0x41,
  .vout_default   = 0x44,
  .module_rdy     = 0x45,
  .enable_ctl     = 0x46,
  .pd_ctl         = 0x47,
  .ibb_en_rdy     = 0x49,
  .current_sense  = 0x4C,
  .ps_ctl         = 0x50,
  .precharge_ctl  = 0x5E,
};



/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_ab_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index)
{
  pm_ab_data_type *ab_ptr = NULL;
  uint8 num_of_peripherals = 0;

  ab_ptr = pm_ab_data_arr[pmic_index];

  if (NULL == ab_ptr)
  {
    num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_AB_NUM, pmic_index);

    if (num_of_peripherals == 0)
    {
      return;
    }

    pm_malloc( sizeof(pm_ab_data_type), (void**)&ab_ptr);
    
    /* Assign Comm ptr */
    ab_ptr->comm_ptr = comm_ptr;

    /* IBB Register Info - Obtaining Data through dal config */
    ab_ptr->ab_reg_table = &ab_reg;

    CORE_VERIFY_PTR(ab_ptr->ab_reg_table);

    ab_ptr->base_address = peripheral_info->base_address;

    ab_ptr->num_of_peripherals = num_of_peripherals;

    pm_ab_data_arr[pmic_index] = ab_ptr;
  }
}


pm_ab_data_type* pm_ab_get_data(uint32 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS)
  {
    return pm_ab_data_arr[pmic_index];
  }
  return NULL;
}

uint8 pm_ab_get_num_peripherals(uint32 pmic_index)
{
  if((pmic_index < PM_MAX_NUM_PMICS) &&
     (pm_ab_data_arr[pmic_index] != NULL))
  {
    return pm_ab_data_arr[pmic_index]->num_of_peripherals;
  }

  return 0;
}


