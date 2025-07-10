//============================================================================
/**
  Copyright (c) 2015-2019,2021 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
//============================================================================

#include <Protocol/EFIHALIOMMUProtocol.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include "IORT.h"
#include "HALIOMMUReg.h"
#include "HALIOMMULib.h"
#include "mmu.h"

/* Forward function declarations */
void _HAL_IOMMU_protocol_init(HAL_IOMMU_fptable_t **p_fp_table);
void _HAL_IOMMU_protocol_deinit(void);
static EFI_STATUS HAL_IOMMU_Device_Tree_Init(void);

EFI_HAL_IOMMU_PROTOCOL HAL_IOMMUProtocol = 
{
    HAL_IOMMU_REVISION,
    _HAL_IOMMU_protocol_init,
    _HAL_IOMMU_protocol_deinit,
};

void _HAL_IOMMU_protocol_init(HAL_IOMMU_fptable_t **p_fp_table)
{
    static HAL_IOMMU_fptable_t hal_iommu_fp_table =
    {
        hal_iommu_domain_create,
        hal_iommu_domain_delete,
        hal_iommu_domain_attach_device,
        hal_iommu_domain_detach_device,
        hal_iommu_domain_configure,
        hal_iommu_flush_domain,
        hal_iommu_flush_domain_va_list,
        hal_iommu_register_fault_handler,
        hal_iommu_configure_bypass_domain,
		IDIOM_Detach,
        arch_mmu_init_aspace,
        arch_mmu_destroy_aspace,
        arch_mmu_map,
        arch_mmu_unmap,
        hal_iommu_domain_update_aspace,
    };
    
    // install function pointer table
    *p_fp_table = &hal_iommu_fp_table;
}

void _HAL_IOMMU_protocol_deinit(void)
{
    // TODO
    return;
}

/**
  Allocates one or more 4KB pages of a certain memory type.

  Allocates the number of 4KB pages of a certain memory type and returns a pointer to the allocated
  buffer.  The buffer returned is aligned on a 4KB boundary.  If Pages is 0, then NULL is returned.
  If there is not enough memory remaining to satisfy the request, then NULL is returned.

  @param  Pages                 The number of 4 KB pages to allocate.

  @return A pointer to the allocated buffer or NULL if allocation fails.

**/
VOID *
HAL_IOMMU_InternalAllocatePages (
  uint32_t            Pages
  )
{
  return UncachedAllocatePages(Pages);
}

EFI_STATUS
EFIAPI
HAL_IOMMUDxeEntryPoint(
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
   EFI_HANDLE  handle = NULL;
   EFI_STATUS  status;

   // Publish the HAL_IOMMU Protocol
   status = gBS->InstallMultipleProtocolInterfaces( &handle, 
         &gEfiHalIommuProtocolGuid, 
         (void **)&HAL_IOMMUProtocol, NULL );
   if (EFI_SUCCESS != status)
   {
      return status;
   }
   
   // Register BootExitServices Callback function
   //TODO
   
   // Invoke IORT Device Tree initialization and return
   return HAL_IOMMU_Device_Tree_Init();
}

static EFI_STATUS HAL_IOMMU_Device_Tree_Init(void)
{
   if( parseIORTDT() == 0)
   {
      return EFI_SUCCESS;
   }
   else
    return EFI_NOT_READY;
}

HAL_IOMMUResult_t IDIOM_domain_lookup(void**p_domain_local, void *client_handle)
{
    HAL_IOMMUResult_t ret = HAL_IOMMU_ERR_OK;
	/* Input Validation */
    if( !client_handle || !p_domain_local ) {
        return HAL_IOMMU_ERR_NULL_POINTER;
    }
    
	return ret;	
}
