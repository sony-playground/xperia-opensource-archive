/*============================================================================
  FILE:         DalVAdc.c

  OVERVIEW:     Implementation of a Physical ADC device DAL for the
                PMIC VADC peripheral.

  DEPENDENCIES: None

                Copyright (c) 2009-2016, 2018-2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/adc/devices/vadc/src/DalVAdc.c#1 $$DateTime: 2022/08/18 10:15:46 $$Author: pwbldsvc $

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2018-02-06  jjo  Enhance RUMI check.
  2018-01-31  jjo  Remove latency vote.
  2016-03-23  jjo  Add HW supported checks.
  2015-08-12  jjo  Updated for VADC refresh.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "DalVAdc.h"
#include "VAdcBsp.h"
#ifdef ADC_DIAG_LOGGING
#include "VAdcDiag.h"
#endif
#include "DDIPlatformInfo.h"
#include "VAdcDtParser.h"
#include "pm_vadc_target_config.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define VADC_SPMI_READ_NUM_RETRIES 5

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
//boolean gVAdcOverrideRumiCheck = FALSE;
boolean gVAdcOverrideRumiCheck = TRUE;

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
/*======================================================================

  FUNCTION        VAdc_ReadChannelInternal

  DESCRIPTION
      This function reads an ADC channel and returns the scaled result
      and status of the read. It is not meant for reading calibration
      channels.

  DEPENDENCIES
      None

  PARAMETERS
      pDevCtxt         [in]
      uChannel         [in]
      pAdcDeviceResult [out]

  RETURN VALUE
      DAL_SUCCESS or an error

  SIDE EFFECTS
      None

======================================================================*/
static DALResult
VAdc_ReadChannelInternal(
   VAdcDevCtxt *pDevCtxt,
   uint32 uChannel,
   AdcDeviceResultType *pAdcDeviceResult
   )
{
   const VAdcChannelConfigType *pChConfig = &pDevCtxt->pBsp->paChannels[uChannel];
   pm_vadc_channel_cfg vadc_ch_cfg;

   pm_err_flag_type result;
   uint32 uCode = 0x8000;

   vadc_ch_cfg.uChannel = pChConfig->uAdcHardwareChannel;
   vadc_ch_cfg.eCalMethod = pChConfig->eCalMethod;
   vadc_ch_cfg.eDecimationRatio = pChConfig->eDecimationRatio;
   vadc_ch_cfg.eAverageMode = pChConfig->eAverageMode;
   vadc_ch_cfg.eSettlingDelay = pChConfig->eSettlingDelay;
   vadc_ch_cfg.uAdcSID = pChConfig->uSlaveId;

   result = pm_vadc_read_adc(pDevCtxt->pmicVAdcDev,
                             &vadc_ch_cfg,
                             &uCode);
   if (result != PM_ERR_FLAG_SUCCESS)
   {
      return DAL_ERROR;
   }

   VAdcProcessConversionResult(&pChConfig->scalingFactor,
                               pChConfig->eScalingMethod,
                               pChConfig->pIntTable,
                               pChConfig->uPullUp,
                               pChConfig->nOffset,
                               pDevCtxt->pBsp->uFullScale_code,
                               pDevCtxt->pBsp->uFullScale_uV,
                               pDevCtxt->pBsp->uFullRatiometric_code,
                               uCode,
                               pAdcDeviceResult);

   VAdc_LogConversionResult(&pDevCtxt->debug,
                            pChConfig->pszName,
                            pAdcDeviceResult);

#ifdef ADC_DIAG_LOGGING
   vadc_diag_send_client_log(uChannel,
                             pAdcDeviceResult,
                             (uint32)pChConfig->eDecimationRatio);
#endif

   return DAL_SUCCESS;
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * The following functions are for DALDriver specific functionality
 * -------------------------------------------------------------------------*/
DALResult
VAdc_DriverInit(VAdcDrvCtxt *pCtxt)
{
   return DAL_SUCCESS;
}

DALResult
VAdc_DriverDeInit(VAdcDrvCtxt *pCtxt)
{
   return DAL_SUCCESS;
}

/*----------------------------------------------------------------------------
 * The following functions are declared in DalDevice Interface.
 * -------------------------------------------------------------------------*/
DALResult
VAdc_DeviceInit(VAdcClientCtxt *pCtxt)
{
   struct pm_vadc_log_inf loginf;
   VAdcDevCtxt *pDevCtxt = pCtxt->pVAdcDevCtxt;
   DALResult ret;
   pm_err_flag_type pmResult;
   static uint32 deviceId = 0;
#ifndef ADC_BOOT_DRIVER
   const VAdcAveragedChannelConfigType *pAveragedChannelCfg;
   VAdcAveragedChannelType *pAveragedChannel;
#endif
#ifndef VADC_UNIT_TEST
   const VAdcGpioChannelMappingType *pGpioChannelMapping;
   uint32 uGpioMappingIdx;
#endif
   VAdcBspType *DT_bsp;

   ret = VAdc_LogInit(&pDevCtxt->debug, pDevCtxt->DevId);
   if (ret != DAL_SUCCESS)
   {
      return ret;
   }

   const char* vadcDTPath = pm_vadc_target_get_dt_path (pDevCtxt->DevId);
   ++deviceId;

   // Device tree config loading
   if (vadcDTPath != NULL) {
      if (vadcDTPath[0] != '\0') {
         ret = DALSYS_Malloc(sizeof(VAdcBspType), (VOID**)&DT_bsp);
         if (ret != DAL_SUCCESS) 
         {
            return ret;
         }

         if (0 == vadc_read_dt_device_root(vadcDTPath, DT_bsp)) {
            /* Only use updated DT based configuration if parsing is complete */
            pDevCtxt->pBsp = DT_bsp;
         }
         else {
            DALSYS_Free(DT_bsp);
         }
      }
   }

   if (DALPLATFORMINFO_TYPE_RUMI == DalPlatformInfo_Platform() &&
       !gVAdcOverrideRumiCheck)
   {
      pm_model_type pmic_model = pm_get_pmic_model(pDevCtxt->pBsp->ucPmicDevice);

      if (pmic_model == PMIC_IS_UNKNOWN || pmic_model == PMIC_IS_INVALID)
      {
         /* PMIC is not supported on this RUMI */
         pDevCtxt->bHardwareSupported = FALSE;
         return DAL_SUCCESS;
      }
   }

   pDevCtxt->bHardwareSupported = TRUE;

#ifndef VADC_UNIT_TEST
   pmResult = pm_get_pmic_info(pDevCtxt->pBsp->ucPmicDevice, &pDevCtxt->pmicDeviceInfo);
   if (pmResult != PM_ERR_FLAG_SUCCESS)
   {
      VAdc_LogError(&pDevCtxt->debug, "VAdc - failed to get PMIC device info", TRUE);
      return DAL_ERROR;
   }
#endif

   /* Inititlize PMIC VADC driver */
   pmResult = pm_vadc_device_init(&pDevCtxt->pmicVAdcDev, pDevCtxt->pBsp);
   if (pmResult != PM_ERR_FLAG_SUCCESS)
   {
      VAdc_LogError(&pDevCtxt->debug, "VAdc - failed to initialize PMIC VAdc device", TRUE);
      return DAL_ERROR;
   }

   /* Register the logging interface */
   loginf.EOC = NULL;
   loginf.Error = NULL;
   loginf.Interrupt = NULL; 
   loginf.DumpRegisters = NULL;
   loginf.debugCtxt = (VAdcDebugInfoTypeLoc *)&pDevCtxt->debug;
#ifndef ADC_LOG_DISABLED
   loginf.EOC = (void (*)(VAdcDebugInfoTypeLoc *)) VAdc_LogEOC;
   loginf.Error = (void (*)(VAdcDebugInfoTypeLoc *, const char *, DALBOOL))VAdc_LogError;
   loginf.Interrupt = (void (*)(VAdcDebugInfoTypeLoc *))VAdc_LogInterrupt; 
   loginf.DumpRegisters = (void (*)(VAdcDebugInfoTypeLoc *, struct pm_vadc_reg_dump *))VAdc_LogDumpRegisters;
#endif
   pm_vadc_register_log_inf(pDevCtxt->pmicVAdcDev, &loginf);

#ifndef VADC_UNIT_TEST
   /* Map static GPIOs */
   for (uGpioMappingIdx = 0; uGpioMappingIdx < pDevCtxt->pBsp->uNumGpioChannelMappings; uGpioMappingIdx++)
   {
      pGpioChannelMapping = &pDevCtxt->pBsp->paGpioChannelMappings[uGpioMappingIdx];
      pm_gpio_perph_index eGpio = pGpioChannelMapping->eGpio;

      pmResult = pm_gpio_enable(pGpioChannelMapping->uPmicId, 
                                eGpio,
                                FALSE);
      if (pmResult != PM_ERR_FLAG_SUCCESS)
      {
         VAdc_LogError(&pDevCtxt->debug, "VAdc - failed to configure static GPIO", TRUE);
         return DAL_ERROR;
      }
   }
#endif

   /* Configure averaged channels */
   pDevCtxt->uTotalNumChannels = *pDevCtxt->pBsp->puNumChannels;

#ifndef ADC_BOOT_DRIVER
   if (pDevCtxt->pBsp->puNumAveragedChannels != NULL && *pDevCtxt->pBsp->puNumAveragedChannels != 0)
   {
      uint32 uChannelIdx;
      ret = DALSYS_Malloc((sizeof(VAdcAveragedChannelType) * *pDevCtxt->pBsp->puNumAveragedChannels),
                          (void **)&pDevCtxt->paAveragedChannels);
      if (ret != DAL_SUCCESS)
      {
         VAdc_LogError(&pDevCtxt->debug, "VAdc - could not allocate memory for averaged channels", TRUE);
         return ret;
      }

      for (uChannelIdx = 0; uChannelIdx < *pDevCtxt->pBsp->puNumAveragedChannels; uChannelIdx++)
      {
         pAveragedChannelCfg = &pDevCtxt->pBsp->paAveragedChannels[uChannelIdx];
         pAveragedChannel = &pDevCtxt->paAveragedChannels[uChannelIdx];

         pAveragedChannel->eState = VADC_AVERAGED_CHANNEL_STATE_UNKNOWN;

         ret = VAdc_GetChannel(pCtxt,
                               pAveragedChannelCfg->pszLowName,
                               &pAveragedChannel->uLowChannel);
         if (ret != DAL_SUCCESS)
         {
            VAdc_LogError(&pDevCtxt->debug, "VAdc - low averaged channel not found", TRUE);
            return ret;
         }

         ret = VAdc_GetChannel(pCtxt,
                               pAveragedChannelCfg->pszMedName,
                               &pAveragedChannel->uMedChannel);
         if (ret != DAL_SUCCESS)
         {
            VAdc_LogError(&pDevCtxt->debug, "VAdc - med averaged channel not found", TRUE);
            return ret;
         }

         ret = VAdc_GetChannel(pCtxt,
                               pAveragedChannelCfg->pszHighName,
                               &pAveragedChannel->uHighChannel);
         if (ret != DAL_SUCCESS)
         {
            VAdc_LogError(&pDevCtxt->debug, "VAdc - high averaged channel not found", TRUE);
            return ret;
         }
      }

      pDevCtxt->uTotalNumChannels += *pDevCtxt->pBsp->puNumAveragedChannels;
   }
#endif

   return DAL_SUCCESS;
}

DALResult
VAdc_DeviceDeInit(VAdcClientCtxt *pCtxt)
{
   /* ADC is marked as static - deinit is never called */
   return DAL_SUCCESS;
}

DALResult
VAdc_Open(
   VAdcClientCtxt *pCtxt,
   uint32 dwaccessMode
   )
{
   return DAL_SUCCESS;
}

DALResult
VAdc_Close(VAdcClientCtxt *pCtxt)
{
   return DAL_SUCCESS;
}

/*----------------------------------------------------------------------------
 * The following functions are extended in DalAdcDevice Interface.
 *
 * These functions are documented in DDIAdcDevice.h
 * -------------------------------------------------------------------------*/
DALResult
VAdc_SetDeviceIndex(
   VAdcClientCtxt *pCtxt,
   uint32 uDeviceIndex
   )
{
   VAdcDevCtxt *pDevCtxt = pCtxt->pVAdcDevCtxt;

   pDevCtxt->uDeviceIndex = uDeviceIndex;

   return DAL_SUCCESS;
}

DALResult
VAdc_GetDeviceProperties(
   VAdcClientCtxt *pCtxt,
   AdcDeviceDevicePropertiesType *pAdcDeviceProp
   )
{
   VAdcDevCtxt *pDevCtxt = pCtxt->pVAdcDevCtxt;

   if (pDevCtxt->bHardwareSupported)
   {
      pAdcDeviceProp->uNumChannels = pDevCtxt->uTotalNumChannels;
   }
   else
   {
      pAdcDeviceProp->uNumChannels = 0;
   }

   pAdcDeviceProp->uNumMeas = 0;

   return DAL_SUCCESS;
}

DALResult
VAdc_GetChannel(
   VAdcClientCtxt *pCtxt,
   const char *pszChannelName,
   uint32 *puChannelIdx
   )
{
   VAdcDevCtxt *pDevCtxt = pCtxt->pVAdcDevCtxt;
   const char *pszCurrentChannelName;
   uint32 uNumChannels;
   uint32 uChannel;

   if (!pDevCtxt->bHardwareSupported)
   {
      return DAL_ERROR;
   }

   uNumChannels = *pDevCtxt->pBsp->puNumChannels;

   for (uChannel = 0; uChannel < uNumChannels; uChannel++)
   {
      pszCurrentChannelName = pDevCtxt->pBsp->paChannels[uChannel].pszName;

      if (strcmp(pszChannelName, pszCurrentChannelName) == 0)
      {
         *puChannelIdx = uChannel;
         return DAL_SUCCESS;
      }
   }

#ifndef ADC_BOOT_DRIVER
   if (pDevCtxt->pBsp->puNumAveragedChannels != NULL)
   {
      for (uChannel = 0; uChannel < *pDevCtxt->pBsp->puNumAveragedChannels; uChannel++)
      {
         pszCurrentChannelName = pDevCtxt->pBsp->paAveragedChannels[uChannel].pszName;

         if (strcmp(pszChannelName, pszCurrentChannelName) == 0)
         {
            *puChannelIdx = uChannel + uNumChannels;
            return DAL_SUCCESS;
         }
      }
   }
#endif

   return DAL_ERROR;
}

DALResult
VAdc_ReadChannel(
   VAdcClientCtxt *pCtxt,
   uint32 uChannelIdx,
   AdcDeviceResultType *pAdcDeviceResult
   )
{
   VAdcDevCtxt *pDevCtxt = pCtxt->pVAdcDevCtxt;
   DALResult result;
#ifndef ADC_BOOT_DRIVER
   const VAdcAveragedChannelConfigType *pAveragedChannelCfg;
   VAdcAveragedChannelType *pAveragedChannel;
   AdcDeviceResultType lowResult;
   AdcDeviceResultType medResult;
   AdcDeviceResultType highResult;
#endif

   pAdcDeviceResult->eStatus = ADC_DEVICE_RESULT_INVALID;

   if (!pDevCtxt->bHardwareSupported)
   {
      return DAL_ERROR;
   }

   if (uChannelIdx >= pDevCtxt->uTotalNumChannels)
   {
      pAdcDeviceResult->eStatus = ADC_DEVICE_RESULT_INVALID_CHANNEL;
      return DAL_ERROR;
   }

   VAdc_LogConversionRequest(&pDevCtxt->debug, uChannelIdx);

#ifndef ADC_BOOT_DRIVER
   if (uChannelIdx >= *pDevCtxt->pBsp->puNumChannels)
   {
      /* Averaged channel reading */
      pAveragedChannelCfg = &pDevCtxt->pBsp->paAveragedChannels[uChannelIdx - *pDevCtxt->pBsp->puNumChannels];
      pAveragedChannel = &pDevCtxt->paAveragedChannels[uChannelIdx - *pDevCtxt->pBsp->puNumChannels];

      /* The medium channel is always read first. Decisions about when to transition
       * need to be made with the same channel. Otherwise, jumps can happen, as well
       * as getting different values going from low-to-high versus high-to-low */
      result = VAdc_ReadChannelInternal(pDevCtxt, pAveragedChannel->uMedChannel, &medResult);
      if (result != DAL_SUCCESS || medResult.eStatus != ADC_DEVICE_RESULT_VALID)
      {
         return DAL_ERROR;
      }

      if (medResult.nPhysical > pAveragedChannelCfg->nHighToMed)
      {
         result = VAdc_ReadChannelInternal(pDevCtxt, pAveragedChannel->uHighChannel, &highResult);
         if (result != DAL_SUCCESS || highResult.eStatus != ADC_DEVICE_RESULT_VALID)
         {
            return result;
         }

         if (medResult.nPhysical < pAveragedChannelCfg->nMedToHigh)
         {
            pAveragedChannel->eState = VADC_AVERAGED_CHANNEL_STATE_MED_HIGH;
            VAdcBlendResult(medResult.nPhysical,
                            &medResult,
                            pAveragedChannelCfg->nHighToMed,
                            &highResult,
                            pAveragedChannelCfg->nMedToHigh,
                            pAdcDeviceResult);

            VAdc_LogConversionResult(&pDevCtxt->debug,
                                     pAveragedChannelCfg->pszName,
                                     pAdcDeviceResult);
         }
         else
         {
            pAveragedChannel->eState = VADC_AVERAGED_CHANNEL_STATE_HIGH;
            *pAdcDeviceResult = highResult;
         }
      }
      else if (medResult.nPhysical < pAveragedChannelCfg->nLowToMed)
      {
         result = VAdc_ReadChannelInternal(pDevCtxt, pAveragedChannel->uLowChannel, &lowResult);
         if (result != DAL_SUCCESS || lowResult.eStatus != ADC_DEVICE_RESULT_VALID)
         {
            return result;
         }

         if (medResult.nPhysical > pAveragedChannelCfg->nMedToLow)
         {
            pAveragedChannel->eState = VADC_AVERAGED_CHANNEL_STATE_LOW_MED;
            VAdcBlendResult(medResult.nPhysical,
                            &lowResult,
                            pAveragedChannelCfg->nMedToLow,
                            &medResult,
                            pAveragedChannelCfg->nLowToMed,
                            pAdcDeviceResult);

            VAdc_LogConversionResult(&pDevCtxt->debug,
                                     pAveragedChannelCfg->pszName,
                                     pAdcDeviceResult);
         }
         else
         {
            pAveragedChannel->eState = VADC_AVERAGED_CHANNEL_STATE_LOW;
            *pAdcDeviceResult = lowResult;
         }
      }
      else
      {
         pAveragedChannel->eState = VADC_AVERAGED_CHANNEL_STATE_MED;
         *pAdcDeviceResult = medResult;
      }
   }
   else
   {
#endif
      /* Normal channel reading */
      result = VAdc_ReadChannelInternal(pDevCtxt, uChannelIdx, pAdcDeviceResult);
      if (result != DAL_SUCCESS)
      {
         return result;
      }
#ifndef ADC_BOOT_DRIVER
   }
#endif

   return result;
}

DALResult
VAdc_RecalibrateChannel(
   VAdcClientCtxt *pCtxt,
   uint32 uChannelIdx,
   AdcDeviceRecalibrateResultType *pAdcDeviceRecalibrateResult
   )
{
   VAdcDevCtxt *pDevCtxt = pCtxt->pVAdcDevCtxt;

   pAdcDeviceRecalibrateResult->eStatus = ADC_DEVICE_RESULT_INVALID;

   if (!pDevCtxt->bHardwareSupported)
   {
      return DAL_ERROR;
   }

   if (uChannelIdx >= pDevCtxt->uTotalNumChannels)
   {
      pAdcDeviceRecalibrateResult->eStatus = ADC_DEVICE_RESULT_INVALID_CHANNEL;
      return DAL_ERROR;
   }

   /* For this PMIC design, calibration is taken care of automatically
      by the hardware so just return the scaling values */
   pAdcDeviceRecalibrateResult->eStatus = ADC_DEVICE_RESULT_VALID;
   pAdcDeviceRecalibrateResult->nPhysical1_uV = 0;
   pAdcDeviceRecalibrateResult->nPhysical2_uV = pDevCtxt->pBsp->uFullScale_uV;
   pAdcDeviceRecalibrateResult->uCode1 = 0;
   pAdcDeviceRecalibrateResult->uCode2 = pDevCtxt->pBsp->uFullScale_code;

   return DAL_SUCCESS;
}

DALResult
VAdc_ProcessConversionResult(
   VAdcClientCtxt *pCtxt,
   uint32 uChannelIdx,
   uint32 uAdcCode,
   AdcDeviceResultType *pAdcDeviceResult
   )
{
   const VAdcChannelConfigType *pChConfig;
   VAdcDevCtxt *pDevCtxt = pCtxt->pVAdcDevCtxt;

   pAdcDeviceResult->eStatus = ADC_DEVICE_RESULT_INVALID;

   if (!pDevCtxt->bHardwareSupported)
   {
      return DAL_ERROR;
   }

   if (uChannelIdx >= pDevCtxt->uTotalNumChannels)
   {
      pAdcDeviceResult->eStatus = ADC_DEVICE_RESULT_INVALID_CHANNEL;
      return DAL_ERROR;
   }

   pChConfig = &pDevCtxt->pBsp->paChannels[uChannelIdx];

   VAdcProcessConversionResult(&pChConfig->scalingFactor,
                               pChConfig->eScalingMethod,
                               pChConfig->pIntTable,
                               pChConfig->uPullUp,
                               pChConfig->nOffset,
                               pDevCtxt->pBsp->uFullScale_code,
                               pDevCtxt->pBsp->uFullScale_uV,
                               pDevCtxt->pBsp->uFullRatiometric_code,
                               uAdcCode,
                               pAdcDeviceResult);

   return DAL_SUCCESS;
}

DALResult
VAdc_ProcessConversionResultInverse(
   VAdcClientCtxt *pCtxt,
   uint32 uChannelIdx,
   int32 nPhysical,
   AdcDeviceResultType *pAdcDeviceResult
   )
{
   const VAdcChannelConfigType *pChConfig;
   VAdcDevCtxt *pDevCtxt = pCtxt->pVAdcDevCtxt;

   pAdcDeviceResult->eStatus = ADC_DEVICE_RESULT_INVALID;

   if (!pDevCtxt->bHardwareSupported)
   {
      return DAL_ERROR;
   }

   if (uChannelIdx >= pDevCtxt->uTotalNumChannels)
   {
      pAdcDeviceResult->eStatus = ADC_DEVICE_RESULT_INVALID_CHANNEL;
      return DAL_ERROR;
   }

   pChConfig = &pDevCtxt->pBsp->paChannels[uChannelIdx];

   VAdcProcessConversionResultInverse(&pChConfig->scalingFactor,
                                      pChConfig->eScalingMethod,
                                      pChConfig->pIntTable,
                                      pChConfig->uPullUp,
                                      pChConfig->nOffset,
                                      pDevCtxt->pBsp->uFullScale_code,
                                      pDevCtxt->pBsp->uFullScale_uV,
                                      pDevCtxt->pBsp->uFullRatiometric_code,
                                      nPhysical,
                                      pAdcDeviceResult);

   return DAL_SUCCESS;
}

