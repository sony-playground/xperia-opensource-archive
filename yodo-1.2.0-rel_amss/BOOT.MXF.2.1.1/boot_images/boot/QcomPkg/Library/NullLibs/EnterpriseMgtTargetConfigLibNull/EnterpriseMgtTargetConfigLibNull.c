/**
  @file EnterpriseMgtTargetConfigLibNull.c
  @brief EnterpriseMgtTargetConfigLibNull library functions.
*/
/*=============================================================================
  Copyright (c) 2020,2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NullLibs/EnterpriseMgtTargetConfigLibNull/EnterpriseMgtTargetConfigLibNull.c#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/
#include <Uefi.h>
#include <Base.h>
#include <string.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Library/EnterpriseMgtTargetConfigLib.h>

/**
  Library function to get EnterpriseMgt platform specific lock register address.

  @retval UINT32  : EnterpriseMgt Lock register address.
**/
EFIAPI
UINT32
EnterpriseMgtGetLockRegAddress( VOID )
{
    return 0;
}

/**
  Library function to read EnterpriseMgt platform specific configurations.

  @retval NULL   : Unable to find the right platform specific configuration.
  @retval VOID * : Pointer to the platform specific configuration.
**/
EFIAPI
VOID *
EnterpriseMgtGetPlatformCfg( VOID )
{
    VOID *ReturnCfg = NULL;   
    return ReturnCfg;
}

/**
  Library function to check whether given feature is Software controlled.
  @param[in]  Feature ID.

  @retval TRUE   : Given feature is Software controlled.
  @retval FALSE  : Given feature is Entp Mgmt Hardware controlled.
**/
EFIAPI
BOOLEAN
EnterpriseMgtIsSWFeature( IN UINT32 FeatureType )
{
    UNUSED_PARAM(FeatureType);
    return TRUE;
}

/**
  Library function to disable the feature with a software implementation.
  @param[in]  Feature ID.

  @retval TRUE   : Feature is disabled successfully.
  @retval FALSE  : Failed to disable the feature.
**/
EFIAPI
BOOLEAN 
EnterpriseMgtProcessSWFeatureDisablePolicy( IN UINT32 FeatureType )
{
    UNUSED_PARAM(FeatureType);
    return TRUE;
}

/**
  Helper Library function to call target specific functions after locking the Entp Mgmt registers.

  @retval EFI_STATUS   : Return status of target specific function calls.
**/
EFIAPI
EFI_STATUS 
EnterpriseMgtPostLockBitCalls( VOID )
{
    EFI_STATUS  status = EFI_SUCCESS;
    return status;
}
