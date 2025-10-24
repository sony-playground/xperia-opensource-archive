#ifndef __PM_HAPTICS_CFG_DRIVER_H__
#define __PM_HAPTICS_CFG_DRIVER_H__

/*! \file
*  \n
*  \brief  pm_haptics_driver.h 
*  \details  This file contains functions prototypes and variable/type/constant
*  declarations for supporting haptics peripheral 
*  
*  \n &copy; Copyright 2012-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/haptics/src/pm_haptics_cfg_driver.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/14/19   pxm      Add auto_res_ctrl
05/03/17   czq      Supported for WF source selection.

========================================================================== */

/*===========================================================================
                  INCLUDE FILES
===========================================================================*/
#include "pm_target_information.h"
#include "pm_haptics.h"

/*===========================================================================

                     HAPTICS TYPES AND STRUCTURES 

===========================================================================*/
typedef struct
{
  pm_register_address_type subtype;             //0x005
  pm_register_address_type status_data_msb;     //0x009
  pm_register_address_type status_data_lsb;     //0x00A
  pm_register_address_type fault_status;        //0x00C
  pm_register_address_type en_ctl;              //0x046
  pm_register_address_type vmax_cfg;            //0x048
  pm_register_address_type spmi_play;           //0x04C
  pm_register_address_type tlra_ol_high;        //0x05c
  pm_register_address_type tlra_ol_low;         //0x05d
  pm_register_address_type drv_duty;            //0x060
  pm_register_address_type autores_cfg;         //0x063
  pm_register_address_type fault_clr;           //0x066
  pm_register_address_type vmax_hdrm;           //0x067
  pm_register_address_type mod_status_sel;      //0x070
  pm_register_address_type mod_status_xt;       //0x071
  // - on haptics_pattern
  pm_register_address_type direct_play;         //0x126
} pm_haptics_register_info_type;

typedef struct
{
    pm_comm_info_type              *comm_ptr;
    uint32                         num_of_peripherals;
    pm_haptics_register_info_type  *haptics_reg_table;
    pm_register_address_type       base_address;
    uint8                          dig_maj_min_ver;
} pm_haptics_data_type;


/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/
void pm_haptics_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index);

pm_haptics_data_type* pm_haptics_get_data(uint32 pmic_index);

uint32 pm_haptics_get_num_peripherals(uint32 pmic_index);

#endif // __PM_HAPTICS_CFG_DRIVER_H__

