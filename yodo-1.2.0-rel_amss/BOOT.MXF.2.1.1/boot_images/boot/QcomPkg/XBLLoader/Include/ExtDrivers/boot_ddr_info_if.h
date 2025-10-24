#ifndef BOOT_DDR_INFO_IF_H
#define BOOT_DDR_INFO_IF_H

/*=============================================================================

                       Boot DDR Information

GENERAL DESCRIPTION
  This module implements functions that update and share ddr info in SBL

Copyright 2010-2011, 2015, 2020 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
--------     ---     ----------------------------------------------------------
07/22/2020   dai     Update DDR extended info 
10/05/2015   ck      Corrected copyright
05/25/2011   plc     Added prototype for boot_share_extended_ddr_info
07/28/2010   dh      Initial creation(implemented by Kedar)

============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include "ddr_drivers.h"
#include "boot_ddr_types.h"

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/


typedef struct boot_ddr_info_if_type
{
  bl_error_boot_type (*init)(boot_handle);
  bl_error_boot_type (*deinit)(void);
  bl_error_boot_type (*share_extended_ddr_info)(boot_ddr_device_info_type *);
  bl_error_boot_type (*set_ddr_info)(boot_ddr_device_info_type *ddr_shared_info_ptr);
  boot_ddr_device_info_type *(*get_ddr_info)(void);
  bl_error_boot_type (*populate_ddr_details_shared_table )(boot_handle config_context_handle);
} boot_ddr_info_if_type;


/*===========================================================================
**  Function :  boot_ddr_info_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_ddr_info_get_interfaceobject 
*
* @par Dependencies
*   None 
* 
*/

//bl_error_boot_type boot_ddr_info_get_interface(void *ptr);


extern boot_ddr_info_if_type ddr_info_if;

#endif  /* BOOT_DDR_INFO_IF_H */
