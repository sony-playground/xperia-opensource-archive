/** @file BLkIoSelectLib.c

  Lib for selecting BlkIohandles based on specific conditions

  Copyright (c) 2017, Qualcomm Technologies Incorporated.
  All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 12/01/17   jt      Add NVMe support 
 02/02/17   vk      Initial revision
=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/BlockIo.h>
#include <Protocol/SimpleFileSystem.h>
#include <Library/BootConfig.h>

#include <Library/BlkIoSelectLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomTargetLib.h>
#include <Library/UefiCfgLib.h>
#include <Protocol/EFICardInfo.h>

extern EFI_GUID gEfiEmmcUserPartitionGuid;

extern EFI_GUID gEfiUfsLU0Guid;
extern EFI_GUID gEfiUfsLU1Guid;
extern EFI_GUID gEfiUfsLU2Guid;
extern EFI_GUID gEfiUfsLU3Guid;
extern EFI_GUID gEfiUfsLU4Guid;
extern EFI_GUID gEfiUfsLU5Guid;
extern EFI_GUID gEfiUfsLU6Guid;
extern EFI_GUID gEfiUfsLU7Guid;

extern EFI_GUID gEfiEmmcGppPartition1Guid;
extern EFI_GUID gEfiEmmcGppPartition2Guid;
extern EFI_GUID gEfiEmmcGppPartition3Guid;
extern EFI_GUID gEfiEmmcGppPartition4Guid;

extern EFI_GUID gEfiNvme0Guid; 

extern EFI_GUID gEfiUfsRPMBGuid;

extern EFI_GUID gEfiSdRemovableGuid;

STATIC EFI_STATUS
GetBootDevice (CHAR8 *BootDevice)
{
  EFI_STATUS                  Status;
  STATIC MEM_CARD_INFO        CardInfoData;
  EFI_HANDLE                  *Handles = NULL;
  EFI_BLOCK_IO_PROTOCOL       *BlkIo;
  EFI_MEM_CARDINFO_PROTOCOL   *CardInfo;
  UINTN                       NumberOfHandles;
  UINTN                       j;

  Status = gBS->LocateHandleBuffer (ByProtocol,
                                    &gEfiBlockIoProtocolGuid,
                                    NULL,
                                    &NumberOfHandles,
                                    &Handles);
  if(Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_ERROR,"Failed to get BlkIo handles\n"));
    goto ErrorExit;
  }

  for (j = 0; j < NumberOfHandles; j++)
  {

    Status = gBS->HandleProtocol (Handles[j],
                                  &gEfiBlockIoProtocolGuid,
                                  (VOID **) &BlkIo);
    if (EFI_ERROR (Status))
      continue;

    if (BlkIo->Media->RemovableMedia)
      continue;

    Status = gBS->HandleProtocol (Handles[j],
                                  &gEfiMemCardInfoProtocolGuid,
                                  (VOID**)&CardInfo);

    if(Status != EFI_SUCCESS)
      continue;

  	Status = CardInfo->GetCardInfo (CardInfo, &CardInfoData);
	  if (Status != EFI_SUCCESS)
	  {
	    DEBUG((EFI_D_ERROR,"Failed to get Card Info! status: %d\n", Status));
	    goto ErrorExit;
	  }

	  //DEBUG((EFI_D_ERROR,"CardInfo: Boot device = %a\n", CardInfoData.card_type));
    CopyMem(BootDevice, (VOID*)CardInfoData.card_type, sizeof(CardInfoData.card_type));
    Status = EFI_SUCCESS;
    break;
  }	

ErrorExit:
  if (Handles != NULL)
    FreePool(Handles);
		  
  return Status;
}

#define MAX_HANDLE_COUNT 16

typedef struct _ROOT_PARTI {
   CONST CHAR8*  Name;
   CONST UINTN   GuidCount;
   EFI_GUID*     Guid[MAX_HANDLE_COUNT];
}RootPartitionInfoType;

#define BOOT_FROM_UFS  0x0ULL
#define BOOT_FROM_MMC  0x1ULL
#define BOOT_FROM_SDC  0x2ULL
#define BOOT_FROM_NVME 0x3ULL

STATIC RootPartitionInfoType  RootPartitionInfo[] = 
{
  {"UFS", 8,{&gEfiUfsLU0Guid, &gEfiUfsLU1Guid, &gEfiUfsLU2Guid, &gEfiUfsLU3Guid, &gEfiUfsLU4Guid, &gEfiUfsLU5Guid, &gEfiUfsLU6Guid, &gEfiUfsLU7Guid} },
  {"MMC", 5,{&gEfiEmmcUserPartitionGuid, &gEfiEmmcGppPartition1Guid, &gEfiEmmcGppPartition2Guid, &gEfiEmmcGppPartition3Guid, &gEfiEmmcGppPartition4Guid} },
  {"SDC", 1,{&gEfiSdRemovableGuid}},
  {"NVM", 1,{&gEfiNvme0Guid} }
};


STATIC EFI_STATUS
HandleBootDevice (UINTN BootDevice, EFI_GUID *PartitionType, CHAR16 *PartitionLabel, HandleInfo **pHandles)
{
  EFI_STATUS Status = EFI_NOT_FOUND;
  UINT32 Attribs = 0;
  PartiSelectFilter  HandleFilter;
  UINT32             HandleCount;
  UINTN i = 0;

  for (i=0; i < RootPartitionInfo[BootDevice].GuidCount; i++)
  {
    /* Reset Params */
    HandleCount =  MAX_HANDLE_COUNT;
    Status = EFI_NOT_FOUND;

    /* Set Root for UFS */
    Attribs                     = BLK_IO_SEL_MATCH_ROOT_DEVICE;
    HandleFilter.RootDeviceType = RootPartitionInfo[BootDevice].Guid[i];

    /* Set Partition Type using GUID from caller */
    if (PartitionType != NULL)
    {
      Attribs                         |= BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID;
      HandleFilter.PartitionType       = PartitionType;
    }

    /* Set Partition label from caller */
    if (PartitionLabel != NULL)
    {
      Attribs                         |= BLK_IO_SEL_MATCH_PARTITION_LABEL;
      HandleFilter.PartitionLabel      = PartitionLabel;
    }

    Status = GetBlkIOHandles(Attribs,
                             &HandleFilter,
                             *pHandles,
                             &HandleCount
                           );
    if ((Status == EFI_SUCCESS) && (HandleCount == 1))
    {
      Status = EFI_SUCCESS;
      break;
    }
  }

  return Status;
}

EFI_STATUS
EFIAPI
GetBootDevBlkIOHandle (EFI_GUID *PartitionType, CHAR16* PartitionLabel, HandleInfo *BlkIoHandle)
{
  EFI_STATUS Status;
  CHAR8 BootDevice[4] = {0,0,0,0};
  HandleInfo *pHandles = NULL;

  pHandles = AllocatePool (MAX_HANDLE_COUNT * sizeof (HandleInfo));
  if (pHandles == NULL)
    return EFI_OUT_OF_RESOURCES;

  /* Get Boot Device */
  Status = GetBootDevice ((CHAR8*)&BootDevice);
  BootDevice[3] = '\0';

	DEBUG((EFI_D_ERROR,"Boot device = %a\n", BootDevice));
  
  if (AsciiStrCmp(BootDevice, "UFS") == 0)
    Status = HandleBootDevice (BOOT_FROM_UFS, PartitionType, PartitionLabel, &pHandles);
  else if (AsciiStrCmp(BootDevice, "MMC") == 0)
    Status = HandleBootDevice (BOOT_FROM_MMC, PartitionType, PartitionLabel, &pHandles);
  else if (AsciiStrCmp(BootDevice, "SDC") == 0)
    Status = HandleBootDevice (BOOT_FROM_SDC, PartitionType, PartitionLabel, &pHandles);
  else if (AsciiStrCmp(BootDevice, "NVM") == 0)
    Status = HandleBootDevice (BOOT_FROM_NVME, PartitionType, PartitionLabel, &pHandles);
  else
  {
    ASSERT (FALSE);
    return Status;
  }

  *BlkIoHandle = *pHandles;

  return Status;
}


