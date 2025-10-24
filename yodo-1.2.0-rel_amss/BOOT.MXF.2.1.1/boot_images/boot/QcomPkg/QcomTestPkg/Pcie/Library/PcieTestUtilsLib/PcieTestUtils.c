/** 
 * Utils
 *  
 * Copyright (c) 2021 Qualcomm Technologies, Inc. All rights reserved.
 *
**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/26/21   yg      Initial version

=============================================================================*/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EFITlmm.h>
#include <Protocol/EfiQcPcie.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Library/PcieTestUtils.h>
#include "pcie_host_r.h"
#include <string.h>

EFI_STATUS SetSocGpio (UINTN Pin, UINTN Level)
{
  EFI_TLMM_PROTOCOL *TLMMProtocol = NULL;
  EFI_STATUS Status;

  Status = gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (VOID **)&TLMMProtocol);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "Unable to locate TLMM protocol\r\n"));
    return Status;
  }

     Status = TLMMProtocol->ConfigGpio(
         (UINT32)EFI_GPIO_CFG(Pin, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA),
         Level);
     if (EFI_ERROR(Status))
       return Status;

     Status = TLMMProtocol->GpioOut(
         (UINT32)EFI_GPIO_CFG(Pin, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_2MA),
         Level);
     if (EFI_ERROR(Status))
       return Status;

  return EFI_SUCCESS;  
}


EFI_STATUS GetTargetPlatformInfo (EFIChipInfoIdType        *ChipIdPtr, 
                                  EFIChipInfoVersionType   *ChipVerPtr, 
                                  EFIChipInfoFamilyType    *ChipFamilyPtr, 
                                  UINT32                   *PlatTypePtr)
{
  EFI_STATUS                  Status;
  EFI_CHIPINFO_PROTOCOL      *pChipInfo;
  EFI_PLATFORMINFO_PROTOCOL  *pPlatformInfo;
  EFIChipInfoIdType           ChipId;
  EFIChipInfoVersionType      Version;
  EFIChipInfoFamilyType       ChipFamily;
  EFI_PLATFORMINFO_PLATFORM_INFO_TYPE PlatformInfo;

  if (PlatTypePtr)
  {
     Status = gBS->LocateProtocol (&gEfiPlatformInfoProtocolGuid, NULL,
                                   (VOID **) &pPlatformInfo);
     if (EFI_ERROR(Status))
       return Status;

     Status = pPlatformInfo->GetPlatformInfo(pPlatformInfo, &PlatformInfo);
     if (EFI_ERROR(Status))
       return Status;

     *PlatTypePtr = PlatformInfo.platform;
  }

  Status = gBS->LocateProtocol (&gEfiChipInfoProtocolGuid, NULL,
                               (VOID **) &pChipInfo);
  if (EFI_ERROR(Status))
    return Status;

  if (ChipIdPtr)
  {
     Status = pChipInfo->GetChipId(pChipInfo, &ChipId);
     if (Status != EFI_SUCCESS)
       return Status;

     *ChipIdPtr = ChipId;
  }

  if (ChipVerPtr)
  {
     Status = pChipInfo->GetChipVersion(pChipInfo, &Version);
     if (Status != EFI_SUCCESS)
       return Status;

     *ChipVerPtr = Version;
  }

  if (ChipFamilyPtr)
  {
     Status = pChipInfo->GetChipFamily(pChipInfo, &ChipFamily);
     if (Status != EFI_SUCCESS)
       return Status;

     *ChipFamilyPtr = ChipFamily;
  }

   return Status;
}

static dev_handle_info_type ep_handle_info[MAX_PCIE_CORES];

void probe_cb_fn (pcie_dev_t *pdev, const pcie_dev_probe_cb_payload_t *cb_data, void* user_data)
{
   int i;
   pcie_dev_t *ep_handle, *rc_handle;
   dev_handle_info_type* handle_info = (dev_handle_info_type*)user_data;

   if ((handle_info == NULL) || (cb_data == NULL) ||
       (handle_info->RcIdx != (cb_data->dev_ids.rbdf_info >> 16)))
      return;

   AsciiPrint ("Device EP detected on core %d : Vend ID %X, Dev ID %X\r\n", handle_info->RcIdx, cb_data->dev_ids.vendor_id, cb_data->dev_ids.device_id);

   for (i=0; i<PCIE_MAX_BARS; ++i)
      if (cb_data->rsrc.bars[i].pa)
         AsciiPrint ("BAR %d : 0x%X  0x%X\r\n", i, cb_data->rsrc.bars[i].pa, cb_data->rsrc.bars[i].sz);

   ep_handle = pdev;

   rc_handle = ep_handle;

   while (rc_handle)
   {
      pcie_dev_t *ptr = pcie_get_parent (rc_handle);
      if ((ptr == NULL) || (rc_handle == ptr))
         break;
      rc_handle = ptr;
   }

   if (rc_handle == ep_handle)
      AsciiPrint ("Parent handle failure\n");

   handle_info->ep_handle = ep_handle;
   handle_info->rc_handle = rc_handle;
   handle_info->ep_info = *cb_data;
}

#define REGISTER_OPERATION     1
#define UNREGISTER_OPERATION   2

void register_handler (dev_handle_info_type* handle_info, int reg_operation)
{
   pcie_device_info_t FilterDeviceID;

   FilterDeviceID.vendor_id = PCIE_ID_ANY;
   FilterDeviceID.device_id = PCIE_ID_ANY;
   FilterDeviceID.class_id = PCIE_ID_ANY;
   FilterDeviceID.rbdf_info = 0;

   if (reg_operation == REGISTER_OPERATION)
     pcie_register_device (&FilterDeviceID, probe_cb_fn, handle_info);
   else
     pcie_unregister_device (&FilterDeviceID, probe_cb_fn, handle_info);
}

pcie_status_t get_enumerated_dev_handle (uint32 port_idx, dev_handle_info_type* dev_handle_info_ptr)
{
   dev_handle_info_type *handle_info;

   if (dev_handle_info_ptr == NULL)
      return PCIE_INVALID_PARAM;

   handle_info = &ep_handle_info[port_idx];

   if (handle_info->ep_handle == NULL)
      return PCIE_NOT_READY;

   *dev_handle_info_ptr = *handle_info;

   return PCIE_SUCCESS;
}

pcie_status_t enumerate_pcie_port (uint32 port_idx)
{
   dev_handle_info_type *handle_info;
   pcie_status_t pstatus;

   if (port_idx >= MAX_PCIE_CORES)
      AsciiPrint ("Invalid core index, max set : %d\r\n", MAX_PCIE_CORES);

   handle_info = &ep_handle_info[port_idx];

   gBS->SetMem (handle_info, sizeof(*handle_info), 0);

   handle_info->RcIdx = port_idx;
   register_handler (handle_info, REGISTER_OPERATION);

   pstatus = pcie_enumerate (port_idx);

   register_handler (handle_info, UNREGISTER_OPERATION);

   if (pstatus != PCIE_SUCCESS)
   {
       AsciiPrint ("Link enumeration failed\n");
       return PCIE_ERROR;
   }

   /* By now we should have both EP and RC handles valid */
   if (!handle_info->ep_handle || !handle_info->rc_handle ||
        (handle_info->rc_handle == handle_info->ep_handle))
   {
      AsciiPrint ("Invalid handles\n");
      pcie_reset (port_idx);
      return PCIE_ERROR;
   }

   pcie_enable_device (handle_info->ep_handle);

   gBS->Stall (1000); // wait 1ms

   return PCIE_SUCCESS;
}

pcie_status_t poweroff_pcie_port (uint32 port_idx)
{
   dev_handle_info_type handle_info, *handle_info_ptr;
   pcie_status_t pstatus;

   if (port_idx >= MAX_PCIE_CORES)
      AsciiPrint ("Invalid core index, max set : %d\r\n", MAX_PCIE_CORES);

   pstatus = get_enumerated_dev_handle (port_idx, &handle_info);
   if (pstatus != PCIE_SUCCESS)
   {
       AsciiPrint ("Handle not found\n");
       return PCIE_ERROR;
   }

   pcie_disable_device (handle_info.ep_handle);

   gBS->Stall (1000); // wait 1ms

   pstatus = pcie_reset (port_idx);

   if (port_idx >= MAX_PCIE_CORES)
      AsciiPrint ("Invalid core index, max set : %d\r\n", MAX_PCIE_CORES);

   handle_info_ptr = &ep_handle_info[port_idx];

   gBS->SetMem (handle_info_ptr, sizeof(*handle_info_ptr), 0);

   if (pstatus != PCIE_SUCCESS)
   {
       AsciiPrint ("Core reset failed\n");
      return PCIE_ERROR;
   }

   AsciiPrint ("Core reset done\n");
   return PCIE_SUCCESS;
}

pcie_status_t get_link_status (UINTN CoreIdx, pcie_link_status_t *link_status_info_ptr)
{
   pcie_status_t pstatus;

   memset (link_status_info_ptr, 0, sizeof(*link_status_info_ptr));
   pstatus = pcie_get_link_status (CoreIdx, link_status_info_ptr);
   if (pstatus != PCIE_SUCCESS)
      AsciiPrint ("Failed to get link status %X\n", pstatus);

   return pstatus;
}

// use when we need to map SID to only free memory
UINTN * GetMaxFreeMem (UINT64 *FreeSize)
{
  EFI_STATUS            Status;
  EFI_MEMORY_DESCRIPTOR *MemMap = NULL;
  EFI_MEMORY_DESCRIPTOR *OrigMemMap = 0;
  UINTN                 MemMapSize = 0;
  UINTN                 MapKey, MaxFree = 0;
  UINTN                 DescriptorSize;
  UINT32                DescriptorVersion;
  UINTN                 i;
  UINT64                TotalPages = 0;
  UINTN * MaxFreeBase = 0;

  // First call is to figure out how big the buffer needs to be
  Status = gBS->GetMemoryMap (&MemMapSize, MemMap, &MapKey, &DescriptorSize, &DescriptorVersion);
  if (Status == EFI_BUFFER_TOO_SMALL)
  {
    // In case the AllocatPool changes the memory map we added in some extra descriptors
    MemMapSize += (DescriptorSize * 0x100);
    OrigMemMap = MemMap = AllocatePool (MemMapSize);
  }

  if (OrigMemMap == NULL)
  {
    AsciiPrint ("Unable to allocate memory\n");
    return NULL;
  }

  Status = gBS->GetMemoryMap (&MemMapSize, MemMap, &MapKey, &DescriptorSize, &DescriptorVersion);

  if (EFI_ERROR (Status))
  {
    AsciiPrint ("Failed to get memory map\n");
    return NULL;
  }
  
  for (i = 0; i < MemMapSize/DescriptorSize; i++)
  {
    if (MemMap->Type == EfiConventionalMemory)
    {
      if (MaxFree < MemMap->NumberOfPages)
      {
        MaxFree = MemMap->NumberOfPages;
        MaxFreeBase = (UINTN*)MemMap->PhysicalStart;
      }
    }
    TotalPages += MemMap->NumberOfPages;
    MemMap = NEXT_MEMORY_DESCRIPTOR (MemMap, DescriptorSize);
  }

  FreePool (OrigMemMap);

  AsciiPrint ("EFI Memory Map\n");
  AsciiPrint ("Total memory : %d MB\n", (TotalPages / 256));
  AsciiPrint ("Largest Free chunk : %d MB\n", (MaxFree / 256));
  AsciiPrint ("Free chunk Base : %x MB\n", MaxFreeBase);

  *FreeSize = MaxFree;

  return MaxFreeBase;
}

