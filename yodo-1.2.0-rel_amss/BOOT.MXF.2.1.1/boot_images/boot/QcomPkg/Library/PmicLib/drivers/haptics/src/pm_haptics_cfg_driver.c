/*! \file pm_haptics_driver.c 
*  \n
*  \brief This file contains Haptics peripheral driver initialization during which the driver data is stored.
*  \n
*  \n &copy; Copyright 2012-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/haptics/src/pm_haptics_cfg_driver.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
02/14/19   pxm      Add auto_res_ctrl
11/12/17   aab     Moved common Register address defination to driver file  
01/21/15   al      New file 
========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_haptics_cfg_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACRO AND TYPE DEFINTIONS 

===========================================================================*/
#define PM_HAPTICS_CFG_SUBTYPE     0x0A
#define PMIC_HAPTICS_MAX_HW_VER    0x42

/*===========================================================================

                        STATIC VARIABLES 

===========================================================================*/

/* Static global variable to store the HAPTICS driver data */
static pm_haptics_data_type *pm_haptics_data_arr[PM_MAX_NUM_PMICS];

static pm_haptics_register_info_type haptics_reg =
{ 
  .subtype          = 0x005,
  .status_data_msb  = 0x009,
  .status_data_lsb  = 0x00A,
  .fault_status     = 0x00C,
  .en_ctl           = 0x046,
  .vmax_cfg         = 0x048,
  .spmi_play        = 0x04C,
  .tlra_ol_high     = 0x05c,
  .tlra_ol_low      = 0x05d,
  .drv_duty         = 0x060,
  .autores_cfg      = 0x063,
  .fault_clr        = 0x066,
  .vmax_hdrm        = 0x067,
  .mod_status_sel   = 0x070,
  .mod_status_xt    = 0x071,
  .direct_play      = 0x126,
};

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_haptics_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index)
{
    pm_haptics_data_type *haptics_ptr = NULL;
    uint8 num_of_peripherals = 0;

    haptics_ptr = pm_haptics_data_arr[pmic_index];

    pm_register_data_type data = 0;
    pm_register_address_type subtype_reg;
    
    if (haptics_ptr == NULL)
    {
        num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_HAPTICS_NUM, pmic_index);
        if (num_of_peripherals == 0)
        {
            return;
        }

        pm_malloc( sizeof(pm_haptics_data_type), (void**)&haptics_ptr);
        
        haptics_ptr->dig_maj_min_ver = ((peripheral_info->digital_major_version << 4) | 
                                        (peripheral_info->digital_minor_version));

        CORE_VERIFY(haptics_ptr->dig_maj_min_ver <= PMIC_HAPTICS_MAX_HW_VER);
                                                    
        /* Assign Comm ptr */
        haptics_ptr->comm_ptr = comm_ptr;

        /* HAPTICS Register Info - Obtaining Data through dal config */
        haptics_ptr->haptics_reg_table = &haptics_reg;
        CORE_VERIFY_PTR(haptics_ptr->haptics_reg_table);

        haptics_ptr->base_address = peripheral_info->base_address;

        //haptics_ptr->num_of_peripherals = (uint32)PM_MAX_NUM_HAPTICS;
        haptics_ptr->num_of_peripherals = num_of_peripherals;

        pm_haptics_data_arr[pmic_index] = haptics_ptr;
    }

    // Verify the subtype
    subtype_reg = haptics_ptr->base_address + haptics_ptr->haptics_reg_table->subtype;

    CORE_VERIFY(pm_comm_read_byte(haptics_ptr->comm_ptr->slave_id, subtype_reg, &data) == PM_ERR_FLAG_SUCCESS);
    CORE_VERIFY(data == PM_HAPTICS_CFG_SUBTYPE);
}

pm_haptics_data_type* pm_haptics_get_data(uint32 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS) 
  {
      return pm_haptics_data_arr[pmic_index];
  }

  return NULL;
}

uint32 pm_haptics_get_num_peripherals(uint32 pmic_index)
{
  if((pmic_index < PM_MAX_NUM_PMICS)&& 
     (pm_haptics_data_arr[pmic_index] !=NULL))
  {
      return pm_haptics_data_arr[pmic_index]->num_of_peripherals;
  }

  return 0;
}
