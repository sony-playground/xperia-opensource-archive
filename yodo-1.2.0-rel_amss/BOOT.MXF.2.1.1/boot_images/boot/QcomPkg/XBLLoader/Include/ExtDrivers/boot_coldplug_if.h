#ifndef BOOT_COLDPLUG_IF_H
#define BOOT_COLDPLUG_IF_H

/*===========================================================================

                    BOOT EXTERN COLDPLUG DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external coldplug drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2017 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/22/17   ds      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_comdef.h"
#include "coldplug_api.h"
#include <../../../Library/ColdplugLib/inc/coldplug_priv_api.h>
#include "sdcc_api.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 



typedef struct boot_coldplug_if_type
{
  struct coldplug_handle* (*open_gpt_partition)(enum coldplug_device_type dev_type, int is_embedded_device, const struct coldplug_guid *guid);
  struct coldplug_handle* (*open_mbr_partition)(enum coldplug_device_type dev_type, int is_embedded_device, uint32 mbr_id);
  int (*close_partition )(struct coldplug_handle *chdl);
  int (*read)(struct coldplug_handle *chdl, uint64 lba, uint64 lba_count, uint8 *buf);
  int (*write)(struct coldplug_handle *chdl, uint64 lba, uint64 lba_count, uint8 *buf);
  int (*init)(void);
  void (*sdcc_boot_set_device_info)(sdcc_boot_device_info_type *device_info);
  int (*get_size)(struct coldplug_handle *chdl, uint32 *lba_size, uint64 *lba_count);
  int (*background_init_start)(enum coldplug_device_type device_type, int is_embedded_device, uint32 init_context);
  int (*open_boot_device)(enum coldplug_device_type dev_type, int is_embedded_device);
  int (*background_init_finish)(enum coldplug_device_type device_type, int is_embedded_device, uint32 init_context);
  int (*open_device)(enum coldplug_device_type dev_type, int is_embedded_device);

  struct coldplug_iter* (*iter_open)(enum coldplug_device_type dev_type, int is_embedded_device, int only_fat_partitions);
  int (*iter_close)(struct coldplug_iter *citer);
  struct coldplug_iter_record* (*iter_next)(struct coldplug_iter *citer);
  int (*get_start_lba)(struct coldplug_handle *chdl, uint64 *start_lba);
  struct coldplug_handle* (*open_partition)(const char *parti_name);

} boot_coldplug_if_type;


/*===========================================================================
**  Function :  boot_coldplug_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_coldplug_get_interface
*
* @par Dependencies
*   None 
* 
*/

//bl_error_boot_type boot_coldplug_get_interface(boot_coldplug_if_type *coldplug_if);

extern boot_coldplug_if_type coldplug_if;


#endif  /* BOOT_COLDPLUG_IF_H */
