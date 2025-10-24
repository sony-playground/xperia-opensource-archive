/*=============================================================================

  File: dsiHostSystem.c
  
     Copyright (c) 2010-2021 Qualcomm Technologies, Inc.
     All Rights Reserved.
     Confidential and Proprietary - Qualcomm Technologies, Inc.

=============================================================================*/

/*============================================================================
*                         INCLUDE FILES
============================================================================*/
#include "dsiHostShared.h"
#include "dsiHostSystem.h"
#include "HALdsi_Phy.h"
#include "MDPLib_i.h"

/* --- DO NOT ADD HEADER FILES HERE! --- */

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------------
 * Functions
 *----------------------------------------------------------------------------*/

/* Clear memory
*/
void DSI_OSAL_MemZero(void *pBuffer, uint32 uSizeInBytes)
{
  MDP_OSAL_MEMZERO(pBuffer, uSizeInBytes);
}


/* Copy memory
*/
void DSI_OSAL_MemCpy(void *pDst, void *pSrc, uint32 uSizeInBytes)
{
  MDP_OSAL_MEMCPY(pDst, pSrc, uSizeInBytes);
}


/* Sleep/halt processor for amount of time in milliseconds
*/
void DSI_OSAL_SleepMs(uint32 ms)
{
  MDP_OSAL_DELAYMS(ms);
}


/* Sleep/halt processor for amount of time in milliseconds
*/
void DSI_OSAL_SleepUs(uint32 us)
{
  MDP_OSAL_DELAYUS(us);
}

//-------------------------------------------------------------------------------------------------
//  dsiSystem_FrequencyCalibration
//
//  @brief
//      dynamic refresh calibration
//
//  @params
//      [IN] hDevice
//          DSI device handle.
//      [IN] psDisplayConfig
//          pointer to display config
//
//  @return
//      None.
//-------------------------------------------------------------------------------------------------
DSI_StatusType dsiSystem_FrequencyCalibration(DSI_HandleType         hDevice,
                                         DSI_DisplayConfigType  *psDisplayConfig)
{
    DSI_StatusType            eStatus          = DSI_STATUS_SUCCESS;
    DSI_Device_IDType         eDeviceId        = dsiShared_DeviceHandle2Id(hDevice);
    uint32                    uBitsPerPixel    = 0;
    uint32                    uNumLanes        = psDisplayConfig->sDisplayInfo.uNumLanes;
    HAL_DSI_PhyConfigType     sDsiPhyConfig;

    /* Calculate the bits per pixel */ 
    uBitsPerPixel = dsiShared_GetBitsPerPixel(psDisplayConfig->sDisplayInfo.eColorFormat);

    /* Setup the PhyStructure */
    DSI_OSAL_MemZero(&sDsiPhyConfig, sizeof(HAL_DSI_PhyConfigType));

    sDsiPhyConfig.eDeviceId          = eDeviceId;
    sDsiPhyConfig.uBitsPerPixel      = uBitsPerPixel;
    sDsiPhyConfig.uNumOfDataLanes    = uNumLanes;
    sDsiPhyConfig.uConfigFlags       = 0;
    sDsiPhyConfig.uDesiredBitClkFreq = dsiShared_CalculateDesiredBitClk(&psDisplayConfig->sDisplayInfo, uBitsPerPixel);  /* desired DSI PLL bit clk freq in Hz */
    sDsiPhyConfig.uEscapeFreq        = psDisplayConfig->sDisplayInfo.uEscapeFreq;
    sDsiPhyConfig.pPreDefinedTimings = &psDisplayConfig->sTimingOverride;
    sDsiPhyConfig.eSSCConfig         = psDisplayConfig->sDisplayInfo.eSSCConfig;
    sDsiPhyConfig.bCPhyMode          = psDisplayConfig->sDisplayInfo.bCPhyMode;
    sDsiPhyConfig.bCalibrationMode   = TRUE;
    
    if (DSI_PLL_CONFIG_SPLIT_SOURCE == psDisplayConfig->ePLLSourceType)
    {
      sDsiPhyConfig.ePLLConfigSource = HAL_DSI_PLL_CONFIG_SPLIT_SOURCE;
    }
    else
    {
      sDsiPhyConfig.ePLLConfigSource = HAL_DSI_PLL_CONFIG_INDEPENDENT_SOURCE;
    }
    
    eStatus = dsiShared_FrequencyCalibration(&sDsiPhyConfig, psDisplayConfig);

    return eStatus;
}

/* -----------------------------------------------------------------------
**
** FUNCTION: dsiSystem_ConfigDevicePll()
**
** DESCRIPTION:
**   TBD
**
** INPUT:
**   TBD
**
** ----------------------------------------------------------------------- */
DSI_StatusType dsiSystem_ConfigDevicePll(DSI_HandleType         hDevice,
                                         DSI_DisplayConfigType  *psDisplayConfig)
{
  DSI_StatusType            eStatus          = DSI_STATUS_SUCCESS;
  DSI_Device_IDType         eDeviceId        = dsiShared_DeviceHandle2Id(hDevice);
  MDP_ExtClockResourceList *pExtClockResList = MDPGetExternalClockList();  

  // Ensure that we have a dividers table for this configuration and there is an external clock list
  if (NULL == pExtClockResList)
  {
    // No external clocks to configure
    eStatus = DSI_STATUS_SUCCESS;
  }
  else
  {
    /* Calculate clock configuration */
    HAL_DSI_PhyConfigType            sDsiPhyConfig;
    HAL_DSI_PhyConfigInfoType        sDsiPhyConfigInfo;
    MDPClockTypes                    eDSIClockId;
    MDPExternalClockEntry           *pDSIExtClock   = NULL;
    uint32                           uBitsPerPixel  = dsiShared_GetBitsPerPixel(psDisplayConfig->sDisplayInfo.eColorFormat);
    uint32                           uNumLanes      = psDisplayConfig->sDisplayInfo.uNumLanes;

    /* Setup the PhyStructure */
    DSI_OSAL_MemZero(&sDsiPhyConfig, sizeof(HAL_DSI_PhyConfigType));
    DSI_OSAL_MemZero(&sDsiPhyConfigInfo, sizeof(HAL_DSI_PhyConfigInfoType));

    /* Configure DSI PLL, PLL should be enabled prior to configuring MND to ensure a glitch free transition.
    *
    * HAL_DSI_PhySetup() returns PClk MND divider ratio for Clock Control block (CC) in the form of numerator and denominator;
    * also returned are frequencies of PLL output clocks, which can be used by upper layer to decided MND values.
    */
    sDsiPhyConfig.eDeviceId          = eDeviceId;
    sDsiPhyConfig.uBitsPerPixel      = uBitsPerPixel;
    sDsiPhyConfig.uNumOfDataLanes    = uNumLanes;
    sDsiPhyConfig.uConfigFlags       = 0;
    sDsiPhyConfig.uDesiredBitClkFreq = dsiShared_CalculateDesiredBitClk(&psDisplayConfig->sDisplayInfo, uBitsPerPixel);  /* desired DSI PLL bit clk freq in Hz */
    sDsiPhyConfig.uEscapeFreq        = psDisplayConfig->sDisplayInfo.uEscapeFreq;
    sDsiPhyConfig.pPreDefinedTimings = &psDisplayConfig->sTimingOverride;
    sDsiPhyConfig.bCPhyMode          = psDisplayConfig->sDisplayInfo.bCPhyMode;
    sDsiPhyConfig.eSSCConfig         = psDisplayConfig->sDisplayInfo.eSSCConfig;
    sDsiPhyConfig.bCalibrationMode   = FALSE;

    if (DSI_PLL_CONFIG_SPLIT_SOURCE == psDisplayConfig->ePLLSourceType)
    {
      sDsiPhyConfig.ePLLConfigSource = HAL_DSI_PLL_CONFIG_SPLIT_SOURCE;
    }
    else
    {
      sDsiPhyConfig.ePLLConfigSource = HAL_DSI_PLL_CONFIG_INDEPENDENT_SOURCE;
    }

    if (HAL_MDSS_STATUS_SUCCESS != HAL_DSI_PhyPllSetup(&sDsiPhyConfig, &sDsiPhyConfigInfo))
    {
      DSI_Log_Message(DSI_LOGLEVEL_ERROR, "DSIDriver: DSI%d PLL cannot be locked (Freq:%dHz)!\n", eDeviceId, sDsiPhyConfig.uDesiredBitClkFreq);
      eStatus = DSI_STATUS_FAILED_RESOURCE_NOT_READY;
    }
    else
    {
      // If the PLL does not lock the clock driver will wait indefinitely to change clock sources on the new source.
      // Only execute this path if the PLL has locked.
      HAL_DSI_TimingSettingType        sDsiTimingParams;

      /* Setup DSI Phy timing */
      sDsiTimingParams.eDeviceId          = eDeviceId;
      sDsiTimingParams.uBitclock          = sDsiPhyConfigInfo.uBitClkFreq;
      sDsiTimingParams.uEscapeFreq        = psDisplayConfig->sDisplayInfo.uEscapeFreq;
      sDsiTimingParams.pPreDefinedTimings = &psDisplayConfig->sTimingOverride;
      sDsiTimingParams.bCPhyMode          = psDisplayConfig->sDisplayInfo.bCPhyMode;
      sDsiTimingParams.eTimingMargin      = psDisplayConfig->sDisplayInfo.ePHYTimingMargin;
      sDsiTimingParams.uRefreshRate       = psDisplayConfig->sDisplayInfo.uRefreshRate;

      if (HAL_MDSS_STATUS_SUCCESS != HAL_DSI_PhySetupTimingParams(&sDsiTimingParams))
      {
        DSI_Log_Message(DSI_LOGLEVEL_WARN, "DSI Phy timing setup failed.\n");
      }

      // Select the correct DSI core
      if (DSI_DeviceID_0 == eDeviceId)
      {
        pDSIExtClock = (MDPExternalClockEntry*)pExtClockResList->pDSI0ExtClocks;
        eDSIClockId  = MDP_CLOCKTYPE_DSI0;
      }
      else
      {
        if (DSI_PLL_CONFIG_SPLIT_SOURCE == psDisplayConfig->ePLLSourceType)
        {
          pDSIExtClock = (MDPExternalClockEntry*)pExtClockResList->pSharedSourceExtClocks;
        }
        else
        {
          pDSIExtClock = (MDPExternalClockEntry*)pExtClockResList->pDSI1ExtClocks;
        }
        eDSIClockId  = MDP_CLOCKTYPE_DSI1;
      }

      /* Setup clock Dividers for mdss_pclk#_clk */
      if (sDsiPhyConfigInfo.uPClkDivNumerator != sDsiPhyConfigInfo.uPClkDivDenominator)
      {
        pDSIExtClock[1].uClkPLL_M  = sDsiPhyConfigInfo.uPClkDivNumerator;
        pDSIExtClock[1].uClkPLL_N  = sDsiPhyConfigInfo.uPClkDivDenominator;
        pDSIExtClock[1].uClkPLL_2D = sDsiPhyConfigInfo.uPClkDivDenominator*2; 
      }

      /* Setup clock dividers for mdss_esc#_clk, keep default of CXO if we don't want a divider */
      if (psDisplayConfig->sDisplayInfo.uEscapeDivisor > 0)
      {
        // Source from DSI PLL0  and setup the divider
        //By default it is sourced from primary source (XO). for escape clock if divisor is greater than 0 then source it from byte clock.
        //Byte clock index may be different for different platforms so that index must be filled properly in platform file by referring to MSM SWI.
        //As clk source is used so assign the secondary source value to the clk source here.
        pDSIExtClock[0].uClkSource = pDSIExtClock[0].uClkSecondarySource; 
        pDSIExtClock[0].nClkDiv    = psDisplayConfig->sDisplayInfo.uEscapeDivisor;
      }

      /* Setup MMSS_MDSS_BYTEx_INTF_DIV clk source divider */
      if (sDsiTimingParams.bCPhyMode)
      {
        // byte_intf_div clk divided by 1 for CPhy
        pDSIExtClock[4].nSourceDiv    = 1; /* divided by 1 */

      }
      else
      {
        // byte_intf_div clk divided by 2 for DPhy
        pDSIExtClock[4].nSourceDiv    = 2; /* divided by 2 */

      }

      if (MDP_STATUS_OK != MDPSetupClocks(eDSIClockId, pDSIExtClock))
      {
        DSI_Log_Message(DSI_LOGLEVEL_ERROR, "DSIDriver: DSI%d clock source cannot be configured.\n", eDeviceId);
        eStatus = DSI_STATUS_FAILED_RESOURCE_NOT_READY;
      }
      else if (MDP_STATUS_OK != HAL_DSI_PhySetProperty(eDeviceId, HAL_DSI_PHY_PROPERTYID_POST_CLK_CONFIG, NULL))
      {
        DSI_Log_Message(DSI_LOGLEVEL_ERROR, "DSIDriver: DSI%d Failed to configure post clock config.\n", eDeviceId);
        eStatus = DSI_STATUS_FAILED_RESOURCE_NOT_READY;
      }
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  dsiSystem_DisableClock
//
//  @brief
//      Vote for DSI clock off.
//
//  @params
//      [IN] hDevice
//          DSI device handle.
//
//  @return
//      None.
//-------------------------------------------------------------------------------------------------
//
DSI_StatusType dsiSystem_DisableClock(DSI_HandleType          hDevice)
{
  DSI_StatusType         eStatus        = DSI_STATUS_SUCCESS;
  DSI_Device_IDType      eDeviceID      = dsiShared_DeviceHandle2Id(hDevice);

  if( MDP_STATUS_OK != MDPDisableClocks((DSI_DeviceID_0 == eDeviceID)?MDP_CLOCKTYPE_DSI0: MDP_CLOCKTYPE_DSI1))
  {
    DSI_Log_Message(DSI_LOGLEVEL_WARN, "DSIDriver: DSI%d clocks cannot be disabled.\n" );
    eStatus = DSI_STATUS_FAILED_RESOURCE_NOT_READY;
  }

  return eStatus;
}

#ifdef __cplusplus
}
#endif
