#ifndef BOOT_LOGGER_IF_H
#define BOOT_LOGGER_IF_H

/*===========================================================================

                                boot logger 
                                Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for Boot Logger
  functionality.
  Time unit in boot logger is microsecond(10^-6 second).

Copyright 2010-2012, 2014-2017, 2020-2022 by Qualcomm Technologies, Incorporated.
All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   --------     ------------------------------------------------------
05/04/22   sp           Added boot log_type_none
01/05/22   rama         Clean up
11/13/20   rama         Added boot_get_log_data
08/13/19   ep           Initial Version 
============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_framework.h"
#include "boot_error_if.h"

/*=============================================================================

            GLOBAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
/**
* Value indicating logger should not write timestamp to entry
*/
#define BOOT_DND_TIMESTAMP 0xFFFFFFFF

/**
 * Size of temp buffer available for creating strings
 * Please note, buffers are generally placed on stack so use caution if 
 * adjusting BOOT_LOG_TEMP_BUFFER_SIZE value
 */
#define BOOT_LOG_TEMP_BUFFER_SIZE 96

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
* time marker handle returned to indicate no available time markers
*/
#define LOG_TIME_MARKER_OVERFLOW 0xFFFFFFFF

typedef enum
{
  BL_ERR_LOGGER_TOO_MANY_LOGGERS = BL_ERR_CUSTOM_ERRORS_START,

} bl_error_logger_type;


/**
 * Structure that holds the start address/size of 
 * the boot logger's logging buffer and meta data.
 * This structure can be expanded to store other information.
 * log_buffer_start and meta_info_start must be assigned to 
 * valid addresses prior to use boot logger.
 * boot_log_init must be called before using any
 * boot logger function.
 */
typedef struct boot_log_init_data
{
  /**
  * Start address of the current logging buffer 
  */
  void *log_buffer_start;
  
  /**
  * Size of the current logging buffer 
  */
  uint32 log_buffer_size;
  
  /**
  * Start address of the current time marker buffer
  */
  void *time_marker_buffer_start;

  /**
  * Size of the the current time marker buffer
  */
  uint32 time_marker_buffer_size;

  /**
  * Start address of the current meta info structure
  */
  void *meta_info_start;
  
  /**
  * Size of the current meta info structure
  */
  uint32 meta_info_size;
  
 /**
  * Start address of the old meta info structure.
  * It is used to retrieve reference time from the old boot logger
  * Set this value to NULL will default the reference time of current logger
  * to 0.
  */
  void *old_meta_info_start;
  
} boot_log_init_data;



/**
 * Structure that holds an entry in the boot time marker buffer.
 * Includes a start time value as well as a pointer to next free time marker
 * buffer entry.
 */
typedef struct boot_time_marker_entry_t
{
  /**
   * Start time this entry tracks
   */
  uint32 start_time;

  /**
   * Pointer to next free entry in time marker buffer. NULL if none exists
   */
  struct boot_time_marker_entry_t *next_free_entry;

} boot_time_marker_entry;


/**
 * This struct defines the structure of boot logger's meta info, which keeps
 * track of the logger's internal states.
 * It contains information about current logger's logging buffer and timer.
 * The size of this structure must be smaller than SCL_BOOT_LOG_META_INFO_SIZE
 */
typedef struct boot_log_meta_info
{
  /**
   *pointer that points to beginning of the logging buffer
   */
  uint8  *log_buf_start;
  
  /**
   *pointer that points to the next empty byte in the logging buffer
   */
  uint8  *log_buf_ptr;
  
  /**
   * total size of the logging buffer in bytes
   */
  uint32 log_buf_size;
  
  /**
   *status of logging buffer, initialized(TRUE) or uninitialized(FALSE)
   */
  uint32 log_buf_init;
  
  /**
  * stores the timestamp which serves as a reference point
  */
  uint32 ref_time;
  
  /**
   * pointer to the beginning of the time marker buffer 
   */
  boot_time_marker_entry *time_marker_buf_start;

  /**
   * pointer to next free entry in time marker buffer
   */
  boot_time_marker_entry *time_marker_buf_ptr;

  /**
   * total size of time marker buffer in bytes
   */
  uint32 time_marker_buf_size;
  
  /**
   *the status of time marker buffer, initialized(TRUE) or uninitialized(FALSE)
   */
  uint32 time_marker_buf_init;
} boot_log_meta_info;



typedef bl_error_boot_type (*logger_callback_log_type)(char *message, 
													   uint32 timestamp,
													   char log_type,
													   char *optional_data);


typedef struct boot_registered_logger_if_type
{
  bl_error_boot_type (*init)(boot_handle);
  bl_error_boot_type (*deinit)(void);

  bl_error_boot_type (*log_message_raw)(char *, uint32);

} boot_registered_logger_if_type;



typedef struct boot_logger_if_type
{
  bl_error_boot_type (*init)(boot_handle, boot_log_init_data *);
  bl_error_boot_type (*deinit)(void);

  bl_error_boot_type (*register_logger)(boot_registered_logger_if_type *);
  bl_error_boot_type (*unregister_logger)(boot_registered_logger_if_type *);

  bl_error_boot_type (*log_message)(char *);
  bl_error_boot_type (*log_message_optional)(char *, char *);

  bl_error_boot_type (*log_message_delta_time)(uint32, char *);
  bl_error_boot_type (*log_message_delta_time_optional)(uint32, char *, char *);
  bl_error_boot_type (*get_log_data)(uint8 **boot_log_addr_ptr, uintnt *size_ptr);

} boot_logger_if_type;


/*===========================================================================
**  Function :  boot_logger_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_logger_get_interface object 
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_logger_get_interface(void *ptr);

bl_error_boot_type boot_log_message(char *message);
bl_error_boot_type boot_log_message_optional_data(char *message, char *optional_data);
uint32 boot_log_get_time(void);
uint32 boot_log_delta_time(uint32 old_time, char *message);
uint32 boot_log_delta_time_optional_data(uint32 old_time, char *message, char *optional_data);
bl_error_boot_type boot_log_message_raw(char *message, uint32 timestamp, char log_type, char *optional_data);
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




#endif  /* BOOT_LOGGER_IF_H */
