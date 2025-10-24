/** @file Usb4InitDxe.c

The driver supports the on demand USB initialization.

Copyright (c) 2016 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
EDIT HISTORY

when       who      what, where, why
--------   ---      ----------------------------------------------------------
04/12/16   ck       Init version
=============================================================================*/
#include "Usb4InitDxe.h"
#include <Library/MemoryAllocationLib.h>

#if 0
struct _USB4_PROTOCOL {
  BOOLEAN PcieCbRegd;
  BOOLEAN DpCbRegd;
  BOOLEAN Usb3CbRegd;
  EFI_USB4_PROTOCOL_REGISTER Register;
	EFI_USB4_QUERY_PATH_ENABLE QueryPathEnable;
};
#endif


/*===========================================================================
  FUNCTION DECLARATIONS
===========================================================================*/

/**
   Register as a client with Usb4Protocol
 
   @param[in]      This         - Instance of USB4_PROTOCOL
 
   @retval True = Successful, False = Failure
 
 **/
BOOLEAN
EFIAPI 
Usb4ProtocolRegister (
  IN USB4_PROTOCOL*  This,
  IN USB4_CLIENT_TYPE ClientType, 
  IN USB4_PROTOCOL_CB cb_ptr
)
{
	return TRUE;
};

/**
   Register as a client with Usb4Protocol
 
   @param[in]      This         - Instance of USB4_PROTOCOL
   @param[in]      ClientType   - PCIE, DP or USB3 Client
   @retval True = Path in enabled state, False = Path is in disabled state.
 
 **/
BOOLEAN
EFIAPI
Usb4ProtocolQueryPathEnable (
  IN USB4_PROTOCOL*  This,
  IN USB4_CLIENT_TYPE ClientType,
  IN USB4_CORE_NUM_TYPE CoreNum
)
{
	return TRUE;
}





/**
* @brief Create and initialize a DEV_CTXT instance
*
* @retval New instance on success
* @retval NULL on failure
*/
STATIC
USB4_PROTOCOL_CTXT *
CreateUsb4Protocol(
  VOID
  )
{
  EFI_STATUS             Status = EFI_SUCCESS;
  USB4_PROTOCOL_CTXT     *Usb4ProtocolCtxt = NULL;

  FNC_ENTER_MSG();

  // Allocate the software device structure
  Usb4ProtocolCtxt = (USB4_PROTOCOL_CTXT *)AllocateZeroPool(sizeof(USB4_PROTOCOL_CTXT));
  if (!Usb4ProtocolCtxt) {
    Status = EFI_OUT_OF_RESOURCES;
    DBG(EFI_D_ERROR, "memory allocation failed for USB FN");
    goto ON_EXIT;
  }

  Usb4ProtocolCtxt->Signature = USB4_PROTOCOL_INIT_SIGNATURE;

  Usb4ProtocolCtxt->Usb4Protocol.Revision        = USB4_PROTOCOL_REVISION;
  Usb4ProtocolCtxt->Usb4Protocol.Register        = Usb4ProtocolRegister;
  Usb4ProtocolCtxt->Usb4Protocol.QueryPathEnable = Usb4ProtocolQueryPathEnable;
  //Usb4ProtocolCtxt->Usb4Protocol.PcieCbRegd      = FALSE;
  //Usb4ProtocolCtxt->Usb4Protocol.DpCbRegd        = FALSE;
	//Usb4ProtocolCtxt->Usb4Protocol.Usb3CbRegd      = FALSE;

  Status = gBS->LocateProtocol(
    &gQcomUsbConfigProtocolGuid,
    NULL,
    (VOID **)&Usb4ProtocolCtxt->Usb4Protocol);
  ERR_CHK("Failed to get gQcomUsbConfigProtocolGuid");


ON_EXIT:
  if (EFI_ERROR(Status) && Usb4ProtocolCtxt) {
    FreePool(Usb4ProtocolCtxt);
    Usb4ProtocolCtxt = NULL;
  }

  FNC_LEAVE_MSG();
  return Usb4ProtocolCtxt;
}

/**
Entry point for EFI drivers.

@param  ImageHandle       EFI_HANDLE.
@param  SystemTable       EFI_SYSTEM_TABLE.

@return EFI_SUCCESS       Success.
        EFI_DEVICE_ERROR  Fail.

**/
EFI_STATUS
EFIAPI
Usb4InitDriverEntryPoint(
  IN EFI_HANDLE           ImageHandle
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  USB4_PROTOCOL_CTXT   *Usb4ProtocolCtxt = NULL;

  FNC_ENTER_MSG();

  Usb4ProtocolCtxt = CreateUsb4Protocol();
  if (!Usb4ProtocolCtxt) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_EXIT;
  }

// Install UsbfnIo protocol.
Status = gBS->InstallMultipleProtocolInterfaces(
  &ImageHandle,
  &gQcomUsb4ProtocolGuid, &Usb4ProtocolCtxt->Usb4Protocol, NULL);
ERR_CHK("unable to install USB Init Protocol");
if (Status != EFI_SUCCESS) {
  DEBUG ((EFI_D_ERROR, "Usb4InitDriverEntryPoint: Failed to register for Usb4 protocol, Status = %d\n", Status));
  // return EFI_ABORTED;
}


ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}






