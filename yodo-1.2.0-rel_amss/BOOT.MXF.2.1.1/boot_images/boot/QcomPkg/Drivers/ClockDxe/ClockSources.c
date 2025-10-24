/*
===========================================================================
*/
/**
  @file ClockSources.c

  Interface implementation file for the sources management of the
  clock device driver.
*/
/*
  ====================================================================

  Copyright (c) 2020 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/ClockDxe/ClockSources.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "DALDeviceId.h"
#include "ClockDriver.h"
#include "HALclk.h"
#include "ClockSWEVT.h"
#include "DDIPlatformInfo.h"
#include "QdssSWEvent.h"
#include "tracer_event_ids.h"


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_SourceNPARequest
** =========================================================================*/
/**
  Thin wrapper to make requests on an NPA-controlled source.

  @param *pSource [in] -- Pointer to a source node.
  @param  nRequest [in] -- NPA request to make.
  @param  bSuppressibleRequest [in] -- true if suppressible; false otherwise.

  @return
  None.
*/

static void Clock_SourceNPARequest
(
  ClockSourceNodeType *pSource,
  uint32_t             nRequest,
  bool                 bSuppressibleRequest
)
{
  npa_client_handle hNPA;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  CORE_VERIFY(pSource);

  if (bSuppressibleRequest)
  {
    hNPA = pSource->NPAHandleSuppressible;
  }
  else
  {
    hNPA = pSource->NPAHandle;
  }

  /*
   * If the NPA handle isn't created yet, then the resource hasn't been
   * created and our callback hasn't fired to create the client handle.
   * This requirement will be satisfied at the time of handle creation.
   */
  if (hNPA)
  {
    npa_issue_scalar_request(hNPA, nRequest);
  }

} /* END Clock_SourceNPARequest */


/* =========================================================================
**  Function : Clock_EnableSourceOutputs
** =========================================================================*/
/**
  Enables all the source outputs specified in the BSP data for this source.

  @param *pSource [in] -- Pointer to a source node.

  @return
  None.
*/

static void Clock_EnableSourceOutputs
(
  ClockSourceNodeType *pSource
)
{
  uint32_t                nConfigMask;
  HAL_clk_SourceDescType *pHALSource;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  CORE_VERIFY(pSource);

  /*-----------------------------------------------------------------------*/
  /* Return if source is stubbed on this platform.                         */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_STUBBED(pSource))
  {
    return;
  }

  pHALSource = &pSource->HALSource;
  nConfigMask = pSource->nConfigMask;

  /*-----------------------------------------------------------------------*/
  /* Configure PLL outputs.                                                */
  /*-----------------------------------------------------------------------*/

  if (nConfigMask & CLOCK_CONFIG_PLL_AUX_OUTPUT_ENABLE)
  {
    HAL_clk_ConfigSource(pHALSource, HAL_CLK_CONFIG_PLL_AUX_OUTPUT_ENABLE);
  }

  if (nConfigMask & CLOCK_CONFIG_PLL_AUX2_OUTPUT_ENABLE)
  {
    HAL_clk_ConfigSource(pHALSource, HAL_CLK_CONFIG_PLL_AUX2_OUTPUT_ENABLE);
  }

  if (nConfigMask & CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE)
  {
    HAL_clk_ConfigSource(pHALSource, HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_ENABLE);
  }

  if (nConfigMask & CLOCK_CONFIG_PLL_XO_DOUBLER_DCC)
  {
    HAL_clk_ConfigSource(pHALSource, HAL_CLK_CONFIG_XO_DOUBLER_DCC);
  }

  if (nConfigMask & CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE)
  {
    HAL_clk_ConfigSource(pHALSource, HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_ENABLE);
  }

  if (nConfigMask & CLOCK_CONFIG_PLL_ODD_OUTPUT_ENABLE)
  {
    HAL_clk_ConfigSource(pHALSource, HAL_CLK_CONFIG_PLL_ODD_OUTPUT_ENABLE);
  }

  /*
   * Always enable the main output.
   */
  HAL_clk_ConfigSource(pHALSource, HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_ENABLE);

} /* END Clock_EnableSourceOutputs */


/* =========================================================================
**  Function : Clock_SourceOn
** =========================================================================*/
/**
  Enables a source.

  This function performs the final operations required to turn on a
  clock source.  It handles deciding whether to use an NPA client request,
  a HAL source vote, or a direct HAL source enable call.

  @param *pSource [in] -- Pointer to a source node.
  @param  bSuppressibleRequest [in] -- true if this is a source request is for a suppressible clock.

  @return
  None.
*/

static void Clock_SourceOn
(
  ClockSourceNodeType *pSource,
  bool                 bSuppressibleRequest
)
{
  ClockDrvCtxt         *pDrvCtxt = Clock_GetDrvCtxt();
  ClockVRegRequestType  VRegRequest;
  bool                  bResult;
  bool                  bNeedsCal;
  rail_voltage_level    eEnableCorner, eActiveCorner;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  CORE_VERIFY(pSource);

  if (CLOCK_SOURCE_NPA_CONTROLLED(pSource))
  {
    Clock_SourceNPARequest(pSource, CLOCK_SOURCE_REQUIRED, bSuppressibleRequest);
  }
  else
  {
    if (pSource->pActiveFreqConfig == NULL)
    {
      DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
        "Cannot turn on source[%a] that hasn't been configured.",
        pSource->szName);
      return;
    }

    /*-----------------------------------------------------------------------*/
    /* Determine calibration requirements.                                   */
    /*-----------------------------------------------------------------------*/

    eActiveCorner = pSource->pActiveFreqConfig->eVRegLevel;

    bNeedsCal = !HAL_clk_IsSourceCalibrated(&pSource->HALSource);
    if (!bNeedsCal)
    {
      /*
       * Source doesn't require calibration, so the enable corner is simply
       * the active corner.
       */
      eEnableCorner = eActiveCorner;
    }
    else
    {
      if (!pSource->pCalibrationFreqConfig)
      {
        DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
          "Source[%a] requires calibration, but no calibration config.",
          pSource->szName);
        return;
      }

      /*
       * Source requires calibration, so the enable corner needs to be
       * high enough to support the calibration frequency.
       */
      eEnableCorner =
        MAX(eActiveCorner, pSource->pCalibrationFreqConfig->eVRegLevel);
    }

    /*
     * Vote for voltage required to enable PLL, which may be elevated
     * due to calibration requirements.
     */
    VRegRequest.eVRegLevel = eEnableCorner;
    VRegRequest.bSuppressible = bSuppressibleRequest;
    Clock_VoltageRequest(pSource->nRailMask, &pSource->VRegRequest, &VRegRequest);

    /*-----------------------------------------------------------------------*/
    /* Short-circuit if already enabled.                                     */
    /*-----------------------------------------------------------------------*/

    if (CLOCK_REF_COUNT(pSource, !bSuppressibleRequest))
    {
      return;
    }

    /*-----------------------------------------------------------------------*/
    /* Enable source.                                                        */
    /*-----------------------------------------------------------------------*/

    if (!CLOCK_STUBBED(pSource))
    {
      /*
       * Set calibration frequency if required. If the PLL supports
       * auto-calibration, then this will just set the values HW will use
       * when automatically calibrating during the enable below. If
       * auto-calibration is not supported, then this will actually
       * perform the calibration.
       *
       * Don't set the calibration config if the source is READ_ONLY,
       * since shared PLLs need this set during boot. Shared PLLs must either
       * not require re-calibration or must support auto-cal.
       */
      if (bNeedsCal && !CLOCK_FLAG_IS_SET(pSource, READ_ONLY))
      {
        bResult = HAL_clk_SetSourceCalConfig(&pSource->HALSource,
          &pSource->pCalibrationFreqConfig->HALConfig);
        if (bResult != true)
        {
          DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
            "Failed to calibrate source[%a].", pSource->szName);
          return;
        }
      }

      /*
       * Enable the source.
       */
      if (pSource->nConfigMask & CLOCK_CONFIG_PLL_FSM_MODE_ENABLE)
      {
        bResult = HAL_clk_EnableSourceVote(&pSource->HALSource);
        if (bResult != true)
        {
          DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
            "Unable to enable source[%a] vote", pSource->szName);
          return;
        }
      }
      else
      {
        bResult = HAL_clk_EnableSource(&pSource->HALSource,
          pSource->eDisableMode, NULL);
        if (bResult != true)
        {
          DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
            "Unable to enable source[%a]", pSource->szName);
          return;
        }
      }
    }

    /*
     * If the PLL was enabled at an elevated voltage for calibration, then
     * restore back to the active requirement.
     */
    if (eActiveCorner != eEnableCorner)
    {
      VRegRequest.eVRegLevel = eActiveCorner;
      Clock_VoltageRequest(pSource->nRailMask, &pSource->VRegRequest, &VRegRequest);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Logging.                                                              */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_FLAG_IS_SET(pSource, LOG_STATE_CHANGE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(LOG_SOURCE_STATE_CHANGE))
  {
    ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
                      "%s (Enabled: 1)", pSource->szName);
  }

  Clock_SWEvent(CLOCK_EVENT_SOURCE_STATUS, 2, &pSource->HALSource, 1);

} /* END Clock_SourceOn */


/* =========================================================================
**  Function : Clock_SourceOff
** =========================================================================*/
/**
  Disables a source.

  This function performs the final operations required to turn off a
  clock source.  It handles deciding whether to use an NPA client request,
  a HAL source vote, or a direct HAL source disable call.

  @param *pSource [in] -- Pointer to a source node.
  @param  bSuppressibleRequest [in] -- true if this is a source request is for a suppressible clock.

  @return
  None.
*/

static void Clock_SourceOff
(
  ClockSourceNodeType *pSource,
  bool                 bSuppressibleRequest
)
{
  ClockDrvCtxt         *pDrvCtxt = Clock_GetDrvCtxt();
  ClockVRegRequestType VRegRequest;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pSource)
  {
    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Disable the source using an NPA client if it exists, or HAL call      */
  /* otherwise.                                                            */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_SOURCE_NPA_CONTROLLED(pSource))
  {
    Clock_SourceNPARequest(pSource, CLOCK_SOURCE_NOT_REQUIRED, bSuppressibleRequest);
  }
  else
  {
    if(!CLOCK_STUBBED(pSource) &&
       !CLOCK_REF_COUNT(pSource, !bSuppressibleRequest))
    {
    if (pSource->nConfigMask & CLOCK_CONFIG_PLL_FSM_MODE_ENABLE)
    {
        HAL_clk_DisableSourceVote(&pSource->HALSource);
      }
    else
    {
        HAL_clk_DisableSource(&pSource->HALSource, pSource->eDisableMode, NULL);
      }
    }

    /*-----------------------------------------------------------------------*/
    /* Deassert the voltage requirement.                                     */
    /* For PLL's in standby mode:                                            */
    /*  They require no voltage vote since they operate at retention voltage.*/
    /* For PLL's in save/restore mode:                                       */
    /*  They require no voltage vote since the bias is turned off.           */
    /*-----------------------------------------------------------------------*/

    VRegRequest.eVRegLevel = RAIL_VOLTAGE_LEVEL_OFF;
    VRegRequest.bSuppressible = bSuppressibleRequest;
    Clock_VoltageRequest(pSource->nRailMask, &pSource->VRegRequest, &VRegRequest);
  }

  /* Logging */
  if (CLOCK_FLAG_IS_SET(pSource, LOG_STATE_CHANGE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(LOG_SOURCE_STATE_CHANGE))
  {
    ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
                      "%s (Enabled: 0)", pSource->szName);
  }

  /*-----------------------------------------------------------------------*/
  /* Log source disable.                                                   */
  /*-----------------------------------------------------------------------*/

  Clock_SWEvent(CLOCK_EVENT_SOURCE_STATUS, 2, &pSource->HALSource, 0);

} /* END Clock_SourceOff */


/* =========================================================================
**  Function : Clock_EnableSourceInternal
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_EnableSourceInternal
(
  ClockHandle          hClient,
  ClockSourceNodeType *pSource,
  bool                 bSuppressibleRequest
)
{
  ClockDrvCtxt            *pDrvCtxt = Clock_GetDrvCtxt();
  ClockClientRefCountType *pClientRefCount;
  ClockResult              eResult;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !pSource)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Check if source requires initial configuration before enabling.       */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_FLAG_IS_SET(pSource, INITIALIZED))
  {
    eResult = Clock_InitSource(pSource, NULL);
    if (eResult != CLOCK_SUCCESS)
    {
      return CLOCK_ERROR_INTERNAL;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Get reference count for this client.                                  */
  /*-----------------------------------------------------------------------*/

  pClientRefCount = Clock_GetClientRefCount(hClient, pSource->pClients);
  if (!pClientRefCount)
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to find client(%x) for source: %a.", hClient, pSource->szName);

    return CLOCK_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Only enable on ref count transition from 0 -> 1.                      */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_REF_COUNT(pSource, bSuppressibleRequest))
    {
      /*
       * If the source has a source, then recursively enable that.
       * If the current state is enabled for a insuppressible clock, then we
       * need to release the previously registered vote.
       */
      if (pSource->pSource != NULL)
      {
        eResult = Clock_EnableSourceInternal(pDrvCtxt->hClient,
        pSource->pSource, bSuppressibleRequest);
      if (eResult != CLOCK_SUCCESS)
        {
          return eResult;
        }
      }

      /*
     * Turn on the source.
     * This will vote for [XO, voltage] for this type of client.
       */
        Clock_SourceOn(pSource, bSuppressibleRequest);
    }

  /*-----------------------------------------------------------------------*/
  /* Increment ref count for client and source.                            */
  /*-----------------------------------------------------------------------*/

  CLOCK_REF_COUNT_INC(pClientRefCount, bSuppressibleRequest);
  CLOCK_REF_COUNT_INC(pSource, bSuppressibleRequest);

  return CLOCK_SUCCESS;

} /* END Clock_EnableSourceInternal */


/* =========================================================================
**  Function : Clock_DisableSourceInternal
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_DisableSourceInternal
(
  ClockHandle          hClient,
  ClockSourceNodeType *pSource,
  bool                 bSuppressibleRequest
)
{
  ClockDrvCtxt            *pDrvCtxt = Clock_GetDrvCtxt();
  ClockClientRefCountType *pClientRefCount;
  ClockResult              eResult;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!hClient || !pSource)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if the source should not be disabled.                   */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_FLAG_IS_SET(pSource, DO_NOT_DISABLE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(DO_NOT_DISABLE_SOURCES))
  {
    return CLOCK_SUCCESS;
    }

  /*-----------------------------------------------------------------------*/
  /* Get reference count for this client.                                  */
  /*-----------------------------------------------------------------------*/

  pClientRefCount = Clock_GetClientRefCount(hClient, pSource->pClients);
  if (!pClientRefCount)
    {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to find client(%x) for source: %a.", hClient, pSource->szName);

    return CLOCK_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if client doesn't have outstanding enable requests.     */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_REF_COUNT(pClientRefCount, bSuppressibleRequest))
  {
    return CLOCK_SUCCESS;
    }

  /*-----------------------------------------------------------------------*/
  /* Only disable on ref count transition from 1 -> 0.                     */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_REF_COUNT(pSource, bSuppressibleRequest) == 1)
      {
        /*
     * Turn off the source.
     * This will remove vote for [XO, voltage] for this type of client.
     * The source will remain on if still outstanding ref counts from
     * other client type.
         */
    Clock_SourceOff(pSource, bSuppressibleRequest);

      /*
       * If the source has a source, then recursively disable that.
       */
      if (pSource->pSource != NULL)
      {
      eResult = Clock_DisableSourceInternal(pDrvCtxt->hClient,
        pSource->pSource, bSuppressibleRequest);
      if (eResult != CLOCK_SUCCESS)
        {
          return eResult;
        }
      }

  }

  /*-----------------------------------------------------------------------*/
  /* Decrement ref count for client and source.                            */
  /*-----------------------------------------------------------------------*/

  CLOCK_REF_COUNT_DEC(pClientRefCount, bSuppressibleRequest);
  CLOCK_REF_COUNT_DEC(pSource, bSuppressibleRequest);

  return CLOCK_SUCCESS;

} /* END Clock_DisableSourceInternal */


/* =========================================================================
**  Function : Clock_ConfigSource
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_ConfigSource
(
  ClockSourceNodeType             *pSource,
  const ClockSourceFreqConfigType *pFreqConfig
)
{
  ClockDrvCtxt                    *pDrvCtxt = Clock_GetDrvCtxt();
  const ClockSourceFreqConfigType *pActiveFreqConfig;
  ClockVRegRequestType             VRegRequest;
  ClockResult                      eResult;
  bool                             bResult, bStub;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pSource || !pFreqConfig)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Make sure source is initialized.                                      */
  /*-----------------------------------------------------------------------*/

  if (!CLOCK_FLAG_IS_SET(pSource, INITIALIZED))
  {
    eResult = Clock_InitSource(pSource, pFreqConfig);
    if (eResult != CLOCK_SUCCESS)
    {
      return CLOCK_ERROR_INTERNAL;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if this config is already active.                       */
  /*-----------------------------------------------------------------------*/

  pActiveFreqConfig = pSource->pActiveFreqConfig;
  if (pFreqConfig == pActiveFreqConfig)
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Set the new frequency configuration.                                  */
  /*-----------------------------------------------------------------------*/

  bStub = CLOCK_STUBBED(pSource);

  /*
   * If source is off, then perform a normal, offline configuration.
   */
  if (CLOCK_REF_COUNT_TOTAL(pSource) == 0)
  {
    if (bStub != true)
    {
      bResult = HAL_clk_ConfigPLL(&pSource->HALSource, &pFreqConfig->HALConfig,
        HAL_CLK_SOURCE_CONFIG_MODE_NORMAL);
      if (bResult != true)
      {
        return CLOCK_ERROR_INTERNAL;
      }
    }
  }

  /*
   * If source is on, then dynamically slew from old frequency to new frequency.
   */
  else
  {
    /*
     * Verify active frequency configured to slew from.
     */
    if (pActiveFreqConfig == NULL)
    {
      return CLOCK_ERROR;
    }

    /*
     * Increase the voltage vote if the new config has a higher requirement.
     */
    if (pFreqConfig->eVRegLevel > pActiveFreqConfig->eVRegLevel)
    {
      VRegRequest.eVRegLevel = pFreqConfig->eVRegLevel;
      VRegRequest.bSuppressible = pSource->VRegRequest.bSuppressible;
      Clock_VoltageRequest(pSource->nRailMask, &pSource->VRegRequest, &VRegRequest);
    }

    /*
     * Slew to new configuration.
     */
    if (bStub != true)
    {
      bResult = HAL_clk_ConfigPLL(&pSource->HALSource, &pFreqConfig->HALConfig,
        HAL_CLK_SOURCE_CONFIG_MODE_SLEW);
      if (bResult != true)
      {
        return CLOCK_ERROR_INTERNAL;
      }
    }

    /*
     * Decrease the voltage vote if the new config has a lower requirement.
     */
    if (pFreqConfig->eVRegLevel < pActiveFreqConfig->eVRegLevel)
    {
      VRegRequest.eVRegLevel = pFreqConfig->eVRegLevel;
      VRegRequest.bSuppressible = pSource->VRegRequest.bSuppressible;
      Clock_VoltageRequest(pSource->nRailMask, &pSource->VRegRequest, &VRegRequest);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Update state.                                                         */
  /*-----------------------------------------------------------------------*/

  pSource->pActiveFreqConfig = pFreqConfig;

  /* TODO: Properly handle dynamically switching between reference sources. */
  pSource->pSource = pFreqConfig->pSource;

  /*-----------------------------------------------------------------------*/
  /* Log source config change.                                             */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_FLAG_IS_SET(pSource, LOG_FREQ_CHANGE) ||
      CLOCK_GLOBAL_FLAG_IS_SET(LOG_SOURCE_FREQ_CHANGE))
  {
    ULOG_RT_PRINTF_2(pDrvCtxt->hClockLog,
                      "%s (Freq: %lu)",
                      pSource->szName, pFreqConfig->nFreqHz);
  }

  return CLOCK_SUCCESS;

} /* END Clock_ConfigSource */


/* =========================================================================
**  Function : Clock_SourceResourceAvailableCallback
** =========================================================================*/
/**
  Callback when source NPA resource is ready.

  @param *pContext [in] -- Context pointer, the source pointer in this case.
  @param  nEventType [in] -- 0 for this callback type.
  @param  pResourceName [in] -- Pointer to resource name string.
  @param  nResourceNameLen [in] -- Length of pResourceName string.

  @return
  NULL

  @dependencies
  None.
*/

static void Clock_SourceResourceAvailableCallback
(
  void         *pContext,
  unsigned int  nEventType,
  void         *pResourceName,
  unsigned int  nResourceNameLen
)
{
  ClockSourceNodeType *pSource = pContext;
  const char          *szResource = pResourceName;

  /*
   * Multiple callbacks may be registered. Nothing to do after first
   * callback has fired.
   */
  if (pSource->NPAHandle)
  {
    return;
  }

  /*
   * Create client handles.
   */
  pSource->NPAHandle = npa_create_sync_client(szResource,
    CLOCK_NPA_CLIENT_NAME, NPA_CLIENT_REQUIRED);
  pSource->NPAHandleSuppressible = npa_create_sync_client(szResource,
    CLOCK_NPA_CLIENT_NAME, NPA_CLIENT_SUPPRESSIBLE);

  if (!pSource->NPAHandle || !pSource->NPAHandleSuppressible)
  {
    DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to create NPA handles for %a.", pSource->szName);
    return;
  }

  /*
   * Vote for current requirements.
   */
  if (CLOCK_REF_COUNT_REQ(pSource) > 0)
  {
    Clock_SourceNPARequest(pSource, CLOCK_SOURCE_REQUIRED, false);
  }
  if (CLOCK_REF_COUNT_SUPP(pSource) > 0)
  {
    Clock_SourceNPARequest(pSource, CLOCK_SOURCE_REQUIRED, true);
  }

} /* END Clock_SourceResourceAvailableCallback */


/* =========================================================================
**  Function : Clock_InitSourcesSoft
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_InitSourcesSoft
(
  void
)
{
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  ClockResult          eResult;
  ClockSourceNodeType *pSource;
  uint32_t             i;

  for (i = 0; i < pDrvCtxt->pBSP->nNumSources; i++)
  {
    pSource = pDrvCtxt->pBSP->aSources[i];

  /*
     * Create reference count structure for INTERNAL client.
   */
    eResult = Clock_InsertRefCountClient(pDrvCtxt->hClient, &pSource->pClients);
    if (eResult != CLOCK_SUCCESS)
  {
      return eResult;
  }

  /*
   * If a source is NPA-controlled, then just setup a callback for the
   * resource to become available and return.
   */
  if (CLOCK_SOURCE_NPA_CONTROLLED(pSource))
  {
    npa_resource_available_cb(
      pSource->szName,
      Clock_SourceResourceAvailableCallback,
      pSource);
    }
  }

  return CLOCK_SUCCESS;

} /* END Clock_InitSourcesSoft */


/* =========================================================================
**  Function : Clock_InitSource
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_InitSource
(
  ClockSourceNodeType             *pSource,
  const ClockSourceFreqConfigType *pSourceFreqConfig
)
{
  ClockResult eResult;
  bool        bStub;
  uint32_t    i;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pSource)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Nothing to do if source already initialized.                          */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_FLAG_IS_SET(pSource, INITIALIZED))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Detect initial settings.                                              */
  /*-----------------------------------------------------------------------*/

  /*
   * If a source doesn't have any BSP data (like for XO), then no
   * initialization to be performed.
   */
  if (pSource->aBSP == NULL)
  {
    goto done;
  }

  /*
   * Hookup the calibration frequency config if applicable.
   */
  if (pSource->pCalibrationFreqConfig != NULL)
  {
    eResult = Clock_FindSourceConfig(pSource->pCalibrationFreqConfig,
      pSource->nCalibrationFreqConfigLen, 0, CLOCK_FREQUENCY_HZ_CLOSEST,
      &pSource->pCalibrationFreqConfig);
    if (eResult != CLOCK_SUCCESS)
    {
      return eResult;
    }

    pSource->nCalibrationFreqConfigLen = 1;
  }

  /*
   * Hookup version-specific PLL settings.
   */
  if (pSource->pRegSettings)
  {
    for (i = 0; i < pSource->nRegSettingsLen; i++, pSource->pRegSettings++)
    {
      if (Clock_IsBSPSupported(&pSource->pRegSettings->HWVersion))
      {
        break;
      }
    }

    if (i == pSource->nRegSettingsLen)
    {
      return CLOCK_ERROR;
    }

    pSource->nRegSettingsLen = 1;
  }

  /*
   * If we successfully detect the configuration then don't re-initialize.
   */
  eResult = Clock_DetectSourceConfig(pSource);
  if (eResult == CLOCK_SUCCESS)
  {
    goto done;
  }

  /*
   * If no explicit source configuration supplied, then use the first
   * supported configuration.
   */
  if (!pSourceFreqConfig)
  {
    eResult = Clock_FindSourceConfig(pSource->aBSP, pSource->nBSPLen,
      0, CLOCK_FREQUENCY_HZ_AT_LEAST, &pSourceFreqConfig);
    if ((eResult != CLOCK_SUCCESS) || (pSourceFreqConfig == NULL))
    {
      return eResult;
    }
  }

  /*
   * If source is read-only, then it should already be configured by an
   * earlier SW image. Just hookup the active configuration and don't
   * touch HW.
   */
  if (CLOCK_FLAG_IS_SET(pSource, READ_ONLY))
  {
    pSource->pActiveFreqConfig = pSourceFreqConfig;
    pSource->pSource = pSourceFreqConfig->pSource;
    goto done;
  }

  /*-----------------------------------------------------------------------*/
  /* Apply the initial active config.                                      */
  /*-----------------------------------------------------------------------*/

  bStub = CLOCK_STUBBED(pSource);

  /*
   * Set static PLL register settings before enabling FSM.
   */
  if (pSource->pRegSettings && !bStub)
  {
    HAL_clk_SetSourceRegSettings(&pSource->HALSource,
      &pSource->pRegSettings->HALSettings);
  }

  /*
   * Enable the FSM before Clock_ConfigSource, since HAL_clk_ConfigPLL
   * often relies on this bit being set in the register to setup diffently
   * for FSM mode.
   */
  if (pSource->nConfigMask & CLOCK_CONFIG_PLL_FSM_MODE_ENABLE)
  {
    if (bStub != true)
    {
      HAL_clk_ConfigSource(&pSource->HALSource, HAL_CLK_CONFIG_PLL_FSM_MODE_ENABLE);
    }
  }

  /*
   * Set initial frequency configuration.
   *
   * Set initialized flag before calling Clock_ConfigSource, so it doesn't
   * call back to Clock_InitSource.
   */
  CLOCK_FLAG_SET(pSource, INITIALIZED);
  eResult = Clock_ConfigSource(pSource, pSourceFreqConfig);
  if (eResult != CLOCK_SUCCESS)
  {
    return eResult;
  }

  /*
   * Enable the required outputs.
   */
  Clock_EnableSourceOutputs(pSource);

  /*-----------------------------------------------------------------------*/
  /* Done.                                                                 */
  /*-----------------------------------------------------------------------*/

done:
  CLOCK_FLAG_SET(pSource, INITIALIZED);
  return CLOCK_SUCCESS;

} /* END Clock_InitSource */


/* =========================================================================
**  Function : Clock_FindSourceConfig
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_FindSourceConfig
(
  const ClockSourceFreqConfigType  *aBSP,
  uint32_t                          nBSPLen,
  uint32_t                          nFreqHz,
  ClockFrequencyType                eMatch,
  const ClockSourceFreqConfigType **pMatchingConfig
)
{
  uint32_t                         nAtLeastFrequency = 0xFFFFFFFF;
  const ClockSourceFreqConfigType *pAtLeastConfig = NULL;
  uint32_t                         nAtMostFrequency = 0;
  const ClockSourceFreqConfigType *pAtMostConfig = NULL;
  const ClockSourceFreqConfigType *pBSPConfig;
  uint32_t                         i;

 /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!aBSP || !pMatchingConfig)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*
   * Otherwise find config based on the nFreqHz field.
   * Loop over all configurations.
   */
  for (i = 0; i < nBSPLen; i++)
  {
    pBSPConfig = &aBSP[i];

    /* Stop if we find an exact match */
    if (pBSPConfig->nFreqHz == nFreqHz)
    {
      *pMatchingConfig = pBSPConfig;
      return CLOCK_SUCCESS;
    }

    /* Look for the lowest at-least frequency */
    if ((pBSPConfig->nFreqHz > nFreqHz) &&
        (pBSPConfig->nFreqHz < nAtLeastFrequency))
    {
      nAtLeastFrequency = pBSPConfig->nFreqHz;
      pAtLeastConfig = pBSPConfig;
    }
    /* Look for the highest at-most frequency */
    else if ((pBSPConfig->nFreqHz < nFreqHz) &&
             (pBSPConfig->nFreqHz > nAtMostFrequency))
    {
      nAtMostFrequency = pBSPConfig->nFreqHz;
      pAtMostConfig = pBSPConfig;
    }
  }

  /* Select a config based on the match criteria */
  switch (eMatch)
  {
    case CLOCK_FREQUENCY_HZ_AT_LEAST:
      if (pAtLeastConfig != NULL)
      {
        *pMatchingConfig = pAtLeastConfig;
        return CLOCK_SUCCESS;
      }
      break;

    case CLOCK_FREQUENCY_HZ_AT_MOST:
      if (pAtMostConfig != NULL)
      {
        *pMatchingConfig = pAtMostConfig;
        return CLOCK_SUCCESS;
      }
      break;

    case CLOCK_FREQUENCY_HZ_CLOSEST:
      if ((pAtLeastConfig != NULL) && (pAtMostConfig == NULL))
      {
        *pMatchingConfig = pAtLeastConfig;
        return CLOCK_SUCCESS;
      }
      else if ((pAtMostConfig != NULL) && (pAtLeastConfig == NULL))
      {
        *pMatchingConfig = pAtMostConfig;
        return CLOCK_SUCCESS;
      }
      else if ((pAtLeastConfig != NULL) && (pAtMostConfig != NULL))
      {
        /* Select the closest match, select the lowest in case of a tie */
        if ((nAtLeastFrequency - nFreqHz) < (nFreqHz - nAtMostFrequency))
        {
          *pMatchingConfig = pAtLeastConfig;
          return CLOCK_SUCCESS;
        }
        else
        {
          *pMatchingConfig = pAtMostConfig;
          return CLOCK_SUCCESS;
        }
      }
      break;

    default:
      break;
  }

  /* No match was found */
  *pMatchingConfig = NULL;

  return CLOCK_ERROR;

} /* END Clock_FindSourceConfig */


/* =========================================================================
**  Function : Clock_DetectSourceConfig
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_DetectSourceConfig
(
  ClockSourceNodeType *pSource
)
{
  HAL_clk_PLLConfigType            DetectedConfig = {0};
  const ClockSourceFreqConfigType *pFreqConfig;
  uint32_t                         i;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  if (!pSource)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if (!pSource->aBSP || pSource->pActiveFreqConfig)
  {
    return CLOCK_SUCCESS;
  }

  HAL_clk_DetectPLLConfig(&pSource->HALSource, &DetectedConfig);

  for (i = 0; i < pSource->nBSPLen; i++)
  {
    pFreqConfig = &pSource->aBSP[i];
    if (!Clock_IsBSPSupported(&pFreqConfig->HWVersion))
    {
      continue;
    }

    if (HAL_clk_IsPLLConfigEqual(&pSource->HALSource,
                                 &pFreqConfig->HALConfig, &DetectedConfig))
    {
      pSource->pActiveFreqConfig = pFreqConfig;
      pSource->pSource = pFreqConfig->pSource;
      return CLOCK_SUCCESS;
    }
  }

  return CLOCK_ERROR;

} /* END Clock_DetectDetectedConfig */
