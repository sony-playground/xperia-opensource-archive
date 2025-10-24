#ifndef __PM_QBG_DRIVER_H__
#define __PM_QBG_DRIVER_H__

/*! \file pm_qbg_driver.h
 *  \n
 *  \brief This file contains functions prototypes and variable/type/constant
*          declarations for supporting qbg peripheral  
 *  \n  
 *  \n &copy;
 *  Copyright (c) 2020-2021 Qualcomm Technologies, Inc.  All Rights Reserved. 
 *  Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/qbg/src/pm_qbg_driver.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when         who     what, where, why
--------     ---     ---------------------------------------------------------- 
01/22/2020    CS      Created
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_target_information.h"

/*===========================================================================

                     STRUCTURE TYPE AND ENUM

===========================================================================*/


/************************************************************************/
/* register definitions                                                                     */
/************************************************************************/
typedef struct
{
  uint32                   base_address;                  //0x4F00
  pm_register_address_type perph_type                   ; //0x004
  pm_register_address_type perph_subtype                ; //0x005
  pm_register_address_type status1                      ; //0x008
  pm_register_address_type status2                      ; //0x009
  pm_register_address_type status3                      ; //0x00A
  pm_register_address_type int_rt_sts                   ; //0x010
  pm_register_address_type int_set_type                 ; //0x011
  pm_register_address_type int_polarity_high            ; //0x012
  pm_register_address_type int_polarity_low             ; //0x013
  pm_register_address_type int_latched_clr              ; //0x014
  pm_register_address_type int_en_set                   ; //0x015
  pm_register_address_type int_en_clr                   ; //0x016
  pm_register_address_type int_latched_sts              ; //0x018
  pm_register_address_type int_pending_sts              ; //0x019
  pm_register_address_type mode_ctl1                    ; //0x043
  pm_register_address_type mode_ctl2                    ; //0x044
  pm_register_address_type mode_ctl3                    ; //0x047
  pm_register_address_type en_ctl                       ; //0x046
  pm_register_address_type cmd_adc_ctl7                 ; //0x04D
  pm_register_address_type vbat_empty_threshold         ; //0x056
  pm_register_address_type pon_ocv_acc0_data0           ; //0x070
  pm_register_address_type last_burst_avg_acc0_data0    ; //0x0A0  this is for reading vbatt
  pm_register_address_type last_burst_avg_acc2_data0    ; //0x0A4  this is for reading ibatt.  
}qbg_register_ds;

typedef struct
{
    pm_comm_info_type          *comm_ptr;
    qbg_register_ds            *qbg_register;
    uint8                      num_of_peripherals;
    uint8                      dig_maj_min_ver;
}pm_qbg_data_type;


/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void pm_qbg_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index);

pm_qbg_data_type* pm_qbg_get_data(uint8 pmic_index);

void pm_qbg_get_pmic_info(uint8 *pmic_index, uint8 *slave_id);

#endif // __PM_QBG_DRIVER_H__
