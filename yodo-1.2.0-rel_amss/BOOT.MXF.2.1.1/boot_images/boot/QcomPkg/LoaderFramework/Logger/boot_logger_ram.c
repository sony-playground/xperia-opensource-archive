/*=============================================================================

                            boot logger ram

GENERAL DESCRIPTION
  This file contains the function interface for logging messages during boot
  to the interal buffer.

Copyright 2010-2019, 2021-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.
  

when       who        what, where, why
--------   ---        ---------------------------------------------------------
10/11/22   yps        Fix message_len issue.
05/04/22   sp         Added log type none
01/05/22   rama       Clean up to remove redundant APIs
08/19/19   ep         Initial Version 
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <string.h>
#include "boot_error_if.h"
#include "boot_logger_if.h"
#include "boot_memory_mgr_if.h"
#include "boot_config_context.h"

/*=============================================================================
            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.
=============================================================================*/
//static const char LEGEND_HEADER[] = "Format: Log Type - Time(microsec) - Message - Optional Info";
//static const char LEGEND_KEY[]    = "Log Type: B - Since Boot(Power On Reset),  D - Delta,  S - Statistic";
static const char FORMATTING_STRING_1[] = " - ";
static const char OVERFLOW_MSG[] = " OVERFLOW";
static const char NEWLINE[] = "\r\n";

#define LOG_MAX_NUM_DIGIT_DISPLAY    9
#define LOG_MAX_TIMESTAMP_VAL        1000000000


#define HEADER_LEN              (sizeof(LEGEND_HEADER) -1)
#define KEY_LEN                 (sizeof(LEGEND_KEY) -1)
#define FORMATTING_STRING_1_LEN (sizeof(FORMATTING_STRING_1) -1)
#define OVERFLOW_MSG_LEN        (sizeof(OVERFLOW_MSG) -1)
#define NEWLINE_LEN             (sizeof(NEWLINE) -1)



/*===========================================================================

**  Function :  _boot_log_ram_put_string

** ==========================================================================
*/
/*!
* 
* @brief
* This function will copy string with given length to internal buffer.
* It does not care if the string is NULL terminated or not, only blindly copy
* "len" bytes of chars to the buffer.
*
* @param[in] str  pointer to the start of string
*
* @param[in] len  length of the string in bytes
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
static bl_error_boot_type _boot_log_ram_put_string(boot_log_meta_info *log_meta_info_ptr, const char *str, uint32 len)
{

  if(log_meta_info_ptr == NULL || str == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_NULL_PTR_PASSED);
  }

  if((log_meta_info_ptr->log_buf_ptr - log_meta_info_ptr->log_buf_start + len) > 
     (log_meta_info_ptr->log_buf_size))
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_BUFFER_OVERFLOW);
  }
  memcpy(log_meta_info_ptr->log_buf_ptr, str, len);
  log_meta_info_ptr->log_buf_ptr += len;

  return BL_ERR_NONE;
}
/*_boot_log_ram_put_string*/



/*===========================================================================

**  Function :  _boot_log_ram_put_time

** ==========================================================================
*/
/*!
* 
* @brief
* This function will take a uint32 timestamp and turn it into a decimal
* ASCII number.  Then it will write it to the buffer.
 
* Note:  It will cap out at 999 seconds (16 minutes, 39 seconds).
* This cap was chosen because it should never be maxed out during boot
* and by keeping it shorter it saves space in the buffer.  The size
* can be changed by adjusting LOG_MAX_NUM_DIGIT_DISPLAY to the desired
* number of decimal digits.
*
* @param[in] timestamp  32bits timestamp
*
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
static bl_error_boot_type _boot_log_ram_put_time(boot_log_meta_info *log_meta_info_ptr, char *ascii_char, uint32 timestamp)
{
  /*Limits the number of decimals that the ASCII number is represented as. 
    In this case it can represent 999 seconds (999,999,999 microseconds).  */
  int ascii_char_len = LOG_MAX_NUM_DIGIT_DISPLAY;
  int i;
  bl_error_boot_type status = BL_ERR_NONE;
  
  /*check if timestamp is overflowed*/
  if(timestamp < LOG_MAX_TIMESTAMP_VAL)
  {
    /*Determine decimal ASCII string, starting 
      with the least siginificant digits.*/
    for(i = (ascii_char_len - 1); i >=0 ; i--)
    {
      ascii_char[i] = (char) (timestamp % 10) + '0';
      timestamp /= 10;
    }
    /*Replaced leading zeros with a space, leaving a single 0 if timestamp==0*/
    for(i = 0; ascii_char[i] == '0' && i <= (ascii_char_len - 2); i++)
    {
      ascii_char[i] = ' ';
    }
    
    status = _boot_log_ram_put_string(log_meta_info_ptr, ascii_char, ascii_char_len);
    if(status != BL_ERR_NONE)
    {
      return status;
    }
  }
  else
  {
    status = _boot_log_ram_put_string(log_meta_info_ptr, OVERFLOW_MSG, OVERFLOW_MSG_LEN);
    if(status != BL_ERR_NONE)
    {
      return status;
    }
  }

  return status;
}
/*boot_log_ram_puttime*/



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
                                        uint32 *len_data)
{
  uint32 message_len = 0;
  uint32 optional_data_len = 0;
  uint32 total_message_len = 0;
  bl_error_boot_type status = BL_ERR_NONE;  
  char ascii_char[LOG_MAX_NUM_DIGIT_DISPLAY];

  do
  {
    if((log_meta_info_ptr == NULL) || (start_log_data == NULL) || (len_data == NULL))
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_LOGGER, BL_ERR_INVALID_PARAMETER);
      break;
    }

    /* Calculate message and optional data lengths. */
    if(message != NULL)
    {
	    message_len = strlen(message);
      if((message_len > 0) && (message[message_len - 1] == '\n'))
	    {
		    message_len--;
      }
    }

    if (optional_data != NULL)
    {
      optional_data_len = strlen(optional_data);
    }

      /* Sum up the total length of the output to the buffer */
    if (timestamp != BOOT_DND_TIMESTAMP)
    {
      total_message_len += LOG_MAX_NUM_DIGIT_DISPLAY + FORMATTING_STRING_1_LEN;
    }

    total_message_len += sizeof(log_type)
                      + FORMATTING_STRING_1_LEN
                      + message_len
                      + NEWLINE_LEN;

  /* If optional data exists then add to total message length. */
    if(optional_data != NULL)
    {
      total_message_len += optional_data_len
                        + FORMATTING_STRING_1_LEN;
    }


    /* Buffer must be initialized. */
    if(log_meta_info_ptr != NULL && log_meta_info_ptr->log_buf_init == TRUE) 
    {
      /*If not enough spaces remain in the buffer*/
      if((log_meta_info_ptr->log_buf_ptr   -
          log_meta_info_ptr->log_buf_start +
          total_message_len)               >=
          log_meta_info_ptr->log_buf_size)
      {
      /*Reset pointer to the beginning, overwrite the existing log*/
      log_meta_info_ptr->log_buf_ptr = log_meta_info_ptr->log_buf_start;
      }

      *start_log_data = (char *)log_meta_info_ptr->log_buf_ptr;
      
      if(log_type != LOG_MSG_TYPE_NONE)
      {
	    /* Copy log_type */
        status = _boot_log_ram_put_string(log_meta_info_ptr, &log_type,
                                          sizeof(log_type));
        if(status != BL_ERR_NONE)
        {
          break;
        }
      
        /* Formatting string, for readability */
        status = _boot_log_ram_put_string(log_meta_info_ptr, FORMATTING_STRING_1,
                                        FORMATTING_STRING_1_LEN);
        if(status != BL_ERR_NONE)
        {
          break;
        }
      }

      if(timestamp != BOOT_DND_TIMESTAMP)
      {
        /* Copy timestamp */
        status = _boot_log_ram_put_time(log_meta_info_ptr, ascii_char, timestamp);
        if(status != BL_ERR_NONE)
        {
          break;
        }

        /* Formatting string, for readability */
        status = _boot_log_ram_put_string(log_meta_info_ptr, FORMATTING_STRING_1,
                                          FORMATTING_STRING_1_LEN);
        if(status != BL_ERR_NONE)
        {
          break;
        }
      }

      /* Write out message to ram, checks for null ptr*/
      if(NULL != message) 
      {
        status = _boot_log_ram_put_string(log_meta_info_ptr, message,
                                          message_len);
        if(status != BL_ERR_NONE)
        {
          break;
        }
      }

      /* Write out optional data if applicable. */
      if(optional_data != NULL)
      {
        status = _boot_log_ram_put_string(log_meta_info_ptr, FORMATTING_STRING_1,
                                          FORMATTING_STRING_1_LEN);
        if(status != BL_ERR_NONE)
        {
          break;
        }

        status = _boot_log_ram_put_string(log_meta_info_ptr, optional_data,
                                          optional_data_len);
        if(status != BL_ERR_NONE)
        {
          break;
        }
      }

      status = _boot_log_ram_put_string(log_meta_info_ptr, NEWLINE,
                                        NEWLINE_LEN);
      if(status != BL_ERR_NONE)
      {
        break;
      }
    }

    *len_data = (uint32)((char *)log_meta_info_ptr->log_buf_ptr - (char *)*start_log_data);

  } while(FALSE);

  return status;
}
/* boot_log_message_ram */


