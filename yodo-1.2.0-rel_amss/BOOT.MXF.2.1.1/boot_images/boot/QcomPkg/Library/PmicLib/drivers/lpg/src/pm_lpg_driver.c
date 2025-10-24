/*! \file pm_lpg_driver.c
*  \n
*  \brief This file contains LPG peripheral driver initialization during which the driver data is stored.
*  \n
*  \n &copy; Copyright 2012-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/lpg/src/pm_lpg_driver.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
11/12/17   aab     Moved common Register address defination to driver file
07/16/14   akm     Comm change Updates
03/31/14   akm     Updated to the latest PMIC driver architecture
02/27/13   aab     Creation
========================================================================== */

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_lpg_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the LPG driver data */
static pm_lpg_data_type *pm_lpg_data_arr[PM_MAX_NUM_PMICS];

static pm_lpg_register_info_type lpg_reg =
{
  .peripheral_offset         = 0x100,
  .perph_subtype             = 0x005,
  .lpg_pattern_config        = 0x040,
  .lpg_pwm_size_clk          = 0x041,
  .lpg_pwm_freq_prediv_clk   = 0x042,
  .lpg_pwm_type_config       = 0x043,
  .pwm_value_lsb             = 0x044,
  .pwm_value_msb             = 0x045,
  .enable_control            = 0x046,
  .pwm_sync                  = 0x047,
  .ramp_step_duration_lsb    = 0x050,
  .ramp_step_duration_msb    = 0x051,
  .pause_hi_multiplier       = 0x052,
  .pause_lo_multiplier       = 0x054,
  .hi_index                  = 0x056,
  .lo_index                  = 0x057,
  .lut_lsb                   = 0x040,
  .lut_msb                   = 0x041,
  .ramp_control              = 0x0C8,
  .test1                     = 0x0e2,
  .test2                     = 0x0e3,
  .test3                     = 0x0e4,
  .test4                     = 0x0e5
};

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_lpg_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index)
{
  pm_lpg_data_type *lpg_ptr = NULL;
  uint8 num_of_peripherals = 0;

  lpg_ptr = pm_lpg_data_arr[pmic_index];

  if (lpg_ptr == NULL)
  {
    num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_LPG_NUM, pmic_index);

    if (num_of_peripherals == 0)
    {
      return;
    }
    pm_malloc( sizeof(pm_lpg_data_type), (void**)&lpg_ptr);

    /* Assign Comm ptr */
    lpg_ptr->comm_ptr = comm_ptr;

    /* LPG Register Info - Obtaining Data through dal config */
    lpg_ptr->lpg_reg_table = &lpg_reg;

    CORE_VERIFY_PTR(lpg_ptr->lpg_reg_table);

    lpg_ptr->base_address = peripheral_info->base_address;

    lpg_ptr->num_of_peripherals = num_of_peripherals;

    lpg_ptr->lpg_specific = (pm_lpg_specific_info_type*)pm_target_information_get_specific_info(PM_PROP_LPG_SPECIFIC_DATA);

    CORE_VERIFY_PTR(lpg_ptr->lpg_specific);

    pm_lpg_data_arr[pmic_index] = lpg_ptr;
  }
}

pm_lpg_data_type* pm_lpg_get_data(uint32 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS)
  {
    return pm_lpg_data_arr[pmic_index];
  }

  return NULL;
}


uint8 pm_lpg_get_num_peripherals(uint32 pmic_index)
{
  if((pmic_index < PM_MAX_NUM_PMICS) && (pm_lpg_data_arr[pmic_index] !=NULL))
  {
    return pm_lpg_data_arr[pmic_index]->num_of_peripherals;
  }

  return 0;
}

