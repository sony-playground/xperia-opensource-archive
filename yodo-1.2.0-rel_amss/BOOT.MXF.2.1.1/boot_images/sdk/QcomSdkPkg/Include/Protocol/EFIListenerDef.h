#ifndef LISTENER_DEF_H
#define LISTENER_DEF_H

/**
@file ListenerDef.h
@brief ListernDef definitions

*/
/*===========================================================================
Copyright (c) 2019 Copyright Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.
   
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE


when       who      what, where, why
--------   ---      ------------------------------------
06/30/19   shl      Initial version.

===========================================================================*/

/** @defgroup efi_listener_def_protocol EFI_LISTENER_DEF_PROTOCOL
 *  @ingroup UEFI_CORE 
 */
 /** @defgroup  efi_listener_def_protocol_prot PROTOCOL
 *  @ingroup efi_listener_def_protocol 
 */ 
 /** @defgroup  efi_listener_def_protocol_apis APIs
 *  @ingroup efi_listener_def_protocol 
 */ 

/** @defgroup  efi_listener_def_protocol_data DATA_STRUCTURES
 *  @ingroup efi_listener_def_protocol 
 */

/*----------------------------------------------------------------------------
 * Listener Services callback function pointer
 * -------------------------------------------------------------------------*/
/** @ingroup efi_listener_def_protocol_apis */

typedef EFI_STATUS(*QcomScmListenerCallbackPtr)
(
   IN VOID      *CallbackHandle,
   IN VOID      *SharedBufferPtr,
   IN UINT32     SharedBufferlen
);

#endif /* LISTENER_DEF_H */
