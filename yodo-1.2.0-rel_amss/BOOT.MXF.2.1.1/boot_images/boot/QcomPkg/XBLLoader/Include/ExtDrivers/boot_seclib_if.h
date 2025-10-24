#ifndef BOOT_SECLIB_IF_H
#define BOOT_SECLIB_IF_H
/*===========================================================================

                    BOOT EXTERN SECURE IMAGE AUTH DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external image authentication drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020-2022 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/24/22   ck      Updated auth_data
03/10/22   rama    Add wrap_blob_with_oem_pub_key to seclib interface
06/17/21   rama    Removed qsee_is_memory_dump_allowed
05/02/21   ds      debug policy milestone
04/15/21   ds      changes for debuglib addition
02/05/21   ds      Milestone call updated
01/14/21   rama    Added get_debug_state to boot_seclib_if_type
11/19/20   ds      Added image_load_complete function
09/03/20   ck      Added milestone_segment_load functions
08/06/20   ck      Added parallel hash functions
07/31/20   ds      update signature for auth metadata
07/22/20   rama    Updated SecLib API to remove verified info
06/25/20   rama    Removed boot_query_xpu_violation
06/01/20   rama    Initial Creation.

===========================================================================*/

/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include <boot_comdef.h>
#include <sec_img_auth.h>
#include <boot_error_if.h>
#include <boot_modes.h>
#include <boot_elf_header.h>
#include <boot_whitelist_if.h>


typedef struct boot_seclib_if_type
{
  bl_error_boot_type (*auth_metadata)(uint32 sec_img_id,
                                      uint8 * elfHdr,
                                      uint32 elfHdrSize,
                                      uint8 * progHdr,
                                      uint32 progHdrSize,
                                      uint8 * hashSeg,
                                      uint32 hashSegSize,
                                      uint8 * whitelist,
                                      uint32 whitelistSize);

  bl_error_boot_type (*auth_data)(uint32 sec_img_id,
                                  Elf32_Ehdr * elf_header,
                                  void * program_headers,
                                  uintnt program_headers_count,
                                  whitelst_tbl_entry_type * whitelist_table,
                                  uintnt whitelist_count);

  bl_error_boot_type (*validate_ehdr)(uint32 format,
                                      const void * elf_hdr);

  bl_error_boot_type (*is_valid_segment)(uint32 format,
                                         const void * entry,
                                         boot_boolean * valid_segment);

  bl_error_boot_type (*auth_partial_hash_init)(void * hash_buffer, 
                                               uintnt hash_buff_size,
                                               void * partial_buff, 
                                               uintnt partial_buff_size,
                                               uintnt segment_num);

  bl_error_boot_type (*auth_partial_hash_update)(void * hash_buffer, 
                                                 uintnt hash_buff_size,
                                                 void * partial_buff, 
                                                 uintnt partial_buff_size,
                                                 uintnt segment_num);

  bl_error_boot_type (*auth_partial_hash_finalize)(void * hash_buffer, 
                                                   uintnt hash_buff_size,
                                                   void * partial_buff, 
                                                   uintnt partial_buff_size,
                                                   uintnt segment_num);

  bl_error_boot_type (*auth_parallel_hash_init)(uint32 sec_image_id,
                                                uint8 segment_index,
                                                uintnt * parallel_buffer_size_max);
  
  bl_error_boot_type (*auth_parallel_hash_update)(uint32 sec_image_id,
                                                  const uint8 * parallel_buffer,
                                                  uintnt parallel_buffer_size,
                                                  uint8 segment_index);
  
  bl_error_boot_type (*auth_parallel_hash_finalize)(uint32 sec_image_id,
                                                    uint8 segment_index);

  bl_error_boot_type (*milestone_segment_load_begin)(uint32 sec_image_id,
                                                     uint8 segment_index,
                                                     uintnt segment_base_address,
                                                     uintnt segment_file_size,
                                                     uintnt segment_mem_size,
                                                     sec_img_auth_whitelist_area_t * white_list_area,
                                                     uintnt whitelist_entries);

  bl_error_boot_type (*milestone_segment_load_complete)(void);

  bl_error_boot_type (*pimem_init)(void);
  
  bl_error_boot_type (*pimem_get_status)(uint32 * size_in_mb);

  bl_error_boot_type (*init)(void);

  void (*unlock_xpu_prot_ddr_region)(void);

  bl_error_boot_type (*milestone_set)(boot_mode_type boot_mode, void * qsee_interface);
  
  bl_error_boot_type (*image_load_complete)(boot_boolean img_load_status);
  
  bl_error_boot_type (*dbg_policy_load_milestone)(void);

  bl_error_boot_type (*wrap_blob_with_oem_pub_key)(uint8  *in, 
                                                   uint32 in_len, 
                                                   uint8  *out, 
                                                   uint32 *out_len, 
                                                   uint8  *context);
  
} boot_seclib_if_type;


/*===========================================================================
**  Function :  boot_sec_img_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_sec_img_get_interface
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_seclib_get_interface(void *seclib_img_if);

#endif /* BOOT_SECLIB_IF_H */
