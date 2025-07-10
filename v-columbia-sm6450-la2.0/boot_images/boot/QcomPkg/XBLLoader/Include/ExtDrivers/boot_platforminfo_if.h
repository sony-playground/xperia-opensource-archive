#ifndef BOOT_PLATFORMINFO_IF_H
#define BOOT_PLATFORMINFO_IF_H

/*===========================================================================

                    BOOT PLATFORMINFO IF DEFINITIONS

DESCRIPTION
  Contains definition for platform info interface

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019,2021 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/03/21   ds      platforminfo init
08/02/19   ep      Created the file
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "DDIPlatformInfo.h"
#include "DalDevice.h"


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 




typedef struct boot_platforminfo_if_type
{
	DALResult (*CDTConfigPreDDR)(DalDeviceHandle * _h, void * pMem);
	DALResult (*CDTConfigPostDDR)(DalDeviceHandle * _h, void * pMem);
	DalPlatformInfoPlatformType (*Platform)(void);                                                
	DALResult (*PlatformInfo)(void * pPlatforminfo);
	DALResult (*ChipId)(void * pChipSetId);
	DALResult (*ChipFamily)(void * pChipsetfamily);
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
