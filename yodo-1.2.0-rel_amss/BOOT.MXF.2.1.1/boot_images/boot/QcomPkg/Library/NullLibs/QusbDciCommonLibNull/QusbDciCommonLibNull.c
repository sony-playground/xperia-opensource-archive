/** @file QusbDciCommonLibNull.c
  
  Stub functions for QusbDciCommonLib

  Copyright (c) 2016, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/15/16   kpa     Initial revision

=============================================================================*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "qusb_log.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

// UART logging
void qusb_uart_log(char *message, uint32 value)
{

}

boolean usb_dci_mem_allocate(void** mem_ptr, uint32 size)
{
  return FALSE;
}

boolean usb_dci_mem_free(void* mem_ptr)
{
  return FALSE;
}

void qusb_uart_buffer_log(uint32 id, uint32 value)
{
}

