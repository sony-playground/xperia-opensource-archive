/*=============================================================================

                        RAMDUMP TABLE TARGET SDX

GENERAL DESCRIPTION
  This module defines the memory debug information to be sent to host

Copyright 2020-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Library/RamdumpTableTargetLib/SDX/ramdump_table_target_sdx.c#1 $

when       who       what, where, why
--------   ---       ----------------------------------------------------------
05/25/22   rama      Update target dependent ramdump entries to 50
05/18/22   rama      Move dal_if to mem_if
07/23/21   rama      Added ddr_dt_log_region to the dump table.
06/25/21   rhy  	 Added clear_second_pass_complete in ramdump_table_target_unrecoverable_error_handler
02/21/21   vk        Move to passing dload cookie to helper functions
02/04/21   rhy       Added ramdump_table_target_unrecoverable_error_handler
03/25/20   rhy       Intial creation

=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <stdio.h>
#include "boot_comdef.h"
#include "boot_sbl_if.h"
#include "boot_logger_if.h"
#include <boot_config_context.h>
#include "boot_error_if.h"
#include "boot_target.h"
#include "boot_ramdump_if.h"
#include "boot_crashdump.h"
#include "boot_pmic_if.h"
#include "pm_pbus.h"
#include "boot_ramdump_table.h"
#include "boot_memory_mgr_if.h"
#include "boot_ddr_info_if.h"
#include "boot_edk2_cache_if.h"
#include "boot_reset_if.h"
#include <HALhwio.h>
#include <HALbootHWIO.h>
#include <boot_minidump.h>

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
#define TARGET_DEPENDENT_RAMDUMP_ENTRIES     50

/* Region base address for dynamic RAM dump entries */
typedef struct
{
  /* For adding ramdump table entries */
  boot_handle ramdump_table_handle_ptr;

  /* Region: AOSS */
  uintnt      *aoss_cc_fsm_status_register;
  uintnt      *aoss_cc_fsm_ctrl_register;

  /* Region: Reset Status Register */
  uintnt      *reset_status_register;

  /* Region: PMIC */
  uint64                  *pmic_power_on;
  pm_pbus_data_type       *pbus_log_data;
  pm_pon_reason_events_data_type *pon_events_log;
  
} ramdump_table_sdx_handle;

static bl_error_boot_type _ramdump_add_aoss_cc_regs(boot_handle, ramdump_table_sdx_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_reset_status_reg(boot_handle, ramdump_table_sdx_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_pmic_info(boot_handle, ramdump_table_sdx_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_ddr_regions (boot_handle, ramdump_table_sdx_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_ddr_dt_log_regions(boot_handle, ramdump_table_sdx_handle*, uint32 dload_cookie);


/*=============================================================================

                              FUNCTION DEFINITIONS

=============================================================================*/

/*=========================================================================

**  Function :  _init_handle

** ==========================================================================
*/
/*!
*
* @brief
*   Malloc ramdump_table_type and cmm script handle.
*
*/
static bl_error_boot_type _init_handle(const boot_handle config_context_handle,
                                       ramdump_table_sdx_handle *handle,
                                       boot_memory_mgr_if_type *mem_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  if (config_context_handle == NULL || handle == NULL || mem_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  do
  {
    handle->ramdump_table_handle_ptr = NULL;

    /* Allocate all the required RAMDUMP regions with Uncache */

    /* Region: AOSS */
    return_status = mem_if->malloc_uncached(sizeof(uintnt), (void **)&(handle->aoss_cc_fsm_status_register));
    if ((return_status != BL_ERR_NONE) || ((handle->aoss_cc_fsm_status_register) == NULL))
    {
      break;
    }

    return_status = mem_if->malloc_uncached(sizeof(uintnt), (void **)&(handle->aoss_cc_fsm_ctrl_register));
    if ((return_status != BL_ERR_NONE) || ((handle->aoss_cc_fsm_ctrl_register) == NULL))
    {
      break;
    }

    /* Region: Reset Status Register */
    return_status = mem_if->malloc_uncached(sizeof(uintnt), (void **)&(handle->reset_status_register));
    if ((return_status != BL_ERR_NONE) || ((handle->reset_status_register) == NULL))
    {
      break;
    }

    /* Region: PMIC */
    return_status = mem_if->malloc_uncached(sizeof(uint64), (void **)&(handle->pmic_power_on));
    if ((return_status != BL_ERR_NONE) || ((handle->pmic_power_on) == NULL))
    {
      break;
    }

    return_status = mem_if->malloc_uncached(sizeof(pm_pon_reason_events_data_type),
                                       (void **)&(handle->pon_events_log));
    if ((return_status != BL_ERR_NONE) || ((handle->pon_events_log) == NULL))
    {
      break;
    }

    return_status = mem_if->malloc_uncached(sizeof(pm_pbus_data_type), (void **)&(handle->pbus_log_data));
    if ((return_status != BL_ERR_NONE) || ((handle->pbus_log_data) == NULL))
    {
      break;
    }
  } while (FALSE);

  return return_status;
}

/*=========================================================================

**  Function :  _deinit_handle

** ==========================================================================
*/
/*!
*
* @brief
*   free the mem debug handle.
*
*/
static bl_error_boot_type _deinit_handle(const boot_handle config_context_handle,
    ramdump_table_sdx_handle *handle,
    boot_memory_mgr_if_type *mem_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  if (config_context_handle == NULL || handle == NULL || mem_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  do
  {
    handle->ramdump_table_handle_ptr = NULL;

    if (handle->aoss_cc_fsm_status_register)
    {
      /* Region: AOSS */
      return_status = mem_if->free((void *)(handle->aoss_cc_fsm_status_register));
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }
    handle->aoss_cc_fsm_status_register = NULL;

    if (handle->aoss_cc_fsm_ctrl_register)
    {
      return_status = mem_if->free((void *)(handle->aoss_cc_fsm_ctrl_register));
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }
    handle->aoss_cc_fsm_ctrl_register = NULL;

    if (handle->reset_status_register)
    {
      /* Region: Reset Status Register */
      return_status = mem_if->free((void *)(handle->reset_status_register));
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }
    handle->reset_status_register = NULL;

    if (handle->pmic_power_on)
    {
      /* Region: PMIC */
      return_status = mem_if->free((void *)(handle->pmic_power_on));
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }
    handle->pmic_power_on = NULL;

    if (handle->pon_events_log)
    {
      return_status = mem_if->free((void *)(handle->pon_events_log));
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }
    handle->pon_events_log = NULL;

    if (handle->pbus_log_data)
    {
      return_status = mem_if->free((void *)handle->pbus_log_data);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }
    handle->pbus_log_data = NULL;

  } while (FALSE);

  return return_status;
}
/*===========================================================================

**  Function :  ramdump_table_target_init

** ==========================================================================
*/
/*!
*
* @brief
*   This function populates ramdump_table_info with its SDX specific regions
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
bl_error_boot_type ramdump_table_target_init
(
  boot_handle config_context_handle,
  boot_handle ramdump_table_handle_ptr,
  boot_handle *handle_ptr
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_ramdump_if_type *ramdump_if =  NULL;
  boot_memory_mgr_if_type *mem_if =  NULL;
  ramdump_table_sdx_handle *handle = NULL;
  uint32 dload_cookie = 0;

  if (config_context_handle == NULL || ramdump_table_handle_ptr == NULL
      || handle_ptr == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  do
  {
    /* Allocate handle */
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Malloc mem debug handle */
    return_status = mem_if->malloc(sizeof(ramdump_table_sdx_handle), (void **)&handle);
    if ((return_status != BL_ERR_NONE) || (handle == NULL))
    {
      break;
    }


    return_status = _init_handle(config_context_handle, handle, mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Store ramdump table handle ptr in sdx handle */
    handle->ramdump_table_handle_ptr = ramdump_table_handle_ptr;
    /* Check Mode */
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_INTERFACE, (void **)&ramdump_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (ramdump_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    dload_cookie= ramdump_if->get_saved_cookie();
    /* Add AOSS region */
    return_status = _ramdump_add_aoss_cc_regs(config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Add Reset Status Register region */
    return_status = _ramdump_add_reset_status_reg(config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Add PMIC region */
    return_status = _ramdump_add_pmic_info(config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Add DDR region */
    return_status = _ramdump_add_ddr_regions (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Add DDR DT LOG regions */
    return_status = _ramdump_add_ddr_dt_log_regions (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    *handle_ptr = (void*)handle;

  } while (FALSE);

  return return_status;
}


/*===========================================================================

**  Function :  ramdump_table_target_get_entries_count

** ==========================================================================
*/
/*!
*
* @brief
*   This function return the number of entries in ramdump for the specific target.
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
bl_error_boot_type ramdump_table_target_get_entries_count
(
  uint32 *num_of_entries
)
{
  if (num_of_entries == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  *num_of_entries = TARGET_DEPENDENT_RAMDUMP_ENTRIES;

  return BL_ERR_NONE;
}


static bl_error_boot_type _ramdump_add_aoss_cc_regs
(
  boot_handle config_context_handle,
  ramdump_table_sdx_handle* handle,
  uint32 dload_cookie
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  if (config_context_handle == NULL || handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  *(handle->aoss_cc_fsm_status_register) = HWIO_AOSS_CC_RESET_FSM_STATUS_IN;//HWIO_IN(AOSS_CC_RESET_FSM_STATUS);
  *(handle->aoss_cc_fsm_ctrl_register) = HWIO_AOSS_CC_RESET_FSM_CTRL_IN;//HWIO_IN(AOSS_CC_RESET_FSM_CTRL);

  if(dload_cookie & SBL_DLOAD_MODE_BIT_MASK)
  {
    return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                            RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                            (uintnt)(handle->aoss_cc_fsm_status_register),
                                            sizeof(uintnt),
                                            "Aoss rst fsm stat",
                                            "FSM_STS.BIN");
    if (return_status != BL_ERR_NONE)
    {
      return return_status;
    }

    return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                            RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                            (uintnt)(handle->aoss_cc_fsm_ctrl_register),
                                            sizeof(uintnt),
                                            "Aoss rst fsm ctrl",
                                            "FSM_CTRL.BIN");
  }
  if(dload_cookie & SBL_MINIDUMP_MODE_BIT_MASK)
  {
    if(!(boot_add_minidump_region(MD_SS_BOOT, "FSM_STS", (uint64)(handle->aoss_cc_fsm_status_register), (uint64)(sizeof(*handle->aoss_cc_fsm_status_register)))))
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
    }

    if(!(boot_add_minidump_region(MD_SS_BOOT, "FSM_CTRL", (uint64)(handle->aoss_cc_fsm_ctrl_register), (uint64)(sizeof(*handle->aoss_cc_fsm_ctrl_register)))))
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
    }
  }
  return return_status;
}


static bl_error_boot_type _ramdump_add_reset_status_reg
(
  boot_handle config_context_handle,
  ramdump_table_sdx_handle* handle,
  uint32 dload_cookie
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  char *rst_stat_filename = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;

  if (config_context_handle == NULL || handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }
  do
  {
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Malloc memory for rst_stat_filename */
    return_status = mem_if->malloc(DLOAD_DEBUG_STRLEN_BYTES, (void **)&rst_stat_filename);
    if ((return_status != BL_ERR_NONE) || rst_stat_filename == NULL)
    {
      break;
    }


    return_status = boot_config_context_get_value(config_context_handle,
                    CONFIG_CONTEXT_AOSS_RESET_STATUS_REGISTER,
                    (uint32 *)&(handle->reset_status_register));
    if (return_status != BL_ERR_NONE)
    {
      break;
    }


    if (dload_cookie & SBL_DLOAD_MODE_BIT_MASK)
    {
      snprintf (rst_stat_filename, DLOAD_DEBUG_STRLEN_BYTES, "RST_STAT.BIN");
      return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                            RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                            (uintnt)&(handle->reset_status_register),
                                            sizeof(uintnt),
                                            "Reset Status Region",
                                            rst_stat_filename);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }

    if (dload_cookie & SBL_MINIDUMP_MODE_BIT_MASK)
    {
      snprintf (rst_stat_filename, DLOAD_DEBUG_STRLEN_BYTES, "MD_RST_STAT.BIN");
      if(!(boot_add_minidump_region(MD_SS_BOOT, rst_stat_filename, (uint64)(handle->reset_status_register), (uint64)(sizeof(*handle->reset_status_register)))))
      {
        return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
      }
    }

    if (rst_stat_filename)
    {
      /* free rst_stat_filename */
      return_status = mem_if->free((void *)rst_stat_filename);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      rst_stat_filename = NULL;
    }
  } while (FALSE);

  return return_status;
}


static bl_error_boot_type _ramdump_add_pmic_info
(
  boot_handle config_context_handle,
  ramdump_table_sdx_handle* handle,
  uint32 dload_cookie
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  char *pmic_pon_filename = NULL, *pmic_hist_filename = NULL, *pmic_log_data_filename = NULL;
  boot_pmic_if_type *pmic_if = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;


  if (config_context_handle == NULL || handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }


  do
  {
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Malloc memory for pmic_pon_filename */
    return_status = mem_if->malloc(DLOAD_DEBUG_STRLEN_BYTES, (void **)&pmic_pon_filename);
    if ((return_status != BL_ERR_NONE) || pmic_pon_filename == NULL)
    {
      break;
    }

    /* Malloc memory for pmic_hist_filename */
    return_status = mem_if->malloc(DLOAD_DEBUG_STRLEN_BYTES, (void **)&pmic_hist_filename);
    if ((return_status != BL_ERR_NONE) || pmic_hist_filename == NULL)
    {
      break;
    }

    /* Malloc memory for pmic_log_data_filename */
    return_status = mem_if->malloc(DLOAD_DEBUG_STRLEN_BYTES, (void **)&pmic_log_data_filename);
    if ((return_status != BL_ERR_NONE) || pmic_log_data_filename == NULL)
    {
      break;
    }


    return_status = boot_config_context_get_ptr(config_context_handle,
                    CONFIG_CONTEXT_PMIC_INTERFACE,
                    (void **)&pmic_if);

    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    if (pmic_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Get power on reason for pmic device 0 */
    pmic_if->pm_dev_get_power_on_reason(0, handle->pmic_power_on);
    pmic_if->pm_app_pon_get_all_pon_events(handle->pon_events_log);
    //pmic_if->pm_pbus_logger(0, handle->pbus_log_data);

    if (dload_cookie & SBL_DLOAD_MODE_BIT_MASK)
    {
      snprintf (pmic_pon_filename, DLOAD_DEBUG_STRLEN_BYTES, "PMIC_PON.BIN");
      snprintf (pmic_hist_filename, DLOAD_DEBUG_STRLEN_BYTES, "PMON_HIS.BIN");
      snprintf (pmic_log_data_filename, DLOAD_DEBUG_STRLEN_BYTES, "PBUS_LOG.BIN");

      return_status  = ramdump_table_add_entry(handle->ramdump_table_handle_ptr, RAMDUMP_TABLE_OPTIONAL_DEF_SAVE, (uintnt)(handle->pmic_power_on), (uintnt) sizeof(uintnt), "Pmic PON stat", pmic_pon_filename);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr, RAMDUMP_TABLE_OPTIONAL_DEF_SAVE, (uintnt)(handle->pon_events_log), (uintnt) sizeof(uintnt), "PM PON HIST ", pmic_hist_filename);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr, RAMDUMP_TABLE_OPTIONAL_DEF_SAVE, (uintnt)(handle->pbus_log_data), (uintnt)(sizeof(pm_pbus_data_type)), "Pmic PBUS log dump", pmic_log_data_filename);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }


    if (dload_cookie & SBL_MINIDUMP_MODE_BIT_MASK)
    {
      snprintf (pmic_pon_filename, DLOAD_DEBUG_STRLEN_BYTES, "PMIC_PON");
      snprintf (pmic_hist_filename, DLOAD_DEBUG_STRLEN_BYTES, "PMON_HIS");
      snprintf (pmic_log_data_filename, DLOAD_DEBUG_STRLEN_BYTES, "PBUS_LOG");

      if(!(boot_add_minidump_region(MD_SS_BOOT, pmic_pon_filename, (uint64)(handle->pmic_power_on), (uint64)(sizeof(*handle->pmic_power_on)))))
      {
        return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
      }

      if(!(boot_add_minidump_region(MD_SS_BOOT, pmic_hist_filename, (uint64)(handle->pon_events_log), (uint64)(sizeof(*handle->pon_events_log)))))
      {
        return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
      }

      if(!(boot_add_minidump_region(MD_SS_BOOT, pmic_log_data_filename, (uint64)(handle->pbus_log_data), (uint64)(sizeof(*handle->pbus_log_data)))))
      {
        return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
      }
    }

    if (pmic_pon_filename)
    {
      /* free pmic_pon_filename */
      return_status = mem_if->free((void *)pmic_pon_filename);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      pmic_pon_filename = NULL;
    }

    if (pmic_hist_filename)
    {
      /* free pmic_hist_filename */
      return_status = mem_if->free((void *)pmic_hist_filename);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      pmic_hist_filename = NULL;
    }

    if (pmic_log_data_filename)
    {
      /* free pmic_log_data_filename */
      return_status = mem_if->free((void *)pmic_log_data_filename);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      pmic_log_data_filename = NULL;
    }
  } while (FALSE);

  return return_status;
}


/*===========================================================================

**  Function :  ramdump_table_target_unrecoverable_error_handler

** ==========================================================================
*/
/*!
*
* @brief
*   Function to handle unexpected error during RAMDUMP collection
*
* @par Dependencies
*   None
*
* @retval
*   bl_error_boot_type
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type ramdump_table_target_unrecoverable_error_handler
(
)
{
  bl_error_boot_type return_status =  BL_ERR_NONE;
  boot_ramdump_if_type *ramdump_if =  NULL;
  boot_reset_if_type *reset_if     =  NULL;

  do
  {
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_RAMDUMP_INTERFACE, (void **)&ramdump_if);
    if (return_status != BL_ERR_NONE)
    {
      return return_status;
    }

    if (ramdump_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_RESET_INTERFACE, (void **)&reset_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    if (reset_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Set DLOAD cookie */
    ramdump_if->set_dload_cookie();

	/* Clear SECOND_PASS_COMPLETE */
	ramdump_if->clear_second_pass_complete();
	
    /* Force the device to Warm reset */
    reset_if->hw_reset(BOOT_WARM_RESET_TYPE);

    /* The code should not reach here */
  } while (FALSE);

  return return_status;
}

static bl_error_boot_type _ramdump_add_ddr_regions (boot_handle config_context_handle, ramdump_table_sdx_handle* handle, uint32 dload_cookie)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_ddr_info_if_type *di_if =      NULL;
  boot_ddr_device_info_type *available_ddr =  NULL;
  uint32 size, start_addr_cs1 = 0;
  uint32  index_cs1 = 0,  start_addr = 0, size_cs1, index = 0;

  /* If DLOAD mode is not set, do not take full RAM dump */
  if (!(dload_cookie & SBL_DLOAD_MODE_BIT_MASK))
  {
    return BL_ERR_NONE;
  }

  do
  {
    /* Add DDR region */
    return_status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_DDR_INFO_INTERFACE, (void **)&di_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    if (di_if == NULL)
    {
      break;
    }

    available_ddr = di_if->get_ddr_info();
    index = 0;
    while (index < available_ddr->noofddr)
    {
      start_addr = available_ddr->ddr_info[index].cs_addr;
      size = available_ddr->ddr_info[index].ramsize << CONVERT_TO_MB_SHIFT;

      /* Define EBI1 CS0 Memory Region */
      if (start_addr == SIZE_2GB) // query ddr
      {
        return_status = ramdump_table_add_entry (handle->ramdump_table_handle_ptr,
                                                 RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                                 start_addr,
                                                 size,
                                                 " DDR CS0 Memory",
                                                 "DDRCS0.BIN");

        if (return_status != BL_ERR_NONE)
        {
          goto exit;
        }

        /*Check if EBI1 CS1 exists */
        index_cs1 =0;
        while (index_cs1 < available_ddr->noofddr)
        {
          start_addr_cs1 = available_ddr->ddr_info[index_cs1].cs_addr;
          if (start_addr_cs1 == (start_addr + size))
          {
            size_cs1 = available_ddr->ddr_info[index_cs1].ramsize << CONVERT_TO_MB_SHIFT;
            /*Add EBI1 CS1 Region*/
            return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                                    RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                                    start_addr_cs1,
                                                    size_cs1,
                                                    " DDR CS1 Memory ",
                                                    "DDRCS1.BIN");

            if (return_status != BL_ERR_NONE)
            {
              goto exit;
            }

          }
          index_cs1++;
        }
      }
      index++;
    }
  } while (FALSE);

exit:
  return return_status;
}

static bl_error_boot_type _ramdump_add_ddr_dt_log_regions(boot_handle config_context_handle, ramdump_table_sdx_handle* handle, uint32 dload_cookie)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  char* ddr_dt_log_filename = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;

  if (config_context_handle == NULL || handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  do
  {
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    return_status = mem_if->malloc(DLOAD_DEBUG_STRLEN_BYTES, (void **)&ddr_dt_log_filename);
    if ((return_status != BL_ERR_NONE) || ddr_dt_log_filename == NULL)
    {
      break;
    }

    if (dload_cookie & SBL_MINIDUMP_MODE_BIT_MASK)
    {
      snprintf (ddr_dt_log_filename, DLOAD_DEBUG_STRLEN_BYTES, "MD_XBL_LOG.BIN");}

    if (dload_cookie & SBL_DLOAD_MODE_BIT_MASK)
    {
      snprintf (ddr_dt_log_filename, DLOAD_DEBUG_STRLEN_BYTES, "XBL_LOG.BIN");
    }

    return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                            RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                            (uintnt)(XBL_DDR_LOG_REGION_BASE),
                                            (uintnt)(XBL_DDR_LOG_REGION_SIZE),
                                            "XBL LOG reg ",
                                            ddr_dt_log_filename);

  }while(FALSE);

  return return_status;
}

/*===========================================================================

**  Function :  ramdump_table_target_deinit

** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes clocks as needed for this target, as well as sets
*   up the memory regions to be used.
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
bl_error_boot_type ramdump_table_target_deinit
(
  boot_handle config_context_handle,
  boot_handle handle_ptr
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if =  NULL;

  if (config_context_handle == NULL || handle_ptr == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  ramdump_table_sdx_handle *handle = (ramdump_table_sdx_handle *)handle_ptr;

  do
  {
    /* Allocate handle */
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    return_status = _deinit_handle(config_context_handle, handle, mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* free Ramdump table sdx handle */
    return_status = mem_if->free((void *)handle);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

  } while (FALSE);

  return return_status;
}
