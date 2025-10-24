/*===========================================================================

                    BOOT NVMe DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external NVMe drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/16/20   sp      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <boot_nvme_if.h>
#include <nvme_api.h>

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 
/*===========================================================================
**  Function :  nvme_if
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes NVMe interface
*
* @par Dependencies
*   None 
* 
*/

boot_nvme_if_type nvme_if = {
    nvme_read,
    nvme_write,
    nvme_flush,
    nvme_open,
    nvme_close,
    nvme_get_namespace_sizes,
    nvme_get_device_info
};
