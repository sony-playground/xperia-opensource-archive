/*===========================================================================

                    BOOT PLATFORMINFO INTERFACE DEFINITIONS

DESCRIPTION
  Contains definition for platform info if

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
#include "PlatformInfo.h"
#include "MIprogressive.h"
#include "boot_error_if.h"
#include "boot_platforminfo_if.h"


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 



/*=========================================================================

**  FUNCTION  boot_DalPlatformInfo_Platform

===========================================================================*/
/**
  Return the current platform.

  This function is a wrapper around DalPlatformInfo_GetPlatform(). It provides
  platform retrieval without the code overhead of attaching to the DAL.

  @return
  DalPlatformInfoPlatformType() -- Current platform. \n
  DALPLATFORMINFO_TYPE_UNKNOWN  -- DAL device attach failed or cannot
                                   determine the platform.

  @dependencies
  None.

  @sa
  DalPlatformInfo_GetPlatform().
*/
DalPlatformInfoPlatformType boot_DalPlatformInfo_Platform(void)
{
  return PlatformInfo_Platform();
}

/*===========================================================================

**  Function :  boot_DalPlatformInfo_Platforminfo

** ==========================================================================
*/
/**
  Get platform information from memory.

  This function returns information about the current platform in the parameter
  pPlatforminfo.

  @param[in] Address to the location in memory that return 
                   information

  @return
  DAL_SUCCESS -- PlatformInfo DAL was configured successfully. \n
  DAL_ERROR   -- Invalid parameter.

  @dependencies
  None

*/

DALResult boot_DalPlatformInfo_PlatformInfo(void * pPlatforminfo)
{
  
  DalDeviceHandle        *phPlatformInfo = NULL;
  DALResult              eResult = DAL_SUCCESS ; 
  
  if (phPlatformInfo == NULL)
  {
    eResult = DAL_DeviceAttach(DALDEVICEID_PLATFORMINFO, &phPlatformInfo);
    if (eResult == DAL_SUCCESS)
    {
      eResult = DalPlatformInfo_GetPlatformInfo(phPlatformInfo, (DalPlatformInfoPlatformInfoType*)pPlatforminfo);
    }
  }
  
  
   return eResult;
}

/*===========================================================================

**  Function :  boot_DalPlatformInfo_ChipId

** ==========================================================================
*/
/**
  Get chipid from memory.

  This function returns chipid about the current platform in the parameter
  pChipSetId.

  @param[in] Address to the location in memory that return 
                   information.

  @return
  DAL_SUCCESS -- PlatformInfo DAL was configured successfully. \n
  DAL_ERROR   -- Invalid parameter.

  @dependencies
  None

*/

DALResult boot_DalPlatformInfo_ChipId(void * pChipSetId)
{
  
  DalDeviceHandle        *phChipInfo = NULL;
  DALResult              eResult = DAL_SUCCESS ; 
  
  if (phChipInfo == NULL)
  {
    eResult = DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &phChipInfo);
    if (eResult == DAL_SUCCESS)
    {
       eResult = DalChipInfo_GetChipId(phChipInfo, (DalChipInfoIdType *)pChipSetId); 
    }
   }
   return eResult;
}

/*===========================================================================

**  Function :  boot_DalPlatformInfo_ChipFamily

** ==========================================================================
*/
/**
  Get chipid from memory.

  This function returns chipsetfamily about the current platform in the parameter
  pChipsetfamily.

  @param[in] Address to the location in memory that return 
                   information

  @return
  DAL_SUCCESS -- PlatformInfo DAL was configured successfully. \n
  DAL_ERROR   -- Invalid parameter.

  @dependencies
  None

*/

DALResult boot_DalPlatformInfo_ChipFamily(void * pChipsetfamily)
{
  
  DalDeviceHandle        *phChipInfo = NULL;
  DALResult              eResult = DAL_SUCCESS ; 
 
  if (phChipInfo == NULL)
  {
    eResult = DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &phChipInfo);
    if (eResult == DAL_SUCCESS)
    { 
	   eResult = DalChipInfo_GetChipFamily( phChipInfo ,(DalChipInfoFamilyType *)pChipsetfamily);
    }

   }
   return eResult;
}


boot_platforminfo_if_type platforminfo_if = {
		DalPlatformInfo_CDTConfigPreDDR,
		DalPlatformInfo_CDTConfigPostDDR,
		boot_DalPlatformInfo_Platform,
		boot_DalPlatformInfo_PlatformInfo,
		boot_DalPlatformInfo_ChipId,
		boot_DalPlatformInfo_ChipFamily,
		DalPlatformInfo_IsFusion,
    PlatformInfo_Init
};
