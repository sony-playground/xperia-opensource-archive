#ifndef BOOT_FLASHLESS_SAHARA_H
#define BOOT_FLASHLESS_SAHARA_H
/*=============================================================================

                     Boot Flashless Sahara Device Driver

GENERAL DESCRIPTION
  This file contains the implementation for the boot-specific whitelist based
  protection module, to facilitate preventing the bootloader address spaces
  from being overwritten by a flash load.

Copyright 2019 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
11/26/19   rhy          Initial revision.
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_media_interface_if.h"


#define BL_ERR_FLASHLESS_CUSTOM_ERROR_START 0x100

typedef enum
{
    BL_ERROR_SAHARA_NAK_INVALID_CMD             =    BL_ERR_CUSTOM_ERRORS_START,
    BL_ERROR_SAHARA_NAK_PROTOCOL_MISMATCH,
    BL_ERROR_SAHARA_NAK_INVALID_TARGET_PROTOCOL,
    BL_ERROR_SAHARA_NAK_INVALID_HOST_PROTOCOL,
    BL_ERROR_SAHARA_NAK_INVALID_PACKET_SIZE,
    BL_ERROR_SAHARA_NAK_UNEXPECTED_IMAGE_ID,
    BL_ERROR_SAHARA_NAK_INVALID_HEADER_SIZE,
    BL_ERROR_SAHARA_NAK_INVALID_DATA_SIZE,
    BL_ERROR_SAHARA_NAK_INVALID_IMAGE_TYPE,
    BL_ERROR_SAHARA_NAK_INVALID_TX_LENGTH,
    BL_ERROR_SAHARA_NAK_INVALID_RX_LENGTH,
    BL_ERROR_SAHARA_NAK_GENERAL_TX_RX_ERROR,
    BL_ERROR_SAHARA_NAK_READ_DATA_ERROR,
    BL_ERROR_SAHARA_NAK_UNSUPPORTED_NUM_PHDRS,
    BL_ERROR_SAHARA_NAK_INVALID_PDHR_SIZE,
    BL_ERROR_SAHARA_NAK_MULTIPLE_SHARED_SEG,
    BL_ERROR_SAHARA_NAK_UNINIT_PHDR_LOC,
    BL_ERROR_SAHARA_NAK_INVALID_DEST_ADDR,
    BL_ERROR_SAHARA_NAK_INVALID_IMG_HDR_DATA_SIZE,
    BL_ERROR_SAHARA_NAK_INVALID_ELF_HDR,
    BL_ERROR_SAHARA_NAK_UNKNOWN_HOST_ERROR,
    BL_ERROR_SAHARA_NAK_TIMEOUT_RX,
    BL_ERROR_SAHARA_NAK_TIMEOUT_TX,
    BL_ERROR_SAHARA_NAK_INVALID_HOST_MODE,
    BL_ERROR_SAHARA_NAK_INVALID_MEMORY_READ,
    BL_ERROR_SAHARA_NAK_INVALID_DATA_SIZE_REQUEST,
    BL_ERROR_SAHARA_NAK_MEMORY_DEBUG_NOT_SUPPORTED,
    BL_ERROR_SAHARA_NAK_INVALID_MODE_SWITCH,
    BL_ERROR_SAHARA_NAK_CMD_EXEC_FAILURE,
    BL_ERROR_SAHARA_NAK_EXEC_CMD_INVALID_PARAM,
    BL_ERROR_SAHARA_NAK_EXEC_CMD_UNSUPPORTED,
    BL_ERROR_SAHARA_NAK_EXEC_DATA_INVALID_CLIENT_CMD,
    BL_ERROR_SAHARA_NAK_HASH_TABLE_AUTH_FAILURE,
    BL_ERROR_SAHARA_NAK_HASH_VERIFICATION_FAILURE,
    BL_ERROR_SAHARA_NAK_HASH_TABLE_NOT_FOUND,
    BL_ERROR_SAHARA_NAK_TARGET_INIT_FAILURE,
    BL_ERROR_SAHARA_NAK_IMAGE_AUTH_FAILURE,
    BL_ERROR_SAHARA_NAK_INVALID_IMG_HASH_TABLE_SIZE, 
    BL_ERROR_SAHARA_NAK_TRANSPORT_INIT_FAILURE,
    BL_ERROR_SAHARA_NAK_BULK_TRANSFER_ERROR,
    /* Place all new STATUS error above this */
    BL_ERROR_SAHARA_NAK_LAST_CODE,
    
    
    BL_ERR_NO_FLASHLESS_SUPPORT                   =  BL_ERR_FLASHLESS_CUSTOM_ERROR_START,

} bl_error_sahara_flashless_type;

bl_error_boot_type boot_flashless_dev_get_interface(void *media_interface_if);

#endif //BOOT_FLASHLESS_SAHARA_H