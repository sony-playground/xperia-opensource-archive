/*! \file
*
*  \brief  pm_ibb_driver.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2014 - 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/ibb/src/pm_ibb_driver.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when        who        what, where, why
--------    ---        ----------------------------------------------------------
11/12/17    aab        Moved common Register address defination to driver file
08/20/14    al         Updating comm lib
08/29/14    al         KW fixes
05/20/14    al         Architecture update
04/30/14    al         Initial revision
========================================================================== */

/*===========================================================================

                    INCLUDE FILES

===========================================================================*/
#include "pm_ibb_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACRO AND TYPE DEFINITIONS

===========================================================================*/
#define PMIC_IBB_MAX_HW_VER 0x01

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the IBB data */
static pm_ibb_data_type *pm_ibb_data_arr[PM_MAX_NUM_PMICS];

static pm_ibb_register_info_type ibb_reg =
{
  0x008, 0x040, 0x041, 0x045, 0x046, 0x058, 0x05A
};


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_ibb_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index)
{
  pm_ibb_data_type *ibb_ptr = NULL;
  uint8 num_of_peripherals = 0;

  ibb_ptr = pm_ibb_data_arr[pmic_index];

  if (NULL == ibb_ptr)
  {
    num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_IBB_NUM, pmic_index);
    if (num_of_peripherals == 0)
    {
      return;
    }

    pm_malloc( sizeof(pm_ibb_data_type), (void**)&ibb_ptr);
    
    ibb_ptr->dig_maj_min_ver = ((peripheral_info->digital_major_version << 4) |
                                (peripheral_info->digital_minor_version));

    CORE_VERIFY(ibb_ptr->dig_maj_min_ver <= PMIC_IBB_MAX_HW_VER);

    /* Assign Comm ptr */
    ibb_ptr->comm_ptr = comm_ptr;

    /* IBB Register Info - Obtaining Data through dal config */
    ibb_ptr->ibb_reg_table = &ibb_reg;
    CORE_VERIFY_PTR(ibb_ptr->ibb_reg_table);

    ibb_ptr->base_address = peripheral_info->base_address;

    ibb_ptr->num_of_peripherals = num_of_peripherals;

    pm_ibb_data_arr[pmic_index] = ibb_ptr;
  }
}


pm_ibb_data_type* pm_ibb_get_data(uint32 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS)
  {
    return pm_ibb_data_arr[pmic_index];
  }
  return NULL;
}

uint8 pm_ibb_get_num_peripherals(uint32 pmic_index)
{
  if((pmic_index < PM_MAX_NUM_PMICS) && (pm_ibb_data_arr[pmic_index] !=NULL))
  {
    return pm_ibb_data_arr[pmic_index]->num_of_peripherals;
  }

  return 0;
}


