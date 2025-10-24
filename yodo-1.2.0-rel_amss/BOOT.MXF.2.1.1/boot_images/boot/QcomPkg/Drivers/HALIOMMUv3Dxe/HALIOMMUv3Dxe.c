//============================================================================
/**
  Copyright (c) 2015-2019, 2021 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
//============================================================================
#include <Protocol/IoMmu.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include "HALIOMMUv3.h"
#include <Protocol/EFISmmuMapSid.h>

extern EFI_STATUS HAL_IOMMUv3_Init(VOID);
extern VOID EFIAPI HAL_IOMMUv3_EBS_Callback(IN EFI_EVENT Event, IN VOID *Context);

volatile UINT32 g_unit_test_enabled = 0;

EDKII_IOMMU_PROTOCOL HAL_IOMMUv3_PROTOCOL = {
    EDKII_IOMMU_PROTOCOL_REVISION,
    HAL_IOMMUv3_Set_Attribute,
    HAL_IOMMUv3_Map,
    HAL_IOMMUv3_Unmap,
    HAL_IOMMUv3_Allocate_Buffer,
    HAL_IOMMUv3_Free_Buffer
};


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
  UINT32            Pages
  )
{
    return AllocatePages(Pages);
}

EFI_STATUS  MapPcieSID (IN  UINT32      RBdf,
                        IN  VOID       *HostAddr,
                        IN  UINTN      NumBytes,
                        OUT VOID      **MapHandlePtr)
{
   EFI_STATUS   Status;
   VOID        *MapHandle;
   UINTN        ByteCnt = NumBytes;
   EFI_PHYSICAL_ADDRESS DevAddr = 0;

   if ((HostAddr == 0) || (ByteCnt == 0) || (MapHandlePtr == 0))
      return EFI_INVALID_PARAMETER;

   Status = HAL_IOMMUv3_Map (NULL, EdkiiIoMmuOperationBusMasterCommonBuffer64, HostAddr, &ByteCnt, &DevAddr, &MapHandle);
    if (Status != EFI_SUCCESS)
       return Status;

   Status = HAL_IOMMUv3_Set_Attribute (NULL, (EFI_HANDLE)(UINTN)RBdf, MapHandle, EDKII_IOMMU_ACCESS_WRITE);
   if (Status != EFI_SUCCESS)
   {
      HAL_IOMMUv3_Unmap (NULL, MapHandle);
      return Status;
   }

   *MapHandlePtr = MapHandle;
    
   return EFI_SUCCESS;
}

EFI_STATUS  UnmapSID (IN  VOID* MapHandle)
{
    return HAL_IOMMUv3_Unmap(NULL, MapHandle);
}

EFI_SMMU_MAP_SID_PROTOCOL Smmu_Map_SID_Protocol = 
{
   .Version = EFI_SMMU_MAP_SID_PROTOCOL_VER,

   .MapPcieSid = &MapPcieSID,
   .UnmapSid = &UnmapSID,
};

EFI_STATUS
EFIAPI
HAL_IOMMUv3DxeEntryPoint(
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
    EFI_HANDLE  handle = NULL;
    EFI_EVENT   IOMMUv3_EFI_Event;
    EFI_STATUS  status;

    // Publish the HAL_IOMMU Protocol
    status = gBS->InstallMultipleProtocolInterfaces(&handle, 
                                                    &gEdkiiIoMmuProtocolGuid, 
                                                    (void **)&HAL_IOMMUv3_PROTOCOL, NULL );
    if (EFI_SUCCESS != status)
    {
        return status;
    }

    // Initialize V3 Driver
    status = HAL_IOMMUv3_Init();
    if(EFI_SUCCESS != status) {
        return status;
    }
    
    // Register EBS Callback
    status = gBS->CreateEvent(EVT_SIGNAL_EXIT_BOOT_SERVICES,
                              TPL_CALLBACK,
                              HAL_IOMMUv3_EBS_Callback,
                              NULL,
                              &IOMMUv3_EFI_Event);
    if(EFI_SUCCESS != status) {
        return status;
    }

    status = gBS->InstallMultipleProtocolInterfaces(&handle, 
                                                    &gEfiSmmuMapSidProtocolGuid, 
                                                    (void **)&Smmu_Map_SID_Protocol, NULL);
    // nothing much to do on failure
    
    if(g_unit_test_enabled) {
        UINTN bytes = 0x1000;
        void *map_handle;
        
        HAL_IOMMUv3_Map(NULL, EdkiiIoMmuOperationBusMasterCommonBuffer64, (void *)0x9F800000, &bytes, (void *)0x9F800000, &map_handle);
        
        HAL_IOMMUv3_Set_Attribute(NULL, NULL, map_handle, EDKII_IOMMU_ACCESS_READ | EDKII_IOMMU_ACCESS_WRITE);

        HAL_IOMMUv3_Unmap(NULL, map_handle);
    }
   
    return EFI_SUCCESS;
}
