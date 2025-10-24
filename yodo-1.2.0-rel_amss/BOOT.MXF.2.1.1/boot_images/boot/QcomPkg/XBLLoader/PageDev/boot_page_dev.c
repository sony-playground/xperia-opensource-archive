/*=============================================================================

                     Boot Page Device

GENERAL DESCRIPTION
  This file contains the implementation for boot layer that provides the APIs
  for reading and writing to page based flash devices.

Copyright 2020-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
11/19/21   ck           Added bad block support
10/11/21   ck           Added cache invalidation to boot_page_dev_read
07/01/21   ds           media ioctl changes
05/24/21   rama         changes to make boot_page_dev_hw_init and deinit recallable
01/15/21   ck           Added erase logic to boot_page_dev_write
07/14/20   ck           Added nand driver single block limitation logic
07/07/20   ck           Added bam init/deinit
03/24/20   ck           Initial revision.
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <string.h>
#include "boot_page_dev.h"
#include "boot_nand_if.h"
#include "boot_memory_mgr_if.h"
#include "boot_config_context.h"
#include "boot_statistics_if.h"
#include "boot_bam_if.h"
#include "boot_edk2_cache_if.h"


/*=============================================================================
LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.
=============================================================================*/
/* Page device handle ID */
#define PDEV 0x50444556


typedef uint32 block_translation_table_entry;
#define PAGEDEV_BLOCK_INACCESSIBLE -1


// Block device handle
typedef struct boot_page_dev_obj
{
  uint32 id;
  uint8 * partition_id;
  boot_memory_mgr_if_type * mem_if;
  boot_statistics_if_type * boot_stats_if;
  block_translation_table_entry * block_translation_table;
  boot_nand_if_type * nand_if;
  nand_handle_t nand_handle;
  struct nand_info nand_info;
}page_device_handle;

static boot_boolean boot_page_dev_is_hw_initialized = FALSE;

/*=========================================================================
**  Function :  _init
** ==========================================================================
*/
/*!
* 
* @brief
*   intialize the page dev handle.
* 
* @param[in] pointer to page dev handle
* 
*/
static void _init(page_device_handle * page_dev_handle)
{
  /* Clear page device handle */
  memset((void *)page_dev_handle,
          0,
          sizeof(page_device_handle));

  
  /* Populate id */
  page_dev_handle->id = PDEV;
}


/*=========================================================================
**  Function :  _handle_check
** ==========================================================================
*/
/*!
* 
* @brief
*   Sanitize the page device handle.
* 
* @param[in] page device handle
* 
*/
static bl_error_boot_type _handle_check(page_device_handle * page_dev_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;


  /* Verify page device handle pointer */
  if (page_dev_handle == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Verify id */
  if (page_dev_handle->id != PDEV)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INVALID_HANDLE);
    goto exit;
  }


  /* Verify handle parameters */
  if ((page_dev_handle->partition_id == NULL) ||
      (page_dev_handle->mem_if == NULL) ||
      (page_dev_handle->boot_stats_if == NULL) ||
      (page_dev_handle->nand_if == NULL) ||
      (page_dev_handle->nand_handle == NULL) ||
      (page_dev_handle->block_translation_table == NULL))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }

    
 exit:
  return error;
}


/*=========================================================================
**  Function :  _generate_block_translation_table
** ==========================================================================
*/
/*!
* 
* @brief
*   Generates a table that converts a logical block number to a physical block number.
*   Bad blocks are skipped during image writing which causes data to become skewed
*   across the physical storage.  This table provides the map between where the data block
*   should be to where it actually is.  Table size is equal to the number of blocks in the
*   currently open partition. 
* 
* @param[in] pointer to config context handle
*
*/
static bl_error_boot_type _generate_block_translation_table(page_device_handle * page_dev_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  NAND_STATUS nand_status = NAND_DEVICE_DONE;
  enum nand_block_state current_block_state = NAND_BLOCK_STATE_UNKNOWN;
  block_translation_table_entry * current_table_entry = NULL;
  uint32 current_block_number = 0;
  uint32 bad_block_count = 0;


  /* Validate pointers */
  if ((page_dev_handle == NULL) ||
      (page_dev_handle->mem_if == NULL))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Malloc memory for the table */
  error = page_dev_handle->mem_if->malloc(page_dev_handle->nand_info.block_count * sizeof(block_translation_table_entry),
                                          (void **)&(page_dev_handle->block_translation_table));
  if (error != BL_ERR_NONE)
  {
    goto exit;
  }
  
  if (page_dev_handle->block_translation_table == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_MEMORY_ALLOC_FAIL);
    goto exit;
  }


  /* Populate the table where index is logical block and data is physical block */
  current_table_entry = page_dev_handle->block_translation_table;
  current_block_number = 0;
  while (current_block_number < page_dev_handle->nand_info.block_count)
  {
    /* If the bad block count plus current block number are greater than blocks in
       partition then it is not possible to access this logical block.  Mark as inaccessible
       and move to next block. */
    if ((bad_block_count + current_block_number) >= page_dev_handle->nand_info.block_count)
    {
      *current_table_entry = PAGEDEV_BLOCK_INACCESSIBLE;
      current_block_number++;
      continue;
    }


    /* Check current block state */
    current_block_state = NAND_BLOCK_STATE_UNKNOWN;
    nand_status = page_dev_handle->nand_if->nand_block_get_state(page_dev_handle->nand_handle,
                                                                 (current_block_number + bad_block_count),
                                                                 &current_block_state);
    if (nand_status != NAND_DEVICE_DONE)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
      goto free_and_exit;
    }


    /* If block is bad then increment bad block count and reenter loop with
       same current block number. */
    if (current_block_state != NAND_BLOCK_OK)
    {
      bad_block_count++;
      continue;
    }


    /* Good block was found.  Assign to logical entry and advance values. */
    *current_table_entry = current_block_number + bad_block_count;
    current_table_entry++;
    current_block_number++;
  }


 free_and_exit:
  /* If error is not BL_ERR_NONE then free memory. */
  if (error != BL_ERR_NONE)
  {
    page_dev_handle->mem_if->free(page_dev_handle->block_translation_table);
  }


 exit:
  return error;
}


/*=========================================================================
**  Function :  _translate_logical_to_physical_block
** ==========================================================================
*/
/*!
* 
* @brief
*   Given a logical block number this function dereferences the block translation
*   table and provides the physical block number where the data was really stored at.
*   Data skew across the physical device happens as bad blocks are avoided.
* 
* @param[in] pointer to config context handle
*
*/
static bl_error_boot_type _translate_logical_to_physical_block(page_device_handle * page_dev_handle,
                                                               uint32 logical_block,
                                                               uint32 * physical_block)
{
  bl_error_boot_type error = BL_ERR_NONE;
  block_translation_table_entry * table_entry = NULL;
 
  
  /* Validate pointers */
  if ((page_dev_handle == NULL) ||
      (page_dev_handle->block_translation_table == NULL) ||
      (physical_block == NULL))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Verify logical block supplied is valid */
  if (logical_block >= page_dev_handle->nand_info.block_count)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }


  /* Set table entry pointer to logical block entry */
  table_entry = page_dev_handle->block_translation_table;
  table_entry += logical_block;


  /* Verify physical block is reachable */
  if (*table_entry == PAGEDEV_BLOCK_INACCESSIBLE)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_RESOURCE_NOT_AVAILABLE);
    goto exit;
  }


  /* Assign physical block value */
  *physical_block = *table_entry;
  
  
 exit:
  return error;
}


/*=========================================================================
**  Function :  _translate_logical_to_physical_page
** ==========================================================================
*/
/*!
* 
* @brief
*   Given a logical page number this function dereferences the block translation
*   table and provides the physical page number where the data was really stored at.
*   Data skew across the physical device happens as bad blocks are avoided.
* 
* @param[in] pointer to config context handle
*
*/
static bl_error_boot_type _translate_logical_to_physical_page(page_device_handle * page_dev_handle,
                                                              uint32 logical_page,
                                                              uint32 * physical_page)
{
  bl_error_boot_type error = BL_ERR_NONE;
  uint32 logical_block = 0;
  uint32 physical_block = 0;

  
  /* Validate pointers */
  if ((page_dev_handle == NULL) ||
      (page_dev_handle->block_translation_table == NULL) ||
      (physical_page == NULL))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Calcuate logical block from logical page */
  logical_block = logical_page / page_dev_handle->nand_info.pages_per_block;


  /* Translate logical block to physical block */
  error = _translate_logical_to_physical_block(page_dev_handle,
                                               logical_block,
                                               &physical_block);
  if (error != BL_ERR_NONE)
  {
    goto exit;
  }


  /* Calculate and assign physical page value */
  *physical_page =
    (physical_block * page_dev_handle->nand_info.pages_per_block) +
    (logical_page % page_dev_handle->nand_info.pages_per_block);
  
  
 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_page_dev_open
** ==========================================================================
*/
/*!
* 
* @brief
*   Function to get coldplug handle and return the block dev handle
*   to client.
* 
* @param[in] pointer to config context handle, pointer to page dev handle pointer
*
* 
*/
static bl_error_boot_type boot_page_dev_open(const boot_handle config_context_handle,
                                             boot_handle * boot_handle_ptr)
{
  bl_error_boot_type error = BL_ERR_NONE;
  page_device_handle * page_dev_handle = NULL;
  boot_memory_mgr_if_type * mem_if = NULL;
  NAND_STATUS nand_status = NAND_DEVICE_DONE;
 
  
  /* Verify pointers */
  if((config_context_handle == NULL) ||
     (boot_handle_ptr == NULL))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }
  

  /* Get memory manager interface from config context */
  error = boot_config_context_get_ptr(config_context_handle,
                                      CONFIG_CONTEXT_MEMORY_MGR_INTERFACE,
                                      (void **)&mem_if);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }

  if(mem_if == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }


  /* Malloc memory to hold page device handle */
  error = mem_if->malloc(sizeof(page_device_handle),
                         (void *)&page_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }
  
  if(page_dev_handle == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_MEMORY_ALLOC_FAIL);
    goto exit;
  }

  
  /* Initalize the page device handle */
  _init(page_dev_handle);


  /* Store memory interface in page device handle */
  page_dev_handle->mem_if = mem_if;

  
  /* Get partition id/name from config context */  
  error = boot_config_context_get_ptr(config_context_handle,
                                      CONFIG_CONTEXT_PARTITION_ID,
                                      (void **)&page_dev_handle->partition_id);
  if(error != BL_ERR_NONE)
  {
    goto free_and_exit;
  }
  
  if(page_dev_handle->partition_id == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }


  /* Get boot statistics interface from config context */  
  error = boot_config_context_get_ptr(config_context_handle,
                                      CONFIG_CONTEXT_BOOT_STATS_INTERFACE,
                                      (void **)&page_dev_handle->boot_stats_if);
  if(error != BL_ERR_NONE)
  {
    goto free_and_exit;
  }


  /* Get nand driver interface */
  error = boot_config_context_get_ptr(config_context_handle,
                                      CONFIG_CONTEXT_NAND_INTERFACE,
                                      (void **)&page_dev_handle->nand_if);
  if(error != BL_ERR_NONE)
  {
    goto free_and_exit;
  }

  if(page_dev_handle->nand_if == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }


  /* Open nand partition */
  nand_status = page_dev_handle->nand_if->nand_open(NAND_DEVICE_ID_PARALLEL_FLASH,
                                                    page_dev_handle->partition_id,
                                                    &page_dev_handle->nand_handle);
  if (nand_status != NAND_DEVICE_DONE)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }
  

  /* Get nand partition information */
  nand_status = page_dev_handle->nand_if->nand_get_info(page_dev_handle->nand_handle,
                                                        &page_dev_handle->nand_info);
  if (nand_status != NAND_DEVICE_DONE)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }


  /* Create the block translation table which maps a logical block to
     physical block.  This is required to avoid bad blocks. */
  error = _generate_block_translation_table(page_dev_handle);
  if (error != BL_ERR_NONE)
  {
    goto free_and_exit;
  }
  
  
  /* Return pointer to new page device handle created */
  *boot_handle_ptr = (boot_handle)page_dev_handle;
  

 free_and_exit:
  /* If error is not BL_ERR_NONE then free memory. */
  if (error != BL_ERR_NONE)
  {
    mem_if->free(page_dev_handle);
  }


 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_page_dev_read
** ==========================================================================
*/
/*!
* 
* @brief
*   Read from page based flash device
* 
* @param[in] page dev handle, pointer to destination, source offset,
* number of bytes to read
* 
*/
static bl_error_boot_type boot_page_dev_read(const boot_handle media_handle,
                                             void * ram_addr,
                                             uint64 src_offset,
                                             uint32 bytes_to_read)
{
  bl_error_boot_type error = BL_ERR_NONE;
  page_device_handle * page_dev_handle = NULL;
  uint8 * current_destination = NULL;
  uint8 * temp_page_buffer = NULL;
  NAND_STATUS nand_status = NAND_DEVICE_DONE;
  uint32 current_logical_page_number = 0;
  uint32 current_physical_page_number = 0;
  uint32 available_first_page_bytes = 0;
  uint32 first_page_bytes = 0;
  uint32 whole_pages_remaining = 0;
  uint32 whole_pages_to_read = 0;
  uint32 remaining_pages_in_block = 0;
  uint32 remaining_bytes = 0;
  boot_edk2_cache_if_type * edk2_cache_if = NULL;


  /* Verify arguments passed */
  if ((media_handle == NULL) ||
      (ram_addr == NULL) ||
      (bytes_to_read == 0))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Assign validated pointers */
  page_dev_handle = (page_device_handle *)media_handle;
  current_destination = (uint8 *)ram_addr;

  
  /* Validate page device handle entries */
  error = _handle_check(page_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }


  /* Obtain EDK2 cache interface */
  error = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE,
                                      CONFIG_CONTEXT_EDK2_CACHE_INTERFACE,
                                      (void **)&edk2_cache_if);

  if (error != BL_ERR_NONE)
  {
    goto exit;
  }

  if (edk2_cache_if == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }


  /* Determine which page to start reading from.  Call _translate_logical_to_physical_page
     to determine where the requested page has really shifted to in storage due to bad blocks. */
  current_logical_page_number = src_offset / page_dev_handle->nand_info.page_size_bytes;
  error = _translate_logical_to_physical_page(page_dev_handle,
                                              current_logical_page_number,
                                              &current_physical_page_number);
  if (error != BL_ERR_NONE)
  {
    goto exit;
  }
 

  /* Determine how many first page bytes, whole pages, and remaining bytes are in the transaction */
  available_first_page_bytes = page_dev_handle->nand_info.page_size_bytes - (src_offset % page_dev_handle->nand_info.page_size_bytes);
  first_page_bytes = available_first_page_bytes > bytes_to_read ? bytes_to_read : available_first_page_bytes;
  whole_pages_remaining = (bytes_to_read - first_page_bytes) / page_dev_handle->nand_info.page_size_bytes;
  remaining_bytes = bytes_to_read - (whole_pages_remaining * page_dev_handle->nand_info.page_size_bytes) - first_page_bytes;  
  

  /* Malloc one page worth of memory to use for partial reads that cannot be copied directly to destination. */
  error = page_dev_handle->mem_if->malloc(page_dev_handle->nand_info.page_size_bytes,
                                          (void **)&temp_page_buffer);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }
  
  if(temp_page_buffer == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_MEMORY_ALLOC_FAIL);
    goto exit;
  }


  /* Mark operation start in boot statistics */
  page_dev_handle->boot_stats_if->statistics_start();  

                                    
  /* First page might be a full or partial page. */
  /* Copy page into temp buffer */
  nand_status = page_dev_handle->nand_if->nand_read(page_dev_handle->nand_handle,
                                                    NAND_ACCESS_MAIN,
                                                    current_physical_page_number,
                                                    1,
                                                    (void *)temp_page_buffer,
                                                    page_dev_handle->nand_info.page_size_bytes);

  /* It is ok to receive a page erased failure as page(s) might be erased. */
  if ((nand_status != NAND_DEVICE_DONE) &&
      (nand_status != NAND_DEVICE_FAIL_PAGE_ERASED))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }


  /* Invalidate cache for full/partial page to avoid cache hit on stale data. */
  edk2_cache_if->InvalidateDataCacheRange((void *)temp_page_buffer,
                                          page_dev_handle->nand_info.page_size_bytes);

  
  /* Copy partial data to destination. */
  memcpy(current_destination,
          (temp_page_buffer + page_dev_handle->nand_info.page_size_bytes - available_first_page_bytes),
          first_page_bytes);
  
  
  /* Move destination pointer and current logical page number */
  current_destination += first_page_bytes;
  current_logical_page_number++;


  /* Copy whole pages directly to destination */
  /* NOTE: Nand driver has a limitation where it cannot read pages across two blocks.  Reads must be bound
     to a single block per call and multiple driver reads made to achieve loading of all data. */ 
  while (whole_pages_remaining)
  {
    /* Acquire new physical page number from current logical page number as new block might have been entered. */
    error = _translate_logical_to_physical_page(page_dev_handle,
                                                current_logical_page_number,
                                                &current_physical_page_number);
    if (error != BL_ERR_NONE)
    {
      goto free_and_exit;
    }
  

    /* Determine how many whole pages can be read within the current block */
    remaining_pages_in_block =
      page_dev_handle->nand_info.pages_per_block - (current_logical_page_number % page_dev_handle->nand_info.pages_per_block);
    
    whole_pages_to_read = remaining_pages_in_block < whole_pages_remaining ? remaining_pages_in_block : whole_pages_remaining;


    /* Read max number of whole pages */
    nand_status = page_dev_handle->nand_if-> nand_read(page_dev_handle->nand_handle,
                                                       NAND_ACCESS_MAIN,
                                                       current_physical_page_number,
                                                       whole_pages_to_read,
                                                       current_destination,
                                                       (page_dev_handle->nand_info.page_size_bytes * whole_pages_to_read));

    /* It is ok to receive a page erased failure as page(s) might be erased. */
    if ((nand_status != NAND_DEVICE_DONE) &&
        (nand_status != NAND_DEVICE_FAIL_PAGE_ERASED))
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
      goto free_and_exit;
    }


    /* Increment current logical page, current destination, and decrement whole pages remaining. */
    current_logical_page_number += whole_pages_to_read;
    current_destination += (page_dev_handle->nand_info.page_size_bytes * whole_pages_to_read);
    whole_pages_remaining -= whole_pages_to_read;
  }

    
  /* Last page might be a partial read or was part of whole page read above. */
  if (remaining_bytes)
  {
    /* Acquire new physical page number from current logical page number as new block might have been entered. */
    error = _translate_logical_to_physical_page(page_dev_handle,
                                                current_logical_page_number,
                                                &current_physical_page_number);
    if (error != BL_ERR_NONE)
    {
      goto free_and_exit;
    }


    /* Copy page into temp buffer */
    nand_status = page_dev_handle->nand_if->nand_read(page_dev_handle->nand_handle,
                                                      NAND_ACCESS_MAIN,
                                                      current_physical_page_number,
                                                      1,
                                                      (void *)temp_page_buffer,
                                                      page_dev_handle->nand_info.page_size_bytes);

    /* It is ok to receive a page erased failure as page(s) might be erased. */
    if ((nand_status != NAND_DEVICE_DONE) &&
        (nand_status != NAND_DEVICE_FAIL_PAGE_ERASED))
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
      goto free_and_exit;
    }


    /* Invalidate cache for full/partial page to avoid cache hit on stale data. */
    edk2_cache_if->InvalidateDataCacheRange((void *)temp_page_buffer,
                                            page_dev_handle->nand_info.page_size_bytes);


    /* Copy partial data to destination. */
    memcpy(current_destination,
            temp_page_buffer,
            remaining_bytes);
  }


  /* Mark operation end and how many bytes read in boot statistics */
  page_dev_handle->boot_stats_if->statistics_stop(bytes_to_read);


 free_and_exit:
  /* Free temp buffer memory */
  page_dev_handle->mem_if->free(temp_page_buffer);

  
 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_page_dev_write
** ==========================================================================
*/
/*!
* 
* @brief
*   Write to page based flash device
* 
* @param[in] page dev handle, pointer to destination, source offset,
* number of bytes to write
* 
* NOTE: XBL does not have the memory resources to modify a page.  This is
*       due to a page needing to be erased before it can be written.  A
*       single page cannot be erased.  Erase granularity is at a block level.
*       This means a buffer the size of a block must be available to read/modify/write.
*       Currently that size is 256KB which is not available.
*
*       This function will ensure the dst_offset is block aligned and then
*       erase the entire block(s) required to write all the data requested.
*/
static bl_error_boot_type boot_page_dev_write(const boot_handle media_handle,
                                              void * ram_addr,
                                              uint64 dst_offset,
                                              uint32 bytes_to_write)
{
  bl_error_boot_type error = BL_ERR_NONE;
  page_device_handle * page_dev_handle = NULL;
  uint8 * current_source = NULL;
  NAND_STATUS nand_status = NAND_DEVICE_DONE;
  uint32 current_logical_block_number = 0;
  uint32 current_physical_block_number = 0;
  uint32 bytes_per_block = 0;
  uint32 current_iteration_bytes = 0;
  uint32 current_iteration_pages = 0;
  

  /* Verify arguments passed */
  if ((media_handle == NULL) ||
      (ram_addr == NULL) ||
      (bytes_to_write == 0))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Assign validated pointers */
  page_dev_handle = (page_device_handle *)media_handle;
  current_source = (uint8 *)ram_addr;

  
  /* Validate page device handle entries */
  error = _handle_check(page_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }


  /* Calculate bytes per block */
  bytes_per_block = page_dev_handle->nand_info.page_size_bytes * page_dev_handle->nand_info.pages_per_block;

  
  /* Verify dst_offset is block aligned */
  if (dst_offset % bytes_per_block)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_MISALIGNMENT);
    goto exit;
  }


  /* Determine starting block number */
  current_logical_block_number = dst_offset / bytes_per_block;


  while (bytes_to_write)
  {
    /* Convert current logical block to physical block.  This is due to avoiding
       bad blocks on the physical device. */
    error = _translate_logical_to_physical_block(page_dev_handle,
                                                 current_logical_block_number,
                                                 &current_physical_block_number);
    if (error != BL_ERR_NONE)
    {
      goto exit;
    }


    /* Erase current block */
    nand_status = page_dev_handle->nand_if->nand_erase(page_dev_handle->nand_handle,
                                                       current_physical_block_number,
                                                       1);
    if (nand_status != NAND_DEVICE_DONE)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }

    
    /* Calculate how many bytes to write for this iteration */
    current_iteration_bytes = bytes_to_write > bytes_per_block ? bytes_per_block : bytes_to_write;


    /* Calculate how many pages need to be written */
    current_iteration_pages = current_iteration_bytes / page_dev_handle->nand_info.page_size_bytes;
    current_iteration_pages +=
      current_iteration_bytes % page_dev_handle->nand_info.page_size_bytes ? 1 : 0;


    /* Write data to device */
    nand_status = page_dev_handle->nand_if->nand_write(page_dev_handle->nand_handle,
                                                       NAND_ACCESS_MAIN,
                                                       (current_physical_block_number * page_dev_handle->nand_info.pages_per_block),
                                                       current_iteration_pages,
                                                       (void *)current_source,
                                                       current_iteration_bytes);
    if (nand_status != NAND_DEVICE_DONE)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }

    
    /* Adjust all temp variables */
    bytes_to_write -= current_iteration_bytes;
    current_source += current_iteration_bytes;
    current_logical_block_number++;
  }


 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_page_dev_close
** ==========================================================================
*/
/*!
* 
* @brief
*   get the device attributes for coldplug device
* 
* @param[in] page dev handle
* 
*/
static bl_error_boot_type boot_page_dev_close(const boot_handle media_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  page_device_handle * page_dev_handle = NULL;
  boot_memory_mgr_if_type * mem_if;

  
  /* Verify arguments passed */
  if (media_handle == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Assign validated page device handle pointer */
  page_dev_handle = (page_device_handle *)media_handle;


  /* Validate page device handle entries */
  error = _handle_check(page_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }


  /* Assign validated memory interface pointer */
  mem_if = page_dev_handle->mem_if;


  /* Free the block translation table memory */
  error = mem_if->free(page_dev_handle->block_translation_table);
  if (error != BL_ERR_NONE)
  {
    goto exit;
  }

  
  /* Clear the page device handle */
  memset((void *)page_dev_handle,
          0,
          sizeof(page_device_handle));
  
 
  /* Free handle memory */  
  error = mem_if->free(page_dev_handle);
  if (error != BL_ERR_NONE)
  {
    goto exit;
  }

  
 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_page_dev_hw_init
** ==========================================================================
*/
/*!
* 
* @brief
*   Function to initialize a page based flash device
* 
* @param[in] config context handle
*
* 
*/
static bl_error_boot_type boot_page_dev_hw_init(const boot_handle config_context_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  bam_status_type bam_error = BAM_SUCCESS;
  boot_bam_if_type * bam_if = NULL;

  if(!boot_page_dev_is_hw_initialized)
  {
    /* Validate pointers */
    if (config_context_handle == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INVALID_PARAMETER);
      goto exit;
    }


    /* Get bam interface from config context */
    error = boot_config_context_get_ptr(config_context_handle,
                                        CONFIG_CONTEXT_BAM_INTERFACE,
                                        (void **)&bam_if);
    if (error != BL_ERR_NONE)
    {
      goto exit;
    }

    if (bam_if == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }


    /* Initialize bam */
    bam_error = bam_if->init();
    if (bam_error != BAM_SUCCESS)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }

    boot_page_dev_is_hw_initialized = TRUE;
  }


 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_page_dev_hw_deinit
** ==========================================================================
*/
/*!
* 
* @brief
*   Function to de-initialize a page based flash device
* 
* @param[in] config context handle
*
* 
*/
static bl_error_boot_type boot_page_dev_hw_deinit(const boot_handle config_context_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  bam_status_type bam_error = BAM_SUCCESS;
  boot_bam_if_type * bam_if = NULL;


  if(boot_page_dev_is_hw_initialized)
  {
    /* Validate pointers */
    if (config_context_handle == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INVALID_PARAMETER);
      goto exit;
    }


    /* Get bam interface from config context */
    error = boot_config_context_get_ptr(config_context_handle,
                                        CONFIG_CONTEXT_BAM_INTERFACE,
                                        (void **)&bam_if);
    if (error != BL_ERR_NONE)
    {
      goto exit;
    }

    if (bam_if == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }


    /* De-Initialize bam */
    bam_error = bam_if->deinit();
    if (bam_error != BAM_SUCCESS)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }

    boot_page_dev_is_hw_initialized = FALSE;
  }

 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_page_dev_async_read
** ==========================================================================
*/
/*!
* 
* @brief
*   Async read from page based flash device
* 
* @param[in] page dev handle, pointer to destination, source offset,
* number of bytes to read
* 
*/
static bl_error_boot_type boot_page_dev_async_read(const boot_handle media_handle,
                                                   void * ram_addr,
                                                   uint64 src_offset,
                                                   uint32 bytes_to_read)
{
  return BL_ERR_FEATURE_NOT_SUPPORTED;
}


/*=========================================================================
**  Function :  boot_page_dev_async_poll
** ==========================================================================
*/
/*!
* 
* @brief
*   Async read complete polling check
* 
* @param[in] page dev handle, pointer to unknown
* 
*/
static bl_error_boot_type boot_page_dev_async_poll(const boot_handle media_handle,
                                                   uint8 * unused)
{
  return BL_ERR_FEATURE_NOT_SUPPORTED;
}


/*=========================================================================
**  Function :  boot_page_dev_ioctl
** ==========================================================================
*/
/*!
*
* @brief
*   control page_dev params using ioctl
*
* @param[in] command, in ptr, in size, out ptr, out size ptr
*
*/
static bl_error_boot_type boot_page_dev_ioctl(uint32 cmd, void* in, uintnt in_sz, void* out, uintnt* out_sz)
{
  return BL_ERR_NONE;
}

/*=========================================================================
**  Function :  boot_page_dev_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   hook up the page dev apis to media interface
* 
* @param[in] pointer to boot_media_interface_if_type
* 
*/
bl_error_boot_type boot_page_dev_get_interface(void *media_interface_if)
{
  bl_error_boot_type error = BL_ERR_NONE;
  

  /* Verify arguments */
  if(media_interface_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_PAGEDEV, BL_ERR_INVALID_PARAMETER);
  }
  

  /* Assign apis */
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_init = boot_page_dev_hw_init;
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_deinit = boot_page_dev_hw_deinit;
  ((boot_media_interface_if_type *)media_interface_if)->open = boot_page_dev_open;
  ((boot_media_interface_if_type *)media_interface_if)->close = boot_page_dev_close;
  ((boot_media_interface_if_type *)media_interface_if)->read = boot_page_dev_read;
  ((boot_media_interface_if_type *)media_interface_if)->write = boot_page_dev_write;
  ((boot_media_interface_if_type *)media_interface_if)->async_read = boot_page_dev_async_read;
  ((boot_media_interface_if_type *)media_interface_if)->async_read_poll = boot_page_dev_async_poll;
  ((boot_media_interface_if_type *)media_interface_if)->ioctl = boot_page_dev_ioctl;


  return error;
}
