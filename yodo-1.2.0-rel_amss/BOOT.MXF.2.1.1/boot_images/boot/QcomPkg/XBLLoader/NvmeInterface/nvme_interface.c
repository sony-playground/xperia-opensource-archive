/*===========================================================================

                    BOOT NVMe DRIVER Interface

DESCRIPTION
  Contains functions for external NVMe drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020-2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/27/20   sp      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_config_context.h"
#include "boot_nvme_if.h"
#include "boot_error_if.h"
#include "nvme_api.h"
/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

/*=============================================================================

FUNCTION DEFINITIONS

=============================================================================*/

uint32 nvme_read(struct nvme_handle *handle, void *buff, uint64 lba, uint64 num_blocks)
{
  bl_error_boot_type status = BL_ERR_NONE;
  uint32 nvme_status = NVME_SUCCESS;
  boot_nvme_if_type *nvme_if = NULL;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_NVME_INTERFACE, (void **)&nvme_if);
  if(status != BL_ERR_NONE)
  {
    nvme_status = NVME_SW_EINVAL_PARAM;
  }

  nvme_status = nvme_if->read(handle, buff, lba, num_blocks);
  if(nvme_status != NVME_SUCCESS)
  {
    return nvme_status;
  }

  return nvme_status;
}

uint32 nvme_write(struct nvme_handle *handle, void *buff, uint64 lba, uint64 num_blocks)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_nvme_if_type *nvme_if = NULL;
  uint32 nvme_status = NVME_SUCCESS;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_NVME_INTERFACE, (void **)&nvme_if);
  if(status != BL_ERR_NONE)
  {
    nvme_status = NVME_SW_EINVAL_PARAM;
  }

  return nvme_if->write(handle, buff, lba, num_blocks);
  if(nvme_status != NVME_SUCCESS)
  {
    return nvme_status;
  }

  return nvme_status;
}

uint32 nvme_flush(struct nvme_handle *handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_nvme_if_type *nvme_if = NULL;
  uint32 nvme_status = NVME_SUCCESS;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_NVME_INTERFACE, (void **)&nvme_if);
  if(status != BL_ERR_NONE)
  {
    nvme_status = NVME_SW_EINVAL_PARAM;
  }

  nvme_status = nvme_if->flush(handle);
  if(nvme_status != NVME_SUCCESS)
  {
    return nvme_status;
  }

  return nvme_status;
}

struct nvme_handle* nvme_open(uint32 id, uint32 namespace_num, uint32 *error_num)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_nvme_if_type *nvme_if = NULL;
  struct nvme_handle *handle = NULL;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_NVME_INTERFACE, (void **)&nvme_if);
  if(status != BL_ERR_NONE)
  {
    return handle;
  }

  handle = nvme_if->open(id, namespace_num, error_num);

  return handle;
}

uint32 nvme_close(struct nvme_handle *handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_nvme_if_type *nvme_if = NULL;
  uint32 nvme_status = NVME_SUCCESS;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_NVME_INTERFACE, (void **)&nvme_if);
  if(status != BL_ERR_NONE)
  {
    nvme_status = NVME_SW_EINVAL_PARAM;
  }

  nvme_status = nvme_if->close(handle);
  if(nvme_status != NVME_SUCCESS)
  {
    return nvme_status;
  }

  return nvme_status;
}

uint32 nvme_get_namespace_sizes(struct nvme_handle *handle, struct nvme_namespace_sizes *info)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_nvme_if_type *nvme_if = NULL;
  uint32 nvme_status = NVME_SUCCESS;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_NVME_INTERFACE, (void **)&nvme_if);
  if(status != BL_ERR_NONE)
  {
    nvme_status = NVME_SW_EINVAL_PARAM;
  }

  nvme_status = nvme_if->get_namespace_sizes(handle, info);
  if(nvme_status != NVME_SUCCESS)
  {
    return nvme_status;
  }

  return nvme_status;
}

uint32 nvme_get_device_info(uint32 id, struct nvme_device_info *info)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_nvme_if_type *nvme_if = NULL;
  uint32 nvme_status = NVME_SUCCESS;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_NVME_INTERFACE, (void **)&nvme_if);
  if(status != BL_ERR_NONE)
  {
    nvme_status = NVME_SW_EINVAL_PARAM;
  }

  nvme_status = nvme_if->get_device_info(id, info);
  if(nvme_status != NVME_SUCCESS)
  {
    return nvme_status;
  }

  return nvme_status;
}
