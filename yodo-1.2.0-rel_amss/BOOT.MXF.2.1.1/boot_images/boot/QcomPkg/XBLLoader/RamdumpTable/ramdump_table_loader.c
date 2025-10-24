/*===========================================================================

                  RAMDUMP TABLE DEFINITIONS

DESCRIPTION
  Ramdump table collection is not supported in this library.
  For XBLLoader image

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who     what, where, why
--------    ---     ----------------------------------------------------------
07/13/21    rhy     Removed unrecoverable_error_handler
07/09/21    rhy      Initial revision.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <stdio.h>
#include "boot_error_if.h"
#include "boot_ramdump_table_if.h"
#include "boot_config_context.h"
#include <boot_dbginfo_if.h>

/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/


/*=============================================================================

UN-SUPPORTED FUNCTION

=============================================================================*/

/*===========================================================================

FUNCTION RAMDUMP_TABLE_COPY_RESTRICTED_REGION

DESCRIPTION
  This function is used to read the data from restricted region by correspoding
  handler.

DEPENDENCIES
  None.

RETURN VALUE
  bl_error_boot_type

SIDE EFFECTS
  None.

===========================================================================*/

bl_error_boot_type ramdump_table_copy_restricted_region(uint8 *buf, uint64 addr, uint64 len)
{
  return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE,BL_ERR_FEATURE_NOT_SUPPORTED);
}


/*=========================================================================

**  Function :  ramdump_table_open

** ==========================================================================
*/
/*!
*
* @brief
*   Function not supported.
*
* @param[in] pointer to config context handle, pointer to mem debug handle pointer
*
*
*/
static bl_error_boot_type ramdump_table_open (const boot_handle config_context_handle, boot_handle *handle_ptr)
{
  return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE,BL_ERR_FEATURE_NOT_SUPPORTED);
}




/*=========================================================================

**  Function :  ramdump_table_get_table_addr

** ==========================================================================
*/
/*!
*
* @brief
*   Function not supported.
*
* @param[in] pointer to mem debug handle pointer
*
*
*/
static bl_error_boot_type ramdump_table_get_table_addr(boot_handle handle, uintnt *rd_entries_ptr)
{
  return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE,BL_ERR_FEATURE_NOT_SUPPORTED);
}

/*=========================================================================

**  Function :  ramdump_table_get_table_len

** ==========================================================================
*/
/*!
*
* @brief
*   Function not supported.
*
* @param[in] pointer to mem debug handle pointer
*
*
*/
static bl_error_boot_type ramdump_table_get_table_len(boot_handle handle, uintnt *num_of_entries)
{
  return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE,BL_ERR_FEATURE_NOT_SUPPORTED);
}

/*=========================================================================

**  Function :  ramdump_table_verify_addr

** ==========================================================================
*/
/*!
*
* @brief
*   Function not supported.
*
* @param[in] pointer to mem debug handle pointer
*
*
*/
static bl_error_boot_type ramdump_table_verify_addr
(
  boot_handle handle_ptr,
  uint64 base,
  uint64 len,
  boot_boolean *verified_address
)
{
  return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE,BL_ERR_FEATURE_NOT_SUPPORTED);
}

/*=========================================================================

**  Function :  ramdump_table_verify_restricted_addr

** ==========================================================================
*/
/*!
*
* @brief
*   Function not supported.
*
*   Stub function for now
*
*
*/
static bl_error_boot_type ramdump_table_verify_restricted_addr
(
  boot_handle handle_ptr,
  uint64 base,
  uint64 len,
  boot_boolean *verified_address
)
{
  return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE,BL_ERR_FEATURE_NOT_SUPPORTED);
}

/*=========================================================================

**  Function :  ramdump_table_close

** ==========================================================================
*/
/*!
*
* @brief
*   Function not supported.
*
* @param[in] pointer to config context handle, pointer to mem debug handle pointer
*
*
*/
static bl_error_boot_type ramdump_table_close(const boot_handle config_context_handle, boot_handle handle_ptr)
{
  return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE,BL_ERR_FEATURE_NOT_SUPPORTED);
}

/*=============================================================================

SUPPORTED FUNCTION

=============================================================================*/

/*=========================================================================

**  Function :  ramdump_table_supported

** ==========================================================================
*/
/*!
*
* @brief
*   Function to check whether ram/mini dump collection is supported from QSEE
*
* @param[in] pointer to config context handle, pointer to dump supported
*
*
*/
static bl_error_boot_type ramdump_table_supported(boot_handle config_context_handle, boot_boolean *dump_supported)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_dbginfo_if_type *dbginfo_if = NULL;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_DBGINFO_INTERFACE, (void **)&dbginfo_if);
  if(status != BL_ERR_NONE || dbginfo_if == NULL)
    return status;

  status = dbginfo_if->is_ramdump_allowed((boot_boolean*)dump_supported);
  return status;
}


/* ==========================================================================

**  Function :  boot_ramdump_table_get_interface

** ==========================================================================
*/
/*!
*
* @brief
*   Initialize boot memory debug handler table.
*
* @param[in]
*
*/
bl_error_boot_type boot_ramdump_table_get_interface(void *ramdump_if)
{
  if (ramdump_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
  }

  ((ramdump_table_if *)ramdump_if)->open                        = ramdump_table_open;
  ((ramdump_table_if *)ramdump_if)->is_ramdump_allowed          = ramdump_table_supported;
  ((ramdump_table_if *)ramdump_if)->get_table_addr              = ramdump_table_get_table_addr;
  ((ramdump_table_if *)ramdump_if)->get_table_len               = ramdump_table_get_table_len;
  ((ramdump_table_if *)ramdump_if)->verify_addr                 = ramdump_table_verify_addr;
  ((ramdump_table_if *)ramdump_if)->verify_restricted_addr      = ramdump_table_verify_restricted_addr;
  ((ramdump_table_if *)ramdump_if)->copy_restricted             = ramdump_table_copy_restricted_region;
  ((ramdump_table_if *)ramdump_if)->close                       = ramdump_table_close;

  return BL_ERR_NONE;
}
