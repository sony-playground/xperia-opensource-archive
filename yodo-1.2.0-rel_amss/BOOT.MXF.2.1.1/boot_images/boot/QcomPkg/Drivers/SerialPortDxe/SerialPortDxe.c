/*===============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         SerialPortDxe.c
  DESCRIPTION:    
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  05/05/20   yw         initial version
================================================================================*/
#include <Protocol/EFISerialPort.h>
#include <Library/SerialPortShLib.h>
#include <Library/UefiBootServicesTableLib.h>

/**

  Disable Synchronous IO (Enable buffered IO)

**/
STATIC EFI_STATUS
EFI_SERIAL_PORT_DisableSynchronousSerialPortIO (VOID)
{
	DisableSynchronousSerialPortIO();
	return EFI_SUCCESS;
}

/**

  Enable Serial IO.

**/
STATIC EFI_STATUS
EFI_SERIAL_PORT_EnableSerialOut (VOID)
{
	EnableSerialOut();
	return EFI_SUCCESS;
}

/**
  QcomUtil protocol defination
  
**/
STATIC EFI_SERIAL_PORT_PROTOCOL SerialPortProtocol =
{
   EFI_SERIAL_PORT_PROTOCOL_VERSION_V1,
   EFI_SERIAL_PORT_DisableSynchronousSerialPortIO,
   EFI_SERIAL_PORT_EnableSerialOut
};

/**
  The Entry Point for Serial Port module. 

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurred when executing this entry point.

**/
 
EFI_STATUS EFIAPI 
SerialPortDxeEntry
(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
)
{
	EFI_HANDLE Handle = NULL;
    EFI_STATUS Status;
	
	Status = gBS->InstallMultipleProtocolInterfaces(
                    &Handle,
                    &gEfiSerialPortProtocolGuid,
                    (VOID **)&SerialPortProtocol,
                    NULL );
    if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "Failed to install serial port shared protcol.\n"));
    }
	
	return Status;
}