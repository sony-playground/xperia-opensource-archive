#include <Protocol/EFIUsb4Protocol.h>
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseLib.h>
#include "Usb4ClientUsb3.h"
#include <Guid/EventGroup.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIUsbConfig.h>
#include <Protocol/EFIUsbInitProtocol.h>

STATIC USB4_PROTOCOL *Usb4ClientProtocol = NULL;


BOOLEAN usb4_client_usb3_cb (USB4_EVT_TYPE This, USB4_CORE_NUM_TYPE CoreNum, USB4_EVT_DATA data)
{
	DEBUG ((EFI_D_ERROR, "usb4_client_usb3_cb: Cb trigger from core %d, data 0x%x \n", CoreNum, data));
	return TRUE;
}

EFI_STATUS
EFIAPI
Usb4ClientInit(VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;
  USB4_CORE_NUM_TYPE core_num;
  if (Usb4ClientProtocol == NULL)
  {
    Status = gBS->LocateProtocol(
			   &gQcomUsb4ProtocolGuid,
		           NULL,
		           (VOID**) &Usb4ClientProtocol);
  }
  if (EFI_ERROR(Status) || (NULL == Usb4ClientProtocol))
  {
    DEBUG ((EFI_D_ERROR, "Usb4ClientInit: Error Locating gQcomUsb4ProtocolGuid\n"));
    return Status;
  }
  for (core_num = USB4_CORE_0; core_num <= USB4_CORE_1; core_num++) 
  {
    if (TRUE == Usb4ClientProtocol->QueryPathEnable(Usb4ClientProtocol, USB4_CLIENT_USB3, core_num))
    {
      if (FALSE == Usb4ClientProtocol->Register(Usb4ClientProtocol, USB4_CLIENT_USB3, usb4_client_usb3_cb))
      {
				return EFI_PROTOCOL_ERROR;
      }
    }
  }
	return Status;
}


