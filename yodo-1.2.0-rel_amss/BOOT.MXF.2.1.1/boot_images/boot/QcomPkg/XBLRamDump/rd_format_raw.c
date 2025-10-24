/*===========================================================================

                         Boot Raw dump format interface

GENERAL DESCRIPTION
  This header file contains declarations and definitions for memory
  dumps to raw parition.

Copyright 2021-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who             what, where, why
--------   ---         --------------------------------------------------
05/25/22   rama        Changes for dynamically allocation section_header_table
02/22/21   vk          Initial version

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>
#include "boot_dload_debug.h"
#include "boot_shared_imem_cookie.h"
#include "boot_target.h"
#include <boot_memory_mgr_if.h>
#include <boot_ramdump_wrapper_apis.h>
#include <boot_config_context.h>
#include <boot_media_interface_if.h>
#include <boot_visual_indication_if.h>
#include <boot_reset_if.h>
#include <boot_pmic_if.h>
#include <boot_coldplug_if.h>
#include "boot_raw_partition_ramdump.h"
#include <ramdump_format_if.h>

/* Size of data to write for each call to coldplug write(2MB)*/
#define RAM_DUMP_WRITE_SIZE (0x200000)


/* GUID for ram dump parition */
static  struct coldplug_guid ram_dump_partition_id = { 0x66C9B323, 0xF7FC, 0x48B6, { 0xBF, 0x96, 0x6F, 0x32, 0xE3, 0x35, 0xA4, 0x28 } };

/* Allocate header buffer in ddr */
/* Raw dump header */
struct boot_raw_parition_dump_header raw_dump_header SECTION(".bss.BOOT_UNCACHED_DDR_ZI_ZONE");

/* Table that stores the raw dump section headers */
struct boot_raw_partition_dump_section_header *raw_dump_section_header_table = NULL;

/* Pointer points to the parition offset we are going to write data to*/
static uintnt curr_partition_offset;
static uintnt curr_partition_index;

/*=========================================================================

                       FUNCTION DEFINITIONS

=========================================================================*/

/*===========================================================================

**  Function :  boot_raw_ram_dump_error_handler

** ==========================================================================
*/
/*!
*
* @brief
*   Utility function that handles error in raw ram dump process
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
static bl_error_boot_type boot_raw_ram_dump_error_handler(boot_handle config_context_handle)
{
  /* Turn on LED if there's an write error and enter error handler*/
  bl_error_boot_type status = BL_ERR_NONE;
  boot_visual_indicator_if_type *visual_indicator_if = NULL;

  do
  {
    if (config_context_handle == NULL)
    {
      status  = GET_ERROR_CODE (BL_ERROR_GROUP_RAMDUMP, BL_ERR_INVALID_PARAMETER);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_VISUAL_INDICATOR_INTERFACE, (void **)&visual_indicator_if);
    if (status != BL_ERR_NONE)
    {
      status  = GET_ERROR_CODE (BL_ERROR_GROUP_VISUAL_INDICATOR, BL_ERR_INVALID_PARAMETER);
      break;
    }
    if (visual_indicator_if == NULL)
    {
      status  = GET_ERROR_CODE (BL_ERROR_GROUP_VISUAL_INDICATOR, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    visual_indicator_if->enable_led(RAM_DUMP_LED, TRUE);

  }while (FALSE);
  
  return status;
}

/*===========================================================================

**  Function :  boot_ramdump_media_if_write

** ==========================================================================
*/
/*!
*
* @brief
*   Utility function that writes data to storage and toggle led in between writes
*
* @par Dependencies
*   boot_toggle_led_init needs to be called
*
* @retval
*   BL_ERR_NONE
*
* @par Side Effects
*   None
*
*/
static bl_error_boot_type boot_ramdump_media_if_write(boot_media_interface_if_type *media_if, void *buf_addr, uint64 offset, uint32 *write_size)
{
  bl_error_boot_type status = BL_ERR_NONE, return_status = BL_ERR_NONE;
  boot_handle media_handle;
  uint32 bytes_to_write = 0;
  uint32 total_write_bytes = 0;

  do
  {

    status = media_if->open(CONFIG_CONTEXT_CRT_HANDLE, &media_handle);
    if (status != BL_ERR_NONE)
    {
      DL_LOG("MediaIf Open Fail, Errcode:0x%x", status);
      return_status = status;
      break;
    }

    while (*write_size > 0)
    {
      bytes_to_write =  *write_size > RAM_DUMP_WRITE_SIZE ? RAM_DUMP_WRITE_SIZE : *write_size;
      status = media_if->write(media_handle, buf_addr, offset, bytes_to_write);
      if (status != BL_ERR_NONE)
      {
        DL_LOG("MediaIf Write Fail, Errcode:0x%x", status);
        return_status = status;
        break;
      }
      *write_size -= bytes_to_write;
      buf_addr = (void *)(uintnt)(uint64)buf_addr + bytes_to_write;
      offset += bytes_to_write;
      total_write_bytes += bytes_to_write;
    }
    if (media_handle!= NULL)
    {
      status = media_if->close(media_handle);
      if (status != BL_ERR_NONE)
      {
        DL_LOG("MediaIf Close Fail, Errcode:0x%x", status);
        return_status = status;
        break;
      }
    }
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
  } while (FALSE);
  *write_size = total_write_bytes;
  return return_status;
}


/*===========================================================================

**  Function :  dump_overall_headers

** ==========================================================================
*/
/*!
*
* @brief
*   Utility function that writes the overall header to storage
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type dump_overall_headers(boot_handle media_if)
{
  uint32 write_size = DUMP_HEADER_SIZE;
  return  boot_ramdump_media_if_write(media_if, &raw_dump_header,
                                      0, /* header starts at partition offset 0 */
                                      &write_size);
}


/*===========================================================================

**  Function :  dump_section_headers

** ==========================================================================
*/
/*!
*
* @brief
*   Utility function that writes the section headers to storage
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type dump_section_headers(boot_handle media_if)
{
  uint32 write_size = 0;
  write_size = SECTION_HEADER_SIZE * dload_mem_debug_num_ent();
  return boot_ramdump_media_if_write(media_if, raw_dump_section_header_table, DUMP_HEADER_SIZE, &write_size);
}


/*===========================================================================

**  Function :  get_raw_ram_dump_required_size

** ==========================================================================
*/
/*!
*
* @brief
*  Returns the required total raw partition ram dump size in bytes
*
* @par Dependencies
*   dload_mem_debug_init needs to be called
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
static uint64 get_raw_ram_dump_required_size()
{
  uint32 i = 0;

  /* We first need space to store overall header and section header*/
  uint64 require_size = DUMP_HEADER_SIZE + SECTION_HEADER_SIZE * dload_mem_debug_num_ent();

  for (; i < dload_mem_debug_num_ent() ; i++)
  {
    require_size += dload_mem_debug_mem_length(i);
  }

  return require_size;
}


/*===========================================================================

**  Function :  boot_update_section_header_table_by_index

** ==========================================================================
*/
/*!
*
* @brief
*  Given an index of memory dump sections, fill up the information on
*  section header table
*
* @par Dependencies
*   dload_mem_debug_init needs to be called
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
void boot_update_section_header_table_by_index(struct boot_raw_partition_dump_section_header *section_header_table, uint32 i)
{
  uint64 curr_sec_size = 0;
  uintnt curr_sec_base_addr = 0;
  char * debug_filename = NULL;
  curr_sec_size = dload_mem_debug_mem_length(i);
  curr_sec_base_addr = dload_mem_debug_mem_base(i);

  /* If section size is less than 2KB then we know it's SV type and we
     don't need specify base address */
  if (curr_sec_size < SV_DATA_SIZE_LIMIT)
  {
    section_header_table[i].section_type = RAW_PARITION_DUMP_SV_TYPE;
  }

  /* If section size is less than 128MB but larger than 2KB then it's internal
     system memory, we need to add base address */
  else if (curr_sec_size < SV_MEMORY_SIZE_LIMIT)
  {
    section_header_table[i].section_type = RAW_PARITION_DUMP_SV_TYPE;
    section_header_table[i].section_info.base_addr = curr_sec_base_addr;
  }
  /* For sections that's larger than 128MB it's DDR */
  else
  {
    section_header_table[i].section_type = RAW_PARITION_DUMP_DDR_TYPE;
    section_header_table[i].section_info.base_addr = curr_sec_base_addr;
  }

  section_header_table[i].section_version = RAM_DUMP_SECTION_HEADER_VER;
  section_header_table[i].section_offset = curr_partition_offset;
  section_header_table[i].section_size = curr_sec_size;

  /* Copy the file name to section name */
  debug_filename = dload_mem_debug_filename(i);
  BL_VERIFY(debug_filename, BL_ERR_NULL_PTR_PASSED|BL_ERROR_GROUP_BOOT);

  strlcpy((char *)&section_header_table[i].section_name, debug_filename, SECTION_NAME_LEN);
}


/*===========================================================================

**  Function : rd_raw_format_write 

** ==========================================================================
*/
/*!
*
* @brief
*   This function will write all the section data to partition sequentially
*  It will update the section header with the operation result.
*  If there is not enough space left it will return false.
*
* @par Dependencies
*   dload_mem_debug_init needs to be called
*
* @retval
*   False if there's not enough space left for one section's data
*   True if all sections' data has been written
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type rd_raw_format_write (boot_handle  media_if, char *filename, void *buffer, uintnt size)
{
  uint64 curr_sec_size = 0;
  uintnt curr_sec_base_addr = 0;
  boot_memory_mgr_if_type *mem_if = NULL;
  bl_error_boot_type error = BL_ERR_NONE;
  uint8 * prestrict_region_dump_read_buffer = NULL;
  uint64 size_left = 0, write_size = 0;
  uint64 partition_offset = 0;
  bl_error_boot_type status = BL_ERR_NONE;

  /* Set the size ,base and offset in current section's header */
  curr_sec_size = size;
  curr_sec_base_addr = (uintnt)buffer;

  DL_LOG("RawDump: Dump start address:0x%llx, size 0x%llx", curr_sec_base_addr, curr_sec_size);

  /* Update the section header */
  boot_update_section_header_table_by_index(raw_dump_section_header_table, curr_partition_index);

  /* Now section header info is updated, we need to write the raw section data to storage */
  if (dload_mem_debug_is_restricted_addr(curr_sec_base_addr, curr_sec_size))
  {
    do
    {
      error = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
      if (error != BL_ERR_NONE)
      {
        break;
      }

      error = mem_if->malloc(RESTRICTED_REGION_READ_BUFFER_SIZE, (void *)&prestrict_region_dump_read_buffer);
      if (error != BL_ERR_NONE)
      {
        break;
      }
      size_left = curr_sec_size;
      partition_offset = curr_partition_offset;
      curr_sec_size = 0;
      while (size_left!=0)
      {
        /* Determine write size */
        if (size_left > RESTRICTED_REGION_READ_BUFFER_SIZE)
        {
          write_size = RESTRICTED_REGION_READ_BUFFER_SIZE;
        }
        else
        {
          write_size = size_left;
        }

        /* Copy over data to temporary buffer */
        error = dload_mem_debug_copy_restricted_region(prestrict_region_dump_read_buffer, curr_sec_base_addr, write_size);
        if (error != BL_ERR_NONE)
        {
          break;
        }

        status = boot_ramdump_media_if_write(media_if, (void*)prestrict_region_dump_read_buffer, partition_offset, (void*)&write_size);
        curr_sec_size += write_size;
        if (status != BL_ERR_NONE)
          break;
        curr_sec_base_addr  += write_size;
        partition_offset += write_size;
        size_left -= write_size;
      }

      if (prestrict_region_dump_read_buffer!=NULL)
        error = mem_if->free(prestrict_region_dump_read_buffer);

      if (error != BL_ERR_NONE)
      {
        break;
      }
      prestrict_region_dump_read_buffer = NULL;
    } while (0);
  }
  else
  {
    status = boot_ramdump_media_if_write(media_if, (void*)(uintnt)curr_sec_base_addr, curr_partition_offset, (void*)&curr_sec_size);
  }

  /* Update the actual size and section count we have dumped in overall header */
  raw_dump_header.dump_size += curr_sec_size;
  raw_dump_header.sections_count++;

  if (status == BL_ERR_NONE)
  {
    /* Now section data has been written*/
    /* update the validility flag of the section header */
    raw_dump_section_header_table[curr_partition_index].validity_flag |= RAM_DUMP_VALID_MASK;

    /* Update free space and offset */
    curr_partition_offset += curr_sec_size;
  }
  else
  {
    /* There is not enough space left */
    raw_dump_section_header_table[curr_partition_index].validity_flag |= RAM_DUMP_INSUFFICIENT_STORAGE_MASK;

    /* Update the section size as the size we can dump */
    raw_dump_section_header_table[curr_partition_index].section_size = curr_sec_size;

    /* Update section headers to indicate insufficient storage of current section*/
    dump_section_headers(media_if);
  }

  /* Update the overall header and section table headers */
  dump_overall_headers(media_if);
  dump_section_headers(media_if);

  curr_partition_index++;

  return status;
}

/*===========================================================================

**  Function :  boot_ram_dump_header_init

** ==========================================================================
*/
/*!
*
* @brief
*  Initialize the ram dump header
*
* @par Dependencies
*   dload_mem_debug_init needs to be called
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type boot_ram_dump_header_init(boot_handle config_context_handle, struct boot_raw_partition_dump_section_header **section_header_table)
{
  uint8 ram_dump_signature[] = RAM_DUMP_HEADER_SIGNATURE;
  boot_memory_mgr_if_type *mem_if = NULL;
  bl_error_boot_type status = BL_ERR_NONE;

  do
  {
    
    if(config_context_handle == NULL || section_header_table == NULL)
    {
      status = BL_ERROR_GROUP_RAMDUMP | BL_ERR_INVALID_PARAMETER;
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }
    if(mem_if == NULL)
    {
      status = BL_ERROR_GROUP_RAMDUMP | BL_ERR_INTERFACE_FAILURE;
      break;
    }


    status = mem_if->malloc(dload_mem_debug_num_ent() * sizeof(struct boot_raw_partition_dump_section_header), (void *)section_header_table);
    if(status != BL_ERR_NONE)
    {
      break;
    }
    if(*section_header_table == NULL)
    {
      status = BL_ERROR_GROUP_RAMDUMP | BL_ERR_MEMORY_ALLOC_FAIL;
      break;
    }

    /* Clear the raw ram dump header structures */
    memset(&raw_dump_header, 0x0, sizeof(raw_dump_header));
    memset((void *)(*section_header_table), 0x0, sizeof(struct boot_raw_partition_dump_section_header) * dload_mem_debug_num_ent());

    /* Initialize the header signature and version number */
    memcpy(&raw_dump_header.signature, &ram_dump_signature, sizeof(ram_dump_signature));
    raw_dump_header.version = RAM_DUMP_HEADER_VER;

    /* Set the total dump size required and initialize section count to 0*/
    raw_dump_header.total_dump_size_required = get_raw_ram_dump_required_size();

    /* Set the section count to 0 */
    raw_dump_header.sections_count = 0;

  }while(FALSE);

  return status;
}

/*===========================================================================

**  Function :  boot_ram_dump_header_deinit

** ==========================================================================
*/
/*!
*
* @brief
*  Initialize the ram dump header
*
* @par Dependencies
*   dload_mem_debug_init needs to be called
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type boot_ram_dump_header_deinit(boot_handle config_context_handle, struct boot_raw_partition_dump_section_header *section_header_table)
{
  boot_memory_mgr_if_type *mem_if = NULL;
  bl_error_boot_type status = BL_ERR_NONE;

  do
  {
  
    if(config_context_handle == NULL || section_header_table == NULL)
    {
      status = BL_ERROR_GROUP_RAMDUMP | BL_ERR_INVALID_PARAMETER;
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }
    if(mem_if == NULL)
    {
      status = BL_ERROR_GROUP_RAMDUMP | BL_ERR_INTERFACE_FAILURE;
      break;
    }


    status = mem_if->free(section_header_table);
    if(status != BL_ERR_NONE)
    {
      return status;
    }

  }while(FALSE);

  return status;
}

/*===========================================================================

**  Function :  boot_check_raw_partition

** ==========================================================================
*/
/*!
*
* @brief
*  Initialize the ram dump header
*
* @par Dependencies
*   dload_mem_debug_init needs to be called
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

bl_error_boot_type boot_check_raw_partition(boot_handle config_context_handle, boot_media_interface_if_type *media_if)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_handle media_handle = NULL;

  do
  {
    status = media_if->open(config_context_handle, &media_handle);
    if (status != BL_ERR_NONE)
    {
      DL_LOG("MediaIf Open Fail");
      break;
    }

    if ( media_handle != NULL)
      status = media_if->close(media_handle);

    if (status != BL_ERR_NONE)
    {
      DL_LOG("MediaIf close Fail");
      break;
    }
  } while (FALSE);

  return status;
}

/*===========================================================================

**  Function :  rd_raw_format_init

** ==========================================================================
*/
/*!
*
* @brief
*  Initialize the ram dump header
*
* @par Dependencies
*   dload_mem_debug_init needs to be called
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

bl_error_boot_type rd_raw_format_init (boot_handle media_if)
{
  /* Only perform ram dump if uefi dump cookie is set AND memory debug is allowed */
  if ((boot_shared_imem_cookie_ptr != NULL) &&
      (boot_shared_imem_cookie_ptr->uefi_ram_dump_magic == BOOT_RAW_RAM_DUMP_MAGIC_NUM) &&
      dload_mem_debug_supported())
  {
    DL_LOG("Raw Partition Dump");
    return BL_ERR_NONE;
  }

  return BL_ERR_RD_UNSUPPORTED_MODE;
}

/*===========================================================================

**  Function :  rd_raw_format_open

** ==========================================================================
*/
/*!
*
* @brief
*  Initialize the ram dump header
*
* @par Dependencies
*   dload_mem_debug_init needs to be called
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type rd_raw_format_open (boot_handle  media_if)
{
  bl_error_boot_type status = BL_ERR_NONE;
  uint32 headers_required_size = 0;
  boot_visual_indicator_if_type *visual_indicator_if=NULL;

  do
  {
    status = boot_config_context_set_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PARTITION_ID, &ram_dump_partition_id);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_check_raw_partition (CONFIG_CONTEXT_CRT_HANDLE, media_if);
    if (status != BL_ERR_NONE)
    {
      DL_LOG("There is no raw partiton");
      status = BL_ERROR_GROUP_RAMDUMP|BL_ERROR_OPEN_GPT_PARTITION_FAIL;
      break;
    }


    headers_required_size = DUMP_HEADER_SIZE + (SECTION_HEADER_SIZE * dload_mem_debug_num_ent());

    /* Initialize the header */
    status = boot_ram_dump_header_init(CONFIG_CONTEXT_CRT_HANDLE, &raw_dump_section_header_table);
    if(status != BL_ERR_NONE)
    {
      DL_LOG("RD:dump header init err");
      break;
    }

    /* Write a fresh copy of overall header first to indicate new ram dump */
    status = dump_overall_headers(media_if);
    if (status == BL_ERR_NONE)
    {
      status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_VISUAL_INDICATOR_INTERFACE, (void **)&visual_indicator_if);
      if (status == BL_ERR_NONE)
      {
        visual_indicator_if->toggle_led_init();
      }

      /* We can at least dump all the headers */
      raw_dump_header.dump_size = headers_required_size;

      /* Write a fresh copy of all the section headers to indicate new ram dump*/
      status = dump_section_headers(media_if);
      if (status != BL_ERR_NONE)
      {
        /* There is not enough space to store the section headers.  Set the insufficent storage bit */
        raw_dump_header.dump_size = DUMP_HEADER_SIZE;
        raw_dump_header.validity_flag |= RAM_DUMP_INSUFFICIENT_STORAGE_MASK;
      }
    }

    /* We start writing right after all the headers */
    curr_partition_offset = DUMP_HEADER_SIZE + (SECTION_HEADER_SIZE * dload_mem_debug_num_ent());
    curr_partition_index = 0;

  }while(FALSE);

  return status;
}


/*===========================================================================

**  Function :  rd_raw_format_close

** ==========================================================================
*/
/*!
*
* @brief
*  Initialize the ram dump header
*
* @par Dependencies
*   dload_mem_debug_init needs to be called
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

bl_error_boot_type rd_raw_format_close (boot_handle media_if)
{
  bl_error_boot_type status = BL_ERR_NONE;

  do
  {
    if (curr_partition_index == dload_mem_debug_num_ent())
    {
      /* If all sections finished successully set header to valid */
      raw_dump_header.validity_flag |= RAM_DUMP_VALID_MASK;
      status = BL_ERR_NONE;
    }
    else
    {
      /* if it returns false we know there's not enough space*/
      raw_dump_header.validity_flag |= RAM_DUMP_INSUFFICIENT_STORAGE_MASK;
      status = BL_ERR_RAM_DUMP_FAIL;
    }

    /* Now dump is finished, update the overall header */
    dump_overall_headers(media_if);

    if(boot_ram_dump_header_deinit(CONFIG_CONTEXT_CRT_HANDLE, raw_dump_section_header_table) != BL_ERR_NONE)
    {
      DL_LOG("RD:section header tbl deinit err");
    }

    /* At this point we either finished saving the dump or there is insufficent storage space , reset the device */
    DL_LOG("+---------------+");
    DL_LOG("| RAW Dump done |");
    DL_LOG("+---------------+");
  }while(FALSE);

  return status;
}


/*===========================================================================

**  Function :  rd_raw_format_deinit

** ==========================================================================
*/
/*!
*
* @brief
*  Initialize the ram dump header
*
* @par Dependencies
*   dload_mem_debug_init needs to be called
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

bl_error_boot_type rd_raw_format_deinit (boot_handle media_if)
{
  return BL_ERR_NONE;
}

/*===========================================================================

**  Function :  rd_raw_format_get_interface

** ==========================================================================
*/
/*!
*
* @brief
*  Initialize the ram dump header
*
* @par Dependencies
*   dload_mem_debug_init needs to be called
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/

bl_error_boot_type rd_raw_format_get_interface(void *format_interface_if)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if (format_interface_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INVALID_PARAMETER);
  }

  ((ramdump_format_if_type *)format_interface_if)->init   = rd_raw_format_init;
  ((ramdump_format_if_type *)format_interface_if)->open   = rd_raw_format_open;
  ((ramdump_format_if_type *)format_interface_if)->write  = rd_raw_format_write;
  ((ramdump_format_if_type *)format_interface_if)->close  = rd_raw_format_close;
  ((ramdump_format_if_type *)format_interface_if)->deinit = rd_raw_format_deinit;

  return status;
}

