/** @file DDRInfoTest.c
   
  Test for UEFI DDR Info test.

  Copyright (c) 2017 Qualcomm Technologies Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY


 when         who       what, where, why
 --------     ---       -----------------------------------------------------------
 11/21/2020   kns       Add shub freq test
 12/18/2018   dj        Add ddr info protocal
 09/26/2017   daisond   Use max ddr channels received from GetDDRDetails module
 04/19/2017   daisond   Initial Revision
=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TestInterface.h>
#include <Library/PrintLib.h>
#include <Library/PcdLib.h>
#include <Protocol/EFIDDRGetConfig.h>
#include <Protocol/EFIHWIO.h>
#include <ddr_info_util.h>

#define LOOP_COUNT_FOR_FREQ_SCALING_TEST 10

UINT32 mul_wid = 0xFCA01979;
UINT32 mul_zid = 0xBA031903;

void srand_uefi (UINT32 seed)
{
  if (seed != 0 && seed != 0x464FFFFF) {
    mul_wid = seed;
  }
  else {
    mul_wid = 0xFCA01979;
  }
  mul_zid = 0xBA031903;
}

UINT32 rand_uefi ()
{
    mul_zid = 36969 * (mul_zid & 65535) + (mul_zid >> 16);
    mul_wid = 18000 * (mul_wid & 65535) + (mul_wid >> 16);
    return ((mul_zid << 16) + mul_wid);
}


STATIC
EFI_STATUS
DDRInfoProtocolTest (VOID)
{
  ddr_misc_info               *pDDR_misc_info = NULL;
  EFI_STATUS                  Status = EFI_NOT_FOUND;
  EFI_DDRGETINFO_PROTOCOL     *pDDRGetInfoProtocol = NULL;
  EFI_HWIO_PROTOCOL           *HWIOProtocol = NULL;
  ddr_details_entry           *pDDREntry = NULL;
  ddr_freq_plan_entry         *pDDRFreqTbl = NULL;
  DDR_REGIONS_ENTRY           *pDDRRegionsEntry = NULL;
  shub_freq_plan_entry        *pSHUBFreqTbl = NULL;
  UINT32 ddr_channel = 0, rank = 0, ddr_freq = 0, ddr_max_enabled_freq = 0;
  UINT32 set_ddr_freq = 200000, freq_index = 0;
  UINT32 idx = 0;
  UINT8 *Addr;
  UINT32 set_shub_freq = 0;
  UINT32 shub_freq_value = 0;

  Status = gBS->LocateProtocol(&gEfiDDRGetInfoProtocolGuid, NULL, (VOID**)&pDDRGetInfoProtocol);
  if (EFI_ERROR(Status) || (&pDDRGetInfoProtocol == NULL))
  {
    DEBUG((EFI_D_ERROR, "Locate EFI_DDRGETINFO_PROTOCOL failed, Status =  (0x%x)\r\n", Status));
    return EFI_NOT_FOUND;
  }
  
  Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&HWIOProtocol);
  if ((EFI_SUCCESS != Status) || (HWIOProtocol == NULL))
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to locate HWIO Protocol: 0x%08x\n", Status));
    return EFI_NOT_FOUND;
  }

  Status = HWIOProtocol->MapRegion(HWIOProtocol, "+MCCC_MCCC_MSTR", (UINT8**) &Addr);
  if (EFI_SUCCESS != Status)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to map MCCC_MCCC_MSTR base address: 0x%08x\n", Status));
    return EFI_NOT_FOUND;
  }
  
  pDDREntry = AllocatePool (sizeof (ddr_details_entry));
  if (pDDREntry == NULL) 
      return EFI_OUT_OF_RESOURCES;
  
  pDDRFreqTbl = AllocatePool (sizeof (ddr_freq_plan_entry));
  if (pDDRFreqTbl == NULL)
	  return EFI_OUT_OF_RESOURCES;

  pDDRRegionsEntry = AllocatePool (sizeof (DDR_REGIONS_ENTRY));
  if (pDDRRegionsEntry == NULL)
	  return EFI_OUT_OF_RESOURCES;

  pSHUBFreqTbl = AllocatePool(sizeof(shub_freq_plan_entry));
  if (pSHUBFreqTbl == NULL)
    return EFI_OUT_OF_RESOURCES;
  
  pDDR_misc_info = AllocatePool (sizeof (ddr_misc_info));
  if (pDDR_misc_info == NULL) 
      return EFI_OUT_OF_RESOURCES;

  Status = pDDRGetInfoProtocol->GetDDRDetails(pDDRGetInfoProtocol, pDDREntry);
  if (Status != EFI_SUCCESS)
  {
    if (EFI_ERROR (Status))
    {
      DEBUG((EFI_D_WARN, "Failed to get DDR details"));
    }
	return Status;
  }

  Status = pDDRGetInfoProtocol->GetDDRFreqTable(pDDRGetInfoProtocol, pDDRFreqTbl);
  if (Status != EFI_SUCCESS)
  {
    if (EFI_ERROR (Status))
    {
      DEBUG((EFI_D_WARN, "Failed to get DDR Freq Table"));
    }
	return Status;
  }

  Status = pDDRGetInfoProtocol->GetDDRMappedRegions(pDDRGetInfoProtocol, pDDRRegionsEntry);
  if (Status != EFI_SUCCESS)
  {
    if (EFI_ERROR (Status))
    {
      DEBUG((EFI_D_WARN, "Failed to get DDR Regions Data"));
    }
	return Status;
  }

  Status = pDDRGetInfoProtocol->GetDDRFreq(pDDRGetInfoProtocol, &ddr_freq);
  if (Status != EFI_SUCCESS)
  {
    if (EFI_ERROR (Status))
    {
      DEBUG((EFI_D_WARN, "Failed to get DDR Current Freq"));
    }
	return Status;
  }
  
  Status = pDDRGetInfoProtocol->GetDDRMaxEnabledFreq(pDDRGetInfoProtocol, &ddr_max_enabled_freq);
  if (Status != EFI_SUCCESS)
  {
    if (EFI_ERROR (Status))
    {
      DEBUG((EFI_D_WARN, "Failed to get DDR Max Enabled Freq"));
    }
	return Status;
  }

  Status = pDDRGetInfoProtocol->GetSHUBFreqTable(pDDRGetInfoProtocol, pSHUBFreqTbl);
  if (Status != EFI_SUCCESS)
  {
    if (EFI_ERROR(Status))
    {
      DEBUG((EFI_D_WARN, "Failed to get SHUB Freq Table"));
    }
    return Status;
  }

  Status = pDDRGetInfoProtocol->GetDDRmiscinfoSmemData(pDDRGetInfoProtocol, pDDR_misc_info);

  if (Status != EFI_SUCCESS)
  {
    if (EFI_ERROR(Status))
    {
      DEBUG((EFI_D_WARN, "Failed to get misc ddr info"));
    }
    return Status;
  }
  
  AsciiPrint("DSF code version :");
  if(pDDR_misc_info->dsf_version>0xffff)
	AsciiPrint("%03d.%02d.%02d\n",((pDDR_misc_info->dsf_version)>>16),(((pDDR_misc_info->dsf_version)&0x0000FF00)>>8),((pDDR_misc_info->dsf_version)&0x000000FF));
  else
	  AsciiPrint("%d.%d.%d\n",pDDR_misc_info->dsf_version,pDDR_misc_info->reserved[0],pDDR_misc_info->reserved[1]);
  AsciiPrint("                                 \n");
  AsciiPrint("Number of DDR Channels          :");
  AsciiPrint("0x%016lx\n", pDDREntry->num_channels);  
  AsciiPrint("Manufacturer Id                 :");
  AsciiPrint("0x%016lx\n", pDDREntry->manufacturer_id);
  AsciiPrint("Device Type                     :");
  AsciiPrint("0x%016lx\n", pDDREntry->device_type);
  AsciiPrint("                                 \n");

  for(ddr_channel=0; ddr_channel<pDDREntry->num_channels; ddr_channel++)
  {
    for(rank=0; rank < 2; rank++)
    {
      AsciiPrint("Revision Id1 (CH %d, Rank %d)     :", ddr_channel, rank);
      AsciiPrint("0x%016lx\n", pDDREntry->ddr_params[ddr_channel].revision_id1[rank]);

      AsciiPrint("Revision Id2 (CH %d, Rank %d)     :", ddr_channel, rank);
      AsciiPrint("0x%016lx\n", pDDREntry->ddr_params[ddr_channel].revision_id2[rank]);

      AsciiPrint("Width (CH %d, Rank %d)            :", ddr_channel, rank);
      AsciiPrint("0x%016lx\n", pDDREntry->ddr_params[ddr_channel].width[rank]);

      AsciiPrint("Density (CH %d, Rank %d)          :", ddr_channel, rank);
      AsciiPrint("0x%016lx\n", pDDREntry->ddr_params[ddr_channel].density[rank]);
    }
    AsciiPrint("                                 \n");
  } 
  AsciiPrint("                    \n");
  AsciiPrint("DDR Frequency Table:\n");
  AsciiPrint("DDR Freq\t Enable   \n");
  AsciiPrint("========\t ======   \n");
  for(idx=0; idx < pDDRFreqTbl->num_ddr_freqs; idx++)
  {
      AsciiPrint("%d\t\t ", pDDRFreqTbl->ddr_freq[idx].freq_khz);
      AsciiPrint("  %d\n", pDDRFreqTbl->ddr_freq[idx].enable);
  }
  AsciiPrint("\nMax Enabled Freq: ");
  AsciiPrint("%d KHz\n", ddr_max_enabled_freq);
  AsciiPrint("                    \n");

  AsciiPrint("Max Nominal Freq: ");
  AsciiPrint("%d KHz\n", pDDRFreqTbl->max_nom_ddr_freq);
  AsciiPrint("                    \n");

  AsciiPrint("DDR Current Frequency: ");
  AsciiPrint("%d MHz\n", ddr_freq);
  AsciiPrint("                                 \n");

  // SHUB Frequency Table Information.
  AsciiPrint("\n\n");
  AsciiPrint("SHUB Frequency Table Information Start\n");
  AsciiPrint("SHUB Frequency Table:\n");
  AsciiPrint("SHUB Freq\t  Enable\n");
  AsciiPrint("========\t   ======\n");
  for (idx = 0; idx < pSHUBFreqTbl->num_shub_freqs; idx++)
  {
    AsciiPrint("%d\t\t ", pSHUBFreqTbl->shub_freq[idx].freq_khz);
    AsciiPrint("  %d\n", pSHUBFreqTbl->shub_freq[idx].enable);
  }
  AsciiPrint("========\t   ======\n");
  AsciiPrint("SHUB Frequency Table Information End\n\n");

  ddr_uefi_display_init();
  ddr_uefi_display_off();

  AsciiPrint("Set DDR to Lowest Frequency: 200MHz \n");
  Status = pDDRGetInfoProtocol->SetLowestDDRFreq(pDDRGetInfoProtocol);
  if (Status != EFI_SUCCESS)
  {
    if (EFI_ERROR (Status))
    {
      DEBUG((EFI_D_WARN, "Failed to SetLowestDDRFreq"));
    }
  }
  Status = pDDRGetInfoProtocol->GetDDRFreq(pDDRGetInfoProtocol, &ddr_freq);
  if (Status != EFI_SUCCESS)
  {
    if (EFI_ERROR (Status))
    {
      DEBUG((EFI_D_WARN, "Failed to get DDR Current Freq"));
    }
    return Status;
  }
  AsciiPrint("DDR Current Frequency: ");
  AsciiPrint("%d MHz\n", ddr_freq);
  AsciiPrint("                                 \n");
  ddr_freq = 0;

  AsciiPrint("Set DDR to Max Nominal Frequency:%d KHz\n", pDDRFreqTbl->max_nom_ddr_freq);
  Status = pDDRGetInfoProtocol->SetMaxNominalDDRFreq(pDDRGetInfoProtocol);
  if (Status != EFI_SUCCESS)
  {
    if (EFI_ERROR (Status))
    {
      DEBUG((EFI_D_WARN, "Failed to SetMaxNominalDDRFreq"));
    }
  }
  Status = pDDRGetInfoProtocol->GetDDRFreq(pDDRGetInfoProtocol, &ddr_freq);
  if (Status != EFI_SUCCESS)
  {
    if (EFI_ERROR (Status))
    {
      DEBUG((EFI_D_WARN, "Failed to get DDR Current Freq"));
    }
    return Status;
  }
  AsciiPrint("DDR Current Frequency: ");
  AsciiPrint("%d KHz\n", (ddr_freq*1000));
  AsciiPrint("                                 \n");

  for(freq_index = 1; freq_index<pDDRFreqTbl->num_ddr_freqs; freq_index++)
  {
        if(pDDRFreqTbl->ddr_freq[freq_index].enable == TRUE)
        {
            set_ddr_freq = pDDRFreqTbl->ddr_freq[freq_index].freq_khz;
        }
        else
        {
            continue;
        }
      AsciiPrint("DDR Set Frequency                 :");
      AsciiPrint("%d MHz\n", set_ddr_freq/1000);
      Status = pDDRGetInfoProtocol->SetDDRFreq(pDDRGetInfoProtocol, set_ddr_freq);
      if (Status != EFI_SUCCESS)
      {
            if (EFI_ERROR (Status))
            {
                  DEBUG((EFI_D_WARN, "Failed to set DDR Freq"));
            }
            return Status;
      }
      idx = 0;
      while(1)
      {
            ddr_freq = 0, 
            Status = pDDRGetInfoProtocol->GetDDRFreq(pDDRGetInfoProtocol, &ddr_freq);
            if (Status != EFI_SUCCESS)
            {
                  if (EFI_ERROR (Status))
                  {
                        DEBUG((EFI_D_WARN, "Failed to get DDR Current Freq"));
                  }
                  return Status;
            }
            idx++;
            /*DDR frequency read is in the range of set DDR frequency +5 or -5 */
            if(( (ddr_freq <= ((set_ddr_freq/1000)+5)) && (ddr_freq >= ((set_ddr_freq/1000)-5)) ) || (idx == 100))
                  break;
      }
      AsciiPrint("DDR Current Frequency             :");
      AsciiPrint("%d MHz\n", ddr_freq);
      AsciiPrint("                                 \n");     
  }
  
  for(freq_index = pDDRFreqTbl->num_ddr_freqs-1; freq_index>=1; freq_index--)
  {
        if(pDDRFreqTbl->ddr_freq[freq_index].enable == TRUE)
        {
            set_ddr_freq = pDDRFreqTbl->ddr_freq[freq_index].freq_khz;
        }
        else
        {
            continue;
        }
      AsciiPrint("DDR Set Frequency                 :");
      AsciiPrint("%d MHz\n", set_ddr_freq/1000);
      Status = pDDRGetInfoProtocol->SetDDRFreq(pDDRGetInfoProtocol, set_ddr_freq);
      if (Status != EFI_SUCCESS)
      {
            if (EFI_ERROR (Status))
            {
                  DEBUG((EFI_D_WARN, "Failed to set DDR Freq"));
            }
            return Status;
      }
      idx = 0;
      while(1)
      {
            ddr_freq = 0, 
            Status = pDDRGetInfoProtocol->GetDDRFreq(pDDRGetInfoProtocol, &ddr_freq);
            if (Status != EFI_SUCCESS)
            {
                  if (EFI_ERROR (Status))
                  {
                        DEBUG((EFI_D_WARN, "Failed to get DDR Current Freq"));
                  }
                  return Status;
            }
            idx++;
            /*DDR frequency read is in the range of set DDR frequency +5 or -5 */
            if(( (ddr_freq <= ((set_ddr_freq/1000)+5)) && (ddr_freq >= ((set_ddr_freq/1000)-5)) ) || (idx == 100))
                  break;
      }
      AsciiPrint("DDR Current Frequency             :");
      AsciiPrint("%d MHz\n", ddr_freq);
      AsciiPrint("                                 \n");     
  }
  AsciiPrint("                                 \n");
  ddr_uefi_display_on();
  
  AsciiPrint("No of DDR regions             :");
  AsciiPrint("%d \n", pDDRRegionsEntry->no_of_ddr_regions);
  AsciiPrint("DDR rank0 size(MB)            :");
  AsciiPrint("0x%x \n", pDDRRegionsEntry->ddr_rank0_size);
  AsciiPrint("DDR rank1 size(MB)            :");
  AsciiPrint("0x%x \n", pDDRRegionsEntry->ddr_rank1_size);
  AsciiPrint("DDR rank0 pre-mapped address  :");
  AsciiPrint("0x%x \n", pDDRRegionsEntry->ddr_cs0_start_addr);
  AsciiPrint("DDR rank1 pre-mapped address  :");
  AsciiPrint("0x%x \n", pDDRRegionsEntry->ddr_cs1_start_addr);
  AsciiPrint("Highest Bank Bit              :");
  AsciiPrint("0x%x \n", pDDRRegionsEntry->highest_bank_bit);
  AsciiPrint("                                 \n");
  for(idx=0; idx < pDDRRegionsEntry->no_of_ddr_regions; idx++)
  {
     AsciiPrint("DDR REGION[%d] start address  :0x%lx\n", idx, pDDRRegionsEntry->ddr_region[idx].start_address);
     AsciiPrint("DDR REGION[%d] size           :0x%lx\n", idx, pDDRRegionsEntry->ddr_region[idx].size);
     AsciiPrint("DDR REGION[%d] granule size   :0x%x MB\n", idx, pDDRRegionsEntry->ddr_region[idx].granule_size);
     AsciiPrint("DDR REGION[%d] seg start index   :0x%x\n", idx, pDDRRegionsEntry->ddr_region[idx].segments_start_index);
     AsciiPrint("                                 \n");
  }

  ddr_uefi_display_off();
  AsciiPrint("SHUB Frequency Switch Information Start\n");
  AsciiPrint("Set Freq:\t\tMeasure Freq:\n");
  AsciiPrint("========\t\t======\n");
  for (freq_index = 1; freq_index <= pSHUBFreqTbl->num_shub_freqs - 1; freq_index++)
  {
    if (pSHUBFreqTbl->shub_freq[freq_index].enable == TRUE)
    {
      set_shub_freq = pSHUBFreqTbl->shub_freq[freq_index].freq_khz;
    }
    else
    {
      continue;
    }

    AsciiPrint("%d MHz\t\t ", set_shub_freq / 1000);
    Status = pDDRGetInfoProtocol->SetSHUBFreq(pDDRGetInfoProtocol, set_shub_freq);
    if (Status != EFI_SUCCESS)
    {
      if (EFI_ERROR(Status))
      {
        DEBUG((EFI_D_WARN, "Failed to set SHUB Freq"));
      }
      return Status;
    }

    idx = 0;
    while (1)
    {
      shub_freq_value = 0,
      Status = pDDRGetInfoProtocol->GetSHUBFreq(pDDRGetInfoProtocol, &shub_freq_value);
      if (Status != EFI_SUCCESS)
      {
        if (EFI_ERROR(Status))
        {
          DEBUG((EFI_D_WARN, "Failed to Measure SHUB Current Freq.\n"));
        }
        return Status;
      }
      idx++;
      if (((shub_freq_value <= ((set_shub_freq / 1000) + 5)) && (shub_freq_value >= ((set_shub_freq / 1000) - 5))) || (idx == 100))
        break;
    }
    AsciiPrint("%d MHz\n", shub_freq_value / 1000);
  }
  AsciiPrint("========\t\t======\n");
  AsciiPrint("\nSHUB Frequency Switch Information End\n\n");
  AsciiPrint("                                 \n");

  ddr_uefi_display_on();
  
  return EFI_SUCCESS;
}

/**
  Entry point for the application

  @param[in] ImageHandle    Image handle 
  @param[in] SystemTable    Pointer to the System Table
  
  @retval EFI_SUCCESS       Execution successful
  @retval other             Error occurred

**/
EFI_STATUS
EFIAPI
DDRInfoTestMain 
(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
)
{
  EFI_STATUS  Status;
  TEST_START("DDRInfoTest");

  Status = DDRInfoProtocolTest();

  TestStatus("DDRInfoTest", Status);
  TEST_STOP("DDRInfoTest");
  return EFI_SUCCESS;
}
