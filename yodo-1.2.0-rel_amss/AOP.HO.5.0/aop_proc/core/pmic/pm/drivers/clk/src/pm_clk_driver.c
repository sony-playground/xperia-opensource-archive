/*! \file pm_clk_driver.c
 *  \n
 *  \brief This file contains CLOCK peripheral driver initialization during which the driver
 *         driver data is stored.
 *  \n
 *  \n &copy; Copyright 2013-2018 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/clk/src/pm_clk_driver.c#1 $
 
when        who     what, where, why
--------    ---     ----------------------------------------------------------
08/12/13    aks      Fix KW Errors   
04/12/13    aks      Created as part of Code refactoring.
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_clk_driver.h"
#include "pm_version.h"
#include "pm_target_information.h"
#include "device_info.h"
#include "pm_debug.h"


/*===========================================================================

                        GLOBAL VARIABLES 

===========================================================================*/

/* global variable to store the CLK driver data */
pm_clk_data_type *pm_clk_data_arr[PM_MAX_NUM_PMICS];

pm_clk_data_type* pm_clk_get_data(uint8 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS)
  {
       return pm_clk_data_arr[pmic_index];
  }
  return NULL;
   
}
