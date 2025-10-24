/*! \file  pm_pbs_rtrr.c 
 *  
 *  \brief  This file contains the pmic PBS implementation
 *  \details  This file contains the pm_pbs_rtrr dump during the reset
 *  
 *  &copy; Copyright 2014-2019, 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pbs/src/pm_pbs_rtrr.c#1 $ 
$DateTime: 2022/08/18 10:15:46 $  $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ---------------------------------------------------------- 

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_pbs_driver.h"
#include "pm_pbs_rtrr.h"
#include "pm_pbs_info.h"
#include "pm_utils.h"
#include "DDIPlatformInfo.h"
#include "DDIChipInfo.h"
#include "pm_config_sbl.h"

#define PM_PBS_RAM_START_ADDR 0x400
#define PM_PBS_RTRR_START_ADDR 0x20
#define PM_PBS_RTRR_DUMP_SIZE_DWORDS 160
#define MEM_INTF_RD_DATA0_OFFS         0x4C
#define PERIPH_OFFSET                0x100

/*=========================================================================
      Function Definitions
==========================================================================*/
pm_err_flag_type
pm_pbs_rtrr_ram_dump(uint32 slave_id, pm_pbs_rtrr_dump_data_type *pm_pbs_rtrr_data)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 read_data = 0;
  uint8 read_counter = 0;
  uint16 rtrr_dataset_start_addr = 0;
  uint16 pbs_ram_rtrr_dataset_start_addr_placeholder = 0;
  pm_pbs_info_data_type **pm_pbs_temp_data = NULL;
  pm_pbs_info_data_type *pm_pbs_data = NULL;
  uint8 pmic_index = 0;
  uint8 periph_id = 0;
  
  //calculate pmic_index from sid, for arch_pre7 FALSE case we are passing SID = 0 always so pmic_index = slave_id
  err_flag = pm_get_pmic_index_from_slave(slave_id, &pmic_index);
  
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED ;
  }

  /* Retrieve PBS info config data */
  pm_pbs_temp_data = (pm_pbs_info_data_type**)pm_target_information_get_specific_info(PM_PROP_PBS_INFO);
  if(NULL == pm_pbs_temp_data)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  pm_pbs_data = pm_pbs_temp_data[pmic_index];
	periph_id = (pm_pbs_data->perph_base_addr)/ PERIPH_OFFSET;
	
  /* Configuring the start address for reading RTRR info.	 */
  pbs_ram_rtrr_dataset_start_addr_placeholder = 0x400 + PM_PBS_RTRR_START_ADDR ;
  err_flag = pm_pbs_config_access(slave_id, pbs_ram_rtrr_dataset_start_addr_placeholder, PM_PBS_ACCESS_READ_BURST, PM_PBS_TYPE_RAM, periph_id);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  
  /* Reading the Start address of the RTRR data set in PBS RAM and storing it in temp variable */
  err_flag = pm_comm_read_byte_array(slave_id, pm_pbs_data->perph_base_addr+MEM_INTF_RD_DATA0_OFFS, 4, (uint8*)&read_data);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  rtrr_dataset_start_addr = (uint32)(read_data & 0x0000FFFF);
  /* Configuring to disable PBS core read access */
  err_flag |= pm_pbs_disable_access(slave_id, PM_PBS_TYPE_RAM, periph_id);
  
  read_data = 0 ;
  
  err_flag = pm_pbs_config_access(slave_id, rtrr_dataset_start_addr , PM_PBS_ACCESS_READ_BURST, PM_PBS_TYPE_RAM, periph_id);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  
  /* Reading the thre requested bytes from RTRR read_counter < PM_PBS_RTRR_DUMP_SIZE_DWORDS */
  for (read_counter = 0; read_counter < PM_PBS_RTRR_DUMP_SIZE_DWORDS  ; read_counter++)
  {
    err_flag = pm_comm_read_byte_array(slave_id, pm_pbs_data->perph_base_addr+MEM_INTF_RD_DATA0_OFFS, 4, (uint8*)&read_data);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
    
    if(read_counter == 0 )
    {
      pm_pbs_rtrr_data->version = (uint32)read_data;
    }
    
    if ((uint32)read_data == 0x00000500)
    {
      break;
    }
    
    pm_pbs_rtrr_data->data[read_counter] = (uint32)read_data;
  }
  
  /* Configuring to disable PBS core read access */
  err_flag |= pm_pbs_disable_access(slave_id, PM_PBS_TYPE_RAM, periph_id);
  
  return err_flag;
}
