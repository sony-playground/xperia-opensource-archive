/*===========================================================================

                    BOOT EFS COOKIE IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external efs cookie drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/20/20   rhy     Added init, stat and ipa_get
08/06/19   ep      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_efs_if.h"
#include "fs_public.h"


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


/*===========================================================================

**  Function :  boot_efs_handle_cookies

** ==========================================================================
*/
/*!
*
* @par Description:
*  Handles all the FS cookies that are set.
*  Also loads the EFS partitions from the eMMC card to the RAM.
**************************************************************************/
void boot_efs_handle_cookies(void)
{
  //efs_handle_cookies();
}


int boot_efs_get(const char *path, void *data, fs_size_t length)
{
    // efs_get()
    return 0;
}

int boot_efs_stat (const char *path, struct fs_stat *buf)
{
    return 0;
}

int boot_efs_read_only_initialize(){
    //efs_read_only_initialize();
    return 0;
}

boot_efs_if_type efs_if = {
    boot_efs_handle_cookies,
    boot_efs_read_only_initialize,
    boot_efs_stat,
    boot_efs_get
};

