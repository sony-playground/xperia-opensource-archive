/** @file TLMMDxe.c
**/
/*===========================================================================

             M A I N   D A L   T L M M   D R I V E R   F I L E

DESCRIPTION

  Contains the majority of functionality for the DAL TLMM driver.  The
  API in this module MUST always remain target independent.


===========================================================================
             Copyright (c) 2010-2015,2021 Qualcomm Technologies, Inc.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/18/21   amar    Extending TLMM driver to support EFI_GPIO_PROTOCOL.
09/16/14   sho     Use DAL configuration to register devices
05/01/14   asmitp  Renamed header file DALSYSProtocol.h to EFIDALSYSProtocol.h
01/06/11   dcf     Created.
==============================================================================*/

/*==============================================================================

                       INCLUDE FILES FOR THIS MODULE

==============================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EFIDALSYSProtocol.h>
#include <DALDeviceId.h>
#include <DalDevice.h>
#include <DDITlmm.h>
#include <Protocol/EFITlmm.h>
#include <DALSys.h>


#include <GPIO.h>
#include <GPIOTypes.h>
#include <GPIOCore.h>
#include <Protocol/EFIGPIO.h>


/*==============================================================================

                         DEFINES FOR THIS MODULE

==============================================================================*/


/*==============================================================================

                     EXTERNAL DEFINES FOR THIS MODULE

==============================================================================*/

extern DALResult TLMM_DalTlmm_Attach(const char *pszArg, DALDEVICEID DeviceId, 
                            DalDeviceHandle **phDalDevice);




/*==============================================================================

                      PROTOTYPES USED IN THIS MODULE

==============================================================================*/

EFI_STATUS
EFI_TLMM_ConfigGpio(IN UINT32 config, IN UINT32 enable);

EFI_STATUS
EFI_TLMM_ConfigGpioGroup(IN UINT32 enable, IN UINT32 *config_group, IN UINT32 size);

EFI_STATUS
EFI_TLMM_GpioIn(IN UINT32 config, OUT UINT32 *value);

EFI_STATUS
EFI_TLMM_GpioOut(IN UINT32 config, IN UINT32 value);

EFI_STATUS
EFI_TLMM_SetInactiveConfig(IN UINT32 gpio_number, IN UINT32 config);

EFI_STATUS EFI_GPIO_Attach (
  IN  GPIODeviceIdType      eDevice,
  OUT GPIOClientHandleType *pHandle);

EFI_STATUS EFI_GPIO_RegisterPinExplicit (
  IN  GPIOClientHandleType  Handle,
  IN  uint32                nPinNumber,
  IN  GPIOAccessType        AccessType,
  OUT GPIOKeyType          *GPIOKey);


EFI_STATUS EFI_GPIO_ConfigPin (
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey,
  IN  GPIOConfigType        Config);


EFI_STATUS EFI_GPIO_ConfigPinInactive (
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey);


EFI_STATUS EFI_GPIO_ReadPin (
  IN  GPIOClientHandleType Handle,
  IN  GPIOKeyType          GPIOKey,
  OUT GPIOValueType       *pValue);


EFI_STATUS EFI_GPIO_WritePin (
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey,
  IN  GPIOValueType         Value);


EFI_STATUS EFI_GPIO_RegisterDevicePin (
  IN  GPIOClientHandleType  Handle,
  IN  fdt_node_handle      *pClientnode,
  IN  const char           *szName,
  OUT GPIOKeyType          *pGPIOkey);


EFI_STATUS EFI_GPIO_RegisterDeviceConfig (
  IN  GPIOClientHandleType  Handle,
  IN  fdt_node_handle      *pClientnode,
  IN  const char           *szName,
  OUT GPIOKeyType          *pGPIOkey);

EFI_STATUS EFI_GPIO_GetPinConfig(
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey,
  OUT GPIOConfigType       *Config);

/*==============================================================================

                     GLOBAL VARIABLES FOR THIS MODULE

==============================================================================*/


/*
 * DALTLMM interface handle.  This must be initialized before accessing any 
 * DALTLMM APIs. 
 */

DalDeviceHandle * tlmm_handle;



/*
 * For dynamic device loading the DALSYSModConfig structure is populated 
 * by this module. 
 */

static DALDEVICEID DalTlmm_DeviceId[1] = { DALDEVICEID_TLMM };
static DALREG_DriverInfo DALTLMM_DriverInfo = { TLMM_DalTlmm_Attach, 1, DalTlmm_DeviceId };
static DALREG_DriverInfo * DALDriverInfoArr[1] = { &DALTLMM_DriverInfo };

static DALSYSConfig DALSYSModConfig = 
   {
      {0, NULL},              // string device info
      {1, DALDriverInfoArr}   // numeric driver info
   };


/*
 * Function table for DAL wrapper APIs.
*/

static EFI_TLMM_PROTOCOL TLMMProtocol = 
{
  EFI_TLMM_PROTOCOL_REVISION,
  EFI_TLMM_ConfigGpio,
  EFI_TLMM_ConfigGpioGroup,
  EFI_TLMM_GpioIn,
  EFI_TLMM_GpioOut,
  EFI_TLMM_SetInactiveConfig
};


/*
 * Function table for EFI GPIO Protocol handler APIs.
*/

static EFI_GPIO_PROTOCOL GPIOProtocol = 
{
  EFI_GPIO_PROTOCOL_REVISION,
  EFI_GPIO_Attach,
  EFI_GPIO_RegisterPinExplicit,
  EFI_GPIO_RegisterDevicePin,
  EFI_GPIO_RegisterDeviceConfig,
  EFI_GPIO_ConfigPin,
  EFI_GPIO_ConfigPinInactive,
  EFI_GPIO_ReadPin,
  EFI_GPIO_WritePin,
  EFI_GPIO_GetPinConfig,
};



/*==============================================================================

                             API IMPLEMENTATION

==============================================================================*/

/* =========================================================================
**  Function : GPIO_RESULT__TO__EFI_STATUS
** =========================================================================*/
/*
  Mapping of GPIOResult to EFI_STATUS.
 */

static __inline EFI_STATUS GPIO_RESULT__TO__EFI_STATUS
(
  GPIOResult Status
)
{
  switch (Status)
  {
    case GPIO_SUCCESS:
      return EFI_SUCCESS;

    case GPIO_RESOURCE_NOT_FOUND:
      return EFI_NOT_FOUND;

    case GPIO_NOT_SUPPORTED:
      return EFI_UNSUPPORTED;

    case GPIO_INVALID_PARAMETER:
      return EFI_INVALID_PARAMETER;

    case GPIO_INTERNAL_ERROR:
    default:
      return EFI_PROTOCOL_ERROR;
  }
} /* END EFI_STATUS__TO__GPIO_RESULT */


/*==============================================================================

  FUNCTION      EFI_TLMM_ConfigGpio

  DESCRIPTION   See EFI_TLMM_CONFIG_GPIO in Protocol/TLMM.h

==============================================================================*/

EFI_STATUS
EFI_TLMM_ConfigGpio(IN UINT32 config, IN UINT32 enable)
{
  DALResult result = DAL_ERROR;
  DALGpioEnableType dal_enable = DAL_TLMM_GPIO_DISABLE;

  if(tlmm_handle)
  {
    if(enable != 0)
    {
      dal_enable = DAL_TLMM_GPIO_ENABLE;
    }
    result = DalTlmm_ConfigGpio(tlmm_handle, config, dal_enable);
  }
  if(DAL_SUCCESS == result)
  {
    return(EFI_SUCCESS);
  }
  return(EFI_UNSUPPORTED);

} /* EFI_TLMM_ConfigGpio */



/*==============================================================================

  FUNCTION      EFI_TLMM_ConfigGpioGroup

  DESCRIPTION   See EFI_TLMM_CONFIG_GPIO_GROUP in Protocol/TLMM.h

==============================================================================*/ 

EFI_STATUS
EFI_TLMM_ConfigGpioGroup(IN UINT32 enable, IN UINT32 *config_group, IN UINT32 size)
{
  DALResult result = DAL_ERROR;
  DALGpioEnableType dal_enable = DAL_TLMM_GPIO_DISABLE;

  if(tlmm_handle)
  {
    if(enable != 0)
    {
      dal_enable = DAL_TLMM_GPIO_ENABLE;
    }
    result = DalTlmm_ConfigGpioGroup(tlmm_handle, dal_enable, (uint32*)config_group, size);
  }
  if(DAL_SUCCESS == result)
  {
    return(EFI_SUCCESS);
  }
  return(EFI_UNSUPPORTED);

} /* EFI_TLMM_ConfigGpioGroup */



/*==============================================================================

  FUNCTION      EFI_TLMM_GpioIn

  DESCRIPTION   See EFI_TLMM_GPIO_IN in Protocol/TLMM.h

==============================================================================*/ 

EFI_STATUS
EFI_TLMM_GpioIn(IN UINT32 config, OUT UINT32 *value)
{
  DALResult result = DAL_ERROR;
  DALGpioValueType dal_value;

  if(tlmm_handle)
  {
    result = DalTlmm_GpioIn(tlmm_handle, config, &dal_value);

    if(dal_value == DAL_GPIO_LOW_VALUE)
    {
      *value = 0;
    }
    else
    {
      *value = 1;
    }
  }
  if(DAL_SUCCESS == result)
  {
    return(EFI_SUCCESS);
  }
  return(EFI_UNSUPPORTED);

} /* EFI_TLMM_GpioIn */



/*==============================================================================

  FUNCTION      EFI_TLMM_GpioOut

  DESCRIPTION   See EFI_TLMM_GPIO_OUT in Protocol/TLMM.h

==============================================================================*/ 

EFI_STATUS
EFI_TLMM_GpioOut(IN UINT32 config, IN UINT32 value)
{
  DALResult result = DAL_ERROR;
  DALGpioValueType dal_value = DAL_GPIO_LOW_VALUE;
  if(tlmm_handle)
  {
    if( value != 0)
    {
      dal_value = DAL_GPIO_HIGH_VALUE;
    }
    result = DalTlmm_GpioOut(tlmm_handle, config, dal_value);
  }
  if(DAL_SUCCESS == result)
  {
    return(EFI_SUCCESS);
  }
  return(EFI_UNSUPPORTED);

} /* EFI_TLMM_GpioOut */



/*==============================================================================

  FUNCTION      EFI_TLMM_SetInactiveConfig

  DESCRIPTION   See EFI_TLMM_SET_INACTIVE_CONFIG in Protocol/TLMM.h

==============================================================================*/ 

EFI_STATUS
EFI_TLMM_SetInactiveConfig(IN UINT32 gpio_number, IN UINT32 config)
{
  DALResult result = DAL_ERROR;
  if(tlmm_handle)
  {
    result = DalTlmm_SetInactiveConfig(tlmm_handle, gpio_number, config);
  }
  if(DAL_SUCCESS == result)
  {
    return(EFI_SUCCESS);
  }
  return(EFI_UNSUPPORTED);

} /* EFI_TLMM_SetInactiveConfig */



/*==============================================================================

  FUNCTION      EFI_GPIO_Attach

  DESCRIPTION   See EFI_GPIO_ATTACH in Protocol/EFIGPIO.h

==============================================================================*/ 

EFI_STATUS EFI_GPIO_Attach (
  IN  GPIODeviceIdType      eDevice,
  OUT GPIOClientHandleType *pHandle
)
{
  return GPIO_RESULT__TO__EFI_STATUS(
    GPIO_Attach(eDevice, pHandle));
}; /* END EFI_GPIO_ConfigPin */


/*==============================================================================

  FUNCTION      EFI_GPIO_RegisterPinExplicit

  DESCRIPTION   See EFI_GPIO_REGISTER_PIN_EXPLICIT in Protocol/EFIGPIO.h

==============================================================================*/ 

EFI_STATUS EFI_GPIO_RegisterPinExplicit (
  IN  GPIOClientHandleType  Handle,
  IN  uint32                nPinNumber,
  IN  GPIOAccessType        AccessType,
  OUT GPIOKeyType          *GPIOKey
)
{
  return GPIO_RESULT__TO__EFI_STATUS(
    GPIO_RegisterPinExplicit(Handle, nPinNumber, AccessType, GPIOKey));
}; /* END EFI_GPIO_RegisterPinExplicit */


/*==============================================================================

  FUNCTION      EFI_GPIO_ConfigPin

  DESCRIPTION   See EFI_GPIO_CONFIG_PIN in Protocol/EFIGPIO.h

==============================================================================*/ 

EFI_STATUS EFI_GPIO_ConfigPin (
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey,
  IN  GPIOConfigType        Config
)
{
  return GPIO_RESULT__TO__EFI_STATUS(
    GPIO_ConfigPin(Handle, GPIOKey, Config));
}; /* END EFI_GPIO_ConfigPin */


/*==============================================================================

  FUNCTION      EFI_GPIO_ConfigPinInactive

  DESCRIPTION   See EFI_GPIO_CONFIG_PIN_INACTIVE in Protocol/EFIGPIO.h

==============================================================================*/ 

EFI_STATUS EFI_GPIO_ConfigPinInactive (
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey
)
{
  return GPIO_RESULT__TO__EFI_STATUS(
    GPIO_ConfigPinInactive(Handle, GPIOKey));
}; /* END EFI_GPIO_ConfigPinInactive */


/*==============================================================================

  FUNCTION      EFI_GPIO_ReadPin

  DESCRIPTION   See EFI_GPIO_READ_PIN in Protocol/EFIGPIO.h

==============================================================================*/ 

EFI_STATUS EFI_GPIO_ReadPin (
  IN  GPIOClientHandleType Handle,
  IN  GPIOKeyType          GPIOKey,
  OUT GPIOValueType       *pValue
)
{
  return GPIO_RESULT__TO__EFI_STATUS(
    GPIO_ReadPin(Handle, GPIOKey, pValue));
}; /* END EFI_GPIO_ReadPin */


/*==============================================================================

  FUNCTION      EFI_GPIO_WritePin

  DESCRIPTION   See EFI_GPIO_WRITE_PIN in Protocol/EFIGPIO.h

==============================================================================*/ 

EFI_STATUS EFI_GPIO_WritePin (
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey,
  IN  GPIOValueType         Value
)
{
  return GPIO_RESULT__TO__EFI_STATUS(
    GPIO_WritePin(Handle, GPIOKey, Value));
} /* END EFI_GPIO_WritePin */


/*==============================================================================

  FUNCTION      EFI_GPIO_RegisterDevicePin

  DESCRIPTION   See EFI_GPIO_REGISTER_DEVICE_PIN in Protocol/EFIGPIO.h

==============================================================================*/ 

EFI_STATUS EFI_GPIO_RegisterDevicePin (
  IN  GPIOClientHandleType  Handle,
  IN  fdt_node_handle      *pClientnode,
  IN  const char           *szName,
  OUT GPIOKeyType          *pGPIOkey
)
{
  return GPIO_RESULT__TO__EFI_STATUS(
    GPIO_RegisterDevicePin(Handle, pClientnode, szName, pGPIOkey));
} /* END EFI_GPIO_RegisterDevicePin */


/*==============================================================================

  FUNCTION      EFI_GPIO_RegisterDeviceConfig

  DESCRIPTION   See EFI_GPIO_REGISTER_DEVICE_CONFIG in Protocol/EFIGPIO.h

==============================================================================*/ 

EFI_STATUS EFI_GPIO_RegisterDeviceConfig (
  IN  GPIOClientHandleType  Handle,
  IN  fdt_node_handle      *pClientnode,
  IN  const char           *szName,
  OUT GPIOKeyType          *pGPIOkey
)
{
  return GPIO_RESULT__TO__EFI_STATUS(
    GPIO_RegisterDeviceConfig(Handle, pClientnode, szName, pGPIOkey));
} /* END EFI_GPIO_RegisterDeviceConfig */


/*==============================================================================

  FUNCTION      EFI_GPIO_GetPinConfig

  DESCRIPTION   See EFI_GPIO_GET_PIN_CONFIG in Protocol/EFIGPIO.h

==============================================================================*/ 

EFI_STATUS EFI_GPIO_GetPinConfig(
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey,
  OUT GPIOConfigType       *Config
)
{
  return GPIO_RESULT__TO__EFI_STATUS(
    GPIO_GetPinConfig(Handle, GPIOKey, Config));
} /* END EFI_GPIO_GetPinConfig */


/*==============================================================================

  FUNCTION      DALTLMMEntryPoint

  DESCRIPTION   EFI DAL-Wrapper Entry point for TLMM/GPIO access.

==============================================================================*/ 

EFI_STATUS
EFIAPI
TLMMEntryPoint (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_HANDLE  handle = NULL;
  EFI_STATUS  status;
  DALResult result = DAL_ERROR;

  DALSYS_InitMod(&DALSYSModConfig);

  result = DAL_DeviceAttach(DALDEVICEID_TLMM, &tlmm_handle);

  if(DAL_SUCCESS == result)
  {
    status = gBS->InstallMultipleProtocolInterfaces(&handle,
                                                    &gEfiTLMMProtocolGuid, 
                                                    (void **)&TLMMProtocol,
                                                    &gEfiGPIOProtocolGuid,
                                                    (void **)&GPIOProtocol, NULL );
    ASSERT_EFI_ERROR(status);
    DalDevice_Open(tlmm_handle, DAL_OPEN_SHARED);
  }
  else
  {
    DAL_DeviceDetach(handle);
    DALSYS_DeInitMod();
    status = EFI_UNSUPPORTED;
  }

  return status;

} /* DALTLMMEntryPoint */

