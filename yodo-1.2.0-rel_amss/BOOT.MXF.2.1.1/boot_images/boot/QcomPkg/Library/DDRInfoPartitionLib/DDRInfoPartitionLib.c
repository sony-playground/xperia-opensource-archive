/*
 * @file DDRInfoPartitionLib.c
 *
 * @brief DDRInfoPartitionLib functions
 *
 * Copyright (c) 2017 by Qualcomm Technologies, Inc. 
 * All Rights Reserved.
 *
 */
/*=======================================================================
                        Edit History

when       who       what, where, why
--------   ----      --------------------------------------------------- 
04/23/22   suragaik  updated BW calculation formula for Freq switch
11/21/20   kns       Add shub freq functions
12/18/18   dj        Add ddr info protocal
09/26/17   daisond   Calling ddr_get_max_channels to get max ddr channels
04/27/17   ddk       Initital Version
========================================================================*/
#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DDRInfoPartitionLib.h>
#include <com_dtypes.h>
#include <smem.h> 
#include <MemRegionInfo.h>
#include "ddr_drivers.h"
#include <npa.h>
#include <api/systemdrivers/icbarb.h>
#include <api/systemdrivers/busywait.h>
#include <npa_resource.h>
#include <Include/Library/Clock.h>
#include "HALbootHWIO.h"

#define GCC_MEMNOC_CLK_DEBUG HWIO_GCC_DEBUG_MUX_MUXR_MUX_SEL_GCC_MEMNOC_CLK_FVAL

npa_client_handle reqClientDDR = NULL;
ICBArb_MasterSlaveType ddrMasterSlave[] =
    {{ICBID_MASTER_APPSS_PROC, ICBID_SLAVE_EBI1}};

npa_client_handle reqClientSHUB = NULL;
ICBArb_MasterSlaveType shubMasterSlave[] =
    {{ICBID_MASTER_APPSS_PROC, ICBID_SLAVE_LLCC}};

ClockHandle gcc_clock_handle = 0;
const char *ddr_info_cname = "ddr_info";

/*==============================================================================

  FUNCTION      GetDDRDetails

  DESCRIPTION   See EFI_DDRGetInfo_GetDDRDetails in Protocol/EFIDDRGetConfig.h

==============================================================================*/

EFI_STATUS
GetDDRDetails (IN OUT struct ddr_details_entry_info *ddr_detail)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  VOID   *pDDRTable = NULL;

  if ((ddr_detail == NULL))
    return EFI_INVALID_PARAMETER;
  /* Get the DDR details table */
  pDDRTable = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
  if (pDDRTable == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_WARN, "WARNING: Unable to read DDR Info table from SMEM\n"));
    return EFI_NOT_READY;
  }
   
  memscpy((void *)ddr_detail, sizeof(ddr_details_entry), pDDRTable, sizeof(ddr_details_entry));   

  return Status;
}



/*==============================================================================

  FUNCTION      EFI_GetDDRFreqTable

  DESCRIPTION   See EFI_DDRGetInfo_GetDDRFreqTable in Protocol/EFIDDRGetConfig.h

==============================================================================*/

EFI_STATUS
GetDDRFreqTable (IN OUT struct ddr_freq_plan_entry_info   *clk_plan_tbl)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  VOID   *pDDRFreqTbl = NULL;
  VOID   *pDDRInfoBase = NULL;
  
  

  if ((clk_plan_tbl == NULL))
    return EFI_INVALID_PARAMETER;
  /* Get the DDR details table */
  pDDRInfoBase = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
  pDDRFreqTbl = (void*)&(((ddr_details_entry*)pDDRInfoBase)->ddr_freq_tbl);
  
  if (pDDRFreqTbl == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_WARN, "WARNING: Unable to read DDR Freq Plan table from SMEM\n"));
    return EFI_NOT_READY;
  }

  memscpy((void *)clk_plan_tbl, (sizeof(struct ddr_freq_plan_entry_info)), pDDRFreqTbl, (sizeof(struct ddr_freq_plan_entry_info))); 
  
  return Status;
}


/*==============================================================================

  FUNCTION      EFI_GetDDRFreq

  DESCRIPTION   See EFI_DDRGetInfo_GetDDRFreq in Protocol/EFIDDRGetConfig.h

==============================================================================*/

EFI_STATUS
GetDDRFreq (IN OUT UINT32    *ddr_freq)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  VOID   *pDDRFreqTbl = NULL;
  VOID   *pDDRInfoBase = NULL;
  

  if ((ddr_freq == NULL))
    return EFI_INVALID_PARAMETER;
  /* Get the DDR details table */
  pDDRInfoBase = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
  pDDRFreqTbl = (void*)&(((ddr_details_entry*)pDDRInfoBase)->ddr_freq_tbl);

  if (pDDRInfoBase == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_WARN, "WARNING: Unable to read DDR Info table from SMEM\n"));
    return EFI_NOT_READY;
  }

  *ddr_freq = 1000000 / *(UINT32*)(((struct ddr_freq_plan_entry_info *)pDDRFreqTbl)->clk_period_address);	
  
  return Status;
}

/*==============================================================================

  FUNCTION      EFI_GetDDRMaxEnabledFreq

  DESCRIPTION   See EFI_DDRGetInfo_GetDDRMaxEnabledFreq in Protocol/EFIDDRGetConfig.h

==============================================================================*/

EFI_STATUS
GetDDRMaxEnabledFreq (IN OUT UINT32    *ddr_freq)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  VOID   *pDDRFreqTbl = NULL;
  VOID   *pDDRInfoBase = NULL;
  UINT32  idx=0;
  

  if ((ddr_freq == NULL))
    return EFI_INVALID_PARAMETER;
  /* Get the DDR details table */
  pDDRInfoBase = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
  pDDRFreqTbl = (void*)&(((ddr_details_entry*)pDDRInfoBase)->ddr_freq_tbl);

  if (pDDRInfoBase == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_WARN, "WARNING: Unable to read DDR Info table from SMEM\n"));
    return EFI_NOT_READY;
  }

  idx = (((struct ddr_freq_plan_entry_info *)pDDRFreqTbl)->num_ddr_freqs);
  do{
       *ddr_freq =  (((struct ddr_freq_plan_entry_info *)pDDRFreqTbl)->ddr_freq[idx].freq_khz);	
  }while(((struct ddr_freq_plan_entry_info *)pDDRFreqTbl)->ddr_freq[idx--].enable != 1);
  
  return Status;
}


/**
  Remove DDR Request Client for DDR frequency switching
**/
void deinit_ddr_clk()
{
  // destroy the npa clients
  npa_complete_request(reqClientDDR);

  if (gcc_clock_handle)
    Clock_Detach(gcc_clock_handle);
}

/**
  Switch DDR frequency
**/
UINT32 switch_ddr_freq(UINT32 freq_khz)
{
  UINT32 set_freq_khz = 0;
  UINT64 bandwidth = 0;
  ICBArb_RequestType aRequest[1];
  if (reqClientDDR == NULL)
  {
    // init the npa request nodes
    reqClientDDR = npa_create_sync_client_ex("/icb/arbiter",
                                             "DDR UEFI req client",
                                             NPA_CLIENT_SUPPRESSIBLE_VECTOR,
                                             sizeof(ddrMasterSlave),
                                             &ddrMasterSlave);
  }
  ICBArb_Request3Type type3;
  aRequest[0].arbType = ICBARB_REQUEST_TYPE_3;
  /* Bandwidth is 95% of (DDR_Frequency(in MHz) * num_channels * NUM_DQ_PCH) */
  bandwidth = (((freq_khz / 1000) * 4 * 95) / 100);
  type3.uIb = bandwidth * 1000000;
  type3.uAb = 0;
  type3.uLatencyNs = 0;
  aRequest[0].arbData = (ICBArb_RequestUnionType)type3;

  npa_issue_vector_request(reqClientDDR,
                           sizeof(aRequest) / (sizeof(npa_resource_state)),
                           (npa_resource_state *)aRequest);

  return set_freq_khz;
}

/*==============================================================================

  FUNCTION      EFI_SetDDRFreq

  DESCRIPTION   See EFI_DDRGetInfo_SetDDRFreq in Protocol/EFIDDRGetConfig.h

==============================================================================*/

EFI_STATUS
SetDDRFreq (IN UINT32    ddr_freq)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  VOID       *pDDRTable = NULL;

 
  /* Get the DDR details table */
  pDDRTable = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
  if (pDDRTable == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_WARN, "WARNING: Unable to read DDR Info table from SMEM\n"));
    return EFI_NOT_READY;
  }
  
  switch_ddr_freq(ddr_freq);

  return Status;
}


/*==============================================================================

  FUNCTION      SetMaxNominalDDRFreq

  DESCRIPTION   See EFI_DDRGETINFO_SETMAXNOMINALDDRFREQ in Protocol/EFIDDRGetConfig.h

==============================================================================*/

EFI_STATUS
SetMaxNominalDDRFreq ()
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  VOID   *pDDRFreqTbl = NULL;
  VOID   *pDDRInfoBase = NULL;
  UINT32  DDRFreq=0;
  
  /* Get the DDR details table */
  pDDRInfoBase = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
  if (pDDRInfoBase == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_WARN, "WARNING: Unable to read DDR Info table from SMEM\n"));
    return EFI_NOT_READY;
  }
  
  pDDRFreqTbl = (void*)&(((ddr_details_entry*)pDDRInfoBase)->ddr_freq_tbl);
  DDRFreq = (((struct ddr_freq_plan_entry_info *)pDDRFreqTbl)->max_nom_ddr_freq);

  Status = SetDDRFreq(DDRFreq);
  if (Status != EFI_SUCCESS)
  {
    DEBUG ((EFI_D_ERROR, "WARNING: Unable to set Max nominal freq \n"));
    return Status;
  }
  return Status;
}

/*==============================================================================

  FUNCTION      SetLowestDDRFreq

  DESCRIPTION   See EFI_DDRGETINFO_SETLOWESTDDRFREQ in Protocol/EFIDDRGetConfig.h

==============================================================================*/

EFI_STATUS
SetLowestDDRFreq ()
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  VOID   *pDDRFreqTbl = NULL;
  VOID   *pDDRInfoBase = NULL;
  UINT32  DDRFreq=0;
  UINT8 idx = 1; /*lowest DDR freq index is 1 */
  
  /* Get the DDR details table */
  pDDRInfoBase = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
  if (pDDRInfoBase == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_WARN, "WARNING: Unable to read DDR Info table from SMEM\n"));
    return EFI_NOT_READY;
  }
  
  pDDRFreqTbl = (void*)&(((ddr_details_entry*)pDDRInfoBase)->ddr_freq_tbl);
  DDRFreq = (((struct ddr_freq_plan_entry_info *)pDDRFreqTbl)->ddr_freq[idx].freq_khz);

  Status = SetDDRFreq(DDRFreq);
  if (Status != EFI_SUCCESS)
  {
    DEBUG ((EFI_D_ERROR, "WARNING: Unable to set lowest DDR freq \n"));
    return Status;
  }
  return Status;
}

/*==============================================================================

  FUNCTION      GetDDRMappedRegions

  DESCRIPTION   See EFI_GetDDRMappedRegions in Protocol/EFIDDRGetConfig.h

==============================================================================*/

EFI_STATUS
GetDDRMappedRegions (IN OUT struct ddr_regions_data_info *DDRRegionsData)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  VOID   *pDDRRegionsData = NULL;

  if ((DDRRegionsData == NULL))
    return EFI_INVALID_PARAMETER;
  /* Get the DDR Info SMEM */
  pDDRRegionsData = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
  if (pDDRRegionsData == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_WARN, "WARNING: Unable to read DDR Regions Data from SMEM\n"));
    return EFI_NOT_READY;
  }
  
  /* Get DDR regions Data */
  pDDRRegionsData = (VOID*)(((UINT8 *)pDDRRegionsData) + sizeof(ddr_details_entry));
   
  memscpy((void *)DDRRegionsData, sizeof(DDR_REGIONS_ENTRY), pDDRRegionsData, sizeof(DDR_REGIONS_ENTRY));   

  return Status;
}

/*==============================================================================

  FUNCTION      EFI_GetSHUBFreqTable

  DESCRIPTION   See EFI_DDRGetInfo_GetSHUBFreqTable in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
GetSHUBFreqTable(IN OUT struct shub_freq_plan_entry_info *clk_plan_tbl)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  VOID *pSHUBFreqTbl = NULL;
  VOID *pDDRInfoBase = NULL;

  if ((clk_plan_tbl == NULL))
    return EFI_INVALID_PARAMETER;

  pDDRInfoBase = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32 *)&DDRInfoBuffSz);
  if (pDDRInfoBase == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG((EFI_D_WARN, "WARNING: Unable to read SHUB Freq Plan table from SMEM\n"));
    return EFI_NOT_READY;
  }
  pSHUBFreqTbl = (VOID *)(((UINT8 *)pDDRInfoBase) + sizeof(ddr_details_entry) + sizeof(DDR_REGIONS_ENTRY));

  memscpy((void *)clk_plan_tbl, (sizeof(struct shub_freq_plan_entry_info)), pSHUBFreqTbl, (sizeof(struct shub_freq_plan_entry_info)));

  return Status;
}


/*==============================================================================

  FUNCTION      GetDDRmiscinfoSmemData

  DESCRIPTION   See EFI_GetXbl2QuantumSmemData in Protocol/EFIDDRGetConfig.h

==============================================================================*/

EFI_STATUS
GetDDRmiscinfoSmemData (IN OUT ddr_misc_info *ddr_misc_infoSmemData)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  VOID   *pDDRmiscinfoSmemData = NULL;

  if ((ddr_misc_infoSmemData == NULL))
    return EFI_INVALID_PARAMETER;
  /* Get the DDR Info SMEM */
  pDDRmiscinfoSmemData = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32*)&DDRInfoBuffSz);
  if (pDDRmiscinfoSmemData == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG ((EFI_D_WARN, "WARNING: Unable to read data from DDRINFO SMEM\n"));
    return EFI_NOT_READY;
  }
  
  /* Get XBL to quantum smem data */
  pDDRmiscinfoSmemData = (VOID*)(((UINT8 *)pDDRmiscinfoSmemData) + DDR_MISC_INFO_SMEM_DATA_OFFSET);
   
  memscpy((void *)ddr_misc_infoSmemData, sizeof(ddr_misc_info), pDDRmiscinfoSmemData, sizeof(ddr_misc_info));   

  return Status;
}

/**
  Switch SHUB frequency
**/
UINT32 switch_shub_freq(UINT32 freq_khz)
{
  UINT64 bandwidth = 0;
  ICBArb_RequestType aRequest[1];
  ICBArb_Request3Type type3;
  aRequest[0].arbType = ICBARB_REQUEST_TYPE_3;

  type3.uAb = 0;
  type3.uLatencyNs = 0;
  bandwidth = (((freq_khz / 1000) * 16 * 95) / 100);
  type3.uIb = bandwidth * 1000000;
  aRequest[0].arbData = (ICBArb_RequestUnionType)type3;

  if (reqClientSHUB == NULL)
  {
    // init the npa request nodes
    reqClientSHUB = npa_create_sync_client_ex("/icb/arbiter",
                                              "SHUB UEFI req client",
                                              NPA_CLIENT_SUPPRESSIBLE_VECTOR,
                                              sizeof(shubMasterSlave),
                                              &shubMasterSlave);
  }

  npa_issue_vector_request(reqClientSHUB,
                           sizeof(aRequest) / (sizeof(npa_resource_state)),
                           (npa_resource_state *)aRequest);

  return freq_khz;
}

/*==============================================================================

  FUNCTION      EFI_SetSHUBFreq

  DESCRIPTION   See EFI_DDRGetInfo_SetSHUBFreq in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
SetSHUBFreq(IN UINT32 shub_freq)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 DDRInfoBuffSz = 0;
  VOID *pDDRTable = NULL;

  if (!shub_freq)
    return EFI_NOT_FOUND;

  /* Get the DDR details table */
  pDDRTable = smem_get_addr(DDRINFO_UEFI_SMEM_ID, (uint32 *)&DDRInfoBuffSz);
  if (pDDRTable == NULL)
  {
    /*NOTE: We should be here only if SMEM is not initialized (virtio, SmemNullLib)*/
    DEBUG((EFI_D_WARN, "WARNING: Unable to read DDR Info table from SMEM\n"));
    return EFI_NOT_READY;
  }

  switch_shub_freq(shub_freq);

  return Status;
}

/*==============================================================================

  FUNCTION      EFI_GetSHUBFreq

  DESCRIPTION   See EFI_DDRGetInfo_MeasureSHUBFreq in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
GetSHUBFreq(OUT UINT32 *shub_freq)
{
  ClockIdType nGccDebugMuxId = 0;
  UINT32 nMeasuredFreq = 0;
  const char *ddr_shub_debug_mux_name = "gcc";
  ClockResult Status = CLOCK_ERROR;

  if (!gcc_clock_handle)
  {
    Status = Clock_Attach(&gcc_clock_handle, ddr_info_cname);
    if (Status != CLOCK_SUCCESS)
      return EFI_NOT_FOUND;
  }

  Status = Clock_GetId(gcc_clock_handle, ddr_shub_debug_mux_name, &nGccDebugMuxId);
  if (Status != CLOCK_SUCCESS)
    return EFI_NOT_FOUND;

  Status = Clock_MeasureFrequencyEx(gcc_clock_handle, nGccDebugMuxId, GCC_MEMNOC_CLK_DEBUG, &nMeasuredFreq);
  if (Status != CLOCK_SUCCESS)
    return EFI_NOT_FOUND;

  *shub_freq = nMeasuredFreq / 1000; //khz

  return EFI_SUCCESS;
}
