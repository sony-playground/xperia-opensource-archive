/*===========================================================================

                         Boot Statistics Interface File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for boot statistics

Copyright 2020 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who         what, where, why
--------   ---         --------------------------------------------------
09/23/20   ck          Added init function and removed redundant CALCULATE_TIMESTAMP call
09/14/20   ck          Corrected throughput calculation
02/15/20   ds          initial version

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <stdio.h>
#include "boot_statistics_if.h"
#include "boot_logger_if.h"
#include "boot_memory_mgr_if.h"
#include "boot_target.h"
#include "boot_config_context.h"


static struct boot_statistics_obj
{
  uint32 flash_timer_start_timetick;
  uint32 flash_total_time_us;
  uint32 flash_total_bytes_read;
  uint32 flash_byte_counter;
} boot_statistics_obj;


/*=========================================================================
                            
                       FUNCTION DEFINITIONS

=========================================================================*/
/*=========================================================================

**  Function :  _init

** ==========================================================================
*/
/*!
* 
* @brief
*   intialize the boot stats handle.
* 
* @param[in] pointer to boot stats handle
* 
*/
static void _init()
{
  boot_statistics_obj.flash_timer_start_timetick = 0;
  boot_statistics_obj.flash_total_time_us = 0;
  boot_statistics_obj.flash_total_bytes_read = 0;
  boot_statistics_obj.flash_byte_counter = 0;
}


bl_error_boot_type boot_statistics_init(void)
{
  bl_error_boot_type error = BL_ERR_NONE;

  
  /* Clear internal structure */   
  _init();
    

  return error;
}


/*===========================================================================

**  Function : boot_statistics_flash_read_start

** ==========================================================================
*/
/*!
* 
* @brief  
*   Called before reading from flash.  This gets the current timer value and
*   stores it for use when boot_statistics_flash_read_stop is called.
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
bl_error_boot_type boot_statistics_flash_read_start()
{
  boot_statistics_obj.flash_timer_start_timetick = boot_log_get_time();
  return BL_ERR_NONE;
}


/*===========================================================================

**  Function : boot_statistics_flash_read_stop

** ==========================================================================
*/
/*!
* 
* @brief  
*   Called after reading from flash.  This gets the current timer value
*   calculates the delta from the start value, and updates the flash statistics.
*
* @par Input
*   bytes_read    Number of bytes read from flash
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
bl_error_boot_type boot_statistics_flash_read_stop(uint32 bytes_read)
{
  
  uint32 flash_timer_stop_timetick = boot_log_get_time();

  /* Update the flash statistics, total bytes read and byte counter. */
  boot_statistics_obj.flash_total_time_us += flash_timer_stop_timetick - (boot_statistics_obj.flash_timer_start_timetick);

  boot_statistics_obj.flash_total_bytes_read += bytes_read;
  boot_statistics_obj.flash_byte_counter += bytes_read;
  
  return BL_ERR_NONE;
}


/*===========================================================================

**  Function : boot_statistics_reset_flash_byte_counter

** ==========================================================================
*/
/*!
* 
* @brief  
*   A counter seperate from the total flash bytes counter exists so functions
*   can access the number of flash bytes read during a particular period.  This
*   function resets that counter.
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
bl_error_boot_type boot_statistics_reset_flash_byte_counter()
{
  boot_statistics_obj.flash_byte_counter = 0;
  
  return BL_ERR_NONE;
}


/*===========================================================================

**  Function : boot_statistics_get_flash_byte_counter

** ==========================================================================
*/
/*!
* 
* @brief  
*   A counter seperate from the total flash bytes counter exists so functions
*   can access the number of flash bytes read during a particular period.  This
*   function returns the value in that counter.
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
bl_error_boot_type boot_statistics_get_flash_byte_counter(uint32* bytes_read)
{
  bl_error_boot_type return_value = BL_ERR_NONE;


  /* Validate pointers */
  if (bytes_read == NULL)
  {
    return_value = GET_ERROR_CODE(BL_ERROR_GROUP_BOOTSTATS, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  *bytes_read = boot_statistics_obj.flash_byte_counter;
  

 exit:
  return return_value;
}


/*===========================================================================

**  Function : boot_statistics_log_flash

** ==========================================================================
*/
/*!
* 
* @brief  
*   Reports the flash throughput (speed, total bytes read, total time)
*   via the boot logger.
*
* @par Input
*   None
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
bl_error_boot_type boot_statistics_log_flash()
{
  #define TIME_US_TO_SECOND_DIVISION       1000000
  #define TIME_SINGLE_UNIT_STEP_DIVISION   1000
  #define KB_TO_BYTE_DIVISION              1000

  uint32 flash_bytes_per_second = 0;
  uint32 remaining_time_division = TIME_US_TO_SECOND_DIVISION;
  uint32 current_time_value = boot_statistics_obj.flash_total_time_us;
  char temp_buffer[BOOT_LOG_TEMP_BUFFER_SIZE];


  /* Calculate throughput only if data was read from flash. */
  if (boot_statistics_obj.flash_total_bytes_read &&
      boot_statistics_obj.flash_total_time_us)
  {
    /* If time value is > total bytes read then throughput will result in 0.
       Get time value as small as possible since initial value is micro seconds and final reported value is seconds. */
    while ((current_time_value >= TIME_SINGLE_UNIT_STEP_DIVISION) &&
           (remaining_time_division > 1))
    {
      current_time_value /= TIME_SINGLE_UNIT_STEP_DIVISION;
      remaining_time_division /= TIME_SINGLE_UNIT_STEP_DIVISION;
    }

    /* Time value is as small as possible.  If time value is still > bytes read 0 will be reported.
       Calculate bytes per second throughput. */
    flash_bytes_per_second = boot_statistics_obj.flash_total_bytes_read / current_time_value;  /* bytes per current_time_value's unit of measure */
    flash_bytes_per_second *= remaining_time_division;  /* Converts from bytes per current_time_values unit of measure to final bytes per second */
  }


  /* If bytes per second >= KB_TO_BYTE_DIVISION then display throughput as KB/s.  If not then display as B/s. */
  if (flash_bytes_per_second >= KB_TO_BYTE_DIVISION)
  {
    snprintf(temp_buffer,
             BOOT_LOG_TEMP_BUFFER_SIZE,
             "Flash Throughput, %d KB/s  (%d Bytes,  %d us)",
             (flash_bytes_per_second / KB_TO_BYTE_DIVISION),
             boot_statistics_obj.flash_total_bytes_read,
             boot_statistics_obj.flash_total_time_us);
  }
  else
  {
    snprintf(temp_buffer,
             BOOT_LOG_TEMP_BUFFER_SIZE,
             "Flash Throughput, %d B/s  (%d Bytes,  %d us)",
             flash_bytes_per_second,
             boot_statistics_obj.flash_total_bytes_read,
             boot_statistics_obj.flash_total_time_us);
  }


  /* Write results to boot log */
  boot_log_message_raw(temp_buffer,
                       BOOT_DND_TIMESTAMP,
                       LOG_MSG_TYPE_STATISTIC,
                       NULL);

                       
  return BL_ERR_NONE;
}


boot_statistics_if_type boot_statistics_if = {
  boot_statistics_init,
  boot_statistics_flash_read_start,
  boot_statistics_flash_read_stop,
  boot_statistics_get_flash_byte_counter,
  boot_statistics_reset_flash_byte_counter,
  boot_statistics_log_flash  
};