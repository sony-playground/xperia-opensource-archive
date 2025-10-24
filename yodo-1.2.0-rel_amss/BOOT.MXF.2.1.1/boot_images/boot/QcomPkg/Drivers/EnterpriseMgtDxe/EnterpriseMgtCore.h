/**
  @file EnterpriseMgtCore.h
  @brief EnterpriseMgt dxe core functions.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/EnterpriseMgtDxe/EnterpriseMgtCore.h#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/
#ifndef __ENTERPRISEMGTCORE__H__
#define __ENTERPRISEMGTCORE__H__

#include <Protocol/EFIEnterpriseMgt.h>
#include "EnterpriseMgtDxeBaseDef.h"

/**
  Helper function to program EnterpriseMgt LOCK registers.

  @param  RegisterAddress   EnterpriseMgt LOCK register address.
  @param  BitMask           EnterpriseMgt LOCK bitmask to program.
  @param  Value             EnterpriseMgt LOCK register bit value to program.

  @retval TRUE              EnterpriseMgt LOCK register programmed successfully.
  @retval FALSE             EnterpriseMgt LOCK register programming failed.
**/
BOOLEAN EnterpriseMgtLockRegXBit (
    IN UINT32 RegisterAddress, 
    IN UINT32 BitMask, 
    IN UINT32 Value
    );

/**
  Processes Enterprise Management client policies to disable hardware features
  and stores the processed information policy structure.

  @param[in] pStore  Structure having list of features to disable.
  
  @retval EFI_SUCCESS            Successfully processed requested client policies.
  @retval EFI_NOT_FOUND          Platform configuration error.
  @retval EFI_INVALID_PARAMETER  Invalid arguments.
  @retval EFI_OUT_OF_RESOURCES   Memory allocation failed for internal usage.
  @retval EFI_DEVICE_ERROR       Internal error while processing requested client policies.
  @retval EFI_VOLUME_CORRUPTED   Internal context data corruption after processing client policies.
  @retval SetVariable() or FlushVariableServices() returned error code.

**/
EFI_STATUS 
EFIAPI 
EnterpriseMgtProcessClientPolicies (
    IN ENT_MGT_POLICY_STORE *pStore
    );

#endif /*__ENTERPRISEMGTCORE__H__*/