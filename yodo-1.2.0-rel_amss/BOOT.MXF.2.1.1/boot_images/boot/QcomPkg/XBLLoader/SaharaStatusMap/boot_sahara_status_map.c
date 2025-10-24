/*=============================================================================

                     Boot Sahara Status Mapping

GENERAL DESCRIPTION
  This file contains the mapping between bl_error_boot_type and boot_sahara_status.

Copyright 2020-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
11/23/20   rhy          Initial revision.
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_sahara_status_map_if.h"
#include "boot_sahara.h"
#include "boot_whitelist_if.h"
#include "boot_elf_loader.h"
#include "boot_mbn_loader.h"

/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

typedef struct
{
    bl_error_boot_type client_error;
    boot_sahara_status sahara_status;
}boot_sahara_status_map;


boot_sahara_status_map sahara_status_map[] = 
{
    {(BL_ERR_NONE),                                                        SAHARA_STATUS_SUCCESS},
    {(BL_ERROR_GROUP_MBN_LOADER | BL_ERR_MBN_LOADER_IMAGE_ID_MISMATCH),    SAHARA_NAK_UNEXPECTED_IMAGE_ID},
    {(BL_ERROR_GROUP_LOADER_IF  | BL_ERR_NO_FLASH) ,                       SAHARA_NAK_INVALID_IMAGE_TYPE},
    {(BL_ERROR_GROUP_WHITELIST  | BL_ERR_NOT_IN_WHITELIST),                SAHARA_NAK_INVALID_DEST_ADDR  },
    {(BL_ERROR_GROUP_ELF_LOADER | BL_ERR_IMAGE_HDR_INVALID),               SAHARA_NAK_INVALID_ELF_HDR },
    {(BL_ERROR_GROUP_ELF_LOADER | BL_ERR_HASH_TBL_AUTH_FAIL),              SAHARA_NAK_HASH_TABLE_AUTH_FAILURE},
    {(BL_ERROR_GROUP_ELF_LOADER | BL_ERR_ELF_LOADER_AUTH_FAILED),          SAHARA_NAK_HASH_VERIFICATION_FAILURE},
    {(BL_ERROR_GROUP_ELF_LOADER | BL_ERR_ELF_LOADER_HASH_SEGMENT_FAILURE), SAHARA_NAK_HASH_TABLE_NOT_FOUND},
};

/*=============================================================================

FUNCTION DEFINITIONS

=============================================================================*/
/*=========================================================================

**  Function :  boot_sahara_get_status

** ==========================================================================
*/
/*!
* 
* @brief
*   mapping bl_error_boot_type to boot sahara status
* 
* @param[in]
* 
*/
bl_error_boot_type boot_sahara_get_status(bl_error_boot_type client_error,
                                          boot_sahara_status *status)
{
    bl_error_boot_type return_status = BL_ERR_NONE;
    boot_sahara_status_map *curr_map_entry = sahara_status_map;
    /* Get number of entries of sahara_status_map */
    uint32 sahara_status_map_size = sizeof(sahara_status_map)/sizeof(boot_sahara_status_map), index = 0;
    
    if(status == NULL)
    {
        return_status = GET_ERROR_CODE(BL_ERROR_GROUP_SAHARA_STATUS_MAP, BL_ERR_NULL_PTR_PASSED);
        goto exit;
    }
    
    /* Parse the curr_map_entry for mapping error to Sahara status */
    for(index = 0; index < sahara_status_map_size; index++)
    {
        if( (curr_map_entry[index].client_error) == client_error )
        {
            *status = (curr_map_entry[index].sahara_status);
            goto exit;
        }
    }
    
    /* if no mapping is found, add SAHARA_NAK_ERROR_NOT_MAPPED to client_error */
    *status = SAHARA_NAK_ERROR_NOT_MAPPED + client_error;
    
  exit:
    return return_status;
}

boot_sahara_status_map_handler_if sahara_status_map_if = {
    boot_sahara_get_status      /* get_mapped_sahara_status */
};
