/** @file FvDecompress.c

  Source for decompressing FV in Post SEC

  Copyright (c) 2019 Qualcomm Technologies, Inc.
  All rights reserved.

**/


/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/04/19   kpa     Initial revision

=============================================================================*/

#include "com_dtypes.h"

#include <Library/FvDecompressLib.h>
#include "FvDecompressInternalLib.h"
#include <Library/HobLib.h>

#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/MountFvLib.h>

/*****************************************************************************
 *            Public functions
 *****************************************************************************/


/**
   API to Reinitialize Fv Decompress Lib.
   This retrieves FV Data pointer shared by SEC via HOB and initializes
   post-SEC instance of the Lib

  @param  None

  @retval EFI_SUCCESS           Initialization was success else error.

**/
EFI_STATUS 
DecompressFvLibInit ( 
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
)
{
  EFI_HOB_GUID_TYPE       *GuidHob;
  VOID                    *DecompressFvList, **FvListPtr ;
  EFI_STATUS Status;
  
  /* Retrieve GUID HOB data that contains the FV buffer info. */
  GuidHob = GetFirstGuidHob (&gFvDecompressHobGuid);  
  
  if (GuidHob == NULL) 
    return EFI_NOT_FOUND;
  
  FvListPtr = GET_GUID_HOB_DATA (GuidHob);
  DecompressFvList = *FvListPtr;

  Status = FvListInitPostSec (DecompressFvList);

  if (EFI_ERROR (Status))
    DEBUG ((EFI_D_ERROR, "Error: FvListInitPostSec Failed - %r\n", Status));

  return Status;
 
}

/**
  This api enables decompression and mounting of additional firmware volumes
  from main fv.

  @param  FvFileGuid            GUID of the FV whose decompression status
                                to be checked and mounted.

  @retval EFI_SUCCESS           FV to be decompressed found and mounted
                                else error.

**/
EFI_STATUS
MountDecompressedFv (IN  EFI_GUID *FvFileGuid)
{  
  EFI_STATUS Status;  
  UINT64  TempBuffAddr =0; 
  UINT64  TempBuffSize =0;
  UINTN FvWaitStart, FvWaitEnd, WaitTime;

  if (FvFileGuid == NULL)
    return EFI_INVALID_PARAMETER;
  
  FvWaitStart = GetTimerCountms ();    
  Status = WaitForProcessingComplete (FvFileGuid);
  if (EFI_ERROR (Status))
  {
    DEBUG ((EFI_D_ERROR, "Error: WaitForProcessingComplete Failed - %r\n", Status));
    return Status;    
  } 
    
  Status = GetDecompressedFvBufferInfo (FvFileGuid, &TempBuffAddr, &TempBuffSize);
  if (EFI_ERROR (Status))
  {
    DEBUG ((EFI_D_ERROR, "Error: GetDecompressedFvBufferInfo Failed - %r\n", Status));
    return Status;    
  } 
    
  FV_DECOMPRESS_DBG_LOG((EFI_D_ERROR, "DecompressFvList BaseAddr: 0x%x Size: 0x%x\n", TempBuffAddr, TempBuffSize));

  Status = MountFVFromBuffer ((EFI_PHYSICAL_ADDRESS) (UINTN) TempBuffAddr,
                              (UINT64) TempBuffSize,
                               NULL,
                              0);
  if(Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_ERROR, "Error: Failed to Mount FV \n"));
    return Status;
  }
  FvWaitEnd = GetTimerCountms ();
  WaitTime = FvWaitEnd - FvWaitStart;
  
  
  FV_DECOMPRESS_DBG_LOG ((EFI_D_ERROR, "FV Launch Wait Delta : %d ms\n", WaitTime));    

  
  Status = ConnectByProtocol (&gEfiFirmwareVolumeBlockProtocolGuid);

  if(Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_ERROR, "Error: ConnectByProtocol Failed \n"));
    return Status;
  }
  
  Status = FreeDecompressFvInfo (FvFileGuid);
  
  return Status;
}

