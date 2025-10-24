/*==================================================================================================

FILE: Uart.c

Copyright (c) 2020 Qualcomm Technologies, Inc.
        All Rights Reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.

==================================================================================================*/
/*==================================================================================================
                                            DESCRIPTION
====================================================================================================

GLOBAL FUNCTIONS:
   uart_close
   uart_initialize
   uart_open
   uart_poll
   uart_receive
   uart_read
   uart_transmit
   uart_write

==================================================================================================*/
/*==================================================================================================
Edit History


when       who     what, where, why
--------   ---     --------------------------------------------------------
03/27/20   ck      Initial revision

==================================================================================================*/

/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/
#include "UartApi.h"


/*==================================================================================================
                                          LOCAL FUNCTIONS
==================================================================================================*/
uart_result uart_close(uart_handle h)
{
   return UART_SUCCESS;
}


uart_result uart_open(uart_handle* h, uart_port_id id, uart_open_config* config)
{
   return UART_SUCCESS;
}


static void *uart_isr(void *h)
{
   return NULL;
}


uart_result uart_receive(uart_handle h, char* buf, uint32 buf_size, void* cb_data)
{ 
   return UART_SUCCESS;
}


uart_result uart_transmit(uart_handle h, char* buf, uint32 bytes_to_tx, void* cb_data)
{
   return UART_SUCCESS;
}


RETURN_STATUS EFIAPI
uart_initialize(void)
{
   return RETURN_SUCCESS;
}


BOOLEAN EFIAPI
uart_poll(void)
{
   return 0;
}


UINTN EFIAPI
uart_read(OUT UINT8 *user_buffer, IN UINTN bytes_requested)
{ 
   return(bytes_requested);
}


UINTN EFIAPI
uart_write(IN UINT8 *user_buffer, IN UINTN bytes_to_send)
{
   return(bytes_to_send);
}


BOOLEAN EFIAPI
uart_is_cable_connected(void)
{
   return TRUE;
}


BOOLEAN EFIAPI
uart_power_off(void)
{
   return TRUE;
}


BOOLEAN EFIAPI
uart_power_on(void)
{
   return TRUE;
}

RETURN_STATUS EFIAPI
uart_set_baud_rate(IN UINT32 baud_rate, IN VOID* callback_fn)
{
   return RETURN_SUCCESS;
}