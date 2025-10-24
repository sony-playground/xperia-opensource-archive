#ifndef __VADC_COMMON_H__
#define __VADC_COMMON_H__
/*============================================================================
  @file VAdcCommon.h

  Common scaling functions and helper functions for VADC.

                Copyright (c) 2015-2021 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/* $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/adc/devices/common/protected/VAdcCommon.h#1 $ */

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "AdcScalingBsp.h"
#include "DDIAdcDevice.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
void
VAdcProcessConversionResult(
   const VAdcChannelScalingFactor *pScaling,
   VAdcScalingMethodType eScalingMethod,
   const AdcIntTableType *pIntTable,
   uint32 uPullUp,
   int32 nOffset,
   uint32 uFullScale_code,
   uint32 uFullScale_uV,
   uint32 uFullRatiometric_code,
   uint32 uCode,
   AdcDeviceResultType *pResult
   );

void
VAdcProcessConversionResultInverse(
   const VAdcChannelScalingFactor *pScaling,
   VAdcScalingMethodType eScalingMethod,
   const AdcIntTableType *pIntTable,
   uint32 uPullUp,
   int32 nOffset,
   uint32 uFullScale_code,
   uint32 uFullScale_uV,
   uint32 uFullRatiometric_code,
   int32 nPhysical,
   AdcDeviceResultType *pResult
   );

#endif /* #ifndef __VADC_COMMON_H__ */

