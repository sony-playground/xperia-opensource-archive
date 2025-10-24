#ifndef __PM_PWM_DRIVER_H__
#define __PM_PWM_DRIVER_H__

/*! \file
 *  \n
 *  \brief  ipwm.h
 *  \details
 *  \n &copy; Copyright (c) 2012-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
              Qualcomm Technologies Proprietary and Confidential.
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pwm/src/pm_pwm_driver.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/20/14   al      Updating comm lib
06/20/14   al      Updated coypright info
12/11/12   al      Created.
========================================================================== */

#include "pm_target_information.h"
#include "pm_pwm.h"

#define PERIPH_SUBTYPE_PWM_REV_B    0xB
#define PERIPH_SUBTYPE_PWM_REV_C    0xC

typedef struct
{
  uint8                   size_mask;
  uint8                   clk_mask;
  uint16                  max_pwm_value; 
  uint8                   pwm_size_start_bit_pos; 
  pm_pwm_clock_freq_type  max_freq;
  pm_pwm_bit_size_type    max_pwm_size;
}pm_pwm_specific_data;


typedef struct
{
  pm_register_address_type pwm_size_clk;             //  0x041
  pm_register_address_type pwm_freq_prediv_clk;      //  0x042
  pm_register_address_type pwm_type_config;          //  0x043
  pm_register_address_type pwm_value_lsb;            //  0x044
  pm_register_address_type pwm_value_msb;            //  0x045
  pm_register_address_type enable_control;           //  0x046
  pm_register_address_type pwm_sync;                 //  0x047
}pm_pwm_register_info_type;


typedef struct
{
  pm_comm_info_type           *comm_ptr;
  pm_pwm_register_info_type   *pwm_reg_table;
  pm_pwm_specific_data        *pwm_specific_data;
  pm_register_address_type    base_address;
  uint8                       num_of_peripherals;
  uint16                      dig_maj_min_ver;
  uint8                       periph_subtype;
}pm_pwm_data_type;


/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void pm_pwm_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index);

pm_pwm_data_type* pm_pwm_get_data(uint32 pmic_index);

uint8 pm_pwm_get_num_peripherals(uint32 pmic_index);

#endif // __PM_PWM_DRIVER_H__

