/*! \file pm_ldo_driver.c
*  \n
*  \brief This file contains LDO peripheral driver initialization during which the driver
*         driver data is stored.
*  \n
*  \n &copy; Copyright 2012-2018 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/ldo/src/pm_ldo_driver.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/25/13   aks     Code Refactoring: Removing PMIC_SubRsc from pwr algs   
04/12/13   hs      Code refactoring.
02/27/13   hs      Code refactoring.
12/06/12   hw      Rearchitecturing module driver to peripheral driver
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_ldo_driver.h"
#include "pm_target_information.h"
#include "pm_comm.h"
#include "device_info.h"
#include "pm_debug.h"


/*===========================================================================

                        GLOBAL VARIABLES 

===========================================================================*/

/*global variable to store the LDO driver data */
pm_ldo_data_type *pm_ldo_data_arr[PM_MAX_NUM_PMICS];

/*===========================================================================

                     INTERNAL DRIVER FUNCTIONS 

===========================================================================*/
pm_ldo_data_type* pm_ldo_get_data(uint8 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS) 
  {
      return pm_ldo_data_arr[pmic_index];
  }

  return NULL;
}
