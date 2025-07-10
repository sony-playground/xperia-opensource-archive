#ifndef BOOT_EEPROM_IF_H
#define BOOT_EEPROM_IF_H

/*===========================================================================

                    BOOT EXTERN EEPROM DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external eeprom driver

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
05/12/20   ck      Initial Creation

===========================================================================*/

/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "boot_comdef.h"
#include "eeprom_api.h"


typedef struct boot_eeprom_if_type
{
  EEPROM_STATUS (* eeprom_open)(uint32 dev_id, eeprom_handle_t * handle);
  EEPROM_STATUS (* eeprom_close)(eeprom_handle_t handle);
  EEPROM_STATUS (* eeprom_get_info)(eeprom_handle_t handle, struct eeprom_info * eeprom_info);
  EEPROM_STATUS (* eeprom_write)(eeprom_handle_t handle, uint32 byte_offset, uint32 byte_count, void * buffer);
  EEPROM_STATUS (* eeprom_read)(eeprom_handle_t handle, uint32 byte_offset, uint32 byte_count, void * buffer);
} boot_eeprom_if_type;


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

/*===========================================================================
**  Function :  boot_eeprom_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_eeprom_get_interface
*
* @par Dependencies
*   None 
* 
*/

extern boot_eeprom_if_type eeprom_if;


#endif  /* BOOT_EEPROM_IF_H */
