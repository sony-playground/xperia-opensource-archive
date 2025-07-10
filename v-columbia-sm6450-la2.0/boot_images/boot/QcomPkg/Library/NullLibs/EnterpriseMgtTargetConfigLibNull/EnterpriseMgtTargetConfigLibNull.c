/**
  @file EnterpriseMgtTargetConfigLibNull.c
  @brief EnterpriseMgtTargetConfigLibNull library functions.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.0/QcomPkg/Library/NullLibs/EnterpriseMgtTargetConfigLibNull/EnterpriseMgtTargetConfigLibNull.c#1 $
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