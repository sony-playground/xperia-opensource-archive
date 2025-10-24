/*=============================================================================

                                BOOT RAM Initialization

GENERAL DESCRIPTION
  This file contains the software that performs the SBL RAM initialization
  and scatter loading regions.

Copyright 2010-2011, 2013-2015, 2017, 2018, 2020, 2022 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
10/13/22   rama    use config_context to get pbl_media
09/16/20   rama    Fix PBL interface parameter casting issue
09/11/20   rama    Added BOOT_PBL_H
09/10/20   ds      updates for PBL shared data
07/23/20   rama    Added pbl_shared_data_if
05/10/20   ds      move to edk2 arm mmu/cache lib
05/07/20   ck      Replaced boot_pbl_get_flash_type with boot_pbl_get_media_type
04/23/18   kpa     Update boot_device_type in shared imem
07/13/17   yps     Flush boot imem region after init boot imem which is cacheable
10/05/15   ck      Corrected copyright
02/12/14   ck      boot_shared_imem_cookie structure now has version entry that gets set
10/22/13   ck      Removed rpm_sync_cookie from boot_shared_imem_init as it is
                   no longer needed in Bear Family
05/01/13   jz      Clear RPM sync cookie at startup
06/07/11   dh      use boot_shared_imem_cookie_ptr instead of hardcoding
                   cookie addresses.
02/24/11   dh      add boot_shared_imem_init to initialized boot shared imem
08/06/10   aus     Clean-up
07/22/10   aus     Initial revision
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <string.h>
#include "boot_comdef.h"
#include "boot_ram_init.h"
#include "boot_sbl_if.h"
#include "boot_shared_imem_cookie.h"
#include "boot_error_if.h"
#include <Library/CacheMaintenanceLib.h>
#include <boot_media_types.h>

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
/*Define a global pointer which points to the boot shared imem cookie structure */
struct boot_shared_imem_cookie_type *boot_shared_imem_cookie_ptr =
  (struct boot_shared_imem_cookie_type *)SHARED_IMEM_BOOT_BASE;


/*=============================================================================

                              FUNCTION DEFINITIONS

=============================================================================*/
/*============================================================================

**  Function : boot_ram_init

** ==========================================================================
*/
/*!
*
* @brief
*   Copy initialized data (RW-DATA) into RAM. And, Zero-out (ZI-DATA) in RAM.
*   See the file sbl*.scl for a description of the structure of RAM.
*
* @param[in] boot_ram_init_data Pointer which contains the addresses for the
*                               RW and ZI load regions and execute regions
*
* @par Dependencies
*   None.
*
* @retval
*   True if success, fail otherwise
*
* @par Side Effects
*   Memory not in the RW region and Zero-Init region is
*   not affected by this function -- those locations are left in an
*   unknown state.
*
*/
bl_error_boot_type boot_ram_init( boot_ram_init_data_type *boot_ram_init_data )
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  /* Copy RW data from load to image region only if load and image
     regions are different. */
  if ( boot_ram_init_data->load_rw_base != boot_ram_init_data->image_rw_base)
  {
    /* Copy RW data from the load region to the execute region .*/
    memcpy( boot_ram_init_data->image_rw_base,
            boot_ram_init_data->load_rw_base,
            (uint32)(uintptr_t)boot_ram_init_data->image_rw_len);
  }

  /* Zero out the zero-init data segment. */
  memset( boot_ram_init_data->image_zi_base, 0, (uint32)(uintptr_t)boot_ram_init_data->image_zi_len);

  return return_status;

} /* boot_ram_init() */


/*===========================================================================

**  Function :  boot_shared_imem_init

** ==========================================================================
*/
/*!
*
* @brief
*   This funcion will initialize the boot shared imem to all 0xFFFFFFFF value if
*   it has not been initialized yet.
*
* @param[in] bl_shared_data Pointer to shared data
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
bl_error_boot_type boot_shared_imem_init(boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_media_type boot_media = MEDIA_TYPE_MAX;
  /*Make sure size of the cookie struct doesn't exceed the boot shared imem size*/

  do
  {
    if (sizeof(struct boot_shared_imem_cookie_type) > SHARED_IMEM_BOOT_SIZE)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_RAM, BL_ERR_TOO_MEMORY_FAILURE);
      break;
    }

    /*First check to see if magic number is present*/
    if (boot_shared_imem_cookie_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_RAM, BL_ERR_UNINITIALIZED_VARIABLE);
      break;
    }
    if (boot_shared_imem_cookie_ptr->shared_imem_magic !=
        BOOT_SHARED_IMEM_MAGIC_NUM)
    {
      /*If magic number is not there then
        intialize the whole boot shared imem to 0xFFFFFFFF*/
      memset((void*)boot_shared_imem_cookie_ptr,
             SHARED_IMEM_REGION_DEF_VAL,
             SHARED_IMEM_BOOT_SIZE);

      boot_shared_imem_cookie_ptr->shared_imem_magic =
        BOOT_SHARED_IMEM_MAGIC_NUM;

      boot_shared_imem_cookie_ptr->shared_imem_version =
        BOOT_SHARED_IMEM_VERSION_NUM;

      return_status = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_PBL_MEDIA_BOOT_DEVICE, &boot_media);
      if(return_status != BL_ERR_NONE)
      {
        break;
      }

      boot_shared_imem_cookie_ptr->boot_device_type = boot_media;

      WriteBackInvalidateDataCacheRange((void *)SHARED_IMEM_BOOT_BASE, SHARED_IMEM_BOOT_SIZE);
    }
  } while (FALSE);

  return return_status;
}

