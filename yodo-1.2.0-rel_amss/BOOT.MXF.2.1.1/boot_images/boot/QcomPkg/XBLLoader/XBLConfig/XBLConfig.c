/*=============================================================================

                            XBLConfig Module Sources

GENERAL DESCRIPTION
  This file defines XBL config api's to support initializing XBLconfig module
  and access a config item.

Copyright 2016,2017,2020-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
09/13/22     yps      Fix name length issue.
05/24/22     yps      Update best match algorithm for oem flavor id 
05/19/22     tmt      Move cfg_sort_table to xbl_config_data so init/clear at correct places
05/02/22     tmt      Guard against 2nd call to create_cfg_sort_list()
04/19/22     yps      Add apis to support dtbo
12/20/21     yps      Implement best match algorithm
11/11/21     tmt      Fix xblconfig_status_type xblconfig_create_platforminfo() encoding
06/25/21     tmt      Add DTB support: xblconfig_open_by_hwinfo, xblconfig_chipinfo, xblconfig_platforminfo
04/20/21     rrwt     added nullptr error check before free of xbl_cfg
10/16/20     rama     Added init mode to xblconfig_init.
10/16/17     kpa      Replace strcmp by strncmp
05/10/17     kpa      rename XBLCONFIG_SIZE_OVERFLOW_ERR to XBLCONFIG_OVERFLOW_ERR
05/03/17     kpa      update meta data buffer pointer used for validation.
03/15/17     kpa      fix memory leaks in error scenario, update get data api's
03/02/17     kpa      use heap instead of stack variable for xbl config cookie
02/14/17     kpa      code cleanup
02/10/17     kpa      Update error checks in xcfg_load_meta_data
01/20/17     kpa      Updates to metadata header and config item parsing logic
10/14/16     kpa      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>

#include "XBLConfig.h"
#include "XcfgImageInterface.h"
#include "XcfgUtils.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
#define EIGHT_BYTE_ALIGN_SIZE 0x8

/* ChipInfo & PlatformInfo Masks */
#define ChipVersionMask 0xFFFF0000
#define PlatformTypeMask 0xFF000000
#define PlatformSubTypeMask 0x00FF0000
#define PlatformVersionMask 0x0000FFFF

#define dtb_ext ".dtb"
#define dtbo_ext ".dtbo"

typedef struct cfg_item_list
{
  struct cfg_item_list * p_prev_item;
  struct cfg_item_list * p_next_item;
  uintnt index;
  /* pointer to start of entry in blob */
  xcfg_metadata_table_entries_type *entry_ptr;
} cfg_item_list_type;

typedef struct cfg_sort_list
{
  cfg_item_list_type *p_dtb_list;
  cfg_item_list_type *p_soc_dtbo_list;
  cfg_item_list_type *p_platform_dtbo_list;
} cfg_sort_list_type;

typedef struct xbl_config_type
{
  void *xcfg_metadata_buff;
  uintnt xcfg_metadata_start_offset;

  /* List to manage variable length config entries */
  xcfg_parsed_metadata_table_entry_type *config_entry_list;
  uintnt max_config_entries;

  /* Data structure to keep track of open config items */
  xcfg_config_handle_type *xcfg_handle_list;
  uint32 xcfg_handle_max_count;
  uint32 xcfg_handle_count;

  boot_handle config_context_handle;
  uint32 dtbo_initialized;
  cfg_sort_list_type *cfg_sort_table;
} xbl_config_type;

xcfg_image_interface_type *xcfg_image_interface = NULL;

static xbl_config_type *xbl_config_data = NULL;
extern boolean segment_loadable;
boolean segment_loadable __attribute__((weak));

#define INITIAL_CONFIG_HANDLES  5
#define SIZE_INCREASE_MULTIPLE 2

/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/

/*===========================================================================
**  Function :  xcfg_load_meta_data
** ==========================================================================
*/
/*!
*
* @brief
*   This function finds and loads xblconfig meta data
*
* @param[out]
*   xcfg_elf_metadata_buff_ptr      pointer to buffer loaded with meta data
*   xcfg_metadata_start_offset_ptr  pointer to store meta data start offset
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

xblconfig_status_type xcfg_load_meta_data(boot_handle config_context_handle)
{
  uint8 xcfg_cookie_ptr[XCFG_LOADER_MAGIC_COOKIE_SIZE];
  xblconfig_status_type status = XBLCONFIG_INIT_ERR;
  uintnt max_logical_blocks = 0, index = 0, cookie_size = 0;
  uintnt blk_size = 0, blk_offset = 0;
  boolean meta_data_found = FALSE;
  segment_loadable = TRUE;

  do
  {
    status = xcfg_image_interface->init(config_context_handle);
    if (status != XBLCONFIG_SUCCESS)
      break;

    status =  xcfg_image_interface->get_max_logical_block_count(&max_logical_blocks);
    if (status != XBLCONFIG_SUCCESS)
      break;

    /* Allocate temporary buffer for reading cookie */
    cookie_size = XCFG_LOADER_MAGIC_COOKIE_SIZE;

    for (index = 0; index < max_logical_blocks; index++)
    {
      status = xcfg_image_interface->get_block_info(index, &blk_size, &blk_offset);

      if (status != XBLCONFIG_SUCCESS)
        break;

      /* Search for meta data in current block/segment */
      if (segment_loadable == TRUE  && blk_size > 0 && meta_data_found == FALSE)
      {
        /* Read first four bytes to check if its a xbl Config data segment */
        status = xcfg_image_interface->get_block_data(blk_offset, cookie_size, (void *)xcfg_cookie_ptr, FALSE);
        /*Note: 'Block' is a generic term to denote fileformat's data items to be checked
          (which is used to contain xblconfig blob. In case of elf file format its a segment */
        if (status != XBLCONFIG_SUCCESS)
          break;

        if (
          xcfg_cookie_ptr[XCFG_LOADER_MAG0_INDEX] == XCFG_LOADER_MAG0 &&
          xcfg_cookie_ptr[XCFG_LOADER_MAG1_INDEX] == XCFG_LOADER_MAG1 &&
          xcfg_cookie_ptr[XCFG_LOADER_MAG2_INDEX] == XCFG_LOADER_MAG2 &&
          xcfg_cookie_ptr[XCFG_LOADER_MAG3_INDEX] == XCFG_LOADER_MAG3
        )
        {
          status = xcfg_malloc(blk_size, (&xbl_config_data->xcfg_metadata_buff));
          if (status != XBLCONFIG_SUCCESS)
            break;

          xbl_config_data->config_context_handle = config_context_handle;

          /* Load the xbl Config data segment */
          status = xcfg_image_interface->get_block_data(blk_offset, blk_size, xbl_config_data->xcfg_metadata_buff, TRUE);
          if (status != XBLCONFIG_SUCCESS)
            break;

          /* Store the offset of meta data start. That shall later be needed to get individual item offsets */
          xbl_config_data->xcfg_metadata_start_offset = blk_offset;

          if (status == XBLCONFIG_SUCCESS)
            meta_data_found = TRUE;
        }
      }
    }

    if ((xbl_config_data->xcfg_metadata_buff == NULL) || (index > max_logical_blocks))
    {
      /* meta data was not found or all blocks were not processed */
      status = XBLCONFIG_META_DATA_LOAD_ERR;
      break;
    }
    else if (status != XBLCONFIG_SUCCESS)
    {
      break;
    }

    xcfg_image_interface->reset();

  } while (0);

  /* Free malloced memory in case of error */
  if (status != XBLCONFIG_SUCCESS)
  {
    /* Since this is memory leak cleanup after error, ignore
       the free api status and continue freeing all buffer's
    */
    xcfg_free((void**)xbl_config_data->xcfg_metadata_buff);
  }
  return status;
}

/*===========================================================================
**  Function :  xcfg_populate_config_item_list
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes the data structure that maintains config item
*   list.
*
* @param[in]
*  xcfg_parsed_metadata_table_entry_type    Pointer to config entry list
*  xcfg_metadata_header_type                Pointer to meta data header
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
static xblconfig_status_type xcfg_populate_config_item_list
(
  xcfg_parsed_metadata_table_entry_type *config_entry_list,
  xcfg_metadata_header_type *xcfg_header
)
{
  xblconfig_status_type status = XBLCONFIG_INIT_ERR;
  uintnt index =0, extended_bytes = 0, entry_ptr_val = 0;

  xcfg_metadata_table_entries_type *item_entry_ptr;
  do
  {
    if (config_entry_list == NULL || xcfg_header == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    item_entry_ptr = (xcfg_metadata_table_entries_type *)
                     ((uintnt)xcfg_header + sizeof(xcfg_metadata_header_type));

    // Populate the config item meta list with pointers to each entry
    for (index = 0; index < xbl_config_data->max_config_entries; index++)
    {
      config_entry_list[index].entry_ptr = item_entry_ptr;

      extended_bytes = (uintnt)item_entry_ptr->config_name_len % EIGHT_BYTE_ALIGN_SIZE;
      if (extended_bytes != 0)
      {
        // name length is not a multiple of byte size
        extended_bytes = EIGHT_BYTE_ALIGN_SIZE - extended_bytes;
      }

      // Point to next entry in the meta data blob
      entry_ptr_val = (uintnt) item_entry_ptr
                      + sizeof(xcfg_metadata_table_entries_type)
                      + (uintnt)item_entry_ptr->config_name_len
                      + extended_bytes
                      - 0x1 ;/* substract size of first byte that is included
                              in xcfg_metadata_table_entries_type */

      if (entry_ptr_val < (uintnt)item_entry_ptr)
      {
        status = XBLCONFIG_OVERFLOW_ERR;
        break;
      }

      item_entry_ptr = (xcfg_metadata_table_entries_type *)entry_ptr_val;
    }
    status = XBLCONFIG_SUCCESS;

  } while (0);

  return status;
}

/*===========================================================================
**  Function :  xcfg_handle_init
** ==========================================================================
*/
/*!
*
* @brief
*  Function to initialize data structure maintaining open handles.
*  Everytime this api is called, if handle list is running out of space
*  it shall double its size.
*
* @param[out]
*  xcfg_config_handle_type **xcfg_handle_ptr         Pointer to config handle list
*  uint32 *handle_max_count_ptr                      Pointer to max handle count
*  uint32 *handle_count_ptr                          Pointer to count of handles in use
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
static xblconfig_status_type xcfg_handle_init
(
  xcfg_config_handle_type **xcfg_handle_ptr,
  uint32 *handle_max_count_ptr,
  uint32 *handle_count_ptr
)
{
  xblconfig_status_type status = XBLCONFIG_HANDLE_ERR;
  xcfg_config_handle_type *xcfg_handle_temp_ptr = NULL;
  uint32 handle_list_size =0;
  boolean handle_init_flag = FALSE;
  do
  {
    if ( handle_max_count_ptr == NULL || handle_count_ptr == NULL ||
         xcfg_handle_ptr == NULL )
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    if (*handle_max_count_ptr != 0)
    {
      if (*xcfg_handle_ptr == NULL)
      {
        // Null pointer for handle list but max handle count being
        // non-zero, it should have been initialized earlier.
        // looks incorrect.
        status = XBLCONFIG_NULL_PTR_ERR;
        break;
      }

      if (*handle_count_ptr == *handle_max_count_ptr)
      {
        // Overflow check. at this point (*handle_max_count_ptr) is not 0
        if (sizeof(xcfg_config_handle_type) > (XCFG_UINT32_MAX / (*handle_max_count_ptr)))
        {
          status = XBLCONFIG_OVERFLOW_ERR;
          break;
        }

        handle_list_size = (*handle_max_count_ptr) * sizeof(xcfg_config_handle_type);

        // List of handles exhausted hence double the allocated memory for list
        if (handle_list_size > (XCFG_UINT32_MAX / SIZE_INCREASE_MULTIPLE))
        {
          status = XBLCONFIG_OVERFLOW_ERR;
          break;
        }

        status = xcfg_malloc((handle_list_size * SIZE_INCREASE_MULTIPLE), (void **)&xcfg_handle_temp_ptr);
        if (status != XBLCONFIG_SUCCESS)
        {
          break;
        }

        memset((void *)xcfg_handle_temp_ptr, 0x0, (handle_list_size * SIZE_INCREASE_MULTIPLE));

        //relocate list to new memory region
        memcpy((void *)xcfg_handle_temp_ptr, (void *)*xcfg_handle_ptr,
               handle_list_size);

        status = xcfg_free((void**)xcfg_handle_ptr);
        if (status != XBLCONFIG_SUCCESS)
        {
          break;
        }
        *xcfg_handle_ptr = xcfg_handle_temp_ptr;
        *handle_max_count_ptr = *handle_max_count_ptr * 2;
        status = XBLCONFIG_SUCCESS;
      }
    }
    else
    {
      //Since max handle count is zero, this is first time init
      if (*xcfg_handle_ptr != NULL)
        break;

      *handle_max_count_ptr = INITIAL_CONFIG_HANDLES;
      handle_list_size = (*handle_max_count_ptr) * sizeof(xcfg_config_handle_type);

      status = xcfg_malloc(handle_list_size, (void **)xcfg_handle_ptr);
      if (status != XBLCONFIG_SUCCESS)
      {
        break;
      }

      memset((void *)*xcfg_handle_ptr, 0x0, handle_list_size);
      *handle_count_ptr = 0;
      handle_init_flag = TRUE;
      status = XBLCONFIG_SUCCESS;
    }

  } while (0);

  /* Free malloced memory in case of error */
  if (status != XBLCONFIG_SUCCESS)
  {
    xcfg_free((void**)&xcfg_handle_temp_ptr);

    if (xcfg_handle_ptr != NULL)
    {
      if (*xcfg_handle_ptr != NULL && handle_init_flag == TRUE)
      {
        /* xcfg_handle_ptr was malloced in this invocation of api */
        xcfg_free((void**)xcfg_handle_ptr);
      }
    }
  }

  return status;
}

/*===========================================================================
**  Function :  xcfg_handle_allocate
** ==========================================================================
*/
/*!
*
* @brief
*  Function to initialize data structure maintaining open handles.
*  Everytime this api is called, if handle list is running out of space
*  it shall double its size.
*
* @param[in]
*  xcfg_config_handle_type **xcfg_handle_ptr  pointer to handle list
*  uint32 *handle_max_count                   Pointer to count of max
*                                             handles available
*
* @param[out]
*  uint32 *handle_count                 Pointer to current open handle count
*  uint32 *free_handle_index            Pointer filled with available handle
*                                       index
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
static xblconfig_status_type xcfg_handle_allocate
(
  xcfg_config_handle_type **xcfg_handle_ptr,
  uint32 *handle_max_count,
  uint32 *handle_count_ptr,
  uint32 *free_handle_index
)
{
  xblconfig_status_type status = XBLCONFIG_HANDLE_ERR;
  uintnt index;
  do
  {
    if ( (*handle_count_ptr) >= (*handle_max_count))
    {
      // no more space to allocate handle
      status = xcfg_handle_init(xcfg_handle_ptr, handle_max_count,
                                handle_count_ptr);

      if (status != XBLCONFIG_SUCCESS || ((*handle_count_ptr) >= (*handle_max_count)))
        break;
    }
    //allocate handle from list. Find first free entry.
    for (index =0; index < (*handle_max_count) ; index++)
    {
      if ((*xcfg_handle_ptr)[index].is_valid == FALSE)
      {
        (*xcfg_handle_ptr)[index].is_valid = TRUE;
        break;
      }
    }
    if (index < (*handle_max_count))
    {
      *free_handle_index = index;
      status = XBLCONFIG_SUCCESS;
    }
    else
    {
      status = XBLCONFIG_HANDLE_ERR;
    }

  } while (0);
  return status;
}

/*===========================================================================
**  Function :  xblconfig_init
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes xblconfig module
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xblconfig_init(boot_handle config_context_handle, xblconfig_init_mode_type xblconfig_init_mode)
{
  xblconfig_status_type status = XBLCONFIG_INIT_ERR;
  /* XBLConfig header structure */
  xcfg_metadata_header_type *xcfg_header;

  do
  {
    if (xbl_config_data != NULL)
    {
      status = XBLCONFIG_SUCCESS;
      break;
    }

    if (xblconfig_init_mode == XBLCONFIG_INIT_FROM_FLASH)
    {

      /* Point xbl config image interface to xcfg loader function table */
      xcfg_image_interface = &xcfg_loader_image_interface;

    }
    else if (xblconfig_init_mode == XBLCONFIG_INIT_FROM_RAM_ADDRESS)
    {

      /* Point xbl config image interface to xcfg ram function table */
      xcfg_image_interface = &xcfg_ram_addr_image_interface;

    }

    status = xcfg_malloc(sizeof(xbl_config_type), (void **)&xbl_config_data);
    if ( (status != XBLCONFIG_SUCCESS) || (xbl_config_data == NULL) )
    {
      break;
    }

    xbl_config_data->xcfg_metadata_buff = NULL;
    xbl_config_data->xcfg_metadata_start_offset = 0;

    xbl_config_data->config_entry_list = NULL;
    xbl_config_data->max_config_entries = 0;

    xbl_config_data->xcfg_handle_list = NULL;
    xbl_config_data->xcfg_handle_max_count = 0;
    xbl_config_data->xcfg_handle_count = 0;
    xbl_config_data->dtbo_initialized = 0;
    xbl_config_data->cfg_sort_table = NULL;


    /*Initialize module for validating buffers to which data can be loaded
      from storage, example those from heap
    */
    status = xcfg_load_addr_validation_init(config_context_handle);
    if (status != XBLCONFIG_SUCCESS)
      break;

    //Load and authenticate xbl config hash table and get meta data blob
    status = xcfg_load_meta_data(config_context_handle);
    if (status != XBLCONFIG_SUCCESS)
    {
      break;
    }

    //Validate meta data header
    xcfg_header = (xcfg_metadata_header_type *)xbl_config_data->xcfg_metadata_buff;
    if (xcfg_header == NULL)
      break;

    if (xcfg_header->major_version != XBL_CONFIG_MAJOR_VERSION &&
        xcfg_header->minor_version != XBL_CONFIG_MINOR_VERSION)
    {
      // unsupported meta data format.
      break;
    }

    xbl_config_data->max_config_entries = xcfg_header->number_of_entries;

    // Parse the meta data to index the entries.
    status = xcfg_malloc((xbl_config_data->max_config_entries * sizeof(xcfg_parsed_metadata_table_entry_type)),
                         (void **)&xbl_config_data->config_entry_list);
    if (status != XBLCONFIG_SUCCESS)
    {
      break;
    }
    memset((void *)xbl_config_data->config_entry_list, 0, xbl_config_data->max_config_entries * sizeof(xcfg_parsed_metadata_table_entry_type));
    status = xcfg_populate_config_item_list(xbl_config_data->config_entry_list, xcfg_header);
    if (status != XBLCONFIG_SUCCESS)
      break;

    //Initialize list for open handles
    status = xcfg_handle_init(&xbl_config_data->xcfg_handle_list, &xbl_config_data->xcfg_handle_max_count,
                              &xbl_config_data->xcfg_handle_count);
    if (status != XBLCONFIG_SUCCESS)
      break;

    status = xcfg_load_addr_validation_deinit();

  } while (0);

  /* Free malloced memory in case of error */
  if (status != XBLCONFIG_SUCCESS && xbl_config_data->config_entry_list != NULL)
  {
    xcfg_free((void**)&xbl_config_data->config_entry_list);
  }

  return status;
} /* xblconfig_init */


/*===========================================================================
**  Function :  xblconfig_open
** ==========================================================================
*/
/*!
*
* @brief
*   This function parses xbl config meta data to locate config item and
*   returns a config handle if found, along with its size
*
* @param[in]    config_name       Null terminated config item name string
*
* @param[out]   config_handle     Config item handle, if found
*               config_item_size  Total size of config item
*
* @par Dependencies
*   XBLConfig module should have been initialized via xblconfig_init
*   before calling xblconfig_open
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xblconfig_open
(
  const char *config_name,
  uint32 *config_handle,
  uint32 *config_item_size
)
{
  xcfg_metadata_table_entries_type *item_entry_ptr;
  xblconfig_status_type status = XBLCONFIG_OPEN_ERR;
  uintnt index;

  do
  {
    if ( config_name == NULL || config_handle == NULL ||
         config_item_size == NULL )
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    if (xbl_config_data == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }

    //Parse config table entries to locate item.
    for (index = 0; index < xbl_config_data->max_config_entries; index++)
    {
      item_entry_ptr = xbl_config_data->config_entry_list[index].entry_ptr;
      if (strncmp(config_name, &item_entry_ptr->config_name_start, item_entry_ptr->config_name_len) == 0)
      {
        //Config entry is found. Allocate handle
        status =  xcfg_handle_allocate(&xbl_config_data->xcfg_handle_list, &xbl_config_data->xcfg_handle_max_count,
                                       &xbl_config_data->xcfg_handle_count, config_handle);
        if (status != XBLCONFIG_SUCCESS)
          break;

        //Update handle with config data info
        xbl_config_data->xcfg_handle_list[(*config_handle)].config_entry_index = index;
        *config_item_size = item_entry_ptr->size;
        xbl_config_data->xcfg_handle_count++;
        break;
      }
    }
    if (index == xbl_config_data->max_config_entries)
    {
      status = XBLCONFIG_OPEN_ERR;
    }
  } while (0);

  return status;
}/* xblconfig_open */

/*===========================================================================
**  Function :  xblconfig_create_chipinfo
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the chipinfo value as used by xblconfig_open_by_hwinfo
*   Per XBLConfig v2.0 spec, chipinfo parameter (uint64) is created thusly...
*     [63..48] Chip_Family
*     [47..32] Chip_ID
*     [31..24] Major_Version
*     [23..16] Minor_Version
*     [15..0]  Reserved
*
* @param[in]         cFamily                  16-bit Chip_Family
*                    cId                      16-bit Chip_ID
*                    cVersion                 16-bit Major_Minor_Version
*
* @param[out]        chipinfo                 64-bit chip code
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xblconfig_create_chipinfo
(
  uint16   cFamily,
  uint16   cID,
  uint16   cVersion,
  uint64  *chipinfo
)
{
  uint64 hWord;
  uint32 lWord;

  if (NULL == chipinfo)
    return XBLCONFIG_NULL_PTR_ERR;

  hWord = (cFamily<<16)  | cID;
  lWord = (cVersion<<16) & ChipVersionMask;

  *chipinfo = (hWord<<32)|lWord;

  return XBLCONFIG_SUCCESS;
}

/*===========================================================================
**  Function :  xblconfig_create_platforminfo
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the platforminfo value as used by xblconfig_open_by_hwinfo
*   Per XBLConfig v2.0 spec, platforminfo parameter (uint64) is created thusly...
*     [63..56] Platform_Type
*     [55..48] Platform_SubType
*     [47..40] Major_Version
*     [39..32] Minor_Version
*     [31..0]  Reserved
*
* @param[in]         pType                        8-bit platform Type
*                    pVersion                     16-bit Platform Version
*                    pSubtype                     8-bit Platform SubType
*                    pOemVariant                  8-bit OEM Variant Id
* @param[out]        platforminfo                 64-bit platform code
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xblconfig_create_platforminfo
(
  uint8    pType,
  uint16   pVersion,
  uint8    pSubtype,
  uint8    pOemVariant,
  uint64  *platforminfo
)
{
  uint64 hWord;
  uint32 lWord = 0;

  if (NULL == platforminfo)
    return XBLCONFIG_NULL_PTR_ERR;

  hWord = ((pType<<24) & PlatformTypeMask) |
          ((pSubtype<<16) & PlatformSubTypeMask) |
          (pVersion & PlatformVersionMask);

  lWord = (pOemVariant<<24);

  *platforminfo = (hWord<<32)|lWord;

  return XBLCONFIG_SUCCESS;
}

/*===========================================================================
**  Function :  config_match_chipinfo
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the comparative result of chipinfo base on the best
*   match algorithm
*
* @param[in]         prequested_chipinfo          address of device's chipinfo
*                    pentry_chipinfo              address of current entry chipinfo
*
*
* @par Dependencies
*   None
*
* @retval
*      boolean       TRUE                         chipinfo match successfully
*                    FALSE                        chipinfo match failure
*
* @par Side Effects
*   None
*
*/

static boolean config_match_chipinfo
(
  uint64 *prequested_chipinfo,
  uint64 *pentry_chipinfo)
{
  chipinfo_hierarchy_type *requested_chipinfo_ptr = (chipinfo_hierarchy_type *)prequested_chipinfo;
  chipinfo_hierarchy_type *entry_chipinfo_ptr = (chipinfo_hierarchy_type *)pentry_chipinfo;
  if ( pentry_chipinfo == NULL || (uint64)*pentry_chipinfo == 0xFFFFFFFFFFFFFFFF)
    goto next_entry;

  if (requested_chipinfo_ptr->ChipFamily == entry_chipinfo_ptr->ChipFamily)
  {
    if (requested_chipinfo_ptr->ChipId == entry_chipinfo_ptr->ChipId ||
        entry_chipinfo_ptr->ChipId == 0)
    {
      if (requested_chipinfo_ptr->Major_version == entry_chipinfo_ptr->Major_version)
      {
        if (requested_chipinfo_ptr->Minor_version >= entry_chipinfo_ptr->Minor_version)
          goto check_platforminfo;
        else
          goto next_entry;
      }
      else
      {
        if (requested_chipinfo_ptr->Major_version > entry_chipinfo_ptr->Major_version)
          goto check_platforminfo;
        else
          goto next_entry;
      }
    }
  }
next_entry:
  return FALSE;
check_platforminfo:
  return TRUE;
}

/*===========================================================================
**  Function :  config_match_platforminfo
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the comparative result of platforminfo base on the best
*   match algorithm
*
* @param[in]         prequested_platforminfo          address of device's platforminfo
*                    pentry_platforminfo              address of current entry platforminfo
*
*
* @par Dependencies
*   None
*
* @retval
*      boolean       TRUE                         platforminfo match successfully
*                    FALSE                        platforminfo match failure
*
* @par Side Effects
*   None
*
*/

static boolean config_match_platforminfo
(
  uint64 *prequested_platforminfo,
  uint64 *pentry_platforminfo)
{
  platfrominfo_hierarchy_type *requested_platforminfo_ptr = (platfrominfo_hierarchy_type *)prequested_platforminfo;
  platfrominfo_hierarchy_type *entry_platforminfo_ptr = (platfrominfo_hierarchy_type *)pentry_platforminfo;

  if (pentry_platforminfo == NULL || (uint64)*pentry_platforminfo == 0xFFFFFFFFFFFFFFFF)
    goto next_entry;

  if (requested_platforminfo_ptr->Platformtype == entry_platforminfo_ptr->Platformtype)
  {
    if (requested_platforminfo_ptr->PlatformSubtype == entry_platforminfo_ptr->PlatformSubtype ||
        entry_platforminfo_ptr->PlatformSubtype == 0)
    {
      if (requested_platforminfo_ptr->Major_version == entry_platforminfo_ptr->Major_version)
      {
        if (requested_platforminfo_ptr->Minor_version >= entry_platforminfo_ptr->Minor_version)
        {
          goto check_oem_flavor_id;
        }
        else
        {
          goto next_entry;
        }
      }
      else
      {
        if (requested_platforminfo_ptr->Major_version > entry_platforminfo_ptr->Major_version)
          goto check_oem_flavor_id;
        else
          goto next_entry;
     }
   }
   else
   {
     goto next_entry;
   }
 }
 else
 {
   if(entry_platforminfo_ptr->Platformtype == 0)
     goto check_oem_flavor_id;
   else
     goto next_entry;
 }

 check_oem_flavor_id:
  /*If oem flavor id is not exact match, fetch dtbo/dtb whose oem_flavor_id is 0 */
  if( requested_platforminfo_ptr->Oem_flavor_id == entry_platforminfo_ptr->Oem_flavor_id ||
      entry_platforminfo_ptr->Oem_flavor_id == 0)
    goto bingo;

next_entry:
  return FALSE;
bingo:
  return TRUE;
}
/*===========================================================================
 **  Function :  add_cfg_item_to_list
 ** ==========================================================================
 */
/*!
*
* @brief
*   This function insterts config item to sort list table
*
* @param[in]        plist_header             pointer of sort list table
*                   item_entry_ptr           pointer of config item entry
*                   index                    the config index in metadate table
*
* @param[out]
*
* @par Dependencies
*   config module should have been initialized via xblconfig_init
*   before calling xblconfig_open
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type add_cfg_item_to_list(cfg_item_list_type **plist_header, xcfg_metadata_table_entries_type *item_entry_ptr, uintnt index)
{
  xblconfig_status_type status = XBLCONFIG_ADD_SORT_LIST_FAILED;
  cfg_item_list_type *p_curr_cfg_item = NULL, *p_cfg_item = NULL;
  do
  {
    status = xcfg_malloc(sizeof(cfg_item_list_type), (void **)&p_curr_cfg_item);
    if (status != XBLCONFIG_SUCCESS)
    {
      break;
    }
    p_curr_cfg_item->entry_ptr = item_entry_ptr;
    p_curr_cfg_item->index = index;
    p_curr_cfg_item->p_next_item = NULL;
    p_curr_cfg_item->p_prev_item = NULL;
    if (*plist_header == NULL)
    {
      *plist_header = p_curr_cfg_item;
      p_curr_cfg_item->p_prev_item = NULL;
      status = XBLCONFIG_SUCCESS;
      break;
    }
    else
    {
      for (p_cfg_item = *plist_header; p_cfg_item!=NULL; p_cfg_item=p_cfg_item->p_next_item)
      {
        /*if chipinfo is greater than the currect chipinfo,  or chipinfo is equal current chipinfo
         * and platforminfo is greater than the current platforminfo, the item will come first   */
        if ((p_curr_cfg_item->entry_ptr->chipinfo > p_cfg_item->entry_ptr->chipinfo)||
            ((p_curr_cfg_item->entry_ptr->chipinfo || p_cfg_item->entry_ptr->chipinfo)&&
             (p_curr_cfg_item->entry_ptr->platforminfo > p_cfg_item->entry_ptr->platforminfo)))
        {
          if (p_cfg_item == *plist_header)
          {
            /*if it is the first elment in link, update header point*/
            *plist_header = p_curr_cfg_item;
            p_curr_cfg_item->p_next_item = p_cfg_item;
            p_cfg_item->p_prev_item = p_curr_cfg_item;
          }
          else
          {
            p_cfg_item->p_prev_item->p_next_item = p_curr_cfg_item;
            p_curr_cfg_item->p_next_item = p_cfg_item;
          }
          status = XBLCONFIG_SUCCESS;
          break;
        }
        else
        {
          if (p_cfg_item->p_next_item == NULL)
          {
            p_cfg_item->p_next_item = p_curr_cfg_item;
            status = XBLCONFIG_SUCCESS;
            break;
          }
        }
      }
    }
  } while (FALSE);
  return status;

} /*===========================================================================
 **  Function :  create_cfg_sort_list
 ** ==========================================================================
 */
/*!
*
* @brief
*   This function parses xbl config meta data to locate config item and
*   Create three sorts list table for dtb, soc dtbo and platform dtbo.
*
* @param[in]
*
* @param[out]
*
* @par Dependencies
*   config module should have been initialized via xblconfig_init
*   before calling xblconfig_open
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type create_cfg_sort_list(void)
{
  xcfg_metadata_table_entries_type *item_entry_ptr;
  xblconfig_status_type status = XBLCONFIG_OPEN_ERR;
  chipinfo_hierarchy_type *entry_chipinfo_ptr = NULL;
  uintnt index;
  uint8 ext_max_length = 0;
  uint8 dtb_ext_length = strlen(dtb_ext);
  uint8 dtbo_ext_length = strlen(dtbo_ext);

  do
  {

    if (xbl_config_data == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }
    else if (xbl_config_data->dtbo_initialized)
      return XBLCONFIG_SUCCESS;

    if (xbl_config_data->cfg_sort_table == NULL)
    {
      status = xcfg_malloc(sizeof(cfg_sort_list_type), (void **)&xbl_config_data->cfg_sort_table);
      if (status != XBLCONFIG_SUCCESS)
      {
        break;
      }
      xbl_config_data->cfg_sort_table->p_dtb_list = NULL;
      xbl_config_data->cfg_sort_table->p_soc_dtbo_list = NULL;
      xbl_config_data->cfg_sort_table->p_platform_dtbo_list = NULL;
    }
    ext_max_length = dtb_ext_length > dtbo_ext_length?dtb_ext_length:dtbo_ext_length;
    //Parse config table entries to locate item.
    for (index = 0; index < xbl_config_data->max_config_entries; index++)
    {
      item_entry_ptr = xbl_config_data->config_entry_list[index].entry_ptr;

      if (&item_entry_ptr->config_name_start != NULL && item_entry_ptr->config_name_len > ext_max_length)
      {

        if (strncmp(((char *)&item_entry_ptr->config_name_start+(item_entry_ptr->config_name_len-dtb_ext_length)), dtb_ext, dtb_ext_length)==0 && item_entry_ptr->platforminfo==0)
        {
          status = add_cfg_item_to_list(&xbl_config_data->cfg_sort_table->p_dtb_list, item_entry_ptr, index);
        }
        else
        {
          /* sort dtbo table*/
          if (strncmp(((char *)&item_entry_ptr->config_name_start+(item_entry_ptr->config_name_len-dtbo_ext_length)), dtbo_ext, dtbo_ext_length)==0 )
          {
            entry_chipinfo_ptr = (chipinfo_hierarchy_type *)&item_entry_ptr->chipinfo;
            /*if platforminfo is 0x0 and chip version is not 0x0, it is soc dtbo*/
            if (item_entry_ptr->platforminfo==0x0 && (entry_chipinfo_ptr->Major_version<<8|entry_chipinfo_ptr->Minor_version) != 0x0)
              status = add_cfg_item_to_list(&xbl_config_data->cfg_sort_table->p_soc_dtbo_list, item_entry_ptr, index);
            else
              status = add_cfg_item_to_list(&xbl_config_data->cfg_sort_table->p_platform_dtbo_list, item_entry_ptr, index);

          }
        }
        if (status != XBLCONFIG_SUCCESS)
          break;

      }
    }
  } while (FALSE);
  if (status == XBLCONFIG_SUCCESS)
    xbl_config_data->dtbo_initialized = 1;
  return status;
}

/*===========================================================================
**  Function :  cfg_item_config_open_first_dtb
** ==========================================================================
*/
/*!
*
* @brief
*   This function parses xbl config meta data to locate config item and
*   returns a config handle if found, along with its size
*
* @param[in]        chipinfo                 64-bit chip code
*                   platforminfo             64-bit platform code
*                   config_name_starts_with  Null terminated config item [partial] name string
*
* @param[out]   config_handle     Config item handle, if found
*               config_item_size  Total size of config item
*
* @par Dependencies
*   config module should have been initialized via xblconfig_init
*   before calling xblconfig_open
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/

xblconfig_status_type cfg_item_config_open_first_dtb
(
  uint64  chipinfo,
  uint64  platforminfo,
  const char *config_name_starts_with,
  uint32 *config_handle,
  uint32 *config_item_size
)
{
  xcfg_metadata_table_entries_type *item_entry_ptr;
  xblconfig_status_type status = XBLCONFIG_OPEN_ERR;
  uintnt index;
  cfg_item_list_type *p_dtb_node;
  do
  {
    if ( config_handle == NULL || config_item_size == NULL )
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    if (xbl_config_data == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }
    status = create_cfg_sort_list();
    if (status != XBLCONFIG_SUCCESS)
      break;
    //Parse config table entries to locate item.
    for (p_dtb_node = xbl_config_data->cfg_sort_table->p_dtb_list; p_dtb_node!=NULL; p_dtb_node=p_dtb_node->p_next_item)
    {
      item_entry_ptr = p_dtb_node->entry_ptr;

      if (config_match_chipinfo(&chipinfo, (void *)&item_entry_ptr->chipinfo)!= TRUE)
      {
        continue;
      }

      if (config_name_starts_with != NULL)
      {
        if (strncmp(config_name_starts_with, (char *)&item_entry_ptr->config_name_start, strlen(config_name_starts_with)) != 0)
          continue;
      }

      index = p_dtb_node->index;
      break; /*bingo the chipfamily dtb has been found*/
    }
    if (p_dtb_node == NULL)
    {
      status = XBLCONFIG_ITEM_NOT_FOUND;
      break;
    }
    else
    {

      //Config entry is found. Allocate handle
      status =  xcfg_handle_allocate(&xbl_config_data->xcfg_handle_list, &xbl_config_data->xcfg_handle_max_count,
                                     &xbl_config_data->xcfg_handle_count, config_handle);
      if (status != XBLCONFIG_SUCCESS)
        break;

      //Update handle with config data info
      xbl_config_data->xcfg_handle_list[(*config_handle)].config_entry_index = index;
      *config_item_size = item_entry_ptr->size;
      xbl_config_data->xcfg_handle_count++;
    }
  } while (0);

  return status;
}/* cfg_itme_config_open_first_dtb */

/*===========================================================================
**  Function :  cfg_item_config_open_next_dtbo
** ==========================================================================
*/
/*!
*
* @brief
*   This function parses config items to get best match DTBO binary
* @param[in]        chipinfo                 64-bit chip code
*                   platforminfo             64-bit platform code
*                   config_name_starts_with  Null terminated config item [partial] name string
*                   state                    which DTBO to get.
*
* @param[out]   config_handle     Config item handle, if found
*               config_item_size  Total size of config item
*               state             current match states.
*
* @par Dependencies
*   XBLConfig module should have been initialized via xblconfig_init
*   before calling xblconfig_open
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type cfg_item_config_open_next_dtbo
(
  uint64  chipinfo,
  uint64  platforminfo,
  const char *config_name_starts_with,
  uint32 *config_handle,
  uint32 *config_item_size,
  cfg_dtbo_state_type *state
)
{
  xcfg_metadata_table_entries_type *item_entry_ptr;
  xblconfig_status_type status = XBLCONFIG_SUCCESS;
  uintnt index;
  cfg_item_list_type *p_dtbo_node, *p_dtbo_list;
  uint64 cplatforminfo;

  /*Check input parameters*/
  do
  {
    if ( config_handle == NULL || config_item_size == NULL || state == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    if (xbl_config_data == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }
    if (*state > CFG_GET_MAX_DTBO)
    {
      status = XBLCONFIG_INVALID_DTBO_STATE;
      break;
    }
  } while (0);

  if (status != XBLCONFIG_SUCCESS)
    return status;


  do
  {
    if ( *state == CFG_GET_MAX_DTBO)
    {
      status = XBLCONFIG_DTBO_NOTFOUND;
      break;
    }

    /*If it is SOC dtbo, go to search in soc dtbo list, otherwise goto search in platform list */
    if (*state==CFG_GET_SOC_DTBO)
    {
      p_dtbo_list = xbl_config_data->cfg_sort_table->p_soc_dtbo_list;
      cplatforminfo = 0;
    }
    else
    {
      p_dtbo_list = xbl_config_data->cfg_sort_table->p_platform_dtbo_list;
      cplatforminfo = platforminfo;
    }

    //Parse config table entries to locate item.
    for (p_dtbo_node = p_dtbo_list; p_dtbo_node!=NULL; p_dtbo_node=p_dtbo_node->p_next_item)
    {
      item_entry_ptr = p_dtbo_node->entry_ptr;

      if (config_match_chipinfo(&chipinfo, (void *)&item_entry_ptr->chipinfo)!= TRUE)
        continue;

      if (config_match_platforminfo(&cplatforminfo, (void *)&item_entry_ptr->platforminfo) != TRUE)
        continue;

      /* if config name provide and it is not the second match in first enter, do config name matching.*/
      if (config_name_starts_with != NULL)
      {
        if (strncmp(config_name_starts_with, (char *)&item_entry_ptr->config_name_start, strlen(config_name_starts_with)) != 0)
          continue;
      }

      index = p_dtbo_node->index;
      break; /*bingo the dtbo has been found*/

    }

    if (p_dtbo_node == NULL)
    {
      /*if DTBO was not found in currect list , bump state and continue to search next dtbo list */
      *state=*state+1;
      continue;
    }
    else
    {
      /*DTBO is found. Allocate handle*/
      status =  xcfg_handle_allocate(&xbl_config_data->xcfg_handle_list, &xbl_config_data->xcfg_handle_max_count,
                                     &xbl_config_data->xcfg_handle_count, config_handle);
      if (status != XBLCONFIG_SUCCESS)
        break;
      /*Update handle with config data info*/
      xbl_config_data->xcfg_handle_list[(*config_handle)].config_entry_index = index;
      *config_item_size = item_entry_ptr->size;
      xbl_config_data->xcfg_handle_count++;
      /*Bump the state and return to client side*/
      *state=*state+1;
      break;
    }

  } while (1);

  return status;
}/* cfg_item_config_open_next_dtbo */


/*===========================================================================
**  Function :  xblconfig_open_by_hwinfo
** ==========================================================================
*/
/*!
*
* @brief
*   This function parses xbl config meta data to locate config item and
*   returns a config handle if found, along with its size
*
* @param[in]        chipinfo                 64-bit chip code
*                   platforminfo             64-bit platform code
*                   config_name_starts_with  Null terminated config item [partial] name string
*
* @param[out]   config_handle     Config item handle, if found
*               config_item_size  Total size of config item
*
* @par Dependencies
*   XBLConfig module should have been initialized via xblconfig_init
*   before calling xblconfig_open
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xblconfig_open_by_hwinfo
(
  uint64  chipinfo,
  uint64  platforminfo,
  const char *config_name_starts_with,
  uint32 *config_handle,
  uint32 *config_item_size
)
{
  xcfg_metadata_table_entries_type *item_entry_ptr;
  xblconfig_status_type status = XBLCONFIG_OPEN_ERR;
  uintnt index;

  do
  {
    if ( config_handle == NULL || config_item_size == NULL )
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    if (xbl_config_data == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }

    //Parse config table entries to locate item.
    for (index = 0; index < xbl_config_data->max_config_entries; index++)
    {
      item_entry_ptr = xbl_config_data->config_entry_list[index].entry_ptr;
      // if config name provided, just compare config name. otherwise it will go through best match algorithm.
      if ( (config_name_starts_with != NULL) && (config_name_starts_with[0] != '\0') )
      {
        if (strncmp(config_name_starts_with, (char *)&item_entry_ptr->config_name_start, strlen(config_name_starts_with)) == 0)
        {
          break;
        }
      }
      else
      {
        if (config_match_chipinfo(&chipinfo, (void *)&item_entry_ptr->chipinfo)!= TRUE)
          continue;
        if (config_match_platforminfo(&platforminfo, (void *)&item_entry_ptr->platforminfo) != TRUE)
          continue;
        break;
      }
    }
    if (index == xbl_config_data->max_config_entries)
    {
      status = XBLCONFIG_ITEM_NOT_FOUND;
      break;
    }
    else
    {

      //Config entry is found. Allocate handle
      status =  xcfg_handle_allocate(&xbl_config_data->xcfg_handle_list, &xbl_config_data->xcfg_handle_max_count,
                                     &xbl_config_data->xcfg_handle_count, config_handle);
      if (status != XBLCONFIG_SUCCESS)
        break;

      //Update handle with config data info
      xbl_config_data->xcfg_handle_list[(*config_handle)].config_entry_index = index;
      *config_item_size = item_entry_ptr->size;
      xbl_config_data->xcfg_handle_count++;
    }
  } while (0);

  return status;
}/* xblconfig_open_by_hwinfo */

/*===========================================================================
**  Function :  xblconfig_read
** ==========================================================================
*/
/*!
*
* @brief
*   This function copies config item data equal to input "size" from read offset
*   into provided buffer
*
* @param[in]    config_handle   Handle to identify config item to be read
*               read_offset     Offset within config item to start read
*               size            Size of data to be read
*
* @param[out]   buffer          Data buffer provided by callee for reading data
*
* @par Dependencies
*   NOTE:   The user of xblconfig_read api has to allocate memory and
*           point it via buffer for loading data.
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xblconfig_read
(
  const uint32 config_handle,
  uint32 read_offset,
  uint32 size,
  void *buffer
)
{
  xblconfig_status_type status = XBLCONFIG_READ_ERR;
  xcfg_metadata_table_entries_type *item_entry_ptr;
  uintnt parsed_entry_index = 0, total_offset = 0;
  uint32 config_item_start = 0, test_size = 0;
  do
  {
    if (xbl_config_data == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }

    if (buffer == NULL)
    {
      status = XBLCONFIG_NULL_PTR_ERR;
      break;
    }
    if (size == 0)
    {
      status = XBLCONFIG_INVALID_SIZE;
      break;
    }
    if ((config_handle >= xbl_config_data->xcfg_handle_max_count) ||
        xbl_config_data->xcfg_handle_list[config_handle].is_valid == FALSE)
    {
      break;
    }

    /* check for overflow */
    test_size = read_offset + size;
    if (test_size < size)
    {
      status = XBLCONFIG_OVERFLOW_ERR;
      break;
    }

    /*Initialize module for validating buffers to which data can be loaded
      from storage example those from heap
    */
    status = xcfg_load_addr_validation_init(xbl_config_data->config_context_handle);
    if (status != XBLCONFIG_SUCCESS)
      break;

    parsed_entry_index = xbl_config_data->xcfg_handle_list[config_handle].config_entry_index;
    item_entry_ptr = xbl_config_data->config_entry_list[parsed_entry_index].entry_ptr;
    config_item_start = item_entry_ptr->offset_from_meta_start;

    /* ensure data to be read is within bounds. read offset + requested size
       will not exceed max config item size
    */
    if (read_offset > item_entry_ptr->size ||
        (read_offset + size) > item_entry_ptr->size)
    {
      status = XBLCONFIG_INVALID_SIZE;
      break;
    }

    total_offset =  xbl_config_data->xcfg_metadata_start_offset + config_item_start + read_offset;
    if (total_offset < xbl_config_data->xcfg_metadata_start_offset)
    {
      status = XBLCONFIG_OVERFLOW_ERR;
      break;
    }

    status = xcfg_image_interface->get_block_data(total_offset, (uintnt)size, buffer, TRUE);

    if (status != XBLCONFIG_SUCCESS)
      break;

    status = xcfg_load_addr_validation_deinit();

  } while (0);

  return status;
}/* xblconfig_read */

/*===========================================================================
**  Function :  xblconfig_close
** ==========================================================================
*/
/*!
*
* @brief
*   This function free's config handle to be closed(sets to 0)
*
* @param[in]  config_handle   Handle to be closed
*   None
*
* @par Dependencies
*   NOTE:   The user of xblconfig_close api has to free memory
*           used for reads associated with the handle to be closed.
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xblconfig_close (uint32 config_handle)
{
  xblconfig_status_type status = XBLCONFIG_CLOSE_ERR;

  do
  {
    if (xbl_config_data == NULL)
    {
      status = XBLCONFIG_UNINITIALIZED;
      break;
    }

    if ((config_handle >= xbl_config_data->xcfg_handle_max_count) ||
        xbl_config_data->xcfg_handle_count == 0)
    {
      break;
    }

    if (xbl_config_data->xcfg_handle_list[config_handle].is_valid != FALSE)
    {
      /*Ensure handle is not already freed to avoid handle count
        underrun across multiple api invocations for same handle
      */
      xbl_config_data->xcfg_handle_list[config_handle].config_entry_index = 0;
      xbl_config_data->xcfg_handle_list[config_handle].is_valid = FALSE;
      xbl_config_data->xcfg_handle_count--;
      status = XBLCONFIG_SUCCESS;
    }
  } while (0);

  return status;
} /* xblconfig_close */

/*===========================================================================
**  Function :  xblconfig_deinit
** ==========================================================================
*/
/*!
*
* @brief
*   This function deinitializes xblconfig module. Free's all internal allocated
*   buffers
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xblconfig_deinit(void)
{
  xblconfig_status_type status = XBLCONFIG_DEINIT_ERR;

  do
  {

    /* Free all allocated buffers */
    status = xcfg_free((void**)&xbl_config_data->xcfg_metadata_buff);
    if (status != XBLCONFIG_SUCCESS)
      break;

    status = xcfg_free((void**)&xbl_config_data->config_entry_list);
    if (status != XBLCONFIG_SUCCESS)
      break;

    status = xcfg_free((void**)&xbl_config_data->xcfg_handle_list);
    if (status != XBLCONFIG_SUCCESS)
      break;

    status = xcfg_free((void**)&xbl_config_data->cfg_sort_table);
    if (status != XBLCONFIG_SUCCESS)
      break;

    status = xcfg_image_interface->deinit();
    if (status != XBLCONFIG_SUCCESS)
      break;

    /* reset config item handle counts*/
    xbl_config_data->xcfg_handle_max_count = 0;
    xbl_config_data->xcfg_handle_count = 0;

    xbl_config_data->max_config_entries = 0;

    status = xcfg_free((void**)&xbl_config_data);
    if (status != XBLCONFIG_SUCCESS)
      break;

    status = XBLCONFIG_SUCCESS;

  } while (FALSE);

  return status;
} /* xblconfig_deinit */

