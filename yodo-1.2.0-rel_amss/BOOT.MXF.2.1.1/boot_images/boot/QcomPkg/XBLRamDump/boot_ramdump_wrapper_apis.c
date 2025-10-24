/*=============================================================================

                       Boot Shared Functions Consumer

GENERAL DESCRIPTION
  This file contains definitions of functions for boot ramdump must functions

Copyright 2020 - 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
07/02/21   rama    Fix error handling in read_ddr_training_data_from_partition
05/24/21   yps     Fixed Raw dump issue with when switch partition.
05/27/20   yps     Intial creation
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <boot_config_context.h>
#include <boot_framework.h>
#include <boot_ramdump_if.h>
#include <boot_dal_if.h>
#include <boot_clk_if.h>
#include <boot_pmic_if.h>
#include <boot_qsee_if.h>
#include <boot_whitelist_if.h>
#include <boot_smem_if.h>
#include <boot_logger_if.h>
#include <boot_ddr_info_if.h>
#include <boot_platforminfo_if.h>
#include <boot_coldplug_if.h>
#include <boot_shared_imem_cookie.h>
#include <boot_media_interface_if.h>
#include <boot_edk2_cache_if.h>
#include <boot_edk2_armlib_if.h>
#include "secboot_hw.h"
#include "boot_sbl_shared.h"
#include "boot_sbl_if.h"
#include "coldplug_api.h"

extern uint8 ddr_params_partition_id[];

bl_error_boot_type  read_ddr_training_data_from_partition(uint8 * ddr_training_data_buf, uint64 offset, uint64 size )
{
  bl_error_boot_type return_status = BL_ERR_NONE, temp_status = BL_ERR_NONE;
  boot_media_interface_if_type *media_if = NULL;
  boot_handle media_handle = NULL;
  boot_handle crt_handle = NULL;
  uint32 pbl_media_boot_device = 0;
  uint32 boot_device = 0;
  struct coldplug_guid *previous_partition_id = NULL;
  do
  {
    return_status = boot_config_context_get_crt_handle(&crt_handle);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = boot_config_context_get_value(crt_handle, CONFIG_CONTEXT_BOOT_DEVICE, (void *)&boot_device);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }
    /* backup boot media device */
    return_status = boot_config_context_get_value(crt_handle, CONFIG_CONTEXT_PBL_MEDIA_BOOT_DEVICE, (void *)&pbl_media_boot_device);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }
    /* backup current partition GUID */
    return_status = boot_config_context_get_ptr(crt_handle, CONFIG_CONTEXT_PARTITION_ID, (void **)(uintptr_t)&previous_partition_id);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }
    
    return_status = boot_config_context_set_value(crt_handle, CONFIG_CONTEXT_BOOT_DEVICE, pbl_media_boot_device);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }

    /* set DDR partition GUID */
    return_status = boot_config_context_set_ptr(crt_handle, CONFIG_CONTEXT_PARTITION_ID, ddr_params_partition_id);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = boot_config_context_get_ptr(crt_handle, CONFIG_CONTEXT_BOOT_MEDIA_INTERFACE, (void **)&media_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = media_if->open(crt_handle, &media_handle);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = media_if->read(media_handle, (void *)ddr_training_data_buf, offset, size);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
  } while (FALSE);

  do
  {
    if (media_handle!= NULL)
    {
      temp_status = media_if->close(media_handle);
      if (temp_status != BL_ERR_NONE)
      {
        return_status = temp_status;
        break;
      }
    }
    
    /* restore boot media device */
    temp_status = boot_config_context_set_value(crt_handle, CONFIG_CONTEXT_BOOT_DEVICE, boot_device);
    if (temp_status != BL_ERR_NONE)
    {
      return_status = temp_status;
      break;
    }
    /* restore previous partition GUID */
    return_status = boot_config_context_set_ptr(crt_handle, CONFIG_CONTEXT_PARTITION_ID, previous_partition_id);
    if (temp_status != BL_ERR_NONE)
    {
      return_status = temp_status;
      break;
    }   
  }while (FALSE);
  return return_status;
}

boolean boot_PlatformInfo_IsFusion(void)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_platforminfo_if_type *platforminfo_if = NULL;

  return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PLATFORMINFO_INTERFACE, (void **)&platforminfo_if);
  if (return_status != BL_ERR_NONE)
    return 0;

  return platforminfo_if->IsFusion();
}

/* SONY_BEGIN(Ramdumper support) */
#ifdef FEATURE_SONY_RAMDUMP
pm_err_flag_type boot_pm_dev_get_power_on_reason(unsigned pmic_device_index,
                                                 uint64 * pwr_on_reason)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_pmic_if_type *pmic_if = NULL;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PMIC_INTERFACE, (void **)&pmic_if);
  if(status != BL_ERR_NONE)
    return 0;

  return pmic_if->pm_dev_get_power_on_reason(pmic_device_index, pwr_on_reason);
}
#endif /* FEATURE_SONY_RAMDUMP */
/* SONY_END(Ramdumper support) */
