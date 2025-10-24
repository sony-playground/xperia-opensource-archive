/*! \file pm_comm.c
*
*  \brief This file contains processor specific initialization functions.
*         This file contains code for Target specific settings and modes.
*
*  &copy; Copyright 2014 - 2020 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/comm/src/pm_comm.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ------------------------------------------------
10/12/15   aab    Updated pm_comm_info_init()
07/16/14   akm    Multiple PMIC's configuration support ( >2 PMICS)

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_resource_manager.h"
#include "pm_target_information.h"
#include "pm_comm.h"
#include "hw_module_type.h"
#include "CoreVerify.h"
#include "pm_version.h"
#include "device_info.h"
#include "pm_device.h"


/* PMIC Comm Info, Each PMIC device has 1 or more slave ids */
static pm_comm_info_type *pm_comm_info = NULL ;
static boolean pm_comm_info_initialized = FALSE;

void pm_comm_info_init(void)
{
  uint8  pmic_counter = 0;
  uint32 total_slave_count = 0;
  uint32 slave_id_counter = 0;
  uint8  num_slaves_per_pmic = 0;

  if (pm_comm_info_initialized == TRUE)
  {
    return;
  }

  pm_malloc(PM_MAX_NUM_SLAVE_IDS * sizeof(pm_comm_info_type),
            (void **)&pm_comm_info);

  while (pmic_counter < PM_MAX_NUM_PMICS)
  {
    num_slaves_per_pmic = pm_get_num_of_sid_supported(pmic_counter);

    if (num_slaves_per_pmic == 0)
    {
      total_slave_count += pm_is_pmiclib_arch_pre7() ? 2 : 1;
    }

    for (slave_id_counter = 0;
         slave_id_counter < num_slaves_per_pmic;
         slave_id_counter++, total_slave_count++)
    {
      pm_comm_info[total_slave_count].mCommType = SPMI_1_0Type;
      pm_comm_info[total_slave_count].pmic_index = pmic_counter;
      pm_get_slave_id(pmic_counter, slave_id_counter,
                      &pm_comm_info[total_slave_count].slave_id);
    }
    
    if( pm_is_pmiclib_arch_pre7() )
    {
        pmic_counter++;
    }
    else
    {
        pmic_counter += (num_slaves_per_pmic == 0) ? 1 : num_slaves_per_pmic;
    }
    
  }

  pm_comm_info_initialized = TRUE;
}


pm_comm_info_type*
pm_comm_get_comm_info(uint32 pmic_index,
                      uint32 slave_id_index)
{
  uint32 comm_info_idx = 0;

  if (!pm_comm_info_initialized) return NULL;

  if (TRUE == pm_is_pmiclib_arch_pre7())
  {
    comm_info_idx = (pmic_index * pm_get_num_slaves_per_pmic()) + slave_id_index;
  }
  else
  {
    comm_info_idx = pmic_index + slave_id_index;
  }

  return &pm_comm_info[comm_info_idx];
}

boolean
pm_comm_initialized(void)
{
  return pm_comm_info_initialized;
}
