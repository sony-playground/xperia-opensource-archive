/** @file UfsBlockIO2.c
   
   This file implements the utility function for Block IO 2 in UFS driver
  
   Copyright (c) 2017, 2019-2020 Qualcomm Technologies, Inc. 
   All Rights Reserved. 
   Qualcomm Technologies Proprietary and Confidential  
   
**/

/*=============================================================================
                              EDIT HISTORY

when         who     what, where, why
----------   ----    ---------------------------------------------------------- 
2020-06-09   eo      Porting to Nand support to XBL Core
2019-10-22   sa      Removed unused Variables.
2019-09-12   sa      Removed unused variable.
2017-03-03   eo      Initial version

=============================================================================*/
#include "NandFtl.h"
#include "NandMibib.h"

#include <Uefi.h>

#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/ArmLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <string.h>
#include "Protocol/EFISmem.h"

static flash_ftl_client_t  hHandleMibib;
static flash_ftl_info_t    gMibibInfo;

/******************************************************************************
* Name: NandOpenPartiEntries
*
* Description:
*	 Open all partition entries in FTL layer
*
* Arguments:
*     NandMibibPartiTable  [IN] [OUT]:    Pointer to internal MIBIB partition table data structure.
*
* Returns:
*	 EFI_SUCCESS or error status
*
******************************************************************************/
EFI_STATUS 
NandOpenPartiEntries (
  IN OUT NandMibibPartiTable    *MibibPartiTable
  )
{
   EFI_STATUS   Status = EFI_SUCCESS;
   UINT32       NumEntries = 0, Idx = 0;
   CONST CHAR8 *PartiName;
   flash_ftl_client_t  hHandlePartiEntry;
   flash_ftl_info_t    PartiInfo;

   NumEntries = MibibPartiTable->PartiNumEntries;
   for (Idx = 1; Idx <= NumEntries; Idx++)
   {
      hHandlePartiEntry = MibibPartiTable->PartiEntries[Idx].PartiHandle;
      PartiName = (CONST CHAR8 *)&MibibPartiTable->PartiEntries[Idx].PartiName[0];
      if (hHandlePartiEntry == NULL)
      {
         if (FLASH_FTL_OK != flash_ftl_open(&hHandlePartiEntry, (const uint8 *)PartiName))
         {
            DEBUG ((EFI_D_ERROR, "Nand FTL Open:: returned failure, ftl_handle = 0x%x\n", hHandlePartiEntry));
            Status = EFI_DEVICE_ERROR;
            goto NandInitPartiExit;
         }
		 
         if (FLASH_FTL_OK != flash_ftl_get_info(hHandlePartiEntry, &PartiInfo))
         {
            DEBUG ((EFI_D_ERROR, "Nand FTL get info:: returned failure, ftl_handle = 0x%x\n", hHandlePartiEntry));
            Status = EFI_DEVICE_ERROR;
            goto NandInitPartiExit;
         }
         MibibPartiTable->PartiEntries[Idx].BlockCount = PartiInfo.lba_count;
		 MibibPartiTable->PartiEntries[Idx].PartiHandle = (VOID *)hHandlePartiEntry;
      }
   }

NandInitPartiExit:
   return Status;
}

/******************************************************************************
* Name: NandInitMibibPartiTable
*
* Description:
*	 Initialize the MIBIB partition table
*
* Arguments:
*     NandMibibPartiTable  [IN] [OUT]:    Pointer to internal MIBIB partition table data structure.
*
* Returns:
*	 EFI_SUCCESS or error status
*
******************************************************************************/
EFI_STATUS 
NandInitMibibPartiTable (
  IN OUT NandMibibPartiTable    *MibibPartiTable
  )
{
   EFI_SMEM_PROTOCOL *smem_protocol;
   EFI_STATUS Status = EFI_SUCCESS;
   UINT32 NumEntries = 0, Idx = 0, Size = 0;
   flash_partable_t                  SmemAarmPartitionTable;
   flash_usr_partable_t              PartitionTable = NULL;
   struct flash_usr_partition_entry  *PartitionEntry = NULL;
   UINT32 part_tbl_size = 0;

   /* Memset MIBIB table structure */
   memset((void*)MibibPartiTable,0 ,sizeof(NandMibibPartiTable));

   if (FLASH_FTL_OK != flash_ftl_open(&hHandleMibib, (const uint8 *)"all")) //"mibib"
   {
      DEBUG ((EFI_D_ERROR, "Nand FTL Open:: returned failure, ftl_handle = 0x%x\n", hHandleMibib));
      Status = EFI_DEVICE_ERROR;
      goto NandInitMibibExit;
   }

   if (FLASH_FTL_OK != flash_ftl_get_info(hHandleMibib, &gMibibInfo))
   {
      DEBUG ((EFI_D_ERROR, "Nand FTL get info:: returned failure, ftl_handle = 0x%x\n", hHandleMibib));
      Status = EFI_DEVICE_ERROR;
      goto NandInitMibibExit;
   }

   /* Initialize SMEM protocol handle */
   Status = gBS->LocateProtocol(&gEfiSMEMProtocolGuid, NULL,
       (void**)&smem_protocol);
   if(Status != EFI_SUCCESS)
   {
     AsciiPrint("ERROR: SMEM LocateProtocol returned %d\n", Status);
     goto NandInitMibibExit;
   }

   /* "flash_partition_table" stores 1 element more than the actual partition table size.
      This is the handle for the whole device which is opened using "all" as partition name.
      But from SMEM we only need to get the actual partition table, so reducing the size by 1 
    */
   part_tbl_size = sizeof(struct flash_partition_table) - sizeof(struct flash_partition_entry);

   /* Read the MIBIB partition table from shared memory referenced by SMEM_AARM_PARTITION_TABLE */
   Status = smem_protocol->SmemAlloc(SMEM_AARM_PARTITION_TABLE, part_tbl_size, (void **)&SmemAarmPartitionTable);
   if(Status != EFI_SUCCESS)
   {
     AsciiPrint("ERROR: SmemAlloc(SMEM_AARM_PARTITION_TABLE) returned %d\n", Status);
      goto NandInitMibibExit;
   }
      
   /* Initialize partition table */
   PartitionTable = (flash_usr_partable_t)SmemAarmPartitionTable;
   NumEntries = PartitionTable->numparts;
   PartitionEntry = (struct flash_usr_partition_entry *)&PartitionTable->part_entry[0];

   Size = AsciiStrLen("all");
   AsciiStrCpyS((CHAR8 *)MibibPartiTable->PartiEntries[0].PartiName, (Size+1), 
	  (CONST CHAR8 *)"all");
   MibibPartiTable->PartiEntries[0].PartiHandle = (VOID *)hHandleMibib;
   MibibPartiTable->PartiEntries[0].BlockCount  = gMibibInfo.lba_count;
   MibibPartiTable->PartiNumEntries = NumEntries;
   MibibPartiTable->EraseBlockSize  = gMibibInfo.erase_block_size_in_kbytes;
   MibibPartiTable->LbaSize         = gMibibInfo.lba_size_in_kbytes;
   for (Idx = 1; Idx <= NumEntries; Idx++)
   {
      Size = AsciiStrLen(PartitionEntry->name);
 
      AsciiStrCpyS((CHAR8 *)MibibPartiTable->PartiEntries[Idx].PartiName, (Size+1), 
        (CONST CHAR8 *)PartitionEntry->name);
	  	  
      /* Next Partition entry */
      PartitionEntry++;
   }
   
   /* Initialize each partition entry in the MIBIB partition table */
   Status = NandOpenPartiEntries(MibibPartiTable);
   
NandInitMibibExit:
   return Status;
}

