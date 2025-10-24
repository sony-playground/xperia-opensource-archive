/*=============================================================================

                            XBLConfig Module Sources

GENERAL DESCRIPTION
  This file defines XBL config api's that interface with XBLRamLib's start address
  load module.

Copyright 2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
10/16/20     rama    Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>
#include "XBLConfig.h"
#include "boot_config_context.h"
#include "XcfgUtils.h"
#include <XcfgImageInterface.h>

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
#define XCFG_RAM_MAX_LOGICAL_BLOCK_COUNT 1

typedef struct xcfg_ram_info_type
{
  xcfg_metadata_header_type *xcfg_metadata_ptr;
  uint32 xcfg_metadata_size;
  uintnt max_logical_block_count;
} xcfg_ram_info_type;

xcfg_ram_info_type *xcfg_ram_info_table = NULL;
boolean segment_loadable = FALSE;

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
    if ( max_logical_blk_ptr == NULL || xcfg_ram_info_table == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    *max_logical_blk_ptr = xcfg_ram_info_table->max_logical_block_count;
    status = XBLCONFIG_SUCCESS;

  } while (0);

  return status;
}

/*===========================================================================
**  Function :  xcfg_ram_image_get_block_info
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the block size and offset for a given index
*  (info of metadata header in case of init from start address)
*
* @param[in]
*   index                index of the block info to be retrieved
* @param[out]
*   blk_size_ptr         pointer to store the block size
*   blk_offset_ptr       pointer to store the block offset
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
xblconfig_status_type xcfg_ram_image_get_block_info
(
  uintnt index,
  uintnt *blk_size_ptr,
  uintnt *blk_offset_ptr
)
{
  xblconfig_status_type status = XBLCONFIG_SUCCESS;

  do
  {
    if ( blk_size_ptr == NULL || blk_offset_ptr == NULL || xcfg_ram_info_table == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }

    if (index > 0)
    {
      status = XBLCONFIG_META_DATA_LOAD_ERR;
      break;
    }

    *blk_offset_ptr = 0;
    *blk_size_ptr = xcfg_ram_info_table->xcfg_metadata_size;
    segment_loadable = TRUE;
  } while (0);

  return status;
}

/*===========================================================================
**  Function :  xcfg_ram_get_data
** ==========================================================================
*/
/*!
*
* @brief
*   This function loads data from xbl segment in ram to destinition buffer
*
* @param[in]
*  uintnt file_offset          - Start of data to be loaded
*
*  uintnt file_size            - Size of data to be loaded.
*
* @param[out]
*  void *buffer                - pointer to buffer, loaded with data
*
*
* @par Dependencies
*  XBLConfig data segment is assumed to be loaded before calling the api
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xcfg_ram_get_data( uintnt file_offset, uintnt file_size, void *buffer)
{
  xblconfig_status_type status = XBLCONFIG_SUCCESS;
  uintnt phy_addr;

  do
  {
    if (buffer == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    if ( file_size == 0)
    {
      status = XBLCONFIG_INVALID_SIZE;
      break;
    }
    if (file_size > XCFG_UINT32_MAX)
    {
      status = XBLCONFIG_OVERFLOW_ERR;
      break;
    }

    phy_addr = (uintnt)(xcfg_ram_info_table->xcfg_metadata_ptr) + file_offset;

    memcpy( buffer, (void *)phy_addr, (uint32) file_size);

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
    if (xcfg_ram_info_table == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }
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
    if (xcfg_ram_info_table == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }

    status = xcfg_free((void**)&(xcfg_ram_info_table));

    /* if any buffer freeing failed, indicate it to caller */
    if (status != XBLCONFIG_SUCCESS)
    {
      break;
    }

    status = XBLCONFIG_SUCCESS;

  } while (0);

  return status;
}

/*===========================================================================
**  Function :  xcfg_ram_image_interface_init
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes xbl config image loading interface
*
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
xblconfig_status_type xcfg_ram_image_interface_init(boot_handle config_context_handle)
{
  xblconfig_status_type status = XBLCONFIG_RAM_ELF_INFO_INIT_ERR;
  xcfg_metadata_header_type *xcfg_metadata_ptr = NULL;
  do
  {

    if (xcfg_ram_info_table == NULL)
    {
      /*Ramlib data structs are expected to be set before interface init.
      In case of ramlib the data is already available
        since xbl config is part of xbl elf.  */
      status = XBLCONFIG_RAM_ELF_INFO_INIT_ERR;
      break;
    }
    xcfg_metadata_ptr = xcfg_ram_info_table->xcfg_metadata_ptr;
    if (xcfg_metadata_ptr == NULL)
    {
      status = XBLCONFIG_RAM_ELF_INFO_INIT_ERR;
      break;
    }
    /* Populate xcfg_ram_info_table */
    xcfg_ram_info_table->xcfg_metadata_size = xcfg_metadata_ptr->XBLconfig_meta_size;
    xcfg_ram_info_table->max_logical_block_count = XCFG_RAM_MAX_LOGICAL_BLOCK_COUNT;

    status = XBLCONFIG_SUCCESS;

  } while (0);

  /* Free malloced memory in case of error */
  if (status != XBLCONFIG_SUCCESS)
  {
    xcfg_free((void**)&(xcfg_ram_info_table));
  }

  return status;

} /* xcfg_ram_image_interface_init */

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
*  xcfg_ram_start_address   Start address of xbl config
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
  uintnt *xcfg_ram_start_address
)
{
  xblconfig_status_type status = XBLCONFIG_INIT_ERR;

  do
  {
    if (xcfg_ram_info_table != NULL)
    {
      status = XBLCONFIG_SUCCESS;
      break;
    }

    if (xcfg_ram_start_address == NULL)
    {
      break;
    }

    status = xcfg_malloc(sizeof(xcfg_ram_info_type), (void **)&xcfg_ram_info_table);
    if (status != XBLCONFIG_SUCCESS)
    {
      break;
    }

    xcfg_ram_info_table->xcfg_metadata_ptr = (xcfg_metadata_header_type *)xcfg_ram_start_address;
    status = XBLCONFIG_SUCCESS;
  } while (FALSE);
  return status;
}

xcfg_image_interface_type xcfg_ram_addr_image_interface =
{
  xcfg_ram_image_interface_init,
  xcfg_ram_image_get_max_logical_block_count,
  xcfg_ram_image_get_block_info,
  xcfg_ram_get_block_data,
  xcfg_ram_image_interface_deinit,
  xcfg_ram_image_interface_reset
};
