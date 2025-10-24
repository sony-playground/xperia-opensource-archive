#ifndef BOOT_LOGGER_H
#define BOOT_LOGGER_H

/*===========================================================================

                                boot logger 
                                Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for Boot Logger
  functionality.
  Time unit in boot logger is microsecond(10^-6 second).

Copyright 2010-2012, 2014-2017, 2019-2022 by Qualcomm Technologies, Incorporated.
All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   --------     ------------------------------------------------------
11/16/22   yps          Removed some APIs
06/23/22   ds           changes for FR78810 - stream logs to media
05/04/22   sp           Added boot log_type_none
01/25/22   ds           boot_log_backup_to_buffer
01/05/22   rama         Cleanup
11/13/20   rama         Added boot_get_log_data
06/12/19   yps          Warpped boot_log_message the same as UEFI
04/24/17   ds           boot_log_pbl_clk_freq
01/30/17   ds           boot_log_pbl_version
06/15/16   kpa          Added boot_log_set_init_info boot_log_get_init_info
08/20/15   elt          Added boot_log_start_time_marker, boot_log_stop_time_marker,
                        boot_log_stop_time_marker_optional_data, and modified
                        data structures for supporting independent time markers
08/18/15   elt          Added BOOT_LOGGER_ASYNC_UART_MAGIC_NUM
06/24/15   ck           Added boot_log_raw_fuse_values
04/07/15   plc          Added note to BOOT_LOG_TEMP_BUFFER_SIZE definition
06/10/14   ck           Added boot_log_ apps_frequency, image_version, ddr_frequency,
                        boot_config_register, delta_time_optional_data,
                        stop_timer_option_data, and message_optional_data
06/02/14   ck           Added BOOT_LOG_TEMP_BUFFER_SIZE definition
06/02/14   ck           Moved defines from boot_logger.c to here
06/02/14   ck           Added boot_log_message_raw
08/30/12   dh           Change boot_log_copy to boot_log_relocate
05/10/12   dh           Change boot_log_set_ref_time to take an argument as reference time
06/21/11   kpa          Add boot_log_forever_loop_check api
11/10/10   dh           Add boot_log_copy api
09/27/10   dh           Add meta info structure for internal bookkeeping
08/11/10   dh           Initial port from 7x30 
============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_comdef.h"
#include <boot_error_if.h>

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
/**
 * Infinite loop
 */
#define INFINITE_LOOP() while(1)

/**
* Log message type(char) : absolute time since boot
*/
#define LOG_MSG_TYPE_BOOT  'B'

/**
* Log message type(char) : delta time
*/
#define LOG_MSG_TYPE_DELTA 'D'

/**
* Log message type(char) : statistical message
*/
#define LOG_MSG_TYPE_STATISTIC 'S'

#define LOG_MSG_TYPE_NONE ' '

/**
* Infinite loop magic number
*/
#define BOOT_LOGGER_LOOP_MAGIC_NUM 0xD1C2B3A3

/**
* Asynchronous uart logging magic number
*/
#define BOOT_LOGGER_ASYNC_UART_MAGIC_NUM 0xE1D50C10

/**
* return value when timestamp overflow happens
*/
#define LOG_TIMESTAMP_OVERFLOW  0xFFFFFFFF

/**
* Value indicating logger should not write timestamp to entry
*/
#define BOOT_DND_TIMESTAMP 0xFFFFFFFF

/**
* time marker handle returned to indicate no available time markers
*/
#define LOG_TIME_MARKER_OVERFLOW 0xFFFFFFFF

/**
* time marker handle for implementing base timer
*/
#define LOG_BASE_TIME_MARKER 0

/**
 * Size of temp buffer available for creating strings
 * Please note, buffers are generally placed on stack so use caution if 
 * adjusting BOOT_LOG_TEMP_BUFFER_SIZE value
 */
#define BOOT_LOG_TEMP_BUFFER_SIZE 96

/**
* Warp boot_log_message the same as UEFI's API LogMsg for common drivers
**/
#define LogMsg(a) boot_log_message(a)


/* Use the common bootlog_buffer declared in boot_logger.c */
extern char bootlog_buffer[BOOT_LOG_TEMP_BUFFER_SIZE];


/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================

**  Function :  boot_log_get_meta_info

** ==========================================================================
*/
/*!
* 
* @brief
*  This function returns a pointer to the meta info structure used by current logger.
*
* @par Dependencies
*   None
*   
* @retval
*   a pointer to the meta info structure used by this logger.
* 
* @par Side Effects
*   None
* 
*/
struct boot_log_meta_info* boot_log_get_meta_info(void);


/*===========================================================================

**  Function :  boot_log_set_ref_time

** ==========================================================================
*/
/*!
* 
* @brief
* This function will set the  timestamp(unit is microsecond) passed in the argument 
* as a reference time to be used by all logging functions.
* the reference time can be set at the beginning in order to get an accurate result.
*
* @param[in] ref_time  reference time that all logging function will use. Unit should
*                      be microsecond
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

void boot_log_set_ref_time(uint32 ref_time);


/*===========================================================================

**  Function :  boot_log_message

** ==========================================================================
*/
/*!
* 
* @brief
*  Logs the given message.It will prefix a timestamp, which is the current 
*  absolute time minus the reference time, to the message string.
*
* @param[in] message  log message
*
* @par Dependencies
*   boot_logger_timer
*   boot_logger_ram
*
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_log_message(char *);


/*===========================================================================

**  Function :  boot_log_message_optional_data

** ==========================================================================
*/
/*!
* 
* @brief
*  Logs the given message.It will prefix a timestamp, which is the current 
*  absolute time minus the reference time, to the message string.
*
* @param[in] message           log message
*
* @param[in] optional_data     Optional data that can be added to entry
*
* @par Dependencies
*   boot_logger_timer
*   boot_logger_ram
*
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_log_message_optional_data(char *,
                                                  char *);


/*===========================================================================

**  Function :  boot_log_message_raw

** ==========================================================================
*/
/*!
* 
* @brief
*  Logs the given message.  Unlike boot_log_message, all data points must be
*  provided.
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
bl_error_boot_type boot_log_message_raw(char *,
                                        uint32,
                                        char,
                                        char *);


/*===========================================================================

**  Function :  boot_log_start_timer

** ==========================================================================
*/
/*!
* 
* @brief
*  This funcion will start the base time marker and mark the beginning of the 
*  timed section and store the current timestamp internally.
*
* @par Dependencies
*   boot_logger_timer
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
void boot_log_start_timer(void);

/*===========================================================================

**  Function :  boot_log_start_time_marker

** ==========================================================================
*/
/*!
* 
* @brief
*  This funcion will try to allocate and start a new time marker
*  and mark the beginning of the timed section and store the current 
*  timestamp internally.
*
* @par Dependencies
*   boot_logger_timer
*   
* @retval
*   Handle to created time marker. Returns LOG_TIME_MARKER_OVERFLOW if space is 
*   not available for creating a new timer.
* 
* @par Side Effects
*   None
* 
*/
uint32 boot_log_start_time_marker(void);

/*===========================================================================

**  Function :  boot_log_stop_timer

** ==========================================================================
*/
/*!
* 
* @brief
*  This funcion will substract the current timestamp with the previus stored 
*  timestamp by boot_log_start_timer(if any) to get the delta time value and 
*  then prefix the delta time to the log message.
*
* @param[in] message  log message
*
* @par Dependencies
*  boot_logger_timer
*  boot_logger_ram
*   
* @retval
*   delta time
* 
* @par Side Effects
*   None
* 
*/
uint32 boot_log_stop_timer(char *);


/*===========================================================================

**  Function :  boot_log_stop_timer_optional_data

** ==========================================================================
*/
/*!
* 
* @brief
*  This funcion will substract the current timestamp with the previus stored 
*  timestamp by boot_log_start_timer(if any) to get the delta time value and 
*  then prefix the delta time to the log message.
*
* @param[in] message           log message
*
* @param[in] optional_data     Optional data that can be added to entry
*
* @par Dependencies
*  boot_logger_timer
*  boot_logger_ram
*   
* @retval
*   delta time
* 
* @par Side Effects
*   None
* 
*/
uint32 boot_log_stop_timer_optional_data(char *,
                                         char *);

/*===========================================================================

**  Function :  boot_log_stop_time_marker

** ==========================================================================
*/
/*!
* 
* @brief
*  This funcion will substract the current timestamp with the previus stored 
*  timestamp for a time marker specified by handle to get the delta time 
*  value and then prefix the delta time to the log message.
*
* @param[in] handle  handle to time marker returned by 
*                    boot_log_start_time_marker
*
* @param[in] message  log message
*
* @par Dependencies
*  boot_logger_timer
*  boot_logger_ram
*   
* @retval
*   delta time
* 
* @par Side Effects
*   None
* 
*/
uint32 boot_log_stop_time_marker(uint32, char *);


/*===========================================================================

**  Function :  boot_log_stop_time_marker_optional_data

** ==========================================================================
*/
/*!
* 
* @brief
*  This funcion will substract the current timestamp with the previus stored 
*  timestamp for a time marker specified by handle to get the delta time 
*  value and then prefix the delta time to the log message.
*
* @param[in] handle  handle to time marker returned by 
*                    boot_log_start_time_marker
*
* @param[in] message  log message
*
* @param[in] optional_data  Optional data that can be added to entry
*
* @par Dependencies
*  boot_logger_timer
*  boot_logger_ram
*   
* @retval
*   delta time
* 
* @par Side Effects
*   None
* 
*/
uint32 boot_log_stop_time_marker_optional_data(uint32, char *, char *);

/*===========================================================================

**  Function :  boot_log_dump

** ==========================================================================
*/
/*!
* 
* @brief
* This function will dump the logged messages to various outputs.  Currently, 
* it only supports JTAG.It may be expanded to support other methods of displaying,
* such as UART, etc.
*
* @param[in] init_data  boot logger intialization data which contains boot
*                       logger's buffer address
*
* @par Dependencies
*  boot_logger_jtag
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
//void boot_log_dump(boot_log_init_data *);

/*===========================================================================

**  Function :  boot_log_get_time

** ==========================================================================
*/
/*!
* 
* @brief
* This will return the current timestamp which is the absolute time since boot
* subtracts the reference time.
*
* @par Dependencies
*  boot_logger_timer
*   
* @retval
*   current timestamp minus the reference time, LOG_TIMESTAMP_OVERFLOW 
*   if overflow happens
* 
* @par Side Effects
*   None
* 
*/
uint32 boot_log_get_time(void);


/*===========================================================================

**  Function :  boot_log_delta_time

** ==========================================================================
*/
/*!
* 
* @brief
* This will log the delta time, the time between the old_time that was given
* and the time this function is executed.  It will also return this delta time. 
*
* @param[in] old_time          previous time reference point 
*
* @param[in] message           log message
*
* @par Dependencies
*  boot_logger_timer
*   
* @retval
*   delta time between the old_time that was given
*   and the time this function is executed.
*   LOG_TIMESTAMP_OVERFLOW if overflow happens
* 
* @par Side Effects
*   None
* 
*/
uint32 boot_log_delta_time(uint32,
                           char *);


/*===========================================================================

**  Function :  boot_log_delta_time_optional_data

** ==========================================================================
*/
/*!
* 
* @brief
* This will log the delta time, the time between the old_time that was given
* and the time this function is executed.  It will also return this delta time. 
*
* @param[in] old_time          previous time reference point 
*
* @param[in] message           log message
*
* @param[in] optional_data     Optional data that can be added to entry
*
* @par Dependencies
*  boot_logger_timer
*   
* @retval
*   delta time between the old_time that was given
*   and the time this function is executed.
*   LOG_TIMESTAMP_OVERFLOW if overflow happens
* 
* @par Side Effects
*   None
* 
*/
uint32 boot_log_delta_time_optional_data(uint32,
                                         char *,
                                         char *);


/*===========================================================================

**  Function :  boot_log_relocate

** ==========================================================================
*/
/*!
* 
* @brief
* Copy the log and meta info in one memory location to some other 
* memory location and continue to save logs at that location.
*
* @param[in] dst_meta_info_addr  destination address to save meta info
*
* @param[in] dst_log_buf_addr  destination address to save message log
*
* @param[in] dst_log_buf_size  size of the destination message log buf size
*
* @param[in] dst_time_marker_buf_addr  destination address to save time markers
*
* @param[in] dst_time_marker_buf_size  size of the destination time marker 
*                                      buffer
*
* @param[in] src_meta_info_addr  source address to read meta info
*
* @param[in] src_log_buf_addr  source address to read message log
*
* @param[in] src_log_buf_size  size of the source message log buf size
*
* @param[in] src_time_marker_buf_addr  source address to read time markers
*
* @param[in] src_time_marker_buf_size  size of the source time marker buffer
*
* @par Dependencies
*  boot_logger_ram
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/

void boot_log_relocate
(
  void *dst_meta_info_addr,
  void *dst_log_buf_addr,
  uint32 dst_log_buf_size,
  void *dst_time_marker_buf_addr,
  uint32 dst_time_marker_buf_size,
  void *src_meta_info_addr,
  void *src_log_buf_addr,
  uint32 src_log_buf_size,
  void *src_time_marker_buf_addr,
  uint32 src_time_marker_buf_size
);

 

/*===========================================================================

**  Function : boot_log_ddr_frequency

** ==========================================================================
*/
/*!
* 
* @brief  
*   Logs the ddr frequency.
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
bl_error_boot_type boot_log_ddr_frequency(void);


/*===========================================================================

**  Function : boot_get_log_data

** ==========================================================================
*/
/*!
* 
* @brief  
*   Function returns the log base address and size of init boot logs.
*
* @par Dependencies
*   Must be called after boot_log_init.
*
* @retval
*   None
* 
* @par Side Effects
*   None
*  
*/
bl_error_boot_type boot_get_log_data(uint8 **log_base_addr_ptr, uintnt *size_ptr);

/*===========================================================================

**  Function : boot_log_backup_to_buffer

** ==========================================================================
*/
/*!
* 
* @brief  
*   Function saves last X bytes of the logs to X byte buffer
*
* @par Dependencies
*   Must be called after boot_log_init.
*
* @retval
*   None
* 
* @par Side Effects
*   None
*  
*/
void boot_log_backup_to_buffer(void *mem_buffer_start, uint32 mem_buffer_size);

#endif  /* BOOT_LOGGER_H */
