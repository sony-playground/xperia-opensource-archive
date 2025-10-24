/*! \file  pm_pbs_driver.c 
 *  
 *  \brief  This file contains the pmic PBS implementation
 *  \details  This file contains the pm_pbs_ram_image_load & pm_pbs_ram_image_verify API
 *  implementation for SBl1 boot and also implementation for  other helper functions
 *  used in PBS driver.
 *  
 *  &copy; Copyright 2014-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pbs/src/pm_pbs_driver.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when         who     what, where, why
----------   ---     ---------------------------------------------------------- 
07/31/2016   aab     Removed pbs ram load/verify delay
07/31/2016   aab     Updated pbs ram load/verify delay to 5us
12/04/2015   aab     Updated pm_pbs_ram_image_verify() 
07/16/2014   akm     Comm change Updates
06/02/2014   aab     Updated to use pm_clk_busy_wait() API
12/18/2013   aab     Updated pm_pbs_ram_image_load() and  pm_pbs_ram_image_verify() 
03/20/2013   kt      Moving and renaming the file to pm_pbs_driver.c 
                     from pm_pbs.c and adding comments.
10/19/2012   umr     PBS Core Driver.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_pbs_driver.h"
#include "pm_pbs_client.h"
#include "pm_pbs_info.h"
#include "pm_log_utils.h"
#include "CoreVerify.h"
#include "pm_config_sbl.h"

#define PM_PBS_CORE_VER_SUPPORT_NEW_SEQ 0x0303 //maj version 0x03 , minor version 0x03
#define PM_PCE_ENABLE_DONE_STATUS_POLLING_MAX 10
#define PM_PBS_CORE_VER_SUPPORT_8BYTE 0x0501 //maj version 0x05 , minor version 0x01
#define PM_PBS_VERSION_3P0  0x0300
#define PM_PBS_VERSION_3P1  0x0301
#define PM_PBS_VERSION_5P0  0x0500
#define PBS_SIZE_MULTIPLIER 32

#define PBS_CORE_REVISION1_ADDR           0x00
#define PBS_CORE_REVISION2_ADDR           0x01
#define PERIPH_TYPE_OFFSET_ADDR           0x04 
#define PERIPH_SUBTYPE_OFFSET_ADDR        0x05 
#define NO_OF_CLIENTS_REG_OFFST           0x07
#define MEM_INTF_CFG_ADDR                 0x40
#define MEM_INTF_CTL_ADDR                 0x41
#define MEM_INTF_ADDR_LSB_ADDR            0x42
#define MEM_INTF_WR_DATA0_ADDR            0x48
#define MEM_INTF_RD_DATA0_ADDR            0x4C
#define MEM_INTF_WR_DATA0_8BYTE_ADDR      0x80
#define MEM_INTF_RD_DATA0_8BYTE_ADDR      0x88
#define PCE_ENABLE_DONE_STATUS_ADDR       0x9D
#define PMIC5_OTP_CFG1_ADDR               0xEB
#define PMIC5_OTP_PCE_FORCE_ON_ADDR       0xE9
#define PBS_CORE_RAM_CFG1_ADDR            0xA0
#define PBS_CORE_RAM_CFG3_ADDR            0xA6   // MSB  PBS RAM Size
#define PBS_CORE_NVM_CFG1_UPTO_V5P0_ADDR  0xA2
#define PBS_CORE_NVM_CFG1_V5P0_ONWA_ADDR  0xA3
#define PBS_CORE_NVM_CFG2_UPTO_V5P0_ADDR  0xA3
#define PBS_CORE_NVM_CFG2_V5P0_ONWA_ADDR  0xA4
#define FOUR_BYTES_MASK                0xFFFFFFFF

#define PMIC_PBS_CORE_MAX_HW_VER       0x64
#define PERIPH_OFFSET                0x100

/* Static global variable to store the PBS data */
static pm_pbs_data_type *pm_pbs_data_arr[PM_MAX_NUM_PMICS]; 

static uint8 pbs_core_count = 0;

static pm_pbs_client_register_info_type pbs_client_reg = 
{
  .peripheral_offset = 0x100,
  .hw_trig_re_en     = 0x0040,
  .hw_trig_fe_en     = 0x0041, 
  .trig_ctl          = 0x0042, 
  .en_ctl1           = 0x0046,
  .trig_latched_clr  = 0x0048, 
  .scratch1          = 0x0050, 
  .scratch2          = 0x0051
};

/*=========================================================================
      PBS Driver Init
==========================================================================*/

void pm_pbs_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index)
{
  pm_pbs_data_type *pbs_core_ptr = NULL;
  uint8 no_of_clients =0;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 num_of_peripherals = 0;

  // Abort if the new PBS client driver is used on HW with old PBS client subtype
  // New driver doesn't support the old PBS client peripheral
  if (peripheral_info->peripheral_subtype == PM_HW_MODULE_PBS_CLIENT) 
  {
    CORE_VERIFY(0);
  }

  if ((peripheral_info->peripheral_subtype == PM_HW_MODULE_PBS_CLIENT_1TRIG) ||
      (peripheral_info->peripheral_subtype == PM_HW_MODULE_PBS_CLIENT_4TRIG))
  {
    return;
  }

  pbs_core_ptr = pm_pbs_data_arr[pmic_index];
  
  if (pbs_core_ptr == NULL)
  {
    num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_PBS_CORE, pmic_index);
    if (num_of_peripherals == 0)
    {
      return;
    }

    //Reset PBS Core Count for Every PMIC
    pbs_core_count = 0 ;
    pm_malloc( sizeof(pm_pbs_data_type), (void**)&pbs_core_ptr);
    
    pbs_core_ptr->dig_maj_min_ver = ((peripheral_info->digital_major_version << 4) | 
                                     (peripheral_info->digital_minor_version));

    CORE_VERIFY(pbs_core_ptr->dig_maj_min_ver <= PMIC_PBS_CORE_MAX_HW_VER);
 
    /* Assign Comm ptr */
    pbs_core_ptr->comm_ptr = comm_ptr;
 
    /* PBS Register Info - Obtaining Data through dal config */
    pbs_core_ptr->pbs_client_reg_table = &pbs_client_reg;
        
    CORE_VERIFY_PTR(pbs_core_ptr->pbs_client_reg_table);
 
    pbs_core_ptr->no_of_pbs_core = num_of_peripherals;
 
    pm_malloc(sizeof(pm_register_address_type)*(pbs_core_ptr->no_of_pbs_core), (void**)&(pbs_core_ptr->base_address));
    pbs_core_ptr->base_address[pbs_core_count] = peripheral_info->base_address;
 
    err_flag = pm_comm_read_byte(comm_ptr->slave_id, pbs_core_ptr->base_address[pbs_core_count] + NO_OF_CLIENTS_REG_OFFST , &no_of_clients);
    CORE_VERIFY (err_flag == PM_ERR_FLAG_SUCCESS);
    
    pm_malloc(sizeof(uint8)*(pbs_core_ptr->no_of_pbs_core), (void**)&(pbs_core_ptr->pbs_client_count));
    pbs_core_ptr->pbs_client_count[pbs_core_count] = no_of_clients;
 
    CORE_VERIFY(pbs_core_ptr->pbs_client_count[pbs_core_count] != 0);

    pm_pbs_data_arr[pmic_index] = pbs_core_ptr;

  }  
  else
  {
    pbs_core_count = pbs_core_count + 1;

    if(pbs_core_count >= pbs_core_ptr->no_of_pbs_core)
    {
      CORE_VERIFY(0);
    }

    pbs_core_ptr->base_address[pbs_core_count] = peripheral_info->base_address;

    pm_comm_read_byte(comm_ptr->slave_id, pbs_core_ptr->base_address[pbs_core_count] + NO_OF_CLIENTS_REG_OFFST , &no_of_clients);
    
    pbs_core_ptr->pbs_client_count[pbs_core_count] = no_of_clients;

    CORE_VERIFY(pbs_core_ptr->pbs_client_count[pbs_core_count] != 0);
    
  }    
  
}


/*=========================================================================
      Function Definitions
==========================================================================*/
static pm_err_flag_type
pm_pbs_get_pbs_core_ver(uint8 slave_id, uint16 core_base_addr, uint32 *version)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 maj_ver = 0, min_ver = 0;

  err_flag |= pm_comm_read_byte(slave_id, core_base_addr + PBS_CORE_REVISION1_ADDR,
                                &min_ver);

  err_flag |= pm_comm_read_byte(slave_id, core_base_addr + PBS_CORE_REVISION2_ADDR,
                                &maj_ver);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  if(version == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    return err_flag;
  }
  *version = (uint32)maj_ver << 8 | (uint32)min_ver;

  return err_flag;

}


pm_err_flag_type
pm_pbs_get_mem_info(uint32 slave_id, uint16 *pbs_start_addr,
                         uint16 *otp_size, uint16 *pbs_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 otp_size_base = 0, otp_size_mult = 0, pbs_size_base_lsb = 0, otp_mask = 0x3, pbs_size_base_msb = 0;

  uint8 pmic_index;
  uint16 pbs_size_base = 0;
  uint32 supported_version =0;
  pm_pbs_info_data_type **pm_pbs_temp_data = NULL;
  pm_pbs_info_data_type *pm_pbs_data = NULL;
  pm_register_address_type reg_offset = 0;
  
  if(pbs_start_addr == NULL || pbs_size == NULL || otp_size == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    return err_flag;
  }

  /* Retrieve PBS info config data */
  pm_pbs_temp_data = (pm_pbs_info_data_type**)pm_target_information_get_specific_info(PM_PROP_PBS_INFO);
  if(NULL == pm_pbs_temp_data)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  
  err_flag = pm_get_pmic_index_from_slave(slave_id, &pmic_index);

  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED ;
  }
  
  pm_pbs_data = pm_pbs_temp_data[pmic_index];
  if(NULL == pm_pbs_data)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag |= pm_pbs_get_pbs_core_ver (slave_id, pm_pbs_data->perph_base_addr, &supported_version);


  reg_offset = (supported_version > PM_PBS_VERSION_5P0) ? PBS_CORE_NVM_CFG1_V5P0_ONWA_ADDR : PBS_CORE_NVM_CFG1_UPTO_V5P0_ADDR;
  err_flag |= pm_comm_read_byte(slave_id, pm_pbs_data->perph_base_addr + reg_offset,
                                &otp_size_base);

  reg_offset = (supported_version > PM_PBS_VERSION_5P0) ? PBS_CORE_NVM_CFG2_V5P0_ONWA_ADDR : PBS_CORE_NVM_CFG2_UPTO_V5P0_ADDR;							
  err_flag |= pm_comm_read_byte(slave_id, pm_pbs_data->perph_base_addr + reg_offset,
                                &otp_size_mult);

  err_flag |= pm_comm_read_byte(slave_id, pm_pbs_data->perph_base_addr + PBS_CORE_RAM_CFG1_ADDR,
                                &pbs_size_base_lsb);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  *otp_size = otp_size_base * (1 << (otp_size_mult & otp_mask)) * 8;

  if(supported_version >= PM_PBS_VERSION_3P0)
  {
    *pbs_start_addr = 4 * (*otp_size);
  }
  else
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  /*For backward compatibility with 3.1 pbs version keep both ways of pbs size
   *calculations
   */
 
  if ((pbs_size_base_lsb <= 8) || ((supported_version >= PM_PBS_VERSION_3P1 ) && (supported_version < PM_PBS_VERSION_5P0 ) ))
  {
    *pbs_size = pbs_size_base_lsb * PBS_SIZE_MULTIPLIER;
  }

  else if (supported_version >= PM_PBS_VERSION_5P0)
  {
    reg_offset = (supported_version > PM_PBS_VERSION_5P0) ? (PBS_CORE_RAM_CFG1_ADDR + 1) : PBS_CORE_RAM_CFG3_ADDR;
	
    err_flag |= pm_comm_read_byte(slave_id, pm_pbs_data->perph_base_addr + reg_offset, &pbs_size_base_msb);

    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }

    pbs_size_base = (pbs_size_base_msb << 8) | pbs_size_base_lsb;
    *pbs_size = pbs_size_base * PBS_SIZE_MULTIPLIER;

  }
  else
  {
    *pbs_size = (2 * (pbs_size_base_lsb - 8) * PBS_SIZE_MULTIPLIER * 8);
  }

  return err_flag;
}

/** 
 * @name pm_pbs_ram_image_verify 
 *  
 * @brief Please refer to pm_pbs_driver.h file for info 
 *        regarding this function.
 */
pm_err_flag_type
pm_pbs_ram_image_verify(uint32 slave_id, pm_pbs_ram_data_type *data, unsigned size, uint8 periph_id)
{
  int i;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint64 read_val = 0, data_val = 0;
  pm_pbs_info_data_type **pm_pbs_temp_data = NULL;
  pm_pbs_info_data_type *pm_pbs_data = NULL;
  uint16 pbs_core_base_addr = periph_id * PERIPH_OFFSET;
  uint8 pmic_index; 
  uint32 support_version = 0;
  uint8 step_size = 0; 
  uint8 read_byte_size = 0; 
  uint16 pbs_ram_read_addr = 0;

  /* Retrieve PBS info config data */
  pm_pbs_temp_data = (pm_pbs_info_data_type**)pm_target_information_get_specific_info(PM_PROP_PBS_INFO);
  
  if(NULL == pm_pbs_temp_data)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if (TRUE == pm_is_pmiclib_arch_pre7())
  {
    pm_get_pmic_index_from_slave (slave_id, &pmic_index);
  }
  else
  {
    pmic_index = (uint8)slave_id;
  }
  
  pm_pbs_data = pm_pbs_temp_data[pmic_index];
  
  if(NULL == pm_pbs_data)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_pbs_get_mem_info(slave_id, &pm_pbs_data->pbs_ram_start_addr,
                &pm_pbs_data->pbs_otp_mem_size, &pm_pbs_data->pbs_ram_mem_size);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    pm_log_message("pm_pbs_ram_image_verify: err_flag = %d, ram size failed", err_flag);
    return err_flag;
  }

  /* Configuring read access in burst mode to PBS RAM */
  err_flag = pm_pbs_config_access(slave_id, pm_pbs_data->pbs_ram_start_addr, PM_PBS_ACCESS_READ_BURST, PM_PBS_TYPE_RAM, periph_id);
  if (err_flag != PM_ERR_FLAG_SUCCESS) return err_flag; //Stop on first error

  err_flag = pm_pbs_get_pbs_core_ver (slave_id, pbs_core_base_addr, &support_version);
  if (err_flag != PM_ERR_FLAG_SUCCESS) return err_flag; 
  
  if (support_version >= PM_PBS_CORE_VER_SUPPORT_8BYTE)
  {
    step_size = 2;
    pbs_ram_read_addr = pbs_core_base_addr + MEM_INTF_RD_DATA0_8BYTE_ADDR;
    read_byte_size = 8;
  }
  else
  {
    step_size = 1;
    pbs_ram_read_addr = pbs_core_base_addr + MEM_INTF_RD_DATA0_ADDR;
    read_byte_size = 4;
    
  }

  for (i = 0; i < size; i = i+ step_size)
  {
    err_flag |= pm_comm_read_byte_array(slave_id, pbs_ram_read_addr, read_byte_size, (uint8*)&read_val);
    
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      pm_log_message("*** pm_pbs_ram read fail: word number = %d, read_val = %d, slave_id = %d", i, read_val, slave_id);
      return err_flag; //Stop on first error
    }

      data_val = *((uint64 *)&data[i]);
    // For 4 byte comparison, 0 out 4 byte MSB values
    if (support_version < PM_PBS_CORE_VER_SUPPORT_8BYTE)
    {
      data_val = data_val & FOUR_BYTES_MASK;
    }
    if (data_val != read_val)
    {
      if( pm_pbs_data->skip_verify_supported &&
         (i >= pm_pbs_data->skip_verify_start && i <= pm_pbs_data->skip_verify_end) )
      {
        continue;
      }
      else
      {
        if (support_version >= PM_PBS_CORE_VER_SUPPORT_8BYTE)
        {
          pm_log_message("***pbs ram verify fail word number = 0x%x, slave_id = 0x%x, periph_id = 0x%x, read_val = 0x%lx, dataval = 0x%lx", i, slave_id, periph_id, read_val, data_val);
        }
        else
        {
          pm_log_message("***pbs ram verify fail word number = 0x%x, slave_id = 0x%x, periph_id = 0x%x, read_val = 0x%x, dataval = 0x%x", i, slave_id, periph_id, read_val, data_val);
        }
        return PM_ERR_FLAG_DATA_VERIFY_ERR;
      }
    }
  }

  return err_flag;
}

/** 
 * @name pm_pbs_ram_image_load 
 *  
 * @brief Please refer to pm_pbs_driver.h file for info 
 *        regarding this function.
 */
pm_err_flag_type
pm_pbs_ram_image_load(uint32 slave_id, pm_pbs_ram_data_type *data, unsigned size, uint8 periph_id)
{
  int i;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 pmic_index, read_perphtype = 0, read_perphsubtype = 0;
  pm_pbs_info_data_type **pm_pbs_temp_data = NULL;
  pm_pbs_info_data_type *pm_pbs_data = NULL;
  uint16 pbs_core_base_addr = periph_id * PERIPH_OFFSET;
  uint32 support_version = 0;
  uint16 pbs_ram_wr_addr = 0;

  //Verify given peripheral ID is PBS_CORE
  err_flag = pm_comm_read_byte(slave_id, pbs_core_base_addr + PERIPH_TYPE_OFFSET_ADDR, &read_perphtype);
  err_flag = pm_comm_read_byte(slave_id, pbs_core_base_addr + PERIPH_SUBTYPE_OFFSET_ADDR, &read_perphsubtype);
  
  if ((read_perphtype != PM_HW_MODULE_PBS ) || (read_perphsubtype != PM_HW_MODULE_PBS_CORE))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }  

  /* Retrieve PBS info config data */
  pm_pbs_temp_data = (pm_pbs_info_data_type**)pm_target_information_get_specific_info(PM_PROP_PBS_INFO);
  if(NULL == pm_pbs_temp_data)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if (TRUE == pm_is_pmiclib_arch_pre7())
  {
    pmic_index = (uint8)(slave_id / 2);
  }
  else
  {
    pmic_index = (uint8)slave_id;
  }
  
  pm_pbs_data = pm_pbs_temp_data[pmic_index];
  if(NULL == pm_pbs_data)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_pbs_get_mem_info(slave_id, &pm_pbs_data->pbs_ram_start_addr,
                &pm_pbs_data->pbs_otp_mem_size, &pm_pbs_data->pbs_ram_mem_size);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    pm_log_message("pm_pbs_ram_image_verify: err_flag = %d, ram size failed", err_flag);
    return err_flag;
  }

  /* Configuring read access in burst mode to PBS RAM */
  err_flag = pm_pbs_config_access(slave_id, pm_pbs_data->pbs_ram_start_addr, PM_PBS_ACCESS_WRITE_BURST, PM_PBS_TYPE_RAM, periph_id);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  err_flag = pm_pbs_get_pbs_core_ver (slave_id, pbs_core_base_addr, &support_version);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  if (support_version >= PM_PBS_CORE_VER_SUPPORT_8BYTE)
  {
    pbs_ram_wr_addr = pbs_core_base_addr + MEM_INTF_WR_DATA0_8BYTE_ADDR;
    err_flag = pm_comm_pbs_write_byte_array(slave_id, pbs_ram_wr_addr, size*4, (uint8 *)&data[0]);
  }
  else
  {
    pbs_ram_wr_addr = pbs_core_base_addr + MEM_INTF_WR_DATA0_ADDR;

    for (i = 0; i < size; i = i + 1)
    {
    err_flag = pm_comm_write_byte_array(slave_id, pbs_ram_wr_addr, 4, (uint8 *)&data[i]);
      if (err_flag != PM_ERR_FLAG_SUCCESS)
      {
        return err_flag;
      }
    }
  }

  
  err_flag = pm_pbs_disable_access(slave_id, PM_PBS_TYPE_RAM, periph_id);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  
  err_flag = pm_pbs_ram_image_verify(slave_id, data, size, periph_id);

  return err_flag;
}

/** 
 * @name pm_pbs_disable_access 
 *  
 * @brief Please refer to pm_pbs_driver.h file for info 
 *        regarding this function.
 */
pm_err_flag_type 
pm_pbs_disable_access(uint32 slave_id, pm_pbs_type pbs_type,uint8 periph_id) 
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 support_version = 0;
  uint16 mem_intf_cfg_addr =  0;
  uint16 mem_intf_ctl_addr = 0;
  uint16 otp_cfg1_addr = 0;
  uint16 otp_force_on_addr = 0;
  uint16 pbs_core_base_addr = periph_id * PERIPH_OFFSET;
  
  mem_intf_cfg_addr =  pbs_core_base_addr + MEM_INTF_CFG_ADDR;          //PMIO_PBS_CORE_MEM_INTF_CFG_ADDR
  mem_intf_ctl_addr = pbs_core_base_addr + MEM_INTF_CTL_ADDR;           //PMIO_PBS_CORE_MEM_INTF_CTL_ADDR
  otp_cfg1_addr = pbs_core_base_addr + PMIC5_OTP_CFG1_ADDR;             //PMIO_PBS_CORE_PMIC5_OTP_CFG1_ADDR
  otp_force_on_addr = pbs_core_base_addr + PMIC5_OTP_PCE_FORCE_ON_ADDR; //PMIO_PBS_CORE_PMIC5_OTP_PCE_FORCE_ON_ADDR


  if(pbs_type >= PM_PBS_TYPE_INVALID)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(PM_PBS_TYPE_ROM == pbs_type)
  {
    //check if DIG MAJ is greater than 3 and DIG MIN is greater 3 pbs_core >= 3.3
    err_flag = pm_pbs_get_pbs_core_ver (slave_id, pbs_core_base_addr, &support_version);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }

    if(support_version >= PM_PBS_CORE_VER_SUPPORT_NEW_SEQ)
    {
      err_flag = pm_comm_write_byte(slave_id, otp_cfg1_addr, 0x00);
      err_flag |= pm_comm_write_byte(slave_id, otp_force_on_addr, 0x00);
    }
  }

  /* Configuring to disable PBS ROM/RAM access */
  err_flag |= pm_comm_write_byte(slave_id, mem_intf_cfg_addr, 0x00);
  err_flag |= pm_comm_write_byte(slave_id, mem_intf_ctl_addr, 0x00);

  return err_flag;
}

/** 
 * @name pm_pbs_config_access 
 *  
 * @brief Please refer to pm_pbs_driver.h file for info 
 *        regarding this function.
 */
pm_err_flag_type 
pm_pbs_config_access(uint32 slave_id, uint16 addr, pm_pbs_access_type access_type, pm_pbs_type pbs_type, uint8 periph_id) 
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 access_val = 0;
  uint8 otp_cfg_value = 0x00;
  uint8 otp_force_en_value = 0x01;
  uint8 pce_en_value = 0;
  uint32 support_version = 0;
  uint8 pce_en_read_count = 0;
  uint16 mem_intf_cfg_addr =  0;
  uint16 mem_intf_ctl_addr = 0;
  uint16 otp_cfg1_addr = 0;
  uint16 otp_force_on_addr = 0;
  uint16 pce_en_done_status = 0;
  uint16 mem_intf_addr_lsb =0;
  uint16 pbs_core_base_addr = periph_id * PERIPH_OFFSET;  

  mem_intf_cfg_addr = pbs_core_base_addr + MEM_INTF_CFG_ADDR;            //PMIO_PBS_CORE_MEM_INTF_CFG_ADDR
  mem_intf_ctl_addr = pbs_core_base_addr + MEM_INTF_CTL_ADDR;            //PMIO_PBS_CORE_MEM_INTF_CTL_ADDR
  otp_cfg1_addr = pbs_core_base_addr + PMIC5_OTP_CFG1_ADDR;              //PMIO_PBS_CORE_PMIC5_OTP_CFG1_ADDR
  otp_force_on_addr = pbs_core_base_addr + PMIC5_OTP_PCE_FORCE_ON_ADDR;  //PMIO_PBS_CORE_PMIC5_OTP_PCE_FORCE_ON_ADDR
  pce_en_done_status = pbs_core_base_addr + PCE_ENABLE_DONE_STATUS_ADDR; //PMIO_PBS_CORE_PCE_ENABLE_DONE_STATUS_ADDR
  mem_intf_addr_lsb = pbs_core_base_addr + MEM_INTF_ADDR_LSB_ADDR;       //PMIO_PBS_CORE_MEM_INTF_ADDR_LSB_ADDR
  
  if(pbs_type >= PM_PBS_TYPE_INVALID)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  err_flag = pm_pbs_get_pbs_core_ver (slave_id, pbs_core_base_addr, &support_version);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  switch (access_type)
  {
    case PM_PBS_ACCESS_READ_SINGLE:
      access_val = 0x00;
      break;

    case PM_PBS_ACCESS_WRITE_SINGLE:
      access_val = 0x40;
      break;

    case PM_PBS_ACCESS_READ_BURST:
      if (support_version >= PM_PBS_CORE_VER_SUPPORT_8BYTE)
      {
        access_val = 0xA0;
	    }
	    else
      {
        access_val = 0x80;
      }
      break;
      
    case PM_PBS_ACCESS_WRITE_BURST:
      if (support_version >= PM_PBS_CORE_VER_SUPPORT_8BYTE)
      {
        access_val = 0xE0;
	    }
	    else
      {
        access_val = 0xC0;
      }
      break;

    default:
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  /* Configuring to enable PBS ROM/RAM access */
  err_flag = pm_comm_write_byte(slave_id, mem_intf_cfg_addr, 0x80);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /* Configuring type of access to PBS ROM/RAM */
  err_flag |= pm_comm_write_byte(slave_id, mem_intf_ctl_addr, access_val);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(PM_PBS_TYPE_ROM == pbs_type)
  {
    //check if DIG MAJ is greater than 3 and DIG MIN is greater 3 pbs_core >= 3.3
     err_flag = pm_pbs_get_pbs_core_ver (slave_id, pbs_core_base_addr, &support_version);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
    if(support_version >= PM_PBS_CORE_VER_SUPPORT_NEW_SEQ)
    {
      err_flag = pm_comm_write_byte(slave_id, otp_cfg1_addr, otp_cfg_value);
      if (err_flag != PM_ERR_FLAG_SUCCESS)
      {
        return err_flag;
      }

      err_flag = pm_comm_write_byte(slave_id, otp_force_on_addr, otp_force_en_value);
      if (err_flag != PM_ERR_FLAG_SUCCESS)
      {
        return err_flag;
      }

      // keep reading PCE_ENABLE_DONE to check whether it already been set.
      while(pce_en_read_count++ < PM_PCE_ENABLE_DONE_STATUS_POLLING_MAX)
      {
        err_flag = pm_comm_read_byte_mask(slave_id, pce_en_done_status, 0x01, &pce_en_value);
        if (err_flag != PM_ERR_FLAG_SUCCESS)
        {
          return err_flag;
        }

        if(0x01 == pce_en_value)
        {
          break;
        }

        err_flag = pm_busy_wait(1);
        if (err_flag != PM_ERR_FLAG_SUCCESS)
        {
          return err_flag;
        }
      }
      
      if(pce_en_value != 0x01)
      {
        return PM_ERR_FLAG_PERIPHERAL_ERR;
      }
    }
  }

  /* Configuring the base address */
  err_flag |= pm_comm_write_byte_array(slave_id, mem_intf_addr_lsb, 2, (uint8*)&addr);

  return err_flag;
}


pm_pbs_data_type* pm_pbs_get_data(uint8 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS) 
  {
    return pm_pbs_data_arr[pmic_index];
  }

  return NULL;
}


uint8 pm_pbs_client_get_num_peripherals(uint8 pmic_index, pm_pbs_core_type pbs_core_index)
{
  if( (pmic_index < PM_MAX_NUM_PMICS) && (pm_pbs_data_arr[pmic_index] != NULL))
  {
    return pm_pbs_data_arr[pmic_index]->pbs_client_count[pbs_core_index];
  }

  return 0;
}
