/** @file DDRInfoPartitionLib.h
  
  DDR Info interface

  Copyright (c) 2017 by Qualcomm Technologies, Inc. 
  All Rights Reserved.
 
**/

/*=======================================================================
                        Edit History

when      who      what, where, why
--------  ----     ---------------------------------------------------
11/21/20  kns      Add shub freq functions
12/18/18  dj       Add ddr info protocal
04/27/17  ddk      Initital Version
========================================================================*/

#include <Uefi.h>
#include <MemRegionInfo.h>
#include <DDRDetails.h>

#define NUM_DQ_PCH 2


/**
  Get DDR details from DDR info stored in shared memory
**/

EFI_STATUS
GetDDRDetails (IN OUT struct ddr_details_entry_info *ddr_detail);

/**
  Get DDR Frequency Table from DDR info stored in shared memory
**/
EFI_STATUS
GetDDRFreqTable (IN OUT struct ddr_freq_plan_entry_info *clk_plan_tbl);

/**
  Get DDR Frequency
**/
EFI_STATUS
GetDDRFreq (IN OUT UINT32    *ddr_freq);

/**
  Get DDR Max Enabled Frequency
**/
EFI_STATUS
GetDDRMaxEnabledFreq (IN OUT UINT32    *ddr_freq);

/**
  Set DDR Frequency
**/
EFI_STATUS
SetDDRFreq (IN UINT32    ddr_freq);

/**
  Set Max nominal DDR Frequency
**/
EFI_STATUS
SetMaxNominalDDRFreq ();

/**
  Set lowest DDR Frequency
**/
EFI_STATUS
SetLowestDDRFreq ();

/**
  Get DDR regions details
**/
EFI_STATUS
GetDDRMappedRegions (IN OUT struct ddr_regions_data_info *DDRRegionsData);

/**
  Switch DDR frequency
**/
UINT32 switch_ddr_freq(UINT32 freq_khz);

/**
  Remove DDR Request Client for DDR frequency switching
**/
void deinit_ddr_clk();

/**
  Get SHUB Frequency Table from DDR info stored in shared memory
**/
EFI_STATUS
GetSHUBFreqTable(IN OUT struct shub_freq_plan_entry_info *clk_plan_tbl);

/**
  Set SHUB Frequency
**/
EFI_STATUS
SetSHUBFreq(IN UINT32 shub_freq);

/**
  Get SHUB Frequency
**/
EFI_STATUS
GetSHUBFreq(OUT UINT32 *shub_freq);

/**
  GetDDRmiscinfoSmemData
**/
EFI_STATUS
GetDDRmiscinfoSmemData (OUT ddr_misc_info *ddr_misc_infoSmemData);
