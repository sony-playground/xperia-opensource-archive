/*! \file pm_version.c 
*  \n
*  \brief This file contains PMIC version auto-detection implementation
*  \n
*  \n &copy; Copyright 2010-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/*===================================================================
			        EDIT HISTORY FOR MODULE
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/framework/src/pm_version.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/23/18   aab     Updated to detect Yoda PMIC
11/19/17   aab     Addeded pm_is_target_pre_silicon() and pm_is_pmic_present()
04/14/15   al      Adding changes for Hawker support
07/16/14   akm     Comm change Updates
05/15/13   kt      New PMIC Version driver format.
04/16/13   kt      Added pm_get_pbs_info API.
01/26/13   kt      Added pm_get_pmic_info API.
01/24/13   kt      Adding device index param to pmic model and revision APIs.
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_version.h"
#include "DALSys.h"
#include "pm_utils.h"
#include "pm_comm.h"
#include "device_info.h"
#include "pm_config_sbl.h"
#include "pm_config_target.h"
#include "pm_device.h"
#include "DALDeviceId.h"
#include "DDIPlatformInfo.h"
#include "DDIChipInfo.h"
#include "CoreVerify.h"
#include "pm_target_information.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

/* QC PMIC Peripheral type value */
#define PM_TYPE_QC_DEVICE        0x51

#define PM_DOUBLE_SLAVE_ID 2
#define PM_SINGLE_SLAVE_ID 1

#define PM_NUM_BYTES_REV_ID 7
#define PM_NUM_BYTES        4

#define AON_LPI_BASE_ADDR        0x0A00
#define AON_LPI_REV_ADDR         AON_LPI_BASE_ADDR + 0x04
/* Static global variable to store the pmic device info */
static pm_device_info_type pm_device_info_arr[PM_MAX_BUSES_SUPPORTED][PM_MAX_NUM_PMICS];
static pm_pdm_chip_info_type pm_pdm_chip_info_arr[PM_MAX_BUSES_SUPPORTED][PM_MAX_NUM_PMICS];


/* Static global variable to store the pmic slave id values */
static uint32 supported_slave_ids[PM_MAX_BUSES_SUPPORTED][PM_MAX_NUM_SLAVE_IDS]; 

/* Flag to check if PMIC Version driver is initialized */
static boolean pm_version_initialized = FALSE;

/*num of slaves per pmic should be fixed for a target - current
plan is to support fixed number of slaves per pmic, 
with the existing pmic config we cannot support a 
target having both 1 and 2 slaves per pmic on the same target*/
static const uint8 pm_num_slaves_per_pmic = PM_MAX_NUM_SLAVE_IDS_PER_PMIC; 

/*=========================================================================
      Function Definitions
==========================================================================*/


/** 
 * @name pm_version_detect 
 *  
 * @brief Please refer to device_info.h file for further info on
 *        this function.
 */
pm_err_flag_type pm_version_detect(void) 
{
  pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;
  uint32            slave_id = 0;
  uint8             pmic_index = 0;
  uint16            base_addr = 0x0100;
  uint16            metal_rev_addr = base_addr + 0x02;
  //const             uint8 PM_NUM_BYTES = 4;
  //const             uint8 PM_NUM_BYTES_REV_ID = 7;
  uint8             pmic_rev_info[PM_NUM_BYTES_REV_ID] = {0};
  uint8             rev_id[PM_NUM_BYTES] = {0};
  uint8             aon_lpi_type_subtype[2] = {0};
  
  uint8                 i=0;
  pm_register_data_type slave_count  = 0;
  uint32                pmic_slaves = 0;
  boolean               arch_pre7 = pm_is_pmiclib_arch_pre7();
  uint8 min_num_slaves_per_pmic = (arch_pre7) ? PM_DOUBLE_SLAVE_ID : PM_SINGLE_SLAVE_ID;

  /* This function needs to be called only once to read the PMIC
     version info and store it */
  if (pm_version_initialized)
  {
    return err_flag;
  }

  memset(supported_slave_ids, INVALID_SLAVE_ID, sizeof(uint32)* PM_MAX_NUM_SLAVE_IDS * PM_MAX_BUSES_SUPPORTED);

  for (i = 0; i < PM_MAX_BUSES_SUPPORTED; i++)
  {
    pmic_index = 0;
    slave_id = 0;
    for(slave_id = 0; slave_id < PM_MAX_NUM_SLAVE_IDS; 
          slave_id += slave_count, pmic_index += arch_pre7 ? 1 : slave_count )  
    {
      if(pmic_index >= PM_MAX_NUM_PMICS)
      {
        break;
      }
      
      if(slave_id == 14 || slave_id == 15)
        continue;
      
      /* Read PMIC Device revision information */
      err_flag = pm_comm_read_byte_array_ex( i, slave_id, 
                                          metal_rev_addr, PM_NUM_BYTES, rev_id);
      
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
      pm_device_info_arr[i][pmic_index].ePmicModel = (pm_model_type)rev_id[3];
      pm_device_info_arr[i][pmic_index].nPmicAllLayerRevision = (uint32)rev_id[1];
      pm_device_info_arr[i][pmic_index].nPmicMetalRevision = (uint32)rev_id[0];

      err_flag = pm_comm_read_byte_array_ex(i, slave_id, base_addr, PM_NUM_BYTES_REV_ID, (uint8*) pmic_rev_info);
      pm_pdm_chip_info_arr[i][pmic_index].pdmChipRevision = (pmic_rev_info[3] << 24)| (pmic_rev_info[2] << 16)| (pmic_rev_info[1] << 8) | pmic_rev_info[0]; 
        
      /*store slave count*/
      slave_count = pmic_rev_info[6] ? pmic_rev_info[6] : PM_DOUBLE_SLAVE_ID;
	  
	    /*work around for interlagos PMIC to be detected as single slave id. 
	      Reg 0x106 is not present in interlagos even though it is single slave id PMIC*/
	    
      if(pm_device_info_arr[i][pmic_index].ePmicModel == PMIC_IS_SMB1398)
	    {
		    slave_count = PM_SINGLE_SLAVE_ID;
	    }
	    /*End Interlagos workaround*/
	  
      pm_device_info_arr[i][pmic_index].nSlaveCount = slave_count;
      
      
      /* Store PMIC Device slave ids value */
      
      
      for (pmic_slaves = 0; pmic_slaves < slave_count; pmic_slaves++)
      {
        supported_slave_ids [i][(pmic_index * min_num_slaves_per_pmic) + pmic_slaves] = slave_id + pmic_slaves;
      }
  
      /* SW Work around (using AON_LPI presence only in Yoda) for the wrong REVID subtype used on Yoda PMIC */ 
      if (pm_device_info_arr[i][pmic_index].ePmicModel == PMIC_IS_PM855) 
      {
        err_flag = pm_comm_read_byte_array_ex(i, slave_id, AON_LPI_REV_ADDR, 2, aon_lpi_type_subtype); 
        if( (err_flag == PM_ERR_FLAG_SUCCESS) &&  
            (aon_lpi_type_subtype[0] == PM_HW_MODULE_PON) &&  
            (aon_lpi_type_subtype[1] == PM_HW_MODULE_PON_AON_LPI) ) 
        { 
          pm_device_info_arr[i][pmic_index].ePmicModel = PMIC_IS_PM8009; 
        }
      }

    }//for
  }

  pm_version_initialized = TRUE;
  return err_flag;
}

pm_err_flag_type pm_version_deinit(void)
{
  pm_version_initialized = FALSE;
  
  return PM_ERR_FLAG_SUCCESS;
}


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

  model = pm_device_info_arr[0][pmic_index].ePmicModel;

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

  all_layer_rev = pm_device_info_arr[0][pmic_index].nPmicAllLayerRevision;

  return all_layer_rev;
}

/** 
 * @name pm_get_slave_id
 *  
 * @brief Please refer to device_info.h file for further info on
 *        this function.
 */
pm_err_flag_type pm_get_slave_id(uint8 pmic_index, uint8 slave_id_index, uint32* slave_id_ptr)
{
  
  uint8 supported_sid_idx = 0;

  if(slave_id_ptr == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if( pmic_index >= PM_MAX_NUM_PMICS )
  {
    *slave_id_ptr = PM_MAX_NUM_SLAVE_IDS;
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if((pm_version_initialized == FALSE) || 
      (slave_id_index >= (pm_device_info_arr[0][pmic_index].nSlaveCount)))
  {
    *slave_id_ptr = PM_MAX_NUM_SLAVE_IDS;
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  supported_sid_idx = (TRUE == pm_is_pmiclib_arch_pre7()) ? ((pmic_index * 2)+ slave_id_index) : (pmic_index + slave_id_index);

  *slave_id_ptr = (supported_sid_idx < PM_MAX_NUM_SLAVE_IDS) ? supported_slave_ids[0][supported_sid_idx] : PM_MAX_NUM_SLAVE_IDS;

  if(*slave_id_ptr >= PM_MAX_NUM_SLAVE_IDS) 
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return PM_ERR_FLAG_SUCCESS;
}

uint8 pm_get_num_slaves_per_pmic(void)
{
  return pm_num_slaves_per_pmic;
}


pm_err_flag_type pm_get_pmic_info(uint8 pmic_index, pm_device_info_type* pmic_device_info_ptr)

{
  if((pmic_device_info_ptr == NULL) || (!pm_version_initialized) || 
     (pmic_index >= PM_MAX_NUM_PMICS))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  pmic_device_info_ptr->ePmicModel = pm_device_info_arr[0][pmic_index].ePmicModel;
  pmic_device_info_ptr->nPmicAllLayerRevision = pm_device_info_arr[0][pmic_index].nPmicAllLayerRevision;
  pmic_device_info_ptr->nPmicMetalRevision = pm_device_info_arr[0][pmic_index].nPmicMetalRevision;
  pmic_device_info_ptr->nSlaveCount = pm_device_info_arr[0][pmic_index].nSlaveCount;

  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type pm_resolve_chip_revision(uint32 slave_id, boolean *valid_sid, uint32 *pmic_revision)
{
   pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;
   uint8 pmic_index;
   pm_model_type pmic_model = PMIC_IS_INVALID;

   if (pm_is_slave_id_supported(slave_id) == FALSE)
   {
      *valid_sid = FALSE;
      return PM_ERR_FLAG_INVALID_PARAMETER;
   }

   if (TRUE == pm_is_pmiclib_arch_pre7())
   {
      pmic_index = (uint8)(slave_id / 2);
   }
   else
   {
      pmic_index = (uint8)slave_id;

      //if multiple slave id pmic then point it to first slave of this PMIC since
      //PMIC index corresponding to rest of slave_id will point invalid
      while ((pmic_index > 0) && (pm_get_pmic_model(pmic_index) == PMIC_IS_UNKNOWN))
      {
         pmic_index--;
      }
   }

   pmic_model = pm_get_pmic_model(pmic_index);

   if ((pmic_model == PMIC_IS_INVALID) || (pmic_model == PMIC_IS_UNKNOWN) || (pmic_index >= PM_MAX_NUM_PMICS))
   {
      *valid_sid = FALSE;
      err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
   }
   else
   {
      *valid_sid = TRUE;
      *pmic_revision =  pm_pdm_chip_info_arr[0][pmic_index].pdmChipRevision;
   }

   return err_flag;
}

pm_err_flag_type 
pm_get_peripheral_info(uint8 sid_index, peripheral_info_type *peripheral_info)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_register_address_type base_address = (pm_register_address_type)peripheral_info->base_address;
    uint32 digital_minor_index = 0;
    uint32 digital_major_index = 1;
    uint32 analog_minor_index = 2;
    uint32 analog_major_index = 3;
    uint32 peripheral_type_index = 4;
    uint32 peripheral_subtype_index = 5;
    uint32 peripheral_dummy_index = 6;
    //const uint32 num_of_bytes = 7;
    const uint32 num_of_bytes = 6;
    pm_register_data_type temp_peripheral_info[7] = {0};


    // Reset the peripheral info
    peripheral_info->peripheral_type = 0;
    peripheral_info->peripheral_subtype = 0;
    peripheral_info->analog_major_version = 0;
    peripheral_info->analog_minor_version = 0;
    peripheral_info->digital_major_version = 0;
    peripheral_info->digital_minor_version = 0;

    /* Burst read the peripheral info */
    pm_comm_read_byte_array(sid_index, base_address, num_of_bytes, temp_peripheral_info);

    /* When we burst read multiple bytes from a non-existent peripheral, the data returned
       should be same on all the bytes so we need to do the below check and return error */
    if(temp_peripheral_info[peripheral_subtype_index] == temp_peripheral_info[peripheral_dummy_index])
    {
        return PM_ERR_FLAG_INVALID_PERIPHERAL;
    }

    /* Valid peripheral type can never be 0 */
    if(temp_peripheral_info[peripheral_type_index] == 0)
    {
        return PM_ERR_FLAG_INVALID_PERIPHERAL;
    }

    peripheral_info->peripheral_type = temp_peripheral_info[peripheral_type_index];
    peripheral_info->peripheral_subtype = temp_peripheral_info[peripheral_subtype_index];
    peripheral_info->digital_major_version = temp_peripheral_info[digital_major_index];
    peripheral_info->digital_minor_version = temp_peripheral_info[digital_minor_index];
    peripheral_info->analog_major_version = temp_peripheral_info[analog_major_index];
    peripheral_info->analog_minor_version = temp_peripheral_info[analog_minor_index];

    return err_flag;
}



boolean 
pm_is_pmic_present(uint8 pmic_index)
{
    pm_model_type pmic_model = PMIC_IS_INVALID;
    pmic_model = pm_get_pmic_model(pmic_index);

    if((pmic_model == PMIC_IS_UNKNOWN) || (pmic_model == PMIC_IS_INVALID))
    {
       return FALSE; //PMIC NOT present
    }
    else
    {
       return TRUE; // PMIC is present
    }
}


boolean
pm_is_target_pre_silicon(void)
{
    DalPlatformInfoPlatformType platform_type = DALPLATFORMINFO_TYPE_UNKNOWN;

    platform_type = DalPlatformInfo_Platform();

    if (platform_type == DALPLATFORMINFO_TYPE_RUMI)
    {
       return TRUE; //Target is Pre silicon
    }
    else
    {
       return FALSE;//Target is NOT pre silicon
    }
}

boolean pm_is_slave_id_supported(uint8 slave_id)
{
  boolean slave_id_supported = FALSE;

  if((pm_version_initialized == TRUE) &&
     (slave_id < PM_MAX_NUM_SLAVE_IDS) &&
     (supported_slave_ids[0][slave_id] <= slave_id) &&
     (supported_slave_ids[0][slave_id] < PM_MAX_NUM_SLAVE_IDS)
     )
  {
      slave_id_supported = TRUE;
  }

  return slave_id_supported;
}

uint32 
pm_get_primary_pmic_index(void)
{
  return PM_PRIMARY_PMIC_INDEX;
}

uint8 pm_get_num_of_sid_supported(uint8 pmic_index)
{
   uint8 number_of_slave_ids = 0;

   if ((pmic_index >= PM_MAX_NUM_PMICS)
       || (pm_version_initialized != TRUE)
       || ( pm_is_pmic_present(pmic_index) == FALSE)
       )
   {
      number_of_slave_ids = 0;
   }
   else
   {
      number_of_slave_ids = pm_device_info_arr[0][pmic_index].nSlaveCount;
   }

   return number_of_slave_ids;
}

boolean pm_is_pmiclib_arch_pre7(void)
{
   return PMICLIB_ARCH_PRE7;
}

pm_err_flag_type pm_get_pmic_index_from_slave(uint8 slave_id , uint8 *pmic_index)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

   if(FALSE == pm_is_slave_id_supported(slave_id))
   {
     return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED ;
   }
   
   if(TRUE == pm_is_pmiclib_arch_pre7())
   {
     *pmic_index = slave_id / 2 ;
   }
   else
   {
     if ((slave_id > 0) && (pm_get_pmic_model(slave_id) == PMIC_IS_UNKNOWN))
     {
       slave_id--;
     }
	 
     *pmic_index = slave_id;
	  	
   }
   
   return err_flag;
}

uint8 
pm_get_num_of_sid_supported_ex(uint32 bus_id,  uint8 pmic_index)
{
   uint8 number_of_slave_ids = 0;

   if ((pmic_index >= PM_MAX_NUM_PMICS)
       || (pm_version_initialized != TRUE)
       || ( pm_is_pmic_present(pmic_index) == FALSE 
       || bus_id >= PM_MAX_BUSES_SUPPORTED)
       )
   {
      number_of_slave_ids = 0;
   }
   else
   {
      number_of_slave_ids = pm_device_info_arr[bus_id][pmic_index].nSlaveCount;
   }

   return number_of_slave_ids;
}

pm_err_flag_type 
pm_get_pmic_info_ex(uint32 bus_id, uint8 pmic_index, pm_device_info_type* pmic_device_info_ptr)

{

  if((pmic_device_info_ptr == NULL) || (!pm_version_initialized) || 
     (pmic_index >= PM_MAX_NUM_PMICS) || bus_id >= PM_MAX_BUSES_SUPPORTED )
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  

  pmic_device_info_ptr->ePmicModel = pm_device_info_arr[bus_id][pmic_index].ePmicModel;
  pmic_device_info_ptr->nPmicAllLayerRevision = pm_device_info_arr[bus_id][pmic_index].nPmicAllLayerRevision;
  pmic_device_info_ptr->nPmicMetalRevision = pm_device_info_arr[bus_id][pmic_index].nPmicMetalRevision;
  pmic_device_info_ptr->nSlaveCount = pm_device_info_arr[bus_id][pmic_index].nSlaveCount;

  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type 
pm_get_pmic_index_from_slave_ex(uint32 bus_id, uint8 slave_id , uint8 *pmic_index)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   
   if( (bus_id >= PM_MAX_BUSES_SUPPORTED) ||  FALSE == pm_is_slave_id_supported_ex(bus_id, slave_id))
   {
     return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
   }
   
   if(TRUE == pm_is_pmiclib_arch_pre7())
   {
     *pmic_index = slave_id / 2 ;
   }
   else
   {
     if ((slave_id > 0) && (pm_get_pmic_model_ex(bus_id, slave_id) == PMIC_IS_UNKNOWN))
     {
       slave_id--;
     }
     *pmic_index = slave_id ;	  	
   }
	 
   return err_flag;
}


pm_model_type 
pm_get_pmic_model_ex(uint32 bus_id, uint8 pmic_index)
{
  pm_model_type model = PMIC_IS_INVALID;

  if((!pm_version_initialized) || (pmic_index >= PM_MAX_NUM_PMICS) ||
      (bus_id >= PM_MAX_BUSES_SUPPORTED)) 
  {
    return model;
  }

  model = pm_device_info_arr[bus_id][pmic_index].ePmicModel;
	 
  return model;
}

boolean 
pm_is_slave_id_supported_ex(uint32 bus_id, uint8 slave_id)
{
  boolean slave_id_supported = FALSE;
  
  if(bus_id >= PM_MAX_BUSES_SUPPORTED)
  {
    return slave_id_supported;  
  }

  if((pm_version_initialized == TRUE) &&
     (slave_id < PM_MAX_NUM_SLAVE_IDS) &&
     (supported_slave_ids[bus_id][slave_id] <= slave_id) &&
     (supported_slave_ids[bus_id][slave_id] < PM_MAX_NUM_SLAVE_IDS)
     )
  {
      slave_id_supported = TRUE;
  }

  return slave_id_supported;
}


pm_err_flag_type 
pm_resolve_chip_revision_ex(uint32 bus_id, uint32 slave_id, boolean *valid_sid, uint32 *pmic_revision)
{
   pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;
   uint8 pmic_index;
   pm_model_type pmic_model = PMIC_IS_INVALID;

   if (pm_is_slave_id_supported_ex(bus_id, slave_id) == FALSE)
   {
      *valid_sid = FALSE;
      return PM_ERR_FLAG_INVALID_PARAMETER;
   }

   if (TRUE == pm_is_pmiclib_arch_pre7())
   {
      pmic_index = (uint8)(slave_id / 2);
   }
   else
   {
      pmic_index = (uint8)slave_id;

      //if multiple slave id pmic then point it to first slave of this PMIC since
      //PMIC index corresponding to rest of slave_id will point invalid
      while ((pmic_index > 0) && (pm_get_pmic_model_ex(bus_id, pmic_index) == PMIC_IS_UNKNOWN))
      {
         pmic_index--;
      }
   }

   pmic_model = pm_get_pmic_model_ex(bus_id, pmic_index);
	  	
   if ((pmic_model == PMIC_IS_INVALID) || (pmic_model == PMIC_IS_UNKNOWN) || (pmic_index >= PM_MAX_NUM_PMICS))
   {
      *valid_sid = FALSE;
      err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
   }
   else
   {
      *valid_sid = TRUE;
      *pmic_revision =  pm_pdm_chip_info_arr[bus_id][pmic_index].pdmChipRevision;
   }
   
   return err_flag;
}

pm_err_flag_type 
pm_get_slave_id_ex(uint32 bus_id, uint8 pmic_index, uint8 slave_id_index, uint32* slave_id_ptr)
{
  
  uint8 supported_sid_idx = 0;

  if(slave_id_ptr == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if( pmic_index >= PM_MAX_NUM_PMICS )
  {
    *slave_id_ptr = PM_MAX_NUM_SLAVE_IDS;
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if(bus_id >= PM_MAX_BUSES_SUPPORTED)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if((pm_version_initialized == FALSE) || 
      (slave_id_index >= (pm_device_info_arr[bus_id][pmic_index].nSlaveCount)))
  {
    *slave_id_ptr = PM_MAX_NUM_SLAVE_IDS;
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  supported_sid_idx = (TRUE == pm_is_pmiclib_arch_pre7()) ? ((pmic_index * 2)+ slave_id_index) : (pmic_index + slave_id_index);

  *slave_id_ptr = (supported_sid_idx < PM_MAX_NUM_SLAVE_IDS) ? supported_slave_ids[bus_id][supported_sid_idx] : PM_MAX_NUM_SLAVE_IDS;

  if(*slave_id_ptr >= PM_MAX_NUM_SLAVE_IDS) 
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return PM_ERR_FLAG_SUCCESS;
}

