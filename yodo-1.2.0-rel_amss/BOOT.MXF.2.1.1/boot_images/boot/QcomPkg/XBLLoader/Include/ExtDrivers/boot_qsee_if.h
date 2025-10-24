#ifndef BOOT_QSEE_INTERFACE_H
#define BOOT_QSEE_INTERFACE_H

/*===========================================================================

                          Boot SBL QSEE Interface

GENERAL DESCRIPTION
 Contains common defintion used by SBL and QSEE.

Copyright 2013-2015,2017,2020-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/22/22   ck      Increased BOOT_IMAGES_NUM_ENTRIES to 25
09/11/20   rama    Added set parameter API and remove bl_shared_data dependencies
03/03/17   ds     remove clobber prot
06/25/15   as      Removed boot_sbl_qsee_interface_get_appsbl_entry
06/25/15   as      Added boot_sbl_qsee_interface_get_image_entry
06/22/15   ck      Added boot_sbl_qsee_interface_get_appsbl_entry
05/25/15   kpa     Added "reset_required" to boot_sbl_qsee_interface
02/19/15   kpa     Added appsbl_entry_index to boot_sbl_qsee_interface
02/19/15   kpa     Update boot_sbl_qsee_interface
10/29/14   kpa     Support 64 bit memory map
11/20/14   kedara  Code cleanup,update to to include MIheader.h
10/29/14   ck      Updated to support 64 bit addresses
05/07/14   kedara  Include boot_target.h for BOOT_IMAGES_NUM_ENTRIES define
04/02/14   ck      Updated boot_sbl_qsee_interface to Bear 2.0 BAS spec
04/01/14   ck      Updated pbl_secboot_verified_info_type to secboot_verified_info_type
                   as Bear PBL now uses common secboot lib.
03/21/14   ck      Added boot_sbl_qsee_interface_get_eident and
                   boot_sbl_qsee_interface_get_entry_point functions
12/02/13   ck      Initial creation
============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include "MIprogressive.h"
#include "MIheader.h"
#include "boot_whitelist_if.h"  // !!! decouple this
#include "secboot.h"

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/

/* SBL - QSEE Magic Number 1 */
#define SBL_QSEE_MAGIC_NUMBER_1  0xCE473D94

/* SBL - QSEE Magic Number 2 */
#define SBL_QSEE_MAGIC_NUMBER_2  0x3CB237BA

/* Third version */
#define SBL_QSEE_INTERFACE_VERSION 4

#define BOOT_IMAGES_NUM_ENTRIES 25

/*---------------------------------------------------------------------------
  Reset types support.
---------------------------------------------------------------------------*/
typedef enum
{
  NO_RESET = 0x0,
  RESET_DEVICE_BY_QSEE = 0x1
} reset_required_status_type;

/*---------------------------------------------------------------------------
  SBL Boot Images Entry Structure
  
  For each image loaded by SBL, there is a matching image entry in the
  boot_sbl_qsee_interface structure that is passed to QSEE at the end of 
  SBL execution.  The boot_images_entry structure is populated by the logic
  that loads the image.
---------------------------------------------------------------------------*/

typedef struct boot_images_entry
{
  secboot_sw_type image_id;
  uint32 e_ident;
  uint64 entry_point;
  secboot_verified_info_type image_verified_info;
  uint32 reserved_1;
  uint32 reserved_2;
  uint32 reserved_3;
  uint32 reserved_4;

} boot_images_entry;


/*---------------------------------------------------------------------------
  SBL - QSEE Interface Structure
  
  The following is needed by QSEE and is populated during SBL execution.
---------------------------------------------------------------------------*/

typedef struct boot_qsee_interface
{  
  uint32 magic_1;
  uint32 magic_2;
  uint32 version;
  uint32 number_images;
  uint32 reset_required;
  boot_images_entry boot_image_entry[BOOT_IMAGES_NUM_ENTRIES];
  uint64 ddr_enter_self_refresh;
  uint64 ddr_exit_self_refresh;
  uint32 appsbl_entry_index;
  uint32 reserved_2;
} boot_qsee_interface;

typedef enum boot_qsee_param_type
{
  BOOT_QSEE_PARAM_RESET_REQUIRED,
  BOOT_QSEE_PARAM_IMAGE_ID,
  BOOT_QSEE_PARAM_IMAGE_E_IDENT,
  BOOT_QSEE_PARAM_IMAGE_ENTRY_POINT,
  BOOT_QSEE_PARAM_DDR_ENTER_SELF_REFRESH,
  BOOT_QSEE_PARAM_DDR_EXIT_SELF_REFRESH,
  BOOT_QSEE_PARAM_APPSBL_ENTRY_INDEX,
  BOOT_QSEE_PARAM_IMAGE_ENTRY_INDEX,
  BOOT_QSEE_PARAM_MAX_ID = 0x7FFFFFFF
}boot_qsee_param_type;

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/


typedef struct boot_qsee_if_type
{
  bl_error_boot_type (*init)(void);
  bl_error_boot_type (*get_qsee_interface_ptr)(boot_qsee_interface * ptr);
  bl_error_boot_type (*get_value)(secboot_sw_type image_id, boot_qsee_param_type parameter_id, uintnt * entry_index);
  bl_error_boot_type (*set_value)(boot_qsee_param_type parameter_id, uintnt value);
} boot_qsee_if_type;


/*===========================================================================
**  Function :  boot_qsee_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_qsee_get_interface
*
* @par Dependencies
*   None 
* 
*/

//bl_error_boot_type boot_qsee_get_interface(boot_qsee_if_type *qsee_if);

extern boot_qsee_if_type qsee_if;


#endif /* BOOT_QSEE_INTERFACE_H */
