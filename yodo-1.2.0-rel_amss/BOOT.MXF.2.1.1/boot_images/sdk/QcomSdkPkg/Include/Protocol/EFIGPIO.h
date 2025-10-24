/**
  @file  EFIGPIO.h
  @brief General-Purpose Input/Output Protocol for UEFI.
*/
/*=============================================================================
  Copyright (c) 2021 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     	what, where, why
 --------   ---     	-----------------------------------------------------------
 01/14/22	brateesh	added get pin config
 07/05/21   amr    		Created.
=============================================================================*/
#ifndef __EFIGPIO_H__
#define __EFIGPIO_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/
#include <GPIOTypes.h>


/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @ingroup efi_gpio_protocol_data
  Protocol version.
*/
#define EFI_GPIO_PROTOCOL_REVISION 0x0000000000000001

/*  Protocol GUID definition */
/** @ingroup efi_gpio_protocol_data */
#define EFI_GPIO_PROTOCOL_GUID \
    { 0x1A7405FC, 0x0285, 0x41F0, { 0xA5, 0x35, 0x01, 0x81, 0x41, 0xF8, 0x39, 0xE7 } }

/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/** @cond */
/**
  External reference to the GPIO Protocol GUID.
*/
extern EFI_GUID gEfiGPIOProtocolGuid;
/** @endcond */


/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/

/* EFI_GPIO_ATTACH */
/** @ingroup efi_gpio_protocol_apis
  @par Summary
  Attaches to a GPIO device and initializes a client handle.

  This function is required to be called first on a per-GPIO device basis.
  A client can attach to multiple GPIO devices, but must call this API for
  each required device.  The handle initialized in this function will be
  passed to all subsequent functions beginning with the EFI_GPIO_REGISTER_PIN or
  EFI_GPIO_REGISTER_PIN_EXPLICIT.

  @param eDevice  [in]  The GPIO HW device required by the client.
  @param pHandle  [out] A client handle to initialize.

  @return
  EFI_SUCCESS -- A client handle was created.
  EFI_PROTOCOL_ERROR  -- A Attach failed.
  EFI_INVALID_PARAMETER --  The parameter is invalid.

  @dependencies
  None.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_GPIO_ATTACH)(
  IN  GPIODeviceIdType      eDevice,
  OUT GPIOClientHandleType *pHandle
);


/* EFI_GPIO_REGISTER_PIN_EXPLICIT */
/** @ingroup efi_gpio_protocol_apis
  @par Summary
  Registers a GPIO signal with the GPIO driver for accessing additional APIs
  for environments where the GPIO string signal name is not available.

  This function must be called on a per-GPIO basis for a particular device
  (see GPIO_Attach).  Using a GPIO configuration, clients will call
  this API to retrieve the GPIO pin key which will be passed into all subsequent
  functions and identifies the associated GPIO as valid and available.

  Note:  The GPIOConfigType Config structure must have the GPIO number
         initialized before calling this API as it will be used to register
         the pin.  The rest of the parameters are not used in this function.

  @param Handle     [in]  The device handle (see EFI_GPIO_ATTACH).
  @param nPinNumber [in]  Address of a GPIOConfigType configuration.
  @param AccessType [in]  The type of access desired - shared or exclusive
                          (see GPIOTypes.h).  Shared will allow multiple entities
                          to retrieve the same pin key, while exclusive will lock
                          the GPIO to the first caller.
  @param *GPIOKey   [out] Container for the GPIOKey to access GPIO APIs.

  @return
  EFI_SUCCESS -- The operation completed successfully.
  EFI_PROTOCOL_ERROR  -- The operation completed un-successfully.
  EFI_INVALID_PARAMETER --  The parameter is invalid.

  @dependencies
  EFI_GPIO_ATTACH must have been called prior to calling this API.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_GPIO_REGISTER_PIN_EXPLICIT)(
  IN  GPIOClientHandleType  Handle,
  IN  uint32                nPinNumber,
  IN  GPIOAccessType        AccessType,
  OUT GPIOKeyType          *GPIOKey);


/* EFI_GPIO_CONFIG_PIN */
/** @ingroup efi_gpio_protocol_apis
  @par Summary
  Configures a GPIO pin.

  This function configures a GPIO pin to the setting specified by the calling
  client if the GPIO is properly registered (see EFI_GPIO_REGISTER_PIN and
  EFI_GPIO_REGISTER_PIN_EXPLICIT).

  @param Handle  [in] The device handle (see EFI_GPIO_ATTACH).
  @param GPIOKey [in] A valid GPIO pin key.
  @param Config  [in] The GPIO configuration to program.

  @return
  EFI_SUCCESS -- The operation completed successfully.
  EFI_PROTOCOL_ERROR  -- The operation completed un-successfully.
  EFI_INVALID_PARAMETER --  The parameter is invalid.

  @dependencies
  EFI_GPIO_ATTACH must have been called prior to calling this API.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_GPIO_CONFIG_PIN)(
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey,
  IN  GPIOConfigType        Config);


/* EFI_GPIO_CONFIG_PIN_INACTIVE */
/** @ingroup efi_gpio_protocol_apis
  @par Summary
  Configures a GPIO pin.

  This function configures a GPIO pin to a pre-determined low-power setting,
  which has been specified at boot time or otherwise stated.

  @param Handle  [in] The device handle (see EFI_GPIO_ATTACH).
  @param GPIOKey [in] A valid GPIO pin key.

  @return
  EFI_SUCCESS -- The operation completed successfully.
  EFI_PROTOCOL_ERROR  -- The operation completed un-successfully.
  EFI_INVALID_PARAMETER --  The parameter is invalid.

  @dependencies
  EFI_GPIO_ATTACH must have been called prior to calling this API.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_GPIO_CONFIG_PIN_INACTIVE)(
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey);


/* EFI_GPIO_READ_PIN */
/** @ingroup efi_gpio_protocol_apis
  @par Summary
  Reads the input state of the GPIO line.

  This function can be used to read the input signal of a pin (high or low).

  @param Handle    [in]  The device handle (see EFI_GPIO_ATTACH).
  @param GPIOKey   [in]  A valid GPIO pin key.
  @param *pValue   [out] Storage for capturing state of GPIO pin.

  @return
  EFI_SUCCESS -- The operation completed successfully.
  EFI_PROTOCOL_ERROR  -- The operation completed un-successfully.
  EFI_INVALID_PARAMETER --  The parameter is invalid.

  @dependencies
  EFI_GPIO_ATTACH must have been called prior to calling this API.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_GPIO_READ_PIN)(
  IN  GPIOClientHandleType Handle,
  IN  GPIOKeyType          GPIOKey,
  OUT GPIOValueType       *pValue);


/* EFI_GPIO_WRITE_PIN */
/** @ingroup efi_gpio_protocol_apis
  @par Summary
  Drivers the GPIO line to given state.

  This function can be used to drive the signal of a pin (high or low).

  @param Handle    [in]  The device handle (see EFI_GPIO_ATTACH).
  @param GPIOKey   [in]  A valid GPIO pin key.
  @param Value     [in]  The value (high or low) to drive.  TRUE = high,
                         FALSE = low.

  @return
  EFI_SUCCESS -- The operation completed successfully.
  EFI_PROTOCOL_ERROR  -- The operation completed un-successfully.
  EFI_INVALID_PARAMETER --  The parameter is invalid.

  @dependencies
  EFI_GPIO_ATTACH must have been called prior to calling this API.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_GPIO_WRITE_PIN)(
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey,
  IN  GPIOValueType         Value);


/* EFI_GPIO_REGISTER_DEVICE_PIN */
/** @ingroup efi_gpio_protocol_apis
  @par Summary
  Register specific pin with GPIO driver

  This function read GPIO pin information from device tree and register it with GPIO driver

  @param  Handle    [in]  The device handle (see EFI_GPIO_ATTACH).
  @param *clientnode[in]  Client device node
  @param *szName    [in]  String which point to bit bang gpio property
  @param *pGPIOkey  [out] GPIO key which return to client

  @return
  EFI_SUCCESS -- The operation completed successfully.
  EFI_PROTOCOL_ERROR  -- The operation completed un-successfully.
  EFI_INVALID_PARAMETER --  The parameter is invalid.

  @dependencies
  EFI_GPIO_ATTACH must have been called prior to calling this API.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_GPIO_REGISTER_DEVICE_PIN)(
  IN  GPIOClientHandleType  Handle,
  IN  void                 *pClientnode,
  IN  const char           *szName,
  OUT GPIOKeyType          *pGPIOkey);


/* EFI_GPIO_REGISTER_DEVICE_CONFIG */
/** @ingroup efi_gpio_protocol_apis
  @par Summary
  Register set of GPIO pins configurations with GPIO driver

  This function read GPIO configuration from device tree and register it with GPIO driver

  @param  Handle    [in]  The device handle (see EFI_GPIO_ATTACH).
  @param *pClientnode [in]  Client device node
  @param *szName    [in]  String which point to bit bang gpio property
  @param *pGPIOkey  [out] GPIO key which return to client


  @return
  EFI_SUCCESS -- The operation completed successfully.
  EFI_PROTOCOL_ERROR  -- The operation completed un-successfully.
  EFI_INVALID_PARAMETER --  The parameter is invalid.

  @dependencies
  EFI_GPIO_ATTACH must have been called prior to calling this API.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_GPIO_REGISTER_DEVICE_CONFIG)(
  IN  GPIOClientHandleType  Handle,
  IN  void                 *pClientnode,
  IN  const char           *szName,
  OUT GPIOKeyType          *pGPIOkey);


/* EFI_GPIO_GET_PIN_CONFIG */
/** @ingroup efi_gpio_protocol_apis
  @par Summary
  Retrieves the current GPIO pin configuration.

  This function returns the current GPIO configuration programmed to hardware.

  @param Handle  [in] The device handle (see EFI_GPIO_ATTACH).
  @param GPIOKey [in] A valid GPIO pin key.
  @param Config  [in] Storage for the configuration retrieval.

  @return
  EFI_SUCCESS -- The operation completed successfully.
  EFI_PROTOCOL_ERROR  -- The operation completed un-successfully.
  EFI_INVALID_PARAMETER --  The parameter is invalid.

  @dependencies
  EFI_GPIO_ATTACH must have been called prior to calling this API.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_GPIO_GET_PIN_CONFIG)(
  IN  GPIOClientHandleType  Handle,
  IN  GPIOKeyType           GPIOKey,
  OUT GPIOConfigType       *Config);


/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_gpio_protocol_prot
  @par Summary
  General-Purpose Input/Output Protocol for UEFI.

  @par Parameters
  @inputprotoparams{gpio_proto_params.tex}
*/

typedef struct _EFI_GPIO_PROTOCOL {
  UINT64                           Revision;
  EFI_GPIO_ATTACH                  Attach;
  EFI_GPIO_REGISTER_PIN_EXPLICIT   RegisterPinExplicit;
  EFI_GPIO_REGISTER_DEVICE_PIN     RegisterDevicePin;
  EFI_GPIO_REGISTER_DEVICE_CONFIG  RegisterDeviceConfig;
  EFI_GPIO_CONFIG_PIN              ConfigPin;
  EFI_GPIO_CONFIG_PIN_INACTIVE     ConfigPinInactive;
  EFI_GPIO_READ_PIN                ReadPin;
  EFI_GPIO_WRITE_PIN               WritePin;
  EFI_GPIO_GET_PIN_CONFIG          GetPinConfig;
} EFI_GPIO_PROTOCOL;

#endif /* __EFIGPIO_H__ */
