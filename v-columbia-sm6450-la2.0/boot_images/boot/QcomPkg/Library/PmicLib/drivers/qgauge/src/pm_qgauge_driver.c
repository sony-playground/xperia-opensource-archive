/*! \file
*  
*  \brief  pm_qgauge_driver.c driver implementation.
*  \details qgauge driver implementation.
*  &copy;
*  Copyright (c) 2018, 2021 Qualcomm Technologies, Inc.  All Rights Reserved. 
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


$Header: //components/rel/core.boot/6.0/QcomPkg/Library/PmicLib/drivers/qgauge/src/pm_qgauge_driver.c#4 $
$Author: pwbldsvc $
$DateTime: 2021/11/25 13:43:41 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
02/21/18    sv     Initial revision
========================================================================== */

/*===========================================================================

                    INCLUDE FILES

===========================================================================*/
#include "pm_qgauge_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the qgauge driver data */
static pm_qgauge_data_type *pm_qgauge_data_arr[PM_MAX_NUM_PMICS];

static qgauge_register_ds qgauge_reg =
{ 
    .base_address         = 0x4800,     
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
    .en_ctl               = 0x046,      
    .vbat_empty_threshold = 0x04B,      
    .vbat_low_threshold   = 0x04c,
    .pon_ocv_acc0_data0   = 0x070,      
    .last_adc_v_data0     = 0x0c0,      
    .last_adc_v_data1     = 0x0c1,      
    .last_adc_i_data0     = 0x0c2,      
    .last_adc_i_data1     = 0x0c3,  
};


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_qgauge_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index)
{
    pm_qgauge_data_type *qgauge_ptr = NULL;
    //pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    uint32 prop_id_arr[] = {PM_PROP_QGAUGE_NUM};
    
    qgauge_ptr = pm_qgauge_data_arr[pmic_index];

    if(NULL == qgauge_ptr)
    {
        pm_malloc( sizeof(pm_qgauge_data_type), (void**)&qgauge_ptr);

        /* Assign Comm ptr */
        qgauge_ptr->comm_ptr = comm_ptr;

        /* qgauge Register Info - Obtaining Data through dal config */
        qgauge_ptr->qgauge_register = &qgauge_reg;
        CORE_VERIFY_PTR(qgauge_ptr->qgauge_register);

        qgauge_ptr->qgauge_register->base_address = peripheral_info->base_address;

        qgauge_ptr->num_of_peripherals = pm_target_information_get_periph_count_info(prop_id_arr[pmic_index], pmic_index);
        CORE_VERIFY(qgauge_ptr->num_of_peripherals != 0);

        pm_qgauge_data_arr[pmic_index] = qgauge_ptr;
    }
}

pm_qgauge_data_type* pm_qgauge_get_data(uint8 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS)
  {
      return pm_qgauge_data_arr[pmic_index];
  }

  return NULL;
}

uint8 pm_qgauge_get_num_peripherals(uint8 pmic_index)
{
  if((pmic_index < PM_MAX_NUM_PMICS)&&
  	  (pm_qgauge_data_arr[pmic_index] != NULL))
  {
      return pm_qgauge_data_arr[pmic_index]->num_of_peripherals;
  }

  return 0;
}


void pm_qgauge_get_pmic_info(uint8 *pmic_index, uint8 *slave_id)
{
    uint8 i = 0;

    if(!pmic_index || !slave_id)
        return;

    for(i = 0; i < PM_MAX_NUM_PMICS; i++)
    {
        if(pm_qgauge_data_arr[i])
        {
            *pmic_index = pm_qgauge_data_arr[i]->comm_ptr->pmic_index;
            *slave_id   = pm_qgauge_data_arr[i]->comm_ptr->slave_id;
            break;
        }
    }

    return;
}

