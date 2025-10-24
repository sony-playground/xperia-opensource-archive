/*=============================================================================

                     Boot Sahara Logging

GENERAL DESCRIPTION
  This file contains the APIs for enabling sahara logging for debugging.

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
#include "boot_sahara_logging.h"


#define SAHARA_PACKET_LOG_LENGTH (0x64)

/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
struct boot_sahara_packet_log *sahara_log = NULL;

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
  bl_error_boot_type status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if = NULL;
  do
  {
    /* exit if sahara_logger is already allocated */
    if(sahara_log != NULL)
    {
      break;
    }

    if(config_context_handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    if(mem_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    status = mem_if->malloc((sizeof(struct boot_sahara_packet_log) * SAHARA_PACKET_LOG_LENGTH), (void *)&sahara_log);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    if(sahara_log == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_MEMORY_ALLOC_FAIL);
      break;
    }

  }while(FALSE);

  return status;
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
  bl_error_boot_type status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if = NULL;
  do
  {
    /* exit if sahara_logger is already freed */
    if(sahara_log == NULL)
    {
      break;
    }

    if(config_context_handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    if(mem_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    status = mem_if->free(sahara_log);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    sahara_log = NULL;

  }while(FALSE);

  return status;

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
  enum boot_sahara_packet_direction direction
)
{

  static uint32 sahara_packet_log_num = 0, sahara_packet_log_num_total = 0;
  if(sahara_log == NULL || packet_buffer == NULL)
    return;

  if (sahara_packet_log_num >= SAHARA_PACKET_LOG_LENGTH)
  {
    sahara_packet_log_num = 0;
  }
  sahara_log[sahara_packet_log_num].command = 
    (enum boot_sahara_cmd_id) packet_buffer[0];
  sahara_log[sahara_packet_log_num].length = length;
  sahara_log[sahara_packet_log_num].direction = direction;
  sahara_log[sahara_packet_log_num].log_num = sahara_packet_log_num_total;
  sahara_packet_log_num++;
  sahara_packet_log_num_total++;
}