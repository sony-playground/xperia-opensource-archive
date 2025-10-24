/** @file NvmeLoaderLibNull.c
  
  Stub functions for NvmeLoaderLib

  Copyright (c) 2020 Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/17/20   sp      Initial revision

=============================================================================*/
#include "nvme_api.h"

uint32 nvme_read(struct nvme_handle *handle,
                 void               *buff,
                 uint64             lba,
                 uint64             num_blocks)
{
  return NVME_SUCCESS;
}

uint32 nvme_write(struct nvme_handle *handle,
                  void               *buff,
                  uint64             lba,
                  uint64             num_blocks)
{
  return NVME_SUCCESS;
}

uint32 nvme_flush(struct nvme_handle *handle)
{
  return NVME_SUCCESS;
}

struct nvme_handle *nvme_open (uint32 id, uint32 namespace_num, uint32 *error_num)
{
  return NULL;
}

uint32 nvme_close (struct nvme_handle *handle)
{
  return NVME_SUCCESS;
}

uint32 nvme_get_namespace_sizes (struct nvme_handle *handle,
                                 struct nvme_namespace_sizes *info)
{
  return NVME_SUCCESS;
}

uint32 nvme_get_device_info (uint32 id,
                             struct nvme_device_info *info)
{
  return NVME_SUCCESS;
}
