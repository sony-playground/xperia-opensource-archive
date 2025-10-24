/*=============================================================================

                            XBLConfig Module Sources

GENERAL DESCRIPTION
  This file defines XBL config api's that interface with XBLRamLib's elf image
  load module.

Copyright 2017,2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
10/16/20     rama     Added image interface table for xcfg RAM APIs
06/25/20     rama     Updated to SecLib calls
05/10/17     kpa      rename XBLCONFIG_SIZE_OVERFLOW_ERR to XBLCONFIG_OVERFLOW_ERR
05/03/17     kpa      update integer overflow checks
01/24/17     kpa      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>
#include "XBLConfig.h"
#include "XcfgRamElf.h"
#include "boot_config_context.h"
#include "XcfgFlashInterface.h"
#include "XcfgUtils.h"
#include "boot_loader_if.h"
#include <boot_elf_loader.h>
#include "boot_elf_header.h"
#include "MIprogressive.h"
#include <XcfgImageInterface.h>

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

/* XBLConfig elf info structure containing pointer to
hash buffer, elf header and segment info for ram lib */
//static xcfg_ram_elf_info_type xcfg_ram_elf_info;

//static boot_handle elf_loader = 0;
//static boot_loader_if_type loader_if;
boolean segment_loadable = FALSE;

/*
typedef struct elf_segment_info_type
{
  boot_boolean is_loadable;
  uint64 file_size;
  uint64 file_offset;
  uint64 dest_addr;
  uint64 memsz;
} elf_segment_info_type;
*/

typedef struct xcfg_ram_elf_type
{
  xcfg_ram_elf_info_type xcfg_ram_elf_info;
  boot_handle elf_loader;
  boot_loader_if_type *loader_if;
} xcfg_ram_elf_type;

static xcfg_ram_elf_type *xcfg_ram_elf_data = NULL;

extern bl_error_boot_type boot_seclib_is_valid_segment(uint32 format, const void *entry, boot_boolean *valid_segment);

/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/

/*===========================================================================
**  Function :  xcfg_ram_image_get_max_logical_block_count
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the max number of image logical blocks
*  (segments in case of elf image)
*
* @param[out]
*   max_logical_blk_ptr      pointer to max logical blocks
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xcfg_ram_image_get_max_logical_block_count
(
  uintnt *max_logical_blk_ptr
)
{
  xblconfig_status_type status = XBLCONFIG_META_DATA_LOAD_ERR;
  do
  {
    if ( max_logical_blk_ptr == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    *max_logical_blk_ptr = xcfg_ram_elf_data->xcfg_ram_elf_info.max_phnum;
    status = XBLCONFIG_SUCCESS;

  } while (0);

  return status;
}

static
boolean boot_get_elf_phdr_entry_info
(
  void *elf_hdr,
  void *prog_hdr,
  uintnt index,
  uintnt *seg_file_size_ptr,
  boolean *is_seg_loadable_ptr,
  uintnt *file_offset,
  uintnt *physical_addr
)
{
  boolean status = FALSE;
  boot_boolean valid_segment;
  uint8 elf_format;
  bl_error_boot_type sec_img_success = BL_ERR_IMG_SECURITY_FAIL;
  void *prog_hdr_entry_addr =NULL;

  BL_VERIFY((NULL != elf_hdr) && (NULL != prog_hdr) &&
            (NULL != seg_file_size_ptr) &&
            (NULL != file_offset) && (NULL != physical_addr),
            BL_ERR_NULL_PTR_PASSED|BL_ERROR_GROUP_BOOT);

  /* Check the EI_CLASS to see if it's 32bit or 64bit ELF
   * Note the e_ident format is the same in both 32bit and 64bit
   */
  elf_format = ((Elf64_Ehdr *)elf_hdr)->e_ident[ELFINFO_CLASS_INDEX];

#if 0
  /* Verify elf header*/
  sec_img_success = boot_seclib_img_auth_validate_elf(elf_format, (const void *)elf_hdr);
  BL_VERIFY((sec_img_success == BL_ERR_NONE),
            (uint16)sec_img_success|BL_ERROR_GROUP_SECIMG);
#endif
  prog_hdr_entry_addr =  (elf_format == ELF_CLASS_64) ?
                         (void *)&(((Elf64_Phdr *)prog_hdr)[index]):
                         (void *)&(((Elf32_Phdr *)prog_hdr)[index]);

#if 1
  sec_img_success = boot_seclib_is_valid_segment(elf_format, prog_hdr_entry_addr, &valid_segment);
  BL_VERIFY((sec_img_success == BL_ERR_NONE),
            (uint16)sec_img_success|BL_ERROR_GROUP_SECIMG);

  if (valid_segment)
  {
    *is_seg_loadable_ptr = TRUE;
    segment_loadable = TRUE;
  }
  else
  {
    *is_seg_loadable_ptr = FALSE;
    segment_loadable = FALSE;
  }
#endif
  *seg_file_size_ptr = (elf_format == ELF_CLASS_64) ?
                       (((Elf64_Phdr *)prog_hdr)[index]).p_filesz :
                       (((Elf32_Phdr *)prog_hdr)[index]).p_filesz;

  *file_offset = (elf_format == ELF_CLASS_64) ?
                 (((Elf64_Phdr *)prog_hdr)[index]).p_offset :
                 (((Elf32_Phdr *)prog_hdr)[index]).p_offset;

  *physical_addr = (elf_format == ELF_CLASS_64) ?
                   (((Elf64_Phdr *)prog_hdr)[index]).p_paddr :
                   (((Elf32_Phdr *)prog_hdr)[index]).p_paddr;



  status = TRUE;

  return status;
}

xblconfig_status_type xcfg_ram_image_get_block_info
(
  uintnt index,
  uintnt *blk_size_ptr,
  /*boolean *is_blk_loadable_ptr,*/
  uintnt *blk_offset_ptr
)
{
  xblconfig_status_type status = XBLCONFIG_META_DATA_LOAD_ERR;
  xcfg_ram_segment_info_type *xcfg_segment_info_ptr;
  boolean seg_status = FALSE;
  uintnt blk_destn_addr =0;
  boolean is_blk_loadable = 0;

  do
  {
    if ( blk_size_ptr == NULL || blk_offset_ptr == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }

    seg_status = boot_get_elf_phdr_entry_info(
                   (void *)xcfg_ram_elf_data->xcfg_ram_elf_info.elf_hdr,
                   (void*)xcfg_ram_elf_data->xcfg_ram_elf_info.prog_hdr,
                   index,
                   blk_size_ptr,
                   &is_blk_loadable,
                   blk_offset_ptr,
                   &blk_destn_addr
                 );
    if (seg_status == FALSE)
    {
      status = XBLCONFIG_META_DATA_LOAD_ERR;
      break;
    }

    xcfg_segment_info_ptr = xcfg_ram_elf_data->xcfg_ram_elf_info.segment_info_ptr;

    /*while searching for meta data also keep track of segment offset and size */
    xcfg_segment_info_ptr[index].offset = *blk_offset_ptr;
    xcfg_segment_info_ptr[index].size = *blk_size_ptr;
    xcfg_segment_info_ptr[index].is_verified = FALSE;
    xcfg_segment_info_ptr[index].p_addr = blk_destn_addr;
    xcfg_segment_info_ptr[index].is_valid = TRUE;

    if (is_blk_loadable == 1)
      segment_loadable = TRUE;
    else
      segment_loadable = FALSE;

    status = XBLCONFIG_SUCCESS;
  } while (0);

  return status;
}

/*===========================================================================
**  Function :  xcfg_ram_get_block_data
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns xbl config data at input offset
*  (segments in case of elf image)
*
* @param[in]
*  uintnt block_offset         - Start of data to be loaded in partition from
*                                storge device
*  uintnt block_size           - Size of data to be loaded.
*
* @param[out]
*  void *buffer                - pointer to buffer, loaded with data
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/

xblconfig_status_type xcfg_ram_get_block_data
(
  uintnt block_offset,
  uintnt block_size,
  void *buffer,
  boot_boolean validate
)
{
  return xcfg_ram_get_data(block_offset, block_size, buffer);
}

/*===========================================================================
**  Function :  xcfg_ram_image_interface_reset
** ==========================================================================
*/
/*!
*
* @brief
*   This function resets xbl config image loading interface
*
* @param[out]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xcfg_ram_image_interface_reset (void)
{
  xblconfig_status_type status = XBLCONFIG_SUCCESS;
  do
  {
    if (xcfg_ram_elf_data == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }
#if 0
    /* Close the image partition and release the flash translation interface */
    xcfg_ram_elf_data->loader_if->close(xcfg_ram_elf_data->elf_loader);
#endif

  } while (FALSE);

  return status;
}

/*===========================================================================
**  Function :  xcfg_ram_image_interface_deinit
** ==========================================================================
*/
/*!
*
* @brief
*   This function deinitializes xbl config image loading interface
*   It free's up structures allocated by image loading interface
*
* @param[out]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xcfg_ram_image_interface_deinit (void)
{
  xblconfig_status_type status = XBLCONFIG_DEINIT_ERR;
  do
  {
    if (xcfg_ram_elf_data == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }

    status = xcfg_free((void**)&(xcfg_ram_elf_data->xcfg_ram_elf_info.segment_info_ptr));

    /* if any buffer freeing failed, indicate it to caller */
    if (status != XBLCONFIG_SUCCESS)
      break;

    status = XBLCONFIG_SUCCESS;

  } while (0);

  return status;
}

/*===========================================================================
**  Function :  xcfg_ram_get_config_item_segment
** ==========================================================================
*/
/*!
*
* @brief
*   This function parses program header table and locates segment cointaining
* data at given offset.
*
* @param[in]
*    xcfg_elf_info_ptr        Pointer to struct containing segments info
*    config_item_start_offset location of requested item data within partition
*    config_item_size         size of data
*
* @param[out]
*   segment_index             pointer to segment index
*   segment_offset            pointer to segment offset
*   segment_size              pointer to segment size
*   phy_addr                  pointer to data block destination address
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xcfg_ram_get_config_item_segment
(
  xcfg_ram_elf_info_type *xcfg_elf_info_ptr,
  uintnt config_item_start_offset,
  uintnt config_item_size,
  uintnt *segment_index,
  uintnt *segment_offset,
  uintnt *segment_size,
  uintnt *phy_addr
)
{
  xblconfig_status_type status = XBLCONFIG_VERIFY_ERR;
  uintnt index =0 ;
  xcfg_ram_segment_info_type *xcfg_segment_info_ptr;

  do
  {
    if ( segment_index == NULL || segment_offset == NULL ||
         segment_size == NULL || phy_addr == NULL || xcfg_elf_info_ptr == NULL
       )
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    if ( xcfg_elf_info_ptr->segment_info_ptr == NULL)
    {
      status = XBLCONFIG_INIT_ERR;
      break;
    }

    xcfg_segment_info_ptr  = xcfg_elf_info_ptr->segment_info_ptr;
    for (index =0; index < xcfg_elf_info_ptr->max_phnum; index++)
    {
      /*Check for integer overflow */
      if ((xcfg_segment_info_ptr[index].offset + xcfg_segment_info_ptr[index].size)
          < xcfg_segment_info_ptr[index].offset)
      {
        status = XBLCONFIG_OVERFLOW_ERR;
        break;
      }
      if ((config_item_start_offset + config_item_size)
          < config_item_start_offset)
      {
        status = XBLCONFIG_OVERFLOW_ERR;
        break;
      }

      if ( xcfg_segment_info_ptr[index].offset <= config_item_start_offset &&
           (xcfg_segment_info_ptr[index].offset + xcfg_segment_info_ptr[index].size)
           >= (config_item_start_offset + config_item_size) )
      {
        /* Config data fully contained within segment*/
        *segment_index = index;
        *segment_offset = xcfg_segment_info_ptr[index].offset;
        *segment_size = xcfg_segment_info_ptr[index].size;
        *phy_addr = xcfg_segment_info_ptr[index].p_addr;
        status = XBLCONFIG_SUCCESS;
        break;
      }
    }
  } while (FALSE);

  return status;
}

/*===========================================================================
**  Function :  xcfg_set_is_verified_flag
** ==========================================================================
*/
/*!
*
* @brief
*   This function sets the flag indicating a segment has been hash
*  verified once
*
* @param[in]
*  segment_index               verified segment  index
*
* @param[out]
*    None                      pointer to verified flag status
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
static xblconfig_status_type xcfg_set_is_verified_flag
(
  xcfg_ram_elf_info_type *xcfg_elf_info_ptr,
  uintnt segment_index
)
{
  xblconfig_status_type status = XBLCONFIG_VERIFY_ERR;
  do
  {
    if ( xcfg_elf_info_ptr == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }

    if (segment_index >= xcfg_ram_elf_data->xcfg_ram_elf_info.max_phnum)
    {
      status = XBLCONFIG_INVALID_SIZE;
      break;
    }

    xcfg_elf_info_ptr->segment_info_ptr[segment_index].is_verified = TRUE;
    status = XBLCONFIG_SUCCESS;

  } while (0);

  return status;
}

boolean boot_get_elf_hash_segment_size
(
  void *elf_hdr,
  void *prog_hdr,
  uintnt *hash_segment_size
)
{
  boolean status = FALSE;
  uint8 elf_format = 0;
  uintnt phdr_num = 0, index = 0;
  uint32 phdr_flags = 0;
  uint64 phdr_memsz =0;
  //bl_error_boot_type sec_img_success = BL_ERR_IMG_SECURITY_FAIL;

  BL_VERIFY((NULL !=  elf_hdr) && (NULL !=  prog_hdr) &&
            (NULL !=  hash_segment_size),
            BL_ERR_NULL_PTR_PASSED|BL_ERROR_GROUP_BOOT);

  /* Check the EI_CLASS to see if it's 32bit or 64bit ELF
   * Note the e_ident format is the same in both 32bit and 64bit
   */
  elf_format = ((Elf64_Ehdr *)elf_hdr)->e_ident[ELFINFO_CLASS_INDEX];

#if 0
  /* Verify elf header*/
  sec_img_success = boot_seclib_img_auth_validate_elf(elf_format, (const void *)elf_hdr);
  BL_VERIFY((sec_img_success == BL_ERR_NONE),
            (uint16)sec_img_success|BL_ERROR_GROUP_SECIMG);
#endif

  if (elf_format == ELF_CLASS_64)
  {
    phdr_num = ((Elf64_Ehdr *)elf_hdr)->e_phnum;
  }
  else
  {
    phdr_num = ((Elf32_Ehdr *)elf_hdr)->e_phnum;
  }

  /* Locate hash segment */
  for (index = 0; index < phdr_num; index++)
  {
    if (elf_format == ELF_CLASS_64)
    {
      phdr_flags = (((Elf64_Phdr *)prog_hdr)[index]).p_flags;
      phdr_memsz = (((Elf64_Phdr *)prog_hdr)[index]).p_memsz;
    }
    else
    {
      phdr_flags = (((Elf32_Phdr *)prog_hdr)[index]).p_flags;
      phdr_memsz = (((Elf32_Phdr *)prog_hdr)[index]).p_memsz;
    }

    /* Check for the hash segment program header to parse QC header */
    if ( MI_PBT_SEGMENT_TYPE_VALUE(phdr_flags) == MI_PBT_HASH_SEGMENT)
    {
      *hash_segment_size = (uintnt)phdr_memsz;
      status = TRUE;
      break;
    }
  }
  return status;
}

boolean boot_get_elf_prog_header_count
(
  void *elf_hdr,
  uintnt *max_phnum
)
{
  boolean status = FALSE;
  uint8 elf_format = 0;
  //bl_error_boot_type sec_img_success = BL_ERR_IMG_SECURITY_FAIL;

  BL_VERIFY((NULL !=  elf_hdr) && (NULL !=  max_phnum),
            BL_ERR_NULL_PTR_PASSED|BL_ERROR_GROUP_BOOT);

  /* Check the EI_CLASS to see if it's 32bit or 64bit ELF
   * Note the e_ident format is the same in both 32bit and 64bit
   */
  elf_format = ((Elf64_Ehdr *)elf_hdr)->e_ident[ELFINFO_CLASS_INDEX];

#if 0
  /* Verify elf header*/
  sec_img_success = boot_seclib_img_auth_validate_elf(elf_format, (const void *)elf_hdr);
  BL_VERIFY((sec_img_success == BL_ERR_NONE),
            (uint16)sec_img_success|BL_ERROR_GROUP_SECIMG);
#endif

  *max_phnum =0;
  if (elf_format == ELF_CLASS_64)
  {
    *max_phnum = ((Elf64_Ehdr *)elf_hdr)->e_phnum;
    status = TRUE;
  }
  else
  {
    *max_phnum = ((Elf32_Ehdr *)elf_hdr)->e_phnum;
    status = TRUE;
  }

  return status;
}

xblconfig_status_type xcfg_ram_image_interface_init(boot_handle config_context_handle)
{
  xblconfig_status_type status = XBLCONFIG_META_DATA_LOAD_ERR;
  uintnt hash_segment_size  = 0;
  boolean hash_segment_status = FALSE;

  xcfg_ram_elf_info_type *xcfg_elf_info_ptr = &xcfg_ram_elf_data->xcfg_ram_elf_info;
  uintnt max_phnum = 0;
  uintnt *max_phnum_ptr = NULL;

  do
  {

    /*First locate hash segment */
    if (xcfg_elf_info_ptr->elf_hdr == NULL || xcfg_elf_info_ptr->prog_hdr == NULL ||
        xcfg_elf_info_ptr->hash_buffer == NULL )
    {
      /*Ramlib data structs for elf and prog headers are expected to be
        set before interface init. In case of ramlib the data is already available
        since xbl config is part of xbl elf.  */
      status = XBLCONFIG_RAM_ELF_INFO_INIT_ERR;
      break;
    }
    /* Hash segment shall have been already authenticated as a part of
       XBL elf load since XBLConfig segments for Ram Lib usecase are part of
       XBL elf. No need to explicitly reauthenticate */

    /* Get hash segment data size of xbl config image */
    hash_segment_status = boot_get_elf_hash_segment_size(
                            xcfg_elf_info_ptr->elf_hdr,
                            xcfg_elf_info_ptr->prog_hdr,
                            &hash_segment_size);
    if (hash_segment_status != TRUE)
    {
      status = XBLCONFIG_HASH_SEG_ERR;
      break;
    }

    xcfg_elf_info_ptr->hash_buffer_size = hash_segment_size;

    /* Configure internal data structs */
    if ( TRUE != boot_get_elf_prog_header_count(xcfg_elf_info_ptr->elf_hdr,
         &max_phnum))
    {
      /* Could not get max prog header count from elf header */
      status = XBLCONFIG_META_DATA_LOAD_ERR;
      break;
    }

    /*overflow check */
    if (sizeof(xcfg_ram_segment_info_type) > (XCFG_UINT32_MAX / max_phnum))
    {
      status = XBLCONFIG_OVERFLOW_ERR;
      break;
    }

    /* Prepare segment info data struct, keeping track of all segment
       offset and sizes
    */
    status = xcfg_malloc( max_phnum * sizeof(xcfg_ram_segment_info_type),
                          (void **)&(xcfg_elf_info_ptr->segment_info_ptr));
    if (status != XBLCONFIG_SUCCESS)
    {
      break;
    }

    memset( (void *)(xcfg_elf_info_ptr->segment_info_ptr), 0x0,
            (uint32)(max_phnum * sizeof(xcfg_ram_segment_info_type)));

    max_phnum_ptr = &xcfg_elf_info_ptr->max_phnum;
    *max_phnum_ptr = max_phnum;

    status = XBLCONFIG_SUCCESS;

  } while (0);

  /* Free malloced memory in case of error */
  if (status != XBLCONFIG_SUCCESS)
  {
    xcfg_free((void**)&(xcfg_elf_info_ptr->segment_info_ptr));
  }

  return status;

} /* xcfg_ram_image_interface_init */

/*===========================================================================
**  Function :  xcfg_validate_data
** ==========================================================================
*/
/*!
*
* @brief
*   This function is a stub to verify the loaded XBLConfig item.
*   It is an intermediate api to add image meta data (eg segment info)
*   needed by authentication api's which do the actual validation.
*
* @param[in]
*     start_offset      location of requested item data within partition
*     config_item_size  Pointer to size of data to be verified
*     buffer            Pointer to data to be verified
*
* @param[out]
*  None
*
* @par Dependencies
*   buffer is assumed to be populated with data to be verified
*
* @retval
*   xblconfig_status_type. XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xcfg_validate_data
(
  uintnt start_offset,
  uintnt config_item_buffer_size,
  void *buffer
)
{

  /*This function is a stub to verify the loaded XBLConfig item
  Since the config segment is already present in memory and
  authenticated by the time xbl ram lib runs, it not necessary
  to re-authenticate or validate the data again */
  return XBLCONFIG_SUCCESS;
}


/*===========================================================================
**  Function :  xcfg_verified_config_data_read
** ==========================================================================
*/
/*!
*
* @brief
*   This function reads XBLConfig item and later proceeds to validate it
*   (eg verify its hash in context of elf image).
*
* @param[in]
*     start_offset      location of requested item data within partition
*     config_item_size  size of data to be verified
*     buffer            Pointer to data to be verified
*
* @param[out]
*  None
*
* @par Dependencies
*   buffer is assumed to be big enough for data to be read and verified
*
* @retval
*   xblconfig_status_type. XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xcfg_verified_config_data_read
(
  uintnt start_offset,
  uintnt config_item_size,
  void *buffer
)
{
  xblconfig_status_type status = XBLCONFIG_VERIFY_ERR;
  //bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if (xcfg_ram_elf_data == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }

    if ( buffer == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }

    if (config_item_size == 0)
    {
      status = XBLCONFIG_INVALID_SIZE;
      break;
    }

    /* Load config item data into input buffer */
    status = xcfg_ram_get_data(start_offset,
                               config_item_size,
                               buffer);
    if (status != XBLCONFIG_SUCCESS)
    {
      break;
    }
#if 0
    return_status = xcfg_ram_elf_data->loader_if->load_buffer(xcfg_ram_elf_data->elf_loader, start_offset, config_item_size, buffer);

    if (return_status != BL_ERR_NONE)
    {
      status = XBLCONFIG_HASH_SEG_ERR;
      break;
    }
#endif

  } while (FALSE);

  return status;
}

/*===========================================================================
**  Function :  xblconfig_ramlib_init
** ==========================================================================
*/
/*!
*
* @brief
*   This function sets elf meta info consumed by xbl config ramlib
*
* @param[in]
*    elf_hdr            pointer to elf header
*    prog_hdr           pointer to prog header table
*    hash_buffer        pointer to buffer containing hash segment.
*
* @param[out]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xblconfig_ramlib_init
(
  boot_handle config_context_handle,
  void *elf_hdr,
  void *prog_hdr,
  void *hash_buffer
)
{
  xblconfig_status_type status = XBLCONFIG_INIT_ERR;
  //bl_error_boot_type return_status = BL_ERR_NONE;


  do
  {
    status = xcfg_malloc(sizeof(xcfg_ram_elf_type), (void **)&xcfg_ram_elf_data);
    if (status != XBLCONFIG_SUCCESS)
    {
      break;
    }

    if (elf_hdr == NULL || prog_hdr == NULL || hash_buffer == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }

    xcfg_ram_elf_data->xcfg_ram_elf_info.elf_hdr = elf_hdr;
    xcfg_ram_elf_data->xcfg_ram_elf_info.prog_hdr = prog_hdr;
    xcfg_ram_elf_data->xcfg_ram_elf_info.hash_buffer = hash_buffer;
#if 0
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_LOADER_INTERFACE, (void**)&xcfg_ram_elf_data->loader_if);
    if (return_status != BL_ERR_NONE || xcfg_ram_elf_data->loader_if->open == NULL)
    {
      status = XBLCONFIG_RAM_ELF_INFO_INIT_ERR;
      break;
    }

    return_status = xcfg_ram_elf_data->loader_if->open(config_context_handle, &xcfg_ram_elf_data->elf_loader);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    boot_elf_loader_metadata_type elf_metadata;
    elf_metadata.elf_hdr = elf_hdr;
    elf_metadata.prog_hdr = prog_hdr;
    elf_metadata.hash_buffer = hash_buffer;

    //return_status = xcfg_ram_elf_data->loader_if->set(elf_handle, BOOT_LOADER_METADATA, &elf_metadata);
    return_status = xcfg_ram_elf_data->loader_if->set(&xcfg_ram_elf_data->elf_loader, BOOT_LOADER_METADATA, &elf_metadata);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
#endif
    status = XBLCONFIG_SUCCESS;

  } while (FALSE);
  return status;
}

/*===========================================================================
**  Function :  xcfg_ramlib_get_physical_address
** ==========================================================================
*/
/*!
*
* @brief
*   This function gives physical address corresponding to given offset for
*   config data that is already loaded in ram
*
* @param[in]
*    blk_offset         data block offset that needs to be translated
*                       to phy addr where its already loaded
*    blk_size           data block size
*
* @param[out]
*    physical_addr      pointer to elf header
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xcfg_ramlib_get_physical_address
(
  uintnt blk_offset,
  uintnt blk_size,
  uintnt *physical_addr
)
{
  xblconfig_status_type status = XBLCONFIG_INIT_ERR;
  uintnt segment_index, segment_offset, segment_size, phy_addr;
  do
  {
    if (physical_addr == NULL || blk_size == 0)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    /* get segment index of config data item */
    status = xcfg_ram_get_config_item_segment(&xcfg_ram_elf_data->xcfg_ram_elf_info,
             blk_offset,
             blk_size,
             &segment_index,
             &segment_offset,
             &segment_size,
             &phy_addr );
    if (status != XBLCONFIG_SUCCESS)
    {
      break;
    }
    else
    {
      /*reinit status to default */
      status = XBLCONFIG_INIT_ERR;
    }

    /*Ensure the block offset is bigger than or equal to its
      segment start, although the above get_config_item_segment
      should have also checked the same */
    if (segment_offset > blk_offset)
    {
      status = XBLCONFIG_INVALID_SIZE;
      break;
    }

    /* get the location in memory of requested block */
    *physical_addr = phy_addr + (blk_offset - segment_offset);

    if (*physical_addr < phy_addr)
    {
      status = XBLCONFIG_OVERFLOW_ERR;
      break;
    }
    status = XBLCONFIG_SUCCESS;

  } while (FALSE);

  return status;
}


xcfg_image_interface_type xcfg_ram_image_interface =
{
  xcfg_ram_image_interface_init,
  xcfg_ram_image_get_max_logical_block_count,
  xcfg_ram_image_get_block_info,
  xcfg_ram_get_block_data,
  xcfg_ram_image_interface_deinit,
  xcfg_ram_image_interface_reset
};
