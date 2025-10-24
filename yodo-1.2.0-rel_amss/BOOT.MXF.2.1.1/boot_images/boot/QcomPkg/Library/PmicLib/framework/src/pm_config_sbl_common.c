/*! \file  pm_config_sbl_common.c
 *
 *  \brief  File Contains the PMIC Set Mode Implementation
 *  \details This file extract the common elements from pm_config_sbl.c and 
 *  pm_config_sbl_coderam.c file
 *
 *  &copy; Copyright 2013-2022 QUALCOMM Technologies Inc, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/framework/src/pm_config_sbl_common.c#2 $
$DateTime: 2022/09/01 19:06:39 $  $Author: pwbldsvc $


when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/16/21   rh      Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_sbl_boot.h"
#include "pm_config_sbl.h"
#include "pm_target_information.h"
#include "CoreVerify.h"
#include "pm_version.h"
#include "XBLConfig.h"
#include "pm_sdam.h"
#include "pm_log_utils.h"
#include "pm_sbl_boot_target.h"
#include "pm_sdam_driver.h"
#include "pm_config_target_size.h"
#include "pm_config_sbl_common.h"
#include "pm_dt_parser.h"
#include "pm_resource_manager.h"

static uintnt pm_bl_psi_addr = 0;
#define PM_SBL_COND_REV_ID_REG 0x52
#define PM_PSI_FRAGMENT_PAD_SIZE 0x100

#define PBS_CRC_CHECK_RETRIES_US       500000
#define PBS_CRC_CHECK_DELAY_US         2000
#define PBS_CRC_CHECK_STATE1_INIT      1
#define PBS_CRC_CHECK_STATE4_RESTORE   4
#define PBS_CRC_CHECK_STATE5_START     5
#define PBS_CRC_CHECK_STATE6_COMPLETE  6
#define CRC_SDAM_INDEX 0

#define GET_PID_FROM_ADDR(x) (x / 0x100)

pm_err_flag_type
pm_sbl_validate_cond_config( pm_sbl_config_info_type *sbl_config_info_ds,
                            pm_sbl_cond_seq_type   *cond_ds_ptr,
                            uint8    cond_start_index,
                            uint8    cond_end_index,
                            boolean  *valid_cfg )
{
  pm_err_flag_type err_flag =  PM_ERR_FLAG_SUCCESS;
  uint8 reg_read_data;
  uint8 index = cond_start_index;
  uint8 pmic_index;
  pm_device_info_type pmic_info;
  //conditional reg config table ptr. Index 0 is used in cond table
  pm_sbl_cond_seq_type *cond_cfg_tbl = &cond_ds_ptr[cond_start_index - 1];

  //Max number of entries in conditiaonl table
  uint8 max_num_cond_config = sbl_config_info_ds->cond_num_entries;

  //pm_err_flag_type err_flag_chip_rev = PM_ERR_FLAG_SUCCESS;
  boolean valid_sid = FALSE;
  uint32 rev_id_read;


  if ( ((cond_start_index == 0)  && (cond_end_index  > 0 )) ||
       ((cond_start_index  > 0)  && (cond_end_index == 0 )) ||
       ( cond_start_index   > max_num_cond_config)       ||
       ( cond_end_index     > max_num_cond_config)     )
  {
    err_flag |= PM_ERR_FLAG_INVALID_PARAMETER;
    *valid_cfg = FALSE;
    return err_flag;
  }

  //Execute conditional check
  for(; index <= cond_end_index; index++, cond_cfg_tbl++)
  {
    //Check for valid SID
    /*err_flag_chip_rev |= */pm_resolve_chip_revision_ex(cond_cfg_tbl->cond_busid, cond_cfg_tbl->cond_sid, 
                                                  &valid_sid, &rev_id_read);
    if (valid_sid == FALSE)
    {
      //This configuation does NOT apply to this SID (PMIC does not exist)
      *valid_cfg = FALSE;
      continue;
    }
    if(cond_cfg_tbl->cond_address == PM_SBL_COND_REV_ID_REG) // new clogic for Rev ID check 
    {
      err_flag |= pm_get_pmic_index_from_slave_ex(cond_cfg_tbl->cond_busid, cond_cfg_tbl->cond_sid, &pmic_index);
      err_flag |= pm_get_pmic_info_ex(cond_cfg_tbl->cond_busid,  pmic_index, &pmic_info); 
      reg_read_data = ((pmic_info.nPmicAllLayerRevision << 4) |(pmic_info.nPmicMetalRevision));
    }
    else
    {
      err_flag |= pm_comm_read_byte_mask_ex(cond_cfg_tbl->cond_busid, cond_cfg_tbl->cond_sid,
                                        cond_cfg_tbl->cond_address,
                                        cond_cfg_tbl->cond_mask,
                                        &reg_read_data);
    }
    switch(cond_cfg_tbl->cond_operation)
    {
      case EQUAL:
        *valid_cfg &= (reg_read_data == cond_cfg_tbl->cond_data)?TRUE:FALSE;
        break;

      case GREATER:
        *valid_cfg &= (reg_read_data > cond_cfg_tbl->cond_data)?TRUE:FALSE;
        break;

      case GREATER_OR_EQUAL:
        *valid_cfg &= (reg_read_data >= cond_cfg_tbl->cond_data)?TRUE:FALSE;
        break;

      case LESS:
        *valid_cfg &= (reg_read_data < cond_cfg_tbl->cond_data)?TRUE:FALSE;
        break;

      case LESS_OR_EQUAL:
        *valid_cfg &= (reg_read_data <= cond_cfg_tbl->cond_data)?TRUE:FALSE;
        break;

      default:
        *valid_cfg = FALSE;
        break;
    }

    if (*valid_cfg == FALSE)
    {
       return err_flag;
    }
  }

  return err_flag;
}

// Allocate the full buffer as required.  If allocation failed, fall back to allocate only a small piece
pm_err_flag_type 
pm_config_read_init(sbl_config_info_t *info, uint32 buf_size, uint32 cfg_size)
{
  xblconfig_status_type xblcfg_err_flag = XBLCONFIG_SUCCESS;
  DALResult status;

  info->config_buff_size = 0;
  info->pdm_config_ds_buff = NULL;

  if (buf_size >= cfg_size)
  {
    status = DALSYS_Malloc(buf_size, (VOID**)&info->pdm_config_ds_buff);

    if (status != DAL_SUCCESS) 
    {
      // No memory fragment that fits, moves on to loading in pieces
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
  }
  else 
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  // Read the complete XBL config if buffer is good
  xblcfg_err_flag |= xblconfig_read(info->xbl_cfg_h, 0, cfg_size, info->pdm_config_ds_buff);

  if((xblcfg_err_flag != XBLCONFIG_SUCCESS) || (cfg_size == 0) )
  {
    // xblconfig_read can not fail here, otherwise code will try fragmented load even though
    // large memory buffer has been allocated
    CORE_VERIFY(0);
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  info->config_buff_size = cfg_size;
  return PM_ERR_FLAG_SUCCESS;
}

void 
*pm_config_allocate_and_read(sbl_config_info_t *info, uint32 offset, uint32 size)
{
  void *pt;
  xblconfig_status_type xblcfg_err_flag = XBLCONFIG_SUCCESS;
  DALResult status;

  // If data needed is outside of the preloaded data chunk
  if (info->pdm_config_ds_buff == NULL || info->config_buff_size < (offset + size)) 
  {
     // Load data in fragments
     status = DALSYS_Malloc(size, (VOID**)&pt);
     CORE_VERIFY(status==DAL_SUCCESS);
     xblcfg_err_flag |= xblconfig_read(info->xbl_cfg_h, offset, size, pt);
     CORE_VERIFY(xblcfg_err_flag == XBLCONFIG_SUCCESS);
     return pt;
  }
  else
  {
     // Config is loaded already, just calculate the buffer offset and return the value
     return info->pdm_config_ds_buff + offset;
  }
}

void 
pm_config_read_into_pbs_ram_buf(sbl_config_info_t *info, uint32 offset, uint32 size, void **pbs_ram_buff)
{
  xblconfig_status_type xblcfg_err_flag = XBLCONFIG_SUCCESS;
  DALResult status;

  if (info->pdm_config_ds_buff == NULL || info->config_buff_size < (offset + size)) 
  {
     // Reallocate buffer if requested buffer is larger than existing buffer
     if (size > info->pbs_ram_buff_size && info->pbs_ram_buff != NULL) {
       status = DALSYS_Free(info->pbs_ram_buff);
       CORE_VERIFY(status==DAL_SUCCESS);
       info->pbs_ram_buff = NULL;
     }
     // No preloaded config, load data in fragment
     if (info->pbs_ram_buff == NULL) {
        status = DALSYS_Malloc(size + PM_PSI_FRAGMENT_PAD_SIZE, 
                               (VOID**)&info->pbs_ram_buff);
        info->pbs_ram_buff_size = size + PM_PSI_FRAGMENT_PAD_SIZE;
        CORE_VERIFY(status==DAL_SUCCESS);
     }

     CORE_VERIFY(size <= info->pbs_ram_buff_size);
     xblcfg_err_flag |= xblconfig_read(info->xbl_cfg_h, offset, size, info->pbs_ram_buff);
     CORE_VERIFY(xblcfg_err_flag == XBLCONFIG_SUCCESS);
     *pbs_ram_buff = info->pbs_ram_buff;
  }
  else
  {
     // Config is loaded already, just calculate the buffer offset and return the value
     *pbs_ram_buff = info->pdm_config_ds_buff + offset;
  }
}

void 
config_free_buffer(sbl_config_info_t *info, void *buf)
{
  DALResult status;
  
  if (info->pdm_config_ds_buff != NULL && buf != NULL) 
  { 
    if (buf <= info->pdm_config_ds_buff || (info->pdm_config_ds_buff + info->config_buff_size) < buf)
    {
      status = DALSYS_Free(buf);
      CORE_VERIFY(status==DAL_SUCCESS);
    }
  }
}

pm_err_flag_type 
pm_psi_set_base_address(uintnt address)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if (address != 0x0)
  {
    /*update variable that holds PMIC elf start address*/
    pm_bl_psi_addr = address;
  }
  else
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }

   return err_flag;
}

pm_err_flag_type 
pm_psi_get_base_address(uintnt* address)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  /*update with variable that holds PMIC elf start address*/
  if(NULL != address)
  {
    *address = pm_bl_psi_addr;
  }
  else
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  return err_flag;
}


void pm_sbl_config_check_psi_crc(sbl_config_info_t *info, uint32 sid, uint32 pbs_ram_idx, uint32 ram_config_offset)
{
  int i;
  uint8 reg_crc[3];
  uint8 reg_crc_status = 0;
  uint32 crc_sdam_status_addr[] = PBS_CRC_CHECK_STATUS_ADDR;
  uint32 crc_sdam_value_addr[] = PBS_CRC_CHECK_VALUE_ADDR;
  pm_pbs_ram_data_type    *pbs_ram_compiler_crc       = NULL;
  pm_err_flag_type        err_flag              = PM_ERR_FLAG_SUCCESS;

  /* Default failed state is to reload the PBS */
  info->reload_pbs_state = RELOAD_PBS_STATE_RELOAD;

  /* PBS CRC check only works on Tokei */
  if (sid != 0) {
     info->reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
     return;
  }

  /* If pbs_ram_index is larger than defined, return with reload */
  if (pbs_ram_idx >= (sizeof(crc_sdam_status_addr) / sizeof(uint32))) 
  {
     info->reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
     return;
  }

  pm_config_read_into_pbs_ram_buf(info, ram_config_offset, 4, (void **)&pbs_ram_compiler_crc);

  for(i=0 ;i<PBS_CRC_CHECK_RETRIES_US ;i+=PBS_CRC_CHECK_DELAY_US)
  {
     err_flag = pm_comm_read_byte (sid,
                                   crc_sdam_status_addr[pbs_ram_idx],   
                                   &reg_crc_status);
     if (err_flag != PM_ERR_FLAG_SUCCESS) 
     {
        info->reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
        break;
     }

     if (reg_crc_status == PBS_CRC_CHECK_STATE1_INIT    ||
         reg_crc_status == PBS_CRC_CHECK_STATE4_RESTORE ||
         reg_crc_status == PBS_CRC_CHECK_STATE5_START   )
     {
        /* Still checking for CRC, keep looping */
        pm_busy_wait(PBS_CRC_CHECK_DELAY_US);
        continue;
     }
     else if(reg_crc_status == PBS_CRC_CHECK_STATE6_COMPLETE)
     {
        /* PBS valid */
        info->reload_pbs_state = RELOAD_PBS_STATE_SKIP;
     }
     else 
     {
        /* No valid PBS */
        info->reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
        pm_log_message("PBS_RAM %d reloading", pbs_ram_idx);
        break;
     }

     /* Clear the CRC status to make sure it is computed on next PON */
     reg_crc_status = 0;
     err_flag = pm_comm_write_byte (sid,
                                   crc_sdam_status_addr[pbs_ram_idx],   
                                   reg_crc_status);

     err_flag |= pm_comm_read_byte_array (sid,
                                         crc_sdam_value_addr[pbs_ram_idx],   
                                         2,    
                                         reg_crc);
     if (err_flag != PM_ERR_FLAG_SUCCESS) 
     {
        info->reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
        break;
     }

     if (reg_crc[0] != pbs_ram_compiler_crc[0].word3 || 
         reg_crc[1] != pbs_ram_compiler_crc[0].word4) 
     {
        /* If CRC value mismatches, reload PSI */
        info->reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
        pm_log_message("PBS_RAM %d reloading", pbs_ram_idx);
     }

     break;
  }
}

void 
pm_sbl_config_check_psi_crc_v2(uint8 *reload_pbs_state, uint32 sid, uint32 pbs_ram_idx, void *pbs_ram)
{
  int i;
  uint8 reg_crc[3];
  uint8 reg_crc_status = 0;
  uint32 crc_sdam_status_addr[] = PBS_CRC_CHECK_STATUS_ADDR;
  uint32 crc_sdam_value_addr[] = PBS_CRC_CHECK_VALUE_ADDR;
  pm_pbs_ram_data_type    *pbs_ram_compiler_crc = (pm_pbs_ram_data_type*)pbs_ram;
  pm_err_flag_type        err_flag              = PM_ERR_FLAG_SUCCESS;
  uint8 pmic_index;

  /*Validate arguments*/
  CORE_VERIFY_PTR(reload_pbs_state);
  CORE_VERIFY_PTR(pbs_ram);
  
  /* Default failed state is to reload the PBS */
  *reload_pbs_state = RELOAD_PBS_STATE_RELOAD;

  /* PBS CRC check only works on Tokei */
  /*if (sid != 0) {
     *reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
     pm_log_message("PBS_RAM %d reloading", pbs_ram_idx);
     return;
  }*/

  /* Aurora has a Wailua which doesnt support CRC check */
  err_flag = pm_get_pmic_index_from_slave(sid, &pmic_index);
  if((err_flag != PM_ERR_FLAG_SUCCESS) || (pm_get_pmic_model(pmic_index) == PMIC_IS_PM8250))
  {
     *reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
     return;
  }
  
  /* If pbs_ram_index is larger than defined, return with reload */
  if (pbs_ram_idx >= (sizeof(crc_sdam_status_addr) / sizeof(uint32))) 
  {
     *reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
     return;
  }

  for(i=0 ;i<PBS_CRC_CHECK_RETRIES_US ;i+=PBS_CRC_CHECK_DELAY_US)
  {
     err_flag = pm_comm_read_byte (CRC_SDAM_INDEX,
                                   crc_sdam_status_addr[pbs_ram_idx],   
                                   &reg_crc_status);
     if (err_flag != PM_ERR_FLAG_SUCCESS) 
     {
        *reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
        break;
     }

     // Remove after initial testing - 
     //pm_log_message("PSI CRC checker status %d", reg_crc_status);

     if (reg_crc_status == PBS_CRC_CHECK_STATE1_INIT    ||
         reg_crc_status == PBS_CRC_CHECK_STATE4_RESTORE ||
         reg_crc_status == PBS_CRC_CHECK_STATE5_START   )
     {
        /* Still checking for CRC, keep looping */
        pm_busy_wait(PBS_CRC_CHECK_DELAY_US);
        continue;
     }
     else if(reg_crc_status == PBS_CRC_CHECK_STATE6_COMPLETE)
     {
        /* PBS valid */
        *reload_pbs_state = RELOAD_PBS_STATE_SKIP;
     }
     else 
     {
        /* No valid PBS */
        *reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
        pm_log_message("PBS_RAM %d reloading for sid %d", pbs_ram_idx, sid);
        break;
     }

     /* Clear the CRC status to make sure it is computed on next PON */
     reg_crc_status = 0;
     err_flag = pm_comm_write_byte (CRC_SDAM_INDEX,
                                   crc_sdam_status_addr[pbs_ram_idx],   
                                   reg_crc_status);

     err_flag |= pm_comm_read_byte_array (CRC_SDAM_INDEX,
                                         crc_sdam_value_addr[pbs_ram_idx],   
                                         2,    
                                         reg_crc);
     if (err_flag != PM_ERR_FLAG_SUCCESS) 
     {
        *reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
        break;
     }

     if (reg_crc[0] != pbs_ram_compiler_crc[0].word3 || 
         reg_crc[1] != pbs_ram_compiler_crc[0].word4) 
     {
        /* If CRC value mismatches, reload PSI */
        *reload_pbs_state = RELOAD_PBS_STATE_RELOAD;
        pm_log_message("PBS RAM %d CRC mismatch for sid %d; read_val = 0x%02x%02x, data_val_0 = 0x%02x%02x",
                        pbs_ram_idx, sid, reg_crc[1], reg_crc[0], pbs_ram_compiler_crc[0].word4, pbs_ram_compiler_crc[0].word3);
        pm_log_message("PBS_RAM %d reloading for sid %d", pbs_ram_idx, sid);
     }

     // Removing after initial test - Debug only
     // pm_log_message("PSI CRC checker CRC value = %x %x", reg_crc[0], reg_crc[1]);
     // pm_log_message("PSI CRC known good value = %x %x", pbs_ram_compiler_crc[0].word3, pbs_ram_compiler_crc[0].word4);
     break;
  }
}


static pm_err_flag_type
pm_config_sbl_is_peripheral_whitelisted(uint32 bus_id, uint32 slave_id, uint16 addr, uint8 *bitmap_ptr , boolean *whitelisted)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean is_sid_valid = FALSE;
  uint32 bitmap_index = 0 ;
  uint8 pmic_index = 0;
  uint8 slaves_count = 0;
  uint16 peripheral_index = 0 ;
  uint8 bit_position = 0;
  uint8 bitmap_value = 0;
  uint8 mask = 0;
  uint8 slave_id_index = 0;
  
  //if the slave id is Invalid, continue to next setting      
  is_sid_valid = pm_is_slave_id_supported_ex(bus_id,slave_id);
  
  if(!is_sid_valid)
  {
    pm_log_message ("Invlaid slave_id: 0x%x", slave_id );
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  err_flag = pm_get_pmic_index_from_slave_ex(bus_id, slave_id , &pmic_index);
  
  if (err_flag != PM_ERR_FLAG_SUCCESS) 
  {
    pm_log_message ("OEM_PSI- Error err_flag: 0x%x ; slave_id: 0x%x", err_flag, slave_id );
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  //Calculate Bitmap index and Value
  peripheral_index =  GET_PID_FROM_ADDR(addr); 

  bitmap_index = peripheral_index / 8;   
  
  if(TRUE == pm_is_pmiclib_arch_pre7())
  {
    slaves_count = pm_get_num_of_sid_supported(pmic_index);
    slave_id_index = slave_id % 2 ;
    bitmap_value = bitmap_ptr[(pmic_index * (slaves_count * PM_MAX_BITMAP_ENTRIES)) + (slave_id_index * PM_MAX_BITMAP_ENTRIES) + bitmap_index];
  }
  else
  {
    bitmap_value = (uint8)(*(bitmap_ptr + (slave_id * PM_MAX_BITMAP_ENTRIES) + bitmap_index));
  }
  
  bit_position = GET_PID_FROM_ADDR(addr)  % 0x8;  

  mask = 0x1 << bit_position; 
  
  *whitelisted = (mask & bitmap_value) ? TRUE : FALSE;
  
  if(*whitelisted == FALSE)
  {
    pm_log_message ("OEM_PSI- PID 0x%x on SID 0x%x not whitelisted" , peripheral_index, slave_id );  
  }
  
  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type
pm_config_sbl_oem_psi( void )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 settings_index = 0;
  uint32 clogic_index = 0;
  uint8 settings_operation =0;
  uint32 settings_bus_id = 0;
  uint32 settings_slave_id = 0;
  uint16 settings_register_addr = 0;
  uint8 settings_data = 0;
  uint8 settings_mask = 0;
  uint8 cond_start = 0, cond_end = 0;
  uint32 count = 0;
  boolean valid_config_flag = TRUE;
  pm_dt_psi_config  *psi_dt_config = NULL;
  pm_sbl_cond_seq_type *clogic_conditions = NULL;
  pm_sbl_config_info_type sbl_config_info ;
  uint8 *whitelist_bitmap_ptr = NULL;
  boolean whitelist_status = FALSE;

  pm_log_message ("OEM_PSI Start");
  psi_dt_config = pm_dt_get_node( PMIC_DT_NODE_OPSI_CONFIG );
  whitelist_bitmap_ptr = pm_target_information_get_specific_info(PM_PROP_OEM_PSI_WLIST_PERIPH_BITMAP);
  
  if(whitelist_bitmap_ptr == NULL || psi_dt_config == NULL )
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  //If there are no settings to execute , return success 
  if(psi_dt_config->settings_count == 0)
  {
    return PM_ERR_FLAG_SUCCESS;  
  }
  
  // update sbl_config_info structure
  sbl_config_info.cond_num_entries = psi_dt_config->clogic->clogic_count; 
  //Construct Clogic  
  pm_malloc((psi_dt_config->clogic->clogic_count * sizeof(pm_sbl_cond_seq_type)), (void**)&clogic_conditions); 
  
  if(psi_dt_config->clogic->clogic_count > 0)
  {    
    for(count = 0; count < psi_dt_config->clogic->clogic_count; count++)
    {
      clogic_index = count * PM_OEM_PSI_CLOGIC_STEP_LENGTH;
      clogic_conditions[count].cond_bustype = (uint8) psi_dt_config->clogic->clogic_data[clogic_index +0 ];      
      clogic_conditions[count].cond_busid = (uint8)psi_dt_config->clogic->clogic_data[clogic_index +1 ];     
      clogic_conditions[count].cond_sid = (uint8)psi_dt_config->clogic->clogic_data[clogic_index +2 ];
      clogic_conditions[count].cond_data = (uint8)psi_dt_config->clogic->clogic_data[clogic_index +3 ];
      clogic_conditions[count].cond_mask = (uint8)psi_dt_config->clogic->clogic_data[clogic_index +4 ];
      clogic_conditions[count].cond_address = (uint16)psi_dt_config->clogic->clogic_data[clogic_index +5 ];
      clogic_conditions[count].cond_operation = (uint8)psi_dt_config->clogic->clogic_data[clogic_index +6 ];
    }
  }
  //PSI Settings
  for(count = 0; count < psi_dt_config->settings_count; count++)
  {
    settings_index = count*PM_OEM_PSI_SEQ_STEP_LENGTH;      
    settings_bus_id = psi_dt_config->opsi_seq[settings_index+1];     
    settings_operation = psi_dt_config->opsi_seq[settings_index+2];
    settings_slave_id = psi_dt_config->opsi_seq[settings_index+3];
    settings_register_addr = psi_dt_config->opsi_seq[settings_index+4];
    settings_data = psi_dt_config->opsi_seq[settings_index+5];
    settings_mask = psi_dt_config->opsi_seq[settings_index+6];
    cond_start = psi_dt_config->opsi_seq[settings_index+7];
    cond_end = psi_dt_config->opsi_seq[settings_index+8];
    
    
    if ((cond_start == 0) && (cond_end == 0))
    {
        valid_config_flag = TRUE; //Normal configuration
    }
    else
    {
        if(clogic_conditions == NULL)
        {
          break;
        }
        err_flag |= pm_sbl_validate_cond_config(&sbl_config_info, 
                                                     clogic_conditions, cond_start,cond_end, &valid_config_flag);
    }
        
    if(valid_config_flag)
    {
        switch(settings_operation)
        {
          case PM_SBL_WRITE:
            err_flag = pm_config_sbl_is_peripheral_whitelisted(settings_bus_id, settings_slave_id, 
                                            settings_register_addr, whitelist_bitmap_ptr, &whitelist_status);
            if (err_flag == PM_ERR_FLAG_SUCCESS && whitelist_status == TRUE)
            {
                err_flag |= pm_comm_write_byte_mask_ex(settings_bus_id,settings_slave_id, 
                                                       settings_register_addr, settings_mask, settings_data);
            }
            break;
          case PM_SBL_DELAY:
            pm_busy_wait(settings_register_addr);
            break;
          case PM_SBL_NOP:
            break;
          default:
            err_flag |= PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
        }
    }    
  }
  
  pm_free((void**)&clogic_conditions);  
  
  pm_log_message ("OEM_PSI Done");
  
  return err_flag;
}
