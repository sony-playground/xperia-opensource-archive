/**
 * Copyright (c) 2020, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 */

/**
  @file SmcInvoke.c

  UEFI service for object invoke over SMC.  This service supports remote object 
  invoke, callback object invoke, and async op handling.

  SMC invoke service will be exposed as one of ScmDxe APIs, ScmGetClientEnv(), client 
  can use this API to get Client Environment Object, and then open more services through 
  this object.

  Below are high-level calling flows:

  1. Regular calling flow

            UEFI                       |                QTEE
                                       |
    remote invoke call                 | 
             |                         |
    invoke req msg marshal             |
  ( + async op req marshal in cbMsg)   |
             |                         |
          SMC call  ------------------------------> invoke req msg unmarshal  
                                                           |
                                                     remote obj invoke 
                                                           |
                                                      handle async op
                                                           |
             |<----------------------------------- invoke rsp msg marshal
             |                                    ( + callback req msg marshal )
             |                                    ( + async op req marshal in cbMsg )                  
     callback req msg ?
             |
       No    |  Yes
     ----------------  
     |              |
invoke rsp msg  callback req msg   
 unmarshal       unmarshal   
     |              | 
   handle     callback obj invoke  
async op req        |
     |        handle async op req
   done             | 
           callback rsp msg marshal 
           ( + async op req marshal ) ----------> callback rsp msg unmarshal
                                                           |
                                                     handle async op req
                                                           |
                    <-..........more callback reqs ........|
                    |
                    ......................................->
                                                           |
                                                     handle async op req
                                                           |
          invoke rsp msg unmarshal <-----------  invoke rsp msg marshal
                    |                                                                                                
             handle async op req
                    |
                  done


 2. On exiting UEFI

            UEFI                       |                QTEE
                                       |
    remote invoke call                 |
             |                         |
    invoke req msg marshal             |
   ( clientEnvObj release op)          | 
    ( + other async op req marshal)    |
             |                         |
          SMC call  ------------------------------> invoke req msg unmarshal  
                                                           |
                                                     remote obj invoke 
                                                           |
                                                      handle async op
                                                           |
             |<----------------------------------- invoke rsp msg marshal
             |                                    ( + async op req marshal )     
             |       
     rsp msg unmarshal      
             |       
     handle async op   
             |             
           done
  
*/
/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     -----------------------------------------------------------
01/26/23   shl     Update version check to tolerate different minor versions
10/05/20   shl     Changed API used
07/16/20   shl     Added Qsee log support
01/09/20   shl     Initial revision

=============================================================================*/
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <string.h>
#include <Library/UefiCfgLib.h>
#include <Protocol/EFIScm.h>
#include <Protocol/EFIShmBridge.h>
#include "Listener.h"
#include "Credential.h"
#include "IClientEnv.h"
#include "SMCInvoke.h"
#include "qsee_interface_armv8.h"
#include "tz_syscall.h"
#include "SmcInvokeApi.h"

#include "LogBuffer.h"

#define TEST_RETURN(xx)                                                      \
  do                                                                         \
  {                                                                          \
    if ((xx))                                                                \
    {                                                                        \
      DEBUG((EFI_D_ERROR, " ..%a:%d Failed!  ret = 0x%x  \n", __FUNCTION__, __LINE__, (xx)));   \
      goto Exit;                                                             \
    }                                                                        \
  } while(0)


#define TEST_TRUE(xx)                                                        \
  do                                                                         \
  {                                                                          \
    if (!(xx))                                                               \
    {                                                                        \
      DEBUG((EFI_D_ERROR, "..%a: %d Failed! \n", __FUNCTION__, __LINE__));   \
      goto Exit;                                                             \
    }                                                                        \
  } while(0)

#define ALIGN_UP(size, alignment)  (((size) + ((alignment)-1)) & ~((alignment)-1))

#define PAGE_SIZE       4096
#define ARGS_ALIGN(x)   ALIGN_UP(x, INVOKE_BUF_ALIGN_BYTES)
#define PAGE_ALIGN(x)   ALIGN_UP(x, PAGE_SIZE)  

/** asynch version uefi currently support */
#define SMCINVOKE_ASYNC_VERSION_LOCAL    SMCINVOKE_ASYNC_VERSION_1_1

/** global root env object */
static Object rootEnvObj = Object_NULL;

/** global client env object, all uefi clients will share this object */
static Object  clientEnvObj = Object_NULL;

/** Shared memory bridge protocol */
static EFI_SHMBRIDGE_PROTOCOL *ShmBridgeProtocol = NULL;

/** Local object table is used to track the local objects sent to QTEE.
  * Indexes in the local object table run from 0...maxLocalObj-1. */
#define HANDLE_TO_INDEX(h)     ( ((h)-1) & ~SmcInvokeObj_NS )
#define INDEX_TO_HANDLE(i)     ( ((i)+1) | SmcInvokeObj_NS )   

typedef struct 
{
   Object     obj;
   uint32_t   refs;
} LocalObjCxt;

/** maxLocalObj:    defines the max local object allowed in localObjTable, its value
  *                 is determined by SmcInvokeConfig in uefiplat.cfg
  * localObjTable:  stores local objects
  * numOfLocalObj:  track currently how many local objects in the table */
static size_t       maxLocalObj   = 256;
static LocalObjCxt *localObjTable = NULL;
static size_t       numOfLocalObj = 0;

/** Remote object table is used to track the remote objects received from QTEE.
  * Indexes in the remote object table run from 0...maxRemoteObj-1. */
#define REMOTE_HANDLE_MAGIC   0x24680ACE

typedef struct
{
   SmcInvokeObj  objHandle;
   uint32_t      magicNum;
   uint32_t      refs;
} RemoteObjCxt;

/** maxRemoteObj:    defines the max local object allowed in remoteObjTable, its value
 *                   is determined by SmcInvokeConfig in uefiplat.cfg
 *  remoteObjTable:  stores local objects
 *  numOfRemoteObj:  track currently how many remote objects in the table */
static size_t        maxRemoteObj   = 256;
static RemoteObjCxt *remoteObjTable = NULL;
static size_t        numOfRemoteObj = 0;

/** maxAsyncOp:       defines the max number of async ops allowed in localAsyncOpMsg/remoteAsyncOpMsg
 *                    its value is determined by SmcInvokeConfig in uefiplat.cfg
 *  asyncOpReqLen:    localAsyncOpMsg or remoteAsyncOpMsg length, will be assign a non-zero value in init.
 *  localAsyncOpMsg:  stores async ops to be sent to QTEE 
 *  remoteAsyncOpMsg: stores async ops received from QTEE */
static size_t          maxAsyncOp           = 256;
static size_t          asyncOpReqLen        = 0;
static AsyncOpMessage *localAsyncOpMsg      = NULL;
static AsyncOpMessage *remoteAsyncOpMsg     = NULL;
static bool            pendingRemoteAsyncOp = false;

/** common buf is used for all the above tables/req allocation */
static void   *commonBuf    = NULL;
static size_t  commonBufLen = 0;

extern VOID  *log_buffer;
extern UINT32 TzDiagVersion;

/** SCM call request structure */
static struct
{
  uint32_t    scmId;
  uint32_t    paramId;
  uintptr_t   arg[SCM_MAX_NUM_PARAMETERS];
} scmReq;

/** SCM call response array */
static uintptr_t  scmRsp[SCM_MAX_NUM_RESULTS] = {0};

/** Forward declarations */
static int32_t RemoteObj_invoke( ObjectCxt cxt, ObjectOp  op, ObjectArg *args, ObjectCounts counts );
static int32_t RemoteObj_invokeInternal( SmcInvokeObj objHandle, ObjectOp op, ObjectArg *args, ObjectCounts counts );

/** lower layer SCM call */
extern EFI_STATUS SysCallInternal
(
   IN  UINT32   SmcId,
   IN  UINT32   ParamId,
   IN  UINT64   Parameters[SCM_MAX_NUM_PARAMETERS],
   OUT UINT64   Results[SCM_MAX_NUM_RESULTS],
   OUT UINT64  *TrustedOsId
);


/**  Add a local object into the object table:
 *     1. a table index will be returned after a successful addition
 *     2. if the same object was already added before, increases refs and 
 *        returns the table index
 *     3. first time added object will be retained once to make sure it will
 *        not be deleted locally while it is still held by QTEE. The non-first
 *        time added object will only be increased refs
 *     4. will crash if no empty entry is available, developer should increase the
 *        table size and then give a try. In this way it is guaranteed that we 
 *        always have enough entries while the device is in the field.
 */
static int32_t LocalObj_add( Object obj, size_t *index )
{
   size_t freeEntry       = maxLocalObj;
   size_t numOfObjChecked = 0;

   for ( size_t i = 0; i < maxLocalObj; ++i )
   {
      if( !Object_isNull(localObjTable[i].obj) )
      {
         /* check the existing object */
         ++numOfObjChecked;
         if( localObjTable[i].obj.context == obj.context && localObjTable[i].obj.invoke == obj.invoke )
         {
            /* found it */
            ++localObjTable[i].refs;
            *index = i;

            return Object_OK;
         }
      }
      else
      {
         /* book the first free entry anyway, just in case the object is not in the table */
         if( freeEntry == maxLocalObj )
            freeEntry = i;
 
         /* bail out if the whole table is already checked */ 
         if( numOfObjChecked == numOfLocalObj )
            break;
      }
   }

   if ( freeEntry < maxLocalObj )
   {
      localObjTable[freeEntry].obj  = obj;
      localObjTable[freeEntry].refs = 1; 
      ++numOfLocalObj;
      Object_retain(obj);
      *index = freeEntry;
   }
   else
   {
      /* assert here so it can be caught at dev time */ 
      DEBUG((EFI_D_ERROR, "localObjTable is full!! Increase SmcInvokeMaxLocalObj in uefiplat.cfg \n"));
      ASSERT(0);
   }

   return Object_OK;
}


/**   Retrieve a local object based on input index of the local object table.
 *    The rectrieved object will be retained once to make sure it will
 *    not be deleted locally while it is still held by local clients. 
 *    it is the local clients' responsibility to release it after using it.
 */
static Object LocalObj_retrieve( size_t index )
{  
   Object obj = Object_NULL;

   if( index < maxLocalObj )
   {   
      obj = localObjTable[index].obj;
      if( !Object_isNull( obj ) )
         Object_retain( obj );
   }

   return obj;
}


/** 
 *   Delete an object based on input index of the object table
 */
static void LocalObj_delete( size_t index )
{
   if( index < maxLocalObj && !Object_isNull(localObjTable[index].obj ))
   {
      Object_release(localObjTable[index].obj);
      localObjTable[index].obj = Object_NULL;
      --numOfLocalObj;
   }

   return;
}


/** 
 *  Release a object based on input index of the object table
 */
static void LocalObj_release( size_t index )
{
   if( index < maxLocalObj    && 
       localObjTable[index].refs > 0   &&
       --localObjTable[index].refs == 0  )
      LocalObj_delete( index );

   return;
}


/**
 *   Create a remote object:
 *     1.  this function is called when a remote object(OO from local point of view)
 *         is detected in the message buffers from QTEE.
 *     2.  rootEnvObj is also created by calling this function.
 */
static int32_t RemoteObj_create( SmcInvokeObj objHandle, Object *remoteObj )
{ 
   size_t  i;

   for (  i = 0; i < maxRemoteObj; ++i )
   {
      if( remoteObjTable[i].magicNum == 0  )
      {
         remoteObjTable[i].objHandle = objHandle;   
         remoteObjTable[i].magicNum     = REMOTE_HANDLE_MAGIC;
         remoteObjTable[i].refs         = 1;
         ++numOfRemoteObj;

        *remoteObj = (Object){ RemoteObj_invoke, (void *)&remoteObjTable[i]};

         return Object_OK;
      }
   }

   /* assert here so it can be caught at dev time */ 
   DEBUG((EFI_D_ERROR, "remoteObjTable is full!! Increase SmcInvokeMaxRemoteObj in uefiplat.cfg \n"));
   ASSERT(0);

   return Object_ERROR_KMEM;
}


/**
 *  Retain a remote object
 */
static void RemoteObj_retain( RemoteObjCxt *me )
{
   ++me->refs;
   return;
}


/**
 *  Delete a remote object
 */
static void RemoteObj_delete( RemoteObjCxt *me )
{
   size_t i = ( (uintptr_t)me - (uintptr_t)remoteObjTable )/sizeof(remoteObjTable[0]);

   if( i < maxRemoteObj )
   {
      remoteObjTable[i].objHandle = 0;
      remoteObjTable[i].magicNum     = 0;
      remoteObjTable[i].refs         = 0;
      --numOfRemoteObj;
   }
   else
      DEBUG((EFI_D_ERROR, " RemoteObj_delete failed !!! %d \n"));

   return;
}


/**
 *  Release a remote object, this operation will cross the domain boundary when refs is 0
 *  To achieve better performance, this operation will be queued into pending async op array
 *  when refs is 0, and the pending async ops will be sent to QTEE in batch as a piggybacked 
 *  message of other SMC invoke message or a callback object request response message.
 */
static void RemoteObj_release( RemoteObjCxt *me )
{
   /* should never be here, but who knows what the client will do. */
   TEST_TRUE( me->refs != 0 );

   /* tamper proof, keep at least 1 ref for clientEnvObj, otherwise if other clients invoke
    * this object but it has already been released, there will be a crash. clientEnvObj is 
    * eventually released when exiting boot service. */
   TEST_TRUE( !( me->refs == 1 && me == clientEnvObj.context ));

   if( --me->refs == 0 )
   {
      /** Queue release op, will send release op in batch later */
      if( localAsyncOpMsg->opRelease.count < maxAsyncOp )
      {
         localAsyncOpMsg->opRelease.obj[localAsyncOpMsg->opRelease.count] = me->objHandle;
         ++localAsyncOpMsg->opRelease.count;
         RemoteObj_delete( me );
      }
      else
      {
         /* assert here so it can be caught at dev time */ 
         DEBUG((EFI_D_ERROR, "localAsyncOpMsg is too small!! Increase SmcInvokeMaxLocalAsyncOp in uefiplat.cfg \n"));
         ASSERT(0);
      }
   }

Exit:

   return;
}


/**
 *  Invoke a remote object. 
 *  Here is the remote invoke call sequence:
 *
 *     RemoteObj_invoke()
 *                 |---> RemoteObj_invokeInternal()
 *                                       |---> ScmCall()
 *                                                |---> SysCallInternal()
 */
static int32_t RemoteObj_invoke( ObjectCxt      cxt, 
                                 ObjectOp       op, 
                                 ObjectArg     *args, 
                                 ObjectCounts   counts )
{
   int32_t        ret             = Object_ERROR_INVALID;
   RemoteObjCxt  *me              = (RemoteObjCxt *)cxt;
   tzdbg_log_t   *log             = NULL;
   uint32_t       QseeLogStart    = 0;
   uint32_t       QseeLogNewStart = 0;

   EFI_TPL       PrevTPL = gBS->RaiseTPL( TPL_CALLBACK );

   TEST_TRUE( me != NULL );

   /* Reject operations on a dead object */
   TEST_TRUE( me->magicNum == REMOTE_HANDLE_MAGIC );

   if( ObjectOp_isLocal( op ) )
   {
      ret = Object_OK;
      switch( op )
      {
         case Object_OP_retain:
            RemoteObj_retain( me );
            break;
     
         case Object_OP_release:
            RemoteObj_release( me );
            break;

         default:   
            ret = Object_ERROR_REMOTE;
            break;
      }
   }
   else
   {  
      if (log_buffer)
      {
         if(TzDiagVersion < (UINT32)TZ_DIAG_LATEST_VERSION) // TZ diag version less than 9.1.0
         {
            log = (tzdbg_log_t*)log_buffer;
            QseeLogStart = (UINT32)(log->log_pos.log_Legacyheader.offset);
         }
         else // TZ diag version 9.1.0 and above
         {
            log = (tzdbg_log_t*)log_buffer;
            QseeLogStart = (UINT32)(log->log_pos.log_Latestheader.offset);
         }
      }

      RemoteObj_retain( me );
      ret = RemoteObj_invokeInternal( me->objHandle, op, args, counts );
      RemoteObj_release( me );

      if (log_buffer)
      {
         if(TzDiagVersion < (UINT32)TZ_DIAG_LATEST_VERSION) // TZ diag version less than 9.2.0
         {
            QseeLogNewStart = (UINT32)(log->log_pos.log_Legacyheader.offset);
         }
         else // TZ diag version 9.2.0 and above
         {
            QseeLogNewStart = (UINT32)(log->log_pos.log_Latestheader.offset);
         }
         DisplayQseeLog(QseeLogStart, QseeLogNewStart);
      }
   }

/* this is temparaily released for unblocking other team, will remove this after TZ support is there */
   if( localAsyncOpMsg->opRelease.count > 0)
      DEBUG((EFI_D_ERROR, " RemoteObj_invoke  count %d \n", localAsyncOpMsg->opRelease.count ));

   for( int i=0; i< localAsyncOpMsg->opRelease.count; ++i)
   {
      if( RemoteObj_invokeInternal( localAsyncOpMsg->opRelease.obj[i], Object_OP_release, NULL, 0) )
         DEBUG((EFI_D_ERROR, "remote Object_OP_release failed !!  \n" ));
   }
   localAsyncOpMsg->opRelease.count = 0;
/* this is temparaily released for unblocking other team, will remove this after TZ support is there */

Exit:

   gBS->RestoreTPL( PrevTPL );

   return ret;
}


/**
 *  Copy an object sent to QTEE:
 *    1. if the object is remote, pass the remote handle and retain it if this is an 
 *       outbound (i.e. it's an OI).
 *    2. if the object is local,  add it to boject table and pass the resulting handle.
 */
static int32_t CopyObj_toRemote( Object         sourceObj,
                                 SmcInvokeObj  *remoteObj,
                                 bool           outbound )
{
   int32_t  ret = Object_OK;

   if( Object_isNull( sourceObj ) )
      *remoteObj = NullSmcInvokeObj;
   else if( sourceObj.invoke == RemoteObj_invoke )
   {
      RemoteObjCxt *me = (RemoteObjCxt *)sourceObj.context;

      if( outbound )
          RemoteObj_retain(me);

      *remoteObj = me->objHandle;
   }
   else
   {
      size_t index;
      ret = LocalObj_add( sourceObj, &index );
      TEST_RETURN( ret );
      *remoteObj = (SmcInvokeObj)INDEX_TO_HANDLE( index );        
   }

Exit:

   return ret;
}


/**
 *  Copy an object received from QTEE:
 *    1. if the object is local, recover(get) it from the object table and retain it.
 *    2. if the object is remote, create a new object wrapper around it.
 */
static int32_t CopyObj_fromRemote( SmcInvokeObj remoteObj,  Object *destObj )
{
   int32_t  ret = Object_OK;

   if( remoteObj == NullSmcInvokeObj )
      *destObj = Object_NULL;
   else if( SmcInvokeObj_isSecure( remoteObj ) )
   {
      /* Remote object, create a remote object to wrap it */
      ret = RemoteObj_create( remoteObj, destObj );
   }
   else
   {
      /* local object */
      *destObj = LocalObj_retrieve( HANDLE_TO_INDEX(remoteObj) );
      if( Object_isNull( *destObj ) )
      {
         DEBUG((EFI_D_ERROR, " LocalObj_retrieve failed, remoteObj = 0x%x \n", remoteObj ));
         ret = Object_ERROR_BADOBJ;
      }
   }

   return ret;
}


/**
 *  Unmarshal callback message buffer into Object Args
 */
static int32_t CallbackMsg_unmarshal( const void          *cbMsg,
                                            size_t         cbMsgLen,
                                            ObjectCounts   counts,
                                            ObjectArg     *args )
{
   int32_t  ret = Object_OK;
   size_t   i;
   void    *ptr;

   CallBackMessage *pCbMsg = (CallBackMessage *)cbMsg;

   FOR_ARGS(i, counts, Buffers)
   {
      ptr = (void *)( (uintptr_t)pCbMsg + pCbMsg->args[i].b.offset );

      args[i].b = (ObjectBuf){ ptr, pCbMsg->args[i].b.size };
   }

   FOR_ARGS(i, counts, OI)
   {
      if( (ret = CopyObj_fromRemote( pCbMsg->args[i].o, &args[i].o )) )
         break;
   }

   return ret;
}


/**
 *  Marshal Object Args into callBack message buffer.
 */
static int32_t CallbackMsg_marshal( const ObjectArg     *args,
                                          ObjectCounts   counts,
                                          void          *cbMsg,
                                          size_t         cbMsgLen )
{
   int32_t ret = Object_OK;
   size_t  i;

   CallBackMessage *pCbMsg = (CallBackMessage *)cbMsg;

   FOR_ARGS( i, counts, BO )
      pCbMsg->args[i].b.size = (uint32_t)args[i].b.size;

   FOR_ARGS( i, counts, OO )
      if( ( ret = CopyObj_toRemote( args[i].o, &pCbMsg->args[i].o, false ) ) )
         break;

   /** release all OO added so far if error is detected */
   if( ret )
   {
      DEBUG((EFI_D_ERROR, " CallbackMsg_marshal cleanup due to error \n"));

      for( size_t j = ObjectCounts_indexOO(counts); j < i; ++j)
      {
         if( pCbMsg->args[j].o != NullSmcInvokeObj &&  pCbMsg->args[j].o & SmcInvokeObj_NS  )
         {
            LocalObj_release( HANDLE_TO_INDEX( pCbMsg->args[j].o ) );
         }
      }
   }
   return ret;
}


/**
 *  Process asynchronous operations request from QTEE. 
 *  This function releases the local objects added into localObjTable before.
 */
static void RemoteAsyncOpMsg_process( const void    *msg,
                                            size_t   msgLen,
                                            boolean  doRelease )
{
   AsyncOpMessage  *pMsg = (AsyncOpMessage *)msg;

   /* this is QTEE version checking, will allow major version 1 to continue processing */
   TEST_TRUE( ASYNC_MAJOR_VERSION(pMsg->header.version) == ASYNC_MAJOR_VERSION(SMCINVOKE_ASYNC_VERSION_LOCAL) );

   TEST_TRUE( pMsg->header.op == Object_OP_release );

   size_t count = pMsg->opRelease.count;
   if( count == 0 )
      return;

   size_t asyncMsgLen =  sizeof(AsyncOpMessage) + count*sizeof(SmcInvokeObj);
   TEST_TRUE( msgLen >= asyncMsgLen );

   if( doRelease ) 
   {
      for( size_t i = 0; i < count; ++i)
      {
         if( SmcInvokeObj_isNS( pMsg->opRelease.obj[i]) )
            LocalObj_release( HANDLE_TO_INDEX( pMsg->opRelease.obj[i] ) );
         else
            DEBUG((EFI_D_ERROR, " Not NS obj!! objHandle = 0x%x \n", pMsg->opRelease.obj[i] ));
      }
   }
   else
   {  
      if( asyncMsgLen > asyncOpReqLen )
      {
         /* assert here so it can be caught at dev time */ 
         DEBUG((EFI_D_ERROR, "remoteAsyncOpMsg is too small!! Increase MaxAsyncOp in uefiplat.cfg \n"));
         ASSERT(0);
      }

      memscpy( (void *)remoteAsyncOpMsg, asyncOpReqLen, msg, asyncMsgLen );
      pendingRemoteAsyncOp = true;
   }

Exit:

   return;
}


/**
 *  This function checks async ops request piggy-backed in callback request from QTEE. 
 *  If cbMsg is large enough to hold async ops, pass this buffer for further handling. 
 */
static void RemoteAsyncOpMsg_check( const void *cbMsg,  size_t cbMsgLen )
{
   CallBackMessage *pCbMsg       = (CallBackMessage *)cbMsg;
   size_t           cbMsgRealLen = 0;

   CALLBACK_GET_MSG_LENGTH( pCbMsg->counts, pCbMsg->args, cbMsgRealLen);

   TEST_TRUE( cbMsgLen > cbMsgRealLen );

   RemoteAsyncOpMsg_process( cbMsg + cbMsgRealLen, (cbMsgLen - cbMsgRealLen), false );

Exit:

   return;
}


/**
 *  Append local pending async op request. 
 */
static void LocalAsyncOps_append( void *buf, size_t bufLen )
{
   size_t msgBodyLen = localAsyncOpMsg->opRelease.count*sizeof(SmcInvokeObj); 
   size_t msgLen     = sizeof(AsyncOpMessage) + msgBodyLen;

   if( bufLen >= msgLen )
   {
      memscpy( buf, bufLen, (void *)localAsyncOpMsg, msgLen );
      memset( (void *)localAsyncOpMsg + sizeof(AsyncOpMessage), 0, msgBodyLen );
      localAsyncOpMsg->opRelease.count = 0;
   }
   else 
      /** do nothing, next smc invoke will release them all at one shot */

   return;
}


/** 
 *  CallBack object invocation.
 */
static int32_t CallbackObj_invoke( void *cbMsg, size_t cbMsgLen )
{
   int32_t          ret          = Object_OK;
   CallBackMessage *pCbMsg       = (CallBackMessage *)cbMsg;
   ObjectOp         op           = pCbMsg->op;
   ObjectCounts     counts       = pCbMsg->counts;
   SmcInvokeObj     cxt          = pCbMsg->cxt;
   ObjectArg       *args         = NULL;
   Object           cbObj        = Object_NULL;
   size_t           cbMsgRealLen = 0;
   size_t           i            = 0;

   /** check the release op first */ 
   if( op == Object_OP_release )
   {
      LocalObj_release( HANDLE_TO_INDEX(cxt) );
      goto Exit;
   }

   /* Remote domain should maintain its own local reference counting and cross-domain retain
    * requests should not be sent. */
   ret = Object_ERROR_BADOBJ;
   TEST_TRUE( op != Object_OP_retain );

   CALLBACK_GET_MSG_LENGTH( counts, pCbMsg->args, cbMsgRealLen );
   ret = Object_ERROR;
   TEST_TRUE( cbMsgLen >= cbMsgRealLen );

   if( ObjectCounts_total( counts ) )
   {
      args = (ObjectArg *)AllocateZeroPool( sizeof(ObjectArg) * ObjectCounts_total(counts) );
      ret = Object_ERROR_KMEM;
      TEST_TRUE( args != NULL );
   }

   /* retrieve the callback object from the localObjTable */
   cbObj = LocalObj_retrieve( HANDLE_TO_INDEX(cxt) );
   ret = Object_ERROR_BADOBJ;
   TEST_TRUE( ! Object_isNull( cbObj ) );

   if( args )
   {
      ret = CallbackMsg_unmarshal( cbMsg, cbMsgLen, counts, args );
      /* If fail here, args will contain only valid OI from local object table, 
       * valid OI from remote object table or Object_NULL. So it's safe to release them. */
      TEST_RETURN( ret );
   }

   ret = Object_invoke( cbObj, op, args, counts );
   /* If fail here, the content of OO in args is unreliable and must NOT
    * be released. OIs are safe to release. */
   TEST_RETURN( ret );

   if( args )
   {
      /* From this moment on, we can assume the whole content of args is ok
       * so we need to release on exit both OO and OI */
      ret = CallbackMsg_marshal( args, counts, cbMsg, cbMsgLen );

      /* All remote OO have been added to the ObjectTable by CallbackMsg_marshal(),
       * which implies they all get an additional retain as part of the operation.
       * All local OO have been retained. To make things even, we now release them once. */
      FOR_ARGS(i, counts, OO)
         Object_RELEASE_IF(args[i].o);
   }

Exit:

   pCbMsg->result = ret;
   if( ret )
   {
      DEBUG((EFI_D_ERROR,"CallbackObj_invoke ret = 0x%x \n", ret));
   }

   if( args )
   {
      /* Object lifetime should be the duration of a call. */
      FOR_ARGS( i, counts, OI )
         Object_RELEASE_IF( args[i].o );

      FreePool( args );
   }

   Object_RELEASE_IF( cbObj );

   /* piggyback any local pending release ops to callback message buffer */
   if( localAsyncOpMsg->opRelease.count > 0 )
      LocalAsyncOps_append( cbMsg + cbMsgRealLen, ( cbMsgLen - cbMsgRealLen ) );

   return ret;

}


/**
 *  Execute a synchronous invocation. 
 *  Handle any callback request( object callback and listener callback ) that is received.
 * 
 *  ScmDxe in UEFI doesn't support the cached memory Scm call, so Cache Coherance is disabled. 
 *  If the performance is really an issue, we will look into it and may open another FR,
 *  this new FR should also involve TZ side support and will impact many other areas. 
 */
static int32_t ScmCall( void    *siMsg,
                        size_t   siMsgLen,
                        void    *cbMsg,
                        size_t   cbMsgLen )
{
   int32_t      ret = Object_OK;
   EFI_STATUS   Status;

   /* scm register protocol */
   memset((void *)(&scmReq), 0, sizeof(scmReq));

   scmReq.scmId   = TZ_SMC_INVOKE_ID;
   scmReq.paramId = TZ_SMC_INVOKE_ID_PARAM_ID;
   scmReq.arg[0]  = (uintptr_t)siMsg;
   scmReq.arg[1]  = siMsgLen;
   scmReq.arg[2]  = (uintptr_t)cbMsg;
   scmReq.arg[3]  = cbMsgLen;

   do 
   {
      /* clean scmRsp before send it into tz */
      memset((void *)(&scmRsp), 0, sizeof(scmRsp));

      Status = SysCallInternal( scmReq.scmId,
                                scmReq.paramId,
                                scmReq.arg,
                                scmRsp,
                                NULL );
      if( Status )
      {
         DEBUG((EFI_D_ERROR, "SysCallInternal failed! Status = 0x%x\n", Status ));
         ret = Object_ERROR;
         goto Exit;
      }

      if( scmRsp[1] == QSEE_RESULT_INCOMPLETE )
      {
         /* legacy listerner request */ 
         memset( (void *)(&scmReq), 0, sizeof(scmReq) );
         scmReq.scmId   = TZ_OS_LISTENER_RESPONSE_HANDLER_ID;
         scmReq.paramId = TZ_OS_LISTENER_RESPONSE_HANDLER_ID_PARAM_ID;
         scmReq.arg[0]  = scmRsp[3];

         /* call listener */  
         Status = ListenerExec( scmRsp[3] );
         if( Status != EFI_SUCCESS )
         {
            DEBUG((EFI_D_ERROR, "Listener Callback function failed. \r\n"));
            scmReq.arg[1] = QSEE_RESULT_RESERVED;
         }
         else
            scmReq.arg[1] = QSEE_RESULT_SUCCESS;
      }
      else if( scmRsp[1] == QSEE_RESULT_CBACK_REQUEST && scmRsp[2] == 0 )
      {
         /* callback object request */
         memset( (void *)(&scmReq), 0, sizeof(scmReq) );
         scmReq.scmId   = TZ_SMC_INVOKE_CBACK_RSP_ID;
         scmReq.paramId = TZ_SMC_INVOKE_CBACK_RSP_ID_PARAM_ID;
         scmReq.arg[0]  = (uintptr_t)cbMsg;
         scmReq.arg[1]  = cbMsgLen;

         /* copy apended async OP request from QTEE in cbMsg if there is any, to make sure it
            will not be contaminated, in case the resulting invocation overwrites the async op
            request msg or TOCTOU issues */
         RemoteAsyncOpMsg_check( cbMsg, cbMsgLen );

         /* Perform callback invocation. */
         CallbackObj_invoke( cbMsg, cbMsgLen );

         /* process async ops now if there is any */
         if( pendingRemoteAsyncOp )
         {
            RemoteAsyncOpMsg_process( remoteAsyncOpMsg, asyncOpReqLen, true );         
            memset( (void *)remoteAsyncOpMsg, 0, asyncOpReqLen );
            pendingRemoteAsyncOp = false;
         }
      }
      else if( scmRsp[1] == QSEE_RESULT_CBACK_REQUEST && scmRsp[2] != 0 )
      {
         DEBUG((EFI_D_ERROR, "Should never happend !\n"));
         ASSERT(0);
      }
      else
      {
         /* normal smc invoke return bails out here. Could have cbMsg with async op request */
         break;
      }

   }while( true );

Exit:

   return ret;
}


/**
 *  Mashal args into SMC invoke message buffer
 */
static int32_t SmcInvokeMsg_marshal( const ObjectArg    *args,
                                           ObjectCounts  counts,
                                           void         *siMsg,
                                           size_t        siMsgLen)
{
   int32_t  ret = Object_OK;
   size_t   i;

   SmcInvokeMessage *pSiMsg = (SmcInvokeMessage *)siMsg;

   size_t headerLen = sizeof(SmcInvokeMessage) + sizeof(SmcInvokeArg) * ObjectCounts_total(counts);

   /* Start of the buffer portion after all args[] */
   uint32_t offset = ARGS_ALIGN( headerLen ); 

   FOR_ARGS( i, counts, Buffers )
   {
      TEST_TRUE( !( args[i].b.size && !args[i].b.ptr )); 

      /* siMsgLen has been precalculated based on the same args and counts, 
         so no need to check buffer overflow. */
      memscpy( siMsg+offset, args[i].b.size, args[i].b.ptr, args[i].b.size );

      pSiMsg->args[i].b.offset = offset;
      pSiMsg->args[i].b.size   = (uint32_t)args[i].b.size;

      offset += ARGS_ALIGN( args[i].b.size );
   }

   FOR_ARGS( i, counts, OI )
      if( (ret = CopyObj_toRemote(args[i].o, &pSiMsg->args[i].o, true)) )
      {
         DEBUG((EFI_D_ERROR, " CopyObj_toRemote failed \n"));
         pSiMsg->args[i].o = NullSmcInvokeObj;
         break;
      }

   /* cleanup if error is detected */
   if( ret )
   {
      DEBUG((EFI_D_ERROR, " SmcInvokeMsg_marshal cleanup due to error \n"));

      for( size_t j = ObjectCounts_indexOI(counts); j < i; ++j )
      {
         if( RemoteObj_invoke == args[j].o.invoke ) 
            Object_release( args[j].o );
         else if( !Object_isNull( args[j].o ) )
            LocalObj_release( HANDLE_TO_INDEX( pSiMsg->args[j].o ) );
      }
   }

Exit:

   return ret;
}


/**
 *  Unmarshal SMC invoke message buffer into args. 
 */
static int32_t SmcInvokeMsg_unmarshal( const void          *siMsg,
                                             size_t         siMsgLen,
                                             ObjectArg     *args,
                                             ObjectCounts   counts )
{
   int32_t   ret = Object_OK;
   size_t    i;
   void     *ptr;

   SmcInvokeMessage *pSiMsg = (SmcInvokeMessage *)siMsg;

   FOR_ARGS( i, counts, BO )
   {
      ptr = (void *)( (uintptr_t)pSiMsg + pSiMsg->args[i].b.offset );

      args[i].b.size = memscpy( args[i].b.ptr, args[i].b.size, ptr, pSiMsg->args[i].b.size );
   }

   FOR_ARGS( i, counts, OO )
   {
      if( ( ret = CopyObj_fromRemote( pSiMsg->args[i].o, &args[i].o ) ) )
      {
         DEBUG((EFI_D_ERROR, " CopyObj_fromRemote failed \n"));
         break;
      }
   }

   /* Cleanup if error is detected */
   if( ret )
   {
      DEBUG((EFI_D_ERROR, " SmcInvokeMsg_unmarshal cleanup due to error \n"));
      for( size_t j = ObjectCounts_indexOO(counts); j < i; ++j )
         Object_RELEASE_IF( args[j].o );
   }

   return  ret;
}


/**
 *  This function does following things:
 *     1. allocate smc invoke message buffer( siMsg ) and callback message buffer( cbMsg )
 *     2  marshal arg[] into siMsg and if there is any, marshal pending async op requests into cbMsg
 *     3. Send the message to QTEE
 *     4. unmarshal siMsg into arg[]
 *     5. Process any async ops request from QTEE, the request is packed in cbMsg
 *     6. release local objects (OI) retained during this invoke session
 *     7. release the siMsg and cbMsg
 */
static int32_t RemoteObj_invokeInternal( SmcInvokeObj   remoteObj, 
                                         ObjectOp       op,
                                         ObjectArg     *args,
                                         ObjectCounts   counts )
{
   int32_t   ret          = Object_OK;
   void     *msgBuf       = NULL;
   size_t    msgBufLen    = 0;
   void     *siMsg        = NULL;
   size_t    siMsgLen     = 0;
   void     *cbMsg        = NULL;
   size_t    cbMsgLen     = 0;
   size_t    siMsgRealLen = 0;
   size_t    asyncOpLen   = 0;
   size_t    i;

   /* Length is rounded up to 8 when returned */
   INVOKE_GET_MSG_LENGTH(counts, args, siMsgRealLen);             
   siMsgLen   = PAGE_ALIGN( siMsgRealLen );

   /* calculate cbMsg size, always give two more pages to reduce the chance of out of cbMsg memory. 
      Please note smc invoke originator may not know callback object call will be triggered or not,
      the originator should regsiter the expected callback message length. Here claim more memory
      for cbMsg may cover caller's miss */ 
   asyncOpLen = sizeof(AsyncOpMessage) + localAsyncOpMsg->opRelease.count*sizeof(SmcInvokeObj);
   cbMsgLen   = PAGE_ALIGN( asyncOpLen ) + 2*PAGE_SIZE;

   /* registeredCbMsgLen is only buffer size, not include CallBackMessage header */
   size_t registeredCbMsgBufLen = PAGE_ALIGN(SmcInvokeGetCbMsgBufLen());
   if( cbMsgLen < registeredCbMsgBufLen + 2*PAGE_SIZE )
      cbMsgLen = registeredCbMsgBufLen + 2*PAGE_SIZE;

   ret = Object_ERROR_KMEM;
   msgBufLen = siMsgLen + cbMsgLen;
   msgBuf = ShmBridgeProtocol->ShmBridgeAllocate( ShmBridgeProtocol, &msgBufLen, ShmBridgeBootSvcData );
   TEST_TRUE( msgBuf != NULL );
   TEST_TRUE( msgBufLen == (siMsgLen + cbMsgLen) );

   siMsg = msgBuf;
   cbMsg = siMsg + siMsgLen;

   /* starting from now on, no need for siMsg/cbMsg pointer checking, feel free to dereference. */
   ((SmcInvokeMessage *)siMsg)->cxt    = remoteObj;
   ((SmcInvokeMessage *)siMsg)->op     = op;
   ((SmcInvokeMessage *)siMsg)->counts = counts;

   ret = SmcInvokeMsg_marshal( args, counts, siMsg, siMsgLen);
   TEST_RETURN( ret );

   /* Per QTEE Async op release protocol, always add async header in cbMsg even though there is no
      async op pending, to let QTEE knows what type of async op this smc invoke session supports */ 
   LocalAsyncOps_append( cbMsg, cbMsgLen );

   /* send to QTEE */
   ret = ScmCall(siMsg, siMsgLen, cbMsg, cbMsgLen);

   if( !ret )
   {
      /* process async op request from remote */
      RemoteAsyncOpMsg_process( cbMsg, cbMsgLen, true );

      /* take return value from x1 */
      ret = scmRsp[2];
      if( !ret )
      {
         if(( ret = SmcInvokeMsg_unmarshal( siMsg, siMsgLen, args, counts )))
            DEBUG((EFI_D_ERROR, " SmcInvokeMsg_unmarshal failed \n"));
      }
      else
         DEBUG((EFI_D_ERROR, " Smc Invoke call failed ret 0x%x \n", ret));
   }
   else
      DEBUG((EFI_D_ERROR, " ScmCall failed ret 0x%x \n", ret));

   /* Release local OI retained during the invocation. Release remote objects only since local ones 
      are released by the async op request from remote */
   FOR_ARGS( i, counts, OI )
   {
      if( NullSmcInvokeObj != ((SmcInvokeMessage *)siMsg)->args[i].o )
      {
         if( RemoteObj_invoke == args[i].o.invoke )
            Object_release(args[i].o);
      }
   }

Exit:

   if( msgBuf )
      ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, msgBuf );


   /* reset this registered callback message length to 0 to avoid miss use */    
   SmcInvokeSetCbMsgBufLen( 0 );

   return ret;
}


/**
 * Get a client environment object using CBOR encoded credential
 */
static int32_t CreateClientEnvObject( Object rootEnvObj, Object *obj )
{
   /* Hardcode self credential buffer in CBOR encoded format. 
      CBOR encoded credential is created using following paramters, 
       #define ATTR_UID        1
       #define ATTR_PKG_NAME   3
       #define SYSTEM_UID      1000
       static const uint8_t bufString[] = {"UefiSmcInvoke"};
    */
   const uint8_t encodedBuf[] = { 0xA2, 0x01, 0x19, 0x03, 0xE8, 0x03, 0x6E, 0x55,
                                  0x65, 0x66, 0x69, 0x53, 0x6D, 0x63, 0x49, 0x6E,
                                  0x76, 0x6F, 0x6B, 0x65, 0x0 };

   Object credentialObj = Object_NULL;

   int32_t  ret = Credential_create( encodedBuf, sizeof(encodedBuf), &credentialObj);
   TEST_RETURN ( ret );

   ret = IClientEnv_registerAsClient( rootEnvObj, credentialObj, obj );
   if( ret )
      DEBUG((EFI_D_ERROR, "IClientEnv_registerAsClient failed %d \n", ret ));

   Object_release( credentialObj );

Exit:

   return ret;
}


/**
 *  SMC invoke Api called in ScmGetClientEnv()
 */
EFI_STATUS SmcInvokeGetClientEnv( Object *obj )
{
   /* clientEnvObj is created at SmcInvokeInit time, if the creation fails, then ScmDxe will 
    * never be loaded and advertised. So it is safe to assume clientEnvObj is already created
    * successfully if this function is called. 
    *
    * clientEnvObj is shared among all uefi clients, it is used by different clients at
    * different time. In this way only one clientEnvObj is required by uefi and it saves 
    * resources at QTEE side and also achieves better performance and easy management. */
   if( !Object_isNull( clientEnvObj ) )
   {
      Object_retain( clientEnvObj );
     *obj = clientEnvObj;
      return EFI_SUCCESS;
   }
   else
   {
      /* should never be here */
      DEBUG((EFI_D_ERROR, " clientEnvObj is NULL object !!! \n")); 
      return EFI_DEVICE_ERROR;
   }
}


/**
 *  SMC invoke Api called in ScmDxeInit()
 */
EFI_STATUS SmcInvokeInit()
{  
   EFI_STATUS  Status;
   uint32_t    smcInvokeConfig = 0;

   /** the reason to make it customer configurable is that customer may  have their own use
    *  cases which may require bigger size tables, in such case, they can touch the config
    *  file and use the same binary we delivered. */
   if( GetConfigValue("SmcInvokeConfig", &smcInvokeConfig) == EFI_SUCCESS )
   {
      /* bit definition please see uefiplat.cfg, no good macro can be defined */
      maxLocalObj  = ( smcInvokeConfig >>21 ) & 0x000007FF;
      maxRemoteObj = ( smcInvokeConfig >>10 ) & 0x000007FF;
      maxAsyncOp   = ( smcInvokeConfig & 0x000003FF );
   }

   size_t localObjTableLen  = ARGS_ALIGN(( sizeof(LocalObjCxt)  * maxLocalObj ));
   size_t remoteObjTableLen = ARGS_ALIGN(( sizeof(RemoteObjCxt) * maxRemoteObj ));

   asyncOpReqLen  = ARGS_ALIGN(( sizeof(AsyncOpMessage) + maxAsyncOp*sizeof(SmcInvokeObj) ));
    
   /** no need to do integer overflow check */
   commonBufLen = localObjTableLen + remoteObjTableLen + 2*asyncOpReqLen;

   /** one shot allocation, better performance and easy memory management */
   commonBuf = AllocateZeroPool( commonBufLen );
   Status  = EFI_OUT_OF_RESOURCES;
   TEST_TRUE( commonBuf != NULL );

   localObjTable    = (LocalObjCxt    *)commonBuf ;
   remoteObjTable   = (RemoteObjCxt   *)((void *)localObjTable   + localObjTableLen );
   localAsyncOpMsg  = (AsyncOpMessage *)((void *)remoteObjTable  + remoteObjTableLen );
   remoteAsyncOpMsg = (AsyncOpMessage *)((void *)localAsyncOpMsg + asyncOpReqLen );

   /** init local async op message */
   localAsyncOpMsg->header.version = SMCINVOKE_ASYNC_VERSION_LOCAL;
   localAsyncOpMsg->header.op      = Object_OP_release;

   Status = gBS->LocateProtocol(&gEfiShmBridgeProtocolGuid, NULL, (VOID **)&ShmBridgeProtocol);
   TEST_RETURN ( Status );

   Status = EFI_DEVICE_ERROR;

   /* create rootEnvObj */
   int32_t ret = RemoteObj_create(InitialIEnvSmcInvokeObj, &rootEnvObj);
   TEST_RETURN ( ret );

   /* create clientEnvObj */
   ret = CreateClientEnvObject( rootEnvObj, &clientEnvObj );
   TEST_RETURN ( ret );
   /* double check here because this is from QTEE */
   TEST_TRUE( !Object_isNull( clientEnvObj) );

   return EFI_SUCCESS;

Exit:

   SmcInvokeDeinit();
   return Status;
}


/**
 *  SMC invoke core Api called in ScmArmV8ExitBootServicesHandler.
 */
void SmcInvokeDeinit(void)
{
   TEST_TRUE( !Object_isNull( clientEnvObj ) );

   uint32_t refs = ((RemoteObjCxt *)clientEnvObj.context)->refs;
   if( refs > 1 )
      DEBUG((EFI_D_ERROR, " someone did not release clientEnvObj !!!. refs = %d\n", refs ));

/* this is temparaily released for unblocking other team, will remove this after TZ support is there */
   for( int i=0; i< localAsyncOpMsg->opRelease.count; ++i)
   {
      if( RemoteObj_invokeInternal( localAsyncOpMsg->opRelease.obj[i], Object_OP_release, NULL, 0) )
         DEBUG((EFI_D_ERROR, "remote Object_OP_release failed !!  \n" ));
   }
   localAsyncOpMsg->opRelease.count = 0;
/* this is temparaily released for unblocking other team, will remove this after TZ support is there */

   /* release it anyway. */
   int32_t ret = RemoteObj_invokeInternal(((RemoteObjCxt *)clientEnvObj.context)->objHandle, Object_OP_release, NULL, 0);
   TEST_RETURN( ret );

Exit:

   /* release clientEnvObj */
   RemoteObj_delete((RemoteObjCxt *)clientEnvObj.context);

   /* release rootEnvObj */
   RemoteObj_delete((RemoteObjCxt *)rootEnvObj.context);

   /* all callback objects have been released */
   if( numOfRemoteObj != 0 )
      DEBUG((EFI_D_ERROR, "Remote object table is not empty. %d  \n", numOfRemoteObj  ));

   if( numOfLocalObj != 0 )
      DEBUG((EFI_D_ERROR, "Local object table is not empty. %d  \n", numOfLocalObj  ));

   if( localAsyncOpMsg->opRelease.count != 0 )
      DEBUG((EFI_D_ERROR, "Async op array is not empty. %d  \n", localAsyncOpMsg->opRelease.count  ));

   if( commonBuf )
      FreePool( commonBuf );

   return;

}

