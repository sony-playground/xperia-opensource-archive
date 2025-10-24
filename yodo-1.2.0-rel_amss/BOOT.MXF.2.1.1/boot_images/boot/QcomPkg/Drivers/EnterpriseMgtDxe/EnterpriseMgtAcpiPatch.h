/**
  @file EnterpriseMgtAcpiPatch.h
  @brief EnterpriseMgt dxe functions to register a callback for ACPI platform dxe init event.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/EnterpriseMgtDxe/EnterpriseMgtAcpiPatch.h#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/
#ifndef __ENTERPRISEMGTACPIPATCH_H__
#define __ENTERPRISEMGTACPIPATCH_H__

#include "EnterpriseMgtDxeBaseDef.h"

/**
  Function to register a callback for ACPI platform dxe init event.

  @retval EFI_SUCCESS           Registered successfully.
  @retval CreateEvent() or  RegisterProtocolNotify() returned value.
**/
EFI_STATUS EnterpriseMgtRegisterForAcpiPlatform (
    IN ENT_MGT_PROCESSED_POLICY *pPolicy
    );

#endif /*__ENTERPRISEMGTACPIPATCH_H__*/