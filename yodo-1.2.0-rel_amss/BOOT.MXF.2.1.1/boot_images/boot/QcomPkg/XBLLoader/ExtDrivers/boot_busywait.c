/*===========================================================================

                    BOOT BUSYWAIT WRAPPER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external authentication drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2019 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/23/19   ep      Created the file

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_error_if.h"
#include "MIprogressive.h"
#include "boot_busywait_if.h"
#include "CeML.h"
#include "busywait.h"

/*===========================================================================
                           DEFINITIONS
===========================================================================*/



/*===========================================================================
                      FUNCTION DEFINITIONS
===========================================================================*/



/*===========================================================================
**  Function :  boot_busywait_get_interface
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes a boot_crypto_if
*
* @par Dependencies
*   None
*
*/
/*
bl_error_boot_type boot_busywait_get_interface(void *ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    boot_busywait_if_type *busywait_if = (boot_busywait_if_type *)ptr;
    if(busywait_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_BUSYWAIT, BL_ERR_INVALID_PARAMETER);
      break;
    }

    busywait_if->init = busywait_init;
    busywait_if->busywait = busywait;

  } while(FALSE);

  return return_status;
}
*/

boot_busywait_if_type busywait_if =
{
  busywait_init,
  busywait
};
