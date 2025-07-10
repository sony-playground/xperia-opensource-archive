/** @file
*  XnWrapperLib.c
*  Copyright (c) 2021 Qualcomm Technologies, Inc. All Rights Reserved.
*  Portions Copyright (c) 2018 Microsoft Corporation. All rights reserved
*  Library to wrap QC's XN-support code.
*
*  Must be linked anonymously to BDS.
*
*  Library constructor registers a handler for ReadyToBoot event.
*  The handler subs in a local fuction point to gBS's AllocatePages call.
*  The local function calls the original AllocatePages and then if it is a code
*  segment calls gDS->SetMemorySpaceAttributes to remove XN attribute from the
*  allocated pages.
*
**/

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PerformanceLib.h>

STATIC EFI_ALLOCATE_PAGES mOriginalAllocatePages = NULL;
EFI_EVENT                 mReadyToBootEvent;

/**
  Allocates pages from the memory map.

  @param  Type                   The type of allocation to perform
  @param  MemoryType             The type of memory to turn the allocated pages
                                 into
  @param  NumberOfPages          The number of pages to allocate
  @param  Memory                 A pointer to receive the base allocated memory
                                 address

  @return Status. On success, Memory is filled in with the base address allocated
  @retval EFI_INVALID_PARAMETER  Parameters violate checking rules defined in
                                 spec.
  @retval EFI_NOT_FOUND          Could not allocate pages match the requirement.
  @retval EFI_OUT_OF_RESOURCES   No enough pages to allocate.
  @retval EFI_SUCCESS            Pages successfully allocated.

**/
EFI_STATUS
EFIAPI
LocalAllocatePages (
  IN  EFI_ALLOCATE_TYPE     Type,
  IN  EFI_MEMORY_TYPE       MemoryType,
  IN  UINTN                 NumberOfPages,
  OUT EFI_PHYSICAL_ADDRESS  *Memory
  )
{
  EFI_STATUS  Status;
  EFI_STATUS  WbStatus;

  ASSERT (mOriginalAllocatePages != NULL);

  Status = mOriginalAllocatePages (Type, MemoryType, NumberOfPages, Memory);

  if ((!EFI_ERROR (Status)) && ((MemoryType == EfiLoaderCode) || (MemoryType == EfiBootServicesCode) || (MemoryType == EfiRuntimeServicesCode))) {
    WbStatus = gDS->SetMemorySpaceAttributes (*Memory, NumberOfPages*EFI_PAGE_SIZE, EFI_MEMORY_WB);
    if (EFI_ERROR (WbStatus)) {
      DEBUG ((DEBUG_ERROR, "XnWrapperLib: Failed clearing XN %r \n", WbStatus));
      ASSERT(FALSE);
    }
  }

  return Status;
}

/**
  Event handler registered for ReadyToBoot.
  Points gBS->AllocatePages to a local function that calls the original function and also handles XN.

  @param Event      The event that occured, not used
  @param Context    The event context

**/
VOID
EFIAPI
ReadyToBootHandler (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  PERF_CALLBACK_BEGIN(&gEfiEventReadyToBootGuid);
  DEBUG ((DEBUG_INFO, "XnWrapper ReadyToBootHandler\n"));
  mOriginalAllocatePages = gBS->AllocatePages;
  gBS->AllocatePages = LocalAllocatePages;
  gBS->Hdr.CRC32 = 0;
  gBS->CalculateCrc32(gBS, sizeof (EFI_BOOT_SERVICES), &gBS->Hdr.CRC32);

  //
  // ReadyToBoot can get signalled multiple times. We only need to run once.
  //
  gBS->CloseEvent(mReadyToBootEvent);
  PERF_CALLBACK_END(&gEfiEventReadyToBootGuid);
}

/**
  Constructor:

  Create a ReadyToBoot event that would call ReadyToBootHandler.

  @param[in] ImageHandle  Driver's image handle.
  @param[in] *SystemTable Pointer to system table.

  @return EFI_SUCCESS

**/
EFI_STATUS
EFIAPI
XnWrapperConstructor (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS  Status;

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  ReadyToBootHandler,
                  NULL,
                  &gEfiEventReadyToBootGuid,
                  &mReadyToBootEvent
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "XnWrapperConstructor: Failed to create event %r\n", Status));
    ASSERT(FALSE);
  }

  return EFI_SUCCESS;
}
