
#include "pm_config_setting.h"
#include "pm_target_information.h"

pm_err_flag_type
pm_config_img_settings_init ( void )
{
	pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
	uint32 pam_config_data_size = 0, config_size = 0, i = 0;
	pm_config_data_kvp pam_config_data = {0}; 
	pm_config_data_kvp *pam_config_data_ptr = &pam_config_data;
	boolean is_img_initialized = FALSE;
	void **config_arr;
  	
  	err_flag = pm_config_pam_data(&pam_config_data_ptr, &pam_config_data_size);
	err_flag |= pm_target_information_data_arr(&config_arr, &config_size);
	
	if (err_flag != PM_ERR_FLAG_SUCCESS)
	{
		return err_flag;
	}
	else if((config_size == 0) || (pam_config_data_size == 0))
	{
		err_flag |= PM_ERR_FLAG_INVALID_PARAMETER;
	}
	else
	{
		for(i = 0; i < pam_config_data_size; ++i)
		{
			if (pam_config_data_ptr[i].prop_id > config_size)
			{
				return PM_ERR_FLAG_INVALID_CONFIG_SETTING;
			}
			config_arr[pam_config_data_ptr[i].prop_id] = pam_config_data_ptr[i].ptr;
		}
	}

	is_img_initialized = (err_flag == PM_ERR_FLAG_SUCCESS) ? TRUE : FALSE;
	pm_update_img_init_status(is_img_initialized);

	return err_flag;
}

