/** @file UfsBlockIO2.h
   
  This file provides UFS Block IO 2 feature internal definitions. 

  Copyright (c) 2014 - 2016, 2021-2022 Qualcomm Technologies, Inc. 
  All Rights Reserved. 
  Qualcomm Technologies Proprietary and Confidential

**/

/*=============================================================================
                              EDIT HISTORY

when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
2022-04-14   sa      Added support for BlockIo2 with multiple doorbells.
2021-04-28   jt      Add ICE support 
2015-11-16   rh      Adapt the BlockIO2 file from SDCC driver
2015-01-09   rm      Add fix for Blockio2 random crash
2014-05-09   rm      Initial version

=============================================================================*/

#ifndef _UFS_BLOCK_IO2_H_
#define _UFS_BLOCK_IO2_H_

#include <Library/UefiLib.h>

/* Block IO 2 polling period, 100000 is 10ms */
#define BLKIO2_POLL_PERIOD   100000    

/* Length of the request list(Set to maximum number of transfer slots)
   Doorbell 0 is reserved for Synchronous call, so 31 slots left for Async */
#define  REQ_LIST_SIZE  31

/* Define for TransferType */
#define   BLOCKIO_READ          (1 << 0)
#define   BLOCKIO_WRITE         (1 << 1)
#define   BLOCKIO2_READ         (1 << 2)
#define   BLOCKIO2_WRITE        (1 << 3)
#define   BLOCKERASE_PURGE      (1 << 4) 

#define   IS_CRYPTO_TYPE(type)  (type == BLOCKIO_CRYPTO_READ) || (type == BLOCKIO_CRYPTO_WRITE) || \
                                (type == BLOCKIO2_CRYPTO_READ) || (type == BLOCKIO2_CRYPTO_WRITE)
typedef struct{
  BOOLEAN                    BlkIO2Initialized;   
  BOOLEAN                    PurgeEventInitialized;   
  BOOLEAN                    TimerSet;          
  EFI_ERASE_BLOCK_TOKEN     *EraseToken;
} DRIVER_INFO;

typedef struct {
  VOID                      *This;
  EFI_LBA                    Lba;
  VOID                      *Token;
  UINT64                     BufferSize;
  VOID                      *Buffer;
  UINT64                    *Index;
  VOID                      *CryptoIvInput;
  INT32                      Type;
  BOOLEAN                    IsStart;
  BOOLEAN                    EventPending; 
  UINT32                     DbBit; 
  UINT64                     CmdDesc; 
  UINT32                     RespOffset; 
  UINT32                     PrdtOffset;   
  UINTN                      XferSizeInBytes;  
} REQ_ENTRY;

typedef struct {
  EFI_LOCK                   ReqListLock;
  REQ_ENTRY                  *Entries;      // Array of request entries
  UINT32                     FilledEntries; // Number of entries filled in the list
} BLKIO2_REQ_LIST;

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
*    CryptoIndex        [IN] : A pointer to the configuration table index. 
*    CryptoIvInput      [IN] : A pointer to a buffer that contains additional 
*                              cryptographic parameters.
*
*
* Returns:
*    EFI_SUCCESS or error status
******************************************************************************/
EFI_STATUS 
BlkIoSlotFullHandler (
  IN EFI_BLOCK_IO_PROTOCOL   *This,
  IN UINT32                  TransferType,
  IN EFI_LBA                 Lba,
  IN UINT64                  BufferSize,
  OUT VOID                   *Buffer, 
  IN UINT64                  *CryptoIndex, 
  IN VOID                    *CryptoIvInput
);
   
/******************************************************************************
* Name: BlkIo2TimerEventNotify
*
* Description:
*    Handle requests in request queue depending on device status
*
* Arguments:
*    Event              [IN] : UEFI event method, not used
*    Context            [IN] : Can be any forms of input parameter, not used
*
* Returns:
*    Returns true or false
*
******************************************************************************/     
VOID
BlkIo2TimerEventNotify(
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
);                   
  
/******************************************************************************
*  Handle one request in Block IO 2 way. That is, start the transfer, set timer 
*  and signal the pending event. Error will be handled inside the function.
*
* Arguments:
*    pReq           [IN] : pointer to the request entry in the request list
******************************************************************************/
VOID BlkIo2HandleRequest (REQ_ENTRY *pReq);                
  
/******************************************************************************
* Name: BlkIo2ReqListInit
*
* Description:
*    This function is to move the pointer to next request in the queue
*    This function has to be called after dealing with current request
*
* Arguments:
*    pReqList           [IN] : pointer to Block Io 2 structure
*    ListSize           [IN] : The size of request queue
*
* Returns:
*    return EFI_SUCCESS or EFI_OUT_OF_RESOURCES
*
******************************************************************************/
EFI_STATUS BlkIo2ReqListInit(BLKIO2_REQ_LIST *pReqList, UINTN ListSize);  

#endif /* ifdef UFS_BLOCK_IO2_H_ */
