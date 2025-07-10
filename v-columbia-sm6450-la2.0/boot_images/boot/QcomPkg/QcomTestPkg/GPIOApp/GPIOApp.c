/** @file GPIOApp.c
   
  GPIO Test Application. 
   
  This application tests the GPIO.h interface
  and indirectly testing EFIGPIO.h as well
  (becouse GPIOApiLib is wrapper over EFIGPIO Protocol)

  Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/20/21   amr     Created.

=============================================================================*/


#include <GPIO.h>
#include <Library/QcomLib.h>
#include <Library/TestInterface.h>
#include <Library/MemoryAllocationLib.h>


/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.  This application 
  is presented to test the mechanism for which to manipulate 
  GPIO.  It should only be used in test scenarios as it affects 
  the state of the HW.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
GPIOAppMain (
  IN EFI_HANDLE          ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  UINTN                 argc = 0;
  CHAR8               **argv = NULL;
  EFI_STATUS            status = EFI_SUCCESS;
  UINTN                 pinNumber = 0;
  GPIOKeyType           GPIOKey = {0};
  GPIOConfigType        TestConfig = {0};
  GPIOClientHandleType  GPIOHandle = {0};
  GPIOResult            eResult = GPIO_ERROR;
  GPIODeviceIdType      eDevice = GPIO_DEVICE_TLMM;
  GPIOAccessType        AccessType = GPIO_ACCESS_SHARED;

  TEST_START("GPIO");

  status = GetCmdLineArgs (ImageHandle, &argc, &argv);
  if (EFI_ERROR(status) || argc != 2)
  {
    AsciiPrint("Error: Command line arguments failed. \r\n "
               "Usage: GPIOTest.efi <pin number>\r\n "
               "\tex: GPIOTest.efi 8 \r\n ");
    status = EFI_INVALID_PARAMETER;
    goto endoftest;
  }

  pinNumber = AsciiStrDecimalToUintn(argv[1]);

  /* Attach to the GPIO driver. */
  eResult = GPIO_Attach(eDevice, &GPIOHandle);
  if(GPIO_SUCCESS != eResult)
  {
    status = EFI_OUT_OF_RESOURCES;
    goto endoftest;
  }

  /* Register the Test Pin with GPIO driver. */
  eResult = GPIO_RegisterPinExplicit(GPIOHandle, pinNumber, AccessType, &GPIOKey);
  if(GPIO_SUCCESS != eResult)
  {
    status = EFI_PROTOCOL_ERROR;
    goto endoftest;
  }

  /* Test the GPIO driver interface. This application does not have a way to
     verify that the HW has been affected.  The purpose is to test the interface
     mechanism.  Only probing the physical device or examining the contents of
     HW registers can the actual functionality be fully verified. */

  /* Create a GPIO configuration for testing. */
  TestConfig.func  = 0;
  TestConfig.dir   = GPIO_OUT;
  TestConfig.pull  = GPIO_NP;
  TestConfig.drive = 200;         // TODO: not sure which macro to use. GPIO_2MA is only for EFITLMM. 

  /* Configure the GPIO. */
  eResult = GPIO_ConfigPin(GPIOHandle, GPIOKey, TestConfig);
  if(GPIO_SUCCESS == eResult)
  {
    /* Drive the GPIO HIGH. */
    eResult = GPIO_WritePin(GPIOHandle, GPIOKey, GPIO_HIGH);

    if(GPIO_SUCCESS == eResult)
    {
      /* Drive the GPIO LOW */
      eResult = GPIO_WritePin(GPIOHandle, GPIOKey, GPIO_LOW);
    }
  }

endoftest:

  if(argv)
    FreePool(argv);

  TestStatus("GPIO",status);
  TEST_STOP("GPIO");

  return status;

} /* GPIOAppMain */

