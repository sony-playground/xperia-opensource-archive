#ifndef BOOT_LOGGER_RAM_H
#define BOOT_LOGGER_RAM_H

/*===========================================================================

                                boot logger 
                                Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for Boot Logger
  functionality.
  Time unit in boot logger is microsecond(10^-6 second).

Copyright 2010-2019, 2021-2022 by Qualcomm Technologies, Incorporated.  
All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   --------     ------------------------------------------------------
01/05/22   rama         Clean up to remove redundant APIs
08/13/19   ep           Initial Version 
============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_comdef.h"
#include "boot_error_if.h"


/*===========================================================================

**  Function :  boot_log_message_ram

** ==========================================================================
*/
/*!
* 
* @brief
* This funcion will copy the given message to logging buffer and prefix the
* message by a given timestamp.
* The log_type is generally used to show what type of timing is used, but
* it could technically be used for other type of info.
*
* @param[in] message  log message
*
* @param[in] timestamp  timestamp to log
*   Value of BOOT_DND_TIMESTAMP indicates timestamp will not be printed
*
* @param[in] log_type  type of the log
*
* @param[in] optional_data  Optional data that can be added to entry
*
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_log_message_ram(boot_log_meta_info *log_meta_info_ptr,
                                        char *message,
                                        uint32 timestamp,
                                        char log_type,
                                        char *optional_data,
                                        char **start_log_data,
                                        uint32 *len_data);


#endif  /* BOOT_LOGGER_RAM_H */
