#ifndef BOOT_SAHARA_CMD_HANDLER_IF_H
#define BOOT_SAHARA_CMD_HANDLER_IF_H

/*===========================================================================
                    BOOT SAHARA COMMAND HANDLER IF DEFINITIONS

DESCRIPTION
  Contains function pointers for Sahara Command handlers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2021 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/10/20   rhy     Inital revision

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_error_if.h"
#include "boot_framework.h"
#include "boot_comdef.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

typedef struct boot_sahara_command_handler_if
{                       
    bl_error_boot_type (*read_serial_number)(uint32*);
    
    bl_error_boot_type (*get_ddr_training)(uint32*, uint8**);
        
    /* Resets the target */
    bl_error_boot_type (*reset)    (void);
}boot_sahara_command_handler_if;


/*===========================================================================
**  Function :  boot_sahara_command_handler_table_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_sahara_command_handler_table_get_interface
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_sahara_command_handler_table_get_interface(void *sahara_cmd_handler_ptr);

#endif /* BOOT_SAHARA_CMD_HANDLER_IF_H */
