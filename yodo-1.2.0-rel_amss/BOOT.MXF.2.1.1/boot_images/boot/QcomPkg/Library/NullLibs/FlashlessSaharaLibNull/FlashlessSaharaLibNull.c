/**
  Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/16/21   ck      Added edit history and copyright

=============================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_config_context.h"
#include "boot_media_interface_if.h"


/*=========================================================================
                       MACRO DEFINITIONS
==========================================================================*/


/*=========================================================================
      Data
==========================================================================*/


/*=========================================================================
      Function Prototypes
==========================================================================*/


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

/*=========================================================================

**  Function :  boot_flashless_dev_get_interface

** ==========================================================================
*/
/*!
* 
* @brief
*   hook up the block dev apis to media interface
* 
* @param[in] pointer to boot_media_interface_if_type
* 
*/
bl_error_boot_type boot_flashless_dev_get_interface(void *media_interface_if)
{
  bl_error_boot_type error = BL_ERR_NONE;
  
  if(media_interface_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_SAHARA, BL_ERR_INVALID_PARAMETER);
  }
  
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_init =     NULL;
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_deinit =   NULL;
  ((boot_media_interface_if_type *)media_interface_if)->open =              NULL;
  ((boot_media_interface_if_type *)media_interface_if)->close =             NULL;
  ((boot_media_interface_if_type *)media_interface_if)->read =              NULL;
  ((boot_media_interface_if_type *)media_interface_if)->write =             NULL;
  ((boot_media_interface_if_type *)media_interface_if)->async_read =        NULL;
  ((boot_media_interface_if_type *)media_interface_if)->async_read_poll =   NULL;

  return error;
}

