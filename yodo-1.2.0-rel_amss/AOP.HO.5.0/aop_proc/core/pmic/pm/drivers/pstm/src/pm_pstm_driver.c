/*! \file pm_pstm_driver.c 
*  \n
*  \brief This file contains PSTM peripheral driver initialization during which the driver
*         driver data is stored. 
*  \n  
*  \n &copy; Copyright 2012-2020 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/drivers/pstm/src/pm_pstm_driver.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------

========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_pstm_driver.h"
#include "pm_target_information.h"
#include "pm_version.h"
#include "pm_comm.h"
#include "device_info.h"
#include "pm_debug.h"

/*===========================================================================

                        GLOBAL VARIABLES 

===========================================================================*/

/* global variable to store the SMPS driver data */
pm_pstm_data_type *pm_pstm_data_arr[PM_MAX_NUM_PMICS];

/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/

/*===========================================================================

                     INTERNAL DRIVER FUNCTIONS 

===========================================================================*/
pm_pstm_data_type* pm_pstm_get_data(uint8 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS) 
  {
      return pm_pstm_data_arr[pmic_index];
  }

  return NULL;
}
