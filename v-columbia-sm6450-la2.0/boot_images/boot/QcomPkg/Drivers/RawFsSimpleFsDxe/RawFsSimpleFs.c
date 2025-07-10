/** @file RawFsSimpleFs.c

Implementation for Qualcomm UEFI Simple File System protocol

Copyright (c) 2020 Qualcomm Technologies, Inc. All rights
reserved.

**/

/*=============================================================================
EDIT HISTORY


when         who     what, where, why
--------     ---     -----------------------------------------------------------
2020/05/12   dm      Fixed logging issue
2020/05/06   vb      fix compilation error due to NULL check
2020/02/13   dm      Initial version
=============================================================================*/

#include <Library/UefiBootServicesTableLib.h>
#include <Library/QcomLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BootConfig.h>
#include "RawFsSimpleFs.h"

#define MAX_FILE_NAME_LEN 48
/* folder name length + file name length + 1 (separator) + 1 (terminating NULL char) */
#define MAX_FILE_PATH_LEN  ((2 * MAX_FILE_NAME_LEN) + 2)

static EFI_GUID gSmbiosPartitionTypeGuid = { 0x04A856B8, 0x84C1, 0x4075,{ 0x83, 0x91, 0x9A, 0x99, 0x42, 0x35, 0xE5, 0xF0 } };
static EFI_GUID gDppPartitionGuid = { 0xF97B8793, 0x3ABF, 0x4719,{ 0x89, 0x6B, 0x7C, 0x3E, 0x9B, 0x85, 0xE1, 0x04 } };

extern EFI_GUID gEfiUfsLU4Guid;
extern EFI_GUID gEfiSpiNor0Guid;

static EFI_GUID *gDiskTypeGuid = NULL;

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL customSimpleFileSystemProtocol = {
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION,
    RawFsSimpleFsOpenVolume
};

EFI_FILE_PROTOCOL customFileProtocol = {
    EFI_FILE_PROTOCOL_REVISION,
    RawFsSimpleFsOpen,
    RawFsSimpleFsClose,
    RawFsSimpleFsDelete,
    RawFsSimpleFsRead,
    RawFsSimpleFsWrite,
    RawFsSimpleFsGetPosition,
    RawFsSimpleFsSetPosition,
    RawFsSimpleFsGetInfo,
    RawFsSimpleFsSetInfo,
    RawFsSimpleFsFlush
};

EFI_STATUS
GetSanitizedPath(
    IN CHAR16      *pInputFilePath,
    IN CHAR16      *pPrevFilePath,
    IN OUT CHAR16  *pAbsolutePath,
    IN OUT UINT8   *pslashCount
)
{
    EFI_STATUS status = EFI_SUCCESS;
    UINT8      slashIdx = 0;
    UINT8      tempStrIdx = 0;
    UINT8      inputIdx = 0;
    BOOLEAN    foundString = FALSE;

    // ignore leading slash
    if (pInputFilePath[0] == L'\\')
    {
        pInputFilePath++;
    }

    if (StrStr(pPrevFilePath, L"\\") != NULL)
    {
        *pslashCount = *pslashCount + 1;
    }

    // copy previous location to absolute path
    StrnCpyS(pAbsolutePath, MAX_FILE_PATH_LEN, pPrevFilePath, StrLen(pPrevFilePath)+1);

    // return when filename is empty
    if (StrCmp(pInputFilePath, L"") == 0 || StrCmp(pInputFilePath, L"\\") == 0 
        || pInputFilePath == NULL)
    {
        DEBUG((EFI_D_INFO, "[RawFsSimpleFsDxe]GetSanitizedPath:Filename is empty.\n"));
        return status;
    }

    // return error when '..' is attempted on root directory
    if ((StrCmp(pInputFilePath, L"..") == 0 || StrCmp(pInputFilePath, L"..\\") == 0)
        && (StrLen(pAbsolutePath) == 0))
    {
        DEBUG((EFI_D_ERROR, "[RawFsSimpleFsDxe]GetSanitizedPath:Invalid attempt to get parent directory for the root directory.\n"));
        return EFI_NOT_FOUND;
    }

    // loop through the input filepath to construct the absolute path
    UINTN inputLen = StrLen(pInputFilePath);
    for (inputIdx = 0; inputIdx < inputLen; inputIdx++)
    {
        if (pInputFilePath[inputIdx] == L'.')
        {
            if (pInputFilePath[inputIdx+1] != L'.')
            {
                continue;
            }
            else
            {
                // '..' is found; get parent directory of current location
                UINT8 absPathSlashIdx = 0;
                for (UINT16 charIdx = 0; charIdx < StrLen(pAbsolutePath); charIdx++)
                {
                    if (pAbsolutePath[charIdx] == L'\\')
                    {
                        absPathSlashIdx = charIdx;
                    }
                }
                if (absPathSlashIdx != 0)
                {
                    pAbsolutePath[absPathSlashIdx] = L'\0';
                    *pslashCount = *pslashCount ? (*pslashCount - 1):0;
                } 
                else
                {
                    DEBUG((EFI_D_ERROR, "[RawFsSimpleFsDxe]GetSanitizedPath:Invalid attempt to get parent directory for the root directory.\n"));
                    return EFI_NOT_FOUND;
                }
            }
        }
        else if (pInputFilePath[inputIdx] == L'\\')
        {
            // copy string before slash to absolute path
            slashIdx = inputIdx;
            if (foundString == TRUE)
            {
                if (StrLen(pAbsolutePath) != 0)
                {
                    StrnCatS(pAbsolutePath, MAX_FILE_PATH_LEN, L"\\", StrLen(L"\\")+1);
                    *pslashCount = *pslashCount + 1;
                }
                StrnCatS(pAbsolutePath,
                            MAX_FILE_PATH_LEN, 
                            &pInputFilePath[tempStrIdx],
                            (slashIdx-tempStrIdx));
                StrnCatS(pAbsolutePath, MAX_FILE_PATH_LEN, L"\0", StrLen(L"\0"));
                foundString = FALSE;
            }
        }
	    else if (foundString == FALSE)
        {
            // valid string found
            tempStrIdx = inputIdx;
            foundString = TRUE;
        }
    }

    // copy any remaining input string to absolute path
    if (foundString == TRUE)
    {
        if (StrLen(pAbsolutePath) != 0)
        {
            StrnCatS(pAbsolutePath, MAX_FILE_PATH_LEN, L"\\", StrLen(L"\\")+1);
            *pslashCount = *pslashCount + 1;
        }
        StrnCatS(pAbsolutePath, 
                    MAX_FILE_PATH_LEN,
                    &pInputFilePath[tempStrIdx],
                    (inputIdx-tempStrIdx));
        StrnCatS(pAbsolutePath, MAX_FILE_PATH_LEN, L"\0", StrLen(L"\0"));
    }

    // replace trailing slash
    UINT8 tempLen = StrLen(pAbsolutePath);
    if (tempLen != 0 && pAbsolutePath[tempLen-1] == L'\\')
    {
        pAbsolutePath[tempLen-1] = L'\0';
        *pslashCount = *pslashCount ? (*pslashCount - 1):0;
    }

    DEBUG((EFI_D_INFO, "[RawFsSimpleFsDxe]GetSanitizedPath:slashCount: %d\n", *pslashCount));

    //RawFS doesn't support multiple directory structure.
    //Check if multiple slash(/) found in filepath.
    if (*pslashCount >= 2)
    {
        DEBUG((EFI_D_ERROR, "[RawFsSimpleFsDxe]GetSanitizedPath:File path has more than one set of backslash! Will bail out.\n"));
        return EFI_NOT_FOUND;
    }

    DEBUG((EFI_D_INFO, "[RawFsSimpleFsDxe]GetSanitizedPath:pAbsolutePath: %s\n", pAbsolutePath));
    return status;
}

EFI_STATUS
GetRawFSProtocol(
    IN OUT EFI_RAW_FILE_SYSTEM_PROTOCOL    **pRawFSProtocol
)
{
    EFI_STATUS status = EFI_SUCCESS;

    // get raw file system protocol handle
    status = gBS->LocateProtocol(
      &gEfiRawFileSystemProtocolGuid,
      NULL,
      (VOID **)pRawFSProtocol);

    return status;
}

EFI_STATUS 
AllocateNextFileInfo(
    CHAR16            *pNextFileinDir,
    EFI_FILE_INFO    **pNextFileInfo
)
{
    EFI_STATUS status = EFI_SUCCESS;
    UINTN      nextFileInfoSize = 0;

    if (*pNextFileInfo)
    {
        FreePool(*pNextFileInfo);
        *pNextFileInfo = NULL;
    }

    if (pNextFileinDir != NULL)
    {
        nextFileInfoSize = sizeof(EFI_FILE_INFO) + StrSize(pNextFileinDir) - sizeof(CHAR16);
        *pNextFileInfo = AllocateZeroPool(nextFileInfoSize);
        if (*pNextFileInfo == NULL)
        {
          DEBUG((EFI_D_ERROR, "[RawFsSimpleFsDxe]AllocateNextFileInfo:AllocateZeroPool error.\n"));
          return EFI_OUT_OF_RESOURCES;
        }

        CopyMem((*pNextFileInfo)->FileName, pNextFileinDir, StrSize(pNextFileinDir));
        (*pNextFileInfo)->Size = nextFileInfoSize;

        //Free memory allocated to hold the file name
        FreePool(pNextFileinDir);
        pNextFileinDir = NULL;
    }

    DEBUG((EFI_D_INFO, "[RawFsSimpleFsDxe]AllocateNextFileInfo:pNextFileInfo %x.\n", (*pNextFileInfo)));
    if (*pNextFileInfo)
    {
        DEBUG((EFI_D_INFO, "[RawFsSimpleFsDxe]AllocateNextFileInfo:FileName %s.\n", (*pNextFileInfo)->FileName));
    }
    return status;
}


EFI_STATUS
EFIAPI RawFsSimpleFsOpenVolume(
    IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL    *This,
    OUT EFI_FILE_PROTOCOL                **Root
)
{
    EFI_STATUS                  status = EFI_SUCCESS;
    SIMPLE_FILESYSTEM_INSTANCE *pInstance = NULL;
    SIMPLE_FILESYSTEM_FILE     *pFileInstance = NULL;

    pInstance = SIMPLE_FILESYSTEM_INSTANCE_FROM_THIS(This);
    DEBUG((EFI_D_INFO, "RawFsSimpleFsOpenVolume:Instance->PartitionGuid: %x.\n", pInstance->PartitionGuid));

    // Create file instance
    pFileInstance = AllocateZeroPool (sizeof (SIMPLE_FILESYSTEM_FILE));
    if (pFileInstance == NULL)
    {
      DEBUG((EFI_D_ERROR, "RawFsSimpleFsOpenVolume:AllocateZeroPool error.\n"));
      return EFI_OUT_OF_RESOURCES;
    }

    pInstance->File = pFileInstance;
    pFileInstance->FSInstance = pInstance;
    pFileInstance->Signature = SIMPLE_FILESYSTEM_FILE_SIGNATURE;
    pFileInstance->FilePosition = 0;
    CopyMem(&pFileInstance->FileProtocol, &customFileProtocol, sizeof(customFileProtocol));

    pFileInstance->FileInfo.Size      = sizeof (EFI_FILE_INFO);
    pFileInstance->FileInfo.FileSize = 0;
    pFileInstance->FileInfo.PhysicalSize = pFileInstance->FileInfo.FileSize;
    pFileInstance->FileInfo.Attribute = EFI_FILE_DIRECTORY;
    ZeroMem(pFileInstance->FileInfo.FileName, sizeof(pFileInstance->FileInfo.FileName));
    pFileInstance->FileInfo.FileName[0] = L'\0';
    pFileInstance->NextFileInfo = NULL;

    *Root = &pFileInstance->FileProtocol;
    DEBUG((EFI_D_INFO, "RawFsSimpleFsOpenVolume:*Root: %x.\n", *Root));

    return status;
}


EFI_STATUS
EFIAPI RawFsSimpleFsOpen (
    IN EFI_FILE_PROTOCOL    *This,
    OUT EFI_FILE_PROTOCOL  **NewHandle,
    IN CHAR16               *FileName,
    IN UINT64                OpenMode,
    IN UINT64                Attributes
)
{
    EFI_STATUS                        status = EFI_SUCCESS;
    SIMPLE_FILESYSTEM_FILE           *pFileInstance = NULL;
    SIMPLE_FILESYSTEM_FILE           *pNewFileInstance = NULL;
    UINTN                             fileInstanceSize = 0;
    EFI_RAW_FILE_SYSTEM_PROTOCOL     *pRawFSProtocol = NULL;
    EFI_GUID                         *partitionGuid = NULL;
    UINTN                             fileSize = 0;
    CHAR16                            pAbsolutePath[MAX_FILE_PATH_LEN] = {0};
    UINT8                             slashCount = 0;
    UINT8                             isDirectory = FALSE;
    CHAR16                           *pNextFileinDir = NULL;
    EFI_FILE_INFO                    *pNextFileInfo = NULL;

    status = SimpleFileSystemValidateInputs(NewHandle, FileName, OpenMode, Attributes);
    if (EFI_ERROR(status))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsOpen:Input validation failed.Status: %r\n", status));
        goto RawFsSimpleFsOpenExit;
    }

    //Hack to avoid the logging when searching for bootloader image in RawFS partitions.
    if (StrStr(FileName, L"EFI\\BOOT\\BOOT") != NULL)
    {
        return EFI_NOT_FOUND;
    }

    if (StrLen(FileName) >= MAX_FILE_PATH_LEN)
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsOpen:Filename is too long.\n"));
        status = EFI_INVALID_PARAMETER;
        goto RawFsSimpleFsOpenExit;
    }

    pFileInstance = SIMPLE_FILESYSTEM_FILE_FROM_THIS(This);

    status = GetSanitizedPath(FileName, &pFileInstance->FileInfo.FileName[0], &pAbsolutePath[0], &slashCount);
    if (EFI_ERROR(status))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsOpen:Failed to get absolute filepath.Status: %r\n", status));
        goto RawFsSimpleFsOpenExit;
    }

    DEBUG((EFI_D_INFO, "RawFsSimpleFsOpen:pAbsolutePath: %s.\n", pAbsolutePath));

    // Set all fields to default value when we attempt to open root volume
    if (StrLen(&pAbsolutePath[0]) == 0)
    {
        pNewFileInstance = AllocateZeroPool (sizeof (SIMPLE_FILESYSTEM_FILE));
        if (pNewFileInstance == NULL)
        {
            DEBUG((EFI_D_ERROR, "RawFsSimpleFsOpen:AllocateZeroPool error.\n"));
            status = EFI_OUT_OF_RESOURCES;
            goto RawFsSimpleFsOpenExit;
        }
        pNewFileInstance->FSInstance  = pFileInstance->FSInstance;
        pNewFileInstance->Signature = SIMPLE_FILESYSTEM_FILE_SIGNATURE;
        pNewFileInstance->FilePosition = 0;
        pNewFileInstance->FileOpenMode = OpenMode;
        pNewFileInstance->FileInfo.Size = sizeof(EFI_FILE_INFO);
        pNewFileInstance->FileInfo.Attribute = EFI_FILE_DIRECTORY;
        CopyMem (&pNewFileInstance->FileProtocol, &customFileProtocol, sizeof (customFileProtocol));
        *NewHandle = &pNewFileInstance->FileProtocol;
        DEBUG((EFI_D_INFO, "RawFsSimpleFsOpen:*NewHandle: %x.\n", *NewHandle));
        return status;
    }


    // Check if file exists on RawFS partition when open mode is read
    if ((OpenMode & EFI_FILE_MODE_READ) == EFI_FILE_MODE_READ)
    {
        status = GetRawFSProtocol(&pRawFSProtocol);
        if (EFI_ERROR(status))
        {
            DEBUG((EFI_D_ERROR, "RawFsSimpleFsOpen:Failed to locate RawFileSystemDxe Protocol.Status: %r\n", status));
            goto RawFsSimpleFsOpenExit;
        }
        partitionGuid = &pFileInstance->FSInstance->PartitionGuid;
        status = pRawFSProtocol->FileRead(pRawFSProtocol, 
                                        pAbsolutePath,
                                        NULL,
                                        &fileSize,
                                        NULL,
                                        partitionGuid,
                                        gDiskTypeGuid);
        if (EFI_ERROR(status))
        {
            // Multiple directories are not allowed in RawFS.
            // So, filepath would generally be in foldername\filename format,
            // If slash is found, it is considered to be a file and no directory check needed.
            if (slashCount == 0)
            {
                fileSize = 0;
                DEBUG((EFI_D_WARN, "RawFsSimpleFsOpen:Attempting to check for directory.\n"));
                status = pRawFSProtocol->GetNextFileNameInDirectory(pRawFSProtocol,
                                           pAbsolutePath,
                                           NULL,
                                           partitionGuid,
                                           NULL,
                                           &fileSize,
                                           &pNextFileinDir,
                                           gDiskTypeGuid);
                if (!EFI_ERROR(status))
                {
                    isDirectory = TRUE;
                    DEBUG((EFI_D_INFO, "RawFsSimpleFsOpen:pNextFileinDir: %s.\n", pNextFileinDir));
                    status = AllocateNextFileInfo(pNextFileinDir, &pNextFileInfo);
                    if (EFI_ERROR(status))
                    {
                        DEBUG((EFI_D_ERROR, "RawFsSimpleFsOpen:Memory allocation failed for nextFileInfo.\n"));
                        goto RawFsSimpleFsOpenExit;
                    }
                }
            }

            if (EFI_ERROR(status) && ((OpenMode & EFI_FILE_MODE_CREATE) != EFI_FILE_MODE_CREATE))
            {
                DEBUG((EFI_D_ERROR, "RawFsSimpleFsOpen:Failed to locate file/directory in partition.\n"));
                goto RawFsSimpleFsOpenExit;
            }
            status = EFI_SUCCESS;
        }
    }

    // Initialize fileinstance data structure when file already exists or it is a file create request.
    fileInstanceSize = sizeof(SIMPLE_FILESYSTEM_FILE) + StrSize(pAbsolutePath) - sizeof(CHAR16);
    pNewFileInstance = AllocateZeroPool(fileInstanceSize);
    if (pNewFileInstance == NULL)
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsOpen:AllocateZeroPool error.\n"));
        status = EFI_OUT_OF_RESOURCES;
        goto RawFsSimpleFsOpenExit;
    }
    pNewFileInstance->Signature = SIMPLE_FILESYSTEM_FILE_SIGNATURE;
    pNewFileInstance->FilePosition = 0;
    pNewFileInstance->FileOpenMode = OpenMode;
    pNewFileInstance->FSInstance = pFileInstance->FSInstance;
    pNewFileInstance->NextFileInfo = NULL;
    if ((OpenMode & EFI_FILE_MODE_CREATE) == EFI_FILE_MODE_CREATE)
    {
        pNewFileInstance->FileInfo.Attribute = Attributes;
    }
    if (isDirectory)
    {
        pNewFileInstance->FileInfo.Attribute |= EFI_FILE_DIRECTORY;
        pNewFileInstance->NextFileInfo = pNextFileInfo;
        DEBUG((EFI_D_INFO, "[RawFsSimpleFsOpen]RawFsSimpleFsOpen:pNewFileInstance->NextFileInfo: %x.\n", pNewFileInstance->NextFileInfo));
    }
    CopyMem(&pNewFileInstance->FileProtocol, &customFileProtocol, sizeof (customFileProtocol));
    CopyMem(&pNewFileInstance->FileInfo.FileName[0], pAbsolutePath, StrSize(pAbsolutePath));

    DEBUG((EFI_D_INFO, "RawFsSimpleFsOpen:pNewFileInstance->FileInfo.FileName: %s.\n", pNewFileInstance->FileInfo.FileName));
    pNewFileInstance->FileInfo.Size = sizeof(EFI_FILE_INFO) + StrSize(pAbsolutePath) - sizeof (CHAR16);

    *NewHandle = &pNewFileInstance->FileProtocol;
    DEBUG((EFI_D_INFO, "RawFsSimpleFsOpen:*NewHandle: %x.\n", *NewHandle));

RawFsSimpleFsOpenExit:
    return status;
}


EFI_STATUS
EFIAPI RawFsSimpleFsClose(
    IN EFI_FILE_PROTOCOL  *This
)
{
    EFI_STATUS              status = EFI_SUCCESS;
    SIMPLE_FILESYSTEM_FILE *pFileInstance = NULL;

    pFileInstance = SIMPLE_FILESYSTEM_FILE_FROM_THIS(This);
    DEBUG((EFI_D_INFO, "RawFsSimpleFsClose:NextFileInfo: %x.\n", pFileInstance->NextFileInfo));

    if (pFileInstance->NextFileInfo)
    {
        DEBUG((EFI_D_INFO, "RawFsSimpleFsClose:NextFileInfo->Size: %d.\n", pFileInstance->NextFileInfo->Size));
        DEBUG((EFI_D_INFO, "RawFsSimpleFsClose:NextFileInfo->FileName: %s.\n", pFileInstance->NextFileInfo->FileName));

        FreePool(pFileInstance->NextFileInfo);
        pFileInstance->NextFileInfo = NULL;

        DEBUG((EFI_D_INFO, "RawFsSimpleFsClose:Freed NextFileInfo.\n"));
    }
    FreePool(pFileInstance);
    return status;
}


EFI_STATUS
EFIAPI RawFsSimpleFsDelete(
    IN EFI_FILE_PROTOCOL *This
)
{
    EFI_STATUS                        status = EFI_SUCCESS;
    EFI_RAW_FILE_SYSTEM_PROTOCOL     *pRawFSProtocol = NULL;
    EFI_GUID                         *partitionGuid = NULL;
    CHAR16                           *pFilePath = NULL;
    SIMPLE_FILESYSTEM_FILE           *pFileInstance = NULL;

    pFileInstance = SIMPLE_FILESYSTEM_FILE_FROM_THIS(This);
    if (NULL == pFileInstance->FileInfo.FileName)
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsDelete:FileName is NULL.\n"));
        return EFI_INVALID_PARAMETER;
    }

    status = GetRawFSProtocol(&pRawFSProtocol);
    if (status != EFI_SUCCESS)
    {
      DEBUG((EFI_D_ERROR, "RawFsSimpleFsDelete:Failed to locate RawFileSystemDxe Protocol.Status: %r\n",status));
      return status;
    }

    partitionGuid = &pFileInstance->FSInstance->PartitionGuid;
    pFilePath = pFileInstance->FileInfo.FileName;

    // delete file
    status = pRawFSProtocol->FileDelete(pRawFSProtocol, 
                                pFilePath,
                                NULL,
                                partitionGuid,
                                gDiskTypeGuid);
    
    // If Raw FS protocol could not delete file, print an error message and return
    if(EFI_ERROR(status))
    {
         DEBUG((EFI_D_ERROR, "RawFsSimpleFsDelete:Deleting file %s failed.Status: %r\n", pFilePath, status));
         if (status == EFI_VOLUME_CORRUPTED)
         {
              DEBUG((EFI_D_INFO, "RawFsSimpleFsDelete:Partition header is corrupted!\n"));
         }
         else
         {
              DEBUG((EFI_D_INFO, "RawFsSimpleFsDelete:Failed to delete block data.\n"));
         }
    }
    else
    {
        RawFsSimpleFsClose(This);
    }

    return status;
}


EFI_STATUS
EFIAPI RawFsSimpleFsRead(
    IN     EFI_FILE_PROTOCOL      *This,
    IN OUT UINTN                  *BufferSize,
    OUT VOID                      *Buffer
)
{
    EFI_STATUS                        status = EFI_SUCCESS;
    EFI_RAW_FILE_SYSTEM_PROTOCOL     *pRawFSProtocol = NULL;
    EFI_GUID                         *partitionGuid = NULL;
    CHAR16                           *pFilePath = NULL;
    UINTN                             fileSize = 0;
    VOID                             *fileBuffer = NULL;
    SIMPLE_FILESYSTEM_FILE           *pFileInstance = NULL;
    EFI_FILE_INFO                    *pInputFileInfo = NULL;
    CHAR16                           *pNextFileinDir = NULL;

    if ((This == NULL) || (BufferSize == NULL) || ((Buffer == NULL) && (*BufferSize > 0)))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsRead:Input validation failed.\n"));
        status = EFI_INVALID_PARAMETER;
        goto RawFsSimpleFsReadExit;
    }

    pFileInstance = SIMPLE_FILESYSTEM_FILE_FROM_THIS(This);
    if (NULL == pFileInstance->FileInfo.FileName)
    {
        DEBUG((EFI_D_WARN, "RawFsSimpleFsRead:Filename is NULL.\n"));
        status = EFI_INVALID_PARAMETER;
        goto RawFsSimpleFsReadExit;
    }

    status = GetRawFSProtocol(&pRawFSProtocol);
    if (EFI_ERROR(status))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsRead:Failed to locate RawFileSystemDxe Protocol.Status: %r\n", status));
        goto RawFsSimpleFsReadExit;
    }

    partitionGuid = &pFileInstance->FSInstance->PartitionGuid;
    pFilePath = pFileInstance->FileInfo.FileName;

    // Input file is a directory
    if ((pFileInstance->FileInfo.Attribute & EFI_FILE_DIRECTORY) == EFI_FILE_DIRECTORY)
    {
        pInputFileInfo = pFileInstance->NextFileInfo;
        if (pInputFileInfo != NULL)
        {
            status = pRawFSProtocol->GetNextFileNameInDirectory(pRawFSProtocol,
                                       pFilePath,
                                       NULL,
                                       partitionGuid,
                                       pInputFileInfo->FileName,
                                       &pInputFileInfo->FileSize,
                                       &pNextFileinDir,
                                       gDiskTypeGuid);
            // success
            if (!EFI_ERROR(status))
            {
                // attempt was made to read from deleted file
                if (pInputFileInfo->FileSize == 0)
                {
                    DEBUG((EFI_D_ERROR, "RawFsSimpleFsRead:Attempt to read from deleted file.\n"));
                    status = EFI_DEVICE_ERROR;
                    goto RawFsSimpleFsReadExit;
                }

                if (*BufferSize < pInputFileInfo->Size)
                {
                    *BufferSize = pInputFileInfo->Size;
                    DEBUG((EFI_D_INFO, "RawFsSimpleFsRead:Buffer too small.\n"));
                    status = EFI_BUFFER_TOO_SMALL;
                    goto RawFsSimpleFsReadExit;
                }

                CopyMem(Buffer, pInputFileInfo, pInputFileInfo->Size);
                *BufferSize = pInputFileInfo->Size;
                status = AllocateNextFileInfo(pNextFileinDir, &pFileInstance->NextFileInfo);
                if (EFI_ERROR(status))
                {
                    DEBUG((EFI_D_ERROR, "RawFsSimpleFsRead:Memory allocation failed for nextFileInfo.\n"));
                    goto RawFsSimpleFsReadExit;
                }
                DEBUG((EFI_D_INFO, "RawFsSimpleFsRead:GetNextFileNameInDirectory done.\n"));
            }
            else
            {
                DEBUG((EFI_D_ERROR, "RawFsSimpleFsRead:GetNextFileNameInDirectory failed. Status: %r.\n", status));
            }
            goto RawFsSimpleFsReadExit;
       }
       else
       {
           // Directory read. All entries have been read, so return a zero-size buffer.
           *BufferSize = 0;
           DEBUG((EFI_D_WARN, "RawFsSimpleFsRead:No more entries found in directory.\n"));
           status = EFI_SUCCESS;
           goto RawFsSimpleFsReadExit;
       }
    }

    if (NULL != Buffer)
    {
        fileSize = *BufferSize;
        fileBuffer = AllocateZeroPool(fileSize);
    }

    // read the file
    status = pRawFSProtocol->FileRead(pRawFSProtocol,
                                     pFilePath,
                                     fileBuffer,
                                     &fileSize,
                                     NULL,
                                     partitionGuid,
                                     gDiskTypeGuid);
    if (EFI_ERROR(status))
    {
      DEBUG((EFI_D_ERROR, "RawFsSimpleFsRead:Reading file %s failed.Status: %r\n", pFilePath, status));
      if (status == EFI_VOLUME_CORRUPTED)
      {
        DEBUG((EFI_D_INFO, "RawFsSimpleFsRead:Partition header is corrupted!\n"));
      }
      // set file size to 0 so that we do not attempt to read the file
      fileSize = 0;
      goto RawFsSimpleFsReadExit;
    }

    pFileInstance->FileInfo.FileSize = fileSize;
    pFileInstance->FileInfo.PhysicalSize = fileSize;

    if (*BufferSize < pFileInstance->FileInfo.FileSize || NULL == Buffer)
    {
        DEBUG((EFI_D_INFO, "RawFsSimpleFsRead:Buffer too small.\n"));
        status = EFI_BUFFER_TOO_SMALL;
        *BufferSize = fileSize;
        goto RawFsSimpleFsReadExit;
    }
    else if (pFileInstance->FilePosition >= pFileInstance->FileInfo.FileSize)
    {
        *BufferSize = 0;
        if (pFileInstance->FilePosition > pFileInstance->FileInfo.FileSize)
        {
            DEBUG((EFI_D_ERROR, "RawFsSimpleFsRead:Current file position beyond end of the file.\n"));
            status = EFI_DEVICE_ERROR;
            goto RawFsSimpleFsReadExit;
        }
    }
    else
    {
        if (NULL != fileBuffer)
        {
            *BufferSize = fileSize - pFileInstance->FilePosition;
            CopyMem(Buffer, fileBuffer + pFileInstance->FilePosition, *BufferSize);
            pFileInstance->FilePosition += (*BufferSize);
        }
    }
    DEBUG((EFI_D_INFO, "RawFsSimpleFsRead:pFileInstance->FilePosition: %d.\n", pFileInstance->FilePosition));

RawFsSimpleFsReadExit:
    if (fileBuffer != NULL)
    {
        FreePool(fileBuffer);
        fileBuffer = NULL;
    }
    return status;
}


EFI_STATUS
EFIAPI RawFsSimpleFsWrite(
    IN     EFI_FILE_PROTOCOL    *This,
    IN OUT UINTN                *BufferSize,
    IN     VOID                 *Buffer
)
{
    EFI_STATUS                        status = EFI_SUCCESS;
    EFI_RAW_FILE_SYSTEM_PROTOCOL     *pRawFSProtocol = NULL;
    EFI_GUID                         *partitionGuid = NULL;
    CHAR16                           *pFilePath = NULL;
    SIMPLE_FILESYSTEM_FILE           *pFileInstance = NULL;
    UINTN                             fileSize = 0;
    UINT8                            *pFileBuffer = NULL;
    UINTN                             bytesToWrite = 0;

    if ((This == NULL) || (BufferSize == NULL) || (Buffer == NULL))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsWrite:Input validation failed.\n"));
        status = EFI_INVALID_PARAMETER;
        goto RawFsSimpleFsWriteExit;
    }

    pFileInstance = SIMPLE_FILESYSTEM_FILE_FROM_THIS(This);
    if (NULL == pFileInstance->FileInfo.FileName)
    {
        DEBUG((EFI_D_WARN, "RawFsSimpleFsWrite:Filename is NULL.\n"));
        status = EFI_INVALID_PARAMETER;
        goto RawFsSimpleFsWriteExit;
    }

    // we cannot write to a read-only file
    if (((pFileInstance->FileInfo.Attribute & EFI_FILE_READ_ONLY) == EFI_FILE_READ_ONLY) ||
        ((pFileInstance->FileOpenMode & EFI_FILE_MODE_WRITE) != EFI_FILE_MODE_WRITE))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsWrite:Attempt to write to a read-only file.\n"));
        status = EFI_ACCESS_DENIED;
        goto RawFsSimpleFsWriteExit;
    }

    // write to open directories not supported
    if ((pFileInstance->FileInfo.Attribute & EFI_FILE_DIRECTORY) == EFI_FILE_DIRECTORY)
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsWrite:Write to open directories not supported.\n"));
        status = EFI_UNSUPPORTED;
        goto RawFsSimpleFsWriteExit;
    }

    status = GetRawFSProtocol(&pRawFSProtocol);
    if (EFI_ERROR(status))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsWrite:Failed to locate RawFileSystemDxe Protocol.Status: %r\n", status));
        goto RawFsSimpleFsWriteExit;
    }

    partitionGuid = &pFileInstance->FSInstance->PartitionGuid;
    pFilePath = pFileInstance->FileInfo.FileName;

    //read existing file data when file position is not zero
    if (pFileInstance->FilePosition != 0)
    {
        // get file size
        status = pRawFSProtocol->FileRead(pRawFSProtocol, pFilePath, NULL, &fileSize,
                                          NULL, partitionGuid, gDiskTypeGuid);
        if (EFI_ERROR(status))
        {
            DEBUG((EFI_D_ERROR, "RawFsSimpleFsWrite:Reading file %s failed.Status: %r\n", pFilePath, status));
            if (status == EFI_VOLUME_CORRUPTED)
            {
              DEBUG((EFI_D_INFO, "RawFsSimpleFsWrite:Partition header is corrupted!\n"));
            }
            else
            {
              DEBUG((EFI_D_INFO,"RawFsSimpleFsWrite:Failed to write block data with RawFSProtocol.\n"));
            }
            // set file size to 0 so that we do not attempt to read the file
            fileSize = 0;
            goto RawFsSimpleFsWriteExit;
        }
        else
        {
            pFileBuffer = AllocateZeroPool(fileSize);
            if (NULL == pFileBuffer)
            {
                DEBUG((EFI_D_ERROR,"RawFsSimpleFsWrite:AllocateZeroPool error.\n"));
                status = EFI_OUT_OF_RESOURCES;
                goto RawFsSimpleFsWriteExit;
            }

            status = pRawFSProtocol->FileRead(pRawFSProtocol, pFilePath, pFileBuffer, &fileSize,
                                            NULL, partitionGuid, gDiskTypeGuid);
            if (EFI_ERROR(status))
            {
                DEBUG((EFI_D_ERROR, "RawFsSimpleFsWrite:Failed to read existing data from partition.\n"));
                goto RawFsSimpleFsWriteExit;
            } 
            else
            {
                // on success, seek to current file position and copy input buffer to pfilebuffer
                // write the updated buffer to RawFS
                bytesToWrite = pFileInstance->FilePosition + *BufferSize;
                if ( bytesToWrite > fileSize)
                {
                    pFileBuffer = ReallocatePool(fileSize, bytesToWrite, pFileBuffer);
                    if (NULL == pFileBuffer)
                    {
                        DEBUG((EFI_D_ERROR,"RawFsSimpleFsWrite:AllocateZeroPool error.\n"));
                        status = EFI_OUT_OF_RESOURCES;
                        goto RawFsSimpleFsWriteExit;
                    }
                }
                CopyMem(pFileBuffer+pFileInstance->FilePosition, Buffer, *BufferSize);
            }
        }
    }
    else
    {
        pFileBuffer = Buffer;
        bytesToWrite = *BufferSize;
    }

    // write file
    status = pRawFSProtocol->FileWrite(pRawFSProtocol, pFileBuffer, bytesToWrite, pFilePath, NULL, 
                             partitionGuid, gDiskTypeGuid);
    // If Raw FS protocol could not write file, print an error message and return
    if(EFI_ERROR(status))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsWrite:Writing file %s failed.Status: %r\n", pFilePath, status));
        if (status == EFI_VOLUME_CORRUPTED)
        {
          DEBUG((EFI_D_INFO, "RawFsSimpleFsWrite:Partition header is corrupted!\n"));
        }
        else
        {
          DEBUG((EFI_D_INFO, "RawFsSimpleFsWrite:Failed to write block data with RawFSProtocol.\n"));
        }
        goto RawFsSimpleFsWriteExit;
    }
    else
    {
        pFileInstance->FilePosition += (*BufferSize);
        pFileInstance->FileInfo.FileSize = pFileInstance->FilePosition;
        pFileInstance->FileInfo.PhysicalSize = pFileInstance->FilePosition;
    }
    DEBUG((EFI_D_INFO, "RawFsSimpleFsWrite:pFileInstance->FilePosition: %d.\n", pFileInstance->FilePosition));

RawFsSimpleFsWriteExit:
    if (pFileBuffer && (pFileBuffer != Buffer))
    {
        FreePool(pFileBuffer);
        pFileBuffer = NULL;
    }
    return status;
}


EFI_STATUS
EFIAPI RawFsSimpleFsFlush(
    IN EFI_FILE_PROTOCOL  *This
)
{
    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI RawFsSimpleFsGetInfo(
    IN     EFI_FILE_PROTOCOL    *This,
    IN     EFI_GUID             *InformationType,
    IN OUT UINTN                *BufferSize,
    OUT    VOID                 *Buffer
)
{
    EFI_STATUS                        status = EFI_SUCCESS;
    SIMPLE_FILESYSTEM_FILE           *pFileInstance = NULL;
    EFI_FILE_INFO                    *fileInfo = NULL;;
    EFI_RAW_FILE_SYSTEM_PROTOCOL     *pRawFSProtocol = NULL;
    EFI_GUID                         *partitionGuid = NULL;
    CHAR16                           *pFilePath = NULL;
    UINTN                             fileSize = 0;
    SIMPLE_FILESYSTEM_INSTANCE       *pInstance = NULL;

    if ((This == NULL)                         ||
        (InformationType == NULL)              ||
        (BufferSize == NULL)                   ||
        ((Buffer == NULL) && (*BufferSize > 0)))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsGetInfo:Input validation failed.\n"));
        status = EFI_INVALID_PARAMETER;
        goto RawFsSimpleFsGetInfoExit;
    }

    pFileInstance = SIMPLE_FILESYSTEM_FILE_FROM_THIS(This);
    if (CompareGuid (InformationType, &gEfiFileInfoGuid))
    {
        if (NULL == pFileInstance->FileInfo.FileName)
        {
            DEBUG((EFI_D_WARN, "RawFsSimpleFsGetInfo:Filename is NULL.\n"));
            status = EFI_INVALID_PARAMETER;
            goto RawFsSimpleFsGetInfoExit;
        }

        status = GetRawFSProtocol(&pRawFSProtocol);
        if (EFI_ERROR(status))
        {
            DEBUG((EFI_D_ERROR, "RawFsSimpleFsGetInfo:Failed to locate RawFileSystemDxe Protocol.Status: %r\n", status));
            goto RawFsSimpleFsGetInfoExit;
        }

        partitionGuid = &pFileInstance->FSInstance->PartitionGuid;
        pFilePath = pFileInstance->FileInfo.FileName;

        // get the file size
        status = pRawFSProtocol->FileRead(pRawFSProtocol,
                                         pFilePath,
                                         NULL,
                                         &fileSize,
                                         NULL,
                                         partitionGuid,
                                         gDiskTypeGuid);
        if (EFI_ERROR(status))
        {
            DEBUG((EFI_D_ERROR, "RawFsSimpleFsGetInfo:Reading file %s failed.Status: %r\n", pFilePath, status));
            if (status == EFI_VOLUME_CORRUPTED)
            {
              DEBUG((EFI_D_INFO, "RawFsSimpleFsGetInfo:Partition header is corrupted!\n"));
            }
            goto RawFsSimpleFsGetInfoExit;
        }

        pFileInstance->FileInfo.FileSize = fileSize;
        pFileInstance->FileInfo.PhysicalSize = fileSize;

        // Return file info
        UINTN size = (UINTN)pFileInstance->FileInfo.Size;
        if (*BufferSize < size)
        {
            DEBUG((EFI_D_INFO, "RawFsSimpleFsGetInfo:Buffer too small.\n"));
            status = EFI_BUFFER_TOO_SMALL;
            *BufferSize = size;
            goto RawFsSimpleFsGetInfoExit;
        }

        fileInfo = (EFI_FILE_INFO *) Buffer;
        CopyMem (fileInfo, &pFileInstance->FileInfo, size);
        *BufferSize = size;
    }
    else
    {
        pInstance = pFileInstance->FSInstance;
        CHAR16 *PartitionName = &pInstance->PartitionName[0];
        status = SimpleFileSystemGetInfo(This,
                                        InformationType,
                                        BufferSize,
                                        Buffer,
                                        PartitionName);
        if (status == EFI_BUFFER_TOO_SMALL)
        {
            // This error need not be logged.
            // Expected to return the required buffer size, 
            // if buffer is not large enough (null/non-null).
            goto RawFsSimpleFsGetInfoExit;
        }

        if (EFI_ERROR(status))
        {
            DEBUG((EFI_D_ERROR, "RawFsSimpleFsGetInfo:Status: %r\n", status));
            goto RawFsSimpleFsGetInfoExit;
        }
    }

RawFsSimpleFsGetInfoExit:
    return status;
}


EFI_STATUS
EFIAPI RawFsSimpleFsSetInfo(
    IN EFI_FILE_PROTOCOL        *This,
    IN EFI_GUID                 *InformationType,
    IN UINTN                     BufferSize,
    IN VOID                     *Buffer
)
{
    return SimpleFileSystemSetInfo(This, 
                                   InformationType,
                                   BufferSize,
                                   Buffer);
}


EFI_STATUS
EFIAPI RawFsSimpleFsGetPosition(
    IN EFI_FILE_PROTOCOL    *This,
    OUT UINT64              *Position
)
{
    SIMPLE_FILESYSTEM_FILE     *pFileInstance = NULL;

    if ((This == NULL) || (Position == NULL))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsGetPosition:Input validation failed.\n"));
        return EFI_INVALID_PARAMETER;
    }

    pFileInstance = SIMPLE_FILESYSTEM_FILE_FROM_THIS(This);

    // request is not valid on open directories
    if ((pFileInstance->FileInfo.Attribute & EFI_FILE_DIRECTORY) == EFI_FILE_DIRECTORY)
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsGetPosition:Invalid request on directory.\n"));
        return EFI_UNSUPPORTED;
    }
    else
    {
        *Position = pFileInstance->FilePosition;
        return EFI_SUCCESS;
    }
}


EFI_STATUS
EFIAPI RawFsSimpleFsSetPosition(
    IN EFI_FILE_PROTOCOL       *This,
    IN UINT64                   Position
)
{
    EFI_STATUS                        status = EFI_SUCCESS;
    SIMPLE_FILESYSTEM_FILE           *pFileInstance = NULL;
    EFI_RAW_FILE_SYSTEM_PROTOCOL     *pRawFSProtocol = NULL;
    EFI_GUID                         *partitionGuid = NULL;
    UINTN                             fileSize = 0;
    CHAR16                           *pNextFileinDir = NULL;

    if (This == NULL)
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsSetPosition:Input validation failed.\n"));
        status = EFI_INVALID_PARAMETER;
        goto RawFsSimpleFsSetPositionExit;
    }

    pFileInstance = SIMPLE_FILESYSTEM_FILE_FROM_THIS(This);

    //seek request for nonzero is not valid on open directories
    if ((pFileInstance->FileInfo.Attribute & EFI_FILE_DIRECTORY) == EFI_FILE_DIRECTORY)
    {
        if (Position != 0)
        {
            DEBUG((EFI_D_ERROR, "RawFsSimpleFsSetPosition:Seek request for nonzero not valid on directories.\n"));
            status = EFI_UNSUPPORTED;
            goto RawFsSimpleFsSetPositionExit;
        }

        // Reset directory position to first entry when position = 0.
        status = GetRawFSProtocol(&pRawFSProtocol);
        if (EFI_ERROR(status))
        {
            DEBUG((EFI_D_ERROR, "RawFsSimpleFsSetPosition:Failed to locate RawFileSystemDxe Protocol.Status: %r\n", status));
            goto RawFsSimpleFsSetPositionExit;
        }

        partitionGuid = &pFileInstance->FSInstance->PartitionGuid;
        if (pFileInstance->NextFileInfo != NULL)
        {
            status = pRawFSProtocol->GetNextFileNameInDirectory(pRawFSProtocol,
                                        pFileInstance->FileInfo.FileName,
                                        NULL,
                                        partitionGuid,
                                        NULL,
                                        &fileSize,
                                        &pNextFileinDir,
                                        gDiskTypeGuid);
            if (!EFI_ERROR(status))
            {
                status = AllocateNextFileInfo(pNextFileinDir, &pFileInstance->NextFileInfo);
                if (EFI_ERROR(status))
                {
                    DEBUG((EFI_D_ERROR, "RawFsSimpleFsSetPosition:Memory allocation failed for nextFileInfo.\n"));
                    goto RawFsSimpleFsSetPositionExit;
                }
            }
            else
            {
                DEBUG((EFI_D_ERROR, "RawFsSimpleFsSetPosition:GetNextFileNameInDirectory failed. Status: %r\n", status));
            }
        }
        goto RawFsSimpleFsSetPositionExit;
    }
    else if (Position == 0xFFFFFFFFFFFFFFFF)
    {
        pFileInstance->FilePosition = pFileInstance->FileInfo.FileSize;
    }
    else
    {
        pFileInstance->FilePosition = Position;
    }

RawFsSimpleFsSetPositionExit:
    return status;
}


static EFI_STATUS
InstallSimpleFSonPartHandle()
{
    EFI_STATUS                    status = EFI_SUCCESS;
    EFI_HANDLE                   *handleBuffer = NULL;
    UINTN                         numHandles = 0;
    UINTN                         handleCounter = 0;
    EFI_GUID                     *tempPartTypeGuid = NULL;
    EFI_PARTITION_ENTRY          *tempPartEntry = NULL;
    SIMPLE_FILESYSTEM_INSTANCE   *pInstance = NULL;
    CHAR16                       *tempPartitionName  = NULL;
    UINTN                         foundSmbiosHandle = 0;
    UINTN                         foundDppHandle = 0;

    status = gBS->LocateHandleBuffer(ByProtocol,
        &gEfiPartitionTypeGuid,
        NULL,
        &numHandles,
        &handleBuffer);
    if (EFI_ERROR(status))
    {
        DEBUG((EFI_D_WARN, "[%a] LocateHandleBuffer failed. Returning: %r.\n", __FUNCTION__, status));
        goto InstallSimpleFSExit;
    }

    for (handleCounter = 0; handleCounter < numHandles; handleCounter++)
    {
        status = gBS->HandleProtocol(handleBuffer[handleCounter],
                                    &gEfiPartitionTypeGuid,
                                    (VOID**)&tempPartTypeGuid);
        if (EFI_ERROR(status))
        {
            continue;
        }

        status = gBS->HandleProtocol(handleBuffer[handleCounter],
                                   &gEfiPartitionRecordGuid,
                                   (VOID **)&tempPartEntry);
        if(EFI_ERROR(status))
        {
          continue;
        }
        tempPartitionName = tempPartEntry->PartitionName;

        if (CompareGuid(tempPartTypeGuid, &gSmbiosPartitionTypeGuid))
        {
            foundSmbiosHandle = 1;
        }
        else if (CompareGuid(tempPartTypeGuid, &gDppPartitionGuid))
        {
            foundDppHandle = 1;
        }
        else
        {
            continue;
        }

        // Create an instance
        pInstance = AllocateZeroPool (sizeof (SIMPLE_FILESYSTEM_INSTANCE) + StrSize(tempPartitionName));
        ASSERT (pInstance != NULL);

        pInstance->File = NULL;
        pInstance->Signature = SIMPLE_FILESYSTEM_INSTANCE_SIGNATURE;
        CopyMem (&pInstance->PartitionName[0], tempPartitionName, StrSize(tempPartitionName));
        CopyMem (&pInstance->PartitionGuid, tempPartTypeGuid, sizeof(EFI_GUID));
        CopyMem (&pInstance->SimpleFs,
                    &customSimpleFileSystemProtocol, 
                    sizeof(customSimpleFileSystemProtocol));

        // Install protocol
        status = gBS->InstallProtocolInterface(&handleBuffer[handleCounter],
            &gEfiSimpleFileSystemProtocolGuid,
            EFI_NATIVE_INTERFACE,
            &pInstance->SimpleFs);

        if (EFI_ERROR(status))
        {
            DEBUG((EFI_D_WARN, "InstallSimpleFSonPartHandle:PartitionGuid %x - status: %r.\n",*tempPartTypeGuid, status));
            goto InstallSimpleFSExit;
        }
    }

    if (foundSmbiosHandle && foundDppHandle)
    {
        status = EFI_SUCCESS;
    }
    else
    {
        status = EFI_NOT_FOUND;
        DEBUG((EFI_D_INFO, "InstallSimpleFSonPartHandle:Failed. Status: %r.\n", status));
    }

InstallSimpleFSExit:
    if (handleBuffer != NULL)
    {
        gBS->FreePool(handleBuffer);
        handleBuffer = NULL;
    }

    return status;
}


/**
RawFsSimpleFsDriverEntryPoint()

Initializes SimpleFS protocol on partition(SMBIOS,DPP,etc.) handles.

@param[in]  ImageHandle   The firmware allocated handle for the EFI image.
@param[in]  SystemTable   A pointer to the EFI System Table.

@return
EFI_SUCCESS               Simple FS protocol initialized successfully.
EFI_UNSUPPORTED           Simple FS protocol not supported.
EFI_XXXXXX                Failure occured. (Refer to UEFI spec for details)

**/
EFI_STATUS
RawFsSimpleFsDriverEntryPoint(
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    EFI_STATUS                        status = EFI_SUCCESS;
    EFI_RAW_FILE_SYSTEM_PROTOCOL     *pRawFSProtocol = NULL;

    status = GetRawFSProtocol(&pRawFSProtocol);
    if (EFI_ERROR(status))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsDriverEntryPoint:Failed to locate RawFileSystemDxe Protocol.\n"));
        goto Exit;
    }

    DEBUG((EFI_D_INFO, "RawFsSimpleFsDriverEntryPoint:pRawFSProtocol->Revision: %x.\n", pRawFSProtocol->Revision>>16));

    if ((pRawFSProtocol->Revision>>16) == 1)
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsDriverEntryPoint:Not supported on RawFS Revision1.\n"));
        status = EFI_UNSUPPORTED;
        goto Exit;
    }

    status = InstallSimpleFSonPartHandle();

    if (EFI_ERROR(status))
    {
        DEBUG((EFI_D_ERROR, "RawFsSimpleFsDriverEntryPoint:Failed. Status: %r.\n", status));
        goto Exit;
    }

    // get disk type
    if (boot_from_ufs())
    {
        gDiskTypeGuid = &gEfiUfsLU4Guid;
    }
    else if (boot_from_nvme())
    {
        gDiskTypeGuid = &gEfiSpiNor0Guid;
    }
    else if (boot_from_emmc())
    {
        gDiskTypeGuid = &gEfiEmmcGppPartition1Guid;
    }

Exit:
    return status;
}
