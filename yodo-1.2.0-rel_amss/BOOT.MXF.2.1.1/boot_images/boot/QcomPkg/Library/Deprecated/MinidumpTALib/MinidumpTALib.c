/******************************************************************//**
 * @file MinidumpTALib.c
 *
 * @brief MinidumpTALib functions
 *
 * Copyright (c) 2020 by Qualcomm Technologies, Inc. 
 * All Rights Reserved.
 *
 *********************************************************************/

#include <Library/MinidumpTALib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIQseecom.h>

#define MINIDUMMP_TA_NAME         "mdcompress_a"
#define MINIDUMPTA_PARTITION_GUID \
    { 0xc6a5a9f5, 0x86cd, 0x4bea, { 0xa2, 0xca, 0x6c, 0x58, 0x64, 0x4b, 0x0d, 0xa8 } }

/**
 * Minidump TA Loading
 */
EFI_STATUS MinidumpTALoad (VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_QSEECOM_PROTOCOL *MinidumpQseecomProtocol = NULL; 
  EFI_GUID MinidumpTAPartitionGuid = MINIDUMPTA_PARTITION_GUID;
  UINT32 HandleId = 0;

  /* Get handle to TzeLoaderProtocol */ 
  Status = gBS->LocateProtocol(&gQcomQseecomProtocolGuid, NULL, (VOID **)&MinidumpQseecomProtocol); 
  if(EFI_ERROR(Status)) 
  { 
    DEBUG ((EFI_D_ERROR, "MinidumpTALib:Unable to locate QseeCom protocol: %r\n", Status));  
    return Status; 
  } 

  Status = MinidumpQseecomProtocol->QseecomStartAppByGuid(MinidumpQseecomProtocol, &MinidumpTAPartitionGuid, &HandleId); 
  if (EFI_ERROR(Status)) 
  { 
    DEBUG ((EFI_D_ERROR, "MinidumpTALib:LoadImageFromPartition(mdcompress) failed: 0x%r\n", Status)); 
    return Status;
  } 
  DEBUG ((EFI_D_ERROR, "MinidumpTALib:LoadImageFromPartition(mdcompress) success: 0x%r\n", Status));
  return Status; 
}

