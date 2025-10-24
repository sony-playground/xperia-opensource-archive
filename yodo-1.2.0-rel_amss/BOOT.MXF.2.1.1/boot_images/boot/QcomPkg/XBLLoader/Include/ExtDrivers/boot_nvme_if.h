/*===========================================================================

                    BOOT EXTERN NVMe DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external NVMe driver

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/16/20   sp      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <nvme_api.h>

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 



typedef struct boot_nvme_if_type
{
    uint32 (*read) (struct nvme_handle *handle, void *buff, uint64 lba, uint64 num_blocks);
    uint32 (*write) (struct nvme_handle *handle, void *buff, uint64 lba, uint64 num_blocks);
    uint32 (*flush) (struct nvme_handle *handle);
    struct nvme_handle* (*open) (uint32 id, uint32 namespace_num, uint32 *error_num);
    uint32 (*close) (struct nvme_handle *handle);
    uint32 (*get_namespace_sizes) (struct nvme_handle *handle, struct nvme_namespace_sizes *info);
    uint32 (*get_device_info) (uint32 id, struct nvme_device_info *info);
} boot_nvme_if_type;


extern boot_nvme_if_type nvme_if;