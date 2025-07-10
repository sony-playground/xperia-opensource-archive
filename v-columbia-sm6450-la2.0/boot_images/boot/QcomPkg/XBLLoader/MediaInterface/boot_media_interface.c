/*=============================================================================

                              Boot Media Interface

GENERAL DESCRIPTION
  Plugs the correct interface as per the boot media.

Copyright 2019-2020 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ----------------------------------------------------------
01/22/21   rhy          Added boot_media_booting_from_storage
05/13/20   ck           Added EepromDevLib
03/16/20   ck           Corrected FLASHLESS_ENABLED multi USB_FLASHLESS switch entries
09/29/19   digants      Initial revision.
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"
#include "boot_media_types.h"
#include "boot_config_context.h"
#include "boot_error_if.h"
#include "boot_media_interface_if.h"
#include "boot_block_dev.h"
#include "boot_eeprom_dev.h"
#include "boot_page_dev.h"   
#include "boot_flashless_sahara.h"


/*=============================================================================

                            DEFINITIONS

=============================================================================*/

/*=========================================================================

**  Function :  boot_media_get_interface

** ==========================================================================
*/
/*!
* 
* @brief
*   Routes to the correct media interface based in boot device.
* 
* @param[in] config context and pointer to media_interface_if
* 
*/
bl_error_boot_type boot_media_get_interface(const boot_handle config_context_handle, void *media_interface_if)
{
  bl_error_boot_type error = BL_ERR_NONE;
  boot_media_type boot_device = NO_FLASH;
  
  error = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, (void *)&boot_device);
  if(error != BL_ERR_NONE)
  {
    return error;
  }
  
  switch (boot_device)
  {
#ifdef BLOCKDEV_ENABLED
    case SDC_FLASH:
    case MMC_FLASH:
    case UFS_FLASH:
    case SPI_FLASH:
      error = boot_block_dev_get_interface(media_interface_if);
      break;
#endif


#ifdef PAGEDEV_ENABLED
    case NAND_FLASH:
      error = boot_page_dev_get_interface(media_interface_if);
      break;
#endif


#ifdef FLASHLESS_ENABLED
    case PCIE_FLASHLESS:
    case USB_FLASHLESS:
      error = boot_flashless_dev_get_interface(media_interface_if);
      if(error != BL_ERR_NONE)
      {
        break;
      }
      
      break;
#else
    case USB_FLASHLESS:
      /* For device programmer */
      break;
#endif


#ifdef EEPROMDEV_ENABLED
    case EEPROM_FLASH:
      error = boot_eeprom_dev_get_interface(media_interface_if);
      break;
#endif


    case NO_FLASH:
    default:
      error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_MEDIA_IF, BL_ERR_NO_FLASH);
      break;
  }
  return error;
}

/*===========================================================================

**  Function :  boot_media_booting_from_storage

** ==========================================================================
*/
/*!
*
* @brief
*   This function returns TRUE if boot_device is storage.
*
* @param[in]
*   None
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
bl_error_boot_type boot_media_booting_from_storage(boot_handle config_context_handle,
                                            boot_boolean *boot_from_storage_media)
{
    boot_media_type boot_device = NO_FLASH;
  
    // Get boot device from the context table
    bl_error_boot_type error = boot_config_context_get_value(config_context_handle, 
                                        CONFIG_CONTEXT_BOOT_DEVICE, (void *)&boot_device);
    if(error != BL_ERR_NONE)
    {
        return error;
    }
    
    switch (boot_device)
    {
   
        case SDC_FLASH:
        case MMC_FLASH:
        case UFS_FLASH:
        case SPI_FLASH:
        case NAND_FLASH:
        *boot_from_storage_media = TRUE;
        break;
        
        case PCIE_FLASHLESS:
        case USB_FLASHLESS:
        *boot_from_storage_media = FALSE;
        break;
   
        
    default:
        error = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_MEDIA_IF, BL_ERR_NO_FLASH);
    break;
    }
  return error;
}