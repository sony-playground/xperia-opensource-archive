/** @file FvDecompressInternalLib.h

  Header file for decompress FV HOB info and other utility Api's

  Copyright (c) 2019 - 2021 Qualcomm Technologies, Inc.
  All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 07/16/21   cm        Added member StageToMount in FV_ENTRY_INFO 
 06/04/19   kpa       Initial revision
 
=============================================================================*/

#ifndef _FVDECOMPRESSINTERNALLIB_H_
#define _FVDECOMPRESSINTERNALLIB_H_

#include <Library/KernelLib.h>
#include <Library/FvDecompressLib.h>


/* LOCAL_DEBUG_LEVEL : 0 => Disable all debug messages
 *                     1 => Critical minimal debug
 */
#define LOCAL_DEBUG_LEVEL  0

/*****************************************************************************
 *   FV_DECOMPRESS_DBG_LOG : Log the message if enabled via LOCAL_DEBUG_LEVEL
 *   Not for use outside the FvDecompressionLib context.
 *****************************************************************************/
#define FV_DECOMPRESS_DBG_LOG(Expression)         \
  if (LOCAL_DEBUG_LEVEL > 0)                      \
    DEBUG (Expression);


#define MAX_FV_PROCESS_ENTRIES   8

typedef struct {
    UINT64         BufferAddr; 
    UINT32         BufferSize;
    LockHandle     *LockPtr;
    EFI_GUID       ImageGuid;
    VOID           *Section;
    VOID           *ScratchBuffer;
    UINT32         ScratchBufferSize;     
    UINT32         AuthenticationStatus;
    MOUNTING_STAGE StageToMount;
} FV_ENTRY_INFO;

typedef struct {
  UINT32         InProcessFvCount;
  FV_ENTRY_INFO  FvBuff[MAX_FV_PROCESS_ENTRIES];
  UINT8          FvListStatus[MAX_FV_PROCESS_ENTRIES];
} FVS_DECOMPRESS_INFO;

/**
  Api to create and initialize FV list
  

  @param  FvEntryPtr            Entry pointer if present else NULL.
  @param  FvFileGuid            GUID of the FV to be searched.

  @retval EFI_SUCCESS           Operation was success else error code.
          EFI_NOT_READY         If list of FV's is not maintained. 

**/
EFI_STATUS 
DecompressFvListInit (OUT VOID **DataPtr);

/**
  Api adds an entry for input FV being processed. The EFI Guid
  is an ID used to create and locate the FV entry.

  @param  EFI_GUID            Guid of FV whos entry is to be created.
  
  @retval EFI_SUCCESS           Operation was success else error code.

**/ 
EFI_STATUS 
AllocateDecompressFvInfo (
  IN  EFI_GUID    *FvFileGuid,
  OUT FV_ENTRY_INFO **FvEntryPtr
);

/**
  Api free's entry for input FV. The EFI Guid
  is an ID used to locate the FV entry to be freed.

  @param  EFI_GUID            Guid of FV whos entry is to be created.
  
  @retval EFI_SUCCESS           Operation was success else error code.

**/ 
EFI_STATUS 
FreeDecompressFvInfo (IN  EFI_GUID *FvFileGuid);

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
);

/**
  This api retrieve's Fv File ImageGUIDS that are expected to be mounted 
  in a certain stage

  @param  Stage                 The stage at which FV is expected to be mounted,
                                this is type MOUNTING_STAGE
  @param  FvGuidList            Pointer to list Fv GUIDS
  @param  MaxFvGuidCount        The value of max number of FV is filled in here
  @param  FvGuidCountPtr        Pointer that point to number of FV GUIDS

  @retval EFI_SUCCESS           The volume was found else error.

**/
EFI_STATUS
GetDecompressedFvFileGuidsInStage(
  IN MOUNTING_STAGE Stage,
  IN OUT EFI_GUID *FvGuidList,
  IN OUT UINT32 *MaxFvGuidCount,
  IN OUT UINT32 *FvGuidCountPtr
);

/**
  Api to save arguments to be passed on to FV decompression module.
  Only NonNull parameters are updated

  @param  *Section              Section address
  @param  *DstBuffer            FV Buffer
  @param  *ScratchBuffer        buffer used by decompression module
  @param  AuthenticationStatus  Saved status of decompression operation
  @param  ScratchBufferSize     Temporary buffer size
  @param  *FvFileGuid           GUID of the FV under process

  @retval EFI_SUCCESS           Operation was success else error.

**/
EFI_STATUS
SetFvDecompressArgs (
  IN EFI_GUID  *FvFileGuid,           
  IN VOID      **DstBuffer             OPTIONAL,
  IN UINT32    *DstBufferSize          OPTIONAL,  
  IN VOID      **Section               OPTIONAL,
  IN VOID      **ScratchBuffer         OPTIONAL,  
  IN UINT32    *ScratchBufferSize      OPTIONAL,
  IN UINT32    *AuthenticationStatus   OPTIONAL    
);

/**
  Api to retrieve arguments to be passed on to FV decompression module.
  Only NonNull parameters are updated

  @param  *Section              Section address
  @param  *DstBuffer            FV Buffer
  @param  *ScratchBuffer        buffer used by decompression module
  @param  AuthenticationStatus  Saved status of decompression operation
  @param  ScratchBufferSize     Temporary buffer size
  @param  *FvFileGuid           GUID of the FV under process

  @retval EFI_SUCCESS           Operation was success else error.

**/
EFI_STATUS
GetFvDecompressArgs (
  IN  EFI_GUID  *FvFileGuid,           
  OUT VOID      **DstBuffer             OPTIONAL,
  OUT UINT32    *DstBufferSize          OPTIONAL,  
  OUT VOID      **Section               OPTIONAL,
  OUT VOID      **ScratchBuffer         OPTIONAL,  
  OUT UINT32    *ScratchBufferSize      OPTIONAL,  
  OUT UINT32    *AuthenticationStatus   OPTIONAL
);


/**
  This api reinitializes Data struct that keeps track of all FV lists under process.
  To be used post SEC.

  @param  FvListPtr     pointer to original list of FVs under process

  @retval EFI_SUCCESS           The volume was found else error.

**/
EFI_STATUS
FvListInitPostSec (IN VOID  *FvListPtr);  

  
#endif
