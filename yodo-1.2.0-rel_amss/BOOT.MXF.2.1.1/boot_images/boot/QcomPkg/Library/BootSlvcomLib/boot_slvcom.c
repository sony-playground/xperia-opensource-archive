/*===========================================================================

                    BOOT SLAVECOM INTERFACE DEFINITIONS

DESCRIPTION
  Contains definition for Slave com if

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/10/22   batta    Initial revision
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <boot_slvcom_if.h>
#include "slvcom.h"


slvcom_open_config_type slv_open_config;
slvcom_handle_type slv_handle;

/*=========================================================================

**  FUNCTION  boot_slvcom_init

**  [in] params : None.

**  [RETURN] : BL_ERR_NONE, if success.
               BOOT slvcom specific error in case of failure.

===========================================================================*/

bl_error_boot_type boot_slvcom_driver_init(void)
{
   bl_error_boot_type status = BL_ERR_NONE;

   /* Initialize SLVCOM interface */

   // slvcom_init doesn't return anything. If there's any error, a fatal error
   // log will be printed from SLVCOM Library.
   slvcom_init();

   /* Initialize SLVCOM specific structures. */
   SLVCOM_OPEN_CONFIG_INIT(&slv_open_config);
   slv_open_config.name = "Helios";

   // Opens/Creates a handle to interact with slave. */
   status = slvcom_open(&slv_open_config, &slv_handle);
   if(status != BL_ERR_NONE) {
      return GET_ERROR_CODE(BL_ERROR_GROUP_SLVCOMINFO_IF, BL_ERR_BOOT_SLVCOM_OPEN_FAILURE);
   }

   // Makes Non-secure to active low to indicate secure communication.
   status = slvcom_secmode_enable(&slv_handle);
   if(status != BL_ERR_NONE) {
      return GET_ERROR_CODE(BL_ERROR_GROUP_SLVCOMINFO_IF, BL_ERR_BOOT_SLVCOM_SECMODE_ENABLE_FAILURE);
   }

   return BL_ERR_NONE;
}

/*=========================================================================

**  FUNCTION  boot_slvcom_init

**  [in] params : buf - Sahara buffer passed from Sahara Client.
                  offset - Restricted region address.
                  size - Restricted region size.

**  [RETURN] : BL_ERR_NONE, if success.
               Boot slvcom specific error in case of failure.
===========================================================================*/

bl_error_boot_type boot_slvcom_ahb_read(uint8 *buf, uint64 offset, uint64 size)
{
   bl_error_boot_type status = BL_ERR_NONE;

   // Slave AHB memory read.
   status = slvcom_ahb_read(slv_handle, offset, (size >> 2), buf, SAHARA_MAX_MEMORY_DATA_SIZE_IN_BYTES);
   
   if(status != BL_ERR_NONE) {
      return GET_ERROR_CODE(BL_ERROR_GROUP_SLVCOMINFO_IF, BL_ERR_BOOT_SLVCOM_AHB_READ_FAILURE);
   }

   return BL_ERR_NONE;
}
    
/*=========================================================================

** Boot SLVCOM interface initialization.

==========================================================================*/
boot_slvcom_if_type boot_slvcom_if = {
    boot_slvcom_driver_init,
    boot_slvcom_ahb_read
};
