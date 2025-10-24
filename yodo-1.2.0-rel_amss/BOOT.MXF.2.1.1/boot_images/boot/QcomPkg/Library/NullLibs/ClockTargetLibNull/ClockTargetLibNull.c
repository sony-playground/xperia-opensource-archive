/**
  Copyright (c) 2021-2022, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/16/21   ck      Added edit history and copyright
 05/02/22   rhy     Set pointer to true in Clock_IsOn function

=============================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "ClockBoot.h"
#include "Clock.h"

/*=========================================================================
                       MACRO DEFINITIONS
==========================================================================*/
#define CLK_HW_CTL_MASK 0x2
#define CLK_DCD_ENABLE  0x1
#define CLK_ENA_MASK    0x1

/*=========================================================================
      Data
==========================================================================*/


/*=========================================================================
      Function Prototypes
==========================================================================*/


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

boolean Clock_DebugInit(void)
{
  return TRUE;
}


ClockResult Clock_Init(void)
{
  return CLOCK_SUCCESS;
}


ClockResult Clock_ExitBoot(void)
{
  return CLOCK_SUCCESS;
}


boolean Clock_GetClockFrequency(ClockQueryType eBootLogClock,
                                uint32 *pnFrequencyHz)
{
  return TRUE;
}


ClockResult Clock_InitRPM( void )
{
  return CLOCK_SUCCESS;
}


boolean Clock_SetBIMCSpeed(uint32 nFreqKHz )
{
  return TRUE;
}


boolean Clock_SetQUPV3Frequency(ClockQueryType eClock,
                                uint32 nFreqHz)
{
  return TRUE;
}


uint32 Clock_SetSDCClockFrequencyExt(uint32 nFreqKHz,
                                     ClockIdType eClock)
{
  return TRUE;
}


boolean Clock_SetSDCClockFrequency(ClockQDSSLevelType ePerfLevel,
                                   ClockIdType eClock)
{
  return TRUE;
}


boolean Clock_UFSInit( ClockQDSSLevelType ePerfLevel )  
{
  return TRUE;
}


ClockResult ClockSec_Init(void)
{
  return CLOCK_SUCCESS;
}

ClockResult ClockSec_ExitBoot(void)
{
  return CLOCK_SUCCESS;
}

ClockResult Clock_Attach
(
  ClockHandle *pHandle,
  const char  *szName
)
{
  return CLOCK_SUCCESS;
}

ClockResult Clock_Detach
(
  ClockHandle hClient
)
{
  return CLOCK_SUCCESS;
}

ClockResult Clock_GetId
(
  ClockHandle  hClient,
  const char  *szName,
  ClockIdType *pId
)
{
  return CLOCK_SUCCESS;
}

ClockResult Clock_EnableEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
  return CLOCK_SUCCESS;
}

ClockResult Clock_DisableEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
  return CLOCK_SUCCESS;
}

ClockResult Clock_IsEnabled
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  bool        *pbIsEnabled
)
{
  return CLOCK_SUCCESS;
}

ClockResult Clock_IsOn
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  bool        *pbIsOn
)
{
  if(pbIsOn != NULL)
      *pbIsOn = TRUE;
  return CLOCK_SUCCESS;
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
  return CLOCK_SUCCESS;
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
  return CLOCK_SUCCESS;
}

ClockResult Clock_SetDivider
(
ClockHandle hClient,
ClockIdType ClockId,
uint32_t nDivider
)
{
 return CLOCK_SUCCESS;
}

ClockResult Clock_GetFrequency
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  uint32_t    *pnFrequencyHz
)
{
  return CLOCK_SUCCESS;
}

ClockResult Clock_MeasureFrequencyEx
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  uint32_t     nMuxSel,
  uint32_t    *pnFrequencyHz
)
{
  return CLOCK_SUCCESS;
}

ClockResult Clock_ResetBlock
(
  ClockHandle    hClient,
  ClockIdType    ClockId,
  ClockResetType eReset
)
{
  return CLOCK_SUCCESS;
}

ClockResult Clock_Reset
(
  ClockHandle    hClient,
  ClockIdType    ClockId,
  ClockResetType eReset
)
{
  return CLOCK_SUCCESS;
}
