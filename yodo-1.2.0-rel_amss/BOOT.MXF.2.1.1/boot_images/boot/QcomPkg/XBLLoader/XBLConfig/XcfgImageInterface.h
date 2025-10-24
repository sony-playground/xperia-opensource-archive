#ifndef XBL_CONFIG_IMAGE_INT_H
#define XBL_CONFIG_IMAGE_INT_H
/*=============================================================================

                      XBLConfig Image Interface Module Sources

GENERAL DESCRIPTION
  This file defines XBL config api's that interface with Elf image
  load module.

Copyright 2016, 2017, 2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
10/16/20     rama     Added xcfg_image_interface table.
03/27/17     kpa      Added xcfg_image_interface_reset
03/03/17     kpa      Added xcfg_load_addr_validation_init, deinit
02/14/17     kpa      Rename XBLCONFIG_ERR_NONE to XBLCONFIG_SUCCESS
                      added xcfg_validate_data
10/14/16     kpa      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_framework.h"
#include "XBLConfig.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/


/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/
typedef struct xcfg_image_interface_type{
  xblconfig_status_type (*init)(boot_handle);
  xblconfig_status_type (*get_max_logical_block_count)(uintnt *);
  xblconfig_status_type (*get_block_info)(uintnt, uintnt *, uintnt *);
  xblconfig_status_type (*get_block_data)(uintnt, uintnt, void *, boot_boolean);
  xblconfig_status_type (*deinit)(void);
  xblconfig_status_type (*reset)(void);
  xblconfig_status_type (*get_metadata_size)(uint32 *);
}xcfg_image_interface_type;

extern xcfg_image_interface_type xcfg_loader_image_interface;
extern xcfg_image_interface_type xcfg_ram_addr_image_interface;

/*===========================================================================
**  Function :  xcfg_validate_data
** ==========================================================================
*/
/*!
* 
* @brief
*   This function verifies the loaded XBLConfig item.
*   It is an intermediate api to add image meta data (eg segment info) 
*   needed by authentication api's which do the actual validation.
* 
* @param[in]    
*     start_offset      location of requested item data within partition
*     config_item_size  Pointer to size of data to be verified
*     buffer            Pointer to data to be verified
*
* @param[out] 
*  None
*        
* @par Dependencies
*   buffer is assumed to be populated with data to be verified
*   
* @retval
*   xblconfig_status_type. XBLCONFIG_SUCCESS if no error else error value
* 
* @par Side Effects
*   None
* 
*/
xblconfig_status_type xcfg_validate_data
(
  uintnt start_offset,
  uintnt config_item_size,
  void *buffer  
);

/*===========================================================================
**  Function :  xcfg_verified_config_data_read
** ==========================================================================
*/
/*!
* 
* @brief
*   This function reads XBLConfig item and later proceeds to validate it
*   (eg verify its hash in context of elf image).
*
* @param[in]    
*     start_offset      location of requested item data within partition
*     config_item_size  size of data to be verified
*     buffer            Pointer to data to be verified
*
* @param[out] 
*  None
*        
* @par Dependencies
*   buffer is assumed to be big enough for data to be read and verified
*   
* @retval
*   xblconfig_status_type. XBLCONFIG_SUCCESS if no error else error value
* 
* @par Side Effects
*   None
* 
*/
xblconfig_status_type xcfg_verified_config_data_read
(
  uintnt start_offset,
  uintnt config_item_size,
  void *buffer
);

/*===========================================================================
**  Function :  xcfg_load_addr_validation_init
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes load address validation module
*  (such as whitelist checks)
* 
* @param[in]    
*  None
*
* @param[out] 
*  None
*        
* @par Dependencies
*   None
*   
* @retval
*   xblconfig_status_type. XBLCONFIG_SUCCESS if no error else error value
* 
* @par Side Effects
*   None
* 
*/
xblconfig_status_type xcfg_load_addr_validation_init(boot_handle config_context_handle);

/*===========================================================================
**  Function :  xcfg_load_addr_validation_deinit
** ==========================================================================
*/
/*!
* 
* @brief
*   This function deinitializes load address validation module
*  (such as whitelist checks)
* 
* @param[in]    
*  None
*
* @param[out] 
*  None
*        
* @par Dependencies
*   None
*   
* @retval
*   xblconfig_status_type. XBLCONFIG_SUCCESS if no error else error value
* 
* @par Side Effects
*   None
* 
*/
xblconfig_status_type xcfg_load_addr_validation_deinit (void);


#endif /* XBL_CONFIG_IMAGE_INT_H */
