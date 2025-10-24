/**
  @file  EFISerialPort.h
  @brief Serial port Protocol for UEFI.
*/

/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/05/20  yw      init version.
=============================================================================*/

#ifndef __EFI_SERIAL_PORT_H__
#define __EFI_SERIAL_PORT_H__

/** @defgroup EFI_SERIAL_PORT_PROTOCOL  EFI_SERIAL_PORT_PROTOCOL 
 *  @ingroup UEFI_CORE 
 */
 /** @defgroup  EFI_SERIAL_PORT_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_SERIAL_PORT_PROTOCOL 
 */ 
 /** @defgroup  EFI_SERIAL_PORT_PROTOCOL_apis APIs
 *  @ingroup EFI_SERIAL_PORT_PROTOCOL 
 */ 

/** @defgroup  EFI_SERIAL_PORT_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_SERIAL_PORT_PROTOCOL 
 */
 
/**@ingroup EFI_SERIAL_PORT_PROTOCOL_data
**/
#define EFI_SERIAL_PORT_PROTOCOL_VERSION_V1 0x0000000000010001

#define EFI_SERIAL_PORT_PROTOCOL_GUID \
	{ 0x10365745, 0x2b76, 0x41f9, { 0xbf, 0xda, 0x5c, 0x48, 0x21, 0x9b, 0x45, 0x32 } } 

extern EFI_GUID gEfiSerialPortProtocolGuid;

/**@ingroup EFI_SERIAL_PORT_PROTOCOL_apis

  Disable Synchronous IO (Enable buffered IO)

**/
typedef
EFI_STATUS
(EFIAPI *EFI_DISABLE_SYNC_SERIAL_PORT_IO) (VOID);

/**@ingroup EFI_SERIAL_PORT_PROTOCOL_apis

  Enable Serial IO.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_ENABLE_SERIAL_OUT) (VOID);

/** @ingroup EFI_SERIAL_PORT_PROTOCOL_prot
**/
typedef struct _EFI_SERIAL_PORT_PROTOCOL {
	UINT64                              Revision;
	EFI_DISABLE_SYNC_SERIAL_PORT_IO   	DisableSynchronousSerialPortIO;
	EFI_ENABLE_SERIAL_OUT            	EnableSerialOut;
} EFI_SERIAL_PORT_PROTOCOL;

#endif