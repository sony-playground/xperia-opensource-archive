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

/*----------------------------------------------------------------------------
 * Listener Services callback function pointer
 * -------------------------------------------------------------------------*/

typedef EFI_STATUS(*QcomScmListenerCallbackPtr)
(
   IN VOID      *CallbackHandle,
   IN VOID      *SharedBufferPtr,
   IN UINT32     SharedBufferlen
);

#endif /* LISTENER_DEF_H */
