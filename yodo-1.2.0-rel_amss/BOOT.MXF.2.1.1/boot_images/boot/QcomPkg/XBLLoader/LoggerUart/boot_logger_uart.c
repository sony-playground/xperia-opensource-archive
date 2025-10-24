/*===========================================================================

                    BOOT LOGGER UART DRIVER

DESCRIPTION
  This file contains the function interface for logging messages during boot
  to the uart buffer.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2013-2015, 2018 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/24/18   vk      Add UART poweroff to flush logs
02/06/18   yps     move uart tx buffer to heap
08/18/15   elt     Added boot_log_uart_check_async, boot_log_ram_to_uart
09/17/14   kedara  Update Uart Driver api's.
05/28/14   ck      Added optional data argument to boot_log_message_uart
05/28/14   ck      Updated header for new bootlogger layout
08/20/13   lm      Initial Creation.

===========================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "Uart.h"
#include "boot_logger_uart.h"
#include "boot_uart_if.h"
#include "boot_shared_imem_cookie.h"
#include "DALStdDef.h"
#include "boot_error_if.h"
#include "boot_logger_if.h"
#include "boot_config_context.h"

/*=============================================================================
            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.
=============================================================================*/

/**
 * Header and formating info.
 * Used to centralize the formatting strings so that if a change was made to
 * these it would propogate throughout the logger module correctly.
 */

static boot_handle _config_context_handle = NULL;
/*=============================================================================

                              FUNCTION DEFINITIONS

=============================================================================*/



bl_error_boot_type logger_uart_init(boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_uart_if_type *uart_if = NULL;

  do
  {
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_UART_INTERFACE, (void **)&uart_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    uart_if->init();

    // TBD: we should define an internal structure instead
    _config_context_handle = config_context_handle;
  } while (FALSE);

  return return_status;
}


bl_error_boot_type logger_uart_deinit(void)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  uart_power_off();

  return return_status;
}


bl_error_boot_type logger_uart_log_message_raw(char *message, uint32 data_len)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_uart_if_type *uart_if = NULL;

  do
  {
    return_status = boot_config_context_get_ptr(_config_context_handle, CONFIG_CONTEXT_UART_INTERFACE, (void **)&uart_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    uart_if->tx(message, data_len);

  } while (FALSE);


  return return_status;
}


static boot_registered_logger_if_type logger_uart_if =
{
  logger_uart_init,
  logger_uart_deinit,
  logger_uart_log_message_raw
};



bl_error_boot_type boot_logger_uart_get_interface(boot_registered_logger_if_type **logger_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if ((logger_if == NULL) || ((logger_if == NULL)))
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_INVALID_PARAMETER);
      break;
    }

    *logger_if = &logger_uart_if;

  } while (FALSE);

  return return_status;
}
