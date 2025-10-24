/*===========================================================================

                         Boot HFAT format interface

GENERAL DESCRIPTION
  This feature file contains definitions  for  HFAT format

Copyright 2021-2022 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when       who             what, where, why
--------   ---         --------------------------------------------------
05/23/22   rama        Changes for dynamically allocation section_header_table
02/22/21   vk          Initial revision

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>
#include <stdio.h>
#include <fs_errno.h>
#include "errno.h"
#include "boot_dload_debug.h"
#include "boot_extern_efs_interface.h"
#include "boot_shared_imem_cookie.h"
#include "boot_raw_partition_ramdump.h"
#include "boot_target.h"
#include "boot_ramdump_wrapper_apis.h"
#include <boot_reset_if.h>
#include <boot_visual_indication_if.h>
#include <boot_pmic_if.h>
#include <boot_config_context.h>
#include <boot_edk2_cache_if.h>
#include <ramdump_format_if.h>
#include <boot_coldplug_if.h>
#include <boot_media_types.h>

/* Max number of cumulative dumps supported */
#define MAXDUMPS 100
#define MAX_SIZE_FOLDER_STRING 5 /* foldernames range from 1-100, needed for same qsnprintf */

#define MAX_FILE_NAME 256
#define SD_DUMP_HEADER_NAME "rawdump.bin"
#define INVALID_FILE_HANDLE -1
#define SECTOR_SIZE 512

typedef struct boot_ramdump_errlog_data_type
{
   int err_no; /* EFS error returned by efs routines */
   char filename[MAX_FILE_NAME]; /* File in which error has occured */

} boot_ramdump_errlog_data_type;


/* Buffer to store filenames */
static char cookiefilepath[MAX_FILE_NAME];
static char cookiefilename[MAX_FILE_NAME];
static char foldername[MAX_FILE_NAME];
static char foldernumber[MAX_FILE_NAME];

static  uint32 err_count = 0;
static  uint32 memregion_index = 0;
static boot_ramdump_errlog_data_type boot_sd_rd_errdata;

/* 512 Bytes buffer if the base address is 0*/
static uint8 sector_buf[SECTOR_SIZE];

/* GUID for sdcard dump parition */
static struct coldplug_guid sd_dump_partition_id = { 0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }};

/* GUID for NVMe FAT parition */
static struct coldplug_guid nvme_dump_partition_id = { 0xC12A7328, 0xF81F, 0x11D2, { 0xBA, 0x4B, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B }};

/*=========================================================================

                       FUNCTION DEFINITIONS

=========================================================================*/

/*===========================================================================

**  Function :  boot_ramdump_reset

** ==========================================================================
*/
/*!
*
* @brief :  This routine checks for the reset cookie file on sd card and resets
*  the target if its found. This is done to prevent device from continuing to
*  bootup in dload mode after saving ramdumps to SD card
*
* @param[in]
*  None
*
* @par Dependencies:
*  Must be called after efs_boot_initialize.
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
static bl_error_boot_type boot_ramdump_reset( void )
{
  int32 fs_handle = INVALID_FILE_HANDLE;
  bl_error_boot_type return_status = BL_ERR_COOKIE_FILE_NOT_FOUND;
  boot_edk2_cache_if_type *edk2_cache_if = NULL;
  uint32 str_size = 0;

  str_size = strlcpy(cookiefilename, cookiefilepath, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT);

  str_size = strlcat(cookiefilename, "rtcookie.txt", MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  fs_handle = boot_efs_open(cookiefilename, O_RDONLY);

  /* Reset target if Cookie file exists.*/
  if (!(fs_handle < 0))
  {
    /*File exists. Close reset cookie file handle */
    boot_efs_close(fs_handle);

    /* If cache is on, some data might still be in the cache and not
    written to memory. So flush the cache before causing a watchdog reset */
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_EDK2_CACHE_INTERFACE, (void**)&edk2_cache_if);
    if (return_status != BL_ERR_NONE || edk2_cache_if == NULL)
    {
      return return_status;
    }

    return_status = BL_ERR_RAMDUMP_COLLECTED_REBOOT;
  }
  
  return return_status;
}


/*===========================================================================

**  Function :  boot_efs_write_file

** ==========================================================================
*/
/*!
*
* @brief : Helper function to write certain size of data to a given file
*          boot_sd_rd_errdata.err_no will be set if there's an error
*
* @param[in]
*  None
*
* @par Dependencies:
*  Must be called after efs_boot_initialize.
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
static void boot_efs_write_file(int32 fs_handle, uint8 *buf_addr, uint32 size)
{
  int32 tbytes_written;
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_visual_indicator_if_type *visual_indicator_if=NULL;

  while (size > 0)
  {
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_VISUAL_INDICATOR_INTERFACE, (void **)&visual_indicator_if);
    if (return_status == BL_ERR_NONE)
    {
      visual_indicator_if->toggle_led();
    }

    tbytes_written = boot_efs_write(fs_handle, buf_addr, size);
    if (tbytes_written < 0)
    {
      /* Break on any EFS write error */
      boot_sd_rd_errdata.err_no = boot_efs_errno;
      if (boot_sd_rd_errdata.err_no == ENOSPC)
        DL_LOG("FAT partition write failed, due to no space left on FAT partition ");
      else
        DL_LOG("FAT partition write failed! ERR CODE:0x%x", boot_sd_rd_errdata.err_no);
      break;
    }
    size -= tbytes_written;
    buf_addr += tbytes_written;
  }
}

/*===========================================================================

**  Function :  find_next_available_index

** ==========================================================================
*/
/*!
*
* @brief
*    This routine analyzes the integer incremented folder names in the root
*   directory of the SD device, and returns the value of the next available
*   folder.
*
*   When no available indexes are left available, "0" is returned as an error
*
* @par Dependencies
*     SDCC Hw and EFS needs to be initialised
*
* @retval
*   int32 next_avail_index
*
* @par Side Effects
*   None
*
*/
static uint32 find_next_available_index( void )
{
  uint32 next_avail_index = 0;
  uint32 i, str_size = 0;
  EFSDIR *dir_ptr = NULL;

  for (i = 1; i <= MAXDUMPS; i++)
  {
    snprintf(foldernumber, MAX_SIZE_FOLDER_STRING, "%lu/", (uintnt)i);

    str_size = strlcpy(foldername, cookiefilepath, MAX_FILE_NAME);
    BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

    str_size = strlcat (foldername, foldernumber, MAX_FILE_NAME);
    BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

    /* Attempt to open integer digit named folder to determine
       current presence.  Break's are placed such that if efs
       error occurs, we stop attempting to create a folder, and
       error value is returned. */
    dir_ptr = boot_efs_opendir (foldername);

    /* If the folder doesn't exist, create it */
    if (dir_ptr == NULL)
    {
      /* 0666:Provide read/write permissions for all users */
      if (boot_efs_mkdir(foldername, 0666) == 0)
      {
        next_avail_index = i;
      }
      break;
    }
    /* Else, if it already exists, close it and check the next */
    else
    {
      if (boot_efs_closedir (dir_ptr) != 0)
      {
        break;
      }
    }
  }
  return next_avail_index;
}

static int
boot_create_errfile (char *filename)
{
  int ret = 0;
  char err_filename[MAX_FILE_NAME];
  int32  fs_handle = INVALID_FILE_HANDLE;
  uint32 str_size = 0;

  memset (err_filename, 0, MAX_FILE_NAME);
  err_filename[(MAX_FILE_NAME-1)]='\0';

  str_size = strlcpy (err_filename, cookiefilepath, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  str_size = strlcpy(err_filename, foldername, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  str_size = strlcat (err_filename, filename, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  /* 0666:Provide write/execute permissions for User,group and others */
  fs_handle = boot_efs_open(err_filename, O_WRONLY|O_CREAT|O_TRUNC, 0666);
  if (fs_handle >= 0)
  {
    ret = boot_efs_close(fs_handle);
  }
  else
  {
    DL_LOG("Error creating file %s", err_filename);
    ret = -1;
  }

  return ret;
}

static int
boot_delete_errfile (char *filename)
{
  char err_filename[MAX_FILE_NAME];
  uint32 str_size = 0;

  memset (err_filename, 0, MAX_FILE_NAME);
  err_filename[(MAX_FILE_NAME-1)]='\0';

  str_size = strlcpy (err_filename, cookiefilepath, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  str_size = strlcpy(err_filename, foldername, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  str_size = strlcat (err_filename, filename, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  return boot_efs_unlink(err_filename);
}

static int
boot_update_errfile (char *filename, char *current_err_file)
{
  int ret = 0;
  char err_filename[MAX_FILE_NAME];
  uint32 error_info_size;
  int32  fs_handle = INVALID_FILE_HANDLE;
  uint32 str_size = 0;

  memset (err_filename, 0, MAX_FILE_NAME);
  err_filename[(MAX_FILE_NAME-1)]='\0';

  str_size = strlcpy (err_filename, cookiefilepath, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  str_size = strlcpy(err_filename, foldername, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  str_size = strlcat (err_filename, filename, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  /* 0666:Provide write/execute permissions for User,group and others */
  fs_handle = boot_efs_open(err_filename, O_WRONLY, 0666);
  if (fs_handle < 0)
  {
    DL_LOG("Error creating file %s", err_filename);
    ret = -1;
  }

  /*generate error file name + newline */
  if (boot_sd_rd_errdata.err_no == ENOSPC)
    str_size = snprintf(boot_sd_rd_errdata.filename, MAX_FILE_NAME, "%s write failed due to no space left on SD card\n", current_err_file);
  else
    str_size = snprintf(boot_sd_rd_errdata.filename, MAX_FILE_NAME, "%s write failed! Errcode %d\n", current_err_file, boot_sd_rd_errdata.err_no);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  error_info_size = sizeof(boot_sd_rd_errdata.err_no) + str_size;

  /* write the error number and error file name to error log */
  if (fs_handle != INVALID_FILE_HANDLE)
  {
    boot_efs_lseek(fs_handle, 0, SEEK_END);
    boot_efs_write_file(fs_handle, (void *)&boot_sd_rd_errdata, error_info_size);
    boot_efs_close(fs_handle);
  }

  return ret;
}

/*===========================================================================

**  Function :  rd_hfat_format_write

** ==========================================================================
*/
/*!
*
* @brief
*    This routine reads the memory regions and writes to the respective files
*   in the SD card.  It checks the SD card for space availability first, and
*   without deleting any previous dumps, saves the new dumps under a new,
*   numerically indexed and named folder.
*
* @par Dependencies
*     SDCC Hw and EFS needs to be initialised
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type rd_hfat_format_write (boot_handle raw_handle, char *filename, void *buffer, uintnt size)
{

  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_visual_indicator_if_type *visual_indicator_if=NULL;
  boot_memory_mgr_if_type *mem_if = NULL;
  bl_error_boot_type error = BL_ERR_NONE;

  char filepath[MAX_FILE_NAME];
  int32  fs_handle =  INVALID_FILE_HANDLE;
  uint32 str_size;
  uint64 baseaddr = 0, length = 0;
  uint32 size_left = 0, write_size = 0;
  uint8 * prestrict_region_dump_read_buffer = NULL;

  memset (&filepath, 0, MAX_FILE_NAME);
  filepath[(MAX_FILE_NAME-1)]='\0';

  str_size = strlcpy(filepath, foldername, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  str_size = strlcat(filepath, filename, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT );

  /* 0666:Provide write/execute permissions for User,group and others */
  fs_handle = boot_efs_open (filepath, O_WRONLY|O_CREAT|O_TRUNC, 0666);
  boot_sd_rd_errdata.err_no = ENOERR;

  baseaddr = (uint64)buffer;
  length = (uint64)size;

  DL_LOG("start addr:0x%016llx size:0x%016llx file: %s", baseaddr, length, filepath);

  /* On error, continue to try next file */
  if (INVALID_FILE_HANDLE != fs_handle)
  {
    if (dload_mem_debug_is_restricted_addr(baseaddr, length))
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
        size_left = length;
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
          error = dload_mem_debug_copy_restricted_region(prestrict_region_dump_read_buffer, baseaddr, write_size);
          if (error != BL_ERR_NONE)
          {
            break;
          }

          if (boot_sd_rd_errdata.err_no == ENOERR)
          {
            boot_efs_write_file(fs_handle, prestrict_region_dump_read_buffer, write_size);
            baseaddr  += write_size;
            size_left -= write_size;
          }
          else
          {
            break;
          }
        }

        // Free temp buffer
        if (prestrict_region_dump_read_buffer != NULL)
        {
          error = mem_if->free(prestrict_region_dump_read_buffer);
        }
        if (error != BL_ERR_NONE)
        {
          break;
        }
        prestrict_region_dump_read_buffer = NULL;

      } while (0);
    }
    else
    {
      /* If the Base address of the Ram address is '0'  copy  512Bytes into local buffer
        and pass the  local buffer to the EFS to write into SD card. EFS can't handle data
        writes for Null Pointer */
      if (baseaddr == 0)
      {
        /* Copy the initial 512Bytes (SDCC Sector size)  in temporary buffer */
        memcpy(sector_buf, (void *)(uintnt)baseaddr, SECTOR_SIZE);

        /* Flush temp buffer to file  */
        boot_efs_write_file(fs_handle, sector_buf, SECTOR_SIZE);

        baseaddr += SECTOR_SIZE;
        length -=SECTOR_SIZE;
      }

      /* Dump the rest of this memory region data to same file */
      if (boot_sd_rd_errdata.err_no == ENOERR)
      {
        boot_efs_write_file(fs_handle, (void *) (uintnt)(baseaddr), length);
      }
    }
  }
  boot_efs_close(fs_handle);

  if (boot_sd_rd_errdata.err_no != ENOERR)
  {
    err_count++;
    DL_LOG("failed");

    /*if there is a write error, delete the partial file */
    boot_efs_unlink(filepath);

    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_VISUAL_INDICATOR_INTERFACE, (void **)&visual_indicator_if);
    if (return_status == BL_ERR_NONE)
    {
      visual_indicator_if->enable_led(RAM_DUMP_LED, TRUE);
    }

    boot_update_errfile("errfile.txt", filepath);
  }
  else
  {
    DL_LOG("done");
  }

  memregion_index++;

  return BL_ERR_NONE;
} /* boot_process_sd_dumps */

/*===========================================================================

**  Function :  boot_ram_dump_check_rdcookie

** ==========================================================================
*/
/*!
*
* @brief
*   This routine checks whether file rdcookie.txt exists and records
* the directory path to cookiefilepath.
*
* @param[in]
*   path Pointer to the searching directory.
*
* @par Dependencies:
*
* @retval
*   int Handler for the rdcookie.txt file.
*
* @par Side Effects
*   Set static variable cookiefilepath.
*
*/
static int boot_ram_dump_check_rdcookie(const char *path)
{
  uint32 str_size = 0;
  int fd;

  str_size = strlcpy(cookiefilepath, path, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT);

  str_size = strlcpy(cookiefilename, path, MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT);

  str_size = strlcat(cookiefilename, "rdcookie.txt", MAX_FILE_NAME);
  BL_VERIFY((str_size < MAX_FILE_NAME), BL_ERR_INVALID_FILE_NAME|BL_ERROR_GROUP_BOOT);

  fd = boot_efs_open(cookiefilename, O_RDONLY);

  if (fd >= 0)
  {
    boot_efs_close(fd);
  }

  return fd;
}

/*===========================================================================

**  Function :  rd_hfat_format_init

** ==========================================================================
*/
/*!
*
* @brief
*   This routine checks whether file rdcookie.txt exists and records
* the directory path to cookiefilepath.
*
* @param[in]
*   path Pointer to the searching directory.
*
* @par Dependencies:
*
* @retval
*   int Handler for the rdcookie.txt file.
*
* @par Side Effects
*   Set static variable cookiefilepath.
*
*/

bl_error_boot_type rd_hfat_format_init (boot_handle media_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_visual_indicator_if_type *visual_indicator_if=NULL;
  boot_coldplug_if_type *coldplug_if = NULL;
  boot_media_type boot_device;
  int dev_loc;
  enum coldplug_device_type dev_type;
  struct coldplug_guid *partition_id;
  char mount_path[] = "fs_mnt";

  return_status = boot_config_context_get_value (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_BOOT_DEVICE, (void *)&boot_device);
  if (return_status != BL_ERR_NONE)
  {
    return return_status;
  }


  memset (&foldername, 0, MAX_FILE_NAME);
  memset (&cookiefilepath, 0, MAX_FILE_NAME);

  /* ensure string arrays delimited correctly */
  foldername[(MAX_FILE_NAME-1)]='\0';
  cookiefilepath[(MAX_FILE_NAME-1)]='\0';

  DL_LOG("HFAT Dump Init");

  /* Initialize the LED handling logic */
  return_status = boot_config_context_get_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_VISUAL_INDICATOR_INTERFACE, (void **)&visual_indicator_if);
  if (return_status == BL_ERR_NONE)
  {
    visual_indicator_if->toggle_led_init();
  }

  boot_efs_boot_initialize();

  /* Poll the coldplug device */
  return_status = boot_config_context_get_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_COLDPLUG_INTERFACE, (void **)&coldplug_if);
  if (return_status != BL_ERR_NONE)
  {
    return return_status;
  }

  if(boot_device == NVME_FLASH)
  {
    DL_LOG("NVMe FAT Partition Dump Init");
    dev_loc = 1;
    dev_type = COLDPLUG_DEVICE_NVME;
    partition_id = &nvme_dump_partition_id;
  }
  else
  {
    DL_LOG("SD Dump Init");
    dev_loc = 0;
    dev_type = COLDPLUG_DEVICE_SD;
    partition_id = &sd_dump_partition_id;
    if (coldplug_if->open_device(dev_type, dev_loc) != COLDPLUG_RESULT_SUCCESS)
    {
      return BL_ERR_RD_UNSUPPORTED_MODE;
    }
  }

  boot_fs_boot_mount(dev_type, dev_loc, partition_id, mount_path);

  /* Return if cookie file doesn't exit.*/
  if ((boot_ram_dump_check_rdcookie(SD_RAM_DUMP_PATH) < 0)  &&
      (boot_ram_dump_check_rdcookie(SD_PATH) < 0))
  {
    return BL_ERR_RD_UNSUPPORTED_MODE;
  }

  return BL_ERR_NONE;
}

/*===========================================================================

**  Function :  rd_hfat_format_open

** ==========================================================================
*/
/*!
*
* @brief
*   This routine checks whether file rdcookie.txt exists and records
* the directory path to cookiefilepath.
*
* @param[in]
*   path Pointer to the searching directory.
*
* @par Dependencies:
*
* @retval
*   int Handler for the rdcookie.txt file.
*
* @par Side Effects
*   Set static variable cookiefilepath.
*
*/
bl_error_boot_type rd_hfat_format_open (boot_handle  raw_handle)
{
  int ret = 0;
  uint32 cur_dump_index = 0;

  /* Reset global variables */
  err_count = 0;
  memregion_index = 0;


  /* if folder could not be created, or maximum number of dumps has been met */
  cur_dump_index = find_next_available_index();
  if (cur_dump_index == 0)
  {
    boot_create_errfile("errmax.txt");
    DL_LOG("Max FAT partition dump");
    return BL_ERR_RD_UNSUPPORTED_MODE;
  }

  ret = boot_create_errfile("errfile.txt");
  if (ret < 0)
  {
    DL_LOG("Failed to create errfile.txt");
    return BL_ERR_RD_UNSUPPORTED_MODE;
  }

  return BL_ERR_NONE;
}

/*===========================================================================

**  Function :  rd_hfat_format_close

** ==========================================================================
*/
/*!
*
* @brief
*   This routine checks whether file rdcookie.txt exists and records
* the directory path to cookiefilepath.
*
* @param[in]
*   path Pointer to the searching directory.
*
* @par Dependencies:
*
* @retval
*   int Handler for the rdcookie.txt file.
*
* @par Side Effects
*   Set static variable cookiefilepath.
*
*/
bl_error_boot_type rd_hfat_format_close (boot_handle raw_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_visual_indicator_if_type *visual_indicator_if = NULL;
  char mount_path[] = "fs_mnt";

  /*At the end of dump loop we check for error */
  if (err_count == 0)
  {
    /* If no error occured during the Ramdump delete the error file */
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_VISUAL_INDICATOR_INTERFACE, (void **)&visual_indicator_if);
    if (return_status != BL_ERR_NONE)
    {
      visual_indicator_if->enable_led(RAM_DUMP_LED, TRUE);
    }

    boot_delete_errfile("errfile.txt");
    DL_LOG("No error, errfile.txt deleted");

    DL_LOG("+----------------+");
    DL_LOG("| HFAT Dump done |");
    DL_LOG("+----------------+");
  }
  else
  {
    DL_LOG("Failed count: %d", err_count);
  }

  /* reset target if reset cookie present rtcookie.txt */
  return_status = boot_ramdump_reset();
  if(return_status != BL_ERR_RAMDUMP_COLLECTED_REBOOT)
  {
    /* At the end of sd card ram dump, if we are in raw ram dump mode, reset the device so we don't enter sahara */
    if ((boot_shared_imem_cookie_ptr != NULL) &&
        (boot_shared_imem_cookie_ptr->uefi_ram_dump_magic == BOOT_RAW_RAM_DUMP_MAGIC_NUM))
    {
      return_status = BL_ERR_RAMDUMP_COLLECTED_WARM_REBOOT;
    }
  }


  /* umount the coldplug device after operation done */
  boot_efs_umount(mount_path);


  return return_status;
}

/*===========================================================================

**  Function :  rd_hfat_format_deinit

** ==========================================================================
*/
/*!
*
* @brief
*   This routine checks whether file rdcookie.txt exists and records
* the directory path to cookiefilepath.
*
* @param[in]
*   path Pointer to the searching directory.
*
* @par Dependencies:
*
* @retval
*   int Handler for the rdcookie.txt file.
*
* @par Side Effects
*   Set static variable cookiefilepath.
*
*/
bl_error_boot_type rd_hfat_format_deinit (boot_handle media_if)
{
  return BL_ERR_NONE;
}

/*===========================================================================

**  Function :  rd_hfat_format_get_interface

** ==========================================================================
*/
/*!
*
* @brief
*   This routine checks whether file rdcookie.txt exists and records
* the directory path to cookiefilepath.
*
* @param[in]
*   path Pointer to the searching directory.
*
* @par Dependencies:
*
* @retval
*   int Handler for the rdcookie.txt file.
*
* @par Side Effects
*   Set static variable cookiefilepath.
*
*/
bl_error_boot_type rd_hfat_format_get_interface(void *format_interface_if)
{
  bl_error_boot_type error = BL_ERR_NONE;

  if (format_interface_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_INVALID_PARAMETER);
  }

  ((ramdump_format_if_type *)format_interface_if)->init   = rd_hfat_format_init;
  ((ramdump_format_if_type *)format_interface_if)->open   = rd_hfat_format_open;
  ((ramdump_format_if_type *)format_interface_if)->write  = rd_hfat_format_write;
  ((ramdump_format_if_type *)format_interface_if)->close  = rd_hfat_format_close;
  ((ramdump_format_if_type *)format_interface_if)->deinit = rd_hfat_format_deinit;

  return error;
}

