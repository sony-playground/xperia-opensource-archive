/** @file UartSettingsLibNull.c
  
  Stub functions for Uart Settings Lib

  Copyright (c) 2020, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/02/20   ck      Added uart_settings_get_fw
 02/10/20   ck      Initial revision

=============================================================================*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "com_dtypes.h"


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 
typedef enum
{
   UART_SUCCESS = 0,
   UART_ERROR,
}uart_result;

typedef enum
{
   UART_FIRST_PORT = 0,
   UART_DEBUG_PORT = UART_FIRST_PORT,

   UART_SECOND_PORT,
   UART_HS_PORT = UART_SECOND_PORT,

   UART_MAX_PORTS,
}uart_port_id;

typedef struct
{
   volatile uint32 uart_base;
   volatile uint32 qup_common_base;
   uint32 gpio_tx_config;
   uint32 gpio_rx_config;
   uint32 gpio_cts_config;
   uint32 gpio_rfr_config;
   uint32 clock_id_index;
   void*  bus_clock_id;
   void*  core_clock_id;
   uint32 base_freq;
   uint32 irq_num;
   uint32 tcsr_base;
   uint32 tcsr_offset;
   uint32 tcsr_value;
}UART_PROPERTIES;


UART_PROPERTIES* uart_settings_get_properties(uart_port_id port)
{
  return NULL;
}


uart_result uart_settings_get_fw(uint8** base_ptr, uint32 version)
{
   return UART_SUCCESS;
}
