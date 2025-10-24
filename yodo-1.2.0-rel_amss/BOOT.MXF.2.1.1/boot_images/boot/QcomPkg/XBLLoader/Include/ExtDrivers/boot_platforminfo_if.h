#ifndef BOOT_PLATFORMINFO_IF_H
#define BOOT_PLATFORMINFO_IF_H

/*===========================================================================

                    BOOT PLATFORMINFO IF DEFINITIONS

DESCRIPTION
  Contains definition for platform info interface

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019,2021-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/05/22   rama    add PlatformSubtype and PlatformVersion to boot_platform_if_type
04/03/21   ds      platforminfo init
08/02/19   ep      Created the file
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "DDIPlatformInfo.h"
#include "DalDevice.h"
#include "boot_error_if.h"


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 




typedef struct boot_platforminfo_if_type
{
  DALResult (*CDTConfigPreDDR)(DalDeviceHandle * _h, void * pMem);
  DALResult (*CDTConfigPostDDR)(DalDeviceHandle * _h, void * pMem);
  bl_error_boot_type (*Platform)(DalPlatformInfoPlatformType * platform);
  bl_error_boot_type (*PlatformSubtype)(uint32 * platform_sub_type);
  bl_error_boot_type (*PlatformVersion)(uint32 * platform_version);
  bl_error_boot_type (*PlatformInfo)(void * pPlatforminfo);
  bl_error_boot_type (*ChipId)(void * pChipSetId);
  bl_error_boot_type (*ChipFamily)(void * pChipsetfamily);
  bl_error_boot_type (*get_platforminfo_data)(DalPlatformInfoPlatformType *pType, uint32 *pSubtype, uint32 *pVersion);
  boolean (*IsFusion) (void);
  DALResult (*Init) (void);
  
} boot_platforminfo_if_type;


/*===========================================================================
**  Function :  boot_platforminfo_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_platforminfo_if
*
* @par Dependencies
*   None 
* 
*/

//bl_error_boot_type boot_platforminfo_get_interface(void *ptr);


extern boot_platforminfo_if_type platforminfo_if;

#endif /* BOOT_PLATFORMINFO_IF_H */
