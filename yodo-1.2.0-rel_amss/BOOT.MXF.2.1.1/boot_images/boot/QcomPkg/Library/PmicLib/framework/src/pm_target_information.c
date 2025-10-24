/*! \file pm_target_information.c
*
*  \brief This file contains target specific PMIC settings common across processors.
*  \n
*  &copy; Copyright 2012-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/framework/src/pm_target_information.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when        who       what, where, why
--------    ---       ----------------------------------------------------------
06/25/15    al          removing loader specific API from common file
11/19/14    al          Re-naming to target
11/12/14    al          Removing not required include
10/17/14    aab         Added pm_target_information_spmi_chnl_cfg
07/16/14    akm         Comm change Updates
03/31/14    akm         Updated to the latest PMIC driver architecture
09/19/13    aab         Added support for SBL_REG_CONFIG and PBS_RAM_CONFIG
12/06/12    hw          Architecture change from Module to Peripheral based driver
08/07/12    hs          Added support for 5V boost.
04/16/12    hs          Removed irq files.
04/03/10    wra         Creating file for MSM8960
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_target_information.h"
#include "pm_version.h"
#include "pm_comm.h"
#include "device_info.h"
#include "CoreVerify.h"
#include "pm_config_setting.h"

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/
static boolean pm_target_info_init = FALSE;
static boolean pm_target_common_info_init = FALSE;
static boolean pm_target_img_info_init = FALSE;

static void* pm_config_data_arr[PM_PROP_MAX] = {NULL};

/*===========================================================================

                     FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type pm_target_information_init ( void )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  /*
   * Runtime detection to support multiple PMIC configuration on any target.
   * We're only concerned with the primary PMIC here so we use index 0.
  */
  err_flag = pm_config_common_populate_settings( pm_config_data_arr, PM_PROP_MAX);

  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    pm_target_common_info_init = TRUE;
    pm_target_info_init = (pm_target_common_info_init & pm_target_img_info_init);
  } 

  return err_flag;
}

void 
pm_update_img_init_status(boolean pm_image_init_status)
{
  pm_target_img_info_init = pm_image_init_status;
  pm_target_info_init = (pm_target_common_info_init & pm_target_img_info_init);
}

boolean
pm_target_information_initialized ( void )
{
  return pm_target_info_init;
}

pm_err_flag_type
pm_target_information_data_arr(void ***config_data_arr, uint32 *config_arr_size)
{
	pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
	
	if((config_data_arr == NULL) || (config_arr_size == NULL))
	{
		return PM_ERR_FLAG_INVALID_PARAMETER;
	}
	
	*config_data_arr = pm_config_data_arr;
	*config_arr_size = PM_PROP_MAX;
	
	return err_flag;
}

pm_err_flag_type
pm_target_information_read_peripheral_rev ( pm_comm_info_type *comm_ptr,
                                        peripheral_info_type *peripheral_info )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type base_address =
                    (pm_register_address_type)peripheral_info->base_address;
  uint32 digital_minor_index = 0;
  uint32 digital_major_index = 1;
  uint32 analog_minor_index = 2;
  uint32 analog_major_index = 3;
  uint32 peripheral_type_index = 4;
  uint32 peripheral_subtype_index = 5;
  uint32 peripheral_dummy_index = 6;
  const uint32 num_of_bytes = 7;
  pm_register_data_type temp_peripheral_info[7] = { 0 };

  if ( !comm_ptr )
  {
    return PM_ERR_FLAG_BUS_ERR;
  }

  // Reset the peripheral info
  peripheral_info->peripheral_type = 0;
  peripheral_info->peripheral_subtype = 0;
  peripheral_info->analog_major_version = 0;
  peripheral_info->analog_minor_version = 0;
  peripheral_info->digital_major_version = 0;
  peripheral_info->digital_minor_version = 0;

  /* Burst read the peripheral info */
  pm_comm_read_byte_array(comm_ptr->slave_id, base_address,
                          num_of_bytes, temp_peripheral_info);

  /* When we burst read multiple bytes from a non-existent peripheral,
     the data returned should be same on all the bytes so we need to do
     the below check and return error */
  if ( temp_peripheral_info[peripheral_subtype_index] ==
       temp_peripheral_info[peripheral_dummy_index] )
  {
    return PM_ERR_FLAG_INVALID_PERIPHERAL;
  }

  /* Valid peripheral type can never be 0 */
  if ( temp_peripheral_info[peripheral_type_index] == 0 )
  {
    return PM_ERR_FLAG_INVALID_PERIPHERAL;
  }

  peripheral_info->peripheral_type = temp_peripheral_info[peripheral_type_index];
  peripheral_info->peripheral_subtype = temp_peripheral_info[peripheral_subtype_index];
  peripheral_info->digital_major_version = temp_peripheral_info[digital_major_index];
  peripheral_info->digital_minor_version = temp_peripheral_info[digital_minor_index];
  peripheral_info->analog_major_version = temp_peripheral_info[analog_major_index];
  peripheral_info->analog_minor_version = temp_peripheral_info[analog_minor_index];

  return err_flag;
}

void*
pm_target_information_get_specific_info(uint32 prop_id)
{
  if (prop_id < PM_PROP_MAX)
  {
    return pm_config_data_arr[prop_id];
  }

  return NULL;
  
}

uint32
pm_target_information_get_periph_count_info ( uint32 prop_id,
                                              uint8 pmic_index )
{
  uint32 *count = NULL;

  if ((count = (uint32*)pm_target_information_get_specific_info(prop_id)) != NULL)
  {
    if (pmic_index < PM_MAX_NUM_PMICS)
    {
      return *(count + pmic_index);
    }
  }
  return 0;
}
