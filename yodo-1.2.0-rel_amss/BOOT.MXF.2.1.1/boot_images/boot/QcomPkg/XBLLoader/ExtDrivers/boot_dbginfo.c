/*===========================================================================

                    BOOT WRAPPER FOR DBGINFO LIB

DESCRIPTION
  Contains wrapper definition for debug info library

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
  Copyright 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/18/21   rama    added boot_get_subsystem_debug_options
06/02/21   ds      minidump changes
05/13/21   ds      fix whichramdump
05/02/21   ds      oem_lcs api
04/03/21   ds      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <boot_dbginfo_if.h>
#include <boot_error_if.h>
#include <dbginfolib_extended.h>
/*===========================================================================
                           DEFINITIONS
===========================================================================*/



/*===========================================================================
                      FUNCTION DEFINITIONS
===========================================================================*/ 

/**
 * @brief This function gets the eud enabled status
 *
 * @param[in] pointer to store dbg_state
 *
 * @return
 *   bl_error_boot_type
 *
 * @sideeffects
 *   None
 *
 *
 */
bl_error_boot_type boot_is_eud_enabled(boot_boolean *eud_enabled)
{
  *eud_enabled = (boot_boolean)(dbgil_is_eud_enabled());
  return BL_ERR_NONE;
}

/**
 * @brief This function gets which ramdump is allowed
 *
 * @param[in] pointer to store rd_type
 *
 * @return
 *   bl_error_boot_type
 *
 * @sideeffects
 *   None
 *
 *
 */
bl_error_boot_type boot_which_ramdump_allowed(ramdump_type *rd_type)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  uint32 rd_option = dbgil_get_crashdump_options();

  *rd_type = RAMDUMP_NOT_ALLOWED;
  
  if((rd_option & DBGIL_CDO_SEC_FULL_DUMP) == DBGIL_CDO_SEC_FULL_DUMP)
  {
    *rd_type = FULL_DUMP_ALLOWED;
  }
  else if((rd_option & DBGIL_CDO_MINI_DUMP) == DBGIL_CDO_MINI_DUMP)
  {
    *rd_type = MINIDUMP_ALLOWED;
  }
  else if((rd_option & DBGIL_CDO_NS_DUMP) == DBGIL_CDO_NS_DUMP)
  {
    *rd_type = NSEC_DUMP_ALLOWED;
  }

  return return_status;
}

/**
 * @brief This function tells if minidump is allowed
 *
 * @param[in] pointer to store rd_type
 *
 * @return
 *   bl_error_boot_type
 *
 * @sideeffects
 *   None
 *
 *
 */
bl_error_boot_type boot_is_minidump_enabled(boot_boolean *minidump_allowed)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  *minidump_allowed = FALSE;
  uint32 rd_option = dbgil_get_crashdump_options();
  if(rd_option > DBGIL_CDO_SEC_FULL_DUMP)
  {
    return_status = GET_ERROR_CODE(BL_ERROR_GROUP_DBGINFOLIB,BL_INVALID_RD_OPTION);
    return return_status;
  }
  
  if((rd_option & DBGIL_CDO_MINI_DUMP) == DBGIL_CDO_MINI_DUMP)
  {
    *minidump_allowed = TRUE;
  }
   
  return return_status;
}

/**
 * @brief This function gets the ramdump allowed status
 *
 * @param[in] pointer to store ramdump allowed status
 *
 * @return
 *   bl_error_boot_type
 *
 * @sideeffects
 *   None
 *
 *
 */
bl_error_boot_type boot_is_ramdump_allowed(boot_boolean *rd_allowed)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  uint32 rd_type = RAMDUMP_NOT_ALLOWED;
  
  return_status = boot_which_ramdump_allowed(&rd_type);
  if(return_status != BL_ERR_NONE)
  {
    return return_status;
  }
  
  if(rd_type != RAMDUMP_NOT_ALLOWED)
  {
    *rd_allowed = TRUE;
  }
  
  return return_status;
}

/**
 * @brief This function gets auth enabled status
 *
 * @param[in] pointer to store auth enabed status
 *
 * @return
 *   bl_error_boot_type
 *
 * @sideeffects
 *   None
 *
 *
 */
bl_error_boot_type boot_is_auth_enabled(boot_boolean *auth_enabled)
{
  *auth_enabled = (boot_boolean)(dbgil_is_auth_enabled());
  return BL_ERR_NONE;
}

/**
 * @brief This function gets XBL_SC subsystem debug options
 *
 * @param[in] pointer to store subsystem debug options
 *
 * @return
 *   bl_error_boot_type
 *
 * @sideeffects
 *   None
 *
 *
 */
bl_error_boot_type boot_get_subsystem_debug_option(dbgil_subsys_t subsys_id, boot_boolean *subsys_dbg_option)
{
  if(subsys_dbg_option == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_DBGINFOLIB, BL_ERR_INVALID_PARAMETER);
  }

  if(subsys_id >= DBGIL_NUMBER_SUBSYS)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_DBGINFOLIB, BL_ERR_INVALID_PARAMETER);
  }

  *subsys_dbg_option = (boot_boolean)(dbgil_get_subsystem_debug_options(subsys_id));

  return BL_ERR_NONE;
}
/**
 * @brief This function gets auth enabled status
 *
 * @param[in] pointer to store auth enabed status
 *
 * @return
 *   bl_error_boot_type
 *
 * @sideeffects
 *   None
 *
 *
 */
bl_error_boot_type boot_is_oem_lcs_dev_state(boot_boolean *status)
{
  *status = (boot_boolean)(dbgil_is_oem_lcs_development_state());
  return BL_ERR_NONE;
}

boot_dbginfo_if_type dbginfo_if =
{
  boot_is_eud_enabled,
  boot_is_ramdump_allowed,
  boot_which_ramdump_allowed,
  boot_is_minidump_enabled,
  boot_is_auth_enabled,
  boot_get_subsystem_debug_option,
  boot_is_oem_lcs_dev_state
};
