#ifndef BOOT_DBGINFO_IF_H
#define BOOT_DBGINFO_IF_H
/*===========================================================================

                    BOOT EXTERN SECURE IMAGE AUTH DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for debug info library

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/18/21   rama    Added get_subsys_debug_option
06/02/21   ds      minidump changes
05/02/21   ds      oem lcs api
04/03/21   ds      Initial Creation.
===========================================================================*/

/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include <boot_comdef.h>
#include <dbginfolib.h>
#include <boot_error_if.h>

typedef enum
{
  BL_INVALID_RD_OPTION = BL_ERR_CUSTOM_ERRORS_START  
}bl_ddbginfo_error_type;

typedef enum ramdump_type
{
  RAMDUMP_NOT_ALLOWED = 0,
  MINIDUMP_ALLOWED = 1 << 0,
  NSEC_DUMP_ALLOWED = 1 << 1,
  FULL_DUMP_ALLOWED = 1 << 2
}ramdump_type;

typedef struct boot_dbginfo_if_type
{
  bl_error_boot_type (*is_eud_enabled)(boot_boolean *eud_enabled);
  bl_error_boot_type (*is_ramdump_allowed)(boot_boolean *rd_allowed);
  bl_error_boot_type (*which_ramdump_allowed)(ramdump_type *rd_type);
  bl_error_boot_type (*is_minidump_allowed)(boot_boolean *minidump_allowed);
  bl_error_boot_type (*is_auth_enabled)(boot_boolean *auth_enabled);
  bl_error_boot_type (*get_subsys_debug_option)(dbgil_subsys_t subsys_id, boot_boolean *subsys_dbg_option);
  bl_error_boot_type (*is_oem_lcs_dev_state)(boot_boolean *status);
} boot_dbginfo_if_type;


extern boot_dbginfo_if_type dbginfo_if;

/* Exposing API directly for handling early errors in XBL */
bl_error_boot_type boot_is_oem_lcs_dev_state(boot_boolean *status);

#endif /* BOOT_SECLIB_IF_H */
