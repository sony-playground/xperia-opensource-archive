/*! \file  pm_config_loader.c
 *  
 *  \brief  File Contains the API to map the loader specific settings
 *  \details  This file contains the API to map the loader specific settings
 *  
 *    Platform: Kailua.XX.1.0
 *    Revision: KAILUA.XX.1.0-UEFI-00001 (Working Set)
 *    Template Version: 
 *    $Header: //components/rel/core.boot/6.1/QcomPkg/SocPkg/Kailua/Settings/PMIC/pm_config_loader.c#1 $ 
 *    $DateTime: 2022/01/28 04:56:53 $  $Author: pwbldsvc $
 *  
 *  &copy; Copyright Mar. 4, 2022 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        INCLUDE HEADER FILES

===========================================================================*/

#include "pm_config_setting.h"
#include "pm_target_information.h"

pm_err_flag_type
pm_config_img_settings_init ( void )
{
	pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
	uint32 arb_config_data_size = 0, config_size = 0, i = 0;
	pm_config_data_kvp arb_config_data = {0}; 
	pm_config_data_kvp *arb_config_data_ptr = &arb_config_data;
	boolean is_img_initialized = FALSE;
	void **config_arr;
	
  	err_flag = pm_config_arb_data(&arb_config_data_ptr, &arb_config_data_size);
	err_flag |= pm_target_information_data_arr(&config_arr, &config_size);
	
	if (err_flag != PM_ERR_FLAG_SUCCESS)
	{
		return err_flag;
	}
	else if((config_size == 0) || (arb_config_data_size == 0))
	{
		err_flag |= PM_ERR_FLAG_INVALID_PARAMETER;
	}
	else
	{
		for(i = 0; i < arb_config_data_size; ++i)
		{
			if (arb_config_data_ptr[i].prop_id > config_size)
			{
				return PM_ERR_FLAG_INVALID_CONFIG_SETTING;
			}
			config_arr[arb_config_data_ptr[i].prop_id] = arb_config_data_ptr[i].ptr;
		}
	}

	is_img_initialized = (err_flag == PM_ERR_FLAG_SUCCESS) ? TRUE : FALSE;
	pm_update_img_init_status(is_img_initialized);

	return err_flag;
}
