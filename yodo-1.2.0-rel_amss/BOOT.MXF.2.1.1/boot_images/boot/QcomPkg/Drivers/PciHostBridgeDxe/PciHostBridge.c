/** @file
*  Pci Host Bridge support for Qualcomm PCIe Root Complex
*
*  Copyright (c) 2016-2017, 2020 - 2022 Qualcomm Technologies Inc. All rights reserved.
*  Copyright (c) 2011-2015, ARM Ltd. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
*
*  EDIT HISTORY
*
*  when      who      what, where, why
*  --------  -------  --------------------------------------------------------
*  12/17/20   yg      Fix ACPI UID to be same across reboots
*  02/10/17  ts       Fixed a simple debug message typo
*  07/08/16  ts       Derived from ARMJuno PciHostBridgeDxe for Qualcomm PCIe
**/

#include "PciHostBridge.h"
#include "Library/QcomBaseLib.h"

#include <Guid/EventGroup.h>

/* IOMMU protocol utilization */
EDKII_IOMMU_PROTOCOL        *gHalIoMmuProtocol = NULL;
EFI_EVENT                    gHalIoMmuEvent;
VOID                        *gHalIoMmuRegistration;

/* Template for PCI Host Bridge Instance */
STATIC CONST PCI_HOST_BRIDGE_INSTANCE
gPciHostBridgeInstanceTemplate = {
  .Signature           = PCI_HOST_BRIDGE_SIGNATURE,
  .Handle              = NULL,
  .ImageHandle         = NULL,
  .ResourceSubmitted   = FALSE,
  .CanRestarted        = TRUE,
  .NumberOfRootBridges = 0,
  .RbHead              = {.ForwardLink = NULL, .BackLink = NULL},
  .HbList              = {.ForwardLink = NULL, .BackLink = NULL},
  .ResAlloc            = {.NotifyPhase = PciHbRaNotifyPhase,
                          .GetNextRootBridge = PciHbRaGetNextRootBridge,
                          .GetAllocAttributes = PciHbRaGetAllocAttributes,
                          .StartBusEnumeration = PciHbRaStartBusEnumeration,
                          .SetBusNumbers = PciHbRaSetBusNumbers,
                          .SubmitResources = PciHbRaSubmitResources,
                          .GetProposedResources = PciHbRaGetProposedResources,
                          .PreprocessController = PciHbRaPreprocessController
                         }
};

/* Global list of all HostBridge Instances */
STATIC LIST_ENTRY gPciHostBridgeInstanceList;

/* Combine both Host bridge index and Rootbridge index to derive unique UID in the system.
 * Since UID should NOT change across reboots ref 10.3.3 ACPI Device Path in UEFI Spec 2.8 */
#define MAKE_ACPI_UID(x,y) ((x & 0xFFFF) | ((y & 0xFFFF) << 16))

/**
  @fn HostBridgeConstructor
  @brief HostBridge Constructor routine

  This function will construct a single HostBridge and all RootBridge
  Instances underneath it keep a note of all this HostBridge Instance
  in Global Linked List gPciHostBridgeInstanceList

  @param[in]   ImageHandle     EFI Image Handle of this DXE image
  @param[in]   HostBridgeIndex Current HostBridgeIndex start from 0 to
               be initialized

  @retval EFI_SUCCESS            A new HostBridge and its RootBridges are successfully created
  @retval EFI_DEVICE_ERROR       Installing Protocols failed.
  @retval EFI_OUT_OF_RESOURCES   A new HostBridge cannot be created because AllocateCopyPool failed.
**/

EFI_STATUS
HostBridgeConstructor (
  IN EFI_HANDLE                     ImageHandle,
  IN UINT32                         HostBridgeIndex
  )
{
  EFI_STATUS                  Status;
  PCI_HOST_BRIDGE_INSTANCE*   HostBridge;
  UINT32                      RbIdx;

  PCI_TRACE ("HostBridgeConstructor()");

  HostBridge = AllocateCopyPool (sizeof(PCI_HOST_BRIDGE_INSTANCE), &gPciHostBridgeInstanceTemplate);
  if (HostBridge == NULL)
  {
    PCI_TRACE ("HostBridgeConstructor(): FAIL to allocate resources");
    return EFI_OUT_OF_RESOURCES;
  }

  Status = gBS->InstallMultipleProtocolInterfaces (&HostBridge->Handle,
                    &gEfiPciHostBridgeResourceAllocationProtocolGuid, &HostBridge->ResAlloc,
                    NULL);

  if (EFI_ERROR (Status))
  {
    PCI_TRACE ("HostBridgeConstructor(): FAIL to install resource allocator");
    FreePool (HostBridge);
    return EFI_DEVICE_ERROR;
  }

  HostBridge->ImageHandle = ImageHandle;
  HostBridge->HostBridgeIndex = HostBridgeIndex;

  /* Get Number of PCIe Root Bridges to be installed under one segment */
  HostBridge->NumberOfRootBridges = PcieConfigLibGetNumberOfRootBridges (HostBridgeIndex);  // TODO: Just a stopgap solution for now

  /* Make a note of this HostBrisge Instance in the global
   * linked list, so, it would come handy when we are calling
   * HostBridgeDestructor.  */
  InsertTailList (&gPciHostBridgeInstanceList, &HostBridge->HbList);

  /* Initialize RbHead, this list would hold all the instances
   * of the available root bridges */
  InitializeListHead (&HostBridge->RbHead);

  for (RbIdx = 0; RbIdx < HostBridge->NumberOfRootBridges; RbIdx++)
  {
    /* Make sure to give arg in such a way that the UID matches to what's listed in the
     * ACPI Tables, which is same as the HW index (which is HostBridgeIndex) */
    Status = PciRbConstructor (HostBridge, MAKE_ACPI_UID(HostBridgeIndex, RbIdx));

    /* If a port is not available just continue */
    if ((Status != EFI_SUCCESS) && (Status != EFI_NOT_FOUND))
    {
      PCI_TRACE ("Failed to construct PCI Root Bridge.");
      return Status;
    }
  }

  return EFI_SUCCESS;
}

/**
  @fn HostBridgeDestructor
  @brief HostBridge Destructor routine

  This function will delete all the RootBridges underneath this HostBridge
  and itself

  @param[in] void

  @retval EFI_SUCCESS or appropriate EFI_ERROR
**/
EFI_STATUS
HostBridgeDestructor (VOID)
{
  LIST_ENTRY* HbList;
  LIST_ENTRY* RbList;
  PCI_HOST_BRIDGE_INSTANCE* HostBridge;
  PCI_ROOT_BRIDGE_INSTANCE* RootBridge;
  EFI_STATUS Status = EFI_SUCCESS;

  HbList = gPciHostBridgeInstanceList.ForwardLink;

  while (HbList != &gPciHostBridgeInstanceList)
  {
    HostBridge = HOST_BRIDGE_INSTANCE_FROM_LIST_ENTRY (HbList);

    RbList = HostBridge->RbHead.ForwardLink;

    while (RbList != &HostBridge->RbHead)
    {
      RootBridge = ROOT_BRIDGE_INSTANCE_FROM_LIST_ENTRY(RbList);
      RbList = RbList->ForwardLink;
      Status = PciRbDestructor (RootBridge);
      ASSERT_EFI_ERROR(Status);
    }

    Status = gBS->UninstallMultipleProtocolInterfaces (HostBridge->Handle,
                          &gEfiPciHostBridgeResourceAllocationProtocolGuid,
                          &HostBridge->ResAlloc, NULL);
    ASSERT_EFI_ERROR (Status);

    HbList = HbList->ForwardLink;
    FreePool (HostBridge);
  }

  return Status;
}

/**
  Event notification that is fired when IOMMU protocol is installed.

  @param  Event                 The Event that is being processed.
  @param  Context               Event Context.

**/
VOID
EFIAPI
HalIoMmuProtocolCallback (
  IN  EFI_EVENT       Event,
  IN  VOID            *Context
  )
{
  EFI_STATUS   Status;

  Status = gBS->LocateProtocol (&gEdkiiIoMmuProtocolGuid, NULL, (VOID **)&gHalIoMmuProtocol);

  if (!EFI_ERROR(Status))
    gBS->CloseEvent (gHalIoMmuEvent);
}

/**
  @fn PciHostBridgeEntryPoint
  @brief Entry point of this driver

  This function will initialize all the available PCIe RootPorts
  and call HostBridge constructor to create required HostBridge
  and RootBridge Instance

  @param ImageHandle     Handle of driver image
  @param SystemTable     Point to EFI_SYSTEM_TABLE

  @retval EFI_SUCCESS or appropriate EFI_ERROR
**/
EFI_STATUS
EFIAPI
PciHostBridgeEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                  Status = EFI_SUCCESS;
  UINT32                      HostBridgeIndex;
  UINT32                      MaxHostBridges;

  PCI_TRACE ("PciHostBridgeEntryPoint()");

//  DEBUG((EFI_D_WARN, "Host Bridge Entry %ld\r\n", GetTimerCountms ()));

  /* Initialize global list head for Host Bridge Instances */
  InitializeListHead (&gPciHostBridgeInstanceList);

  /* Initialize all PCIe root ports */
  Status = PcieConfigLibEnableRootPorts();
  if EFI_ERROR (Status)
  {
    //PCIe_Deinitialize(); TODO: implement routine in Lib to disable devices
    DEBUG((EFI_D_WARN, "PciHostBridgeEntryPoint: Init hardware failed, Status = (0x%p)\r\n", Status));
    return Status;
  }

  MaxHostBridges = PcieConfigLibGetNumberOfHostBridges();

  for (HostBridgeIndex = 0; HostBridgeIndex < MaxHostBridges; HostBridgeIndex++)
  {
    // Creation of the PCI Host Bridge Instance
    Status = HostBridgeConstructor (ImageHandle, HostBridgeIndex);

    if (EFI_ERROR (Status))
    {
      PCI_TRACE ("PciHostBridgeEntryPoint(): ERROR: Fail to construct PCI Host Bridge.");
      return Status;
    }
  }

  if (!EFI_ERROR (Status))
    gHalIoMmuEvent = EfiCreateProtocolNotifyEvent (&gEdkiiIoMmuProtocolGuid,
                                                   TPL_CALLBACK, HalIoMmuProtocolCallback,
                                                   NULL, &gHalIoMmuRegistration);

  DEBUG((EFI_D_WARN, "Host Bridge done %ld\r\n", GetTimerCountms ()));
  return Status;
}

/**
  @fn PciHostBridgeUnload
  @brief Unload routine of this driver

  This function will call destructor for all HostBridges and associated
  RootBridges

  @param ImageHandle     Handle of driver image
  @param SystemTable     Point to EFI_SYSTEM_TABLE

  @retval EFI_SUCCESS or appropriate EFI_ERROR
**/
EFI_STATUS
EFIAPI
PciHostBridgeUnload (IN EFI_HANDLE  ImageHandle)
{
  EFI_STATUS Status;

  Status = HostBridgeDestructor();

  ASSERT_EFI_ERROR (Status);

  return Status;
}
