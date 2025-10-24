/** @file
  I2C Keyboard Driver that manages I2C keyboard and produces Simple Text Input
  Protocol and Simple Text Input Ex Protocol.

Copyright (c) 2018 Qualcomm Technologies Inc. All rights reserved.
Portions Copyright (c) 2004 - 2012,2021 Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 6/28/21    rchriste Adding offmode charging check
 6/2/21     rchriste Adding PAM Client vote for LDO 12C
 1/22/21    rchriste Adding support for MK QRD
 05/27/19   ssumit   i2c_open deadlock FIX with other minor changes
 04/05/19   ssumit   KW error, boot time optimization
 02/19/19   ssumit   Optimization to check Platform and reduce load time 
 11/01/18   ssumit   Adding support for Poipu CLS
 05/05/17   ltg      Added bug fixes and enable command 
 03/13/17   ltg      Initial revision for UEFI I2C Keyboard Driver 
=============================================================================*/

#include "EfiKey.h"
#include "Keyboard.h"

#include <Protocol/EFITlmm.h>
#include <Protocol/EFIChargerEx.h>
#include <Library/QcomLib.h>
EFI_TLMM_PROTOCOL    *TLMMProtocol   = NULL;

#define QCOM_KEYBOARD_DEVICE_GUID \
    { 0xE7F58A0E, 0xBED2, 0x4B5A, { 0xBB, 0x43, 0x8A, 0xB2, 0x3D, 0xD0, 0xE2, 0xB0} }
    
#define TLMM_GPIO_KBD          EFI_GPIO_CFG(104, 0, GPIO_INPUT, GPIO_PULL_UP, GPIO_2MA)
#define GPIO_INIT_INTERVAL     1000000  // 0.1s

#pragma pack(1)
typedef struct {
  VENDOR_DEVICE_PATH             VendorDevicePath;
  EFI_DEVICE_PATH_PROTOCOL       End;
} EFI_KEYBOARD_DEVICE_PATH;
#pragma pack()

typedef struct {
  EFI_HANDLE      ImageHandle;
  VOID *          I2CHandle;
  I2C_KB_DEV      kbddevice;
} KBD_INIT_CONFIG;

int is_kbd_up = 0;
 EFI_KEYBOARD_DEVICE_PATH KeyboardDxeDevicePath =
 {
   {
     {
       HARDWARE_DEVICE_PATH,
       HW_VENDOR_DP,
       {
         (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
         (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
       }
     },
     QCOM_KEYBOARD_DEVICE_GUID
   },
   {
     END_DEVICE_PATH_TYPE,
     END_ENTIRE_DEVICE_PATH_SUBTYPE,
     {
       (UINT8) (END_DEVICE_PATH_LENGTH),
       (UINT8) ((END_DEVICE_PATH_LENGTH) >> 8)
     }
   }
 };

HidDescriptor gHidDesc;

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------

/**
  Debug function to print out buffer of size length

  @param buffer     pointer to buffer
  @param length     number of bytes in buffer to print

  @retval None
**/
VOID i2c_test_hex_dump (IN UINT8 *buffer, IN UINT32 length)
{
  UINT32 size = 0;

  DEBUG((EFI_D_INFO, "[I2CKeyboard] i2c_test_hex_dump [ENTRY] \n"));
  if (buffer == NULL){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] i2c_test_hex_dump [EXIT], buffer == NULL \n"));
    return ;
  }

  DEBUG((EFI_D_INFO, "\n"));
  for (size = 0; size < length; size++)
  {
    if (!(size & 7))
    {
      DEBUG((EFI_D_INFO, "\n"));
    }
    DEBUG((EFI_D_INFO, "%02x ", buffer[size]));
  }
  DEBUG((EFI_D_INFO, "\n\n"));
  DEBUG((EFI_D_INFO, "[I2CKeyboard] i2c_test_hex_dump [EXIT] \n"));
}

/**
  Return EFI_STATUS value for i2c_status value

  @param I2cStatus     i2c_status value

  @retval EFI_SUCCESS             I2C_SUCCESS
  @retval I2C_ERROR_INVALID_PARAMETER   I2C_ERROR_INVALID_PARAMETER
  @retval EFI_DEVICE_ERROR        any other errors
**/
EFI_STATUS
I2cStatusToEfiStatus(
  i2c_status I2cStatus
){
  EFI_STATUS Status = EFI_SUCCESS;

  // Convert from i2c_status to EFI_STATUS
  switch (I2cStatus) {
    case I2C_SUCCESS:
      Status = EFI_SUCCESS;
      break;
    case I2C_ERROR_INVALID_PARAMETER:
      Status = I2C_ERROR_INVALID_PARAMETER;
      break;
    case I2C_ERROR_UNSUPPORTED_CORE_INSTANCE:
    case I2C_ERROR_API_INVALID_EXECUTION_LEVEL:
    case I2C_ERROR_API_NOT_SUPPORTED:
    case I2C_ERROR_API_ASYNC_MODE_NOT_SUPPORTED:
    case I2C_ERROR_API_PROTOCOL_MODE_NOT_SUPPORTED:
    case I2C_ERROR_HANDLE_ALLOCATION:
    case I2C_ERROR_HW_INFO_ALLOCATION:
    case I2C_ERROR_BUS_NOT_IDLE:
    case I2C_ERROR_TRANSFER_TIMEOUT:
    case I2C_ERROR_INPUT_FIFO_OVER_RUN:
    case I2C_ERROR_OUTPUT_FIFO_UNDER_RUN:
    case I2C_ERROR_INPUT_FIFO_UNDER_RUN:
    case I2C_ERROR_OUTPUT_FIFO_OVER_RUN:
    case I2C_ERROR_COMMAND_OVER_RUN:
    case I2C_ERROR_COMMAND_ILLEGAL:
    case I2C_ERROR_COMMAND_FAIL:
    case I2C_ERROR_INVALID_CMD_OPCODE:
    case I2C_ERROR_START_STOP_UNEXPECTED:
    case I2C_ERROR_DATA_NACK:
    case I2C_ERROR_ADDR_NACK:
    case I2C_ERROR_ARBITRATION_LOST:
    case I2C_ERROR_PLATFORM_INIT_FAIL:
    case I2C_ERROR_PLATFORM_DEINIT_FAIL:
    case I2C_ERROR_PLATFORM_CRIT_SEC_FAIL:
    case I2C_ERROR_PLATFORM_SIGNAL_FAIL:
    case I2C_ERROR_PLATFORM_GET_CONFIG_FAIL:
    case I2C_ERROR_PLATFORM_GET_CLOCK_CONFIG_FAIL:
    case I2C_ERROR_PLATFORM_REG_INT_FAIL:
    case I2C_ERROR_PLATFORM_DE_REG_INT_FAIL:
    case I2C_ERROR_PLATFORM_CLOCK_ENABLE_FAIL:
    case I2C_ERROR_PLATFORM_GPIO_ENABLE_FAIL:
    case I2C_ERROR_PLATFORM_CLOCK_DISABLE_FAIL:
    case I2C_ERROR_PLATFORM_GPIO_DISABLE_FAIL:
    case I2C_TRANSFER_CANCELED:
    case I2C_TRANSFER_FORCE_TERMINATED:
    case I2C_TRANSFER_COMPLETED:
    case I2C_TRANSFER_INVALID:
    case I2C_ERROR_HANDLE_ALREADY_IN_QUEUE:
    case I2C_ERROR_DMA_REG_FAIL:
    case I2C_ERROR_DMA_EV_CHAN_ALLOC_FAIL:
    case I2C_ERROR_DMA_TX_CHAN_ALLOC_FAIL:
    case I2C_ERROR_DMA_RX_CHAN_ALLOC_FAIL:
    case I2C_ERROR_DMA_TX_CHAN_START_FAIL:
    case I2C_ERROR_DMA_RX_CHAN_START_FAIL:
    case I2C_ERROR_DMA_TX_CHAN_STOP_FAIL:
    case I2C_ERROR_DMA_RX_CHAN_STOP_FAIL:
    case I2C_ERROR_DMA_TX_CHAN_RESET_FAIL:
    case I2C_ERROR_DMA_RX_CHAN_RESET_FAIL:
    case I2C_ERROR_DMA_EV_CHAN_DE_ALLOC_FAIL:
    case I2C_ERROR_DMA_TX_CHAN_DE_ALLOC_FAIL:
    case I2C_ERROR_DMA_RX_CHAN_DE_ALLOC_FAIL:
    case I2C_ERROR_DMA_INSUFFICIENT_RESOURCES:
    case I2C_ERROR_DMA_PROCESS_TRANSFER_FAIL:
    case I2C_ERROR_DMA_EVT_OTHER:
    default:
      Status = EFI_DEVICE_ERROR;
      break;
  }
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2cStatusToEfiStatus [EXIT] Status=%d.\r\n", Status));
  return Status;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
// HID FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------
/**
  Reset the device

  @param i2c_handle             Pointer to i2c handle
  @param cfg                    Pointer to i2c config

  @retval EFI_SUCCESS             Reset completed successfully.
  @retval I2C_ERROR_INVALID_PARAMETER   I2C handle is not configured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS ResetDevice(IN VOID * i2c_handle, IN i2c_slave_config cfg)
{
  i2c_status istatus = I2C_SUCCESS;
  i2c_descriptor write_desc = {0};

  UINT8 wrBuf[4] = {LOW_BYTE(gHidDesc.wCommandRegister), HIGH_BYTE(gHidDesc.wCommandRegister), RESET_CMD_LOW, RESET_CMD_HIGH};
  UINT32 bytes_read = 0;
  UINT32 bytes_written = 0;

  DEBUG((EFI_D_INFO, "[I2CKeyboard] ResetDevice [ENTRY] \n"));
  if (i2c_handle == NULL){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] ResetDevice [EXIT], i2c_handle is null\n"));
    istatus = I2C_ERROR_INVALID_PARAMETER;
    goto error;
  }

  // set up transfer list
  write_desc.buffer = wrBuf;
  write_desc.length = 4;
  write_desc.flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  // read the report descriptor
  istatus = i2c_transfer(i2c_handle, &cfg, &write_desc, 1, NULL, NULL, 0, &bytes_read);
  if (EFI_ERROR(I2cStatusToEfiStatus(istatus)))
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] ResetDevice [EXIT],i2c_transfer failed: Status=%d.\r\n", istatus));
    goto error;
  }

  // Send enable command
  wrBuf[0] = LOW_BYTE(gHidDesc.wCommandRegister);
  wrBuf[1] = HIGH_BYTE(gHidDesc.wCommandRegister);
  wrBuf[2] = ENABLE_CMD_LOW;
  wrBuf[3] = ENABLE_CMD_HIGH;

  // set up transfer list
  write_desc.buffer = wrBuf;
  write_desc.length = 4;
  
  istatus = i2c_transfer(i2c_handle, &cfg, &write_desc, 1, NULL, NULL, 0, &bytes_written);
  if (EFI_ERROR(I2cStatusToEfiStatus(istatus)))
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] ResetDevice [EXIT],i2c_transfer failed, Status=%d.\r\n", istatus));
    goto error;
  }

  error:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] ResetDevice [EXIT] Status=%d.\r\n", istatus));
  return I2cStatusToEfiStatus(istatus);
}

/**
  Get the input report from the device

  @param i2c_handle     Pointer to i2c handle
  @param cfg            Pointer to i2c config

  @retval EFI_SUCCESS             Input report retrieval completed successfully.
  @retval I2C_ERROR_INVALID_PARAMETER   I2C handle is not configured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS GetInputReport(IN VOID * i2c_handle, IN i2c_slave_config cfg, OUT InputReport* gReportDesc)
{
  i2c_status istatus = I2C_SUCCESS;
  UINT8 rdBuf[gHidDesc.wMaxInputLength + 2];
  UINT32 bytes_read = 0;

  DEBUG((EFI_D_INFO, "[I2CKeyboard] GetInputReport [ENTRY] \n"));
  if (i2c_handle == NULL){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] GetInputReport [EXIT], i2c_handle is null\n"));
    istatus = I2C_ERROR_INVALID_PARAMETER;
    goto error;
  }

  if (gReportDesc == NULL){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] GetInputReport [EXIT], gReportDesc is null\n"));
    istatus = I2C_ERROR_INVALID_PARAMETER;
    goto error;
  }

  i2c_descriptor buffer_desc[2] = {{0}};
  buffer_desc[0].flags = I2C_FLAG_START | I2C_FLAG_WRITE;
  
  buffer_desc[1].buffer = rdBuf;
  buffer_desc[1].length = gHidDesc.wMaxInputLength + 2;
  buffer_desc[1].flags = I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP;

  // read the report descriptor
  istatus = i2c_transfer(i2c_handle, &cfg, buffer_desc, 2, NULL, NULL, 0, &bytes_read);
  if (EFI_ERROR(I2cStatusToEfiStatus(istatus)))
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] GetInputReport [EXIT], i2c_transfer Failed \n"));
    goto error;
  }
  if (bytes_read == 0){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] GetInputReport [EXIT], Did not read any bytes.\n"));
    goto error;
  }

  // if length > 0, copy report, otherwise copy zeroes
  if (rdBuf[0] != 0x0){      
    CopyMem(gReportDesc, rdBuf, sizeof(gReportDesc));
  }
  else{
    SetMem(&gReportDesc, sizeof(gReportDesc), 0);
  }

  error:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] GetInputReport [EXIT] Status=%d.\r\n", istatus));
  return I2cStatusToEfiStatus(istatus);
}

/**
  Get report descriptor from HID compliant device

  @param i2c_handle     Pointer to i2c handle
  @param cfg            Pointer to i2c config

  @retval EFI_SUCCESS             Report descriptor retrieved successfully.
  @retval I2C_ERROR_INVALID_PARAMETER   I2C handle is not confiured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS ReadReportDescriptor(IN VOID * i2c_handle, IN i2c_slave_config cfg, OUT UINT8* ReportDesc)
{
  i2c_status istatus = I2C_SUCCESS;
  UINT8 rdBuf[gHidDesc.wReportDescLength];
  UINT8 wrBuf[2] = {LOW_BYTE(gHidDesc.wReportDescRegister), HIGH_BYTE(gHidDesc.wReportDescRegister)};
  UINT32 bytes_read = 0;  
  i2c_descriptor buffer_desc[2] = {{0}};

  DEBUG((EFI_D_INFO, "[I2CKeyboard] ReadReportDescriptor [ENTRY] \n"));
  if (i2c_handle == NULL){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] ReadReportDescriptor [EXIT], i2c_handle is null\n"));
    istatus = I2C_ERROR_INVALID_PARAMETER;
    goto error;
  }

  // set up transfer list
  buffer_desc[0].buffer = wrBuf;
  buffer_desc[0].length = 2;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;
  
  buffer_desc[1].buffer = rdBuf;
  buffer_desc[1].length = gHidDesc.wReportDescLength;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP;


  // read the report descriptor
  istatus = i2c_transfer(i2c_handle, &cfg, buffer_desc, 2, NULL, NULL, 0, &bytes_read);
  if (EFI_ERROR(I2cStatusToEfiStatus(istatus)))
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] ReadReportDescriptor [EXIT], i2c_transfer Failed \n"));
    goto error;
  }

  // if length > 0, copy report, otherwise copy zeroes
  if (rdBuf[0] != 0x0){      
    CopyMem(ReportDesc, rdBuf, sizeof(ReportDesc));
  }
  error:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] ReadReportDescriptor [EXIT] Status=%d.\r\n", istatus));
  return I2cStatusToEfiStatus(istatus);
}

/**
  Parse report descriptor from HID compliant device

  @param ReportDesc     Pointer to report descriptor

  @retval EFI_SUCCESS             Report descriptor parsed successfully.
  @retval EFI_DEVICE_ERROR        Device is not valid.
**/
EFI_STATUS
ParseReportDescriptor( IN UINT8 * ReportDesc, OUT UINT8 * ReportID)
{
  UINT8 temp_report_id = 0;

  /* below values are based on HID Device Class Definition */
  UINT8 keyboard_header [4] = {0x5, 0x1, 0x9, 0x6};
  UINT8 report_id_key [1] = {0x85};

  DEBUG((EFI_D_INFO, "[I2CKeyboard] ParseReportDescriptor [ENTRY] \n"));
  // search report descriptor for Keyboard usage page
  for (int i = 0; i < gHidDesc.wReportDescLength-3; i+=2){
    if (CompareMem(ReportDesc+i, keyboard_header, 4) == 0){
      // search for report ID
      for (int j = i+4; j < gHidDesc.wReportDescLength-1; j+=2){
        if (CompareMem(ReportDesc+j, report_id_key, 1) == 0){
          temp_report_id = ReportDesc[j+1];
          CopyMem(ReportID, &temp_report_id, 1);
          return EFI_SUCCESS;
        }
      }
      DEBUG((EFI_D_WARN, "[I2CKeyboard] Could not find report ID for keyboard.\n"));
    }
  }
  DEBUG((EFI_D_INFO, "[I2CKeyboard] ParseReportDescriptor [EXIT] \n"));
  return EFI_DEVICE_ERROR;
}

/**
  Get HID descriptor from HID compliant device

  @param i2c_handle     Pointer to i2c handle
  @param cfg            Pointer to i2c config

  @retval EFI_SUCCESS             HID descriptor retrieved successfully.
  @retval I2C_ERROR_INVALID_PARAMETER   I2C handle is not configured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS ReadHidDescriptor(IN VOID * i2c_handle, IN i2c_slave_config cfg)
{
  i2c_status istatus = I2C_SUCCESS;
  UINT8 rdBuf[HID_DESC_LENGTH] = {0};
  UINT8 wdBuf[2] = {HID_DESC_ADDR_LOW, HID_DESC_ADDR_HIGH};
  UINT32 bytes_read = 0;
  i2c_descriptor buffer_desc[2] = {{0}};

  DEBUG((EFI_D_INFO, "[I2CKeyboard] ReadHidDescriptor [ENTRY] \n"));
  if (i2c_handle == NULL){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] ReadHidDescriptor [EXIT] i2c_handle is null\n"));
    istatus = I2C_ERROR_INVALID_PARAMETER;
    goto error;
  }

  // set up transfer list
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 2;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  buffer_desc[1].buffer = rdBuf;
  buffer_desc[1].length = HID_DESC_LENGTH;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP;



  // read the HID descriptor
  istatus = i2c_transfer(i2c_handle, &cfg, buffer_desc, 2, NULL, NULL, 0, &bytes_read);
  if (EFI_ERROR(I2cStatusToEfiStatus(istatus)))
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] ReadHidDescriptor [EXIT],i2c_transfer Failed \n"));
    goto error;
  }

  CopyMem(&gHidDesc, rdBuf, sizeof(gHidDesc));
  
  error:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] ReadHidDescriptor [EXIT] Status=%d.\r\n", istatus));
  return I2cStatusToEfiStatus(istatus);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
// QUEUE FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------
/**
  Check whether the EFI key buffer is empty.

  @param Queue     Pointer to instance of EFI_KEY_QUEUE.

  @retval TRUE    The EFI key buffer is empty.
  @retval FALSE   The EFI key buffer isn't empty.
**/
BOOLEAN
IsEfiKeyQueueEmpty (
  IN  EFI_KEY_QUEUE         *Queue
  )
{
  DEBUG((EFI_D_INFO, "[I2CKeyboard] IsEfiKeyQueueEmpty [ENTRY] \n"));
  ASSERT (Queue != NULL);
  DEBUG((EFI_D_INFO, "[I2CKeyboard] IsEfiKeyQueueEmpty [EXIT] \n"));
  return (BOOLEAN) (Queue->Head == Queue->Tail);
}

/**
  Read & remove one key data from the EFI key buffer.

  @param Queue     Pointer to instance of EFI_KEY_QUEUE.
  @param KeyData   Receive the key data.

  @retval EFI_SUCCESS   The key data is popped successfully.
  @retval EFI_NOT_READY There is no key data available.
**/
EFI_STATUS
PopEfiKeyQueue (
  IN  EFI_KEY_QUEUE         *Queue,
  OUT EFI_KEY_DATA          *KeyData OPTIONAL
  )
{
  DEBUG((EFI_D_INFO, "[I2CKeyboard] PopEfiKeyQueue [ENTRY] \n"));
  // Check for null input
  if (Queue == NULL){
  DEBUG((EFI_D_WARN, "[I2CKeyboard] PopEfiKeyQueue [EXIT], Queue == NULL\n"));
    return I2C_ERROR_INVALID_PARAMETER;
  }
  if (IsEfiKeyQueueEmpty (Queue)) {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] PopEfiKeyQueue [EXIT] IsEfiKeyQueueEmpty (Queue)\n"));
    return EFI_NOT_READY;
  }

  // Check for null input
  if (KeyData == NULL){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] PopEfiKeyQueue KeyData == NULL [EXIT] \n"));
    return I2C_ERROR_INVALID_PARAMETER;
  }
  //
  // Retrieve and remove the values
  //
  if (KeyData != NULL) {
    CopyMem (KeyData, &Queue->Buffer[Queue->Head], sizeof (EFI_KEY_DATA));
  }
  Queue->Head = (Queue->Head + 1) % KEYBOARD_EFI_KEY_MAX_COUNT;
  DEBUG((EFI_D_INFO, "[I2CKeyboard] PopEfiKeyQueue [EXIT] \n"));
  return EFI_SUCCESS;
}

/**
  Push one key data to the EFI key buffer.

  @param Queue     Pointer to instance of EFI_KEY_QUEUE.
  @param KeyData   The key data to push.
**/
VOID
PushEfiKeyQueue (
  IN  EFI_KEY_QUEUE         *Queue,
  IN  EFI_KEY_DATA          *KeyData
  )
{
  DEBUG((EFI_D_INFO, "[I2CKeyboard] PushEfiKeyQueue [ENTRY] \n"));
  // Check for null input
  if (Queue == NULL || KeyData == NULL){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] PushEfiKeyQueue [EXIT], (Queue == NULL || KeyData == NULL)\n"));
    return ;
  }

  if ((Queue->Tail + 1) % KEYBOARD_EFI_KEY_MAX_COUNT == Queue->Head) {
    //
    // If Queue is full, pop the one from head.
    //
    PopEfiKeyQueue (Queue, NULL);
  }
  CopyMem (&Queue->Buffer[Queue->Tail], KeyData, sizeof (EFI_KEY_DATA));
  Queue->Tail = (Queue->Tail + 1) % KEYBOARD_EFI_KEY_MAX_COUNT;
  DEBUG((EFI_D_INFO, "[I2CKeyboard] PushEfiKeyQueue [EXIT] \n"));
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
// SIMPLE TEXT INPUT PROTOCOL FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------

/**
  Resets the input device hardware.

  The Reset() function resets the input device hardware. As part
  of initialization process, the firmware/device will make a quick
  but reasonable attempt to verify that the device is functioning.
  If the ExtendedVerification flag is TRUE the firmware may take
  an extended amount of time to verify the device is operating on
  reset. Otherwise the reset operation is to occur as quickly as
  possible. The hardware verification process is not defined by
  this specification and is left up to the platform firmware or
  driver to implement.

  @param This                 A pointer to the EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL instance.

  @param ExtendedVerification Indicates that the driver may perform a more exhaustive
                              verification operation of the device during reset.

  @retval EFI_SUCCESS         The device was reset.
  @retval EFI_DEVICE_ERROR    The device is not functioning correctly and could not be reset.

**/
EFI_STATUS
EFIAPI
I2CKeyboardReset (
  IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
  IN BOOLEAN                         ExtendedVerification
  )
{
  I2C_KB_DEV *I2CKeyboardDevice = NULL;
  EFI_STATUS Status = EFI_SUCCESS;

  if (This == NULL ){
    return I2C_ERROR_INVALID_PARAMETER;
  }

  I2CKeyboardDevice = I2C_KB_DEV_FROM_THIS (This);

  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReset [ENTRY] \n"));
  if (I2CKeyboardDevice == NULL){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] I2CKeyboardReset [EXIT], I2CKeyboardDevice == NULL\n"));
    return I2C_ERROR_INVALID_PARAMETER;
  }

  if (ExtendedVerification == TRUE){
    Status = ResetDevice(I2CKeyboardDevice->I2CHandle, I2CKeyboardDevice->I2CConfig);
    if (Status != EFI_SUCCESS){
      DEBUG((EFI_D_WARN, "[I2CKeyboard] ResetDevice was unsuccessful: %d\n", Status));
      return Status;
    }    
  }

  //
  // Clear KeyCode and EfiKey Buffers
  //
  I2CKeyboardDevice->KeyCodeQueue.Head  = 0;
  I2CKeyboardDevice->KeyCodeQueue.Tail  = 0;
  I2CKeyboardDevice->EfiKeyQueue.Head   = 0;
  I2CKeyboardDevice->EfiKeyQueue.Tail   = 0;

  //
  // Reset the status indicators
  //
  I2CKeyboardDevice->CapsLock   = FALSE;
  I2CKeyboardDevice->NumLock    = FALSE;
  I2CKeyboardDevice->ScrollLock = FALSE;
  I2CKeyboardDevice->LeftCtrl   = FALSE;
  I2CKeyboardDevice->RightCtrl  = FALSE;
  I2CKeyboardDevice->LeftAlt    = FALSE;
  I2CKeyboardDevice->RightAlt   = FALSE;
  I2CKeyboardDevice->LeftShift  = FALSE;
  I2CKeyboardDevice->RightShift = FALSE;
  I2CKeyboardDevice->LeftLogo   = FALSE;
  I2CKeyboardDevice->RightLogo  = FALSE;
  I2CKeyboardDevice->Menu       = FALSE;
  I2CKeyboardDevice->SysReq     = FALSE;

  I2CKeyboardDevice->IsSupportPartialKey = FALSE;

  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReset [EXIT] Status=%d.\r\n", Status));
  return EFI_SUCCESS;
}

/**
  Internal function to read the next keystroke from the keyboard buffer.

  @param  I2CKeyboardDevice       I2C keyboard's private structure.
  @param  KeyData                 A pointer to buffer to hold the keystroke
                                  data for the key that was pressed.
  @retval EFI_SUCCESS             The keystroke information was returned.
  @retval EFI_NOT_READY           There was no keystroke data availiable.
  @retval EFI_DEVICE_ERROR        The keystroke information was not returned due to
                                  hardware errors.
  @retval I2C_ERROR_INVALID_PARAMETER   KeyData is NULL.
  @retval Others                  Fail to translate keycode into EFI_INPUT_KEY

**/
EFI_STATUS
I2CKeyboardReadKeyStrokeWorker (
  IN OUT I2C_KB_DEV                 *I2CKeyboardDevice,
     OUT EFI_KEY_DATA               *KeyData
  )
{
  EFI_STATUS                            Status;
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStrokeWorker [ENTRY] \n"));
  if (I2CKeyboardDevice == NULL || KeyData == NULL){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] I2CKeyboardReadKeyStrokeWorker [EXIT], I2CKeyboardDevice == NULL || KeyData == NULL)\n"));
    return I2C_ERROR_INVALID_PARAMETER;
  }

  if (IsEfiKeyQueueEmpty(&I2CKeyboardDevice->EfiKeyQueue)) {
    DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStrokeWorker [EXIT], (IsEfiKeyQueueEmpty(&I2CKeyboardDevice->EfiKeyQueue))\n"));
    return EFI_NOT_READY;
  }

  Status = PopEfiKeyQueue (&I2CKeyboardDevice->EfiKeyQueue, KeyData);
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStrokeWorker [EXIT] Status=%d.\r\n", Status));
  return Status;
}

/**
  Reads the next keystroke from the input device.

  @param  This                 The EFI_SIMPLE_TEXT_INPUT_PROTOCOL instance.
  @param  Key                  A pointer to a buffer that is filled in with the keystroke
                               information for the key that was pressed.

  @retval EFI_SUCCESS          The keystroke information was returned.
  @retval EFI_NOT_READY        There was no keystroke data availiable.
  @retval EFI_DEVICE_ERROR     The keystroke information was not returned due to
                               hardware errors.

**/
EFI_STATUS
EFIAPI
I2CKeyboardReadKeyStroke (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
  OUT EFI_INPUT_KEY                    *Key
  )
{
  I2C_KB_DEV   *I2CKeyboardDevice;
  EFI_STATUS   Status;
  EFI_KEY_DATA KeyData;
  
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStroke [ENTRY] \n"));
  if (This == NULL || Key == NULL){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] I2CKeyboardReadKeyStroke [EXIT], (I2CKeyboardDevice == NULL || Key == NULL)\n"));
    return I2C_ERROR_INVALID_PARAMETER;
  }

  I2CKeyboardDevice = I2C_KB_DEV_FROM_THIS (This);

  Status = I2CKeyboardReadKeyStrokeWorker (I2CKeyboardDevice, &KeyData);
  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStroke [EXIT], I2CKeyboardReadKeyStrokeWorker (I2CKeyboardDevice, &KeyData) \n"));
    return Status;
  }
  CopyMem (Key, &KeyData.Key, sizeof (EFI_INPUT_KEY));
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStroke I2CKeyboardReadKeyStrokeWorker [EXIT] \n"));
  return EFI_SUCCESS;
}

/**
  Event notification function registered for EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.WaitForKeyEx
  and EFI_SIMPLE_TEXT_INPUT_PROTOCOL.WaitForKey.

  @param  Event        Event to be signaled when a key is pressed.
  @param  Context      Points to I2C_KB_DEV instance.

**/
VOID
EFIAPI
I2CKeyboardWaitForKey (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  )
{
  I2C_KB_DEV  *I2CKeyboardDevice;
  EFI_KEY_DATA KeyData;

  I2CKeyboardDevice = (I2C_KB_DEV *) Context;
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardWaitForKey [ENTRY] \n"));
  ASSERT (I2CKeyboardDevice != NULL);

  if(!IsEfiKeyQueueEmpty (&I2CKeyboardDevice->EfiKeyQueue)) {
    CopyMem (
      &KeyData,
      &(I2CKeyboardDevice->EfiKeyQueue.Buffer[I2CKeyboardDevice->EfiKeyQueue.Head]),
      sizeof (EFI_KEY_DATA)
      );
    gBS->SignalEvent (Event);
  }
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardWaitForKey [EXIT] \n"));
}

/**
  Timer event handler: read a series of KeyCodes from I2C
  and put them into memory KeyCode buffer.
  it read as much KeyCodes to either fill
  the memory buffer or empty the keyboard buffer.

  @param Event       The timer event
  @param Context     A I2C_KB_DEV pointer

**/
VOID
EFIAPI
I2CKeyboardTimerHandler (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  I2C_KB_DEV *I2CKeyboardDevice;
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_KEY_DATA KeyData;
  InputReport gReportDesc;
  UINTN               Index;
  UINT8               Index2;
  BOOLEAN             KeyPress;
  UINT8               *CurKeyCodeBuffer;
  UINT8               *OldKeyCodeBuffer;

  uint32                  uGpio_int_Value    = 0;

  if ( is_kbd_up == 0 ) {
    DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardTimerHandler is_kbd_up is 0 \n"));
      return;
	}

  Status = TLMMProtocol->GpioIn(EFI_GPIO_CFG(I2C_KB_INT, 0, GPIO_INPUT, GPIO_PULL_UP, GPIO_8MA), &uGpio_int_Value);
  if (Status == EFI_SUCCESS) {
    // Check GPIO. if GPIO is high, I2CKeyboard hasn't KB buffer exist
    if (uGpio_int_Value == GPIO_HIGH_VALUE) {
      DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardTimerHandler [Input not from kbd] \n"));
      return ;
    }
  }

  I2CKeyboardDevice = (I2C_KB_DEV *) Context;
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardTimerHandler [ENTRY] \n"));
  ASSERT (I2CKeyboardDevice != NULL);

  SetMem(&gReportDesc, sizeof(gReportDesc), 0);
  I2CKeyboardDevice->LeftCtrl = FALSE;
  I2CKeyboardDevice->LeftShift = FALSE;
  I2CKeyboardDevice->LeftAlt = FALSE;
  I2CKeyboardDevice->LeftLogo = FALSE;
  I2CKeyboardDevice->RightCtrl = FALSE;
  I2CKeyboardDevice->RightShift = FALSE;
  I2CKeyboardDevice->RightAlt = FALSE;
  I2CKeyboardDevice->RightLogo = FALSE;
  
  Status = GetInputReport(I2CKeyboardDevice->I2CHandle, I2CKeyboardDevice->I2CConfig, &gReportDesc);
  if (Status != EFI_SUCCESS){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] I2CKeyboardTimerHandler [EXIT], GetInputReport Failed \n"));
    return ;
  }

  if (gReportDesc.length == 0x0){
    DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardTimerHandler [EXIT], gReportDesc.length is 0\n"));
    return ;
  }

  // reject any reports that do not come from our device, specified by report ID
  if (gReportDesc.reportID != I2CKeyboardDevice->ReportID){
    return ;
  }

  CurKeyCodeBuffer  = gReportDesc.Keyboard_data;
  OldKeyCodeBuffer  = I2CKeyboardDevice->LastKeyCodeArray;

  //
  // Handle normal key's pressing situation
  //
  KeyPress = FALSE;
  for (Index = 0; Index < 6; Index++) {

    if (!I2CKBD_VALID_KEYCODE (CurKeyCodeBuffer[Index])) {
      continue;
    }
    //
    // For any key in current keycode buffer, if it is not in old keycode buffer,
    // then it is pressed. Otherwise, it is not pressed.
    //
    KeyPress = TRUE;
    for (Index2 = 0; Index2 < 6; Index2++) {

      if (!I2CKBD_VALID_KEYCODE (OldKeyCodeBuffer[Index2])) {
        continue;
      }

      if (CurKeyCodeBuffer[Index] == OldKeyCodeBuffer[Index2]) {
        KeyPress = FALSE;
        break;
      }
    }

    if (KeyPress) {
      if (gReportDesc.KeyboardLeftControl == 0x1){
        I2CKeyboardDevice->LeftCtrl = TRUE;
      }
      if (gReportDesc.KeyboardLeftShift == 0x1){
        I2CKeyboardDevice->LeftShift = TRUE;
      }
      if (gReportDesc.KeyboardLeftAlt == 0x1){
        I2CKeyboardDevice->LeftAlt = TRUE;
      }
      if (gReportDesc.KeyboardLeftGui == 0x1){
        I2CKeyboardDevice->LeftLogo = TRUE;
      }
      if (gReportDesc.KeyboardRightControl == 0x1){
        I2CKeyboardDevice->RightCtrl = TRUE;
      }
      if (gReportDesc.KeyboardRightShift == 0x1){
        I2CKeyboardDevice->RightShift = TRUE;
      }
      if (gReportDesc.KeyboardRightAlt == 0x1){
        I2CKeyboardDevice->RightAlt = TRUE;
      }
      if (gReportDesc.KeyboardRightGui == 0x1){
        I2CKeyboardDevice->RightLogo = TRUE;
      }

      //
      // Translate saved keycode into EFI_INPUT_KEY
      //
      Status = KeyCodeToEfiInputKey (I2CKeyboardDevice, CurKeyCodeBuffer[Index], &KeyData);
      if (EFI_ERROR (Status)) {
        DEBUG((EFI_D_WARN, "[I2CKeyboard] I2CKeyboardTimerHandler [EXIT], KeyCodeToEfiInputKey Failed \n"));
        return ;
      }
      PushEfiKeyQueue (&I2CKeyboardDevice->EfiKeyQueue, &KeyData);
    }
  }

  //
  // Update LastKeycodeArray buffer in the I2CKeyboardDevice data structure.
  //
  for (Index = 0; Index < 6; Index++) {
    I2CKeyboardDevice->LastKeyCodeArray[Index] = CurKeyCodeBuffer[Index];
  }
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardTimerHandler [EXIT] \n"));
}

/**
  Free the waiting key notify list.

  @param ListHead  Pointer to list head

  @retval I2C_ERROR_INVALID_PARAMETER  ListHead is NULL
  @retval EFI_SUCCESS            Sucess to free NotifyList
**/
EFI_STATUS
KbdFreeNotifyList (
  IN OUT LIST_ENTRY           *ListHead
  )
{
  KEYBOARD_CONSOLE_IN_EX_NOTIFY *NotifyNode;

  if (ListHead == NULL) {
    return I2C_ERROR_INVALID_PARAMETER;
  }
  while (!IsListEmpty (ListHead)) {
    NotifyNode = CR (
                   ListHead->ForwardLink,
                   KEYBOARD_CONSOLE_IN_EX_NOTIFY,
                   NotifyEntry,
                   I2C_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE
                   );
    RemoveEntryList (ListHead->ForwardLink);
    gBS->FreePool (NotifyNode);
  }

  return EFI_SUCCESS;
}

/**
  Check whether the pressed key matches a registered key or not.

  @param  RegsiteredData    A pointer to keystroke data for the key that was registered.
  @param  InputData         A pointer to keystroke data for the key that was pressed.

  @retval TRUE              Key pressed matches a registered key.
  @retval FLASE             Key pressed does not matches a registered key.

**/
BOOLEAN
IsKeyRegistered (
  IN EFI_KEY_DATA  *RegisteredData,
  IN EFI_KEY_DATA  *InputData
  )
{
  ASSERT (RegisteredData != NULL && InputData != NULL);

  if ((RegisteredData->Key.ScanCode    != InputData->Key.ScanCode) ||
      (RegisteredData->Key.UnicodeChar != InputData->Key.UnicodeChar)) {
    return FALSE;
  }

  //
  // Assume KeyShiftState/KeyToggleState = 0 in Registered key data means these state could be ignored.
  //
  if (RegisteredData->KeyState.KeyShiftState != 0 &&
      RegisteredData->KeyState.KeyShiftState != InputData->KeyState.KeyShiftState) {
    return FALSE;
  }
  if (RegisteredData->KeyState.KeyToggleState != 0 &&
      RegisteredData->KeyState.KeyToggleState != InputData->KeyState.KeyToggleState) {
    return FALSE;
  }

  return TRUE;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
// SIMPLE TEXT INPUT EX PROTOCOL FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------

/**
  Resets the input device hardware.

  The Reset() function resets the input device hardware. As part
  of initialization process, the firmware/device will make a quick
  but reasonable attempt to verify that the device is functioning.
  If the ExtendedVerification flag is TRUE the firmware may take
  an extended amount of time to verify the device is operating on
  reset. Otherwise the reset operation is to occur as quickly as
  possible. The hardware verification process is not defined by
  this specification and is left up to the platform firmware or
  driver to implement.

  @param This                 A pointer to the EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL instance.

  @param ExtendedVerification Indicates that the driver may perform a more exhaustive
                              verification operation of the device during reset.

  @retval EFI_SUCCESS         The device was reset.
  @retval EFI_DEVICE_ERROR    The device is not functioning correctly and could not be reset.

**/
EFI_STATUS
EFIAPI
I2CKeyboardResetEx (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN BOOLEAN                            ExtendedVerification
  )
{
  EFI_STATUS                Status;
  I2C_KB_DEV                *I2CKeyboardDevice;

  if (This == NULL ){
    DEBUG((EFI_D_WARN, "[I2CKeyboard] I2CKeyboardResetEx This == NULL)\n"));
    return I2C_ERROR_INVALID_PARAMETER;
  }

  I2CKeyboardDevice = TEXT_INPUT_EX_I2C_KB_DEV_FROM_THIS (This);
  if (I2CKeyboardDevice == NULL){
    return I2C_ERROR_INVALID_PARAMETER;
  }

  Status = I2CKeyboardDevice->SimpleInput.Reset (&I2CKeyboardDevice->SimpleInput, ExtendedVerification);
  
  return Status;
}

/**
  Reads the next keystroke from the input device.

  @param  This                   Protocol instance pointer.
  @param  KeyData                A pointer to a buffer that is filled in with the keystroke
                                 state data for the key that was pressed.

  @retval EFI_SUCCESS            The keystroke information was returned.
  @retval EFI_NOT_READY          There was no keystroke data available.
  @retval EFI_DEVICE_ERROR       The keystroke information was not returned due to
                                 hardware errors.
  @retval I2C_ERROR_INVALID_PARAMETER  KeyData is NULL.

**/
EFI_STATUS
EFIAPI
I2CKeyboardReadKeyStrokeEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
  OUT EFI_KEY_DATA                      *KeyData
  )
{
  I2C_KB_DEV                        *I2CKeyboardDevice;

  if (This == NULL || KeyData == NULL){
    return I2C_ERROR_INVALID_PARAMETER;
  }
  
  I2CKeyboardDevice = TEXT_INPUT_EX_I2C_KB_DEV_FROM_THIS (This);

  return I2CKeyboardReadKeyStrokeWorker (I2CKeyboardDevice, KeyData);
}

/**
  Set certain state for the input device.

  @param  This                    Protocol instance pointer.
  @param  KeyToggleState          A pointer to the EFI_KEY_TOGGLE_STATE to set the
                                  state for the input device.

  @retval EFI_SUCCESS             The device state was set appropriately.
  @retval EFI_DEVICE_ERROR        The device is not functioning correctly and could
                                  not have the setting adjusted.
  @retval EFI_UNSUPPORTED         The device does not support the ability to have its state set.
  @retval I2C_ERROR_INVALID_PARAMETER   KeyToggleState is NULL.

**/
EFI_STATUS
EFIAPI
I2CKeyboardSetState (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN EFI_KEY_TOGGLE_STATE               *KeyToggleState
  )
{
  I2C_KB_DEV                            *I2CKeyboardDevice;
  EFI_STATUS                            Status = EFI_SUCCESS;

  if (This == NULL || KeyToggleState == NULL){
    return I2C_ERROR_INVALID_PARAMETER;
  }

  I2CKeyboardDevice = TEXT_INPUT_EX_I2C_KB_DEV_FROM_THIS (This);

  if ((*KeyToggleState & EFI_TOGGLE_STATE_VALID) != EFI_TOGGLE_STATE_VALID) {
    Status = EFI_UNSUPPORTED;
    goto Exit;
  }

  I2CKeyboardDevice->ScrollLock   = FALSE;
  I2CKeyboardDevice->NumLock  = FALSE;
  I2CKeyboardDevice->CapsLock     = FALSE;
  I2CKeyboardDevice->IsSupportPartialKey = FALSE;

  if ((*KeyToggleState & EFI_SCROLL_LOCK_ACTIVE) == EFI_SCROLL_LOCK_ACTIVE) {
    I2CKeyboardDevice->ScrollLock = TRUE;
  }
  if ((*KeyToggleState & EFI_NUM_LOCK_ACTIVE) == EFI_NUM_LOCK_ACTIVE) {
    I2CKeyboardDevice->NumLock = TRUE;
  }
  if ((*KeyToggleState & EFI_CAPS_LOCK_ACTIVE) == EFI_CAPS_LOCK_ACTIVE) {
    I2CKeyboardDevice->CapsLock = TRUE;
  }
  if ((*KeyToggleState & EFI_KEY_STATE_EXPOSED) == EFI_KEY_STATE_EXPOSED) {
    I2CKeyboardDevice->IsSupportPartialKey = TRUE;
  }

  if (EFI_ERROR (Status)) {
    Status = EFI_DEVICE_ERROR;
  }

Exit:
  return Status;
}

/**
  Register a notification function for a particular keystroke for the input device.

  @param  This                        Protocol instance pointer.
  @param  KeyData                     A pointer to a buffer that is filled in with the keystroke
                                      information data for the key that was pressed.
  @param  KeyNotificationFunction     Points to the function to be called when the key
                                      sequence is typed specified by KeyData.
  @param  NotifyHandle                Points to the unique handle assigned to the registered notification.

  @retval EFI_SUCCESS                 The notification function was registered successfully.
  @retval EFI_OUT_OF_RESOURCES        Unable to allocate resources for necessary data structures.
  @retval I2C_ERROR_INVALID_PARAMETER       KeyData or NotifyHandle or KeyNotificationFunction is NULL.

**/
EFI_STATUS
EFIAPI
I2CKeyboardRegisterKeyNotify (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN  EFI_KEY_DATA                       *KeyData,
  IN  EFI_KEY_NOTIFY_FUNCTION            KeyNotificationFunction,
  OUT VOID                               **NotifyHandle
  )
{
  EFI_STATUS                            Status;
  I2C_KB_DEV                        *I2CKeyboardDevice;
  LIST_ENTRY                            *Link;
  KEYBOARD_CONSOLE_IN_EX_NOTIFY     *CurrentNotify;
  KEYBOARD_CONSOLE_IN_EX_NOTIFY     *NewNotify;

  if (KeyData == NULL || NotifyHandle == NULL || KeyNotificationFunction == NULL || This == NULL) {
    return I2C_ERROR_INVALID_PARAMETER;
  }

  I2CKeyboardDevice = TEXT_INPUT_EX_I2C_KB_DEV_FROM_THIS (This);
  //
  // Return EFI_SUCCESS if the (KeyData, NotificationFunction) is already registered.
  //
  for (Link = I2CKeyboardDevice->NotifyList.ForwardLink; Link != &I2CKeyboardDevice->NotifyList; Link = Link->ForwardLink) {
    CurrentNotify = CR (
                      Link,
                      KEYBOARD_CONSOLE_IN_EX_NOTIFY,
                      NotifyEntry,
                      I2C_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE
                      );
    if (IsKeyRegistered (&CurrentNotify->KeyData, KeyData)) {
      if (CurrentNotify->KeyNotificationFn == KeyNotificationFunction) {
        *NotifyHandle = CurrentNotify;
        Status = EFI_SUCCESS;
        goto Exit;
      }
    }
  }

 //
  // Allocate resource to save the notification function
  //
  NewNotify = (KEYBOARD_CONSOLE_IN_EX_NOTIFY *) AllocateZeroPool (sizeof (KEYBOARD_CONSOLE_IN_EX_NOTIFY));
  if (NewNotify == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  NewNotify->Signature         = I2C_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE;
  NewNotify->KeyNotificationFn = KeyNotificationFunction;
  CopyMem (&NewNotify->KeyData, KeyData, sizeof (EFI_KEY_DATA));
  InsertTailList (&I2CKeyboardDevice->NotifyList, &NewNotify->NotifyEntry);

  *NotifyHandle                = NewNotify;
  Status                       = EFI_SUCCESS;

Exit:
  return Status;
}

/**
  Remove a registered notification function from a particular keystroke.

  @param  This                      Protocol instance pointer.
  @param  NotificationHandle        The handle of the notification function being unregistered.

  @retval EFI_SUCCESS              The notification function was unregistered successfully.
  @retval I2C_ERROR_INVALID_PARAMETER    The NotificationHandle is invalid

**/
EFI_STATUS
EFIAPI
I2CKeyboardUnregisterKeyNotify (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN VOID                         *NotificationHandle
  )
{
  EFI_STATUS                            Status;
  I2C_KB_DEV                            *I2CKeyboardDevice;
  LIST_ENTRY                            *Link;
  KEYBOARD_CONSOLE_IN_EX_NOTIFY         *CurrentNotify;

  if (This == NULL || NotificationHandle == NULL){
    return I2C_ERROR_INVALID_PARAMETER;
  }
  
  I2CKeyboardDevice = TEXT_INPUT_EX_I2C_KB_DEV_FROM_THIS (This);
  
  for (Link = I2CKeyboardDevice->NotifyList.ForwardLink; Link != &I2CKeyboardDevice->NotifyList; Link = Link->ForwardLink) {
    CurrentNotify = CR (
                      Link,
                      KEYBOARD_CONSOLE_IN_EX_NOTIFY,
                      NotifyEntry,
                      I2C_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE
                      );
    if (CurrentNotify == NotificationHandle) {
      //
      // Remove the notification function from NotifyList and free resources
      //
      RemoveEntryList (&CurrentNotify->NotifyEntry);

      gBS->FreePool (CurrentNotify);
      Status = EFI_SUCCESS;
      goto Exit;
    }
  }

  //
  // Can not find the specified Notification Handle
  //
  Status = I2C_ERROR_INVALID_PARAMETER;
Exit:
  return Status;
}

/**
  Keyboard Init function for I2C keyboard initialization.

  @param Event       The timer event
  @param Context     EFI_HANDLE

**/

VOID
EFIAPI
I2CKeyboardInit (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
     EFI_STATUS        Status = EFI_SUCCESS;
     i2c_slave_config  cfg;
     VOID              *I2CHandle = NULL;
     UINT8             ReportID = 0;
     UINT8             ReportDesc [gHidDesc.wReportDescLength+1];
     KBD_INIT_CONFIG   *kbd_config = NULL;
     EFI_HANDLE        ImageHandle = NULL;

     kbd_config = (KBD_INIT_CONFIG *) Context;
     cfg.bus_frequency_khz = I2C_DEFAULT_BUS_FREQ;
     cfg.slave_address = I2C_SLAVE_ADDR;
     
     cfg.mode = I2C;
     cfg.slave_max_clock_stretch_us = I2C_SLAVE_MAX_CLOCK_STRETCH_US;
     cfg.core_configuration1 = 0;
     cfg.core_configuration2 = 0;     
     I2CHandle = kbd_config->I2CHandle;
     ImageHandle = ( EFI_HANDLE *) (kbd_config->ImageHandle);

     Status = ReadHidDescriptor(I2CHandle, cfg);
     if (Status != EFI_SUCCESS){
       DEBUG((EFI_D_ERROR, "[I2CKeyboard] ReadHidDescriptor was unsuccessful: %d\n", Status));
       goto ErrorExit1;
     }

     Status = ReadReportDescriptor(I2CHandle, cfg, ReportDesc);
     if (Status != EFI_SUCCESS){
       DEBUG((EFI_D_ERROR, "[I2CKeyboard] ReadReportDescriptor was unsuccessful: %d\n", Status));
       goto ErrorExit1;
     }

    Status = ParseReportDescriptor(ReportDesc, &ReportID);
    if (Status != EFI_SUCCESS){
      DEBUG((EFI_D_ERROR, "[I2CKeyboard] ParseReportDescriptor was unsuccessful: %d\n", Status));
      goto ErrorExit1;
    }

    kbd_config->kbddevice.ReportID = ReportID;

    ZeroMem (kbd_config->kbddevice.LastKeyCodeArray, sizeof (UINT8) * 6);

    InitializeListHead (&kbd_config->kbddevice.NotifyList);

    //
    // Reset Keyboard Device exhaustively.
    //
    Status = kbd_config->kbddevice.SimpleInputEx.Reset (
                                              &kbd_config->kbddevice.SimpleInputEx,
                                              TRUE
                                              );
    if (EFI_ERROR (Status)) {
      gBS->UninstallMultipleProtocolInterfaces (
             kbd_config->ImageHandle,
             &gEfiSimpleTextInProtocolGuid,
             &kbd_config->kbddevice.SimpleInput,
             &gEfiSimpleTextInputExProtocolGuid,
             &kbd_config->kbddevice.SimpleInputEx,
             &gEfiDevicePathProtocolGuid,
             &KeyboardDxeDevicePath,
             NULL
             );
      DEBUG((EFI_D_WARN, "[I2CKeyboard] %a Exit REset failed \r\n", __FUNCTION__));
      goto ErrorExit1;
    }
    is_kbd_up = 1;
ErrorExit1:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] %a Exit \r\n", __FUNCTION__));
  gBS->CloseEvent (Event ); 
  }
  
EFI_STATUS 
InitKybdPamClient(VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;
  npa_client_handle reqClient = NULL;
  npa_query_type    query_result;
  npa_query_status  query_status = NPA_QUERY_NO_VALUE;
  
  // Query PMIC_NPA_GROUP_ID_KYPD client before getting handle
  query_status = npa_query_by_name(PMIC_NPA_GROUP_ID_KYPD, NPA_QUERY_CURRENT_STATE, &query_result);
  
  if (NPA_QUERY_SUCCESS == query_status)
  {
    reqClient =  npa_create_sync_client(
                   PMIC_NPA_GROUP_ID_KYPD,
                   "keypad",
                   NPA_CLIENT_REQUIRED); 
    
    if (NULL == reqClient)
    {
      DEBUG((EFI_D_ERROR, "[I2CKeyboard] %a Failed to retrieve NPA keypad Handle \r\n", __FUNCTION__));
      return EFI_DEVICE_ERROR;
    }

    // Once the client is valid, we can issue activate request.
    npa_issue_required_request(reqClient, PMIC_NPA_MODE_ID_GENERIC_ACTIVE );
  }
  else
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] %a Keyboard PAM client Query Resource by Name Failed query_status = (%d)\r\n", __FUNCTION__, query_status));
    return EFI_DEVICE_ERROR;
  }
  return Status;
}

/* I2CKBGetChargerPowerStatus */
EFI_STATUS I2CKBGetChargerPowerStatus(void)
{
  EFI_STATUS                Status            = EFI_SUCCESS;
  BOOLEAN                   bOffModeCharging   = FALSE;
  EFI_CHARGER_EX_PROTOCOL   *ChargerExProtocol = NULL;

  Status = gBS->LocateProtocol(&gChargerExProtocolGuid,
                                NULL,
                                (void**)&ChargerExProtocol);

  if ((ChargerExProtocol != NULL && ChargerExProtocol->IsOffModeCharging != NULL) &&
      ((EFI_SUCCESS != Status)                                                 ||
      (EFI_SUCCESS != ChargerExProtocol->IsOffModeCharging(&bOffModeCharging))))
  {
    // Unable to locate charger protocol, just continue with power okay status
    Status = EFI_SUCCESS;  
    DEBUG ((EFI_D_ERROR, "%a: ChargerExProtocol = 0x%x,  bOffModeCharging = %d\r\n", __func__, *ChargerExProtocol, bOffModeCharging));
  }
  else if (TRUE  == bOffModeCharging)
  {
    // off mode charging
    Status = EFI_OUT_OF_RESOURCES;
  }
  else
  {
    // Charger power status is ok
    Status = EFI_SUCCESS;
  }

  return Status;
}

/**
  Entrypoint of I2C Keyboard Driver.

  This function is the entrypoint of I2C Keyboard Driver.
  This function produces Simple Text Input Protocol and Simple Text Input Ex Protocol,
  initializes the keyboard device, and submit Asynchronous Interrupt Transfer to manage
  this keyboard device.

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
I2CKeyboardEntryPoint(
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PLATFORMINFO_PLATFORM_TYPE PlatformType;
  EFI_EVENT   TimerEvent = NULL;
  KBD_INIT_CONFIG *i2c_kbd_config = NULL;
  EFI_EVENT         WaitForKeyEvent;
  UINT8             ReportID = 0;

  i2c_slave_config cfg;
  cfg.bus_frequency_khz = I2C_DEFAULT_BUS_FREQ;
  cfg.slave_address = I2C_SLAVE_ADDR;
  
  cfg.mode = I2C;
  cfg.slave_max_clock_stretch_us = I2C_SLAVE_MAX_CLOCK_STRETCH_US;
  cfg.core_configuration1 = 0;
  cfg.core_configuration2 = 0; 

  // Load the driver if Platform is QRD
  Status = GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }
  if(( (EFI_PLATFORMINFO_TYPE_QRD != PlatformType)))
  {
    return EFI_UNSUPPORTED;
  }
  
  //Check power status
  Status = I2CKBGetChargerPowerStatus();
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] %a in off mode charging. Exiting. \r\n", __FUNCTION__));
    return Status;
  }
  
  //
  // Allocate private data
  //
  i2c_kbd_config = AllocateZeroPool (sizeof (KBD_INIT_CONFIG));
  if (i2c_kbd_config == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ErrorExit;
  }
  
  i2c_kbd_config->ImageHandle = ImageHandle;
  
  /* Initialize the I2C Core  */
  i2c_status istatus = I2C_SUCCESS;
  istatus = i2c_open((i2c_instance)(I2C_INSTANCE_022), &(i2c_kbd_config->I2CHandle));
  if (I2C_SUCCESS != istatus)
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] Failed to initialize I2C. Error = %d\n", istatus));
    goto ErrorExit;
  }
  
  //Init pmic GPIO
  EFI_QCOM_PMIC_GPIO_PROTOCOL *PmicGPIOProtocol = NULL;
  
  Status = gBS->LocateProtocol(&gQcomPmicGpioProtocolGuid,
          NULL,
          (VOID **)&PmicGPIOProtocol);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a: locate PMIC GPIO protocol failed\r\n", __func__));
    return Status;
  }
  

  Status = PmicGPIOProtocol->CfgMode(PMIC_B, EFI_PM_GPIO_1, EFI_PM_GPIO_DIG_OUT);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a: setting GPIO cfgmode failed\r\n", __func__));
    return Status;
  }

  Status = PmicGPIOProtocol->SetVoltageSource(PMIC_B, EFI_PM_GPIO_1, EFI_PM_GPIO_VIN1);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a: setting GPIO voltage source failed\r\n", __func__));
    return Status;
  }

  Status = PmicGPIOProtocol->SetOutBufCfg(PMIC_B, EFI_PM_GPIO_1, EFI_PM_GPIO_OUT_BUF_CFG_CMOS);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a: setting GPIO out bufcfg failed\r\n", __func__));
    return Status;
  }

  Status = PmicGPIOProtocol->SetOutDrvStr(PMIC_B, EFI_PM_GPIO_1, EFI_PM_GPIO_OUT_DRV_STR_MEDIUM);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a: setting GPIO outdrv failed\r\n", __func__));
    return Status;
  }

  Status = PmicGPIOProtocol->Enable(PMIC_B, EFI_PM_GPIO_1, TRUE);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a: setting GPIO to enable failed\r\n", __func__));
    return Status;
  }
  
  Status = PmicGPIOProtocol->SetOutputLevel(PMIC_B, EFI_PM_GPIO_1, EFI_PM_GPIO_LEVEL_HIGH);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a: setting output value failed\r\n", __func__));
    return Status;
  }
  
  InitKybdPamClient();
  
  //
  // Initialize TLMM
  //
  EFI_TLMM_PROTOCOL *gTLMMProtocol = NULL;
  Status = gBS->LocateProtocol( &gEfiTLMMProtocolGuid, NULL, (void**)&gTLMMProtocol);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_WARN, "[I2CKeyboard] %a: LocateProtocol gEfiTLMMProtocolGuid Protocol failed 0x%x\r\n", __FUNCTION__, Status));
    goto ErrorExit1;
  }
     
  // Configure nINT so it can be read later
  Status = gTLMMProtocol->ConfigGpio(TLMM_GPIO_KBD, TLMM_GPIO_ENABLE);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_WARN, "[I2CKeyboard] failed to enable TLMM_GPIO_KBD pin 0x%x\r\n", Status));
    Status = EFI_UNSUPPORTED;
    goto ErrorExit1;
  }

     
    //
    // Setup the device instance
    //
    i2c_kbd_config->kbddevice.Signature                 = I2C_KB_DEV_SIGNATURE;
    i2c_kbd_config->kbddevice.ReportID                          = ReportID;
    i2c_kbd_config->kbddevice.I2CHandle                         = i2c_kbd_config->I2CHandle;
    i2c_kbd_config->kbddevice.I2CConfig                         = cfg;
    (i2c_kbd_config->kbddevice.SimpleInput).Reset               = I2CKeyboardReset;
    (i2c_kbd_config->kbddevice.SimpleInput).ReadKeyStroke       = I2CKeyboardReadKeyStroke;

    (i2c_kbd_config->kbddevice.SimpleInputEx).Reset               = I2CKeyboardResetEx;
    (i2c_kbd_config->kbddevice.SimpleInputEx).ReadKeyStrokeEx     = I2CKeyboardReadKeyStrokeEx;
    (i2c_kbd_config->kbddevice.SimpleInputEx).SetState            = I2CKeyboardSetState;
    (i2c_kbd_config->kbddevice.SimpleInputEx).RegisterKeyNotify   = I2CKeyboardRegisterKeyNotify;
    (i2c_kbd_config->kbddevice.SimpleInputEx).UnregisterKeyNotify = I2CKeyboardUnregisterKeyNotify;

    ZeroMem (i2c_kbd_config->kbddevice.LastKeyCodeArray, sizeof (UINT8) * 6);

    InitializeListHead (&i2c_kbd_config->kbddevice.NotifyList);

    Status = gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void **)&TLMMProtocol);
    if (EFI_ERROR (Status)) {
      DEBUG((EFI_D_WARN, "[I2CKeyboard] Failed to LocateProtocol TLMMProtocol.\n"));
      goto ErrorExit;
    }

    if (TLMMProtocol == NULL) {
      DEBUG ((EFI_D_WARN, "[I2CKeyboard] Error locating TLMM protocol %x\r\n", Status));
      Status = EFI_UNSUPPORTED;
      goto ErrorExit;
    }

    //
    // Setup a periodic timer, used for reading keystrokes at a fixed interval
    //
    Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  I2CKeyboardTimerHandler,
                  &i2c_kbd_config->kbddevice,
                  &i2c_kbd_config->kbddevice.TimerEvent
                  );
    if (!EFI_ERROR (Status)) {
      Status = gBS->SetTimer (i2c_kbd_config->kbddevice.TimerEvent, TimerPeriodic, KEYBOARD_TIMER_INTERVAL);
    }
    else {
      DEBUG((EFI_D_WARN, "[I2CKeyboard] Error setting up Timer %d\n", Status));
      goto ErrorExit;
    }

    //
    // Setup the WaitForKey event
    //
    // The callback will be called anytime something is waiting on 'WaitForKey'
    // and the event is not signalled.
    Status = gBS->CreateEvent (
                      EVT_NOTIFY_WAIT,
                      TPL_CALLBACK,
                      I2CKeyboardWaitForKey,
                      &i2c_kbd_config->kbddevice,
                      &WaitForKeyEvent
                      );
    if (EFI_ERROR (Status)) {
      DEBUG((EFI_D_WARN, "[I2CKeyboard] Error setting up WaitForKey %d\n", Status));
      goto ErrorExit;
    }

    i2c_kbd_config->kbddevice.SimpleInput.WaitForKey = WaitForKeyEvent;
    i2c_kbd_config->kbddevice.SimpleInputEx.WaitForKeyEx = WaitForKeyEvent;

    //
    // Install protocol interfaces for the keyboard device.
    //
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &(i2c_kbd_config->ImageHandle),
                    &gEfiSimpleTextInProtocolGuid,
                    &i2c_kbd_config->kbddevice.SimpleInput,
                    &gEfiSimpleTextInputExProtocolGuid,
                    &i2c_kbd_config->kbddevice.SimpleInputEx,
                    &gEfiDevicePathProtocolGuid,
                    &KeyboardDxeDevicePath,
                    NULL
                    );
    if (EFI_ERROR (Status)) {
      DEBUG((EFI_D_WARN, "[I2CKeyboard] Error installing simpletext protocol %d\n", Status));
      goto ErrorExit;
    }

  Status = gBS->CreateEvent (
                EVT_TIMER | EVT_NOTIFY_SIGNAL,
                TPL_CALLBACK,
                I2CKeyboardInit,
                i2c_kbd_config,
                &TimerEvent
                );

  if (!EFI_ERROR (Status)) {
    Status = gBS->SetTimer (TimerEvent, TimerPeriodic, (GPIO_INIT_INTERVAL));
  }
  else {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] Error setting up Timer %d\n", Status));
    goto ErrorExit;
  }
    goto ErrorExit1;

  //
  // Error handler
  //
  ErrorExit:
    //
    // Report error code
    //
    if (Status != EFI_SUCCESS) {
      DEBUG((EFI_D_WARN, "[I2CKeyboard] Error starting keyboard %d\n", Status));
    }
    if(i2c_kbd_config)
    {
      if ((&(i2c_kbd_config->kbddevice) != NULL) && (i2c_kbd_config->kbddevice.SimpleInput.WaitForKey != NULL)) {
        gBS->CloseEvent (i2c_kbd_config->kbddevice.SimpleInput.WaitForKey);
      }
      if ((&(i2c_kbd_config->kbddevice) != NULL) && (i2c_kbd_config->kbddevice.TimerEvent != NULL)) {
        gBS->CloseEvent (i2c_kbd_config->kbddevice.TimerEvent);
      }
      if ((&(i2c_kbd_config->kbddevice) != NULL) && (i2c_kbd_config->kbddevice.SimpleInputEx.WaitForKeyEx != NULL)) {
        gBS->CloseEvent (i2c_kbd_config->kbddevice.SimpleInputEx.WaitForKeyEx);
      }
    }
    KbdFreeNotifyList (&i2c_kbd_config->kbddevice.NotifyList);

    if (&i2c_kbd_config->kbddevice != NULL) {
      gBS->FreePool (&i2c_kbd_config->kbddevice);
    }

ErrorExit1:
  DEBUG((EFI_D_INFO, "[I2CKeyboard]  %a Exit \r\n", __FUNCTION__));
  return Status;
}