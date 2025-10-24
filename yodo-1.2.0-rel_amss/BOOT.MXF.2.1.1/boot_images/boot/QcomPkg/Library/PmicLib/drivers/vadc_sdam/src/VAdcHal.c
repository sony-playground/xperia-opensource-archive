/*============================================================================
  FILE:         VAdcHal.c

  OVERVIEW:     Implementation of device HAL for VADC

  DEPENDENCIES: None

                Copyright (c) 2012, 2014-2015, 2017-2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/vadc_sdam/src/VAdcHal.c#2 $$DateTime: 2022/09/06 16:40:40 $$Author: pwbldsvc $

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2022-01-11  ha   Update for ADC PMIC 5 Gen 3
  2019-09-19  rh   Decouple RegDump function from the VAdcLog
  2015-08-12  jjo  Updated for VADC refresh.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "VAdcHal.h"
#include "AdcHalPmio.h"
#include "pm_pmio.h"
#include "pm_comm.h"
#include "busywait.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define ADC_SPMI_ADDR(perph, reg)      ((((perph) << 8) & 0xff00) | ((reg) & 0xff))
#define ARRAY_LENGTH(a)                (sizeof(a) / sizeof((a)[0]))
#define VADC_SPMI_READ_NUM_RETRIES     5
#define VADC_HAL_NUM_REGISTERS_TO_DUMP 17
#define ADC_HS_STS_READY_VAL           0x1

/* Use RTOS busywait to pause thread until HS sts is met 
 * and minimize SPMI traffic */
#define ADC_SDAM_HS_POLL_TIME_MAX_US         15000  /* 15 mS */
#define ADC_SDAM_HS_CLR_STS_POLL_TIME_MAX_US 10000  /* 10 mS */
#define ADC_SDAM_HS_POLL_TIME_ITR_US         150    /* 100 uS */

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/
static VAdcHalRegType g_aVAdcRegDump[VADC_HAL_NUM_REGISTERS_TO_DUMP];
static const uint8 gaucRegDumpAddresses[VADC_HAL_NUM_REGISTERS_TO_DUMP] =
{
   PMIO_ADDR(HS),
   PMIO_ADDR(STATUS1),
   PMIO_ADDR(INT_RT_STS),
   PMIO_ADDR(INT_LATCHED_STS),
   PMIO_ADDR(INT_PENDING_STS),
   PMIO_ADDR(EOC_STS),
   PMIO_ADDR(SID),
   PMIO_ADDR(PERPH_CH),
   PMIO_ADDR(ADC_DIG_PARAM),
   PMIO_ADDR(FAST_AVG),
   PMIO_ADDR(ADC_CH_SEL_CTL),
   PMIO_ADDR(DELAY_CTL),
   PMIO_ADDR(CH_0_DATA0),
   PMIO_ADDR(CH_0_DATA1),
   PMIO_ADDR(STATUS2),
   PMIO_ADDR(STATUS3),
   PMIO_ADDR(PBS_TRIG_SET),
};

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
/*======================================================================

  FUNCTION        VAdc_ReadBytes

  DESCRIPTION     This function reads from the VAdc peripheral

  DEPENDENCIES    None

  PARAMETERS
      pCtxt            [in]  pointer to the HAL interface context
      uOffset          [in]  the starting address
      pucData          [out] the bytes read
      uLen             [in]  the number of bytes to read

  RETURN VALUE    PM_ERR_FLAG_SUCCESS or an error code

  SIDE EFFECTS    None

======================================================================*/
static pm_err_flag_type
VAdc_ReadBytes(
   VAdcHalInterfaceType *piVAdcHal,
   uint32 uOffset,
   uint8 *pucData,
   uint32 uLen
   )
{
   pm_err_flag_type result;
   uint32 i;

   for (i = 0; i < VADC_SPMI_READ_NUM_RETRIES; i++)
   {
      result = pm_comm_read_byte_array_ex(piVAdcHal->spmi_bus_id,
                                          piVAdcHal->spmi_slave_id,
                                          ADC_SPMI_ADDR(piVAdcHal->spmi_peripheral_id, uOffset),
                                          uLen,
                                          pucData);
      if (result != PM_ERR_FLAG_SUCCESS)
      {
         continue;
      }

      return result;
   }

   return result;
}

/*======================================================================

  FUNCTION        VAdc_WriteBytes

  DESCRIPTION     This function writes to the VAdc peripheral

  DEPENDENCIES    None

  PARAMETERS
      pCtxt            [in] pointer to the HAL interface context
      uOffset          [in] the starting address
      pucData          [in] the bytes to write
      uLen             [in] the number of bytes to write

  RETURN VALUE    PM_ERR_FLAG_SUCCESS or an error code

  SIDE EFFECTS    None

======================================================================*/
static pm_err_flag_type
VAdc_WriteBytes(
   VAdcHalInterfaceType *piVAdcHal,
   uint32 uOffset,
   uint8 *pucData,
   uint32 uLen
   )
{
   return pm_comm_write_byte_array_ex(piVAdcHal->spmi_bus_id,
                                      piVAdcHal->spmi_slave_id,
                                      ADC_SPMI_ADDR(piVAdcHal->spmi_peripheral_id, uOffset),
                                      uLen,
                                      pucData);

}

static uint32 VAdcHalGetSettlingDelayUs(VAdcSettlingDelay eSettlingDelay)
{
   switch (eSettlingDelay)
   {
      case VADC_SETTLING_DELAY_100_US:
         return 100;
      case VADC_SETTLING_DELAY_200_US:
         return 200;
      case VADC_SETTLING_DELAY_300_US:
         return 300;
      case VADC_SETTLING_DELAY_400_US:
         return 400;
      case VADC_SETTLING_DELAY_500_US:
         return 500;
      case VADC_SETTLING_DELAY_600_US:
         return 600;
      case VADC_SETTLING_DELAY_700_US:
         return 700;
      case VADC_SETTLING_DELAY_800_US:
      case VADC_SETTLING_DELAY_900_US:
      case VADC_SETTLING_DELAY_1_MS:
         return 1000;
      case VADC_SETTLING_DELAY_2_MS:
         return 2000;
      case VADC_SETTLING_DELAY_4_MS:
         return 4000;
      case VADC_SETTLING_DELAY_6_MS:
      case VADC_SETTLING_DELAY_8_MS:
         return 8000;
      case VADC_SETTLING_DELAY_10_MS:
      case VADC_SETTLING_DELAY_16_MS:
         return 16000;
      case VADC_SETTLING_DELAY_32_MS:
         return 32000;
      case VADC_SETTLING_DELAY_64_MS:
         return 64000;
      case VADC_SETTLING_DELAY_128_MS:
         return 128000;
      default:
         return 50;
   }
}

static uint32 VAdcHalGetSampleTimeUs(VAdcDecimationRatioType eDecimationRatio)
{
   /*
    * These sample times are for PMIC5 with CONV_MODE == FULL_SINC2 and
    * DIG_BOOST_EN == 1
    */
   switch (eDecimationRatio)
   {
      case VADC_DECIMATION_RATIO_256:
         return 142;
      case VADC_DECIMATION_RATIO_512:
         return 283;
      case VADC_DECIMATION_RATIO_1024:
         return 567;
      default:
         return 567;
   }
}

static uint32 VAdcHalGetNumAverages(VAdcAverageModeType eAveragingMode)
{
   switch (eAveragingMode)
   {
      case VADC_AVERAGE_2_SAMPLES:
         return 2;
      case VADC_AVERAGE_4_SAMPLES:
         return 4;
      case VADC_AVERAGE_8_SAMPLES:
         return 8;
      case VADC_AVERAGE_16_SAMPLES:
         return 16;
      default:
         return 1;
   }
}

static uint32 VAdcHalGetConversionTime(VAdcConversionParametersType *pParams)
{
   uint32 uSettlingDelay_us;
   uint32 uSampleTime_us;
   uint32 uNumAverages;

   uSettlingDelay_us = VAdcHalGetSettlingDelayUs(pParams->eSettlingDelay);
   uSampleTime_us = VAdcHalGetSampleTimeUs(pParams->eDecimationRatio);
   uNumAverages = VAdcHalGetNumAverages(pParams->eAverageMode);

   /*
    * For fast averaging, only the first sample takes the full sample time.
    * Remaining samples take half the time.
    */
   return uSettlingDelay_us + uSampleTime_us + ((uSampleTime_us * (uNumAverages - 1)) / 2);
}

static pm_err_flag_type VAdcHalTriggerPBS (VAdcHalInterfaceType* piVAdcHal)
{
   uint8 aucData[1] = {1};

   return VAdc_WriteBytes (piVAdcHal, 
                           PMIO_ADDR(PBS_TRIG_SET), 
                           aucData, 
                           1);

}

static void VAdcHalImageHSPollTimer (uint32 poll_time_us)
{
   return busywait(poll_time_us);
}

static pm_err_flag_type VAdcHalGetHSStatus (VAdcHalInterfaceType* piVAdcHal,
                                            uint32 poll_time_max_us, 
                                            boolean clr_req)
{
   pm_err_flag_type result;

   uint32           poll_time_us = 0;
   uint8               stData[2] = {0};

   while (poll_time_us < poll_time_max_us)
   {
      VAdcHalImageHSPollTimer(ADC_SDAM_HS_POLL_TIME_ITR_US);
      
      result = VAdc_ReadBytes(piVAdcHal, 
                              PMIO_ADDR(HS), 
                              &stData[0], 
                              1);

      result |= VAdc_ReadBytes(piVAdcHal, 
                               PMIO_ADDR(PBS_TRIG_SET), 
                               &stData[1], 
                               1);

      if (result != PM_ERR_FLAG_SUCCESS)
      {
         return result;
      }

      boolean hs_sts = (stData[0] == ADC_HS_STS_READY_VAL);

      /* Cap polling for EOC_CLR to 1mS MAX and keep HS status READY as success
       * criteria. 
       */
      if (clr_req)
      {
         if (hs_sts) 
         {
            /* Wait for another 100uS before returning in case of clear 
             * EOC sts. This is to ensure PBS_TRIG_SET will eventually get
             * cleared. We dont want to return ERROR status to client sw in 
             * EOC_CLR stage.  
             */
            VAdcHalImageHSPollTimer(ADC_SDAM_HS_POLL_TIME_ITR_US);
            return PM_ERR_FLAG_SUCCESS;
         }
      }

      if ((hs_sts) && 
          (!stData[1]))
      {
         return PM_ERR_FLAG_SUCCESS;
      }
      
      poll_time_us += ADC_SDAM_HS_POLL_TIME_ITR_US;
   }

   return PM_ERR_FLAG_FAILURE;
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
pm_err_flag_type VAdcHalGetRevisionInfo(VAdcHalInterfaceType *piVAdcHal)
{
	/* SDAM version of ADC interface does not support revision info */
   piVAdcHal->revisionInfo.usDigitalRev = 0;
   piVAdcHal->revisionInfo.ucType = 0;
   piVAdcHal->revisionInfo.ucSubType = 0;
   return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type VAdcHalClearEoc(VAdcHalInterfaceType *piVAdcHal, uint8 uChId)
{
   pm_err_flag_type result;
   uint8 aucData[1] = {(1 << uChId)};

   /* Check HS status is READY and PBS_TRIG_SET is cleared */
   result = VAdcHalGetHSStatus(piVAdcHal, ADC_SDAM_HS_CLR_STS_POLL_TIME_MAX_US, TRUE);

   if (result)
   {
      return result;
   }

   /* Clear EOC */
   result = VAdc_WriteBytes (piVAdcHal,
                             PMIO_ADDR(EOC_CLR),
                             aucData,
                             1);

   if (result != PM_ERR_FLAG_SUCCESS)
   {
      return result;
   }

   /* Enusre PERIPH_CH is 0 */
   aucData[0] = 0;
   result = VAdc_WriteBytes (piVAdcHal,
                             PMIO_ADDR(PERPH_CH),
                             aucData,
                             1);

   if (result != PM_ERR_FLAG_SUCCESS)
   {
      return result;
   }

   /* Trigger PBS to indicate ADC_PBS of EOC clear */
   return VAdcHalTriggerPBS (piVAdcHal);
}

pm_err_flag_type VAdcHalGetStatus(VAdcHalInterfaceType *piVAdcHal, VAdcStatusType *pStatus)
{
   pm_err_flag_type result;
   uint8 aucData[1];

   result = VAdc_ReadBytes(piVAdcHal,
                           PMIO_ADDR(STATUS1),
                           aucData,
                           ARRAY_LENGTH(aucData));
   
   if (result != PM_ERR_FLAG_SUCCESS)
   {
      return result;
   }

   /* Just use EOC bit for status, parallel conversion renders imm_req_sts 
    * bit obselete */
   pStatus->eConversionStatus = (VAdcConversionStatusType)(PMIO_GET_FVAL(STATUS1, EOC, aucData[0]));

   return PM_ERR_FLAG_SUCCESS;
}

/* Temporarily comment the IRQ config */
#if 0
pm_err_flag_type VAdcHalConfigInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 ucIntrMask, VAdcInterruptConfigType eConfig)
{
   pm_err_flag_type result;
   uint8 aucData[3];

   result = VAdc_ReadBytes(piVAdcHal, PMIO_ADDR(INT_SET_TYPE), aucData, ARRAY_LENGTH(aucData));
   if (result != PM_ERR_FLAG_SUCCESS)
   {
      return result;
   }

   switch (eConfig)
   {
      case VADC_INTERRUPT_CONFIG_LEVEL_HIGH:
         aucData[0] &= ~ucIntrMask;
         aucData[1] |= ucIntrMask;
         aucData[2] &= ~ucIntrMask;
         break;
      case VADC_INTERRUPT_CONFIG_LEVEL_LOW:
         aucData[0] &= ~ucIntrMask;
         aucData[1] &= ~ucIntrMask;
         aucData[2] |= ucIntrMask;
         break;
      case VADC_INTERRUPT_CONFIG_RISING_EDGE:
         aucData[0] |= ucIntrMask;
         aucData[1] |= ucIntrMask;
         aucData[2] &= ~ucIntrMask;
         break;
      case VADC_INTERRUPT_CONFIG_FALLING_EDGE:
         aucData[0] |= ucIntrMask;
         aucData[1] &= ~ucIntrMask;
         aucData[2] |= ucIntrMask;
         break;
      default:
         return PM_ERR_FLAG_INVALID_PARAMETER ;
   }

   return VAdc_WriteBytes(piVAdcHal, PMIO_ADDR(INT_SET_TYPE), aucData, ARRAY_LENGTH(aucData));
}

pm_err_flag_type VAdcHalGetPendingInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 *pucIntrMask)
{
   pm_err_flag_type result;
   uint8 aucData[1];

   result = VAdc_ReadBytes(piVAdcHal, PMIO_ADDR(INT_LATCHED_STS), aucData, ARRAY_LENGTH(aucData));

   if (result != PM_ERR_FLAG_SUCCESS)
   {
      return result;
   }

   *pucIntrMask = aucData[0];

   return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type VAdcHalClearInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 ucIntrMask)
{
   uint8 aucData[1];

   aucData[0] = ucIntrMask;

   return VAdc_WriteBytes(piVAdcHal, PMIO_ADDR(INT_LATCHED_CLR), aucData, ARRAY_LENGTH(aucData));
}

pm_err_flag_type VAdcHalEnableInterrupts(VAdcHalInterfaceType *piVAdcHal, uint8 ucIntrMask)
{
   uint8 aucData[1];

   aucData[0] = ucIntrMask;

   return VAdc_WriteBytes(piVAdcHal, PMIO_ADDR(INT_EN_SET), aucData, ARRAY_LENGTH(aucData));
}

pm_err_flag_type VAdcHalSetInterruptMid(VAdcHalInterfaceType *piVAdcHal, uint32 uIntrMid)
{
   uint8 aucData[1];

   aucData[0] = PMIO_FVAL(INT_MID_SEL, INT_MID_SEL, (uint8)uIntrMid);

   return VAdc_WriteBytes(piVAdcHal, PMIO_ADDR(INT_MID_SEL), aucData, ARRAY_LENGTH(aucData));
}
#endif

pm_err_flag_type VAdcHalSetEnable(VAdcHalInterfaceType *piVAdcHal, VAdcEnableType eEnable)
{
   return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type VAdcHalRequestConversion(VAdcHalInterfaceType *piVAdcHal, VAdcConversionParametersType *pParams, uint32 *puConvTimeUs)
{
   pm_err_flag_type result;
   uint8 aucData[5];
   uint8 sidData[3];
   uint8 uHwSettle;

   /* Check to make sure the ADC_PBS is free to accept a new request 
    * 1. PBS_TRIG_SET is 0 
    * 2. HS is bit[0] is set READY. 
    */
   result = VAdcHalGetHSStatus(piVAdcHal, ADC_SDAM_HS_POLL_TIME_MAX_US, FALSE);
   if (result)
   {
      return PM_ERR_FLAG_FAILURE;
   }

   /* ADC channel config */
   aucData[0] = PMIO_FVAL(ADC_DIG_PARAM, CAL_SEL, (uint8)pParams->eCalMethod) |
                PMIO_FVAL(ADC_DIG_PARAM, DEC_RATIO_SEL, (uint8)pParams->eDecimationRatio);

   aucData[1] = PMIO_FVAL(FAST_AVG, FAST_AVG_EN, PMIO_VAL(FAST_AVG, FAST_AVG_EN, FAST_AVG_ENABLED)) |
                PMIO_FVAL(FAST_AVG, FAST_AVG_SAMPLES, (uint8)pParams->eAverageMode);

   aucData[2] = PMIO_FVAL(ADC_CH_SEL_CTL, ADC_CH_SEL, (uint8)pParams->uChannel);

   switch (pParams->eSettlingDelay)
   {
      case VADC_SETTLING_DELAY_0_US:
         uHwSettle = 0;
         break;
      case VADC_SETTLING_DELAY_100_US:
         uHwSettle = 1;
         break;
      case VADC_SETTLING_DELAY_200_US:
         uHwSettle = 2;
         break;
      case VADC_SETTLING_DELAY_300_US:
         uHwSettle = 3;
         break;
      case VADC_SETTLING_DELAY_400_US:
         uHwSettle = 4;
         break;
      case VADC_SETTLING_DELAY_500_US:
         uHwSettle = 5;
         break;
      case VADC_SETTLING_DELAY_600_US:
         uHwSettle = 6;
         break;
      case VADC_SETTLING_DELAY_700_US:
         uHwSettle = 7;
         break;
      case VADC_SETTLING_DELAY_800_US:
      case VADC_SETTLING_DELAY_900_US:
      case VADC_SETTLING_DELAY_1_MS:
         uHwSettle = 8;
         break;
      case VADC_SETTLING_DELAY_2_MS:
         uHwSettle = 9;
         break;
      case VADC_SETTLING_DELAY_4_MS:
         uHwSettle = 10;
         break;
      case VADC_SETTLING_DELAY_6_MS:
      case VADC_SETTLING_DELAY_8_MS:
         uHwSettle = 11;
         break;
      case VADC_SETTLING_DELAY_10_MS:
      case VADC_SETTLING_DELAY_16_MS:
         uHwSettle = 12;
         break;
      case VADC_SETTLING_DELAY_32_MS:
         uHwSettle = 13;
         break;
      case VADC_SETTLING_DELAY_64_MS:
         uHwSettle = 14;
         break;
      case VADC_SETTLING_DELAY_128_MS:
         uHwSettle = 15;
         break;
      default:
         uHwSettle = 0;
   }

   aucData[3] = PMIO_FVAL(DELAY_CTL, HW_SETTLE_DELAY, uHwSettle);
   aucData[4] = 0;

   sidData[0] = PMIO_FVAL(SID, SID, (uint8)pParams->uSid);
   sidData[1] = ((uint8)0x80); /* cov_req bit[7] and ch_id bit[2:0] - Imm. conv dedicated to ch 0 */
   sidData[2] = 1; /* Immidiate conversion - set TIMER_SEL to 1 */

   result = VAdc_WriteBytes(piVAdcHal, PMIO_ADDR(SID), sidData, 3);
   if (result != PM_ERR_FLAG_SUCCESS)
   {
      return result;
   }

   result = VAdc_WriteBytes(piVAdcHal, PMIO_ADDR(ADC_DIG_PARAM), aucData, ARRAY_LENGTH(aucData));
   if (result != PM_ERR_FLAG_SUCCESS)
   {
      return result;
   }

   /* Trigger PBS */
   result = VAdcHalTriggerPBS (piVAdcHal);
   if (result != PM_ERR_FLAG_SUCCESS)
   {
      return result;
   }

   *puConvTimeUs = VAdcHalGetConversionTime(pParams);

   return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type VAdcHalGetConversionCode(VAdcHalInterfaceType *piVAdcHal, uint32 *puCode)
{
   pm_err_flag_type result;
   uint8 aucData[2];

   result = VAdc_ReadBytes(piVAdcHal, PMIO_ADDR(CH_0_DATA0), aucData, ARRAY_LENGTH(aucData));
   if (result != PM_ERR_FLAG_SUCCESS)
   {
      return result;
   }

   *puCode = (aucData[1] << 8) | aucData[0];

   return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type VAdcHalDumpRegisters(VAdcHalInterfaceType *piVAdcHal, VAdcHalRegDumpType *pVAdcRegDump)
{
   pm_err_flag_type result;
   uint8 aucData[1];
   uint32 uOffset;
   uint32 uReg;

   for (uReg = 0; uReg < VADC_HAL_NUM_REGISTERS_TO_DUMP; uReg++)
   {
      uOffset = gaucRegDumpAddresses[uReg];

      result = VAdc_ReadBytes(piVAdcHal, uOffset, aucData, ARRAY_LENGTH(aucData));
      if (result != PM_ERR_FLAG_SUCCESS)
      {
         return result;
      }

      g_aVAdcRegDump[uReg].ucOffset = (uint8)uOffset;
      g_aVAdcRegDump[uReg].ucVal = aucData[0];

   }
   pVAdcRegDump->aVAdcReg = g_aVAdcRegDump;
   pVAdcRegDump->reg_size = VADC_HAL_NUM_REGISTERS_TO_DUMP;
   return PM_ERR_FLAG_SUCCESS;
}

