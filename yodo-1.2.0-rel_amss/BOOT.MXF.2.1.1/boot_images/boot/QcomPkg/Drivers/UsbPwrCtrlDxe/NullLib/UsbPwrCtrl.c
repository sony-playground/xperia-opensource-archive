/**
@file  UsbPwrCtrl.c
@brief USB Power Control Module related Declaration
*/
/*=============================================================================
Copyright (c) 2020 - 2021 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     -----------------------------------------------------------
07/30/20   kas	   Initial Release
=============================================================================*/

/*===========================================================================*/
/*                  INCLUDE FILES                                            */
/*===========================================================================*/
#include <Uefi.h>

/**
  Library Dependencies
*/
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UsbPwrCtrlLib.h>

/*===========================================================================*/
/*                  LOCAL VARIABLE DECLARATIONS                              */
/*===========================================================================*/
EFI_USB_PWR_CTRL_PROTOCOL UsbPwrCtrlProtocolImplementation;

/*===========================================================================*/
/*                  FUNCTION DEFINITIONS                                     */
/*===========================================================================*/
/**
  Initialize UsbPwrCtrl Module

  @param none

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS UsbPwrCtrlInit(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  if(EFI_SUCCESS == Status)
  {
    Status = gBS->InstallMultipleProtocolInterfaces(&ImageHandle,
                                                    &gQcomUsbPwrCtrlProtocolGuid,
                                                    &UsbPwrCtrlProtocolImplementation,
                                                    NULL);
  }
  return Status;
}

/**
EFI_UsbPwrCtrl_GetHwInfo()

@brief
Get Hardware Information
*/
EFI_STATUS
EFIAPI
EFI_UsbPwrCtrl_GetHwInfo
(
  OUT EFI_USB_PWR_CTRL_USB_PORTHW_INFO *pUsbPortHwInfo
)
{
  return EFI_UNSUPPORTED;
}

/**
EFI_UsbPwrCtrl_GetVbusDetectStatus()

@brief
Get Vbus Detect Status
*/
EFI_STATUS
EFIAPI
EFI_UsbPwrCtrl_GetVbusDetectStatus
(
  IN  UINT8   PortIndex,
  OUT BOOLEAN *bVbusDetect
)
{
	return EFI_UNSUPPORTED;
}

/**
EFI_UsbPwrCtrl_GetVbusSrcOkStatus()

@brief
Get Vbus Source-OK Status
*/
EFI_STATUS
EFIAPI
EFI_UsbPwrCtrl_GetVbusSrcOkStatus
(
  IN  UINT8   PortIndex,
  OUT BOOLEAN *bVbusSrcOk
)
{
	return EFI_UNSUPPORTED;
}

/**
EFI_UsbPwrCtrl_GetHsUsbChgPortType()

@brief
Get BC1.2 Detection Result
*/
EFI_STATUS
EFIAPI
EFI_UsbPwrCtrl_GetHsUsbChgPortType
(
  IN  UINT8   PortIndex,
  OUT EFI_USB_PWR_CTRL_HSUSB_CHGPORT_TYPE *ChgPortType
)
{
	return EFI_UNSUPPORTED;
}

/**
EFI_UsbPwrCtrl_GetUsbIDStatus()

@brief
Get USB ID Status
*/
EFI_STATUS
EFIAPI
EFI_UsbPwrCtrl_GetUsbIDStatus
(
  IN  UINT8   PortIndex,
  OUT BOOLEAN *bUsbId
)
{
	return EFI_UNSUPPORTED;
}

/**
EFI_UsbPwrCtrl_GetTypeCPortStatus()

@brief
Get Type C Port Status
*/
EFI_STATUS
EFIAPI
EFI_UsbPwrCtrl_GetTypeCPortStatus
(
  IN  UINT8   PortIndex,
  OUT EFI_USB_PWR_CTRL_TYPEC_PORT_STATUS *TypeCPortStatus
)
{
	return EFI_UNSUPPORTED;
}

/**
EFI_UsbPwrCtrl_GetTypeCPortPDStatus()

@brief
Get Type C Port Power Delivery Status
*/
EFI_STATUS
EFIAPI
EFI_UsbPwrCtrl_GetTypeCPortPDStatus
(
  IN  UINT8   PortIndex,
  OUT EFI_USB_PWR_CTRL_PD_STATUS  *PDStatus
)
{
	return EFI_UNSUPPORTED;
}

/**
EFI_UsbPwrCtrl_SetInputPower()

@brief
Configure Input Power
*/
EFI_STATUS
EFIAPI
EFI_UsbPwrCtrl_SetInputPower
(
  IN  UINT8   PortIndex,
  IN  EFI_USB_PWR_CTRL_INOUT_POWER_CONFIG  InputPowerCfg
)
{
	return EFI_UNSUPPORTED;
}

/**
EFI_UsbPwrCtrl_SetOutputPower()

@brief
Configure Output Power
*/
EFI_STATUS
EFIAPI
EFI_UsbPwrCtrl_SetOutputPower
(
  IN  UINT8   PortIndex,
  IN  EFI_USB_PWR_CTRL_INOUT_POWER_CONFIG  OutputPowerCfg
)
{
  return EFI_UNSUPPORTED;
}

/**
EFI_UsbPwrCtrl_SetVbusSourceEn()

@brief
Enable/Disable Vbus Source
*/
EFI_STATUS
EFIAPI
EFI_UsbPwrCtrl_SetVbusSourceEn
(
  IN  UINT8   PortIndex,
  IN  BOOLEAN  bVbusSrcEn
)
{
	return EFI_UNSUPPORTED;
}

/**
EFI_UsbPwrCtrl_SetVconnEn()

@brief
Enable/Disable Vconn Source
*/
EFI_STATUS
EFIAPI
EFI_UsbPwrCtrl_SetVconnEn
(
  IN  UINT8   PortIndex,
  IN  BOOLEAN  bVconnEn
)
{
	return EFI_UNSUPPORTED;
}

/**
  USB Power Control Protocol implementation
 */
EFI_USB_PWR_CTRL_PROTOCOL UsbPwrCtrlProtocolImplementation =
{
  USB_PWR_CTRL_REVISION,
  EFI_UsbPwrCtrl_GetHwInfo,
  EFI_UsbPwrCtrl_GetVbusDetectStatus,
  EFI_UsbPwrCtrl_GetVbusSrcOkStatus,
  EFI_UsbPwrCtrl_GetHsUsbChgPortType,
  EFI_UsbPwrCtrl_GetUsbIDStatus,
  EFI_UsbPwrCtrl_GetTypeCPortStatus,
  EFI_UsbPwrCtrl_GetTypeCPortPDStatus,
  EFI_UsbPwrCtrl_SetInputPower,
  EFI_UsbPwrCtrl_SetOutputPower,
  EFI_UsbPwrCtrl_SetVbusSourceEn,
  EFI_UsbPwrCtrl_SetVconnEn,
};