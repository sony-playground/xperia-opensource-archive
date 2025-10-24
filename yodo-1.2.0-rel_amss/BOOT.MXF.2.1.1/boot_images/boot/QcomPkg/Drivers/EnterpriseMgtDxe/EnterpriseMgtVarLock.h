/**
  @file EnterpriseMgtVarLock.h
  @brief EnterpriseMgt dxe helper functions to lock UEFI variable.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/EnterpriseMgtDxe/EnterpriseMgtVarLock.h#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/
#ifndef __ENTERPRISEMGTVARLOCK_H__
#define __ENTERPRISEMGTVARLOCK_H__

#include "EnterpriseMgtDxeBaseDef.h"

/**
  Protocol function to lock EnterpriseMgt UEFI Variable.

  @retval EFI_SUCCESS          Locked successfully.
  @retval EnterpriseMgtLockUEFIVariable returned value.
**/
EFI_STATUS EnterpriseMgtLockNowVar( VOID );

/**
  Function to register a callback for Ready to Boot Event.

  @retval EFI_SUCCESS           Registered successfully.
  @retval EfiCreateEventReadyToBootEx returned value.
**/
EFI_STATUS EnterpriseMgtRegisterForReadyToBootEvent( VOID );

#endif /*__ENTERPRISEMGTVARLOCK_H__*/