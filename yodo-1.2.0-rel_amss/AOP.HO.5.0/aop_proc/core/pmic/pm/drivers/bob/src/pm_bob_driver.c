/*! \file pm_bob_driver.c 
*  \n
*  \brief This file contains BOB peripheral driver initialization during which the driver
*         driver data is stored.
*  \n  
*  \n &copy; Copyright 2016 - 2018 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/bob/src/pm_bob_driver.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/22/15   al      Created
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_bob_driver.h"
#include "pm_target_information.h"
#include "device_info.h"
#include "pm_debug.h"

/*===========================================================================

                        GLOBAL VARIABLES 

===========================================================================*/

/*global variable to store the BOB driver data */
pm_bob_data_type *pm_bob_data_arr[PM_MAX_NUM_PMICS];

/*===========================================================================

                     INTERNAL DRIVER FUNCTIONS 

===========================================================================*/
pm_bob_data_type* pm_bob_get_data(uint8 pmic_index)
{
    if(pmic_index < PM_MAX_NUM_PMICS)
    {
        return pm_bob_data_arr[pmic_index];
    }

    return NULL;
}
