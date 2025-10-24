/** 
  @file  EFIHSUart.h
  @brief HSUart UEFI Protocol definitions.
*/
/*=============================================================================
  Copyright (c) 2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 1/18/22    JJ      Initial Version

=============================================================================*/

#ifndef __EFIHSUART_H__
#define __EFIHSUART_H__

/** @defgroup efi_hs_uart_protocol EFI_HS_UART_PROTOCOL
 *  @ingroup INTERFACES 
 */
 /** @defgroup  efi_hs_uart_protocol_prot PROTOCOL
 *  @ingroup efi_hs_uart_protocol 
 */ 
 /** @defgroup  efi_hs_uart_protocol_apis APIs
 *  @ingroup efi_hs_uart_protocol 
 */ 

/** @defgroup  efi_hs_uart_protocol_data DATA_STRUCTURES
 *  @ingroup efi_hs_uart_protocol 
 */

/** @ingroup efi_hs_uart_protocol_data
  Protocol version. 
*/
#define HSUART_DXE_REVISION 0x00010006

/** @ingroup efi_hs_uart_protocol_data
  HS-UART UEFI typedefs
*/
typedef struct _EFI_QCOM_HSUART_PROTOCOL   EFI_QCOM_HSUART_PROTOCOL;
/** @endcond */

/*  HS-UART UEFI Procotol GUID */
/** @ingroup efi_hs_uart_protocol_data */
extern EFI_GUID gQcomHSUartProtocolGuid;

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* OPEN */ 
/** @ingroup efi_hs_uart_protocol_apis
  @par Summary
  This function is called by the client code to initialize the respective 
  HS-UART core instance used by the client.
  
*/
typedef
RETURN_STATUS
(EFIAPI *OPEN) (
    void
);

/* READ */
/** @ingroup efi_hs_uart_protocol_apis
  @par Summary
  Performs an hsuart read.

  @param[out] buffer                Buffer into which data is read.
  @param[in]  buffer_len            Length of data that needs to be read.
                                    the slave.
  @return 
  Actual bytes read
*/
typedef
UINTN
(EFIAPI *READ) (
    OUT UINT8 *user_buffer,
    IN UINTN bytes_requested
);

/* WRITE */
/** @ingroup efi_hs_uart_protocol_apis
  @par Summary
  Performs an hsuart write.

  @param[out] buffer                Buffer from which data is written.
  @param[in]  buffer_len            Length of data that needs to be written.
                                    the slave.

  @return 
  Actual bytes written
*/
typedef
UINTN
(EFIAPI *WRITE) (
    IN UINT8 *user_buffer,
    IN UINTN bytes_to_send
);

/* POLL */
/** @ingroup efi_hs_uart_protocol_apis
  @par Summary
  Polls for RX Watermark

  @return 
  Boolean TRUE if watermark set and vice versa.
*/
typedef
BOOLEAN
(EFIAPI *POLL) (
    void
);

/* CLOSE */ 
/** @ingroup efi_hs_uart_protocol_apis
  @par Summary
  This function is called by the client code to de-initialize the respective 
  HS-UART core instance used by the client.
  
*/
typedef
RETURN_STATUS
(EFIAPI *CLOSE) (
    void
);

/* SETBAUD */
/** @ingroup efi_hs_uart_protocol_apis
  @par Summary
  This function is called by the client code to de-initialize the respective
  HS-UART core instance used by the client.

*/
typedef
RETURN_STATUS
(EFIAPI *SETBAUD) (
    IN UINTN baud_rate
);
/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_hs_uart_protocol_prot
  @par Summary
  Qualcomm HS-UART Protocol interface.

  @par Parameters
  @inputprotoparams{hsuart_proto_params.tex} 
*/
struct _EFI_QCOM_HSUART_PROTOCOL {
  UINT64        Revision;
  OPEN          open;
  READ          read;
  WRITE         write;
  POLL          poll;
  CLOSE         close;
  SETBAUD       set_baudrate;
};

#endif	/* __EFIHSUART_H__ */
