/*=============================================================================

                     sahara logging lib

GENERAL DESCRIPTION
  This file contains the APIs required to stub sahara logging features.

Copyright 2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
02/11/22   rama         Initial revision.
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <boot_config_context.h>
#include <boot_error_if.h>

/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
/*=============================================================================

FUNCTION DEFINITIONS

=============================================================================*/
/*=========================================================================

**  Function :  boot_sahara_logger_init

** ==========================================================================
*/
/*!
*
* @brief
*   intialize the buffers required for sahara logging.
*
* @param[in] 
*   boot_handle config context handle
*
*/
bl_error_boot_type boot_sahara_logger_init(boot_handle config_context_handle)
{
  return BL_ERR_NONE;
}


/*=========================================================================

**  Function :  boot_sahara_logger_deinit

** ==========================================================================
*/
/*!
*
* @brief
*   deinitialize the buffers allocated for sahara logging.
*
* @param[in]
*   boot_handle config context handle
*
*/
bl_error_boot_type boot_sahara_logger_deinit(boot_handle config_context_handle)
{
  return BL_ERR_NONE;
}


/* ============================================================================
**  Function : boot_sahara_log_packet_buffer
** ============================================================================
*/
/*!
*   @brief
*   This function logs the command in the input packet buffer along with some
*   packet and state information.
*   
*   @details
*   This function stores the packet buffer command and length into log. The
*   direction of the packet (transmit or receive) and the current state
*   of the target state machine is also stored. The packets are stored
*   in a round robin fashion where if the log fills up, the index into the
*   log will reset to 0 and overwrite the log entries starting from the
*   index 0 of the log buffer.
*   
*   @param *packet_buffer   -  [IN/OUT] Input packet
*   @param length           -  [IN    ] Packet length
*   @param direction        -  [IN    ] Packet transmit or receive
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/
void boot_sahara_log_packet_buffer
(
  uint8* packet_buffer,
  uint32 length,
  uint32 direction
)
{
  return;
}