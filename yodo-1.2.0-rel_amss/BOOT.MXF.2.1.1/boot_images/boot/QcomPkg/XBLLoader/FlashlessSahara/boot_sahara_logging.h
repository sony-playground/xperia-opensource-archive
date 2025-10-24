#ifndef BOOT_SAHARA_LOGGING_H
#define BOOT_SAHARA_LOGGING_H

/*=============================================================================

                              Boot Sahara Logging

GENERAL DESCRIPTION
  Internal header for sahara logging.

Copyright 2022 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ----------------------------------------------------------
02/11/22   rama         Initial revision.
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include <boot_config_context.h>
#include <boot_sahara.h>
#include <boot_sahara_internal.h>

/*=============================================================================

                              DEFINITIONS

=============================================================================*/

struct boot_sahara_packet_log
{
  enum boot_sahara_cmd_id command;             // command received or
                                               //   to be transmitted
  uint32 length;                               // length of packet in bytes
  enum boot_sahara_packet_direction direction; // direction of packet
  uint32 log_num;                              // packet log number
};

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
bl_error_boot_type boot_sahara_logger_init(boot_handle config_context_handle);


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
bl_error_boot_type boot_sahara_logger_deinit(boot_handle config_context_handle);

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
);


#endif /* BOOT_SAHARA_LOGGING_H */
