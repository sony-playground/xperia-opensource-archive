/*============================================================================
  FILE:         DDRInfoDxe.c

  OVERVIEW:     Implementation of the DDRGetInfo EFI protocol interface

  DEPENDENCIES: None

                Copyright (c) 2017 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary,
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  when        who      what, where, why
  ----------  ---      -----------------------------------------------------------
  2020-11-21  kns      Add shub freq functions
  2018-12-18  dj       Add ddr info protocal
  2017-04-19  daisond  Initial revision.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EFIDDRGetConfig.h>
#include <Library/DDRInfoPartitionLib.h>
#include <Library/UefiLib.h>
#include <npa.h>
#include <Protocol/EFIHWIO.h>


/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*===========================================================================*/
/* EFI_GetDDRDetails */ 
/**
  @par Summary
  Gets information about the DDR

  @param[in]  This          Pointer to the EFI_DDRGETINFO_PROTOCOL instance.
  @param[out] PlatformInfo  Pointer to the DDR information

  @return
  EFI_SUCCESS        -- Function completed successfully.  \n
*/


static EFI_STATUS
EFI_GetDDRDetails(
	IN EFI_DDRGETINFO_PROTOCOL *This,
	OUT struct ddr_details_entry_info	*DdrDetails
	);

static EFI_STATUS
EFI_GetDDRFreqTable(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT struct ddr_freq_plan_entry_info   *clk_plan_tbl
   );
   
static EFI_STATUS
EFI_GetDDRFreq(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT UINT32                 *ddr_freq
   );
   
static EFI_STATUS
EFI_SetDDRFreq(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   IN UINT32                   ddr_freq
   );
   
static EFI_STATUS
EFI_GetDDRMaxEnabledFreq(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   IN UINT32                  *ddr_freq
   );

static EFI_STATUS
EFI_GetDDRMappedRegions (
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT struct ddr_regions_data_info    *DDRRegionsData
   );

static EFI_STATUS
EFI_GetDDRmiscinfoSmemData(
    IN EFI_DDRGETINFO_PROTOCOL *This,
    OUT ddr_misc_info *ddr_misc_infoSmemData); 
  
/*----------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/

/*==============================================================================

  FUNCTION      EFI_GetDDRDetails

  DESCRIPTION   See EFI_DDRGetInfo_GetDDRDetails in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_GetDDRDetails (
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT struct ddr_details_entry_info    *DdrDetails
   )
{
  EFI_STATUS	  Status;
  if (DdrDetails == NULL)
    return EFI_INVALID_PARAMETER;
  Status = GetDDRDetails(DdrDetails);

  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;
  

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

/*==============================================================================

  FUNCTION      EFI_GetDDRFreqTable

  DESCRIPTION   See EFI_DDRGetInfo_GetDDRFreqTable in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_GetDDRFreqTable(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT struct ddr_freq_plan_entry_info   *clk_plan_tbl
   )
{
  EFI_STATUS	  Status;
  if (clk_plan_tbl == NULL)
    return EFI_INVALID_PARAMETER;
  Status = GetDDRFreqTable(clk_plan_tbl);

  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

/*==============================================================================

  FUNCTION      EFI_GetDDRMaxEnabledFreq

  DESCRIPTION   See EFI_DDRGetInfo_GetDDRMaxEnabledFreq in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_GetDDRMaxEnabledFreq(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT UINT32                 *ddr_freq
   )
{
  EFI_STATUS	  Status;
  if (ddr_freq == NULL)
    return EFI_INVALID_PARAMETER;
  Status = GetDDRMaxEnabledFreq(ddr_freq);

  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;
  

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

/*==============================================================================

  FUNCTION      EFI_GetDDRFreq

  DESCRIPTION   See EFI_DDRGetInfo_GetDDRFreq in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_GetDDRFreq(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT UINT32                 *ddr_freq
   )
{
  EFI_STATUS	  Status;
  if (ddr_freq == NULL)
    return EFI_INVALID_PARAMETER;
  Status = GetDDRFreq(ddr_freq);

  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;
  

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

/*==============================================================================

  FUNCTION      EFI_SetDDRFreq

  DESCRIPTION   See EFI_DDRGetInfo_SetDDRFreq in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_SetDDRFreq(
   IN EFI_DDRGETINFO_PROTOCOL *This,
   IN UINT32                   ddr_freq
   )
{
  EFI_STATUS	  Status;
  
  Status = SetDDRFreq(ddr_freq);

  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;
  

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

/*==============================================================================

  FUNCTION      EFI_SetMaxNominalDDRFreq

  DESCRIPTION   See EFI_DDRGETINFO_SETMAXNOMINALDDRFREQ in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_SetMaxNominalDDRFreq(
   IN EFI_DDRGETINFO_PROTOCOL *This
   )
{
  EFI_STATUS	  Status;
  
  Status = SetMaxNominalDDRFreq();

  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;
  

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

/*==============================================================================

  FUNCTION      EFI_SetLowestDDRFreq

  DESCRIPTION   See EFI_DDRGETINFO_SETLOWESTDDRFREQ in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_SetLowestDDRFreq(
   IN EFI_DDRGETINFO_PROTOCOL *This
   )
{
  EFI_STATUS	  Status;
  
  Status = SetLowestDDRFreq();

  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;
  

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

/*==============================================================================

  FUNCTION      EFI_GetDDRMappedRegions

  DESCRIPTION   See EFI_GetDDRMappedRegions in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_GetDDRMappedRegions (
   IN EFI_DDRGETINFO_PROTOCOL *This,
   OUT struct ddr_regions_data_info    *DDRRegionsData
   )
{
  EFI_STATUS	  Status;
  if (DDRRegionsData == NULL)
    return EFI_INVALID_PARAMETER;
  Status = GetDDRMappedRegions(DDRRegionsData);

  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;
  

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

/*==============================================================================

  FUNCTION      EFI_GetSHUBFreqTable

  DESCRIPTION   See EFI_DDRGetInfo_GetSHUBFreqTable in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_GetSHUBFreqTable(
    IN EFI_DDRGETINFO_PROTOCOL *This,
    OUT struct shub_freq_plan_entry_info *clk_plan_tbl)
{
  EFI_STATUS Status;

  if (clk_plan_tbl == NULL)
    return EFI_INVALID_PARAMETER;

  Status = GetSHUBFreqTable(clk_plan_tbl);
  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

/*==============================================================================

  FUNCTION      EFI_SetSHUBFreq

  DESCRIPTION   See EFI_DDRGetInfo_SetSHUBFreq in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_SetSHUBFreq(
    IN EFI_DDRGETINFO_PROTOCOL *This,
    IN UINT32 shub_freq)
{
  EFI_STATUS Status;

  Status = SetSHUBFreq(shub_freq);
  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

/*==============================================================================

  FUNCTION      EFI_GetSHUBFreq

  DESCRIPTION   See EFI_DDRGetInfo_GetSHUBFreq in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_GetSHUBFreq(
    IN EFI_DDRGETINFO_PROTOCOL *This,
    OUT UINT32 *shub_freq)
{
  EFI_STATUS Status;

  if (shub_freq == NULL)
    return EFI_INVALID_PARAMETER;

  Status = GetSHUBFreq(shub_freq);
  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

/*==============================================================================

  FUNCTION      EFI_GetDDRmiscinfoSmemData

  DESCRIPTION   See EFI_GetDDRmiscinfoSmemData in Protocol/EFIDDRGetConfig.h

==============================================================================*/
EFI_STATUS
EFI_GetDDRmiscinfoSmemData(
    IN EFI_DDRGETINFO_PROTOCOL *This,
    OUT ddr_misc_info *ddr_misc_infoSmemData) 
{
  EFI_STATUS Status;

  if (ddr_misc_infoSmemData == NULL)
    return EFI_INVALID_PARAMETER;

  Status = GetDDRmiscinfoSmemData(ddr_misc_infoSmemData);
  if (Status != EFI_SUCCESS)
    return EFI_UNSUPPORTED;

#ifdef PRE_SIL
  return EFI_UNSUPPORTED;
#else
  return EFI_SUCCESS;
#endif
}

#define EFI_DDRGETINFO_PROTOCOL_REVISION_V6 0x0000000000060000
STATIC EFI_DDRGETINFO_PROTOCOL DDRGetInfoProtocol = 
{
  EFI_DDRGETINFO_PROTOCOL_REVISION_V6,
  EFI_GetDDRDetails,
  EFI_GetDDRFreqTable,
  EFI_GetDDRFreq,
  EFI_SetDDRFreq,
  EFI_GetDDRMaxEnabledFreq,
  EFI_SetMaxNominalDDRFreq,
  EFI_SetLowestDDRFreq,
  EFI_GetDDRMappedRegions,
  EFI_GetSHUBFreqTable,
  EFI_SetSHUBFreq,
  EFI_GetSHUBFreq,
  EFI_GetDDRmiscinfoSmemData,
};

/*==============================================================================

  FUNCTION      icb_arbiter_resource_avail_cb

  DESCRIPTION   Issue NPA request to set DDR frequency to nominal
                 if the Callback is called.

==============================================================================*/

static void icb_arbiter_resource_avail_cb( void *context,    //The context passed into this npa_resource_available_cb
                                    unsigned int event_type,  //The event identifier - 0 for resource created
                                    void *resource_name,      //The name of the resource to become available
                                    unsigned int rname_len )  //The length of the resource name
{
  /* This callback is called if the resource is available*/
  EFI_STATUS Status = EFI_SUCCESS;
  /*Issue the NPA request to set DDR Frequency to Max Nominal*/
  Status = EFI_SetMaxNominalDDRFreq(&DDRGetInfoProtocol);
  if(Status != EFI_SUCCESS)
  {
     DEBUG ((EFI_D_ERROR, "EFI_SetMaxNominalDDRFreq failed:%r\n", Status));
  }
}


/*==============================================================================

  FUNCTION      SetNominalDDRFreq

  DESCRIPTION   Register for npa resource callback for "icb/arbiter"

==============================================================================*/

VOID
EFIAPI
SetNominalDDRFreq (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  npa_resource_available_cb("/icb/arbiter", icb_arbiter_resource_avail_cb, NULL);
}

/*==============================================================================

  FUNCTION      SetMaxNomDDRFreq

  DESCRIPTION   Creates a notify event callback for NPA protocol

==============================================================================*/

EFI_STATUS SetMaxNomDDRFreq()
{
  EFI_EVENT NpaNotifyEvent = (EFI_EVENT)NULL;
  VOID *NpaNotifyEventReg = NULL;

  NpaNotifyEvent = EfiCreateProtocolNotifyEvent (
                          &gEfiNpaProtocolGuid,
                          TPL_CALLBACK,
                          SetNominalDDRFreq,
                          NULL,
                          &NpaNotifyEventReg
                          );

  if (NpaNotifyEvent == NULL)
    return EFI_DEVICE_ERROR;
  else
    return EFI_SUCCESS;
}

/*==============================================================================

  FUNCTION      Map_MCCC_MCCC_MSTR_Region

  DESCRIPTION   Maps the MCCC_MCCC_MSTR region using HWIO protocol

==============================================================================*/

EFI_STATUS Map_MCCC_Region()
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_HWIO_PROTOCOL         *HWIOProtocol = NULL;
  UINT8* Addr = NULL;
  
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
  return Status;
}


/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
DDRInfoEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{

   EFI_STATUS Status = EFI_SUCCESS;
   
   Status = gBS->InstallMultipleProtocolInterfaces (&ImageHandle, 
                                 &gEfiDDRGetInfoProtocolGuid, 
                                 &DDRGetInfoProtocol, 
                                 NULL, NULL);

   if (Status != EFI_SUCCESS)
    return Status;

   Status = SetMaxNomDDRFreq();
   if (Status != EFI_SUCCESS)
    return Status;

   Status = Map_MCCC_Region();
   return Status;
}

