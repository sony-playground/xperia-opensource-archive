/*! \file pm_version_init.c 
*  \n
*  \brief This file contains PMIC version auto-detection implementation
*  \n
*  \n &copy; Copyright 2010-2013 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/pm/framework/src/init/pm_version_init.c#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------

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

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

/* QC PMIC Peripheral type value */
#define PM_TYPE_QC_DEVICE        0x51

#define PM_DOUBLE_SLAVE_ID       2
#define PM_SINGLE_SLAVE_ID       1

/* extern global variable to store the pmic device info */
extern pm_device_info_type pm_device_info_arr[PM_MAX_NUM_PMICS];

/* extern global variable to store the pmic device primary slave id value */
extern uint8 pm_primary_slave_id[PM_MAX_NUM_SLAVE_IDS];

/* Flag to check if PMIC Version driver is initialized */
extern boolean pm_version_initialized;

extern uint8  pm_num_slaves_per_pmic;

/** 
 * @name pm_version_detect 
 *  
 * @brief Please refer to device_info.h file for further info on
 *        this function.
 */
pm_err_flag_type pm_version_detect(void) 
{
  pm_err_flag_type      err_flag = PM_ERR_FLAG_SUCCESS;
  uint32                slave_id = 0;
  uint8                 pmic_index = 0;
  uint16                base_addr = 0x0100;
  uint16                metal_rev_addr = base_addr + 0x02;
  pm_register_data_type slave_count  = 0;
  uint32                pmic_slaves = 0;
  const  uint8  num_of_bytes = 5;
#define NUM_OF_BYTES 5
  uint8  rev_id[NUM_OF_BYTES] = {0};



  /* AON_LPI variables */
  uint16            aon_lpi_base_addr = 0x0A00;
  uint16            aon_lpi_rev_addr = aon_lpi_base_addr + 0x04;
  const uint8       aon_lpi_num_bytes = 2;
#define AON_LPI_NUM_BYTES 2
  uint8             aon_lpi_data[AON_LPI_NUM_BYTES] = {0};
 
  boolean           arch_pre7 = pm_is_pmiclib_arch_pre7();
  uint8             min_num_slaves_per_pmic = (arch_pre7) ? PM_DOUBLE_SLAVE_ID : PM_SINGLE_SLAVE_ID;

  /* This function needs to be called only once to read the PMIC
     version info and store it */
  if (pm_version_initialized)
  {
    return err_flag;
  }

  memset(pm_primary_slave_id, INVALID_SLAVE_ID, sizeof(uint8)* PM_MAX_NUM_SLAVE_IDS);
  
  for(slave_id = 0; slave_id < PM_MAX_NUM_SLAVE_IDS;
                slave_id += slave_count, pmic_index += arch_pre7 ? 1 : slave_count)
  {
    if(pmic_index >= PM_MAX_NUM_PMICS)
    {
      break;
    }
     
    /* Read PMIC Device revision information */
    err_flag = pm_comm_read_byte_array(slave_id, 
    	                                metal_rev_addr, num_of_bytes, rev_id, 0);

    /* Make sure if the QC PMIC device exists or not based on if the SPMI
       read operation for PMIC peripheral type value for the specific slave
       id is successful or not and if the data read is equal to QC PMIC
       peripheral type value or not */

    if ((err_flag != PM_ERR_FLAG_SUCCESS) || (rev_id[2] != PM_TYPE_QC_DEVICE) )
    {
      /* Once it's confirmed that the QC PMIC device corresponding to the
         slave id doesn't exist, then disregard the error flag returned
         from SPMI read operation and continue to check for other slave ids */
      slave_count = arch_pre7 ? PM_DOUBLE_SLAVE_ID : PM_SINGLE_SLAVE_ID;
      err_flag = PM_ERR_FLAG_SUCCESS;
      continue;      
    } 
    /* Store PMIC chip revison information in static global array */
    pm_device_info_arr[pmic_index].ePmicModel = (pm_model_type)rev_id[3];
    pm_device_info_arr[pmic_index].nPmicAllLayerRevision = (uint32)rev_id[1];
    pm_device_info_arr[pmic_index].nPmicMetalRevision = (uint32)rev_id[0];

    /*store slave count*/
    slave_count = rev_id[4] ? rev_id[4] : PM_DOUBLE_SLAVE_ID;
    pm_device_info_arr[pmic_index].nSlaveCount = slave_count;

    /* Store PMIC Device slave ids value */
    for (pmic_slaves = 0; pmic_slaves < slave_count; pmic_slaves++)
    {
       pm_primary_slave_id [(pmic_index * min_num_slaves_per_pmic) + pmic_slaves] = (uint8)(slave_id + pmic_slaves);
    }

    /* SW Work around for the wrong REVID subtype used on Yoda PMIC */
    if (pm_device_info_arr[pmic_index].ePmicModel == PMIC_IS_PM855)
    {
      err_flag = pm_comm_read_byte_array(slave_id, aon_lpi_rev_addr, aon_lpi_num_bytes, aon_lpi_data, 0);
      if( (err_flag == PM_ERR_FLAG_SUCCESS) && 
          (aon_lpi_data[0] == PM_HW_MODULE_PON) && 
          (aon_lpi_data[1] == PM_HW_MODULE_PON_AON_LPI) )
      {
        pm_device_info_arr[pmic_index].ePmicModel = PMIC_IS_PM8009;
      }
    }
  }
  pm_get_debug_info()->pm_device_info_arr = pm_device_info_arr;
  pm_version_initialized = TRUE;
  return err_flag;
}
