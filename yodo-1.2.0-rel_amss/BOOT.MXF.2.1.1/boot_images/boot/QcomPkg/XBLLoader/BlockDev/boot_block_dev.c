/*=============================================================================

                     Boot Block Device

GENERAL DESCRIPTION
  This file contains the implementation for boot layer that provides the APIs
  for reading and writing to block based flash devices.

Copyright 2019-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
02/14/22   rama         Move block dev unaligned buffer to heap
07/01/21   ds           media ioctl changes
05/24/21   rama         changes to make boot_block_dev_hw_init and deinit recallable
02/23/20   ds           boot_statistics for flash read
09/29/19   digants      Initial revision.
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <string.h>
#include "boot_block_dev.h"
#include "boot_block_dev_internal.h"
#include "boot_coldplug_if.h"
#include "boot_memory_mgr_if.h"
#include "boot_config_context.h"
#include "boot_media_types.h"
#include "boot_statistics_if.h"
#include <boot_edk2_cache_if.h>

/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
//Block device handle ID
#define BDEV 0x42444556
#define INTERNAL_DEVICE 0x1
#define EXTERNAL_DEVICE 0x0

#define BDEV_IOCTL_MAGIC 0x42494F4D

#define BOOT_PARTITION_INIT_DONE_MASK 0x1
#define USER_PARTITION_BACKGROUND_INIT_START_MASK 0x2
#define USER_PARTITION_BACKGROUND_INIT_FINISH_MASK 0x4
#define ALL_PARTITIONS_INIT_DONE (BOOT_PARTITION_INIT_DONE_MASK | USER_PARTITION_BACKGROUND_INIT_START_MASK | USER_PARTITION_BACKGROUND_INIT_FINISH_MASK)

typedef struct  
{
  uint32 magic;
  phys_partitions curr_phys_parti;
  boot_boolean do_background_init;
}block_dev_ioctl_info;

static block_dev_ioctl_info ioctl_info;

// Block device handle
typedef struct boot_block_dev_obj
{
  uint32 id;
  uint8 *partition_id;
  boot_media_type boot_device;
  struct coldplug_handle* coldplug_handle_ptr;
  uint32 blksz;
  uint64 blkcnt;
  boot_coldplug_if_type *coldplug_if;
  boot_memory_mgr_if_type *mem_if;
  boot_statistics_if_type *boot_stats_if;
} block_device_handle;

typedef enum 
{
  STORAGE_NONE = 0,
  STORAGE_READ = 1,
  STORAGE_WRITE = 2,
}storage_operation;
typedef struct last_read_info
{
  storage_operation last_storage_operation;
  uint32 prv_sector ;
  uint8 *last_read_gpt_id ;
} last_read_info;

static last_read_info storage_last_read_info ={STORAGE_NONE,0,NULL};
static uint8 block_dev_unaligned_rw_buffer[MAX_SECTOR_SIZE] __attribute__ ((aligned (CACHE_LINE_LENGTH_BYTES)));
/* from LSB -
 bit 0 - BOOT_PARTITION_INIT_DONE
 bit 1 - USER_PARTITION_BACKGROUND_INIT_START
 bit 3 - USER_PARTITION_BACKGROUND_INIT_FINISH
*/
static uint8 boot_block_dev_hw_init_status = 0x0; // bit map for init status 

/*=============================================================================

FUNCTION DEFINITIONS

=============================================================================*/
/*=========================================================================

**  Function :  _init

** ==========================================================================
*/
/*!
*
* @brief
*   intialize the block dev handle.
*
* @param[in] pointer to block dev handle
*
*/
static void _init(block_device_handle *handle)
{
  memset((void *)handle, 0, sizeof(block_device_handle));
  handle->id = BDEV;
  handle->partition_id = NULL;
  handle->boot_device = 0;
  handle->coldplug_handle_ptr = NULL;
  handle->blksz = 0;
  handle->blkcnt = 0;
  handle->coldplug_if = NULL;
  handle->mem_if = NULL;
}

/*=========================================================================

**  Function :  _init_ioctl_info()

** ==========================================================================
*/
/*!
*
* @brief
*   intialize the block dev ioctl_info.
*
* @param[in] None
*
*/
static void _init_ioctl_info(void)
{
  memset((void *)(&ioctl_info), 0, sizeof(ioctl_info));
  ioctl_info.magic = BDEV_IOCTL_MAGIC;
  ioctl_info.curr_phys_parti = ALL_PARTITIONS;
  ioctl_info.do_background_init = FALSE;
}

/*=========================================================================

**  Function :  _handle_check

** ==========================================================================
*/
/*!
*
* @brief
*   Sanitize the block dev handle.
*
* @param[in] block dev handle
*
*/
static bl_error_boot_type _handle_check(boot_handle handle)
{
  if (handle==NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INVALID_PARAMETER);
  }

  if (((block_device_handle *)handle)->id != BDEV)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INVALID_HANDLE);
  }

  return BL_ERR_NONE;
}

/*=========================================================================

**  Function :  _get_dev_attr

** ==========================================================================
*/
/*!
*
* @brief
*   get the device attributes for coldplug device
*
* @param[in] boot device,device location pointer
* @param[in] device type pointer
*
*/
static bl_error_boot_type _get_dev_attr(boot_media_type boot_device, int *dev_loc_ptr, enum coldplug_device_type *dev_type_ptr)
{
  if (boot_device == MMC_FLASH)
  {
    *dev_loc_ptr = INTERNAL_DEVICE;
    *dev_type_ptr = COLDPLUG_DEVICE_SD;
  }
  else if (boot_device == SDC_FLASH)
  {
    *dev_loc_ptr = EXTERNAL_DEVICE;
    *dev_type_ptr = COLDPLUG_DEVICE_SD;
  }
  else if (boot_device == UFS_FLASH)
  {
    *dev_loc_ptr = INTERNAL_DEVICE;
    *dev_type_ptr = COLDPLUG_DEVICE_UFS;
  }
  else if (boot_device == SPI_FLASH)
  {
    *dev_loc_ptr = INTERNAL_DEVICE;
    *dev_type_ptr = COLDPLUG_DEVICE_SPI_NOR;
  }
  else if (boot_device == NVME_FLASH)
  {
    *dev_loc_ptr = INTERNAL_DEVICE;
    *dev_type_ptr = COLDPLUG_DEVICE_NVME;
  }
  else
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_UNSUPPORTED_BLOCK_DEV);
  }
  return BL_ERR_NONE;
}

/*=========================================================================

**  Function :  boot_block_dev_hw_init

** ==========================================================================
*/
/*!
*
* @brief
*   Function to initialize block based flash device
*
* @param[in] config context handle
*
*
*/
static bl_error_boot_type boot_block_dev_hw_init(const boot_handle config_context_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  boot_media_type boot_device;
  int dev_loc = INTERNAL_DEVICE;
  enum coldplug_device_type dev_type = COLDPLUG_DEVICE_DEVNULL;
  boot_coldplug_if_type *coldplug_if = NULL;
  int16 cldplg_status = COLDPLUG_RESULT_INVALID_ARG;

  if((boot_block_dev_hw_init_status & ALL_PARTITIONS_INIT_DONE) != ALL_PARTITIONS_INIT_DONE)
  {
    if (config_context_handle == NULL)
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INVALID_PARAMETER);
    }
    
    if(ioctl_info.magic != BDEV_IOCTL_MAGIC)
    {
      _init_ioctl_info();
    }
    
    error = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, &boot_device);
    if (error != BL_ERR_NONE)
    {
      return error;
    }

    error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_COLDPLUG_INTERFACE, (void **)&coldplug_if);
    if (error != BL_ERR_NONE)
    {
      return error;
    }
    if (coldplug_if == NULL)
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INTERFACE_FAILURE);
    }

    error = _get_dev_attr(boot_device, &dev_loc, &dev_type);
    if(error != BL_ERR_NONE)
    {
      return error;
    }
    
    if((ioctl_info.curr_phys_parti == BOOT_PARTITION || ioctl_info.curr_phys_parti == ALL_PARTITIONS)
    && !(boot_block_dev_hw_init_status & BOOT_PARTITION_INIT_DONE_MASK))
    {
      cldplg_status = coldplug_if->init();
      if (cldplg_status != COLDPLUG_RESULT_SUCCESS)
      {
        return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_INIT_FAILURE);
      }

      cldplg_status = coldplug_if->open_boot_device(dev_type, dev_loc);
      if (cldplg_status != COLDPLUG_RESULT_SUCCESS && cldplg_status != COLDPLUG_RESULT_NOT_SUPPORTED)
      {
        return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_OPEN_BOOT_DEV_FAILURE);
      }
      boot_block_dev_hw_init_status |=  BOOT_PARTITION_INIT_DONE_MASK;
    }

    // now we can read anything from boot-lun

    if(ioctl_info.curr_phys_parti == USER_PARTITION || ioctl_info.curr_phys_parti == ALL_PARTITIONS)
    {
      if(!(boot_block_dev_hw_init_status & USER_PARTITION_BACKGROUND_INIT_START_MASK))
      {
        cldplg_status = coldplug_if->background_init_start(dev_type, dev_loc, 0);
        if (cldplg_status != COLDPLUG_RESULT_SUCCESS && cldplg_status != COLDPLUG_RESULT_NOT_SUPPORTED)
        {
          return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_BACKGRND_INIT_START_FAILURE);
        }
        
        boot_block_dev_hw_init_status |= USER_PARTITION_BACKGROUND_INIT_START_MASK;
        
        if(ioctl_info.do_background_init == TRUE)
        {
          return BL_ERR_NONE;
        }
      }

      // cannot access device, so don't call any coldplug APIs
      // this is the spot to initialize other things in parallel to UFS

      if((boot_block_dev_hw_init_status & USER_PARTITION_BACKGROUND_INIT_START_MASK) 
        && !(boot_block_dev_hw_init_status & USER_PARTITION_BACKGROUND_INIT_FINISH_MASK))
      {
        cldplg_status = coldplug_if->background_init_finish(dev_type, dev_loc, 0);
        if (cldplg_status != COLDPLUG_RESULT_SUCCESS && cldplg_status != COLDPLUG_RESULT_NOT_SUPPORTED)
        {
          return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_BACKGRND_INIT_FINISH_FAILURE);
        }

        cldplg_status = coldplug_if->open_device(dev_type, dev_loc);
        if (cldplg_status != COLDPLUG_RESULT_SUCCESS && cldplg_status != COLDPLUG_RESULT_NOT_SUPPORTED)
        {
          return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_OPEN_DEV_FAILURE);
        }
        boot_block_dev_hw_init_status |= USER_PARTITION_BACKGROUND_INIT_FINISH_MASK;
      }
    }
  }

  return error;
}

/*=========================================================================

**  Function :  boot_block_dev_open

** ==========================================================================
*/
/*!
*
* @brief
*   Function to get coldplug handle and return the block dev handle
*   to client.
*
* @param[in] pointer to config context handle, pointer to block dev handle pointer
*
*
*/
static bl_error_boot_type boot_block_dev_open(const boot_handle config_context_handle, boot_handle *handle_ptr)
{
  bl_error_boot_type error = BL_ERR_NONE;
  boot_media_type boot_device = 0;
  block_device_handle *handle = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;
  boot_statistics_if_type *boot_stats_if = NULL;
  uint8 *partition_id = NULL;
  boot_coldplug_if_type *coldplug_if = NULL;
  struct coldplug_handle *coldplug_hdl_ptr = NULL;
  int dev_loc = INTERNAL_DEVICE;
  enum coldplug_device_type dev_type = COLDPLUG_DEVICE_DEVNULL;
  uint32 blksz =0;
  uint64 blkcnt = 0;

  if (config_context_handle == NULL || handle_ptr == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INVALID_PARAMETER);
  }

  error = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, &boot_device);
  if (error != BL_ERR_NONE)
  {
    return error;
  }

  error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_PARTITION_ID, (void **)&partition_id);
  if (error != BL_ERR_NONE)
  {
    return error;
  }
  if (partition_id == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INTERFACE_FAILURE);
  }

  error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
  if (error != BL_ERR_NONE)
  {
    return error;
  }
  if (mem_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INTERFACE_FAILURE);
  }

  error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_COLDPLUG_INTERFACE, (void **)&coldplug_if);
  if (error != BL_ERR_NONE)
  {
    return error;
  }
  if (coldplug_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INTERFACE_FAILURE);
  }

  error = _get_dev_attr(boot_device, &dev_loc, &dev_type);
  if (error != BL_ERR_NONE)
  {
    return error;
  }

  coldplug_hdl_ptr = coldplug_if->open_gpt_partition(dev_type, dev_loc, (struct coldplug_guid *)partition_id);
  if (coldplug_hdl_ptr == NULL)
  {
    GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_HANDLE_FAILURE);
    return BL_ERROR_OPEN_GPT_PARTITION_FAIL;
  }

  error = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_BOOT_STATS_INTERFACE, (void **)&boot_stats_if);
  if (error != BL_ERR_NONE)
  {
    return error;
  }

  error = mem_if->malloc(sizeof(block_device_handle), (void *)&handle);
  if (error != BL_ERR_NONE)
  {
    return error;
  }
  if (handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_MEMORY_ALLOC_FAIL);
  }

  _init(handle);

  if (coldplug_if->get_size(coldplug_hdl_ptr, &blksz, &blkcnt) != COLDPLUG_RESULT_SUCCESS)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_GET_SIZE_FAILURE);
  }

  handle->partition_id = partition_id;
  handle->boot_device  =boot_device;
  handle->coldplug_handle_ptr = coldplug_hdl_ptr;
  handle->blksz = blksz;
  handle->blkcnt = blkcnt;
  handle->coldplug_if = coldplug_if;
  handle->mem_if = mem_if;
  handle->boot_stats_if = boot_stats_if;

  *handle_ptr = (boot_handle)handle;
  
  return BL_ERR_NONE;
}

/*=========================================================================

**  Function :  boot_block_dev_read

** ==========================================================================
*/
/*!
*
* @brief
*   Read from block based flash device
*
* @param[in] block dev handle, pointer to destination, source offset,
* number of bytes to read
*
*/
static bl_error_boot_type boot_block_dev_read(const boot_handle handle, void *ram_addr, uint64 src_offset, uint32 bytes_to_read)
{
  bl_error_boot_type error = BL_ERR_NONE;
  uint32 sector_size = 0, start_sector = 0, end_sector = 0, num_sectors = 0, leading_pad = 0;
  uint32 trailing_length = 0;
  uint64 end_sector_bytes = 0;
  uint16 block_count = 0;
  uint8* dest_addr = (uint8*)ram_addr;
  boot_edk2_cache_if_type *edk2_cache_if = NULL;
  do
  {
    error = _handle_check(handle);
    if (error != BL_ERR_NONE)
    {
      break;
    }

    error = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_EDK2_CACHE_INTERFACE, (void **)&edk2_cache_if);
    if(error != BL_ERR_NONE)
    {
      break;
    }
    if(edk2_cache_if == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    if (ram_addr == NULL || bytes_to_read == 0)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INVALID_PARAMETER);
      break;
    }

    sector_size = ((block_device_handle *)handle)->blksz;

    if (sector_size == 0 || sector_size > MAX_SECTOR_SIZE)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INCORRECT_SECTOR_SIZE);
      break;
    }

    ((block_device_handle *)handle)->boot_stats_if->statistics_start();

    start_sector = src_offset / sector_size;
    leading_pad = src_offset % sector_size;
    end_sector_bytes = src_offset + bytes_to_read;
    end_sector = end_sector_bytes  / sector_size;
    trailing_length = end_sector_bytes % sector_size;
    num_sectors = (trailing_length != 0) ? (end_sector - start_sector + 1):(end_sector - start_sector);

    /* This handles the case of reading a partial sector. In this partial sector
       read we need to skip the length of leading bytes */
    if (leading_pad > 0 )
    {
      /*If the currect sector to be read is the same as privious sector and parition is the same and 
        last time is also block read operation,ignoring the same sector read from UFS this time. 
        Block dev layer will use the date from last read buffer.*/
      if((storage_last_read_info.last_storage_operation != STORAGE_READ || 
          storage_last_read_info.prv_sector != start_sector || 
          storage_last_read_info.last_read_gpt_id != ((block_device_handle *)handle)->partition_id))
      {
        if (COLDPLUG_RESULT_SUCCESS != ((((block_device_handle *)handle)->coldplug_if)->read(((block_device_handle *)handle)->coldplug_handle_ptr, start_sector,
                                        1, block_dev_unaligned_rw_buffer)))
        {
          error =  GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_READ_FAILURE);
          break;
        }
        /* Invalidate Cache range for local buffer to avoid cache hits for stale data. */
        edk2_cache_if->InvalidateDataCacheRange((void *)block_dev_unaligned_rw_buffer, MAX_SECTOR_SIZE);
        storage_last_read_info.last_storage_operation = STORAGE_READ;
        storage_last_read_info.prv_sector = start_sector;
        storage_last_read_info.last_read_gpt_id = ((block_device_handle *)handle)->partition_id;
      }
      /* If the requested read lies within this sector, that is the read is less than
         a sector */
      if ((end_sector == start_sector) && (trailing_length != 0))
      {
        memcpy(dest_addr, &block_dev_unaligned_rw_buffer[leading_pad], bytes_to_read);
        break;
      }
      else
      {
        memcpy(dest_addr, &block_dev_unaligned_rw_buffer[leading_pad], (sector_size - leading_pad));
        dest_addr += (sector_size - leading_pad);
      }

      /* As we have read a partial sector decrement the total number
         of sectors to be read and increment the start sector */
      if (num_sectors > 0)
      {
        num_sectors --;
      }

      start_sector++;
    }/* leading_pad */

    /* If trailing bytes exist, that is a partial read of the last sector, then we
       decrement the number of sectors and do the partial read of the last sector separately */
    if ( (trailing_length != 0) && (num_sectors > 0))
    {
      num_sectors--;
    }

    /* Read all the remaining sectors by looping. */
    while (num_sectors > 0)
    {
      /* If the number of sectors to be read exceeds max value of block_count,
         do it in a loop */
      block_count = (num_sectors > BLOCK_COUNT_MAX)? BLOCK_COUNT_MAX : num_sectors;

      if (COLDPLUG_RESULT_SUCCESS != ((((block_device_handle *)handle)->coldplug_if)->read(((block_device_handle *)handle)->coldplug_handle_ptr,
                                      start_sector, block_count, dest_addr)))
      {
        error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_READ_FAILURE);
        break;
      }
    
      num_sectors  -= block_count;
      start_sector += block_count;
      dest_addr    += block_count*sector_size;
    } /* num_sectors */

    /* If num_sectors is still > 0, that means we broke out prematurely, and
       need to break out of the overall loop, so we catch the FALSE return_status
       and don't continue loading the final trailing bytes, if there are any     */
    if (num_sectors > 0)
    {
      break;
    }

    /* Read the traling bytes - the partial sector at the end */
    if ( trailing_length != 0 )
    {
      if((storage_last_read_info.last_storage_operation != STORAGE_READ || 
          storage_last_read_info.prv_sector != start_sector || 
          storage_last_read_info.last_read_gpt_id != ((block_device_handle *)handle)->partition_id))
      {
        if (COLDPLUG_RESULT_SUCCESS != ((((block_device_handle *)handle)->coldplug_if)->read(((block_device_handle *)handle)->coldplug_handle_ptr, start_sector,
                                        1, block_dev_unaligned_rw_buffer)))
        {
          error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_READ_FAILURE);
          break;
        }

        /* Invalidate Cache range for local buffer to avoid cache hits for stale data. */
        edk2_cache_if->InvalidateDataCacheRange((void *)block_dev_unaligned_rw_buffer, MAX_SECTOR_SIZE);
        storage_last_read_info.last_storage_operation = STORAGE_READ;
        storage_last_read_info.prv_sector = start_sector;
        storage_last_read_info.last_read_gpt_id = ((block_device_handle *)handle)->partition_id;
      }
      memcpy(dest_addr, block_dev_unaligned_rw_buffer, trailing_length);
    }

    if (error == BL_ERR_NONE)
    {
      ((block_device_handle *)handle)->boot_stats_if->statistics_stop(bytes_to_read);
    }

  }while(FALSE);

  return error;

} /* dev_sdcc_read_bytes */

/*=========================================================================

**  Function :  boot_block_dev_write

** ==========================================================================
*/
/*!
*
* @brief
*   Write from block based flash device
*
* @param[in] block dev handle, pointer to destination, source offset,
* number of bytes to read
*
*/
static bl_error_boot_type boot_block_dev_write(const boot_handle handle, void *ram_addr, uint64 dst_offset, uint32 bytes_to_write)
{
  bl_error_boot_type error = BL_ERR_NONE;
  uint32 start_sector = 0, leading_length = 0;
  uint32 end_sector = 0, trailing_length = 0;
  uint16 block_count = 0;
  uint8 *buf_addr = (uint8*)ram_addr;
  uint32 sector_size = 0;
 
  do
  {
    error = _handle_check(handle);
    if (error != BL_ERR_NONE)
    {
      break;
    }

    if (ram_addr == NULL || bytes_to_write == 0)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INVALID_PARAMETER);
      break;
    }

    sector_size = ((block_device_handle *)handle)->blksz;

    if (sector_size == 0 || sector_size > MAX_SECTOR_SIZE)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INCORRECT_SECTOR_SIZE);
      break;
    }

    start_sector = dst_offset/sector_size;
    leading_length = dst_offset % sector_size;
    end_sector = (dst_offset + bytes_to_write)/sector_size;
    trailing_length = (dst_offset + bytes_to_write) % sector_size;

    if (leading_length >= sector_size)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INCORRECT_SECTOR_SIZE);
      break;
    }
    /* Nothing to write */
    if (bytes_to_write == 0)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INCORRECT_SECTOR_SIZE);
      break;
    }


    if (leading_length > 0)
    {
      /* Read the orginal data from start sector */
      if (COLDPLUG_RESULT_SUCCESS != ((((block_device_handle *)handle)->coldplug_if)->read(((block_device_handle *)handle)->coldplug_handle_ptr, start_sector,
                                      1, block_dev_unaligned_rw_buffer)))
      {
        error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_READ_FAILURE);
        break;
      }

      /* When end_sector equals start_sector, the whole write won't exceed one sector */
      if (end_sector == start_sector)
      {
        /* Check the write size, make sure we don't overflow the buffer.
           Not necessary but added for klocwork*/
        if ((bytes_to_write + leading_length) <= sector_size)
        {
          memcpy(&block_dev_unaligned_rw_buffer[leading_length], buf_addr, bytes_to_write);
        }
        else
        {
          error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_BUFFER_OVERFLOW);
          break;
        }

        /* Now write back this one leading sector and we are done */
        if (COLDPLUG_RESULT_SUCCESS != ((((block_device_handle *)handle)->coldplug_if)->write(((block_device_handle *)handle)->coldplug_handle_ptr,
                                        start_sector,
                                        1,
                                        block_dev_unaligned_rw_buffer)))
        {
          error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_WRITE_FAILURE);
        }
        break;
      }

      /* The write size is more than this sector, need to copy data till this sector's end */
      memcpy(&block_dev_unaligned_rw_buffer[leading_length], buf_addr, sector_size - leading_length);
      buf_addr += sector_size - leading_length;
      /* Now write back this one leading sector */
      if (COLDPLUG_RESULT_SUCCESS != ((((block_device_handle *)handle)->coldplug_if)->write(((block_device_handle *)handle)->coldplug_handle_ptr,
                                      start_sector,
                                      1,
                                      block_dev_unaligned_rw_buffer)))
      {
        error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_WRITE_FAILURE);
        break;
      }

      /* As we have write a partial sector,increment the start sector */
      start_sector++;
    }

    /* write all the aligned sectors by looping. */
    while (start_sector < end_sector)
    {
      /* If the number of sectors to be write exceeds max value of block_count,
         do it in a loop */
      block_count = ((end_sector - start_sector) > BLOCK_COUNT_MAX)? BLOCK_COUNT_MAX : (end_sector - start_sector);

      if (COLDPLUG_RESULT_SUCCESS != ((((block_device_handle *)handle)->coldplug_if)->write(((block_device_handle *)handle)->coldplug_handle_ptr,
                                      start_sector,
                                      block_count,
                                      buf_addr)))
      {
        error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_WRITE_FAILURE);
        break;
      }
      start_sector += block_count;
      buf_addr += block_count*sector_size;
    }

    /* If start_sector does not equals end_sector, that means we broke out prematurely, and
       need to break out of the overall loop, so we catch the FALSE return_status
       and don't continue writing the final trailing bytes, if there are any */
    if (start_sector != end_sector)
    {
      break;
    }

    /* Write trailing sector */
    if (trailing_length > 0)
    {
      /* Read sector for partial write */
      if (COLDPLUG_RESULT_SUCCESS != ((((block_device_handle *)handle)->coldplug_if)->read(((block_device_handle *)handle)->coldplug_handle_ptr,
                                      end_sector,
                                      1,
                                      block_dev_unaligned_rw_buffer)))
      {
        error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_READ_FAILURE);
        break;
      }

      /* Copy trailing data to write buffer */
      memcpy(block_dev_unaligned_rw_buffer, buf_addr, trailing_length);

      /* Write back updated sector */
      if (COLDPLUG_RESULT_SUCCESS != ((((block_device_handle *)handle)->coldplug_if)->write(((block_device_handle *)handle)->coldplug_handle_ptr,
                                      end_sector,
                                      1,
                                      block_dev_unaligned_rw_buffer)))
      {
        error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_WRITE_FAILURE);
        break;
      }
    }
  }while(FALSE);

  storage_last_read_info.last_storage_operation = STORAGE_WRITE;
  return error;
}

/*=========================================================================

**  Function :  boot_block_dev_close

** ==========================================================================
*/
/*!
*
* @brief
*   get the device attributes for coldplug device
*
* @param[in] block dev handle
*
*/
static bl_error_boot_type boot_block_dev_close(const boot_handle handle)
{
  bl_error_boot_type error = BL_ERR_NONE;

  error = _handle_check(handle);
  if (error != BL_ERR_NONE)
  {
    return error;
  }

  ((block_device_handle *)handle)->id = 0;

  if (((((block_device_handle *)handle)->coldplug_if)->close_partition(((block_device_handle *)handle)->coldplug_handle_ptr)) != COLDPLUG_RESULT_SUCCESS)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_CLOSE_PARTITION_FAILURE);
  }

  error = (((block_device_handle *)handle)->mem_if)->free(handle);
  if (error != BL_ERR_NONE)
  {
    return error;
  }

  return error;
}

/*=========================================================================

**  Function :  boot_block_dev_ioctl

** ==========================================================================
*/
/*!
*
* @brief
*   control block_dev params using ioctl
*
* @param[in] command, in ptr, in size, out ptr, out size ptr 
*
*/
static bl_error_boot_type boot_block_dev_ioctl(uint32 cmd, void* in, uintnt in_sz, void* out, uintnt* out_sz)
{
  bl_error_boot_type error = BL_ERR_NONE;
  
  if(cmd >= BDEV_IOCTL_MAX || cmd < DEFAULT_MEDIA_INIT)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COMMAND_NOT_RECOGNIZED);
  }
  
  if(ioctl_info.magic != BDEV_IOCTL_MAGIC || cmd == DEFAULT_MEDIA_INIT)
  {
    _init_ioctl_info();
  }
  switch(cmd)
  {
    case BDEV_SET_HW_INIT_PARTITION:
      if(in == NULL)
      {
        error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV,BL_ERR_INVALID_PARAMETER);
        break;
      }
      ioctl_info.curr_phys_parti = (phys_partitions) *((phys_partitions *)(in));
      break;
    
    case BDEV_SET_DO_BACKGROUND_INIT:
     if(in == NULL)
      {
        error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV,BL_ERR_INVALID_PARAMETER);
        break;
      }
      if(*((uint32 *)in) > 0)
      {
        ioctl_info.do_background_init = TRUE;        
      }
      else
      {
        ioctl_info.do_background_init = FALSE; 
      }
      break;
      
    case GET_CURRENT_PARTITION_SIZE:
      if(in == NULL || out == NULL)
      {
        error = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV,BL_ERR_INVALID_PARAMETER);
        break;
      }
      error = _handle_check(in);
      if(error != BL_ERR_NONE)
      {
        break;
      }
      *((uint32 *)out) = (((block_device_handle *)in)->blksz)*(((block_device_handle *)in)->blkcnt);
      break;
   
    default:
      break;
  }

  return error;
}

/*=========================================================================

**  Function :  boot_block_dev_get_interface

** ==========================================================================
*/
/*!
*
* @brief
*   hook up the block dev apis to media interface
*
* @param[in] pointer to boot_media_interface_if_type
*
*/
bl_error_boot_type boot_block_dev_get_interface(void *media_interface_if)
{
  bl_error_boot_type error = BL_ERR_NONE;

  if (media_interface_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INVALID_PARAMETER);
  }

  ((boot_media_interface_if_type *)media_interface_if)->media_hw_init = boot_block_dev_hw_init;
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_deinit = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->open = boot_block_dev_open;
  ((boot_media_interface_if_type *)media_interface_if)->close = boot_block_dev_close;
  ((boot_media_interface_if_type *)media_interface_if)->read = boot_block_dev_read;
  ((boot_media_interface_if_type *)media_interface_if)->write = boot_block_dev_write;
  ((boot_media_interface_if_type *)media_interface_if)->async_read = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->async_read_poll = NULL;
  ((boot_media_interface_if_type *)media_interface_if)->ioctl = boot_block_dev_ioctl;

  return error;
}
