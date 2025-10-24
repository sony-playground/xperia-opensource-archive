/*! \file
*  
*  \brief  pm_qbg_driver.c driver implementation.
*  \details qbg driver implementation.
*  &copy;
*  Copyright (c) 2018-2021 Qualcomm Technologies, Inc.  All Rights Reserved. 
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/qbg/src/pm_qbg_driver.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
02/21/18    sv     Initial revision
========================================================================== */

/*===========================================================================

                    INCLUDE FILES

===========================================================================*/
#include "pm_qbg_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACRO AND TYPE DEFINITIONS

===========================================================================*/
#define PMIC_BMS_QBG_MAIN_MAX_HW_VER 0x10

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the qbg driver data */
static pm_qbg_data_type *pm_qbg_data_arr[PM_MAX_NUM_PMICS];

static qbg_register_ds qbg_reg =
{ 
    .base_address         = 0x4F00,     
    .perph_type           = 0x004,      
    .perph_subtype        = 0x005,      
    .status1              = 0x008,      
    .status2              = 0x009,      
    .status3              = 0x00A,      
    .int_rt_sts           = 0x010,      
    .int_set_type         = 0x011,      
    .int_polarity_high    = 0x012,      
    .int_polarity_low     = 0x013,      
    .int_latched_clr      = 0x014,      
    .int_en_set           = 0x015,      
    .int_en_clr           = 0x016,      
    .int_latched_sts      = 0x018,      
    .int_pending_sts      = 0x019,
    .mode_ctl1            = 0x043,      
    .mode_ctl2            = 0x044,      
    .mode_ctl3            = 0x047,      
    .en_ctl               = 0x046,
    .vbat_empty_threshold = 0x056,         
    .pon_ocv_acc0_data0   = 0x080,      
    .last_burst_avg_acc0_data0 = 0x0C0,      
    .last_burst_avg_acc2_data0 = 0x0C4,      
};


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_qbg_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index)
{
    pm_qbg_data_type *qbg_ptr         = NULL;
    
    qbg_ptr = pm_qbg_data_arr[pmic_index];

    if (NULL == qbg_ptr)
    {
        pm_malloc( sizeof(pm_qbg_data_type), (void**)&qbg_ptr);
        
        qbg_ptr->dig_maj_min_ver = ((peripheral_info->digital_major_version << 4) |
                                    peripheral_info->digital_minor_version);

        CORE_VERIFY(qbg_ptr->dig_maj_min_ver <= PMIC_BMS_QBG_MAIN_MAX_HW_VER);

        /* Assign Comm ptr */
        qbg_ptr->comm_ptr = comm_ptr;

        /* qbg Register Info - Obtaining Data through dal config */
        qbg_ptr->qbg_register = &qbg_reg;
        CORE_VERIFY_PTR(qbg_ptr->qbg_register);

        qbg_ptr->qbg_register->base_address = peripheral_info->base_address;

        qbg_ptr->num_of_peripherals = 1;

        pm_qbg_data_arr[pmic_index] = qbg_ptr;
    }
}

pm_qbg_data_type* pm_qbg_get_data(uint8 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS)
  {
      return pm_qbg_data_arr[pmic_index];
  }

  return NULL;
}

uint8 pm_qbg_get_num_peripherals(uint8 pmic_index)
{
  if((pmic_index < PM_MAX_NUM_PMICS)&&
  	  (pm_qbg_data_arr[pmic_index] != NULL))
  {
      return pm_qbg_data_arr[pmic_index]->num_of_peripherals;
  }

  return 0;
}


void pm_qbg_get_pmic_info(uint8 *pmic_index, uint8 *slave_id)
{
    uint8 i = 0;

    if(!pmic_index || !slave_id)
        return;

    for(i = 0; i < PM_MAX_NUM_PMICS; i++)
    {
        if(pm_qbg_data_arr[i])
        {
            *pmic_index = pm_qbg_data_arr[i]->comm_ptr->pmic_index;
            *slave_id   = pm_qbg_data_arr[i]->comm_ptr->slave_id;
            break;
        }
    }

    return;
}

