/** @file UfsBlockIO2.c
   
   This file implements the utility function for Block IO 2 in UFS driver
  
   Copyright (c) 2014-2017, 2020-2022 Qualcomm Technologies, Inc. 
   All Rights Reserved. 
   Qualcomm Technologies Proprietary and Confidential  
   
**/

/*=============================================================================
                              EDIT HISTORY

when         who     what, where, why
----------   ----    ---------------------------------------------------------- 
2022-07-06   jt      Start request in timer callback if not done yet 
2022-04-14   sa      Added support for BlkIo2 with multiple doorbells.
2021-04-28   jt      Add ICE support 
2017-02-01   jt      Don't continue to poll if return status is success
2016-09-23   jt      Add storage write protect  
2015-11-16   rh      Adapt the BlockIO2 file from SDCC driver
2015-04-17   rm      Only check transfer complete in BlkIoTakeOverTransfer 
2015-03-10   rm      Use same TPL for BLOCKIO and BLOCKIO2
2015-03-06   rm      Add fix for Blockio2 concurrent issue 
2015-01-09   rm      Add fix for Blockio2 random crash 
2014-05-09   rm      Initial version.

=============================================================================*/

#include <Uefi.h>

#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/ArmLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/UncachedMemoryAllocationLib.h>

#include <Protocol/BlockIo.h>
#include <Protocol/BlockIoCrypto.h>
#include <Protocol/BlockIo2.h>
#include <Protocol/EFIRpmb.h>
#include <Protocol/EFICardInfo.h>
#include <Protocol/EFIEraseBlock.h>
#include <Protocol/EFIStorageWriteProtect.h>
#include <Protocol/EFIStorageDeviceMgmt.h>

#include "UFS.h"
#include "UfsBlockIO2.h"
#include <api/storage/ufs_api.h>

#define UFS_TPL TPL_CALLBACK

static EFI_LOCK          BlkIo2Lock = EFI_INITIALIZE_LOCK_VARIABLE (UFS_TPL);
extern BLKIO2_REQ_LIST   gUfsReqList;

extern EFI_EVENT         gUfsBlkIo2TimerEvent;
extern DRIVER_INFO       gUfsTransferInfo;

/* used to initialize other lock */
static EFI_LOCK BlkIo2InitLock = EFI_INITIALIZE_LOCK_VARIABLE (UFS_TPL); 

VOID BlkIo2CompleteTransfer (
   IN REQ_ENTRY *pReq)
{
   BLKIO2_REQ_LIST *pReqList = &gUfsReqList;

   EfiAcquireLock (&pReqList->ReqListLock);
   pReqList->FilledEntries--; 
   EfiReleaseLock (&pReqList->ReqListLock);
   
   pReq->This = NULL; 

   ASSERT(pReq->Token); 

   /* Signal the event completion to clients */
   if((pReq->Index != NULL) && (pReq->CryptoIvInput != NULL)){
   	  gBS->SignalEvent(((EFI_BLOCK_IO_CRYPTO_TOKEN *)pReq->Token)->Event); 
   }
   else{
   	  gBS->SignalEvent(((EFI_BLOCK_IO2_TOKEN *)pReq->Token)->Event); 
   }
}  
VOID BlkIo2RestoreContext (
   IN REQ_ENTRY *pReq, 
   IN struct ufs_xfr_context *xfr_context)   
   {
   if ((xfr_context == NULL) || (pReq == NULL)) {
      return; 
   }

   xfr_context->utp_doorbell_bit = pReq->DbBit;
   xfr_context->resp_upiu_offset = pReq->RespOffset;    
   xfr_context->prdt_offset = pReq->PrdtOffset;   
   xfr_context->xfer_len = pReq->XferSizeInBytes; 
   xfr_context->utp_cmd_desc_phy = pReq->CmdDesc; 
   xfr_context->data_buf_phy = (UINT64)((UINT8 *)pReq->Buffer - pReq->XferSizeInBytes); 
} 

/******************************************************************************
*   Handle error in Block IO 2
*
* Arguments:
*    pReq               [IN] : pointer to request entry in request list
*    rc                 [IN] : status
******************************************************************************/
VOID BlkIo2ErrorHandler(
   IN REQ_ENTRY                *pReq,
   IN INT32                     rc
   )
{
   EFI_STATUS status = EFI_SUCCESS;
   
   if (rc != UFS_EOK)
   {
      if (rc == -UFS_EINVAL) {
         status = EFI_INVALID_PARAMETER;
      } 
      else {
         status = EFI_DEVICE_ERROR;
      }
   } 
   else {
      status = EFI_SUCCESS;
   }
   
   if((pReq->Index != NULL) && (pReq->CryptoIvInput != NULL)){
     ((EFI_BLOCK_IO_CRYPTO_TOKEN *)pReq->Token)->TransactionStatus = status;
   }
   else {
     ((EFI_BLOCK_IO2_TOKEN *)pReq->Token)->TransactionStatus = status;
   }

   BlkIo2CompleteTransfer(pReq);
} 

/******************************************************************************
* Block IO 2 start to make transfer
*
* Arguments:
*    pReq           [IN] : pointer to the request entry in the request list
*
* Returns:
*    error code
******************************************************************************/
INT32 BlkIo2StartTransfer (
   IN REQ_ENTRY *pReq)
{ 
   INT32         rc = UFS_EOK;
   UFS_DEV      *UfsDevice;
   UINT32        transfer_size = 0, block_count = 0, block_size = 0;
   EFI_LBA       Lba;
   UINTN         BufferSize;
   UINT8        *temp_buffer;
   struct ufs_handle *hUFS;
   struct ufs_crypto_context *crypto_ctxt = NULL; 
   struct ufs_xfr_context xfr_context = {0}; 
   struct ufs_crypto_context crypto; 
   UINT64       *Index = NULL; 
   VOID         *CryptoIvInput = NULL; 
   
   /* Grab from request list */        
   BufferSize = pReq->BufferSize; 
   if (BufferSize == 0) {
     return -UFS_EINVAL;
   }

   Lba = pReq->Lba; 
   temp_buffer = (UINT8*)pReq->Buffer;
   Index = pReq->Index;
   CryptoIvInput = pReq->CryptoIvInput;

   if ((Index != NULL) && (CryptoIvInput != NULL)) {
      UfsDevice = UFS_DEV_FROM_BLOCKIO_CRYPTO (pReq->This); 
      crypto.cfg_index = *(Index) & 0xff;
      crypto.dun = *((UINT64 *)CryptoIvInput); 
      crypto_ctxt = &crypto; 
   }
   else {
      UfsDevice = UFS_DEV_FROM_BLOCKIO2 (pReq->This);
   }
         
   hUFS = UfsDevice->DeviceHandle;

   block_size = UfsDevice->BlkIo.Media->BlockSize;
   block_count = (BufferSize/block_size);
   transfer_size = (block_count > UFS_MAX_BLOCK_TRANSFERS) ? 
                     UFS_MAX_BLOCK_TRANSFERS : block_count;
         
   if (pReq->Type == BLOCKIO2_READ) {
      rc = ufs_read_ex (hUFS, temp_buffer, Lba, transfer_size, &xfr_context, crypto_ctxt);
   }
   else if (pReq->Type == BLOCKIO2_WRITE) {
      rc = ufs_write_ex (hUFS, temp_buffer, Lba, transfer_size, &xfr_context, crypto_ctxt);
   }
   else {
      DEBUG ((EFI_D_ERROR, "Blkio2: Bad transfer type value!\n"));
      ASSERT(FALSE);
   }
                             
   Lba = Lba + transfer_size;
   block_count = block_count - transfer_size;
   BufferSize = block_count * block_size;
   temp_buffer = temp_buffer + (transfer_size * block_size);
   
   // Restore to request entry 
   pReq->BufferSize = BufferSize;
   pReq->Lba = Lba;
   pReq->Buffer = (VOID*)temp_buffer; 
   pReq->IsStart = TRUE;
   pReq->DbBit = xfr_context.utp_doorbell_bit; 
   pReq->CmdDesc = xfr_context.utp_cmd_desc_phy; 
   pReq->RespOffset = xfr_context.resp_upiu_offset; 
   pReq->PrdtOffset = xfr_context.prdt_offset; 
   pReq->XferSizeInBytes = transfer_size * block_size; 
  
   return rc;
} 

/******************************************************************************
*  Handle one request in Block IO 2 way. That is, start the transfer and
*  set the timer. Error will be handled inside the function.
*
* Arguments:
*    pReq           [IN] : pointer to the request entry in the request list
******************************************************************************/
VOID BlkIo2HandleRequest (
   IN REQ_ENTRY *pReq)
{
   INT32 rc = UFS_EOK;
   
   rc = BlkIo2StartTransfer(pReq);
   if (rc == -UFS_EBUSY) {
      // Pending transfer, continue
      ;
   }
   else if (rc != UFS_EOK)
   {
      BlkIo2ErrorHandler(pReq, rc);
      return;
   }

   // Set timer if not set
   if (gUfsTransferInfo.TimerSet == FALSE)
   {
      gUfsTransferInfo.TimerSet = TRUE;
      gBS->SetTimer (gUfsBlkIo2TimerEvent, TimerPeriodic, BLKIO2_POLL_PERIOD);
   }
} 

/******************************************************************************
* Name: BlkIoSlotFullHandler
*
* Description:
*    If request entries are available, a Block IO request will be
*    handled immediately in UFS.c. This function is called when there are
*    no request entries available. Each request entry is checked to see if an
*    existing BlockIo2 transfer has been started. If not, start the transfer.
*    Otherwise, poll to see if the transfer completed. When we find a completed
*    transfer at some particular request entry, we start the Block IO request.
*    The status related to BlockIO 2 will be saved and signaled to the
*    caller in the future.
*
* Arguments:
*    This               [IN] : Indicates a pointer to the calling context.
*    TransferType       [IN] : Type of data transfer
*    Lba                [IN] : The starting Logical Block Address to read/write from
*    BufferSize         [IN] : Size of Buffer, must be a multiple of device block size.
*    Buffer             [IN] : A pointer to the destination buffer for the data.
*
* Returns:
*    EFI_SUCCESS or error status
*
******************************************************************************/
EFI_STATUS BlkIoSlotFullHandler (
   IN EFI_BLOCK_IO_PROTOCOL   *This,
   IN UINT32                   TransferType,
   IN EFI_LBA                  Lba,
   IN UINTN                    BufferSize,
   OUT VOID                   *Buffer,
   IN UINT64                  *CryptoIndex, 
   IN VOID                    *CryptoIvInput) 
{
   EFI_STATUS Status = EFI_SUCCESS; 
   INT32 rc = -UFS_ENOENT;  
   UINT32 i = 0; 
   BLKIO2_REQ_LIST *pReqList = &gUfsReqList;
   REQ_ENTRY  *pReq; 
   UFS_DEV *UfsDevice = NULL;
   struct ufs_xfr_context xfr_context; 

   // Find a completed entry. For the entries not started, go ahead and start them. 
   while (1) {
      pReq = pReqList->Entries + (i % REQ_LIST_SIZE); 
      if (pReq->IsStart) {
         // For entries already started and only pending the signaling of the event, 
         // the request is complete and the slot is available
         if (pReq->EventPending == TRUE) {
            rc = UFS_EOK; 
         } 
         else {
            if ((NULL != CryptoIndex) && (NULL != CryptoIvInput)) {
               UfsDevice = UFS_DEV_FROM_BLOCKIO_CRYPTO (pReq->This);
            }
            else {
               UfsDevice = UFS_DEV_FROM_BLOCKIO (pReq->This);}
               BlkIo2RestoreContext(pReq, &xfr_context); 
               rc = ufs_poll_xfer (UfsDevice->DeviceHandle, &xfr_context); 
            }

          if (rc == UFS_EOK) {
            // If current BlkIo2 transfer at a request entry is finished, start the
            // BlkIO request. After that is done, check to see if there is more data
            // for the previous BlkIo2 request. If there is, transfer the next chunk. 
            // Otherwise, set event pending and return.  
            if (TransferType == BLOCKIO_READ) {
               Status = UFSReadBlocks(This, This->Media->MediaId, Lba, BufferSize, Buffer, CryptoIndex, CryptoIvInput);
            } 
            else if (TransferType == BLOCKIO_WRITE) {
               Status = UFSWriteBlocks(This, This->Media->MediaId, Lba, BufferSize, Buffer, CryptoIndex, CryptoIvInput);
            } 
            else {
               return EFI_INVALID_PARAMETER; 
            }

            if (pReq->BufferSize == 0) {
               ASSERT(pReq->Token); 
                
               if ((pReq->Index != NULL) && (pReq->CryptoIvInput != NULL)) 
               {
                 ((EFI_BLOCK_IO_CRYPTO_TOKEN *)pReq->Token)->TransactionStatus = EFI_SUCCESS;
               }
               else 
               {
                 ((EFI_BLOCK_IO2_TOKEN *)pReq->Token)->TransactionStatus = EFI_SUCCESS;
               } 

               pReq->EventPending = TRUE; 
            } 
            else {
               BlkIo2HandleRequest(pReq);
            }
            break;
         }
      }
      else {
        BlkIo2HandleRequest (pReq);
      }
      i++; 
   }

   return Status; 
} 

/******************************************************************************
*  Handle requests in request queue depending on device status
*
* Arguments:
*    Event              [IN] : UEFI event method, not used
*    Context            [IN] : Can be any forms of input parameter, not used
******************************************************************************/
VOID BlkIo2TimerEventNotify (
                     IN  EFI_EVENT  Event,
                     IN  VOID      *Context)
{  
   INT32 rc = -UFS_ENOENT;  
   BLKIO2_REQ_LIST        *pReqList = &gUfsReqList;
   struct ufs_xfr_context xfr_context; 
   UINT32 i = 0; 
   REQ_ENTRY *pInitReq = pReqList->Entries; 
   REQ_ENTRY *pReq; 
  
   // Cancel timer to do the processing
   if (gUfsTransferInfo.TimerSet == TRUE) {
      gBS->SetTimer (gUfsBlkIo2TimerEvent, TimerCancel, 0);
   }

   EfiAcquireLock (&BlkIo2Lock);

   // Go through all the entries and see what the state of each entry is
   if (pReqList->FilledEntries > 0) 
   { 
     for (i = 0; i < REQ_LIST_SIZE; i++) 
     {
        pReq = pInitReq + i; 
        if (pReq->This != NULL) 
        {
          // If there is an event pending, we just need to cleanup the entry
          // and signal the event 
          if (pReq->EventPending) 
          {
            pReq->EventPending = FALSE; 
            BlkIo2CompleteTransfer(pReq); 
          }
          // If the entry is already started, check to see whether the transfer completed or not
          else if (pReq->IsStart) 
          {  
             UFS_DEV *UfsDevice = NULL; 
             if ((pReq->Index != NULL) && (pReq->CryptoIvInput != NULL)) 
             {
               UfsDevice = UFS_DEV_FROM_BLOCKIO_CRYPTO(pReq->This);
             }
             else 
             {
               UfsDevice = UFS_DEV_FROM_BLOCKIO2(pReq->This);
             } 
             BlkIo2RestoreContext(pReq, &xfr_context);         
             rc = ufs_poll_xfer (UfsDevice->DeviceHandle, &xfr_context);
             if (rc == UFS_EOK) 
             {
               // If request at an entry is finished, see if there is more data
               // to be transferred. If not, clear the entry and signal the event */
               if(pReq->BufferSize > 0) 
               {  
                 BlkIo2HandleRequest(pReq);
               }        
               else
               {
                 if ((pReq->Index != NULL) && (pReq->CryptoIvInput != NULL)) 
                 {
                   ((EFI_BLOCK_IO_CRYPTO_TOKEN *)pReq->Token)->TransactionStatus = EFI_SUCCESS;
                 }
                 else 
                 {
                   ((EFI_BLOCK_IO2_TOKEN *)pReq->Token)->TransactionStatus = EFI_SUCCESS;
                 } 
			     BlkIo2CompleteTransfer(pReq);
               }
             }  
             else if (rc == -UFS_EBUSY) 
             {
               // Transfer not completed, move to the next entry
                 ;
             }
             else 
             {
                BlkIo2ErrorHandler(pReq, rc);
             }
          }
          else if (pReq->IsStart == FALSE) 
          {
             BlkIo2HandleRequest (pReq);
          }
       }
    }
   
    // Set timer again
    gUfsTransferInfo.TimerSet = TRUE;
    gBS->SetTimer (gUfsBlkIo2TimerEvent, TimerPeriodic, BLKIO2_POLL_PERIOD);
 }
 else
 {
    // Timer is cancelled at the beginning, so we are done. 
    gUfsTransferInfo.TimerSet = FALSE;
 }
    
 EfiReleaseLock (&BlkIo2Lock);
 return;
}

/******************************************************************************
*  This function is to move the pointer to next request in the queue;
*  to be called after dealing with current request
*
* Arguments:
*    pReqList           [IN] : pointer to Block Io 2 structure
*    ListSize           [IN] : The size of request queue
*
* Returns:
*    return EFI_SUCCESS or EFI_OUT_OF_RESOURCES
******************************************************************************/
EFI_STATUS BlkIo2ReqListInit (BLKIO2_REQ_LIST *pReqList, UINTN ListSize)
{
   EFI_STATUS Status = EFI_SUCCESS;
   pReqList->ReqListLock = BlkIo2InitLock;
   /* Allocate buffer for requests list.*/
   pReqList->Entries = (REQ_ENTRY *)AllocateZeroPool(ListSize * sizeof(REQ_ENTRY));
   if (pReqList->Entries == NULL)
   {
      Status = EFI_OUT_OF_RESOURCES;
      DEBUG ((EFI_D_WARN, "Command Queue initialization failed\n"));
   }
   else
   {
      pReqList->FilledEntries = 0; 
   }    
   
   return Status;
}
