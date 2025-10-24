#ifndef __PM_EUSB_DRIVER_H__
#define __PM_EUSB_DRIVER_H__

/*! \file pm_eusb_driver.h
*  \n
*  \brief  This file contains functions prototypes and variable/type/constant
*         declarations for supporting eusb peripheral.
*
*  \n &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/eusb/src/pm_eusb_driver.h#1 $

$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when         who      what, where, why
--------   ---      ----------------------------------------------------------
01/06/22   akm     Implement EUSB driver
========================================================================== */

/*===========================================================================
            INCLUDE FILES
===========================================================================*/
#include "pm_target_information.h"

/*===========================================================================

                     EUSB TYPES AND STRUCTURES

===========================================================================*/
typedef struct
{
  pm_register_address_type eusb_eusb_en;                    // 0x46
} pm_eusb_register_info_type;


typedef struct
{
  pm_comm_info_type            *comm_ptr;
  pm_eusb_register_info_type  *eusb_reg_table;
  pm_register_address_type     base_address;
  uint8                        num_of_peripherals;
  uint8                        dig_maj_min_ver;
}pm_eusb_data_type;


/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void 
pm_eusb_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index);

pm_eusb_data_type* 
pm_eusb_get_data(uint32 pmic_index);


#endif // __PM_EUSB_DRIVER_H__

