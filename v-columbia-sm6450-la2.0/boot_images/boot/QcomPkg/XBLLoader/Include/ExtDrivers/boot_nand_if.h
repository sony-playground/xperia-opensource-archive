#ifndef BOOT_NAND_IF_H
#define BOOT_NAND_IF_H

/*===========================================================================

                    BOOT EXTERN NAND DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external nand driver

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
07/15/20   ck      Added nand_update_partition_tbl_smem
03/30/20   ck      Initial Creation

===========================================================================*/

/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "boot_comdef.h"
#include "boot_config_context.h"
#include "nand_api.h"


typedef struct boot_nand_if_type
{
  NAND_STATUS (* nand_open)(uint32 dev_id, const uint8 * partition_name, nand_handle_t *handle);
  NAND_STATUS (* nand_close)(nand_handle_t handle, uint32 close_all);
  NAND_STATUS (* nand_get_info)(nand_handle_t handle, struct nand_info * nand_info);
  NAND_STATUS (* nand_block_set_state)(nand_handle_t handle, uint32 block, enum nand_block_state block_state);
  NAND_STATUS (* nand_block_get_state)(nand_handle_t handle, uint32 block, enum nand_block_state * block_state);
  NAND_STATUS (* nand_erase)(nand_handle_t handle, uint32 start_block, uint32 block_count);
  NAND_STATUS (* nand_write)(nand_handle_t handle, enum page_access_opcode opcode, uint32 start_page, uint32 page_count, void * buffer, uint32 buffer_size);
  NAND_STATUS (* nand_read)(nand_handle_t handle, enum page_access_opcode opcode, uint32 start_page, uint32 page_count, void * buffer, uint32 buffer_size);
  NAND_STATUS (* nand_reinit)(void);
  NAND_STATUS (* nand_update_partition_tbl_smem)(void);
} boot_nand_if_type;


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

/*===========================================================================
**  Function :  boot_nand_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_nand_get_interface
*
* @par Dependencies
*   None 
* 
*/

extern boot_nand_if_type nand_if;


/*===========================================================================
**  Function :  boot_nand_store_partition_table
** ==========================================================================
*/
/*!
* 
* @brief
*   Store nand partition table in SMEM
*   
* @par Dependencies
*   SMEM needs to be initialized 
*      
* @retval
*   None                                                               
* 
* @par Side Effects
*   None
* 
*/
bl_error_boot_type boot_nand_store_partition_table(boot_handle config_context_handle);


#endif  /* BOOT_NAND_IF_H */
