/*===========================================================================

                    BOOT EEPROM DRIVER DEFINITIONS

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
#include "boot_error_if.h"
#include "boot_eeprom_if.h"


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
boot_eeprom_if_type eeprom_if = {
  eeprom_open,
  eeprom_close,
  eeprom_get_info,
  eeprom_write,
  eeprom_read
};
