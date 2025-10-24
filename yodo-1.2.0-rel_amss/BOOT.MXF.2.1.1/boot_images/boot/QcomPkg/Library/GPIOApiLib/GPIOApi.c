/*
===============================================================================

FILE: GPIOApi.c

DESCRIPTION:
  Wrapper Library for GPIO common interface (GPIO.h).

===============================================================================

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/GPIOApiLib/GPIOApi.c#1 $

===============================================================================
            Copyright (c) 2021 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===============================================================================

*/


//=============================================================================
//                   Includes and Public Data Declarations
//=============================================================================

#include <Library/CoreVerify.h>                 // for CORE_VERIFY macro
#include <Uefi.h>                               // for UEFI typedefs like EFI_GUID, status codes
#include <Library/UefiBootServicesTableLib.h>   // for gBS
#include <GPIO.h>
#include <Protocol/EFIGPIO.h>                   // for EFI_GPIO_PROTOCOL


/*=========================================================================
                          Data Definitions
==========================================================================*/

static EFI_GPIO_PROTOCOL *gGPIOProtocol = NULL;


/*===========================================================================
                          Function Definitions
=============================================================================*/

/* =========================================================================
**  Function : EFI_STATUS__TO__GPIO_RESULT
** =========================================================================*/
/*
  Mapping of EFI_STATUS to GPIOResult.
 */

static __inline GPIOResult EFI_STATUS__TO__GPIO_RESULT
(
  EFI_STATUS Status
)
{
  switch (Status)
  {
    case EFI_SUCCESS:
      return GPIO_SUCCESS;

    case EFI_NOT_FOUND:
      return GPIO_RESOURCE_NOT_FOUND;

    case EFI_UNSUPPORTED:
      return GPIO_NOT_SUPPORTED;

    case EFI_INVALID_PARAMETER:
      return GPIO_INVALID_PARAMETER;

    case EFI_PROTOCOL_ERROR:
      return GPIO_INTERNAL_ERROR;

    default:
      return GPIO_ERROR;
  }
} /* END EFI_STATUS__TO__GPIO_RESULT */


/* =========================================================================
**  Function : GPIO_Attach
** =========================================================================*/
/*
  See GPIO.h.
*/

GPIOResult GPIO_Attach
(
  GPIODeviceIdType      eDevice,
  GPIOClientHandleType *pHandle
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  if (!gGPIOProtocol){
    Status = gBS->LocateProtocol(&gEfiGPIOProtocolGuid, NULL, (void**)(&gGPIOProtocol));
  }
  CORE_VERIFY(EFI_SUCCESS == Status);
  CORE_VERIFY_PTR(gGPIOProtocol);
  return EFI_STATUS__TO__GPIO_RESULT(
    gGPIOProtocol->Attach(eDevice, pHandle));
} /* END GPIO_Attach */


/* =========================================================================
**  Function : GPIO_RegisterPin
** =========================================================================*/
/*
  See GPIO.h.
*/

GPIOResult GPIO_RegisterPin
(
  GPIOClientHandleType  Handle,
  const char           *pszSignal,
  GPIOAccessType        AccessType,
  GPIOConfigType       *pConfig,
  GPIOKeyType          *pGPIOKey
)
{
  CORE_VERIFY_PTR(gGPIOProtocol);
  return EFI_STATUS__TO__GPIO_RESULT(EFI_UNSUPPORTED);
} /* END GPIO_RegisterPin */


/* =========================================================================
**  Function : GPIO_RegisterPinExplicit
** =========================================================================*/
/*
  See GPIO.h.
*/

GPIOResult GPIO_RegisterPinExplicit
(
  GPIOClientHandleType  Handle,
  uint32                nPinNumber,
  GPIOAccessType        AccessType,
  GPIOKeyType          *GPIOKey
)
{
  CORE_VERIFY_PTR(gGPIOProtocol);
  return EFI_STATUS__TO__GPIO_RESULT(
    gGPIOProtocol->RegisterPinExplicit(Handle, nPinNumber, AccessType, GPIOKey));
} /* END GPIO_RegisterPinExplicit */


/* =========================================================================
**  Function : GPIO_ConfigPin
** =========================================================================*/
/*
  See GPIO.h.
*/

GPIOResult GPIO_ConfigPin
(
  GPIOClientHandleType  Handle,
  GPIOKeyType           GPIOKey,
  GPIOConfigType        Config
)
{
  CORE_VERIFY_PTR(gGPIOProtocol);
  return EFI_STATUS__TO__GPIO_RESULT(
    gGPIOProtocol->ConfigPin(Handle, GPIOKey, Config));
} /* END GPIO_ConfigPin */


/* =========================================================================
**  Function : GPIO_ConfigPinInactive
** =========================================================================*/
/*
  See GPIO.h.
*/

GPIOResult GPIO_ConfigPinInactive
(
  GPIOClientHandleType  Handle,
  GPIOKeyType           GPIOKey
)
{
  CORE_VERIFY_PTR(gGPIOProtocol);
  return EFI_STATUS__TO__GPIO_RESULT(
    gGPIOProtocol->ConfigPinInactive(Handle, GPIOKey));
} /* END GPIO_ConfigPinInactive */


/* =========================================================================
**  Function : GPIO_ReadPin
** =========================================================================*/
/*
  See GPIO.h.
*/

GPIOResult GPIO_ReadPin
(
  GPIOClientHandleType Handle,
  GPIOKeyType          GPIOKey,
  GPIOValueType       *pValue
)
{
  CORE_VERIFY_PTR(gGPIOProtocol);
  return EFI_STATUS__TO__GPIO_RESULT(
    gGPIOProtocol->ReadPin(Handle, GPIOKey, pValue));
} /* END GPIO_ReadPin */


/* =========================================================================
**  Function : GPIO_WritePin
** =========================================================================*/
/*
  See GPIO.h.
*/

GPIOResult GPIO_WritePin
(
  GPIOClientHandleType  Handle,
  GPIOKeyType           GPIOKey,
  GPIOValueType         Value
)
{
  CORE_VERIFY_PTR(gGPIOProtocol);
  return EFI_STATUS__TO__GPIO_RESULT(
    gGPIOProtocol->WritePin(Handle, GPIOKey, Value));
} /* END GPIO_WritePin */


/* =========================================================================
**  Function : GPIO_RegisterDeviceConfig
** =========================================================================*/
/*
  See GPIO.h.
*/

GPIOResult GPIO_RegisterDeviceConfig
(
  GPIOClientHandleType  Handle,
  fdt_node_handle      *pClientnode,
  const char           *szName,
  GPIOKeyType          *pGPIOkey
)
{
  CORE_VERIFY_PTR(gGPIOProtocol);
  return EFI_STATUS__TO__GPIO_RESULT(
    gGPIOProtocol->RegisterDeviceConfig(Handle, pClientnode, szName, pGPIOkey));
} /* END GPIO_RegisterDeviceConfig */


/* =========================================================================
**  Function : GPIO_RegisterDevicePin
** =========================================================================*/
/*
  See GPIO.h.
*/

GPIOResult GPIO_RegisterDevicePin
(
  GPIOClientHandleType  Handle,
  fdt_node_handle      *pClientnode,
  const char           *szName,
  GPIOKeyType          *pGPIOkey
)
{
  CORE_VERIFY_PTR(gGPIOProtocol);
  return EFI_STATUS__TO__GPIO_RESULT(
    gGPIOProtocol->RegisterDevicePin(Handle, pClientnode, szName, pGPIOkey));
} /* END GPIO_RegisterDevicePin */


/* =========================================================================
**  Function : GPIO_GetPinConfig
** =========================================================================*/
/*
  See GPIO.h.
*/

GPIOResult GPIO_GetPinConfig
(
  GPIOClientHandleType Handle,
  GPIOKeyType          GPIOKey,
  GPIOConfigType      *Config
)
{
  CORE_VERIFY_PTR(gGPIOProtocol);
  return EFI_STATUS__TO__GPIO_RESULT(
    gGPIOProtocol->GetPinConfig(Handle, GPIOKey, Config));
} /* END GPIO_GetPinConfig */

