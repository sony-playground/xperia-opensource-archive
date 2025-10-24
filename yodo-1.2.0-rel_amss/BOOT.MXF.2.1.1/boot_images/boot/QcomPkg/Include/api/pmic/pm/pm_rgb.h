#ifndef __PM_RGB_H__
#define __PM_RGB_H__

/*! \file pm_rgb.h
 *  \n
 *  \brief  PMIC RGB driver APIs
 *  \details  This file contains functions and variable declarations to support
 *   the PMIC RGB LED module.
 *
 *
 *  \n &copy; Copyright (c) 2012-2020  by QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/15/20    xp      Remove unused APIs
07/26/17   sv      Added get Rgb picIndex API .
05/01/17   aab     Added pm_rgb_specific_data_type: used for RGB related config data
11/05/15   al      Syncing to latest
08/22/14   aab     Updated LED brightness level
03/31/14   akm     Merged pm_rgb_enable() and pm_rgb_enable_atc() API
===========================================================================*/

/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include "com_dtypes.h"
#include "pm_err_flags.h"

/*===========================================================================
                     GLOBAL TYPE DEFINITIONS
===========================================================================*/

/*
 * LED bitmasks.
 */
#define PM_RGB_SEGMENT_ALL    0x07
/** Red color. */
#define PM_RGB_SEGMENT_R      0x04
/** Green color. */
#define PM_RGB_SEGMENT_G      0x02
/** Blue color. */
#define PM_RGB_SEGMENT_B      0x01


/*
 * LED brightness level
 */
#define PM_RGB_DIM_LEVEL_LOW  0x080
#define PM_RGB_DIM_LEVEL_MID  0x100
#define PM_RGB_DIM_LEVEL_HIGH 0x180
#define PM_RGB_DIM_LEVEL_MAX  0x1FF


/*===========================================================================
                          FUNCTION DEFINITIONS
===========================================================================*/



/*===========================================================================
FUNCTION  pm_rgb_enable

DESCRIPTION
  This function enables the invidual segments of a RGB LED.

PARAMETERS
  1) Name: pmic_device_index
    - Selects which PMIC.
  2) Name: rgb_mask
    - Mask of the RGB segments to enable/disable (PM_RGB_SEGMENT_*).
  3) Name: enable
    - Boolean to enable/disable the indicated RGB segments.

RETURN VALUE
  Type: pm_err_flag_type
  - Possible values:
    - PM_ERR_FLAG_SUCCESS               -> Operation succeeded.
    - PM_ERR_FLAG_FEATURE_NOT_SUPPORTED -> Feature not available on this
                                            version of the PMIC.
    - PM_ERR_FLAG_BUS_ERR           -> Communication with PM chip failed.

DEPENDENCIES
  The following function must have been called:
  1) pm_init()
===========================================================================*/
pm_err_flag_type pm_rgb_enable
(
  uint32              pmic_device_index,
  uint32              rgb_mask,
  boolean             enable
);

#endif

