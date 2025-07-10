/*===========================================================================
                             ClockApi.c

DESCRIPTION:
  Clock Lib for common clock interface 

Copyright (c) 2020 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                   Includes and Public Data Declarations
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------

#include <Library/Clock.h>
#include <Library/ClockImage.h>
#include <Uefi.h>
#include <Protocol/EFIClock.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>

/*=========================================================================
      Function Prototypes
==========================================================================*/
extern EFI_GUID gQcomTokenSpaceGuid;

/*=========================================================================
     Definitions
==========================================================================*/

#define CLOCK_ID_INVALID          0

//===========================================================================
//                             Function Definitions
//===========================================================================

ClockResult Clock_Attach
(
  ClockHandle *pHandle,
  const char  *szName
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_CLOCK_PROTOCOL  *pClockProtocol;
  EFI_STATUS           Status;
	
  if(pHandle == NULL || szName == NULL)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }
	
  Status = gBS->LocateProtocol(&gEfiClockProtocolGuid,
                             NULL,
                             (VOID **)&pClockProtocol);
  if(Status != EFI_SUCCESS)
  {
	pHandle = NULL;
	result = CLOCK_ERROR;
	DEBUG(( EFI_D_WARN, "%a: Clock LocateProtocol failed\r\n", __func__));
	return result;
  }
	
  *pHandle = (ClockHandle)pClockProtocol;
	
  return result;
	
}

ClockResult Clock_Detach
(
  ClockHandle hClient
)
{
	if(hClient)
	{
		hClient = 0;
	}
	return CLOCK_SUCCESS;
}

ClockResult Clock_GetId
(
  ClockHandle  hClient,
  const char  *szName,
  ClockIdType *pId
)
{
  ClockResult         result = CLOCK_SUCCESS;
  UINTN               nId;
  
	
  if(hClient == 0 || szName == NULL || pId == NULL)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }
  
  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
  
  if(EFI_SUCCESS==pHandle->GetID(pHandle, szName, &nId))
  {
    *pId =(ClockIdType)nId;
     return result;
  }

 
  *pId = CLOCK_ID_INVALID;
  return CLOCK_ERROR_NOT_FOUND;

}

ClockResult Clock_EnableEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }
	
  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient;
  
  Status = pHandle->EnableClockPowerDomain(pHandle,ClockId);
  if(Status != EFI_SUCCESS)
  {
	Status = pHandle->EnableClock(pHandle,ClockId);
	if(Status != EFI_SUCCESS)
	{
	  result = CLOCK_ERROR_NOT_SUPPORTED;
	}
  }
		
  return result;
}

ClockResult Clock_DisableEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }
	
  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
  
  Status = pHandle->DisableClockPowerDomain(pHandle,ClockId);
  if(Status != EFI_SUCCESS)
  {
	Status = pHandle->DisableClock(pHandle,ClockId);
	if(Status != EFI_SUCCESS)
	{
	  result = CLOCK_ERROR_NOT_SUPPORTED;
	}
  }
		
  return result;
}

ClockResult Clock_IsEnabled
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  bool        *pbIsEnabled
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0 || pbIsEnabled == NULL)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }
	
  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 

  Status = pHandle->IsClockEnabled(pHandle,ClockId,(BOOLEAN*)pbIsEnabled);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;
}

ClockResult Clock_IsOn
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  bool        *pbIsOn
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0 || pbIsOn == NULL)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->IsClockOn(pHandle,ClockId,(BOOLEAN*)pbIsOn);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;
}

ClockResult Clock_SetFrequencyEx
(
  ClockHandle          hClient,
  ClockIdType          ClockId,
  uint32_t             nFreq,
  ClockFrequencyType   eMatch,
  uint32_t            *pnResultFreq,
  uint32_t             nFlags
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->SetClockFreqHz(pHandle,ClockId,nFreq,(EFI_CLOCK_FREQUENCY_TYPE)eMatch,pnResultFreq);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;
}

ClockResult Clock_GetFrequency
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  uint32_t    *pnFrequencyHz
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0 || pnFrequencyHz == NULL)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->GetClockFreqHz(pHandle,ClockId,pnFrequencyHz);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;
}

ClockResult Clock_MeasureFrequencyEx
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  uint32_t     nMuxSel,
  uint32_t    *pnFrequencyHz
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0 || pnFrequencyHz == NULL)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->MeasureFreqHz(pHandle,ClockId,nMuxSel,pnFrequencyHz);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }

  return result;
}

ClockResult Clock_Query
(
  ClockHandle            hClient,
  ClockIdType            ClockId,
  ClockQueryType         eQuery,
  uint32_t               nPerfLevel,
  ClockQueryResultType  *pResult
)
{
	/* Not required on UEFI for now */
	return CLOCK_SUCCESS;
}

ClockResult Clock_ResetBlock
(
  ClockHandle    hClient,
  ClockIdType    ClockId,
  ClockResetType eReset
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->ResetClock(pHandle,ClockId,(EFI_CLOCK_RESET_TYPE)eReset);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;
}

ClockResult Clock_Reset
(
  ClockHandle    hClient,
  ClockIdType    ClockId,
  ClockResetType eReset
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->ResetClockBranch(pHandle,ClockId,(EFI_CLOCK_RESET_TYPE)eReset);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;
}


ClockResult Clock_SelectExternalSourceEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFreqHz,
  uint32_t    nSource,
  uint32_t    nDiv2x,
  uint32_t    nM,
  uint32_t    nN,
  uint32_t    n2D,
  uint32_t    nFlags
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->SelectExternalSource(pHandle,ClockId,nFreqHz,nSource,nDiv2x,nM,nN,n2D);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;
}

ClockResult Clock_Configure
(
  ClockHandle     hClient,
  ClockIdType     ClockId,
  ClockConfigType eConfig
)
{
	/* Not required on UEFI for now */
	return CLOCK_SUCCESS;
}

ClockResult Clock_SetDivider
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nDivider
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->SetClockDivider(pHandle,ClockId,nDivider);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;
}

ClockResult Clock_Invert
(
  ClockHandle hClient,
  ClockIdType ClockId,
  bool        bInvert
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->InvertClock(pHandle,ClockId,(BOOLEAN)bInvert);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;	
}

ClockResult Clock_ProcessorSleep
(
  ClockHandle        hClient,
  ClockSleepModeType eMode,
  uint32_t           nFlags
)
{
  ClockResult result = CLOCK_SUCCESS;
	
  /* No processor sleep functionality yet */
  return result;
}


ClockResult Clock_ProcessorRestore
(
  ClockHandle        hClient,
  ClockSleepModeType eMode,
  uint32_t           nFlags
)
{
  ClockResult result = CLOCK_SUCCESS;
	
  /* No processor restore functionality yet */
  return result;
}

ClockResult Clock_GetMaxPerfLevel 
(
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t   *pnPerfLevel
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->GetMaxPerfLevel(pHandle,nCPU,pnPerfLevel);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;	
}

ClockResult Clock_GetMinPerfLevel
(
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t   *pnPerfLevel
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->GetMinPerfLevel(pHandle,nCPU,pnPerfLevel);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;	
}


ClockResult Clock_GetCPUFrequencyLevels 
(
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t   *pnFrequencyLevels 
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->GetCPUFrequencyLevels(pHandle,nCPU,pnFrequencyLevels);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;	
}

ClockResult Clock_GetCPUFrequencyPlan 
(
  ClockHandle         hClient,
  uint32_t            nCPU,
  ClockFreqPlanType  *pCPUFreqPlan,
  uint32_t            nSize
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->GetCPUFrequencyPlan(pHandle,nCPU,(EFI_CLOCK_FREQ_PLAN_TYPE*)pCPUFreqPlan,nSize);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;	
}

ClockResult Clock_SetCPUFrequency 
(
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t    nFrequencyHz,
  uint32_t   *pnResultFreqHz
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->SetCPUFrequency(pHandle,nCPU,nFrequencyHz,pnResultFreqHz);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;	
}


ClockResult Clock_GetCPUFrequency 
(
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t   *pnFrequencyHz
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->GetCPUFrequency(pHandle,nCPU,pnFrequencyHz);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;	
}


ClockResult Clock_GetCpuPerfLevelFrequency 
(
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t    nPerfLevel,
  uint32_t   *pnFrequencyHz,
  uint32_t   *pnRequiredVoltage
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->GetCpuPerfLevelFrequency(pHandle,nCPU,nPerfLevel,pnFrequencyHz,pnRequiredVoltage);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;	
}



ClockResult Clock_SetCpuPerfLevel 
(
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t    nPerfLevel,
  uint32_t   *pnFrequencyHz
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->SetCpuPerfLevel(pHandle,nCPU,nPerfLevel,pnFrequencyHz);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;	
}



ClockResult Clock_GetCpuPerfLevel 
(
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t   *pnPerfLevel
)
{
  ClockResult result = CLOCK_SUCCESS;
  EFI_STATUS           Status;
	
  if(hClient == 0)
  {
	return CLOCK_ERROR_INVALID_PARAMETER;
  }

  EFI_CLOCK_PROTOCOL *pHandle = (EFI_CLOCK_PROTOCOL*)hClient; 
	
  Status = pHandle->GetCpuPerfLevel(pHandle,nCPU,pnPerfLevel);
  if(Status != EFI_SUCCESS)
  {
	result = CLOCK_ERROR;
  }
		
  return result;	
}

