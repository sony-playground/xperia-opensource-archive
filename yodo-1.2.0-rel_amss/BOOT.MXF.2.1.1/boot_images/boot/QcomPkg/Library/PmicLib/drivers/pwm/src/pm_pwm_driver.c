/*! \file
 *  \n
 *  \brief  pm_pwm_driver.c
 *  \details
 *  \n &copy; Copyright 2012 - 2022 QUALCOMM Technologies, Inc. All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pwm/src/pm_pwm_driver.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when        who     what, where, why
--------    ---     ----------------------------------------------------------
08/20/14    al      Updating comm lib
08/29/14    al      KW fixes
05/20/14    al      Architecture update
05/09/14    va      Using common debug and assert Marco
10/16/12    al      removed unimplemented irq
07/24/12    al      New file
========================================================================== */
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_pwm_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/
#define PMIC_PWM_MAX_HW_VER   0x01

/* Static global variable to store the PWM driver data */
static pm_pwm_data_type *pm_pwm_data_arr[PM_MAX_NUM_PMICS];

static pm_pwm_register_info_type pwm_reg =
{
  .pwm_size_clk         = 0x041,
  .pwm_freq_prediv_clk  = 0x042,
  .pwm_type_config      = 0x043,
  .pwm_value_lsb        = 0x044,
  .pwm_value_msb        = 0x045,
  .enable_control       = 0x046,
  .pwm_sync             = 0x047,
};


static pm_pwm_specific_data pwm_rev_b_data =
{
  .size_mask          	  = 0x04,
  .clk_mask               = 0x03,
  .max_pwm_value          = 0x1FF, 
  .pwm_size_start_bit_pos = 2, 
  .max_freq               = PM_PWM_CLK__19_2_MHZ, 
  .max_pwm_size           = PM_PWM_SIZE__9BIT,
};

static pm_pwm_specific_data pwm_rev_c_data =
{
  .size_mask          	  = 0x70,
  .clk_mask               = 0x07,
  .max_pwm_value          = 0x7FFF,
  .pwm_size_start_bit_pos = 4,
  .max_freq               = PM_PWM_CLK__76_8_MHZ,
  .max_pwm_size           = PM_PWM_SIZE__15BIT,
};

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_pwm_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index)
{
  pm_pwm_data_type *pwm_ptr = NULL;
  pwm_ptr = pm_pwm_data_arr[pmic_index];

  if (NULL == pwm_ptr)
  {

    pm_malloc( sizeof(pm_pwm_data_type), (void**)&pwm_ptr);
    
    pwm_ptr->dig_maj_min_ver = ((peripheral_info->digital_major_version << 8) |
                                peripheral_info->digital_minor_version);

    pwm_ptr->periph_subtype = peripheral_info->peripheral_subtype;

    CORE_VERIFY (pwm_ptr->dig_maj_min_ver <= PMIC_PWM_MAX_HW_VER);

    /* Assign Comm ptr */
    pwm_ptr->comm_ptr = comm_ptr;

    /* PWM Register Info - Obtaining Data through dal config */
    pwm_ptr->pwm_reg_table = &pwm_reg;

    CORE_VERIFY_PTR(pwm_ptr->pwm_reg_table);

    if (pwm_ptr->periph_subtype == PERIPH_SUBTYPE_PWM_REV_B)
    {
      pwm_ptr->pwm_specific_data = &pwm_rev_b_data;
    }
    else
    {
      pwm_ptr->pwm_specific_data = &pwm_rev_c_data;
    }
    CORE_VERIFY_PTR(pwm_ptr->pwm_specific_data);

    pwm_ptr->base_address = peripheral_info->base_address;

    pwm_ptr->num_of_peripherals = 1;

    pm_pwm_data_arr[pmic_index] = pwm_ptr;
  }
  else 
  {
    pwm_ptr->num_of_peripherals++;
  }
}

pm_pwm_data_type* pm_pwm_get_data(uint32 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS)
  {
    return pm_pwm_data_arr[pmic_index];
  }
  return NULL;
}

uint8 pm_pwm_get_num_peripherals(uint32 pmic_index)
{
  if((pmic_index < PM_MAX_NUM_PMICS) && (pm_pwm_data_arr[pmic_index] !=NULL))
  {
    return pm_pwm_data_arr[pmic_index]->num_of_peripherals;
  }

  return 0;
}

