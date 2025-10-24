/** @file DTBLoaderLib.h

  Copyright (c) 2022 Qualcomm Technologies, Inc. All rights reserved.
 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/04/22   tmt     Initial creation of Library

=============================================================================*/

#ifndef DTBLOADERLIB_H_
#define DTBLOADERLIB_H_

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include <boot_error_if.h>
#include <boot_config_context.h>

/*=========================================================================
     API Function Prototypes
==========================================================================*/
/**
 * boot_pre_ddr_dtb_load - Load pre_ddr DTB
 * @config_context_handle:
 *
 * returns: 0 (success) else error indicator
 */
bl_error_boot_type boot_pre_ddr_dtb_load(boot_handle config_context_handle);

/**
 * boot_post - Load post_ddr DTB
 * @config_context_handle:
 *
 * returns: 0 (success) else error indicator
 */
bl_error_boot_type boot_post_ddr_dtb_load(boot_handle config_context_handle);

#endif  /* DTBLOADERLIB_H_ */
