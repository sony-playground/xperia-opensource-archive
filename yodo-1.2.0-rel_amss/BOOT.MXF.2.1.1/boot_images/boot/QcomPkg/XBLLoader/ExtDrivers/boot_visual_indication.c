
/*=============================================================================

                        Boot Visual Indication

GENERAL DESCRIPTION
  This file defines boot visual indication functions

Copyright 2013, 2015, 2020 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
10/05/15   ck      Corrected copyright
07/11/15   rp       Changed boot_enable_led function to have an additional argument for color
04/09/13   dh      Initial creation
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_config_context.h"
#include <boot_visual_indication_if.h>
#include <boot_pmic_if.h>
#include <boot_timer_if.h>

static  uint32 previous_time = 0;

/* The LED flash interval in microseconds*/
#define LED_FLASH_INTERVAL_US (500000U)


/*===========================================================================

**  Function :  boot_enable_led

** ==========================================================================
*/
/*!
 * @brief This function turn on/off an led according to input
 * @return None.
 *
 */
bl_error_boot_type boot_enable_led(uint32 led_color, boot_boolean led_on)
{
  boot_pmic_if_type *pmic_if;
  bl_error_boot_type status = BL_ERR_NONE;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PMIC_INTERFACE, (void *)&pmic_if);
  if (status != BL_ERR_NONE)
  {
    return status;
  }

  if (pmic_if->pm_enable_led(led_color, led_on) ==  PM_ERR_FLAG_SUCCESS)
    return BL_ERR_NONE;

  return BL_ERR_FEATURE_NOT_SUPPORTED;
}


/*===========================================================================

**  Function :  boot_toggle_led_init

** ==========================================================================
*/
/*!
 * @brief This function initializes the timer count for led toggling
 *
 */
bl_error_boot_type boot_toggle_led_init(void)
{
  boot_timer_if_type *timer_if;
  bl_error_boot_type status = BL_ERR_NONE;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_TIMER_INTERFACE, (void *)&timer_if);
  if (status != BL_ERR_NONE)
  {
    return status;
  }

  return timer_if->get_time(0, &previous_time);
}


/*===========================================================================

**  Function :  boot_toggle_led

** ==========================================================================
*/
/*!
 * @brief This function executes the pmic rgb led functions to toggle LED
 */
bl_error_boot_type boot_toggle_led(void)
{
  boot_boolean ret_val = TRUE;
  uint32 led_color = PM_RGB_SEGMENT_B;
  boot_pmic_if_type *pmic_if;
  boot_timer_if_type *timer_if;
  bl_error_boot_type status = BL_ERR_NONE;

  uint32 current_time = 0;
  static boot_boolean current_led_status = FALSE;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_TIMER_INTERFACE, (void *)&timer_if);
  if (status != BL_ERR_NONE)
  {
    return FALSE;
  }
  timer_if->get_time(previous_time, &current_time);

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PMIC_INTERFACE, (void *)&pmic_if);
  if (status != BL_ERR_NONE)
  {
    return FALSE;
  }

  /* There may be problem when current_time is out of range, but only
   * one time, so do not take it into account
   */
  if ((current_time - previous_time) >= LED_FLASH_INTERVAL_US)
  {
    current_led_status = !current_led_status;
    ret_val = pmic_if->pm_enable_led(led_color, current_led_status);
    previous_time = current_time;
  }

  return ret_val;
}



boot_visual_indicator_if_type visual_indicator_if =
{
  NULL,
  NULL,
  boot_enable_led,
  boot_toggle_led_init,
  boot_toggle_led
};

