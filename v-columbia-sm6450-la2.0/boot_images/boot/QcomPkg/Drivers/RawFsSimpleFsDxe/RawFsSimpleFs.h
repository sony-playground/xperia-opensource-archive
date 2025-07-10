/**
@file  RawFsSimpleFs.h
@brief Simple File System related declarations.
*/
/*=============================================================================
Copyright (c) 2020 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when         who     what, where, why
--------     ---     -----------------------------------------------------------
2020/02/13   dm      Initial version
=============================================================================*/

#ifndef _RAWFS_SIMPLEFS_FUNCTIONS_H_
#define _RAWFS_SIMPLEFS_FUNCTIONS_H_

#include <Protocol/EFIRawFileSystem.h>
#include <Guid/FileInfo.h>
#include "RawFsSimpleFsUtil.h"

#define SIMPLE_FILESYSTEM_INSTANCE_SIGNATURE    SIGNATURE_32 ('s', 'f', 's', 'm')
#define SIMPLE_FILESYSTEM_FILE_SIGNATURE        SIGNATURE_32 ('s', 'f', 'i', 'l')

#define SIMPLE_FILESYSTEM_INSTANCE_FROM_THIS(this)  \
    CR (this, SIMPLE_FILESYSTEM_INSTANCE, SimpleFs, SIMPLE_FILESYSTEM_INSTANCE_SIGNATURE)

#define SIMPLE_FILESYSTEM_FILE_FROM_THIS(this)  \
    CR (this, SIMPLE_FILESYSTEM_FILE, FileProtocol, SIMPLE_FILESYSTEM_FILE_SIGNATURE)


typedef struct _SIMPLE_FILESYSTEM_INSTANCE   SIMPLE_FILESYSTEM_INSTANCE;
typedef struct _SIMPLE_FILESYSTEM_FILE       SIMPLE_FILESYSTEM_FILE;

struct _SIMPLE_FILESYSTEM_INSTANCE {
    UINT32                            Signature;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   SimpleFs;
    EFI_GUID                          PartitionGuid;
    SIMPLE_FILESYSTEM_FILE           *File;
    CHAR16                            PartitionName[1];
};

struct _SIMPLE_FILESYSTEM_FILE {
    UINT32                            Signature;
    EFI_FILE_PROTOCOL                 FileProtocol;
    UINT64                            FileOpenMode;
    UINT64                            FilePosition;
    SIMPLE_FILESYSTEM_INSTANCE       *FSInstance;
    EFI_FILE_INFO                    *NextFileInfo;
    EFI_FILE_INFO                     FileInfo;
};


/**
  Open the root directory on a volume.

  @param  This     A pointer to the volume to open the root directory.
  @param  RootFile A pointer to the location to return the opened file handle for the
                   root directory.

  @retval EFI_SUCCESS          The device was opened.
  @retval EFI_UNSUPPORTED      This volume does not support the requested file system type.
  @retval EFI_NO_MEDIA         The device has no medium.
  @retval EFI_DEVICE_ERROR     The device reported an error.
  @retval EFI_VOLUME_CORRUPTED The file system structures are corrupted.
  @retval EFI_ACCESS_DENIED    The service denied access to the file.
  @retval EFI_OUT_OF_RESOURCES The volume was not opened due to lack of resources.
  @retval EFI_MEDIA_CHANGED    The device has a different medium in it or the medium is no
                               longer supported. Any existing file handles for this volume are
                               no longer valid. To access the files on the new medium, the
                               volume must be reopened with OpenVolume().

**/
EFI_STATUS
EFIAPI RawFsSimpleFsOpenVolume(
    IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL    *This,
    OUT EFI_FILE_PROTOCOL                **Root
);


/**
  Opens a new file relative to the source file's location.

  @param  This       A pointer to the EFI_FILE_PROTOCOL instance that is the file
                     handle to the source location. This would typically be an open
                     handle to a directory.
  @param  NewHandle  A pointer to the location to return the opened handle for the new
                     file.
  @param  FileName   The Null-terminated string of the name of the file to be opened.
                     The file name may contain the following path modifiers: "\", ".",
                     and "..".
  @param  OpenMode   The mode to open the file. The only valid combinations that the
                     file may be opened with are: Read, Read/Write, or Create/Read/Write.
  @param  Attributes Only valid for EFI_FILE_MODE_CREATE, in which case these are the
                     attribute bits for the newly created file.

  @retval EFI_SUCCESS              The file was opened.
  @retval EFI_NOT_FOUND            The specified file could not be found on the device.
  @retval EFI_NO_MEDIA             The device has no medium.
  @retval EFI_MEDIA_CHANGED        The device has a different medium in it or the medium is no
                                   longer supported.
  @retval EFI_DEVICE_ERROR         The device reported an error.
  @retval EFI_VOLUME_CORRUPTED     The file system structures are corrupted.
  @retval EFI_WRITE_PROTECTED      An attempt was made to create a file, or open a file for write
                                   when the media is write-protected.
  @retval EFI_ACCESS_DENIED        The service denied access to the file.
  @retval EFI_OUT_OF_RESOURCES     Not enough resources were available to open the file.
  @retval EFI_VOLUME_FULL          The volume is full.
  @retval EFI_INVALID_PARAMETER    Input validation failed.

**/
EFI_STATUS
EFIAPI RawFsSimpleFsOpen (
    IN     EFI_FILE_PROTOCOL    *This,
    OUT EFI_FILE_PROTOCOL    **NewHandle,
    IN     CHAR16               *FileName,
    IN     UINT64               OpenMode,
    IN     UINT64               Attributes
);


/**
  Closes a specified file handle.

  @param  This          A pointer to the EFI_FILE_PROTOCOL instance that is the file
                        handle to close.

  @retval EFI_SUCCESS   The file was closed.

**/
EFI_STATUS
EFIAPI RawFsSimpleFsClose(
    IN EFI_FILE_PROTOCOL  *This
);


/**
  Close and delete the file handle.

  @param  This                     A pointer to the EFI_FILE_PROTOCOL instance that is the
                                   handle to the file to delete.

  @retval EFI_SUCCESS              The file was closed and deleted, and the handle was closed.
  @retval EFI_INVALID_PARAMETER    Input validation failed.
  @retval Other EFI errors

**/
EFI_STATUS
EFIAPI RawFsSimpleFsDelete(
    IN EFI_FILE_PROTOCOL *This
);


/**
  Reads data from a file.

  @param  This       A pointer to the EFI_FILE_PROTOCOL instance that is the file
                     handle to read data from.
  @param  BufferSize On input, the size of the Buffer. On output, the amount of data
                     returned in Buffer. In both cases, the size is measured in bytes.
  @param  Buffer     The buffer into which the data is read.

  @retval EFI_SUCCESS          Data was read.
  @retval EFI_NO_MEDIA         The device has no medium.
  @retval EFI_DEVICE_ERROR     The device reported an error.
  @retval EFI_DEVICE_ERROR     An attempt was made to read from a deleted file.
  @retval EFI_DEVICE_ERROR     On entry, the current file position is beyond the end of the file.
  @retval EFI_VOLUME_CORRUPTED The file system structures are corrupted.
  @retval EFI_BUFFER_TOO_SMALL The BufferSize is too small to read the current directory
                               entry. BufferSize has been updated with the size
                               needed to complete the request.
  @retval EFI_INVALID_PARAMETER Input validation failed.

**/
EFI_STATUS
EFIAPI RawFsSimpleFsRead(
    IN     EFI_FILE_PROTOCOL      *This,
    IN OUT UINTN                  *BufferSize,
    OUT VOID                      *Buffer
);


/**
  Writes data to a file.

  @param  This       A pointer to the EFI_FILE_PROTOCOL instance that is the file
                     handle to write data to.
  @param  BufferSize On input, the size of the Buffer. On output, the amount of data
                     actually written. In both cases, the size is measured in bytes.
  @param  Buffer     The buffer of data to write.

  @retval EFI_SUCCESS          Data was written.
  @retval EFI_UNSUPPORTED      Writes to open directory files are not supported.
  @retval EFI_NO_MEDIA         The device has no medium.
  @retval EFI_DEVICE_ERROR     The device reported an error.
  @retval EFI_DEVICE_ERROR     An attempt was made to write to a deleted file.
  @retval EFI_VOLUME_CORRUPTED The file system structures are corrupted.
  @retval EFI_WRITE_PROTECTED  The file or medium is write-protected.
  @retval EFI_ACCESS_DENIED    The file was opened read only.
  @retval EFI_VOLUME_FULL      The volume is full.
  @retval EFI_INVALID_PARAMETER Input validation failed.
  @retval EFI_OUT_OF_RESOURCES  Not enough resources were available to write the file.

**/
EFI_STATUS
EFIAPI RawFsSimpleFsWrite(
    IN     EFI_FILE_PROTOCOL    *This,
    IN OUT UINTN                *BufferSize,
    IN     VOID                 *Buffer
);

/**
  Dummy implementation of flush as this would be handled in RawFS protocol on read/write/delete file request.

  @param  This A pointer to the EFI_FILE_PROTOCOL instance that is the file
               handle to flush.

  @retval EFI_SUCCESS          The data was flushed.

**/

EFI_STATUS
EFIAPI RawFsSimpleFsFlush(
    IN EFI_FILE_PROTOCOL  *This
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

  @retval EFI_SUCCESS           The information was returned.
  @retval EFI_UNSUPPORTED       The InformationType is not known.
  @retval EFI_NO_MEDIA          The device has no medium.
  @retval EFI_DEVICE_ERROR      The device reported an error.
  @retval EFI_VOLUME_CORRUPTED  The file system structures are corrupted.
  @retval EFI_BUFFER_TOO_SMALL  The BufferSize is too small to read the current directory entry.
                                BufferSize has been updated with the size needed to complete
                                the request.
  @retval EFI_INVALID_PARAMETER Input validation failed.

**/
EFI_STATUS
EFIAPI RawFsSimpleFsGetInfo(
    IN     EFI_FILE_PROTOCOL    *This,
    IN     EFI_GUID             *InformationType,
    IN OUT UINTN                *BufferSize,
    OUT VOID                    *Buffer
);


/**
  Sets information about a file.

  @param  This            A pointer to the EFI_FILE_PROTOCOL instance that is the file
                          handle the information is for.
  @param  InformationType The type identifier for the information being set.
  @param  BufferSize      The size, in bytes, of Buffer.
  @param  Buffer          A pointer to the data buffer to write. The buffer's type is
                          indicated by InformationType.

  @retval EFI_UNSUPPORTED      The InformationType is not known.
  @retval EFI_WRITE_PROTECTED  InformationType is EFI_FILE_INFO_ID and the media is
                               read-only.
  @retval EFI_WRITE_PROTECTED  InformationType is EFI_FILE_PROTOCOL_SYSTEM_INFO_ID
                               and the media is read only.
  @retval EFI_WRITE_PROTECTED  InformationType is EFI_FILE_SYSTEM_VOLUME_LABEL_ID
                               and the media is read-only.

**/
EFI_STATUS
EFIAPI RawFsSimpleFsSetInfo(
    IN EFI_FILE_PROTOCOL        *This,
    IN EFI_GUID                 *InformationType,
    IN UINTN                     BufferSize,
    IN VOID                     *Buffer
);


/**
  Returns a file's current position.

  @param  This            A pointer to the EFI_FILE_PROTOCOL instance that is the file
                          handle to get the current position on.
  @param  Position        The address to return the file's current position value.

  @retval EFI_SUCCESS      The position was returned.
  @retval EFI_UNSUPPORTED  The request is not valid on open directories.
  @retval EFI_INVALID_PARAMETER Input validation failed.

**/
EFI_STATUS
EFIAPI RawFsSimpleFsGetPosition(
    IN     EFI_FILE_PROTOCOL    *This,
    OUT UINT64                  *Position
);

/**
  Sets a file's current position.

  @param  This            A pointer to the EFI_FILE_PROTOCOL instance that is the
                          file handle to set the requested position on.
  @param  Position        The byte position from the start of the file to set.

  @retval EFI_SUCCESS      The position was set.
  @retval EFI_UNSUPPORTED  The seek request for nonzero is not valid on open
                           directories.
  @retval EFI_DEVICE_ERROR An attempt was made to set the position of a deleted file.
  @retval EFI_INVALID_PARAMETER Input validation failed.

**/
EFI_STATUS
EFIAPI RawFsSimpleFsSetPosition(
    IN EFI_FILE_PROTOCOL        *This,
    IN UINT64                    Position
);


/**
  Initializes SimpleFS protocol on partition(SMBIOS,DPP,etc.) handles.
  
  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.
  
  @return  EFI_SUCCESS         Simple FS protocol initialized successfully.
  @return  EFI_UNSUPPORTED     Simple FS protocol not supported.
  @return  EFI_XXXXXX          Failure occured. (Refer to UEFI spec for details)

**/
EFI_STATUS
RawFsSimpleFsDriverEntryPoint(
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
);

#endif
