#ifndef __PM_APP_RGB__H__
#define __PM_APP_RGB__H__

/*! \file pm_app_rgb.h
 *  \n
 *  \brief  PMIC RGB algorithms
 *  \details  This file contains functions and variable declarations to support
 *   the PMIC RGB
 *
 *
 *  \n &copy; Copyright (c) 2018-2021  by QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================
                                Edit History
This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.

 
when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/15/20   xp      API refine
03/22/18   al      Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "com_dtypes.h"
#include "pm_err_flags.h"

/*=========================================================================== 
 
                     GLOBAL DEFINES
 
===========================================================================*/



/*=========================================================================== 
 
                     GLOBAL TYPE DEFINITIONS
 
===========================================================================*/

/*! \enum type of LED configuration 
 *  \brief .
 */
typedef enum
{
  /* Glow LED with steady brightness */
   PM_RGB_STATE_GLOW, 
   /* Blink LED */
   PM_RGB_STATE_BLINK,
  /* Turn off LED */
   PM_RGB_STATE_OFF,  
  /*Invalid*/ 
   PM_RGB_STATE_INVALID,
}pm_rgb_state_type;

typedef struct
{
  pm_rgb_state_type rgb_state;  /*Refer #pm_rgb_state_type for more info*/
  uint32 rgb_mask;              /*RGB color mask*/
  uint32 dim_level;             /*RGB brightness level*/
}pm_app_rgb_config_type; 


/*===========================================================================

                     PROTOTYPES 

===========================================================================*/


/*===========================================================================
FUNCTION  pm_rgb_led_config

DESCRIPTION
  This function enables/disables RGB LED(s) with given brightness level

PARAMETERS
  1) Name: rgb_mask
    - Selects which RGB LED to ON/OFF
      Valid Values:
        PM_RGB_SEGMENT_R
        PM_RGB_SEGMENT_G
        PM_RGB_SEGMENT_B
        PM_RGB_SEGMENT_ALL
        ORed by any of PM_RGB_SEGMENT_R, PM_RGB_SEGMENT_G and PM_RGB_SEGMENT_B
  2) Name: dim_level
    - Selects the RGB LED brightness level
      The suggesed value is: 
        PM_RGB_DIM_LEVEL_LOW 
        PM_RGB_DIM_LEVEL_MID 
        PM_RGB_DIM_LEVEL_HIGH
        PM_RGB_DIM_LEVEL_MAX         
  3) Name: enable_rgb
        TRUE:  Enable LED
        FALSE: Disable LED. In this case, the dim_level doesn't matter

RETURN VALUE
  Type: pm_err_flag_type
  - Possible values:
    - PM_ERR_FLAG_SUCCESS               -> Operation succeeded.
    - PM_ERR_FLAG_INVALID_PARAMETER -> Invalid input parameter
    - PM_ERR_FLAG_FEATURE_NOT_SUPPORTED -> Feature not available on this
                                            version of the PMIC.
    - PM_ERR_FLAG_BUS_ERR           -> Communication with PM chip failed.

USAGE EXAMPLE:
  pm_rgb_led_config(PM_RGB_SEGMENT_R,  PM_RGB_DIM_LEVEL_LOW, TRUE); Turn on Red LED with low brightness
  pm_rgb_led_config(PM_RGB_SEGMENT_R,  PM_RGB_DIM_LEVEL_LOW, FALSE); Turn off Red LED
  

DEPENDENCIES
  The following function must have been called:
  1) pm_driver_init()
===========================================================================*/
pm_err_flag_type pm_rgb_led_config
(
  uint32 rgb_mask,
  uint32 dim_level,
  boolean enable_rgb
);

/*===========================================================================
FUNCTION  pm_rgb_led_blink

DESCRIPTION
  This function blinks RGB LED(s) with given brightness level

PARAMETERS
  1) Name: rgb_mask
    - Selects which RGB LED to blink
      Valid Values:
        PM_RGB_SEGMENT_R
        PM_RGB_SEGMENT_G
        PM_RGB_SEGMENT_B
        PM_RGB_SEGMENT_ALL
        ORed by any of PM_RGB_SEGMENT_R, PM_RGB_SEGMENT_G and PM_RGB_SEGMENT_B
  2) Name: dim_level
    - Selects the RGB LED brightness level
      The suggesed value is: 
        PM_RGB_DIM_LEVEL_LOW 
        PM_RGB_DIM_LEVEL_MID 
        PM_RGB_DIM_LEVEL_HIGH
        PM_RGB_DIM_LEVEL_MAX         

RETURN VALUE
  Type: pm_err_flag_type
  - Possible values:
    - PM_ERR_FLAG_SUCCESS               -> Operation succeeded.
    - PM_ERR_FLAG_INVALID_PARAMETER -> Invalid input parameter
    - PM_ERR_FLAG_FEATURE_NOT_SUPPORTED -> Feature not available on this
                                            version of the PMIC.
    - PM_ERR_FLAG_BUS_ERR           -> Communication with PM chip failed.

USAGE EXAMPLE:
  pm_rgb_led_blink(PM_RGB_SEGMENT_R,  PM_RGB_DIM_LEVEL_LOW); Blink Red LED with low brightness
  

DEPENDENCIES
  The following function must have been called:
  1) pm_driver_init()
===========================================================================*/
pm_err_flag_type pm_rgb_led_blink(uint32 rgb_mask, uint32 dim_level);


#endif  //__PM_APP_RGB__H__

