/*============================================================================
  FILE:         VAdcCommon.c

  OVERVIEW:     Common scaling functions and helper functions for VADC.

  DEPENDENCIES: None

                Copyright (c) 2015-2016, 2018, 2020-2021 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/adc/devices/common/src/VAdcCommon.c#1 $$DateTime: 2022/08/18 10:15:46 $$Author: pwbldsvc $

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2016-08-12  jjo  Pass pointer to scaling table.
  2015-08-20  jjo  Initial version.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "VAdcCommon.h"
#include "AdcScalingUtil.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define ADC_UV_PER_MV 1000
#define FLOOR(x) (x < 0 ? 0 : x)

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

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
/*======================================================================

  FUNCTION        VAdcScaleCodeToPercent

  DESCRIPTION     Scales the ADC result from code to percent (0 to
                  0xffff).

  DEPENDENCIES    None

  PARAMETERS
      uFullScale_code   [in]  full-scale ADC code
      nCode        [in]  the raw ADC code
      puPercent    [out] the value in percent (0 to 0xffff)

  RETURN VALUE    None

  SIDE EFFECTS    None

======================================================================*/
static void
VAdcScaleCodeToPercent(
   uint32 uFullScale_code,
   int32 nCode,
   uint32 *puPercent
   )
{
   /* Note: max ADC code before overflow is 0x10000, which is far beyond
      the full scale reading of 0x4000 */
   uint32 uCode = ABS(nCode);
   *puPercent = (uCode * 0xffff) / uFullScale_code;

   return;
}

/*======================================================================

  FUNCTION        VAdcScaleCodeToMicrovolts

  DESCRIPTION     Scales the ADC result from code to microvolts.

  DEPENDENCIES    None

  PARAMETERS
      pScaling         [in] AMUX scaling
      uFullScale_code  [in] full-scale ADC code
      uFullScale_uV    [in] full-scale uV value
      nCode        [in]  the raw ADC code
      pnMicrovolts [out] the value in microvolts

  RETURN VALUE    None

  SIDE EFFECTS    None

======================================================================*/
static void
VAdcScaleCodeToMicrovolts(
   const VAdcChannelScalingFactor *pScaling,
   uint32 uFullScale_code,
   uint32 uFullScale_uV,
   int32 nCode,
   int32 *pnMicrovolts
   )
{
   int64 n64Code = nCode;
   int64 n64Microvolts;

   n64Microvolts = (n64Code * uFullScale_uV) / uFullScale_code;


   /*
    * Since PMIC AMUX channels have a prescalar gain applied to the input,
    * we need to scale input by inverse of the channel prescalar gain to
    * obtain the actual input voltage.
    */
   n64Microvolts *= pScaling->uDenominator;
   n64Microvolts /= pScaling->uNumerator;

   *pnMicrovolts = (int32)n64Microvolts;

   return;
}

/*======================================================================

  FUNCTION        VAdcScaleCodeToMicrovoltsInverse

  DESCRIPTION     Scales the ADC result from microvolts to code.

  DEPENDENCIES    None

  PARAMETERS
      pScaling         [in] AMUX scaling
      uFullScale_code  [in] full-scale ADC code
      uFullScale_uV    [in] full-scale uV value
      uMicrovolts      [in] the value in microvolts
      puCode           [out] the raw ADC code

  RETURN VALUE    None

  SIDE EFFECTS    None

======================================================================*/
static void
VAdcScaleCodeToMicrovoltsInverse(
   const VAdcChannelScalingFactor *pScaling,
   uint32 uFullScale_code,
   uint32 uFullScale_uV,
   int32 nMicrovolts,
   int32 *pnCode
   )
{
   int64 n64Code;
   int64 n64Microvolts = nMicrovolts;

   /* First, remove the prescalar gain */
   n64Microvolts *= pScaling->uNumerator;
   n64Microvolts /= pScaling->uDenominator;

   n64Code = (n64Microvolts * uFullScale_code) / uFullScale_uV;
   *pnCode = (int32)n64Code;

   return;
}

static AdcDeviceResultStatusType
VAdcScaleCodeToResistance(
   uint32 uFullScale_code,
   uint32 uPullUp,
   int32 nCode,
   int32 *pnResistance
   )
{
   int64 n64FS = uFullScale_code;
   int64 n64PU = uPullUp;
   int64 n64Code = FLOOR(nCode);  /* Will not have negative voltage */
   int64 n64R;

   if (nCode == uFullScale_code)
   {
      /* Avoid division by zero */
      *pnResistance = 0x7fffffff;
      return ADC_DEVICE_RESULT_VALID;
   }

   /* Apply voltage divider equation */
   n64R = (n64PU * n64Code) / (n64FS - n64Code);

   if (n64R > 0x7fffffff)
   {
      /* Avoid overflow */
      *pnResistance = 0x7fffffff;
      return ADC_DEVICE_RESULT_VALID;
   }

   *pnResistance = (int32)n64R;

   return ADC_DEVICE_RESULT_VALID;
}

static AdcDeviceResultStatusType
VAdcScaleResistanceToCode(
   uint32 uFullScale_code,
   uint32 uPullUp,
   int32 nResistance,
   int32 *pnCode
   )
{
   int64 n64FS = uFullScale_code;
   int64 n64PU = uPullUp;
   int64 n64R = nResistance;
   int64 n64Code;

   if (nResistance < 0)
   {
      return ADC_DEVICE_RESULT_INVALID;
   }

   /* Apply voltage divider equation */
   n64Code = (n64FS * n64R) / (n64R + n64PU);

   *pnCode = (int32)n64Code;

   return ADC_DEVICE_RESULT_VALID;
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
/*======================================================================

  FUNCTION        VAdcProcessConversionResult

  DESCRIPTION     This function is called at the end of conversion to process
                  the result. The raw result is converted into a scaled 16-bit
                  result and then and the scaled result is converted into
                  physical units in millivolts. Further scaling may be
                  performed by the scaling function defined in the BSP.

  DEPENDENCIES    None

  PARAMETERS
      pScaling         [in] AMUX scaling
      eScalingMethod   [in] scaling method
      pIntTable        [in] scaling table
      uPullUp          [in] pull up resistor value
      uFullScale_code  [in] full-scale ADC code
      uFullScale_uV    [in] full-scale uV value
      uFullRatiometric_code    [in] full-scale Ratiometric value
      uCode        [in]  the raw ADC code
      puMicrovolts [out] the value in microvolts

  RETURN VALUE    None

  SIDE EFFECTS    None

======================================================================*/
void
VAdcProcessConversionResult(
   const VAdcChannelScalingFactor *pScaling,
   VAdcScalingMethodType eScalingMethod,
   const AdcIntTableType *pIntTable,
   uint32 uPullUp,
   int32  nOffset,
   uint32 uFullScale_code,
   uint32 uFullScale_uV,
   uint32 uFullRatiometric_code,
   uint32 uCode,
   AdcDeviceResultType *pResult
   )
{
   int32 nCode = (int32)uCode;
   int32 nMicrovolts;
   
   pResult->eStatus = ADC_DEVICE_RESULT_VALID;
   pResult->uCode = uCode;

   VAdcScaleCodeToPercent(uFullScale_code,
                          nCode,
                          &pResult->uPercent);

   VAdcScaleCodeToMicrovolts(pScaling,
                             uFullScale_code,
                             uFullScale_uV,
                             nCode,
                             &nMicrovolts);
   pResult->uMicrovolts = FLOOR(nMicrovolts);

   /* By default, scale the physical result in units of millivolts */
   pResult->nPhysical = AdcDivideWithRounding(nMicrovolts, ADC_UV_PER_MV);

   /* Call the BSP scaling function (if present) */
   switch (eScalingMethod)
   {
      case VADC_SCALE_TO_MILLIVOLTS:
         /* by default, nPhysical is in millivolts */
         break;
      case VADC_SCALE_THERMISTOR:
         pResult->eStatus = VAdcScaleThermistor(pResult->uCode,
                                                0,
                                                uFullRatiometric_code,
                                                uPullUp,
                                                pIntTable->pTable,
                                                pIntTable->uLength,
                                                &pResult->nPhysical);
         break;
      case VADC_SCALE_INTERPOLATE_FROM_MILLIVOLTS:
         pResult->eStatus = AdcMapLinearInt32toInt32(pIntTable->pTable,
                                                     pIntTable->uLength,
                                                     pResult->nPhysical,
                                                     &pResult->nPhysical);
         break;
      case VADC_SCALE_INTERPOLATE_FROM_MICROVOLTS:
         pResult->eStatus = AdcMapLinearInt32toInt32(pIntTable->pTable,
                                                     pIntTable->uLength,
                                                     pResult->uMicrovolts,
                                                     &pResult->nPhysical);
         break;
      case VADC_SCALE_RESISTOR_DIVIDER:
         pResult->eStatus = VAdcScaleCodeToResistance(uFullRatiometric_code,
                                                      uPullUp,
                                                      nCode,
                                                      &pResult->nPhysical);
         break;
      default:
         /* By default, nPhysical is in millivolts */
         break;
   }

   /* Scale the output according to the offset */
   pResult->nPhysical += nOffset;

   return;
}

/*======================================================================

  FUNCTION        VAdcProcessConversionResultInverse

  DESCRIPTION     Inverse of VAdc_ProcessConversionResultInverse.

  DEPENDENCIES    None

  PARAMETERS
      pScaling         [in] AMUX scaling
      eScalingMethod   [in] scaling method
      pIntTable        [in] scaling table
      uPullUp          [in] pull up resistor value
      uFullScale_code  [in] full-scale ADC code
      uFullScale_uV    [in] full-scale uV value
      uFullRatiometric_code    [in] full-scale Ratiometric value
      nPhysical        [in]  the physical value
      puMicrovolts [out] the value in microvolts

  RETURN VALUE    None

  SIDE EFFECTS    None

======================================================================*/
void
VAdcProcessConversionResultInverse(
   const VAdcChannelScalingFactor *pScaling,
   VAdcScalingMethodType eScalingMethod,
   const AdcIntTableType *pIntTable,
   uint32 uPullUp,
   int32  nOffset,
   uint32 uFullScale_code,
   uint32 uFullScale_uV,
   uint32 uFullRatiometric_code,
   int32 nPhysical,
   AdcDeviceResultType *pResult
   )
{
   boolean bHaveCode = FALSE;
   int32 nMillivolts;
   int32 nMicrovolts;
   int32 nCode;

   pResult->eStatus = ADC_DEVICE_RESULT_VALID;
   pResult->nPhysical = nPhysical - nOffset;

   /* Remaining: eStatus, uMicrovolts, uCode, uPercent */

   /* Reverse the BSP scaling */
   switch (eScalingMethod)
   {
      case VADC_SCALE_THERMISTOR:
         pResult->eStatus = VAdcScaleThermistorInverse(pResult->nPhysical,
                                                       0,
                                                       uFullRatiometric_code,
                                                       uPullUp,
                                                       pIntTable->pTable,
                                                       pIntTable->uLength,
                                                       &pResult->uCode);
         if (pResult->eStatus != ADC_DEVICE_RESULT_VALID)
         {
            return;
         }

			nCode = pResult->uCode;
         VAdcScaleCodeToMicrovolts(pScaling,
                                   uFullScale_code,
                                   uFullScale_uV,
                                   nCode,
                                   &nMicrovolts);
         pResult->uMicrovolts = FLOOR(nMicrovolts);
         bHaveCode = TRUE;
         /* Remaining: uPercent */

         break;
      case VADC_SCALE_INTERPOLATE_FROM_MICROVOLTS:
         /* Gets uV, in this case nMillivolts is holding uV instead of mV */
         pResult->eStatus = AdcMapLinearInt32toInt32Inverse(pIntTable->pTable,
                                                            pIntTable->uLength,
                                                            pResult->nPhysical,
                                                            &nMicrovolts);
         if (pResult->eStatus != ADC_DEVICE_RESULT_VALID)
         {
            return;
         }

         pResult->uMicrovolts = (uint32)(nMicrovolts);

         break;
      case VADC_SCALE_INTERPOLATE_FROM_MILLIVOLTS:
         /* Gets mV */
         pResult->eStatus = AdcMapLinearInt32toInt32Inverse(pIntTable->pTable,
                                                            pIntTable->uLength,
                                                            pResult->nPhysical,
                                                            &nMillivolts);
         if (pResult->eStatus != ADC_DEVICE_RESULT_VALID)
         {
            return;
         }

         nMicrovolts = nMillivolts * ADC_UV_PER_MV;
         pResult->uMicrovolts = (uint32)(nMicrovolts);
         /* Remaining: uCode, uPercent */

         break;
      case VADC_SCALE_RESISTOR_DIVIDER:
         pResult->eStatus = VAdcScaleResistanceToCode(uFullRatiometric_code,
                                                      uPullUp,
                                                      pResult->nPhysical,
                                                      &nCode);
         if (pResult->eStatus != ADC_DEVICE_RESULT_VALID)
         {
            return;
         }
         
         pResult->uCode = (uint32) nCode;

         VAdcScaleCodeToMicrovolts(pScaling,
                                   uFullScale_code,
                                   uFullScale_uV,
                                   nCode,
                                   &nMicrovolts);

         pResult->uMicrovolts = FLOOR(nMicrovolts);
         bHaveCode = TRUE;
         /* Remaining: uPercent */

         break;
      default:
         /* By default, nPhysical is in millivolts */
         nMicrovolts = pResult->nPhysical * ADC_UV_PER_MV;
         pResult->uMicrovolts = FLOOR(nMicrovolts);
         /* Remaining: uCode, uPercent */

         break;
   }

   /* Restore offset adjustement */
   pResult->nPhysical = nPhysical;

   if (!bHaveCode)
   {
      VAdcScaleCodeToMicrovoltsInverse(pScaling,
                                       uFullScale_code,
                                       uFullScale_uV,
                                       nMicrovolts,
                                       &nCode);
      pResult->uCode = (uint32)nCode;
      /* Remaining: uPercent */
   }

   /* Calculate the value in percent (0 to 0xffff) */
   VAdcScaleCodeToPercent(uFullScale_code,
                          nCode,
                          &pResult->uPercent);

   return;
}

