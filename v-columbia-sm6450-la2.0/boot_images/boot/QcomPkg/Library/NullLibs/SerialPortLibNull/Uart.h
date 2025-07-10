#ifndef __UART_H__
#define __UART_H__
/*==================================================================================================

FILE: Uart.h

DESCRIPTION: UEFI driver for UARTDM/UARTBAM

==================================================================================================*/

/**
  Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/16/21   ck      Added edit history and copyright

=============================================================================*/

/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/

RETURN_STATUS EFIAPI uart_initialize(void);
BOOLEAN       EFIAPI uart_poll(void);
UINTN         EFIAPI uart_read(OUT UINT8 *user_buffer, IN UINTN bytes_requested);
UINTN         EFIAPI uart_write(IN UINT8 *user_buffer, IN UINTN bytes_to_send);

#endif  // __UART_H__
