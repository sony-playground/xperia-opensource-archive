#ifndef BOOT_UART_IF_H
#define BOOT_UART_IF_H
/*===========================================================================

                    BOOT UART DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external uart drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2013-2019 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/07/19   ep      Major update
09/17/14   kedara  Update Uart Driver api's.
                   remove FEATURE_BOOT_EXTERN_UART_COMPLETED
08/20/13   lm      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"
#include "boot_comdef.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

typedef struct boot_uart_if_type
{
  boolean (*init)(void);
//  uint32 (*rx)(char* buf, uint32 bytes_to_rx);
  UINTN EFIAPI (*rx)(OUT UINT8 *, IN UINTN);
  uint32 (*tx)(char* buf, uint32 bytes_to_tx);
} boot_uart_if_type;


/*===========================================================================
**  Function :  boot_uart_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_uart_get_interface
*
* @par Dependencies
*   None 
* 
*/

//bl_error_boot_type boot_uart_get_interface(boot_uart_if_type *uart_if);

extern boot_uart_if_type uart_if;


#endif /* BOOT_UART_IF_H */

