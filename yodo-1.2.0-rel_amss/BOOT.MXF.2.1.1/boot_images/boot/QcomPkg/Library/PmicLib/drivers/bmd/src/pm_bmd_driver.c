/*! \file pm_bmd_driver.c
*  \n
*  \brief This file contains bmd peripheral driver initialization during which the driver data is stored.
*  \n
*  \n &copy; Copyright 2017-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/bmd/src/pm_bmd_driver.c#1 $

$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/07/18   xmp     Implement BMD driver
11/20/17   richaa  Created
========================================================================== */

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_bmd_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACRO AND TYPE DEFINITIONS

===========================================================================*/
#define PMIC_BMD_MAX_HW_VER 0x01

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the BMD data */
static pm_bmd_data_type *pm_bmd_data_arr[PM_MAX_NUM_PMICS];

static pm_bmd_register_info_type bmd_reg =
{
  .bmd_fsm_sts       = 0x09,
  .bmd_int_rt_sts    = 0x10,
  .bmd_mode_ctl      = 0x40,
  .bmd_timing        = 0x41,
  .bmd_deb_ctl       = 0x42,
  .bmd_threshold_ctl = 0x43,
  .bmd_src_ctl       = 0x44,
  .bmd_bmd_adc_ctl   = 0x45,
  .bmd_bmd_en        = 0x46,
  .bmd_bmd_adc_dly   = 0x47,
  .bmd_lockbit       = 0xD1,
};


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_bmd_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index)
{
  pm_bmd_data_type *bmd_ptr = pm_bmd_data_arr[pmic_index];
  uint8 num_of_peripherals = 0;

  if (NULL == bmd_ptr)
  {
    num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_BMD_NUM, pmic_index);
    if (num_of_peripherals == 0)
    {
      return;
    }
    
    pm_malloc(sizeof(pm_bmd_data_type), (void**)&bmd_ptr);
    CORE_VERIFY(NULL != bmd_ptr);
    
    bmd_ptr->dig_maj_min_ver = ((peripheral_info->digital_major_version << 0x4) | 
                                (peripheral_info->digital_minor_version));

    CORE_VERIFY (bmd_ptr->dig_maj_min_ver <= PMIC_BMD_MAX_HW_VER);

    /* Assign Comm ptr */
    bmd_ptr->comm_ptr = comm_ptr;

    bmd_ptr->bmd_reg_table = &bmd_reg;

    bmd_ptr->base_address = peripheral_info->base_address;

    bmd_ptr->num_of_peripherals = num_of_peripherals;

    pm_bmd_data_arr[pmic_index] = bmd_ptr;
  }
}


pm_bmd_data_type* pm_bmd_get_data(uint32 pmic_index)
{
  return (pmic_index < PM_MAX_NUM_PMICS) ? pm_bmd_data_arr[pmic_index] : NULL;
}

