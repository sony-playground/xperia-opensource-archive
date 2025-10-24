#ifndef BOOT_VISUAL_INDICATION_IF_H
#define BOOT_VISUAL_INDICATION_IF_H
/*=============================================================================

                        Boot Visual Indication

GENERAL DESCRIPTION
  This file defines SBL visual indication functions

Copyright 2013, 2015 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
10/05/15   ck      Corrected copyright
07/11/15   rp     Changed boot_enable_led function declaration to include led color as input
04/09/13   dh      Initial creation
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_comdef.h"
#include "boot_error_if.h"


typedef enum
{
  BL_ERR_VISUAL_INDICATOR_PMIC                = BL_ERR_CUSTOM_ERRORS_START,

} bl_error_visual_indicator_type;

/*=============================================================================

                              FUNCTION DEFINITIONS

=============================================================================*/


typedef struct boot_visual_indicator_if_type
{
  bl_error_boot_type (*init)(void* boot_handle);
  bl_error_boot_type (*deinit)(void);

  bl_error_boot_type (*enable_led)(uint32 led_color, boot_boolean led_on);
  bl_error_boot_type (*toggle_led_init)(void);
  bl_error_boot_type (*toggle_led)(void);

} boot_visual_indicator_if_type;

extern boot_visual_indicator_if_type visual_indicator_if;

#endif  /* BOOT_VISUAL_INDICATION_IF_H */

