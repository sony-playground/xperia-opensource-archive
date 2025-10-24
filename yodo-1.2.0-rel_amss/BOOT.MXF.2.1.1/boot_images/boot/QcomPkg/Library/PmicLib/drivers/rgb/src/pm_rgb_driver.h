#ifndef PM_RGB_DRIVER__H
#define PM_RGB_DRIVER__H

/*! \file pm_rgb_driver.h
*  \n
*  \brief  This file contains functions prototypes and variable/type/constant
*         declarations for supporting rgb peripheral.
*
*  \n &copy; Copyright 2012-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/rgb/src/pm_rgb_driver.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/16/14   akm     Comm change Updates
03/31/14   akm     Updated to the latest PMIC driver architecture
03/04/13   aab     Created
========================================================================== */

/*===========================================================================
            INCLUDE FILES
===========================================================================*/
#include "pm_target_information.h"
#include "pm_sdam.h"

/*===========================================================================

                     RGB TYPES AND STRUCTURES

===========================================================================*/
typedef struct
{
  pm_register_address_type peripheral_offset;
  pm_register_address_type src_sel;             //0x045
  pm_register_address_type en_ctl;              //0x046
  pm_register_address_type chgr_led_config;     //0x058
} pm_rgb_register_info_type;


typedef struct
{
  pm_comm_info_type          *comm_ptr;
  pm_rgb_register_info_type  *rgb_reg_table;
  pm_register_address_type    base_address;
  uint8                       num_of_peripherals;
  uint8                       sub_type;
  uint8                       dig_maj_min_ver;
} pm_rgb_data_type;

typedef struct
{
  uint32        clock:8;
  uint32        pre_div:8;
  uint32        exp:8;
  uint32        bit_size:8;
  uint32        ramp_step_duration:8;
  uint32        hi_multiplier:8;
  uint32        low_multiplier:8;
  uint32        rgb_sdam_pmic:8;
  pm_sdam_type  rgb_sdam:8;
  uint32        sdam_enable_arg:8;
  uint32        sdam_disable_arg:8;
  uint32        is_rgb_sdam_trig_supported:1;
  uint32        is_lpg_supported:1; //1 for LPG and 0 for PWM
  uint32        ramp_direction:1;
  uint32        ramp_toggle:1;
  uint32        en_pause_hi:1;
  uint32        en_pause_lo:1;
  uint32        rgb_dim_level_max:16;
  uint8         led_lpg_pwm_ch[3];
  uint8         rgb_pmic;
}pm_rgb_specific_data_type;


/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void pm_rgb_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index);

pm_rgb_data_type* pm_rgb_get_data(uint32 pmic_index);

uint8 pm_rgb_get_num_peripherals(uint32 pmic_index);

#endif // PM_RGB_DRIVER__H

