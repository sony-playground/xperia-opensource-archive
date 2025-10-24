/**
@file  EfiRawFileSystem.h
@brief Raw File System UEFI Protocol definitions.
*/
/*=============================================================================
Copyright (c) 2018-2020 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
02/13/20   dm      Added new API to find file in directory
05/31/18   prema   Fixed issues related to read and write files to raw file system
03/12/18   ltg     Initial revision

=============================================================================*/
#ifndef __EFI_RAW_FILE_SYSTEM_H_
#define __EFI_RAW_FILE_SYSTEM_H_

/*===========================================================================
INCLUDE FILES
===========================================================================*/
/** @defgroup EFI_RAW_FILE_SYSTEM_PROTOCOL  EFI_RAW_FILE_SYSTEM_PROTOCOL
 *  @ingroup PERIPHERALS 
 */
 /** @defgroup  EFI_RAW_FILE_SYSTEM_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_RAW_FILE_SYSTEM_PROTOCOL 
 */ 
 /** @defgroup  EFI_RAW_FILE_SYSTEM_PROTOCOL_apis APIs
 *  @ingroup EFI_RAW_FILE_SYSTEM_PROTOCOL 
 */ 

/** @defgroup  EFI_RAW_FILE_SYSTEM_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_RAW_FILE_SYSTEM_PROTOCOL 
 */ 
/*===========================================================================
MACRO DECLARATIONS
===========================================================================*/
/** @ingroup EFI_RAW_FILE_SYSTEM_PROTOCOL_data
Protocol version. */
#define EFI_RAW_FILE_SYSTEM_PROTOCOL_REVISION 0x0000000000020000

/* Protocol GUID definition */
#define EFI_RAW_FILE_SYSTEM_PROTOCOL_GUID \
        { 0xc3b885f3, 0xa0e4, 0x4314,{ 0x91, 0x83, 0x8a, 0x1a, 0x93, 0x80, 0x85, 0x2f } };

/*===========================================================================
EXTERNAL VARIABLES
===========================================================================*/
/** @cond */
/* External reference to the RawFileSystem Protocol GUID. */
extern EFI_GUID gEfiRawFileSystemProtocolGuid;

/*===========================================================================
TYPE DEFINITIONS
===========================================================================*/
/* Protocol declaration */
typedef struct _EFI_RAW_FILE_SYSTEM_PROTOCOL EFI_RAW_FILE_SYSTEM_PROTOCOL;
/** @endcond */


/*===========================================================================
FUNCTION DEFINITIONS
===========================================================================*/
/* EFI_FILEWRITE */
/** @ingroup EFI_RAW_FILE_SYSTEM_PROTOCOL_apis
@par Summary
Writes new file in raw file system or overwrites an existing file in the raw file system.

@param[in]  This                            Pointer to the EFI_RAW_FILE_SYSTEM_PROTOCOL instance.
@param[in]  pInputFileBuffer                Pointer to buffer containint input file contents
@param[in]  InputFileBufferSize             Size of input file
@param[in]  pFSFilePath                     Path ([Folder]\[File]) in the file system which the file will be saved as. [Folder] parameter is required.
@param[in]  PartitionName                   Signature (CHAR16*) of the partition (DPP, SMBIOS, GENERIC)
@param[in]  PartitionGuid                   Pointer to GUID of the partition (DPP, SMBIOS, etc.)
@param[in]  RootDeviceTypeGuid              Pointer to GUID of the disk (LUN4, SPINOR, etc.)

@par Description
Function that writes a file to the file system.

@return
EFI_SUCCESS           -- Function completed successfully. \n
EFI_INVALID_PARAMETER -- Parameter is invalid. \n
EFI_XXXX              -- Other errors\n
*/
typedef
EFI_STATUS
(EFIAPI *EFI_FILEWRITE)(
    IN EFI_RAW_FILE_SYSTEM_PROTOCOL     *This,
    IN UINT8                            *pInputFileBuffer,
    IN UINTN                             InputFileBufferSize,
    IN CHAR16                           *pFSFilePath,
    IN CHAR16                           *PartitionName,
    IN EFI_GUID                         *PartitionGuid,
    IN EFI_GUID                         *RootDeviceTypeGuid
    );

/* EFI_FILEDELETE */
/** @ingroup EFI_RAW_FILE_SYSTEM_PROTOCOL_apis
@par Summary
Deletes file from raw file system.

@param[in]  This                            Pointer to the EFI_RAW_FILE_SYSTEM_PROTOCOL instance.
@param[in]  pFSFilePath                     Path to the file to delete in the FS
@param[in]  PartitionName                   Signature (CHAR16*) of the partition (DPP, SMBIOS, GENERIC)
@param[in]  PartitionGuid                   Pointer to GUID of the partition (DPP, SMBIOS, etc.)
@param[in]  RootDeviceTypeGuid              Pointer to GUID of the disk (LUN4, SPINOR, etc.)

@par Description
Function that deletes a file from the file system.

@return
EFI_SUCCESS           -- Function completed successfully. \n
EFI_INVALID_PARAMETER -- Parameter is invalid. \n
EFI_XXXX              -- Other errors\n
*/
typedef
EFI_STATUS
(EFIAPI *EFI_FILEDELETE)(
    IN EFI_RAW_FILE_SYSTEM_PROTOCOL     *This,
    IN CHAR16                           *pFSFilePath,
    IN CHAR16                           *PartitionName,
    IN EFI_GUID                         *PartitionGuid,
    IN EFI_GUID                         *RootDeviceTypeGuid
    );

/* EFI_FORMATRAWFILESYSTEM */
/** @ingroup EFI_RAW_FILE_SYSTEM_PROTOCOL_apis
@par Summary
Formats raw file system with specified header.

@param[in]  This                            Pointer to the EFI_RAW_FILE_SYSTEM_PROTOCOL instance.
@param[in]  PartitionName                   Signature (CHAR16*) of the partition (DPP, SMBIOS, GENERIC)
@param[in]  PartitionGuid                   Pointer to GUID of the partition (DPP, SMBIOS, etc.)
@param[in]  RootDeviceTypeGuid              Pointer to GUID of the disk (LUN4, SPINOR, etc.)

@par Description
Function that deletes a file from the file system.

@return
EFI_SUCCESS           -- Function completed successfully. \n
EFI_INVALID_PARAMETER -- Parameter is invalid. \n
EFI_XXXX              -- Other errors\n
*/
typedef
EFI_STATUS
(EFIAPI *EFI_FORMATRAWFILESYSTEM)(
    IN EFI_RAW_FILE_SYSTEM_PROTOCOL     *This,
    IN UINTN                             fsBlockSize,
    IN UINTN                             numCombinedHeaderBlocks,
    IN CHAR16                           *PartitionName,
    IN EFI_GUID                         *PartitionGuid,
    IN EFI_GUID                         *RootDeviceTypeGuid
    );


/* EFI_FILEREAD */
/** @ingroup EFI_RAW_FILE_SYSTEM_PROTOCOL_apis
@par Summary
Reads file from raw file system.
If the pOutBuffer parameter is NULL, the function will return the size of the file in the FileSize parameter.
If the pOutBuffer parameter is not NULL, the function will populate it with the first FileSize bytes from the file.
If FileSize is larger than the actual size of the file, the function will copy the entire file into the buffer and return the size of the file in the FileSize parameter.

@param[in]  This                            Pointer to the EFI_RAW_FILE_SYSTEM_PROTOCOL instance.
@param[in]  pReadFilePath                   Path to file to read
@param[in]  pOutBuffer                      Pointer to buffer to place file contents
@param[in]  FileSize                        Pointer to size of the file
@param[in]  PartitionName                   Signature (CHAR16*) of the partition (DPP, SMBIOS, GENERIC)
@param[in]  PartitionGuid                   Pointer to GUID of the partition (DPP, SMBIOS, etc.)
@param[in]  RootDeviceTypeGuid              Pointer to GUID of the disk (LUN4, SPINOR, etc.)

@par Description
Function that reads a file from the file system.

@return
EFI_SUCCESS           -- Function completed successfully. \n
EFI_INVALID_PARAMETER -- Parameter is invalid. \n
EFI_XXXX              -- Other errors\n
*/
typedef
EFI_STATUS
(EFIAPI *EFI_FILEREAD)(
    IN EFI_RAW_FILE_SYSTEM_PROTOCOL     *This,
    IN CHAR16                           *pReadFilePath,
    IN OUT UINT8                        *pOutBuffer,
    IN OUT UINTN                        *FileSize,
    IN CHAR16                           *PartitionName,
    IN EFI_GUID                         *PartitionGuid,
    IN EFI_GUID                         *RootDeviceTypeGuid
    );

/* EFI_VERIFYSIGNATURE */
/** @ingroup EFI_RAW_FILE_SYSTEM_PROTOCOL_apis
@par Summary
Checks that the file system signature is valid.

@param[in]  This                            Pointer to the EFI_RAW_FILE_SYSTEM_PROTOCOL instance.
@param[in]  PartitionName                   Signature (CHAR16*) of the partition (DPP, SMBIOS, GENERIC)
@param[in]  PartitionGuid                   Pointer to GUID of the partition (DPP, SMBIOS, etc.)
@param[in]  RootDeviceTypeGuid              Pointer to GUID of the disk (LUN4, SPINOR, etc.)

@par Description
Function that checks that the file system signature is valid.

@return
EFI_SUCCESS           -- Function completed successfully. \n
EFI_INVALID_PARAMETER -- Parameter is invalid. \n
EFI_XXXX              -- Other errors\n
*/
typedef
BOOLEAN
(EFIAPI *EFI_VERIFYSIGNATURE)(
    IN EFI_RAW_FILE_SYSTEM_PROTOCOL     *This,
    IN CHAR16                           *PartitionName,
    IN EFI_GUID                         *PartitionGuid,
    IN EFI_GUID                         *RootDeviceTypeGuid
    );

/* EFI_GETNEXTFILENAMEINDIR */
/** @ingroup EFI_RAW_FILE_SYSTEM_PROTOCOL_apis
@par Summary
Gets the next file name from a directory.
If pFiletoRead is NULL, pNextFile returns the first found file name in directory.
If pFiletoRead is not NULL, pNextFile returns the next file name in directory 
found after pFileRead. If no more files exist, nextfile returns NULL.

@param[in]  This                            Pointer to the EFI_RAW_FILE_SYSTEM_PROTOCOL instance.
@param[in]  pDirectoryName                  Directory to read
@param[in]  PartitionName                   Signature (CHAR16*) of the partition (DPP, SMBIOS, GENERIC)
@param[in]  PartitionGuid                   Pointer to GUID of the partition (DPP, SMBIOS, etc.)
@param[in]  pFiletoRead                     Input file name whose size need to be returned.
@param[in, out]  pFileSize                  Size of the input file
@param[out]  pNextFile                      Pointer to first/next file name found in directory
@param[in]  RootDeviceTypeGuid              Pointer to GUID of the disk (LUN4, SPINOR, etc.)

@par Description
Function that checks if the directory exists in file system.

@return
EFI_SUCCESS           -- Directory found in file system. \n
EFI_NOT_FOUND         -- Directory not found in file system. \n
EFI_INVALID_PARAMETER -- Parameter is invalid. \n
EFI_XXXX              -- Other errors\n
*/
typedef
EFI_STATUS
(EFIAPI *EFI_GETNEXTFILENAMEINDIR)(
    IN EFI_RAW_FILE_SYSTEM_PROTOCOL     *This,
    IN CHAR16                           *pDirectoryName,
    IN CHAR16                           *PartitionName,
    IN EFI_GUID                         *PartitionGuid,
    IN CHAR16                           *pFiletoRead,
    IN OUT UINTN                        *pFileSize,
    OUT CHAR16                          **pNextFile,
    IN EFI_GUID                         *RootDeviceTypeGuid
    );

/*===========================================================================
PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup EFI_RAW_FILE_SYSTEM_PROTOCOL_prot
@par Summary
EFI_RAW_FILE_SYSTEM_PROTOCOL Protocol interface.
*/
struct _EFI_RAW_FILE_SYSTEM_PROTOCOL {
    UINT64                          Revision;
    EFI_FILEREAD                    FileRead;
    EFI_FILEWRITE                   FileWrite;
    EFI_FILEDELETE                  FileDelete;
    EFI_FORMATRAWFILESYSTEM         FormatFileSystem;
    EFI_VERIFYSIGNATURE             VerifySignature;
    EFI_GETNEXTFILENAMEINDIR        GetNextFileNameInDirectory;
};

#endif  /* __EFI_RAW_FILE_SYSTEM_H_ */

