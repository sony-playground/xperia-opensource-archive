/** @file UsbfnLoopback.c

  Tests for UEFI USB FUNCTION PROTOCOL

**/
//============================================================================
/**
  Copyright (c) 2011-2021 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 12/20/21   bxr     Modify python decode error to generate uefi build report
                    with build option "-y, -Y"
 04/08/21   pohanw  Move Find partition & Mount/unmount to USBMSD 
 02/20/19   kameya  Add support for speed API for SLT loopback.
 10/11/18   kameya  Support USB SLT loopback feature.
 02/01/17   pm      Port from Boot.xf.1.4
 01/22/16   ck      Support on demand USBFn configuration
 02/05/15   al      Changing TPL_CALLBACK to TPL_CALLBACK
 12/18/14   amitg   Fix KW Errors
 12/08/14   ck      Fix incorrect LunNum after unmount
 10/14/14   ck      Add state machine and remove global vars
 08/14/14   martinl Support for USB mass storage app 
 11/15/11   cching  initial check in for USB MSD support in peripheral

=============================================================================*/

#include <Uefi.h>
#include <Library/MemoryAllocationLib.h>      // Allocate* functions
#include <Library/UefiBootServicesTableLib.h> // gBS
#include <Library/QcomLib.h>   //Mount/Unmount

#include "UsbMsd.h"        // Header
#include "UsbMsdDesc.h"    // device info
#include "UsbMsdSm.h"      // global State machine
#include "UsbMsdUtility.h" // *_CHK
#include "UsbError.h"      //  USB ASSERTs
#include "UsbMsdXfer.h"    // XFER_TYPE, Issue|Abort Xfer

// ExitBootSerice GUID
extern EFI_GUID gEfiEventExitBootServicesGuid;


  
#include <Protocol/EFIUsbMsdPeripheral.h>
#include <Protocol/BlockIo.h>
#include <Protocol/EFIEraseBlock.h>
#include <Protocol/EFIUsbConfig.h>
#include <Library/QcomUtilsLib.h>
#include <Library/BaseMemoryLib.h>

//ENABLE_RPMB_READ
#include <Library/RpmbLib.h>
#include <Protocol/EFIRpmb.h>



EFI_STATUS
EFIAPI
UsbMsdUnmountHandle (
  //IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This,
  IN    EFI_HANDLE               *Handle
  );
EFI_STATUS
EFIAPI
UsbMsdMountHandle (
  //IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This,
  IN    CHAR16    *PartitionLabel
  );
EFI_STATUS
EFIAPI
UsbMsdFindPartitions (
  OUT   PartitionCtx**    PartitionPtr,
  OUT   UINT16*           NumPartitionPtr
  );

/*
* @brief Implement EFI_USB_MSD_GET_DEVICE_SPEED
* @see EFIUsbMsdPeriperahl.h
*/
EFI_STATUS
EFIAPI
UsbMsdGetDeviceSpeed(
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This,
  OUT EFI_USB_BUS_SPEED                 *BusSpeed);


/*
* @brief Implement EFI_USB_MSD_START_DEVICE
* @see EFIUsbMsdPeriperahl.h
*/
EFI_STATUS
EFIAPI
UsbMsdStartDevice(
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This);


/*
* @brief Implement EFI_USB_MSD_STOP_DEVICE
* @see EFIUsbMsdPeriperahl.h
*/
EFI_STATUS
EFIAPI
UsbMsdStopDevice(
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This);

/* 
* @brief Implement EFI_USB_MSD_ASSIGN_BLKIO_HANDLE
* @see EFIUsbMsdPeriperahl.h
*/
EFI_STATUS
EFIAPI
UsbMsdAssignBlkIoHandle(
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This,
  IN  EFI_BLOCK_IO_PROTOCOL             *BlkIoHandle,
  IN  UINT32                            LunNum
);


/*
* @brief Implement EFI_USB_MSD_QUERY_MAX_LUN
* @see EFIUsbMsdPeriperahl.h
*/
EFI_STATUS
EFIAPI
UsbMsdQueryMaxLun(
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This,
  OUT UINT8                             *NumLunSupported
);


/*
* @brief Implement EFI_USB_MSD_EVENT_HANDLER
* @see EFIUsbMsdPeriperahl.h
*/
EFI_STATUS
EFIAPI
UsbMsdEventHandler(
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This
);


/**
* @brief Event notification callback for ExitBootService
*
* @param[in]  Event      Event whose notification function is being invoked
* @param[in]  Context    Pointer to the notification function’s context, which 
*                        is implementation-dependent
*/
VOID
EFIAPI
UsbMsdExitBootService(
  IN EFI_EVENT  Event,
  IN VOID      *Context
);


//
// @brief Create an instance of USBMSD_DEV
//
STATIC
USBMSD_DEV
*CreateUsbMsdInstance (
  VOID
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  USBMSD_DEV *UsbMsd = NULL;

  FNC_ENTER_MSG ();

  UsbMsd = (USBMSD_DEV *) AllocateZeroPool(sizeof(USBMSD_DEV));
  MCR_CHK(UsbMsd);

  // USB MSD Peripheral protocol.
  UsbMsd->Signature                        = USBMSD_DEV_SIGNATURE;
  UsbMsd->UsbMsdProtocol.Revision            = EFI_USB_MSD_PERIPHERAL_PROTOCOL_REVISION_V3;
  UsbMsd->UsbMsdProtocol.AssignBlkIoHandle = UsbMsdAssignBlkIoHandle;
  UsbMsd->UsbMsdProtocol.QueryMaxLun       = UsbMsdQueryMaxLun;
  UsbMsd->UsbMsdProtocol.EventHandler      = UsbMsdEventHandler;
  UsbMsd->UsbMsdProtocol.StartDevice       = UsbMsdStartDevice;
  UsbMsd->UsbMsdProtocol.StopDevice        = UsbMsdStopDevice;
  UsbMsd->UsbMsdProtocol.GetDeviceSpeed    = UsbMsdGetDeviceSpeed;
  UsbMsd->UsbMsdProtocol.UnmountFatPartition = UsbMsdUnmountHandle;
  UsbMsd->UsbMsdProtocol.MountFatPartition   = UsbMsdMountHandle;
  UsbMsd->UsbMsdProtocol.FindPartitions      = UsbMsdFindPartitions;

  // Init the LUN mapping
  gBS->SetMem(UsbMsd->UsbMsdMedia.BlkIoLunMap, USB_MSD_MAX_SUPPORTED_LUN * sizeof(USBMSD_LUN_ASSOCIATION), 0);

  // Register for boot services exit event.
  Status = gBS->CreateEventEx(
    EVT_NOTIFY_SIGNAL,
    TPL_CALLBACK,
    UsbMsdExitBootService,
    UsbMsd,
    &gEfiEventExitBootServicesGuid,
    &UsbMsd->ExitBootServiceEvent);
  WRN_CHK("unable to create ExitBootServiceEvent with status code", Status);

  UsbMsd->DeviceStarted = FALSE;

  Status = EFI_SUCCESS;

ON_EXIT:

  if (EFI_ERROR(Status)){
    if (UsbMsd){    
      FreePool(UsbMsd);
      UsbMsd = NULL;
    }
  }

  FNC_LEAVE_MSG ();
  return UsbMsd;
}

/**
* @brief The entry point of the module
* @param[in]  ImageHandle         The handle of the image the EfiUsbMsdPeripheralProtocol
                                  will be installed on.
* @param[in]  EFI_SYSTEM_TABLE    EFI System Table 
*
* @retval EFI_SUCCESS Operation succeeded.
* @retval Others      Operation failed.
**/
EFI_STATUS
EFIAPI
UsbMsdDriverEntryPoint (
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{

  EFI_STATUS Status = EFI_SUCCESS;

  USBMSD_DEV *UsbMsd = NULL;

  FNC_ENTER_MSG();

  ARG_CHK(ImageHandle);

  UsbMsd = CreateUsbMsdInstance();
  MCR_CHK(UsbMsd);  

  // Install USB_MSD_PERIPHERAL_PROTOCOL protocol.
  Status = gBS->InstallMultipleProtocolInterfaces(
    &ImageHandle,
    &gEfiUsbMsdPeripheralProtocolGuid, 
    &UsbMsd->UsbMsdProtocol, 
    NULL);
  ERR_CHK("unable to install USB MSD Peripheral protocols %r", Status);

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}

/**
 @brief This is a driver exit point function that is called when
 gBS->ExitBootServices() is called.

 @param  Event                   Pointer to this event
 @param  Context                 Event handler private data

 **/
VOID
EFIAPI
UsbMsdExitBootService (
  EFI_EVENT  Event,
  VOID       *Context
  )
{
  USBMSD_DEV *UsbMsd  = NULL;
  EFI_STATUS  Status  = EFI_SUCCESS;

  FNC_ENTER_MSG ();

  ARG_CHK(Context);

  UsbMsd = (USBMSD_DEV *)Context; 

  if(UsbMsd){   
    FreePool(UsbMsd);
    UsbMsd = NULL;
  }

ON_EXIT:
  FNC_LEAVE_MSG ();

}


/* see function description above */
EFI_STATUS
RemoveBlkIoLunAssociation(
  USBMSD_DEV* CONST UsbMsd,
  CONST UINT32      LunNum
  )
{

  EFI_STATUS Status = EFI_SUCCESS;

  FNC_ENTER_MSG ();

  gBS->SetMem(&UsbMsd->UsbMsdMedia.BlkIoLunMap[LunNum], sizeof(USBMSD_LUN_ASSOCIATION), 0);
  UsbMsd->UsbMsdMedia.NumLuns -= 1;

  DBG(EFI_D_INFO, "Free LUN %d, BlkIo %p, Num of active LUN %d",
    LunNum,
    UsbMsd->UsbMsdMedia.BlkIoLunMap[LunNum].BlkIoHandle,
    UsbMsd->UsbMsdMedia.NumLuns
    );

  FNC_LEAVE_MSG ();
  return Status;
}


/**
* @brief Check whether the association between the LUN and the BlkIoHandle is 
*       valid
*
* @param  UsbMsd                  The USBMSD_DEV instance
* @param  BlkIoHandle             The BlockIo handle to be associated with the Lun
*                                 specified by the LunNum.
* @param  LunNum                  The number of the LUN to be associated with BlkIoHandle
*
* @retval EFI_SUCCESS             The association between BlkIoHandle and LunNum is valid           
* @retval EFI_NOT_READY           The requested LUN is already associated with an BlkIo Handle return 
* @retval EFI_UNSUPPORTED         The BlkIoHandle is already associated with a LUN
**/
EFI_STATUS
CheckBlkIoLunAssociation(
  IN USBMSD_DEV*  CONST                 UsbMsd,
  IN EFI_BLOCK_IO_PROTOCOL CONST* CONST BlkIoHandle,
  IN CONST UINT32                       LunNum
  )
{

  UINTN      Index  = 0;
  EFI_STATUS Status = EFI_SUCCESS;

  FNC_ENTER_MSG ();

  ARG_CHK(UsbMsd && BlkIoHandle);

  for(Index = 0; Index < USB_MSD_MAX_SUPPORTED_LUN; Index++) {

    if(UsbMsd->UsbMsdMedia.BlkIoLunMap[Index].BlkIoHandle == BlkIoHandle){
      Status = EFI_UNSUPPORTED;
      ERR_CHK(
        "The BlkIoHanlde 0x%x is currently associated with LUN %d",
        BlkIoHandle,
        UsbMsd->UsbMsdMedia.BlkIoLunMap[Index].Lun.Index
      );
    }

    if(LunNum == UsbMsd->UsbMsdMedia.BlkIoLunMap[Index].Lun.Index &&
       UsbMsd->UsbMsdMedia.BlkIoLunMap[Index].BlkIoHandle &&
       BlkIoHandle != UsbMsd->UsbMsdMedia.BlkIoLunMap[Index].BlkIoHandle){
      Status = EFI_NOT_READY;
      ERR_CHK("The LUN %d is currently associated with BlkIoHanlde 0x%x",
        LunNum,
        UsbMsd->UsbMsdMedia.BlkIoLunMap[Index].BlkIoHandle
      );
    }
  }

  ON_EXIT:

  FNC_LEAVE_MSG ();
  return Status;
}


/* see function description above */
EFI_STATUS
EFIAPI
UsbMsdQueryMaxLun (
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This,
  OUT UINT8                             *NumLunSupported
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  FNC_ENTER_MSG ();
  ARG_CHK(This && NumLunSupported);
  *NumLunSupported = USB_MSD_MAX_SUPPORTED_LUN;
  FNC_LEAVE_MSG();
ON_EXIT:
  return Status;
}

/* see function description above */
EFI_STATUS
EFIAPI
UsbMsdAssignBlkIoHandle (
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This,
  IN  EFI_BLOCK_IO_PROTOCOL             *BlkIoHandle,
  IN  UINT32                             LunNum
  )
{
  USBMSD_DEV *UsbMsd  = NULL;
  EFI_STATUS  Status  = EFI_SUCCESS;

  FNC_ENTER_MSG ();

  // When the client is going to unmount a LUN, BlkIoHandle is nULL. 
  // Thus, only This param cannot be NULL.
  ARG_CHK(This);

  UsbMsd = USBMSD_FROM_THIS(This);

  //
  // The device can support only up to MAX_SUPPORTED_LUN - 1
  //
  if(USB_MSD_MAX_SUPPORTED_LUN <= LunNum) {
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  //
  // Remove association
  //
  if(!BlkIoHandle) {
    Status = RemoveBlkIoLunAssociation(UsbMsd, LunNum);
    goto ON_EXIT;
  }

  //
  // Check whether the association can be supported
  //
  Status = CheckBlkIoLunAssociation(UsbMsd, BlkIoHandle, LunNum);
  if(EFI_ERROR(Status)) {
    goto ON_EXIT;
  }

  //
  // Now associate the BlkIo to LUN
  //
  UsbMsd->UsbMsdMedia.BlkIoLunMap[LunNum].BlkIoHandle                 = BlkIoHandle;
  UsbMsd->UsbMsdMedia.BlkIoLunMap[LunNum].Lun.Index                   = LunNum;
  UsbMsd->UsbMsdMedia.BlkIoLunMap[LunNum].Lun.Property.Enabled        = TRUE;
  UsbMsd->UsbMsdMedia.BlkIoLunMap[LunNum].Lun.Property.Removable      = BlkIoHandle->Media->RemovableMedia;
  UsbMsd->UsbMsdMedia.BlkIoLunMap[LunNum].Lun.BlockSize               = BlkIoHandle->Media->BlockSize;
  UsbMsd->UsbMsdMedia.BlkIoLunMap[LunNum].Lun.NumBlocks               = BlkIoHandle->Media->LastBlock+1;
  UsbMsd->UsbMsdMedia.BlkIoLunMap[LunNum].Lun.Property.ReadOnly       = BlkIoHandle->Media->ReadOnly;
  UsbMsd->UsbMsdMedia.BlkIoLunMap[LunNum].Lun.Property.NeedAttention  = FALSE;
  UsbMsd->UsbMsdMedia.NumLuns += 1;

  DBG(EFI_D_INFO, "Add LUN %d, BlkIo %p, Num of active LUN %d",
    LunNum,
    UsbMsd->UsbMsdMedia.BlkIoLunMap[LunNum].BlkIoHandle,
    UsbMsd->UsbMsdMedia.NumLuns
    );

  ON_EXIT:

  FNC_LEAVE_MSG();
  return Status;
}


/* see function description above */
EFI_STATUS
EFIAPI
UsbMsdEventHandler(
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This)
{
  EFI_STATUS                 Status      = EFI_SUCCESS;
  EFI_USBFN_IO_PROTOCOL     *UsbfnIo     = NULL;
  EFI_USBFN_MESSAGE          Msg         = EfiUsbMsgNone;
  EFI_USBFN_MESSAGE_PAYLOAD  Payload;
  UINTN                      PayloadSize = sizeof (Payload);
  USBMSD_DEV                *UsbMsd      = NULL;

  ARG_CHK(This);

  UsbMsd  = USBMSD_FROM_THIS(This);
  ARG_CHK(UsbMsd);
  UsbfnIo = UsbMsd->UsbfnIoProtocol;  

  // Skip polling UsbfnIo events when device is stopped by UsbMsdDxe.
  if (!UsbMsd->DeviceStarted) {
    goto ON_EXIT;
  }

  if (!UsbfnIo) {
    Status = EFI_PROTOCOL_ERROR;
    goto ON_EXIT;
  }

  // Always check for new transfers or poll the controller. ------------------
  Status = UsbfnIo->EventHandler(
    UsbfnIo,
    &Msg,
    &PayloadSize,
    &Payload
    );

  // Pass meaningful events to state machine
  if (Msg != EfiUsbMsgNone) {
    Status = DevSmProcessEvent(&UsbMsd->StateMachine, Msg, PayloadSize, &Payload);
    if (EFI_ERROR(Status)) {
      DBG(EFI_D_ERROR, "State machine failed to process event: %r", Status);      
    }

    // abort all of the xfers when disconnected.
    if (Msg == EfiUsbMsgBusEventDetach) {
      Status = EFI_NOT_READY;
      
      // move xfer to free state
      if (NULL != UsbMsd->StateMachine.CtrlXfer.Buffer && UsbMsd->UsbfnIoProtocol) {
        AbortXfer(UsbMsd->UsbfnIoProtocol, &UsbMsd->StateMachine.CtrlXfer);
      }

      if (NULL != UsbMsd->StateMachine.BulkRxXfer.Buffer && UsbMsd->UsbfnIoProtocol) {
        AbortXfer(UsbMsd->UsbfnIoProtocol, &UsbMsd->StateMachine.BulkRxXfer);
      }

      if (NULL != UsbMsd->StateMachine.BulkTxXfer.Buffer && UsbMsd->UsbfnIoProtocol) {
        AbortXfer(UsbMsd->UsbfnIoProtocol, &UsbMsd->StateMachine.BulkTxXfer);
      }

      if (NULL != UsbMsd->StateMachine.CBW.Buffer && UsbMsd->UsbfnIoProtocol) {
        AbortXfer(UsbMsd->UsbfnIoProtocol, &UsbMsd->StateMachine.CBW);
      }

      if (NULL != UsbMsd->StateMachine.CSW.Buffer && UsbMsd->UsbfnIoProtocol) {
        AbortXfer(UsbMsd->UsbfnIoProtocol, &UsbMsd->StateMachine.CSW);
      }
    }
  } 

ON_EXIT:
  return Status;
}


/* see function description above */
EFI_STATUS
EFIAPI
UsbMsdStartDevice(
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This)
{
  EFI_STATUS      Status = EFI_SUCCESS;
  USBMSD_DEV     *UsbMsd = NULL;

  FNC_ENTER_MSG();

  ARG_CHK(This);

  UsbMsd  = USBMSD_FROM_THIS(This);
  ARG_CHK(UsbMsd);

  if (UsbMsd && UsbMsd->DeviceStarted) {
    Status = EFI_NOT_READY;
    ERR_CHK("Usb MSD device is already started");
  }

  // Locate the USB FN IO protocol.
  Status = gBS->LocateProtocol(
    &gEfiUsbfnIoProtocolGuid,
    NULL,
    (VOID **)&UsbMsd->UsbfnIoProtocol
    );
  ERR_CHK("Failed to located USB FN IO protocol: %r", Status);

  // Init State Machine
  Status = DevSmInitialize(&UsbMsd->StateMachine, UsbMsd->UsbfnIoProtocol);
  ERR_CHK("Usb MSD state machine initialization failed %r", Status);

  // Starts USB enumeration
  Status = UsbMsd->UsbfnIoProtocol->ConfigureEnableEndpointsEx(UsbMsd->UsbfnIoProtocol, 
    (EFI_USB_DEVICE_INFO *) &UsbMsdDeviceInfo, 
    (EFI_USB_SUPERSPEED_DEVICE_INFO *) &UsbMsdSSDeviceInfo);
  ERR_CHK("Failed to configure and enable endpoints %r", Status); 

  UsbMsd->DeviceStarted = TRUE;
  
ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/* see function description above */
EFI_STATUS
EFIAPI
UsbMsdStopDevice(
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This)
{
  EFI_STATUS      Status = EFI_SUCCESS;
  USBMSD_DEV     *UsbMsd = NULL;
  EFI_USBFN_IO_PROTOCOL  *UsbfnIo = NULL;

  FNC_ENTER_MSG();

  ARG_CHK(This);

  UsbMsd  = USBMSD_FROM_THIS(This);
  ARG_CHK(UsbMsd);
  UsbfnIo = UsbMsd->UsbfnIoProtocol;  

  if (UsbMsd && !UsbMsd->DeviceStarted) {
    Status = EFI_NOT_READY;
    ERR_CHK("Usb MSD device is already stopped");
  }

  UsbMsd->DeviceStarted = FALSE;
  
  if (!UsbfnIo) {
    Status = EFI_PROTOCOL_ERROR;
    goto ON_EXIT;
  }

  // Stop the controller
  Status = UsbfnIo->StopController(UsbfnIo);
  ERR_CHK("Failed to stop controller %r", Status);

  // clear up state machine
  DevSmCleanup(&UsbMsd->StateMachine);

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;  
}


/* see function description above */
EFI_STATUS
EFIAPI
UsbMsdGetDeviceSpeed(
  IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This,
  OUT EFI_USB_BUS_SPEED                 *BusSpeed)
{    
  EFI_STATUS        Status   = EFI_SUCCESS;
  USBMSD_DEV        *UsbMsd  = NULL;

  FNC_ENTER_MSG();

  ARG_CHK(BusSpeed);
  ARG_CHK(This);
  UsbMsd  = USBMSD_FROM_THIS(This);
  ARG_CHK(UsbMsd);

  *BusSpeed = UsbBusSpeedUnknown;

  if (!UsbMsd->DeviceStarted) {
    ERR_CHK("USB MSD device enumeration was not started");
  }

  if ((UsbMsd->StateMachine.CurrentState >= DEV_STATE_CONFIGURED) && (UsbMsd->StateMachine.CurrentState < DEV_NUM_STATES)) {
    *BusSpeed = UsbMsd->StateMachine.BusSpeed;
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


EFI_STATUS
EFIAPI
UsbMsdUnmountHandle (
  //IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This,
  IN    EFI_HANDLE               *Handle
  )
{
    EFI_STATUS        Status = EFI_SUCCESS;
    DBG(EFI_D_ERROR, "UsbMsdUnmountHandle 0x%x", Handle);

    Status = UnmountFatPartition(Handle);
    if (Status != EFI_SUCCESS)
    {
      DBG(EFI_D_ERROR, "UsbMsdUnmountHandle failed %r", Status);
    }
    return Status;
}

EFI_STATUS
EFIAPI
UsbMsdMountHandle (
  //IN  EFI_USB_MSD_PERIPHERAL_PROTOCOL   *This,
  IN    CHAR16    *PartitionLabel
  )
{
  EFI_STATUS        Status   = EFI_SUCCESS; 
  DBG(EFI_D_ERROR, "UsbMsdMountHandle 0x%x", PartitionLabel);
  
  Status = MountFatPartition(PartitionLabel);

  if (Status != EFI_SUCCESS)
  {
    DBG(EFI_D_ERROR, "UsbMsdMountHandle failed %r", Status);
  }

  return Status;
}

#ifndef USB_PARTITION_FLAG

/* GUIDS */
extern EFI_GUID gEfiEmmcUserPartitionGuid;
extern EFI_GUID gEfiEmmcBootPartition1Guid; 
extern EFI_GUID gEfiEmmcBootPartition2Guid; 
extern EFI_GUID gEfiEmmcGppPartition1Guid; 
//extern EFI_GUID gEfiPartitionRecordGuid;
extern EFI_GUID gEfiSdRemovableGuid;
//extern EFI_GUID gEfiSdccRpmbProtocolGuid;
extern EFI_GUID gEfiUfsLU0Guid;
extern EFI_GUID gEfiUfsLU1Guid;
extern EFI_GUID gEfiUfsLU2Guid;
extern EFI_GUID gEfiUfsLU3Guid;
extern EFI_GUID gEfiUfsLU4Guid;
extern EFI_GUID gEfiUfsLU5Guid;
extern EFI_GUID gEfiUfsLU6Guid;
extern EFI_GUID gEfiUfsLU7Guid;
//extern EFI_GUID gEfiUfsRPMBGuid;
extern EFI_GUID gEfiNvme0Guid; 
extern EFI_GUID gInitUsbControllerGuid;
extern EFI_GUID gInitUsbStopControllerGuid;
extern EFI_GUID gInitUsbLoopbackControllerGuid;

extern EFI_GUID gEfiEventToggleUsbModeGuid;

//Partition Type
//extern EFI_GUID gEfiPartTypeSystemPartGuid;
//extern EFI_GUID gEfiPlatPartitionTypeGuid;
//extern EFI_GUID gEfiACPITableLoadGuid;
//extern EFI_GUID gEfiAblFvNameGuid;



#define MAX_NUM_PARTITIONS      1024 
#define PARTITION_NAME_LENGTH   32 
#define MAX_ROOT_PARTITIONS     16
#define NUM_LUNS_SUPPORTED      2
#define PAGE_SCROLL_SIZE        3
#define WIDECHAR_TO_CHAR_MASK   0x00ff
#define MAX_NUM_HANDLES         128
#define UEFI_VAR_MOUNTS_NAME    L"LUNMountsMSD"
#define RPMB_DISPLAY_NAME       "RPMB"
#define COL_LEN                 21

/* Printed to show drive is selected */
#define SELECTION_INVALID       0xffff
#define KILOBYTE                1024
#define MEGABYTE                1024*1024
#define RPMB_BUFFER_IN_BYTES    5*MEGABYTE
#define RPMB_BLOCK_SIZE         512
#define QUEST_MAX_PARTITONS 2


/* Globals */
STATIC HandleInfo    RootHandleInfoList[16];
STATIC HandleInfo    HandleInfoList[MAX_NUM_HANDLES];                   
STATIC PartitionCtx* Partitions = NULL;
STATIC UINT16       NumPartitions;                                
STATIC UINTN      NumRootPartitions;

typedef struct _ROOT_PARTI {
   CONST CHAR8*  Name;
   EFI_GUID*     Guid;
}RootPartitionInfoType;

RootPartitionInfoType  RootPartitionInfo[] = 
{
  {"eMMC User",      &gEfiEmmcUserPartitionGuid},
  {"eMMC Boot1",     &gEfiEmmcBootPartition1Guid},
  {"eMMC Boot2",     &gEfiEmmcBootPartition2Guid},
  {"eMMC GPP",       &gEfiEmmcGppPartition1Guid},
  {"SDCard",         &gEfiSdRemovableGuid},
  {"UFS-LUN 0",      &gEfiUfsLU0Guid},
  {"UFS-LUN 1",      &gEfiUfsLU1Guid},
  {"UFS-LUN 2",      &gEfiUfsLU2Guid},
  {"UFS-LUN 3",      &gEfiUfsLU3Guid},
  {"UFS-LUN 4",      &gEfiUfsLU4Guid},
  {"UFS-LUN 5",      &gEfiUfsLU5Guid},
  {"UFS-LUN 6",      &gEfiUfsLU6Guid},
  {"UFS-LUN 7",      &gEfiUfsLU7Guid},
  {"NVME-0",         &gEfiNvme0Guid},
};

#define ENABLE_RPMB_READ()     1// (!boot_from_nvme())


#if ENABLE_RPMB_READ
STATIC EFI_SDCC_RPMB_PROTOCOL          *RpmbProtocol;
STATIC UINTN        RpmbSizeInBytes = 0;
extern EFI_STATUS
EFIAPI
RPMBReadData (
   UINT32                Lba, 
   UINT32                BlockCount, 
   UINT8                 *ReadBuffer
   );

EFI_STATUS
RpmbDummyFlushBlocks (IN EFI_BLOCK_IO_PROTOCOL  *This)
{
  return EFI_SUCCESS;
}

EFI_STATUS
RPMBDummyWriteBlocks (
   IN EFI_BLOCK_IO_PROTOCOL   *This,
   IN UINT32                  MediaId,
   IN EFI_LBA                 Lba,
   IN UINTN                   BufferSize,
   IN VOID                    *Buffer
   )
{ 
  /* RPMB is Read Only */
  return EFI_DEVICE_ERROR;
}

EFI_STATUS
RPMBDummyReset(
  IN  EFI_BLOCK_IO_PROTOCOL   *This,
  IN  BOOLEAN                 ExtendedVerification
  )
{  
   return EFI_SUCCESS;
}

EFI_STATUS
RPMBReadBlocks (
  IN EFI_BLOCK_IO_PROTOCOL   *This,
  IN UINT32                  MediaId,
  IN EFI_LBA                 Lba,
  IN UINTN                   BufferSize,
  OUT VOID                   *Buffer
  )
{
  UINT32 FirstByte;

  if (BufferSize % RPMB_BLOCK_SIZE != 0) {
    return EFI_BAD_BUFFER_SIZE;
  }

  FirstByte = Lba * RPMB_BLOCK_SIZE / sizeof(UINT32);
  if ((FirstByte*sizeof(UINT32)) > RpmbSizeInBytes) { 
    DBG(EFI_D_INFO, "invalid LBA");
    return EFI_INVALID_PARAMETER;
  }
  
  CopyMem(Buffer, &RpmbBuffer[FirstByte],  BufferSize);

  return EFI_SUCCESS;
}

/* Media Element for local RpmbBlkIo*/
STATIC EFI_BLOCK_IO_MEDIA RpmbMedia = 
{
  SIGNATURE_32('e', 'm', 'm', 'c'),            /* MediaId */
  FALSE,                                    /* RemovableMedia */
  TRUE,                                     /* MediaPresent */
  FALSE,                                    /* LogicalPartition */
  TRUE,                                     /* ReadOnly */
  FALSE,                                    /* WriteCaching */
  RPMB_BLOCK_SIZE,                          /* BlockSize */
  4,                                        /* IoAlign */
  sizeof(RpmbBuffer)/RPMB_BLOCK_SIZE - 1,   /* LastBlock, will be set again later */ 
  0,                                        /* LowestAlignedLba */ 
  8,                                        /* LogicalBlocksPerPhysicalBlock */
  0                                         /* OptimalTransferLengthGranularity */
};

/* Local Blkio Instance to Handle Reading Rpmb Partition */
STATIC EFI_BLOCK_IO_PROTOCOL RpmbBlkIo = {
  EFI_BLOCK_IO_PROTOCOL_REVISION2,          /* Revision    */
  &RpmbMedia,                               /* Media       */
  RPMBDummyReset,                           /* Reset       */
  RPMBReadBlocks,                           /* ReadBlocks  */
  RPMBDummyWriteBlocks,                     /* WriteBlocks */
  RpmbDummyFlushBlocks                      /* Flush       */
};

extern EFI_STATUS
EFIAPI
RPMBReadData (
   UINT32                Lba, 
   UINT32                BlockCount, 
   UINT8                 *ReadBuffer
   );

/*Reads and Stores the Rpmb in RAM*/
STATIC VOID  CacheRpmb (VOID)
{
  EFI_STATUS   Status = EFI_SUCCESS;
  UINT32       RpmbBlocks;

  Status = gBS->LocateProtocol(&gEfiSdccRpmbProtocolGuid, NULL,
                                (void**)&RpmbProtocol);
  if (EFI_ERROR(Status))
    DBG (EFI_D_INFO, "Couldnt Find Rpmbprotocol");

  RpmbSizeInBytes = RpmbProtocol->RPMBPartitionSizeInBytes;
  
  RpmbBuffer = AllocatePool(RpmbSizeInBytes);

  if (RpmbBuffer == NULL)
    DBG (EFI_D_INFO, "Failed to Allocate RPMB Buffer");
  
  RpmbBlocks = RpmbSizeInBytes/RPMB_BLOCK_SIZE;
  Status = RPMBReadData (0, RpmbBlocks, (UINT8*)  RpmbBuffer);
  if (EFI_ERROR(Status))
    DBG (EFI_D_INFO, "Failed to Read RPMB Data");
  RpmbMedia.LastBlock = RpmbBlocks - 1;
}
#endif

STATIC EFI_STATUS IncrementPartitionsIndex (VOID)
{
  EFI_STATUS   Status = EFI_SUCCESS;
  if((NumPartitions+1) >=  MAX_NUM_PARTITIONS )
  {
    //DBG(EFI_D_WARN,"\n\n WARNING: Partitions Buffer Full! No more entries accepted. \n");
    Status = EFI_BUFFER_TOO_SMALL;
  }
  else
  {
    NumPartitions++;
  }  
  return Status;
}
/* Copies a WideChar String to an Char String*/
STATIC VOID WideCharToAsciiStr (CHAR8 *Dest, CHAR16 *Src)
{
  UINT32 i;
  for (i = 0; i < PARTITION_NAME_LENGTH; i++)
  { 
    Dest[i] = Src[i] & WIDECHAR_TO_CHAR_MASK; 
    if (Src[i] == 0)
      break;
  }
}

/* Finds all partitions and populates Partitions array */
STATIC VOID FindPartitions()
{
  UINT32                Attribs = 0;
  UINT32                MaxHandles;
  UINT32                MaxRootHandles;
  EFI_STATUS            Status;
  PartiSelectFilter     HandleFilter;
  EFI_PARTITION_ENTRY*  PartEntry;
  UINT16                i, j;
  UINT16                Parent;
  EFI_ERASE_BLOCK_PROTOCOL *EraseBlock;

  HandleFilter.PartitionType  = 0; 
  HandleFilter.VolumeName     = 0;
  NumPartitions               = 0;
  MaxRootHandles                  = sizeof(RootHandleInfoList) / sizeof(*RootHandleInfoList);


  NumRootPartitions = sizeof(RootPartitionInfo)/sizeof(*RootPartitionInfo);
  ASSERT (NumRootPartitions < MAX_ROOT_PARTITIONS);

  /* Seach by GUID */
  Attribs |= BLK_IO_SEL_MATCH_ROOT_DEVICE; 
  
  /*Allocate space to store paritions being discovered */
  Partitions = AllocatePool(MAX_NUM_PARTITIONS * sizeof(PartitionCtx));

  ASSERT(Partitions != NULL);
  /* Fix for Klockwork */
  if(Partitions == NULL)
  {
    return;
  }
  DEBUG(( EFI_D_ERROR, "usbmsd FindPartition, %d\r\n", NumRootPartitions));

  for (i = 0; i < NumRootPartitions; ++i)
  { 
    /* Find Root Partitions First */
    Attribs |= BLK_IO_SEL_SELECT_ROOT_DEVICE_ONLY;
    HandleFilter.RootDeviceType = RootPartitionInfo[i].Guid;
    GetBlkIOHandles(Attribs, &HandleFilter, RootHandleInfoList, &MaxRootHandles);
    //DBG(EFI_D_WARN,"\n\n popo %d= %s \n",i, RootPartitionInfo[i].Name);

    /* copy name over */
    AsciiStrCpyS(Partitions[NumPartitions].Name, PARTITION_NAME_LENGTH, RootPartitionInfo[i].Name);
     
    if (MaxRootHandles == 0)
    {
      /* Root Partition not Found, still add to Partitions to be printed*/
      Partitions[NumPartitions].Found  = FALSE;
      Partitions[NumPartitions].Parent = NumPartitions;
      if(IncrementPartitionsIndex()!= EFI_SUCCESS)
      {
        break;
      }
      continue;
    }

    Status = gBS->HandleProtocol (
        RootHandleInfoList[0].Handle,
        &gEfiEraseBlockProtocolGuid,
        (VOID **) &EraseBlock);
    
    
    /* Root partition found, fill root tree node */
    Partitions[NumPartitions].Handle = RootHandleInfoList[0].Handle;
    Partitions[NumPartitions].BlkIo  = RootHandleInfoList[0].BlkIo;
    Partitions[NumPartitions].Found  = TRUE;
    Partitions[NumPartitions].Parent = NumPartitions;
    Partitions[NumPartitions].Erase  = EraseBlock;
    Parent = NumPartitions;

    // Increment NumPartitions via IncrementPartitionsIndex
    if(IncrementPartitionsIndex()!= EFI_SUCCESS)
    {
      break;
    }
    
    /* Remove Root-only attribute to find subpartitions */
    Attribs   &= ~BLK_IO_SEL_SELECT_ROOT_DEVICE_ONLY;
    HandleFilter.RootDeviceType = RootPartitionInfo[i].Guid;
    MaxHandles = sizeof(HandleInfoList) / sizeof(*HandleInfoList); 
    GetBlkIOHandles (Attribs, &HandleFilter, HandleInfoList, &MaxHandles);

    /* check if any subpartitions are found. 1 means only found root */
    if (MaxHandles == 1)
      continue;

    /* Find The Names of each subpartitions */
    for(j = 0; j < MaxHandles; j++)
    {
      Status = gBS->HandleProtocol(HandleInfoList[j].Handle, 
                                   &gEfiPartitionRecordGuid, 
                                   (VOID **) &PartEntry);
      if (EFI_ERROR (Status))
           continue;  /* Root Partition Found, Skip iteration */

      Status = gBS->HandleProtocol(HandleInfoList[j].Handle, 
                                   &gEfiEraseBlockProtocolGuid, 
                                   (VOID **) &EraseBlock);
      

      Partitions[NumPartitions].Handle = HandleInfoList[j].Handle;
      Partitions[NumPartitions].BlkIo  = HandleInfoList[j].BlkIo;
      Partitions[NumPartitions].Found  = TRUE;
      Partitions[NumPartitions].Parent = Parent;
      Partitions[NumPartitions].Erase  = EraseBlock;

      if (PartEntry->PartitionName[0] == 0) 
        continue;  /* Dont add Partitions that have Null names*/

      WideCharToAsciiStr(Partitions[NumPartitions].Name, PartEntry->PartitionName);
      if(IncrementPartitionsIndex()!= EFI_SUCCESS)
      {
        break;
      }
    }         
  }
  DEBUG(( EFI_D_ERROR, "partition FindPartition 0x%x %d\r\n", Partitions, NumPartitions));

  /* Adding in the RPMB Partition */
#if ENABLE_RPMB_READ
  CacheRpmb();

  Partitions[NumPartitions].BlkIo  = &RpmbBlkIo;
  Partitions[NumPartitions].Found  = TRUE;
  Partitions[NumPartitions].Parent = NumPartitions;
  AsciiStrCpyS(Partitions[NumPartitions].Name, PARTITION_NAME_LENGTH, RPMB_DISPLAY_NAME);
  IncrementPartitionsIndex();
#endif 
}

volatile uint32 gInitPartition = 0;
EFI_STATUS
EFIAPI
UsbMsdFindPartitions (
  OUT   PartitionCtx**    PartitionPtr,
  OUT   UINT16*           NumPartitionPtr
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  if (0 == gInitPartition)
  {
    /* Search and store all Partitions, fill Partitions[] */
    DEBUG((EFI_D_ERROR, "UsbMsdFindPartitions, init 0x%x %d\n\n", Partitions, NumPartitions));
    FindPartitions();
    //gInitPartition = 1;
    
  }
  DEBUG((EFI_D_ERROR, "UsbMsdFindPartitions, found return 0x%x %d\n", Partitions, NumPartitions));

  *PartitionPtr = Partitions;
  *NumPartitionPtr = NumPartitions;
  return Status;
}

#endif

