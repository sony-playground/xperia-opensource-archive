/** @file
  Initializes SMBios table.

  Copyright (c) 2011,2012, 2014-2022 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/13/22   dnkg    Fixed alignment issues
 06/21/21   sood    Fixed MISRA rules:Initialized SmbiosListHeadPtr with NULL in SmBiosTableDxeInitialize()
 03/30/21   kbarad  Fixed Klocwork issue
 02/24/20   kbarad  Adding PCD configurable support to fill SMBIOS table
 02/13/20   dm      Added Simple file system support for block-based Smbios access
 04/12/18   ltg     Add Raw File System support
 03/21/18   md      Add Spinor support
 12/01/17   jt      Add NVMe support
 07/05/16   bh      Update file system call after API change
 04/23/15   vk      Add UFS support
 10/16/14   vk      LoadFileFromPartition signature update
 09/11/12   niting  Fix status of init
 07/09/12   yg      Add filesize param
 04/25/12   yg      Revert Type 3 table removal
 04/24/12   yg      Remove System Enclosure table
 03/20/12   kedara  Support config file based table loading.
 03/07/12   kedara  Added support for System Enclosure (Type 3) table
 05/25/11   niting  Initial revision

=============================================================================*/

#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>

#include <Protocol/Smbios.h>

#include <Library/QcomLib.h>
#include <Library/EfiFileLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BootConfig.h>
#include <Library/BaseMemoryLib.h>

#define CONFIG_FILE_PATH                         L"\\SMBIOS\\SMBIOS.CFG"
#define RAW_FS_CONFIG_FILE_PATH                  L"SMBIOS\\SMBIOS.CFG"
#define SMBIOS_PART_NAME                         L"SMBIOS"
#define DEFAULT_FS_BLOCKSIZE                     256  // 1/8 of TZ Block Size

static EFI_GUID gSmbiosPartitionTypeGuid =
{ 0x04A856B8, 0x84C1, 0x4075,{ 0x83, 0x91, 0x9A, 0x99, 0x42, 0x35, 0xE5, 0xF0 } };

#include <SmbiosCfgInfo.h>
#include <Protocol/EFIRawFileSystem.h>


EFI_STATUS UpdateSysEnclosureInfoTable( EFI_SMBIOS_PROTOCOL     *Smbios);
EFI_STATUS UpdateBiosInfoTable( EFI_SMBIOS_PROTOCOL     *Smbios);
EFI_STATUS UpdateProcessorInfoTable (EFI_SMBIOS_PROTOCOL     *Smbios);
EFI_STATUS UpdateSystemInfoTable (EFI_SMBIOS_PROTOCOL     *Smbios);
EFI_STATUS UpdateMemoryArrayInfoTable (EFI_SMBIOS_PROTOCOL     *Smbios);
EFI_STATUS UpdateCacheInfoTable (EFI_SMBIOS_PROTOCOL     *Smbios);

//Root Partition
extern EFI_GUID gEfiEmmcGppPartition1Guid;
extern EFI_GUID gEfiEmmcUserPartitionGuid;
extern EFI_GUID gEfiUfsLU4Guid;
extern EFI_GUID gEfiNvme0Guid;
extern EFI_GUID gEfiSpiNor0Guid;

//Partition Types
extern EFI_GUID gEfiPlatPartitionTypeGuid;
extern EFI_GUID gSmbiosPartitionTypeGuid;

/**
Function to get a matching partition handle
after comparing the Emmc type, Partition Name and
Partition type GUID

@param PartHandle    - partition handle
@Param PartTypeGuid  - Partition type GUID
@Param PartitionName - Partition name (optional)
@Param Protocol      - Protocol

@retval EFI_SUCCESS    Partition handle found
@retval EFI_NOT_FOUND  Partition handle not found
@retval EFI_XXXX       Other errors

**/
EFI_STATUS
GetPartitionHandle(
    IN OUT EFI_HANDLE              *PartHandle,
    IN EFI_GUID                    *PartTypeGuid,
    IN CHAR16                      *PartitionName,
    IN EFI_GUID                    *Protocol
)
{
  EFI_STATUS                 Status             = EFI_SUCCESS;
  EFI_HANDLE                *HandleBuffer       = NULL;
  UINTN                      NumHandles         = 0;
  UINTN                      HandleCounter      = 0;
  EFI_GUID                  *TempPartTypeGuid   = NULL;
  CHAR16                    *TempPartitionName  = NULL;
  EFI_PARTITION_ENTRY       *TempPartEntry      = NULL;
  EFI_DEVICE_PATH_PROTOCOL  *DevPathInst        = NULL;

  if ((PartHandle == NULL) ||
      (PartTypeGuid == NULL) ||
      (Protocol == NULL))
  {
    return EFI_INVALID_PARAMETER;
  }

  Status = gBS->LocateHandleBuffer(
    ByProtocol,
    Protocol,
    NULL,
    &NumHandles,
    &HandleBuffer
    );
  if(EFI_ERROR(Status))
  {
    return Status;
  }

  for(HandleCounter = 0; HandleCounter < NumHandles; HandleCounter++)
  {
    Status = gBS->HandleProtocol(
      HandleBuffer[HandleCounter],
      &gEfiPartitionTypeGuid,
      (VOID**)&TempPartTypeGuid
      );
    if(EFI_ERROR(Status))
    {
      continue;
    }

    Status = gBS->HandleProtocol(
      HandleBuffer[HandleCounter],
      &gEfiDevicePathProtocolGuid,
      (VOID**)&DevPathInst
      );
    if(EFI_ERROR(Status))
    {
      continue;
    }

    Status = gBS->HandleProtocol(
      HandleBuffer[HandleCounter],
      &gEfiPartitionRecordGuid,
      (VOID **) &TempPartEntry
      );
    if(EFI_ERROR(Status))
    {
      continue;
    }

    TempPartitionName = TempPartEntry->PartitionName;
    DevPathInst = (EFI_DEVICE_PATH_PROTOCOL*)(((UINT8*)DevPathInst)+DevPathInst->Length[0]);

    if(DevPathInst->Type == 4)
    {
      if(CompareGuid(TempPartTypeGuid,PartTypeGuid))
      {
        *PartHandle = HandleBuffer[HandleCounter];
        Status = EFI_SUCCESS;
        goto GetPartitionHandle;
      }
    }
  }

  Status = EFI_NOT_FOUND;

GetPartitionHandle:
  if(HandleBuffer != NULL)
  {
    gBS->FreePool(HandleBuffer);
    HandleBuffer = NULL;
  }

  return Status;
}

/**
LoadCfgFileFromRawPartition
Loads a  file from a block-based partition specified by Root Device type GUID
Partition Type GUID and Partition Label

@param  RawFSProtocol     Handle to Raw File System Protocol
@param  CfgFilePath       Pointer to file path
@param  DiskTypeGuid      Pointer to the disk type guid
@param  PartitionType     Pointer to the partition type guid
@param  PartitionLabel    Pointer to partition label
@param  SmbiosCfgBuffPtr  Pointer to the buffer to store file contents
@param  FileSize          Pointer to size of contents copied to buffer

@retval EFI_SUCCESS           File read successfully
@retval EFI_OUT_OF_RESOURCES  Cannot allocate buffer
@retval EFI_VOLUME_CORRUPTED  Partition is corrupted

**/
EFI_STATUS
LoadCfgFileFromRawPartition(
  IN EFI_RAW_FILE_SYSTEM_PROTOCOL     *pRawFSProtocol,
  IN CHAR16                           *pCfgFilePath,
  IN EFI_GUID                         *pDiskTypeGuid,
  IN EFI_GUID                         *pPartitionType,
  IN CHAR16                           *pPartitionLabel,
  IN OUT UINT8                        **ppSmbiosCfgBuffPtr,
  IN OUT UINTN                        *pFileSize
)
{
  EFI_STATUS                        Status = EFI_SUCCESS;
  EFI_HANDLE                        PartHandle = NULL;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL  *Fs           = NULL;
  EFI_FILE_PROTOCOL                *FsRoot       = NULL;
  EFI_FILE_PROTOCOL                *File         = NULL;
  UINT64                            Attributes   = 0x0;

  Status = GetPartitionHandle(
    &PartHandle,
    &gSmbiosPartitionTypeGuid,
    NULL,
    &gEfiSimpleFileSystemProtocolGuid
    );

  if(!EFI_ERROR(Status) && (PartHandle != NULL))
  {
    Status = gBS->HandleProtocol(
      PartHandle,
      &gEfiSimpleFileSystemProtocolGuid,
      (VOID **)&Fs
      );
    if(EFI_ERROR(Status))
    {
      DEBUG((EFI_D_ERROR, "[SmbiosTableDxe] Failed to locate SimpleFS Protocol."));
      goto LoadCfgFileFromRawPartitionExit;
    }
  }
  else
  {
    Status = EFI_UNSUPPORTED;
    DEBUG((EFI_D_ERROR, "[SmbiosTableDxe] Warning: Block Smbios unsupported platform type."));
    goto LoadCfgFileFromRawPartitionExit;
  }

  Status = Fs->OpenVolume(Fs,&FsRoot);
  if(!EFI_ERROR(Status) && NULL != FsRoot)
  {
    Status = FsRoot->Open(
      FsRoot,
      &File,
      pCfgFilePath,
      EFI_FILE_MODE_READ,
      Attributes
      );
    if(EFI_ERROR(Status))
    {
      Status = EFI_NOT_FOUND;
      DEBUG((EFI_D_ERROR,"[SmbiosTableDxe] SimpleFs File open failed."));
      goto LoadCfgFileFromRawPartitionExit;
    }
  }
  else
  {
    Status = EFI_NOT_FOUND;
    DEBUG((EFI_D_ERROR, "[SmbiosTableDxe] SimpleFs OpenVolume failed."));
    goto LoadCfgFileFromRawPartitionExit;
  }
  // get file size
  Status = File->Read(File, pFileSize, NULL);
  if (EFI_ERROR(Status))
  {
    if (EFI_BUFFER_TOO_SMALL == Status)
    {
      *ppSmbiosCfgBuffPtr = (UINT8*)AllocateZeroPool(sizeof(UINT8) * (*pFileSize));
      if (*ppSmbiosCfgBuffPtr == NULL)
      {
        Status = EFI_OUT_OF_RESOURCES;
        DEBUG((EFI_D_WARN, "[SmbiosTableDxe] Failed to allocate buffer for config file. Status = 0x%x", Status));
        goto LoadCfgFileFromRawPartitionExit;
      }
      // read file
      Status = File->Read(File, pFileSize, *ppSmbiosCfgBuffPtr);
      if (EFI_ERROR(Status))
      {
        DEBUG((EFI_D_ERROR, "[SmbiosTableDxe] SimpleFs File read failed."));
        goto LoadCfgFileFromRawPartitionExit;
      }
    }
  }

LoadCfgFileFromRawPartitionExit:
  if (File != NULL)
  {
    File->Close (File);
  }
  if (FsRoot != NULL)
  {
    FsRoot->Close (FsRoot);
  }
  return Status;
}

/**
Set up the SMBios table

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
EFI_STATUS
SmBiosTableDxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_SMBIOS_PROTOCOL     *Smbios;
  EFI_STATUS              Status;
  UINT8                   *SmbiosCfgBuffPtr = NULL;
  UINTN                   FileSize = 0;
  UINT32                  BlkIOAttrib = 0;
  EFI_RAW_FILE_SYSTEM_PROTOCOL *RawFSProtocol = NULL;

  // Pointer to list of smbios tables to be added
  SMBIOS_TABLE_NODE *SmbiosListHeadPtr = NULL;

  Status = gBS->LocateProtocol (
    &gEfiSmbiosProtocolGuid,
    NULL,
    (VOID **) &Smbios
    );
  ASSERT_EFI_ERROR (Status);

  // Initialize Smbios Table List struct
  SmbiosConfigInit(&SmbiosListHeadPtr);
    // Initialize the Head Node;
  SetSmbiosListHeadNode (SmbiosListHeadPtr);

  if(TRUE == PcdGetBool(PcdUseSmbiosCfgFile))
  {
    // Set attributes for fetching Block IO handle
    BlkIOAttrib = BLK_IO_SEL_PARTITIONED_GPT;
    BlkIOAttrib |= BLK_IO_SEL_MEDIA_TYPE_NON_REMOVABLE;
    BlkIOAttrib |= BLK_IO_SEL_MATCH_ROOT_DEVICE;
    BlkIOAttrib |= BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID;

    // Load Smbios file into buffer

    if (boot_from_emmc())
    {
      //Attempt to load from Plat partition in eMMC GPP
      Status = LoadFileFromPartition(
        BlkIOAttrib,
        CONFIG_FILE_PATH,
        &gEfiEmmcGppPartition1Guid,
        &gEfiPlatPartitionTypeGuid,
        NULL,
        &SmbiosCfgBuffPtr,
        &FileSize
        );
      //Attempt to load from User Partition
      if (Status != EFI_SUCCESS)
      {
        Status = LoadFileFromPartition(
          BlkIOAttrib,
          CONFIG_FILE_PATH,
          &gEfiEmmcUserPartitionGuid,
          &gEfiPlatPartitionTypeGuid,
          NULL,
          &SmbiosCfgBuffPtr,
          &FileSize
          );
      }
    }
    else if (boot_from_ufs())
    {
      //Search in only SMBIOS partition for the config file, PLAT partition should not have SMBIOS config as it may get wiped away during an update.
      Status = LoadCfgFileFromRawPartition(
        RawFSProtocol,
        RAW_FS_CONFIG_FILE_PATH,
        &gEfiUfsLU4Guid,
        &gSmbiosPartitionTypeGuid,
        SMBIOS_PART_NAME,
        &SmbiosCfgBuffPtr,
        &FileSize
        );
    }
    else if (boot_from_nvme())
    {
      //Search in only SMBIOS partition for the config file, PLAT partition should not have SMBIOS config as it may get wiped away during an update.
      Status = LoadCfgFileFromRawPartition(
        RawFSProtocol,
        RAW_FS_CONFIG_FILE_PATH,
        &gEfiSpiNor0Guid,
        &gSmbiosPartitionTypeGuid,
        SMBIOS_PART_NAME,
        &SmbiosCfgBuffPtr,
        &FileSize
        );
    }

    if (Status == EFI_SUCCESS)
    {
      // Parse config file and update tables if it exists.
      UpdateCfgBasedInfoTable(SmbiosCfgBuffPtr, FileSize, SmbiosListHeadPtr);
      AddSmbiosTables(Smbios,SmbiosListHeadPtr);
    }
  }
  Status = EFI_SUCCESS;

  // Override Config file changes if any with preset values.
  if(TRUE == PcdGetBool(PcdUpdateBiosInfoTable))
  {
    UpdateBiosInfoTable(Smbios);
  }

  if(TRUE == PcdGetBool(PcdUpdateSmbiosTableType7))
  {
    UpdateCacheInfoTable(Smbios);
  }

  if(TRUE == PcdGetBool(PcdUpdateProcessorInfoTable))
  {
    UpdateProcessorInfoTable(Smbios);
  }

  if(TRUE == PcdGetBool(PcdUpdateSystemInfoTable))
  {
    UpdateSystemInfoTable(Smbios);
  }

  if(TRUE == PcdGetBool(PcdUpdateSmbioTableType16_Type17_Type19))
  {
    UpdateMemoryArrayInfoTable(Smbios);
  }

  if(TRUE == PcdGetBool(PcdUseSmbiosCfgFile))
  {
    UpdateSysEnclosureInfoTable(Smbios);
  }
  return Status;
}

