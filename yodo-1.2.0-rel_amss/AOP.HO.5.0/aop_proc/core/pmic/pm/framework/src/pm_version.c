/*! \file pm_version.c 
*  \n
*  \brief This file contains PMIC version auto-detection implementation
*  \n
*  \n &copy; Copyright 2010-2013 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/framework/src/pm_version.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/15/13   kt      New PMIC Version driver format.
04/12/13   hs      Code refactoring.
02/27/13   hs      Code refactoring.
01/26/13   kt      Added pm_get_pmic_info API.
01/24/13   kt      Adding device index param to pmic model and revision APIs.
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_version.h"
#include "pm_utils.h"
#include "pm_comm.h"
#include "device_info.h"
#include "pm_debug.h"
#include "pm_target_information.h"
#include "pm_config_target.h"
/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

/*global variable to store the pmic device info */
pm_device_info_type pm_device_info_arr[PM_MAX_NUM_PMICS];

/*global variable to store the pmic device primary slave id value */
uint8 pm_primary_slave_id[PM_MAX_NUM_SLAVE_IDS];

/* Flag to check if PMIC Version driver is initialized */
boolean pm_version_initialized = FALSE;

/*num of slaves per pmic should be fixed for a target - current
plan is to support fixed number of slaves per pmic, 
with the existing pmic config we cannot support a 
target having both 1 and 2 slaves per pmic on the same target*/
const uint8 pm_num_slaves_per_pmic = 2;

/*=========================================================================
      Function Definitions
==========================================================================*/
/** 
 * @name pm_get_pmic_model 
 *  
 * @brief This is a public API. Please refer to pm_version.h 
 *        file for further info on this function.
 */
pm_model_type pm_get_pmic_model(uint8 pmic_index)
{
  pm_model_type model = PMIC_IS_INVALID;

  if((!pm_version_initialized) ||  (pmic_index >= PM_MAX_NUM_PMICS)) 
  {
    return model;
  }

  model = pm_device_info_arr[pmic_index].ePmicModel;

  return model;
}

/** 
 * @name pm_get_pmic_revision 
 *  
 * @brief This is a public API. Please refer to pm_version.h 
 *        file for further info on this function.
 */
uint8 pm_get_pmic_revision(uint8 pmic_index)
{
  uint8 all_layer_rev = 0;

  if((!pm_version_initialized) || (pmic_index >= PM_MAX_NUM_PMICS)) 
  {
    return all_layer_rev;
  }

  all_layer_rev = pm_device_info_arr[pmic_index].nPmicAllLayerRevision;

  return all_layer_rev;
}

/** 
 * @name pm_get_slave_id
 *  
 * @brief Please refer to device_info.h file for further info on
 *        this function.
 */
pm_err_flag_type pm_get_slave_id(uint8 pmic_index, uint8 slave_id_index, uint32 *slave_id_ptr)
{

  if(slave_id_ptr == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if((pm_version_initialized == FALSE) || 
      (slave_id_index >= (pm_device_info_arr[pmic_index].nSlaveCount)))
  {
    *slave_id_ptr = PM_MAX_NUM_SLAVE_IDS;
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if( pmic_index >= PM_MAX_NUM_PMICS )
  {
    *slave_id_ptr = PM_MAX_NUM_SLAVE_IDS;
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (TRUE == pm_is_pmiclib_arch_pre7())
  {                                    
     *slave_id_ptr = (uint32)pm_primary_slave_id [(pmic_index * 2)+ slave_id_index];
  }
  else
  {
    *slave_id_ptr = (uint32)pm_primary_slave_id [pmic_index + slave_id_index];
  }

  if(*slave_id_ptr >= PM_MAX_NUM_SLAVE_IDS) 
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type pm_get_pmic_info(uint8 pmic_index, pm_device_info_type* pmic_device_info_ptr)

{
  if((pmic_device_info_ptr == NULL) || (!pm_version_initialized) || 
     (pmic_index >= PM_MAX_NUM_PMICS))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  pmic_device_info_ptr->ePmicModel = pm_device_info_arr[pmic_index].ePmicModel;
  pmic_device_info_ptr->nPmicAllLayerRevision = pm_device_info_arr[pmic_index].nPmicAllLayerRevision;
  pmic_device_info_ptr->nPmicMetalRevision = pm_device_info_arr[pmic_index].nPmicMetalRevision;
  pmic_device_info_ptr->nSlaveCount = pm_device_info_arr[pmic_index].nSlaveCount;

  return PM_ERR_FLAG_SUCCESS;
}


uint8 pm_get_num_of_sid_supported(uint8 pmic_index)
{
    uint8 number_of_slave_ids = 0;
    pm_model_type pmic_model = PMIC_IS_INVALID;
    pmic_model = pm_get_pmic_model(pmic_index);

    if((pmic_model == PMIC_IS_UNKNOWN) || (pmic_model == PMIC_IS_INVALID))
    {
      number_of_slave_ids = 0;
    }
    else
    {
      number_of_slave_ids = pm_device_info_arr[pmic_index].nSlaveCount;
    }

    return number_of_slave_ids;
}

boolean pm_is_pmiclib_arch_pre7(void)
{
   return PMICLIB_ARCH_PRE7;
}
