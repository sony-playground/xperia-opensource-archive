/** @file
  This driver uses the EFI_FIRMWARE_VOLUME2_PROTOCOL to expose files in firmware
  volumes via the the EFI_SIMPLE_FILESYSTEM_PROTOCOL and EFI_FILE_PROTOCOL.

  It will expose a single directory, containing one file for each file in the firmware
  volume. If a file has a UI section, its contents will be used as a filename.
  Otherwise, a string representation of the GUID will be used.
  Files of an executable type (That is PEIM, DRIVER, COMBINED_PEIM_DRIVER and APPLICATION)
  will have ".efi" added to their filename.

  Its primary intended use is to be able to start EFI applications embedded in FVs
  from the UEFI shell. It is entirely read-only.

Copyright (c) 2020, Qualcomm Technologies, Inc.  All Rights Reserved.
Portions Copyright (c) 2014, ARM Limited. All rights reserved.
Portions Copyright (c) 2014 - 2015, Intel Corporation. All rights reserved.<BR>

This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#ifndef _RAWFS_SIMPLEFS_UTIL_FUNCTIONS_H_
#define _RAWFS_SIMPLEFS_UTIL_FUNCTIONS_H_

#include <Guid/FileSystemInfo.h>
#include <Guid/FileSystemVolumeLabelInfo.h>
#include <Protocol/SimpleFileSystem.h>


/**
  Input validation before opening a new file relative to the source file's location.

  @param  NewHandle  A pointer to the location to return the opened handle for the new
                     file.
  @param  FileName   The Null-terminated string of the name of the file to be opened.
                     The file name may contain the following path modifiers: "\", ".",
                     and "..".
  @param  OpenMode   The mode to open the file. The only valid combinations that the
                     file may be opened with are: Read, Read/Write, or Create/Read/Write.
  @param  Attributes Only valid for EFI_FILE_MODE_CREATE, in which case these are the
                     attribute bits for the newly created file.

  @retval EFI_SUCCESS                Input validation passed.
  @retval EFI_INVALID_PARAMETER      Input validation failed.

**/
EFI_STATUS
SimpleFileSystemValidateInputs (
    IN EFI_FILE_PROTOCOL   **NewHandle,
    IN CHAR16               *FileName,
    IN UINT64                OpenMode,
    IN UINT64                Attributes
);


/**
  Sets information about a file.

  @param  This            A pointer to the EFI_FILE_PROTOCOL instance that is the file
                          handle the information is for.
  @param  InformationType The type identifier for the information being set.
  @param  BufferSize      The size, in bytes, of Buffer.
  @param  Buffer          A pointer to the data buffer to write. The buffer's type is
                          indicated by InformationType.

  @retval EFI_SUCCESS          The information was set.
  @retval EFI_UNSUPPORTED      The InformationType is not known.
  @retval EFI_NO_MEDIA         The device has no medium.
  @retval EFI_DEVICE_ERROR     The device reported an error.
  @retval EFI_VOLUME_CORRUPTED The file system structures are corrupted.
  @retval EFI_WRITE_PROTECTED  InformationType is EFI_FILE_INFO_ID and the media is
                               read-only.
  @retval EFI_WRITE_PROTECTED  InformationType is EFI_FILE_PROTOCOL_SYSTEM_INFO_ID
                               and the media is read only.
  @retval EFI_WRITE_PROTECTED  InformationType is EFI_FILE_SYSTEM_VOLUME_LABEL_ID
                               and the media is read-only.
  @retval EFI_ACCESS_DENIED    An attempt is made to change the name of a file to a
                               file that is already present.
  @retval EFI_ACCESS_DENIED    An attempt is being made to change the EFI_FILE_DIRECTORY
                               Attribute.
  @retval EFI_ACCESS_DENIED    An attempt is being made to change the size of a directory.
  @retval EFI_ACCESS_DENIED    InformationType is EFI_FILE_INFO_ID and the file was opened
                               read-only and an attempt is being made to modify a field
                               other than Attribute.
  @retval EFI_VOLUME_FULL      The volume is full.
  @retval EFI_BAD_BUFFER_SIZE  BufferSize is smaller than the size of the type indicated
                               by InformationType.

**/
EFI_STATUS
EFIAPI
SimpleFileSystemSetInfo (
    IN EFI_FILE_PROTOCOL        *This,
    IN EFI_GUID                 *InformationType,
    IN UINTN                     BufferSize,
    IN VOID                     *Buffer
);


/**
  Returns information about a file.

  @param  This            A pointer to the EFI_FILE_PROTOCOL instance that is the file
                          handle the requested information is for.
  @param  InformationType The type identifier for the information being requested.
  @param  BufferSize      On input, the size of Buffer. On output, the amount of data
                          returned in Buffer. In both cases, the size is measured in bytes.
  @param  Buffer          A pointer to the data buffer to return. The buffer's type is
                          indicated by InformationType.

  @retval EFI_SUCCESS          The information was returned.
  @retval EFI_UNSUPPORTED      The InformationType is not known.
  @retval EFI_NO_MEDIA         The device has no medium.
  @retval EFI_DEVICE_ERROR     The device reported an error.
  @retval EFI_VOLUME_CORRUPTED The file system structures are corrupted.
  @retval EFI_BUFFER_TOO_SMALL The BufferSize is too small to read the current directory entry.
                               BufferSize has been updated with the size needed to complete
                               the request.
**/
EFI_STATUS
SimpleFileSystemGetInfo(
    IN     EFI_FILE_PROTOCOL        *This,
    IN     EFI_GUID                 *InformationType,
    IN OUT UINTN                    *BufferSize,
    OUT    VOID                     *Buffer,
    IN     CHAR16                   *pPartitionName
);

#endif
