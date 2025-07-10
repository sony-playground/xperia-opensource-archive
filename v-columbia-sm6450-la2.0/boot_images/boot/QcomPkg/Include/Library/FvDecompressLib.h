/** @file FvDecompressLib.h

  Header file for processing decompressed FV in post SEC  environment

  Copyright (c) 2019 Qualcomm Technologies, Inc.
  All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 06/04/19   kpa     Initial revision
 
=============================================================================*/

#ifndef _FVDECOMPRESSLIB_H_
#define _FVDECOMPRESSLIB_H_

typedef enum 
{
  SYNCHRONOUS = 0,
  BACKGROUND  = 1
} DECOMPRESSION_MODE;

/**
   API to initialize Fv Decompress Lib and dependencies. Also creates a
   Data HOB to pass on FV Decompression meta info beyond SEC. Needed to
   enable FV Decompression optimization. SEC starts off FV decompression, 
   which is checked at a later stage in DXE. The meta data needed to perform
   status check for decompression operation is passed on by SEC to DXE in a data HOB

  @param  None

  @retval EFI_SUCCESS           Initialization was success else error.

**/
EFI_STATUS 
PrePiDecompressFvLibInit (VOID);

/**
  Api to start decompression of additional firmware volumes from main fv.
  The Api searches for fv with input file guid and starts off
  decompression in either blocking or non-blocking mode

  @param  Buffer                Pointer to the firmware volume to look into. Usually
                                Boot Firmware Volume (BFV).
  @param  BufferSize            Size of buffer containing source FV.
  @param  FvFileGuid            GUID of the FV to be searched, decompressed and mounted.
  @param  LaunchMode            Flag to enable nonBlocking/Background operation (multithreaded)            
  
  @retval EFI_SUCCESS           Operation was success else error.

**/

EFI_STATUS
StartFvDecompression (
  IN  VOID                *Buffer,
  IN  UINTN               BufferSize,
  IN  EFI_GUID            *FvFileGuid,
  IN  DECOMPRESSION_MODE  LaunchMode
);

/**
  Api to Build FV Hob for Dxe consumption. Needed to pass on the FV buffer info
  to DXE after decompression, so as to enable DXE to mount the FV.

  @param  FvGuid            GUID of the FV whose HOB needs to be added.

  @retval EFI_SUCCESS       Operation was success else error code.


**/
EFI_STATUS
PropagateProcessingFvInfo (IN EFI_GUID  *FvGuid);
  
/**
  This api enables decompression and mounting of additional firmware volumes.
  The api assumes the decompression is already started for input fv. It waits
  on the operation to complete, if not so, then proceeds to mount.  

  @param  FvFileGuid            GUID of the FV whose decompression status
                                to be checked and mounted.

  @retval EFI_SUCCESS           FV to be decompressed found and mounted
                                else error.

**/
EFI_STATUS
MountDecompressedFv (IN EFI_GUID *FvFileGuid);

/**
  Api to wait till FV corresponding to input GUID name is decompressed/processed
  for further use. Is a blocking api.

  @param  FvFileGuid            GUID of the FV whose processing status is being queried

  @retval EFI_SUCCESS           The volume was found else error.

**/
EFI_STATUS
WaitForProcessingComplete (IN  EFI_GUID *FvFileGuid);


/**
  Api to start decompression of firmware volume.
  FV decompression carried out in either blocking or non-blocking mode

  @param  FfsFileInfoSectionPtr File info section pointer
  @param  OutputBuffer          Pointer to the decompressed firmware volume. 
  @param  OutSizePtr            Size of buffer for decompressed FV.
  @param  FvFileGuid            GUID of the FV to be decompressed
  @param  LaunchMode            Flag to enable nonBlocking call (multithreaded)            
  
  @retval EFI_SUCCESS           Operation was success else error.

**/
EFI_STATUS 
PerformGuidedSectionDecode (
    IN  EFI_COMMON_SECTION_HEADER  *FfsFileInfoSectionPtr,
    OUT VOID                       **OutputBuffer,
    OUT UINTN                      *OutSizePtr,
    IN  EFI_GUID                   *FvFileGuid,
    IN  DECOMPRESSION_MODE         LaunchMode    
  );
#endif
