/*=============================================================================

                         RAMDUMP TABLE TARGET SM

GENERAL DESCRIPTION
  This module defines the memory debug information to be sent to host

Copyright 2019-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/

/*=============================================================================
#
#                              EDIT HISTORY FOR MODULE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
#  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Library/RamdumpTableTargetLib/SM/ramdump_table_target_sm.c#1 $
#
#  when       who     what, where, why
#  --------   ---     ----------------------------------------------------------
#  06/10/22   batta   Added support for Slave ramdumps
#  05/28/22   rama    Update target dependent ramdump entries to 50
#  05/27/22   amaji   Enable _ramdump_add_pmic_pm_pbs_pon_reason_history
#  02/09/22   ck      Updated heap names
#  12/16/21   rama    Added logic to copy shared IMEM region to DDR before encrypting
#  10/07/21   rama    Added logic to encrypt shared IMEM for minidumps
#  07/23/21   rama    Added ddr_dt_log_region to dump table
#  07/13/21   zxz     Enable _ramdump_add_pmic_dump_data
#  07/02/21   rama    changes to dump extended ddr logs region
#  06/29/21   yps     optimize code
#  04/20/21   ds      usb pipo fix
#  03/25/21   ds      rst_bin fix and PIMEM dump fix
#  02/11/21   vk      Enable for SM
#  02/04/21   rhy     Added ramdump_table_target_unrecoverable_error_handler
#  05/10/20   ds      move to edk2 arm mmu/cache lib
#  04/20/20   rhy     added AOSS reset status register using Config Context and removed sbl1_hw_get_reset_status()
#  03/26/20   rhy     Initial creation
#
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <stdio.h>
#include <HALhwio.h>
#include <HALbootHWIO.h>
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
#include "boot_ddr_info_if.h"
#include <seclib_defs.h>
#include <boot_seclib_if.h>
#include "boot_ramdump_wrapper_apis.h"
#include "boot_edk2_cache_if.h"
#include "boot_ramdump_if.h"
#include "boot_reset_if.h"
#include <boot_heap.h>
#include <ddr_drivers.h>
#include <boot_coldplug_if.h>
#include <boot_shared_imem_cookie.h>
#include "boot_dload_debug.h"
#include <boot_minidump.h>
#include <boot_memory_mgr_if.h>
#include <boot_slvcom_if.h>
#include <boot_chipinfo_if.h>
#include <boot_xrc_if.h>
#include "ChipInfoDefs.h"
#include <DALSys.h>

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
/* This macro needs to be updated for every new entry added in this target specific file */
#define TARGET_DEPENDENT_RAMDUMP_ENTRIES    50

/* Region base address for dynamic RAM dump entries */
typedef struct
{
  boot_handle ramdump_table_handle_ptr;
  /* For adding ramdump table entries */

  /* Region: AOSS */
  uint32      *aoss_cc_fsm_status_register;
  uint32      *aoss_cc_fsm_ctrl_register;
  uint32      *aoss_cc_reset_debug_enable_register;

  /* Region: Reset Status Register */
  uint32      *reset_status_register;

  /* Region: PMIC */
  uint64                  *pmic_power_on;
  pm_pbus_data_type       *pbus_log_data;
  pm_pon_reason_events_data_type     *pon_events_log;
  pm_pbs_pon_reason_history_data_type *pon_reason_history_ptr;

} ramdump_table_sm_handle;


static bl_error_boot_type _ramdump_add_ipa_mem_regions (boot_handle, ramdump_table_sm_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_pmic_info (boot_handle, ramdump_table_sm_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_pmic_pm_pbs_pon_reason_history(boot_handle, ramdump_table_sm_handle*,uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_pmic_dump_data (boot_handle, ramdump_table_sm_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_shared_imem_region (boot_handle, ramdump_table_sm_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_smem_info_region (boot_handle, ramdump_table_sm_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_reset_status_reg (boot_handle, ramdump_table_sm_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_ddr_training_data (boot_handle, ramdump_table_sm_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_pimem_data( boot_handle, ramdump_table_sm_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_binning_info (boot_handle, ramdump_table_sm_handle*);
static bl_error_boot_type _ramdump_add_aoss_cc_regs (boot_handle, ramdump_table_sm_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_ddr_regions (boot_handle, ramdump_table_sm_handle*, uint32 dload_cookie);
static bl_error_boot_type _ramdump_add_slave_regions (boot_handle, ramdump_table_sm_handle*, uint32 dload_cookie);

static uint8 ddr_partition_data[SCL_DDR_PARTITION_DATA_BUF_SIZE] = {0};

extern uintnt  Image$$STACK$$Base[];
extern uintnt  Image$$STACK$$Length[];
extern uintnt  Image$$RAMDUMP_DATA_RW$$Base[];
extern uintnt  Image$$RAMDUMP_DATA_RW$$Length[];

extern slvcom_handle_type slv_handle;

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
                                       ramdump_table_sm_handle *handle,
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

    if (return_status != BL_ERR_NONE || ((handle->aoss_cc_fsm_status_register) == NULL))
    {
      break;
    }

    return_status = mem_if->malloc_uncached(sizeof(uintnt), (void **)&(handle->aoss_cc_fsm_ctrl_register));

    if ((return_status != BL_ERR_NONE) || ((handle->aoss_cc_fsm_ctrl_register) == NULL))
    {
      break;
    }

    return_status = mem_if->malloc_uncached(sizeof(uintnt), (void **)&(handle->aoss_cc_reset_debug_enable_register));

    if ((return_status != BL_ERR_NONE) || ((handle->aoss_cc_reset_debug_enable_register) == NULL))
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
	
	return_status = mem_if->malloc_uncached(sizeof(pm_pbs_pon_reason_history_data_type), (void **)&(handle->pon_reason_history_ptr));

    if ((return_status != BL_ERR_NONE) || ((handle->pon_reason_history_ptr) == NULL))
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
*   Free the mem debug handle.
*
*/
static bl_error_boot_type _deinit_handle(const boot_handle config_context_handle,
    ramdump_table_sm_handle *handle,
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

    if (handle->aoss_cc_reset_debug_enable_register)
    {
      return_status = mem_if->free((void *)(handle->aoss_cc_reset_debug_enable_register));

      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }
    handle->aoss_cc_reset_debug_enable_register = NULL;


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
	
    if (handle->pon_reason_history_ptr)
    {
      return_status = mem_if->free((void *)handle->pon_reason_history_ptr);

      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }
    handle->pon_reason_history_ptr=NULL;

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
*   This function populates ramdump_table_info with its SM specific regions
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
  boot_memory_mgr_if_type *mem_if = NULL;
  ramdump_table_sm_handle *handle = NULL;
  uint32 dload_cookie = 0;
  ChipInfoIdType chipinfo_id;
  boot_chipinfo_if_type *chipinfo_if = NULL;

  if ( (config_context_handle == NULL) || (ramdump_table_handle_ptr == NULL) || (handle_ptr == NULL) )
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
    return_status = mem_if->malloc(sizeof(ramdump_table_sm_handle), (void **)&handle);
    if ((return_status != BL_ERR_NONE) || (handle == NULL))
    {
      break;
    }


    /* Check Mode */
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_INTERFACE, (void **)&ramdump_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (ramdump_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DAL, BL_ERR_INTERFACE_FAILURE);
      break;
    }



    return_status = _init_handle(config_context_handle, handle, mem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Store ramdump table handle ptr in sdx handle */
    handle->ramdump_table_handle_ptr = ramdump_table_handle_ptr;

    dload_cookie = ramdump_if->get_saved_cookie();

    /* Add SMEM info regions */
    return_status = _ramdump_add_smem_info_region (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Add PMIC region */
    return_status = _ramdump_add_pmic_info (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Add Reset Status Register region */
    return_status = _ramdump_add_reset_status_reg (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    /* Add Shared IMEM region */
    return_status = _ramdump_add_shared_imem_region (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Add IPA region */
    return_status = _ramdump_add_ipa_mem_regions (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Add PMIC region */
    return_status = _ramdump_add_pmic_dump_data (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Add DDR training data */
    return_status = _ramdump_add_ddr_training_data (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
	

#ifdef SCL_pIMEM_BASE    
    /* Add PIMEM region */
    return_status = _ramdump_add_pimem_data (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
#endif

	/* Add PMIC region */
    return_status =  _ramdump_add_pmic_pm_pbs_pon_reason_history(config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
	
    /* Add AOSS region */
    return_status = _ramdump_add_aoss_cc_regs (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Add DDR regions */
    return_status = _ramdump_add_ddr_regions (config_context_handle, handle, dload_cookie);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    /* Get ChipInfo interface */
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_CHIPINFO_INTERFACE, (void **)&chipinfo_if);
    if(return_status != BL_ERR_NONE)
    {
       break;
    }
    /* Get ChipInfo ID */
    return_status = chipinfo_if->get_chip_id(&chipinfo_id);
    if(return_status != BL_ERR_NONE) {
       break;
    }
    /* Add helios ramdump regions */
    if(chipinfo_id == CHIPINFO_ID_SXR_AURORA) {
       return_status = _ramdump_add_slave_regions(config_context_handle, handle, dload_cookie);
    }

    *handle_ptr = (void*)handle;

  } while (FALSE);

  {
   /* TODO: FIXME:flashless sahara dependency */
   static  struct coldplug_guid ram_dump_partition_id = { 0x66C9B323, 0xF7FC, 0x48B6, { 0xBF, 0x96, 0x6F, 0x32, 0xE3, 0x35, 0xA4, 0x28 } };
   return_status = boot_config_context_set_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PARTITION_ID, &ram_dump_partition_id);
   if (return_status != BL_ERR_NONE)
   {
     return return_status;
   }

   return_status = boot_config_context_set_value (config_context_handle, CONFIG_CONTEXT_JUMP_FLAG, FALSE);
   if(return_status != BL_ERR_NONE)
   {
     return return_status;
   }

  }

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
  ramdump_table_sm_handle* handle,
  uint32 dload_cookie
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  if (config_context_handle == NULL || handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  *(handle->aoss_cc_fsm_status_register)         = HWIO_AOSS_CC_RESET_FSM_STATUS_IN;   //HWIO_IN(AOSS_CC_RESET_FSM_STATUS);
  *(handle->aoss_cc_fsm_ctrl_register)           = HWIO_AOSS_CC_RESET_FSM_CTRL_IN;     //HWIO_IN(AOSS_CC_RESET_FSM_CTRL);
  *(handle->aoss_cc_reset_debug_enable_register) = HWIO_AOSS_CC_RESET_DEBUG_ENABLE_IN; //HWIO_IN(AOSS_CC_RESET_DEBUG_ENABLE);

  /* If DLOAD mode is not set, do not add this range */
  if (dload_cookie & SBL_DLOAD_MODE_BIT_MASK)
  {
    return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                            RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                            (uintnt)(handle->aoss_cc_fsm_status_register),
                                            sizeof(*handle->aoss_cc_fsm_status_register),
                                            "Aoss rst fsm stat",
                                            "FSM_STS.BIN");
    if (return_status != BL_ERR_NONE)
    {
      return return_status;
    }

    return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                            RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                            (uintnt)handle->aoss_cc_fsm_ctrl_register,
                                            sizeof(*handle->aoss_cc_fsm_ctrl_register),
                                            "Aoss rst fsm ctrl",
                                            "FSM_CTRL.BIN");
    if (return_status != BL_ERR_NONE)
    {
      return return_status;
    }

    return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                            RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                            (uintnt)handle->aoss_cc_reset_debug_enable_register,
                                            sizeof(*handle->aoss_cc_reset_debug_enable_register),
                                            "Aoss reset debug en",
                                            "DBG_EN.BIN");
    if(return_status != BL_ERR_NONE)
    {
      return return_status;
    }
  }
  if(dload_cookie & SBL_MINIDUMP_MODE_BIT_MASK)
  {
    if(!(boot_add_minidump_region(MD_SS_BOOT, "FSM_STS", (uint64)(handle->aoss_cc_fsm_status_register), sizeof(*handle->aoss_cc_fsm_status_register))))
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
    }

    if(!(boot_add_minidump_region(MD_SS_BOOT, "FSM_CTRL", (uint64)(handle->aoss_cc_fsm_ctrl_register), sizeof(*handle->aoss_cc_fsm_ctrl_register))))
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
    }

    if(!(boot_add_minidump_region(MD_SS_BOOT, "DBG_EN", (uint64)(handle->aoss_cc_reset_debug_enable_register), sizeof(*handle->aoss_cc_reset_debug_enable_register))))
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
    }
  }
  return return_status;
}


static bl_error_boot_type _ramdump_add_reset_status_reg
(
  boot_handle config_context_handle,
  ramdump_table_sm_handle* handle,
  uint32 dload_cookie
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  struct boot_shared_imem_cookie_type *boot_shared_imem_cookie_ptr =
                  (struct boot_shared_imem_cookie_type *)SHARED_IMEM_BOOT_BASE;

  if (config_context_handle == NULL || handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }
  do
  {

    *handle->reset_status_register = boot_shared_imem_cookie_ptr->reset_status_register;

    if (dload_cookie & SBL_DLOAD_MODE_BIT_MASK)
    {
      return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                              RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                              (uintnt)(handle->reset_status_register),
                                              sizeof(*handle->reset_status_register),
                                              "Reset Status Region",
                                              "RST_STAT.BIN");
      if (return_status != BL_ERR_NONE)
      {
        break;
      }
    }

    if (dload_cookie & SBL_MINIDUMP_MODE_BIT_MASK)
    {
      if(!(boot_add_minidump_region(MD_SS_BOOT, "RST_STAT", (uint64)(handle->reset_status_register), sizeof(*handle->reset_status_register))))
      {
        return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
      }
    }

  } while (FALSE);

  return return_status;
}


static bl_error_boot_type _ramdump_add_ipa_mem_regions
(
  boot_handle config_context_handle,
  ramdump_table_sm_handle* handle,
  uint32 dload_cookie
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  ramdump_table_memory_region dump_regions[] = {IPA_MEMORY_REGION_TABLE};
  uint32 index = 0;

  /* If DLOAD mode is not set, do not add this range */
  if (!(dload_cookie & SBL_DLOAD_MODE_BIT_MASK))
  {
    return BL_ERR_NONE;
  }

  while ( dump_regions[index].region_base != 0x0 )
  {
    return_status = ramdump_table_add_entry (handle->ramdump_table_handle_ptr,
                    RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                    (uintnt)dump_regions[index].region_base,
                    (uintnt) dump_regions[index].region_size,
                    dump_regions[index].desc,
                    dump_regions[index].filename);

    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    index++;
  }

  return return_status;
}

static bl_error_boot_type _ramdump_add_shared_imem_region
(
  boot_handle config_context_handle,
  ramdump_table_sm_handle* handle,
  uint32 dload_cookie
)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if = NULL;
  uint8 * shared_imem_dump_buffer_ptr = NULL;

  do
  {
    /* If MINIDUMP mode is not set, do not add this range */
    if (!(dload_cookie & SBL_MINIDUMP_MODE_BIT_MASK))
    {
      status = BL_ERR_NONE;
      break;
    }

    if (config_context_handle == NULL || handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }
    if(mem_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    status = mem_if->malloc(SHARED_IMEM_SIZE, (void **)&shared_imem_dump_buffer_ptr);
    if((status != BL_ERR_NONE) || (shared_imem_dump_buffer_ptr == NULL))
    {
      break;
    }

    memcpy((void *)shared_imem_dump_buffer_ptr, (void *)SHARED_IMEM_BASE, SHARED_IMEM_SIZE);

    if (!(boot_add_minidump_region(MD_SS_BOOT, "SHRDIMEM", (uint64)shared_imem_dump_buffer_ptr, (uint64)SHARED_IMEM_SIZE)))
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
      break;
    }

  }while(FALSE);

  return BL_ERR_NONE;
}

static bl_error_boot_type _ramdump_add_smem_info_region
(
  boot_handle config_context_handle,
  ramdump_table_sm_handle* handle,
  uint32 dload_cookie
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  uint32 *platform_info_build_id = NULL;
  uint32 platform_info_build_id_size = 0;
  uint32 *platform_info_version = NULL;
  uint32 platform_info_version_size = 0;

  if (config_context_handle == NULL || handle == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  platform_info_build_id = smem_get_addr(SMEM_HW_SW_BUILD_ID, &platform_info_build_id_size);
  platform_info_version = smem_get_addr(SMEM_IMAGE_VERSION_TABLE, &platform_info_version_size);

  if (dload_cookie & SBL_DLOAD_MODE_BIT_MASK)
  {

    if(platform_info_build_id != NULL)
    {
      return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                              RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                              (uintnt)platform_info_build_id,
                                              platform_info_build_id_size,
                                              "SMEM info",
                                              "SMEMINFO.BIN");
      if(return_status != BL_ERR_NONE)
      {
        return return_status;
      }
    }
    if(platform_info_version != NULL)
    {
      return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                              RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                              (uintnt)platform_info_version,
                                              platform_info_version_size,
                                              "SMEM info",
                                              "SMEM_VER.BIN");
      if(return_status != BL_ERR_NONE)
      {
        return return_status;
      }
    }
  }

  if(dload_cookie & SBL_MINIDUMP_MODE_BIT_MASK)
  {

    if(platform_info_build_id != NULL)
    {
      if(!(boot_add_minidump_region(MD_SS_BOOT, "SMEMINFO", (uint64)platform_info_build_id, (uint64)platform_info_build_id_size)))
      {
        return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
      }
    }

    if(platform_info_version != NULL)
    {
      if(!(boot_add_minidump_region(MD_SS_BOOT, "SMEM_VER", (uint64)platform_info_version, (uint64)platform_info_version_size)))
      {
        return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
      }
    }
  }

  return return_status;
}

static bl_error_boot_type _ramdump_add_pmic_info
(
  boot_handle config_context_handle,
  ramdump_table_sm_handle* handle,
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
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
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
    if((return_status != BL_ERR_NONE) || (pmic_log_data_filename == NULL))
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
    pmic_if->pm_pbus_logger(0, handle->pbus_log_data);

    if (dload_cookie & SBL_DLOAD_MODE_BIT_MASK)
    {
      snprintf (pmic_pon_filename, DLOAD_DEBUG_STRLEN_BYTES, "PMIC_PON.BIN");
      snprintf (pmic_hist_filename, DLOAD_DEBUG_STRLEN_BYTES, "PMON_HIS.BIN");
      snprintf (pmic_log_data_filename, DLOAD_DEBUG_STRLEN_BYTES, "PBUS_LOG.BIN");

      return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                              RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                              (uintnt)(handle->pmic_power_on),
                                              (uintnt) sizeof(uintnt),
                                              "Pmic PON stat",
                                              pmic_pon_filename);

      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                              RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                              (uintnt)(handle->pon_events_log),
                                              (uintnt) sizeof(*handle->pon_events_log),
                                              "PM PON HIST ",
                                              pmic_hist_filename);

      if (return_status != BL_ERR_NONE)
      {
        break;
      }

#if 0 //Not present on SM
      return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                              RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                              (uintnt)(handle->pbus_log_data),
                                              (uintnt)(sizeof(pm_pbus_data_type)),
                                              "Pmic PBUS log dump",
                                              pmic_log_data_filename);

      if (return_status != BL_ERR_NONE)
      {
        break;
      }
#endif

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

#if 0 // Not present on SM
      if(!(boot_add_minidump_region(MD_SS_BOOT, pmic_log_data_filename, (uint64)(handle->pbus_log_data), (uint64)(sizeof(*handle->pbus_log_data)))))
      {
        return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
      }
#endif
    }

    if (pmic_pon_filename)
    {
      /* Free pmic_pon_filename */
      return_status = mem_if->free((void *)pmic_pon_filename);

      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      pmic_pon_filename = NULL;
    }

    if (pmic_hist_filename)
    {
      /* Free pmic_hist_filename */
      return_status = mem_if->free((void *)pmic_hist_filename);

      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      pmic_hist_filename = NULL;
    }

    if(pmic_log_data_filename)
    {
      /* Free pmic_log_data_filename */
      return_status = mem_if->free((void *)pmic_log_data_filename);

      if(return_status != BL_ERR_NONE)
      {
        break;
      }

      pmic_log_data_filename = NULL;
    }

  } while (FALSE);

  return return_status;
}

static bl_error_boot_type  _ramdump_add_pmic_pm_pbs_pon_reason_history
(
  boot_handle config_context_handle,
  ramdump_table_sm_handle* handle,
  uint32 dload_cookie
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  char *pmic_pm_pbs_pon_filename = NULL ;
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
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Malloc memory for pmic_pm_pbs_pon_filename */
    return_status = mem_if->malloc(DLOAD_DEBUG_STRLEN_BYTES, (void **)&pmic_pm_pbs_pon_filename);

    if ((return_status != BL_ERR_NONE) || pmic_pm_pbs_pon_filename == NULL)
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
    pmic_if->pm_pbs_get_pon_reason_history(handle->pon_reason_history_ptr );


    if (dload_cookie & SBL_DLOAD_MODE_BIT_MASK)
    {
      snprintf (pmic_pm_pbs_pon_filename, DLOAD_DEBUG_STRLEN_BYTES, "PMPONHIS.BIN");
      

      return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                              RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                              (uintnt)(handle->pon_reason_history_ptr),
                                              (uintnt) sizeof(uintnt),
                                              "PM PON HIST",
                                              pmic_pm_pbs_pon_filename);

      if (return_status != BL_ERR_NONE)
      {
        break;
      }
	  
	}  

   if (dload_cookie & SBL_MINIDUMP_MODE_BIT_MASK)
    {
      snprintf (pmic_pm_pbs_pon_filename, DLOAD_DEBUG_STRLEN_BYTES, "PM_PON_HIST");
   
	  if(!(boot_add_minidump_region(MD_SS_BOOT, pmic_pm_pbs_pon_filename, (uint64)(handle->pon_reason_history_ptr), (uint64)(sizeof(*handle->pon_reason_history_ptr)))))
      {
        return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_MD_ADD_REGION_FAIL);
      }

    }

    if (pmic_pm_pbs_pon_filename)
    {
      /* Free pmic_pm_pbs_pon_filename */
      return_status = mem_if->free((void *)pmic_pm_pbs_pon_filename);

      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      pmic_pm_pbs_pon_filename = NULL;
    }

  } while (FALSE);

  return return_status;
}



static bl_error_boot_type _ramdump_add_pmic_dump_data (boot_handle config_context_handle, ramdump_table_sm_handle* handle, uint32 dload_cookie)
{
  boot_pmic_if_type *pmic_if = NULL;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    /* If DLOAD mode is not set, do not add this range */
    if (!(dload_cookie & SBL_DLOAD_MODE_BIT_MASK))
    {
      return_status = BL_ERR_NONE;
      break;
    }

    return_status = boot_config_context_get_ptr(config_context_handle,
                    CONFIG_CONTEXT_PMIC_INTERFACE,
                    (void **)&pmic_if);

    if (BL_ERR_NONE != return_status)
    {
      break;
    }
    if (NULL == pmic_if)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    return_status = ramdump_table_add_restricted_region (handle->ramdump_table_handle_ptr, 0,
                                                        SCL_PMIC_DUMP_DATA_BUF_SIZE,
                                                        "PMIC registers",
                                                        "sbl_pmic_dump.bin",
                                                        (void*)(pmic_if->pm_pmic_dump));
  } while (FALSE);

  return return_status;
}

static bl_error_boot_type _ramdump_add_slave_regions(boot_handle config_context_handle, ramdump_table_sm_handle* handle, uint32 dload_cookie)
{
  boot_slvcom_if_type *boot_slvcom_if = NULL;
  boot_xrc_if_type *boot_xrc_if = NULL;
  bl_error_boot_type return_status = BL_ERR_NONE;
  uint32 index = 0;

  ramdump_table_memory_region slave_dump_regions[] = {SLAVE_MEMORY_REGION_TABLE};

  do
  {
    /* If DLOAD mode is not set, do not add this range */
    if(!(dload_cookie & SBL_DLOAD_MODE_BIT_MASK))
    {
       return_status = BL_ERR_NONE;
       break;
    }

    return_status = boot_config_context_get_ptr(config_context_handle,
                    CONFIG_CONTEXT_BOOT_SLVCOM_INTERFACE,
                    (void **)&boot_slvcom_if);

    if(BL_ERR_NONE != return_status) {
        break;
    }

    if(NULL == boot_slvcom_if) {
       return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SLVCOMINFO_IF, BL_ERR_BOOT_SLVCOM_INTERFACE_FAILURE);
       break;
    }

    return_status = boot_config_context_get_ptr(config_context_handle,
                    CONFIG_CONTEXT_BOOT_XRC_INTERFACE,
                    (void **)&boot_xrc_if);

    if(BL_ERR_NONE != return_status) {
        break;
    }

    if(NULL == boot_xrc_if) {
       return_status = GET_ERROR_CODE(BL_ERROR_GROUP_XRC_IF, BL_ERROR_BOOT_XRC_INTERFACE_FAILURE);
       break;
    }

    return_status = boot_xrc_if->init(slv_handle);
    if(!return_status) {
        break;
    }

    while(slave_dump_regions[index].region_base != 0 &&
          slave_dump_regions[index].region_size != 0 &&
          slave_dump_regions[index].desc != NULL &&
          slave_dump_regions[index].filename != NULL)
    {
         return_status = ramdump_table_add_restricted_region(handle->ramdump_table_handle_ptr,
                                                            slave_dump_regions[index].region_base | SCL_SLAVE_MEMORY_RESTRICT_REGION_BASE,
                                                            slave_dump_regions[index].region_size,
                                                            slave_dump_regions[index].desc,
                                                            slave_dump_regions[index].filename,
                                                            (void *)(boot_slvcom_if->ahb_read));

         index++;
    }



  } while(FALSE);

  return return_status;
}

static bl_error_boot_type _ramdump_add_ddr_training_data(boot_handle config_context_handle, ramdump_table_sm_handle* handle, uint32 dload_cookie)
{

  bl_error_boot_type status = BL_ERR_NONE;

  /* If DLOAD mode is not set, do not add this range */
  if (!(dload_cookie & SBL_DLOAD_MODE_BIT_MASK))
  {
    return BL_ERR_NONE;
  }

  status = read_ddr_training_data_from_partition((uint8 *)ddr_partition_data, 0, (uint64)SCL_DDR_PARTITION_DATA_BUF_SIZE);
  if(status != BL_ERR_NONE)
  {
    return status;
  }

  status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                   RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                   (uintnt)(ddr_partition_data),
                                   (uintnt)(SCL_DDR_PARTITION_DATA_BUF_SIZE),
                                   "DDR Training Data",
                                   "DDR_DATA.BIN");
  if(status != BL_ERR_NONE)
  {
    return status;
  }

  return status;
}




#ifdef SCL_pIMEM_BASE    
static bl_error_boot_type _ramdump_add_pimem_data(boot_handle config_context_handle, ramdump_table_sm_handle* handle, uint32 dload_cookie)
{
  uint32 size_in_mb = 0;
  bl_error_boot_type return_status = BL_ERR_NONE;
  bl_error_boot_type sec_return_status = BL_ERR_NONE;
  boot_seclib_if_type *seclib_if;

  /* If DLOAD mode is not set, do not add this range */
  if (!(dload_cookie & SBL_DLOAD_MODE_BIT_MASK))
  {
    return BL_ERR_NONE;
  }

  return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_SECLIB_INTERFACE, (void **)&seclib_if);
  if (return_status != BL_ERR_NONE)
  {
    return return_status;
  }

  sec_return_status = seclib_if->pimem_get_status(&size_in_mb);

  if (sec_return_status == BL_ERR_NONE)
  {
    /*Add pimem region */
    return_status = ramdump_table_add_entry (handle->ramdump_table_handle_ptr,
                    RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                    (uintnt)SCL_pIMEM_BASE,
                    (uintnt)(size_in_mb << CONVERT_TO_MB_SHIFT),
                    "PIMEM region", "PIMEM.BIN");

  }
  else
  {
    DL_LOG("pImem Disabled,ERRCODE:%d",sec_return_status);
  }

  return return_status;
}
#endif

static bl_error_boot_type _ramdump_add_ddr_regions (boot_handle config_context_handle, ramdump_table_sm_handle* handle, uint32 dload_cookie)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  uint64 start_addr =0;
  uint64 size =0;
  uint32 index =0;
  DDR_REGIONS_DATA *ddr_info = NULL;
  VOID   *pDDRRegionsData = NULL;
  UINT32 DDRInfoBuffSz = 0;
  char ddr_string_info[DLOAD_DEBUG_STRLEN_BYTES], ddr_filename[DLOAD_DEBUG_STRLEN_BYTES];
  uint64 file_cnt =0 ;
  int i = 0;

  /* If DLOAD mode is not set, do not take full RAM dump */
  if (!(dload_cookie & SBL_DLOAD_MODE_BIT_MASK))
  {
    return BL_ERR_NONE;
  }

  do
  {
    /* Get the RAM partition table */
    pDDRRegionsData = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
    if (pDDRRegionsData == NULL)
    {
      /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
      boot_log_message("Ramdump Error: can't get ddr info from SMEM");
      break ;
    }

    ddr_info = (VOID*)(((UINT8 *)pDDRRegionsData) + sizeof(ddr_details_entry));
    index = 0;

    for (i= 0; i < ddr_info->no_of_ddr_regions; i++)
    {
      start_addr = ddr_info->ddr_region[i].start_address;
      size = ddr_info->ddr_region[i].size;

      /* Define DDR Memory Region  EBI1 CS0/CS1 etc */
      file_cnt = 0;

      do
      {
        memset(ddr_string_info, 0, DLOAD_DEBUG_STRLEN_BYTES);
        memset(ddr_filename, 0, DLOAD_DEBUG_STRLEN_BYTES);
        snprintf (ddr_string_info, DLOAD_DEBUG_STRLEN_BYTES, " DDR CS%u part%u Memory", index, file_cnt);
        snprintf (ddr_filename, DLOAD_DEBUG_STRLEN_BYTES, "DDRCS%u_%u.BIN", index, file_cnt);

        /* Split to 2GB files */
        if (size >= SIZE_2GB)
        {
          return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                                  RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                                  start_addr + SIZE_2GB * file_cnt,
                                                  SIZE_2GB,
                                                  ddr_string_info,
                                                  ddr_filename);

          if (return_status != BL_ERR_NONE)
          {
            break;
          }
          size -= SIZE_2GB;
        }
        else
        {
          return_status = ramdump_table_add_entry(handle->ramdump_table_handle_ptr,
                                                  RAMDUMP_TABLE_OPTIONAL_DEF_SAVE,
                                                  start_addr + SIZE_2GB * file_cnt,
                                                  size,
                                                  ddr_string_info,
                                                  ddr_filename);

          if (return_status != BL_ERR_NONE)
          {
            break;
          }

          size -= size;
        }

        file_cnt++;
      } while (size);

      index++;
    }
  } while (FALSE);

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

  ramdump_table_sm_handle *handle = (ramdump_table_sm_handle *)handle_ptr;

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

    /* Free Ramdump table SM handle */
    return_status = mem_if->free((void *)handle);
    if (return_status != BL_ERR_NONE)
    {
      break;
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
*   This function is stubbed out to return BL_ERR_FEATURE_NOT_SUPPORTED
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
bl_error_boot_type ramdump_table_target_unrecoverable_error_handler (void)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_edk2_cache_if_type *edk2_cache_if = NULL;
  static boot_handle handle = NULL;
  uint8 * external_cached_heap_base_addr = NULL;
  ChipInfoIdType chipinfo_id;
  boot_chipinfo_if_type *chipinfo_if = NULL;

  do
  {
    /* Cache config context handle */
    return_status = boot_config_context_get_crt_handle(&handle);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_EDK2_CACHE_INTERFACE, (void**)&edk2_cache_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    if (edk2_cache_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* re-initialize heap, zi-buffer, restore stack-pointer and re-enter download mode without reset */
    edk2_cache_if->WriteBackInvalidateDataCacheRange((void *)SCL_RAMDUMP_DLOAD_BUFFERS_BASE, (uintnt)SCL_RAMDUMP_DLOAD_BUFFERS_SIZE);

    external_cached_heap_base_addr = xbl_get_external_cached_heap_addr();
    edk2_cache_if->WriteBackInvalidateDataCacheRange((void *)external_cached_heap_base_addr,
                                                     xbl_get_external_cached_heap_size());


    /* Get ChipInfo interface */
    return_status = boot_config_context_get_ptr(handle, CONFIG_CONTEXT_CHIPINFO_INTERFACE, (void **)&chipinfo_if);
    if(return_status != BL_ERR_NONE)
    {
       break;
    }
    /* Get ChipInfo ID */
    return_status = chipinfo_if->get_chip_id(&chipinfo_id);
    if(return_status != BL_ERR_NONE) {
       break;
    }

    /* Ignore DALSYS de-init in Aurora for USB PIPO usecase */
    if(chipinfo_id != CHIPINFO_ID_SXR_AURORA) {
       DALSYS_DeInitMod();
    }

    edk2_cache_if->WriteBackInvalidateDataCacheRange((void *)Image$$RAMDUMP_DATA_RW$$Base, (uintnt)Image$$RAMDUMP_DATA_RW$$Length);
    edk2_cache_if->WriteBackInvalidateDataCacheRange((void *)Image$$STACK$$Base, (uintnt)Image$$STACK$$Length);

    ((void (*)())(uintnt)(SCL_RAMDUMP_CODE_BASE))(handle);

  } while (FALSE);

  return return_status;
}
