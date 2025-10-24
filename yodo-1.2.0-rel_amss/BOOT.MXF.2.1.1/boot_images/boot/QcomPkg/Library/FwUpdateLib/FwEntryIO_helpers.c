/** @file FwEntryIO_helpers.c
   
  Payload fw entry read write functions for data driven firmware update solution.

  Copyright (c) 2012-2015, 2017-2018, 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when          who      what, where, why
 ----------    ---      --------------------------------------------------
 2021/02/13    dmohan   Changes to support A/B Recovery feature
 2019/03/13    vkasilya Removed redundant freepool Buffer to avoid crash.
 2019/02/06    rajb     Skipping delete of partition contents in delete phase
 2019/02/01    rajb     Removed redundant code
 2018/06/28    prema    Change to support multiple DPP entries and skip duplicate 
                        backup and delete operations in backup and rollback phase.
                        Changes to return unsupported for FAT and SSD Update types 
                        and to remove functions related to FAT and SSD processing
 2018/05/21    gparam   Changes to reject any request for FAT file update through
                        firmware update
 2017/06/21    gparam   Change to return payload files parsed from the payload FV
                        in a newly allocated buffer instead of pointing to location
                        within the FV
 2017/05/08    gparam   Minor tweaks to logging
 2017/04/18    gparam   Fixed the incorrect error handling during file read from FV
 2017/02/22    pkn      Added changes required to support new update type - FWCLASS_GUID
 2015/04/15    mic      Added 64bit firmware update support
 2012/10/11    rs       Added DeleteFile and DeletePartition functions
 2012/10/08    mic      Moved common macro to FwCommonLib
 2012/09/28    rs       Implementation of the helper functions to read/write
 2012/09/21    mic      Initial version

=============================================================================*/

#include <Uefi.h>
#include <Include/Library/FwCommonLib.h>

#include <Library/FwCommonLib.h>
#include <Library/FwUpdateLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/EdkiiSystemCapsuleLib.h>
#include <Library/QcomLib.h>

#include <Include/Library/MemoryAllocationLib.h>
#include "FwPayloadEntry.h"
#include "FwEntryIO_helpers.h"

#define FIRST_BLOCK 0
#define DEFAULT_COPY_LOOP_CNT 2

#define FW1_FILE_SIZE    1024

extern BOOLEAN bDoubleUpdateNeeded;
const FWENTRY_READ FwEntrySourceReadFunctions[FWENTRY_SOURCE_TYPE_MAX]={
  FwUpdateReadEntryFromFV
};

const FWENTRY_READ FwEntryDestReadFunctions[FWENTRY_UPDATE_TYPE_MAX]={
  FwUpdateReadEntryFromPartition,
  FwUpdateReadEntryFromFat,
  FwUpdateReadEntryFromDppQcom,
  FwUpdateReadEntryFromDppOem,
  FwUpdateReadEntryFromDppQcom,
  FwUpdateReadEntryFromPartition,
  FwUpdateReadDestEntryFromHW1
};

const FWENTRY_WRITE FwEntryDestWriteFunctions[FWENTRY_UPDATE_TYPE_MAX]={
  FwUpdateWriteEntryToPartition,
  FwUpdateWriteEntryToFat,
  FwUpdateWriteEntryToDppQcom,
  FwUpdateWriteEntryToDppOem,
  FwUpdateWriteEntryToDppQcom,
  FwUpdateWriteEntryToPartition,
  FwUpdateWriteDestEntryToHW1
};

const FWENTRY_READ FwEntryBackupReadFunctions[FWENTRY_BACKUP_TYPE_MAX]={
  FwUpdateReadEntryFromPartition,
  FwUpdateReadEntryFromFat,
  FwUpdateReadBackupEntryFromHW1
};
  
const FWENTRY_WRITE FwEntryBackupWriteFunctions[FWENTRY_BACKUP_TYPE_MAX]={
  FwUpdateWriteEntryToPartition,
  FwUpdateWriteEntryToFat,
  FwUpdateWriteBackupEntryToHW1
};

 /**
 * This function backs up fw entry from destination path to 
 * backup path. If target entry doesn't exist in destination 
 * path, backup operation will be skipped 
 *
 * @param FwEntry -  Firmware entry 
 * 
 * @return EFI_STATUS 
 */
EFI_STATUS
FwEntryBackup(
    IN QPAYLOAD_FW_ENTRY *FwEntry
    )
{
  EFI_STATUS                        Status                = EFI_SUCCESS;
  FWENTRY_UPDATE_TYPE               UpdateType            = FWENTRY_UPDATE_TYPE_MAX;
  FWENTRY_BACKUP_TYPE               BackupType            = FWENTRY_BACKUP_TYPE_MAX;
  VOID                              *Buffer               = NULL;
  VOID                              *BufferDest           = NULL;
  UINTN                             BufSize               = 0;
  UINTN                             BufSizeDest           = 0;
  FWENTRY_READ                      FwReadDestFunction    = NULL; 
  FWENTRY_READ                      FwReadBackupFunction  = NULL; 
  FWENTRY_WRITE                     FwWriteBackupFunction = NULL;
  UINTN                             LoopCount             = 0;
  BOOLEAN                           IsDppType             = FALSE;

  if (FwEntry == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  /*Unknown update type should be ignored if double update is needed*/
  if ((FwEntry->Metadata.UpdateType >= FWENTRY_UPDATE_TYPE_MAX ) ||
      (FwEntry->Metadata.BackupType >= FWENTRY_BACKUP_TYPE_MAX ))
  {
    if(bDoubleUpdateNeeded)
    {
      return EFI_SUCCESS;
    }
    else
    {
      Status = EFI_INVALID_PARAMETER;
      DEBUG_ERR_LABEL("Unknown UpdateType/BackupType\n",FwEntryBackupExit);
    }
  }

  UpdateType = FwEntry->Metadata.UpdateType;
  BackupType = FwEntry->Metadata.BackupType;

  Status = FwEntryCheckForDppUpdateType (FwEntry, &IsDppType);
  HANDLE_ERROR_LABEL(Status,FwEntryCheckForDppUpdateType(FwEntry), FwEntryBackupExit);

  if (TRUE == IsDppType)
  {
    /* DPP types are the only update types that are allowed to do
       file-by-file update instead of whole partition. But
       still, the backup has to happen as whole partition

       If current update type is of DPP, then overwrite the
       destination read function to whole partition read
       instead of the one associated to current update type.
       This will result in taking whole partition backup instead
       of just the backup of the file being updated.
    */
    FwReadDestFunction   = FwUpdateReadEntryFromPartition;
  }
  else
  {
    FwReadDestFunction   = FwEntryDestReadFunctions[UpdateType];
  }

  FwWriteBackupFunction  = FwEntryBackupWriteFunctions[BackupType];
  FwReadBackupFunction   = FwEntryBackupReadFunctions[BackupType];

  if ((FwReadDestFunction == NULL) || 
      (FwWriteBackupFunction == NULL) || 
      (FwReadBackupFunction == NULL))
  {
    Status = EFI_INVALID_PARAMETER;
    DEBUG_ERR_LABEL("      Bad FwReadDestFunction/FwWriteBackupFunction/FwReadBackupFunction!!\n",
                    FwEntryBackupExit);
  }

  Status = FwReadDestFunction(FWENTRY_OPERATION_PATH_TYPE_DEST,FwEntry,&Buffer,&BufSize);
  //If the destination doesn't exist we need to skip the backup for this FwEntry.
  //We are assuming a partition will always exist, but a DPP entry or File may not.
  //A success should be returned in that case.
  if (Status == EFI_NOT_FOUND)
  {
    Status = EFI_SUCCESS;
    DEBUG_WARN_LABEL("      Original file does not exist. Ignoring backup request\n",
                     FwEntryBackupExit);
  }
  else
  {
    HANDLE_ERROR_LABEL(Status, FwReadDestFunction, FwEntryBackupExit);
  }

  //We need to write to the Backup partition and verify it - twice
  for (LoopCount = 0; LoopCount < DEFAULT_COPY_LOOP_CNT; LoopCount++)
  {
    Status = FwWriteBackupFunction(FWENTRY_OPERATION_PATH_TYPE_BACKUP,FwEntry,Buffer,BufSize);
    HANDLE_ERROR_LABEL(Status, FwWriteBackupFunction, FwEntryBackupExit);

    Status = FwReadBackupFunction(FWENTRY_OPERATION_PATH_TYPE_BACKUP,FwEntry,&BufferDest,&BufSizeDest);
    HANDLE_ERROR_LABEL(Status, FwReadBackupFunction, FwEntryBackupExit);

    //Check if what we read back from the backup partition is same as what we were writing
    if((BufSize == BufSizeDest) && (CompareMem (BufferDest,Buffer,BufSize) == 0))
    {
      Status = EFI_SUCCESS;
      goto FwEntryBackupExit;
    }
    else
    {
      Status = EFI_VOLUME_CORRUPTED;
      //Free-up the BufferDest as everytime in this loop, there will be a new allocation in the Read()
      if(BufferDest != NULL)
      {
        gBS->FreePool(BufferDest);
        BufferDest = NULL;
      }  
    }
  }

FwEntryBackupExit:

  if (Buffer != NULL)
  {
    gBS->FreePool(Buffer);
    Buffer = NULL;
  }

  if (BufferDest != NULL)
  {
    gBS->FreePool(BufferDest);
    BufferDest = NULL;
  }
  return Status;
}


/**
 * This function updates the FwEntry from payload path to 
 * destination path. 
 *
 * @param FwEntry -  Firmware entry
 * 
 * @return EFI_STATUS 
 */

EFI_STATUS
FwEntryUpdate(
    IN QPAYLOAD_FW_ENTRY *FwEntry,
    IN FWENTRY_OPERATION_PATH_TYPE PathType
    ) 
{
  EFI_STATUS                        Status               = EFI_SUCCESS;
  FWENTRY_UPDATE_TYPE               UpdateType           = FWENTRY_UPDATE_TYPE_MAX;
  FWENTRY_SOURCE_TYPE               SourceType           = FWENTRY_SOURCE_TYPE_MAX;
  VOID                             *Buffer               = NULL;
  VOID                             *BufferDest           = NULL;
  UINTN                             BufSize              = 0;
  UINTN                             BufSizeDest          = 0;
  FWENTRY_READ                      FwReadFunction       = NULL; 
  FWENTRY_WRITE                     FwWriteFunction      = NULL;
  UINTN                             LoopCount            = 0;

  if(FwEntry == NULL)  
  {
    return EFI_INVALID_PARAMETER;
  }

  /*Unknown update type should be ignored if double update is needed*/
  if ((FwEntry->Metadata.UpdateType >= FWENTRY_UPDATE_TYPE_MAX ) ||
      (FwEntry->Metadata.BackupType >= FWENTRY_BACKUP_TYPE_MAX ))
  {
    if(bDoubleUpdateNeeded)
    {
      return EFI_SUCCESS;
    }
    else
    {
      return EFI_INVALID_PARAMETER;
    }
  }

  UpdateType = FwEntry->Metadata.UpdateType;
  SourceType = FWENTRY_SOURCE_TYPE_FV;
 
  if ((UpdateType >= FWENTRY_UPDATE_TYPE_MAX) || (SourceType >= FWENTRY_SOURCE_TYPE_MAX) )
  {
    return EFI_INVALID_PARAMETER;
  }
  
  switch(FwEntry->Metadata.Operation)
  {
    case FWENTRY_OPERATION_TYPE_DELETE:
      DEBUG((EFI_D_ERROR,"Deprecated operation DELETE encountered\n"));
      Status = EFI_UNSUPPORTED;
      goto FwEntryUpdateExit;

    case FWENTRY_OPERATION_TYPE_UPDATE:

      if ((UpdateType == FWENTRY_UPDATE_TYPE_FAT_FILE) ||
          (UpdateType == FWENTRY_UPDATE_TYPE_SSD))
      {
        DEBUG((EFI_D_ERROR,"Unsupported update type for operation type UPDATE\n"));
        return EFI_UNSUPPORTED;
      }

      FwWriteFunction  = FwEntryDestWriteFunctions[UpdateType];
      FwReadFunction   = FwEntryDestReadFunctions[UpdateType];

      if ((FwWriteFunction == NULL) || 
          (FwReadFunction == NULL))
      {
        return EFI_INVALID_PARAMETER;
      }

      //Check if the payload was encrypted. In that case, no need to read from FV.
      //Just read from the DecryptedBuffer.

      Buffer = FwEntry->FwEntryBuffer;
      BufSize = FwEntry->FwEntrySize;
      if ((Buffer == NULL) || (BufSize == 0))
      {
        return EFI_INVALID_PARAMETER;
      }

      //We need to write to the Dest partition and verify it - twice
      for (LoopCount = 0; LoopCount < DEFAULT_COPY_LOOP_CNT; LoopCount++)
      {
        Status = FwWriteFunction(PathType,FwEntry,Buffer,BufSize);
        HANDLE_ERROR_LABEL(Status, FwWriteFunction, FwEntryUpdateExit);

        Status = FwReadFunction(PathType,FwEntry,&BufferDest,&BufSizeDest);
        HANDLE_ERROR_LABEL(Status, FwEntryUpdate, FwEntryUpdateExit);

        //Check if what we read back from the dest partition is same as what we were writing

        if(FwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_PARTITION)
        {
          if ((CompareMem (BufferDest,Buffer,BufSize) == 0))
          {
            Status = EFI_SUCCESS;
            goto FwEntryUpdateExit;
          }
        }
        else
        {
          if ((CompareMem (BufferDest,Buffer,BufSize) == 0) && 
              (BufSize == BufSizeDest) )
          {
            Status = EFI_SUCCESS;
            goto FwEntryUpdateExit;
          }
        }

        Status = EFI_VOLUME_CORRUPTED;
        //Free-up the BufferDest as everytime in this loop, there will be a new allocation in the Read()
        if( BufferDest != NULL)
        {
          gBS->FreePool(BufferDest);
          BufferDest = NULL;
        }
      }

      break;

    case FWENTRY_OPERATION_TYPE_IGNORE:
      return EFI_SUCCESS;

    default:
      DEBUG((EFI_D_WARN,"Unsupported operation type\n"));
      return EFI_UNSUPPORTED;
  }

 
FwEntryUpdateExit:

  if (BufferDest != NULL)
  {
    gBS->FreePool(BufferDest);
    BufferDest = NULL;
  }
  
  return Status;
}


/**
 * This function rolls back the FwEntry from the destination/backup path to 
 * backup/destination path respectively.
 *
 * @param FwEntry -  Firmware entry
 * 
 * @return EFI_STATUS 
 */

EFI_STATUS
FwEntryRollback(
    IN QPAYLOAD_FW_ENTRY *FwEntry
    )
{
  EFI_STATUS                        Status                  = EFI_SUCCESS;
  FWENTRY_UPDATE_TYPE               UpdateType              = FWENTRY_UPDATE_TYPE_MAX;
  FWENTRY_BACKUP_TYPE               BackupType              = FWENTRY_BACKUP_TYPE_MAX;
  VOID                             *Buffer                  = NULL;
  VOID                             *BufferReadBack          = NULL;
  UINTN                             BufSize                 = 0;
  UINTN                             BufSizeReadBack         = 0;
  FWENTRY_READ                      FwReadFunction          = NULL;
  FWENTRY_READ                      FwReadBackFunction      = NULL;
  FWENTRY_WRITE                     FwWriteFunction         = NULL;
  UINTN                             LoopCount               = 0;
  BOOLEAN                           IsDppType              = FALSE;
  FWENTRY_OPERATION_PATH_TYPE       RollbackSourceType     = 0;
  FWENTRY_OPERATION_PATH_TYPE       RollbackDestType       = 0;

  if (FwEntry == NULL) 
  {
    return EFI_INVALID_PARAMETER;
  }
  /*Unknown update type should be ignored if double update is needed*/
  if ((FwEntry->Metadata.UpdateType >= FWENTRY_UPDATE_TYPE_MAX ) ||
      (FwEntry->Metadata.BackupType >= FWENTRY_BACKUP_TYPE_MAX ))
  {
    if(bDoubleUpdateNeeded)
    {
      Status = EFI_SUCCESS;
      goto FwEntryRollbackExit;
    }
    else
    {
      Status = EFI_INVALID_PARAMETER;
      goto FwEntryRollbackExit;
    }
  }

  UpdateType = FwEntry->Metadata.UpdateType;
  BackupType = FwEntry->Metadata.BackupType;

  switch(FwEntry->Metadata.Operation)
  {
    case FWENTRY_OPERATION_TYPE_DELETE:
      DEBUG((EFI_D_ERROR,"Deprecated operation DELETE encountered\n"));
      Status = EFI_UNSUPPORTED;
      goto FwEntryRollbackExit;

    case FWENTRY_OPERATION_TYPE_UPDATE:
      /* Rollback need to be done from backup to dest for custom firmware component.*/
      if (FwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_CUSTOM_FIRMWARE1)
      {
        FwReadFunction = FwEntryBackupReadFunctions[BackupType];
        FwWriteFunction  = FwEntryDestWriteFunctions[UpdateType];
        FwReadBackFunction = FwEntryDestReadFunctions[UpdateType];
        RollbackSourceType = FWENTRY_OPERATION_PATH_TYPE_BACKUP;
        RollbackDestType = FWENTRY_OPERATION_PATH_TYPE_DEST;
      }
      else
      {
        /* Backup partitions are updated with capsule contents first.
           So, rollback should be done from dest to backup.
        */
        FwReadFunction = FwEntryDestReadFunctions[UpdateType];
        FwWriteFunction = FwEntryBackupWriteFunctions[BackupType];
        FwReadBackFunction = FwEntryBackupReadFunctions[BackupType];
        RollbackSourceType = FWENTRY_OPERATION_PATH_TYPE_DEST;
        RollbackDestType = FWENTRY_OPERATION_PATH_TYPE_BACKUP;

        Status = FwEntryCheckForDppUpdateType (FwEntry, &IsDppType);
        HANDLE_ERROR_LABEL(Status,FwEntryCheckForDppUpdateType(FwEntry), FwEntryRollbackExit);
        
        if (TRUE == IsDppType)
        {
          /* DPP types are the only update types that are allowed to do
             file-by-file update instead of whole partition. But
             still, the backup has to happen as whole partition
          
             If current update type is of DPP, then overwrite the
             destination read function to whole partition read
             instead of the one associated to current update type.
             This will result in taking whole partition backup instead
             of just the backup of the file being updated.
          */
          FwReadFunction  = FwUpdateReadEntryFromPartition;
          RollbackSourceType = FWENTRY_OPERATION_PATH_TYPE_BACKUP;
          RollbackDestType = FWENTRY_OPERATION_PATH_TYPE_DEST;
        }
      }

      if ((FwReadFunction == NULL) || 
          (FwWriteFunction == NULL) || 
          (FwReadBackFunction == NULL))
      {
        Status = EFI_INVALID_PARAMETER;
        goto FwEntryRollbackExit;
      }

      Status = FwReadFunction(RollbackSourceType,FwEntry,&Buffer,&BufSize);
      HANDLE_ERROR_LABEL(Status, FwReadFunction, FwEntryRollbackExit);

      /*We need to write to the RollbackDestType and verify it - twice*/
      for (LoopCount = 0; LoopCount < DEFAULT_COPY_LOOP_CNT; LoopCount++)
      {
        Status = FwWriteFunction(RollbackDestType,FwEntry,Buffer,BufSize);
        HANDLE_ERROR_LABEL(Status, FwEntryRollback, FwEntryRollbackExit);
      
        Status = FwReadBackFunction(RollbackDestType,FwEntry,&BufferReadBack,&BufSizeReadBack);
        HANDLE_ERROR_LABEL(Status, FwEntryRollback, FwEntryRollbackExit);
      
        /*Check if what we read back from the RollbackDestType partition 
          is same as what we were writing
        */
        if ((CompareMem (BufferReadBack,Buffer,BufSize) == 0) && 
            (BufSize == BufSizeReadBack))
        {
          Status = EFI_SUCCESS;
          goto FwEntryRollbackExit;
        }
    
        Status = EFI_VOLUME_CORRUPTED;
        /*Free-up the BufferReadBack as everytime in this loop, there will be a 
          new allocation in the Read()*/
        if( BufferReadBack != NULL)
        {
          gBS->FreePool(BufferReadBack);
          BufferReadBack = NULL;
        }
      }
      break;

    case FWENTRY_OPERATION_TYPE_IGNORE:
      
      Status = EFI_SUCCESS;
      goto FwEntryRollbackExit;

    default:
      DEBUG((EFI_D_WARN,"Unsupported operation type\n"));
      Status = EFI_UNSUPPORTED;
      goto FwEntryRollbackExit;
  }

FwEntryRollbackExit:

    if (Buffer != NULL)
    {
      gBS->FreePool(Buffer);
      Buffer = NULL;
    }
    if (BufferReadBack != NULL)
    {
      gBS->FreePool(BufferReadBack);
      BufferReadBack = NULL;
    }

  return Status;
}

 /**
 * Reads Entry from an FV
 *  into a buffer.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @Param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 * 
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateReadEntryFromFV(
    IN FWENTRY_OPERATION_PATH_TYPE         PathType,
    IN QPAYLOAD_FW_ENTRY                  *FwEntry,
    IN VOID                              **Buffer,
    IN OUT UINTN                          *BufferSize
    )

{
  EFI_STATUS                          Status     = EFI_SUCCESS;
  FV_BUFFER_HANDLE                   *FvBufferHandle = NULL;
  UINT32                              FileHeaderSize = 0;
  BOOLEAN                             ReadResult = FALSE;
  VOID                               *FileBuffer = NULL;
  UINTN                               FileBufferSize = 0;

  if ((FwEntry == NULL) || 
      (Buffer == NULL) || 
      (BufferSize == NULL) ||
      (*Buffer != NULL))
  {  
    return EFI_INVALID_PARAMETER;
  }
  *Buffer = NULL;

  //If PathType is Source we should return unsupported
  //as source is FV which is not FAT
  if (PathType == FWENTRY_OPERATION_PATH_TYPE_SOURCE) 
  {
    FvBufferHandle = (FV_BUFFER_HANDLE *)FwEntry->Handle[PathType];

    if ((FvBufferHandle == NULL) ||
        (FvBufferHandle->Buffer == NULL) ||
        (FvBufferHandle->BufferSize == 0))
    {
      return EFI_UNSUPPORTED;
    }
  }
  else if (PathType == FWENTRY_OPERATION_PATH_TYPE_BACKUP) 
  {
    return EFI_UNSUPPORTED;
  }
  else if (PathType == FWENTRY_OPERATION_PATH_TYPE_DEST) 
  {
    return EFI_UNSUPPORTED;
  }
  else
  {
    return EFI_INVALID_PARAMETER;
  }

  ReadResult = GetFfsByName(
    FvBufferHandle->Buffer,
    FvBufferHandle->BufferSize,
    &(FwEntry->Metadata.FileGuid),
    EFI_FV_FILETYPE_RAW,
    &FileBuffer,
    &FileBufferSize
    );
  if (FALSE == ReadResult)
  {
    Status = EFI_NOT_FOUND;
    HANDLE_ERROR_LABEL(Status,GetFfsByName,FwUpdateReadEntryFromFVExit);
  }
  
  if (IS_FFS_FILE2 (FileBuffer)) {
    FileHeaderSize = sizeof(EFI_FFS_FILE_HEADER2);
  } else {
    FileHeaderSize = sizeof(EFI_FFS_FILE_HEADER);
  }

  FileBuffer = (UINT8 *)FileBuffer + FileHeaderSize;
  FileBufferSize = FileBufferSize - FileHeaderSize;

  *Buffer = AllocateCopyPool (FileBufferSize, FileBuffer);
  if (*Buffer == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    HANDLE_ERROR_LABEL(Status,AllocateCopyPool,FwUpdateReadEntryFromFVExit);
  }

  *BufferSize = FileBufferSize;

  return EFI_SUCCESS;

FwUpdateReadEntryFromFVExit:
  if(EFI_ERROR(Status))
  {
    if(*Buffer != NULL)
    {
      gBS->FreePool(*Buffer);
      *Buffer = NULL;
    }
  }

  return Status;
}

/**
 * Reads an entry from an unformatted partition
 *  into a buffer.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @Param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 *
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateReadEntryFromPartition(
    IN FWENTRY_OPERATION_PATH_TYPE       PathType,
    IN QPAYLOAD_FW_ENTRY                 *FwEntry,
    IN VOID                              **Buffer,
    IN OUT UINTN                         *BufferSize
    )
{
  EFI_STATUS               Status      = EFI_SUCCESS;
  EFI_HANDLE               PartHandle  = NULL;

  if ((FwEntry == NULL) || 
      (Buffer == NULL) || 
      (BufferSize == NULL))
  {
    return EFI_INVALID_PARAMETER;
  } 
  *Buffer = NULL;

  PartHandle = FwEntry->Handle[PathType];

  if (PartHandle == NULL)
  {
    return EFI_UNSUPPORTED;
  }
         
  Status = FwUpdatePartitionRead(PartHandle,Buffer,BufferSize);
  HANDLE_ERROR_LABEL(Status,FwUpdatePartitionRead,FwUpdateReadEntryFromBlockExit);

  return EFI_SUCCESS;

FwUpdateReadEntryFromBlockExit:
  
  if(EFI_ERROR(Status))
  {
    if (*Buffer != NULL)
    {
      gBS->FreePool(*Buffer);
      *Buffer = NULL;
    }
  }
  return Status;
}

/**
 * Reads a entry from a FAT partition
 *  into a buffer.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @Param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 * 
 * Note: This function is no more supported as FAT file updates to
 * partitions other than DPP is deprecated to avoid possiblity of
 * file system corruption on power failure
 *
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateReadEntryFromFat(
    IN FWENTRY_OPERATION_PATH_TYPE       PathType,
    IN QPAYLOAD_FW_ENTRY                 *FwEntry,
    IN VOID                              **Buffer,
    IN OUT UINTN                         *BufferSize
    )
{
  return EFI_UNSUPPORTED;
}

/**
 * Reads a DPP item from DPP Qcom or OEM path
 *  into a buffer.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @Param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 * @param Type       - OEM or DPP 
 *  
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateReadEntryFromDpp(
    IN FWENTRY_OPERATION_PATH_TYPE       PathType,
    IN QPAYLOAD_FW_ENTRY                 *FwEntry,
    IN VOID                              **Buffer,
    IN OUT UINTN                         *BufferSize,
    IN CHAR16                            *Type
    )
{
  EFI_STATUS       Status       = EFI_SUCCESS;
  CHAR16           *DPPName     = NULL;

  if ((FwEntry == NULL) || 
      (Buffer == NULL) || 
      (BufferSize == NULL) || 
      (Type == NULL))
  { 
    return EFI_INVALID_PARAMETER;
  }
  *Buffer = NULL;

  //If PathType is Source we should return unsupported
  //as source is FV and not DPP
  if (PathType == FWENTRY_OPERATION_PATH_TYPE_SOURCE) 
  {
    return EFI_UNSUPPORTED;
  }
  else if (PathType == FWENTRY_OPERATION_PATH_TYPE_BACKUP) 
  {
    return EFI_UNSUPPORTED;
  }
  else if (PathType == FWENTRY_OPERATION_PATH_TYPE_DEST) 
  {
    DPPName = FwEntry->Metadata.UpdatePath.FileName;
  }
  else
  {
    return EFI_INVALID_PARAMETER;
  }

  if (DPPName == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status = FwUpdateDppRead(Type,DPPName,Buffer,BufferSize);
  HANDLE_ERROR_LABEL(Status, FwUpdateDppRead, FwUpdateReadEntryFromDppExit);

  return EFI_SUCCESS;

FwUpdateReadEntryFromDppExit:
  if (EFI_ERROR(Status))
  {
    if (*Buffer !=NULL)
    {
      gBS->FreePool(*Buffer);
      *Buffer = NULL;
    }
  }
  return Status;
}

/**
 * Reads a DPP item from DPP Qcom path
 *  into a buffer.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @Param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 *
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateReadEntryFromDppQcom(
    IN FWENTRY_OPERATION_PATH_TYPE       PathType,
    IN QPAYLOAD_FW_ENTRY                 *FwEntry,
    IN VOID                              **Buffer,
    IN OUT UINTN                         *BufferSize
    )
{
  return FwUpdateReadEntryFromDpp(PathType,FwEntry, Buffer, BufferSize,L"QCOM");
}

/**
 * Reads a DPP item from DPP OEM path
 *  into a buffer.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @Param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 *
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateReadEntryFromDppOem(
    IN FWENTRY_OPERATION_PATH_TYPE       PathType,
    IN QPAYLOAD_FW_ENTRY                 *FwEntry,
    IN VOID                              **Buffer,
    IN OUT UINTN                         *BufferSize
    )
{
  return FwUpdateReadEntryFromDpp(PathType,FwEntry, Buffer, BufferSize,L"OEM");
}

/**
 * Sample implementation to demonstrate reading a custom firmware entry from
 * update destination/backup path into a buffer. Added to help OEMs integrate
 * custom firmware component to firmware update process.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 * @param FileName   - FileName to read
 *
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateReadEntryFromHW1(
  IN FWENTRY_OPERATION_PATH_TYPE        PathType,
  IN QPAYLOAD_FW_ENTRY                 *FwEntry,
  IN VOID                             **Buffer,
  IN OUT UINTN                         *BufferSize,
  IN CHAR16                            *FileName
  )
{
#if defined(PRODMODE)
  return EFI_UNSUPPORTED;
#else
  EFI_STATUS                          Status      = EFI_SUCCESS;
  UINTN                               BytesToRead = 0;
  UINT32                              FileSize    = 0;

  Status = AllocateAndZero(EfiBootServicesData,FW1_FILE_SIZE,Buffer);
  if(EFI_ERROR(Status))
  {
    DEBUG((EFI_D_WARN,"memory alloc failed.\n"));
    return Status;
  }

  Status = GetFileSize(
    FileName,
    NULL,
    &gEfiPartTypeSystemPartGuid,
    NULL,
    TRUE,
    NULL,
    &FileSize
    );
  if (EFI_ERROR (Status))
  {
    DEBUG ((EFI_D_ERROR, "Failed to get size of the file. Status: %r\n", Status));
    return Status;
  }

  BytesToRead = FileSize;
  DEBUG ((EFI_D_ERROR, "BytesToRead: %d\n", BytesToRead));

  Status = ReadFile (
    FileName,
    NULL,
    &gEfiPartTypeSystemPartGuid,
    NULL,
    TRUE,
    NULL,
    &BytesToRead,
    0,
    *Buffer,
    FW1_FILE_SIZE
    );

  if (EFI_ERROR (Status))
  {
    DEBUG ((EFI_D_ERROR, "Failed to read FW1.bin. Status: %r\n", Status));
  }

  *BufferSize = BytesToRead;

  return Status;
#endif
}

/**
 * Sample implementation to demonstrate reading a custom firmware entry
 * from update destination path into a buffer. Added to help OEMs integrate
 * custom firmware component to firmware update process.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 *
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateReadDestEntryFromHW1(
  IN FWENTRY_OPERATION_PATH_TYPE        PathType,
  IN QPAYLOAD_FW_ENTRY                 *FwEntry,
  IN VOID                             **Buffer,
  IN OUT UINTN                         *BufferSize
  )
{
#if defined(PRODMODE)
  return EFI_UNSUPPORTED;
#else
  return FwUpdateReadEntryFromHW1(
    PathType,
    FwEntry,
    Buffer,
    BufferSize,
    L"FW1.bin"
    );
#endif
}

/**
 * Sample implementation to demonstrate reading a custom firmware entry
 * from update backup path into a buffer. Added to help OEMs integrate
 * custom firmware component to firmware update process.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 *
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateReadBackupEntryFromHW1(
  IN FWENTRY_OPERATION_PATH_TYPE        PathType,
  IN QPAYLOAD_FW_ENTRY                 *FwEntry,
  IN VOID                             **Buffer,
  IN OUT UINTN                         *BufferSize
  )
{
#if defined(PRODMODE)
  return EFI_UNSUPPORTED;
#else
  return FwUpdateReadEntryFromHW1(
    PathType,
    FwEntry,
    Buffer,
    BufferSize,
    L"FW1_BACKUP.bin"
    );
#endif
}

/**
 * Writes a block file to an unformatted partition
 *  from a buffer.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @Param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 *  
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateWriteEntryToPartition(
    IN FWENTRY_OPERATION_PATH_TYPE       PathType,
    IN QPAYLOAD_FW_ENTRY                 *FwEntry,
    IN VOID                              *Buffer,
    IN UINTN                             BufferSize
    )
{
  EFI_STATUS               Status;
  EFI_HANDLE               PartHandle;

  if ((FwEntry == NULL) || (Buffer == NULL)) 
    return EFI_INVALID_PARAMETER;

  PartHandle = FwEntry->Handle[PathType];

  if (PartHandle == NULL)
  {
    return EFI_UNSUPPORTED;
  }

  if(PathType == FWENTRY_OPERATION_PATH_TYPE_SOURCE)
  {
    return EFI_UNSUPPORTED;
  }

  Status = FwUpdatePartitionWrite(PartHandle,
                                  Buffer,
                                  BufferSize);
  HANDLE_ERROR_LABEL(Status,FwUpdatePartitionWrite,FwUpdateWriteEntryToBlockExit);

FwUpdateWriteEntryToBlockExit:

  return Status;
}

/**
 * Writes a fat file to FAT partition from a buffer.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @Param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 *  
 * Note: This function is no more supported as FAT file updates to
 * partitions other than DPP is deprecated to avoid possiblity of
 * file system corruption on power failure
 *
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateWriteEntryToFat(
    IN FWENTRY_OPERATION_PATH_TYPE        PathType,
    IN QPAYLOAD_FW_ENTRY                 *FwEntry,
    IN VOID                              *Buffer,
    IN UINTN                              BufferSize
    )
{
  return EFI_UNSUPPORTED;
}


/**
 * Writes Dpp item to Dpp Qcom or OEM path from a buffer.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @Param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size 
 * @param Type       - QCOM or OEM 
 *  
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateWriteEntryToDpp(
    IN FWENTRY_OPERATION_PATH_TYPE       PathType,
    IN QPAYLOAD_FW_ENTRY                 *FwEntry,
    IN VOID                              *Buffer,
    IN UINTN                             BufferSize,
    IN CHAR16                            *Type
    )
{
  EFI_STATUS                   Status  = EFI_SUCCESS;
  CHAR16                      *DPPName = NULL;

  if ((FwEntry == NULL) || (Buffer == NULL) || (Type == NULL)) 
    return EFI_INVALID_PARAMETER;

  //If PathType is Source we should return unsupported
  //as source is FV and not DPP
  if (PathType == FWENTRY_OPERATION_PATH_TYPE_SOURCE) 
  {
    return EFI_UNSUPPORTED;
  }
  else if (PathType == FWENTRY_OPERATION_PATH_TYPE_BACKUP) 
  {
    return EFI_UNSUPPORTED;
  }
  else if (PathType == FWENTRY_OPERATION_PATH_TYPE_DEST) 
  {
    DPPName = FwEntry->Metadata.UpdatePath.FileName;
  }
  else
  {
    return EFI_INVALID_PARAMETER;
  }

  if(DPPName == NULL)
  {
    return EFI_UNSUPPORTED;
  }

  Status = FwUpdateDppWrite(Type,DPPName,Buffer,BufferSize);
  
  HANDLE_ERROR_LABEL(Status, FwUpdateDppWrite, FwUpdateWriteEntryToDppExit);

FwUpdateWriteEntryToDppExit:

  return Status;
}

/**
 * Writes Dpp item to Dpp Qcom path from a buffer.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @Param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 *  
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateWriteEntryToDppQcom(
    IN FWENTRY_OPERATION_PATH_TYPE       PathType,
    IN QPAYLOAD_FW_ENTRY                 *FwEntry,
    IN VOID                              *Buffer,
    IN UINTN                             BufferSize
    )
{
  return FwUpdateWriteEntryToDpp(PathType,FwEntry,Buffer,BufferSize,L"QCOM");
}

/**
 * Writes Dpp item to Dpp Oem path from a buffer.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @Param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 *  
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateWriteEntryToDppOem(
    IN FWENTRY_OPERATION_PATH_TYPE       PathType,
    IN QPAYLOAD_FW_ENTRY                 *FwEntry,
    IN VOID                              *Buffer,
    IN UINTN                             BufferSize
    )
{
  return FwUpdateWriteEntryToDpp(PathType,FwEntry,Buffer,BufferSize,L"OEM");
}

/**
 * Sample implementation to demonstrate writing a custom firmware entry
 * to update destination/backup path from a buffer. Added to help OEMs integrate
 * custom firmware component to firmware update process.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 * @param FileName   - FileName to write
 *
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateWriteEntryToHW1(
  IN FWENTRY_OPERATION_PATH_TYPE        PathType,
  IN QPAYLOAD_FW_ENTRY                 *FwEntry,
  IN VOID                              *Buffer,
  IN UINTN                              BufferSize,
  IN CHAR16                            *FileName
  )
{
#if defined(PRODMODE)
  return EFI_UNSUPPORTED;
#else
  EFI_STATUS                          Status       = EFI_SUCCESS;
  UINTN                               BytesToWrite = 0;
  UINT32                              FileSize     = 0;

  BytesToWrite = BufferSize;

  Status = GetFileSize(
    FileName,
    NULL,
    &gEfiPartTypeSystemPartGuid,
    NULL,
    TRUE,
    NULL,
    &FileSize
    );

  if (Status == EFI_NOT_FOUND)
  {
    /* If a new file is being written, NOT_FOUND error is expected.*/
    Status = EFI_SUCCESS;
  }
  else if (EFI_ERROR (Status))
  {
    DEBUG ((EFI_D_ERROR, "Failed to get size of the file. Status: %r\n", Status));
    return Status;
  }

  if (FileSize > BytesToWrite)
  {
    BytesToWrite = FileSize;
  }
  DEBUG ((EFI_D_ERROR, "BytesToWrite: %d\n", BytesToWrite));

  Status = WriteFile (
    FileName,
    NULL,
    &gEfiPartTypeSystemPartGuid,
    NULL,
    TRUE,
    NULL,
    &BytesToWrite,
    0,
    (UINT8*)Buffer,
    FW1_FILE_SIZE
    );

  if (EFI_ERROR (Status))
  {
    DEBUG ((EFI_D_ERROR, "Failed to write into HW1. Status: %r\n", Status));
  }

  return Status;
#endif
}

/**
 * Sample implementation to demonstrate writing a custom firmware entry
 * to update destination path from a buffer. Added to help OEMs integrate
 * custom firmware component to firmware update process.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 *
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateWriteDestEntryToHW1(
  IN FWENTRY_OPERATION_PATH_TYPE        PathType,
  IN QPAYLOAD_FW_ENTRY                 *FwEntry,
  IN VOID                              *Buffer,
  IN UINTN                              BufferSize
  )
{
#if defined(PRODMODE)
  return EFI_UNSUPPORTED;
#else
  return FwUpdateWriteEntryToHW1(
    PathType,
    FwEntry,
    Buffer,
    BufferSize,
    L"FW1.bin"
    );
#endif
}

/**
 * Sample implementation to demonstrate writing a custom firmware entry
 * to update backup path from a buffer. Added to help OEMs integrate
 * custom firmware component to firmware update process.
 * 
 * @param PathType   - Source/Dest/BackUp
 * @param FwEntry    - FwEntry
 * @param Buffer     - Buffer to store the file
 * @param BufferSize - Buffer size
 *
 * @return EFI_STATUS 
 */
EFI_STATUS
FwUpdateWriteBackupEntryToHW1(
  IN FWENTRY_OPERATION_PATH_TYPE        PathType,
  IN QPAYLOAD_FW_ENTRY                 *FwEntry,
  IN VOID                              *Buffer,
  IN UINTN                              BufferSize
  )
{
#if defined(PRODMODE)
  return EFI_UNSUPPORTED;
#else
  return FwUpdateWriteEntryToHW1(
    PathType,
    FwEntry,
    Buffer,
    BufferSize,
    L"FW1_Backup.bin"
    );
#endif
}

