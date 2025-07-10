/** @file SmcInvokeCompat.c

  SmcInvokeCompat.c implements smc invoke compatible support which is an interim solution
  to transition from legacy tz apps calls to Mink invoke calls, in this solution the 
  existing clients will not be impacted and all legacy tz apps calls will be internally
  converted to smc invoke calls.

  Once all clients have switched to the new smc invoke calls in their tz apps, this 
  support will retire. 

  Copyright (c) 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/12/20   shl     Initial version

 =============================================================================*/

#include <stdlib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <string.h>
#include <object.h>
#include "IClientEnv.h"
#include "IQSEEComCompat.h"
#include "IQSEEComCompatAppLoader.h"
#include "SmcInvokeApi.h"

#define ELFCLASSNONE    0      /* Unknown class. */
#define ELFCLASS32      1      /* 32-bit architecture. */
#define ELFCLASS64      2      /* 64-bit architecture. */

const static uint32_t CQSEEComCompatAppLoader_UID = 122;

/* Becasue QTEE will not support AppId in smc invoke, we need to support on
 * NS side so our clients will not be imapcted. To diff with the lagacy AppId, 
 * a prefix of 0xFFFF0000 is added to the lagacy appId which starts from 1. */
#define  APP_ID_PREFIX   0xFFFF0000

#define  NUM_OF_APPS     20
#define  MAX_NAME_SIZE   64

typedef struct
{
   Object    clientEnv;
   Object    appLoad;
   Object    appController;
   uint32_t  archType;
   uint32_t  id;
   uint8_t   name[MAX_NAME_SIZE];
   size_t    nameSize;
} AppCtx;

static AppCtx   *appCtxTable       = NULL;
static uint32_t  appCtxTableIndex  = 0;

static Object  clientEnv = Object_NULL;
static Object  appLoad   = Object_NULL;


/**
 * Get a freed index of appCxtTable
 */
static inline EFI_STATUS GetFreeTableIndex( uint32_t *index )
{
   uint32_t i;

   for( i = 0; i < NUM_OF_APPS; ++i )
   {
      if( appCtxTable[i].id == 0 )
      {
         *index = i;
         return EFI_SUCCESS; 
      }   
   }

   return EFI_OUT_OF_RESOURCES; 
}


/**
 * Convert an appId to the index of appCxt
 */
static inline EFI_STATUS AppIdToIndex( uint32_t appId, uint32_t *index )
{
   if( !(appId & APP_ID_PREFIX ) )
        return EFI_NOT_FOUND; 

   *index = appId & (~APP_ID_PREFIX);
                                                           
    if( *index == 0 || *index > (NUM_OF_APPS - 1) )
        return EFI_INVALID_PARAMETER;

    --(*index);

    return EFI_SUCCESS; 
}


/**
 * Init smc invoke compatible API
 */
EFI_STATUS SmcInvokeCompatInit()
{ 
   EFI_STATUS  Status = SmcInvokeGetClientEnv( &clientEnv );
   if( Status || Object_isNull(clientEnv ))
	     goto Exit;

   int32_t ret = IClientEnv_open( clientEnv, CQSEEComCompatAppLoader_UID, &appLoad );
   if( Object_isERROR(ret) || Object_isNull(appLoad ))
   {
      Object_release( clientEnv );
      DEBUG((EFI_D_ERROR, "IClientEnv_open failed ret = %d \r\n", ret ));
      Status = EFI_DEVICE_ERROR;
      goto Exit;
   }

   appCtxTable = ( AppCtx *)AllocateZeroPool( sizeof(AppCtx)*NUM_OF_APPS );
   if( !appCtxTable )
      return EFI_OUT_OF_RESOURCES;

Exit:

   return Status;

}


/**
 * Deinit smc invoke compatible API
 */
void SmcInvokeCompatDeinit()
{
   uint32_t ret;
   uint32_t i;

   for( i = 0; i < NUM_OF_APPS; ++i )
   {
      if( !Object_isNull( appCtxTable[i].appController) )
      {
         /* disconnect apps loaded through smc invoke compatible module,
            so at HLOS time these apps still can be connected and used. */
         ret = IQSEEComCompat_disconnect( appCtxTable[i].appController );
         if( Object_isERROR(ret) )
            DEBUG((EFI_D_ERROR, "IQSEEComCompat_disconnect failed, appId = 0x%x  ret = 0x%x\n", appCtxTable[i].id, ret));

         Object_ASSIGN_NULL( appCtxTable[i].appController );

         appCtxTable[i].nameSize = 0;
      }
   }     

   Object_RELEASE_IF( appLoad );
   Object_RELEASE_IF( clientEnv );

   FreePool( appCtxTable );

   return;
}


/**
 * Load an app through  smc invoke compatible API
 */
EFI_STATUS SmcInvokeCompatStartApp( const void      *image,  
                                          uint32_t   imageSize,
                                          uint32_t  *appId )
{
   EFI_STATUS status;
   uint32_t   i;

   if( image == NULL || imageSize == 0 || appId == NULL )
      return EFI_INVALID_PARAMETER;

   if( appCtxTableIndex < NUM_OF_APPS )
   {
      i = appCtxTableIndex;
      ++appCtxTableIndex;
   }
   else
   {
      /* let's see if there is a freed index, nomarl case should not come here, this is
         for some bizarre test case, like keep loading/unloading TAs. */ 
      status = GetFreeTableIndex( &i );
      ASSERT( status == EFI_SUCCESS );
   }

   int32_t ret = IQSEEComCompatAppLoader_loadFromBuffer( appLoad,
                                                         image, 
                                                         imageSize,
                                                         NULL,
                                                         0,
                                                         appCtxTable[i].name,
                                                         MAX_NAME_SIZE,
                                                        &appCtxTable[i].nameSize,
                                                        &appCtxTable[i].appController );
   if( Object_isERROR(ret) )
   {
      DEBUG((EFI_D_ERROR, "IQSEEComCompatAppLoader_loadFromBuffer failed ret = %d \n", ret));
      appCtxTable[i].appController = Object_NULL;
      return EFI_DEVICE_ERROR;
   }

   appCtxTable[i].archType = ELFCLASS64;
   appCtxTable[i].id       = ( i + 1 ) | APP_ID_PREFIX;

   *appId = appCtxTable[i].id;

   return EFI_SUCCESS;
}


/**
 * Unload an app through smc invoke compatible API
 */
EFI_STATUS SmcInvokeCompatShutdownApp( uint32_t appId )
{
   EFI_STATUS status;
   uint32_t   i;

   status = AppIdToIndex( appId, &i );
   if( status != EFI_SUCCESS )
      return status;

   Object_ASSIGN_NULL( appCtxTable[i].appController );

   appCtxTable[i].archType = ELFCLASSNONE;
   appCtxTable[i].id       = 0;

   memset(appCtxTable[i].name, 0, MAX_NAME_SIZE );
   appCtxTable[i].nameSize = 0;

   return EFI_SUCCESS;
}


/**
 * Send an app through  smc invoke compatible API
 */
EFI_STATUS SmcInvokeCompatSendCmd( uint32_t   appId,
                                   void      *req,
                                   uint32_t   reqLen,
                                   void      *rsp,
                                   uint32_t   rspLen )
{
   EFI_STATUS status;
   uint32_t i;

   status = AppIdToIndex( appId, &i );
   if( status != EFI_SUCCESS )
      return status;

   if( Object_isNull( appCtxTable[i].appController) )
      return EFI_DEVICE_ERROR;

   size_t  out_len = 0;
   int32_t ret = IQSEEComCompat_sendRequest( appCtxTable[i].appController,
                                             req, reqLen,
                                             rsp, rspLen,
                                             req, reqLen, &out_len,
                                             rsp, rspLen, &out_len,
                                             NULL, 0,
                                             (appCtxTable[i].archType == ELFCLASS64)? 1:0,
                                             Object_NULL, Object_NULL,
                                             Object_NULL, Object_NULL);
    if( Object_isERROR(ret) )
    {
       DEBUG((EFI_D_ERROR, "IQSEEComCompat_sendRequest failed ret = 0x%x\r\n", ret ));
       return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}


/**
 * Look up an app ID through smc invoke compatible API
 */
EFI_STATUS SmcInvokeCompatLookupAppId( const uint8_t   *name,
                                             uint32_t   nameSize,
                                             uint32_t  *appId )
{
   uint32_t i;

   /* trim off unneeded NULL */
   while( nameSize > 0 && name[nameSize-1] == '\0')
      --nameSize;

   if( appId == NULL || nameSize == 0 || nameSize > MAX_NAME_SIZE )
      return EFI_INVALID_PARAMETER;

   for( i = 0; i < NUM_OF_APPS; ++i )
   {
      if( appCtxTable[i].nameSize == nameSize && memcmp(appCtxTable[i].name, name, nameSize ) == 0 )
      {
         *appId = appCtxTable[i].id;
          return EFI_SUCCESS;
      }
   }  

   return EFI_NOT_FOUND;;
}

