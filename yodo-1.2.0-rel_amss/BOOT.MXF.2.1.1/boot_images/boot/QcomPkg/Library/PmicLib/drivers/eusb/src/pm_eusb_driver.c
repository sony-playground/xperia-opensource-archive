/*! \file pm_eusb_driver.c
*  \n
*  \brief This file contains eusb peripheral driver initialization during which the driver data is stored.
*  \n
*  \n &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/eusb/src/pm_eusb_driver.c#1 $

$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/06/22   akm     Implement EUSB driver
========================================================================== */

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_eusb_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACRO AND TYPE DEFINITIONS

===========================================================================*/
#define PMIC_EUSB_MAX_HW_VER 0x02

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the EUSB data */
static pm_eusb_data_type *pm_eusb_data_arr[PM_MAX_NUM_PMICS];

static pm_eusb_register_info_type eusb_reg =
{
  .eusb_eusb_en        = 0x46,
};


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void 
pm_eusb_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index)
{
  pm_eusb_data_type *eusb_ptr = pm_eusb_data_arr[pmic_index];
  uint8 num_of_peripherals = 0;

  if (NULL == eusb_ptr)
  {
    num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_EUSB_NUM, pmic_index);
    if (num_of_peripherals == 0)
    {
      return;
    }
    
    pm_malloc(sizeof(pm_eusb_data_type), (void**)&eusb_ptr);
    CORE_VERIFY(NULL != eusb_ptr);
    
    eusb_ptr->dig_maj_min_ver = ((peripheral_info->digital_major_version << 0x4) | 
                                (peripheral_info->digital_minor_version));

    CORE_VERIFY (eusb_ptr->dig_maj_min_ver <= PMIC_EUSB_MAX_HW_VER);

    /* Assign Comm ptr */
    eusb_ptr->comm_ptr = comm_ptr;

    eusb_ptr->eusb_reg_table = &eusb_reg;

    eusb_ptr->base_address = peripheral_info->base_address;

    eusb_ptr->num_of_peripherals = num_of_peripherals;

    pm_eusb_data_arr[pmic_index] = eusb_ptr;
  }
}


pm_eusb_data_type* 
pm_eusb_get_data(uint32 pmic_index)
{
  return (pmic_index < PM_MAX_NUM_PMICS) ? pm_eusb_data_arr[pmic_index] : NULL;
}

