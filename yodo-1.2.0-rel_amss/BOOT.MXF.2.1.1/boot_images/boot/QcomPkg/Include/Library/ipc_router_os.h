#ifndef IPC_ROUTER_OS_H
#define IPC_ROUTER_OS_H

/*===========================================================================

                    I P C    R O U T E R   O S   R E X

   This file describes the QURT interface to the IPC Router.
   This file must be compatible with all operating systems on which the 
   router will be used.

  ---------------------------------------------------------------------------
  Copyright (c) 2012-2013 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/Library/ipc_router_os.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/04/09   ap      Klockwork fixes
07/01/09   ap      Changed IPC_ROUTER_OS_MESSAGE macro to directly call MSG_* 
05/07/09   sa      Removed flow control ioctl, switched to ping mechanism
02/03/09   sa      Moved in network order macros from DS header
10/16/08   sa      Added ipc_router_get_fc_status function
04/08/08   sa      Switched back to using IPC_ROUTER_OS_MESSAGE macro
03/20/08   sa      Switched to using ipc_router_os_message function
                   and added smem logging 
10/31/07   rr      Fix signals so we only use ONCIPC_REPLY_SIG
08/24/07   bfc     Increased the size of the IPC_ROUTER_CLIENT_QUEUE_SIZE.
04/10/07   rr      Initial Draft
===========================================================================*/


/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "comdef.h"
#include "stdlib.h"
#include "string.h"  
#include "err.h"
#include <Library/KernelLib.h>
#include <Library/UefiBootServicesTableLib.h>

/*===========================================================================
                CONSTANT / MACRO DACLARATIONS
===========================================================================*/

/* msg.h defines MSG_0() as MSG() */
#define MSG_0 

/* Allow var arg style calls to MSG */
#define _MSGPASTE(a,b) 
#define _MSGPASTE_(a,b) 
#define _MSGCNT(...) 
#define _MSGCNT_(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,cnt,...) cnt


#define IPC_ROUTER_MSG_EMERG   
#define IPC_ROUTER_MSG_CRIT    
#define IPC_ROUTER_MSG_ERR     
#define IPC_ROUTER_MSG_ALERT   
#define IPC_ROUTER_MSG_NOTICE  
#define IPC_ROUTER_MSG_WARNING 
#define IPC_ROUTER_MSG_DEBUG   
#define IPC_ROUTER_MSG_INFO    

#define IPC_ROUTER_OS_MESSAGE(level, fmt, ...)  

/*===========================================================================
                      TYPE DECLARATIONS                     
===========================================================================*/
void *ipc_router_os_malloc( size_t size );
void *ipc_router_os_calloc( uint32 num, size_t size );
/*===========================================================================
                         MACRO DACLARATIONS
===========================================================================*/
#define ipc_router_os_sem VOID*

//#define ipc_router_os_malloc(size)  \
//            malloc(size)

#define ipc_router_os_free(ptr)  \
            gBS->FreePool(ptr);

//#define ipc_router_os_calloc(num,size)  \
//            calloc(num,size)

#define ipc_router_os_mem_set(ptr,value,size)\
            memset(ptr,value,size)
/*=============================================================================
  MACRO  ipc_router_os_mem_copy
=============================================================================*/
/*!
@brief
  Copy over from source buffer to destination buffer.

@param[in]  dst     Pointer to the destination buffer
@param[in]  d_len   Size in bytes of the destination buffer
@param[in]  src     Pointer to the source buffer
@param[in]  c_len   Size in bytes to copy from source to destination

@retval   Total number of bytes which were copied from source to destination
*/
/*=========================================================================*/
#define ipc_router_os_mem_copy(d,ds,s,ss) memscpy(d,ds,s,ss)

#define ipc_router_os_sem_init(sem) InitRecursiveLock (0, (LockHandle**)sem);
#define ipc_router_os_sem_lock(sem) AcquireLock (*sem);
#define ipc_router_os_sem_unlock(sem) ReleaseLock (*sem); 
#define ipc_router_os_sem_deinit(sem) DestroyLock(*sem);


#endif /* IPC_ROUTER_OS_H */

