/**
 * @file dtb_loader.c
 * @brief
 * Source file for XBL loading of DTB files.
 *
 * Copyright 2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
 *
 */

/*==========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who        what, where, why
--------   ---        ---------------------------------------------------------
05/04/22   tmt        Initial creation of file, pulling common code out of sbl1_config.c

===========================================================================*/

/*==========================================================================
                             INCLUDE FILES
===========================================================================*/
#include <stdio.h>
#include <limits.h>
#include <boot_error_if.h>
#include <boot_logger.h>
#include <boot_framework.h>
#include <boot_config_context.h>
#include <boot_chipinfo_if.h>
#include <boot_platforminfo_if.h>
#include <XBLConfig.h>
#include "DTBExtnLib.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

/* These names need to agree with create_xbl_config.json */
#define S_DTB_NAME "pre-ddr-soc"    // S_ short for SRAM
#define D_DTB_NAME "soc"            // D_ short for DRAM

#define S_OVERLAY_NAME "pre-ddr-overlay"
#define D_OVERLAY_NAME "overlay"

#define Log_BUF_SIZE 80

typedef enum
{
  DTB_LOADER_PRE_DDR,         /* Pre-DDR load request */
  DTB_LOADER_POST_DDR,        /* Post-DDR load request */
  DTB_LOADER_MAX
} dtb_load_request;

/*==========================================================================
        Function to load DTB from XblConfig
===========================================================================*/
static bl_error_boot_type boot_dtb_load(boot_handle config_context_handle, dtb_load_request pre_or_post)
{

  // DTBExtnLib overhead
  int retValue = 0;
  void *fdt_handle = NULL;

  // System overhead
  xblconfig_status_type xcfg_return;
  bl_error_boot_type status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if = NULL;

  // chipinfo data collection
  ChipInfoIdType cID = 0;
  ChipInfoVersionType cVersion = 0;
  ChipInfoFamilyType cFamily = 0;
  uint16 ci_version = 0;
  uint64 chipinfo=0LL;
  boot_chipinfo_if_type *chipinfo_if = NULL;

  // platforminfo data collection
  DalPlatformInfoPlatformType pType = 0;
  uint32 pSubtype = 0;
  uint32 pVersion = 0;
  uint16 pi_version = 0;
  uint64 platforminfo=0LL;
  boot_platforminfo_if_type *platforminfo_if = NULL;

  // DTBO API parameters
  char *name_starts_with = S_DTB_NAME;
  char *oname_starts_with = S_OVERLAY_NAME;
  uint32 x_handle;        /* XBLConfig Handle */
  uint32 x_size;          /* Size of data referenced by handle */
  void  *x_buffer = NULL; /* Buffer for data referenced by handle */
  cfg_dtbo_state_type state = CFG_GET_INITIALIZED; /* client provides state var to DTBO */
  void *primary_blob = NULL,      /* DTB, base of merge */
  *merge_blob = NULL,        /* Merged DTB, output of merge */
  *overlay_blob = NULL,      /* Overlay DTB, new overlay to merge into base */
  *dtb_blob = NULL;          /* Always points to current, useable DTB */

  uint32 dtb_blob_size,      /* Size of current, useable DTB */
  new_size;                  /* Size of merged DTB after overlay */

  // Error Message Buffer
  char log_buf[Log_BUF_SIZE];

  do
  {
    /* Acquire Memory Interface */
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (BL_ERR_NONE != status)
      break;
    if (NULL == mem_if)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Acquire ChipInfo Interface */
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_CHIPINFO_INTERFACE, (void **)&chipinfo_if);
    if (BL_ERR_NONE != status)
      break;
    if (NULL == chipinfo_if)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Acqure ChipInfo Data */
    status = chipinfo_if->get_chipinfo_data(&cID, &cVersion, &cFamily);
    if (BL_ERR_NONE == status)
    {
      ci_version = cVersion >> 16;
      ci_version = (ci_version<<8)|(cVersion & 0x00FF);
      xcfg_return = xblconfig_create_chipinfo((uint16)cFamily, (uint16)cID, ci_version, &chipinfo);
      if (XBLCONFIG_SUCCESS != xcfg_return)
      {
        snprintf(log_buf, Log_BUF_SIZE, "xcfg_chipinfo.err[%x]", xcfg_return);
        boot_log_message(log_buf);
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_CHIPINFO_FAIL);
        break;
      }
    }
    else
      break;

    if (DTB_LOADER_POST_DDR == pre_or_post)
    {
      /* Acqure PlatformInfo Interface */
      status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_PLATFORMINFO_INTERFACE, (void **)&platforminfo_if);
      if (status != BL_ERR_NONE)
        break;
      if (NULL == platforminfo_if)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_INTERFACE_FAILURE);
        break;
      }

      /* Acqure PlatformInfo Data */
      status = platforminfo_if->get_platforminfo_data(&pType, &pSubtype, &pVersion);
      if (BL_ERR_NONE == status)
      {
        pi_version = pVersion >> 16;
        pi_version = (pi_version<<8)|(pVersion & 0x00FF);
        xcfg_return = xblconfig_create_platforminfo((uint8)pType, pi_version, (uint8)pSubtype, 0, &platforminfo);
        if (XBLCONFIG_SUCCESS != xcfg_return)
        {
          snprintf(log_buf, Log_BUF_SIZE, "xcfg_platinfo.err[%x]", xcfg_return);
          boot_log_message(log_buf);
          status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_PLATFORMINFO_FAIL);
          break;
        }
      }
      else
        break;

      /* Adjust name_starts_with parameter */
      name_starts_with = D_DTB_NAME;
      oname_starts_with = D_OVERLAY_NAME;
    }

    /* Preliminaries are out of the way */
    /* Step 1: find chip family dtb */
    xcfg_return = cfg_item_config_open_first_dtb(chipinfo, platforminfo, name_starts_with, &x_handle, &x_size);
    if (XBLCONFIG_SUCCESS != xcfg_return)
    {
      snprintf(log_buf, Log_BUF_SIZE, "cfg_item_config_open_first_dtb[%s] returned[%x]", name_starts_with, xcfg_return);
      boot_log_message(log_buf);
      status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, XBLCONFIG_CHIPFAMILY_DTB_NOTFOUND);
      break;
    }

    /* Allocate Buffer for First DTB */
    status = mem_if->malloc(x_size, &x_buffer);
    if (BL_ERR_NONE != status)
    {
      xblconfig_close(x_handle);
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, status);
      break;
    }

    /* Read First DTB into local buffer */
    xcfg_return = xblconfig_read(x_handle, 0, x_size, x_buffer);
    xblconfig_close(x_handle);
    if (XBLCONFIG_SUCCESS != xcfg_return)
    {
      status = mem_if->free(x_buffer);
      if (BL_ERR_NONE != status)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
        break;
      }
      x_buffer = NULL;
      status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_XCFG_READ_FAIL);
      break;
    }

    /* dtb_blob initialized to SoC.dtb loaded as base DTB */
    dtb_blob = x_buffer;        /* Only malloc buffer at this point */
    x_buffer = NULL;
    dtb_blob_size = x_size;

    /* Match available dtbo files: SoC and then Platform */
    for (;;)
    {
      xcfg_return = cfg_item_config_open_next_dtbo(chipinfo, platforminfo, oname_starts_with, &x_handle, &x_size, &state);
      if (XBLCONFIG_SUCCESS != xcfg_return)
      {
        if (XBLCONFIG_DTBO_NOTFOUND == xcfg_return)
          break;          /* we are done, no more overlay files */
        else
        {
          snprintf(log_buf, Log_BUF_SIZE, "DTBO: %s* dtbo can't be found[%x]!", oname_starts_with, xcfg_return);
          boot_log_message(log_buf);
          status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, xcfg_return);
          goto err_exit;
        }
      }

      /* DTBO found, allocate buffer to read it into */
      status = mem_if->malloc(x_size, (void **) &x_buffer);
      if (BL_ERR_NONE != status)
      {
        xblconfig_close(x_handle);
        status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, status);
        goto err_exit;
      }

      /* Read DTBO into local buffer */
      xcfg_return = xblconfig_read(x_handle, 0, x_size, x_buffer);
      xblconfig_close(x_handle);
      if (XBLCONFIG_SUCCESS != xcfg_return)
      {
        status = mem_if->free(x_buffer);
        if (BL_ERR_NONE != status)
        {
          status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
          goto err_exit;
        }
        x_buffer = NULL;
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_XCFG_READ_FAIL);
        goto err_exit;
      }

      /* Setup Overlay/Merge Operation */
      primary_blob = dtb_blob;        /* primary_blob = current base blob */
      overlay_blob = x_buffer;        /* overlay_blob was just read into memory */
      if (dtb_blob_size > UINT_MAX - x_size)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_IMG_SIZE_TOO_BIG);
        goto err_exit;
      }
      else
        new_size = dtb_blob_size + x_size;

      dtb_blob = x_buffer = NULL;     /* buffers are handed off, NULL for correct error handling */

      /* Allocate buffer for merge */
      status = mem_if->malloc(new_size, &merge_blob);
      if (BL_ERR_NONE != status)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, status);
        goto err_exit;
      }
      /* Perform Overlay/Merge Operation */
      retValue = fdt_merge_overlay(primary_blob, overlay_blob, merge_blob, new_size);
      if (0 != retValue)
      {
        snprintf(log_buf, Log_BUF_SIZE, "fdt merge overlay failed:returned [%d]", retValue);
        boot_log_message(log_buf);
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, XBLCONFIG_DTBO_MERGE_FAILED);
        goto err_exit;
      }

      /* Cleanup after Overlay/Merge, prep for next iteration */
      status = mem_if->free(primary_blob);
      if (BL_ERR_NONE != status)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
        goto err_exit;
      }
      primary_blob = NULL;

      status = mem_if->free(overlay_blob);
      if (BL_ERR_NONE != status)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
        goto err_exit;
      }
      overlay_blob = NULL;

      dtb_blob = merge_blob;
      merge_blob = NULL;
      dtb_blob_size = new_size;
    }

    /* We should have a valid DTB to register with library */
    /* If DEFAULT DTB buffer valid, must free it first */
    retValue = fdt_get_blob_handle(&fdt_handle, DEFAULT_BLOB_ID);
    if (0 == retValue)
    {
      if (NULL != fdt_handle)
      {
        status = mem_if->free(fdt_handle);
        if (BL_ERR_NONE != status)
        {
          status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
          goto err_exit;
        }
      }
      fdt_handle = NULL;
    }

    /* Register new DTB with library */
    retValue = fdt_set_blob_handle(dtb_blob, DEFAULT_BLOB_ID);
    if (0 != retValue)
    {
      snprintf(log_buf, Log_BUF_SIZE, "fdt_set_blob_handle got an error [%d]", retValue);
      boot_log_message(log_buf);
      status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_FDT_SET_BLOB_FAIL);
      goto err_exit;
    }

    /* skip error checks on good exit */
    status = BL_ERR_NONE;
    break;

err_exit:
    /* Prevent memory leaks: dtb_blob, primary_blob, merge_blob, overlay_blob */
    if (NULL != dtb_blob)
    {
      if (mem_if->free(dtb_blob)!= BL_ERR_NONE)
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
    }
    if (NULL != primary_blob)
    {
      if (mem_if->free(primary_blob)!= BL_ERR_NONE)
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
    }
    if (NULL != merge_blob)
    {
      if (mem_if->free(merge_blob)!= BL_ERR_NONE)
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
    }
    if (NULL != overlay_blob)
    {
      if (mem_if->free(overlay_blob)!= BL_ERR_NONE)
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
    }
  } while (FALSE);

  snprintf(log_buf, Log_BUF_SIZE, "DTB %s Found: [%s][%llx][%llx]", (status ? "Not" : ""), name_starts_with, chipinfo, platforminfo);
  boot_log_message(log_buf);

  return status;
}

bl_error_boot_type boot_pre_ddr_dtb_load(boot_handle config_context_handle)
{
  return boot_dtb_load(config_context_handle, DTB_LOADER_PRE_DDR);
}

bl_error_boot_type boot_post_ddr_dtb_load(boot_handle config_context_handle)
{
  return boot_dtb_load(config_context_handle, DTB_LOADER_POST_DDR);
}
