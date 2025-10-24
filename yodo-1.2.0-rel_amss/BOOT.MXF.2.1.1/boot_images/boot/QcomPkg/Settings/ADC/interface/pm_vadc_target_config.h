#ifndef __PM_VADC_TARGET_CONFIG_H__
#define __PM_VADC_TARGET_CONFIG_H__

/*============================================================================
  FILE:         pm_vadc_target_config.h

  OVERVIEW:     Header file for VADC target config data.

  DEPENDENCIES: None

                Copyright (c) 2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------


============================================================================*/
#include "AdcBsp.h"

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

/*----------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/
AdcBspType* 
pm_vadc_target_get_adc_bsp (uint32 bspId);

uint32 
pm_vadc_target_get_adc_bsp_id (void);

const char* 
pm_vadc_target_get_dt_path (uint32 deviceId);

#endif
