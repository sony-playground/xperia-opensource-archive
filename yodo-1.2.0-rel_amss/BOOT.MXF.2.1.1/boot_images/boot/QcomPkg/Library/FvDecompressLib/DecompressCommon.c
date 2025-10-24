/** @file DecompressCommon.c

  Source for decompressing FV

  Copyright (c) 2019, 2021 Qualcomm Technologies, Inc.
  All rights reserved.

**/


/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/16/21   cm      Added Stage Parameter
 06/04/19   kpa     Initial revision

=============================================================================*/

#include "com_dtypes.h"

#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

#include <Library/FvParserLib.h>
#include <Library/FvDecompressLib.h>
#include "FvDecompressInternalLib.h"

#include <Pi/PiFirmwareFile.h>
#include <Pi/PiBootMode.h>
#include <Pi/PiHob.h>
#include <Library/HobLib.h>

#include <Guid/ExtractSection.h>

/*GUID for Decompression Data HOB {12DBD93D-402A-416E-EC20-5F80CF5F7FE7}*/
extern EFI_GUID gFvDecompressHobGuid;

/*Note:
  The list of FVs (DecompressFvList) is intended to be initialized once only
  in SEC and the pointer queried in later phases (DXE onwards) to get the
  status of FV processing started in SEC. Since this lib would get compiled
  in many drivers, initializing a new instance later is not preferred.
  DecompressFvHobInit should only be called in SEC. 
*/

/*****************************************************************************
 *            Private functions
 *****************************************************************************/
 
static int DecompressThreadEntry (VOID* ARG)
{
  EFI_COMMON_SECTION_HEADER  *Section;
  VOID                       *DstBuffer;
  VOID                       *ScratchBuffer;
  UINT32                      AuthenticationStatus;  
  UINT32                      ScratchBufferSize;
  EFI_STATUS                  Status;  

  FV_ENTRY_INFO              *FvEntryPtr   = NULL;

  FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "DecompressThreadEntry: Start \n"));  

  if (ARG == NULL)
    return (int) EFI_INVALID_PARAMETER;
  
  FvEntryPtr = (FV_ENTRY_INFO *) ARG;

  DstBuffer         = (VOID *)FvEntryPtr->BufferAddr;
  Section           = FvEntryPtr->Section;
  ScratchBuffer     = FvEntryPtr->ScratchBuffer;
  ScratchBufferSize = FvEntryPtr->ScratchBufferSize;
    
  AcquireLock (FvEntryPtr->LockPtr);   
  
  //
  // Call decompress function
  //
  Status = ExtractGuidedSectionDecode (Section, &DstBuffer,
                                       ScratchBuffer, &AuthenticationStatus);
          
  FreePages (ScratchBuffer, EFI_SIZE_TO_PAGES (ScratchBufferSize));

  /* Update Destination buffer start to skip 8 bytes. ExtractGuidedSectionDecode  
    returns meta info in first eight bytes and actual decompressed data starts after */
  DstBuffer = DstBuffer + 8;
  FvEntryPtr->BufferAddr  = (UINT64) DstBuffer;

  ReleaseLock (FvEntryPtr->LockPtr);
  
  if (EFI_ERROR (Status))
  {
    //
    // Decompress failed
    //
    DEBUG ((EFI_D_ERROR, "Decompress Failed - %r\n", Status));
    return (int)EFI_NOT_FOUND;
  }
  
  FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "DecompressThreadEntry: Done \n"));  
  return 0;
}

/*API For Thread setup, creation */
STATIC
EFI_STATUS
LaunchFvDecompressThread (VOID* ARG)
{
  Thread  *FvThread;
  FvThread = NULL;

  FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "Start FvLaunch Thread \n"));

  FvThread = ThreadCreate ("FvLaunch", &DecompressThreadEntry, ARG, DEFAULT_PRIORITY + 5, DEFAULT_STACK_SIZE);
  ThreadResume (FvThread);

  return EFI_SUCCESS;
}

/*****************************************************************************
 *            Public functions
 *****************************************************************************/

/**
  Api to start decompression of firmware volume.
  FV decompression carried out in either blocking or non-blocking mode

  @param  FfsFileInfoSectionPtr File info section pointer
  @param  OutputBuffer          Pointer to the decompressed firmware volume. 
  @param  OutSizePtr            Size of buffer for decompressed FV.
  @param  FvFileGuid            GUID of the FV to be decompressed
  @param  LaunchMode            Flag to enable nonBlocking/background operation (multithreaded)
  @param  Stage                 The stage at which FV is expected to be mounted,
                                this is type MOUNTING_STAGE
  
  @retval EFI_SUCCESS           Operation was success else error.

**/ 
EFI_STATUS 
PerformGuidedSectionDecode (
    IN  EFI_COMMON_SECTION_HEADER  *FfsFileInfoSectionPtr,
    OUT VOID                       **OutputBuffer,
    OUT UINTN                      *OutSizePtr,
    IN  EFI_GUID                   *FvFileGuid,
    IN  DECOMPRESSION_MODE         LaunchMode,
    IN  MOUNTING_STAGE             Stage
  )
{
  EFI_STATUS                 Status;
  UINT32                     DstBufferSize = 0;
  VOID                       *ScratchBuffer;
  UINT32                     ScratchBufferSize;
  VOID                       *DstBuffer = NULL;
  UINT16                     SectionAttribute;
  EFI_COMMON_SECTION_HEADER  *Section;
  FV_ENTRY_INFO              *FvEntryPtr = NULL;  

  if ((OutputBuffer == NULL) || (OutSizePtr == NULL) || (FfsFileInfoSectionPtr == NULL))
    return EFI_INVALID_PARAMETER;

  Section = (EFI_COMMON_SECTION_HEADER*)FfsFileInfoSectionPtr;

  *OutputBuffer = NULL;
  Status = EFI_NOT_FOUND;

  if (Section->Type != EFI_SECTION_GUID_DEFINED)
    return EFI_INVALID_PARAMETER;
  
  Status = ExtractGuidedSectionGetInfo (Section, &DstBufferSize,
                                        &ScratchBufferSize, &SectionAttribute);
  if (EFI_ERROR (Status))
  {
    //
    // GetInfo failed
    //
    DEBUG ((EFI_D_ERROR, "Decompress GetInfo Failed - %r\n", Status));
    return EFI_NOT_FOUND;
  }
  //
  // Allocate destination buffer, extra one page for adjustment
  //
  DstBuffer = (VOID *)(UINTN)AllocatePages (EFI_SIZE_TO_PAGES (DstBufferSize)+1);
  if (DstBuffer == NULL)
    return EFI_OUT_OF_RESOURCES;
  
  //
  // DstBuffer still is one section. Adjust DstBuffer offset, skip EFI section header
  // to make section data at page alignment.
  // For compressed sections there is a Raw section header as well alongwith FV type section
  // so account for that too
  DstBuffer = (UINT8 *)DstBuffer + EFI_PAGE_SIZE - (sizeof (EFI_COMMON_SECTION_HEADER) * 2);
      
  //
  // Allocate scratch buffer
  //
  ScratchBuffer = (VOID *)(UINTN)AllocatePages (EFI_SIZE_TO_PAGES (ScratchBufferSize));
  if (ScratchBuffer == NULL)
    return EFI_OUT_OF_RESOURCES;

  FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "PerformGuidedSectionDecode: Processing FV %g\n", FvFileGuid));       
   
   /*Hob Creation has to happen before thread launch in SEC, if multithreaded*/ 
   Status = AllocateDecompressFvInfo (FvFileGuid, &FvEntryPtr);
   if(Status != EFI_SUCCESS)
   {
      DEBUG ((EFI_D_ERROR, "ERROR: Unable to add to FV info HOB %g\n", FvFileGuid));
      return Status;         
   }

  /*Initialize Thread Args */
  FvEntryPtr->BufferAddr            = (UINT64) DstBuffer;
  FvEntryPtr->BufferSize            = DstBufferSize;
  FvEntryPtr->Section               = Section;
  FvEntryPtr->ScratchBuffer         = ScratchBuffer;
  FvEntryPtr->ScratchBufferSize     = ScratchBufferSize;
  FvEntryPtr->StageToMount          = Stage;

  if (LaunchMode == BACKGROUND)
  {
    LaunchFvDecompressThread ((void*)FvEntryPtr);
  }
  else
  {
    Status = (EFI_STATUS) DecompressThreadEntry ((void*)FvEntryPtr);
    if(Status != EFI_SUCCESS)
    {
      DEBUG ((EFI_D_ERROR, "ERROR: DecompressThreadEntry failed for %g\n", FvFileGuid));
      return Status;         
   }    
  }

  *OutSizePtr = DstBufferSize;
  *OutputBuffer = DstBuffer + 8;
  
  FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, " Decompress Complete - %p\n", DstBuffer));

  return EFI_SUCCESS;
}

/**
  This api enables decompression and mounting of additional firmware volumes
  from main fv.

  @param  Buffer                Pointer to the firmware volume to look into. Usually
                                Boot Firmware Volume (BFV).
  @param  BufferSize            Size of buffer containing source FV.
  @param  FvFileGuid            GUID of the FV to be searched, decompressed and mounted.
  @param  Stage                 The stage at which FV is expected to be mounted, 
                                this is type MOUNTING_STAGE

  @retval EFI_SUCCESS           The volume was found else error.

**/
EFI_STATUS
StartFvDecompression (
    IN  VOID                *Buffer,
    IN  UINTN               BufferSize,
    IN  EFI_GUID            *FvFileGuid,
    IN  DECOMPRESSION_MODE  LaunchMode,
    IN  MOUNTING_STAGE      Stage
  )
{
  FVContext*     FvCtxt;
  FfsFileInfo    FfsFileInfo, *FfsFileInfoPtr;
  VOID *OutBuffer;
  UINTN OutSize  = 0, ActualFvSize  = 0;
  EFI_STATUS Status = EFI_SUCCESS;

  if (Buffer == NULL || BufferSize == 0 || FvFileGuid == NULL)
    return EFI_INVALID_PARAMETER;

  FvCtxt = OpenFVFile (Buffer, BufferSize, &ActualFvSize);

  if (FvCtxt == NULL)
    return EFI_INVALID_PARAMETER;

  FfsFileInfoPtr = GetNextFileFromFV (FvCtxt, &FfsFileInfo, 0);

  while (FfsFileInfoPtr)
  {
    FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "File : %g\n", &FfsFileInfoPtr->FileNameGuid));
    FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "File Size : %d (0x%X)\n", FfsFileInfoPtr->FileSize, FfsFileInfoPtr->FileSize));
    FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "File Type : %x\n", FfsFileInfoPtr->FileType));
    FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "File UI Name : %a\n", FfsFileInfoPtr->UIFileName));
    FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "File Ptr : %p\n\n", FfsFileInfoPtr->ROFileDataPtr));


    if (FfsFileInfoPtr->Attributes & FFS_FILE_ATTRIBUTE_COMPRESSED)
    {
      if (CompareGuid (FvFileGuid, &FfsFileInfoPtr->FileNameGuid))
      {

       Status = PerformGuidedSectionDecode ((EFI_COMMON_SECTION_HEADER  *)FfsFileInfoPtr->SectionPtr,
                                            &OutBuffer, &OutSize, FvFileGuid, LaunchMode, Stage);

       if (Status != EFI_SUCCESS)
       {
          DEBUG ((EFI_D_ERROR, "ERROR: Unable to decompress Fv: %g\n", &FfsFileInfoPtr->FileNameGuid, FvFileGuid));
          return Status;
       }

       CloseFVFile (FvCtxt);
       return EFI_SUCCESS;
      }
    }
    FfsFileInfoPtr = GetNextFileFromFV (FvCtxt, &FfsFileInfo, 0);
  }

  FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "ProcessFvDecompression: Done \n"));

  CloseFVFile (FvCtxt);
  return EFI_NOT_FOUND;
}


