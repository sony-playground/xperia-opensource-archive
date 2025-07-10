/*===========================================================================

                    BOOT WRAPPER FOR SECLIB CALLS

DESCRIPTION
  Contains wrapper definition for external image authentication drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
  Copyright 2020-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/17/21   rama    Removed qsee_is_memory_dump_allowed
05/02/21   ds      debug policy milestone
04/15/21   ds      changes for debuglib addition
03/04/21   rama    Replace seclib.h with seclib_defs.h
01/30/21   yps     Fixed LLVM12 compilation issue
01/19/21   rama    Removed PIMEM_STATUS which is directly obtained from seclib.h
01/14/21   rama    Added get_debug_state
12/02/20   rama    SMC ID and PARAM ID from seclib_syscall.h
07/31/20   ds 		 update signature for auth metadata
07/22/20   rama    Updated SecLib API to remove verified info
06/25/20   rama    Initial Revision
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <seclib_defs.h>
#include <boot_seclib_if.h>
#include <boot_fastcall_tz.h>
#include <boot_logger_if.h>
#include <Library/CacheMaintenanceLib.h>
#include <boot_error_if.h>
#include <boot_sbl_shared.h>
#include <seclib_syscall.h>
/*===========================================================================
                           DEFINITIONS
===========================================================================*/

/*===========================================================================
                      FUNCTION DEFINITIONS
===========================================================================*/ 

/**
 * @brief This function authenticates image Metadata
 *      
 *
 * @param[in,out] sec_img_id           	SW Image ID
 *                sec_img_data          Pointer to ELF header         
 *                                     
 * 				  
 * @return BL_ERR_NONE on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
bl_error_boot_type boot_seclib_img_auth_verify_metadata
( 
  uint32 sec_img_id,
  uint8 *elfHdr ,
  uint32 elfHdrSize,
  uint8 *progHdr,
  uint32 progHdrSize,
  uint8 *hashSeg,
  uint32 hashSegSize,
  uint8 *whitelist,
  uint32 whitelistSize
)
{
  int smc_status;
  bl_error_boot_type status = BL_ERR_IMG_SECURITY_FAIL;
  boot_tz_indirect_arg_list_t indirect_arg_list;
  uint32 start_time = boot_log_get_time(); 

  indirect_arg_list.arg[0] = (uintnt) progHdr;
  indirect_arg_list.arg[1] = (uintnt) progHdrSize;
  indirect_arg_list.arg[2] = (uintnt) hashSeg;
  indirect_arg_list.arg[3] = (uintnt) hashSegSize;
  indirect_arg_list.arg[4] = (uintnt) whitelist;
  indirect_arg_list.arg[5] = (uintnt) whitelistSize;

  
  WriteBackInvalidateDataCacheRange((void *)&sec_img_id, sizeof(sec_img_id)); 
  WriteBackInvalidateDataCacheRange((void *)elfHdr, elfHdrSize);
  WriteBackInvalidateDataCacheRange((void *)progHdr, progHdrSize);
  WriteBackInvalidateDataCacheRange((void *)hashSeg, hashSegSize);
  WriteBackInvalidateDataCacheRange((void *)whitelist, whitelistSize);
  WriteBackInvalidateDataCacheRange((void *)&indirect_arg_list, sizeof(indirect_arg_list));  
  
  smc_status = boot_fastcall_tz_no_rsp (TZ_PIL_SEC_IMG_VERIFY_METADATA_ID,
                                  TZ_PIL_SEC_IMG_VERIFY_METADATA_ID_PARAM_ID,
                                  sec_img_id,
                                  elfHdr,
                                  elfHdrSize,
                                  &indirect_arg_list);

  if(smc_status == SMC_SUCCESS)
  {
    status = BL_ERR_NONE;
  }
  boot_log_delta_time(start_time, "Auth Metadata");
  return status;
}

/**
 * @brief This function authenticates an ELF images hash segments
 *      
 *
 * @param[in,out] sec_img_id              SW Image ID
 *                v_info                  Pointer to location for verifed info
 *                                   
 *
 * @return BL_ERR_NONE on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
bl_error_boot_type boot_seclib_img_auth_hash_elf_segments(uint32 sec_img_id)
{
  int smc_status;
  bl_error_boot_type status = BL_ERR_IMG_SECURITY_FAIL;
  uint32 start_time = boot_log_get_time();
  
  WriteBackInvalidateDataCacheRange((void *)&sec_img_id, sizeof(sec_img_id));
  
  smc_status = boot_fastcall_tz_no_rsp (TZ_PIL_SEC_IMG_HASH_SEGMENTS_ID,
                                  TZ_PIL_SEC_IMG_HASH_SEGMENTS_ID_PARAM_ID,
                                  sec_img_id,
                                  0,
                                  0,
                                  0);
  if(smc_status == SMC_SUCCESS)
  {
    status = BL_ERR_NONE;
  }
  boot_log_delta_time(start_time, "Segments hash check");
  return status;
}


/**
 * @brief This function validates the ELF image
 *      
 *
 * @param[in,out] elf_hdr               Pointer to ELF header
 *                                    
 *                        
 *
 * @return BL_ERR_NONE on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
bl_error_boot_type boot_seclib_img_auth_validate_elf(uint32 format, const void *elf_hdr)
{
  int smc_status;
  bl_error_boot_type status = BL_ERR_IMG_SECURITY_FAIL;
  uint64 elf_hdr_size = (format == ELF_CLASS_64) ? sizeof(Elf64_Ehdr) : sizeof(Elf32_Ehdr);
    
  WriteBackInvalidateDataCacheRange((void *)elf_hdr, elf_hdr_size); 
  smc_status = boot_fastcall_tz_no_rsp (TZ_PIL_SEC_IMG_VALIDATE_ELF_ID,
                                  TZ_PIL_SEC_IMG_VALIDATE_ELF_ID_PARAM_ID,
                                  format,
                                  (uint32)(uintptr_t) elf_hdr,
                                  elf_hdr_size,
                                  0);
  if(smc_status == SMC_SUCCESS)                                  
  {
    status = BL_ERR_NONE;
  }
  return status;
}


/**
 * @brief This function checks if the image segment is valid
 *
 *
 * @param[in,out] format              File format
 *                entry               Pointer to hash segment to be checked
 *                valid_segment       Pointer to stored result
 *
 * @return BL_ERR_NONE on success.
 *
 * @sideeffects  None
 *
 *
 */
bl_error_boot_type boot_seclib_is_valid_segment(uint32 format, const void *entry, boot_boolean *valid_segment)
{
  boot_tzt_result_regs_t result;
  uint64 prog_hdr_size = (format == ELF_CLASS_64) ? sizeof(Elf64_Phdr) : sizeof(Elf32_Phdr);

  WriteBackInvalidateDataCacheRange((void *)entry, prog_hdr_size);
  WriteBackInvalidateDataCacheRange((void *)&format, sizeof(format));
  
  boot_fastcall_tz (TZ_PIL_SEC_IMG_VALID_SEG_ID,
                    TZ_PIL_SEC_IMG_VALID_SEG_ID_PARAM_ID,
                    format,
                    entry,
                    prog_hdr_size,
                    0,
                    &result);

  *valid_segment = result.reg[0];
  return BL_ERR_NONE;
}


/**
 * @brief This function checks whether authentication is enabled
 *      
 *
 * @param[in,out] code_seg            Type of code segment descriptor
 *                *is_auth_enabled    Pointer to store auth_en flag. 
 *                                                           
 *
 * @return BL_ERR_NONE on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
bl_error_boot_type boot_seclib_is_auth_enabled(uint32 *is_auth_enabled)
{
  /* will be something like 
  return boot_fastcall_tz_2arg(TZ_SEC_IMG_AUTH_IS_AUTH_ENABLED_CMD, 
                               TZ_SEC_IMG_AUTH_IS_AUTH_ENABLED_CMD_PARAM_ID,
                               0,
                               is_auth_enabled);*/
  return BL_ERR_NONE;
}

/**
 * @brief This function initializes module to compute partial hash
 *
 *
 * @param[in] 
 *                hash_buffer         Hash segment of data to be hashed
 *                hash_buff_size      Hash segment size
 *                partial_buff        Pointer to data to be hashed
 *                partial_buff_size   Size of data buffer
 *                segment_num         Index of segment containing data
 *
 * @return BL_ERR_NONE on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
bl_error_boot_type boot_seclib_img_auth_partial_hash_init
( 
  void   *hash_buffer, 
  uintnt hash_buff_size,
  void   *partial_buff, 
  uintnt partial_buff_size,
  uintnt segment_num
)
{
  int smc_status;
  bl_error_boot_type status = BL_ERR_IMG_SECURITY_FAIL;  
  boot_tz_indirect_arg_list_t indirect_arg_list;
  boot_tzt_result_regs_t result;
  
  indirect_arg_list.arg[0] = (uintnt) hash_buffer;
  indirect_arg_list.arg[1] = (uintnt) hash_buff_size;
  indirect_arg_list.arg[2] = (uintnt) segment_num;

  WriteBackInvalidateDataCacheRange((void *)hash_buffer, hash_buff_size);
  WriteBackInvalidateDataCacheRange((void *)&indirect_arg_list, sizeof(indirect_arg_list));
  
  smc_status = boot_fastcall_tz (TZ_PIL_SEC_IMG_PARTIAL_HASH_ID,
                                 TZ_PIL_SEC_IMG_PARTIAL_HASH_ID_PARAM_ID,
                                 SEC_IMG_AUTH_HASH_INIT,
                                 partial_buff,
                                 partial_buff_size,
                                 &indirect_arg_list,
                                 &result);
  if(smc_status == SMC_SUCCESS)
  {
    status = BL_ERR_NONE;
  }
  return status;
}

/**
 * @brief This function updates running hash for new data buffer
 *      
 *
 * @param[in] 
 *                hash_buffer         Hash segment of data to be hashed
 *                hash_buff_size      Hash segment size
 *                partial_buff        Pointer to data to be hashed
 *                partial_buff_size   Size of data buffer
 *                segment_num         Index of segment containing data
 *
 * @return BL_ERR_NONE on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
bl_error_boot_type boot_seclib_img_auth_partial_hash_update
( 
  void   *hash_buffer, 
  uintnt hash_buff_size,
  void   *partial_buff, 
  uintnt partial_buff_size,
  uintnt segment_num
)
{
  int smc_status;
  bl_error_boot_type status = BL_ERR_IMG_SECURITY_FAIL;   
  boot_tz_indirect_arg_list_t indirect_arg_list;
  boot_tzt_result_regs_t result;

  indirect_arg_list.arg[0] = (uintnt) hash_buffer;
  indirect_arg_list.arg[1] = (uintnt) hash_buff_size;
  indirect_arg_list.arg[2] = (uintnt) segment_num;

  WriteBackInvalidateDataCacheRange((void *)partial_buff , partial_buff_size);
  WriteBackInvalidateDataCacheRange((void *)hash_buffer, hash_buff_size);  
  WriteBackInvalidateDataCacheRange((void *)&indirect_arg_list, sizeof(indirect_arg_list));  
  
  smc_status = boot_fastcall_tz (TZ_PIL_SEC_IMG_PARTIAL_HASH_ID,
                                 TZ_PIL_SEC_IMG_PARTIAL_HASH_ID_PARAM_ID,
                                 SEC_IMG_AUTH_HASH_UPDATE,
                                 partial_buff,
                                 partial_buff_size,
                                 &indirect_arg_list,
                                 &result);   
                                 
  if(smc_status == SMC_SUCCESS)
  {
    status = BL_ERR_NONE;
  }                     
  return status;
}
  
/**
 * @brief This function indicates security module that no further hash data
 *        shall be added and it should compute final hash.
 *      
 *
 * @param[in] 
 *                hash_buffer         Hash segment of data to be hashed
 *                hash_buff_size      Hash segment size
 *                partial_buff        Pointer to data to be hashed
 *                partial_buff_size   Size of data buffer
 *                segment_num         Index of segment containing data
 *
 * @return BL_ERR_NONE on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
bl_error_boot_type boot_seclib_img_auth_partial_hash_finalize
( 
  void   *hash_buffer, 
  uintnt hash_buff_size,
  void   *partial_buff, 
  uintnt partial_buff_size,
  uintnt segment_num
)
{
  int smc_status;
  bl_error_boot_type status = BL_ERR_IMG_SECURITY_FAIL;   
  boot_tz_indirect_arg_list_t indirect_arg_list;
  boot_tzt_result_regs_t result;

  indirect_arg_list.arg[0] = (uintnt) hash_buffer;
  indirect_arg_list.arg[1] = (uintnt) hash_buff_size;
  indirect_arg_list.arg[2] = (uintnt) segment_num;

  WriteBackInvalidateDataCacheRange((void *)partial_buff , partial_buff_size);
  WriteBackInvalidateDataCacheRange((void *)&indirect_arg_list, sizeof(indirect_arg_list));  
  
  smc_status = boot_fastcall_tz (TZ_PIL_SEC_IMG_PARTIAL_HASH_ID,
                                 TZ_PIL_SEC_IMG_PARTIAL_HASH_ID_PARAM_ID,
                                 SEC_IMG_AUTH_HASH_FINALIZE,
                                 partial_buff,
                                 partial_buff_size,
                                 &indirect_arg_list,
                                 &result);            
                    
  if(smc_status == SMC_SUCCESS)
  {
    status = BL_ERR_NONE;
  }                     
  return status;
}

/**
 * @brief This function initializes pimem
 *      
 *
 * @param[in] void
 *
 * @return void
 *
 * @sideeffects  
 * None
 *
 *
 */
bl_error_boot_type boot_seclib_pimem_init(void)
{
  uint32 start_time;

  boot_log_message("Pimem init cmd, entry");
  start_time = boot_log_get_time(); 	  
  
  /* Initialize Pimem by calling into XBL SEC */
  boot_fastcall_tz_no_rsp (TZ_PIMEM_INIT_CMD,
                           TZ_PIMEM_INIT_CMD_PARAM_ID,
                           0,0,0,0);
  boot_log_delta_time(start_time, "Pimem init cmd, exit");
  return BL_ERR_NONE;
}  

/**
 * @brief This function returns the size of pimem that is 
 * allowed to be dumped
 *      
 *
 * @param[in] 
 *                size_in_mb  Pointer to variable that holds 
 *                            the pimem size
 *
 * @return PIMEM_SUCCESS on success. Appropriate error code on failure.
 *
 * @sideeffects  None
 *
 *
 */
bl_error_boot_type boot_seclib_pimem_get_status(uint32 * size_in_mb)
{
  PIMEM_STATUS pimem_enable_status = -1;
  boot_tzt_result_regs_t result_regs;

  boot_fastcall_tz(SECLIB_PIMEM_GET_STATUS_ID,
                   SECLIB_PIMEM_GET_STATUS_PARAM_ID,
                      0,0,0,0,
                      &result_regs);

  pimem_enable_status = (PIMEM_STATUS)result_regs.reg[0];
  *size_in_mb = (uint32)result_regs.reg[1];
  
  if(pimem_enable_status == PIMEM_OK)
	  return BL_ERR_NONE;
  else
	  return BL_ERR_IMG_SECURITY_FAIL;
}


/**
 * @brief This function will determine if ram dumps are allowed or not
 *
 * @param[in]
 *   secboot_info  Pointer to shared data
 *
 * @return
 *   bl_error_boot_type indicating if ram dumps are allowed or not
 *
 * @sideeffects
 *   None
 *
 *
 */
bl_error_boot_type
boot_seclib_qsee_is_memory_dump_allowed(boot_boolean *memdump_allowed)
{
	//TODO: FIXME smc call not required for is_mem_dump_allowed.
    *memdump_allowed = 1;
	return BL_ERR_NONE;
}

/**
 * @brief This function initializes seclib
 *
 * @param[in] void
 *
 *
 * @return
 *   bl_error_boot_type indicating if seclib initialization was successful
 *   BL_ERR_NONE = initialization successful
 *   other       = initialization failed
 *
 * @sideeffects
 *   None
 *
 *
 */
bl_error_boot_type
boot_seclib_init(void)
{
  return TRUE;
}

/**
 * @brief This function unlocks xpu protected DDR region
 *
 * @param[in] void
 *
 *
 * @return
 *   void
 *
 * @sideeffects
 *   None
 *
 *
 */
void boot_seclib_unlock_xpu_protected_ddr_region()
{
  boot_fastcall_tz_no_rsp (TZ_UNLOCK_CMD,
                           TZ_UNLOCK_CMD_PARAM_ID,
                           2,0,0,0);
}

/*===========================================================================
**  Function :  boot_seclib_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_seclib_get_interface
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_seclib_get_interface(void *seclib_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(seclib_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SECLIB, BL_ERR_NULL_PTR_PASSED);
      break;
    }


    ((boot_seclib_if_type *)seclib_if)->auth_metadata = boot_seclib_img_auth_verify_metadata;
    ((boot_seclib_if_type *)seclib_if)->auth_data = boot_seclib_img_auth_hash_elf_segments;
    ((boot_seclib_if_type *)seclib_if)->validate_ehdr = boot_seclib_img_auth_validate_elf;
    ((boot_seclib_if_type *)seclib_if)->is_valid_segment = boot_seclib_is_valid_segment;
    ((boot_seclib_if_type *)seclib_if)->auth_partial_hash_init = boot_seclib_img_auth_partial_hash_init;
    ((boot_seclib_if_type *)seclib_if)->auth_partial_hash_update = boot_seclib_img_auth_partial_hash_update;
    ((boot_seclib_if_type *)seclib_if)->auth_partial_hash_finalize = boot_seclib_img_auth_partial_hash_finalize;
    ((boot_seclib_if_type *)seclib_if)->pimem_init = boot_seclib_pimem_init;
    ((boot_seclib_if_type *)seclib_if)->pimem_get_status = boot_seclib_pimem_get_status;
    ((boot_seclib_if_type *)seclib_if)->init = boot_seclib_init;
    ((boot_seclib_if_type *)seclib_if)->unlock_xpu_prot_ddr_region = boot_seclib_unlock_xpu_protected_ddr_region;
    ((boot_seclib_if_type *)seclib_if)->milestone_set = NULL;
    ((boot_seclib_if_type *)seclib_if)->image_load_complete = NULL;
    ((boot_seclib_if_type *)seclib_if)->dbg_policy_load_milestone = NULL;
  }while(FALSE);

  return return_status;
}