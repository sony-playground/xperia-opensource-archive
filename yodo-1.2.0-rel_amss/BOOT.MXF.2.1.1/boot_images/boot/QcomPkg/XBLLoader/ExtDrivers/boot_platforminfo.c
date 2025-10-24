/*===========================================================================

                    BOOT PLATFORMINFO INTERFACE DEFINITIONS

DESCRIPTION
  Contains definition for platform info if

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
01/05/22   rama    Update platforminfo_if
04/03/21   ds      platforminfo init
08/02/19   ep      Created the file
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "DDIPlatformInfo.h"
#include "PlatformInfo.h"
#include "MIprogressive.h"
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

  @param[in] DalPlatformInfoPlatformType * -- Address to the location in memory that return 
                   information.

  @return
  BL_ERR_NONE on success

  @dependencies
  None.

  @sa
  DalPlatformInfo_GetPlatform().
*/
bl_error_boot_type boot_DalPlatformInfo_Platform(DalPlatformInfoPlatformType *platform)
{
  bl_error_boot_type status = BL_ERR_NONE;
  if(platform == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *platform = PlatformInfo_Platform();
  }

  return status;
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
  BL_ERR_NONE on success

  @dependencies
  None

*/

bl_error_boot_type boot_DalPlatformInfo_PlatformInfo(void * pPlatforminfo)
{
  bl_error_boot_type status = BL_ERR_NONE;
  DalDeviceHandle        *phPlatformInfo = NULL;
  DALResult              eResult = DAL_SUCCESS ; 

  do
  {

    if(pPlatforminfo == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    eResult = DAL_DeviceAttach(DALDEVICEID_PLATFORMINFO, &phPlatformInfo);
    if (eResult != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    eResult = DalPlatformInfo_GetPlatformInfo(phPlatformInfo, (DalPlatformInfoPlatformInfoType*)pPlatforminfo);
    if(eResult != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_INTERFACE_FAILURE);
      break;
    }
  }while(FALSE);

  return status;
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
  BL_ERR_NONE on success

  @dependencies
  None

*/

bl_error_boot_type boot_DalPlatformInfo_ChipId(void * pChipSetId)
{
  bl_error_boot_type status = BL_ERR_NONE;
  DalDeviceHandle        *phChipInfo = NULL;
  DALResult              eResult = DAL_SUCCESS ; 

  do
  {

    if(pChipSetId == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    eResult = DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &phChipInfo);
    if (eResult != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_INTERFACE_FAILURE);
      break;
    }
    eResult = DalChipInfo_GetChipId(phChipInfo, (DalChipInfoIdType *)pChipSetId);
    if(eResult != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_INTERFACE_FAILURE);
      break;
    }
  }while(FALSE);

  return status;
}

/*===========================================================================

**  Function :  boot_DalPlatformInfo_ChipFamily

** ==========================================================================
*/
/**
  Get chip family from memory.

  This function returns chipsetfamily about the current platform in the parameter
  pChipsetfamily.

  @param[in] Address to the location in memory that return 
                   information

  @return
  BL_ERR_NONE on success

  @dependencies
  None

*/

bl_error_boot_type boot_DalPlatformInfo_ChipFamily(void * pChipsetfamily)
{
  bl_error_boot_type status = BL_ERR_NONE;
  DalDeviceHandle        *phChipInfo = NULL;
  DALResult              eResult = DAL_SUCCESS ; 

  do
  {

    if(pChipsetfamily == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    eResult = DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &phChipInfo);
    if (eResult != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_INTERFACE_FAILURE);
      break;
    }
    eResult = DalChipInfo_GetChipFamily( phChipInfo ,(DalChipInfoFamilyType *)pChipsetfamily);
    if(eResult != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_INTERFACE_FAILURE);
      break;
    }
  }while(FALSE);

  return status;
}

/*===========================================================================

**  Function :  boot_DalPlatformInfo_PlatformSubtype

** ==========================================================================
*/
/**
  Get platform subtype from memory.

  This function returns chipsetfamily about the current platform in the parameter
  pChipsetfamily.

  @param[in] Address to the location in memory that return 
                   information

  @return
  BL_ERR_NONE on success

  @dependencies
  None

*/
bl_error_boot_type boot_DalPlatformInfo_PlatformSubtype(uint32 * platform_sub_type)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(platform_sub_type == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *platform_sub_type = PlatformInfo_PlatformSubtype();
  }

  return status;
}

/*===========================================================================

**  Function :  boot_DalPlatformInfo_PlatformVersion

** ==========================================================================
*/
/**
  Get platform version from memory.

  This function returns chipsetfamily about the current platform in the parameter
  pChipsetfamily.

  @param[in] Address to the location in memory that return 
                   information

  @return
  BL_ERR_NONE on success

  @dependencies
  None

*/
bl_error_boot_type boot_DalPlatformInfo_PlatformVersion(uint32 * platform_version)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if(platform_version == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_NULL_PTR_PASSED);
  }
  else
  {
    *platform_version = PlatformInfo_PlatformVersion();
  }

  return status;
}

/*==========================================================================
        Function to get platforminfo data
===========================================================================*/
static bl_error_boot_type boot_get_platforminfo_data(DalPlatformInfoPlatformType *pType, uint32 *pSubtype, uint32 *pVersion)
{
  bl_error_boot_type status = BL_ERR_NONE;

  do
  {
    if(pType == NULL || pSubtype == NULL || pVersion == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_DalPlatformInfo_Platform(pType);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_DalPlatformInfo_PlatformSubtype(pSubtype);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_DalPlatformInfo_PlatformVersion(pVersion);
    if(status != BL_ERR_NONE)
    {
      break;
    }

  }while(FALSE);

  return status;
}

boot_platforminfo_if_type platforminfo_if = {
    DalPlatformInfo_CDTConfigPreDDR,
    DalPlatformInfo_CDTConfigPostDDR,
    boot_DalPlatformInfo_Platform,
    boot_DalPlatformInfo_PlatformSubtype,
    boot_DalPlatformInfo_PlatformVersion,
    boot_DalPlatformInfo_PlatformInfo,
    boot_DalPlatformInfo_ChipId,
    boot_DalPlatformInfo_ChipFamily,
    boot_get_platforminfo_data,
    DalPlatformInfo_IsFusion,
    PlatformInfo_Init
};
