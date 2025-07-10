/*
 * Copyright 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

/* @file boot_ramdump.c
 *
 * This module passes the target specific memory debug information
 * to ramdumper.
 */

#ifdef FEATURE_SONY_RAMDUMP

#include "boot_target.h"
#include "boot_shared_imem_cookie.h"
#include "boot_util.h"
#include "boot_extern_efs_interface.h"
#include "boot_dload_debug.h"
#include "boot_logger.h"
#include "boot_ramdump.h"
#include "boot_ramdump_raw_partition.h"
#include "pm_boot.h"
#include "pm_rtc.h"
#include "SpmiBus.h"
#include <string.h>
#include <stdio.h>

#include <boot_ramdump_wrapper_apis.h>
#include <boot_config_context.h>
#include <boot_media_interface_if.h>
#include <boot_visual_indication_if.h>
#include <boot_reset_if.h>
#include <boot_pmic_if.h>
#include <boot_ramdump_table_if.h>

/* GUID for ram dump parition */
extern uint8 raw_dump_partition_id[];

/* GUID for rdimage dump parition */
extern uint8 rdimage_partition_id[];

/* Raw dump header */
struct boot_raw_partition_dump_header boot_raw_dump_header
                                 SECTION(".bss.BOOT_UNCACHED_DDR_ZI_ZONE");

/* Table that stores the raw dump section headers */
struct boot_raw_partition_dump_section_header
                boot_raw_dump_section_header_table[MAX_NUM_REGIONS]
                                 SECTION(".bss.BOOT_UNCACHED_DDR_ZI_ZONE");

/* Number of sections we need to dump */
static uint32 raw_dump_sections_num;

/* Total number of bytes on ram dump partition */
static uint64 partition_size;

/* Pointer points to the partition offset we are going to write data to*/
static uint64 curr_partition_offset;

static struct ramdump_memdesc *memdesc = NULL;
static boot_handle config_context_handle = NULL;

static void boot_raw_ram_dump_error_handler()
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_visual_indicator_if_type *visual_indicator_if=NULL;

  status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_VISUAL_INDICATOR_INTERFACE, (void **)&visual_indicator_if);
  if(status == BL_ERR_NONE)
  {
    /* Turn on LED if there's an write error and enter error handler*/
    visual_indicator_if->enable_led(PM_RGB_SEGMENT_R, TRUE);
  }

  BL_VERIFY(0, BL_ERR_RAM_DUMP_FAIL);
}

static bl_error_boot_type boot_ramdump_media_if_write(void *buf_addr, uint64 offset, uint32 write_size)
{
  bl_error_boot_type status = BL_ERR_NONE, return_status = BL_ERR_NONE;
  boot_media_interface_if_type *media_if = NULL;
  boot_visual_indicator_if_type *visual_indicator_if=NULL;
  boot_handle media_handle;

  uint32 bytes_to_write = 0;
  uint32 total_write_bytes = 0;

  do
  {
    /* First try to find the ram dump parition */
    status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_PARTITION_ID, &raw_dump_partition_id);
    if(status != BL_ERR_NONE)
    {
      DL_LOG("context set Fail, Errcode:0x%x", status);
      return_status = status;
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_BOOT_MEDIA_INTERFACE, (void **)&media_if);
    if(status != BL_ERR_NONE)
    {
      DL_LOG("MediaIf Get Fail, Errcode:0x%x", status);
      return_status = status;
      break;
    }

    if (media_if == NULL)
    {
      DL_LOG("MediaIf Get Fail, Errcode:0x%x", status);
      return_status = status;
      break;
    }

    status = media_if->open(config_context_handle, &media_handle);
    if(status != BL_ERR_NONE)
    {
      DL_LOG("MediaIf Open Fail, Errcode:0x%x", status);
      return_status = status;
      break;
    }

    /* Get the Visual Indicator LED ptr */
    status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_VISUAL_INDICATOR_INTERFACE, (void **)&visual_indicator_if);
    if(status != BL_ERR_NONE)
    {
      DL_LOG("MediaIf Open Fail, Errcode:0x%x", status);
      return_status = status;
      break;
    }

    while(write_size > 0)
    {
      bytes_to_write =  write_size > RAW_DUMP_WRITE_SIZE ? RAW_DUMP_WRITE_SIZE : write_size;
      status = media_if->write(media_handle, buf_addr, offset, bytes_to_write);
      if(status != BL_ERR_NONE)
      {
        DL_LOG("MediaIf Write Fail, Errcode:0x%x", status);
        return_status = status;
        break;
      }
      /*Toggle led in between writes*/
      visual_indicator_if->toggle_led();

      write_size -= bytes_to_write;
      buf_addr = (void *)(uintnt)(uint64)buf_addr + bytes_to_write;
      offset += bytes_to_write;
      total_write_bytes += bytes_to_write;
    }
    if(media_handle!= NULL)
    {
      status = media_if->close(media_handle);
      if(status != BL_ERR_NONE)
      {
        DL_LOG("MediaIf Close Fail, Errcode:0x%x",status);
        return_status = status;
        break;
      }
    }
    if(return_status != BL_ERR_NONE)
    {
      break;
    }
  } while(FALSE);

  return return_status;
}

static void dump_section_headers()
{
  boot_ramdump_media_if_write(boot_raw_dump_section_header_table,
                         RAW_DUMP_HEADER_SIZE,
                         RAW_DUMP_SECTION_HEADER_SIZE * raw_dump_sections_num);
}

static void dump_overall_headers()
{
  boot_ramdump_media_if_write(&boot_raw_dump_header,
                             0, /* header starts at partition offset 0 */
                             RAW_DUMP_HEADER_SIZE);
}

static void boot_ramdump_restricted_region_write(uint64 curr_sec_base_addr,
                         uint64 partition_offset, uint32 curr_sec_size)
{
  boot_memory_mgr_if_type *mem_if = NULL;
  uint8 * prestrict_region_dump_read_buffer = NULL;
  uint64 size_left = 0,write_size = 0;
  bl_error_boot_type status = BL_ERR_NONE;

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = mem_if->malloc(RESTRICTED_REGION_READ_BUFFER_SIZE, (void *)&prestrict_region_dump_read_buffer);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    size_left = curr_sec_size;
    partition_offset = curr_partition_offset;
    curr_sec_size = 0;

    while(size_left != 0)
    {
      write_size = (size_left > RESTRICTED_REGION_READ_BUFFER_SIZE) ?
              RESTRICTED_REGION_READ_BUFFER_SIZE : size_left;
      // Copy over data to temporary buffer
      status = dload_mem_debug_copy_restricted_region(prestrict_region_dump_read_buffer,
                                                     curr_sec_base_addr,
                                                     write_size);
      if(status != BL_ERR_NONE)
      {
        break;
      }

      status = boot_ramdump_media_if_write((void*)prestrict_region_dump_read_buffer,
                                           partition_offset,
                                           write_size);
      curr_sec_size += write_size;
      if(status != BL_ERR_NONE)
        break;
      curr_sec_base_addr  += write_size;
      partition_offset += write_size;
      size_left -= write_size;
    }

    if(prestrict_region_dump_read_buffer!=NULL)
      status = mem_if->free(prestrict_region_dump_read_buffer);

    prestrict_region_dump_read_buffer = NULL;

  } while(0);
}

static boot_boolean boot_process_raw_ram_dump_sections()
{
  uint32 i = 0;
  boot_boolean dump_success = TRUE;
  uint64 curr_sec_size = 0;
  uint64 curr_sec_base_addr = 0;
  uint64 free_space_size = 0;

  /* We start writing right after all the headers */
  curr_partition_offset = RAW_DUMP_HEADER_SIZE +
                    (RAW_DUMP_SECTION_HEADER_SIZE * raw_dump_sections_num);

  /* Initial free space without all the headers */
  free_space_size = partition_size - curr_partition_offset;

 /* Iterate through the sections and process each section*/
  for(; i < raw_dump_sections_num ; i++)
  {
    curr_sec_size =  boot_raw_dump_section_header_table[i].section_size;
    curr_sec_base_addr =  boot_raw_dump_section_header_table[i].phys_addr;

    /* Set the offset in current section's header */
    boot_raw_dump_section_header_table[i].section_offset = curr_partition_offset;

    /* Now section header info is updated,
       we need to write the raw section data to storage */

    if(free_space_size >= curr_sec_size)
    {
      if(dload_mem_debug_is_restricted_addr(curr_sec_base_addr,curr_sec_size))
        boot_ramdump_restricted_region_write(curr_sec_base_addr,
                                  curr_partition_offset,
                                  curr_sec_size);
      else
        boot_ramdump_media_if_write((void*) (uintnt)curr_sec_base_addr,
                                  curr_partition_offset,
                                  curr_sec_size);
      /* Now section data has been written*/
      /* update the validility flag of the section header */
      boot_raw_dump_section_header_table[i].validity_flag |= RAW_DUMP_VALID_MASK;

      /* Update the actual size and section count we have dumped
         in overall header */
      boot_raw_dump_header.dump_size += curr_sec_size;
      boot_raw_dump_header.sections_count++;

      /* Update free space and offset */
      curr_partition_offset += curr_sec_size;
      free_space_size -= curr_sec_size;
    }
    else
    {
      /* There is not enough space left */
      boot_raw_dump_section_header_table[i].validity_flag |=
                                    RAW_DUMP_INSUFFICIENT_STORAGE_MASK;

      /* Update the section size as the size we can dump */
      boot_raw_dump_section_header_table[i].section_size = free_space_size;

      /* Use up all the free space for this section */
      if(dload_mem_debug_is_restricted_addr(curr_sec_base_addr,curr_sec_size))
        boot_ramdump_restricted_region_write(curr_sec_base_addr,
                                  curr_partition_offset,
                                  free_space_size);
      else
        boot_ramdump_media_if_write((void*)(uintnt)curr_sec_base_addr,
                                  curr_partition_offset,
                                  free_space_size);

      /* Update the actual size and section count we have dumped
         in overall header */
      boot_raw_dump_header.dump_size += free_space_size;
      boot_raw_dump_header.sections_count++;

      /* Update section headers to indicate insufficient storage
         of current section*/
      dump_section_headers();

      dump_success = FALSE;

      break;
    }

    /* Update the overall header and section table headers */
    dump_overall_headers();
    dump_section_headers();
  }

  return dump_success;
}

static void boot_process_raw_ram_dump()
{
  uint32 headers_required_size = 0;

  /* Make sure the number of sections we need to dump doesn't exceed
     the max we support */
  if(raw_dump_sections_num > MAX_NUM_REGIONS)
  {
    boot_raw_ram_dump_error_handler();
  }

  headers_required_size = RAW_DUMP_HEADER_SIZE +
                         (RAW_DUMP_SECTION_HEADER_SIZE * raw_dump_sections_num);

  /* Write a fresh copy of overall header first to indicate new ram dump */
  dump_overall_headers();

  if(partition_size > headers_required_size)
  {
    bl_error_boot_type status = BL_ERR_NONE;
    boot_visual_indicator_if_type *visual_indicator_if=NULL;

    /* Init LED for Visual Indication of dump start */
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_VISUAL_INDICATOR_INTERFACE, (void **)&visual_indicator_if);
    if(status == BL_ERR_NONE)
    {
      visual_indicator_if->toggle_led_init();
    }

    /* We can at least dump all the headers */
    boot_raw_dump_header.dump_size = headers_required_size;

    /* Write a fresh copy of all the section headers to indicate new ram dump*/
    dump_section_headers();

    /* Dump each sections */
    boot_process_raw_ram_dump_sections();
  }
  else
  {
    /* There is not enough space to store the section headers */
    boot_raw_dump_header.dump_size = RAW_DUMP_HEADER_SIZE;
  }

  /* Now dump is finished, update the overall header */
  /* update dump header signature to indicate successful dump */
  boot_raw_dump_header.signature = RAW_DUMP_HEADER_SIGNATURE;
  dump_overall_headers();
}

static void boot_ramdump_to_raw_partition(uint8 *partition_id)
{

  char buf[64];

  boot_log_message("boot_ramdump_to_raw_partition, Start");

  /* We can only proceed if this partition can hold at least the header
     and if memory dump is allowed */
  if(partition_size >= sizeof(boot_raw_dump_header))
  {
    /* Process the dump */
    boot_process_raw_ram_dump();
  }

  snprintf(buf, sizeof(buf), "Partition size=%dMB dump size=%dMB",
           partition_size >> CONVERT_TO_MB_SHIFT,
           boot_raw_dump_header.dump_size >> CONVERT_TO_MB_SHIFT);
  boot_log_message(buf);

  boot_log_message("boot_ramdump_to_raw_partition, End");
}

static void boot_raw_dump_add_section(struct ramdump_memdesc_region *region,
                                      uint32 index)
{
  boot_raw_dump_section_header_table[index].phys_addr = region->phys_addr;
  boot_raw_dump_section_header_table[index].section_size = region->size;
  strlcpy((char *)&boot_raw_dump_section_header_table[index].section_name,
          (char *)&region->name, MAX_NAME_LEN);
}

static void boot_raw_dump_header_init(void)
{
  /* Clear the raw ram dump header structures */
  memset(&boot_raw_dump_header, 0x0, sizeof(boot_raw_dump_header));
  memset(&boot_raw_dump_section_header_table[0], 0x0,
          sizeof(boot_raw_dump_section_header_table));

  /* Initialize the header signature and version number */
  boot_raw_dump_header.signature = RAW_DUMP_HEADER_FAIL;
  boot_raw_dump_header.version = RAW_DUMP_HEADER_VER;

  /* Set the total dump size required to an intial value */
  boot_raw_dump_header.dump_size_required =
                RAW_DUMP_HEADER_SIZE + RAW_DUMP_SECTION_HEADER_SIZE;

  /* Set the section count to 0 */
  boot_raw_dump_header.sections_count = 0;
}

static void boot_ramdump_memdesc_init(void)
{
  memdesc = (struct ramdump_memdesc *)RAMDUMP_MEM_DESC_BASE;

  memset(memdesc, 0, RAMDUMP_MEM_DESC_SIZE);
  memdesc->hdr.magic = RAMDUMP_MEM_DESC_MAGIC;
  memdesc->hdr.version = RAMDUMP_MEM_DESC_VERSION;
  memdesc->hdr.num_regions = 0;
}

void boot_ramdump_add_region(struct ramdump_memdesc_region *region)
{
  uint32 offset = sizeof(struct ramdump_memdesc_header) +
               memdesc->hdr.num_regions * sizeof(struct ramdump_memdesc_region);
  uint32 section_index = raw_dump_sections_num;

  /* Do not overflow RAMDUMP_MEM_DESC_SIZE */
  if((offset + sizeof(struct ramdump_memdesc_region)) > RAMDUMP_MEM_DESC_SIZE)
    return;

  /* Check if we need to clone the new region and
     populate the raw section dump headers with necessary info */
  if(region->flags & RAW_PARTITION_DUMP_FLAG)
  {
    raw_dump_sections_num++;
    boot_raw_dump_header.dump_size_required += region->size;
    boot_raw_dump_add_section(region, section_index);
    region->flags |= RAW_DUMP_SECTION_INDEX_FLAG(section_index);
  }

  /* Update the memdesc table and header */
  memcpy((void *)((uintnt)memdesc + offset), region,
             sizeof(struct ramdump_memdesc_region));
  memdesc->hdr.num_regions++;

}

uint64 boot_ramdump_get_hlos_end_addr(void)
{
  struct ramdump_memdesc_region *region;
  int index, hlos_index = -1;
  uint64 hlos_end_addr = 0;

  /* Check if memdesc is initialized */
  if((memdesc == NULL) || (memdesc->hdr.magic != RAMDUMP_MEM_DESC_MAGIC))
  {
    return 0;
  }

  region = memdesc->region;

  /* Look for last Linux memory bank */
  for(index = 0; index < memdesc->hdr.num_regions; index++)
  {
    if(!strcmp((const char *)region[index].name, "vmcore"))
    {
      hlos_index = index;
    }
  }

  if(hlos_index != -1)
  {
    hlos_end_addr = region[hlos_index].phys_addr + region[hlos_index].size;
  }

  return hlos_end_addr;
}

static boolean boot_check_ramdump_fail(void)
{
  uint32 i;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 restart_reason = 0;

  err_flag = pm_pon_get_spare_reg(0, PM_PON_SOFT_SPARE, &restart_reason);
  if (err_flag == PM_ERR_FLAG_SUCCESS && restart_reason)
  {
     /* Skip SPARE[0], use SPARE[7 6 5 4 3 2 1] */
     restart_reason = 0x7F & (restart_reason >> 1);
     for (i = 0; i < RAMDUMP_FAIL_REASON_ARRAY_SIZE; i++)
     {
       if (restart_reason == ramdump_fail_reasons[i])
          return TRUE;
     }
  }

  return FALSE;
}


static boolean boot_check_is_ramdump_reason(void)
{
  uint32 i;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 restart_reason = 0;

  err_flag = pm_pon_get_spare_reg(0, PM_PON_SOFT_SPARE, &restart_reason);
  if (err_flag == PM_ERR_FLAG_SUCCESS && restart_reason)
  {
     /* Skip SPARE[0], use SPARE[7 6 5 4 3 2 1] */
     restart_reason = 0x7F & (restart_reason >> 1);
     for (i = 0; i < RAMDUMP_REASONS_ARRAY_SIZE; i++)
     {
       if (restart_reason == ramdump_reasons[i])
          return TRUE;
     }
  }

  return FALSE;
}


static void boot_ramdump_set_reset_reason(uint8 reset_reason)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 shiftedval = 0;

  shiftedval = reset_reason << 1;
  err_flag = pm_pon_set_spare_reg(0, PM_PON_SOFT_SPARE, shiftedval, 0xFF/*PMIO_PON_SOFT_RB_SPARE_RMSK*/);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
     boot_log_message("boot_set_ramdump_reset_reason fail");
  }
}

static void boot_ramdump_partition_size(uint8 *partition_id)
{
  struct coldplug_handle *chdl;
  int ret;
  uint64 blocks = 0;
  uint32 bytes_per_block = 0;

  chdl = coldplug_open_gpt_partition(COLDPLUG_DEVICE_UFS, 1 /* is_embedded */, (struct coldplug_guid *)partition_id);
  if (NULL == chdl)
  {
    boot_log_message("coldplug partition open failed");
    return;
  }

  ret = coldplug_get_size ((void *)chdl, &bytes_per_block, &blocks);
  if (ret == COLDPLUG_RESULT_SUCCESS)
  {
    DL_LOG("blocks = 0x%x bytes_per_block= 0x%x", blocks, bytes_per_block);
    partition_size = blocks * bytes_per_block;
  }

  ret = coldplug_close_partition (chdl);
  if (ret != COLDPLUG_RESULT_SUCCESS)
  {
    boot_log_message("coldplug partition close failed");
  }

}

boot_boolean boot_is_ramdump_to_rddata_allowed(boot_handle config_context_handle)
{
  boot_boolean debug_allow = FALSE;

  debug_allow = dload_mem_debug_supported();
  if (debug_allow)
  {
    /* Get partition size */
    if(!partition_size)
      boot_ramdump_partition_size(raw_dump_partition_id);

    return partition_size > DUMP_MIN_SIZE;
  }

  return FALSE;
}

void boot_ramdump_init(boot_handle handle)
{
  boot_boolean debug_allow = FALSE;
  boot_boolean ramdump_failed = FALSE;

  boot_log_message("boot_ramdump_init, Start");

  config_context_handle = handle;

  ramdump_failed = boot_check_ramdump_fail();
  debug_allow = dload_mem_debug_supported();

  /* Initilaize the memdescs and ramdump headers*/
  boot_raw_dump_header_init();
  boot_ramdump_memdesc_init();
  boot_ramdump_partition_size(raw_dump_partition_id);

  /* Proceed fulldump if rddata is bigger than ddr and collect DDR sections */
  if(debug_allow && boot_is_ramdump_to_rddata_allowed(config_context_handle))
  {
     if (ramdump_failed)
        boot_ramdump_failed_target_init();
     else
        boot_ramdump_target_init(config_context_handle);
  }
  else
     boot_ramdump_target_secure_init();

  /* Initiate ramdumps to raw partition */
  boot_ramdump_to_raw_partition(raw_dump_partition_id);

  if (!boot_is_ramdump_to_rddata_allowed(config_context_handle))
  {
     /* User Varaint :
      * Set PMIC spare register to CRASH W/O DUMPER(0x48) only for rddata < ddr
      */
     boot_ramdump_set_reset_reason(VENDOR_RREASON_NO_RD_IMAGE);
  }
  else
  {
    /* Userdebug Varaint :
     * Upon any crash, by default it enters xblramdump due to dload mode
     * some early crashes might not have proper ramdump reset reason to
     * enter into ramdump mode, setting it here.
     */
     if (!ramdump_failed && !boot_check_is_ramdump_reason()) {
        boot_ramdump_set_reset_reason(VENDOR_RREASON_CLEAR);
     }
  }

  boot_log_message("boot_ramdump_init, End");
}

#endif /* FEATURE_SONY_RAMDUMP */
