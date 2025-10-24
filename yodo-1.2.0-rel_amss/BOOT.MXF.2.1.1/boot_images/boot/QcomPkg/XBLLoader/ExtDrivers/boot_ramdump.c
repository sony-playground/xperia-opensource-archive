/*===========================================================================

                    BOOT SDI IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for SDI image functionality

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2019-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/27/22 � sym � � remove fdt_get_blob_handle api
06/23/22   ds      changes for FR78810 - stream logs to media
02/09/22   ck      Updated heap function names
06/28/21   ck      Converged to common USB/PCIe boot_dload_transition_pbl_forced_dload
06/25/21   rhy     Added boot_clear_second_pass_complete
06/22/21   rama    replace MAX_NUM_OF_SS with MD_SS_MAX
06/16/21   ds      clear dload cookie before reset
06/02/21   ds      minidump changes
01/21/21   rhy     Set SECOND_PASS_COMPLETE to 1 in dump collection
12/16/20   tmt     DTB: DEFAULT_BLOB_ID
11/25/20   rama    Removed DTBInternals.h
11/09/20   rama    Added device-tree setting to reset/shutdown upon fedl timeout.
05/10/20   ds      move to edk2 arm mmu/cache lib
02/24/20   rama    Replaced boothw_target.h with boot_reset_if.h
08/06/19   ep      Initial Creation.

=============================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <stdio.h>
#include <string.h>
#include "boot_error_if.h"
#include "boot_minidump.h"
#include "boot_logger.h"
#include "boot_shared_imem_cookie.h"
#include "boot_config_context.h"
#include "boot_crashdump.h"
#include "pbl_sbl_external.h"
#include <boot_ramdump_if.h>
#include <boot_smem_if.h>
#include <boot_pmic_if.h>
#include <boot_busywait_if.h>
#include <boot_reset_if.h>
#include <boot_edk2_armlib_if.h>
#include <DTBExtnLib.h>
#include <boot_sw_defines.h>
#include <sbl1_hw.h>
#include <boot_media_types.h>
#include <boot_logger_if.h>

#include "HALbootHWIO.h"
#include "HALhwio.h"


#define BOOT_DTB_FEDL_TIMEOUT_NODE "/sw/boot/fedl_timeout"

/* Structure must match the property in dtsi */
struct boot_fedl_timeout_property
{
  uint32_t version;
  uint32_t action;
} boot_fedl_timeout_property;

/*===========================================================================
**  Function :  boot_dload_read_saved_cookie
** ==========================================================================
*/
/*!
*
* @brief
*   Return the saved cookie value
**
* @param[out] saved cookie value
*
* @par Dependencies
*  None
*
*/
uint32 boot_dload_read_saved_cookie(void)
{
  return HWIO_TCSR_TCSR_BOOT_MISC_DETECT_INM(SBL_DLOAD_MODE_BIT_MASK | SBL_MINIDUMP_MODE_BIT_MASK);
}

/*===========================================================================

FUNCTION  boot_smem_alloc_for_minidump

DESCRIPTION
  Allocate SMEM memory to be used for minidump feature

DEPENDENCIES
  SMEM init to be done; So please ensure to call this API after smem_init

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
bl_error_boot_type boot_smem_alloc_for_minidump(boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  md_global_toc  *md_smem_base = NULL;
  uint32 *md_shared_imem_ptr = (uint32 *)MD_SHARED_IMEM_BASE;
  boot_smem_if_type *smem_if = NULL;

  do
  {
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SMEM_INTERFACE, (void **)&smem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    md_smem_base = (md_global_toc  *)smem_if->alloc( SBL_MINIDUMP_SMEM_ID, sizeof(md_global_toc));
    if (md_smem_base == 0x0)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SMEM, BL_ERR_FAIL_ALLOCATE_SMEM);
      break;
    }
    md_smem_base->md_revision = MD_REVISION;
    md_smem_base->md_toc_init = TRUE;
    memset(md_smem_base->md_ss_toc, 0, sizeof(md_ss_toc)*MD_SS_MAX);

    /* Update shared IMEM location with the global SMEM TOC address */
    *(md_shared_imem_ptr) = (uint32)(uintptr_t)md_smem_base;
  } while (FALSE);

  return return_status;
}

/*===========================================================================

FUNCTION  BOOT_DLOAD_ENTRY

DESCRIPTION
  Determines if identifier is present in BOOT_MISC_DETECT register to tell
  SBL to enter the boot downloader, instead on continuing the normal boot
  process.

DEPENDENCIES
  Data in BOOT_MISC_DETECT (or GCC_WIND_DOWN_TIMER for v1) is retained across a reset.

RETURN VALUE
  TRUE indicates downloader should be entered.

SIDE EFFECTS
  None

===========================================================================*/
boolean boot_dload_entry(void)
{
  /* Check to see if download ID is present.
     For Bear family the cookie is now stored in the register BOOT_MISC_DETECT
     and not IMEM.  This register is shared with PBL and maybe others.  Only
     one bit is needed and the mask SBL_BOOT_MISC_DETECT_MASK defines what
     section of the register SBL owns. */
  char dbg_info[40];
  uint32 dload_flag =0x0;
  boolean status = FALSE;

  do
  {
    dload_flag = HWIO_TCSR_TCSR_BOOT_MISC_DETECT_INM(SBL_DLOAD_MODE_BIT_MASK | SBL_MINIDUMP_MODE_BIT_MASK);
    if (dload_flag)
    {
      snprintf(dbg_info, 40, "TCSR reg value 0x%x ", dload_flag);
      boot_log_message(dbg_info);

      status = TRUE;
      /* Set SECOND_PASS_COMPLETE to 1 */
      HWIO_OUTF(AOSS_CC_RESET_FSM_CTRL, SECOND_PASS_COMPLETE, 1);

      break;
    }
  } while (0);

  return status;

} /* boot_dload_entry() */

/*===========================================================================

FUNCTION  BOOT_DLOAD_IS_DLOAD_MODE_SET

DESCRIPTION
  This function shall return if the dload cookie is set or not for the
  phone to go in download mode.

DEPENDENCIES
  Data in BOOT_MISC_DETECT (or GCC_WIND_DOWN_TIMER for v1) is retained across a reset.

RETURN VALUE
  TRUE indicates cookies are set
  FALSE cookies are not set

SIDE EFFECTS
  None

===========================================================================*/
boolean boot_dload_is_dload_mode_set( void )
{
  boolean status = FALSE;
  do
  {
    /* Evaluate dload mode bit that is in the BOOT_MISC_DETECT register */
    if (HWIO_TCSR_TCSR_BOOT_MISC_DETECT_INM(SBL_DLOAD_MODE_BIT_MASK | SBL_MINIDUMP_MODE_BIT_MASK))
    {
      status=TRUE;
      break;
    }
  } while (0);

  return status;
}


/*===========================================================================
**  Function :  boot_dload_set_cookie
** ==========================================================================
*/
/*!
*
* @brief
*   Set the SBL dload mode cookie
**
* @par Dependencies
*  None
*
*/
void boot_dload_set_cookie( void )
{
  HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OUTM(SBL_DLOAD_MODE_BIT_MASK,
                                       SBL_DLOAD_MODE_BIT_MASK);
}

/*===========================================================================
**  Function :  boot_minidump_set_cookie
** ==========================================================================
*/
/*!
*
* @brief
*   Set the SBL minidump mode cookie
**
* @par Dependencies
*  None
*
*/
void boot_minidump_set_cookie( void )
{
  HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OUTM(SBL_MINIDUMP_MODE_BIT_MASK,
                                       SBL_MINIDUMP_MODE_BIT_MASK );
}

/*=============================================================================

**  Function :  boot_dload_transition_pbl_forced_dload

** ==========================================================================
*/
/*!
*
* @brief
*   This function sets the magic numbers for PBL to detect and enter forced
*   download mode.  It then calls the target specific function to trigger a
*   system reset.
*
* @par Dependencies
*   None
*
* @retval
*   bl_error_boot_type
*
* @par Side Effects
*   Set's PBL magic numbers to enter forced download, resets target, never to
*   return.
*
*/
extern boot_log_init_data boot_log_data;

bl_error_boot_type boot_dload_transition_pbl_forced_dload(boot_handle config_context)
{

  /* PBL uses the last four bits of BOOT_MISC_DETECT to trigger forced download.
     Preserve the other bits of the register. */
  uint32 register_value = 0;
  bl_error_boot_type return_status = BL_ERR_NONE;
  uintnt boot_device = NO_FLASH;

  /* Validate pointers */
  if (config_context == NULL)
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }
  /* Obtain boot device */
  return_status = boot_config_context_get_value(config_context,
                  CONFIG_CONTEXT_BOOT_DEVICE,
                  (void *)&boot_device);

  if (return_status != BL_ERR_NONE)
  {
    goto exit;
  }


  /* Relocate boot logs to IPA OCIMEM region location for future analysis */
  boot_log_relocate((void *)(SHARED_IMEM_BASE-SIZE_8KB),
                    (void *)((uintnt)(SHARED_IMEM_BASE-SIZE_8KB)+(uintnt)boot_log_data.meta_info_size),
                    boot_log_data.log_buffer_size,
                    (void *)((uintnt)(SHARED_IMEM_BASE-SIZE_8KB)+(uintnt)boot_log_data.meta_info_size+(uintnt)boot_log_data.log_buffer_size),
                    boot_log_data.time_marker_buffer_size,
                    (void *)boot_log_data.meta_info_start,
                    (void *)boot_log_data.log_buffer_start,
                    boot_log_data.log_buffer_size,
                    (void *)boot_log_data.time_marker_buffer_start,
                    boot_log_data.time_marker_buffer_size);


  /* Read current TCSR register, clear PBL evaluated bits */
  register_value =HWIO_TCSR_TCSR_BOOT_MISC_DETECT_INM(HWIO_TCSR_TCSR_BOOT_MISC_DETECT_RMSK);

  /* Clear any SBL DLOAD, MINIDUMP area */
  register_value &= ~(SBL_DLOAD_MODE_BIT_MASK | SBL_MINIDUMP_MODE_BIT_MASK);

  /* Clear the PBL masked area and then apply HS_USB value */
  register_value &= ~(FORCE_DLOAD_MASK);


  /* Determine if PCIe EDL should be entered, if not default to USB */
  if ((boot_device == PCIE_FLASHLESS) ||
      xbl_pcie_fast_boot_enabled())
  {
    /* Apply EDL PCIe bits to TCSR */
    register_value |= FORCE_DLOAD_BOOT_PCIE;


    /* Add message to loggers */
    boot_log_message ("Enter PBL EDL PCIe");
  }
  else
  {
    /* Apply EDL USB bits to TCSR */
    register_value |= FORCE_DLOAD_BOOT_USB;


    /* Add message to loggers */
    boot_log_message ("Enter PBL EDL USB");
  }


  /* Write the new value back out to the register */
  HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OUT(register_value);


  boot_cache_flush_boot_regions();


  /* Attempt a warm reset.  Execution should not return. */
  return_status = boot_hw_reset(BOOT_WARM_RESET_TYPE);

  if (return_status != BL_ERR_NONE)
  {
    goto exit;
  }


exit:
  return return_status;
}


/*===========================================================================

**  Function :  boot_init_for_dload

** ==========================================================================
*/
/*!
*
* @brief
*   Wrapper function that calls smem_boot_debug_init().
*
* @param[in] bl_shared_data Pointer to shared data structure
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
bl_error_boot_type boot_init_for_dload(boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
#ifdef BOOT_DISABLE_DCACHE_IN_DLOAD
  boot_edk2_armlib_if_type *edk2_armlib_if = NULL;
  /* Disable cache and MMU */
  return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_EDK2_ARMLIB_INTERFACE, (void**)&edk2_armlib_if);
  if (return_status != BL_ERR_NONE || edk2_armlib_if == NULL)
  {
    return return_status;
  }
  edk2_armlib_if->ArmDisableCachesAndMmu();
#endif /* BOOT_DISABLE_DCACHE_IN_DLOAD */
  return return_status;
} /* boot_smem_init_for_dload() */

/*===========================================================================

FUNCTION  boot_dload_is_forced_dload_timeout_set

DESCRIPTION
  This function shall return if the forced dload timeout reset cookie  is set or not

DEPENDENCIES
  Data in BOOT_MISC_DETECT.

RETURN VALUE
  TRUE indicates cookies are set
  FALSE cookies are not set

SIDE EFFECTS
  None

===========================================================================*/
boolean boot_dload_is_forced_dload_timeout_set(void)
{
  boolean status = FALSE;
  do
  {
    /* Evaluate dload mode bit that is in the BOOT_MISC_DETECT register */
    if (HWIO_TCSR_TCSR_BOOT_MISC_DETECT_INM(FORCE_DLOAD_TIMEOUT_RESET_WARM_BOOT_COOKIE))
    {
      status=TRUE;
      break;
    }
  } while (0);

  return status;
}

/*=============================================================================

**  Function :  boot_dload_handle_forced_dload_timeout

** ==========================================================================
*/
/*!
*
* @brief
*   This function checks if PBL set FORCE_DLOAD_TIMEOUT_RESET_WARM_BOOT_COOKIE
*   If set then calls the target specific function to trigger a
*   system reset.
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   resets target, if cookie is set
*
*/
bl_error_boot_type boot_dload_handle_forced_dload_timeout(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_busywait_if_type *busywait_if = NULL;
  boot_reset_if_type *reset_if = NULL;
  void *fdt_handle = NULL;
  fdt_node_handle node;
  int ret_val =0;
  struct boot_fedl_timeout_property fedl_timeout = {0, BOOT_FEDL_TIMEOUT_ACTION_HARD_RESET};

  if (boot_dload_is_forced_dload_timeout_set())
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_BUSYWAIT_INTERFACE, (void **)&busywait_if);
    if (status != BL_ERR_NONE)
    {
      return status;
    }
    if (busywait_if == NULL)
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_INTERFACE_FAILURE);
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RESET_INTERFACE, (void **)&reset_if);
    if (status != BL_ERR_NONE)
    {
      return status;
    }
    if (reset_if == NULL)
    {
      return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_INTERFACE_FAILURE);
    }

      ret_val = fdt_get_node_handle(&node, fdt_handle, BOOT_DTB_FEDL_TIMEOUT_NODE);
      if (ret_val == 0)
      {
        ret_val = fdt_get_prop_values_of_node(&node, "WW", &fedl_timeout, sizeof(struct boot_fedl_timeout_property));
        if (ret_val != 0 || fedl_timeout.version != BOOT_FEDL_TIMEOUT_PROP_VERSION)
        {
          if (fedl_timeout.version != BOOT_FEDL_TIMEOUT_PROP_VERSION)
          {
            boot_log_message("DTB: setting version mismatch");
          }
          fedl_timeout.action = BOOT_FEDL_TIMEOUT_ACTION_HARD_RESET;
        }
      }

    if (ret_val != 0)
    {
      boot_log_message("DTB: couldn't retrieve fedl timeout action setting");
    }

    if (fedl_timeout.action == BOOT_FEDL_TIMEOUT_ACTION_SHUTDOWN)
    {
      boot_log_message ("EMERGENCY_DLOAD_TIMEOUT_COOKIE_SET: Powerdown");
      busywait_if->busywait(300000); /* Wait for log 300 mS */
      reset_if->hw_powerdown();
    }
    else
    {
      boot_log_message ("EMERGENCY_DLOAD_TIMEOUT_COOKIE_SET: Reset");
      busywait_if->busywait(300000); /* Wait for log 300 mS */
      reset_if->hw_reset(BOOT_HARD_RESET_TYPE);
    }
  }
  return status;
} /* boot_dload_handle_forced_dload_timeout() */


/*===========================================================================
**  Function :  boot_clear_second_pass_complete
** ==========================================================================
*/
/*!
*
* @brief
*   Clear the SECOND_PASS_COMPLETE
**        
* @par Dependencies
*  None
*
*/
void boot_clear_second_pass_complete( void )
{
  /* Clear SECOND_PASS_COMPLETE */
  HWIO_OUTF(AOSS_CC_RESET_FSM_CTRL, SECOND_PASS_COMPLETE, 0);
}


/*===========================================================================
**  Function :  boot_ramdump_get_interface
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes a boot_ramdump_get_interface
*
* @par Dependencies
*   None
*
*/

//TODO: FIXME
byte * xbl_get_external_cached_heap_addr(void);
uintnt xbl_get_external_cached_heap_size(void);

bl_error_boot_type boot_ramdump_get_interface(void* _ramdump_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_ramdump_if_type *ramdump_if = (boot_ramdump_if_type *)_ramdump_if;

  do
  {
    if (ramdump_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_INVALID_PARAMETER);
      break;
    }

    ramdump_if->set_dload_cookie = boot_dload_set_cookie;
    ramdump_if->get_saved_cookie = boot_dload_read_saved_cookie;
    ramdump_if->transition_pbl_forced_dload = boot_dload_transition_pbl_forced_dload;
    ramdump_if->get_external_heap_addr = xbl_get_external_cached_heap_addr;
    ramdump_if->get_external_heap_size = xbl_get_external_cached_heap_size;
    ramdump_if->clear_second_pass_complete = boot_clear_second_pass_complete;

  } while (FALSE);


  return return_status;
}
