/*=============================================================================

                             boot timer

GENERAL DESCRIPTION
  This file contains the implementation of boot logger timer functions .
  Time unit in boot logger is microsecond(10^-6 second).

Copyright 2010, 2015 - 2019 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who        what, where, why
--------   ---        ---------------------------------------------------------
08/19/19   ep         Initial Version
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_config_context.h"
#include "boot_timer_if.h"
#include "boot_timer_hw_if.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
// !!! this is defined on boot_target.h
#define LOG_MAX_COUNT_VAL  138547732

static boot_timer_hw_if_type *ltimer_hw_if = &timer_hw_if;
/*=============================================================================

                              FUNCTION DEFINITIONS

=============================================================================*/


/*===========================================================================

**  Function :  boot_timer_init

** ==========================================================================
*/
/*!
*
* @brief
*  Returns a timestamp which is the current absolute time since bootup
*  subtracts the reference time.
*
* @retval
*    Current time in microseconds.
*    LOG_TIMESTAMP_OVERFLOW if timestamp overflows
*
* @par Side Effects
*   None
*
*/
static bl_error_boot_type boot_timer_init2(boot_timer_hw_if_type *_timer_hw_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if (_timer_hw_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_TIMER, BL_ERR_INVALID_PARAMETER);
      break;
    }

    ltimer_hw_if = _timer_hw_if;

  } while (FALSE);

  return return_status;
}


/*===========================================================================

**  Function :  boot_get_time

** ==========================================================================
*/
/*!
*
* @brief
*  Returns a timestamp which is the current absolute time since bootup
*  subtracts the reference time.
*
* @retval
*    Current time in microseconds.
*    LOG_TIMESTAMP_OVERFLOW if timestamp overflows
*
* @par Side Effects
*   None
*
*/
static bl_error_boot_type boot_get_time2(uint32 ref_time, uint32 *crt_time)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if (ltimer_hw_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_TIMER, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    if (crt_time == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_TIMER, BL_ERR_INVALID_PARAMETER);
      break;
    }

    uint32 curr_time = ltimer_hw_if->get_timestamp();

    /* check if the count overflows*/
    if (curr_time != LOG_MAX_COUNT_VAL)
    {
      // TBD: check underflow
      curr_time -= ref_time;
    }
    else
    {
      curr_time = LOG_TIMESTAMP_OVERFLOW;
    }

    *crt_time = curr_time;

  } while (FALSE);

  return return_status;
}


/*===========================================================================

**  Function :  boot_get_time_count

** ==========================================================================
*/
/*!
*
* @brief
*  Returns a timestamp which is the current absolute time since bootup
*  subtracts the reference time.
*
* @retval
*    Current time in microseconds.
*    LOG_TIMESTAMP_OVERFLOW if timestamp overflows
*
* @par Side Effects
*   None
*
*/
static bl_error_boot_type boot_get_time_count2(uint32 *crt_time)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if (ltimer_hw_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_TIMER, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }

    if (crt_time == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_TIMER, BL_ERR_INVALID_PARAMETER);
      break;
    }

    *crt_time = ltimer_hw_if->get_timestamp();

  } while (FALSE);

  return return_status;
}


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

bl_error_boot_type boot_timer_get_interface(void *ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    boot_timer_if_type *timer_if = (boot_timer_if_type *)ptr;
    if (timer_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_TIMER, BL_ERR_INVALID_PARAMETER);
      break;
    }

    timer_if->init = boot_timer_init2;
    timer_if->get_time = boot_get_time2;
    timer_if->get_time_count = boot_get_time_count2;

  } while (FALSE);

  return return_status;
}


// Legacy functions which should be removed at some point
uint32 boot_get_time_count(void)
{
  uint32 count;

  (void)boot_get_time_count2(&count);

  return count;
}
