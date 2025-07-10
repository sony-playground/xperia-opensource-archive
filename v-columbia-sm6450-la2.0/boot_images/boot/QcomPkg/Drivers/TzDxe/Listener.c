/** @file Listener.c
   
  Implementation of listener internal APIs.

  Copyright (c) 2019-2020 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
   
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/13/20   shl     Added support for smc invoke support
 04/12/20   shl     More code optimization
 07/04/19   shl     Initial revision

 =============================================================================*/
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIListenerDef.h>


// local table for recording listener info
#define MAX_LISTENER_NUM   10

STATIC struct 
{
   UINT32                       ListenerId;
   QcomScmListenerCallbackPtr   CallbackPtr;
   VOID                        *CallbackHandle;
   UINT8                       *SharedBufferPtr;
   UINTN                        SharedBufferLen;

} ListenerTable[MAX_LISTENER_NUM] = { {0, NULL, NULL, NULL, 0} };


UINT32 ListenerGetTableSize( )
{
   return MAX_LISTENER_NUM;
}


UINT32 ListenerGetId( UINT32 Index )
{
   if( Index < MAX_LISTENER_NUM )
      return ListenerTable[Index].ListenerId;
   else
      return 0; 
}


BOOLEAN IsListenerIdValid( UINT32 ListenerId )
{
   if( ListenerId == 0 )
      return FALSE;

   for( UINT32 i = 0; i < MAX_LISTENER_NUM; i++ )
   {
      if( ListenerId == ListenerTable[i].ListenerId )
         return TRUE;
   }

   return  FALSE;
}


EFI_STATUS ListenerExec( UINT32 ListenerId )
{
   EFI_STATUS  Status = EFI_NOT_FOUND;

   for( UINT32 i = 0; i < MAX_LISTENER_NUM; i++ )
   {
      if( ListenerId == ListenerTable[i].ListenerId )
      {
         if( ListenerTable[i].CallbackPtr == NULL )
            continue; 

         // Call the callback function 
         Status = ListenerTable[i].CallbackPtr( ListenerTable[i].CallbackHandle,
                                                ListenerTable[i].SharedBufferPtr,
                                                ListenerTable[i].SharedBufferLen);
         break;

      }
   }

   return  Status;
}


EFI_STATUS ListenerRegister
( 
   UINT32                        ListenerId,
   QcomScmListenerCallbackPtr    CallbackPtr,  
   VOID                         *CallbackHandle,
   UINT8                        *SharedBufferPtr,
   UINTN                         SharedBufferLen
)
{
   if( ListenerId == 0 || CallbackPtr == NULL ) 
      return EFI_INVALID_PARAMETER;

   for( UINT32 i = 0; i < MAX_LISTENER_NUM; i++ )
   {
      if (ListenerTable[i].ListenerId == 0)
      {
         ListenerTable[i].ListenerId      = ListenerId;
         ListenerTable[i].CallbackPtr     = CallbackPtr;
         ListenerTable[i].CallbackHandle  = CallbackHandle;
         ListenerTable[i].SharedBufferPtr = SharedBufferPtr;
         ListenerTable[i].SharedBufferLen = SharedBufferLen;

         return EFI_SUCCESS;
      }
   }

   return EFI_OUT_OF_RESOURCES;

}


VOID ListenerDeregisterByIndex( UINT32 Index )
{
   if( Index < MAX_LISTENER_NUM )
   {
      ListenerTable[Index].ListenerId      = 0;
      ListenerTable[Index].CallbackPtr     = NULL;
      ListenerTable[Index].CallbackHandle  = NULL;
      ListenerTable[Index].SharedBufferPtr = NULL;
      ListenerTable[Index].SharedBufferLen = 0;
   }

   return;
}


VOID ListenerDeregisterById( UINT32 Id )
{
   for( UINT32 i = 0; i < MAX_LISTENER_NUM; i++ )
   {
      if( ListenerTable[i].ListenerId == Id)
      {
         ListenerDeregisterByIndex( i );
         break;
      }
   }

   return;
}



STATIC UINT32 SmcInvokeRegisteredCbMsgBufLen = 0;

VOID SmcInvokeSetCbMsgBufLen( UINT32 len )
{
   SmcInvokeRegisteredCbMsgBufLen = len;
   return;
}


UINT32 SmcInvokeGetCbMsgBufLen( )
{
   return SmcInvokeRegisteredCbMsgBufLen;
}
