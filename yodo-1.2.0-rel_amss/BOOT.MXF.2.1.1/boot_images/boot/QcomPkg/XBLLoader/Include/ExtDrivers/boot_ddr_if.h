#ifndef BOOT_DDR_IF_H
#define BOOT_DDR_IF_H
/*===========================================================================

                    BOOT DDR IF DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external ddr drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
 
    
when       who      what, where, why
--------   ---      ----------------------------------------------------------
01/22/21   rhy      Added setter and getter for DDR dump allowed
07/22/20   dai      Added get_ddr_region_param API 
08/06/19   ep       Initial Creation.
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_error_if.h"
#include "boot_framework.h"
#include "ddr_drivers.h"
#include "ddr_common.h"
#include <boot_modes.h>


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


typedef struct boot_ddr_if_type
{
  boolean (*set_params)(boolean dload_mode, boolean clock_configured);
  boolean (*initialize_device)(uint32 clk_speed, boot_mode_type boot_mode);
  ddr_size_info (*get_size)( void );
  ddr_size_partition (*get_partition)(void);
  boolean (*params_is_training_required)(void);
  void* (*params_get_training_data)(uint32 *size);
  boolean (*params_set_training_data)(void *ddr_training_data, uint32 size);
  boolean (*post_init)(void);
  ddr_info (*get_info)(void);
  bl_error_boot_type (*share_data_to_aop)(boot_handle config_context_handle);
  void (*test)(uint32 clk_speed);
  void (*debug)( void );
  void (*remapper)(void);
  boolean (*get_ddr_details_table)(ddr_details_entry_ptr_type ddr_details_entry_ptr);
  uint32 (*get_max_channels)();
  void (*post_setup)();
  void (*get_granule_size)(uint32* granule_size, uint32 ddr_rank);
  void (*do_phy_training_init)(void);
  boolean (*do_phy_training_restore)(void);
  boolean (*post_training)(void);
  boolean (*is_shrm_load_required)(void);
  void* (*params_get_data_buffer)(uint32 *size, uint8 index);
  uint32 (*get_num_of_ddr_regions)(void);
  bl_error_boot_type (*get_ddr_region_param)(uint8 region_index, DDR_PARAMS_ID param_id,  void *param_value, uint32 *param_size);
  void (*set_ddr_dump_allowed)(boolean);
  boolean (*get_ddr_dump_allowed)();
  void (*fw_exit)();
  bl_error_boot_type (*get_mte_syndrome_regions)(struct syndrome_struct *tag, uint32 *region_count);
  bl_error_boot_type (*shrm_mini_dump_init)(void);
  bl_error_boot_type (*get_dare_syndrome_regions)(struct syndrome_struct *tag, uint32 *region_count);
  uint32 (*get_tr_led_enable)(void);  
} boot_ddr_if_type;


/*===========================================================================
**  Function :  boot_ddr_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_ddr_get_interface
*
* @par Dependencies
*   None 
* 
*/

//bl_error_boot_type boot_ddr_get_interface(void *ptr);


extern boot_ddr_if_type ddr_if;


#endif /* BOOT_DDR_IF_H */
