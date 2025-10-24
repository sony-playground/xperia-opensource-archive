
#include "pm_config_setting.h"
#include "pm_err_flags.h"

/* ============================================

				Definitions

===============================================*/

static pm_err_flag_type
pm_config_populate_data(void **pm_config_data_arr, pm_config_data_kvp *config_info, uint32 config_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 i = 0;

  for (i = 0; i < config_size; ++i)
  {
    if (config_info[i].prop_id >= PM_PROP_MAX)
    {
      return PM_ERR_FLAG_INVALID_CONFIG_SETTING;
    }
    *(pm_config_data_arr + config_info[i].prop_id) = config_info[i].ptr;
  }

  return err_flag;
}


pm_err_flag_type
pm_config_common_populate_settings(void **pm_config_data_arr, uint32 config_data_arr_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_config_data_kvp config_data = {0}; 
  pm_config_data_kvp *config_data_ptr = &config_data; 
  uint32 config_data_size = 0;

  err_flag = pm_config_common_data(&config_data_ptr, &config_data_size);

  if ((err_flag == PM_ERR_FLAG_SUCCESS) && 
      (config_data_size < config_data_arr_size))
  {
    err_flag |= pm_config_populate_data(pm_config_data_arr, config_data_ptr, config_data_size);
  }

  err_flag |= pm_config_lock_by_bit_data(&config_data_ptr, &config_data_size);

  if ((err_flag == PM_ERR_FLAG_SUCCESS) && 
      (config_data_size < config_data_arr_size))
  {
    err_flag |= pm_config_populate_data(pm_config_data_arr, config_data_ptr, config_data_size);
  }

  err_flag |= pm_config_spmi_data(&config_data_ptr, &config_data_size);

  if ((err_flag == PM_ERR_FLAG_SUCCESS) && 
      (config_data_size < config_data_arr_size))
  {
    err_flag |= pm_config_populate_data(pm_config_data_arr, config_data_ptr, config_data_size);
  }

  return err_flag;
}
