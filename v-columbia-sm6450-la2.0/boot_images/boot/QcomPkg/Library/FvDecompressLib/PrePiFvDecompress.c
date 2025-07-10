/** @file PrePiFvDecompress.c

  Source for decompressing FV in pre PI environment

  Copyright (c) 2019-2020 Qualcomm Technologies, Inc.
  All rights reserved.

**/


/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/27/20   cm      Enable single threaded boot 
 06/04/19   kpa     Initial revision

=============================================================================*/

#include "com_dtypes.h"

#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

//#include "StWrappers.h"
#include <Library/KernelLib.h>

#include <Library/FvParserLib.h>
#include <Library/FvDecompressLib.h>
#include "FvDecompressInternalLib.h"

#include <Pi/PiFirmwareFile.h>
#include <Pi/PiBootMode.h>
#include <Pi/PiHob.h>

#include <Guid/ExtractSection.h>

#include <Library/HobLib.h>
#include <Library/PrePiLib.h>
#include <Library/UefiCfgLib.h>

extern BOOLEAN KernelInterfaceInit (VOID);

extern EFI_STATUS InitMemoryMutex (VOID);

extern
VOID *
EFIAPI
BuildGuidDataHob (
  IN CONST EFI_GUID              *Guid,
  IN VOID                        *Data,
  IN UINTN                       DataLength
  );

/*GUID for Decompression Data HOB {12DBD93D-402A-416E-EC20-5F80CF5F7FE7}*/
extern EFI_GUID gFvDecompressHobGuid;

/*****************************************************************************
 *            Private functions
 *****************************************************************************/
 
/* API to initialize the List and Data structures keeping track of FVs under process */
EFI_STATUS 
STATIC
DecompressFvHobInit (VOID)
{
  STATIC BOOLEAN HobInitialized = FALSE;
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 EnableMultiThreading = 0;

  VOID *DataPtr = NULL;  
  
  if(HobInitialized == TRUE)
    return EFI_SUCCESS;

  HobInitialized = TRUE;
  
  if (KernelInterfaceInit() == FALSE)
  {
    GetConfigValue ("EnableMultiThreading", &EnableMultiThreading);
    if (EnableMultiThreading)
    {
      DEBUG ((EFI_D_ERROR, "Error: KernelInterfaceInit failed \n"));
      return EFI_ABORTED;
    }
 
    DEBUG ((EFI_D_WARN, "Warning: KernelInterfaceInit failed \n"));

  }
  Status = DecompressFvListInit (&DataPtr);

  if(Status != EFI_SUCCESS )
    return Status;
  
  if(DataPtr !=NULL)
  {
    /*Since HOB cannot be updated later in DXE, we do not pass the whole data struct
      rather just the pointer to list of FV's under process 
    */
    BuildGuidDataHob ( &gFvDecompressHobGuid, &DataPtr, sizeof (VOID *));
    return EFI_SUCCESS;
  }
  
  return EFI_ABORTED; 
}

/*****************************************************************************
 *            Public functions
 *****************************************************************************/

/**
   API to initialize Fv Decompress Lib and dependencies.

  @param  None

  @retval EFI_SUCCESS           Initialization was success else error.

**/
EFI_STATUS 
PrePiDecompressFvLibInit (VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  /*Setup HOB data to pass on FV buffer info */
  Status = DecompressFvHobInit ();
  if (EFI_ERROR (Status))
     DEBUG ((EFI_D_ERROR, "Error: DecompressFvHobInit Failed - %r\n", Status));
  
  /*Signal memory allocation api's to synchronize using mutex
    from this point onwards, since multiThreaded decompress Fv lib api's
    depend on them.
  */
  return InitMemoryMutex ();
}
/**
  Api to build FV Hob for Dxe consumption

  @param  FvGuid            GUID of the FV whose HOB needs to be added.

  @retval EFI_SUCCESS       Operation was success else error code.


**/
EFI_STATUS
PropagateProcessingFvInfo (IN EFI_GUID  *FvGuid)
{
  EFI_FV_INFO    FvImageInfo;
  EFI_STATUS     Status;  
  UINT64  TempBuffAddr =0; 
  UINT64  TempBuffSize =0;  

  FVContext*     FvCtxt;
  UINTN ActualFvSize  = 0;

  
  if(FvGuid == NULL)
     return EFI_INVALID_PARAMETER;

  Status = GetDecompressedFvBufferInfo (FvGuid, &TempBuffAddr, &TempBuffSize);
  if (EFI_ERROR (Status))
  {
    DEBUG ((EFI_D_ERROR, "Error: GetDecompressedFvBufferInfo Failed - %r\n", Status));
    return Status;    
  } 

  FvCtxt = OpenFVFile ((VOID *)TempBuffAddr, TempBuffSize, &ActualFvSize);
  if (FvCtxt == NULL)
    return EFI_INVALID_PARAMETER;
  Status = GetFVInfo (FvCtxt, (EFI_FV_INFO *)&FvImageInfo);

  CloseFVFile (FvCtxt);  
  
  /* Inform HOB consumer phase, i.e. DXE core, the existance of this FV  */
  BuildFvHob ((EFI_PHYSICAL_ADDRESS) (UINTN) FvImageInfo.FvStart, FvImageInfo.FvSize);

  /* Make the encapsulated volume show up in DXE phase to skip processing of
    encapsulated file again.
  */
  BuildFv2Hob (
    (EFI_PHYSICAL_ADDRESS) (UINTN) FvImageInfo.FvStart,
    FvImageInfo.FvSize, &FvImageInfo.FvName,
    &(((EFI_FFS_FILE_HEADER *) TempBuffAddr)->Name)    // FvFileHandle
    );

  Status = FreeDecompressFvInfo (FvGuid);
  return Status;
}
