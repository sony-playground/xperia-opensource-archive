/*
 * @file PASRLib.c
 *
 * @brief PASRLib functions
 *
 * Copyright (c) 2022 by Qualcomm Technologies, Inc. 
 * All Rights Reserved.
 *
 */
/*=======================================================================
                        Edit History

when       who     what, where, why
--------   ----    --------------------------------------------------- 
05/14/22   ddk     Initital Version
========================================================================*/
#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <com_dtypes.h>
#include <smem.h> 
#include <MemRegionInfo.h>
#include <ddr_drivers.h>
#include <stdio.h>
#include <Protocol/EFIPasr.h>
#include <PASRLib.h>
#include <PASRQMP.h>

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
#define MAX_LENGTH 100
PASR_BLOCK gPasr_Block;

/*==============================================================================

  FUNCTION      PasrConfig

  DESCRIPTION   See EFI_PASR_CONFIG in Protocol/EFIPasr.h

==============================================================================*/

EFI_STATUS
PasrConfig (IN UINT32 NumBlocks, IN PASR_BLOCK *Pasr_Block) 
{
  DDR_REGIONS_ENTRY *ddr_regions = NULL;
  UINT32 DDRInfoBuffSz = 0;
  UINT8 region_idx = 0;
  UINTN region_end = 0;
  
  if(Pasr_Block == NULL)
  {
    DEBUG ((EFI_D_ERROR, "Error: Pasr_Block is NULL\n"));
    return EFI_INVALID_PARAMETER;
  }
  /* Get the DDR Info SMEM */
  ddr_regions = (DDR_REGIONS_ENTRY *)smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
  if (ddr_regions == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_WARN, "WARNING: Unable to read DDR Regions Data from SMEM\n"));
    return EFI_NOT_READY;
  }
  if(NumBlocks != 1)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_ERROR, "Error: NumBlocks more than 1\n"));
    return EFI_INVALID_PARAMETER;
  }
  /* Get DDR regions Data */
  ddr_regions = (DDR_REGIONS_ENTRY *)(((UINT8 *)ddr_regions) + sizeof(ddr_details_entry));
  /* Check if the size is less than the PASR granule size*/
  if(Pasr_Block->Size < (ddr_regions->ddr_region[region_idx].granule_size << 20))
  {
    DEBUG ((EFI_D_ERROR, "Error: PASR size less than PASR granule size\n"));
    return EFI_INVALID_PARAMETER;
  }
  /* Check if the start address is mapped to DDR */
  for(region_idx = 0; region_idx < ddr_regions->no_of_ddr_regions; region_idx++)
  {
      region_end = ddr_regions->ddr_region[region_idx].start_address + ddr_regions->ddr_region[region_idx].size;
      /* If the address is in between the region DDR address range, return the SUCCESS */
      if((Pasr_Block->Address >= ddr_regions->ddr_region[region_idx].start_address) && (Pasr_Block->Address < region_end))
      {
            gPasr_Block.Address = Pasr_Block->Address;
            gPasr_Block.Size = Pasr_Block->Size;
            /* return SUCCESS if valid address is found in the region table */
            return EFI_SUCCESS;
      }
  }
  /* If the address is not found in the region table, then return the address is not a DDR mapped address */
  return EFI_INVALID_PARAMETER;
}

/*==============================================================================

  FUNCTION      PASRActivate

  DESCRIPTION   See EFI_PASR_ACTIVATE in Protocol/EFIPasr.h

==============================================================================*/

EFI_STATUS PASRActivate () 
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  DDR_REGIONS_ENTRY *ddr_regions = NULL;
  PASR_SEGMENT pasr_seg_tbl[MAX_NUM_PASR_SEGMENTS] = {{0, 0}};
  UINT8 region_idx = 0, seg_idx =0;
  UINTN region_end = 0, seg_start = 0, seg_size = 0, seg_end = 0;
  char pasr_message[MAX_LENGTH];
  UINT32 addr_high = 0, addr_low = 0;
  UINTN pasr_mapped_size = 0;

  Status = PASR_QmpInit();
  if ((EFI_ERROR(Status)))
  {
     DEBUG((EFI_D_ERROR, "QMP Channel open failed, Status : 0x%x \r\n", Status));
     return Status;
  }
  
  /* Get the PASR granule size and the DDR regions information using UEFI Protocol */
  /* Get the DDR Info SMEM */
  ddr_regions = (DDR_REGIONS_ENTRY *)smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
  if (ddr_regions == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_ERROR, "WARNING: Unable to read DDR Regions Data from SMEM\n"));
    Status = PASR_QmpDeInit();
    if ((EFI_ERROR(Status)))
    {
       DEBUG((EFI_D_ERROR, "QMP Channel close failed, Status : 0x%x \r\n", Status));
    }
    return EFI_NOT_READY;
  }

  /* Get DDR regions Data */
  ddr_regions = (DDR_REGIONS_ENTRY *)(((UINT8 *)ddr_regions) + sizeof(ddr_details_entry));
  /*char str[100] = "{class: ddr, event: pasr, addr_hi: 0x%08lx, addr_lo: 0x%08lx, refresh: off}”*/
  /* Cosntruct the PASR segment table with segment start address and segment size */
  for(region_idx = 0; region_idx < ddr_regions->no_of_ddr_regions; region_idx++)
  {
      region_end = ddr_regions->ddr_region[region_idx].start_address + ddr_regions->ddr_region[region_idx].size;
      seg_start = ddr_regions->ddr_region[region_idx].start_address + ddr_regions->ddr_region[region_idx].segments_start_offset;
      seg_size =  ddr_regions->ddr_region[region_idx].granule_size << 20;
      for(seg_idx = ddr_regions->ddr_region[region_idx].segments_start_index; seg_idx < MAX_NUM_PASR_SEGMENTS && seg_start < region_end; seg_idx++)
      {
          pasr_seg_tbl[seg_idx].seg_size = seg_size;
          if(seg_start + seg_size > region_end)
          {
             break;
          }
          pasr_seg_tbl[seg_idx].seg_start_addr = seg_start;
          seg_start += seg_size;
      }
  }
  
  /* Issue the SMC call to unmap higher DDR regions */
  //SMC_CALL(Start_Address, Size);
  
  /* Construct the PASR messages based on the calculated segments information*/
  for(seg_idx = 0; (seg_idx < MAX_NUM_PASR_SEGMENTS) && (pasr_mapped_size < gPasr_Block.Size); seg_idx++)
  {
      seg_end = pasr_seg_tbl[seg_idx].seg_start_addr + pasr_seg_tbl[seg_idx].seg_size;
      /* If the pasr start address is greater than the segment end, go to the next segment */
      if(gPasr_Block.Address >= seg_end || pasr_seg_tbl[seg_idx].seg_start_addr == 0)
      {
          continue;
      }
      /* If the pasr start address is present in between the segment range, then reduce the pasr_mapped_size 
      and it cannot be PASR-OFF since it is not aligned to segment boundary */
      if((pasr_seg_tbl[seg_idx].seg_start_addr < gPasr_Block.Address) && (gPasr_Block.Address < seg_end))
      {
            pasr_mapped_size += (seg_end - gPasr_Block.Address); 
      }
      /* If the segment_start_address is >= PASR_START address then this segment can be PASR-OFF if the size doesnt exceed the TOTAL_PASR_SIZE */
      else 
      {
            if(pasr_mapped_size + pasr_seg_tbl[seg_idx].seg_size <= gPasr_Block.Size)
            {
                  pasr_mapped_size += pasr_seg_tbl[seg_idx].seg_size;
                  addr_low = pasr_seg_tbl[seg_idx].seg_start_addr & 0xffffffff;
                  addr_high = (pasr_seg_tbl[seg_idx].seg_start_addr >> 32 ) & 0xffffffff;
                  snprintf(pasr_message, MAX_LENGTH, "{class: ddr, event: pasr, addr_hi: 0x%08lx, addr_lo: 0x%08lx, refresh: %s}", addr_high,  addr_low, "off");
                  /* Send the messages to AOP using GLINK- QMP interface */
                  Status = PASR_QmpSendMsg(pasr_message, MAX_LENGTH);
                  if ((EFI_ERROR(Status)))
                  {
                      DEBUG((EFI_D_ERROR, "Send PASR segment message to AOP failed, Status :0x%x \r\n", Status));
                      DEBUG((EFI_D_ERROR, "PASR segment with seg start address 0x%016lx failed to be sent to AOP\r\n", pasr_seg_tbl[seg_idx].seg_start_addr));
                  }
                  else
                  {
                      DEBUG((EFI_D_ERROR, "PASR segment start address 0x%016lx size 0x%016lx sent to AOP\r\n", pasr_seg_tbl[seg_idx].seg_start_addr, pasr_seg_tbl[seg_idx].seg_size));
                  }
            }
      }
  }
  Status = PASR_QmpDeInit();
  if ((EFI_ERROR(Status)))
  {
     DEBUG((EFI_D_ERROR, "QMP Channel close failed, Status : 0x%x \r\n", Status));
  }
  return Status;
}

















