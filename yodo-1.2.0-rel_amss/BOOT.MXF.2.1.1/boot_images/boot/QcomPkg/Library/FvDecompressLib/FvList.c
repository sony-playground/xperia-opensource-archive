/** @file FvList.c

  Source for maintaining info of FVs under process

  Copyright (c) 2019, 2021 Qualcomm Technologies, Inc.
  All rights reserved.

**/


/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/16/21   cm      Added GetDecompressedFvFileGuidsInStage
 06/04/19   kpa     Initial revision

=============================================================================*/

#include "com_dtypes.h"

#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

#include <Library/FvParserLib.h>
#include <Library/CoreString.h>
#include <Library/FvDecompressLib.h>
#include "FvDecompressInternalLib.h"

#include <Pi/PiFirmwareFile.h>
#include <Pi/PiBootMode.h>
#include <Pi/PiHob.h>

#include <Guid/ExtractSection.h>

STATIC FVS_DECOMPRESS_INFO *DecompressFvList = NULL;

/*****************************************************************************
 *            Private functions
 *****************************************************************************/

/**
  Api to return pointer to an entry in a list for FV under process
  if present

  @param  FvEntryInfoPtr            Entry pointer if present else NULL.
  @param  FvFileGuid            GUID of the FV to be searched.

  @retval EFI_SUCCESS           Operation was success else error code.
          EFI_NOT_READY         If list of FV's is not maintained. 

**/
STATIC
EFI_STATUS 
SearchDecompressFvEntry (
  IN  EFI_GUID    *FvFileGuid,
  OUT FV_ENTRY_INFO **FvEntryInfoPtr
)
{
  UINT32 Index = 0;
  
  if(DecompressFvList == NULL)
    return  EFI_NOT_READY;
  
  if(FvFileGuid == NULL || FvEntryInfoPtr == NULL )
    return  EFI_INVALID_PARAMETER;

  *FvEntryInfoPtr = NULL;
  for(Index =0; Index < MAX_FV_PROCESS_ENTRIES; Index++)
  {
    if (CompareGuid (FvFileGuid, &(DecompressFvList->FvBuff[Index].ImageGuid)))
    {
      FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "SearchDecompressFvEntry: Found  %g\n", &(DecompressFvList->FvBuff[Index].ImageGuid)));
    
      *FvEntryInfoPtr = &DecompressFvList->FvBuff[Index];
      return EFI_SUCCESS;
    }
  }
  
  return EFI_NOT_FOUND;
}

/*****************************************************************************
 *            Public functions
 *****************************************************************************/

/**
  Api to create and initialize FV list
  

  @param  FvEntryPtr            Entry pointer if present else NULL.
  @param  FvFileGuid            GUID of the FV to be searched.

  @retval EFI_SUCCESS           Operation was success else error code.
          EFI_NOT_READY         If list of FV's is not maintained. 

**/
EFI_STATUS 
DecompressFvListInit (OUT VOID **DataPtr)
{
  UINT32 Index = 0;
  LockHandle *LockPtrInit = NULL;
  CHAR8 LockBuff[8] = {0}; 
  
  if (DataPtr == NULL)
    return EFI_INVALID_PARAMETER;  
  
  DecompressFvList = (FVS_DECOMPRESS_INFO*)AllocateZeroPool (sizeof(FVS_DECOMPRESS_INFO));  
  
  FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "DecompressFvList Addr  : 0x%x\n", DecompressFvList));

  if (DecompressFvList != NULL)
  {
    DecompressFvList->InProcessFvCount = 0;
    while(Index < MAX_FV_PROCESS_ENTRIES)
    {
      core_snprintf(LockBuff, sizeof(LockBuff), "FVLCK%d", Index);
      InitRecursiveLock (LockBuff, &LockPtrInit);
      DecompressFvList->FvBuff[Index].LockPtr = LockPtrInit;
      Index++;
    }
    
    *DataPtr = (VOID *) DecompressFvList;
    return EFI_SUCCESS;
  }
  
  return EFI_OUT_OF_RESOURCES;
}

/**
  Api adds an entry for input FV being processed. The EFI Guid
  is an ID used to create and locate the FV entry.

  @param  EFI_GUID            Guid of FV whos entry is to be created.
  @param  FV_ENTRY_INFO       Pointer to newly allocated FV entry.
  
  @retval EFI_SUCCESS           Operation was success else error code.

**/ 
EFI_STATUS 
AllocateDecompressFvInfo (
  IN  EFI_GUID    *FvFileGuid,
  OUT FV_ENTRY_INFO **FvEntryPtr
)
{
  UINT32 Index = 0;
  EFI_STATUS Status = EFI_SUCCESS;
  
  if (DecompressFvList == NULL)
    return  EFI_NOT_READY;
  
  if (FvFileGuid == NULL)
    return  EFI_INVALID_PARAMETER;
  
  if (DecompressFvList->InProcessFvCount >= MAX_FV_PROCESS_ENTRIES)
    return EFI_BUFFER_TOO_SMALL;
  
  Status = SearchDecompressFvEntry (FvFileGuid, FvEntryPtr);
  if (Status != EFI_NOT_FOUND)
  {
    DEBUG ((EFI_D_ERROR, "Error: [AllocateDecompressFvInfo] Potential Duplicate\
 entry %g Status= 0x%x\r\n", FvFileGuid, Status));
    return Status;    
  }
  
  for (Index =0; Index < MAX_FV_PROCESS_ENTRIES; Index++)  
  {
    if (DecompressFvList->FvListStatus[Index] == 0)
    {
      //Free entry found
      DecompressFvList->FvListStatus[Index] = 1;
      break;
    }
  }
  if (Index == MAX_FV_PROCESS_ENTRIES)  
    return EFI_OUT_OF_RESOURCES;
  
  // Keep track of Fv's in process
  DecompressFvList->InProcessFvCount++;
  
  CopyGuid (&(DecompressFvList->FvBuff[Index].ImageGuid), FvFileGuid);
  *FvEntryPtr = &(DecompressFvList->FvBuff[Index]);
  
  return EFI_SUCCESS;
}

/**
  Api free's entry for input FV. The EFI Guid
  is an ID used to locate the FV entry to be freed.

  @param  EFI_GUID            Guid of FV whos entry is to be created.
  
  @retval EFI_SUCCESS           Operation was success else error code.

**/ 
EFI_STATUS 
FreeDecompressFvInfo (IN  EFI_GUID    *FvFileGuid)
{
  UINT32 Index = 0;
  EFI_STATUS Status = EFI_SUCCESS;
  LockHandle *LockHandlePtr;
 
  if (DecompressFvList == NULL)
    return  EFI_NOT_READY;
  
  if (FvFileGuid == NULL)
    return  EFI_INVALID_PARAMETER;
  
  for (Index =0; Index < MAX_FV_PROCESS_ENTRIES; Index++)  
  {
    if (CompareGuid (FvFileGuid, &(DecompressFvList->FvBuff[Index].ImageGuid)))
    {
      FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "FreeDecompressFvInfo : FV Entry Found -> %g\n", &(DecompressFvList->FvBuff[Index].ImageGuid)));

      // Make sure no one is holding the Lock
      Status = WaitForProcessingComplete (FvFileGuid);
      if (EFI_ERROR (Status))
      {
        DEBUG ((EFI_D_ERROR, "Error: WaitForProcessingComplete Failed - %r\n", Status));
        return Status;    
      } 
      
      //Mark entry free
      DecompressFvList->FvListStatus[Index] = 0;
     
      //Conserve LockHandlePtr. Handle is tied to entry and can be reused.
      LockHandlePtr = DecompressFvList->FvBuff[Index].LockPtr;
      SetMem (&(DecompressFvList->FvBuff[Index]), sizeof (FV_ENTRY_INFO), 0x0);

      DecompressFvList->FvBuff[Index].LockPtr = LockHandlePtr;
      
      // Update count
      DecompressFvList->InProcessFvCount--;
      
      return EFI_SUCCESS;
    }
  }
  
  return EFI_NOT_FOUND;
}
   
/**
  This api waits till FV corresponding to input GUID name is decompressed/processed
  for further use. Is a blocking api.

  @param  FvFileGuid            GUID of the FV whose processing status is being queried

  @retval EFI_SUCCESS           The volume was found else error.

**/
EFI_STATUS
WaitForProcessingComplete (IN  EFI_GUID    *FvFileGuid)
{
  EFI_STATUS Status = EFI_SUCCESS;
  FV_ENTRY_INFO    *FvEntryPtr = NULL;

  if(FvFileGuid == NULL)
    return  EFI_INVALID_PARAMETER;
  
  Status = SearchDecompressFvEntry (FvFileGuid, &FvEntryPtr);
  if (EFI_ERROR (Status))
  {
    DEBUG ((EFI_D_ERROR, "Error: SearchDecompressFvEntry Failed - %r\n", Status));
    return Status;    
  } 
  
  /*Block on Fv entry mutex */
  AcquireLock (FvEntryPtr->LockPtr);
  
  ReleaseLock (FvEntryPtr->LockPtr);  
  return EFI_SUCCESS;  
} 

/**
  This api reinitializes Data struct that keeps track of all FV lists under process.
  To be used post SEC.

  @param  FvListPtr     pointer to original list of FVs under process

  @retval EFI_SUCCESS           The volume was found else error.

**/
EFI_STATUS
FvListInitPostSec (IN VOID  *FvListPtr)
{
  if(FvListPtr == NULL)
    return EFI_INVALID_PARAMETER;
  
  DecompressFvList = (FVS_DECOMPRESS_INFO  *) FvListPtr;
  return EFI_SUCCESS;
}

/**
  This api retrieve's Buffer info for FV corresponding to input  
  GUID name.

  @param  FvFileGuid            GUID of the FV whose Buffer info 
                                is to be updated
  @param  FvBufferAddr          Start Address of Buffer containing FV
  @param  FvBufferSize          Size of Buffer

  @retval EFI_SUCCESS           The volume was found else error.

**/
EFI_STATUS
GetDecompressedFvBufferInfo (
  IN EFI_GUID   *FvFileGuid,
  OUT UINT64     *FvBufferAddr,
  OUT UINT64     *FvBufferSize  
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  FV_ENTRY_INFO    *FvEntryPtr = NULL;

  if (FvFileGuid == NULL || FvBufferAddr == NULL  || FvBufferSize == NULL  )
    return  EFI_INVALID_PARAMETER;
  
  Status = SearchDecompressFvEntry (FvFileGuid, &FvEntryPtr);
  if (EFI_ERROR (Status))
  {
    DEBUG ((EFI_D_ERROR, "Error: SearchDecompressFvEntry Failed - %r\n", Status));
    return Status;    
  } 
  
 *FvBufferAddr = FvEntryPtr->BufferAddr ;
 *FvBufferSize = FvEntryPtr->BufferSize ;  
  
  return EFI_SUCCESS;  
}



/**
  This api retrieve's Fv File Image GUIDS that are expected to be mounted 
  in a certain stage

  @param  Stage                 The stage at which FV is expected to be mounted,
                                this is type MOUNTING_STAGE
  @param  FvGuidList            Pointer to list Fv GUIDS
  @param  FvGuidCountPtr        Pointer that point to number of FV GUIDS

  @retval EFI_SUCCESS           The volume was found else error.

**/
EFI_STATUS
GetDecompressedFvFileGuidsInStage(
  IN MOUNTING_STAGE Stage,
  IN OUT EFI_GUID *FvGuidList,
  IN OUT UINT32 *MaxFvGuidCount,
  IN OUT UINT32 *FvGuidCountPtr
)
{
  UINT32 Index = 0;
  UINT32 Count = 0;
  EFI_STATUS Status = EFI_NOT_FOUND;
  
  if ((Stage > MAX_STAGE) || (FvGuidCountPtr == NULL) || (MaxFvGuidCount == NULL))
    return EFI_INVALID_PARAMETER;
  
  if((*FvGuidCountPtr > 0) && FvGuidList == NULL)
    return EFI_INVALID_PARAMETER;
  
  if(DecompressFvList == NULL)
    return  EFI_NOT_READY;
	
  if(*MaxFvGuidCount > MAX_FV_PROCESS_ENTRIES)
    return EFI_BAD_BUFFER_SIZE;
	
  if(*MaxFvGuidCount < MAX_FV_PROCESS_ENTRIES)
  {
  	*MaxFvGuidCount = MAX_FV_PROCESS_ENTRIES;
	return EFI_BUFFER_TOO_SMALL;
  }

  for(Index = 0; Index < *MaxFvGuidCount; Index++)
  {
    if (DecompressFvList->FvBuff[Index].StageToMount == Stage)
    {
      FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "SearchDecompressFvEntryinStage: Found  %g\n", &(DecompressFvList->FvBuff[Index].ImageGuid)));
      *FvGuidList = DecompressFvList->FvBuff[Index].ImageGuid;
      Status = EFI_SUCCESS;
      FvGuidList++;
      Count++;
    }
  }
  
  *FvGuidCountPtr = Count;
  return Status;

}




