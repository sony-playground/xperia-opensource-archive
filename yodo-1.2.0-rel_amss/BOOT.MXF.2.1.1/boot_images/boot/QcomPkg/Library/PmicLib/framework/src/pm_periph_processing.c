/*! \file pm_periph_processing.c
*  
*  \brief This file contains APIs common to loader and core
*  \n   
*  &copy; Copyright 2018-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/framework/src/pm_periph_processing.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       	who     	what, where, why
--------   	---    		---------------------------------------------------------- 
04/04/18    al          New file
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_target_information.h"
#include "pm_comm.h"
#include "device_info.h"
#include "SpmiBus.h"

/*===========================================================================

                        STATIC VARIABLES 

===========================================================================*/


/*===========================================================================

                     FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type
pm_config_lock_by_bit(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 i = 0, j = 0;
  uint32 slave_id = 0;
  uint16 addr = 0, channel = 0;
  Spmi_Result rslt = SPMI_SUCCESS;

  uint32 current_img = pm_get_img_type();

  pm_lock_by_bit_data *lock_by_bit_data_ptr = (pm_lock_by_bit_data *)pm_target_information_get_specific_info(PM_PROP_LOCK_BY_BIT_DATA);
  uint32 *num_lock_by_bit_arrays = (uint32 *)pm_target_information_get_specific_info(PM_PROP_LOCK_BY_BIT_ARR_SIZE);
  
  if((lock_by_bit_data_ptr == NULL) || (num_lock_by_bit_arrays == NULL))
  {
    return PM_ERR_FLAG_DATA_VERIFY_ERR;
  }

  for (i = 0; i < *num_lock_by_bit_arrays; i++)
  {
    for(j = 0; j < lock_by_bit_data_ptr[i].arr_size; j++)
    {
      //Check if peripheral is apps owned
      rslt = SpmiBus_GetChannel((uint8)lock_by_bit_data_ptr[i].arr_ptr[j].bus_id, (uint8)lock_by_bit_data_ptr[i].arr_ptr[j].slave_id, (uint8)lock_by_bit_data_ptr[i].arr_ptr[j].ppid, &channel);

      //if apps owned do not lock in loader and continue 
      if(rslt == SPMI_SUCCESS && current_img == PM_IMG_LOADER)
      {
        continue;
      }
      //In uefi if apps channel is not found, continue
      else if (rslt != SPMI_SUCCESS && current_img == PM_IMG_CORE)
      {
        continue;
      }

      slave_id = lock_by_bit_data_ptr[i].arr_ptr[j].slave_id;

      if(pm_is_slave_id_supported(slave_id) == TRUE) //write only if valid slave id 
      {
        addr = (lock_by_bit_data_ptr[i].arr_ptr[j].ppid * 0x100) + lock_by_bit_data_ptr[i].offset;

        err_flag |= pm_comm_write_byte_ex(lock_by_bit_data_ptr[i].arr_ptr[j].bus_id, slave_id, addr, lock_by_bit_data_ptr[i].arr_ptr[j].lock_value);
      }
    }
  }

  return err_flag;
}
